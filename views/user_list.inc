%% views/header.html %%
<h1>{{$title}}</h1>
<ul>
    [[ foreach($users as $user) : ]]
    <li><a href='@@user/view/{{$user->getId()}}@@'>[View]</a> <a href='@@user/groups/{{$user->getId()}}@@'>[Groups]</a> <a href='@@user/delete/{{$user->getId()}}@@'>[Delete]</a> {{$user->getFullName()}}</li> 
    [[ endforeach; ]] 
</ul>
%% views/footer.html %%
