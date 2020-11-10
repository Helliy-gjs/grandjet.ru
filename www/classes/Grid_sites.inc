<?php
if(!$mode_work && isset($_GET['gridS']) )
//	echo 'Основные элементы сетки<hr>';//comment
	$resuG=$PageM->read_namparams('setgridS',0);
	if(isset($_GET['gridS'])) foreach($resuG[1] as $key=>$val) $resuG[1][$key]=$resuG[1][$key].'&gridS';
	Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,'margin: 10px;flex-direction: row; flex-wrap:nowrap; flex-basis:100%; justify-content:space-around;flex');
	Maket::divclass($Maks_Page[8],$Pth,'margin: 30px;flex-direction: column;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around;flex',' flex');
	echo '<div class="menu set">';
	echo show::work_pages('menu',$Pth,$resuG,'./'.$graphp);
	echo '</div>';
	Maket::closediv(1);
	if(isset($_GET['layoutG'])){
		$clas_modul=array('main-header','main-menu','sidebarL','sidebarC','sidebarR','main_footer');
		$nmod=count($clas_modul);
		foreach($clas_modul as $key=>$val)if($key<$nmod)$arr_modul[$key]=Maket::div3Blockstr($val,'item-'.$key).$val.'-'.$arrmain['idmen'][0].Maket::closedivstr(3);
		Maket::divclass($Maks_Page[0],$Pth,'',' grid');
		Maket::showmodules('main_wrapper',$clas_modul,$Pth,$arr_modul,' grid',$nmod);

		Maket::closediv(1);
		
	}
	elseif(isset($_GET['headerG'])){
		$nmod=4;
		$clas_modul=array('user','logotype','serv','shop');
		$logomod=Maket::scalimag3($arrmain,$arrmain['clas']['img'].$arrmain['namep'][1],'./?np='.$arrmain['nump'],$Pth,0);
		$arr_modul=array($ownerdata,$logomod,$service,$shop);
		//foreach($clas_modul as $key=>$val)if($key<$nmod)$arr_modul[$key]=Maket::div3Blockstr($val,'item-'.$key).'header-item'.$key.Maket::closedivstr(3);
		
		Maket::divclass('main-header',$Pth);
		Maket::showmodules('header',$clas_modul,$Pth,$arr_modul,'grid',$nmod);
		
		
		Maket::closediv(1);
		
	}
	elseif(isset($_GET['contentG'])){
		$clas_modul=array('main-menu','sidebarL','sidebarC','sidebarR','main_footer');
		$nmod=count($clas_modul);
		foreach($clas_modul as $key=>$val)if($key<$nmod)$arr_modul[$key]=Maket::div3Blockstr($val,'item-'.$key).$val.'-'.$arrmain['idmen'][0].Maket::closedivstr(3);
		Maket::divclass('main_wrapper',$Pth,'',' grid');
		Maket::showmodules('main-wrapper',$clas_modul,$Pth,$arr_modul,' grid',$nmod);

		Maket::closediv(1);
	}
	elseif(isset($_GET['footerG'])){
		
	}
	Maket::closediv(1);
	
?>
	