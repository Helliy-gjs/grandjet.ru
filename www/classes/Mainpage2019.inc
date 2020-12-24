<!-- load Main --><?php
if(isset($_GET['debug']))echo '<info class="hidno">'.$pathheader.$pathToClasses.'Mainpage2019.inc'.'</info>';

//echo $arrmain['idmen'][0];

//проверка являетесь ли вы администратором сайта
if ($arrmain['idmen'][0] == '') $arrmain['idmen'][0]='cont';
set_time_limit(10000);

//редактирование страниц
//редактирование данных о пользователе 
if(isset($_GET['cust'] )&&  isset($_GET['editp']) &&  !isset($_GET['tab']) && !$mode_edit){	
	$c=50;//количеситво колонок в текстовом окне
	$r=2;//количество рядов в текстовом окне
	$s=130;//количеситво символов  окне
	$t=1;
	include($pathheader.$pathToClasses.'editall.inc');
}
//числовые параметры header страницы 
//Пользовательский фонт в форме css

else {	
//помещаем весь контент в container, который можем от позиционировать по отношению к body

if($arrmain['idmen'][0]<>'flex' && isset($Maks_Page[0]))Maket::divclass('main_container_'.$arrmain['idmen'][0],$Pth);//divC
else Maket::divclass('#main_container',$Pth);//<div id="main_container">

if ($mode_edit && $levelU>3 ) {
	if (isset($_GET['par'])) $npar =$_GET['par'];
}

//Хедер сайта 
?><!-- load head site --><?php
if(isset($_GET['debug']))echo '<info class="hidno">'.$pathheader.$pathToClasses.'reg2019_'.$ind_scr.'.inc'.'</info>';
if(isset($ind_scr)){
	if (file_exists($pathheader.$pathToClasses.'reg2019_'.$ind_scr.'.inc'))
	include($pathheader.$pathToClasses.'reg2019_'.$ind_scr.'.inc');
	elseif(file_exists($pathheader.$pathToClasses.'reg2019.inc'))
	include($pathheader.$pathToClasses.'reg2019.inc');

	//загрузка содержимого корзины интернет магазина
	if (isset($_GET['new']) || isset($_POST['save'])) include($pathheader.$pathToClasses.'show_cart.inc');
	//Загрузка основного контента сайта
	//print_r($distype);
	if ($distype[1]== 'bl'){	
		if(isset($_GET['debug']))echo '<info class="hidno">'.$pathheader.$pathToClasses.$arrmain['idmen'][0].'ing.inc'.'</info>';
		if(file_exists($pathheader.$pathToClasses.$arrmain['idmen'][0].'ing.inc'))include($pathheader.$pathToClasses.$arrmain['idmen'][0].'ing.inc');
		else '<info class="hidno" Content is absent';
	}
	else echo '<info class="hidno"> Content - nbl</info>';
	//Загрузка футера сайта
	?><!-- load foot site --><?php
		if(isset($_GET['debug']))echo '<info class="hidno">'.$pathheader.$pathToClasses.'foot2019_'.$ind_scr.'.inc'.'</info>';
	if ($distype[5] === 'ft' && !isset($_GET['konstrS'])){
		
			if (file_exists($pathheader.$pathToClasses.'foot2019_'.$ind_scr.'.inc'))
			include($pathheader.$pathToClasses.'foot2019_'.$ind_scr.'.inc');
			elseif(file_exists($pathheader.$pathToClasses.'foot2019.inc'))
			include($pathheader.$pathToClasses.'foot2019.inc');	
			else echo 'footer is absent';
			}
	elseif ($distype[3]<>'nft'){
		
		if($arrmain['idmen'][0]<>'flex'){
		$num_foot=3;
		//if(!$mode_work && isset($_GET['contentS'])) echo 'Блок футера страницы<hr>';//comment
		Maket::divclass($MP[11].$num_foot,$Pth);
		
				$ew->showfooternew($tabl,$arrmain,$Pth,'foot',1,$clas, 10,$num_foot);
			echo '</div>';
		}
		else {
			Maket::divclass('container_footers',$Pth);
			Maket::divclass('footer',$Pth,'',' flex');
			unset($arr['foot']['link']);
			foreach($arr['foot'] as $key=>$val) Maket::showlogo('foot',$arrmain,$Pth,5,$key,'foot');
			Maket::closediv(2);//footers footer #main_container
		}	
		}
	elseif($Maks_Page[11]==$clas['clas'][15] &&  $type_access=='general')  {//неотключаемый программно футер
			Maket::divclass($Maks_Page[11],$Pth);
				echo '<div class="'.$clas['clas'][1].'">';
				echo '<div class="'.$clas['clas'][17].'-'.$clas['clas'][0].'">'.
				$arrmain['loz'][0].'<div class="footer-copy">~©~</div>';
			echo '</div></div>';
		}

			
	echo '</div>';////divC	
	//}
	}
	echo '</div>';
}
//if(isset($_GET['debug']))echo '<info class="hidno">'.$pathheader.$pathToClasses.'Jscripts.inc '.$type_access.'</info>';
//include($pathheader.$pathToClasses.'Jscripts.inc');
?>