<?php
ini_set('display_errors',0);
error_reporting(E_ALL & ~E_NOTICE);
global $pathToClasses;
global $pathToClasses,$pathheader, $spisok,$vend, $tabl, $tablepages, $tablenews, $numrecbd,$loz,$hh;
global $vendors,$PageM,$namenews,$novost,$clas,$hd,$type_menu,$cid, $sid;
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
//$pathheader='.';
define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']));
define('HOST_DIST',     '/bhome/part2/01/ritondel/distributive');
define('HOST_SYSTEM','/bhome/part2/01/ritondel/');
define('HOST_MYDOMEN',     HOST_SYSTEM.$_SERVER['HTTP_HOST'].'/www/');
define('HOST_YOURDOMEN',     '/bhome/part2/01/ritondel/'.$_POST['owndomen'].'/www');
define('HOST_YOUR',     '/bhome/part2/01/ritondel/'.$_POST['owndomen']);
//print_r($_POST);
//echo HOST_YOURDOMEN;
//echo HOST_SYSTEM.$_POST['owndomen'];
if($_POST['chice']=='subdomen'){
	$dest_domen=$_POST['catalog'];
}
elseif($_POST['chice']=='owndomen'){
	if(!chdir(HOST_YOURDOMEN)){
		if(mkdir(HOST_SYSTEM.$_POST['owndomen']))$dest_domen=HOST_SYSTEM.$_POST['owndomen'].'/www/';
	}
	else $dest_domen=HOST_YOURDOMEN;
}
//print_r($_POST);
include_once($pathheader.$pathToClasses.'autoload.inc');
 
try {
	$db = Singleton::getInstance('DB',1);
} catch(DBException $e) {
	exit($e);
}

