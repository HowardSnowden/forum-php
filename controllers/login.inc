<?php
include_once "include/util.inc";
include_once "models/user.inc";



function get_index($params) {
    // @formatter:off
    renderTemplate(
        "views/login.inc",
        array(
            'title' => 'Login',
        )
    );
    // @formatter:on
}

function post_index($params) {
    $email = safeParam($_REQUEST, 'email', false);
    $password = safeParam($_REQUEST, 'password', false);
    $user = User::findByEmailAndPassword($email, $password);
    
    if ($user) {
        $_SESSION['loggedin'] = true;
        $_SESSION['userid'] = $user->getId();
        if (isset($_SESSION['redirect'])) {
            $redirect = $_SESSION['redirect'];
            redirect($redirect);
            exit();
        }
        redirectRelative("index");
    } else {
    $errors['invalidLogin'] = 'Invalid username/password';
    // @formatter:off
    renderTemplate(
        "views/login.inc",
        array(
            'title' => 'Login',
            'errors' => $errors,
            'username' => $email,
            'password' => $password
        )
    );
    // @formatter:on
    }
}
?>