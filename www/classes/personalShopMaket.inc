<?php
//echo '-> запись данных в базу';
//debug($clasShop);
//! Выгрузка персональных данных макета сайта в базу данных	
//die('i am here');
//Загрузка формы

//Запись полей формы
$uid = 1;
$maket_Form = array();

//Запись макета в базу данных
$Maket_Properties = maket::setClassesMaket($clasShop);
$maket = 'shop-1';
//debug($Maket_Properties);
//show::pauza('i am here '.$numpage);
//$Maket_length = array(1,count($clasShop['main']),count($clasShop['header']),count($clasShop['navmenu'])
//,count($clasShop['cat']),count($clasShop['hover']),count($clasShop['search']),count($clasShop['footer']));
//$Maket_Properties =','.maderec($clasShop['main'],1,',').maderec($clasShop['header'],1,',').maderec($clasShop['navmenu'],1,',')
//.maderec($clasShop['cat'],1,',').maderec($clasShop['hover'],1,',').maderec($clasShop['search'],1,',')
//.maderec($clasShop['footer'],1,',').'*'.maderec($Maket_length,1,',');
//if($numpage == 0)Maket::addnewGlbMaket($idmaket,'shop-'.($numpage+1),1,1,$db,$Maket_Properties,$maket_Form,$scrips);
//else Maket::addnewGlbMaket($idmaket,$disp,$numpage,$Site->ids,$db,$Maket_Properties,$maket_Form,$scrips); 
//Селекторы, идентификаторы и классы

// Запись окружения в базу данных

//Окружение
$Style_pages = array('style','main','homepage','footer');
$Scrpt_page = array('wNumb.min','nouislider','swiper','script.min');
$scrips = '';
$maket_Form = '|';
if($numpage=1)Maket::addnewGlbMaket($idmaket,$maket ,$numpage,$Site->ids,$db,$Maket_Properties,$maket_Form,$scrips);
else Maket::addnewGlbMaket($idmaket + 1,$disp.'-'.$numpage,$numpage,$Site->ids,$db,$Maket_Properties,$maket_Form,$scrips); 
//!Преобразование контента страницы в массивы для записи в базу данных
//каталог брендов таблица brends
$arrbrends['name'] = array('Adidas','Nike','Puma','Reebok','UNDER ARMOUR','NEW BALANCE','FILA','CONVERSE');
$arrbrends['img'] = $imgGalerySlider[2];
$arrbrends['alias'] = array('adidas','nike','puma','reebok','underarmour','newbalanse','fila','converse');
$arrbrends['desc'] = array('немецкая транснациональная компания по производству спортивной одежды, обуви и аксессуаров. Это крупнейший производитель спортивной одежды в Европе и второй по величине в мире после Nike.',
'американская транснациональная компания, специализирующаяся на спортивной одежде и обуви. Штаб-квартира — в городе Бивертон.',
'промышленная компания Германии, специализирующаяся на выпуске спортивной обуви, одежды, инвентаря и парфюмерии под торговой маркой Puma.',
'американская компания по производству спортивной одежды, обуви и аксессуаров. Штаб-квартира расположена в Бостоне. С 2005 года является дочерним подразделением компании Adidas.',
'американский производитель и поставщик спортивной одежды и экипировки, расположенный в городе Балтимор, Мэриленд.',
'более известная как New Balance, американский производитель спортивной одежды, базирующийся в Брайтоне, одном из районов Бостона, штат Массачуссетс, США',
'южнокорейская компания — производитель и поставщик спортивной одежды, обуви и спортивных аксессуаров.',
'американская компания, производящая обувь с начала XX века и наиболее известная своими кедами Chuck Taylor All-Star. Контролируется компанией');
//$number_value_tab = 0;
$close_field = 0;
$table = 'brends';
$arrfields=$sw->getallfieldtable($table);
$fields=$arrfields['field'];
$field = 'id';
foreach($arrbrends['name'] as $key=>$val){
    $arrbr[0] = $key;
    $arrbr[1] = $val;
    $arrbr[2] = $arrbrends['alias'][$key];
    $arrbr[3] = $arrbrends['img'][$key];
    $arrbr[4] = $arrbrends['desc'][$key];
    $arrbr[5] = $numpage;
    $arrbr[6] = $Site->ids; 	
    $db->gjsapi($Pth,$table,$arrbr,$fields);
}

//популярные товары
$number_value_tab = $user->getscountab($Site->element,'id', 'c');
//if($number_value_tab == 0){
    $ts=date('U');
    $now=getdate($ts);
    $tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
    $number_value_tab = 0;
    $close_field = 0;
    $table = $Site->element;
    $arrfields=$sw->getallfieldtable($table);
    $fields=$arrfields['field'];
    $field = 'id';
    foreach($priceGalerySlider as $key=>$val){
        $arrel[0] = $key;
        $arrel[1] = 'codeGJS'.$key;
        $arrel[2] = maket::part_texts($titleGalerySlider[$key])[0].'='.maket::part_texts($titleGalerySlider[$key])[1];
        $arrel[3] = $imgGalerySlider[1][$key].'|'.maket::part_texts($titleGalerySlider[$key])[1].'|'.maket::part_texts($titleGalerySlider[$key])[2].'|'.$spisParams;
        $arrel[4] = 'art'.$key;
        $arrel[5] = 'vendor';
        $arrel[6] = $val;
        $arrel[7] = '1';
        $arrel[8] = '1';
        $arrel[9] = $stockGalerySlider[$key]; 
        $arrel[10] = $now['year'].'-'.$now['mon'].'-'.$now['mday'];
        $arrel[11] = $arrel[10];
        $arrel[12] = $Site->ids;
        $arrel[13] = $uid;
        $db->gjsapi($Pth,$table,$arrel,$fields);
    }
