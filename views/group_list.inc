%% views/header.html %%
<h1>{{$title}}</h1>
<form action='@@group/add@@' method='post'>
    <label for="name">Group name:</label>
    <input type="text" id="name" name="group[name]" />
    <input type="submit" value="Add" />
</form>
<ul>
    [[ foreach($groups as $group) : ]]
    <li><a href='@@group/members/{{$group->getId()}}@@'>[Members]</a> <a href='@@group/permissions/{{$group->getId()}}@@'>[Permissions]</a> <a href='@@group/delete/{{$group->getId()}}@@'>[Delete]</a> {{$group->getName()}}</li> 
    [[ endforeach; ]] 
</ul>
%% views/footer.html %%
