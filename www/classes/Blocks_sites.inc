<?php
//if(!$mode_work && isset($_GET['blockS']) ) echo 'Основные элементы топологии<hr>';//comment
//Основные информационные блоки сайта
//блок инфоримации о пользователе
//print_r($PageM->MainAr['buttons']);
//print_r($arrmain);
$resuB=$PageM->read_namparams('setPageBlockS',0);
//$resuB[0]=$resuB[1];

if(isset($_GET['blockS'])) foreach($resuB[1] as $key=>$val) $resuB[1][$key]=$resuB[1][$key].'&blockS';

//Maket::icon_button('cont hidyes','fa fa-bars','div','');
echo '<div class="menu flex">';
echo show::work_pages('serv',$Pth,$resuB,'./'.$graphp);
echo '</div>';
Maket::divclass('menu '.$arrmain['idmen'][0],$Pth,'',' flex');
if (!isset($_GET['editp'])){
		if($Site->types<>5) {
			
			
		}
		else show::work_pages('serv',$Pth,$resuB);
		
	}
echo '</div>';	
//echo '<div class="main_container flex" ' ;
Maket::divclass('main_container',$Pth,'',' flex');
Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth);
Maket::divclass($Maks_Page[8],$Pth,'margin: 30px;flex-direction: column;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around;flex',' flex');
//Массив коээффициентов картинок глобальный для текущего макета и класса
//print_r($Pth('main_container');
//echo $img_log.''.$img_ban;
if($type_access=='global' && (isset($_GET['bannerS']) || isset($_GET['logoS']))){
	$href_tab='./?par='.$Site->ids.'&tab=allsites&editp=ok';
}
else {
	$href_tab='./?np='.$numpage.'&editp=ok';
}

