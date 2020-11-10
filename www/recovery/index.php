<?php
ini_set('display_errors',0);
error_reporting(E_ALL & ~E_NOTICE);
global $pathToClasses;
//$pathToClasses = '../classes/';
$type_page=3;
//include_once($pathToClasses . 'autoload.inc');
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
$arrdom=explode('.deltar.ru',$_SERVER['HTTP_HOST']);
if($arrdom[1] ===  ''){
	include_once($pathheader.'/'.$arrdom[0].$pathToClasses.'autoload.inc');
	$lev_domen = 3;
}
else {
	include($pathheader.$pathToClasses.'autoload.inc');
	$lev_domen = 2;
}
$user = Singleton::getInstance('User');
$Site=$user->initbdF($_SERVER['HTTP_HOST']);
//print_r($_POST);
$mass_RA=$user->right_access($Site->desc_site);
	$code_GGLA=$mass_RA['GA'];
	$code_YAXM=$mass_RA['YM'];
	$prot=$mass_RA['PR'];
$user->check();
$uid=$user->getuserid();
$newpass='';
if($user->getLevel() > 0) {
	header('Location: '.$prot.$_SERVER['HTTP_HOST']);
	exit();
}
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
$hd=3; 
$clas['class']=array('1'=>'block1','3'=>'block3','2'=>'block2','4'=>'block4',
 '5' => 'center','6' => 'user','7' => 'zag','8' => 'news',
 '9' => 'section','10' => 's0','11' => 's1','12' => 's2','13' => 's3',
 '14' => 's4','15' => 's5','16' => 's6','17' => 's7','18' => 's8',
 '19' => 's9', '20' => 's10');
