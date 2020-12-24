<?php 
//Загрузочная страница сайта
if(isset($_GET['error']))ini_set('display_errors',$_GET['error']);
else ini_set('display_errors',0);
error_reporting(E_ALL & ~E_NOTICE);
global $pathToClasses,$glsr,$pathheader,$IsLocal;
$IsLocal = false;
//Загрузка внутрених библиотек
//$pathToClasses = '/classes/';
//$pathheader='.';
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
define('CLASSES', $pathheader.$pathToClasses);
include_once(CLASSES.'autoload.inc');
$db=Utils::loadbdsite($_SERVER['HTTP_HOST']);
//print_r($_GET);
include_once('functions.php');
if(strstr(trim($_SERVER['REQUEST_URI'],'/'),'api') ){	
	include(CLASSES.'allapi.inc');
}
$glsr = glossary();
//установка режима первичной загрузки
$cont='Yes';
// Определение констант и глобальных переменных
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('HOST_SYSTEM','/bhome/part2/01/ritondel/');
define('HOST_DIST',    HOST_SYSTEM.'distributive');
define('HOST_ARCH',    HOST_SYSTEM.'archive');
define('HOST_MYDOMEN',     HOST_SYSTEM.$_SERVER['HTTP_HOST'].'/www/');
define('HOST_MY',     HOST_SYSTEM.$_SERVER['HTTP_HOST']);
define('HOST_ROOT',     HOST_SYSTEM.$_SERVER['HTTP_HOST'].'/www/');
global $pathToClasses,$pathheader, $spisok,$vend, $tabl, $tablepages, $tablenews, $numrecbd,$loz,$hh;
global $vendors,$PageM,$namenews,$novost,$clas,$hd,$type_menu;
$clas=array();
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
//Подключение к БД 

if(!$db){
	try {
			//echo 'construct0';
			$db = Singleton::getInstanceinit('DB',1);
			$insi=$db->init_data;
			if($_SERVER['HTTP_HOST']!='deltar.ru')$Site0=$db->initbd($_SERVER['HTTP_HOST'],$db);
			} catch(DBException $e) {
			exit($e);
			}
		
		//print_r($insi);	
		//echo '<br>';print_r($Site0);
		if(isset($Site0)){
			$bdsite=array(0=>$Site0->bd,1=>$Site0->host,2=>$Site0->logad,3=>$Site0->passwad,4=>$Site0->port);
		//print_r($bdsite);
		if(is_object($Site0) && $Site0->bd !=  $insi[3] ){
		echo '<info class="hidno">Сайт '.$_SERVER['HTTP_HOST'].' зарегистрирован в базе '.$bdsite[0].'</info>';
		//unset($db);
		//$bdname=explode('.',$_POST['owndomen']);
		$nameBD=$bdsite[0];
		$query = "CREATE DATABASE IF NOT EXISTS $nameBD";
		if($bdsite[0]<>'') $db->query($query);
		unset($db);
		try {
			//echo 'construct0';
			$db = Singleton::getInstancepar('DB',$bdsite[1],$bdsite[2],$bdsite[3],$bdsite[0],$bdsite[4]);
			$insi=$db->init_data;
			echo '<info class="hidno">Подключение к базе '.$bdsite[0].'</info>';//$Site=$db->initbd($_SERVER['HTTP_HOST'],$db);
			} catch(DBException $e) {
			exit($e);
			}
		}	
		else 'Сайт '.$_SERVER['HTTP_HOST'].' зарегистрирован не в базе '.$insi[3];
	}
	else {
		
		$query = "CREATE TABLE IF NOT EXISTS `allsites` (
	  `keyid` int(10) NOT NULL auto_increment,
	  `ids` int(10) NOT NULL default '1',
	  `uid` int(6) NOT NULL,
	  `domen` varchar(50) NOT NULL,
	  `nmpage` varchar(20) NOT NULL,
	  `types` int(10) NOT NULL,
	  `strucs` int(10) NOT NULL,
	  `appoint` int(10) NOT NULL,
	  `css` varchar(50) NOT NULL,
	  `script` varchar(50) NOT NULL,
	  `images` varchar(100) NOT NULL,
	  `passwad` varchar(100) NOT NULL,
	  `logad` varchar(50) NOT NULL,
	  `bd` varchar(200) NOT NULL,
	  `host` varchar(100) NOT NULL,
	  `port` int(6) NOT NULL,
	  `pages` varchar(25) NOT NULL,
	  `news` varchar(25) NOT NULL,
	  `element` varchar(25) NOT NULL,
	  `structure` varchar(25) NOT NULL,
	  `desc_site` varchar(250) NOT NULL,
	  PRIMARY KEY  (`keyid`),
	  UNIQUE KEY `ids` (`ids`),
	  UNIQUE KEY `domen` (`domen`)
		) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";
		$db->query($query);
	}	
}	
//else 'база данных подключена';
if(isset($_POST['chice'])){
	if( $_POST['chice']=='owndomen'){
		//Создание базы данных и таблицы allsites
	if(isset($_POST['createdatabase']) && isset($_POST['owndomen']) && $_POST['createdatabase']=='yes'){
		
			$bdname=explode('.',$_POST['owndomen']);
			$nameBD=$bdname[0].'_'.$bdname[1];
			$query = "CREATE DATABASE IF NOT EXISTS $nameBD";
			if($bdname[1]<>'') $db->query($query);
		}
	}
}
//print_r($db->init_data);

