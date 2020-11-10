<?php
//!Классы проекта
$id = array();
$clasShop['main'] = array('_container','page');
$clasShop['header'] = array('contacts-header','menu-page','header');
$clasShop['navmenu'] = array('bottom-header__actions','actions-header');
$clasShop['footer'] = array('footer','logo','phones','phone','widget','mov','social');
$clasShop['search'] = array('categories','brands','products','text','info');
$mainLoz = 'main lozung';
$tel1 = '8-925-505-34-21';
$tel2 = '8-800-1234567';
$dat1['typesite'] = 'spa'; 
$dat1['dat']=array('Бренды','Распродажа','Доставка','Гарантия',
'Оплата','Контакты');
$dat1['href'] = array('options.html','options.html#sale','options.html#movie',
'options.html#warrant','options.html#pay','options.html#contacts');
$dat2['href'] = array('#opt1','#opt2','#opt3','#opt4');
$dat3 = array($glsr['td'],$glsr['nt'],$glsr['sd']);
$breadcrumbs['dat'] = array('Главная','Каталог товаров');
$breadcrumbs['href'] = array('/','');
$contenTop = maket::viewdatapage($dat1,'menu',$Pth,'','ul');
$contscts = '<div class="contacts-header__label">Москва</div><a href="tel:'.$tel1.'" class="contacts-header__phone">'.$tel1.'</a>';		
$contactadd = '<a href="tel:'.$tel2.'" class="contacts-header__phone">'.$tel2.'</a>';
$contLogo = show::showlogo('top-header__logo','',$Pth,8);
$clasNM = array('bottom-header__actions','actions-header');
$navMenu['dat'] = array('<span>'.$glsr['in'].'</span>',
'<span>'.$glsr['rg'].'</span>',
'<span>'.$email.'</span>');
$navMenu['href'] = array('./auth/','./registration','mailto:'.$email);
$navMenu['typesite'] ='spa';
//из глоссария стандартные опции магазина
$navMenu1['dat'] = array('<span>'.$glsr['cl'].'</span>',
'<span><p><span>'.$glsr['ww'].'</span>'.$glsr['dw'].'</p>'.
'<p><span>'.$glsr['ss'].'</span>'.$glsr['ds'].'</p></span>');

