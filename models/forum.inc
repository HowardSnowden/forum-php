<?php

include_once 'include/util.inc';
include_once 'models/validator.inc';
include_once 'models/Model.inc';

class Question extends Model{

    private $title;
    private $post;
    private $tags;
    private $user_id;
    private $post_date;
    
public function __construct($fields = array()){
    parent::__construct($fields);
    $this->setTitle(safeParam($fields, 'title'));
    $this->setPost(safeParam($fields, 'post'));
    $this->setTags(safeParam($fields, 'tags'));
    $this->setUserId(safeParam($fields, 'user_id'));
    $this->setDate(safeParam($fields, 'post_date'));
    }
public function getTitle(){
    return $this->title;
    }
public function setTitle($title){
    $this->title=$title;
    return $this;
    }
    
public function getPost(){
    return $this->post;
    }
public function setPost($post){
    $this->post=$post;
    return $this;
    }
    
public function getDate(){
    return $this->post_date;
    }
public function setDate($post_date){
    $this->post_date=$post_date;
    return $this;
    }

public function getTags(){
    return $this->tags;
    }
public function setTags($tags){
    $this->tags=$tags;
    return $this;
    }
public function getUserId(){
    return $this->user_id;
    }
public function setUserId($user_id){
    $this->user_id=$user_id;
    return $this;
    }
    
    

    public function validate($throw = false) {
        $validator = new Validator();
        $validator -> required('title', $this -> title, "Title is required");
        $validator -> required('post', $this -> post, "Content cannot be empty");
        if ($throw && $validator -> hasErrors()) {
            throw new IllegalStateException(implode(", ", $validator -> allErrors()));
        }
        return $validator;
    }
    
  private function clean() {
        $this -> post = htmlentities($this -> post, ENT_QUOTES);
        $this -> title = htmlentities($this-> title, ENT_QUOTES);
        $this -> tags = htmlentities($this -> tags, ENT_QUOTES);
    }
    
 private static function fromRows($rows){
        $result = array();
        foreach ($rows as $row) {
            $result[] = new Question($row);
        }
        return $result;
    }
    
 static function findAllPosts(){
	 $db=Db::getDb();
     $st = $db->prepare('SELECT * FROM questions ORDER BY post_date desc limit 5');
	$st -> execute();
    
    $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
     $db=null;
    return self::fromRows($rows);
     
 }
static function findPostById($id){
  	$db=Db::getDb();
	$st =$db->prepare("SELECT * FROM questions WHERE id = :id");
    $st -> bindParam(':id', $id);
    $st -> execute();
    $row=$st->fetch(PDO::FETCH_ASSOC);
    return new Question($row);
}

static function findUserPosts($id){
    $db = Db::getDb();
    $st = $db->prepare("SELECT * FROM questions WHERE user_id = :user_id");
    $st -> bindParam(':user_id', $id);
    $st -> execute();
    $rows = $st->fetchAll(PDO::FETCH_ASSOC);
    return self::fromRows($rows);

    }
    
static function findByTag($tag){
    $db = Db::getDb();
    $tag = "%{$tag}%";
    $st = $db->prepare("SELECT * FROM questions WHERE tags like :tags");
    $st -> bindParam(':tags', $tag);
    $st -> execute();
    $rows = $st->fetchAll(PDO::FETCH_ASSOC);
    return self::fromRows($rows);
}

function insert(){
	$db = Db::getDb();
    $this ->clean();
	$st = $db->prepare('INSERT INTO questions (post_date, title, post, tags, user_id) VALUES (date("now"), :title, :post, :tags, :user_id)');
	$st -> bindParam(':title', $this->title);
	$st -> bindParam(':post', $this->post);
	$st -> bindParam(':tags', $this->tags);
    $st -> bindParam(':user_id', $this->user_id);
	$st -> execute();
	$this->id=$db->lastInsertId();
    return $this;
}

function update(){
    $db=Db::getDb();
	$this ->clean();
	$st =$db->prepare('UPDATE questions SET title = :title, post = :post, tags = :tags WHERE id = :id');
	$st -> bindParam(':title', $this->title);
	$st -> bindParam(':post', $this->post);
	$st -> bindParam(':tags', $this->tags);
	$st -> bindParam(':id', $this->id);
	$st -> execute();
    return $this;
}

function delete(){
    $db=Db::getDb();

    $st =$db->prepare("DELETE FROM questions WHERE id = :id;");
	
	$st -> bindParam(':id', $this->id);
	$st -> execute();
    }
}
?>