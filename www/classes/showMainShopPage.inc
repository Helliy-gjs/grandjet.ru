<?php
//echo 'Интернет магазин sportshop'; 

//местные настройки

$arrloz[0] = $glsr['pop'];
$dark = 'dark';
$light = 'light';
//$type_site = 'shop';
$email = 'ruslan@grandjet.ru';

$dat1['typesite'] = 'pwa';
$dat2['typesite'] = 'pwa';
$dat4['typesite'] = 'pwa';
$navMenu['typesite'] = 'pwa';
	$nameSection = array('id','main','header','navmenu','cat','hover','search','footer');
	$clasShop = maket::getClassesMaket ($YourMaket,$nameSection);
	/*$YourMaket = explode('|',$YourMakets[0][10]);	
	$arrClasNumber = explode('*',$YourMaket[1]);	
	$mainClas = explode(',',$arrClasNumber[0]);
	$numbClas = explode(',',$arrClasNumber[1]); 
	$nsClas[0]=0;
	foreach( $numbClas as $i=>$val){
		if($i == 0)$nsClas[$i]=intval($nsClas[0]) ;
		else $nsClas[$i]= $nsClas[$i-1] + intval($numbClas[$i]);
		
	}
	//debug($nsClas);
	//die();
	$k=0;
	$nameSection = array('id','main','header','navmenu','cat','hover','search','footer');
	foreach($mainClas as $i=>$val){
		if($i <= $nsClas[$k]) $clasShop[$nameSection[$k]][] = $val;
		else {
			$k++;
			if($k<count($nameSection))$clasShop[$nameSection[$k]][] = $val;
		}
	}*/
	//$id = $clasShop['id'];
		/*if($i < $numbClas[0]) $id[] = $val;
		elseif($i < $numbClas[0] + $numbClas[1]) $clasShop['main'][] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2]) $clasShop['header'][] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3]) $clasShop['navmenu'][] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4]) $clasShop['cat'][] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4] + $numbClas[5]) $clasShop['hover'][] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4] + $numbClas[5] + $numbClas[6]) $clasShop['search'][] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4] + $numbClas[5] + $numbClas[6] + $numbClas[7]) $clasShop['footer'][] = $val;
	}*/
// debug($clasShop);
 //die();
//загрузка сайта из базы данных	
//echo '<script src="https://kit.fontawesome.com/40fe3b38f8.js" crossorigin="anonymous"></script>';
echo '</head><body>';
//! Загрузка данных каталога
$img = array('bicycl.png');
$arrloz[0] = 'Категория товара';
//!Elements
$arrElements = $ew->getElements('ms',1);
//debug($arrElements);
foreach($arrElements as $value) {
	$titleGalerySlider[] = $value['name'];
	$priceGalerySlider[] = $value['price'];
	$priceoldGalerySlider[] = $value['price'];
	$stockGalerySlider[] = $value['stock'];
	$imgDesc = explode('|',$value['desc']);
	$imgGalerySlider[1][] = $imgDesc[0];
	$namparsGalerySlider[] = explode(';',$imgDesc[3]);
	$parsGalerySlider[] = explode(';',$imgDesc[4]); 		
}
//debug($parsGalerySlider);
//$imgGalerySlider[1] = array('runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg');
//$namparsGalerySlider = array('Тип','Скорость (км/ч)','Складываниие'); 
//$parsGalerySlider = array('электрическая','22', 'Есть');

$news = $db->getAll('news');

