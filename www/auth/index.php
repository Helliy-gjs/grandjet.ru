<?php
//global $pathToClasses;
//$pathToClasses = 'classes/';
//include_once($pathToClasses.'autoload.inc');
ini_set('display_errors',1);
error_reporting(E_ALL & ~E_NOTICE);
global $pathToClasses,$pathheader,$tabl, $tablepages, $tablenews,$list1,$list2,$list3,$list4,$list5,$poisk;
$tablepages='pages';
$tablenews='news';
$clas['class']=array('1'=>'block1','3'=>'block3','2'=>'block2','4'=>'block4',
 '5' => 'center','6' => 'user','7' => 'zag','8' => 'news',
 '9' => 'section','10' => 's0','11' => 's1','12' => 's2','13' => 's3',
 '14' => 's4','15' => 's5','16' => 's6','17' => 's7','18' => 's8',
 '19' => 's9', '20' => 's10');
$clas['img']='../images/';
		$choice_vendors;
$tabl=array('news'=>$tablenews, 'pages'=>$tablepages);	
	//echo 'Работа с удаленным сервером';echo "<BR>";
	$pathToClasses = './classes/';
	$pathheader='.';
	//include($_SERVER['HTTP_HOST'].$pathToClasses.'autoload.inc');
	include($pathheader.$pathToClasses.'autoload.inc');
	//echo $_SERVER['HTTP_HOST'].$pathToClasses.'autoload.inc';

$maxErrorNum = 5;
$warnErrorNum = 50;
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
//print_r(HTTP_FOLDER);echo '----';
//$mass_folder=explode('/',HTTP_FOLDER);

//print_r($_SERVER['HTTP_HOST']);echo '----';
//if($mass_folder[1]<>'')	$_SERVER['HTTP_HOST'].=HTTP_FOLDER;			
$user = Singleton::getInstance('User');
$Site=$user->initbdF($_SERVER['HTTP_HOST']);
$mass_RA=$user->right_access($Site->desc_site);
$code_GGLA=$mass_RA['GA'];
$code_YAXM=$mass_RA['YM'];
$prot=$mass_RA['PR'];
$user->check();
$Site=$user->initbdF($_SERVER['HTTP_HOST']);
//$pgs=$user->namesitepage($_SERVER['HTTP_HOST']);
$pgs=$Site->nmpage;
//echo $pgs;
if(isset($_GET['guest'])) {
	$user->guestEnter();
	header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/'.$pgs);
	exit();
}
if(isset($_GET['logout'])) {
	$user->logout();
	header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/auth/');
	exit();
}
if($user->getLevel() > 0) {
	header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/'.$pgs);
	exit();
}

