%% views/header.html %%
<h1>{{$title}}</h1>

%% views/errors.html %%

<div class='inputs'>Enter E-mail address and first name to have password e-mailed to you. </div>
<div class='inputs'>
    <form action="@@email/send@@" method="post">
        
        <label for="field1">Email </label>
		<input type="text" id="field1" name="email"  />
        <label for="field2">First Name </label>
        <input type="text" id="field2" name="first_name" />
        <input type="submit" value="Send E-mail" />
    <form>
</div>

%% views/footer.html %%