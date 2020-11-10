<?php
	
$resuB=$PageM->read_namparams('setSEO',0);

if(isset($_GET['seoS'])) foreach($resuB[1] as $key=>$val) $resuB[1][$key]=$resuB[1][$key].'&seoS';

//Maket::icon_button('cont hidyes','fa fa-bars','div','');
echo '<div class="menu flex">';
echo show::work_pages('serv',$Pth,$resuB,'./'.$graphp);
echo '</div>';
Maket::divclass('menu '.$arrmain['idmen'][0],$Pth,'',' flex');

echo '</div>';	
Maket::divclass('main_container',$Pth,'',' flex');
Maket::divclass($Maks_Page[17].'-'.$arrmain['idmen'][0],$Pth,'',' flex');
Maket::divclass($Maks_Page[8],$Pth,'margin: 30px;flex-direction: column;flex-wrap:nowrap;flex-basis:100%;justify-content:space-around;',' flex');

if(isset($_GET['findS'])){

	if(!isset($_POST['site'])){
	$scr='';
	$mass_RA=$user->right_access($Site->desc_site);
	$desc['cga']=$mass_RA['GA'];
	$desc['cym']=$mass_RA['YM'];
	$desc['own']=$mass_RA['PR'];
	$arrnampar=$PageM->read_namparams('allsites',$Site->ids,'ids','');
	$arridmen=array(0,1,2,3,4,5,6,7,8,9,10,11);
	$arrstr=array(11=>'Многостраничный', 0=>'Лендинг', 1=>'Галлерея', 7=>'Адаптив', 8=>'Магический', 9=>'Иерархический',6=>'Мобильный', 4=>'Фибинг', 3=>'Твитинг',5=>'Квизинг',10=>'Интернет-магазин',2=>'Блог');
	$arrtyps=array(6=>'Компактный',3=>'Галлерея',7=>'Дизайнерский',8=>'Структурированый',4=>'Мобильный',5=>'Адаптивный',9=>'Каталог',1=>'Лента новостей',2=>'Видеоблог',0=>'Визитка',10=>'Корпоративный');
	$arripp=array(0=>'Новости',1=>'Наука',2=>'Учеба',3=>'Интернет',4=>'Презентация',5=>'Музыка',6=>'Литература',7=>'Спорт',8=>'Развлечения',9=>'Торговля',10=>'Соцсеть');
	echo '<div class="formsection">';
		echo '<form  class="select_opt" action="'.$scr.'" method="post" enctype="multipart/form-data">';
		
		echo '<div class="select_opt"><label><h4>Код Google Analitic   :</h4></label><div><input name="cga" value="'.$desc['cga'].'" type="text"></div></div>';
		echo '<div><label><h4>Код Yandex Metrika   :</h4></label><div><input name="cym" value="'.$desc['cym'].'" type="text"></div></div>';
		$arrnampar=$PageM->read_namparams('allsites',$Site->ids,'ids','');
		$seo=explode('|',$arrnampar[3][20]);
		echo '<div class="select_opt"><label><h4>Использовать SSL-протокол :</h4></label>';
		if($seo[2]=='Y') {
			echo '<div><input type="checkbox" checked name="prt" value="N"/><input type="hidden" name="prt" value="N"';
		}
		else {
			echo '<div><input type="checkbox"  name="prt" value="N"/><input type="hidden" name="prt" value="Y"';
		}
		echo '</div></div><div class="select_opt">';
		$user->selmen($arrstr,'',$arridmen,'',$arrnampar[3][5],'strucs','Выбрать');
		$user->selmen($arripp,'',$arridmen,'',$arrnampar[3][6],'ippt','Выбрать');
		$user->selmen($arrtyps,'',$arridmen,'',$arrnampar[3][7],'typs','Выбрать');
		echo '<input type="submit"  value="Записать изменения "/>';
		echo '<input name="uid" value="'.$uid.'" type="hidden"><input name="site" value="'.$Site->ids.'" type="hidden"></div></form></div>';
}
else{
		$scr='?editp=ok&par='.$Site->ids.'&tab=allsites';
		echo '<div class="formsection4">';
		echo '<form  class="select_opt" action="'.$scr.'" method="post" enctype="multipart/form-data">';
		$arrnampar=$PageM->read_namparams('allsites',$Site->ids,'ids','');
		$arrnampar[3][5]=$_POST['strucs'];
		$arrnampar[3][6]=$_POST['typs'];
		$arrnampar[3][7]=$_POST['ippt'];
		$arrnampar[3][20]=$_POST['cga'].'|'.$_POST['cym'].'|'.$_POST['prt'];
		foreach($arrnampar[3] as $key=>$val)	{
			echo '<div><input type="hidden" size="100"  name="'.$key.'" value="'.$val.'"></div>';
		}
		echo '<input type="submit"  value="Подтвердите запись изменений"/>';
		echo '</form>';
		echo '</div>';
}
}
elseif(isset($_GET['keywordS'])){
	echo '<div class="formsection">';
	echo '<label><h4>Ключевые слова (keywords) страницы</h4> </label>';
	//print_r($for_keywords);
	foreach($for_keywords as $val){
		echo '<h3>'.$val.'</h3>';	
	}
	echo '<a href="./?nameS&blockS&editp=30&np='.$numpage.'">Изменить</a>';
	echo '</div>';
}
elseif(isset($_GET['titleS'])){
	echo '<div class="formsection">';
	echo '<label><h4>Заголовок (title)</h4>:<h3> '.$arrmain['titles'].'</h3></label><a href="./?nameS&blockS&editp=31&np='.$numpage.'">Изменить</a></div>';
	echo '</div>';
}
elseif(isset($_GET['descS'])){
	echo '<div class="formsection">';
	echo '<label><h4>Описание страницы (description):</h4></label><h3>'.$arrmain['descr'].'</h3><a href="./?nameS&blockS&editp=32&np='.$numpage.'">Изменить</a>';
	echo '</div>';
}
Maket::closediv(3);
?>