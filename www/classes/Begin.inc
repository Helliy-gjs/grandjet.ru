<?php
@ $control_mode = $_GET['cm'];// режим отладки включен если cm>0 1-контроль страницы 2-контроль пользователя
@ $poisk=$_POST['poisk'];
@ $tid=$_GET['td'];
if (isset($_POST['vend'])) $vend=$_POST['vend'];
else $vend='';
@ $new = $_GET['new'];
if (isset($_GET['hd'])) $hd=$_GET['hd'];
$clas['clas']=array('0'=>'logo','1'=>'container','3'=>'img','2'=>'header_banner','4'=>'button',
'5' => 'menu','6' => 'portfolio','7' => 'ready','8' => 'news',
'9' => 'section','10' => 'footer-sec','11' => 'home','12' => 'item','13' => 'img',
'14' => 'content','15' => 'main_footer','16'=>'main_footer','17' => 'footer','18' => 'wrapper',
'19' => 'footmenu', '20' => 'top_line','21'=>'menuup','22'=>'adm','23'=>'user');
$clas['img']='./images/';
$clas['csv']='./';
$clas['js']='./js/';
$clas['lib']='./libs/';
$clas['css']='./css/';
$clas['font']='./font/';
$clas['react']='./react/';
$clas['vue']='./vue/';
$clas['ang']='./angular/';
$clas['oth']='./other/';
$vendors=array();
foreach($clas as $key=> $val){
	if($key!== 'clas'    && !file_exists($val)){
		mkdir($val);
		if( $key!== 'css'  && $key!== 'js'  && $key!== 'fonts'  && $key!== 'img' ){
			if(!file_exists($val.'/css/'))mkdir($val.'/css/');
			if(!file_exists($val.'/js/'))mkdir($val.'/js/');
			if(!file_exists($val.'/img/'))mkdir($val.'/img/');
			if(!file_exists($val.'/fonts/'))mkdir($val.'/fonts/');
		}
	}
}

$choice_vendors=array();
$spisok=array();
$ff=200; 
//define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('HOST_SCRIPT',     dirname($_SERVER['SCRIPT_FILENAME']));
define('HOST_ROOT',     '/bhome/part2/01/ritondel/'.$_SERVER['HTTP_HOST'].'/www/');
define('HOST_ARCH',     '/bhome/part2/01/ritondel/archive');
//echo HTTP_FOLDER;


//определяем статус пользователя
$user->check();
$uid=$user->getuserid();
$cid=$user->getusercid();
$currbals = $user->getBalans();
if($_SERVER['HTTP_HOST']==='localhost'){
	$_SERVER['HTTP_HOST']='www.grandjetstudio.com';
	$localdomen='localhost';
}
else $localdomen=$db->namecurbd();

if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}

if($user->isGuest()) ini_set(session.use_strict_mode,1);
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
if (!$user->initbdF($_SERVER['HTTP_HOST'])) {
	echo 'сайт не зарегистрован <br>';
	$tabl=Utils::getsitetables($_SERVER['HTTP_HOST'],$db);
//регистрируем 	в таблице allsites
	
}
elseif(isset($Site)) {
	
	if($_SERVER['HTTP_HOST']==='localhost')$Site->domen='localhost/www/'.$Site->domen;
	$tabl=Utils::getsitetables($Site->domen,$db);
	$clas['tabl'] = $tabl;
	$pgExist = $db->getscountab($tabl['pages'],'','c');
	$vendors=$ew->getvendor($tabl['elem']);
	$levelU=$user->getLevelnew();//данный параметр определяет абсолютные права пользователя
	$pathscrypt='tree_menu.js';
	$logo='grandjetstudio';
	$brow=0;
	//определение стартовой стрвницы сайта
	if($pgExist){
		if($Site && ($user->getLevelnew()>4 ||  $user->getscountab('elemap','id','f')==0 )) $startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
		elseif($Site && $user->getLevel()<=4 && $user->getscountab('elemap','id','f')>0) $startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
		elseif(!$Site) exit('Данный сайт '.$_SERVER['HTTP_HOST'].' не авторизован в системе '.$insi[3]);
		else exit('У вас нет права доступа к сайту '.$insi[3]);
	}
	else $startpage = false;	
	include(CLASSES.'/status.inc');
	//проверяем статус пользователя по отношению к системе
	
}	

