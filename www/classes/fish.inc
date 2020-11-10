<?php
//print_r($arrconf['szimggrp']); 

$contmak = array();
$contmak['clas']=$clas;
$contmak['nump']=$allpage;
$contmak['tabl']=$tabl;
$contmak['descr']='description';
$contmak['titles']='titles';
$contmak['keywds']='keyword1>keyword2';
$contmak['idmen'][0]=$disp;
$contmak['typmen']=$distype;
$contmak['namep'][0] = $Bannrpic;;
$contmak['namep'][1] = $Logopic;
$contmak['max']['imgs']=$arrconf['page']['szimggrp']*$arrconf['page']['szimg'];
$contmak['max']['imgt']=$arrconf['page']['szimgtxtgrp']*$arrconf['page']['szimgtexts'];
$contmak['max']['list'] = $arrconf['page']['szlistgrp']*$arrconf['page']['szlists'];
$contmak['max']['butt'] = $arrconf['page']['szbutgrp']*$arrconf['page']['szbuttons'];
$contmak['max']['buttimg'] = $arrconf['page']['szimgbutgrp']*$arrconf['page']['szimgbut'];
$contmak['max']['cont'] = $arrconf['page']['szcontgrp']*$arrconf['page']['szconts'];
$contmak['max']['loz'] = $arrconf['page']['szlozs'];
$contmak['max']['foot'] = $arrconf['page']['szfoots'];

for($i=2;$i<$arrconf['page']['sznames']+2;$i++) $contmak['namep'][] = 'Name_Page'.$i;
for($i=0;$i<$contmak['max']['loz'];$i++){
	$contmak['loz'][] = 'Your_lozung'.$i;
	$contmak['lozhref'][] = $startpage;
}
$string['cont']=20;
$string['imgt']=10;
$str='';
$strings = 'Loremq Yuo NastoHej. Iuohjjre Forg';
for($i=0;$i<$string['cont'];$i++){
	$strng=substr($strings,rand(0+$i,7+$i),rand(4+$i,18+$i));
	$str.=' '.$strng;							
}
for($i=0;$i<$contmak['max']['cont'] ;$i++){
	$contmak['cont'][] = $str;
	$contmak['conthref'][] = $startpage;
}
for($i=0;$i<$contmak['max']['butt'];$i++){
	$contmak['butt'][] = 'Button'.$i;
	$contmak['butthref'][] = $startpage;
}
for($i=0;$i<$contmak['max']['list'];$i++){
	$contmak['list'][] = 'Menu item'.$i;
	$contmak['listhref'][] = $startpage;
}
for($i=0;$i<$contmak['max']['imgs'];$i++){
	if($i < 10)$contmak['imgs'][] =$clas['img']. $i.'.jpg';
	elseif($i <= 20) $contmak['imgs'][] = $clas['img'].(20-$i).'.jpg';
	elseif($i <= 30) $contmak['imgs'][] = $clas['img'].(30-$i).'.jpg';
	else break;

}
for($i=0;$i<$contmak['max']['buttimg'];$i++){
	if($i < 10)$contmak['buttimgs'][] = $clas['img'].$i.'.jpg';
	elseif($i <= 20) $contmak['buttimg'][] = $clas['img'].(20-$i).'.jpg';
	elseif($i <= 30) $contmak['buttimg'][] = $clas['img'].(30-$i).'.jpg';
	else break;
}
$str='';
$strings = 'Moder Kuogth lastoler. Yomju torg';
for($i=0;$i<$string['imgt'];$i++){
	$strng=substr($strings,rand(0+$i,6+$i),rand(1+$i,9+$i));
	$str.=' '.$strng;							
}
for($i=0;$i<$contmak['max']['imgt'];$i++){
	$contmak['imgt'][] = $str;
	$contmak['imgthref'][] = $startpage;
}
for($i=0;$i<$arrconf['page']['szfoots'];$i++){
	$contmak['foot'][] = 'Footer'.$i;
	$contmak['foothref'][] = $startpage;
}