$optMenu['dat'] = array('<a href="" class="info-header__callback">
<img class="user-header__icon"style="width: 16px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
'.$navMenu1['dat'][0].'</a>',
'<div class="info-header__schedule">
<div>'.$navMenu1['dat'][1].'</div></div>',
'<a href="" class="info-header__cart">
<img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAYAAAA7MK6iAAAABmJLR0QA/wD/AP+gvaeTAAADxklEQVRIib2VS0xcVRjH/+cehhkYOiOPDkYsJhiNaSEQFy7cddMmxoULd5ooxcw0xmDpQoWNk5RasDVt1KQyQGSh0cQmNmpMNG2MXRBjCi2PlmoZqETAeXHncee+zzmuxsAUhgsM/pObfOf7/vf+7uv7DgGArpGeOibXHnPL/oTE+eLlgVOLABHYR5GukZ46l6dm5pEqn1+OabNYOjAHgmZBaTDS3x3dL7BkkMpDtV6fp+Ppp7yS37aHBno6bSFC4GwsGBxy7Rv4i67BqbV8ZvTX27fGdcMKAsDowOl5IshPol47vl/gCgAYerX/nYcqHDeIhOMAftg38GYSVfZdQAy/NvreXcJ5lFAa/fzEuUS5wKRUMXjmvNl+NEBkNadklbypGTpjnOmESHEI/Klzc8I2rTkm6EI1W/srEopYZQGH+i9kXnj5iK/KU7khb1oWFE1DTlORU/NaOq/ks3mNGZYhOBc6pdI8CCbzmj4BTqKkQo+OdV5KOwafHBic7niuua2lJeD0QcA5/++msqpiZBU1m1YV2zBNxhjXBcSiaRqvb/mNAcCG9Xv8n+yRlpaA5BQsSRJ8Xi98Xi+acNAN4OD6+tXxGzUVdjpR8oIWwS/ppGYU52OyjLyuOY4L0kwTnJPFSChilQRXc/qjprCHPDE5BUXTHccFraaSjDHrCgCUBF/u7ZWZXb6RvRSPJS1ufr8tGAAIFUo2o+4ZKiAg53LGWOf5+47AoPz+ympmz+C0ooAQ3CystwXbYOPxeNbxYNhKK8mEpprq147BEsS1bMqw1+caa+tRU+VxHAPAUjyepsy+XliX7GMASOvWdco2/tmNtbU7ihnnMEwzM/rGxTXH4G/CYfPkmQt8JZUCKTnnttZqKqUyzq+sz20LBgDGcOu3yXsP4LFzuwFbnE1HF12RHYOJWXGVLfj+GD536rvdgDeToxksIGYJeGu5oM7BNp0RIP8/eOTD7r+JEE+Ew2HHu1RZwAAgCPl2Wfe/Wy7wDhpEkFDfpbNC4HlKqSXAk9wiU4SITXcRQkSdVEE7BOcLnOGBEOSryODbS4X6Dl4dEUMf9PR53J6a1sPPHG0+9PhLlR7aziEmig8m+D13ledEe1vrMb/f9wokolPi2tCKjtppwwku6dGmpsdowArQWCzx5PDAW9eKPcG+i882NNSjsTEAAAeUuTs1n77/prwnMLPFzzcnp17UdV0w2/5oU1OyeibuTi5Pz97BWkrWbc3+stiyqyEY6v34MJHszGdnTy9v5QkGh1xoUNvclXT+k3B3trj+L3N4AU8Y9iHuAAAAAElFTkSuQmCC"/>
    <span>12</span>
</a>'); 
$opt = '';
foreach ($optMenu['dat'] as $val)$opt .='<div class="info-header__column">'.$val.'</div>'; 
$opts=maket::spanclasstr($opt,$Pth,'bottom-header__info info-header','div');

//Иконки
$Icons[0] = '<img class="icon-page__icon"style="width: 24px;"src="./images/icons/align-justify-solid.svg" alt="user-header">
<span class="close">&times;</span>';
// Новости из таблицы news
$dateNews = array('19.09.2020','5.08.2020');
$date1[0]=explode('.',$dateNews[0]);
$date1[1]=explode('.',$dateNews[1]);

$dat4['dat'] = array('Беговые дорожки','Эллиптические тренажеры','Велотренажеры',
'Гребные тренажеры','Вибромассежеры','Баскетбол','Массажные кресла',
'Силовые тренажеры','Батуты','Детские городки','Дачная мебель','Уличные комплексы','Аксессуары');
//$dat4['typesite'] = 'spa';
foreach($dat4['dat'] as $k=>$val ) $dat4['href'][$k] = './?idcat=#cat'.$k;
foreach($dat4['dat'] as $key=>$val){
    $dat4['sub'][$key]['dat'] = array('Всепогодный '.$key,'Для помещений '.$key,'Профессиональный '.$key,'Любительский '.$key);
    $dat4['sub'][$key]['href'] = array('./?idsubcat='.$key.'#opt1','./?idsubcat='.$key.'#opt2','./?idsubcat='.$key.'#opt3','./?idsubcat='.$key.'#opt4');
}
$dat4['sub'][1]['dat'] = array('Всепогодный ','Для помещений ','Профессиональный ');
$dat4['sub'][3]['dat'] = array('Всепогодный ','Для помещений ','Профессиональный ','Любительский ','Универсальный');
$dat4['sub'][1]['href'] = array('#opt1','#opt2','#opt3');
$dat4['sub'][3]['href'] = array('#opt1','#opt2','#opt3','#opt4','#opt5');

$img = array('logo.png','bicycl.png');

$dateNews[0] = getdate(gmmktime (0, 0, 0, $date1[0][1], $date1[0][0], $date1[0][2]));
$dateNews[1] = getdate(gmmktime (0, 0, 0, $date1[1][1], $date1[1][0], $date1[1][2]));
$dateNews['date'] = array($date1[0][2].'-'.$date1[0][1].'-'.$date1[0][0],
$date1[1][2].'-'.$date1[1][1].'-'.$date1[1][0]);
//debug($dateNews['date']);
$hrefnews = './news';
$newsDat['text'] = array('Уважаемые покупатели, мы рады сообщить вам о сниженеие цен на игровые комплексы.',
'Скидки на все теннисные столы 20%! Акция продлится до конца текущего месяца.',);
$newsDat['name'] = array('Снижение цен.', 'Скидки на тенисные столы');
$newsDat['date'] = array('<div class="news-side__data"><span>'.$dateNews[0]['mday'].'</span>'.$dateNews[0]['month'].'</div>','<div class="news-side__data"><span>'.$dateNews[1]['mday'].'</span>'.$dateNews[1]['month'].'</div>');
$newsDat['href'] = array($hrefnews.'#id1',$hrefnews.'#id2');

//Отзывы из таблицы blogs
$dateReviews['date'] = array('1.09.2020','13.08.2020');

$hrefozs = './oz';
$callDat['text'] = array('Ради экономии места в тренажерном зале купил многофункциональный силовой тренажер Life Gear. За такаую небольшую цену и с такими воможностями он просто не заменим.',
'Ради экономии места в тренажерном зале купил многофункциональный силовой тренажер Life Gear. За такаую небольшую цену и с такими воможностями он просто не заменим.',);
$callDat['name'] = array('Павел Никифоров', 'Степан Николаев');
$callDat['date'] = array('<div class="reviews-side__data">'.$dateReviews['date'][0].'</div>','<div class="reviews-side__data">'.$dateReviews['date'][1].'</div>');
$callDat['href'] = array($hrefozs.'#id1',$hrefozs.'#id2');
$contentNews = show::showBlogItem('news', $newsDat,0).show::showBlogItem('news', $newsDat,1); 
$contentOtz = show::showBlogItem('reviews', $callDat,0,'a','right').show::showBlogItem('reviews', $callDat,1,'a','right');

//Меню выбора категорий и поиска 
foreach ($dat4['dat'] as $i=>$val) {
    if($i<4 ) $contentSF[0]['dat'][$i] = '<label for="" class="categories-search__checkbox checkbox">
    <input data-error="Ошибка" type="checkbox" class="checkbox__input" value="">
    <span class="checkbox__text"><span>'.$val.'</span></span>
    </label>';
    if($i<9 && $i > 3) $contentSF[1]['dat'][$i] = '<label for="" class="categories-search__checkbox checkbox">
    <input data-error="Ошибка" type="checkbox" class="checkbox__input" value="">
    <span class="checkbox__text"><span>'.$val.'</span></span>
    </label>';
    if($i<13 && $i > 8 ) $contentSF[2]['dat'][$i] = '<label for="" class="categories-search__checkbox checkbox">
    <input data-error="Ошибка" type="checkbox" class="checkbox__input" value="">
    <span class="checkbox__text"><span>'.$val.'</span></span>
    </label>';
    }
foreach ($contentSF as $key=>$val) $contentCategories[$key] = maket::viewdatapage($val,'categories-search',$Pth,'','ul');     

//карточка товара
$arrProductCard['img'] = array('runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg');
$arrProductCard['disc'] = array('-5%','-15%','-50%','-25%','-10%');
$arrProductCard['alt'] = array('img','img','img','img','img');
//$arrProductCard1['img'] = array('runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg','runroad.jpg');
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
<img src="./images/'.$img[0].'" alt="">
<div class="lozung_footer">'.$mainLoz.'</div>
</a>',
'phones'=>
'<div class="block-footer__phones">
<p><a href="" class="block-footer__phone"></a>'.$tel1.'</p>
<p><a href="" class="block-footer__phone"></a>'.$tel2.'</p>
</div>',
'pay'=> $contentSite['pay'],
'mov'=> $contentSite['deliv']['block'],
'widget'=> $contentSite['widget'],
'copy'=> $contentSite['copy'],
'social'=> $contentSite['soc']);
$contentFooter = '
<div class="footer__content _container">
    <div class="footer__body">
        <div class="footer__column">
            <div class="footer-block block-footer">
                <div class="block-footer__column">'.$datFoot['logo'].$datFoot['phones'].$datFoot['pay'].'
                </div>   
                <div class="block-footer__column">'.$datFoot['mov'].'</div>
            </div>     
        </div>
        <div class="footer__column">'.$datFoot['widget'].'</div>
        </div>
    <div class="footer__bottom">'.$datFoot['copy'].$datFoot['social'].'</div>
</div>';