<?php

//some utility functions taken from MVC-Template, loginExample and markdown example by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)
include_once "models/user.inc";

function markdown($str) {
    $str = htmlspecialchars(ltrim($str),ENT_QUOTES);
    $str = preg_replace('/\*\*(.+)\*\*/u', '<b>$1</b>', $str);
    $str = preg_replace('/\*([^\*]+)\*/u', '<i>$1</i>', $str);
    $str = preg_replace('/#### ([^\n]*)\n/', "<h4>$1</h4>\n", $str);
    $str = preg_replace('/### ([^\n]*)\n/', "<h3>$1</h3>\n", $str);
    $str = preg_replace('/## ([^\n]*)\n/', "<h2>$1</h2>\n", $str);
    $str = preg_replace('/# ([^\n]*)\n/', "<h1>$1</h1>\n", $str);
    $str = preg_replace('/\[([^\]]+)\]\(([^\)]+)\)/', '<a href=\'$2\'>$1</a>', $str);
    $str = preg_replace('/([^\n\r]{2,})(?:(\r\n){2,}|\r{2,}|\n{2,}|$)/u', "<p>$1</p>\n\n", $str);
    return $str;
}





function validate_present($elements) {
    $errors = array();
    foreach ($elements as $element) {
        
        if (!isset($_POST[$element]) || empty($_POST[$element]) ||  (strlen(trim($_POST[$element])) == 0))
 {
            $errors[$element] = $element;
        }
        
    }
    return $errors;
}



function separate_tags($string){
    $string = explode(" ", $string);
    $result="";
    $url="";
    foreach($string as $value){
    $url=relativeUrl('tag/view/').$value;
   $result .= preg_replace('/\w+ ?/', '<a href='.$url.'>'.$value.'</a> ', $value);
        
    }
    
    
    return $result;
}


function isOwner($itemId){
    if (isset( $_SESSION['userid'])&& $itemId == $_SESSION['userid']) {
        return true;
        }
        }

function passwordObscure($password){
    $result="";
    $password = str_split($password);
    foreach ($password as $char){
        $result .= '*';
        }
        return $result;
        }


function currentUser() {
    $inSession = session_id();
    if (!empty($inSession)) {
        if (isset($_SESSION['userid'])) {
            return $_SESSION['userid'];
        }
    }
    return 0;
}


function isLoggedIn() {
    $inSession = session_id();
    if (!empty($inSession)) {
        if (isset($_SESSION['loggedin'])) {
            return $_SESSION['loggedin'];
        }
    }
    return false;
}

function ensureLoggedIn() {
    if (!isLoggedIn()) {
        $_SESSION['redirect'] = $_SERVER['REQUEST_URI'];
        redirectRelative('login');
        exit();
    }
}

function dumpArray($elements) {
    $result = "<ol>\n";
    foreach ($elements as $key => $value) {
        if (is_array($value)) {
            $result .= "<li>Key <b>$key</b> is an array 
                containing:\n" . dumpArray($value) . "</li>";
        } else {
            $value = nl2br(htmlspecialchars($value)); 
            $result .= "<li>Key <b>$key</b> has value <b>$value</b></li>\n";
        }
    }
    return $result . "</ol>\n";
}

// Function to safely fetch a value from an array, supplying a default if no key is present.
function safeGet($array, $key, $default=false) {  
    if (isset($array[$key])) {
        $value = $array[$key];
        if (!is_array($value)) {
            $value = htmlspecialchars(trim($array[$key]));
        }
        if ($value) {
            return $value;
        }
    }
    return $default;
}

// Function to safely get a variable from an array by index, supplying a default if no key is present.
function safeParam($arr, $index, $default=false) {
    if ($arr && isset($arr[$index])) {
        return $arr[$index];
    }
    return $default;
}

// Dump a variable in a nice debug <div>...
function debug($something) {
    echo "<div class='debug'>\n";
    print_r($something);
    echo "\n</div>\n";
}

// Redirect to a different location....
function redirect($url) {
    header("Location: $url");
    exit();
}

// Functions for handling relative urls...

function redirectRelative($url) {
    redirect(relativeURL($url));
}

function relativeUrl($url) {
    $requestURI = explode('/', $_SERVER['REQUEST_URI']);
    $scriptName = explode('/', $_SERVER['SCRIPT_NAME']);

    $dir = array();
    for ($i = 0; $i < sizeof($scriptName); $i++) {
        if ($requestURI[$i] == $scriptName[$i]) {
            $dir[] = $requestURI[$i];
        } else {
            break;
        }
    }
    return implode('/', $dir) . '/' . $url;
}

function __resolveRelativeUrls($matches) {
    return relativeUrl($matches[1]);
}

// Template utility functions...

function __importTemplate($matches) {
    $fileName = $matches[1];
    if (!file_exists($fileName)) {
        die("Template $fileName doesn't exist.");
    }
    $contents = file_get_contents($fileName);
    $contents = preg_replace_callback('/%%\s*(.*)\s*%%/', '__importTemplate', $contents);
    return $contents;
}

function __cacheName($view) {
    $cachePath = explode('/', $view);
    $idx = sizeof($cachePath) - 1;
    $cachePath[$idx] = 'cache_' . $cachePath[$idx];
    return implode('/', $cachePath);
}

// Function to render a template. $view is the view template, $params are passed to the template.
function renderTemplate($view, $params = array(), $asString = false) {
    $useCaching = false;
    if (!file_exists($view)) {
        die("File $view doesn't exist.");
    }
    // do we have a cached version?
    clearstatcache();
    $cacheName = __cacheName($view);
    if ($useCaching && file_exists($cacheName) && (filemtime($cacheName) >= filemtime($view))) {
         $contents = file_get_contents($cacheName);
    } else {
        // we need to build the file
        $contents = __importTemplate(array('unused', $view));
    
        $contents = preg_replace_callback('/@@\s*(.*)\s*@@/U', '__resolveRelativeUrls', $contents);
    
        // @formatter:off
        $patterns = array(
            array('src' => '/{{/', 'dst' => '<?php echo('),
            array('src' => '/}}/', 'dst' => ');?>'),
            array('src' => '/\[\[/', 'dst' => '<?php '),
            array('src' => '/\]\]/', 'dst' => '?>')
        );
        // @formatter:on
        foreach ($patterns as $pattern) {
            $contents = preg_replace($pattern['src'], $pattern['dst'], $contents);
        }
        file_put_contents($cacheName, $contents);
    }
    extract($params);
    ob_start();
    eval("?>" . $contents);
    $result = ob_get_contents();
    ob_end_clean();
    if (!$asString) {
        echo $result;
    }
    return $result;
}
?>