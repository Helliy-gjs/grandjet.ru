<?php
ini_set('display_errors',0);
error_reporting(E_ALL & ~E_NOTICE);
global $pathToClasses,$hosting_params;
$localpath='../';
$pathToClasses = $localpath.'classes/';
//$pathToClasses = '/classes/';
//$pathheader=$_SERVER["DOCUMENT_ROOT"];
$pathheader='';
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
$type_page=6;
$arrdom=explode('deltar.ru',$_SERVER['HTTP_HOST']);
if($arrdom[1] ===  'deltar.ru')include_once($pathheader.$arrdom[0].$pathToClasses.'autoload.inc');
else include($pathheader.$pathToClasses.'autoload.inc');
$db=Utils::loadbdsite($_SERVER['HTTP_HOST']);
include($pathheader.$pathToClasses.'Begin2019.inc');
include($pathheader.$pathToClasses.'Defmass2019.inc');
include($pathheader.$pathToClasses.'Headmain2019.inc');
//$arrmain=Page::readypagearr($PageS->MainAr,$clas,$linkpages,$Owner_site);
//$site=$Site->ids;
$arrdesc=explode('|',$Site->desc_site);		
if($arrdesc[0]<>'') $code_GGLA=$arrdesc[0];
else $code_GGLA=false;
if($arrdesc[1]<>'')$code_YAXM=$arrdesc[1];
else $code_YAXM=false;	
if($arrdesc[2]=='Y')$prot='https://';
else $prot='http://';	

