%% views/header.html %%
<h1>{{$title}}</h1>

%% views/errors.html %%
<div class='inputs'>
    <form action="@@login/index@@" method="post">
        
        <label for="field1">Email </label>
		<input type="text" id="field1" name="email"  />
        <label for="field2">Password</label>
        <input type="text" id="field2" name="password" />
        <input type="submit" value="Log in" />
    <form>
</div>

<div class='inputs'><a href="@@email/index@@">Forgot Password?</a></div>

%% views/footer.html %%