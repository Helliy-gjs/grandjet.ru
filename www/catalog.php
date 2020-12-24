<?php
//Загрузочная страница сайта
ini_set('display_errors',1);
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
$pathToClasses = 'classes/';
$pathheader='';//$_SERVER["DOCUMENT_ROOT"];
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
//$_SERVER['HTTP_HOST']='grandjs.loc';
define('CLASSES', $pathheader.$pathToClasses);
if($arrdom[1] ===  'deltar.ru')include_once($pathheader.$arrdom[0].'/'.$pathToClasses.'autoload.inc');
else include_once(CLASSES.'autoload.inc');
if(file_exists('functions.php'))include_once('functions.php');
//debug($_SERVER['REQUEST_URI']);
if(strstr(trim($_SERVER['REQUEST_URI'],'/'),'api') ){	
	try {
		if(strstr($_GET['q'],'api/users')){
		$api = new UsersApi();
    }
    elseif(strstr($_GET['q'],'api/structure')){
        $api = new StrucsApi();
    }
    elseif(strstr($_GET['q'],'api/elements')){
            $api = new ElemsApi();
		}
	elseif(strstr($_GET['q'],'api/maket')){
		$api = new MaketApi();
	}	
	elseif(strstr($_GET['q'],'api/brends')){
		$api = new brendsApi();
	}	
	elseif(strstr($_GET['q'],'api/news')){
		$api = new NewsApi();
	}
	elseif(strstr($_GET['q'],'api/infos')){
		$api = new infosApi();
	}
	elseif(strstr($_GET['q'],'api/blogs')){
		$api = new blogsApi();
	}
	elseif(strstr($_GET['q'],'api/quiz')){
		$api = new quizApi();
	}
	elseif(strstr($_GET['q'],'api/params')){
		$api = new paramsApi();
	}
	elseif(strstr($_GET['q'],'api/pic')){
		$api = new picApi();
	}
	elseif(strstr($_GET['q'],'api/allmakets')){
		$api = new allmaketsApi();
	}
	elseif(strstr($_GET['q'],'api/allsites')){
		$api = new allsitesApi();
	}	
	elseif(strstr($_GET['q'],'api/pages')){
		$api = new PagesApi();
	}																																															
    echo $api->run();
	} catch (Exception $e) {
	echo json_encode(Array('error' => $e->getMessage()));
	}
	die();
}
//	
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
//else  $db = Singleton::getInstance('DB',1);
if(file_exists(CLASSES.'/Begin.inc')) include(CLASSES.'/Begin.inc');
//Расчет рабочих параметров сайта
if(!isset($Pth)) $Pth = array();
$type_access = 'general';
if(file_exists(CLASSES.'/Defmass.inc') && isset($numpage) && $type_access != 'general') include(CLASSES.'/Defmass.inc');
else {
	if(file_exists(CLASSES.'/Defshort.inc')) include(CLASSES.'/Defshort.inc');
}
$glsr = glossary();
//print_r($Pth);
//! Загрузка данных каталога
//!Параметры настройки макета

$YourMakets = $sw->allmakets(1,$disp.'-'.$arrmain['nump']);
$scripts=$Site->script;
$arrloz[0] = 'Категория товара';
$dark = 'dark';
$light = 'light';
$type_site = 'shop';
$email = 'ruslan@grandjet.ru';

$dat1['typesite'] = 'pwa';
$dat2['typesite'] = 'pwa';
$dat4['typesite'] = 'pwa';
$navMenu['typesite'] = 'pwa';
$Scrpt_page = $arrmain['scripts'];	
$Style_pages = $arrmain['style'];
//$pgExist = false;
if(!$pgExist){
//!Загрузка персональных данных макета сайта  из верстки
	
if(file_exists(CLASSES.'/personalCatData.inc') && isset($numpage)) include(CLASSES.'/personalCatData.inc');
if(file_exists(CLASSES.'/personalCatMaket.inc') && isset($numpage)) include(CLASSES.'/personalCatMaket.inc');
	}
