<?php
error_reporting(E_ALL);
function __autoload($classname) {
	if(isset($GLOBALS['pathToClasses']) && isset($GLOBALS['pathheader'])) {
		require_once($GLOBALS['pathheader'].$GLOBALS['pathToClasses'].strtolower($classname).'.inc');
	}
}
/*
error_reporting(E_ALL);
function __autoload($classname)
{
    require_once($_SERVER["DOCUMENT_ROOT"].'/classes/'.strtolower($classname) .'.inc');
}
*/
?>