define('MAIN_PAGE_SITE',$Site->nmpage);
define('MAIN_NEWS', $Site->news);
define('MAIN_DOMEN', $Site->domen);
$tabl=$user->getsitetables($Site->domen);
//print_r($Site);
$startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
if ($startpage) {
	$PageM = new Page($startpage,$tabl);
	if(isset($PageM->MainAr['namep'])){
		$main_pic=explode('|',$PageM->MainAr['namep']);
		$img=$clas['img'].$main_pic[0];
	}
	else $img='';
}
$as='authStyle';
$type_style=file_exists('../images/'.$as.'.css');
$type_page=2;
//echo 'SERVER[HTTP_HOST]-->'.$_SERVER['HTTP_HOST'];
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Аутентификация</title>
		<?php
		if ($type_style) echo '<link rel="stylesheet" type="text/css" href="../images/authStyle.css" />';
		elseif(isset($PageM->MainAr['hrefstyle'])) echo '<link rel="stylesheet" type="text/css" href=".'.$PageM->MainAr['hrefstyle'].'" />'; 
		echo '<script src="/scripts/capUpdate.js" type="text/javascript"></script>';
		?>
	</head>
	<body>
		<?php
		$error = $user->getNumErrors();
		$login = '';
		$pass = '';
		$uin = '';
		$mem = 0;
		$capStatus = Captcha::NONE;
		$authStatus = User::NONE;
		//show::infosh($error);
		//echo '---------------------------';
		//echo '$_SERVER[HTTP_REFERER]-->'.$_SERVER["HTTP_REFERER"];
		if(isset($_SERVER['HTTP_REFERER']) && $_SERVER['HTTP_REFERER'] == $prot.$_SERVER['HTTP_HOST'].'/auth/') 
		{
			$referer = true;
			
			if($error > $maxErrorNum) {
				if(!isset($_POST['sign']) || !$user->checkUinCode($_POST['sign'])) {
					$cap = new Captcha();
					$capStatus = $cap->checkCaptcha();
				}			
			} else {
				if(isset($_POST['sign'])) $user->clearUinCode();
			}
			if(isset($_POST['login'])) $login = substr($_POST['login'], 0, 16);
			if(isset($_POST['pass'])) $pass = substr($_POST['pass'], 0, 16);
			//if(isset($_POST['mem'])) $mem = 1;
			if(empty($login) || empty($pass)) {
				$authStatus = User::INCORRECT_LOGIN_PASS;
			} elseif($capStatus == Captcha::NONE || $capStatus == Captcha::OK) {
				$authStatus = $user->auth($login, $pass);
			}
		} else {
			$referer = false;
			$timeOut = 0;
			if($error > $warnErrorNum) $timeOut = 2;
			$uin = $user->getUinCode($timeOut);
		}
		if (!$type_style) echo '<div class="main-header '.$as.'" style="background-image: url('.$img.');">';
		
		if($authStatus != User::LOGIN_SUCCESS) {			
			echo '<table class="'.$as.'"><tr><td rowspan="2" class="center" ><form id="auth" action="/auth/" method="post"> 
					<h4>Вход</h4>';
			//
			if($authStatus == User::INCORRECT_LOGIN_PASS) {
				echo '<div class="'.$as.' wrong">Неверное имя пользователя или пароль.<br>
										Проверьте правильность написания имени пользователя.<br>
										Убедитесь, что пароль вводится на том же языке, что и при регистрации.<br>
										Посмотрите, не нажат ли [Caps Lock].<br></div><br>';
			}
			$tabIndex = 1;
			echo '
			<label>Логин:</label><br>
				<input id="login" class="inp" name="login" type="text" tabindex="'.$tabIndex++.'" maxlength="16"';
			if(!empty($login)) echo ' value="'.htmlspecialchars($login).'"'; 
			echo ' /><br />
				<br />
				<label>Пароль:</label><br />
				<input id="pass" class="inp" name="pass" type="password" tabindex="'.$tabIndex++.'" maxlength="16" /><br>';
			if($error >= $maxErrorNum && $referer) {
				echo '<br><div id="capimg" onclick="toggle(arguments[0]); return false;"><img id="cap" src="/img.php" /><br>
				<a href="#">Обновить рисунок</a></div><br>
				<label>Введите символы, показанные на рисунке выше:</label><br>
				<input id="cap" class="inp" name="cap" type="text" tabindex="'.$tabIndex++.'" maxlength="6" /><br>
				<script type="text/javascript">timeOutUpdate();</script>';
				if($capStatus == Captcha::FAIL) {
					echo '<br><div class="wrong">Неверно введены символы, показанные на рисунке.<br>
															  Повторите ввод.<br></div>';
				}
			}
			if($uin != '') echo '<input id="sign" name="sign" type="hidden" value="'.$uin.'" style="display:none;" />';
				echo '<br><input type="submit" tabindex="'.$tabIndex++.'" value="Войти" />';
				echo '<br><br><a href="'.$prot.$_SERVER['HTTP_HOST'].'/registration/">Регистрация</a>
				  <br><br><a href="'.$prot.$_SERVER['HTTP_HOST'].'/registration/?man=no">Регистрация через соцсети</a>
				  <br><a href="'.$prot.$_SERVER['HTTP_HOST'].'/auth/?guest">Гостевой вход</a>
				  <br><a href="'.$prot.$_SERVER['HTTP_HOST'].'/recovery/">Забыли пароль?</a>
				  <br><a href="'.$prot.$_SERVER['HTTP_HOST'].'/recovery/?rec">Сменить пароль?</a>';
				  
			
			
			echo '</tr>';
			
			echo '</div></td></tr></table>';
			
		echo '</div>';
		
		} else {
			header('Location: '.$prot.$_SERVER['HTTP_HOST']);
			exit();
			}	
			
		echo '</body></html>';
?>		