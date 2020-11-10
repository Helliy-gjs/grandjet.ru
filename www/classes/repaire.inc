<?php
//отладчик
if ($control_mode == 1) {
	//Контроль параметров страницы
    if($user->getLevelnew($uid)>4 || $user->getscountab('elemap','id','t') == 0){
	    echo "Параметры страницы(вид Администратора сайта)<br/>";
	    $ew->Showobjtype($PageM->MainAr);
    }
    else {
        echo "Параметры страницы(вид Пользователя сайта)<br/>";
        $ew->Showobjtype($PageM->MainAr);
    }
}
if ($control_mode == 2) {
	//Контроль пользователя
	echo "Параметры пользователя :";
	echo "код пользователя uid=$uid код фирмы cid=$cid уровень пользователя в базе данных ".$user->getLevel().", права пользователя ".$user->getLevelnew()." <br/>";
	echo "Параметры режима страницы номер numpage=$numpage поиск -$poisk группа товаров tid=$tid производитель -$vend таблица элементов cat_elem=$cat_elem - tabl_elem=".$tabl['elem']." ( $pathscrypt )<br/>";
}

//Основное содержание страницы - конец
if ($control_mode == 3) {
	//Контроль массивов
	echo " Массив абсолютных ссылок (1-2) ";
	echo "<br>";print_r($list[1][0]); echo "<br>";print_r($list[2][0]);echo "<br>";
	echo " Массив навигационых кнопок (3-5)";
	echo "<br>";print_r($list[3][0]); echo "<br>";print_r($list[4][0]);echo "<br>";
	print_r($list[5][0]);echo "<br>";
	echo " Массив текстов (6)";
	echo "<br>";print_r($list[6][0]);echo "<br>";
	echo "<br>";print_r($list[7][0]);echo "<br>";
	echo " Массив лозунгов (7-8)";
	echo "<br>";print_r($list[7][0]);echo "<br>";print_r($list[8][0]);echo "<br>";
	echo " Массив названия страниц (9)";
	echo "<br>";print_r($list[9][0]);echo "<br>";
	echo " Массив уровней меню (10)";
	echo "<br>";print_r($list[10][0]);echo "<br>";
	echo " Массив типов ввода (11)";
	echo "<br>";print_r($list[11][0]);echo "<br>";
	echo " Массив видов ввода (12)";
	echo "<br>";print_r($list[12][0]);echo "<br>";
	echo " Массив новостей ";
	echo "<br>";print_r($aaa['n']);echo "<br>";
	echo " Массив текстов и картинок к ним ";
	print_r($aaa['t']);echo "<br>";
	print_r($aaa['g']);echo "<br>";
	print_r($aaa['l']);echo "<br>";
}
if ($control_mode == 4) {
    $arraycm=$arrmain;
    unset($arraycm['link']);
	echo '<ul>';
	
    if($user->getLevelnew($uid)>4 || $user->getscountab('elemap','id','t') == 0) {
        Maket::spanclass('<b>Страница (Вид Администратора)</b>' . $numpage, $Pth, 'repair','li');
    }
    else {
        Maket::spanclass('<b>Страница (Вид пользователя)</b>' . $numpage, $Pth, 'repair','li');
    }
	
	Maket::spanclass('<b>Название</b>  ',$Pth,'repair','li');
	
	unset($arraycm['namep']['link']);
	foreach($arraycm['namep'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	Maket::spanclass('<b>Лозунги</b> ',$Pth,'repair','li');
	
	unset($arraycm['loz']['link']);
	foreach($arraycm['loz'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	unset($arraycm['lozhref']['link']);
	echo '<li>';
	foreach($arraycm['lozhref'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Ключи</b> ',$Pth,'repair','li');
	
	foreach($arraycm['key'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	Maket::spanclass('<b>Кнопки</b> ',$Pth,'repair','li');
	
	unset($arraycm['butt']['link']);
	foreach($arraycm['butt'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	Maket::spanclass('<b>Ссылки кнопок</b> ',$Pth,'repair','li');
	unset($arraycm['butthref']['link']);
	echo '<li>';
	foreach($arraycm['butthref'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Kартинки для кнопок</b> ',$Pth,'repair','li');
	
	unset($arraycm['buttimg']['link']);
	echo '<li>';
	foreach($arraycm['buttimg'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Меню страницы</b> ',$Pth,'repair','li');
	
	unset($arraycm['list']['link']);
	foreach($arraycm['list'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	unset($arraycm['listhref']['link']);
	Maket::spanclass('<b>Ссылки меню страницы</b> ',$Pth,'repair','li');
	echo '<li>';
	foreach($arraycm['listhref'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Меню футера</b> ',$Pth,'repair','li');
	
	unset($arraycm['foot']['link']);
	foreach($arraycm['foot'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	Maket::spanclass('<b>Ссылки Меню футера</b> ',$Pth,'repair','li');
	
	unset($arraycm['foothref']['link']);
	echo '<li>';
	foreach($arraycm['foothref'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>URL страницы:</b> '.$arraycm['hrefp'][0],$Pth,'repair','li');
	
	Maket::spanclass('<b>Тип вывода</b> ',$Pth,'repair','li');
	echo '<li>';
	unset($arraycm['typmen']['link']);
	foreach($arraycm['typmen'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	echo '<li>';
	echo '<b>URL скриптов:</b> ';
	foreach($arraycm['scripts'] as $val)Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	echo '<li>';
	echo '<b>URL стилей:</b> ';
	foreach($arraycm['style'] as $val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Тайтл:</b> '.$arraycm['title'][0],$Pth,'repair','li');
	
	Maket::spanclass('<b>Тексты</b> ',$Pth,'repair','li');
	
	unset($arraycm['cont']['link']);
	foreach($arraycm['cont'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	Maket::spanclass('<b>Cсылки для текстов</b> ',$Pth,'repair','li');
	
	unset($arraycm['conthref']['link']);
	echo '<li>';
	foreach($arraycm['conthref'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Категории структуры</b> '.$arraycm['idmen'][0],$Pth,'repair','li');
	
	Maket::spanclass('<b>Уровни каталога</b>  ',$Pth,'repair','li');
	
	unset($arraycm['levmen']['link']);
	foreach($arraycm['levmen'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	Maket::spanclass('<b>Иллюстрации</b>  ',$Pth,'repair','li');
	echo '<li>';
	unset($arraycm['imgs']['link']);
	foreach($arraycm['imgs'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Тексты для иллюстраций</b>  ',$Pth,'repair','li');
	
	unset($arraycm['imgt']['link']);
	foreach($arraycm['imgt'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	Maket::spanclass('<b>Ссылки для иллюстраций</b> ',$Pth,'repair','li');
	
	unset($arraycm['imgthref']['link']);
	echo '<li>';
	foreach($arraycm['imgthref'] as $key=>$val) Maket::spanclass($val,$Pth,'repair');
	echo '</li>';
	Maket::spanclass('<b>Ссылка на блог</b> '.$arraycm['n'][4],$Pth,'repair','li');
	
	Maket::spanclass('<b>Домен</b> '.$arraycm['site'][0],$Pth,'repair','li');
	
	Maket::spanclass('<b>Конфигурация '.$arraycm['conf'][1].'</b>',$Pth,'repair','li');
	foreach($arraycm['conf'] as $key=>$val) Maket::spanclass($val,$Pth,'repair','li');
	
	
	Maket::spanclass('<b>Владелец</b> '.$arraycm['idauthor'],$Pth,'repair','li');
	echo '<ul>';
	
}
if ($control_mode == 5){
	echo'==================================================<br>';
	echo '||Параметры:'.$Site->domen.'('.$Site->ids.') тип сайта '.$arrmain['idmen'][0].' глобальный макет '.$idmaket.'             ||<br>';
	echo'==================================================<br>';
	echo 'CONTAINER (контейнер) страницы <br> ';
	echo 'Стили container ';print_r($Pth[$cont_site]);echo '<br>';
	echo 'Main_header (загаловок) страницы <br> ';
	echo 'Стили header ';print_r($Pth[$header_site]);echo '<br>';
	echo '----------------------------------------------<br>';
	echo 'Main_menu (основное меню страницы) <br> ';
	echo 'Стили main_menu ';print_r($Pth[$main_menu_site]);echo '<br>';
	echo '----------------------------------------------<br>';
	echo 'Main_wrapper (контейнер основного информационного блока страницы) <br> ';
	echo 'Стили main_wrapper ';print_r($Pth[$main_wrapper_site]);echo '<br>';
	echo '----------------------------------------------<br>';
	echo 'Sidebare (левый навигационный блок страницы) <br> ';
	echo 'Стили sidebare левый ';print_r($Pth[$sidebareL_site]);echo '<br>';
	echo '----------------------------------------------<br>';
	echo 'Sidebare (правый навигационный блок страницы) <br> ';
	echo 'Стили sidebare правый ';print_r($Pth[$sidebareR_site]);echo '<br>';
	echo '----------------------------------------------<br>';
	echo 'wrapper (информационный блок страницы) <br> ';
	echo 'Стили wrapper ';print_r($Pth[$wrapper_site]);echo '<br>';
	echo '----------------------------------------------<br>';
	echo 'footer (подвальный блок страницы) <br> ';
	echo 'Стили main_footer ';print_r($Pth[$footer_site]);echo '<br>';
	echo '----------------------------------------------<br>';
	//echo 'Размер банера = '.$size_par['pics'][0].'<br>';
	//echo 'Размер лого = '.$size_par['pics'][1].'<br>';
	//echo 'Размер шрифта в баннере ='.$size_par['fonts'][0]. '<br>';
	//echo 'Размер шрифта текстовых блоков в баннере ='.$size_par['fonts'][1]. '<br>';
	//echo 'Размер заглавного шрифта блока лого  ='.$size_par['fontl'][0]. '<br>';
	//echo 'Размер обычного шрифта блока лого  ='.$size_par['fontl'][1]. '<br>';
	echo '----------------------------------------------<br>';
	if (isset($Style_users)) show::infosh('Стиль страницы пользовательский  '.$Style_page.' Стиль макета '.$Style_users.' Стиль редактора '.$Style_edit);
	echo '<br>----------------------------------------------<br>';
}
if ($control_mode == 6) {
	$arrpageadm=Page::readyadmarr($arrmain);
	print_r($arrpageadm); 
}
if ($control_mode == '') {
	//Контрольный режим отключен	
	//ElementsW::Showobjtype($_POST);
}
unset($arraycm);
if(isset($_GET['exit']))exit();
?>