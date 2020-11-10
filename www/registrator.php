<?php
//Запуск режима администратора сайта	
//Унификация наименований домена
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}

//домен для регистрации сайтов пользователей

//Если в БД есть зарегистрированые сайты, то сайт будут добавлен
//Если домен зарегистрирован на нашем хостинге в Zenon 

//определяем кому будет передано управление после заполнения входной формы
//echo '---->';print_r($_GET);
if (isset($_GET['inition']) && $_GET['inition']=='registration'){
		//регистрация основного сайта системы
		$user = Singleton::getInstance('User');
		$your_domen=$_SERVER['HTTP_HOST'];
		$scr='DBinst.php';
		
		//$scr='ADDsite.php';
		echo '<div class="hidno"> Все таблицы в базе будут удалены и соданы заново. ...</div>';
		echo '<div class="hidno"> Все таблицы в базе будут удалены и соданы заново. ...</div>';
		$passw='';
		$site=1;
		$uid=1; 
		$cont='No';
//Форма передает  управление скрипту регистрации сайта и его администратора
	echo '<form  action="'.$scr.'" method="post">';
	echo '<table class="inp" border="0"><tr><td colspan="2"  with="350">ШАГ: 1. Представте администратора сайта...(*обязательные поля)'.$your_domen.'</td>';
	echo '</tr><tr><td class="r"><label>*Имя для администратора      :</label></td><td class="l"><input name="adms" value="'.$_GET['adms'].'" type="text"></td></tr>';
	echo '<tr><td class="r"><label>*Пароль для администратора :</label><td class="l"><input name="pass" value="" type="password"></td></tr>';
	echo '<tr><td class="r"><label>*Пароль для администратора :</label><td class="l"><input name="passw" value="" type="password"></td></tr>';
	echo '<tr><td class="r"><label>*Email для администратора   :</label><td class="l"><input name="eml" value="'.$_GET['eml'].'" type="text"></td></tr>';
	
	echo '<tr><td rowspan="2"><input type="submit"  value="Регистрировать  сайт '.$your_domen.' в персональной базе"/></td></tr>';
	echo '</table><input name="prot" value="'.$_GET['prot'].'" type="hidden"><input name="uid" value="'.$_POST['uid'].'" type="hidden"><input name="site" value="'.$_POST['site'].'" type="hidden"></form>';
		
	}
