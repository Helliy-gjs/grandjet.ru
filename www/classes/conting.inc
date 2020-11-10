<?php
//$a_link  = show::a_link($arrmain);
//$arrmain = page::readyadmarr($arrmain);


//автономный блок поиска по элементам таблицы elements

if(isset($_POST['vend'])) $vend=$_POST['vend'];
else $vend='';
if ($poisk<>'' && $arrmain['typmen'][5]<> 'nfb') {
	
	echo '<div style="clear: both;" class="s10">';
	$a=$ew->viewertab($ew->getlookfortab($poisk,$vend, $tabl['elem']),$sort=1,$vend,$tabl['elem']);
	echo '</div>';// s5	
}
else {//автономный блок вывода структурированой информации structure
		//$ew->result_find_group($tid,$vend);
		if ($ew->gettF($tid)==1) $a=$ew->viewer($ew->viewertid($tid),$sort=1,$vend,$user->getLevel());
			else {
				if ($tid<>0){
					echo '<td class="zag2">'.$ew->getnameSection($tid).'</td></tr>';
				}
	}

if ($arrmain['typmen'][2]=== 'mn'){
	//echo 'menu';
	Maket::divclass($Maks_Page[2],$Pth,'',' grid');
	Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,'',' grid');
	
	show::showallmenu($mode_work,$arrmain,$Pth,'butt');
	echo '</div></div>';
}
elseif($arrmain['typmen'][3]<> 'bt') {
	//Maket::carousel($arrmain,$Pth,0,0);
	 
	if($arrmain['typmen'][7] === 'sw') show::showallmenu($arrmain,$Pth);
	else show::simple_adap_menu($arrmain,'butt',$Pth);
	
}
elseif($arrmain['typmen'][3]=== 'bt') {
	show::menush($arrmain,$Pth,'butt');
}
//else echo 'no menu';
$nl=0;
$nc=$nl+1;


echo '<div class="'.$clas['clas'][20].'" style="text-align: center">';
if (isset($arrmain['link']['loz'][$nl])){
	if($a_link['loz'][$nl]) echo '<span ><h2 class="edit">'.$arrmain['loz'][$nl+1].$a_link['loz'][$nl+1].'</h2></span>'; 
}
else echo '<span><h3>'.$arrmain['loz'][$nl+1].'</h3></span>';
echo '</div>';

Maket::divclass($clas['clas'][9].'-'.$clas['clas'][7],$Pth,'',' '.$arrmain['idmen'][0].'','section');
Maket::divclass($clas['clas'][1].' '.$arrmain['idmen'][0],$Pth,'','');
Maket::divclass($clas['clas'][7].'-left',$Pth,'',' sidebarL');
Maket::showitemsmaket($arrmain,$Pth,0,1);
echo '</div>';
Maket::divclass($clas['clas'][7].'-right',$Pth,'',' sidebarR');
Maket::showitemsmaket($arrmain,$Pth,0,3);
echo '</div>';


echo '</div>';
echo '</section>';
//$nc=$i;

}	
?>