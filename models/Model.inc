<?php
require_once "models/Db.inc";
require_once "include/util.inc";

//Class code taken from ToDoUpload example by Scott Sharkey cs.franklin.edu/~sharkesc
abstract class Model {
    protected $id;

    public function __construct($fields = array()) {
        $id = safeParam($fields, 'id');
        if ($id && is_numeric($id)) {
            $this -> setId($id);
        }
    }

    public function getId() {
        return $this -> id;
    }

    public function setId($id) {
        $this -> id = $id;
        return $this;
    }

    protected static function adHocQuery($q) {
        $db = Db::getDb();
        $st = $db -> prepare($q);
        $st -> execute();
        return $st -> fetchAll(PDO::FETCH_ASSOC);
    }

    public function insertOrUpdate() {
        $db = Db::getDb();
        if ($this -> getId()) {
            $this -> update();
        } else {
            $this -> insert();
        }
        return $this;
    }

    public abstract function insert();
    public abstract function delete();
    public abstract function update();

}
?>