//}
//каталог товаров
$number_value_tab = $user->getscountab($Site->structure,'id', 'c');
//if($number_value_tab == 0){
    $close_field = 0;
    $table = $Site->structure;
    $arrfields=$sw->getallfieldtable($table);
    $fields=$arrfields['field'];
    $field = 'id';
    foreach($dat4['dat'] as $key=>$val) {
        $arrstr[0] = $key;
        $arrstr[1] = 0;
        $arrstr[2] = $val;
        $arrstr[3] = 0;
        $arrstr[4] = 0;
        $arrstr[5] = 0;
        $arrstr[6] = count($dat4['sub'][$key]['dat']);
        $arrstr[7] = 1;
        $arrstr[8] = 1;
        $arrstr[9] = '';
        $arrstr[10] = $Site->ids;
        $arrstr[11] = $uid;
        $db->gjsapi($Pth,$table,$arrstr,$fields);
        }
        foreach($dat4['dat'] as $key=>$val) {
            foreach($dat4['sub'][$key]['dat'] as $k=>$val){
            $arrsub[0] = '';
            $arrsub[1] = $key+1;
            $arrsub[2] = $val;
            $arrsub[3] = 0;
            $arrsub[4] = 0;
            $arrsub[5] = 0;
            $arrsub[6] = 1;
            $arrsub[7] = 1;
            $arrsub[8] = 1;
            $arrsub[9] = '';
            $arrsub[10] = $Site->ids;
            $arrsub[11] = $uid;
            $db->gjsapi($Pth,$table,$arrsub,$fields);
            }
        }    
  //  }
    
//новости и отзывы
$number_value_tab = $user->getscountab($Site->news,'idnews', 'c');
//if($number_value_tab == 0){
    $close_field = 0;
    $table = $Site->news;
    $arrfields=$sw->getallfieldtable($table);
    $fields=$arrfields['field'];
    $field = 'idnews';
    foreach($newsDat['name'] as $key=>$val) {
        $arrnews[0] = $uid;
        $arrnews[1] = $dateNews['date'][$key];
        $arrnews[2] = $val;
        $arrnews[3] = $newsDat['text'][$key];
        $arrnews[4] = '';
        $arrnews[5] = '';
        $arrnews[6] = 'news';
        $arrnews[7] = '';
        $arrnews[8] = '';
        $arrnews[9] = $newsDat['href'][$key];
        $arrnews[10] = $numpage;
        $arrnews[11] = $Site->ids;
        $db->gjsapi($Pth,$table,$arrnews,$fields,'new',$field);
    }
    foreach($callDat['name'] as $key=>$val) {
        $arrreviews[0] = $uid;
        $arrreviews[1] = $dateReviews['date'][$key];
        $arrreviews[2] = $val;
        $arrreviews[3] = $callDat['text'][$key];
        $arrreviews[4] = '';
        $arrreviews[5] = '';
        $arrreviews[6] = 'reviews';
        $arrreviews[7] = '';
        $arrreviews[8] = '';
        $arrreviews[9] = $callDat['href'][$key];
        $arrreviews[10] = $numpage;
        $arrreviews[11] = $Site->ids;
        $db->gjsapi($Pth,$table,$arrreviews,$fields,'new',$field);
    }
//}
//таблица pages
$number_value_tab = $user->getscountab($Site->pages,'numpage', 'c');
//if($number_value_tab == 0){
    $arrcont='';$tt='|';
    foreach($ContText1 as $k=>$val) {
        $arrcont.=$val.';';
        $tt .=';';
    }
    foreach($ContText2['dat'] as $k=>$val) {
        $arrcont.=$val.';';
        $tt .=';';
    }
    if($startpage) $link_pages=$startpage.';'.$startpage.';'.$startpage.';'.$startpage.';'.$startpage;
    else  $link_pages = ';;;;';
    $array[0]= $number_value_tab + 1;
    $array[1]= '|'.$mainLoz.'|'.$ContTextLabel.'|';
    $array[2] = maderec($arrloz);
    $array[3] = 'keywords1>keywords2>keywords3;title_page;description_page';
    $array[4] = 'button1;button2;button3;button4;button5;|'.$link_pages;
    $array[5] = '';
    $array[6] = 'nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac';
    $array[7] = maderec($Scrpt_page,1);
    $array[8] = maderec($Style_pages,1);
    if (!$startpage) $array[9]='main_gra_'.$_SERVER['HTTP_HOST'];
    else $array[9]='title_gra_'.$_SERVER['HTTP_HOST'].'_'.$array[0];
    $array[10] = $arrcont.$tt;
    $array[11] = $type_site;
    $array[12] = ';;;';
    $array[13] = maderec($imgs,1);
    $array[14] = maderec($dat1['dat'],1);
    $array[15] = $link_pages;
    $array[16] = 'footer1;footer2;footer3;footer4;footer5;|'.$link_pages;
    $array[17] = '|';
    $array[18] = maderec($textGalerySlider);
    $array[19] = 0;
    $array[20] = $Site->ids;
    $array[21] = $uid;
    $array[22] = '1|unlimit|'.utils::getConfig(4,'configp',1);

    //!Запись в базу данных	
    $db->insert_tab($Pth,'pages',$array);
//}
?>    