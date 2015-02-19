%% views/header.html %%
<h1>{{$title}}</h1>
<!--added an include to render an error list -->
    %% views/errors.html %%

[[ if(isset($record)) : ]] 
<div class='inputs'>
    <form action="@@forum/add@@" method="post">
        
        <label for="field1">Title :</label>
        <input type="text" id="field1" name='question[title]' value="{{$record->getTitle()}}" />
        <label for="field2">Content:</label>
        <textarea id="field2" name='question[post]' cols =100 rows = 20> {{$record->getPost()}}</textarea>
		<label for="field3">Tags:</label>
		<input type="text" id="field3" name='question[tags]' value = "{{$record->getTags()}}" />
        <input type="hidden" id="field4" name='question[user_id]' value={{User::findById($_SESSION['userid'])->getId()}}>
        <input type="submit" value="Save" />
    <form>
</div>
[[ else : ]]

<div class='inputs'>
    <form action="@@forum/add@@" method="post">
        
        <label for="field1">Title :</label>
        <input type="text" id="field1" name='question[title]'  />
        <label for="field2">Content:</label>
        <textarea id="field2" name='question[post]' cols =100 rows = 20> </textarea>
		<label for="field3">Tags:</label>
		<input type="text" id="field3" name='question[tags]'  />
        <input type="hidden" id="field4" name='question[user_id]' value={{User::findById($_SESSION['userid'])->getId()}}>
        <input type="submit" value="Save" />
    <form>
</div>
[[ endif; ]]

%% views/footer.html %%