foreach($news as $val) {
	if($val->group === 'news'){
		$newsDat['text'][] = $val->newstext;
		$newsDat['name'][] = $val->name;
		$newsDat['date'][] = $val->date;
		$newsDat['href'][] = $val->hrefnew;
	}
	if($val->group === 'reviews'){
		$callDat['text'][] = $val->newstext;
		$callDat['name'][] = $val->name;
		$callDat['date'][] = $val->date;
		$callDat['href'][] = $val->hrefnew;
	}
}
//debug($newsDat);
$hrefnews='';
$hrefozs='';
$dateNews = array($newsDat['date'][0],$newsDat['date'][1]);
$date1[0]=explode('-',$dateNews[0]);
$date1[1]=explode('-',$dateNews[1]);
$dateNews[0] = getdate(gmmktime (0, 0, 0, $date1[0][1], $date1[0][2], $date1[0][0]));
$dateNews[1] = getdate(gmmktime (0, 0, 0, $date1[1][1], $date1[1][2], $date1[1][0]));
$newsDat['date'] = array('<div class="news-side__data"><span>'.$dateNews[0]['mday'].'</span>'.$dateNews[0]['month'].'</div>','<div class="news-side__data"><span>'.$dateNews[1]['mday'].'</span>'.$dateNews[1]['month'].'</div>');
$newsDat['href'] = array($hrefnews.'#id1',$hrefnews.'#id2');

//die();

$contentNews = show::showBlogItem('news', $newsDat,0).show::showBlogItem('news', $newsDat,1); 
$contentOtz = show::showBlogItem('reviews', $callDat,0,'a','right').show::showBlogItem('reviews', $callDat,1,'a','right');

//!Structure
$arrcat = $sw->getData(0,$tabl['elem'],$uid,$Site->ids);

foreach($arrcat['sections'] as $val) {
	$contentShopCat['dat'][$val['id']]=$val['name'];
	$contentShopCat['href'][$val['id']] = './?cat='.$val['id'];
	$arrsubcat[$val['id']] = $sw->getData($val['id'],$tabl['elem'],$uid,$Site->ids);
}
//debug($arrsubcat);

foreach($arrsubcat as $key=>$value){
	//debug($value['sections']);	
	$contentShopCat['label'][$key] = '';
	$dat3[$key] = array($glsr['td'],$glsr['nt'],$glsr['sd']);
	foreach($dat3[$key] as $k=>$val) $contentShopCat['label'][$key] .= maket::spanclasstr($val,$Pth,'item-product__label','div');
	foreach($value['sections'] as $k=>$val) {
		$contentShopCat['sub'][$key]['dat'][$k]=$val['name'];
		$contentShopCat['sub'][$key]['href'][$k]='./?id='.$val['id'];	
	}
}

//$arrNews = $sw->getnews2(0,'news');
//debug($arrNews);
//die();
/*
$hrefnews = './news';
$hrefozs = './oz';
$arrReviews = $sw->getnews2(0,'reviews');
//debug($arrReviews);
$dateNews = array($arrNews[0]['date'],$arrNews[1]['date']);
$date1[0]=explode('-',$dateNews[0]);
$date1[1]=explode('-',$dateNews[1]);
$dateNews[0] = getdate(gmmktime (0, 0, 0, $date1[0][1], $date1[0][2], $date1[0][0]));
$dateNews[1] = getdate(gmmktime (0, 0, 0, $date1[1][1], $date1[1][2], $date1[1][0]));
$newsDat['date'] = array('<div class="news-side__data"><span>'.$dateNews[0]['mday'].'</span>'.$dateNews[0]['month'].'</div>','<div class="news-side__data"><span>'.$dateNews[1]['mday'].'</span>'.$dateNews[1]['month'].'</div>');
$newsDat['href'] = array($hrefnews.'#id1',$hrefnews.'#id2');

$callDat['date'] = array('<div class="reviews-side__data">'.$arrReviews[0]['date'].'</div>','<div class="reviews-side__data">'.$arrReviews[1]['date'].'</div>');
$callDat['href'] = array($hrefozs.'#id1',$hrefozs.'#id2');

$contentNews = show::showBlogItem('news', $newsDat,0).show::showBlogItem('news', $newsDat,1); 
$contentOtz = show::showBlogItem('reviews', $callDat,0,'a','right').show::showBlogItem('reviews', $callDat,1,'a','right');
*/
//Меню выбора категорий и поиска 
foreach ($contentShopCat['dat'] as $i=>$val) {
    if($i<4 ) $contentSF[0]['dat'][$i] = '<label for="" class="'.$clasShop['search'][0].'-search__checkbox checkbox">
    <input data-error="Ошибка" type="checkbox" class="checkbox__input" value="">
    <span class="checkbox__text"><span>'.$val.'</span></span>
    </label>';
    if($i<9 && $i > 3) $contentSF[1]['dat'][$i] = '<label for="" class="'.$clasShop['search'][0].'-search__checkbox checkbox">
    <input data-error="Ошибка" type="checkbox" class="checkbox__input" value="">
    <span class="checkbox__text"><span>'.$val.'</span></span>
    </label>';
    if($i<13 && $i > 8 ) $contentSF[2]['dat'][$i] = '<label for="" class="'.$clasShop['search'][0].'-search__checkbox checkbox">
    <input data-error="Ошибка" type="checkbox" class="checkbox__input" value="">
    <span class="checkbox__text"><span>'.$val.'</span></span>
    </label>';
    }
