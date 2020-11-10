<?php

require_once('check.inc');

header("Content-type: text/xml; charset=UTF-8");
header("Cache-Control: no-store, no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", false);

echo '<?xml version="1.0" encoding="UTF-8"?>';

if(isset($_POST['login'])) {
	echo '<a>';
	$user = Singleton::getInstance('User');
	$a = 0 + $user->isLoginExist($_POST['login']);
	echo '<ans>'.$a.'</ans>';
	echo '</a>';
} else {
	echo '<error></error>';
}

?>