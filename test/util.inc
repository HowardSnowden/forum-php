<?php

//utility functions taken from MVC-Template by Scott Sharkey (cs.franklin.edu/~sharkesc/webd236)

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
function renderTemplate($view, $params) {
    if (!file_exists($view)) {
        die("File $view doesn't exist.");
    }
    # do we have a cached version?
    clearstatcache();
    $cacheName = __cacheName($view);
    if (file_exists($cacheName) && (filemtime($cacheName) >= filemtime($view))) {
        $contents = file_get_contents($cacheName);
    } else {
        # we need to build the file (doesn't exist or template is newer)
        $contents = __importTemplate(array('unused', $view));

        $contents = preg_replace_callback('/@@\s*(.*)\s*@@/U', '__resolveRelativeUrls', $contents);

        // @formatter:off
        $patterns = array(
            array('src' => '/{{/', 'dst' => '<?php echo('),
            array('src' => '/}}/', 'dst' => '); ?>'),
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
    echo $result;
}
?>