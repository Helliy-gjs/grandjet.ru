<?php	
	echo 'Основные элементы макета<hr>';//commentecho
	
	if($YourMakets){
	print_r($YourMakets);
	echo '<hr>';
	echo 'Основные параметры макета<hr>';//commentecho
	print_r($Pth['global']);
	echo '<hr>';
	echo 'Масштабные коэффициенты изображений сайта<hr>';//commentecho
	if($type_access=='global'){
		print_r($Pth['global']['Pics']);
		$rasmer=$Pth['global']['Pics'];
		echo 'Ссылки редактирования масштабных коэффициентов изображений сайта <hr>';
		print_r($Pth['global']['numparams']['link']);
		$edlinkR=$Pth['global']['numparams']['link'];
		echo '<hr>';
		$tabp='allmakets';
		$fieldp='global';
	}
	else {
		print_r($Pth['main_container']['numpar']['Pics']);
		$rasmer=explode(';',$Pth['main_container']['numpar']['Pics']);
		echo '<hr>';
		echo 'Ссылки редактирования масштабных коэффициентов изображений сайта <hr>';
		print_r($Pth['main_container']['link_numpar']['Pics']);
		$edlinkR=explode(';',$Pth['main_container']['link_numpar']['Pics']);
		echo '<hr>';
		$tabp='maket';
		$fieldp='main_container';
	}
	
	echo '<hr>';
	
	echo 'Основные css-классы макета<hr>';//commentecho
	print_r($Maks_Page);
	echo '<hr>';
	echo 'изображения макета '.$type_access;//commentecho
	echo '<hr>';
	$Allpics=array($arrmain['namep'][0],$arrmain['namep'][1]);
	unset($arrmain['imgs']['link']);
	//print_r($arrmain['imgs']);
	foreach ($arrmain['imgs'] as $val)if($val)$Allpics[]=$val;
	//print_r($Allpics);
	//if($type_access=='global')
	$href='./?editp='.$edlinkR[0].'00&tab='.$tabp.'&par='.$Pth[$fieldp]['id'];	
	echo '<a href="javascript:new_window(\''.$href.'\')" title="Изменить размер">Размер баннера '.$rasmer[0].'...</a>';
	/*else echo '<a href="./?editp='.$edlinkR.'00&tab=maket&par='.$Pth['main_container']['id'].'" title="Изменить размер">Размер баннера '.$rasmer[0].'.....</a>';*/
	$href='./?editp='.$edlinkR[0].'00&tab='.$tabp.'&par='.$Pth[$fieldp]['id'];
	//echo '<form action="javascript:new_window(\''.$href.'\')" method="POST" enctype="multipart/form-data">';
	echo '<form action="'.$href.'" method="POST" enctype="multipart/form-data">';
	$pics='';
	foreach($Allpics as $key=>$val){
		Page::scalimag4($clas['img'].$val,$Pth,$clas,'header_banner','div',$Pth[$fieldp]['numpar']['Pics'][$key]);
		echo '<input type="text" size="2" name="3'.$key.'" value="'.$rasmer[$key].'">';	
	}
	echo '<input type="hidden" name="part" value="'.$edlinkR[0].'">';
	echo '<input type="submit" value="Записать">';
	echo '</form>';
	}
?>	