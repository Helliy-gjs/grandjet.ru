<?php	
//Загрузка библиотек

//define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
global $inf,$arrmain,$Site,$mode_edit, $pathToClasses,$pathheader, $spisok,$vend, $tabl,$tablepages, $tablenews, $numrecbd,$loz,$hh,$disp;
global $vendors,$PageM,$namenews,$numpage,$novost,$clas,$hd,$type_menu, $startpage,$levelU;
$clas=array(); 
/*if(isset($_POST['curr']) && !isset($_COOKIE['currency'])) {
           if($_COOKIE['currency'] != '') setcookie('currency', $_POST['curr'],time()+3600*24*7,'/');
        }
            else {
                $_SESSION['currency'] = 'Для смены валют необходимо очитсть куку';
            }*/
///echo $_SERVER['HTTP_HOST'];
if(HTTP_FOLDER<>'/' && HTTP_FOLDER<>'/gjs' && HTTP_FOLDER<>$_SERVER['HTTP_HOST'] && strstr( $_SERVER['HTTP_HOST'],'/')) $_SERVER['HTTP_HOST'].=HTTP_FOLDER;
//Запрос на сервер и получение первичных данных
if(file_exists($pathheader.$pathToClasses.'Begin2019.inc')) include($pathheader.$pathToClasses.'Begin2019.inc');
else echo 'Нет основных переменных системы';	

//Расчет рабочих параметров сайта
if(file_exists($pathheader.$pathToClasses.'Defmass2019.inc')) include($pathheader.$pathToClasses.'Defmass2019.inc');
else echo 'Нет основных переменных системы';
?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">	
<?php


//формирование заголовков и загрузка рабочих параметров в переменные системы
if(file_exists($pathheader.$pathToClasses.'Headmain2019.inc')) include($pathheader.$pathToClasses.'Headmain2019.inc');
else echo 'Нет основных переменных тега head';
	if(isset($_GET['screenplayS']))$tabl['elem']='elemap';
	elseif(isset($_GET['mapS'])  && isset($tabl['pages']) && $mode_edit) {
		$tabl['elem']=$tabl['pages'];
	}
	else $tabl['elem']='elements';


//формирование body	сайта
//echo $PageM->MainAr['idmenu'];
echo '<body onload=defind("'.$PageM->MainAr['hrefp'].'","'.$PageM->MainAr['idmenu'].'","'.$tabl['elem'].'")>'; 



//проверка готовности работы сайта
if ($Site=$user->initbdF($_SERVER['HTTP_HOST'])) {
//Выполнение операций update upgrade	
	if(isset($_GET['upgrade']) && file_exists('upgrade.php'))include('upgrade.php');
	if(isset($_GET['update']) && file_exists('update.php')) include('update.php');
	
//$mySite =  Singleton::getInstance('Site');
//$SiteCurr=$mysite->initbdF($_SERVER['HTTP_HOST'],$numpage,$mode_edit);
//$maketSite = $mysite->getCurrentClas();
//$mysite->InfoEssence($maketSite);
//$mak_array = $sw->getDataS();
//print_r($mak_array);


//Основной контейнер сайта	
//$socialBlock=$ew->socialbutt('small');
if ($type_access !=='general' )Maket::divclass('#main_container-'.$disp,$Pth);//<div 	
	//Основной блок страницы, условием загрузки является установка параметров сайта  
	//print_r($distype);
	//var_dump($numcnfp);
	//if($mode_edit)echo $type_access.' '.$disp.' '.$uid.' '.$numcnfp['id'][0].'/'.$numcnfm['id'][0].'/'.$numcnfs['id'][0];
	if($uid < 0 )echo '<a href="https://'.$Site->domen.'/auth/">Войти</a>';
	if(isset($startpage) && isset($arrmain['typmen']) && isset($numpage) ){
		if($mode_work){
			
			//загрузка готовых решений
			if ($type_access=='general' && file_exists($pathheader.$pathToClasses.'general.inc')){ include ($pathheader.$pathToClasses.'general.inc');
			}
			//загрузка решений пользователя
			elseif(file_exists($pathheader.$pathToClasses.'Mainpage2019.inc')) {
				include($pathheader.$pathToClasses.'Mainpage2019.inc');
			}
			else echo 'Нет основной программы сайта';
		}
		elseif(file_exists($pathheader.$pathToClasses.'Manag2019.inc') && $mode_mang)include($pathheader.$pathToClasses.'Manag2019.inc');
		else { 
		//загрузка в режиме администратора
			if(file_exists($pathheader.$pathToClasses.'Admin2019.inc')) include($pathheader.$pathToClasses.'Admin2019.inc');
			else echo 'Нет системы администрирования сайта';
			
		}
	//echo '</div>';////divC#		
	//загрузка скриптов
		
	}
	else show::infosh('Страница не сформирована');
	
	}
	else exit('Сайт не зарегистрирован в системе grandjetstudio-deltar.ru ');
	echo '<div>';
	include($pathheader.$pathToClasses.'Jscripts.inc');
echo '</div></body></html>';