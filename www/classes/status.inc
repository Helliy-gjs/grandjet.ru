<?php
if(!isset($mass_RA)){
	$mass_RA=$user->right_access($Site->desc_site);
//debug($mass_RA);
	$code_GGLA=$mass_RA['GA'];
	$code_YAXM=$mass_RA['YM'];
	if($code_GGLA<>'' && $mass_RA['metr']) $active_GGLA=true;
	else $active_GGLA=false;
	if($code_YAXM<>'' && $mass_RA['metr'])$active_YAXM=true;
	else $active_YAXM=false;
	$prot=$mass_RA['PR'];
	if(isset($mass_RA['access']))$type_access = $mass_RA['access'];
	else $type_access = 'global';
}	
//определяем статус пользователя
$user->check();
$uid=$user->getuserid();
$cid=$user->getusercid();
$currbals = $user->getBalans();
//echo $currbals;
//echo $user->getLevel();
// регулируем права доступа с учето финансового баланса
if(isset($uid)){
	if($currbals >= 1000 && $user->getLevel() == 2)$user->addClientRights($uid);
	elseif($currbals < 1000 && $user->getLevel() == 4)$user->delManageRights($uid);
}	
//Загрузка файлов csv
if(isset($_GET['load'])) {
    //echo 'default load data from files';
    $pathheader = '.';
    foreach ($tabl as $val){
            $lnf=$user->getscountab($val,'', 'c');
            $file=$pathheader.'/'.$val.'.csv';
            $table=$val;
            if(isset($_GET['addfile'])) {
                $addfile=$file;
               // echo '<br>ready to load data from add '.$file;
            }
            else $addfile='';
            if (file_exists($file)) {
                //echo '<br>Data loading from '.$file;
                $F=fopen($file,"r");
                    if ($F) {
                    fclose($F);
                    Utils::add_tabs_file($Site->domen,$user,$table,$db,$uid,20000,$addfile);
                    //echo '<br>успешная загрузка данных...'.$file;

                   // }
                    //else  echo '<br> файл не найден - '.$file;
           // }
            ///else  echo '<br> файл не найден - '.$file;
			}
		}
	}
}
$number_pages=$user->getscountab($Site->pages,'numpage', 'f');
$number_pub_pages = $user->getscountab('elemap','codeGJS', 'f');
$number_news=$user->getscountab($Site->news,'idnews', 'c');//news
$number_nampars=$user->getscountab('namparams','codparams', 'c');//namparams	
$number_allmakets =  $user->getscountab('allmakets','', 'c');//maket	
//загрузка страниц если страниц нет в базе из файла или поумолчанию
if( $user->getscountab($Site->pages,'site', 't')==0 && $number_pages != 0) {	
	
	$d='SELECT * FROM `'.$Site->pages.'` WHERE `site`=^Ns;';
	$res=$db->query($d,$Site->domen);
	$lpg=$user->getscountab($Site->pages,'numpage', 'f');
	$nn[0]=array('idauthor'=>$uid,'name'=>' Иницилизация страниц1 '.$Site->domen,'newstext'=>'Загрузка страниц на сайт '.$Site->domen.' выполнена. ','idnews'=>($user->getscountab('infos','idnews', 'f')+1),'vendor'=>$Site->domen,'group'=>'inition','imgnews'=>'faviconjpg.jpg','codgjsnews'=>'','hrefnew'=>$Site->domen.'/'.$Site->nmpage,'numpagat'=>$startpage,'site'=>$Site->domen);	
	Utils::prepare_pages($uid,$Site->domen,$lpg,$nn,$db,$Site->types,$Site->pages.'.csv');		
}
//проверяем статус пользователя по отношению к системе
	if ($uid <> 0) {
		$mode_edit=$user->areyouAdmin($_SERVER['HTTP_HOST'],$uid);
		if(!$mode_edit)$mode_mang=$user->areyouManager($_SERVER['HTTP_HOST'],$uid);
		else $mode_mang = false;
	}
	else {
		$mode_edit=false;
		$mode_mang=false;
	}
