<?php
include_once "include/util.inc";
include_once "models/forum.inc";
include_once "controllers/forum.inc";

//taken from MVC_template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)

function get_index($params) {
	// redirect to the sample controller get_list() function...
    get_list($params);
    
}

?>