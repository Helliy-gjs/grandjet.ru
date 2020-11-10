<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>Интернет-магазин от grandjetstudio</title>
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<link rel="shortcut icon" href="favicon.png" />
<?php
echo '<link rel="stylesheet" href="./css/style.css">
<link rel="stylesheet" href="./css/main.css">
<link rel="stylesheet" href="./css/homepage.css">
<link rel="stylesheet" href="./css/footer.css">';
echo '<script src="https://kit.fontawesome.com/40fe3b38f8.js" crossorigin="anonymous"></script>';
echo '</head><body>';


//!Загрузка персональных данных макета сайта  из верстки
	
if(file_exists(CLASSES.'/personalShopData.inc') && isset($numpage)) include(CLASSES.'/personalShopData.inc');
else echo 'не доступен '.CLASSES.'/personalShopData.inc';
if(file_exists(CLASSES.'/personalShopMaket.inc') && isset($numpage)) include(CLASSES.'/personalShopMaket.inc');
else echo 'не доступен '.CLASSES.'/personalShopMaket.inc';
//первая загрузка сайта из html верстки
echo '--------------';
$contentShop = array('contact' => $contscts,'addcont'=>$contactadd,'logo'=>$contLogo,'top'=>$contenTop,'nav'=>$navMenu,'cat'=>$dat4);


echo show::showShopHeader($Pth,'',$clasShop,$contentShop,$optMenu,$Icons);
?>
<main class="page">
    <div class="page__container _container">
        <aside class="page__side">
		<?php		
echo show::showShopCatMain($Pth,$contentShop['cat'],$clasShop['cat']);
echo '<div data-da="page__content,last,992" class="page__content-side">';
echo maket::div2Blockstr($Pth,$contentNews,'<a href="'.$hrefnews.'" class="news-side__title side-title">'.$glsr['nw'].'</a>','page__news-side news-side','news-side__items');    
echo maket::div2Blockstr($Pth,$contentOtz,'<a href="'.$hrefozs.'" class="reviews-side__title side-title">'.$glsr['oz'].'</a>','page__reviews-side reviews-side','reviews-side__items');
echo '</div>';
?>          
</aside>            
<div class="page__content">
<?php
echo show::showformSearches('categories-search',$contentCategories);

echo show::showSwipSliders($contSlider);
?>    

<div class="page__products products-slider">
	<?php 
		echo show::showSwipSliders($contProduct,'products-slider','products-slider__arrow',$arrloz[0]);
	?>
</div>	
</div><!--page-content-->
</div><!--page__container _container-->
</div>
<?php
echo show::showSwipSliders($contentBrend,'brands-slider','brands-slider__arrow');
?>
<section class="page__text text-block">

<?php
echo maket::div2Blockstr($Pth,'<h1 class="text-block__title">О компании</h1>'.$contTextBlock,'','text-block__container _container','text-block__body');    
?>
</section>
<?php
echo maket::div3Blockstr($Pth,$contentInfo.$contentHelp,'page__info-menu info-menu','','page__info-menu info-menu','info-menu__body');
echo '<footer class="footer">'.$contentFooter.'</footer>';
?>
</main>
<script src="./scripts/swiper.min.js" type="text/javascript"></script>
<script src="./scripts/script.min.js" type="text/javascript"></script>
<script src="./js/restapi.js" type="text/javascript"></script>