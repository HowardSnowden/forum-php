<?php
//taken from MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)

function routeUrl() {
    $method = $_SERVER['REQUEST_METHOD'];
    $requestURI = explode('/', $_SERVER['REQUEST_URI']);
    $scriptName = explode('/', $_SERVER['SCRIPT_NAME']);

    for ($i = 0; $i < sizeof($scriptName); $i++) {
        if ($requestURI[$i] == $scriptName[$i]) {
            unset($requestURI[$i]);
        }
    }
    # continued...
    
    $command = array_values($requestURI);
    $controller = 'controllers/' . $command[0] . '.inc';
    $func = strtolower($method) . '_' . (isset($command[1]) ? $command[1] : 'index');
    $params = array_slice($command, 2);
    
    if (file_exists($controller)) {
        require $controller;
        if (function_exists($func)) {
            $func($params);
            exit();
        }
        else {
            die("Command '$func' doesn't exist.");
        }
    } else {
        die("Controller '$controller' doesn't exist.");
    }
}
session_set_cookie_params(60*60*24*14, '/', $_SERVER['SERVER_NAME'], true, false);
session_start();
routeUrl();

