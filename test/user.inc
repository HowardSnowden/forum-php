<?php

include_once 'models/db.inc';
function isValidUser($email, $password){
   $valid = findValidUser($email, $password);
   print_r($valid);
   if (!empty($valid)){
    return true;
    }
    
    else {
    return false;
    }
}



function addUser($firstName, $lastName, $email, $password) {
    global $db;
	
	$sql = 'INSERT INTO USER (first_name, last_name, email, password) VALUES ( :first_name, :last_name, :email, :password)';
	$statement = $db -> prepare($sql);
	$statement -> bindParam(':first_name', $firstName);
	$statement -> bindParam(':last_name', $lastName);
	$statement -> bindParam(':email', $email);
    $statement -> bindParam(':password', $password);
	$statement -> execute();
	return $db -> lastInsertId();
}

function findValidUser($email, $password){
    global $db;
    $sql = "SELECT * FROM USER where email = :email AND password = :password";
    $statement = $db->prepare($sql);
    $statement -> bindParam(':email', $email);
    $statement -> bindParam(':password', $password);
    $statement -> execute();
    return $statement -> fetchAll(PDO::FETCH_ASSOC);
    }
    
    function findUser(){
    global $db;
    $sql = "SELECT * FROM USER";
    $statement = $db->prepare($sql);
    $statement -> execute();
    return $statement -> fetchAll(PDO::FETCH_ASSOC);
    }
    
    
    
    