else {	
//!Преобразование стандартных массивов в данные маета формата верстки	
$d="SELECT `id`, `Maket`, `scripts`, `flag` ,`type`,`needs` FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni";
$scrs=$db->query($d,$YourMakets[0][11],$YourMakets[0][0]);
	//print_r($scrs);
if($scrs){	
	foreach($scrs as $val)	{
		if($val->type === 'js')$Scrpt_libs[] = $val->scripts;
		if($val->type === 'css')$Style_libs[] = $val->scripts;
		}
		//print_r($arrmain['style']);
		
		

	}
	
	
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
<link rel="shortcut icon" href="favicon.png" />
<?php

//!Подключение css окружения
if(isset($Style_libs) && $pgExist){
	if(is_array($Style_libs)){
		foreach($Style_libs as $value){
			if($value && file_exists($pathheader.'/'.$scripts.'/'.$value.'.css')) echo '<link rel="stylesheet" href="'.$scripts.'/'.$value.'.css" />';
			//else echo $pathheader.'/'.$scripts.'/'.$value.'.css';
		}
	}
}
if(isset($Style_pages) && $pgExist){
	if(is_array($Style_pages)){
		foreach($Style_pages as $value){
			if($value != '' && file_exists('css/'.$value.'.css')) echo '<link rel="stylesheet" href="css/'.$value.'.css" />';
			//else echo 'css/'.$value.'.css	';
		}
	}
	echo '</head><body>';
}

if(!$pgExist){
//!первая загрузка сайта 
//первая загрузка окружения	css
echo '<link rel="stylesheet" href="./css/style.css">
    <link rel="stylesheet" href="./css/main.css">
    <link rel="stylesheet" href="./css/homepage.css">
    <link rel="stylesheet" href="./css/footer.css">
    <link rel="stylesheet" href="./css/catalog.css">';

echo '<script src="https://kit.fontawesome.com/40fe3b38f8.js" crossorigin="anonymous"></script>';
echo '</head><body>';
//первая загрузка сайта из html верстки
echo 'Первая загрузка Интернет магазин sportshop';
$contentShop = array('contact' => $contscts,'addcont'=>$contactadd,'logo'=>$contLogo,'top'=>$contenTop,'nav'=>$navMenu,'cat'=>$dat4);

echo show::showShopHeader($Pth,'',$clasShop,$contentShop,$optMenu,$Icons);
?>
<main class="page">
    <div class="page__container _container">
        <aside class="page__side">
        <?php		
echo show::showShopCatMain($Pth,$contentShop['cat'],$clasShop['cat']);

echo show::filterProducts($arrCheck);
?>
</aside>            
<div class="page__content">
<?php
echo show::showformSearches('categories-search',$contentCategories);

echo maket::viewdatapage($breadcrumbs,'breadcrumbs',$Pth,'','ul','__list','__link','');

?>
<div class="catalog">
    <h1 class="catalog__title">Категория товара</h1>
<?php
    echo maket::div2Blockstr($Pth,$catIconsDiv,show::showSortShop(),'catalog__actions actions-catalog','actions-catalog__view view-catalog');
    
    // echo '<div class="catalog__navi navi-catalog navi-catalog_top">'
        // .show::quantyPageItems().show::showListCatalog().'</div>';

    echo '<div class="catalog__products items-products">';
    echo show::showSwipSliderCatalog(contProductCat,'products-slider','products-slider__arrow');
    //echo $contProducts[1];
    echo '</div>
</div>
</div>
</div>';


echo maket::div3Blockstr($Pth,$contentInfo.$contentHelp,'page__info-menu info-menu','','page__info-menu info-menu','info-menu__body');
echo '<footer class="footer">'.$contentFooter.'</footer>';
?>
</main>
<script src="./scripts/wNumb.min.js" type="text/javascript"></script>
<script src="./scripts/nouislider.js" type="text/javascript"></script>
<script src="./scripts/swiper.min.js" type="text/javascript"></script>
<script src="./scripts/script.min.js" type="text/javascript"></script>
<?php
}else {
    
	if(file_exists(CLASSES.'/showMainCatPage.inc')) include(CLASSES.'/showMainCatPage.inc');
//загрузка js	
	if($pgExist && file_exists(CLASSES.'/Jscripts.inc'))include(CLASSES.'/Jscripts.inc');
}
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