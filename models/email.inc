<?php
error_reporting(E_ALL & !E_STRICT);
require_once 'Mail.php';
require_once 'include/util.inc';
//Class code taken from email example by Scott Sharkey cs.franklin.edu/~sharkesc
class Email {
    private static $smtpHost = "ssl://smtp.gmail.com";
    private static $smtpPort = 465;
    private static $smtpAuth = true;
    private static $smtpUsername = 'phpemailaccess@gmail.com';
    private static $smtpPassword = ***REMOVED***;

    private $smtp;
    private $recipients;
    private $carbonCopy;
    private $blindCopy;
    private $subject;
    private $message;
    private $sender;
    private $body;
    private $contentType;

    public function __construct() {
        $options = array();
        $options['host'] = self::$smtpHost;
        $options['port'] = self::$smtpPort;
        $options['auth'] = self::$smtpAuth;
        $options['username'] = self::$smtpUsername;
        $options['password'] = self::$smtpPassword;

        $mail = new Mail();
        $this -> smtp = $mail -> factory('smtp', $options);

        if (is_a($this -> smtp, 'PEAR_Error')) {
            throw new Exception("Could not create mailer");
        }
        // ...continued...
        $this -> recipients = array();
        $this -> carbonCopy = array();
        $this -> blindCopy = array();
        $this -> sender = '"WEBD 236" <' . self::$smtpUsername . '>';
    }

    public function addRecipient($recipient) {
        $this -> recipients[] = $recipient;
    }

    public function setRecipient($recipient) {
        $this -> recipients = array();
        $this -> addRecipient($recipient);
    }

    public function addCC($recipient) {
        $this -> carbonCopy[] = $recipient;
    }

    public function setCC($recipient) {
        $this -> carbonCopy = array();
        $this -> addCC($recipient);
    }

    public function addBcc($recipient) {
        $this -> blindCopy[] = $recipient;
    }

    public function setBcc($recipient) {
        $this -> blindCopy = array();
        $this -> addBcc($recipient);
    }

    public function setSender($sender) {
        $this -> sender = $sender;
    }

    public function setSubject($subject) {
        $this -> subject = $subject;
    }

    public function setBody($body) {
        $this -> body = $body;
    }

    public function setContentType($contentType) {
        $this -> contentType = $contentType;
    }

    public function send($template = false, $variables = false) {
        if ($template) {
            $this -> body = renderTemplate($template, $variables, true);
        }
        $headers = array();
        $headers['From'] = $this -> sender;
        $headers['To'] = implode(", ", $this -> recipients);
        $headers['Cc'] = implode(", ", $this -> carbonCopy);
        $headers['Bcc'] = implode(", ", $this -> blindCopy);
        $headers['Subject'] = $this -> subject;
        if ($this -> contentType) {
            $headers['Content-type'] = $this -> contentType;
        }
        $allRecipients = array_merge($this -> recipients, $this -> blindCopy, $this -> carbonCopy);

        $result = $this -> smtp -> send(implode(", ", $allRecipients), $headers, $this -> body);
        if (is_a($result, 'PEAR_Error')) {
            throw new Exception($result -> getMessage());
        }
    }

}


?>