$clas['img']='../images/';	
//print_r($_POST);
//print_r($_GET);
//иницилизация
//$user = Singleton::getInstance('User');
//$db=Singleton::getInstance('DB');
if ($user->initbdF($_SERVER['HTTP_HOST'])) $Site=$user->initbdF($_SERVER['HTTP_HOST']);						
//$Site=$user->initbdF($_SERVER['HTTP_HOST']);
//таблицы и стартовая страница
$tabl=Utils::getsitetables($Site->domen,Singleton::getInstance('DB'));
$startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_'.substr('grandjet.ru',0,3).'_'.$Site->domen,$Site->pages);
//$startpage=$user->getlookforfields($Site->domen,'main_'.substr('grandjet.ru',0,3).$Site->domen,$Site->pages);
//таблица стилей
//echo 'Стартовая страница:'.$startpage;
if ($startpage) $PageM = new Page($startpage,$tabl);
$main_pic=explode('|',$PageM->MainAr['namep']);
$img=$clas['img'].$main_pic[0];
$as='recStyle';
$type_style=file_exists($clas['img'].$as.'.css');

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Восстановление пароля</title>
		<?php
		if ($type_style) echo '<link rel="stylesheet" type="text/css" href="'.$clas['img'].$as.'.css" />';
		else  echo '<link rel="stylesheet" type="text/css" href=".'.$PageM->MainAr['hrefstyle'].'" />'; 
		?>
		<script src="/scripts/capUpdate.js" type="text/javascript"></script>
		<script src="/scripts/new.js" type="text/javascript"></script>
	</head>
	<body>
		<?php
		
		$login = '';
		$email = '';
		$capStatus = Captcha::NONE;
		$checkStatus = USER::NONE;
		$sendStatus = 0;
		$id = 0;
		$cap = new Captcha();
		$capStatus = $cap->checkCaptcha();
		if(isset($_POST['login'])) $login = substr($_POST['login'], 0, 16);
		if(isset($_POST['email'])) $email = substr($_POST['email'], 0, 32);
		if(!empty($login) && !empty($email) && $capStatus == Captcha::OK) {
			
			$id	= $user->checkLoginEmail($login, $email);
			if($id != 0) {
				$checkStatus = User::LOGIN_SUCCESS;
				if(!isset($_GET['rec']) && !isset($_POST['recnew'])) $newPass = Utils::generatePass();
				elseif($_POST['pass']==$_POST['passr']) $newPass=$_POST['pass'];
				$db = Singleton::getInstance('DB',1);
				$db->start();
				$success_change=$user->changePassUser($id, $newPass);
				$subject = 'Восстановление пароля.';
				$mes = "Здравствуйте $login.\n\n Был восстановлен пароль на вашу учетную запись на сайте $prot {$_SERVER['HTTP_HOST']}/.\n\nНовый пароль: $newPass\n";	
				if($success_change){
				echo 'Новый пароль установлен';	
				if(Utils::sendMail($email, $subject, $mes)) {
					$sendStatus = 1;
					$db->commit();			
				} else {
					$sendStatus = -1;
					$db->rollback();
				}
				}
			 else {
				$checkStatus = User::INCORRECT_LOGIN_PASS;
			 }
			header('Location: '.$prot.$_SERVER['HTTP_HOST']);
			exit();
			}
			else header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/recovery/?error');
			exit();
		}
		elseif($checkStatus != User::LOGIN_SUCCESS ) {
			//show::simple_adap_menu('','empty',0);
			if (!$type_style) echo '<div class="main-header '.$as.'" style="background-image: url('.$img.');">';
			if(isset($_GET['rec'])) {$recnew='rec';$name_comm='Сменить';}
			else {$recnew='';$name_comm='Восстановить';}
		//if(!isset($_POST['pass'])){
			echo '<form class="'.$as.'" id="rec" action="../recovery/?'.$recnew.'" method="post">
			<table><tr><td class="'.$as.'">
					<h1>Смена пароля пользователем</h1>';
					if(isset($_GET['error']))echo '<div class="'.$as.'"Введены несуществующая пара login email. </div>';
			if($checkStatus == User::INCORRECT_LOGIN_PASS) {
				echo '<div class="wrong '.$as.'">Не совпадают имя пользователя и e-mail.<br>
										Проверьте правильность написания имени пользователя и e-mail.<br>
										Посмотрите, не нажат ли [Caps Lock].<br></div><br>';
			}
			$tabIndex = 1;
			echo '<label class="'.$as.'">Введите ваши логин и e-mail.</label><br><br>
				<label class="'.$as.'">Логин:</label><br>
				<input class="'.$as.'" id="login" class="inp" name="login" type="text" tabindex="'.$tabIndex++.'" maxlength="16"';
			if(!empty($login)) echo ' value="'.htmlspecialchars($login).'"'; 
			echo ' /><br>
				<br>
				<label class="'.$as.'">E-mail:</label><br>
				<input class="'.$as.'" id="email" class="inp" name="email" type="text" tabindex="'.$tabIndex++.'" maxlength="32"';
			if(!empty($email)) echo ' value="'.htmlspecialchars($email).'"'; 
			echo ' /><br>';
			echo '<br><div '.$as.' id="capimg" onclick="toggle(arguments[0]); return false;"><img id="cap" src="/img.php" /><br>
							<a href="#">Обновить рисунок</a></div><br>
							<label>Введите символы, показанные на рисунке выше:</label><br>
							<input id="cap" class="inp" value="" name="cap" type="text" tabindex="'.$tabIndex++.'" maxlength="6" /><br>
							<script type="text/javascript">timeOutUpdate();</script>';
			if($capStatus == Captcha::FAIL) {
				echo '<br><div class="wrong '.$as.'">Неверно введены символы, показанные на рисунке.<br>
														  Повторите ввод.<br></div>';
			}
			if(!isset($_POST['recnew']) && isset($_GET['rec'])) {
					echo '<span class="r"><label>Введите пароль:</label></span><br>';
					echo '<span class="r"><input id="pass" name="pass" type="password" tabindex="'.$tabIndex++.'" maxlength="16" /></span><br>';
					echo '<span class="r"><label>Введите пароль еще раз:</label></span><br>';
					echo '<span class="r"><input id="pass" name="passr" type="password" tabindex="'.$tabIndex++.'" maxlength="16" /></span>';
					echo '<input type="hidden" name="recnew" value=""/>';
					}
			echo '<br><input type="submit" tabindex="'.$tabIndex++.'" value="'.$name_comm.'" />';
			echo '</td></tr></table></form>';
			}
			else {
			if($sendStatus == 1) {
				$content = 'На ваш e-mail отправлено письмо с новым паролем.<br>
							<a href=/ style="font-size: 16px;">OK</a>';
			} else {
				if (!isset($_POST['recnew'])) $content = 'Не удалось отправить письмо.<br>
	   						<a href=/recovery/ style="font-size: 16px;">Повторить</a>';
				else 	$content = '';		
			}
			echo "<table '.$as.'><tr><td class=\"center\">$content</td></tr></table>";
		}
		?>		
	</div></body>
</html>