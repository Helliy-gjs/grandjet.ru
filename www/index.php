<?php
//Загрузочная страница сайта
ini_set('display_errors',0);
error_reporting(E_ALL & ~E_NOTICE);
global $inf,$arrmain,$Site,$mode_edit, $pathToClasses,$pathheader, $spisok,$vend, $tabl,$tablepages, $tablenews, $numrecbd,$loz,$hh,$disp;
$clas=array(); 

define('SCRIPT_NAME',    dirname($_SERVER['SCRIPT_NAME']));
define('HTTP_FOLDER',    substr(SCRIPT_NAME,1));
define('HOST_SYSTEM','/bhome/part2/01/ritondel/');
define('HOST_DIST',    HOST_SYSTEM.'/distributive');
define('HOST_MYDOMEN',     HOST_SYSTEM.$_SERVER['HTTP_HOST'].'/www/');
define('HOST_MY',     HOST_SYSTEM.$_SERVER['HTTP_HOST']);
//echo $_SERVER["DOCUMENT_ROOT"].HTTP_FOLDER;
$clas=array();
//header('Content-Type: text/html; charset="utf-8"');
//Загрузка внутрених библиотек
//$pathToClasses = '/classes/';
//$pathheader='.';
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
//$_SERVER['HTTP_HOST']='grandjs.loc';
define('CLASSES', $pathheader.$pathToClasses);
//echo CLASSES;
if($arrdom[1] ===  'deltar.ru')include_once($pathheader.$arrdom[0].'/'.$pathToClasses.'autoload.inc');
else include_once(CLASSES.'autoload.inc');
if(file_exists('functions.php'))include_once('functions.php');
//debug($_SERVER['REQUEST_URI']);
if(strstr(trim($_SERVER['REQUEST_URI'],'/'),'api') ){	
	include(CLASSES.'allapi.inc');
}
//	Подключение базы данных
$db=Utils::loadbdsite($_SERVER['HTTP_HOST']);
$ew = Singleton::getInstance('elementsW');
$sw = Singleton::getInstance('StructureW');
$user = Singleton::getInstance('User');
$Site=$user->initbdF($_SERVER['HTTP_HOST']);
$rest=$user->read_namparams('setMaketPage');
$arridmen=$rest[1];
if(!isset($Pth)) $Pth = array();
//debug($arridmen);
//echo $arridmen[$Site->strucs];
$pgTypeExist = intval($db->getscountab($Site->pages,'numpage', 'f','idmenu',$arridmen[$Site->strucs]));
//var_dump($pgTypeExist);
//else  $db = Singleton::getInstance('DB',1);
if($pgTypeExist == 0){
	$Pth['adm']=array('np'=>1,'uid'=>1,'ids'=>1,'idm'=>1,'sp'=>1);
	//echo 'Нет ни одной страницы '.$pgTypeExist;
	if($arridmen[$Site->strucs]== 'shop'){
		if(file_exists(CLASSES.'loadMainShopPage.inc')) include(CLASSES.'loadMainShopPage.inc');
		else echo 'не дoступен '.CLASSES.'loadMainShopPage.inc';
	}
	elseif($arridmen[$Site->strucs]== 'land'){
		if(file_exists(CLASSES.'loadMainLandPage.inc')) include(CLASSES.'/loadMainLandPage.inc');
		else echo 'не дoступен '.CLASSES.'loadMainLandPage.inc';
	}
}	
else {
	//echo 'страница найдена';
	//die();
if(file_exists(CLASSES.'Begin.inc')) include(CLASSES.'Begin.inc');
//Расчет рабочих параметров сайта

$type_access = 'general';

if(file_exists(CLASSES.'Defmass.inc') && isset($numpage) && $type_access != 'general') include(CLASSES.'Defmass.inc');
else {
	if(file_exists(CLASSES.'Defshort.inc')) include(CLASSES.'Defshort.inc');
}

$glsr = glossary();
 
//! Загрузка данных каталога
//!Параметры настройки макета
//echo $arrmain['idmen'][0].'-'.$numpage;
// echo $arridmen[$Site->types];



	$Scrpt_page = $arrmain['scripts'];	
	$Style_pages = $arrmain['style'];
	$scripts=$Site->script;
//Выбираем макет
$YourMaket = $YourMakets[$disp.'-'.$arrmain['nump']];
//!Преобразование стандартных массивов в данные маета формата верстки	
$d="SELECT `id`, `Maket`, `scripts`, `flag` ,`type`,`needs` FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni";
$scrs=$db->query($d,$YourMaket[0][11],$YourMaket[0][0]);
	//print_r($scrs);
if($scrs){	
	foreach($scrs as $val)	{
		if($val->type === 'js')$Scrpt_libs[] = $val->scripts;
		if($val->type === 'css')$Style_libs[] = $val->scripts;
		}
		//print_r($arrmain['style']);
	}
//debug($Style_pages);

//!формирование html кода страницы
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title><?=$arrmain['titles']?></title>
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<link rel="shortcut icon" href="favicongjs.png" />
<?php
//!Подключение css окружения

	if(isset($Style_libs)){
		if(is_array($Style_libs)){
			foreach($Style_libs as $value){
				if($value && file_exists($pathheader.'/'.$scripts.'/'.$value.'.css')) echo '<link rel="stylesheet" href="'.$scripts.'/'.$value.'.css" />';
				//else echo $pathheader.'/'.$scripts.'/'.$value.'.css';
			}
		}
	}
	if(isset($Style_pages)){
		if(is_array($Style_pages)){
			foreach($Style_pages as $value){
				if($value != '' && file_exists('css/'.$value.'.css')) echo '<link rel="stylesheet" href="css/'.$value.'.css" />';
				//else echo 'css/'.$value.'.css	';
			}
		}
	}
echo '</head><body>';
if($arrmain['idmen'][0]== 'shop'){
	if(file_exists(CLASSES.'showMainShopPage.inc')) include(CLASSES.'showMainShopPage.inc');
}
elseif($arrmain['idmen'][0]== 'land'){
	if(file_exists(CLASSES.'showMainLandPage.inc')) include(CLASSES.'showMainLandPage.inc');
}
//загрузка js	
	if($pgExist && file_exists(CLASSES.'Jscripts.inc'))include(CLASSES.'Jscripts.inc');
	//echo '<script src="js/common.js"></script>';
}
//! Подключение javascript окружения
?>
<div class="hidden"></div>
	<!--[if lt IE 9]>
	<script src="libs/html5shiv/es5-shim.min.js"></script>
	<script src="libs/html5shiv/html5shiv.min.js"></script>
	<script src="libs/html5shiv/html5shiv-printshiv.min.js"></script>
	<script src="libs/respond/respond.min.js"></script>
	<![endif]-->
<!--!Подключение скриптов для поисковиков и SEO -->
	<!-- Yandex.Metrika counter --><!-- /Yandex.Metrika counter -->
	<!-- Google Analytics counter --><!-- /Google Analytics counter -->
</body>
</html>