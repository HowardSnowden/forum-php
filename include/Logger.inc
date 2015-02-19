<?php

//Class code taken from ToDoUpload example by Scott Sharkey cs.franklin.edu/~sharkesc

class Logger {

    private static $instance;
    private $filename;
    private $level;

    const DEBUG = 0;
    const INFO = 1;
    const WARN = 2;
    const ERROR = 3;

    private function __construct() {
        // log everything
        $this -> level = self::DEBUG;
        $this -> filename = 'application.log';
    }

    public static function instance() {
        if (!isset(self::$instance)) {
            self::$instance = new Logger();
        }
        return self::$instance;
    }

    public function debug($message) {
        return $this -> log(self::DEBUG, $message);
    }

    public function info($message) {
        return $this -> log(self::INFO, $message);
    }

    public function warn($message) {
        return $this -> log(self::WARN, $message);
    }

    public function error($message) {
        return $this -> log(self::ERROR, $message);
    }

    private function log($level, $message) {
        if ($level >= $this -> level) {
            $names = array('DEBUG', 'INFO', 'WARN', 'ERROR');
            $timestamp = date("Y-m-d H:i:s", time());
            // open the file
            $fd = fopen($this -> filename, "a");

            // write the message
            fprintf($fd, "%s %s %s\r\n", $timestamp, $names[$level], $message);

            // close the file
            fclose($fd);
        }
    }

}
?>