<?php
echo 'Content blog page';
/*
echo '<div class="header-button">'; 

if ($levelU>3) {
if ($_GET['hd'] <> 5) echo '<a href="?np='.$numpage.'&editp=yes" accesskey="e"> Изменить </a>
<a type="hidden" href="?np='.$numpage.'&editp=ok" accesskey="d"></a>';
	elseif ($PageM->MainAr["idnews"] <> 0) echo '<a href="'.$PageM->MainAr["hrefp"].'?in='.$PageM->MainAr["idnews"].'&hd=5&editp=yes"> Изменить новость </a>';
	if ($_GET['hd'] <> 5) echo '<a href="'.$PageM->MainAr["hrefp"].'?np='.$numpage.'&addp=yes"> Добавить </a>';
	elseif ($PageM->MainAr["idnews"] <> 0) echo '<a href="'.$PageM->MainAr["hrefp"].'?in='.$PageM->MainAr["idnews"].'&hd=5&addp=yes"> Добавить новость </a>';
	}
echo '<a href="/?np='.$startpage.'"><span > На стартовую </span></a>';
	echo '<a  href="./auth/?logout"><span > Выйти </a></span>';
	//if ($numpage<>97) echo '|<a href="'.$PageM->MainAr['hrefp'].'?np=97&tab=a">Полный каталог доступных товаров</a>';
	if ($_SESSION['total_price']>0) {
		echo '<a href="./book/show_cart.php">Посмотреть заказы </a>';
		echo 'Общая сумма = '.number_format($_SESSION['total_price'],2);
		
	}
	else {
	//echo '|<a class="s" href="'.$PageM->MainAr['hrefp'].'?hd=5"><span class="s">Новости</span></a>';
	if ($levelU<=0) echo '<a href="./registration/?site='.$Site->ids.'"> Регистрация </a>';
	if ($levelU<=0) echo '<a href="./auth/">Вход для пользователей </a>';
	if ($levelU<0) echo '<a href="./auth/?guest">Гостевой вход </a>';
	if ($levelU==0) echo '<span>Вы гость сайта </span>'.'<span><a href="./auth/?logout">Выйти</a></Span>';
	}
if ($arrmain['idmen'][0] == 'blog')show::simple_adap_menu($arrmain,$clas,'butt');	
/*echo '<div class="sechead s3">';
$sw->gettexturl('http://inline.ru/','Продолжение >>','Продолжение >>' ,'','Опрос','win');
echo '</div>';

echo '<div class="sechead s3">';
$sw->gettexturl('http://inline.ru/','Продолжение >>','Продолжение >>' ,'','Опрос','win');
echo '</div>';
echo '<div class="sechead s3">';
$sw->gettexturl('https://lenta.ru/','b-yellow-box__wrap">','b-yellow-box__header bordered-title">','','<section class="b-longgrid-column">');
echo '</div>';

echo '</div>';
if ($arrmain['typmen'][3] <> 'nft'){
	echo '<footer class="main-footer">
		<div class="container">
			<div class="footer-logo">
				We Are Real <span>Creators</span>
			</div>
			<div class="footer-copy">~©~</div>
		</div>
	</footer>';
}
else {
	echo '<div id="footer">';
	echo '<div id="footer-sec">';
	$ew->showfooter($tabl,$list[5][0],$GLOBALS['levelU'],1,$clas, 10);
	//$ew->showfooternew($tabl,$arrmain,'butt', $GLOBALS['levelU'],1,$clas, 10);
//$ew->showfooter($tabl,$list,'butt', $levelU,1,$clas, 10);
echo '</div>';
}
