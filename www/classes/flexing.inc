<?php
if(!isset($nBut))$nBut=0;
$n_card=0;
$n_loz=0;
$n_cards=3;
$n_lozes=5;
$n_list=0;	
//print_r($arrmain);
Maket::divclass('main-wrapper-'.$disp,$Pth);
//echo 'Content flex page';
//echo '</div>';
/*
//Шапка страницы
$clas_modul=array('user','logo','serv','shop');
$logomod=Maket::scalimag3($arrmain,$arrmain['clas']['img'].$arrmain['namep'][1],'./?np='.$arrmain['nump'],$Pth,0);
$arr_modul=array($ownerdata,$logomod,$service,$shop);
$nmod=count($arr_modul);
Maket::divclass('#main_container',$Pth);
Maket::divclass('header ',$Pth,$arrmain['idmen'][0]);
Maket::showmodules($clas_modul,$Pth,$arr_modul,$arrmain['idmen'][0],$nmod);

//Блок кнопочного меню	
		

Maket::divclass('container_buttons ',$Pth,'',$arrmain['idmen'][0]);
$arr=$arrmain;
unset($arrmain['butt']['link']);
Maket::showdisplaybutton($arr,$Pth,'button','butt','div');
Maket::closediv(1);
//карточка элемнента
Maket::showlogo('items part-card',$arrmain,$Pth,2,$n_card,'imgt','butt',352);
//show::slidesh($arrmain,$clas,1);

//*/
echo '<div class="wrapper flex">';
echo '<div class="sidebarL flex">';
	echo '<div class="container-U flex">';
	if($arrmain['imgt'][$n_loz+1]) echo show::showlogo('part5-h2',$arrmain,$Pth,3,$n_loz+1,'','loz');
	for($i=$n_card;$i<$n_cards;$i++)echo show::showlogo('items part-card',$arrmain,$Pth,2,$i,'cont','cont',351);
	echo '</div><div class="container-P flex">';
	if($arrmain['cont'][$n_loz+2])echo show::showlogo('part5',$arrmain,$Pth,3,$n_loz+2,'','loz');
	for($i=$n_card;$i<$n_cards;$i++)echo show::showlogo('items part-card',$arrmain,$Pth,2,$i,'cont','imgt',351);	
	echo '</div>';

echo '<div class="smalldevice">';
if($arrmain['cont'][$n_loz+2])echo show::showlogo('part5',$arrmain,$Pth,3,$n_loz+2,'','loz');
	for($i=$n_card;$i<$n_cards;$i++)echo show::showlogo('items part-card',$arrmain,$Pth,2,$i,'cont','cont',351);	
echo '</div>';

Maket::divclass('underfoot',$Pth);
echo show::showlogo('5-h2',$arrmain,$Pth,3,$n_loz,'','loz');
unset($arrmain['list']['link']);
Maket::showdisplaymenu($arr,$Pth,'ufitem','list','div');
$arr_pics=array(0=>$arrmain['clas']['img'].'house.gif');
//echo show::showlogo('banner',$arr_pics,$Pth,1);
echo '</div>';
Maket::closediv(1);//sidebarL
Maket::divclass('container-U',$Pth,'',' flex');
echo show::showlogo('5-h2',$arrmain,$Pth,3,$n_loz+1,'','loz');
for($i=$n_card;$i<$n_cards;$i++)echo show::showlogo('items part-card',$arrmain,$Pth,2,$i,'','imgt',351);
if($arrmain['cont'][$n_loz+2])echo show::showlogo('part6',$arrmain,$Pth,3,$n_loz+2,'','loz');
for($i=$n_card;$i<$n_cards;$i++)echo show::showlogo('items part-card',$arrmain,$Pth,2,$i,'cont','imgt',351);	
for($i=$n_card;$i<$n_cards;$i++)echo show::showlogo('items part-card',$arrmain,$Pth,2,$i,'cont','cont',351);	
echo show::showlogo('1-h2',$arrmain,$Pth,3,$n_loz+2,'','loz');
Maket::divclass('container-U',$Pth,'',' flex');
Maket::divclass('upitems',$Pth,'',' flex');
Maket::divclass('underfoot',$Pth,'',' flex');
//print_r($arrmain['list']);
for($i=0;$i<count($arrmain['list']);$i++) {
	if ($arrmain['idmen'][0] <> 'land') {
		$buthref='./?np='.$arrmain['listhref'][$i];	
				}
	else {
		$buthref='#zak'.$i;
	}
	if($arrmain['list'][$i]<>'')Maket::spanclass('<a href="'.$buthref.'"> '.$arrmain['list'][$i].'</a>',$Pth,'ufitem','div');
}
Maket::closediv(1);
Maket::spanclass('<a href=""><img class="banner" src="./images/house.gif"></a>',$Pth,'banner','div');
		
//$n_cards=4;
//for($i=$n_card;$i<$n_cards;$i++) Maket::showlogo('items part-text',$arrmain,$Pth,4,$i,'imgt','butt',500);
echo '</div>';//upitems
//Maket::showlogo('zag1-h3',$arrmain,$Pth,3,$n_list,'','list');
echo Maket::divclasstr('container-P',$Pth,'',' portfolio  flex');
echo Maket::divclasstr('portfolio',$Pth,'',' flex','section');
echo Maket::divclasstr('portfolio_item',$Pth,'',' flex');
echo Maket::divclasstr('portfolio-item',$Pth,'background-image:url(./images/4.jpg);');

echo '</div>';//portfolio-item
echo '</div>';//portfolio_item
echo Maket::divclasstr('portfolio_item',$Pth,'',' flex');
echo Maket::divclasstr('portfolio-item',$Pth,'background-image:url(./images/4.jpg);');

echo '</div>';//portfolio-item
echo '</div>';//portfolio_item
echo '</section>';//portfolio

echo '</div>';//container-P
echo Maket::divclasstr('container-P',$Pth,'',' portfolio  flex');
echo Maket::divclasstr('portfolio',$Pth,'',' flex','section');
for($i=0;$i<count($arrmain['imgs']);$i++) {
	echo Maket::divclasstr('portfolio_item',$Pth,'',' flex');
	if($arrmain['imgs'][$i]<>''){
		if(!isset($_GET['konstrS']))
			echo Maket::divclasstr('portfolio-item',$Pth,'background-image:url(./images/'.$arrmain['imgs'][$i]).'</div>';
		else {
			echo '<div>'.$arrmain['link']['imgs'][$i].Maket::divclasstr('portfolio-item',$Pth,'background-image:url(./images/'.$arrmain['imgs'][$i]).'</div></div>';
		}
	}
	
	echo '</div>';//portfolio_item
}	
echo '</div>';//portfolio-item
echo '</section>';//portfolio
echo '</div>';//container-P
echo '</div>';//container-U
echo '</div>';//container
if(isset($arrmain['imgt'][$n_card]) && $arrmain['imgt'][$n_card]<>''){
	echo Maket::divclasstr('sidebarL',$Pth,'',' bigdevice');
	for($i=$n_card;$i<$n_cards;$i++)echo show::showlogo('items part-card',$arrmain,$Pth,2,$i,'cont','cont','imgt',351);
	Maket::closediv(1);//sidebarL bigdevice
}	
Maket::closediv(1);//wrapper*/
?>