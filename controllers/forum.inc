<?php
include_once "include/util.inc";
include_once "models/forum.inc";
include_once "models/user.inc";
include_once "models/answers.inc";
include_once "models/validator.inc";
include_once "models/File.inc";
include_once "include/Authenticator.inc";
//This controller is based on MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)
//Handles displaying the index and routing to various forum functions

function get_list($params) {
    $records = Question::findAllPosts();
    
    renderTemplate(
        "views/record_list.inc",
        array(
            'title' => 'My Questions and Answers',
            'records' => $records
        )
    );
    
}

// handles the index of questions view
function get_view($params) {
    $id = safeParam($params, 0, false);
    if ($id === false) {
        die("No Record selected");
    }
    
    $record = Question::findPostById($id);
    $file = File::findByQuestionId($id);
    if (!$record) {
        die("No record with id $id found.");
    }
    
    $answers = Answer::findAll($id);

    renderTemplate(
        "views/record_view.inc",
        array(
            'title' => 'Viewing Record Info',
            'record' => $record,
            'answers' => $answers,
            'files' => $file
        )
    );
}

// retrieves a post and renders the post edit view
function get_edit($params) {
    
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }
    $record = Question::findPostByID($id);
    Authenticator::instance()->ensure('question_edit', false, $record->getUserId() );
    $post = strip_tags($record->getPost());
    $record ->setPost($post);
    if (!$record) {
        die("No record found.");
    }
   
    
    renderTemplate(
        "views/record_edit.inc",
        array(
            'title' => 'Editing Record',
            'record' => $record
            
        )
    );
   
}

// this function is modified so that empty spaces are not recognized as valid content




//added function for creating new posts

function get_add(){
    Authenticator::instance()->ensure('question_create');
    renderTemplate(
        "views/post_add.inc",
        array(
            'title' => 'Add a question',
            )
            );
            }

//this function is modified to check and make sure required elements are present, re-renders the same template and passes
//an array of errors if element(s) are not found

function post_add($params) {
    Authenticator::instance()->ensure('question_create');
    
    $question = safeParam($_REQUEST, 'question', false);

    $question = new Question($question);

    $validator= $question->validate();
    if (!$validator->hasErrors()){
   
    $question->insert();
    redirectRelative("index");
    }
        $record = $question;
         renderTemplate("views/post_add.inc",
        array(
            'title' => 'Add a question',
            'errors' => $validator->allErrors(),
            'record' => $record
            ));
            die();
            }
        


//this function is modified similarly to how the post_add function was modified

function post_edit($params) {
   
    
    $question = safeParam($_REQUEST, 'question', false);
    
    $question = new Question($question);
    Authenticator::instance()->ensure('question_edit', false, $question->getUserId());
    $validator= $question->validate();
    
     
       if(!$validator->hasErrors()){
        $update = Question::findPostById($question->getId());
        $update->setTitle($question->getTitle());
        $update->setPost($question->getPost());
        $update->setTags($question->getTags());
           $id = $question->getId();
        $update->update();
        
    redirectRelative("forum/view/$id");
       }
        
         $record = $question;
       

    renderTemplate("views/record_edit.inc",
        array(
            'title' => 'Editing record',
            'errors' => $validator->allErrors(),
            'record' => $record
            ));
            die();
            
    }



// for deleting a post...
function get_delete($params) {
    
    $id = safeParam($params, 0, false);
    if (!$id) {
        die("No record specified");
    }

    $record = Question::findPostById($id);
    if (!$record) {
        die("No record found.");
    }
    Authenticator::instance()->ensure('question_delete', false, $record->getUserId());
    $record->delete();
    
	
    
    redirectRelative("index");
    
    
   
}

?>