<?php
//Теги заголовка
echo '<head>';
echo '<meta http-equiv="X-Content-Type-Options: nosniff" content="text/html; charset=UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">';
echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
	<meta http-equiv="X-UA-Compatible" content="IE=edge" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0" />';
	//if($faveic=='')echo '<link rel="shortcut icon" href="favicongjs.png" />';
	//echo '<script src="'.$localpath.'/scripts/script.min.js" type="text/javascript">';
	//echo '<script src="'.$localpath.'/scripts/tree_menu.js" type="text/javascript"></script><script src="'.$localpath.'/scripts/tube.js" type="text/javascript"></script>	<script src="'.$localpath.'/scripts/sort.js" type="text/javascript"></script>';
	/*$mysite = Singleton::getInstance('Site');
	$SiteCurr=$mysite->initbdF($_SERVER['HTTP_HOST'],$numpage,$Pth,$mode_edit);
	$envirSite = $mysite->getEnvirSite();
	//$mysite->InfoEssence($envirSite);
	$mysite->loadenviroment();
	*/
	if($type_access === 'general'){
	
	}
if($active_GGLA || $active_YAXM && file_exists('metrica.php')) include_once('metrica.php');
	
//Первым загружается стиль глобальный
		//Параметры макета сайта
//Определяются загружаемые стили и скрипты
//Все загружаемые данные являются внешними и подгружаются из других файлов
//ссылка Файлы стилий  всех страниц макетов grandjetstudio хранятся в таблице Pages
//Пользовательские стили хранятся в maket для каждой страницы свои
//ссылки на внешнии пользовательские файлы стилей  и скриптов хранится в таблице allsites
//show::infosh($spisok_mak_par);
//первым загружаются стили и параметры установленые на странице
//если на странице нет стилей, то загружаются стили стартовой страницы
$msw='';
if (!$PageM->MainAr['hrefstyle']==='') {
	if(file_exists($clas['img'].$PageM->MainAr['hrefstyle'].'.min.css')) {
		$Style_page=$clas['img'].$PageM->MainAr['hrefstyle'].'.min.css'; 
		$msw.='|PSW';
	}
	else $Style_page='';
	//if($mode_edit)echo '<info class="hidno">в ./images отсутствует файл стилей</info>';
	
}
else {
	$Style_page='';
	//if($mode_edit)echo '<info class="hidno">локальные стили текущей страницы не установлены</info>';
}

//echo '<meta http-equiv="X-Content-Type-Options: nosniff" content="text/html; charset=UTF-8" />';

//echo '<link rel="stylesheet" href="./images/stylecont.min.css" />';

//Загрузка библиотеки bootstrap
if(isset($Pth['global']['Bootstr'][0])) {
	$msw.='|BSW';
	echo '<link rel="stylesheet" href="'.$localpath.'libs/bootstrap/bootstrap-grid-3.3.1.min.css" />
	<link rel="stylesheet" href="'.$localpath.'libs/font-awesome-4.2.0/css/font-awesome.min.css" />
	<link rel="stylesheet" href="'.$localpath.'libs/fancybox/jquery.fancybox.css" />
	<link rel="stylesheet" href="'.$localpath.'libs/owl-carousel/owl.carousel.css" />
	<link rel="stylesheet" href="'.$localpath.'libs/countdown/jquery.countdown.css" />';
}
//echo $type_access; 
$standart_style=$arrmain['idmen'][0];
//if($mode_edit)echo '<info class="hidno">=='.$type_access.' режим стилей установлен</info>';
$style_Set[6]=$clas['img'].'settingsStyle.min.css';
if($type_access=='global'){
	$msw.='|GLV';
	echo '<title>'.$arrmain['titles'].'-GLV</title>';
	
if($Style_page<>'' && file_exists($Style_page)) {
		$msw.='|LSW';
		echo '<link rel="stylesheet" type="text/css" href="'.$Style_page.'" />';
		//if($mode_edit)echo '<info class="hidno">==добавлен local стили '.$Style_page.'</info>';
	}
elseif (isset($Site->css)){
	
	if(strstr($Site->css,'|')){
		
		$spisok='';
		$Style_Global=explode('|',$Site->css);
		foreach($Style_Global as $val)	{
			if(file_exists($clas['img'].$val.'.min.css')&& $val<>''){
				echo '<link rel="stylesheet" type="text/css" href="'.$clas['img'].$val.'.min.css" />';
				$msw.='|GSW';
			}
			   if($val<>'')$spisok.='-'.$val;
	}
		//if($mode_edit)echo '<info class="hidno">==global стили '.$spisok.' загружены на сайт</info>';
	}
	elseif($Site->css<>'') {
		if(file_exists($clas['img'].$Site->css.'.min.css'))echo '<link rel="stylesheet" type="text/css" href="'.$clas['img'].$Site->css.'.min.css" />';
		//else echo '<info class="hidno">==global стиль '.$Site->css.'  не загружен на сайт</info>';
		//if($mode_edit)echo '<info class="hidno">==global стиль '.$Site->css.' загружен на сайт</info>';
	}
	else {
		$Site->css='style'.$arrmain['idmen'][0];
		if(file_exists($clas['img'].$Site->css.'.min.css'))echo '<link rel="stylesheet" type="text/css" href="'.$clas['img'].$Site->css.'.min.css" />';
		//else echo '<info class="hidno">==global стиль '.$Site->css.'  не загружен на сайт</info>';
		//if($mode_edit)echo '<info class="hidno">==global стиль '.$Site->css.' загружен на сайт</info>';
	}	
}	
$style_Set[6]=$clas['img'].'settingsStyle.min.css';
}
elseif($type_access=='general') {
	$msw.='|GEV';
	echo '<title>'.$arrmain['titles'].'-GEV</title>';
	if(isset($Style_users)){
		$msw.='|GESW';
	if(is_array($Style_users)){
	foreach($Style_users as $value) {
	//print_r($value);
		if(file_exists($value)){
			echo '<link rel="stylesheet" type="text/css" href="'.$value.'" />';
			//if($mode_edit)echo '<info class="hidno">==загружен user стиль '.$value.'</info>';
		}
		//elseif($mode_edit) echo '<info class="hidno">==Не загружен general стиль '.$value.'</info>';
		}
		}
	elseif ($Style_users <> '' && file_exists($Style_users[0])) {
		$msw.='|USW';
		echo '<link rel="stylesheet" type="text/css" href="'.$Style_users[0].'" />';
		//if($mode_edit)echo '<info class="hidno">==загружен user стиль '.$Style_users[0].'</info>';
	}
	elseif(file_exists($clas['img'].'style'.$standart_style[0].'.min.css')) {
		$msw.='|SSW';
		echo '<link rel="stylesheet" type="text/css" href="'.$clas['img'].'style'.$standart_style[0].'.min.css" />';
	}
	else {
		//if($mode_edit)echo '<info class="hidno">==пользовательские стили не установлены<br></info>';
		
		}
	}
	if($Style_page<>'' && file_exists($Style_page)) {
		$msw.='|LSW';
		echo '<link rel="stylesheet" type="text/css" href="'.$Style_page.'" />';
		//if($mode_edit)echo '<info class="hidno">==добавлен page стиль'.$Style_page.'</info>';
	}
}
else {
	
	echo '<title>'.$arrmain['titles'].'-LOV</title>';
	
}
//print_r($Style_page);
if($Style_page<>'' && file_exists($Style_page)){
		$msw.='|LSW';
		echo '<link rel="stylesheet" type="text/css" href="'.$Style_page.'" />';
		//if($mode_edit)echo '<info class="hidno">==добавлен local '.$Style_page.' стили </info>';
	}
