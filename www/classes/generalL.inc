<?php
$d="SELECT `id`, `Maket`, `scripts`, `flag` ,`type`,`needs` FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni";
	$scrs=$db->query($d,$YourMakets[0][11],$YourMakets[0][0]);
	print_r($scrs);
	foreach($scrs as $val)	{
		if($val->type === 'js')$Scrpt_libs[] = $val->scripts;
		if($val->type === 'css')$Style_libs[] = $val->scripts;
	}
	//print_r($arrmain['style']);
	$Scrpt_page = $arrmain['scripts'];	
	$Style_pages = $arrmain['style'];

?>
<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8" />
	<title><?=$arrmain['titles']?></title>
	<meta http-equiv="X-UA-Compatible" content="IE=edge" />
	<meta name="viewport" content="width=device-width, initial-scale=1.0" />
	<link rel="shortcut icon" href="favicon.png" />
	<?php
//!Подключение css окружения

if(is_array($Style_libs)){
	foreach($Style_libs as $value){
		if($value && file_exists($pathheader.'/'.$scripts.'/'.$value.'.css')) echo '<link rel="stylesheet" href="'.$scripts.'/'.$value.'.css" />';
		//else echo $pathheader.'/'.$scripts.'/'.$value.'.css';
	}
}
if(is_array($Style_pages)){
foreach($Style_pages as $value){
	if($value && file_exists('css/'.$value.'.css')) echo '<link rel="stylesheet" href="css/'.$value.'.css" />';
	//else echo 'css/'.$value.'.css';
	}
}
show::showLandPersonal($arrmain,$Pth,$YourMakets,$db);
if($pgExist && file_exists(CLASSES.'/Jscripts.inc'))include(CLASSES.'/Jscripts.inc');	