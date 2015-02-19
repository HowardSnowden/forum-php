<?php
include_once 'include/util.inc';
include_once 'models/user.inc';




function get_index(){
    renderTemplate(
        "views/register_user.inc", 
        array(
            'title' => 'Register', 
            ) 
            );
            }

function post_index($params){
    $user = safeParam($_REQUEST, 'user', false);
    $user = new User($user);
    $validator = $user->validate();
     
      $other = User::findByEmail($user -> getEmail());
    if ($other && $other -> getId() != $user -> getId()){
        $validator->addError('email', "Email Address is already in use.");
    }
        if ($validator -> hasErrors()) {
        
        renderTemplate(
            "views/register_user.inc",
            array(
                'title' => 'Register',
                'errors' => $validator->allErrors(), 
                'user' => $user
                
            )
        );
        
        return;
    }
    
    $user->insert();
    $_SESSION['userid']=$user->getId();
    $_SESSION['loggedin']=true;
    redirectRelative("index");
    }

    
    
    ?>