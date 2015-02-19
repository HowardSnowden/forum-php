%% views/header.html %%
<h1>{{$record->getTitle()}}</h1>
<div class='display'>

<!--is based on MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)-->
    
    <div>Posted on: {{$record->getDate()}}</div><br>
	<div>Filed under: {{separate_tags($record->getTags())}}</div><br>
    <div class>{{markdown($record->getPost())}}</div>
</div>




[[ if (Authenticator::instance()->can('question_edit', false, $record->getUserId())) :   ]]
<div class="clearboth">
    <span><a href="@@forum/edit/{{$record->getId()}}@@">[Edit]</a>
    <a href="@@forum/delete/{{$record->getId()}}@@">[Delete]</a></span>
    
</div>
[[ endif; ]]

[[ if ($files) : ]]
<br>
    <label>Attachments:</label>
    <div>
        <ul>
        [[ foreach ($files as $file) : ]]
        <li><a href="@@file/download/{{$file->getId()}}@@">[download]</a> <a 

            href="@@file/delete/{{$file->getId()}}/{{$record->getId()}}@@">[delete]</a> <a 

        href="@@file/view/{{$file->getId()}}@@">[view]</a> {{ $file->getOrigName() }}</li>
        [[ endforeach; ]]
        </ul>
    </div>
    [[ endif; ]]



<div class='inputs'>
    <form action="@@file/add@@" method="post" enctype="multipart/form-data">
        <input type="hidden" id="questionId" name="questionId" value="{{$record->getId()}}" />
        <label for="file">Add a file:</label>
        <input type="file" id="file" name="file" /><br />
        <input type="submit" value="Upload" />
    </form>
</div>

        
[[ if (Authenticator::instance()->can('answer_create')) :  ]]

<div class='inputs'>
    <form action="@@answer/add@@" method="post">
        
        
        <label for="field2">Add an answer: </label>
        <textarea id="field2" name="answer[post]" cols =100 rows = 10></textarea>
        <input type="hidden" id="field4" name="answer[user_id]" value={{User::findById($_SESSION['userid'])->getId()}}>
        <input type="hidden" id="field5" name="answer[post_id]" value={{$record->getId()}}>
        <input type="submit" value="Submit" />
    <form>
</div>
[[ endif; ]]
        
<h2>Answers: </h2>

  [[ foreach ($answers as $answer) : ]]
  [[ $user = User::findById($answer->getUserId()); ]]

  <div class="posts">
	
    <div>Posted on: {{$answer->getDate()}} by <a href="@@user/view/{{$answer->getUserId()}}@@">
    {{$user->getFullName()}}</a></div>
	
    <div class="highlight">{{markdown($answer->getPost())}}</div>
    [[if (Authenticator::instance()->can('answer_delete', false, $user->getId())) :  ]]
	<a href="@@answer/delete/{{$answer->getId()}}@@">[Delete]</a></span>
    [[ endif; ]]
  </div>
  [[ endforeach; ]]
<br>
        

%% views/footer.html %%
