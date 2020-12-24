<?php
if($type_access === 'local')$img=$arrmain['clas']['img'].$arrmain['namep'][0];
	else $img=$arrmain['clas']['img'].$Bannrpic;
echo '<div class="menu adm">';
	Maket::divclass($Maks_Page[8],$Pth,'margin: 10px;flex-direction: row;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around;flex',' flex');
		
		$user->stringusermen('user',$Pth,$db->init_data[0],$localpath,$numpage);
		
		echo '</div>';
	echo '<div class="menu flex">';
	$resuB=$PageM->read_namparams('setMaket',0);
	
	if(isset($_GET['maketS'])) foreach($resuB[1] as $key=>$val) $resuB[1][$key]=$resuB[1][$key].'&maketS';
	echo show::work_pages('serv',$Pth,$resuB,'./'.$graphp);
	echo '</div>';
	echo '</div>';
	echo '<hr>';

$YourMakets=$sw->allmakets($Site->ids);	

if(!$mode_work && isset($_GET['maketS']) && isset($_GET['info']) ){
	echo 'Основные элементы макета<hr>';//commentecho
	
	echo '<table style="color:#027; background-color: #999;" ><tr>';
	echo '<td colspan="7" style="text-align: center;"><h2>Параметры сайта</h2></td></tr><tr>';
	echo '<td>Данные сайта '.$Site->domen.'</td><td>Владелец сайта '.$Owner_site->name.'</td><td>зарегистрирован '.date('Y-m-dH:i:s', $user->idCust($cid)->time).'</td><td>Режим '.$type_access.'</td><td>Банер сайта '.$picsglb[1].'</td><td>Логотип сайта '.$picsglb[0].'</td><td>Страница '.$numpage.'('.$startpage.')</td></tr>';
if(isset($Site)){
	echo '<tr>';
	echo '<td colspan="7"><p>глобальные свойства данных</p>';
	$ew->Showobjtab($Site,2,5); 
	echo '</td></tr>';
	echo '<tr>';
	echo '<td colspan="7"><p>локальные свойства данных</p>';
	$ew->Showobjtab($PageM,2,5); 
	echo '</td></tr>';
	echo '<tr>';
	echo '<td colspan="7"><p>свойства макета</p>';
	echo '<tr><td colspan="2"><p>тип </p></td><td>'.$Site->strucs.'</td><td>'.$Site->types.'</td><td>'.$Site->appoint.'</td>';
	echo '<td colspan="2"><p>'.$idmakets[0]['Maket'].'</p></td></tr>';
	echo '<tr><td colspan="7"><p>глобальные классы </p></td></tr>';
	$ew->Showobjtab($Maks_Page,2,5); 
	echo '</td></tr>';
}

$i=0;
foreach($Pth as $key=>$val) {
	if($val){
		echo '<tr><td colspan="7">'.$key.'['.$i.']</td></tr>';
		$ew->Showobjtab($val,2,5);
		echo '</td></tr>';
		$i++;
	}
 }
echo '</td>';
echo '</tr><table>';
}
else {
	
	$content['Wleft']='Content wrapper left sidebar';
	$content['Wcentr']='Content wrapper centr sidebar';
	$content['Wright']='Content wrapper right sidebar';
	$content['Sleft']='Content Sidebar left sidebar';
	$content['Scentr']='Content Sidebar centr sidebar';
	$content['Sright']='Content Sidebar right sidebar';
	$content['subhead']='Content subhead';
	//$Maks_Page =array('main_container','#main-header','#main_menu','main_wrapper','sidebareL','sidebareR','sidebareC','wrapper','header-button','poisk','swpr','main_footer','sechead','edit','menu','menudown','item','header-content','form','button','headline','logo','user','serv','shop','admin','main_banner','social');
	foreach($Maks_Page as $key=>$val){
		$MP[$key]=$val.'-'.$arrmain['idmen'][0];
		
	}
	print_r($Maks_Page);
	
	if(isset($Pth[$MP[0]][5])){
		if($Pth[$MP[0]][5] > 0) $prefix=' grid';
		elseif($Pth[$MP[0]][5]==0 && $arrmain['idmen'][0]=='flex')$prefix=' flex';
	}
	else $prefix='';
	//print_r($MP);
	$main_mod_typ=$MP;
	//$main_mod_typ=array(0=>'spisokUL',1=>'blockHd',2=>'blockUs',3=>'blockSr',4=>'blockAd',5=>'blockSh',6=>'blockBt',7=>'blockMn',8=>'blockSw',9=>'blockCd',10=>'blockFm',11=>'blockPf',12=>'blockGl',13=>'blockCt',14=>'blockBl',15=>'blockNw',16=>'blockAc',17=>'blockFd',18=>'blockBs',19=>'blockOr',20=>'blockTx',21=>'blockFt',22=>'blockLg');
	//$main_mod_typ=array(0=>'spisokUL',1=>'Header',2=>'blockUs',3=>'SidebarR',4=>'blockAd',5=>'blockSh',6=>'Buttons',7=>'Menu',8=>'Slider',9=>'Catalog',10=>'Form',11=>'blockPf',12=>'Galary',13=>'Content',14=>'Blog',15=>'news',16=>'Accordion',17=>'blockFd',18=>'Basket',19=>'Order',20=>'Txt',21=>'Footer',22=>'logo');
	$name_makets=array('Контейнер сайта','Контейнер хедера ','Контейнер меню и кнопок','Контейнер wrapper контента','Контейнер левого сайдбара','Контейнер правого сайдбара','Контейнер основного конттента','Wrapper контайнер','Button контайнер','Контейнер блока поиска','Контейнер слайдера','Контейнер футера','Header контайнер','Edit контейнер','Menu контайнер','Menudown контайнер','Option контайнер',' Контайнер заголовка контента','Контейнер формы','Контейнер кнопки','Контейнер разделителя','Контейнер лого','Контейнер пользователя','Контейнер сервиса','Контейнер магазина','Контейнер админа','Контейнер основного банера','Контейнер соцсетей');
	
if(isset($_GET))	{
include_once($pathheader.$pathToClasses.$arrmain['idmen'][0].'mak.inc');
}
}