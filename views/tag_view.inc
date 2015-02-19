%% views/header.html %% 
<h1>{{$title}}</h1>

<!--is based on MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)-->

  [[ foreach ($records as $record) : ]]
  [[ $user = User::findById($record->getUserId()); ]]

  <div class="posts">
	<div><a href="@@forum/view/{{$record->getId()}}@@">{{$record->getTitle()}}</a></div>
    <div>Posted on: {{$record->getDate()}} by <a href="@@user/view/{{$record->getUserId()}}@@">
    {{$user->getFullName()}}</a></div>
	<div>File under: {{separate_tags($record->getTags())}}</div>
    <div class="highlight">{{(substr(markdown($record->getPost()), 0, 200).'....')}}</div>
	
  </div>
  [[ endforeach; ]]


<hr />
    [[ include_once 'include/util.inc';]]
    [[ if (isLoggedIn()) :]]
    <p><a href="@@forum/add@@">Add a question</a></p>
    [[ endif; ]]
%% views/footer.html %% 