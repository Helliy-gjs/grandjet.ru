<?php
ini_set('display_errors',1);
error_reporting(E_ALL & ~E_NOTICE);
global $pathToClasses;
global $pathToClasses,$pathheader, $spisok,$vend, $tabl, $tablepages, $tablenews, $numrecbd,$loz,$hh;
global $vendors,$PageM,$namenews,$novost,$clas,$hd,$type_menu,$cid, $sid;
//$pathToClasses = '/classes/';
//$pathheader='.';
//include_once ($pathheader.$pathToClasses.'autoload.inc');
//$user = Singleton::getInstance('User');

//die();
if($_POST['pass'] ==  $_POST['passw']){
	print_r($_POST);
	if (!preg_match("#^[a-z0-9]+$#i", $_POST['pass'])){
	  header('Location: http://'.$_SERVER['HTTP_HOST'].'?rep=p');
	  exit();
	}
	if (!preg_match("#^[a-z0-9]+$#i", $_POST['passw'])){
	  header('Location: http://'.$_SERVER['HTTP_HOST'].'?rep=p');
	  exit();
	}

	if($_POST['pass'] != $_POST['passw']) {
		header('Location: http://'.$_SERVER['HTTP_HOST'].'?rep=r');
		exit();
	}
}
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
define('CLASSES', $pathheader.$pathToClasses);
if(strstr($_SERVER['HTTP_HOST'],'deltar.ru')) {
	$arrdom=explode('deltar.ru',$_SERVER['HTTP_HOST']);
	if($arrdom[1] ===  'deltar.ru')include_once($pathheader.$arrdom[0].'/'.$pathToClasses.'autoload.inc');
}
else include_once(CLASSES.'autoload.inc');
$db=Utils::loadbdsite($_SERVER['HTTP_HOST']);
if (isset($_POST['adms']) && isset($_POST['pass']) && isset($_POST['eml']) && isset($_POST['site'])) {
	include('/bhome/part2/01/ritondel/deltar.ru/www/CREATBD.php');
	
	try {
		foreach($query as $val)
			$db->query($val);
	} catch(DBException $e) {
		exit($e.' from '.__FILE__.':'.__LINE__);
	}
$sw=Singleton::getInstance('StructureW');	


if(isset($_FILES)){
		//print_r($_FILES);
		//$sw->showloadfiles();
		foreach($_FILES as $key=>$val){	
			//echo $key.'=>'.$val['size'];
			if($val['error']==0 && $val['size']<>0) {
				//echo '-----'.$sw->type_files_load($_FILES,$key,$clas);
				$load_pic=$sw->all_files_load($key,$key.'1',$_FILES,$clas,$sw->type_files_load($_FILES,$key,$clas,'pages.csv'));
				if($load_pic)echo 'Загрузка файла '.$val['name'].' завершена успешно<br>';
					//show::pauza('Загрузка файла '.$val['name'].' завершена успешно','/?blockS&np='.$numpage);
					//echo 'Загрузка файла '.$val['name'].' завершена успешно<br>';
				else show::pauza('Не удалось осуществить загрузку файла'.$val['name'],'/');
			}	
		}
		$page_file='';
	}	
else $page_file='';
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Иницилизация системы</title>
		<?php
		echo '<link rel="stylesheet" type="text/css" href="./images/settingsStyle.css" />';
		echo '<link rel="stylesheet" type="text/css" href="./images/authStyle.css" />';
		echo '<script src="./scripts/capUpdate.js" type="text/javascript"></script>';
		echo '<link rel="shortcut icon" type="image/png" href="images/favicongra.png"/>';
		?>
	</head>
	<body>
		<?php

echo '<info class="hidno">Таблицы созданы <br></info>';
if (isset($_POST['cga']))$desc['cga']=$_POST['cga'];
else $desc['cga']='';
if(isset($_POST['cym'])) $desc['cym']=$_POST['cym'];
else $desc['cym']='';
if(isset($_POST['chice']) ){
	if( $_POST['chice']==='owndomen' ) $desc['own']='Y';
	else $desc['own']='N';
}
else $desc['own']='Y';
if($_POST['ownbd']==='yes')$desc['ownbd']='yes';
else $desc['ownbd']='no';
$user = Singleton::getInstance('User');
$user->check();
//регистрируем 	в таблице Allsites
$id_exist=$user->checkLoginEmail($_POST['adms'], $_POST['eml']);//Администратор системы теперь
if (!$db->initbdF($_SERVER['HTTP_HOST'])) {
	echo '<div class="hidno"> регистрируем...</div>';
	//инициализация и авторизация сайта user
	if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
	if($id_exist==0){
		
		//print_r($_POST);
		if($user->addAdmin($_POST['adms'], $_POST['pass'],$_POST['eml'])){
			$control_summa=$user->regbd($_SERVER['HTTP_HOST'],1,'',12,7,3,8,$desc,$page_file);
			if($control_summa>0) echo '<br>Сайт подключен за номером '.$control_summa.'<br>';		
		}
	}
	else exit('Что-то пошло не так. Возможно вы не подключили хостинг или не уникальные данные Администратора.');
	// инициализация и авторизация таблицы user
	//$user->addAdmin($_POST['adms'], $_POST['pass'], $_POST['eml']);
	
} 
echo '<table><tr><td class="center">';		
echo '<br>Администртор базы :'.$user->getlogin();
echo '<br>DONE<br>';
echo '<form id="first" action="https://'.$_SERVER["HTTP_HOST"].'" method="post">';
echo '<br><input name="site" value="'.$_POST["site"].'" type="hidden">';
echo '<span><input type="submit"  value="ШАГ: 3. Готово!..."/><br><br>';
echo '</form></td></tr></table>';
}

?>
</body></html>