<?php

require_once('check.inc');
//require_once($_SERVER["DOCUMENT_ROOT"].'/ajax/check.inc');

header("Content-type: text/xml; charset=UTF-8");
header("Cache-Control: no-store, no-cache, must-revalidate");
header("Cache-Control: post-check=0, pre-check=0", false);
echo '<?xml version="1.0" encoding="UTF-8"?>';

if(isset($_POST['id']) && isset($_POST['sortType']) && isset($_POST['sortOrder'])&& isset($_POST['tabl'])) {
	echo '<ss>';
	echo $_POST['id'];
	$sw = Singleton::getInstance('StructureW');
	$arr = $sw->getData($_POST['id'],$_POST['tabl'],1,1);
	$ar = $arr['sections'];
	if($_POST['tabl']==='elemap')
		foreach($ar as $val) {
		echo '<s id="'.$val['id'].'">'.htmlspecialchars($val['name']).'</s>';	
	}
	else 
	foreach($ar as $val) {
		echo '<s id="'.$val['id'].'">'.htmlspecialchars($val['name'].' ('.$val['numEl'].')').'</s>';	
	}
	if($arr['this']['typeF'] == 1) {
		$ew = Singleton::getInstance('ElementsW');
		$arr = $ew->getData($_POST['id'], $_POST['sortType'], $_POST['sortOrder'],$_POST['tabl']);
		foreach($arr as $val) {
			echo '<e id="'.$val['id'].'" art="'.$val['art'].'" price="'.$val['price'].'" ms="'.$val['ms'].'" stock="'.$val['stock'].'" ls="'.$val['ls'].'" codeGJS="'.$val['codeGJS'].'" desc="'.$val['desc'].'" date2="'.$val['date2'].'">'.htmlspecialchars($val['name']).'</e>';
		}
	}	
	echo '<id>'.$_POST['id'].'</id>';
	echo '</ss>';
} else {
	echo '<error></error>';
}

?>