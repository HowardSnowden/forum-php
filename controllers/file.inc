<?php
include_once "include/util.inc";
include_once "include/Authenticator.inc";
include_once "models/validator.inc";
include_once "models/forum.inc";
include_once "include/UploadDir.inc";
include_once "include/deleteOrphans.inc";

function post_add($params) {
    
    
    $questionId = safeParam($_REQUEST, 'questionId', false);
    $question = Question::findPostById($questionId);
    if (!$question) {
        die("No question with that ID found");
    }
    Authenticator::instance()->ensure('question_edit', false, $question->getUserId());
    $dir = new UploadDir();
    $file = $dir -> getUpload('file');
    $file -> setQuestionId($question -> getId());

    $validator = $file -> validate();

    if ($validator -> hasErrors()) {
        die("Problem with file upload");
    }
    $file -> insert();
    redirectRelative("forum/view/{$question->getId()}");
}

function get_download($params) {
    $fileId = safeParam($params, 0);
    $file = File::findById($fileId);
    header('Content-Description: File Transfer');
    header('Content-Type: ' . $file -> getType());
    header('Content-Disposition: attachment; filename=' . $file -> getOrigName());
    header('Content-Transfer-Encoding: binary');
    header('Expires: 0');
    header('Cache-Control: must-revalidate');
    header('Pragma: public');
    header('Content-Length: ' . $file -> getSize());
    ob_clean();
    flush();
    readfile($file -> fullPath());
    exit ;
}

function get_view($params) {
    $fileId = safeParam($params, 0);
    $file = File::findById($fileId);
    header('Last-Modified: ' . date('r'));
    header('Accept-Ranges: bytes');
    header('Content-Length: ' . $file -> getSize());
    header('Content-Type: ' . $file -> getType());
    header('Content-Disposition: inline; filename=' . $file -> getOrigName());
    ob_clean();
    flush();
    readfile($file -> fullPath());
    exit ;
}

function get_delete($params) {
    
    $fileId = safeParam($params, 0);
    $questionId = safeParam($params, 1);
    $question = Question::findPostById($questionId);
    Authenticator::instance() -> ensure('question_edit', false, $question->getUserId());
    $file = File::findById($fileId);
    $file -> delete();
    redirectRelative("forum/view/$questionId");
}

function get_manage() {
    Authenticator::instance()->ensure('admin_page');
    $deletedFiles = deleteOrphans();
    
      renderTemplate("views/administration.inc",
        array(
            'title' => 'Administrative Functions',
            'deletedFiles' => $deletedFiles
            ));
            die();
            
    }

?>