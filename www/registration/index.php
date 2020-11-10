<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
<title>Регистрация</title>
<script src="//ulogin.ru/js/ulogin.js"></script>
</head>
<?php
ini_set('display_errors',0);
error_reporting(E_ALL & ~E_NOTICE);
$type_page=1;
echo '<body>';
//$s = file_get_contents('http://ulogin.ru/token.php?token=' . $_POST['token'] . '&host=' . $_SERVER['HTTP_HOST']);
//$userSoc = json_decode($s, true);
                    //$user['network'] - соц. сеть, через которую авторизовался пользователь
                    //$user['identity'] - уникальная строка определяющая конкретного пользователя соц. сети
                    //$user['first_name'] - имя пользователя
                    //$user['last_name'] - фамилия пользователя	

global $pathToClasses,$pathheader,$tabl, $tablepages, $tablenews,$list1,$list2,$list3,$list4,$list5,$poisk;
$tablepages='pages';
$tablenews='news';
$hd=3; 
$clas['class']=array('1'=>'block1','3'=>'block3','2'=>'block2','4'=>'block4',
 '5' => 'center','6' => 'user','7' => 'zag','8' => 'news',
 '9' => 'section','10' => 's0','11' => 's1','12' => 's2','13' => 's3',
 '14' => 's4','15' => 's5','16' => 's6','17' => 's7','18' => 's8',
 '19' => 's9', '20' => 's10');
$clas['img']='../images/';
		$choice_vendors;

	//echo 'Работа с удаленным сервером';echo "<BR>";
//$pathToClasses = '../classes/';
//include($pathToClasses.'autoload.inc');
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
$arrdom=explode('.deltar.ru',$_SERVER['HTTP_HOST']);
//print_r($arrdom);
if(isset($arrdom[1])){
	include_once($pathheader.'/'.$arrdom[0].$pathToClasses.'autoload.inc');
	$lev_domen = 3;
}
else {
	$pathToClasses = '../classes/';
	$pathheader='';
	include($pathheader.$pathToClasses.'autoload.inc');
	$lev_domen = 2;
}
define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']).'/');
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
//require ('/bhome/part2/01/ritondel/deltar.ru/www/shop/book/book_sc_fns.php');					
$user = Singleton::getInstance('User');
if ($user->initbdF($_SERVER['HTTP_HOST'])) $Site=$user->initbdF($_SERVER['HTTP_HOST']);						
//echo '-+-<br> site ';						
//print_r($Site);
//if (isset($_GET['man'])) echo 'manual='.$_GET['man'];
//if (isset($priv_data))echo '<br>'.$priv_data;
$Site=$user->initbdF($_SERVER['HTTP_HOST']);
$mass_RA=$user->right_access($Site->desc_site);
$code_GGLA=$mass_RA['GA'];
$code_YAXM=$mass_RA['YM'];
$prot=$mass_RA['PR'];