elseif(isset($_GET['inition']) && $_GET['inition']=='inition'){
	//регистрация основного сайта системы
	$your_domen=$_SERVER['HTTP_HOST'];
	$scr='DBinst.php';
	echo '<div class="hidno"> Все таблицы в базе будут удалены и соданы заново. .</div>';
	if($your_domen==='deltar.ru'){
		$desc['cga']='UA-138435351-1';
		$desc['cym']='53323339';
		$desc['own']='Y';
		$desc['page']='pages.csv';
		$desc['ownbd']='no';
	}
}	
else {		
	$user = Singleton::getInstance('User');
	$work_domen=$_SERVER['HTTP_HOST'];	//рабочий домен
	$your_domen=$_SERVER['HTTP_HOST'];
	$ok2=$db->getscountab('allsites','ids', 'f');
	$desc['cga']='';
	$desc['cym']='';
	$desc['own']='';
	
	if(HTTP_FOLDER<>'/' && HTTP_FOLDER<>'/gjs' ) $_SERVER['HTTP_HOST'].=HTTP_FOLDER;	
//Регистрация сайтов пользователей различных типов
$scr='ADDsite.php';
//print_r($_POST);
//if(!strstr($_POST['owndomen'],'.') || strstr($your_domen,'.'))
if (isset($_POST['chice']) && $_GET['mysites']==='new'){
	if($_POST['chice'] !== 'owndomen')$desc['ownbd']='no';
	if($_POST['chice'] === 'subdomen') unset($_POST['createdatabase']);
	if($_POST['chice']==='owndomen' && !strstr($_POST['owndomen'],'.')){
		header('Location: https://deltar.ru/settings/?mysites=new&hosting=yes&buzzy=error&ownd='.$_POST['owndomen']);exit();
	}
	if (isset($_POST['owndomen']) &&  $_POST['chice']==='subdomen') {
		if(!file_exists(HOST_MYDOMEN.$_POST['owndomen'])){		
		$your_domen=$_POST['owndomen'].'.'.$work_domen;	
		//print_r($your_domen);
		}
		
	}
	elseif(isset($_POST['owndomen']) &&  $_POST['chice']=='owndomen')   $your_domen=$_POST['owndomen'];
	elseif(isset($_POST['owndomen']) &&  $_POST['chice']=='sinonim') $your_domen=$_POST['owndomen'].'.'.$_SERVER['HTTP_HOST'];
	elseif(isset($_POST['owndomen']) &&  $_POST['chice']=='symlink' && !file_exists($_POST['owndomen'])) {
		if(file_exists('index.php')){
			$symlink_folder='copywriter';
			$your_domen=$work_domen.'/'.$_POST['owndomen'];
			$script_remote='ln -s ~/'.$work_domen.'/www/'.$symlink_folder.' ~/'.$work_domen.'/www/'.$_POST['owndomen'];
			echo shell_exec($script_remote);
		}
		else header('Location: https://deltar.ru/settings/?mysites=new&hosting=yes&buzzy');
		exit();
		}
	}		
elseif (isset($_POST['owndomen']) && $_POST['chice']<>'symlink') $your_domen=$_POST['owndomen'].'.'.$work_domen;			
else  $your_domen=$work_domen; 
//echo '---------------------------------------------------';
//print_r($your_domen);
//если нет каталога и сайт относится к домену второго или третьего уровня, проверяем свободно ли доменное имя


//if(!$IsLocal){
	define('HOST_YOURDOMEN',     '/bhome/part2/01/ritondel/'.$your_domen.'/www');
	define('HOST_YOUR',     '/bhome/part2/01/ritondel/'.$your_domen);
	if (!chdir(HOST_YOURDOMEN)&& $_POST['chice']<>'subdomen' && $_POST['chice']<>'symlink' && $_POST['chice']<>'sinonim'){

	if (!chdir(HOST_YOUR)) {
	
		if (!$user->check_domen($your_domen)){
			echo $user->check_domen($your_domen,0);
			$href1='https://deltar.ru/settings/?mysites=new&hosting=yes&buzzy='.$your_domen;
		}
		elseif($user->initbdF($your_domen)) {
			header('Location: https://deltar.ru/settings/?mysites=new&hosting=yes&thisdomen='.$your_domen.'&buzzy=exist');
			exit();
			}
		}
	}
//}

//если нет, то начинаем процесс регистрации Проверка

echo '<div class="info"> Таблицы сохраняются...</div>';


if ($ok2<>0) echo '<info class="hidno">В базе зарегистрованы '.$ok2.' сайтов.<br></info>'.$your_domen;
$ok1=$db->getscountab('users','id', 'f');
$ok3=$db->getscountab('customers','customerid', 'f');
}
//если сайт незарегистрирован или является тестовым 
//определяем значения переменных 	записываемых в таблицу
if(isset($user)){
if (!$user->initbdF($your_domen) || $_POST['chice']=='symlink') {
	
	if ($ok2) { 
		$site=$ok2+1;
		if (isset($_GET['idu']) && $_GET['mysites']=='new')$uid=$_GET['idu'];
		else $uid=$ok1+1;
	}
	else {
		$site=1;
		$uid=1;
	}
	echo '<info class="hidno">'.$ok2.' '.$your_domen.' в базе нет'.$site.'</info>';	
}
}
/*elseif(!strstr($your_domen,'.'))	{
	//при неверном выборе доменного имени возвращаемся на этап его определения
	echo 'incorrect domen name. repeat ...'.$your_domen;
	echo '<a href="/settings/?mysites=new&hosting=yes">  Повторить  </a><a href="/">  На главную </a>'  ;
	}*/
elseif(isset($user)){
	echo 'check dir';
	$erro_dist=$user->checkdistfiles(HOST_YOURDOMEN);//наличие файлов
	$erro_dirs=$user->checkdistdir(HOST_YOURDOMEN);//наличие каталогов
	//сайт загестирован то мы уже ушли на него если есть дистрибутив
	//var_dump($erro_dist);
	//var_dump($erro_dirs);
	if ($erro_dist && $erro_dirs)	{
		//$Site=$user->initbdF($your_domen);
		if($Site=$user->initbdF($your_domen)){
		echo '<div class="hidno"> В базе '.$Site->domen.' зарегистрирован '.$ok2.' </div>';
		$mass_RA=$user->right_access($Site->desc_site);
		$code_GGLA=$mass_RA['GA'];
		$code_YAXM=$mass_RA['YM'];
		$prot=$mass_RA['PR'];
		if(isset($user)){
			$user->check();	
			$uid=$user->getuserid();
		}
		$scr='';
		
			}
		}
	}
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Иницилизация системы</title>
		<?php
		
