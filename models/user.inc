<?php


include_once 'models/validator.inc';
include_once 'models/Model.inc';
include_once 'models/Group.inc';

function isValidUser($email, $password){
   $valid = User::findByEmailAndPassword($email, $password);
   if (!empty($valid)){
    return true;
    }
    
    else {
    return false;
    }
    }

class User extends Model {

    private $firstName;
    private $lastName;
    private $email;
    private $password;

 public function __construct($fields = array()){
    parent::__construct($fields);
    $this->setFirstName(safeParam($fields, 'first_name'));
    $this->setLastName(safeParam($fields, 'last_name'));
    $this->setEmail(safeParam($fields, 'email'));
    $this->setPassword(safeParam($fields, 'password'));
    
    }

 

    private function clean() {
        $this -> first_name = htmlentities($this -> first_name, ENT_QUOTES);
        $this -> last_name = htmlentities($this -> last_name, ENT_QUOTES);
        $this -> email = htmlentities($this -> email);
    }
    
        public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('first_name', $this -> first_name, "First name is required");
        $validator -> required('last_name', $this -> last_name, "Last name is required");
        $validator -> email('email', $this -> email, "Invalid email address");
        $validator -> password('password', $this -> password, "Password must be at least 8 chars, have an upper case character, a symbol, and a number");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }

    public function getFullName() {
        return "{$this->first_name} {$this->last_name}";
    }

    public function setFirstName($firstName){
        $this -> first_name = trim($firstName);
    }

    public function getFirstName() {
        return $this -> first_name;
    }

    public function setLastName($lastName) {
        $this -> last_name = trim($lastName);
    }

    public function getlastName() {
        return $this -> last_name;
    }

    public function setEmail($email) {
        $this -> email = trim($email);
    }

    public function getEmail() {
        return $this -> email;
    }

    public function setPassword($password) {
        $this -> password = trim($password);
    }

    public function getPassword() {
        return $this -> password;
    }


    public static function fromRows($rows){
        $result = array();
        foreach ($rows as $row) {
            $result[] = new User($row);
        }
        return $result;
    }

    public static function findById($id){
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM user WHERE id = :user_id");
        $st -> bindParam(':user_id', $id);
        $st -> execute();
        return new User($st -> fetch(PDO::FETCH_ASSOC));
    }

    public function insert() {
        $db = Db::getDb();
        $this->clean();
        $statement = $db -> prepare("INSERT INTO user (first_name, last_name, email, password) VALUES (:first_name, :last_name, :email, :password)");
        $statement -> bindParam(':first_name', $this -> first_name);
        $statement -> bindParam(':last_name', $this -> last_name);
        $statement -> bindParam(':email', $this -> email);
        $statement -> bindParam(':password', $this -> password);
        $statement -> execute();
        $this -> id=$db->lastInsertId();
        
        $group = Group::findByName('Users');
        $group -> addUser($this);


        return $this;
    }

    public function update() {
        $db = Db::getDb();
        $this -> clean();
        $statement = $db -> prepare("UPDATE user SET first_name=:first_name, last_name=:last_name, email=:email, password=:password WHERE id=:id");
        $statement -> bindParam(':first_name', $this -> first_name);
        $statement -> bindParam(':last_name', $this -> last_name);
        $statement -> bindParam(':email', $this -> email);
        $statement -> bindParam(':password', $this -> password);
        $statement -> bindParam(':id', $this -> id);
        $statement -> execute();
        return $this;
    }

    public function delete() {
        self::deleteById($this -> getId());
    }

    private static function deleteById($id) {
        $db = Db::getDb();
        $statement = $db -> prepare("DELETE FROM user WHERE id = :id");
        $statement -> bindParam(':id', $id);
        $statement -> execute();
    }
    
    function deletePosts($id){
    $db=Db::getDb();

    $st =$db->prepare("DELETE FROM questions WHERE user_id = :user_id");
	
	$st -> bindParam(':user_id', $id);
	$st -> execute();
    }


    public static function findAll() {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM user");
        $st -> execute();
        return self::fromRows($st -> fetchAll(PDO::FETCH_ASSOC));
    }

    public static function findByEmail($email) {
        $db = Db::getDb();
        $st = $db -> prepare("SELECT * FROM user WHERE email = :email");
        $st -> bindParam(':email', $email);
        $st -> execute();
        return new User($st -> fetch(PDO::FETCH_ASSOC));
    }

    public static function findByEmailAndPassword($email, $password) {
        $user = self::findByEmail($email);
        if ($user -> getPassword() === $password) {
            return $user;
        }
        return false;
    }

    public function insertOrUpdate() {
        $login = !$this -> id;
        $user = parent::insertOrUpdate();
        if ($login) {
            $_SESSION['userid'] = $user -> getId();
        }
    }

}
?>
    