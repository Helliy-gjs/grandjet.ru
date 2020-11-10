<?php
class ExecuteRemote extends Singleton
{
    private static $host;
    private static $username;
    private static $password;
    private static $error;
    private static $output;

    public static function setup($host, $username=NULL, $password=NULL)
    {
        self::$host = $host;
        self::$username = $username;
        self::$password = $password;
		// connecting
		$connection = ssh2_connect(self::$host, 22);
		ssh2_auth_password($connection, self::$username, self::$password);
    }

    public static function executeScriptSSH($script)
    {
        // Setup connection string
        $connectionString = self::$host;
        $connectionString = (empty(self::$username) ? $connectionString : self::$username.'@'.$connectionString);

        // Execute script
        $cmd = "ssh $connectionString $script 2>&1";
        self::$output['command'] = $cmd;
        exec($cmd, self::$output, self::$error);

        if (self::$error) {
            throw new Exception ("\nError sshing: ".print_r(self::$output, true));
        }

        return self::$output;
    }
	private static function close_connection(){
		self::executeScriptSSH('exit()');
	}
}
?>