//Теги заголовка
		echo '<link rel="stylesheet" type="text/css" href="./images/settingsStyle.css" />';
		echo '<link rel="stylesheet" type="text/css" href="./images/authStyle.css" />';
		echo '<script src="./scripts/capUpdate.js" type="text/javascript"></script>';
		echo '<link rel="shortcut icon" type="image/png" href="images/favicongra.png"/>';
			
		?>
	</head>
	<body>
		<?php
//проверка внешней целостности дистрибутива сайта
$erro_dist=true;
$erro_dirs=true;
if(isset($uid) && $uid!= 1){
	$erro_dist=$user->checkdistfiles(HOST_DIST);//наличие файлов
    $erro_dirs=$user->checkdistdir(HOST_DIST);//наличие каталогов
}
//var_dump($erro_dist);
//var_dump($erro_dirs);
if ($erro_dist && $erro_dirs)	{
	
	echo '<div class="center">';
	if (isset($_GET['rep'])&& $_GET['rep']=='y') echo '<div class="info"> Такие данные уже есть в системе.</div>';
	elseif(isset($_GET['rep']) && $_GET['rep']=='p') echo '<div class="info"> В пароле  Допустимы только латинские буквы и цифры</div>';	
	elseif(isset($_GET['rep']) && $_GET['rep']=='r') echo '<div class="info"> пароли не совпадают</div>';		
// если не зарегистрован производим сбор данных для регистрации		
//данные передаются выбраному ранее скрипту
//echo 'ШАГ: 1. Представте администратора сайта...'.$_SERVER["HTTP_HOST"].'</td>';

//Если сайт уже зарегистрован и не тестовый, то переходим на него
if($db->initbdF($your_domen) && $_POST['chice']<>'symlink') {
	//print_r($user->initbdF($your_domen));
	$Site=$user->initbdF($your_domen);
	$mass_RA=$user->right_access($Site->desc_site);
	$code_GGLA=$mass_RA['GA'];
	$code_YAXM=$mass_RA['YM'];
	$prot=$mass_RA['PR'];
	$initS=$db->init_data;
	$ttext=explode('_',$initS[3]);
	$your_domen=$work_domen;
	$scr='';
	$cont='No';
	//echo $cont.'Сайт зарегистрирован на '.$ttext[0].' '.$scr;
	//header('Location: '.$prot.$your_domen.'/auth/');
	//unset($_POST['owndomen']);
}


	//если вход на страницу идет по ссылке с формы
if (isset($_POST['owndomen']) && $cont==='Yes') {
	if(isset($user))$user->check();
	$passu='';
	if (isset($_GET['login'])) $adms=$_GET['login'];
	if (isset($_GET['emlu'])) $emlu=$_GET['emlu'];
	//print_r($user->getLogin());
	//echo $cont.' '.$_POST['owndomen'].' '.$uid;
	if($ok2<12){
		if($user->getLevel()>=0){	
			$Owner_site=$user->idUserF($uid);	
			//$Owner_site->ids=$Site->ids;
			//$Owner_site->start=$startpage;
		if($Owner_site->level>0){
			$firm['em']=$user->getEmail();
			$firm['name']=$user->getLogin();
			$firm['cfio']=$Owner_site->cfio;
			$firm['telmain']=$Owner_site->telmain;
			//if($user->checkPrivate($firm) && $Owner_site->level==2) $user->addManagerRights($uid);
			$hosting_params=$Owner_site->hosting;
			$social_link=$Owner_site->social;
			$code_host=0;
			foreach($hosting_params as $val)if($val<>'ny')$code_host++;
			$tarif=9-$code_host;
		}
		}	
	//print_r($Owner_site->hosting);	
	//Форма передает  управление скрипту регистрации сайта запустившего его пользователя
	$resu=$user->read_namparams('setTarifPlan',0);
	//print_r($resu);
	if($_POST['chice']==='subdomen')	{
		//$tarif_all=array('Почтовый','Профи','Активный','Конструктор','Готовые решения','Тестовый');
		$tar_max=4;
		
	}
	elseif($_POST['chice']==='sinonim') {
		//$tarif_all=array('Профи','Активный','Конструктор','Готовые решения','Тестовый');
		$tar_max=3;
	}
	elseif($_POST['chice']==='symlink'){
		//$tarif_all=array('Активный','Конструктор','Готовые решения','Тестовый');
		$tar_max=2;
	}
	else { 
		//$tarif_all=array('VPS/VDN','Все включено','Почтовый','Профи','Активный','Конструктор','Готовые решения','Тестовый');
		$tar_max=8;
	}
	foreach($resu[0] as $key=>$val)if($key > (8 - $tar_max))$tarif_all[]=$val;
	$resu=$user->read_namparams('setTypesSite');
	$arr_types=$resu[0];
	//array(6=>'Компактный',3=>'Галлерея',7=>'Дизайнерский',8=>'Структурированый',4=>'Мобильный',5=>'Адаптивный',9=>'Каталог',1=>'Лента новостей',2=>'Видеоблог',0=>'Визитка',10=>'Корпоративный');
	$resu=$user->read_namparams('setMaketPage');
	$arr_strucs=$resu[0];
	//$arr_strucs=array(11=>'Магический', 0=>'Лендинг', 1=>'Галлерея', 7=>'Адаптив', 8=>'Многостраничный', 9=>'Иерархический',6=>'Мобильный', 4=>'Фибинг', 3=>'Твитинг',5=>'Квизинг',10=>'Интернет-магазин',2=>'Блог',12=>'Слои');
	for($i=0;$i<$code_host+5;$i++){
		$arridmen[$i]=$i;
		$arrtyps[$i]=$arr_types[$i].'('.$i.')';
		$arrstr[$i]=$arr_strucs[$i].'('.$i.')';
		if($tarif_all[$tar_max-$i]<>'' && $i<$tar_max)$tarif_name[$i]=$tarif_all[$tar_max-$i].'('.$i.')';
	}
	$resu=$user->read_namparams('setTypesWork');
	$arripp=$resu[0];
	
	if($_POST['chice']<>'subdomen' && $_POST['chice']<>'sinonim')$givesite=$_POST['owndomen'];
	else $givesite=$your_domen;
	
	echo '<form  action="'.$scr.'" method="post" enctype="multipart/form-data">';
	echo '<table class="inp" border="0"><tr><td colspan="2"  with="350">';
	echo '<input name="adms" value="'.$adms.'" type="hidden">';
	echo '<input name="pass" value="'.$passu.'" type="hidden">';
	echo '<input name="eml" value="'.$emlu.'" type="hidden">';
	echo '<input name="owndomen" value="'.$givesite.'" type="hidden">'; 
	if($_POST['chice']=='subdomen') echo '<input name="catalog" value="'.$_POST['owndomen'].'" type="hidden">'; 
	echo '<input name="mysites" value="new" type="hidden">';
	echo '<input name="chice" value="'.$_POST['chice'].'" type="hidden">';
	echo '<input name="cont" value="No" type="hidden">';
	if(!isset($_POST['createdatabase'])){
		echo 'ШАГ: 1. Загрузите файлы (если вы их подготовили). для вашего сайта '.$_POST['owndomen'].'</td>';
		echo '<tr><td class="r"><label>Загрузка данных страниц сайта из файла:</label><td class="l"><input name="page" type="file"><input type="hidden" name="page1" value=""/>формат csv/UTF-8 </td></tr>';
		echo '<tr><td class="r"><label>Загрузка общего баннера(jpg, png, gif):</label><td class="l"><input name="banmain" type="file"><input type="hidden" name="banmain1" value=""/></td></tr>';
		echo '<tr><td class="r"><label>Загрузка логотипа(png better):</label><td class="l"><input name="logo" type="file"><input type="hidden" name="logo1" value=""/></td></tr>';
		echo '<tr><td class="r"><label>Код Google Analitic   :</label><td class="l"><input name="cga" value="'.$desc['cga'].'" type="text"></td></tr>';
		echo '<tr><td class="r"><label>Код Yandex Metrika   :</label><td class="l"><input name="cym" value="'.$desc['cym'].'" type="text"></td><input type="hidden" name="ownbd" value="'.$desc['ownbd'].'"/></tr>';
	
	}
	else echo '<tr><td class="r"><input type="hidden" name="ownbd" value="'.$_POST
	['createdatabase'].'"/></td></tr>';	
	$user->selmen($tarif_name,'',$arridmen,'',$tarif,'tarif','Выбрать');
	$user->selmen($arrstr,'',$arridmen,'',count($arrstr),'strucs','Выбрать');
	$user->selmen($arripp,'',$arridmen,'',count($arripp),'ippt','Выбрать');
	$user->selmen($arrtyps,'',$arridmen,'',count($arrtyps),'typs','Выбрать');
	if(strstr($_POST['owndomen'],'.') || strstr($your_domen,'.')) {
		echo '<input type="submit"  value="Подтвердите создание сайта на домене '.$_POST['owndomen'].'"/></td></tr>';
	}
	elseif($_POST['chice']=='symlink')	echo '<input type="submit"  value="Подтвердите создание сайта на домене '.$work_domen.'/'.$givesite.'"/></td></tr>';
	echo '</table><input name="uid" value="'.$uid.'" type="hidden"><input name="site" value="'.$site.'" type="hidden"></form>';
}
else echo '<form><input href="https://'.$work_domen.'" type="submit" value="Перейти на главную"><br> Регистрация сайтов приостановлена на период внутреннего тестирования системы.</form>'; 
}
elseif($scr=='DBinst.php' && $cont=='Yes') {
	//Если вход прямо из браузера
	if ($ok2==0 && $work_domen='deltar.ru') $passw='tardeladmadmtard';
	else $passw='';

//Форма передает  управление скрипту регистрации сайта и его администратора
	echo '<form  action="'.$scr.'" method="post" enctype="multipart/form-data">';
	echo '<table class="inp" border="0"><tr><td colspan="2"  with="350">ШАГ: 1. Представте администратора сайта...(*обязательные поля)'.$your_domen.'</td>';
	echo '</tr><tr><td class="r"><label>*Имя для администратора      :</label></td><td class="l"><input name="adms" value="" type="text"></td></tr>';
	echo '<tr><td class="r"><label>*Пароль для администратора :</label><td class="l"><input name="pass" value="" type="password"></td></tr>';
	echo '<tr><td class="r"><label>*Пароль для администратора :</label><td class="l"><input name="passw" value="'.$passw.'" type="password"></td></tr>';
	echo '<tr><td class="r"><label>*Email для администратора   :</label><td class="l"><input name="eml" value="" type="text"></td></tr>';
	echo '<tr><td class="r"><label>Код Google Analitic   :</label><td class="l"><input name="cga" value="'.$desc['cga'].'" type="text"></td></tr>';
	echo '<tr><td class="r"><label>Код Yandex Metrika   :</label><td class="l"><input name="cym" value="'.$desc['cym'].'" type="text"></td></tr>';
	echo '<tr><td rowspan="2"><input type="submit"  value="Регистрация  сайта '.$your_domen.'"/></td></tr>';
	echo '<tr><td class="r"><label>Загрузка данных страниц сайта из файла:</label><td class="l"><input name="pages" type="file"><input type="hidden" name="pages1" value="'.$desc['page'].'"/>формат csv/UTF-8 ,fe '.$desc['page'].'</td></tr>';
	echo '</table><input name="prot" value="'.$desc['own'].'" type="hidden"><input name="ownbd" value="'.$desc['ownbd'].'" type="hidden"><input name="uid" value="1" type="hidden"><input name="site" value="1" type="hidden"></form>';
}
else {
	//print_r($_POST);
	$dest_domen='/bhome/part2/01/ritondel/'.$_POST['owndomen'].'/www/';
	//echo '<form><input type="submit" value="Пауза"/></form>';
	if(isset($_POST['owndomen']) &&  $_POST['chice']=='owndomen')$result=$user->createsitedir($dest_domen,HOST_DIST);
}
}
	else {
	echo 'ERROR_files_dist '.$erro_dist.' ERROR_dir_dist '.$erro_dirs.'<br>';	
	exit('Дистрибутив не найден <br>');
	} 
echo '</div>';	
//если сайт зрегистрирован передаем ему управление	
if(isset($user))$user->check();
if (isset($_POST['site'])|| $db->initbdF($your_domen)) {
if($user->getLevel() <= 0) {
	header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/auth/?guest');
	exit();
}
else { 
	//header('Location: http://'.$_SERVER['HTTP_HOST'].'/'.$Site->nmpage);
	if (isset($_GET['np'])) $nump=$_GET['np'];
	else $nump=0;
//include($pathToClasses.'Begin2018.inc');	
//print_r($Site);
if ($Site->nmpage=='') $Site->nmpage='index.php';
if($cont<>'Yes'){
if ($Site->domen == $your_domen && $nump<>0) 
{
	header('Location: '.$prot.$Site->domen.'/'.$Site->nmpage.'?np='.$nump);
    exit();
}
else {
	header('Location: '.$prot.$Site->domen.'/'.$Site->nmpage);
   exit();
	
		}
	}
}
}
?>