//elseif($mode_edit) echo '<info class="hidno">==local стили не загружены на сайт</info>';
//Если установлены стили в макете то они загружаются, и могут отменить некоторые правила глобального стиля
//print_r($Style_users);echo '+++++++++++';


//else echo 'Не загружен стиль '.$Style_users[0];
//дополнительные стили для страниц настройки

if(isset($Pth['global']['styles']) && !isset($style_Set[6])){
	$msw.='|SETSW';
	$style_Set=$user->getstylesfiles($clas,$Pth['global']['styles'],6);
}
else {$msw.='|SETSW';$style_Set[6]=$clas['img'].'settingsStyle.min.css';}
if($style_Set[6]<>'' && file_exists($style_Set[6])){
	echo '<link rel="stylesheet" type="text/css" href="'.$style_Set[6].'" />';
	//if($mode_edit)echo '<info class="hidno">==стили страниц настройки '.$style_Set[6].'  загружены на сайт</info>';
}
//elseif($mode_edit) echo '<info class="hidno">==стили настройки   не загружены на сайт</info>';

//Если установлены стили страницы загружаются они отменя некоторые правила макета

echo '<meta name="description" content="'.$arrmain['descr'].'">';
if(isset($faveic)){
	if(file_exists('./'.$faveic))echo '<link rel="icon" type="image/png" href="./'.$faveic.'" />';
}
echo '<style>
info.hidno{
	display: none;
}
@font-face {
  font-family: "Roboto";
  src: url("../fonts/Roboto/Roboto-Bold.woff2") format("woff2"), url("../fonts/Roboto/Roboto-Bold.woff") format("woff");
  font-weight: bold;
  font-style: normal; }
</style>';
echo '<style>
@font-face {
  font-family: "Museo";
  src: url("../fonts/Museo/MuseoSansCyrl_1.otf") format("opentype");
}
</style>';
echo '<link rel="stylesheet" href="./images/swiper.min.css">';

echo "<SCRIPT LANGUAGE=\"JavaScript\">
var href;
function new_window(href)
{
window.open(href,'newwin','top=400, left=400, menubar=0, toolbar=0, location=0, directories=0, status=0, scrollbars=1, resizable=0, width=400, height=600');
}
function closeOpenedWindow() {
  openedWindow.close()
}


</SCRIPT>";
//print_r($Pth['global']['Sizes']);
if (file_exists('./images/stylemaket.css')){
	echo '<link rel="stylesheet" href="./images/stylemaket.css" />';
}
if (file_exists($pathheader.$pathToClasses.'mainstyles_'.$arrmain['idmen'][0].'.inc')){
	//echo '<info class="hidn">Загружаем базовые стили макета из  mainstyles_'.$arrmain['idmen'][0];
	//include($pathheader.$pathToClasses.'mainstyles_'.$disp.'.inc');
}
echo '</head>';
//echo $pathheader.$pathToClasses.'mainstyles_'.$arrmain['idmen'][0].'.inc';
//echo phpinfo();
//if($mode_edit)echo '<info class="hidno">==макет страницы '.$idmakets[0]['Maket'].'</info>';

?>