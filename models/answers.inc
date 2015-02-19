<?php

include_once 'models/Model.inc';
include_once 'include/util.inc';

class Answer extends Model{

    private $post_date;
    private $post;
    private $post_id;
    private $user_id;
    
    
public function __construct($fields = array()){
    parent::__construct($fields);
    $this->setPost(safeParam($fields, 'post'));
    $this->setPostId(safeParam($fields, 'post_id'));
    $this->setUserId(safeParam($fields, 'user_id'));
    $this->setDate(safeParam($fields, 'post_date'));
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

public function getPostId(){
    return $this->post_id;
    }
public function setPostId($post_id){
    $this->post_id=$post_id;
    return $this;
    }
public function getUserId(){
    return $this->user_id;
    }
public function setUserId($user_id){
    $this->user_id=$user_id;
    return $this;
    }
    
 private static function fromRows($rows){
        $result = array();
        foreach ($rows as $row) {
            $result[] = new Answer($row);
        }
        return $result;
    }
    
 static function findAll($post_id){
	 $db=Db::getDb();
     $st = $db->prepare('SELECT * FROM answers where post_id=:post_id');
     $st->bindParam(':post_id', $post_id);
	$st -> execute();
    $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
    return self::fromRows($rows);
}
static function findById($id){
    $db = Db::getDb();
    $st = $db->prepare('SELECT * FROM answers where id = :id');
    $st->bindParam(':id', $id);
    $st ->execute();
    $row=$st->fetch(PDO::FETCH_ASSOC);
    return new Answer($row);
}


function insert(){
	$db = Db::getDb();
	$st = $db->prepare('INSERT INTO answers (post_date, post, user_id, post_id) VALUES (date("now"), :post, :user_id, :post_id)');
	$st -> bindParam(':post', $this->post);
	$st -> bindParam(':user_id', $this->user_id);
	$st -> bindParam(':post_id', $this->post_id);
	$st -> execute();
	$this->id=$db->lastInsertId();
    return $this;
}

function delete(){
    $db=Db::getDb();

    $st =$db->prepare("DELETE FROM answers WHERE id = :id");
	
	$st -> bindParam(':id', $this->id);
	$st -> execute();
    }

function update(){
    $db=Db::getDb();
	
	$st =$db->prepare('UPDATE answers SET post = :post, WHERE id=:id');
	$st -> bindParam(':post', $this->post);
	$st -> bindParam(':id', $this->id);
	$st -> execute();
    return $this;
}
}

?>