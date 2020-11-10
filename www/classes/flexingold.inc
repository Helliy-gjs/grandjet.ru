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

echo '<div class="wrapper flex">';
echo '<div class="sidebarL flex">';
	echo '<div class="container-U flex">';
	if($arrmain['imgt'][$n_loz+1])Maket::showlogo('part5',$arrmain,$Pth,3,$n_loz+1,'','loz');
	/*for($i=$n_card;$i<$n_cards;$i++)Maket::showlogo('items part-card',$arrmain,$Pth,2,$i,'imgt','butt',351);
	echo '</div><div class="container-P flex">';
	if($arrmain['cont'][$n_loz+2])Maket::showlogo('part5',$arrmain,$Pth,3,$n_loz+2,'','loz');
	for($i=$n_card;$i<$n_cards;$i++)Maket::showlogo('items part-card',$arrmain,$Pth,2,$i,'cont','butt',351);*/	
	echo '</div>';

echo '<div class="smalldevice">';
if($arrmain['cont'][$n_loz+2])Maket::showlogo('part5',$arrmain,$Pth,3,$n_loz+2,'','loz');
	for($i=$n_card;$i<$n_cards;$i++)Maket::showlogo('items part-card',$arrmain,$Pth,2,$i,'','imgt',351);	
echo '</div>';

Maket::divclass('underfoot',$Pth);
Maket::showlogo('5-h2',$arrmain,$Pth,3,$n_loz,'','loz');
unset($arrmain['list']['link']);
Maket::showdisplaymenu($arr,$Pth,'ufitem','list','div');
$arr_pics=array(0=>$arrmain['clas']['img'].'house.gif');
Maket::showlogo('banner',$arr_pics,$Pth,1);
echo '</div>';
Maket::closediv(1);//sidebarL
Maket::divclass('container-U',$Pth,'',' flex');
Maket::showlogo('5-h2',$arrmain,$Pth,3,$n_loz+1,'','loz');
for($i=$n_card;$i<$n_cards;$i++)Maket::showlogo('items part-card',$arrmain,$Pth,2,$i,'','imgt',351);
if($arrmain['cont'][$n_loz+2])Maket::showlogo('part6',$arrmain,$Pth,3,$n_loz+2,'','loz');
for($i=$n_card;$i<$n_cards;$i++)Maket::showlogo('items part-card',$arrmain,$Pth,2,$i,'','imgt',351);	
for($i=$n_card;$i<$n_cards;$i++)Maket::showlogo('items part-card',$arrmain,$Pth,2,$i,'','imgt',351);	
Maket::showlogo('1-h2',$arrmain,$Pth,3,$n_loz+2,'','loz');
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
Maket::divclass('container-P',$Pth,'',' portfolio  flex');
Maket::divclass('portfolio',$Pth,'',' flex','section');
Maket::divclass('portfolio_item',$Pth,'',' flex');
Maket::divclass('portfolio-item',$Pth,'background-image:url(./images/4.jpg);');
echo '</div>';//portfolio-item
echo '</div>';//portfolio_item
//print_r($arrmain['imgs']);
//if(isset($arrmain['link']['imgs']))print_r($arrmain['link']['imgs']);
for($i=0;$i<count($arrmain['imgs']);$i++) {
	Maket::divclass('portfolio_item',$Pth,'',' flex');
	if($arrmain['imgs'][$i]<>''){
		if(!isset($_GET['konstrS']))
			Maket::divclass('portfolio-item',$Pth,'background-image:url(./images/'.$arrmain['imgs'][$i].');').Maket::divclass('portfolio-item',$Pth,'background-image:url(./images/'.$arrmain['imgs'][$i].');');
		else {
			echo '<div>'.$arrmain['link']['imgs'][$i].Maket::divclasstr('portfolio-item',$Pth,'background-image:url(./images/'.$arrmain['imgs'][$i].');').Maket::divclasstr('portfolio-item',$Pth,'background-image:url(./images/'.$arrmain['imgs'][$i].');');'</div>';
		}
	}
	echo '</div>';//portfolio-item
	echo '</div>';//portfolio_item
}	

echo '</section>';//portfolio
echo '</div>';//container-P
echo '</div>';//container-U
//echo '</div>';//container
if(isset($arrmain['imgt'][$n_card]) && $arrmain['imgt'][$n_card]<>''){
	Maket::divclass('sidebarL',$Pth,'',' bigdevice');
	for($i=$n_card;$i<$n_cards;$i++)Maket::showlogo('items part-card',$arrmain,$Pth,2,$i,'','imgt',351);
	Maket::closediv(1);//sidebarL bigdevice
}	
Maket::closediv(1);//wrapper*/
Maket::closediv(1);//main-wrapper-*/
?>