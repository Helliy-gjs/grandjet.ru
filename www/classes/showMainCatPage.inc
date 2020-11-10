<?php
//echo 'Интернет магазин sportshop';
$contscts = '<div class="contacts-header__label">Москва</div><a href="tel:'.$arrmain['owner']->telmain.'" class="contacts-header__phone">'.$arrmain['owner']->telmain.'</a>';		
$contactadd = '<a href="tel:'.$arrmain['owner']->tels.'" class="contacts-header__phone">'.$arrmain['owner']->tels.'</a>';
$contLogo = show::showlogo('top-header__logo','',$Pth,8);
$YourMaket = explode('|',$YourMakets[0][10]);	
$arrClasNumber = explode('*',$YourMaket[1]);	
$mainClas = explode(',',$arrClasNumber[0]);
$numbClas = explode(',',$arrClasNumber[1]);
foreach($mainClas as $i=>$val){
    if($i < $numbClas[0]) $id[] = $val;
    elseif($i < $numbClas[0] + $numbClas[1]) $clasShop['main'][] = $val;
    elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2]) $clasShop['header'][] = $val;
    elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3]) $clasShop['navmenu'][] = $val;
    elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4]) $clasShop['cat'][] = $val;
    elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4] + $numbClas[5]) $clasShop['hover'][] = $val;
    elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4] + $numbClas[5] + $numbClas[6]) $clasShop['search'][] = $val;
    elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3] + $numbClas[4] + $numbClas[5] + $numbClas[6] + $numbClas[7]) $clasShop['footer'][] = $val;
}
//debug($YourMaket);
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
//!Structure
$arrcat = $sw->getData(0,$tabl['elem'],$uid,$Site->ids);
//debug($arrcat);

foreach($arrcat['sections'] as $val) {
	$contentShopCat['dat'][$val['id']]=$val['name'];
	$contentShopCat['href'][$val['id']] = './?cat='.$val['id'];
	$arrsubcat[$val['id']] = $sw->getData($val['id'],$tabl['elem'],$uid,$Site->ids);
}
//debug($arrsubcat);
//die();
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
//debug($contentShopCat);

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

//Слайдер каталога
$j=0;
for($i=0;$i<18;$i++){
    if($i < 9) $j=$i;
    elseif($i < 18) $j = $i-9;
    else $j = 0;
    if (intval($stockGalerySlider[$j]>0)) $skld = 'в наличии';
    else $skld = 'под заказ';
$contentCatProduct['head'][$i] = 
'<a href="" class="item-product__image">
<img src="./images/'.$imgGalerySlider[1][$j].'" alt="">
</a>';
$str =  maket::part_texts($titleGalerySlider[$j]);
$contentCatProduct['body'][$i] =
'<div class="item-product__body">
<a href="" class="item-product__title"><span>'.$str[0].'</span>
'.$str[1].'</a>
<div class="item-product__footer">
<div class="item-product__oldprice">'.$priceoldGalerySlider[$j].'</div>
    <div>
            <a href="" class="item-product__add">
                <img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
            </a>
    </div>        
    <div class="item-product__price">'.$priceGalerySlider[$j].'</div>        
</div>     
</div>';
// $contentProduct['hover'][$i] = 
// '<div class="item-product__hover hover-item-product">
// <div class="hover-item-product__title">
    // <a><span>'.maket::part_texts($titleGalerySlider[$j])[0].'</span>
    // '.maket::part_texts($titleGalerySlider[$j])[1].'</a>
// </div>
// <div class="hover-item-product__options options-item-product">
    // <div class="options-item-product__item">
        // <div class="options-item-product__label">'.$namparsGalerySlider[0].$i.'</div>
        // <div class="options-item-product__value">'.$parsGalerySlider[0].$i.'</div> 
    // </div>
    // <div class="options-item-product__item">
        // <div class="options-item-product__label">'.$namparsGalerySlider[1].$i.'</div>
        // <div class="options-item-product__value">'.$parsGalerySlider[1].$i.'</div> 
    // </div>
    // <div class="options-item-product__item">
        // <div class="options-item-product__label">'.$namparsGalerySlider[2].$i.'</div>
        // <div class="options-item-product__value">'.$parsGalerySlider[2].$i.'</div> 
    // </div> 
// </div>
// <div class="hover-item-product__body">
    // <a href="" class="hover-item-product__compare"><span>Сравнить</span></a>
// </div>
// <div class="hover-item-product__footer">
    // <div class="hover-item-product__old-price">'.$priceoldGalerySlider[$j].'</div>
    // <a href="" class="hover-item-product__cart hover-item-product__cart_catalog"></a>
    // <div class="hover-item-product__price">'.$priceGalerySlider[$j].'</div>
// </div>
// </div>';
$j++;
}
for($i=0;$i<count($contentCatProduct['head']); $i++){
    if($contentCatProduct['head'][$i] != ''){
    if(!isset($contentCatProduct['hover'][$i])) $contentCatProduct['hover'][$i]='';    
    if($i < 9)  $contProdCat[0][$i] = $contentCatProduct['head'][$i].$contentCatProduct['body'][$i].$contentCatProduct['hover'][$i];
    else $contProdCat[1][$i-9] = $contentCatProduct['head'][$i].$contentCatProduct['body'][$i].$contentCatProduct['hover'][$i];
    if($i < 9)  $contProdCat[2][$i] = $contentCatProduct['head'][$i].$contentCatProduct['body'][$i].$contentCatProduct['hover'][$i];
    else $contProdCat[3][$i-9] = $contentCatProduct['head'][$i].$contentCatProduct['body'][$i].$contentCatProduct['hover'][$i];
    }
}
//debug($contProd);
// $contProducts[0] = '';
// for($i=0; $i<9; $i++){  
    // $contProducts[0] .= maket::div2Blockstr($Pth,
    // $contentProduct['head'][$i].$contentProduct['body'][$i].$contentProduct['hover'][$i],
