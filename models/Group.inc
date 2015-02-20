<?php
include_once 'models/Model.inc';
include_once 'models/user.inc';
include_once 'models/Permission.inc';
include_once 'models/validator.inc';

//Class code taken from RBAC example by Scott Sharkey cs.franklin.edu/~sharkesc
class Group extends Model {

    protected $name;

    function __construct($fields = array()) {
        parent::__construct($fields);
        $this -> setName(safeParam($fields, 'name'));
    }

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('name', $this -> name, "Group name is required");
        if ($throw && $validator -> hasErrors()) {
            throw new Exception(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private function clean() {
        $this -> name = htmlentities($this -> name, ENT_QUOTES);
    }

    public function setName($name) {
        $this -> name = trim($name);
        return $this;
    }

    public function getName() {
        return $this -> name;
    }

    private static function fromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = new Group($row);
        }
        return $result;
    }

    public static function findAll() {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM groups ORDER BY name");
        $st -> execute();
        return self::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM groups WHERE id = :id");
        $st -> bindParam(':id', $id);
        $st -> execute();
        return new Group($st -> fetch(PDO::FETCH_ASSOC));
    }

    public static function findByName($name) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM groups WHERE name = :name");
        $st -> bindParam(':name', $name);
        $st -> execute();
        return new Group($st -> fetch(PDO::FETCH_ASSOC));
    }

    public function insert() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("INSERT INTO groups (name) VALUES (:name)");
        $statement -> bindParam(':name', $this -> name);
        $statement -> execute();
        $this -> setId($db -> lastInsertId());
        return $this;
    }

    public function update() {
        $db = Db::getDb();
        $this -> validate(true);
        $this -> clean();
        $statement = $db -> prepare("UPDATE groups SET name=:name WHERE id=:id");
        $statement -> bindParam(':name', $this -> name);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    public function delete() {
        self::deleteById($this -> getId());
    }

    private static function deleteById($id) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM groups WHERE id = :id");
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }

    public static function findByUserId($userId) {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM groups where groups.id in (SELECT groups.id from groups, usergroups WHERE groups.id = usergroups.groupId AND usergroups.userId = :userId) order by name");
        $statement -> bindParam(':userId', $userId);
        $statement -> execute();
        return self::fromRows($statement->fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findByNotUserId($userId) {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM groups where groups.id not in (SELECT groups.id from groups, usergroups WHERE groups.id = usergroups.groupId AND usergroups.userId = :userId) order by name");
        $statement -> bindParam(':userId', $userId);
        $statement -> execute();
        return self::fromRows($statement->fetchAll(PDO::FETCH_ASSOC));
    }

    public function addUser($user) {
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO usergroups (groupId, userId) VALUES (:groupId, :userId)");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':userId', $user -> getId());
        $statement -> execute();
    }

    public function removeUser($user) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM usergroups WHERE groupId = :groupId AND userId = :userId");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':userId', $user -> getId());
        $statement -> execute();
    }

    public function addPermission($permission) {
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO grouppermissions (groupId, permissionId) VALUES (:groupId, :permissionId)");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':permissionId', $permission -> getId());
        $statement -> execute();
    }

    public function removePermission($permission) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM grouppermissions WHERE permissionId = :permissionId AND groupId = :groupId");
        $statement -> bindValue(':groupId', $this -> getId());
        $statement -> bindValue(':permissionId', $permission -> getId());
        $statement -> execute();
    }

    public function getMembers() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT user.id AS id, user.first_name AS first_name, user.last_name AS last_name, user.password AS password FROM user, usergroups WHERE user.id = usergroups.userId and usergroups.groupId = :id ORDER BY last_name, first_name");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return User::fromRows($rows);
    }

    public function getNonMembers() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM user WHERE user.id not in (SELECT user.id FROM user, usergroups WHERE user.id = usergroups.userId and usergroups.groupId = :id) ORDER BY last_name, first_name;");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return User::fromRows($rows);
    }

    public function getPermissions() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT permissions.id AS id, permissions.name as name FROM permissions, grouppermissions WHERE permissions.id = grouppermissions.permissionId and grouppermissions.groupId = :id ORDER BY name");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return Permission::fromRows($rows);
    }

    public function getNonPermissions() {
        $db = Db::getDb();
        $statement = $db -> prepare("SELECT * FROM permissions WHERE permissions.id not in (SELECT permissions.id FROM permissions, grouppermissions WHERE permissions.id = grouppermissions.permissionId and grouppermissions.groupId = :id) ORDER BY name;");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $rows = $statement -> fetchAll(PDO::FETCH_ASSOC);
        return Permission::fromRows($rows);
    }

}
?>