<?php
include_once 'include/util.inc';
//taken from MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)
// This is the "home page", which redirects to the index controller (controllers/index.inc)
// get_index() function, which may redirect to the actual home page controller/function...

$dbname = 'd40oh58uoj0ati';
            $host = 'ec2-107-21-93-97.compute-1.amazonaws.com';
            $username= 'egmvockqyuwpxo';
            $password = 'KXfs8Lj4XmL-aCIIcol2ev9f56';
            // see if we need to create tables
            
        
            $db = new PDO("pgsql:host=$host; port=5432;dbname=$dbname;user=$username;password=$password");
            

            // force exceptions for better debugging.
            $db -> setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);


$st = $db->prepare('SELECT * FROM questions ORDER BY post_date desc limit 5');
	$st -> execute();
    
    $rows = $st -> fetchAll(PDO::FETCH_ASSOC);
 
foreach ($rows as $row){
    echo $row;
}

$db = null;
?>