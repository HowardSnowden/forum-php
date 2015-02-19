<?php

//Class code taken from validator example by Scott Sharkey cs.franklin.edu/~sharkesc
class Validator {
    private $errors;

    public function __construct() {
        $this -> errors = array();
    }

    public function hasErrors() {
        return count($this -> errors) > 0;
    }

    public function allErrors() {
        return $this -> errors;
    }

    public function addError($key, $message) {
        $this -> errors[$key] = $message;
    }

    public function errorsFor($key) {
        if (isset($this -> errors[$key])) {
            return $this -> errors[$key];
        }
        return '';
    }

    public function required($key, $value, $message = false) {
        $pattern = '/[[:graph:]]+/';
        $message = $message ? $message : "Field is required";
        if (!preg_match($pattern, $value)) {
            $this -> addError($key, $message);
            return false;
        }
        return true;
    }

    public function phone($key, $value, $message = false) {
        $pattern = "/^\(?\d{3}\)?[. -]?\d{3}[. -]?\d{4}$/";
        $message = $message ? $message : "Not a valid phone number";
        if (!preg_match($pattern, $value)) {
            $this -> addError($key, $message);
            return false;
        }
        return true;
    }

    public function email($key, $value, $message = false) {
        // this regex copied from
        // http://fightingforalostcause.net/misc/2006/compare-email-regex.php
        // @formatter:off
        $pattern = '/^(?!(?:(?:\x22?\x5C[\x00-\x7E]\x22?)|' . 
        '(?:\x22?[^\x5C\x22]\x22?)){255,})(?!(?:(?:\x22?\x5C' .
        '[\x00-\x7E]\x22?)|(?:\x22?[^\x5C\x22]\x22?)){65,}@)' .
        '(?:(?:[\x21\x23-\x27\x2A\x2B\x2D\x2F-\x39\x3D\x3F\x5E-\x7E]+)' .
        '|(?:\x22(?:[\x01-\x08\x0B\x0C\x0E-\x1F\x21\x23-\x5B\x5D-\x7F]' .
        '|(?:\x5C[\x00-\x7F]))*\x22))(?:\.(?:(?:[\x21\x23-\x27\x2A\x2B\x2D\x2F-' .
        '\x39\x3D\x3F\x5E-\x7E]+)|(?:\x22(?:[\x01-\x08\x0B\x0C\x0E-\x1F\x21\x23-' .
        '\x5B\x5D-\x7F]|(?:\x5C[\x00-\x7F]))*\x22)))*@(?:(?:(?!.*[^.]{64,})' .
        '(?:(?:(?:xn--)?[a-z0-9]+(?:-[a-z0-9]+)*\.){1,126}){1,}' .
        '(?:(?:[a-z][a-z0-9]*)|(?:(?:xn--)[a-z0-9]+))(?:-[a-z0-9]+)*)' .
        '|(?:\[(?:(?:IPv6:(?:(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){7})' .
        '|(?:(?!(?:.*[a-f0-9][:\]]){7,})(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,5})?' .
        '::(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,5})?)))|(?:(?:IPv6:(?:(?:[a-f0-9]{1,4}' .
        '(?::[a-f0-9]{1,4}){5}:)|(?:(?!(?:.*[a-f0-9]:){5,})(?:[a-f0-9]{1,4}' .
        '(?::[a-f0-9]{1,4}){0,3})?::(?:[a-f0-9]{1,4}(?::[a-f0-9]{1,4}){0,3}:)?)))?' .
        '(?:(?:25[0-5])|(?:2[0-4][0-9])|(?:1[0-9]{2})|(?:[1-9]?[0-9]))' .
        '(?:\.(?:(?:25[0-5])|(?:2[0-4][0-9])|(?:1[0-9]{2})|(?:[1-9]?[0-9])))' .
        '{3}))\]))$/iD';
        // @formatter:on
        $message = $message ? $message : "Not a valid email address";
        if (!preg_match($pattern, $value)) {
            $this -> addError($key, $message);
            return false;
        }
        return true;
    }

    public function integer($key, $value, $message = false) {
        $pattern = '/^\d+$/';
        $message = $message ? $message : "Not a valid integer";
        if (!preg_match($pattern, $value)) {
            $this -> addError($key, $message);
            return false;
        }
        return true;
    }

    public function float($key, $value, $message = false) {
        $pattern = '/^[-+]?[0-9]*\.?[0-9]+([eE][-+]?[0-9]+)?$/';
        $message = $message ? $message : "Not a valid float";
        if (!preg_match($pattern, $value)) {
            $this -> addError($key, $message);
            return false;
        }
        return true;
    }

    public function money($key, $value, $message = false) {
        $pattern = '/^\$?\d+([.]?\d{2})?$/';
        $message = $message ? $message : "Not a valid dollar amount";
        if (!preg_match($pattern, $value)) {
            $this -> addError($key, $message);
            return false;
        }
        return true;
    }

    public function between($key, $value, $low, $high, $message = false) {
        $message = $message ? $message : "Must be between $low and $high";
        if ($value < $low || $value > $high) {
            $this -> addError($key, $message);
            return false;
        }
        return true;
    }

    public function password($key, $value, $message = false) {
        $message = $message ? $message : "Not strong enough.";
        // all these must be satisfied
        // @formatter:off
        $patterns = array(
            '/^[[:graph:]]{8,}$/',  # all printable (no ws) and at least 8 in length
            '/[[:upper:]]/',        # at least 1 upper case character
            '/[[:digit:]]/',        # at least 1 digit
            '/[[:punct:]]/'         # at least 1 symbol
        );
        // @formatter:on
        foreach ($patterns as $pattern) {
            if (!preg_match($pattern, $value)) {
                $this -> addError($key, $message);
                return false;;
            }
        }
        return true;
    }
}
?>