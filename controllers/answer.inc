<?php
include_once 'models/answers.inc';
include_once 'include/util.inc';
include_once 'models/forum.inc';
include_once 'include/Authenticator.inc';

    function post_add($params){
    Authenticator::instance()->ensure('answer_create');
    $answer = safeParam($_REQUEST, 'answer', false);
    $answer = new Answer($answer);
        $validator = new Validator();
        $validator->required('post', $answer->getPost());
        $validator->required('post_id', $answer->getPostId());
        $validator->required('user_id', $answer->getUserid());
    
    if (!$validator->hasErrors()){
    $answer->insert();
    $post_id = $answer->getPostId();
    
    redirectRelative("forum/view/$post_id");
}
    }

    function get_delete($params) {
    
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }

    $record = Answer::findById($id);
    $post_id = $record->getPostId();
    if (!$record) {
        die("No record found.");
    }
    Authenticator::instance()->ensure('answer_delete', false, $record->getUserId());
    $record->delete();
    
	
    redirectRelative("forum/view/$post_id");
    
    
    
}
        
    


?>