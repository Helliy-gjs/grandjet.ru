<?php

//! Выгрузка персональных данных макета сайта в базу данных	
$number_value_tab = 0;
$arrFN[0] = $number_value_tab +1;
$arrFN[1] = 'FeedbackForm';
$arrFN[2] = 'post';
$arrFN[3] = 'http://formspree.io/grandjetstudio@gmail.com';
$arrFN[4] = $Pth['adm']['uid'];
$arrFN[5] = $Pth['adm']['ids'];
$arrFN[6] = $Pth['adm']['idm'];
//debug($arrFN);
// Запись формы 

$close_field = 3;
$table = 'nameform';
$arrfields=$sw->getallfieldtable($table);
$fields=$arrfields['field'];
$field = 'id';
$db->gjsapi($Pth,$table,$arrFN,$fields);

$arrF['js'] = array('data-validation-required-message','data-validation-required-message','data-validation-required-message');
$arrF['cls'] = array('main_form','form-group','color_element');
$arrF['type'] = array('text','email','textarea');
$arrF['place'] = array('имя','email','введите сообщение');
$arrF['req'] = array('required','required','required');
$arrF['name'] = array('name','email','message');
$arrF['label'] = array($glsr['yn'].':',$glsr['ye'].':',$glsr['ym'].':',$glsr['sd']);
$arrF['valid'] = array($glsr['en'],$glsr['ee'],$glsr['em']);
//debug($arrF);
//Запись полей формы
$number_value_tab = 0;
$close_field = 1;
$table = 'forms';
$arrfields=$sw->getallfieldtable($table);
$fields=$arrfields['field'];
$field = 'id';
foreach($arrF['name'] as $i=>$val) {
    $arrFF = array($number_value_tab+1,$arrFN[0],$val,$arrF['type'][$i],
    $arrF['place'][$i], $arrF['req'][$i],$val,$arrF['cls'][$i],
    $arrF['js'][$i],$arrF['valid'][$i],$arrF['label'][$i]);
    $db->gjsapi($Pth,$table,$arrFF,$fields);
}

//Запись макета в базу данных
//Селекторы, идентификаторы и классы
$maket_Form = $arrFN[0].'|';
$Maket_length = array(count($id),count($clas0),count($clas2),count($clas1));
$Maket_Properties = maderec($id,1,',').maderec($clas0,1,',').maderec($clas2,1,',').maderec($clas1,1,',').'*'.maderec($Maket_length,1,',');
// Запись окружения в базу данных
//Окружение
if(!isset($Style_pages)) $Style_pages = array(
    'fontsland','mainland','skins/purple','medialand'
);
if(!isset($Pth['global']['styles'])) $Pth['global']['styles'] =  array(
    'bootstrap/bootstrap-grid.min.css',
    'font-awesome/css/font-awesome.min.css',
    'linea/styles.css',
    'magnific-popup/magnific-popup.css',
    'animate/animate.min.css');

$Scrpt_libs = array(
    'jquery/jquery-2.1.3.min.js',
    'parallax/parallax.min.js',
    'magnific-popup/jquery.magnific-popup.min.js',
    'mixitup/mixitup.min.js',
    'scroll2id/PageScroll2id.min.js',
    'waypoints/waypoints.min.js',
    'animate/animate-css.js',
    'jqBootstrapValidation/jqBootstrapValidation.js');

$scrips = maderec($Pth['global']['styles'],1).maderec($Scrpt_libs,1);
//debug(scrips);
if($numpage == 0)Maket::addnewGlbMaket($idmaket,'land-'.($numpage+1),1,1,$db,$Maket_Properties,$maket_Form,$scrips);
else Maket::addnewGlbMaket($idmaket,$disp,$numpage,$Site->ids,$db,$Maket_Properties,$maket_Form,$scrips); 
$scrps = explode(';',$scrips);
$action = 'new';
$number_value_tab = 0;
$close_field = 0;
$table = 'scripts';
$arrfields=$sw->getallfieldtable($table);
$fields=$arrfields['field'];
$field = 'id';
foreach($scrps as $key=>$val){
    $arsc = explode('/',$val);
    $arty = explode('.',$val);
    $arrscr[0] = $key;
    $arrscr[1] = $arsc[0];
    $arrscr[2] = 'f';
    $arrscr[3] = $arty[count($arty)-1];
    $arrscr[4] = substr_replace($val,'',-strlen($arrscr[3])-1);
    $arrscr[5] = 'us|nbl';
    $arrscr[6] = $Site->ids;
    $arrscr[7] = $uid;
    $arrscr[8] = $idmaket;
    $db->gjsapi($Pth,'scripts',$arrscr,$fields);
}
$Scrpt_page = array('common');	
//!Преобразование контента страницы в массивы для записи в базу данных
$arrcont='';$tt='|';
foreach($about as $k=>$val) {
    $arrcont.=$val.';';
    $tt .=';';
}
foreach($blog as $k=>$val) {
    $arrcont.=$val.';';
    $tt .=';';
}
//print_r($arrcont);
//var_dump($array);
if($startpage) $link_pages=$startpage.';'.$startpage.';'.$startpage.';'.$startpage.';'.$startpage;
else  $link_pages = ';;;;';
    $array[0]= 1;
    $array[1]= '';
    $array[2] = maderec($arrloz);
    $array[3] = 'keywords1>keywords2>keywords3;title_page;description_page';
    $array[4] = maderec($dat1['dat']);
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
    $array[14] = maderec($text,1);
    $array[15] = $link_pages;
    $array[16] = 'footer1;footer2;footer3;footer4;footer5;|'.$link_pages;
    $array[17] = maderec($datSoc['dat'],1).maderec($datSoc['icon'],1);
    $array[18] = maderec($blog1);
    $array[19] = 0;
    $array[20] = $Site->ids;
    $array[21] = $uid;
    $array[22] = '1|unlimit|'.utils::getConfig(4,'configp',1);
//!Запись в базу данных		
    //$db->gjsapi('pages',$array);
    //if(file_exists(CLASSES.'/gjsapi.inc')) include(CLASSES.'/gjsapi.inc');
    //debug($array);
    $db->insert_tab($Pth,'pages',$array);
?>    