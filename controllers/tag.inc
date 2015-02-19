<?php

include_once 'models/forum.inc';
include_once 'include/util.inc';



function get_view($params) {
    $tag = safeParam($params, 0, false);
    if ($tag === false) {
        die("No tag selected");
    }
    
    $records = Question::findByTag($tag);
    
    if (!$records) {
        die("No records with tag $tag found.");
    }

    renderTemplate(
        "views/tag_view.inc",
        array(
            'title' => "Viewing posts tagged '$tag'",
            'records' => $records
        )
    );
}



?>