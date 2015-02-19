<?php
include_once 'models/Model.inc';
include_once 'include/util.inc';

//Class code taken from file example by Scott Sharkey cs.franklin.edu/~sharkesc
class File extends Model {

    private $dir;
    private $origName;
    private $nameOnDisk;
    private $type;
    private $size;
    private $questionId;

    public function __construct($fields) {
        parent::__construct($fields);
        $this -> setDir(safeParam($fields, 'dir'));
        $this -> setOrigName(safeParam($fields, 'origName'));
        $this -> setNameOnDisk(safeParam($fields, 'nameOnDisk'));
        $this -> setType(safeParam($fields, 'type'));
        $this -> setSize(safeParam($fields, 'size'));
        $this -> setQuestionId(safeParam($fields, 'questionId'));
    }

    public function fullPath() {
        return $this -> dir . DIRECTORY_SEPARATOR . $this -> nameOnDisk;
    }

    private function removeFromDisk() {
        $path = $this -> fullPath();
        if (is_file($path)) {
            unlink($path);
        }
    }

    private function moveOnDisk($to) {
        $old = $this -> fullPath();
        $new = $this -> dir . DIRECTORY_SEPARATOR . $to;
        if (is_file($old)) {
            rename($old, $new);
        }
        $this -> nameOnDisk = $to;
        return $this;
    }

    public function setDir($dir) {
        $this -> dir = $dir;
        return $this;
    }

    public function setOrigName($origName) {
        $this -> origName = $origName;
        return $this;
    }

    public function setNameOnDisk($nameOnDisk) {
        $this -> nameOnDisk = $nameOnDisk;
        return $this;
    }

    public function setType($type) {
        $this -> type = $type;
        return $this;
    }

    public function setSize($size) {
        $this -> size = $size;
        return $this;
    }

    public function setQuestionId($questionId) {
        $this -> questionId = $questionId;
        return $this;
    }

    public function getDir() {
        return $this -> dir;
    }

    public function getOrigName() {
        return $this -> origName;
    }

    public function getNameOnDisk() {
        return $this -> nameOnDisk;
    }

    public function getType() {
        return $this -> type;
    }

    public function getSize() {
        return $this -> size;
    }

    public function getQuestionId() {
        return $this -> questionId;
    }

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('dir', $this -> dir, "Directory is required");
        $validator -> required('origName', $this -> origName, "Original name is required");
        $validator -> required('nameOnDisk', $this -> nameOnDisk, "Name on disk is required");
        $validator -> required('type', $this -> type, "Type is required");
        $validator -> required('size', $this -> size, "Size is required");
        $validator -> required('questionId', $this -> questionId, "Question ID is required");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    private static function fromRows($rows) {
        $result = array();
        foreach ($rows as $row) {
            $result[] = new File($row);
        }
        return $result;
    }

    static function findById($id) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM file WHERE id = :id');
        $st -> bindParam(':id', $id);
        $st -> execute();
        $row = $st -> fetch(PDO::FETCH_ASSOC);
        return new File($row);
    }

    static function findByQuestionId($questionId) {
        $db = Db::getDb();
        $st = $db -> prepare('SELECT * FROM file WHERE questionId = :questionId');
        $st -> bindParam(':questionId', $questionId);
        $st -> execute();
        $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
        return self::fromRows($rows);
    }

    function insert() {
        $this -> validate(true);
        $db = Db::getDb();
        $statement = $db -> prepare("INSERT INTO file (dir, origName, nameOnDisk, type, size, questionId) values (:dir, :origName, :nameOnDisk, :type, :size, :questionId)");
        $statement -> bindParam(':dir', $this -> dir);
        $statement -> bindParam(':origName', $this -> origName);
        $statement -> bindParam(':nameOnDisk', $this -> nameOnDisk);
        $statement -> bindParam(':type', $this -> type);
        $statement -> bindParam(':size', $this -> size);
        $statement -> bindParam(':questionId', $this -> questionId);
        $statement -> execute();
        $this -> id = $db -> lastInsertId();
        return $this;
    }

    function update() {
        $this -> validate(true);
        $db = Db::getDb();
        $statement = $db -> prepare("UPDATE file SET dir = :dir, origName = :origName, nameOnDisk = :nameOnDisk, type = :type, size = :size, questionId = :questionId WHERE id = :id");
        $statement -> bindParam(':dir', $this -> dir);
        $statement -> bindParam(':origName', $this -> origName);
        $statement -> bindParam(':nameOnDisk', $this -> nameOnDisk);
        $statement -> bindParam(':type', $this -> type);
        $statement -> bindParam(':size', $this -> size);
        $statement -> bindParam(':questionId', $this -> questionId);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    function delete() {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM file WHERE id = :id");
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        $this->removeFromDisk();
    }

}
?>