define('MAIN_PAGE_SITE',$Site->nmpage);
define('MAIN_NEWS', $Site->news);
define('MAIN_DOMEN', $Site->domen);
$tabl=Utils::getsitetables($Site->domen);
//$startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
//if ($startpage) $PageM = new Page($startpage,$tabl);
//$main_pic=explode('|',$PageM->MainAr['namep']);
//$img=$clas['img'].$main_pic[0];
$as='regStyle';
$type_style=file_exists($clas['img'].$as.'.css');
$type_page=1;
$s = file_get_contents($prot.'ulogin.ru/token.php?token=' . $_POST['token'] . '&host=' . $_SERVER['HTTP_HOST']);
$userSoc = json_decode($s, true);
if (isset($_GET['man'])) $manual=$_GET['man'];
else $manual='yes';
if (isset($_POST['manual'])) $manual=$_POST['manual'];
if ($_POST['token'])    {
	$manual='no';
	$priv_data=array('name'=> $userSoc['first_name'],'telmain'=>$userSoc['phone'] ,'em'=> $userSoc['email'],'cfio'=>$userSoc['last_name'] );
		//echo 'it 1s token here -+-<br> priv';
		//print_r($priv_data);
		if ($user->isEmailExist($userSoc['email'], $Site->ids)){
			
			//echo 'it is Email in BD here -+-<br> uin=';
			$uin=$user->isEmailId($userSoc['email'],$Site->ids);
			//print_r($uin);
			$find=$user->isExistCust($uin);
			$cn=$user->getscountab('customers','customerid','f')+1;
			//echo 'user have id '.$cn.'-+-'.$uin.'<br>';
			if (!$find) $user->addUserPrivate($cn,$priv_data);
			
	$uSoc=$user->activeUserSoc($uin);
	//echo 'Data user in BD -+-<br>';
	//print_r($uSoc);
if (isset($uSoc)) {
//echo '<br>форма1 uSoc -+-<br>';
echo '<form class="'.$as.'" style="align:left;" method="post" action="../auth/index.php?uid='.$uin.'">';  //
echo '<span>Вы уже зарегистрованы '.$userSoc->network.' как '.$uSoc->login.'<br><br></span>';
//echo '<span>Успешная авторизация через '.$userSoc["network"].' как Login:'.$uSoc->login.',Email: '.$uSoc->email.'<br><br></span>';
echo '<span><input name="login" value="'.$uSoc->login.'" type="hidden">';
echo '<span><input name="pass" value="'.$uSoc->pass.'" type="hidden">';
echo '<span><input name="passr" value="'.$uSoc->pass.'" type="hidden">';
echo '<span><input name="email" value="'.$uSoc->email.'" type="hidden">';
echo '<span><input name="emailr" value="'.$uSoc->email.'" type="hidden">';
echo '<span><input name="uin" value="'.$uin.'" type="hidden"><input name="sign" value="Войти как '.$userSoc["last_name"].' '. $userSoc["first_name"].'" size="30" type="submit" /><br><br></span>';
echo '</form>';
		}
	}	
$priv_data=array('name'=> $userSoc['first_name'],'telmain'=>$userSoc['phone'] ,'em'=> $userSoc['email'],'cfio'=>$userSoc['last_name'] );
$forlogin=explode('@',$userSoc["email"]);
//echo $forlogin[0].'<br>';
echo '<form class="'.$as.'" style="align:left;" method="post" action="index.php?site='.$Site->ids.'">';  //?uid='.$uid.'
	//echo '<span>Такого пользователя нет. Зарегистрироваться по '.$userSoc["network"].' как '.$userSoc["last_name"].' '.$userSoc["first_name"].'<br><br></span>';
	//echo '<span>Завести дополнительный логин '<br><br></span>';
	echo '<span><input name="login" value="'.$forlogin[0].'" type="hidden">';
	echo '<span><input name="pass" value="" type="hidden">';
	echo '<span><input name="passr" value="" type="hidden">';
	echo '<span><input name="email" value="'.$userSoc["email"].'" type="hidden">';
	echo '<span><input name="emailr" value="'.$userSoc["email"].'" type="hidden">';
	echo '<span><input name="fname" value="'.$userSoc["first_name"].'" type="hidden">';
	echo '<span><input name="lname" value="'.$userSoc["last_name"].'" type="hidden">';
	echo '<span><input name="telm" value="'.$userSoc["phone"].'" type="hidden">';
	echo '<input name="photo" value="'.$userSoc["photo"].'" type="hidden">';
	echo '<input name="nick" value="'.$userSoc["nickname"].'" type="hidden">';
	echo '<input name="city" value="'.$userSoc["city"].'" type="hidden">';
	echo '<input name="country" value="'.$userSoc["country"].'" type="hidden">';
	echo '<input name="bdate" value="'.$userSoc["bdate"].'" type="hidden">';
	echo '<input name="sex" value="'.$userSoc["sex"].'" type="hidden">';
	echo '<span><input name="photo_big" value="'.$userSoc["photo_big"].'" type="hidden">';
	echo '<span class="button"><input name="manual" value="yes" type="hidden"><input name="sign" value="Регистрация нового пользователя '.$userSoc["first_name"].'" size="30" type="submit" /></span><a href="" class="button">Отмена</a></span>';
	Maket::divclass('container__social_reg',$Pth,'display: flex;flex-direction: row;justify-content: center;margin: 0 auto;padding: 200px 300px 0px 0px;width: 600px;');
	//echo '<div class="container__social_reg">';
	echo '<div >';
		echo '<span>'.$userSoc["first_name"].' '.$userSoc["last_name"].' '.$userSoc["email"].' '.$userSoc["phone"];
	echo '</div>';
	echo '<div>';
	echo '<span><img src="'.$userSoc["photo"].'"</img></span><span> nickname-'.$userSoc["nickname"].'</span><span>'.$userSoc["sex"].'</span><span>'.$userSoc["bdate"].'</span><span>'.$userSoc["city"].'</span><span>'.$userSoc["country"].'</span>';
	echo '</div>';
	echo '</form>';
}	
else{
	$uids=$user->getscountab('users','id','f');
	$uid=$uids+1;
	//$cid=$_POST['uid'];
if (isset($_POST['cfio'])){
	$famile=explode(' ',$_POST['cfio']);
	$_POST['fname']=$famile[1].' '.$famile[2];
	$_POST['lname']=$famile[0];
	//echo $_POST['cfio'];
	
}
	else {
		//$activate=0;
		//$cid=0;
	}
	if(isset($_POST['email']))$priv_data=array('name'=> $_POST['fname'],'telmain'=>$_POST['phone'] ,'em'=> $_POST['email'],'cfio'=>$_POST['lname'],'city'=>$_POST['country'],'city'=>$_POST['country'],'photo_big'=>$_POST['photo_big'] );
	//$ids=$Site->ids;
	$user->check();
	//echo $user->getLevel() ;
if($user->getLevelnew() > 0) {
	header('Location: '.$prot.$_SERVER['HTTP_HOST']);
	exit();
}

	$login = $pass = $passr = $email = $emailr = '';
	$post = 0;
	$cap = new Captcha();
	$capStatus = $cap->checkCaptcha();

if(isset($_POST['login']) &&
   isset($_POST['pass'])  &&
   isset($_POST['passr']) &&
   isset($_POST['email']) &&
   isset($_POST['emailr'])) {
   		$post = 1;
		$login = substr($_POST['login'], 0, 16);  
		$pass = substr($_POST['pass'], 0, 16);
		$passr = substr($_POST['passr'], 0, 16);
		$email = substr($_POST['email'], 0, 32);
		$emailr = substr($_POST['emailr'], 0, 32); 	
   
		
		
		$user_details[] =array(`login`=>$login,`email`=>$email);
		if($capStatus == Captcha::OK && ($pass == $passr) && ($email == $emailr)) 
		{
   			$db = Singleton::getInstance('DB');
   			$db->start();
   			if($user->addClient($login, $pass, $email,0)) {
   				$code = $user->addActivateCode();
				$user->addSiteToUser($_POST['uid'], $Site->ids);
				$cn=$user->getscountab('customers','customerid','f')+1;
				$find=$user->isExistCust($_POST['uid']);
					if (!$find)	$user->addcustomer($_POST['uid'],$priv_data);
						//$user->addUserPrivate($cid, $priv_data);
					else exit('Такие данные уже есть в системе') ;
				$cust=$user->idUser($_POST['uid']);	
				$fnm=$cust->name;
				$lnm=$cust->cfio;
   				if($code !== false && $_POST['uid']<>$er) {
					$subject = 'Активация учетной записи';
	   				$mes = "Здравствуйте $login.\n\nСпасибо за регистрацию на http://{$_SERVER['HTTP_HOST']}.\n\nДля активации вашей учетной записи пройдите по ссылке:\nhttps://{$_SERVER['HTTP_HOST']}/registration/?actcode=$code\n\nЛогин: $login\n\nПароль: $pass";
	   				$emladm=$user->whatemail(1,$Site-ids);
					if(Utils::sendMail($email, $subject, $mes, $emladm,$_POST['uid'])) {
						if ($fnm<>'') $content ='Пользователь представился как '. $cust->name.' '.$cust->cfio.' <br>';
	   					$content .= 'Спасибо '.$login.' Запрос на регистрацию пользователя на сайте '.$Site->domen.' принят.<br>
									На указанный при регистрации e-mail адрес отправлено письмо с инструкциями по активации вашей учетной записи.<br>
										Указанный вами e-mail: '.$email.'<br>
										<a href=/ style=\"font-size: 16px;\">OK</a>';
						Utils::sendMail($user_details,6,$uid);				
						$db->commit();
	   				} else {
	   					$content = 'Не удалось отправить письмо с инструкциями по активации вашей учетной записи.<br>
	   								<a href=/registration/ style=\"font-size: 16px;\">Повторить</a>';
	   					$db->rollback();
	   				}
					?>
					<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
					<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
						<head>
							<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
							<title>Регистрация</title>
							<?php
						if ($type_style) echo '<link rel="stylesheet" type="text/css" href="/images/regStyle.css" />';
						else  echo '<link rel="stylesheet" type="text/css" href=".'.$PageM->MainAr['hrefstyle'].'" />'; 
						?>
							<script src="//ulogin.ru/js/ulogin.js"></script>
						</head>
<?php
	   				echo '<table class="'.$as.'" >';
					?>		
								<tr>
									<td class="center">
									<?php 
										echo $content;
									?>
									</td>
								</tr>
							</table>
						</body>
					</html>	   				
	   				<?php
	   				exit();	
   				} else {
   					$db->rollback();	
   				}
   			}
   		}
   }
   
if(isset($_GET['actcode'])) {
	if($user->checkActivateCode($_GET['actcode'])) {
		
		?> 
		<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
		<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
			<head>
				<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
				<title>Регистрация</title>
				<?php
				if ($type_style) echo '<link rel="stylesheet" type="text/css" href="/images/regStyle.css" />';
				else  echo '<link rel="stylesheet" type="text/css" href=".'.$PageM->MainAr['hrefstyle'].'" />'; 
		?>
			</head>
			<body>
			<?php
			
				echo '<table class="'.$as.'">';
			?>	
					<tr>
						<td class="center">
						<?php 
							echo 'Ваша учетная запись активирована.<br>
								  <a href=/auth/ style=\"font-size: 16px;\">ВОЙТИ</a>';
						?>
						</td>
					</tr>
				</table>
			</body>
		</html>	   				
		<?php	
	} else {
		header("HTTP/1.0 404 Not Found");	
	}
}
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Регистрация</title>
		<?php
		if ($type_style) echo '<link rel="stylesheet" type="text/css" href="/images/regStyle.css" />';
		else  echo '<link rel="stylesheet" type="text/css" href=".'.$PageM->MainAr['hrefstyle'].'" />'; 
		?>	
		<script src="/scripts/tube.js" type="text/javascript"></script>
		<script src="/scripts/registration.js" type="text/javascript"></script>
		<script src="/scripts/capUpdate.js" type="text/javascript"></script>
	</head>
	<body onload="checkAll();">
	<?php
	//show::simple_adap_menu('','empty',0);
	if (!$type_style) echo '<div class="main-header '.$as.'" style="background-image: url('.$img.');">';
		echo '<form id="reg" class="'.$as.'" action="'.$prot.$_SERVER['HTTP_HOST'].'/registration/" method="post" onkeyup="toggleKey(arguments[0]);">';
			echo '<table class="'.$as.'">';
			?>
				<tr>
					<td>
<?php	
//if (isset($_GET['man'])) echo 'manual='.$_GET['man'];
//if (isset($priv_data))echo '<br>'; print_r($priv_data);
$uids=$user->getscountab('users','id','f');
//print_r($uids);
$uid=$uids+1;
//echo 'post uid = '.$uid;
if ($manual === 'no')
{					
if(!isset($_GET['actcode']))echo '<div id="uLogin" data-ulogin="display=small;theme=classic;fields=email, phone,first_name,last_name,nickname,bdate,sex,photo,city,country,photo_big;providers=vkontakte,odnoklassniki,mailru,facebook;hidden=other;redirect_uri=http%3A%2F%2F'.$_SERVER['HTTP_HOST'].'%2Fregistration%2F;mobilebuttons=0;" style="position: absolute; left: 400px;width:20%; "></div>';

}
elseif(!$_GET['actcode'])
	{
	echo '<input name="cfio" value="'.$priv_data["last_name"].'" type="hidden">';	
	echo '<input name="fname" value="'.$priv_data["name"].'" type="hidden">';
	echo '<input name="lname" value="'.$priv_data["cfio"].'" type="hidden">';
	echo '<input name="phone" value="'.$priv_data["telmain"].'" type="hidden">';
	echo '<input name="photo" value="'.$priv_data["photo"].'" type="hidden">';
	echo '<input name="city" value="'.$priv_data["city"].'" type="hidden">';
	echo '<input name="country" value="'.$priv_data["country"].'" type="hidden">';
	echo '<input name="bdate" value="'.$priv_data["bdate"].'" type="hidden">';
	echo '<input name="sex" value="'.$priv_data["sex"].'" type="hidden">';
	echo '<input name="nickname" value="'.$priv_data["nick"].'" type="hidden">';
	echo '<input name="photo_big" value="'.$priv_data["photo_big"].'" type="hidden">';
	if(isset($_POST["telm"]))$phone=$_POST["telm"];
	else $phone='';
	if(isset($_POST["lname"]) || isset($_POST["fname"])) $cfio=$_POST["lname"].' '.$_POST["fname"];
		?>		
						<h1>Регистрация</h1>
						<table class="inp">
							<tr>
								<td class="r"><label>Имя для входа (логин):</label></td>
								<td class="l"><input id="login" class="inp" name="login" type="text" tabindex="1" maxlength="16" <?php if($post) echo 'value='.htmlspecialchars($login);?> ></td>
							</tr>
							<tr>
								<td class="r"><label>Укажите пароль:</label></td>
								<td class="l"><input id="pass" class="inp" name="pass" type="password" tabindex="2" maxlength="16" ></td>
							</tr>
							<tr>
								<td class="r"><label>Введите пароль ещё раз:</label></td>
								<td class="l"><input id="passr" class="inp" name="passr" type="password" tabindex="3" maxlength="16" ></td>
							</tr>
							<tr>
								<td class="r"><label>Укажите контактный e-mail:</label></td>
								<td class="l"><input id="email" class="inp" name="email" type="text" tabindex="4" maxlength="32" <?php if($post) echo 'value='.htmlspecialchars($email);?> ></td>
							</tr>
							<tr>
								<td class="r"><label>Введите e-mail ещё раз:</label></td>
								<td class="l"><input id="emailr" class="inp" name="emailr" type="text" tabindex="5" maxlength="32" <?php if($post) echo 'value='.htmlspecialchars($emailr);?> ></td>
							</tr>
							<tr>
								<td class="r"><label>Введите введите номер мобильного (не обязательно):</label></td>
								<td class="l"><input id="phone" class="inp" name="phone" type="tel" tabindex="5" maxlength="12" <?php if($post) echo 'value='.htmlspecialchars($phone);?> ></td>
							</tr>
							<tr>
								<td class="r"><label>Введите ФИО (не обязательно):</label></td>
								<td class="l"><input id="cfio" class="inp" name="cfio" type="text" tabindex="5" maxlength="50" <?php if($post) echo 'value='.htmlspecialchars($cfio);?> ></td>
							</tr>
						</table>
						<br /> 
						<div id="capimg" onclick="toggle(arguments[0]); return false;">
							<img id="cap" src="/img.php" /><br />
							<a href="#">Обновить рисунок</a>
						</div><br />
						<label>Введите символы, показанные на рисунке выше:</label><br />
						<input id="cap" class="inp" name="cap" type="text" maxlength="6" tabindex="6" /><br />
						<br />
						<script type="text/javascript">timeOutUpdate();</script>
						<?php
						
						if($capStatus == Captcha::FAIL) {
							echo '<div class="wrong">Неверно введены символы, показанные на рисунке.<br>
																	  Повторите ввод.<br></div><br>';
						}
					echo '<input name="uid" value="'.$uid.'" type="hidden"><input name="site" value="'.$Site->ids.'" type="hidden">';		
					echo '<input id="regBut" type="submit"  tabindex="7" disabled="disabled" value="Зарегистрироваться" />';
					
		
					echo '</td></tr></table></form>';
}					
	echo '</div></body></html>';
?>