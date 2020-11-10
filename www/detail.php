<?php
ini_set('display_errors',0);
error_reporting(E_ALL);
global $pathToClasses, $eid;
//$pathToClasses = '../classes/';
//include_once($pathToClasses.'autoload.inc');
define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']).'/');
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));
//echo HOST_ROOT;echo "<BR>";
//echo $_SERVER["DOCUMENT_ROOT"];echo "<BR>";
//echo $_SERVER['HTTP_HOST'];echo "<BR>";
//$pathToClasses = '/classes/';
//$pathheader='.';
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
if (strstr($_SERVER['HTTP_HOST'],'.loc')) {
			$IsLocal = true;
		}
else {
	$IsLocal = false;		
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	$pathToClasses='/classes/';
}
		
if($_SERVER['HTTP_HOST']==='localhost'){
	$localpath=$_SERVER['HTTP_HOST'].'/grandjetstudio.com/www';
	$pathheader=$_SERVER["DOCUMENT_ROOT"].'/grandjetstudio.com/www';
}
else $localpath='';		
	
include($pathheader.$pathToClasses.'autoload.inc');
$db=Utils::loadbdsite($_SERVER['HTTP_HOST'],$IsLocal);
include($pathheader.$pathToClasses.'Begin2019.inc');
include($pathheader.$pathToClasses.'Defmass2019.inc');
include($pathheader.$pathToClasses.'Headmain2019.inc');
//$ew = Singleton::getInstance('ElementsW');
//$user = Singleton::getInstance('User');
if ($user->initbdF($_SERVER['HTTP_HOST'])) $Site=$user->initbdF($_SERVER['HTTP_HOST']);
else {
	exit('нет сайта'); 
}
$pathscrypt='tree_menu.js';
$tablepages=$Site->pages;
$tablenews=$Site->news;
$tabl_elem=$Site->element;
$clas['class']=array('1'=>'block1','3'=>'block3','2'=>'block2','4'=>'block4',
 '5' => 'center','6' => 'user','7' => 'zag','8' => 'news',
 '9' => 'section','10' => 's0','11' => 's1','12' => 's2','13' => 's3',
 '14' => 's4','15' => 's5','16' => 's6','17' => 's7','18' => 's8',
 '19' => 's9', '20' => 's10');
$clas['img']='./images/';
$choice_vendors;
$tabl=array('news'=>$tablenews, 'pages'=>$tablepages);			
//echo 'Работа с удаленным сервером';echo "<BR>";
	
	
require (HOST_ROOT.'book/book_sc_fns.php');
$eid = 0;
$ok = 0;
$startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
if (!$startpage) exit('Данная ссылка не авторизована в системе grandjet.ru');
if(isset($numpage)) $PageM= new Page($numpage,$tabl);
else $PageM= new Page($startpage,$tabl);
$numpage=$PageM->MainAr['numpage'];

if(isset($_GET['eid']))
	$eid = $_GET['eid'];
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<?php 
echo '<head>';
echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
echo '<title>'.$PageM->MainAr['title'].'</title>';
echo '<link rel="stylesheet" type="text/css" href="'.$PageM->MainAr['hrefstyle'].'" />';
echo '<script src="'.$PageM->MainAr['hrefscripts'].'/'.$pathscrypt.'" type="text/javascript"></script>';
echo '<script src="'.$PageM->MainAr['hrefscripts'].'/tube.js" type="text/javascript"></script></head>';
		// иницилизация переменных при загрузке страницы
		echo '<body onload=defind("'.$PageM->MainAr['hrefp'].'","'.$PageM->MainAr['typemenu'].'")>';
		
		if($eid != 0) {
			
			$el = $ew->getElement($eid,$tabl['elem']);
			$section=$ew->getSection($eid);
			Maket::divclass('section-goods',$Pth);
			$ok=$ew->showgood($el,$Pth);
			echo '</div>';
			
		} 
		if(!$ok) {
			echo 'нет такого товара';
		}
	?>		
	</body>
</html>