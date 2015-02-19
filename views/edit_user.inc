%% views/header.html %%
<h1>{{$title}}</h1>
    %% views/errors.html %%
<div class='inputs'>
    <form action="@@user/edit/{{$user->getId()}}@@" method="post">
        
        <label for="field1">First Name </label>
        <input type="text" id="field1" name='user[first_name]' value="{{$user->getFirstName()}}" />
        <label for="field2">Last Name</label>
        <input type="text" id="field2" name='user[last_name]' value="{{$user->getLastName()}}" />
		<label for="field3">E-Mail</label>
		<input type="text" id="field3" name='user[email]' value="{{$user->getEmail()}}"  />
        <label for="field4">Password</label>
        <input type="text" id="field4" name='user[password]' value="{{$user->getPassword()}}" />
        <input type = "hidden" name='user[id]' id="field5" value="{{$user->getId()}}">
        <input type="submit" value="Save" />
    <form>
</div>

%% views/footer.html %%