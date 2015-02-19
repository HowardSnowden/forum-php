<?php

//taken from MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)
// This file opens/connects to the database, and sets up the global $db handle...
global $db;
try {
    $db = new PDO('sqlite:questions.db3');
} catch (PDOException $e) {
    die("Could not open database. " . $e->getMessage());
}

// simple function to handle any query with no parameters...
function adHocQuery($q) {
    global $db;
    $st = $db -> prepare($q);
    $st -> execute();
    return $st -> fetchAll(PDO::FETCH_ASSOC);
}
?>
