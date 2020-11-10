<?php
//Основной контейнер сайта	
$order_id='donat';
$targets='Спонсорская поддержка совершенствования системы grandjetstudio';
$summ=1000;
//Maket::divclass('#main_container-'.$disp,$Pth);//<div 	
/*foreach($Maks_Page as $key=>$val){
		$MP[$key]=$val.'-'.$disp;
		
	}
	if(isset($Pth[$MP[0]][5])){
		if($Pth[$MP[0]][5] > 0) $prefix=' grid';
		elseif($Pth[$MP[0]][5]==0 && $disp=='flex')$prefix=' flex';
	}
	else $prefix='';*/
	
//print_r($mysites);
//проверка являетесь ли вы администратором сайта
if ($disp === '') $disp='cont';
set_time_limit(10000);
$ind_scr=substr($disp,0,2);
$bhrf='./'.$graphp.'?np='.$numpage;//путь к данной странице
//редактирование страниц
//редактирование данных о пользователе 
if(isset($_GET['cust'] )&&  isset($_GET['editp']) &&  !isset($_GET['tab']) && !$mode_edit){	
	$c=50;//количеситво колонок в текстовом окне
	$r=2;//количество рядов в текстовом окне
	$s=130;//количеситво символов  окне
	$t=1;
	include($pathheader.$pathToClasses.'editall.inc');
}
//числовые параметры header страницы 
//Пользовательский фонт в форме css

else {	
//помещаем весь контент в container, который можем от позиционировать по отношению к body
//print_r($Maks_Page);

if($type_access === 'local')$img=$arrmain['clas']['img'].$arrmain['namep'][0];
else $img=$arrmain['clas']['img'].$Bannrpic;
//Хедер сайта 
//print_r($distype);
//if ($distype[0]=== 'wr'){
	
	//print_r($contmak);
	if(file_exists($pathheader.$pathToClasses.'pay.inc')){
	$payuser=Singleton::getInstance('Pay');
	$txt=array('Состояние баланса ','Поддержите дальнейшую разработку системы ','Пополнить свой баланс','Введите промокод');
	$payuser->payform('adm-'.$arrmain['idmen'][0].'-'.$idmaket,$Pth,$currbals,500,$txt);
}
	if ($distype[4]=== 'hd'){
		
	if (file_exists($pathheader.$pathToClasses.'reg2019_'.$ind_scr.'.inc'))
	include($pathheader.$pathToClasses.'reg2019_'.$ind_scr.'.inc');
	elseif(file_exists($pathheader.$pathToClasses.'reg2019.inc'))
	include($pathheader.$pathToClasses.'reg2019.inc');
	if($mode_work){
	//$payuser->sponsorpay($Pth,$order_id,$targets,$summ);
	//$payuser->promocodpay($Pth, $summ,$user->getBalans(),$uid);
}
	}
	//print_r($arrmain['butt']);
	//$maxbtn=$arrconf['page']['szbutgrp']*$arrconf['page']['szbuttons'];
	//echo $arrconf['page']['szbuttons'];
	//$arfied = array('loz','butt','cont','list','foot','imgt','imgs');
	//$arnum['butt'] = Maket::rasklad(count($arrmain['butt']),intval(count($arrmain['butt'])/$maxbtn)+1,$arrconf['curpage']['szbuttons']);
	//print_r($arnum); 
	//echo $distype[3];
	$nBut=0;
	if ($distype[3]=== 'bt'){
		 $nBut=$arrconf['page']['szbuttons'];
		if(isset($arnum['butt'][1]))$nend = $arnum['butt'][1];
		else $nend = $arnum['butt'][0];
	//Загрузка основного меню навигации
		Maket::divclass('container_buttons',$Pth,'',' ' .$disp);
			Maket::showdisplaybutton($arrmain,$Pth,'button-'.$disp,'butt','div',0,$nBut);
		Maket::closediv(1);
		
	}
	if ($distype[1]=== 'bl'){
		//Загрузка основного контента сайта
		if(file_exists($pathheader.$pathToClasses.$disp.'ing.inc'))include($pathheader.$pathToClasses.$disp.'ing.inc');
		else '<info class="hidno">Content is absent</info>';
	}
	else echo '<info class="hidno">Content - nbl</info>';
	//Загрузка футера сайта
	if ($distype[5] === 'ft' && !isset($_GET['konstrS'])){
		if (file_exists($pathheader.$pathToClasses.'foot2019_'.$ind_scr.'.inc'))
		include($pathheader.$pathToClasses.'foot2019_'.$ind_scr.'.inc');
		elseif(file_exists($pathheader.$pathToClasses.'foot2019.inc'))
		include($pathheader.$pathToClasses.'foot2019.inc');	
		else echo 'footer is absent';
		}
	//Maket::closediv(1);//main_container-*/	
	//}
	//else {
	//	echo 'Режим настройки макета';
	//}
}
?>