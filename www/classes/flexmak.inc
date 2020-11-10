<?php
if(isset($_GET['GM'])){
echo '<h3>Топология макета</h3>';
		$prefix=' grid';
		$ncontainer=$MP[3];
		$clas_modul=array($MP[1],$MP[8],$MP[7].'-Left',$MP[10],$MP[7].'-Right',$MP[2],$MP[7].'-Center',$MP[6],$MP[4],$MP[5],$MP[17],$MP[11],'wrapper-'.$MP[16]);
		$arrmod=array(1,6,20,8,20,7,12,14,20,15,10,21,22);
		print_r($clas_modul);
		Maket::divclass('#'.$MP[0],$Pth,'',$prefix);
		
}	
elseif(isset($_GET['LG'])){
	echo '<h3>Лого макета</h3>';
	$prefix=' flex';
	$clas_modul=array('logo-logo','logo-item0','logo-'.$disp,'logo-'.$disp.'-li');
	$arrmod=array(4,42,43,44,45);
	$ncontainer[0]='logo';
	
}	
elseif(isset($_GET['HD'])){
		echo '<h3>Хедер макета</h3>';
		$prefix=' flex';
		$clas_modul=array($MP[22],$MP[20],$MP[21],$MP[9],$MP[19]);
		$arrmod=array(4,22,2,20,20);
		$ncontainer=$MP[12];
}
elseif(isset($_GET['BT'])){
		echo '<h3>Блок кнопок</h3>';
		$prefix=' flex';
		$nbutt=0;
		if($nbutt==0) $nbutt=count($arrmain['butt']);
		
		unset($arrmain['butt']['link']);
		foreach($arrmain['butt'] as $key=>$val){
			if($key<$nbutt-1){
				$clas_modul[$key]='button-'.$arrmain['idmen'][0].$nbutt;
				//$main_mod_typ[$key]=$val;
				$arrmod[$key]=6;
			}
		}
		$ncontainer=$MP[8];
		
}	
elseif(isset($_GET['MN'])){
		echo '<h3>Блок меню</h3>';
		$prefix=' flex';
		$nlist=0;
		if($nlist==0) $nlist=count($arrmain['list']);
		
		unset($arrmain['list']['link']);
		foreach($arrmain['list'] as $key=>$val){
			if($key<$nlist-1){
				$clas_modul[$key]='menu-'.$arrmain['idmen'][0].$nlist;
				//$main_mod_typ[$key]=$val;
				$arrmod[$key]=7;
			}
		}
		$ncontainer='main_menu'.'-'.$arrmain['idmen'][0];
		
}
elseif(isset($_GET['CT'])){
		echo '<h3>Основной контент</h3>';
		$prefix=' grid';
		$clas_modul=array($MP[7].'-Left',$MP[7].'-Right',$MP[6],$MP[4],$MP[5]);
		$arrmod=array(20,20,20,20,20,20);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}
elseif(isset($_GET['GL'])){
		echo '<h3>Галерея</h3>';
		$prefix=' grid';
		$clas_modul=array($MP[7].'-Center');
		$arrmod=array(12);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}
elseif(isset($_GET['SL'])){
		echo '<h3>Слайдер</h3>';
		$prefix=' flex';
		$clas_modul=array($MP[10]);
		$arrmod=array(8);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}
elseif(isset($_GET['AC'])){
		echo '<h3>Аккордион</h3>';
		$prefix=' flex';
		$clas_modul=array($MP[10]);
		$arrmod=array(16);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}		
elseif(isset($_GET['FM'])){
		echo '<h3>Форма</h3>';
		$prefix=' flex';
		$clas_modul=array($MP[17]);
		$arrmod=array(10);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}	
elseif(isset($_GET['FT'])){
		echo '<h3>Футер</h3>';
		$prefix=' flex';
		$clas_modul=array($MP[11]);
		$arrmod=array(21);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}		
elseif(isset($_GET['NW'])){
		echo '<h3>Новости</h3>';
		$prefix=' flex';
		$clas_modul=array($MP[5]);
		$arrmod=array(15);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}	
elseif(isset($_GET['BL'])){
		echo '<h3>Блог</h3>';
		$prefix=' flex';
		$clas_modul=array($MP[7].'-Center');
		$arrmod=array(14);
		//Maket::divclass($MP[0],$Pth,'',$prefix);
		$ncontainer=$MP[3];
	}
else {
	include_once($pathheader.$pathToClasses.'propmak.inc');
}
if(isset($nbutt) )$nmod=$nbutt;
elseif( isset($nlist))$nmod=$nlist;
else $nmod=count($clas_modul);
$act='Y';
//$accordion=Maket::accordsh('imgs',$arrmain,$Pth);
//print_r($accordion);
//$slider=Maket::swipersh('imgs',$arrmain,$Pth);	
foreach($clas_modul as $key=>$val){
	if($key<$nmod){
		if(isset($_GET['SL']))$arr_modul['val'][$key]=Maket::swipersh('imgs',$arrmain,$Pth);	
		elseif(isset($_GET['AC']))$arr_modul['val'][$key]=Maket::accordsh('imgs',$arrmain,$Pth);
		else $arr_modul['val'][$key]=Maket::div2Blockstr($val,$arrmain['idmen'][0].$key,$Pth).$val.Maket::closedivstr(2);
		$arr_modul['typ'][$key]=$main_mod_typ[$arrmod[$key]];
	}
}
	if($ncontainer <> '')Maket::showmodules($ncontainer.$prefix,$clas_modul,$Pth,$arr_modul,'',$nmod);
	else Maket::showmodules($prefix,$clas_modul,$Pth,$arr_modul,'',$nmod);
?>