if(!$mode_edit && !$user->isGuest()) $mode_work=true;
elseif($mode_mang && !$mode_edit)$mode_work=true;
else $mode_work=false;	
if($mode_work)$text_access = 'Work mode setted';
elseif($mode_mang)$text_access =  'Manager mode setted';
elseif($mode_edit)$text_access = 'Edit mode setted';
elseif($user->isGuest()) $text_access = 'Guest mode setted';
else $text_access = 'Anonim mode setted';
$sid=$Site->ids;
if(!$mode_mang && !$mode_edit ) $mode_work=true;//&& !$user->isGuest()
else $mode_work=false;
if(!isset($type_page)) $type_page=0;
define('MAIN_PAGE_SITE',$Site->nmpage);
define('MAIN_NEWS', $Site->news);
define('MAIN_DOMEN', $Site->domen);
if(!$mode_work){
	
	//Система загрузки информации на сайт
	//Проверяем наличие страниц на сайте
	$d='SELECT * FROM `'.$Site->pages.'` WHERE `site`=^Ns;';
	$res=$db->query($d,$Site->domen);
	$lpg=$user->getscountab($Site->pages,'numpage', 'f');
	//Определяем состояние таблиц и сохраняем количество записей
	
	//блок обработки внешних параметров для страницы
	if (isset($_GET['tab'])) {
		if (isset($_GET['field'])) $field=isset($_GET['field']);	
		if($_GET['tab']<> 'customers' &&   $_GET['tab']<> 'news' &&   $_GET['tab']<> 'namparams' &&   $_GET['tab']<> 'allsites') $field='id';
		elseif($_GET['tab']=='namparams')$field='codparams';
		elseif($_GET['tab']=='allsites')$field='ids';
		//elseif($_GET['tab']=='forms')$field='idform';
		if ($field<>'')	$number_value_tab=$user->getscountab($_GET['tab'],$field, 'f');
	}
	//если у пользователя достаточнор прав и база страниц пуста выполняем процедуру загрузки страниц на сайт
	if (!$res && $user->getscountab($Site->pages,'numpage', 'f') == 0 && $mode_edit) 
	{ 
	//echo 'на сайте нет страниц ';	
	$nn[0]=array('idauthor'=>$uid,'name'=>' Иницилизация страниц2 '.$Site->domen,'newstext'=>'Загрузка страниц на сайт '.$Site->domen.' выполнена. ','idnews'=>($user->getscountab($tabl['infos'],'idnews', 'f')+1),'vendor'=>$Site->domen,'group'=>'inition','imgnews'=>'faviconjpg.jpg','codgjsnews'=>'','hrefnew'=>$Site->domen.'/'.$Site->nmpage,'numpagat'=>$startpage,'site'=>$Site->domen);
	Utils::prepare_pages($uid,$Site->domen,$lpg,$nn,$db,$Site->types);	
	}
	//Далее загружаются данные в служебные таблицы, при наличии одноименных файлов 
	//Если найден соответсвующий файл найден, то информация загружается,  файл удаляется. Информация дописывается в базу данных 
	
	
	$lna=$user->getscountab('namparams','codparams', 'f');
	//echo 'lna '.$lna.'<br>';
	$file='./nampars.csv';
	if (file_exists($file)) {
		$F=fopen($file,"r");
		if ($F){
			fclose($F);	
			Utils::add_tabs_file($Site->domen,$user,'namparams',$db,$uid,10000,$file);
			//echo '<br>успешная загрузка данных...'.$file;	
			
		}
		//else echo '<br> файл не найден - '.$file;
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
			//else echo '<br> файл не найден -  '.$file;	
	}
	unset($lnp);unset($lna);

	$pathpics='';
}

//$DESCSITES=explode('|',$Site->desc_site);

//if($user->getLevelnew() > 5  &&  $type_access === 'general')$type_access = 'global';
//echo $type_access ;
//иницилизация массива производителей
if (!$vend=='') $choice_vendors[]=$vend;
//Основной банер и логотип страницы
$picsglb=explode(';',$Site->images);
if(isset($picsglb[0]))$Bannrpic=$picsglb[0];
else $Bannrpic='';
if(isset($picsglb[1]))$Logopic=$picsglb[1];
else $Logopic='';
if(isset($picsglb[2]))$photoProf=$picsglb[2];
else $photoProf='photo.jpg';
//echo $photoProf;
//инормация о владельце сайта для вывода в браузер

$Owner_site=$user->idUserF($Site->uid);
if($Owner_site){	
	$Owner_site->ids=$Site->ids;
	$Owner_site->start=$startpage;
	if($Owner_site->level>0){
		$firm['em']=$user->getEmail();
		$firm['name']=$user->getLogin();
		$firm['cfio']=$Owner_site->cfio;
		$firm['telmain']=$Owner_site->telmain;
		$hosting_params=$Owner_site->hosting;
		$social=$Owner_site->social;
		$social_link=$Owner_site->social_link;
		$code_host=0;
		foreach($hosting_params as $val)if($val<>'ny')$code_host++;
		$tarif=9-$code_host;
		
	}
}	
else $Owner_site = (object)array();	

if($mode_edit) {
	$Owner_site->admin='Admin';
	$Owner_site->tarif=8;
	$Owner_site->level=6;
}
else {
	$Owner_site->admin='';
	$Owner_site->tarif=0;
	$Owner_site->level=0;
}
//присвоение владельцу сайта прав администратора



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
	//проверка режима ремонта
