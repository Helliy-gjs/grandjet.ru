<?php
@ $control_mode = $_GET['cm'];// режим отладки включен если cm>0 1-контроль страницы 2-контроль пользователя
@ $poisk=$_POST['poisk'];
@ $tid=$_GET['td'];
if (isset($_POST['vend'])) $vend=$_POST['vend'];
else $vend='';
@ $new = $_GET['new'];
if (isset($_GET['hd'])) $hd=$_GET['hd'];
$clas['clas']=array('0'=>'logo','1'=>'container','3'=>'img','2'=>'main-banner','4'=>'button',
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
$vendors=array();

$choice_vendors=array();
$spisok=array();
$ff=200; 
define('HOST_SCRIPT',     dirname($_SERVER['SCRIPT_FILENAME']));
define('HOST_ROOT',     '/bhome/part2/01/ritondel/'.$_SERVER['HTTP_HOST'].'/www/');
//define('HOST_DIST',     '/bhome/part2/01/ritondel/distributive');
define('HOST_ARCH',     '/bhome/part2/01/ritondel/archive');
//define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
//define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));
//echo HOST_SCRIPT; 
//include($pathheader.$pathToClasses.'autoload.inc');
$ew = Singleton::getInstance('elementsW');
$sw = Singleton::getInstance('StructureW');
$user = Singleton::getInstance('User');
if($_SERVER['HTTP_HOST']==='localhost'){
	$_SERVER['HTTP_HOST']='www.grandjetstudio.com';
	$localdomen='localhost';
}
else $localdomen=$db->namecurbd();

if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}

/*try {
	$db = Singleton::getInstance('DB');
} catch(DBException $e) {
	exit($e);
}
*/
if($user->isGuest()) ini_set(session.use_strict_mode,1);

if($localdomen!='localhost'){
	$user->check();
	$uid=$user->getuserid();
	$cid=$user->getusercid();
}
else {
	$uid=1;
	$cid=1;
}
//echo $uid;
$Site=$user->initbdF($_SERVER['HTTP_HOST']);

if($Site && ($user->getLevelnew()>4 || $user->getLevelnew()<=0)) $startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
elseif($Site && $user->getLevelnew()<=4 && $user->getscountab('elemap','','c')>0) $startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$Site->domen,$Site->pages);
//elseif(file_exists('start.php'))header('Location: http://'.$_SERVER['HTTP_HOST'].'/start.php');
elseif(!$Site) exit('Данный сайт '.$_SERVER['HTTP_HOST'].' не авторизован в системе '.$insi[3]);
else exit('У вас нет права доступа к сайту '.$insi[3]);
//$db=Singleton::getInstance('DB');
$tabl=Utils::getsitetables($Site->domen,$db);

$vendors=$ew->getvendor($tabl['elem']);
if($user->getLevel() < 0) {
	//header('Location: http://'.$_SERVER['HTTP_HOST'].'/auth/');
	//header('Location: http://localhost/grandjetstudio.com/www/auth/');
	}
if($localdomen!='localhost')$levelU=$user->getLevelnew();
else $levelU=6;//данный параметр определяет абсолютные права пользователя
//-1=вход закрыт, 0-статус гостя, 1-зарегистрованый пользователь, не клиент, 2-клиент, 3-открытый договор с положительным балансом, 4-статус специалиста,5-администратор сайта, 6-администратор системы