$user = Singleton::getInstance('User');
$user->check();
$val_balns=$user->getBalans();
$mode=$user->areyouAdmin($_SERVER['HTTP_HOST'],$user->getuserid());
if($val_balns > 999  || $mode){
$view=1;
$loginu=$user->getLogin();
$emlu=$user->getEmail();
$uid=$user->getuserid();
$val_balns=$user->getBalans();
if($user->getLevel() < 0) {
	header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/auth/');
	exit();
}
if($user->getLeveL() == User::GUEST) {
	header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/');
	exit();
}
$ready_host='yes';
//$mass_zags=array('Учетная запись','Регистрационные данные','Мои сайты','Новый сайт','Тариф','Настройки');
//$mass_zakls=array('account','regdata','mysites','hosting','plan','other');
//echo $type_page;
$Owner_site=$user->idUserF($uid);
$hostingparams=$Owner_site->hosting;
//var_dump($hostingparams);
$hosting_params=explode(';',$hostingparams[0]);
if($type_page==6) {
	$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",'setUser');
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$mass_zags=explode('|',$arrnm);
	$mass_zakls=explode('|',$arrtp);
	
}

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Настройки</title>
		<link rel="stylesheet" type="text/css" href="/images/settingsStyle.css" />  
		<script src="/scripts/tube.js" type="text/javascript"></script>
	</head>
	<body>
		
					<?php 
//echo $menu;
//print_r($mass_zakls);
//print($Pth['adm']);
//$d="SELECT `id`, `scripts`, `flag` ,`type`,`needs` FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni";
$d="SELECT `id`, `Maket`, `scripts`, `flag` ,`type`,`needs` FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni";
$scrs=$db->query($d,$Site->ids,$idmaket);
$d="SELECT `id` FROM `fonts` WHERE `ids`=^Ni AND `idm`=^Ni";
$fnts=$db->query($d,$Site->ids,$idmaket);
//print_r($scrs);
$tarif_opt=array('Подключение','Редактор контента','Домен второго уровня SSL','Конструктор','SEO','Почта','Персональная база','Объем диска','Выделенный сервер');
$tarif_name=array('VPS/VDN','Все включено','Почтовый','Профи','Активный','Конструктор','Готовые решения','Тестовый');
$arrstr=array(11=>'Многостраничный', 0=>'Лендинг', 1=>'Галлерея', 7=>'Адаптив', 8=>'Магический', 9=>'Иерархический',6=>'Мобильный', 4=>'Фибинг', 3=>'Твитинг',5=>'Квизинг',10=>'Интернет-магазин',2=>'Блог',12=>'Слои');
$i=0;
//print_r($hosting_params); 
foreach($hosting_params as $val)if($val<>'ny')$i++;
$name_tarif=$tarif_name[9-$i];
$tarif=9-$i;
//echo $name_tarif;
//$hosting_params[1]=$arrstr[$Site->strucs];
//print_r($hosting_params);
if($hosting_params[0]=== 'ny')  $hosting_params[0]='неАктивен';
else $hosting_params[0]='Активен';
if($hosting_params[1]=== 'ny') $hosting_params[1]='Без изменение контента';
else $hosting_params[1]='С изменением контента';
if($hosting_params[2]== 'ny') $hosting_params[2]='Только домен третьего уровня без SSL' ;
else $hosting_params[2]='Домен второго c SSL и третьего уровня без SSL';
if($hosting_params[3]=== 'ny') $hosting_params[3]='Без изменения макета';
else $hosting_params[3]='С изменением макета';
if($hosting_params[4]=== 'ny') $hosting_params[4]='Без настройки SEO';
else $hosting_params[4]='С настройкой  SEO';
if($hosting_params[5]=== 'ny') $hosting_params[5]='Без почтового сервера';
else $hosting_params[5]='С почтовым сервером';
if($hosting_params[6]=== 'ny') $hosting_params[6]='Общая база данных';
else $hosting_params[6]='Персональная база данных';
if($hosting_params[7]=== 'ny' && $hosting_params[8]=='ny') $hosting_params[7]='Дисковое пространство не более 500Mb';
elseif($hosting_params[8]=== 'ny')$hosting_params[7]='дисковое пространство 1Gb';
else $hosting_params[7]='дисковое пространство 10Gb';
if($hosting_params[8]=== 'ny') $hosting_params[8]='Виртуальный сервер';
else $hosting_params[8]='Выделенный сервер VPS/VDN';

if($hosting_params[0]!='Активен' || $tarif > 4 || $user->getMs()>1){
	//echo $hosting_params[0];
	unset($mass_zags[2]);
	unset($mass_zakls[2]);
}

Maket::divclass('user-menu',$Pth,'justify-content: center;padding-left:5px;margin-bottom:5px;',' flex');

$resu=array($mass_zags,$mass_zakls);
echo show::work_pages('user',$Pth,$resu,'/settings/?',$ready_host,'hosting','mysites');
if(isset($_GET['np']))$numpage=$_GET['np'];
else $numpage=$startpage;

$user->stringusermen('user',$Pth,$db->init_data[0],$Site,$numpage);
//print_r($_GET);
echo '</div>';
if(isset($_GET['mysites']) && isset($_GET['hosting'])){
	if($_GET['mysites']=='new' && $_GET['hosting']=='yes' && $val_balns > 1000){
		if (!isset($_POST['chice'])) {
		echo '<div class="center">';	
		echo '<h3>Создание нового сайта</h3>';echo '<br>';
		echo '</div><div class="center">';
		if($tarif>7 && $val_balns > 9999)$domenforload=$_SERVER['HTTP_HOST'];
		else $domenforload='deltar.ru';
		$user->create_own_site($prot.$_SERVER['HTTP_HOST'].'?login='.$loginu.'&emlu='.$emlu.'&idu='.$uid.'&mysites='.$_GET['mysites'],$tarif);
		echo '</div>';
		}
}
else {
	$data['hosting']='<div style="width: 80%;text-align:left; padding: 0 100px;"><h2>Заказать хостинг</h2>';
	if (!isset($_POST['chice'])){
			$data['hosting'].='Для ознакомления и дальнейшей работы с Вашим сайтом Вам нет необходимости в отдельном хостинге, в общепринятом смысмле этого слова. А именно вам не нужно заключать договор с фирмой предоставляющей услуги хостинга, так как это мы берем на себя. Размещение сайта на вашем хостинге, выходит за рамки проекта на сегодняшний день, и может обсуждаться. Для этого пишите на support@grandjet.ru.  <br>';
			$data['hosting'].='В любом случае в данной системе  Ваш сайт располагается на защищеном хостинге надежного провайдера (20 лет мы вместе). <br>';
			$data['hosting'].='Вам нужно только выбрать имя и тип домена, для доступа к сайту через интернет. <br>';
			$data['hosting'].='Есть три уровня работы с сайтом: <br>';
			$data['hosting'].='<h4>Первый (основной):</h4>';
			$data['hosting'].='При использовании домена второго уровня платные условия представлены  <a href="/settings/?plan#domen">здесь...</a><br>';
			$data['hosting'].='При использовании домена третьего уровня платные условия представлены  <a href="/settings/?plan#subdomen">здесь...</a><br>';
			$data['hosting'].='<h4>Второй (начальный):</h4>';
			$data['hosting'].='<a href="/settings/?plan#sinonim">Режимы без регистрации домена</a> и <a href="/settings/?plan#symlink">тестовый </a> являются бесплатными, но имеют ограничения по возможностям <br>';
			$data['hosting'].='Без регистрации домена вы можете использовать готовые шаблоны,наполнять их своей информацией, но не можете изменять дизайн выбраного шаблона<br>';
			$data['hosting'].='Данный режим позволяет вам создать свой сайт с акцентом на его содержание.<br>';
			$data['hosting'].='После того как вы создали наполнение сайта вы можете перейти на другой уровень работы,<br>';
			$data['hosting'].='зарегистрировав домен второго или третьего уровня на платной основе<br>';
			$data['hosting'].='<h4>Третий (тестовый, ознакомительный):</h4>';
			$data['hosting'].='В тестовом режиме вы можете менять сайт в рамках предусмотренного алгоритма<br>';
			$data['hosting'].='и знакомитесь с функционалом готового сайта<br>';
			$data['hosting'].='Если Ваш домен второго '.$_POST['owndomen'].' находится не на нашем хостинге,<br>';
			$data['hosting'].='то нужно его перенести, отправив <a href="">Заявку</a>, <br>';
			$data['hosting'].='а если вы хотите обращаться к сайту c другого ресурса<br>';
			$data['hosting'].='установите на странице, с которой вы хотите переходить на главную страницу сайта<br>';
			$data['hosting'].='следующий HTML-код:<br><br>';
			$data['hosting'].='<div class="user" > &lt;head&gt;
						&lt;title&gt;redirect&lt;/title&gt;
						&lt;meta http-equiv=Refresh content="0; url=http://{Ваш_домен_третьего уровня_}.deltar.ru;" 
						&lt;/head&gt;';
			$data['hosting'].='</div><br>'; 
			$data['hosting'].='<div class="user" >&lt;head&gt;
						&lt;title&gt;redirect&lt;/title&gt;
						&lt;meta http-equiv=Refresh content="0; url=https://{Ваш_домен_второго уровня_}.ru;" 
						&lt;/head&gt;';
			$data['hosting'].='</div>'; 				
			$data['hosting'].='или организуйте переход на указанную страницу иным способом.';
			$data['hosting'].=' Затем вы просто региструете на сайте домен нужного уровня <br>';
			$data['hosting'].=' Для работы по защищеному протоколу SSL необходимо регистрировать домен второго уровня';
			$data['hosting'].='</div>';
		}
	
}
}					

//echo  '<div>';
$allpags=StructureW::getallpages('pages');
$title_chice='Перейти';
$allpags['num'][]='';
$allpags['nam'][]='';
if (isset($_POST['chice'])) $current=$_POST['chice'];
elseif(isset($_GET['np'])) $current=$_GET['np'];
else $current=$numpage;
//запуск редактора
//echo '  np '.$current.'  edp '.$_GET['editp'] ;

//РЕГИСТРАЦИОННЫЕ ДАННЫЕ ПОЛЬЗОВАТЕЛЯ

$data['account']='<div>';
$data['account'].='<h3>Информация о клиенте</h3>';
$sites_user=$user->getsitesuser($uid);
$data['account'].=$user->grandeditor('customers',$tabl,$uid,2).$user->whoareyouhere().' '.$user->Userviewer($arrmain,'user',$Pth,0);
$data['account'].='</div>';
//$data['account'].='<div class="container flex"><div class="header-button flex">';
$data['account'].=Maket::divclasstr('container-tarif',$Pth,'',' flex').Maket::divclasstr('header-button-tarif',$Pth,'justify-content: center;padding-left:5px;margin-bottom:5px;width:100%',' flex');
$data['account'].='<div>';
//ПОДРОБНЫЕ СВЕДЕНИЯ о ПОЛЬЗОВАТЕЛЕ
$data['account'].='<h3>Ваш тариф '.$name_tarif.'('.$tarif.')</h3>';
$data['account'].=Maket::divclasstr('user-tarif',$Pth);
foreach($hosting_params as $key=>$val){
			$data['account'].=Maket::divclasstr('user-tarif-opt'.$key,$Pth).'<b>'.$val.'</b></div>';
		}
$data['account'].='</div></div>';
$data['account'].='<div>';
$data['account'].='<h3>Информация о счете</h3>';
$data['account'].='</div></div></div>';		
//ИНФОРМАЦИЯ о САЙТАХ ПОЛЬЗОВАТЕЛЯ
$data['mysite']=Maket::divclasstr('container-mysite',$Pth,'',' flex').Maket::divclasstr('header-button-mysite',$Pth,'flex-wrap: wrap;justify-content: space-around;margin-left:2px;margin-bottom:5px;width:100%',' flex');
//print_r($sites_user);
if($sites_user){
	
foreach ($sites_user as $val){
		$tabl=$user->getsitetables($val->domen);
		$data['mysites'].='<div  class="flex">';
		$data['mysites'].='<div><h2>'.$val->ids.'<a href="http://'.$val->domen.'">-'.$val->domen.'</a></h2>
		Тип  '.$val->types.'<br>Структура '.$val->strucs.'<br>Назначение '.$val->appoint.'<br>Стили css '.$val->css.'<br>Скипты js '.$val->script.'<br>Таблицы <br>Страниц сайта '.$tabl['pages'].'<br>Блога '.$tabl['news'].'<br>Элементов каталога '.$tabl['elem'].'<br>Элементов изображений каталога '.$val->images.'<br>Каталог структур '.$tabl['str'].'<br>Индексы GA|YM '.$val->desc_site.'</div>';
		$data['mysites'].='<div><h2>Макет '.$type_access.'</h2>';
		$data['mysites'].='</div>';
		$data['mysites'].='</div>';
	}
}	
else $data['mysite'].='<h2>У вас пока нет сайтов</h2></div>';
//ОСНОВНЫЕ НАСТРОЙКИ САЙТОВ
$data['other']='';	
if($user->getLevelnew()>=3){	
//Настройки суперадминистратора системы grandjetstudio

if($user->isSuperAdmin()){
	$data['other']='Редактирование конфигураций.<br>---------------------------------<br>';	
	$view=2;
	$data['other'].=$user->grandeditor('configs',$tabl,1,2).' конфигурации  сайта<br>'.$user->grandeditor('configm',$tabl,1,2).' конфигурации  макета<br>'.$user->grandeditor('configp',$tabl,1,2).' конфигурации  контента<br>-----------------------------<br>';
	if($scrs){
		if(is_array($scrs))
		foreach($scrs as $val)$data['other'].='Cкрипт типа '.$val->flag.' '.$val->Maket. '.'.$val->type.' '.$val->needs.' '.$user->grandeditor('scripts',$tabl,$val->id,2).'<br>';
		else $data['other'].='Cкрипт типа '.$scrs->flag.' '.$scrs->Maket.'.'.$scrs->type.' '.$scrs->needs.' '.$user->grandeditor('scripts',$tabl,$scrs->id,2).'<br>';
	}
	$data['other'].='<a title="addscript" href="../?editp=new&tab=scripts" accesskey="t"> Добавить скрипт </a></br>';
	
	if($fnts){	
		$data['other'].='<br>-----------------------------<br>Редактирование шрифтов<br>';
		if(is_array($fnts)){
			foreach($fnts as $val)
				$data['other'].=$user->grandeditor('fonts',$tabl,$val->id,2).'<br>';
			}
			else $data['other'].=$user->grandeditor('fonts',$tabl,$fnts,2).'<br>';
		}
	$data['other'].='<a title="Добавить шрифт" href="../?editp=new&tab=fonts" accesskey="t"> Добавить шрифт</a><br>';
	$data['other'].='<br>-----------------------------<br>Редактирование структуры таблиц<br>'.
	$user->grandeditor('namparams',$tabl,0,2).' параметров сайтов<br>'.
	$user->grandeditor('namparams',$tabl,1,$view).' параметров страницы.<br>'.
	$user->grandeditor('namparams',$tabl,2,$view).' параметров элементов каталога.<br>'.
	$user->grandeditor('namparams',$tabl,3,$view).' параметров блога.<br>'.
	$user->grandeditor('namparams',$tabl,4,$view).' параметров клиента<br>'.
	$user->grandeditor('namparams',$tabl,5,$view).' параметров.<br>'.
	$user->grandeditor('namparams',$tabl,6,$view).' параметров макета страниц.<br>'.
	$user->grandeditor('namparams',$tabl,7,$view).' параметров макета сайта<br>'.
	$user->grandeditor('namparams',$tabl,8,$view).' параметров структуры каталога.<br>'.
	$user->grandeditor('namparams',$tabl,9,$view).' параметров родственных элементов каталога.<br>'.$user->grandeditor('namparams',$tabl,10,$view).' параметров родственных пользователей.<br>----------------------------------<br>'.$user->grandeditor('allsites',$tabl,$Site->ids,$view);
	$data['other'].=' сайта.<br><span>'.$user->grandeditor('allmakets',$tabl,$idmaket,$view).'<br></span>';
	}
	//$data['other'].=' сайта.<br><span>'.$user->grandeditor('allmakets',$tabl,$idmaket,$view).'<br></span>';
	//$allsts=$sw->getallstyles('maket',$Site->ids,$idmaket,$numpage,'1');
	/*$data['other'].='<span>';	
		print_r($allsts);
	if ($allsts){
		if (isset($_POST['chice1'])) $current=$_POST['chice1'];
		else $current=$allsts['id'][0];
		$title_chice='изменить стиль ';
		$data['other'].='<form style="align:left;  " method="post" action="/?editp=ok&tab=maket" target="_self">';
		$data['other'].=$user->selmenstr($allsts['Maket'][0],$Pth,$allsts['id'][0],'Style',$current,'chice1',$title_chice);
		$data['other'].='<a title="добавить стиль" href="?editp=new&tab=maket">  +</a>';
		$data['other'].='</form></span>';
	}*/
}
elseif($sites_user) {
	//НАСТРОЙКИ АДМИНИСТРАТОРА САЙТА
	$data['other'].='</div>';
	foreach ($sites_user as $val){
	$tabl=$user->getsitetables($val->domen);
	
		$data['other'].='<div  class="flex">';
		$data['other'].='<div>Сайт <h2>Домен '.$val->ids.' '.$val->domen.'</h2><br>Тип  <input type="text" value="'.$val->types.'"/><br>Структура <input type="text" value="'.$val->strucs.'"/><br>Назначение <input type="text" value="'.$val->appoint.'"/><br>Стили css <input type="text" value="'.$val->css.'"/><br>Скипты js <input type="text" value=" '.$val->script.'"/><br>Таблицы <br>Страниц сайта <input type="text" value="'.$tabl['pages'].'"/><br>Блога <input type="text" value="'.$tabl['news'].'"/><br>Элементов каталога <input type="text" value="'.$tabl['elem'].'"/><br>Элементов изображений каталога <input type="text" value="'.$val->images.'"/><br>Каталог структур <input type="text" value="'.$tabl['str'].'"/><br>Индексы GA|YM <input type="text" value="'.$val->desc_site.'"/></div>';
		$data['other'].='<div><h2>Макет '.$type_access.'</h2>';
		
		$data['other'].='</div>';
		$data['other'].='</div>';
	}
	
	
	$data['other'].='</div>';
}
	else $data['other']='';

	//print_r($hosting_params); 
	$name_button=array('Подключение сайтов к хостингу - теперь это очень просто ','Выбрать тариф','Подключить '.$user->getLogin().' к услуге хостинг','Заказать');
	//$tarif_opt=array('Название тарифа','Подключение','Домен третьего уровня','Домен третьего уровня','Персональная база','Многостраничность','Дисковое пространство','Электронная почта');
	$data['plan']='<div>';
		
	//print_r($hosting_params);

	if($hosting_params[0] != 'Активен'){
		$arr_form['host']=$hosting_params;
		$arr_form['type']=array('text','text','textarea','text','text','text','text','text','text','text');
		$arr_form['place']=array('tel...','name...2','desc...3','You...4','You...5','You...6','You...7','You...8','You...9','You...10');
		$arr_form['req']=array('required','required','','','','required','','','','');
		$arr_form['name']=array('phone','name','text');
		echo '<section class="order">';
		Maket::divclass('container',$Pth);
			//Maket::divclass('row',$Pth);
			echo '<div class="row">';
				//Maket::divclass('col-md-7',$Pth);
				show::viewformajax($arr_form,$Pth,$name_button,$tarif,5);
				
				echo '</div>';		
			echo '</div>';		
		echo '</section>';	
	}
	elseif($hosting_params[0] =='Активен'){
		
		if($tarif<8)$data['plan'].='<h2>Подключен тарифный план-'.$tarif.' '.$name_tarif.'</h2>';
		elseif($tarif==8 && $user->getBalans()>100)$data['plan'].='<h2>Тарифный план не выбран</h2>';
		else $data['plan'].='<h2>Недостаточно средств</h2>';
	}
	else $data['plan'].='Для сайта '.$Site->domen.' Вы еще не подключали ни один тарифный план <br>';
	foreach($hosting_params as $key=>$val){
			$data['plan'].='<div>'.$tarif_opt[$key].'  -  '.$val.'</div>';
		}
	foreach($mass_zakls as $val) if(isset($_GET[$val])) $page = $val;
	if (!isset($page)) $page=$mass_zakls[0];
	//show::infosh($data);
	if ($mode_edit && $page=='other'){
		echo Maket::divclasstr('admin',$Pth).$data[$page].'</div>';
	}
	else {
		echo Maket::divclasstr('center',$Pth).$data[$page].'</div>';
	}
	//show::viewer_work_page($Pth,$mass_zags,$mass_zakls,$data);
	echo '</div>';
echo '<div>';
}
else {
	header('Location: '.$prot.$_SERVER['HTTP_HOST'].'?np='.$startpage);
	exit();
}
//echo '</table>';
include($pathheader.$pathToClasses.'Jscripts.inc');
echo '</body></html>';
