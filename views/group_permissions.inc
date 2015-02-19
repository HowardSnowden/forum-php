%% views/header.html %%
<h1>{{$title}}</h1>
<h2>Granted permissions</h2>
<ul>
    [[ foreach($permissions as $permission) : ]]
    <li><a href='@@group/revoke/{{$group->getId()}}/{{$permission->getId()}}/@@'>[Revoke]</a> {{$permission->getName()}}</li> 
    [[ endforeach; ]] 
</ul>
<h2>Available permissions</h2>
<ul>
    [[ foreach($nonpermissions as $permission) : ]]
    <li><a href='@@group/grant/{{$group->getId()}}/{{$permission->getId()}}/@@'>[Grant]</a> {{$permission->getName()}}</li> 
    [[ endforeach; ]] 
</ul>
%% views/footer.html %%
