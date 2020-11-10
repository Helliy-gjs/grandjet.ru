<?php
//Загрузка топологического макета сайта пользователя
$ownerdata=' Дата '.' Имя '.' Телефон '.'Email ';
$service='Настройки На стартовую Выйти';
$style='border: 2px solid grey;color:white;';
$numelem=$user->getscountab($tabl['elem'],'id','c');
if ($numelem==0) $arrmain['typmen'][5]== 'nbf';
Maket::divclass($Maks_Page[0],$Pth,'color:#fff;background: #999;height:100vh;');//divC
if ($arrmain['typmen'][4] == 'nhd') {
	Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,$style,' grid');
	echo Maket::divclasstr($Maks_Page[8],$Pth,$style).$ownerdata.$service;
	echo '</div></div>';
	}
elseif($arrmain['idmen'][0]=='land') {
	
	Maket::divclass($Maks_Page[1],$Pth,$style.'background-image: url('.$img.');',' grid','header');
	Maket::showmaketempty($arrmain,$ownerdata,$service,$Pth,$Maks_Page,$style);
	Maket::divclass($Maks_Page[8],$Pth,$style);
	//Зона основного горизонального меню под  хедером
	if ($arrmain['typmen'][2] == 'bt') echo ' Кнопка '.' Кнопка '.' Кнопка '.' Кнопка ';
	elseif($arrmain['typmen'][1] == 'mn') echo ' текст меню '.' текст меню '.' текст меню '.' текст меню ';
	elseif($arrmain['typmen'][6]<>'sw') echo 'Картинки аккордионом';
	else echo ' Картинки слайдером ';
	echo '</div>';
}
elseif($arrmain['idmen'][0]=='cont')	{
	echo 'Макет контекстного сайта хедер';
	Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,'',' grid','header');
	Maket::showmaketempty($arrmain,$ownerdata,$service,$Pth,$Maks_Page,$style);	
}
elseif($arrmain['idmen'][0]=='gall')	{
	$arrmain['typmen'][4]='nhd';
	echo 'Макет сайт-галлерея (хедер отключен, даже если установлен включенным)';
}
elseif($arrmain['idmen'][0]=='blog')	{
	echo 'Макет сайт-блог хедер';
	Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,'',' grid','header');
	echo Maket::divclasstr($Maks_Page[8],$Pth,$style).$ownerdata;
	echo '</div></div>';
}
elseif($arrmain['idmen'][0]=='mag')	{
	echo 'Макет сайт-магия хедер';
	Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,'',' grid','header');
	Maket::showmaketempty($arrmain,$ownerdata,$service,$Pth,$Maks_Page,$style);	
}
elseif($arrmain['idmen'][0]=='cat')	{
	echo 'Макет сайт-магия хедер';
	Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,'',' grid','header');
	Maket::showmaketempty($arrmain,$ownerdata,$service,$Pth,$Maks_Page,$style);	
}

echo '</header>';
if ($arrmain['typmen'][0]== 'bl'){
	//include($pathheader.$pathToClasses.$arrmain['idmen'][0].'ing.inc');
	echo '<span><h1>Основной заголовок</h1></span>';
	$i=0;
	Maket::divclass($clas['clas'][1],$Pth,'',' grid');
	Maket::divclass($clas['clas'][7].'-left',$Pth,'',' sidebarL');
	Maket::showitemsmaket($arrmain,$Pth,$i,0);
	echo '</div>';
	Maket::divclass($clas['clas'][7].'-left',$Pth,'',' sidebarC');
	Maket::showitemsmaket($arrmain,$Pth,$i,0);
	echo '</div>';
	Maket::divclass($clas['clas'][7].'-right',$Pth,'',' sidebarR');
	Maket::showitemsmaket($arrmain,$Pth,$i,0);
	echo '</div>';	
	echo '</div>';
}

echo '</div>';//divC
?>