<?php

include_once 'include/util.inc';
include_once 'models/email.inc';
include_once 'models/user.inc';

function get_index(){
    
    renderTemplate('views/get_password.inc',
                  array(
                  'title'=>"Password Retrieval"));

}

function post_send(){
    
  $email = safeParam($_POST, 'email', false);
  $first_name = safeParam($_POST, 'first_name', false);
  $user = User::findByEmail($email);
  
    if($user != null && $user->getFirstName() == $first_name){

    
$subject = "Password Retrieval";
$recipient = $user->getEmail();
$email = new Email();
$email -> setRecipient($recipient);
$email -> setSubject($subject);
$email -> setContentType('text/html');

// @formatter:off
$email -> send(
    'views/email_template.html',
    array(
        'title' => $subject,
        'firstName' => $user->getFirstName(),
        'password' => $user->getPassword(),
    )
);

$url = relativeUrl('login');
// @formatter:on
echo("E-mail has been sent! Click <a href= $url> here</a> to return to login page.");
}
else{
    $errors = array();
    $errors['invalid'] = "No such user found";
    
    renderTemplate(
        'views/get_password.inc',
        array(
            'title' => 'Password Retrieval', 
            'errors' => $errors
        ));

            


}
}

?>