$user = Singleton::getInstance('User');
$sw=Singleton::getInstance('StructureW');
//echo $dest_domen;echo '<br>';
$user->check();
//echo '----------------------------';
//$sw->showloadfiles();	 
if(isset($_FILES)){
	if(isset($_FILES['banmain']))  $sw->all_files_load('banmain','banmain1',$_FILES,$clas,$sw->type_files_load($_FILES,$_POST['banmain1']));
	if(isset($_FILES['logo'])) $sw->all_files_load('logo','logo1',$_FILES,$clas,$sw->type_files_load($_FILES,$_POST['logo1']));
	if(isset($_FILES['page'])) $sw->all_files_load('page','page1',$_FILES,$clas,$sw->type_files_load($_FILES,$_POST['pages1']));
}
if(isset($_POST['mysites']) && $_POST['mysites']=='new' && $_POST['chice']<>'symlimk')	{
if(isset($_POST['owndomen']) &&  $_POST['chice']=='subdomen') $result=$user->createsitedir($dest_domen);
elseif(isset($_POST['owndomen']) &&  $_POST['chice']=='owndomen')$result=$user->createsitedir($dest_domen,HOST_DIST);
} 
elseif($user->getlogin()==1) $result=true;	
else $result=false;
$work_domen=$_SERVER['HTTP_HOST'];
if (isset($_POST['adms']) && isset($_POST['pass']) && isset($_POST['eml']) && isset($_POST['site']) && isset($_POST['uid'])) {

if (isset($_POST['cga']))$desc['cga']=$_POST['cga'];
else $desc['cga']='';
if(isset($_POST['cym'])) $desc['cym']=$_POST['cym'];
else $desc['cym']='';
if( $_POST['chice']=='owndomen') $desc['own']='Y';
else $desc['own']='N';
if($_POST['ownbd']=='yes')$desc['ownbd']='yes';
else $desc['ownbd']='no';
if(isset($_POST['mysites'])&& isset($_POST['owndomen'])){
	if (!$user->initbdF($_POST['owndomen']) && $_POST['chice']<>'symlink') {
	echo 'сайт еще не зарегистрован <br> регистрируем...';
//регистрируем 	в таблице Allsites
	
	$user->regbd($_POST['owndomen'],$_POST['uid'],$_POST['mysites'],$_POST['typs'],$_POST['strucs'],$_POST['ippt'],$_POST['tarif'],$desc);
	
	}
	elseif($_POST['chice']=='symlink') {
	$user->regbd($work_domen.'/'.$_POST['owndomen'],$_POST['uid'],$_POST['mysites'],$_POST['typs'],$_POST['strucs'],$_POST['ippt'],$_POST['tarif'],$desc);
	}
	else {
		header('Location: http://'.$_SERVER['HTTP_HOST'].'?rep=y');
		exit();
	}
}
else { 
// инициализация и авторизация таблицы user

$id_exist=$user->checkLoginEmail($_POST['adms'], $_POST['eml']);

if (!$user->initbdF($_SERVER['HTTP_HOST'])) {
	echo 'сайт еще не зарегистрован <br> регистрируем...';
//регистрируем 	в таблице Allsites
	if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
	if($result && $id_exist==0 ){
		$control_summa=$user->regbd($_SERVER['HTTP_HOST'],$_POST['uid'],'',$_POST['typs'],$_POST['strucs'],$_POST['ippt'],$_POST['tarif'],$desc);
		if($control_summa>0) echo 'Сайт подключен. '.$control_summa.'<br>';
		
		}
	else {
		header('Location: https://deltar.ru/?guest');
		exit();
	}
}
}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Регистрация сайта</title>
		<?php
		echo '<link rel="stylesheet" type="text/css" href="./images/authStyle.css" />';
		echo '<script src="./scripts/capUpdate.js" type="text/javascript"></script>';
		echo '<link rel="shortcut icon" type="image/png" href="images/favicongra.png"/>';
		?>
	</head>
	<body>
		<?php
if( $_POST['chice']=='owndomen')$prot_ssl='https://';
else 	$prot_ssl='http://';		
if( $_POST['chice']=='subdomen') {
	header('Location: '.$prot_ssl.$_POST['owndomen']);
	exit();
}
if(isset($_POST['owndomen']) && $_POST['chice']<>'symlink')	{	
//echo $prot_ssl.$_POST['owndomen'];
//print_r($_POST);echo '---->';

echo '<table><tr><td class="center">';		
echo 'Администртор базы :'.$user->getlogin();
echo '<br>DONE<br>';
echo '<form id="first" action="'.$prot_ssl.$_POST['owndomen'].'" method="post">';
echo '<input name="adms" value="'.$_POST['adms'].'" type="hidden">';
echo '<input name="pass" value="'.$_POST['pass'].'" type="hidden">';
echo '<input name="eml" value="'.$_POST['eml'].'" type="hidden">';
echo '<input name="strucs" value="'.$_POST['strucs'].'" type="hidden">';
echo '<input name="tarif" value="'.$_POST['tarif'].'" type="hidden">';
echo '<input name="ippt" value="'.$_POST['ippt'].'" type="hidden">';
echo '<input name="typs" value="'.$_POST['typs'].'" type="hidden">';
echo '<input name="ownbd" value="'.$_POST['ownbd'].'" type="hidden">';
echo '<input name="uid" value="'.$uid.'" type="hidden">';
echo '<input name="prot" value="'.$prot_ssl.'" type="hidden">';
echo '<input name="owndomen" value="'.$_POST['owndomen'].'" type="hidden">';
echo '<br><input name="go" value="1" type="hidden">';
echo '<br><input name="site" value="'.$_POST["site"].'" type="hidden">';
echo '<input type="submit"  value="ШАГ: 3. Перейти на сайт '.$_POST['owndomen'].'!..."/><br><br>';
echo '</form></td></tr></table>';
}
elseif($_POST['chice']=='symlink'){
	header('Location: '.$prot_ssl.$_SERVER["HTTP_HOST"].'?symlink='.$_POST['owndomen']);
	exit();
	}
}
else {
	header('Location: http://'.$_SERVER["HTTP_HOST"].'?rep=y');
	exit();
}
?>
</body></html>