<?php

echo '<div class="menu adm">';
	Maket::divclass($Maks_Page[8],$Pth,'margin: 10px;flex-direction: row;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around;flex',' flex');
		
		if($localdomen==='localhost')$user->stringusermen('user',$Pth,$db->init_data[0],$localpath);
		else $user->stringusermen('user',$Pth);
		//echo '<h2>Структура загруженного макета</h2>
		echo '</div>';
	echo '<div class="menu flex">';
	$resuB=$PageM->read_namparams('setEnvir',0);
	if(isset($_GET['envirS'])) foreach($resuB[1] as $key=>$val) $resuB[1][$key]=$resuB[1][$key].'&envirS';
	echo show::work_pages('serv',$Pth,$resuB,'./'.$graphp);
	echo '</div>';
	echo '</div>';
	echo '<hr>';
$mode_work = false;
if(!$mode_work && isset($_GET['envirS'])){
		
	//$envirSite = $mysite->getEnvirSite();
	if(isset($_GET['scriptS'])){
		echo '<h2>Загрузка скриптов</h2>';
		if(!is_array($envirSite['loaded']['js']))$envirSite['loaded']['js'][0]=$envirSite['loaded']['js'];
		for($i=0;$i<count( $envirSite['loaded']['js']);$i++){
			$scrjs[0][$i] = $envirSite['loaded']['js'][$i]->scripts;
			$scrjs[1][$i] = $envirSite['loaded']['js'][$i]->flag;
			$scrjs[2][$i] = $envirSite['loaded']['js'][$i]->Maket;
			if($scrjs[1][$i] === 'f')echo 'загружен локальный js-скрипт '.$scrjs[2][$i].'.js<br>';
			elseif($scrjs[1][$i] === 'h')echo 'загружен глобальный js-скрипт '.$scrjs[2][$i].'<br>';
		}
	}
elseif(isset($_GET['styleS'])){
	echo '<h2>CSS-стили подгружаемые на страницу</h2>';
	echo '<hr>';
	echo '<div>';
	$standart_style=$arrmain['idmen'][0];
	if($mode_edit)echo '<div>'.$type_access.' режим стилей установлен</div>';
	$style_Set[0]=$clas['img'].'settingsStyle.min.css';
	if(isset($Pth['global']['Bootstr'][0]))echo 'Подключены стили bootstrap<br>';
	if(isset($Pth['global']['Grid'][0]))echo 'Подключены стили smartgrid<br>';
	if($type_access=='global'){
		if($Style_page != '')echo 'Style_page ';print_r($Style_page);
	if($Style_page<>'' && file_exists($Style_page)) {
		if($mode_edit)echo '<div>добавлен local стили '.$Style_page.'</div>';
	}
	elseif (isset($Site->css)){
	if(strstr($Site->css,'|')){
		$spisok=$clas['img'].'/';
		$Style_Global=explode('|',$Site->css);
		if($Style_Global !=''){echo 'Style_Global ';print_r($Style_Global);}
	foreach($Style_Global as $val)	{
			if(file_exists($clas['img'].$val.'.min.css')&& $val<>''){
				echo $clas['img'].$val.'.min.css';
			}
			   if($val<>'')$spisok.='-'.$val;
	}
		if($mode_edit)echo '<div> стили макета'.$spisok.' загружены на сайт</div>';
	}
	elseif($Site->css<>'') {
		if($Site->css != ''){echo 'Style_Site ';print_r($Site->css);}
		if(file_exists($clas['img'].$Site->css.'.min.css'))echo '<div>глобальный стиль '. $clas['img'].$Site->css.' .min.css загружен на сайт</div>';
		else echo '<div>глобальный стиль '.$Site->css.'  не загружен на сайт</div>';
	}
	else {
		$Site->css='style'.$arrmain['idmen'][0];
		if(file_exists($clas['img'].$Site->css.'.min.css'))echo $clas['img'].$Site->css.'.min.css';
		else echo '<div>global стиль '.$Site->css.'  не загружен на сайт</div>';
		if($mode_edit)echo '<div>global стиль '.$Site->css.' загружен на сайт</div>';
	}	
}	
$style_Set[0]=$clas['img'].'settingsStyle.min.css';
}
if($type_access=='general') {
	if($Style_users !=''){echo 'Style_User ';print_r($Style_users);}
	if(isset($Style_users)){
	if(is_array($Style_users)){
	foreach($Style_users as $value) {
		//echo $value;
		if(file_exists($value)){
			if($mode_edit)echo '<div>загружен user стиль '.$value.'</div>';
		}
		//elseif($mode_edit) echo '<div>Не загружен general  стиль '.$value.'</div>';
		}
	}
	elseif ($Style_users <> '' && file_exists($Style_users[0])) {
		if($mode_edit)echo '<div>загружен general стиль '.$Style_users[0].'</div>';
	}
	elseif(file_exists($clas['img'].'style'.$standart_style[0].'.min.css')) {
		echo $clas['img'].'style'.$standart_style[0].'.min.css';
	}
	else {
		if($mode_edit)echo '<div>пользовательские стили не </div>';
		
		}
	}
	if($Style_page<>'' && file_exists($Style_page)) {
		if($mode_edit)echo '<div>добавлен page стиль'.$Style_page.'</div>';
	}
	}

	if($Style_page<>'' && file_exists($Style_page)){
		if($mode_edit)echo '<div>добавлен local '.$Style_page.' стиль </div>';
	}
	elseif($mode_edit) echo '<div>local стили '.$Style_page.' не загружены на сайт</div>';

	if(isset($Pth['global']['styles']) && !isset($style_Set[0]))$style_Set=$user->getstylesfiles($clas,$Pth['global']['styles'],6);
	else $style_Set[0]=$clas['img'].'settingsStyle.min.css';
	if($style_Set[0]<>'' && file_exists($style_Set[0])){
	
	if($mode_edit)echo '<div>также загружены на сайт стили настройки страниц администратора'.$style_Set[0].' </div>';
	}
	elseif($mode_edit) echo '<div>стили настройки   не загружены на сайт</div>';
	echo '</div>';
	if(is_array($envirSite['loaded']['css'])){
		for($i=0;$i<count( $envirSite['loaded']['css']);$i++){
			$scrjs[0][$i] = $envirSite['loaded']['css'][$i]->scripts;
			$scrjs[1][$i] = $envirSite['loaded']['css'][$i]->flag;
			$scrjs[2][$i] = $envirSite['loaded']['css'][$i]->Maket;
			$scrjs[3][$i] = $envirSite['loaded']['css'][$i]->needs;
			if($scrjs[3][$i] ==='us;nbl' ){
				if($scrjs[1][$i] === 'f')echo 'загружен локальный css-скрипт '.$scrjs[2][$i].'.js<br>';
				elseif($scrjs[1][$i] === 'h')echo 'загружен глобальный css-скрипт '.$scrjs[2][$i].'<br>';
			}
		}
	}
	else {
		$scrjs[0] = $envirSite['loaded']['css']->scripts;
			$scrjs[1] = $envirSite['loaded']['css']->flag;
			$scrjs[2] = $envirSite['loaded']['css']->Maket;
			$scrjs[3] = $envirSite['loaded']['css']->needs;
			if($scrjs[3] ==='us;nbl' ){
				if($scrjs[1] === 'f')echo 'загружен локальный css-скрипт '.$scrjs[2].'.js<br>';
				elseif($scrjs[1] === 'h')echo 'загружен глобальный css-скрипт '.$scrjs[2].'<br>';
			}
	}
}
else {
	echo 'Окружение сайта (файлы и библиотеки подгружаемые на страницу сайта)';
	echo $msw.'<br>';
	if(strstr($msw,'GLV')) echo $msw.'-set global version of page<br>';
	if(strstr($msw,'GEV')) echo $msw.'-set general version of page<br>';
	if(strstr($msw,'GEV')) echo $msw.'-set local version of page<br>';
	if(strstr($msw,'PSW')) echo $msw.'-loaded styles of this page<br>';
	if(strstr($msw,'BSW')) echo $msw.'-loaded libs styles<br>';
	if(strstr($msw,'GSW')) echo $msw.'-loaded global styles of this page<br>';
	if(strstr($msw,'GESW')) echo $msw.'-loaded general styles of this page<br>';
	if(strstr($msw,'USW')) echo $msw.'-loaded user styles of this page<br>';
	if(strstr($msw,'LSW')) echo $msw.'-loaded standart styles of this page<br>';
	if(strstr($msw,'MSW')) echo $msw.'-loaded main styles of this page<br>';
	if(strstr($msw,'SLSW')) echo $msw.'-loaded standart styles of this page<br>';
	if(strstr($msw,'SETSW')) echo $msw.'-loaded settings styles of this page<br>';
	
}
}
?>