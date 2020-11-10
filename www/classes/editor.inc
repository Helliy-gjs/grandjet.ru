<?php
if (!$_POST['rec']) {
	
$c=32;
$r=3;
$s=40;
$m=50;
$t=1;
$lpg=$user->getscountab($tabl['pages'],'numpage', 'f');//последняя страница в pages	
	$res1=$db->query('SELECT * FROM '.$tabl["pages"].' WHERE `numpage`=^Ni;',$numpage);
	$l=0;
	foreach($res1 as $val){
	$array[$l]=$val;
	$l++;
	}
	$l=0;
	$res2=$db->query('SELECT * FROM `namparams` WHERE `codparams`=^Ni;',1);
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrname=explode('|',$arrnm);
	$arrtype=explode('|',$arrtp);
	$arrname[]='Домен';
	$arrtype[]=200;	/*
echo '<form id="edit" action="./'.$PageM->MainAr["hrefp"].'?editp=yes" method="post">';
    echo '<h1> Редактор </h1><table class="inp">';
    echo '<tr>';
	for ($k=0;$k<count($arrname)-2;$k++) {
		echo '<td class="r"><label>'.$arrname[$k].'</label></td>';
		if ($arrtype[$k] === 'text')
		echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.'" tabindex="'.$k.'" >'.htmlspecialchars($array[$k]).'</textarea></td>';
		else 
		echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.'" type="text" tabindex="1" maxlength="'.$m.'" value="'.htmlspecialchars($array[$k]).'"></td>';
	$l++;
	if ($l>$t) {$l=0; echo '</tr>';}
	}
	echo '<tr><td class="r"><label>'.$arrname[$k].'</label></td>';
	echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.'" type="text" tabindex="1" maxlength="'.$m.'" value="'.$domen.'"></td></tr>';
	echo '</table>';
	echo '<input name="rec" value="true" type="hidden"><input id="regBut" type="submit"  tabindex="7" value=" Записать " />';
	echo '</form>';*/
$sw->editTBD($arrname,$arrtype,$array,50,3,50,50,1);
	}
else {
	echo 'post ';
	print_r($_POST);
	$db=Singleton::getInstance('DB');
	/*$db->query('UPDATE '.$tabl["pages"].' SET `namep`='.$_POST[1].',`lozung`='.$_POST[2].'
		,`keywards`='.$_POST[3].' ,`buttons`='.$_POST[4].' ,`hrefp`='.$_POST[5].'
		,`typemenu`='.$_POST[6].',`hrefscripts`='.$_POST[7].',`hrefstyle`='.$_POST[8].' 
		,`title`='.$_POST[9].',`content`='.$_POST[10].' ,`idmenu`='.$_POST[11].' ,`levelmenu`='.$_POST[12].'
		,`hrefimage`='.$_POST[13].',`list`='.$_POST[14].',`list_href`='.$_POST[15].'
		,`buthref`='.$_POST[16].' ,`butimg`='.$_POST[17].' ,`imgtext`='.$_POST[18].'
		,`idnews`='.$_POST[19].',`site`='.$_POST[20].' WHERE `numpage`=^Ni;',$_POST[0]);*/
echo '<form id="edit" action="./'.$PageM->MainAr["hrefp"].'" method="post">';
		echo '<input name="rec" value="false" type="hidden"><input id="regBut" type="submit"  tabindex="7" value=" Готово " />';
echo '</form>';		
		}
?>