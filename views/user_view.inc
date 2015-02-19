%% views/header.html %%
<h1>{{$title}}</h1>
<div class='display'>

<!--is based on MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)-->
    [[include_once "include/util.inc";]]
    <div class='user'>First Name:<span class='value'>{{$user->getFirstName()}}</span></div>
	<div class='user'>Last Name:<span class='value'>{{$user->getLastName()}}</span></div>
    <div class='user'>E-mail:  <span class= 'value'>{{$user->getEmail()}}</span></div>
    <div class='user'>Password: <span class='value'>{{passwordObscure($user->getPassword())}}</span></div>
</div>
[[ if (Authenticator::instance()->can('edit_user', false, $user->getId())) :  ]]
<div class="clearboth">
    
    <span><a href="@@user/delete/{{$user->getId()}}@@">[Delete]</a>
    <a href="@@user/edit/{{$user->getId()}}@@">[Edit]</a></span>
</div>
[[ endif; ]]
 <h2>Questions by {{$user->getFirstName()}}</h2>
  
  [[ foreach ($records as $record) : ]]
  [[ $user = User::findById($record->getUserId()); ]]
  <div class="posts">
	<div><a href="@@forum/view/{{$record->getId()}}@@">{{$record->getTitle()}}</a></div>
    <div>Posted on: {{$record->getDate()}} by 
    <a href="@@user/view/{{$user->getId()}}@@">
    {{$user->getFullName()}}</a></div>
	<div>File under: {{separate_tags($record->getTags())}}</div>
    <div class="highlight">{{(substr(markdown($record->getPost()), 0, 200).'....')}}</div>
	
  </div>
  [[ endforeach; ]]


%% views/footer.html %%