// '','items-products__column','item-product');
// }
// $contProducts[1] = '';
// for($i=0; $i<9; $i++){  
    // $contProducts[1] .= maket::div2Blockstr($Pth,
    // $contentProduct['head'][$i].$contentProduct['body'][$i].$contentProduct['hover'][$i],
// '','items-products__column','item-product');
// }
$breadcrumbs['dat'] = array('Главная','Каталог товаров');
$breadcrumbs['href'] = array('/','');
$dat1['typesite'] = 'spa'; 
$dat1['dat']=array('Бренды','Распродажа','Доставка','Гарантия',
'Оплата','Контакты');
$dat1['href'] = array('options.html','options.html#sale','options.html#movie',
'options.html#warrant','options.html#pay','options.html#contacts');
$contenTop = maket::viewdatapage($dat1,'menu',$Pth,'','ul');

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
$contentShop = array('contact' => $contscts,'addcont'=>$contactadd,'logo'=>$contLogo,'top'=>$contenTop,'nav'=>$navMenu,'cat'=>$dat4);
$catIconsDiv = '<div class="view-catalog__item view-catalog__item_grid"></div><div class="view-catalog__item view-catalog__item_list"></div>';
//параметры фильтров
$arrCheck['section']['0'] = array();
$arrCheck['section']['1'] = array();
$arrCheck['section']['2'] = array('Clear-fit','Diadora','Hastingst','Carbon-fitness','Nordic-track');
$arrCheck['section']['3'] = array('50W','100W','250W','500W','1000W');
$arrCheck['section']['4'] = array('50','100','300','800W','1000');
$arrCheck['section']['5'] = array('нет регулировки','механическая','электрическая','электронная');
$arrCheck['Title'] = array('Цена (руб.)','Товары для сравнения','Производитель:','Мощность:','Размер бегового плотна:','Угол наклона:');
$arrCheck['spoller'] = array(0,0,1,1,1,0);
//!вывод информации в браузер
echo show::showShopHeader($Pth,$arrmain,$clasShop);
?>
<main class="page">
    <div class="page__container _container">
        <aside class="page__side">
<?php	
//debug($dat4);	
//die();
echo show::showShopCatMain($Pth,$contentShopCat,$clasShop['cat']);
echo show::filterProducts($arrCheck);
?>
</aside>            
<div class="page__content">
<?php
echo show::showformSearches('categories-search',$contentCategories);

echo maket::viewdatapage($breadcrumbs,'breadcrumbs',$Pth,'','ul','__list','__link','');

?>
<div class="catalog">
    
<?php
    echo maket::div2Blockstr($Pth,$catIconsDiv,show::showSortShop(),'catalog__actions actions-catalog','actions-catalog__view view-catalog');
    
    //echo '<div class="catalog__navi navi-catalog navi-catalog_top">'
        //.show::quantyPageItems().show::showListCatalog().'</div>';

    echo '<div class="catalog__products items-products">';
    echo show::showSwipSliderCatalog($contProdCat,'products-slider','products-slider__arrow');
    //echo $contProducts[1];
    echo '</div>
</div>
</div>
</div>';
echo maket::div3Blockstr($Pth,$contentInfo.$contentHelp,'page__info-menu info-menu','','page__info-menu info-menu','info-menu__body');
echo '<footer class="footer">'.$contentFooter.'</footer>';