%% views/header.html %%
<h1>{{$title}}</h1>
<h2>Members</h2>
<ul>
    [[ foreach($members as $user) : ]]
    <li><a href='@@group/remove/{{$group->getId()}}/{{$user->getId()}}/@@'>[Remove]</a> {{$user->getFullName()}}</li> 
    [[ endforeach; ]] 
</ul>
<h2>Non-members</h2>
<ul>
    [[ foreach($nonmembers as $user) : ]]
    <li><a href='@@group/include/{{$group->getId()}}/{{$user->getId()}}/@@'>[Include]</a> {{$user->getFullName()}}</li> 
    [[ endforeach; ]] 
</ul>
%% views/footer.html %%
