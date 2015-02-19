<!DOCTYPE html>
<html>
    <head>
        <title><?php echo($title);?></title>
        <link rel="stylesheet" href="/lab5/myforum/static/style.css" />
    </head>
    
    
    <body>
        
        <div class="content">
            <?php   include_once 'include/util.inc';
                include_once 'models/user.inc';
                include_once 'models/forum.inc';
                include_once 'models/answers.inc';
                include_once 'include/Authenticator.inc';
            ?>

    <?php  if (isLoggedIn()) : ?>
    <div class="welcome">
    Welcome, <?php echo(User::findById($_SESSION['userid'])->getFullName());?></div>
    <?php  if (Authenticator::instance()->can('admin_page')) : ?>
    <p class="login"><a href="/lab5/myforum/admin">Admin</a></p>
  <?php  endif; ?>
    <p class='login'><a href='/lab5/myforum/index'>Home</a></p>
    <p class='login'><a href="/lab5/myforum/user/view/<?php echo(User::findById($_SESSION['userid'])->getId());?>">My Profile</a></p>
    <p class='login'><a href='/lab5/myforum/logout'>Log Out</a></p>
<?php  else : ?>
    <p class='login'><a href='/lab5/myforum/index'>Home</a></p>
    <p class='login'><a href='/lab5/myforum/register'>Register</a></p>
    <p class='login'><a href='/lab5/myforum/login'>Log in</a></p>
<?php  endif; ?> 
<h1><?php echo($title);?></h1>
<h2>Recent Questions</h2>
<!--is based on MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)-->

  <?php  foreach ($records as $record) : ?>
  <?php  $user = User::findById($record->getUserId()); ?>

  <div class="posts">
	<div><a href="/lab5/myforum/forum/view/<?php echo($record->getId());?>"><?php echo($record->getTitle());?></a></div>
    <div>Posted on: <?php echo($record->getDate());?> by <a href="/lab5/myforum/user/view/<?php echo($record->getUserId());?>">
    <?php echo($user->getFullName());?></a></div>
	<div>File under: <?php echo(separate_tags($record->getTags()));?></div>
    <div class="highlight"><?php echo(markdown(substr($record->getPost(), 0, 200). '....'));?></div>
	
  </div>
  <?php  endforeach; ?>


<hr />
    <?php  include_once 'include/util.inc';?>
    <?php  if (Authenticator::instance()->can('question_create')) : ?>
    <p><a href="/lab5/myforum/forum/add">Add a question</a></p>
    <?php  endif; ?>
        <div class="highlight">
            Author: Damien Pyles | Class: WEBD236 <br>
            Based on MVC template by Scott Sharkey (<a href="http://cs.franklin.edu/~sharkesc/webd236"> cs.franklin.edu/~sharkesc/webd236</a>)
        </div>
        </div><!-- content div -->
    </body>
</html> 