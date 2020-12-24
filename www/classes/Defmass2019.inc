<?php
//echo $numpage;echo '<br>';
$Scrpt_users='';
$version = curl_version();
//print_r($version);

//print_r($arridmen);
//$arridmen=array(8=>'cont', 0=>'land', 1=>'gall', 7=>'flex', 11=>'mag', 9=>'cat',6=>'mob' ,4=>'fb', 3=>'tw',5=>'qw',10=>'shop',2=>'blog',12=>'lay');		
//определяем тополгию макета страницы
$arrstyles1=array('idclas','nameclas','styles','flex','grid','numparams','fonts','video','effects','scripts');
$arrstyles=array('styles','flex','grid','fonts','video');
//проверка наличия макетов у сайта
foreach($arridmen as $value){
	$maket=$value.'-'.$numpage; 
	$YourMakets[$maket]=$sw->allmakets($Site->ids,$maket);
}

echo $disp;
if(isset($disp)){
	if($disp<>'' && isset($YourMakets[$disp.'-'.$numpage])) $AllMakets=$YourMakets[$disp.'-'.$numpage];
	else $AllMakets=array();

show::infosh($AllMakets);
	

	$Pth['type_access']=$type_access;
	$Pth['mode_access']=$mode_work;
	$Pth['prot']=$prot;

	if ($type_access=='local') $img_ban=$clas['img'].$arrmain['namep'][0];
	elseif($type_access=='global') $img_ban=$clas['img'].$Bannrpic;
	elseif($type_access=='general') $img_ban= $clas['img'].'banmain.jpg';
	if ($type_access=='local') $img_log=$clas['img'].$arrmain['namep'][1];
	elseif($type_access=='global') $img_log=$clas['img'].$Logopic;
	elseif($type_access=='general') $img_log= $clas['img'].'logo.png';
	$graphp=$Site->nmpage;
	$ind_scr=substr($arrmain['idmen'][0],0,2);
	$bhrf='./'.$graphp.'?np='.$numpage;//путь к данной странице
	$n = $user->getscountab('allmakets','id', 'f');
	if($n == 0)$n=1;
	if(!empty($AllMakets)){
		if (!$AllMakets){
			//Если у сайта нет макета, то добавлятся стандартный набор макетов
			foreach($arridmen as $key=>$value){
				if ($key<=  intval($Site->types) && isset($numpage) && $numpage != '') Maket::addnewGlbMaket($n+$key,$value.'-'.$numpage,$numpage,$Site->ids,$db);
				}
		}
		else {
			$desc_maket=explode('|',$AllMakets[0][10]);
			if(isset($desc_maket[2]))$type_access=$desc_maket[2];
			else $type_access='global';
			//if($mode_edit) show::infosh($YourMakets);
			
		}
		//echo $AllMakets[0][1];
		if($AllMakets[0][1]){
		//определякм индентификатор активного макета. Макет может быть  установлен для каждой страницы свой, или один для всех страниц 
		//echo $AllMakets[0][1];
		$type_maket=explode('-',$AllMakets[0][1]);
		if ($disp<>'') {
			//if($disp <> $AllMakets[0][1]) $disp=$AllMakets[0][1];
			//находим макет данного данной страницы
			$idmakets=$sw->getlookforalltab($AllMakets[0][1],$Site->ids,'allmakets',0,1,11);
			//если такой макет есть 
			//print_r($idmakets);
			if(isset($idmakets)) $idmaket=$idmakets[0]['id'];
			else { 
			//Если нет находим макет данного сайта
				$idmakets=$sw->getlookforalltab($arridmen[$Site->strucs].'-'.$numpage,$Site->ids,'allmakets',0,1,11);
				//show::infosh($idmakets);
			$idmaket=$idmakets[0]['id'];
			}
		}
		if(!isset($idmaket)) exit('макет сайта загрузить не удалось');
		//если администратор, параметры:номер страницы и номера пользователя, сайта и макета передаются в массив свойств макета
		//if($mode_edit) 
			$Pth['adm']=array('np'=>$numpage,'uid'=>$uid,'ids'=>$Site->ids,'idm'=>$idmaket,'sp'=>$startpage);

		$curr_mak=$user->getscountab('maket','id', 'f')+1;
		//если еще не установлен ни один макет, страница статартовая то администратор загружает стандартные классы
		if ($mode_edit && $idmakets[0]['Maket']<>''  ) Maket::addnewStMaket2($curr_mak,$idmaket,$numpage,$Site->ids,$uid,Singleton::getInstance('DB'));
		$all_maket_name=$ew->view_table('allmakets','id',0);//массив заголовков параметров хранящихся в Allmakets
		if($idmaket>0)$all_maket_par=$ew->view_table('allmakets','id',$idmaket);//массив общих для страниц параметров макетов
		//show::infosh($all_maket_par);
		if(is_array($all_maket_par)) $all_maket_par = $all_maket_par[0];
		$Maket_num_fonts=explode('|',$all_maket_par->fonts);
		foreach($Maket_num_fonts as $val){
			$PthGl['fonts'][]=$ew->getallfonts($val);
		}
		//show::infosh($PthGl['fonts']);
		$spisok_GLparams=explode('|',$all_maket_par->numparams);
		$spisok_GLnames=explode('|',$all_maket_name->numparams);
		//debug($spisok_GLparams);
		//show::infosh($spisok_GLnames);
		foreach($spisok_GLnames as $key=>$val){
			if(isset($spisok_GLparams[$key])){
			if (strstr($spisok_GLparams[$key],';')) $spisok_mak_par['Maket'][$val]=explode(';',$spisok_GLparams[$key]);
			else $spisok_mak_par['Maket'][$val][0]=$spisok_GLparams[$key];
			}
		}
		//debug($all_maket_par);
		if(isset($all_maket_par)){
			$spisok_zagalovkov=$sw->allmaketspage(0,0,$startpage);
			//debug($spisok_zagalovkov);
			//die();
			if (isset($spisok_zagalovkov)){
				foreach($spisok_zagalovkov['Maket'] as $key=>$val){
					//$val='|'.$val;
				  $resm[$key]=explode('|',$val);
					}
	//debug($resm);
	//die();			
		foreach ($resm as $key=>$value){
		//foreach ($value as $i=>$val) if (isset($val[$i+1]))$style_name[$key][$i]=$val[$i+1];
		for ($i=0;$i<count($value);$i++) if (isset($value[$i])) $style_name[$key][$i]=$value[$i];
		}
	}
		$spisok_maketov=$sw->allmaketspage($numpage,$idmaket,$startpage);		
			if (isset($spisok_maketov)){
				if (count($spisok_maketov)>0){
					foreach($spisok_maketov as $i=>$value){
						$Maks_Page[]=$i;
						foreach($value as $key=>$val){
							if(strstr($val,'|')) $Style_par[$key][$i]=explode('|',$val);
							else $Style_par[$key][$i]='';
					}		
				}
			}
		}
		foreach($Maks_Page as $val) $MP[] = $val;

		//числовые параметры сайта
		if(isset($Maks_Page)){
		foreach($Maks_Page as $val){
			foreach($Style_par['numparams'][$val] as $key=>$value){
			if(isset($spisok_GLnames[$key])){	
				if($value)  $spisok_mak_par[$val][$spisok_GLnames[$key]]=explode(';',$value);
				elseif(isset($spisok_mak_par['Maket'][$spisok_GLnames[$key]])) $spisok_mak_par[$val][$spisok_GLnames[$key]]=$spisok_mak_par['Maket'][$spisok_GLnames[$key]];
				else $spisok_mak_par[$val][$spisok_GLnames[$key]]='';
					}
				}
			}
		}

		foreach($arrstyles as $val){ 
			foreach ($Maks_Page as $value){
				$PthAll[$value][$val]=Maket::MaketParPage($style_name[$val],$Style_par[$val][$value]);
			}
		}
		//отдельные значения стилей шрифтов параметров эффектов видео 
		unset($spisok_GLparams);
		unset($spisok_GLnames);
		foreach($PthAll as $key=>$value){
			$Pth[$key]['styles']='';
			$Pth[$key]['scripts']='';
			$Pth[$key]['effects']='';
		foreach ($value as $key2=>$val) {
			if($key2==='styles' || $key2==='flex'  || $key2==='grid'|| $key2==='fonts'  || $key2==='video'  &&  $val<>'') $Pth[$key]['styles'].=$val;
			elseif($key2=='scripts') $Pth[$key]['scripts'][]=$val;
			elseif($key2=='effects') $Pth[$key]['effects'][]=$val;
		}

		}
		//блок основных свойств макета сайта
		foreach($all_maket_par as $key=>$value) {
			$main_maket['par'][]=explode('|',$value);
			$main_maket['name'][]=explode('|',$all_maket_name->$key);
		}
		//print_r($main_maket['par'][2]);
		$arrrr=$sw->getPagelinks(1,'maket','id');

		foreach ($Maks_Page as  $val){
			$num_clas=$ew-> view_table('maket','Maket',$val,'numaket',$idmaket);
			if(isset($num_clas->id))$Pth[$val]['id']=$num_clas->id;
			$nprm_name=explode('|',$spisok_zagalovkov['Maket']['styles']);
			foreach($nprm_name as $key=>$value){
				if(isset($arrrr[2][$key]))$Pth[$val]['link_style'][$value]=$arrrr[2][$key];
				if(isset($Style_par['styles'][$val][$key]))$Pth[$val]['style'][$value]=$Style_par['styles'][$val][$key];
				}
			$nprm_name=explode('|',$spisok_zagalovkov['Maket']['numparams']);
			$nprm_val=explode('|',$spisok_maketov[$val]['numparams']);
			foreach($nprm_name as $key=>$value){
				if(isset($arrrr[3][$key]))$Pth[$val]['link_numpar'][$value]=$arrrr[3][$key];
				if(isset($nprm_val[$key]))$Pth[$val]['numpar'][$value]=$nprm_val[$key];
			}
			$nprm_name=explode('|',$spisok_zagalovkov['Maket']['fonts']);
			$nprm_val=explode('|',$spisok_maketov[$val]['fonts']);
			foreach($nprm_name as $key=>$value){
				if(isset($arrrr[4][$key]))$Pth[$val]['link_font'][$value]=$arrrr[4][$key];
				if(isset($nprm_val[$key]))$Pth[$val]['font'][$value]=$nprm_val[$key];
			}
			$nprm_name=explode('|',$spisok_zagalovkov['Maket']['video']);
			$nprm_val=explode('|',$spisok_maketov[$val]['video']);
			foreach($nprm_name as $key=>$value){
				if(isset($arrrr[5][$key]))$Pth[$val]['link_video'][$value]=$arrrr[5][$key];
				if(isset($nprm_val[$key]))$Pth[$val]['video'][$value]=$nprm_val[$key];
			}	
			$nprm_name=explode('|',$spisok_zagalovkov['Maket']['effects']);
			$nprm_val=explode('|',$spisok_maketov[$val]['effects']);
			foreach($nprm_name as $key=>$value){
				if(isset($arrrr[6][$key]))$Pth[$val]['link_effect'][$value]=$arrrr[6][$key];
				if(isset($nprm_val[$key]))$Pth[$val]['effect'][$value]=$nprm_val[$key];
			}
			$nprm_name=explode('|',$spisok_zagalovkov['Maket']['scripts']);
			$nprm_val=explode('|',$spisok_maketov[$val]['scripts']);
			foreach($nprm_name as $key=>$value){
				if(isset($arrrr[6][$key]))$Pth[$val]['link_script'][$value]=$arrrr[6][$key];
				if(isset($nprm_val[$key]))$Pth[$val]['script'][$value]=$nprm_val[$key];
				}
			}	

		unset($spisok_zagalovkov);
		unset($all_maket_par);
		unset($PthAll);
		unset($arrrr);

	//print_r($spisok_mak_par['Maket']);
	//блок определяющей топологию страницы
	if(isset($spisok_mak_par['Maket'])){
		$Pth['global']=$spisok_mak_par['Maket'];
		$Pth['global']['id']=$main_maket['par'][0][0];
		$Pth['global']['styles']=$main_maket['par'][2];
		$Pth['global']['flex']=$main_maket['par'][3];
		$Pth['global']['grid']=$main_maket['par'][4];
		$Pth['global']['numparams']=$main_maket['par'][5];
		$Pth['global']['fonts']=$main_maket['par'][6];
		$Pth['global']['video']=$main_maket['par'][7];
		$Pth['global']['effects']=$main_maket['par'][8];
		$Pth['global']['scripts']=$main_maket['par'][9];
		$Pth['global']['desc_site']=$main_maket['par'][10];
		$GlobPar=$sw->getPagelinks($idmaket,'allmakets','id');
		$Pth['global']['styles']['link']=$GlobPar[2];
		$Pth['global']['flex']['link']=$GlobPar[3];
		$Pth['global']['grid']['link']=$GlobPar[4];
		$Pth['global']['numparams']['link']=$GlobPar[5];
		$Pth['global']['fonts']['link']=$GlobPar[6];
		$Pth['global']['video']['link']=$GlobPar[7];
		$Pth['global']['effects']['link']=$GlobPar[8];
		$Pth['global']['scripts']['link']=$GlobPar[9];
		}
		}
		else{
			exit(' The grandjet has no any layouts ');
		}
		//print_r($Pth['global']['styles']);
		unset($GlobPar);
		unset($main_maket);
		unset($spisok_mak_par);
		unset($nprm_name);
		unset($nprm_val);

		$Pth['global']['idmen']=$Site->types;
		//if(isset($_GET[])) $type_page=6;
		//Эти стили и парметры загружаются на все страницы с данным макетом

		if (isset($type_page)  &&  isset($Pth['global']['styles']) ){
			//print_r($Pth['global']['styles']);echo $type_page;
			$Style_users=$user->getstylesfiles($clas,$Pth['global']['styles'],$type_page,'.min');
		}

		if ($Pth['global']['desc_site'][0]<>'')  $faveic=$Pth['global']['desc_site'][0];
		else $faveic='favicongjs.png';
		//show::infosh($Style_par['scripts']['main_container'][0]);
		if (isset($Pth['global']['scripts'])) $Scrpt_users=$Pth['global']['scripts'];
		else $Scrpt_users='';
		//параметры управления размером изображений страницы
		if (isset($Pth['global']['Pics'])) $size_par ['pics']=$Pth['global']['Pics'];
		else $size_par ['pics']=array(0=>1.95,1=>1.4);
		//параметры управления размером шрифта
		if (isset($Pth['global']['Sizes'])) {
			foreach($Pth['global']['Sizes'] as $k=>$val)
			if(intval($val)){
				$size_par ['fonts'][$k]=$val.'px';
				$Pth['global']['Sizes'][$k]=$val.'px';
			}
			else $size_par ['fonts'][$k]=$val;
		}
		else $size_par ['fonts']=array(0=>'36px',1=>'14px',2=>'22px',3=>'10px',4=> 4, 5=> 3, 6=> 2);
		//параметры шрифтов
		if (isset($Pth['global']['Scale'])) $size_par ['scale']=$Pth['global']['Scale'];
		else $size_par ['scale']=array(0=>1,1=>1);
		//параметры масштабирования
		if (isset($Pth['global']['Transparent'])) $size_par ['opac']=$Pth['global']['Transparent'];
		else $size_par ['text']=array(0=>1,1=>1);
		//параметры текста
		if (isset($Pth['global']['fonts'])) $size_par ['text']=$Pth['global']['fonts'];
		else $size_par ['text']=array('align'=>1,'decoration'=>1,'overflow'=>'','shadow'=>'','transform'=>'');
		//параметры прозрачности
		if (isset($Pth['global']['Transition'])) $size_par ['trans']=$Pth['global']['Transition'];
		else $size_par ['opac']=array(0=>1,1=>1);
		//параметры переходов
		if (isset($Pth['global']['Bootstr'])) $size_par ['trans']=$Pth['global']['Bootstr'];
		else $size_par ['trans']=array(0=>1,1=>1);
		//параметры сетки
		if (isset($Pth['global']['Grid'])) $size_par ['grid']=$Pth['global']['Grid'];
		else $size_par ['grid']=array(0=>1,1=>1);
		}	
	}
	if($type_access=='global') {
		$arrmain['namep'][1]=$Logopic;
	}
	if($type_access==='global') {
		$arrmain['namep'][0]=$Bannrpic;
	}
	if(!isset($localdomen))$localdomen='';

	if($localdomen==='localhost')$ownerdata=$user->Localviewer($Pth);
	elseif ($user->getLevelnew()<=0) $ownerdata=$user->Userviewer($arrmain,'',$Pth,0);
	else $ownerdata=$user->Ownerviewer($arrmain, $Pth,0);
	$service=$user->Serviceblock($startpage,$levelU,$Site,$Pth);
	//echo $ownerdata;
	if($disp === 'shop'){
		$shop=$user->Shopblock($arrmain,$levelU,$vendors,$Pth);
		$cart = $user->CartBlock($Pth);
		$query = 'SELECT * FROM `brends` LIMIT 6';
		$brands = $db->query($query);
		//print_r($brands);
		$query = 'SELECT * FROM `elements` WHERE `ms`=^Ni AND `ls`=^Ni';
		$popular = $db->query($query.' LIMIT 8', 0, 1);
		if($popular){
			foreach ($popular as $val) $description[] = explode('|',$val->desc);
			//debug($popular);
			foreach($popular as $key=>$value) {
				$popular[$key]->desc = $description[$key];
				$popular[$key]->oldprice = $popular[$key]->price*(1 - $popular[$key]->discont);
			}		
		}
		$currencies = $db->getCurrencies();
		if($currencies){
			$currency = $db->getCurrency($currencies);
			$arrcurr=$sw->selectAllProperties('currency',0,2,6);
			if(isset($_POST['curr'])) {
					$currency->code = $_POST['curr'];
				}
				elseif(!isset($_COOKIE['currency'])) $currency->code = $arrcurr['id'][0];
				elseif(isset($_SESSION['currency']))	{
					if($_SESSION['currency'] != '' ) {
						echo '<strong>'.$_SESSION['currency'].'</strong>';
						$curr='<strong style="color: white">'.$this->currency->code.'</strong>';
					}
			}	
				elseif(is_array($arrcurr)){
					//echo 'currency '.$currency->id;
					$curr='<form style="align:left;  " method="post" action="/" target="_self">';    
					$curr.=$sw->selmenstr('dropdown drop',$arrcurr['Maket'],$arrcurr['id'],$currency->id,'curr','change','Сменить валюту?');
					$curr.='</form>';	
			}
		}	
		//echo $curr;
		}
		else $shop = '';
	 foreach ($Owner_site as $key=>$val)$contentSite['owner'][$key]=$val;
	$contentSite['owner']['block']=$user->Ownerviewer($arrmain, $Pth,0);
	if(isset($Pth['adm']))$contentSite['admin']=$Pth['adm'];
	if(isset($ownerdata))$contentSite['admin']['block']=$ownerdata;
	if($uid > 0)foreach($user->idUserF($uid) as $key=>$val)$contentSite['user'][$key]=$val;
	$contentSite['user']['login']=$user->getLogin();
	$contentSite['user']['email']=$user->getEmail();
	$contentSite['user']['block']=$user->Userviewer($arrmain,'',$Pth,0);
	$contentSite['manag']['status']=$user->whoareyouhere($user->getMs(),false);
	$contentSite['manag']['block']='';
	$contentSite['shop']['block']=$user->Shopblock($arrmain,2,$vendors,$Pth);
	if(isset($cart))$contentSite['order']['block']=$cart ;
	$contentSite['search']['block']=$user->Shopblock($arrmain,3,$vendors,$Pth);
	if(isset($curr))$contentSite['curr']['block']=$curr;
	$ind_scr=substr($disp,0,2);

	if(  $disp=='blog' || $disp=='tw' || $disp=='fb')$ownerdata.=$service;
}
//Определение слов для тайтла страни
//print_r($arrmain);


?>