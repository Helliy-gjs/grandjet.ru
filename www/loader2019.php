<?php	
//Загрузка библиотек

//define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
global $inf,$arrmain,$Site,$mode_edit, $pathToClasses,$pathheader, $spisok,$vend, $tabl,$tablepages, $tablenews, $numrecbd,$loz,$hh;
global $vendors,$PageM,$namenews,$numpage,$novost,$clas,$hd,$type_menu, $startpage,$levelU;
$clas=array(); 

///echo $_SERVER['HTTP_HOST'];
if(HTTP_FOLDER<>'/' && HTTP_FOLDER<>'/gjs' && HTTP_FOLDER<>$_SERVER['HTTP_HOST'] && strstr( $_SERVER['HTTP_HOST'],'/')) $_SERVER['HTTP_HOST'].=HTTP_FOLDER;


if(file_exists($pathheader.$pathToClasses.'Begin2019.inc')) include($pathheader.$pathToClasses.'Begin2019.inc');
else echo 'Нет основных переменных системы';	

if(file_exists($pathheader.$pathToClasses.'Defmass2019.inc')) include($pathheader.$pathToClasses.'Defmass2019.inc');
else echo 'Нет основных переменных системы';
?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">	
<?php
	
	//include($pathheader.$pathToClasses.'Headmain2019.inc');
if(file_exists($pathheader.$pathToClasses.'Headmain2019.inc')) include($pathheader.$pathToClasses.'Headmain2019.inc');
else echo 'Нет основных переменных тега head';
	//if(file_exists($pathheader.$pathToClasses.'instgeneral.inc')) include($pathheader.$pathToClasses.'instgeneral.inc');

if(isset($_GET['cm']) && isset($_GET['info'])) {
	echo 'Всего страниц: '.$number_pages.' опубликовано: '.$number_pub_pages;
	echo '<br>Всего новостей: '.$number_news;
	echo '<br>Всего макетов: '.$number_allmakets;
	echo '<br>Всего зарегистрированых пользователей: '.$user->getscountab('users','', 'c');
	echo '<br>Всего зарегистрированых сайтов: '.$user->getscountab('allsites','', 'c');
	echo '<br>Всего элементов каталога: '.$user->getscountab('elements','', 'c');
	echo '<br>Всего рубрик в каталоге: '.$user->getscountab('structure','', 'c');
}
	//print_r($tabl);
	//if(isset($_GET['mapS'])  && isset($tabl['elemap'])) $tabl['elem']=$tabl['elemap'];
	if(isset($_GET['mapS'])  && isset($tabl['pages'])) $tabl['elem']=$tabl['pages'];
	
	if(isset($_GET['update'])){$update=true;$upgrade=false;$upd=true;} 
	elseif(isset($_GET['recover']))  {$update=false;$upgrade=false;$upd=true;}
	elseif (isset($_GET['upgrade'])) {$update=false;$upgrade=true;$upd=true;}
	
	if(isset($_GET['error']) && $_GET['error'] == 0)$upd = true;
	else $upd = false;
	if ($Site=$user->initbdF($_SERVER['HTTP_HOST'])) {
	if(isset($PageM->MainAr))echo '<body onload=defind("'.$PageM->MainAr['hrefp'].'","'.$PageM->MainAr['typemenu'].'","'.$tabl['elem'].'")>'; 
	else echo '<body>';
	$img=$arrmain['clas']['img'].$arrmain['namep'][0];
	
	if(!$mode_work && !strstr($Site->domen,'deltar.ru')) {
		if($upd){
			show::pauza('обновление сайта из архива');
			if(isset($_GET['upgrade']) && file_exists('upgrade.php'))include('upgrade.php');
			if(isset($_GET['update']) && file_exists('update.php')) include('update.php');
			if(isset($_GET['recover']) && file_exists('update.php')) include('update.php');
		}
	}
	//echo $type_access;
	
	//Основной блок страницы, условием загрузки является установка параметров сайта
	if(isset($arrmain['typmen']) && isset($arrmain['idmen']) && $PageM->MainAr['numpage'] != ''){
		if($mode_work || $user->isGuest()){
			//include($pathheader.$pathToClasses.'Mainpage2019.inc');
			if ($type_access=='general' && file_exists($pathheader.$pathToClasses.'general.inc')) include ($pathheader.$pathToClasses.'general.inc');
			elseif(file_exists($pathheader.$pathToClasses.'Mainpage2019.inc')) include($pathheader.$pathToClasses.'Mainpage2019.inc');
			else echo 'Нет основной программы сайта';
		}
		else { 
			if(file_exists($pathheader.$pathToClasses.'Admin2019.inc')) include($pathheader.$pathToClasses.'Admin2019.inc');
			else echo 'Нет системы администрирования сайта';
			//include($pathheader.$pathToClasses.'Admin2019.inc');
		}
	//echo '===================================';
	?><!-- load javascript --><?php
	if(isset($_GET['debug']))echo '<info class="hidno">'.$pathheader.$pathToClasses.'Jscripts.inc '.$type_access.'</info>';
	include($pathheader.$pathToClasses.'Jscripts.inc');	
	}
	else show::infosh('Страница не сформирована');
	
}
else exit('Сайт не зарегистрирован в системе grandjetstudio-deltar.ru ');
echo '</body></html>';
?>