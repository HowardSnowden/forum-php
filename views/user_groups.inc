%% views/header.html %%
<h1>{{$title}}</h1>
<h2>Member of</h2>
<ul>
    [[ foreach($memberOf as $group) : ]]
    <li><a href='@@group/remove/{{$group->getId()}}/{{$user->getId()}}/@@'>[Leave]</a> {{$group->getName()}}</li> 
    [[ endforeach; ]] 
</ul>
<h2>Available groups</h2>
<ul>
    [[ foreach($notMemberOf as $group) : ]]
    <li><a href='@@group/include/{{$group->getId()}}/{{$user->getId()}}/@@'>[Join]</a> {{$group->getName()}}</li> 
    [[ endforeach; ]] 
</ul>
%% views/footer.html %%
