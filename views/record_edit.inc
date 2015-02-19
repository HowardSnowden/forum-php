%% views/header.html %%
<h1>{{$title}}</h1>
<!--added an include to render error list -->
%% views/errors.html%%

<div class='inputs'>
    <form action="@@forum/edit@@" method="post">
        <input type="hidden" id="id" name="question[id]" value="{{$record->getId()}}" />
        <label for="field1">Title :</label>
        <input type="text" id="field1" name="question[title]" value="{{$record->getTitle()}}" />
        <label for="field2">Content:</label>
        <textarea id="field2" name="question[post]" cols =100 rows = 20>{{$record->getPost()}} </textarea>
		<label for="field3">Tags:</label>
		<input type="text" id="field3" name="question[tags]" value="{{$record->getTags()}}" />
        <input type="hidden" id="field4" name="question[user_id]" value="{{$record->getUserId()}}">
        <input type="submit" value="Save" />
    <form>
</div>
<div class="clearboth">
    <p><a href="@@index@@"><< Back</a></p>
</div>
%% views/footer.html %%
