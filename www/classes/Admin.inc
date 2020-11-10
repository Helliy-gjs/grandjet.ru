<?php
if ($distype[0]=== 'wr'){
	include($pathheader.$pathToClasses.'fish.inc');
	$arrmain=$contmak;
}

if(isset($_GET['settingS'])){ header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/settings/?np='.$_GET['np']);
exit();
}

//основное меню страницы загружается в режимах просмотра данных, и не видно режиме редактирования
//проверка режима редактирования страницы
//echo $arrmain['nump'];
//echo $_POST['publ'];

if(isset($_POST['publ']) && $distype[0] != 'wr'){
if($mode_edit && $_POST['publ']=='public'){
		if(isset($Owner_site->tarif)&& isset($numpage)&& isset($idmaket)){
			//echo '<info class="hidno">Публикуется страница</info>';
		if($sw->publpage($ew,$numpage,$tabl,$Owner_site,$idmaket,$_POST['delay']*86400,$_POST['mfl'],$_POST['lfl'])){
				echo '<info class="hidno">Страница опуликована</info>';
			}
			else echo '<info class="hino">Страница не опубликована</info>';	
		//header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/?np='.$numpage.'&konstrS');exit();
	}
}
elseif($mode_edit && $_POST['publ']=='unpublic'){
	if(isset($Owner_site->tarif)&& isset($numpage)&& isset($idmaket)){
			//echo 'Публикуется страница';
			if($sw->unpublic($numpage,$tabl,$Site->domen,$Owner_site,$idmaket)){
				echo '<info class="hidno">Страница опуликована</info>';
			}
			else echo '<info class="hidno">Страница не опубликована</info>';	
	}
}
elseif($mode_edit && $_POST['publ']=='delayed'){
	if(isset($Owner_site->tarif)&& isset($numpage)&& isset($idmaket)){
			//echo 'Публикация страницы отложена';
			if($sw->publpage($ew,$numpage,$tabl,$Owner_site,$idmaket,$_POST['delay']*86400,$_POST['mfl'],$_POST['lfl'])){
				echo '<info class="hino">Публикация страницы отложена</info>';
			}
			else echo '<info class="hino">Страница не опубликована</info>';	
		//header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/?np='.$numpage.'&konstrS');exit();
	}
	
}	
elseif($mode_edit && $_POST['publ']=='allpublic'){
	if(isset($Owner_site->tarif)&& isset($numpage)&& isset($idmaket)){
			//echo 'Публикация страницы отложена';
			if($sw->allpublpage($ew,$tabl,$Site->domen,$uid,$Owner_site)){
				echo '<info class="hino">Страницы опубликованы</info>';
			}
			else echo '<info class="hino">Страницы не опубликованы</info>';	
		//header('Location: '.$prot.$_SERVER['HTTP_HOST'].'/?np='.$numpage.'&konstrS');
	}
	
}	
}
//режим редактирования
elseif ( $mode_edit && isset($_GET['editp']) ) {
	
	$c=25;//количеситво колонок в текстовом окне
	$r=1;//количество рядов в текстовом окне
	$s=30;//количеситво символов  окне
	//$m=40;
	$t=0;
	if(!strstr($PageM->MainAr['title'],'all'))include($pathheader.$pathToClasses.'editall.inc');
	else include($pathheader.$pathToClasses.'start.inc');
	}
	
	//проверка режима редактирования шрифтов
//проверка режима редактирования шрифтов
elseif($mode_edit && isset($_GET['fontS'])){
	
	include($pathheader.$pathToClasses.'editfonts.inc');
}	
//проверка режима редактирования данных пользователя
elseif(isset($_GET['cust'] )&&  isset($_GET['editp']) &&  !isset($_GET['tab'])){
	
	$c=50;//количеситво колонок в текстовом окне
	$r=2;//количество рядов в текстовом окне
	$s=130;//количеситво символов  окне
	include($pathheader.$pathToClasses.'editall.inc');
}

