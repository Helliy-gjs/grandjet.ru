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
if(getcwd() === '/'){
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
}
$choice_vendors=array();
$spisok=array();
$ff=200; 
//define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
	

//echo $type_access;

if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
if (!$db->initbdF($_SERVER['HTTP_HOST'])) {
	echo 'сайт не зарегистрован <br>';
//регистрируем 	в таблице allsites
	
}
else {
	if(!isset($ew))$ew = Singleton::getInstance('elementsW');
	if(!isset($sw))$sw = Singleton::getInstance('StructureW');
	if(!isset($user))$user = Singleton::getInstance('User');
	if(!isset($Site)) $Site=$user->initbdF($_SERVER['HTTP_HOST']);
	if($_SERVER['HTTP_HOST']==='localhost')$Site->domen='localhost/www/'.$Site->domen;
	$tabl=Utils::getsitetables($Site->domen,$db);
	$clas['tabl'] = $tabl;
	$pgExist = $db->getscountab($tabl['pages'],'','c');
	$vendors=$ew->getvendor($tabl['elem']);
	$levelU=$user->getLevelnew();//данный параметр определяет абсолютные права пользователя
	$pathscrypt='tree_menu.js';
	$logo='grandjetstudio';
	$brow=0;
	if($Site && ($user->getLevelnew()>4 ||  $user->getscountab('elemap','id','f')==0 )) $startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
	elseif($Site && $user->getLevel()<=4 && $user->getscountab('elemap','id','f')>0) $startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
	elseif(!$Site) exit('Данный сайт '.$_SERVER['HTTP_HOST'].' не авторизован в системе '.$insi[3]);
	else exit('У вас нет права доступа к сайту '.$insi[3]);
	if(isset($_GET['nostart'])) unset($startpage);
	//проверяем статус пользователя по отношению к системе
	include($pathheader.$pathToClasses.'status.inc');
	//if($user->isGuest()) ini_set(session.use_strict_mode,1);
}		
//if($user->getLevelnew() ==  0 && !$startpage) {
	//echo '<h3>Вы вышли <a href="./auth/"> Войти </a></h3>';
	//header('Location: https://'.$_SERVER['HTTP_HOST'].'/auth/');
	//exit();
//}
//определение стартовой стрвницы сайта

$arrsite=Maket::readysitearr($Site,$numpage,$clas);
if(isset($arrmain['idmen']))$disp = trim($arrmain['idmen'][0]);
else $disp=$Site->disp;
$rest=$user->read_namparams('setTypesPage');
$arridmen=$rest[1];
if(isset($arrmain['typmen']))$distype = $arrmain['typmen'];
else $distype=$rest[1];
//режим работы при отсутствии стартовой страницы

if(!isset($startpage)){
	echo '<h3><a href="./auth/"> Войти </a></h3>';
	//$allpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_all',$Site->pages);
	//$numpage = $allpage;
	//$PageM= new Page($numpage,$tabl,$uid);
	if(isset($_POST['confp']))$conf=$_POST['confp'];
	else $conf = 1;
	$arrconf['page']=Utils::getConfig($conf);
	include($pathheader.$pathToClasses.'fish.inc');
	//debug($contmak);
	if(isset($contmak))include($pathheader.$pathToClasses.'start.inc');
	$arrmain=$contmak;
	$numpage = 1;
	$startpage = $numpage;
	//exit('------------------------ start pages absent');
	//$user-> stringusermen('','',0,$Site);
	
}
else {
	if(isset($_GET['np']))	if($_GET['np']==='' && !isset($_POST['chice']))$_GET['np']=$startpage;
	
	if (isset($_POST['chice'])) @ $numpage = $_POST['chice'];
	elseif (isset($_GET['np']) && $_GET['np']<>'') @ $numpage = $_GET['np'];
	else $numpage=$startpage;
	//echo $numpage;
	if(!isset($PageM)) {
		$PageM= new Page($numpage,$tabl,$uid);	
	}
	//print_r(array_splice(explode(';',$PageM->MainAr['imgtext']),0,24));
	if (strstr($PageM->MainAr['idmenu'],'mag')) {
	if ($PageM->MainAr['hreflist']) $typelist='hreflist';
	elseif ($PageM->MainAr['butthref']) $typelist='butthref';
	elseif ($PageM->MainAr['buttimg']) $typelist='buttimg'; 

	if ($PageM->MainAr[$idmenu] === 'mag') {
	$arrmag=$PageM->Page_Composite($numpage,$typelist,explode(';',$PageM->MainAr[$typelist]),$tabl);
	}
	if(isset($arrmag)){
		$PageM->MainAr=$arrmag;
		foreach ($arrmag as $key=>$val)$linkpages[]='';
		}
	}
	else {
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
		//print_r($arrconf);
		
		$arrmain=Page::readypagearr($PageM->MainAr,$clas,$linkpages,$Owner_site,$arrconf['page'],$tabl);
		$arrmain['photoProf'] = $photoProf;
		//debug($arrmain['photoProf']);
	}

}

//режим работы при наличии стартовой страницы
//if($startpage)$PageS= new Page($startpage,$tabl);


//определение номера загружаемой страницы и загрузка нативных данных страницы 






//Далее формируются данные страницы в виде единного массива
//проверка на составную страницу, если да пересчитываем данные страницы по магическому алгоритму 
//определение переменных, значение которых отображается на странице
if(isset($control_mode) && $mode_edit){
	echo '<div class="info">';
	include($pathheader.$pathToClasses.'repaire.inc');
	echo '</div>';
}


//Загрузка процедур интернет магазина, при наличии дистрибутива и каталог товаров	
if($ew->view_table($tabl['elem']) && file_exists('./book')){	
	if (chdir('book')) {
		if (fopen('book_sc_fns.php','r')) require ('book_sc_fns.php');
		chdir('../');
}
// Объявить переменные сеанса
	  if(!isset($_SESSION['items'])) $_SESSION['items'] = '0';
	  if(!isset($_SESSION['total_price'])) $_SESSION['total_price'] = '0.00'; 
	  $isShop=true;
}
else $isShop=false;
$isShop=true;

//if($mode_edit)print_r($arrmain);
//debug($arrmain);


?>