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
<h1><?php echo($record->getTitle());?></h1>
<div class='display'>

<!--is based on MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)-->
    
    <div>Posted on: <?php echo($record->getDate());?></div><br>
	<div>Filed under: <?php echo(separate_tags($record->getTags()));?></div><br>
    <div class><?php echo(markdown($record->getPost()));?></div>
</div>




<?php  if (Authenticator::instance()->can('question_edit', false, $record->getUserId())) :   ?>
<div class="clearboth">
    <span><a href="/lab5/myforum/forum/edit/<?php echo($record->getId());?>">[Edit]</a>
    <a href="/lab5/myforum/forum/delete/<?php echo($record->getId());?>">[Delete]</a></span>
    
</div>
<?php  endif; ?>

<?php  if ($files) : ?>
<br>
    <label>Attachments:</label>
    <div>
        <ul>
        <?php  foreach ($files as $file) : ?>
        <li><a href="/lab5/myforum/file/download/<?php echo($file->getId());?>">[download]</a> <a 

            href="/lab5/myforum/file/delete/<?php echo($file->getId());?>/<?php echo($record->getId());?>">[delete]</a> <a 

        href="/lab5/myforum/file/view/<?php echo($file->getId());?>">[view]</a> <?php echo( $file->getOrigName() );?></li>
        <?php  endforeach; ?>
        </ul>
    </div>
    <?php  endif; ?>



<div class='inputs'>
    <form action="/lab5/myforum/file/add" method="post" enctype="multipart/form-data">
        <input type="hidden" id="questionId" name="questionId" value="<?php echo($record->getId());?>" />
        <label for="file">Add a file:</label>
        <input type="file" id="file" name="file" /><br />
        <input type="submit" value="Upload" />
    </form>
</div>

        
<?php  if (Authenticator::instance()->can('answer_create')) :  ?>

<div class='inputs'>
    <form action="/lab5/myforum/answer/add" method="post">
        
        
        <label for="field2">Add an answer: </label>
        <textarea id="field2" name="answer[post]" cols =100 rows = 10></textarea>
        <input type="hidden" id="field4" name="answer[user_id]" value=<?php echo(User::findById($_SESSION['userid'])->getId());?>>
        <input type="hidden" id="field5" name="answer[post_id]" value=<?php echo($record->getId());?>>
        <input type="submit" value="Submit" />
    <form>
</div>
<?php  endif; ?>
        
<h2>Answers: </h2>

  <?php  foreach ($answers as $answer) : ?>
  <?php  $user = User::findById($answer->getUserId()); ?>

  <div class="posts">
	
    <div>Posted on: <?php echo($answer->getDate());?> by <a href="/lab5/myforum/user/view/<?php echo($answer->getUserId());?>">
    <?php echo($user->getFullName());?></a></div>
	
    <div class="highlight"><?php echo(markdown($answer->getPost()));?></div>
    <?php if (Authenticator::instance()->can('answer_delete', false, $user->getId())) :  ?>
	<a href="/lab5/myforum/answer/delete/<?php echo($answer->getId());?>">[Delete]</a></span>
    <?php  endif; ?>
  </div>
  <?php  endforeach; ?>
<br>
        

        <div class="highlight">
            Author: Damien Pyles | Class: WEBD236 <br>
            Based on MVC template by Scott Sharkey (<a href="http://cs.franklin.edu/~sharkesc/webd236"> cs.franklin.edu/~sharkesc/webd236</a>)
        </div>
        </div><!-- content div -->
    </body>
</html>
