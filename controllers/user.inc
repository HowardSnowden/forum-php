<?php
include_once "include/util.inc";
include_once "models/forum.inc";
include_once "models/user.inc";
include_once "include/Authenticator.inc";

   function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No Record selected");
    }
    
    $user = User::findByID($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    
     $record = Question::findUserPosts($id);
    

    renderTemplate(
        "views/user_view.inc",
        array(
            'title' => 'Viewing User',
            'records' => $record,
            'user' => $user
        )
    );
}

function get_edit($params){
    $id = safeParam($params, 0, false);
      
    if (!$id) {
        die("No user specified");
    }

    $user = User::findById($id);
    
    
    if (!$user) {
        die("No user found.");
    }
    Authenticator::instance()->ensure('edit_user', false, $id);
          renderTemplate(
        "views/edit_user.inc",
        array(
            'title' => 'Editing User',
            'user' => $user
        )
    );
    
    }
    
function post_edit($params) {
    
     $user = safeParam($_REQUEST, 'user', false);
     $user = new User($user);
     $validator = $user->validate();
      $other = User::findByEmail($user -> getEmail());
     
    if ($other->getId() != null && $other -> getId() != $user -> getId()){
        $validator->addError('email', "E-mail address is already in use.");
    }
        
    if ($validator->hasErrors()){
       
    renderTemplate("views/edit_user.inc",
        array(
            'title' => 'Editing User',
            'errors' => $validator->allErrors(),
            'user' => $user
            ));
            die();
            }
      Authenticator::instance()->ensure('edit_user', false, $user->getId());
      $user->update();
      session_destroy();
      session_set_cookie_params(60*60*24*14, '/', $_SERVER['SERVER_NAME'], true, false);
      session_start();
      $_SESSION['loggedin'] = true;
      $_SESSION['userid'] = $user->getId();
    
        
    redirectRelative("index");
    }
    
    


    


function get_delete($params) {
    
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No user specified");
    }

    $user = User::findById($id);
    
    
    if (!$user) {
        die("No user found.");
    }
    Authenticator::instance()->ensure('edit_user', false, $id);
    $user->delete();
    $user->deletePosts($id);
    
	
    redirectRelative("logout");


}

function get_manage($params) {
    Authenticator::instance() -> ensure('admin_page');
    
    $users = User::findAll();
    // @formatter:off
    renderTemplate(
        "views/user_list.inc",
        array(
            "title" => "Manage users",
            "users" => $users
        )
    );
    // @formatter:on
}
function get_groups($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No user id specified");
    }
    $user = User::findById($id);
    if (!$user) {
        die("No user with id $id found.");
    }
    $memberOf = Group::findByUserId($id);
    $notMemberOf = Group::findByNotUserId($id);
    renderTemplate(
        "views/user_groups.inc",
        array(
            "title" => "{$user->getFullName()}'s Groups",
            "memberOf" => $memberOf,
            "notMemberOf" => $notMemberOf,
            "user" => $user
        )
    );
}










?>