if(!isset($number_pages)) $number_pages = 0;
if(!$startpage) $numpage = $number_pages + 1;
//echo 'страницa '.$numpage;
//print_r($Site);
//echo ' стартовая '.$startpage;	
if($user->getLevel() < 0 && $startpage ) {
	header('Location: https://'.$_SERVER['HTTP_HOST'].'/auth/');
	exit();
}
else {
	if(isset($_GET['np']))	if($_GET['np']==='' && !isset($_POST['chice']))$_GET['np']=$startpage;
	if (isset($_POST['chice'])) @ $numpage = $_POST['chice'];
	elseif (isset($_GET['np']) && $_GET['np']<>'') @ $numpage = $_GET['np'];
	else $numpage=$startpage;
	//echo ' данная '.$numpage;	
	if(!isset($PageM)) {
		$PageM= new Page($numpage,$tabl,$uid);	
	}
	//print_r(array_splice(explode(';',$PageM->MainAr['imgtext']),0,24));
	if (strstr($PageM->MainAr['idmenu'],'mag')) {
	if ($PageM->MainAr['hreflist']) $typelist='hreflist';
	elseif ($PageM->MainAr['butthref']) $typelist='butthref';
	elseif ($PageM->MainAr['buttimg']) $typelist='buttimg'; 
//print_r($PageM->MainAr);
	if ($PageM->MainAr[$idmenu] === 'mag') {
	$arrmag=$PageM->Page_Composite($numpage,$typelist,explode(';',$PageM->MainAr[$typelist]),$tabl);
	}
	if(isset($arrmag)){
		$PageM->MainAr=$arrmag;
		foreach ($arrmag as $key=>$val)$linkpages[]='';
		}
	}
	
	//для не магических страниц создаем ссылки редактирования данных страницы
		$linkpages=$sw->getPagelinks($numpage);
		if(isset($_POST['confs'])){
			$numcnfs['id'][0]=$_POST['confs'];
			$numcnfs['Maket'][0]='customS'.$_POST['confs'];
		}
		else $numcnfs=Maket::currconfig ('configs','id',0);
		if(is_array($numcnfs))$arrconf['site']=Utils::getConfig($numcnfs['id'][0],'configs');
		else $arrconf['site']=Utils::getConfig($numcnfs,'configs');
		
		if(isset($_POST['confm'])){
			$numcnfm['id'][0]=$_POST['confm'];
			$numcnfm['Maket'][0]='customM'.$_POST['confm'];
		}
		else $numcnfm=Maket::currconfig ('configm','current_ids',$Site->ids);
		if(is_array($numcnfm))$arrconf['maket']=Utils::getConfig($numcnfm['id'][0],'configm');
		else $arrconf['maket']=Utils::getConfig($numcnfm,'configm');
		
		if(isset($_POST['confp'])){ 
			$numcnfp['id'][0]=$_POST['confp'];
			$numcnfp['Maket'][0]='customP'.$_POST['confp'];
		}
		else $numcnfp=Maket::currconfig ('configp','np',$numpage);
		
		if($PageM->MainAr['confp'] != '' && !isset($_POST['confp'])){
			$arrexmpl=explode('|',$PageM->MainAr['confp']);
			
			$i=0;
			$arrfields=$sw->getallfieldtable('configp');
			//print_r($arrfields['field']);
			$arrexname=$arrfields['field'];
			if(strstr($PageM->MainAr['confp'],'|'))$currconfp=explode('|',$PageM->MainAr['confp']);
			else $currconfp[2]=$PageM->MainAr['confp'];
			$arrexmpl2=explode(';',$currconfp[2]);
				
				foreach ($arrexmpl2 as $i=>$val){
					if($i>1 && $i<21)$arrconf['page'][$arrexname[$i]]=intval($val);
					$i++;
				}
		}  
		//print_r($arrconf['curpage']['butt']);
		if(is_array($numcnfp))$arrconf['page']=Utils::getConfig($numcnfp['id'][0],'configp');
		elseif($numcnfp <> 0) $arrconf['page']=Utils::getConfig($numcnfp);
		//print_r($tabl);
		//print_r($PageM->MainAr);
		//if(isset($PageM) && isset($Owner_site) && isset($linkpages) && isset($arrconf['page']))
		$arrmain=Page::readypagearr($PageM->MainAr,$clas,$linkpages,$Owner_site,$arrconf['page'],$tabl);
		
		//print_r($arnum);
		//print_r($arrmain['idmen']);
		//print_r($arrconf['page']);
	}

$rest=$user->read_namparams('setTypesPage');
$arridmen=$rest[1];
if(isset($numpage)) {
	$arrsite=Maket::readysitearr($Site,$numpage,$clas);
	if(isset($arrmain['idmen']))$disp = trim($arrmain['idmen'][0]);
	else $disp='flex';
	
	if(isset($arrmain['typmen']))$distype = $arrmain['typmen'][0];
	else $distype=$rest[1];
}
else{
	$numpage = 1;
	 $disp = $arridmen[$Site->strucs];
}
//режим работы при наличии стартовой страницы
//if($startpage)$PageS= new Page($startpage,$tabl);
//определение номера загружаемой страницы и загрузка нативных данных страницы 
//Далее формируются данные страницы в виде единного массива
//проверка на составную страницу, если да пересчитываем данные страницы по магическому алгоритму 
//определение переменных, значение которых отображается на странице
//Загрузка процедур интернет магазина, при наличии дистрибутива и каталог товаров	
if($ew->view_table($tabl['elem']) && file_exists('./book')){	
	if (chdir('book')) {
		if (fopen('book_sc_fns.php','r')) require ('book_sc_fns.php');
		chdir('../');
}
}
$arrmain['tab']=Utils::getsitetables($Site->domen);
// Объявить переменные сеанса
  if(!isset($_SESSION['items'])) $_SESSION['items'] = '0';
  if(!isset($_SESSION['total_price'])) $_SESSION['total_price'] = '0.00'; 
//print_r($arrmain['link']['loz']);
//print_r($arrmain['tab']);

if(isset($arrmain['idmen'][0]))$pgTypeExist =intval($db->getscountab($Site->pages,'numpage', 'f','idmenu',$arrmain['idmen'][0]));
else $pgTypeExist = 0;
//var_dump($pgTypeExist);
//die();
?>