if(isset($_GET['lozS'])){	
	$rest=$PageM->read_namparams('setTypesPage',0);
	foreach($rest[1] as $i=>$val){
		if($i < count($rest[1])-1)$typmen.=$val.';';
		else $typmen.=$val;
	}
	echo '<div class="formsection4">';
	echo '<form method="POST" action="'.$href_tab.'" enctype="multipart/form-data">';
	if(count($arrmain['loz'])>4) echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	if(isset($arrmain['loz']) &&  $arrmain['loz'][0]<>''){
		echo '<div><h2>Лозунги сайта</h2></div>';
	echo '<div style="display:flex; flex-wrap: nowrap;flex-basis:30%;justify-content: space-around; flex-direction: row;">';
	
	$sw->editaball($arrmain,'numpage','loz',$numpage,$typmen,$tabl,$uid,$Site->ids);
	echo '</div>';
	echo '<hr class="line-1"/>';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	echo '</form><div> ';
	}
}
elseif(isset($_GET['bannerS'])){
	echo '<div>';
	if($type_access=='global') {
		$href='./?editp=100&tab=allsites&par='.$Site->ids;
		echo '<div><h2>Баннер сайта</h2><a href="javascript:new_window(\''.$href.'\')">Изменить</a></div>';	
	}
	else {
		$href='./?nameS&blockS&editp=1000&np='.$numpage;
		echo '<div><h2>Банер страницы</h2><h1>'.$arrmain['namep'][2].'</h1><a href="javascript:new_window(\''.$href.'\')">Изменить</a></div>';	
	}
	echo '<div>'.Page::scalimag4($clas['img'].$arrmain['namep'][0],1).'</div>';
	echo '</div>';
	
}
elseif(isset($_GET['logoS'])){
	
	echo '<div>';
	if($type_access=='global') {
		$href='./?editp=101&tab=allsites&par='.$Site->ids;
		echo '<div><h2>Логотип сайта</h2><a href="javascript:new_window(\''.$href.'\')">Изменить</a></div>';	
	}
	else {
		$href='./?nameS&blockS&editp=1100&np='.$numpage;
		echo '<div><h2>Логотип страницы</h2><h1>'.$arrmain['namep'][2].'</h1><a href="javascript:new_window(\''.$href.'\')">Изменить</a></div>';	
	}
	echo '<div>'.Page::scalimag4($clas['img'].$arrmain['namep'][1],$Pth,$clas,0,'div',1).'</div>';
	echo '</div>';
	
}
elseif(isset($_GET['nameS'])){
	echo '<div class="formsection4">';
	//echo '<form method="POST" action="'.$href_tab.'" enctype="multipart/form-data">';
		echo '<div><h4>Основное название страницы</h4><h1> '.$arrmain['namep'][2].'</h1><a href="./?nameS&blockS&editp=1200&np='.$numpage.'">Изменить</a></div>';
		echo '<div><h4>Дополнительное название страницы</h4><h2>'.$arrmain['namep'][3].'</h2><a href="./?editp=1300&np='.$numpage.'">Изменить</a></div>';
		echo '<div><h4>Гиперссылка</h4><h3>'.$arrmain['namep'][4];
		echo '</h3><a href="./?editp=1400&np='.$numpage.'">Изменить</a></div>';	//$sw->editaball($arrmain,'numpage','namep',$numpage,'bl;mn;bt;ft;hd;bf;sw',$tabl,$uid,$Site->ids);
		echo '</div>';
		echo '<hr class="line-1"/>';
	//echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	//echo '</form></div>';
}
elseif(isset($_GET['buttonS'])){
	
	echo '<div class="formsection4">';
	echo '<form method="POST" action="'.$href_tab.'" enctype="multipart/form-data">';
	if(count($arrmain['butt'])>4)echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	if(isset($arrmain['butt']) && $arrmain['butt'][0]<>''){
	echo '<div><h2>Кнопки навигации страницы</h2></div>';	
	echo '<div style="display:flex; flex-wrap: nowrap;flex-basis:30%;justify-content: space-around; flex-direction: row;">';
	$sw->editaball($arrmain,'numpage','butt',$numpage,'bl;mn;bt;ft;hd;bf;sw',$tabl,$uid,$Site->ids);
	
	if(isset($arrmain['buttimg']) && $arrmain['buttimg'][0]<>''){
		//echo '<div style="display:flex; flex-wrap: wrap;flex-basis:40%;justify-content: center; flex-direction: row;">';
		//echo '<div>';
		$sw->editaball($arrmain,'numpage','buttimg',$numpage,'bl;mn;bt;ft;hd;bf;sw',	$tabl,$uid,$Site->ids);
		//echo '</div>';
		$nopics=1;
		
	}
	echo '</div>';
	echo '<hr class="line-1"/>';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	echo '</form><div> ';
	}
}	
elseif(isset($_GET['menuS'])){	
	
	echo '<div class="formsection4">';
	echo '<form method="POST" action="'.$href_tab.'" enctype="multipart/form-data">';
	if(count($arrmain['list'])>4)echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	if(isset($arrmain['list']) && $arrmain['list'][0]<>''){

		echo '<div><h2>Дополнительная навигация</h2></div>';
	echo '<div style="display:flex; flex-wrap: nowrap;flex-basis:80%;justify-content: space-around; flex-direction: row;">';
	
	$sw->editaball($arrmain,'numpage','list',$numpage,'bl;mn;bt;ft;hd;bf;sw',$tabl,$uid,$Site->ids);
	echo '</div>';
	echo '<hr class="line-1"/>';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	echo '</form><div> ';
}
else echo '<div>На странице еще нет дополнительной навигации</div>';
}
elseif(isset($_GET['textS'])){	
	
	echo '<div class="formsection4">';
	echo '<form method="POST" action="'.$href_tab.'" enctype="multipart/form-data">';
	if(count($arrmain['cont'])>4)echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	if(isset($arrmain['cont']) && $arrmain['cont'][0]<>''){
		echo '<div><h2>Тексты страницы</h2></div>';
	echo '<div style="display:flex; flex-wrap: nowrap;flex-basis:30%;justify-content: space-around; flex-direction: row;">';
	$sw->editaball($arrmain,'numpage','cont',$numpage,'bl;mn;bt;ft;hd;bf;sw',$tabl,$uid,$Site->ids);
	echo '</div>';
	echo '<hr class="line-1"/>';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	echo '</form><div> ';
}
}
elseif(isset($_GET['picS'])){	
	//echo '<div style="display:flex;"><h2>Иллюстрации</h2></div>';
	echo '<div class="formsection4">';
	echo '<form method="POST" action="'.$href_tab.'" enctype="multipart/form-data">';	
	if(count($arrmain['buttimg'])>3) echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	$nopics=1;
	if(isset($arrmain['imgt']) && $arrmain['imgt'][0]<>''){
		echo '<div><h2>Тексты,ссылки,иллюстрации </h2></div>';
		echo '<div style="display:flex; flex-wrap: nowrap;flex-basis:30%;justify-content: space-around; flex-direction: row;">';
		$sw->editaball($arrmain,'numpage','imgt',$numpage,'bl;mn;bt;ft;hd;bf;sw',$tabl,$uid,$Site->ids);
		
		//echo '<div>';
		$sw->editaball($arrmain,'numpage','imgs',$numpage,'bl;mn;bt;ft;hd;bf;sw',	$tabl,$uid,$Site->ids);
		echo '</div>';	
	}
	else $nopics=0;
	echo '<hr class="line-1"/>';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	echo '</form>';
	if($nopics==0)echo '<div>На странице еще нет иллюстраций</div>';
}
elseif(isset($_GET['footS'])){	
	echo '<div class="formsection4">';
	echo '<form method="POST" action="'.$href_tab.'" enctype="multipart/form-data">';
	if(count($arrmain['foot'])>4) echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	$nopics=1;
	if(isset($arrmain['foot']) && $arrmain['foot'][0]<>''){
		echo '<div><h2>Ссылки и названия  подвала</h2></div>';
	echo '<div style="display:flex; flex-wrap: nowrap;flex-basis:40%;justify-content: space-around; flex-direction: row;">';
	
	$sw->editaball($arrmain,'numpage','foot',$numpage,'bl;mn;bt;ft;hd;bf;sw',$tabl,$uid,$Site->ids);
	echo '</div>';
	echo '<hr class="line-1"/>';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	echo '</form>';
	echo '</div>';
	}
	else $nopics=0;
	if($nopics==0)echo '<div>На странице еще нет опций подвала</div>';
}
/*elseif(isset($_GET['screenplayS'])){
	if(file_exists('mapsites.csv')) echo '<a href="./?addfile&mapsites=mapsites">Загрузить сценарий сайта</a>';
	elseif($lpm>0 && isset($_GET['screenplayS'])){
		echo 'Сценарий сайта <b>'.$ew->getnameSection(1,'','mapsites').'</b>';	
		$menumap = new MENU(0,'Карта сайта',$Site->ids,$PageM->MainAr['hrefp'].'?np='.$numpage,$tabl,'', $uid,0);
		
	}
}*/	

