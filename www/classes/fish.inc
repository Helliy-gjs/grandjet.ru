<?php
//print_r($arrconf); 

$contmak = array();
$contmak['clas']=$clas;
$contmak['nump']=1;
$contmak['tabl']=$tabl;
$contmak['descr']='description';
$contmak['titles']='titles';
$contmak['keywds']='keyword1>keyword2';
$contmak['idmen'][0]= 'flex';
$contmak['typmen'] =explode(';', 'wr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac');
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
$contmak['scripts']= '';
$contmak['style']= '';
for($i=2;$i<$arrconf['page']['sznames']+2;$i++) $contmak['namep'][] = 'Name_Page'.$i;
for($i=0;$i<$contmak['max']['loz'];$i++){
	$contmak['loz'][] = 'Your_lozung'.$i;
	$contmak['lozhref'][] = 1;
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
	$contmak['conthref'][] = 1;
}
for($i=0;$i<$contmak['max']['butt'];$i++){
	$contmak['butt'][] = 'Button'.$i;
	$contmak['butthref'][] = 1;
}
for($i=0;$i<$contmak['max']['list'];$i++){
	$contmak['list'][] = 'Menu item'.$i;
	$contmak['listhref'][] = 1;
}
for($i=0;$i<$contmak['max']['imgs'];$i++){
	if($i < 10)$contmak['imgs'][] = $i.'.jpg';
	elseif($i < 19) $contmak['imgs'][] = (19-$i).'.jpg';
	elseif($i <= 29) $contmak['imgs'][] = (29-$i).'.jpg';
	else break;

}
for($i=0;$i<$contmak['max']['buttimg'];$i++){
	if($i < 10)$contmak['buttimgs'][] = $i.'.jpg';
	elseif($i <= 19) $contmak['buttimg'][] = (19-$i).'.jpg';
	elseif($i <= 29) $contmak['buttimg'][] = (29-$i).'.jpg';
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
	$contmak['imgthref'][] = 1;
}
for($i=0;$i<$arrconf['page']['szfoots'];$i++){
	$contmak['foot'][] = 'Footer'.$i;
	$contmak['foothref'][] = 1;
}
//debug($contmak['max']['imgs']);