if(!isset($_GET['editp']) && $mode_edit){
	if(!isset($_GET['maketS']) && !isset($_GET['envirS'] )){
		$resu=$PageM->read_namparams('setAdmin',0);
		//print_r($resu);
		if($IsLocal){
			unset($resu[0][count($resu[0])-2]);
			unset($resu[1][count($resu[1])-2]);
		}
		//print_r($resu);
		Maket::divclass('set_container',$Pth,'margin: 5px;flex-direction: row; flex-wrap:nowrap; flex-basis:100%; justify-content:space-between',' flex;');
			
			if($distype[0] != 'wr'){
				Maket::divclass($Maks_Page[8].'-'.$disp,$Pth,'margin: 5px;flex-direction: row; flex-wrap:nowrap; flex-basis:100%; justify-content:space-around;display:flex;');
				echo '<div class="menu admin">';
				$user->stringusermen('user',$Pth,$db->init_data[0],'.',$numpage);
				echo '</div></div>';
			}
				echo '<div class="menu set">';
				echo show::work_pages('menu',$Pth,$resu,'./'.$graphp);
			echo '</div>';
		
		
echo '</div></div>';
}

	

if(!isset($_GET['konstrS'])){
	
	//Информация о данных топологических элементов
if(isset($_GET['contentS'])){
	include($pathheader.$pathToClasses.'Content_site.inc');
}
if(isset($_GET['blockS'])){
	include($pathheader.$pathToClasses.'Blocks_sites.inc');
}	
if(isset($_GET['gridS'])){
	include($pathheader.$pathToClasses.'Grid_sites.inc');
}	
if(isset($_GET['maketS'])){	
	include($pathheader.$pathToClasses.'MaketProp.inc');
	}	
if(isset($_GET['seoS'])){
	include($pathheader.$pathToClasses.'seo.inc');
	}	
//echo '</div>';
if(isset($_GET['envirS'])){
	
	include($pathheader.$pathToClasses.'environment.inc');
	}	
//echo '</div>';
}
//Maket::closediv(1);
if(isset($_GET['konstrS']) && $mode_edit){
	
	$arrmain=Page::readyadmarr($arrmain);
	//print_r($arrmain['cont']);
	Maket::closediv(1);
	Maket::divclass('set_container',$Pth,'margin: 5px;flex-direction: row; flex-wrap:nowrap; flex-basis:100%; justify-content:space-around',' flex');
	Maket::divclass($Maks_Page[17].'-'.$disp,$Pth,'margin: 30px;flex-direction: column; flex-wrap:nowrap; flex-basis:100%; justify-content:space-around;flex');
	Maket::divclass($Maks_Page[8],$Pth,'margin: 30px;flex-direction: row;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around');
	Maket::divclass('public_container',$Pth,'font-size: 12px;');
	$localpath='';
	Maket::selectors($arrmain,$Pth,$vendors,2,$localpath);
	echo '</div></div>';
	echo '<div>';
	Maket::divclass($Maks_Page[8],$Pth,'margin: 30px;flex-direction: row;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around',' flex');
	Maket::selectors($arrmain,$Pth,$vendors,3,$localpath);
	echo '</div></div>';
	Maket::divclass($Maks_Page[8],$Pth,'margin: 30px 10px;flex-direction: row;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around',' flex');
	if($distype[0] != 'nwr'){
		if($arrconf['site'])Maket::selectors($arrmain,$Pth,$vendors,5,$localpath);
		if($arrconf['maket'])Maket::selectors($arrmain,$Pth,$vendors,6,$localpath);
	}
	if($arrconf['page'] && $distype[0] != 'wr')Maket::selectors($arrmain,$Pth,$vendors,4,$localpath);
	else Maket::selectors($arrmain,$Pth,$vendors,7,$localpath);
	echo '</div></div>';
	if($distype[0] != 'wr'){
		$datepub=$sw->ispublicpage($numpage);
		//echo $datepub;	
		if($datepub==='unpublic' && $datepub<>'absent')$strpub0='Опубликовать   изменения  ';
		else $strpub0='Опубликовать ';
		//echo '<div style="font-size:'.$size_pars1.'px;" >';
		Maket::divclass('public_container',$Pth,'font-size: 12px;');
		if($datepub==='unpublic'  || $datepub==='absent' ){
			$size_pars1=12;
			
			echo '<form method="POST" action="./?konstrS&np='.$numpage.'">';
			echo '<input type="hidden" name="publ" value="public">';
			echo '<label class="delay">Отложить на</label><input class="delay" type="text" name="delay" value="" size="5">дней';
			echo '<br><label class="delay">Отменить публикуцию через</label><input class="delay" type="text" name="lfl" value="" size="5">дней';
			echo '<br><label class="delay">Подключить маркетинговую программу</label><input class="delay" type="text" name="mfl" value="" size="5">';
			Maket::spanclass(Maket::divclasstr('button',$Pth,'','','input type="submit" value=" '.$strpub0.$numpage.'"').'</input>',$Pth);
			echo '</form>';	
			echo '<form method="POST" action="./?konstrS&np='.$numpage.'">';
			echo '<input type="hidden" name="publ" value="allpublic">';
			if($sw->ispublpages($uid,$Site->domen,$tabl)> 0){
				Maket::spanclass(Maket::divclasstr('button',$Pth,'','','input type="submit" value="'.$strpub0.' все опубликованые"').'</input>',$Pth);//
			}	
			 
			echo '</form>';
		}
		elseif($datepub<>'unpublic' && $datepub<>'absent' && $datepub<>'delayed') {
			//echo $datepub;
			$strpub='Опубликовано ';
			Maket::spanclass(Maket::divclasstr('button-grey',$Pth,'','','input type="button" value="'.$strpub.'"').'</input>',$Pth);
		}
		elseif($datepub==='delayed'){
			//echo $datepub;
			$strpub='Опубликовано ';
			Maket::spanclass(Maket::divclasstr('button-grey',$Pth,'','','input type="button" value="'.$strpub.'"').'</input>',$Pth);
		
		}
		else Maket::spanclass(Maket::divclasstr('button-grey',$Pth,'','','input type="button" value="Не опубликовано"').'</input>',$Pth);
		
		echo '</div>';
}
	Maket::closediv(3);
	
	include($pathheader.$pathToClasses.'Mainpage.inc');
}
elseif(!isset($_GET['envirS']) && !isset($_GET['blockS']) && !isset($_GET['seoS'] )&& !isset($_GET['contentS']) && !isset($_GET['gridS'])&& !isset($_GET['editp']) && !isset($_GET['maketS'])) {	
	$arrmain['link']='';
	include($pathheader.$pathToClasses.'Mainpage.inc');
	}
//Maket::closediv(1);	
}
elseif($distype[4]==='nhd'){
		if(!$mode_edit){
		$ownrst=$arrmain['owner']->cfio.': ';
		if ($arrmain['owner']->telmain) $ownrst.=$arrmain['owner']->telmain.' ';
		if ($arrmain['owner']->email) $ownrst.=$arrmain['owner']->email;
		Maket::spanclass($ownrst,$Pth,'admin');
		}
		else $user->stringusermen('user',$Pth);
}	
?>