$logo='grandjetstudio';
//echo $_SERVER['HTTP_HOST'];
//проверяем зарегистрован ли ресурс в таблице Allsites
if (!$user->initbdF($_SERVER['HTTP_HOST'])) {
	echo 'сайт не зарегистрован <br>';
//регистрируем 	в таблице Allsites
	
}
else {
	//проверяем статус пользователя по отношению к системе
	if ($uid <> 0) {
		$mode_edit=$user->areyouAdmin($_SERVER['HTTP_HOST'],$uid);
		$mode_mang=$user->areyouManager($_SERVER['HTTP_HOST'],$uid);
	}
	else {
		$mode_edit=false;
		$mode_mang=false;
	}

if($levelU==6)$mode_edit=true;
if ($mode_edit && $levelU>3 ) {
	if (isset($_GET['par'])) $npar =$_GET['par'];
}
//загрузка содержимого корзины интернет магазина
if (isset($_GET['new']) || isset($_POST['save'])) include($pathheader.$pathToClasses.'show_cart.inc');

//инициализация сайта
//1- если вы автор сайта только $_SERVER['HTTP_HOST'] то вы заходите на него
//2-если вы не автор $_SERVER['HTTP_HOST'] и у вас нет своих сайтов то вы заходите на него

//print_r($Site);
//проверяем есть ли у пользователя свои сайты в том случае если пользователь не автор сайта
//if($user->getuserid()<>$Site->uid)$test_id=$user->your_test_sites($uid);
//else {
	//echo 'Вы автор сайта'; 
	//$test_id=null;
//}
//$user->getlookforfields($_SERVER['HTTP_HOST'],$uid,'Allsites');
//if(is_array($test_id))
//if($test_id<>null) $Site=$user->initbdF($test_id->domen);
//else $Site=$user->initbdF($_SERVER['HTTP_HOST']);
$sid=$Site->ids;
//print_r($Site->domen);
//print_r($test_id->domen);
//print_r($Site);
//проверяем статус пользователя по отношению к сайту, параметр разрешает доступ к редактированию данного сайта

//if($mode_edit)echo 'Режим администрирования';
//else echo 'Режим  пользователя';
if(!$mode_mang && !$mode_edit ) $mode_work=true;//&& !$user->isGuest()
else $mode_work=false;
if(!isset($type_page)) $type_page=0;
define('MAIN_PAGE_SITE',$Site->nmpage);
define('MAIN_NEWS', $Site->news);
define('MAIN_DOMEN', $Site->domen);
//$DESCSITES=explode('|',$Site->desc_site);
$mass_RA=$user->right_access($Site->desc_site);
$code_GGLA=$mass_RA['GA'];
$code_YAXM=$mass_RA['YM'];
if($code_GGLA<>'') $active_GGLA=true;
else $active_GGLA=false;
if($code_YAXM<>'')$active_YAXM=true;
else $active_YAXM=false;
$prot=$mass_RA['PR'];
if($localdomen==='localhost'){
	$prot='http://';
	$localpath=$prot.$localpath;
}
else $localpath='';
//Проверка режима пользователя
/*if ($uid <> 0) {
	$mode_edit=$user->areyouAdmin($Site->domen,$uid);
	$mode_mang=$user->areyouManager($Site->domen,$uid);
	}
else {
	$mode_edit=false;
	$mode_mang=false;
} */
//$mode_edit=false;
if(!$mode_mang && !$mode_edit && !$user->isGuest()) $mode_work=true;
else $mode_work=false;	
//обновление сайта 
//$update=false;
//if (isset($DESCSITES[0])) $code_GGLA=$DESCSITES[0];
//if (isset($DESCSITES[1])) $code_YAXM=$DESCSITES[1];
$picsglb=explode(';',$Site->images);
if(isset($picsglb[1]))$Logopic=$picsglb[1];
else $Logopic='';
if(isset($picsglb[0]))$Bannrpic=$picsglb[0];
else $Bannrpic='';
$clas['imgext']=$picsglb[2];
//echo $Bannrpic;

//print_r($tabl);
//Print_r($startpage);
if (!$startpage) exit('отсутсвует стартовая страница');
else $PageS= new Page($startpage,$tabl);

//если клиент установлен с уровнем положительного доступа, с правами каких-либо изменений
if(isset($_GET['np']))	if($_GET['np']==='' && !$_POST['chice'])$_GET['np']=$starpage;

if (isset($_POST['chice'])) @ $numpage = $_POST['chice'];
elseif (isset($_GET['np']) && $_GET['np']<>'') @ $numpage = $_GET['np'];
//elseif(isset($adminpage)) @ $numpage=$adminpage;
else $numpage=$startpage;
//if(!$sw->isthatsite($Site->domen,$numpage,'elemap'))$numpage=$startpage;
if(isset($numpage)) {
	$PageM= new Page($numpage,$tabl,$mode_edit);	
	
}
//$editpage=$user->getlookforfields('all','edit_gra_deltar.ru',$Site->pages);
//$PageE= new Page($editpage,$tabl);
if(!$mode_work){
	//$adminpage=$user->getlookforfields('all','adm_gra_deltar.ru',$Site->pages);
	//$PageA= new Page($adminpage,$tabl);
	//Система загрузки информации на сайт
	//Проверяем наличие страниц на сайте
	$d='SELECT * FROM `'.$Site->pages.'` WHERE `site`=^Ns;';
	$res=$db->query($d,$Site->domen);
	$lpg=$user->getscountab($Site->pages,'numpage', 'f');
	//Определяем состояние таблиц и сохраняем количество записей
	$number_pages=$user->getscountab($Site->pages,'numpage', 'f');//pages
	$number_news=$user->getscountab($Site->news,'idnews', 'c');//news
	$number_nampars=$user->getscountab('namparams','codparams', 'c');//namparams
	//блок обработки внешних параметров для страницы
	if (isset($_GET['tab'])) {
		if (isset($_GET['field'])) $field=isset($_GET['field']);	
		if($_GET['tab']<> 'customers' &&   $_GET['tab']<> 'news' &&   $_GET['tab']<> 'namparams' &&   $_GET['tab']<> 'Allsites') $field='id';
		elseif($_GET['tab']=='namparams')$field='codparams';
		elseif($_GET['tab']=='Allsites')$field='ids';
		//elseif($_GET['tab']=='forms')$field='idform';
		if ($field<>'')	$number_value_tab=$user->getscountab($_GET['tab'],$field, 'f');
	}
	//если у пользователя достаточнор прав и база страниц пуста выполняем процедуру загрузки страниц на сайт
	if (!$res && $user->getscountab($Site->pages,'numpage', 'f') == 0 && $mode_edit) { 
	echo 'на сайте нет страниц ';	
	$nn[0]=array('idauthor'=>$uid,'name'=>' Иницилизация страниц '.$Site->domen,'newstext'=>'Загрузка страниц на сайт '.$Site->domen.' выполнена. ','idnews'=>($user->getscountab($Site->news,'', 'c')+1),'vendor'=>$Site->domen,'group'=>'inition','imgnews'=>'faviconjpg.jpg','codgjsnews'=>'','hrefnew'=>$Site->domen.'/'.$Site->nmpage,'numpagat'=>$startpage,'site'=>$Site->domen);
	Utils::prepare_pages($uid,$Site->domen,$lpg,$nn,$db);	
	}
	//Далее загружаются данные в служебные таблицы, при наличии одноименных файлов 
	//Если найден соответсвующий файл найден, то информация загружается,  файл удаляется. Информация дописывается в базу данных 
	
	foreach ($tabl as $val){
		$lnf=$user->getscountab($val,'', 'c');
		$file='./'.$val.'.csv';
		$table=$val;
		if(isset($_GET['addfile'])) $addfile=$file;
		else $addfile='';
		if (file_exists($file)) {
			$F=fopen($file,"r");
				if ($F) {
				fclose($F);
				if(Utils::add_tabs_file($Site->domen,$user,$table,$db,$uid,20000,$addfile))
				echo '<br>успешная загрузка данных...'.$file;	
				
				}
				elseif($lnf==0 && $levelU>5) echo '<br> файл не найден - '.$file;
		}
	}
	$lna=$user->getscountab('namparams','codparams', 'f');
	//echo 'lna '.$lna.'<br>';
	$file='./nampars.csv';
	if (file_exists($file)) {
		$F=fopen($file,"r");
		if ($F){
			fclose($F);	
			if(Utils::add_tabs_file($Site->domen,$user,'namparams',$db,$uid,10000,$file))
			echo '<br>успешная загрузка данных...'.$file;	
			
		}
		else echo '<br> файл не найден - '.$file;
	}
	$lnp=$user->getscountab('params','GJScode', 'f');
	//echo 'lnp '.$lnp.'<br>';
	$file='./params.csv';
	if (file_exists($file) && $lpn==0) {
		$F=fopen($file,"r");
			if ($F){
				fclose($F);		
				if(Utils::add_tabs_file($Site->domen,$user,'params',$db,$uid,10000))echo '<br>успешная загрузка данных... '.$file;	
			}
			else echo '<br> файл не найден -  '.$file;	
	}
	unset($lnp);unset($lna);

	$pathpics='';
}	

//elseif ($Site->ids <> $sid) $user->logout(); //exit('Такого пользователя на сайте '.$Site->domen.'  нет');		

//идентификация браузера, пользователя и параметров
$brow=0;

$pathscrypt='tree_menu.js';
$tabl['elemap']='elemap';
$tabl['mapsites']='mapsites';
//В рабочем режиме сайта все начинается с определения страницы входа
//echo $test_id->domen;

//если есть доступ	считываем параметры клиента для вывода на сайт
/*if($mode_work)show::infosh( 'Work '.$numpage.'<br>');
	elseif ($mode_edit)show::infosh( 'Edit '.$numpage.'<br>');
	elseif ($mode_mang)show::infosh( 'Manager '.$numpage.'<br>');
	else show::infosh( 'User '.$numpage.'<br>');*/
$uid=1;	
if($levelU>=0){	
$Owner_site=$user->idUserF($Site->uid);	
$Owner_site->ids=$Site->ids;
$Owner_site->start=$startpage;

//$Owner_site->level=$user->level;
//$Owner_site->telmain=idUser($uid)->telmain;
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
//echo $levelU;print_r($firm);

if($mode_edit) $Owner_site->admin='Admin';
else $Owner_site->admin='';
//show::infosh($Owner_site);
}


/*else {
	$numpage=$startpage;
	$PageM= new Page($startpage,$tabl);
	echo 3;
}*/


//$numpage=$PageM->MainAr['numpage'];
$idnews=$PageM->MainAr['idnews'];
$what=$sw->isthatsite($PageM->MainAr['site'], $numpage, $Site->pages);

if( !$what) exit('Домен '.$domen.' не зарегистрирован');
//elseif($test_id==null && $what->site<>$_SERVER['HTTP_HOST']) exit('Домен '.$_SERVER['HTTP_HOST'].' не зарегистрирован');
if ($numpage == 7) $novost=1;
//выбор таблицы элементов по методу GET
if (isset($_GET['tab'])) @ $tab=$_GET['tab'];
else @ $tab="";

switch ($tab){
		case 'e' :
		{
		$tabl['elem'] = 'elements';
		$cat_elem='Учитываются только товары со склада и транзита';
		$tb='Каталог (склад-транзит)';
		break;
		} 
		case 'a' :
		{
		$tabl['elem'] = 'elemarch';
		$cat_elem='Учитываются товары под заказ (все товары)';
		$tb='Каталог (все товары)';
		break;
		}
		case 'c' :
		{
		$tabl['elem']= 'elemcat';
		$cat_elem='Каталоги производителей';
		break;
		}
		case 's' :
		{
		$tabl['elem'] = 'elemspec';
		$cat_elem='Учитываются только спецпредложения';
		$tb='Каталог (спецпредложения)';
		break;
		}
		default :
		{
		if (isset($Site)) $tabl['elem']=$Site->element;
		else $tabl['elem'] = 'elements';
		$cat_elem='Учитываются товары под заказ (все товары)';
		$tb='Каталог (все товары)';
		break;
		}
}
if ($Site->element === '') $tb='';
//иницилизация массива производителей
if (!$vend=='') $choice_vendors[]=$vend;
//Далее формируются данные страницы в виде единного массива
//проверка на составную страницу, если да пересчитываем данные страницы по магическому алгоритму 
if (strstr($PageM->MainAr['idmenu'],'mag')) {
if ($PageM->MainAr['hreflist']) $typelist='hreflist';
elseif ($PageM->MainAr['butthref']) $typelist='butthref';
elseif ($PageM->MainAr['buttimg']) $typelist='buttimg'; 
//echo $numpage.'--'.$typelist.'  '.$PageM->MainAr['hreflist'].'<br>';

if ($PageM->MainAr[$typelist]) {
	$arrmag=$PageM->Page_Composite($numpage,$typelist,explode(';',$PageM->MainAr[$typelist]),$tabl);
}
if(isset($arrmag)){
	$PageM->MainAr=$arrmag;
	foreach ($arrmag as $key=>$val)$linkpages[]='';
	}
}
else {
	//для не магических страниц создаем ссылки редактирования данных страницы
	if($mode_edit)$linkpages=$sw->getPagelinks($numpage);
	else foreach($PageM->MainAr as $val)$linkpages[]='';
	//$linkadmpage=$sw->getPagelinks($numpage);
}
//определение переменных, значение которых отображается на странице
//print_r($Owner_site);
//print_r($linkpages);
$arrsite=Maket::readysitearr($Site->ids,$tabl,$Site,$numpage,$uid,$clas);
$arrmain=Page::readypagearr($PageM->MainAr,$clas,$linkpages,$Owner_site);
//if(isset($PageA->MainAr))$arradmin=Page::readypagearr($PageA->MainAr,$clas,$linkpages,$Owner_site);
//print_r($arrmain['cont']);
$arrmain['tab']=$tabl;
$arrmain['user']=array($uid,$user->getlevelnew(),$user->getLogin(),$user->getEmail());
//print_r($Owner_site);
$arrmain['hosting']=$Owner_site->hosting;
$arrmain['social']=$Owner_site->social;
//print_r($arrmain['social']);
//print_r($arrmain['user']);
//print_r($linkpages);
//$list=Page::readypagelist($PageM->MainAr,$clas,$linkpages);
//print_r($arrmain['listhref']);
//Загрузка процедур интернет магазина, при наличии дистрибутива и каталог товаров	
if($ew->view_table($tabl['elem'])){	
	if (chdir('book')) {
		if (fopen('book_sc_fns.php','r')) require ('book_sc_fns.php');
		chdir('../');
}
}


//var_dump($img_log);
//session_start();
if($user->isGuest()) ini_set(session.use_strict_mode,1);
// Объявить переменные сеанса
  if(!isset($_SESSION['items'])) $_SESSION['items'] = '0';
  if(!isset($_SESSION['total_price'])) $_SESSION['total_price'] = '0.00'; 
  
}
	//проверка режима ремонта
	if(isset($control_mode)){
		echo '<div class="info">';
		include($pathheader.$pathToClasses.'repaire.inc');
		echo '</div>';
	}

?>