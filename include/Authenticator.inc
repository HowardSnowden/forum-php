<?php
include_once "models/Db.inc";
include_once "models/Permission.inc";
include_once "include/util.inc";
//Class code taken from authenticator example by Scott Sharkey cs.franklin.edu/~sharkesc
class Authenticator {

    private $cache;
    private static $instance;

    // @formatter:off
    const PERMS_QUERY =
        "SELECT DISTINCT permissions.id as id, permissions.name as name
         FROM
            user, usergroups, groups, grouppermissions, permissions
         WHERE
            user.id = :userId AND
            user.id = usergroups.userId AND
            usergroups.groupId = groups.id AND
            groups.id = grouppermissions.groupId AND
            grouppermissions.permissionId = permissions.id";
    // @formatter:on

    private function __construct() {
        $cache = array();
    }

    public static function instance() {
        if (!isset(self::$instance)) {
            self::$instance = new Authenticator();
        }
        return self::$instance;
    }

    private function realUserId($userId) {
        if (isset($userId) && is_numeric($userId)) {
            return $userId;
        }
        if (gettype($userId) == 'object') {
            return $userId -> getId();
        }
        return currentUser();
    }

    public function can($permissionKey, $userId = false, $itemId=false) {
        $userId = $this -> realUserId($userId);
        $permissions = $this -> permissionsFor($userId);
        foreach ($permissions as $permission) {
            if ($permission -> getName() === $permissionKey) {
                return true;
            }
        }
        if ($itemId){
            if (isOwner($itemId)){
                return true;
            }
        }
        return false;
    }

    private function permissionsFor($userId) {
        if (!isset($this -> cache[$userId])) {
            $db = Db::getDb();
            $st = $db -> prepare(self::PERMS_QUERY);
            $st -> bindParam(':userId', $userId);
            $st -> execute();
            $this -> cache[$userId] = Permission::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
        }
        return $this -> cache[$userId];
    }

    public function ensure($permissionKey, $userId = false, $itemId = false) {
        if (!$this -> can($permissionKey, $userId, $itemId)) {
            $userId = $this -> realUserId($userId);
            Logger::instance() -> warn("User $userId attempted unauthorized operation $permissionKey");
            die("You do not have permission to access this resource.  This attempt has been logged.");
        }
    }

}
?>