$query = "CREATE TABLE IF NOT EXISTS `allsites` (
	  `keyid` int(10) NOT NULL auto_increment,
	  `ids` int(10) NOT NULL default '1',
	  `uid` int(6) NOT NULL,
	  `domen` varchar(50) NOT NULL,
	  `nmpage` varchar(20) NOT NULL,
	  `types` int(10) NOT NULL,
	  `strucs` int(10) NOT NULL,
	  `appoint` int(10) NOT NULL,
	  `css` varchar(50) NOT NULL,
	  `script` varchar(50) NOT NULL,
	  `images` varchar(100) NOT NULL,
	  `passwad` varchar(100) NOT NULL,
	  `logad` varchar(50) NOT NULL,
	  `bd` varchar(200) NOT NULL,
	  `host` varchar(100) NOT NULL,
	  `port` int(6) NOT NULL,
	  `pages` varchar(25) NOT NULL,
	  `news` varchar(25) NOT NULL,
	  `element` varchar(25) NOT NULL,
	  `structure` varchar(25) NOT NULL,
	  `desc_site` varchar(250) NOT NULL,
	  PRIMARY KEY  (`keyid`),
	  UNIQUE KEY `ids` (`ids`),
	  UNIQUE KEY `domen` (`domen`)
		) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";
$db->query($query);
$query='SELECT * FROM `allsites`';
$res=$db->query($query);
if($res)$ok2=$db->getscountab('allsites','ids', 'f');
else $ok2=0;

//Инициализация базы данных из скрипта
if(isset($_POST['tarif']))$str_get='uid='.$_POST['uid'].'&owndomen='.$_POST['owndomen'].'&adms='.$_POST['adms'].'&eml='.$_POST['eml'].'&prot='.$_POST['prot'].'&site='.$_POST['site'].'&tarif='.$_POST['tarif'].'&strucs='.$_POST['strucs'].'&ippt='.$_POST['ippt'].'&typs='.$_POST['typs'];
else $str_get='';
if (isset($_POST['go']) && isset($_POST['site']) && $ok2!=0 ) {
	
	echo 'регистрация сайта в новой базе';	
	//Запуск режима иницилизации пустой таблицы Allsites базы данных
	//иницилизация системы: создание таблиц базы, их первичное заполнение 
	header('Location: http://'.$_SERVER['HTTP_HOST'].'?inition=registration&'.$str_get);
	exit('В системе нет зарегистрованых сайтов. Выполните иницилизацию.');
	
	}
elseif(isset($_GET['site']) && $ok2 == 0) {
	$query = array();
	include('CREATESITE.php');	
	try {
		foreach($query as $val)
			$db->query($val);
	} catch(DBException $e) {
		exit($e.' from '.__FILE__.':'.__LINE__);
	}
	if($_GET['site'] >0)$strucs = $_GET['site'];
	else $strucs = 0;
	$typesite = 1;
	$user = Singleton::getInstance('User');
	$desc = array('own' =>'','ownbd' =>'Y','cym'=>'','cga' =>'');
	if(isset($_POST['adms']) && isset($_POST['pass']) && isset($_POST['passw'])&& isset($_POST['eml'])){
		$login = $_POST['adms'];
		$passw = $_POST['passw'];
		$pass = $_POST['pass'];
		$email = $_POST['eml'];
	}
	else {
		$login = 'admin';
		$pass = 'veravolf';
		$passw = 'veravolf';
		$email = 'ruslan@grandjet.ru';
	}
	$_POST['uid']= 1;
	$_POST['site']=1;
	if($user->addAdmin($login,$pass,$email) && $pass == $passw){
			$control_summa=$user->regbd($_SERVER['HTTP_HOST'],1,'',$typesite,$strucs);
			if($control_summa>0) echo '<br>Сайт подключен за номером '.$control_summa.'<br>';
			
		}
}
elseif(!isset($_GET['inition']) && $ok2==0){
	echo 'иницилизация системы' ;
	header('Location: http://'.$_SERVER['HTTP_HOST'].'?inition=inition&'.$str_get);
	exit('В системе нет зарегистрованых сайтов. Выполните иницилизацию.');
}
//запуск режима пользователя 	
if(!isset($_GET['mysites']) && !isset($_GET['inition'])  && $ok2>0) include_once('loader2019.php');
elseif($_SERVER['HTTP_HOST'] !=  'deltar.ru')include_once('registrator.php');
else  include_once('setup.php');

//if(!isset($_GET['mysites']) && !isset($_GET['inition'])  && $ok2>0) include_once('loader2019.php');
///else  include_once('registrator.php');
echo '</body></html>';
?>	