elseif(isset($_GET['mapS'])){
	//$lpm=$user->getscountab('mapsites','id','t');
	$lst1=$PageM->getnamepage($PageM);
	if(file_exists('mapsites.csv')) echo '<a href="./?addfile&mapsites=mapsites">Загрузить сценарий сайта</a>';
	else {	
		if($numpage==$startpage) {
			echo 'Карта сайта '.$Site->domen;
			$menumap = new MENU($startpage,'Карта сайта',$Site->ids,$PageM->MainAr['hrefp'].'?np='.$numpage,$tabl,'', $uid,0);
		}
		else {
			echo 'Карта страницы '.$lst1;//$lst1[$lst11[0]];
			$menumap = new MENU($numpage,'Карта сайта',$arrmain['idmen'][0],$PageM->MainAr['hrefp'].'?np='.$numpage,$tabl,'', $levelU,0);
		}	
	}
}
else {
	//print_r($_FILES);
	//echo '<br>';
	//print_r($_POST);
	//show::pauza();
	if(!isset($_POST['site'])){
		$scr='#';
		$mass_RA=$user->right_access($Site->desc_site);
		$desc['cga']=$mass_RA['GA'];
		$desc['cym']=$mass_RA['YM'];
		$desc['own']=$mass_RA['PR'];
		if($type_access == 'local'){
			$desc['bann']=$arrmain['namep'][0];//$img_ban;
			$desc['logo']=$arrmain['namep'][1];//$img_log;
		}
		else {
			$desc['bann']=$Bannrpic;//$img_ban;
			$desc['logo']=$Logopic;//$img_log;
		}
		$desc['page']=$Site->pages.'.csv';
		$desc['elem']=$Site->element.'.csv';
		$desc['struc']=$Site->structure.'.csv';
		$desc['news']=$Site->news.'.csv';
		$desc['css']=$Site->css.'.css';
		$desc['scrpt']=$Site->script.'.js';
		
		echo '<div><h2> Загрузите файлы (если вы их подготовили). для вашего сайта '.$Site->domen.'</h2></div>';
		echo '<div style="display:flex; flex-wrap: nowrap;flex-basis:40%;justify-content: space-around; flex-direction: row;">';
			
			echo '<div class="select_opt">';
			echo '<form  class="select_opt" action="" method="post" enctype="multipart/form-data">';
				echo '<input class="button" type="submit"  value="Загрузить на сайт"/>';
				echo '<div><label><h3>Загрузка данных для страниц сайта из файла:</h3></label><div><input name="'.$Site->pages.'" type="file"><input type="text" name="'.$Site->pages.'1" value="'.$desc['page'].'"/>'.$desc['page'].'</div></div>';
				echo '<div><label><h3>Загрузка данных блога сайта из файла:</h3></label><div><input name="'.$Site->news.'" type="file"><input type="text" name="'.$Site->news.'1" value="'.$desc['news'].'"/>'.$desc['news'].'</div></div>';
				echo '<div><label><h3>Загрузка пользовательских стилей из файла:</h3></label><div><input name="mystyle" type="file"><input type="text" name="mystyle1" value="'.$desc['css'].'"/></div></div>';
				echo '<div><label><h3>Загрузка JS-скриптов сайта из файла:</h3></label><div><input name="myscrpt" type="file"><input type="text" name="myscrpt1" value="'.$desc['scrpt'].'"/></div></div>';
				echo '<div><label><h3>Загрузка данных каталога товаров сайта из файла:</h3></label><div><input name="elements" type="file"><input type="text" name="elements1" value="'.$desc['elem'].'"/>'.$desc['elem'].'</div></div>';
				echo '<div><label><h3>Загрузка данных структуры каталога сайта из файла:</h3></label><div><input name="structure" type="file"><input type="text" name="structure1" value="'.$desc['struc'].'"/>'.$desc['struc'].'</div></div>';
				
			echo '</div><div class="select_opt">';	
				$sizeB = GetImageSize($img_ban);
				$sizeL = GetImageSize($img_log);
				if($sizeB[0]>$sizeB[1]) $nsb=$sizeB[0]/600;
				else $nsb=$sizeB[1]/600;
				if($sizeL[0]>$sizeL[1]) $nsl=$sizeL[0]/200;
				else $nsl=$sizeL[1]/200;
				if($nsb > 3 || $nsb<1) $nsb=3;
				if($nsl > 3 || $nsl<1) $nsl=1;
				if($type_access == 'global')echo '<div ><label><h3>Загрузка общего баннера сайта:</h3>';
				else echo '<div ><label><h3>Загрузка баннера страницы('.$numpage.'):</h3>';
				echo '</label><div><input name="banmain" type="file"><input type="text" name="banmain1" value="'.$desc['bann'].'"/>'.Page::scalimag4($img_ban,$Pth,'logo','','div',$nsb).'</div><small>rs:'.$sizeB[0].'x'.$sizeB[1].'('.$nsb.')</small></div>';
				if($type_access == 'global')echo '<div><label><h3>Загрузка логотипа сайта:</h3>';
				else echo '<div><label><h3>Загрузка логотип страницы('.$numpage.'):</h3>';
				echo '</label><div><input name="logo" type="file"><input type="text" name="logo1" value="'.$desc['logo'].'"/>'.Page::scalimag4($img_log,$Pth,$clas,0,'div',$nsl).'</div><small>rs:'.$sizeL[0].'x'.$sizeL[1].'('.$nsl.')</small></div>';
			echo '<input class="button" type="submit"  value="Загрузить на сайт"/>';
			echo '<input name="uid" value="'.$uid.'" type="hidden"><input name="site" value="'.$Site->ids.'" type="hidden"></div></form></div>';
				
		//echo '<input type="submit"  value="Записать изменения "/>';
		echo '<input name="uid" value="'.$uid.'" type="hidden"><input name="site" value="'.$Site->ids.'" type="hidden"></div></form></div>';
	}
	elseif(isset($_FILES)){
		$sw->showloadfiles($numpage,'blockS',$clas);	
	}
	else{
		$scr='?editp=ok&par='.$Site->ids.'&tab=allsites';
		echo '<div class="formsection4">';
		echo '<form  class="select_opt" action="'.$scr.'" method="post" enctype="multipart/form-data">';
		$arrnampar=$PageM->read_namparams('allsites',$Site->ids,'ids','');
		$arrnampar[3][5]=$_POST['strucs'];
		$arrnampar[3][6]=$_POST['typs'];
		$arrnampar[3][7]=$_POST['ippt'];
		$arrnampar[3][8]=$_POST['csstl'];
		$arrnampar[3][9]=$_POST['scrpt'];
		$arrnampar[3][10]=$_POST['banmain'].';'.$_POST['logo'];
		$arrnampar[3][16]=$_POST['page'];
		$arrnampar[3][17]=$_POST['blog'];
		$arrnampar[3][18]=$_POST['elem'];
		$arrnampar[3][19]=$_POST['struc'];
		$arrnampar[3][20]=$_POST['cga'].'|'.$_POST['cym'].'|'.$_POST['prt'];
		//print_r($arrnampar[3]);
		foreach($arrnampar[3] as $key=>$val)	{
			echo '<div><input type="text" size="100"  name="'.$key.'" value="'.$val.'"></div>';
		}
		echo '<input type="submit"  value="Подтвердите запись изменений"/>';
		echo '</form>';
		echo '</div>';
	}
	
}

//echo '<hr class="line-1"/>';
Maket::closediv(3);




?>