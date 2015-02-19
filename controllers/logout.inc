<?php

include_once "include/util.inc";

function get_index($params) {
    $_SESSION = array();
    session_destroy();
    redirectRelative("index");
}




?>