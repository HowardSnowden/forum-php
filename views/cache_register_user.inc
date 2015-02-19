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

    <?php  if (isset($errors)) : ?>
    <p>Please correct the following errors:</p>
    <ul>
<?php    foreach ($errors as $error) : ?>
        <li><?php echo($error);?></li>
<?php    endforeach; ?>
    </ul>
<?php  endif; ?>
<div class='inputs'>

<?php  if (!isset($user)) : ?> 
    <form action="/lab5/myforum/register" method="post">
        
        <label for="field1">First Name </label>
        <input type="text" id="first_name" name='user[first_name]'  />
        <label for="field2">Last Name</label>
        <input type="text" id="field2" name='user[last_name]'  />
		<label for="field3">E-Mail</label>
		<input type="text" id="field3" name='user[email]'  />
        <label for="field4">Password</label>
        <input type="text" id="field4" name='user[password]' />
    
    
            <input type="submit" value="Save" />
    
    </form>
<?php  else : ?>
    
      <form action="/lab5/myforum/register" method="post">
        
        <label for="field1">First Name </label>
        <input type="text" id="first_name" name='user[first_name]' value="<?php echo($user->getFirstName());?>" />
        <label for="field2">Last Name</label>
        <input type="text" id="field2" name='user[last_name]' value="<?php echo($user->getLastName());?>" />
		<label for="field3">E-Mail</label>
		<input type="text" id="field3" name='user[email]' value="<?php echo($user->getEmail());?>"  />
        <label for="field4">Password</label>
        <input type="text" id="field4" name='user[password]' value="<?php echo($user->getPassword());?>" />
    
    
            <input type="submit" value="Save" />
    
    </form>
    <?php  endif; ?>
    
</div>
    

        <div class="highlight">
            Author: Damien Pyles | Class: WEBD236 <br>
            Based on MVC template by Scott Sharkey (<a href="http://cs.franklin.edu/~sharkesc/webd236"> cs.franklin.edu/~sharkesc/webd236</a>)
        </div>
        </div><!-- content div -->
    </body>
</html>