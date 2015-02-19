%% views/header.html %%

<h1>{{$title}}</h1>
<ul>
   <li><a href="@@group/manage@@">Manage groups</a></li>
   <li><a href="@@user/manage@@">Manage users</a></li>
   <li><a href="@@file/manage@@">Clean up orphaned files</a></li>
</ul>
[[if (isset($deletedFiles)): ]]

<p>Deleted {{$deletedFiles}} orphaned file(s).</p>

[[ endif; ]]
%% views/footer.html %%

