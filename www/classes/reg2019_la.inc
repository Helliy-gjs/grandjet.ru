<?php
//header for land type
// Layout$Bannrpic

//print_r(show::a_link($arrmain));
$prefix=' grid';
$arr_head = array('user-land','logo-land','serv-land','shop-land','poisk-land');
for($i=0;$i<$arrconf['szbuttons'];$i++)if(isset($arrmain['butt'][$i]))$arr_butt[$i] = $arrmain['butt'][$i];
for($i;$i<$arrconf['szconts'];$i++)$arr_cont[$i] = $arrmain['cont'][$i];

$content[0]['cont'] = '<a href="/">This is header of site</a>';
if($arrmain['typmen'][4] === 'hd')$content[0]['cont'] = show::layoutheaderland($MP,$Pth,$arr_head);
else $content[0]['cont'] = '';

$content[0]['cont'].=Maket::spanclasstr(show::showlogo('zag-h1',$arrmain,$Pth,3,0,'lozhref','loz',0,$disp),$Pth,$MP[8],'div','','',$prefix);

$content[0]['img'] = $img;
$content[0]['clas'] = $MP[1];
$content[0]['height'] = 6;
$content[0]['opac'] = 0.82;
$content[0]['styl']='color: #fff; background-color:#000 ;opacity: 1;z-index: 1;';



show::layoutshadow('header',$content[0],$Pth,$arrmain['idmen'][0]);