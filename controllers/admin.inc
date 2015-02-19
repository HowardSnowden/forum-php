<?php
include_once "include/util.inc";
include_once "models/User.inc";
include_once "include/Authenticator.inc";

function get_index($params) {
    Authenticator::instance() -> ensure('admin_page');
    // @formatter:off
    renderTemplate(
        "views/administration.inc",
        array(
            'title' => 'Administrative functions',
        )
    );
    // @formatter:on
}
?>