foreach ($contentSF as $key=>$val) $contentCategories[$key] = maket::viewdatapage($val,$clasShop['search'][0].'-search',$Pth,'','ul');     
foreach($arrmain['imgs'] as $val) if(!empty($val)) $imgs[] = $val;
foreach ($arrmain['imgt'] as $val) 	if(!empty($val))$titleBodySlider[] = maket::part_texts($val);
$contentSlider['head'] = array(
	'<div class="content-mainslider__title"><span>'.$titleBodySlider[0][0].'</span>'.$titleBodySlider[0][1].'</div>',
	'<div class="content-mainslider__title"><span>'.$titleBodySlider[1][0].'</span>'.$titleBodySlider[1][1].'</div>',
	'<div class="content-mainslider__title"><span>'.$titleBodySlider[2][0].'</span>'.$titleBodySlider[2][1].'</div>');
	
	$contentSlider['body'] = array (
	'<div class="content-mainslider__text text-mainslider">
	<p><span class="text-mainslider__text1">'.$titleBodySlider[0][2].'</span> '.$titleBodySlider[0][3].'</p>
	<p><span class="text-mainslider__text2">'.$titleBodySlider[0][4].'</span></p>
	<p>'.$titleBodySlider[0][5].' <span class="text-mainslider__text3">'.$titleBodySlider[0][6].'</span></p>
	</div>',
	'<div class="content-mainslider__text text-mainslider">
	<p><span class="text-mainslider__text1">'.$titleBodySlider[1][2].'</span> '.$titleBodySlider[1][3].'</p>
	<p><span class="text-mainslider__text2">'.$titleBodySlider[1][4].'</span></p>
	<p>'.$titleBodySlider[1][5].' <span class="text-mainslider__text3">'.$titleBodySlider[1][6].'</span></p>
	</div>',
	'<div class="content-mainslider__text text-mainslider">
	<p><span class="text-mainslider__text1">'.$titleBodySlider[2][2].'</span> '.$titleBodySlider[2][3].'</p>
	<p><span class="text-mainslider__text2">'.$titleBodySlider[2][4].'</span></p>
	<p>'.$titleBodySlider[2][5].' <span class="text-mainslider__text3">'.$titleBodySlider[2][6].'</span></p>
	</div>');
	$contentSlider['foot'] = array(
	'<div class="content-mainslider__footer"><div class="content-mainslider__price">'.$titleBodySlider[0][7].'</div><a href="" class="content-mainslider__button"><span>'.$glsr['id'].' </span></a></div>',
	'<div class="content-mainslider__footer"><div class="content-mainslider__price">'.$titleBodySlider[1][7].'</div><a href="" class="content-mainslider__button"><span>'.$glsr['id'].' </span></a></div>',
	'<div class="content-mainslider__footer"><div class="content-mainslider__price">'.$titleBodySlider[2][7].'</div><a href="" class="content-mainslider__button"><span>'.$glsr['id'].'</span></a></div>');
	$contentSlider['img'] = array(
	'<div class="mainslider__image _ibg"><img src="./images/'.$imgs[0].'" alt=""></div>',
	'<div class="mainslider__image _ibg"><img src="./images/'.$imgs[1].'" alt=""></div>',
	'<div class="mainslider__image _ibg"><img src="./images/'.$imgs[2].'" alt=""></div>');
	//foreach($contentSlider as $key=>$val) 
	for($i=0;$i<count($contentSlider['img']); $i++) {
		if($contentSlider['img'][$i] != '')$contSlider[$i] = maket::showOneSlide($contentSlider, $i);
	}
//Слайдер каталога популярные товары
for($i=0;$i<9;$i++){
	$contentProduct['head'][$i] = maket::spanclasstr('<img src="./images/'.$imgGalerySlider[1][$i].'" alt="">',$Pth,$clasShop['hover'][0].'__image','a href=""');
	$contentProduct['body'][$i] = maket::divShopOptions($Pth,$clasShop['hover'][0],$titleGalerySlider[$i],$priceoldGalerySlider[$i],$priceGalerySlider[$i],$stockGalerySlider[$i]);
	$contentProduct['hover'][$i] = maket::divHoverOptions($Pth,$clasShop['hover'][0],$titleGalerySlider[$i],
	$namparsGalerySlider[$i],$parsGalerySlider[$i],$priceoldGalerySlider[$i],$priceGalerySlider[$i],
	$stockGalerySlider[$i]).'</div>';
}
//Слайдер каталога
// $j=0;
// for($i=0;$i<18;$i++){
    // if($i < 9) $j=$i;
    // elseif($i < 18) $j = $i-9;
    // else $j = 0;
    // if (intval($stockGalerySlider[$j]>0)) $skld = 'в наличии';
    // else $skld = 'под заказ';
// $contentCatProduct['head'][$i] = 
// '<a href="" class="item-product__image">
// <img src="./images/'.$imgGalerySlider[1][$j].'" alt="">
// </a>';
// $contentCatProduct['body'][$i] =
// '<div class="item-product__body">
// <a href="" class="item-product__title"><span>'.maket::part_texts($titleGalerySlider[$j])[0].'</span>
// '.maket::part_texts($titleGalerySlider[$j])[1].'</a>
// <div class="item-product__footer">
// <div class="item-product__oldprice">'.$priceoldGalerySlider[$j].'</div>
    // <div>
            // <a href="" class="item-product__add">
                // <img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
            // </a>
    // </div>        
    // <div class="item-product__price">'.$priceGalerySlider[$j].'</div>        
// </div>     
// </div>';
// $j++;
// }

for($i=0;$i<count($contentProduct['head']); $i++){
    if($contentProduct['head'][$i] != ''){
		//if(!isset($contentCatProduct['hover'][$i])) $contentCatProduct['hover'][$i]='';    
		$contProduct[$i] = $contentProduct['head'][$i].$contentProduct['body'][$i].$contentProduct['hover'][$i];
		//$contProductCat[0][$i] = $contentCatProduct['head'][$i].$contentCatProduct['body'][$i].$contentCatProduct['hover'][$i];
		//$contProductCat[1][$i] = $contentCatProduct['head'][$i].$contentCatProduct['body'][$i].$contentCatProduct['hover'][$i];
		//$contProductCat[2][$i] = $contentCatProduct['head'][$i].$contentCatProduct['body'][$i].$contentCatProduct['hover'][$i];
	}
}

$breadcrumbs['dat'] = array('Главная','Каталог товаров');
$breadcrumbs['href'] = array('/','');
//Слайдер брендов
$brands = $db->getAll('brends');
foreach($brands as $val) $imgGalerySlider[2][] = $val->img;
$ContText = '';
foreach($imgGalerySlider[2] as $k=>$val) $contentBrend[] = '<img id="pic'.$k.'" src="./images/'.$val.'" alt="">';
foreach($arrmain['cont'] as $k=>$val) {
	if($k < 5)	$ContText .= '<p>'.$val.'</p>';
	elseif($k==5) $ContTextLabel = $val;
	else $ContText2['dat'][] = $val;
}

$ContText3 = maket::viewdatapage($ContText2,$clasShop['search'][3].'-block',$Pth,'','ul','_li');
$contTextBlock ='<div class="'.$clasShop['search'][3].'-block__row">
<div class="'.$clasShop['search'][3].'-block__column">'.$ContText.'</div>
<div class="'.$clasShop['search'][3].'-block__column">
<h2 class="'.$clasShop['search'][3].'-block__label">'.$ContTextLabel.'</h2>'.$ContText3.'
<div class="'.$clasShop['search'][3].'-block__image ">
    <img src="images/'.$arrmain['imgs'][3].' " alt="bicycl">
</div>
</div>
</div>';
//Меню информации и помощи
$datInfo['dat'] = array('Бренды','Доставка','Распродажа','Контакты','Отзывы');
$datInfo['href'] = array('options.html','options.html#movie','options.html#sale',
'options.html#contacts','blogs.html#rewiew');
$datInfo['typesite'] = 'spa'; 
$datHelp['dat'] = array('Как заказать','Оплата','Спецпредложения','Гарантия','Возврат'); 
$datHelp['href'] = array('info.html#order','options.html#pay','info.html#spec',
'options.html#warrant','info.html#back');
$datHelp['typesite'] = 'spa';
$contentInfo = '<div class="'.$clasShop['search'][4].'-menu__line">
<div class="'.$clasShop['search'][4].'-menu__label">'.$glsr['if'].'</div>'.maket::viewdatapage($datInfo,$clasShop['search'][4].'-menu',$Pth,'','ul').'
</div>';
$contentHelp = '<div class="'.$clasShop['search'][4].'-menu__line">
<div class="'.$clasShop['search'][4].'-menu__label">'.$glsr['hp'].'</div>'.maket::viewdatapage($datHelp,$clasShop['search'][4].'-menu',$Pth,'','ul').'
</div>';
//подвал

$datFoot = array('logo'=>
'<a href="" class="logo-footer">
<img src="./images/'.$arrmain['namep'][1].'" alt="">
<div class="lozung_footer">'.$arrmain['namep'][2].'</div>
</a>',
'phones'=>
'<div class="block-footer__phones">
<p><a href="" class="block-footer__phone"></a>'.$arrmain['owner']->telmain.'</p>
<p><a href="" class="block-footer__phone"></a>'.$arrmain['owner']->tels.'</p>
</div>',
'pay'=> $contentSite['pay'],
'mov'=> $contentSite['deliv']['block'],
'widget'=> $contentSite['widget'],
'copy'=> $contentSite['copy'],
'social'=> $contentSite['soc']);
$contentFooter = '
<div class="'.$clasShop['footer'][0].'__content _container">
    <div class="'.$clasShop['footer'][0].'__body">
        <div class="'.$clasShop['footer'][0].'__column">
            <div class="'.$clasShop['footer'][0].'-block block-'.$clasShop['footer'][0].'">
                <div class="block-'.$clasShop['footer'][0].'__column '.$clasShop['footer'][2].'">'.$datFoot['logo'].$datFoot['phones'].$datFoot['pay'].'
                </div>   
                <div class="block-'.$clasShop['footer'][0].'__column '.$clasShop['footer'][5].'">'.$datFoot['mov'].'</div>
            </div>     
        </div>
        <div class="'.$clasShop['footer'][0].'__column '.$clasShop['footer'][4].'">'.$datFoot['widget'].'</div>
        </div>
    <div class="'.$clasShop['footer'][0].'__bottom '.$clasShop['footer'][6].'">'.$datFoot['copy'].$datFoot['social'].'</div>
</div>';
$catIconsDiv = '<div class="view-catalog__item view-catalog__item_grid"></div><div class="view-catalog__item view-catalog__item_list"></div>';
//!вывод информации в браузер
//debug($armain['typmen']);
if($arrmain['typmen'][4] != 'nhd')echo show::showShopHeader($Pth,$arrmain,$clasShop);

//debug($contProduct[0]);
//die();
echo maket::divclasstr($clasShop['main'][1],$Pth,'','','main').maket::divclasstr($clasShop['main'][1].'__container '.$clasShop['main'][0],$Pth);
if($arrmain['typmen'][11] != 'nsl'){
	echo maket::divclasstr($clasShop['main'][1].'__'.$clasShop['main'][2],$Pth,'','','aside');    
//echo '<aside class="'.$clasShop['main'][1].'__'.$clasShop['main'][2].'">';

	echo show::showShopCatMain($Pth,$contentShopCat,$clasShop['cat']);		

	echo '<div data-da="page__content,last,992" class="page__content-side">';
	echo maket::div2Blockstr($Pth,$contentNews,'<a href="'.$hrefnews.'" class="news-side__title side-title">'.$glsr['nw'].'</a>','page__news-side news-side','news-side__items');    
	echo maket::div2Blockstr($Pth,$contentOtz,'<a href="'.$hrefozs.'" class="reviews-side__title side-title">'.$glsr['oz'].'</a>','page__reviews-side reviews-side','reviews-side__items');
	echo '</div></aside>';            
}
if($arrmain['typmen'][1] != 'nbl'){
	echo maket::divclasstr($clasShop['main'][1].'__content',$Pth);// '<div class="'.$clasShop['main'][1].'__content">';
	if($arrmain['typmen'][6] != 'nfb')echo show::showformSearches($clasShop['search'][0].'-search',$contentCategories);
	if($arrmain['typmen'][13] != 'nac')echo show::showSwipSliders($contSlider);
	if($arrmain['typmen'][7] != 'nsw'){
		echo '<div class="page__'.$clasShop['search'][2].' '.$clasShop['search'][2].'-slider">';
		echo show::showSwipSliders($contProduct,$clasShop['search'][2].'-slider',$clasShop['search'][2].'-slider__arrow',$arrloz[0]);
		echo '</div>';
	}
	echo '</div>';//<!--page-content-->
	echo '</div>';//<!--page__container _container-->
	echo '</div>';
}
if($arrmain['typmen'][9] != 'nga')echo show::showSwipSliders($contentBrend,$clasShop['search'][1].'-slider',$clasShop['search'][1].'-slider__arrow');
if($arrmain['typmen'][12] != 'nsc'){
	echo '<section class="page__'.$clasShop['search'][3].' '.$clasShop['search'][3].'-block">';
	echo maket::div2Blockstr($Pth,'<h1 class="'.$clasShop['search'][3].'-block__title">'.$glsr['ac'].'</h1>'.$contTextBlock,'',$clasShop['search'][3].'-block__container _container',$clasShop['search'][3].'-block__body');    
	echo '</section>';
}	
if($arrmain['typmen'][10] != 'nsr'){
	echo maket::div3Blockstr($Pth,$contentInfo.$contentHelp,'page__'.$clasShop['search'][4].'-menu '.$clasShop['search'][4].'-menu','','page__'.$clasShop['search'][4].'-menu '.$clasShop['search'][4].'-menu',$clasShop['search'][3].'-menu__body');
}
if($arrmain['typmen'][5] != 'nft')echo '<footer class="footer">'.$contentFooter.'</footer>';
echo '</main>';
//загрузка js	
?>