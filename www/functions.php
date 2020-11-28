<?php

function debug($arr){
    echo '<pre>' . print_r($arr, true) . '</pre>';
}

function redirect($http = false){
    if($http){
        $redirect = $http;
    }else {
        $redirect = isset($_SERVER['HTTP_REFERER']) ? $_SERVER['HTTP_REFERER'] : PATH;
    }
    header($redirect);
    exit;
}

function right_access($ds) {
	
	$arrdesc=explode('|',$ds);		
	if($arrdesc[0]<>'') $ret['GA']=$arrdesc[0];
	else $ret['GA']=false;
	if($arrdesc[1]<>'') $ret['YM']=$arrdesc[1];
	else $ret['YM']=false;	
	if($arrdesc[2]=='N')$ret['PR']='http://';
	else $ret['PR']='https://';	
	if(!isset($arrdesc[3]))$ret['metr']=false;
	else $ret['metr']=true;
	
	return $ret;
}

function glossary(){

return array(
    'bd' => 'День рождения' ,
    'tn' => 'Номер телефона',
    'el' => 'E-mail',
    'ws' => 'Веб-сайт',
    'ft' => 'Фото',
    'am' => 'О себе',
    'ac' => 'О компании',
    'ic' => 'Познакомимся ближе',
    'lam' => 'Немного о себе',
    'pi' => 'Персональная информация',
    'rm' => 'Резюме',
    'kn' => 'Мои знания и достижения',
    'wr' => 'Работа',
    'st' => 'Учеба',
    'pf' => 'Портфолио',
    'lw' => 'Мои разработки',
    'dc' => 'Описание работы',
    'lk' => 'Посмотреть',
    'cn' => 'Контакты',
    'lm' => 'Оставьте ваше сообщение',
    'ad' => 'Адрес',
    'tf' => 'Телефон',
    'yn' => 'Ваше имя',
    'ye' => 'Ваш E-mail',
    'ym' => 'Ваше сообщение',
    'sd' => 'Отправить',
    'ee' => 'Не корректно введен E-mail',
    'en' => 'Вы не ввели имя',
    'em' => 'Вы не ввели сообщение',
    'bp' => 'Бессплатно по России',
    'in' => 'Вход',
    'rg' => 'Регистрация',
    'cl' => 'Обратный звонок',
    'ww' => 'Пн-Пт:',
    'ss' => 'Сб-Вс:',
    'dw' => '09:00-21:00',
    'ds' => '10:00-20:00',
    'ct' => 'Каталог товаров',
    'nw' => 'Новости',
    'oz' => 'Отзывы',
    'fd' => 'Найти',
    'cs' => 'Выбрано',
    'al' => 'Везде',
    'er' => 'Ошибка',
    'td' => 'Товар дня',
    'nt' => 'Новинка',
    'sd' =>'Скидка дня',
    'id' =>'Подробнее',
    'hp' => 'Помощь',
    'if' => 'Информация',
    'br' => 'Бренды',
    'py' => 'Оплата',
    'wr' => 'Гарантия',
    'dl' => 'Доставка',
    'sl' => 'Распродажа',
    'stc' => 'в наличии',
    'pzk' => 'под заказ',
    'pop' => 'Популярные товары'
);
}

function maderec($text,$m=0,$sel=';'){
    $aa='';$tt='|';
    if(is_array($text)){
	    foreach($text as $val) {
		    $aa.=$val.$sel;
		    $tt .=$sel; 
	    }	
	    if($m == 0)$aa.=$tt;
    }
elseif($m == 0) $aa.=$text.';|;;';
else $aa =  $text.$sel;
return $aa;
}

function part_name($str,$dlt='='){
	if(strstr($str,$dlt)) $res=explode($dlt,$str);
	else $res[0]=$str;
	return $res[0];
}

function part_text($str,$n=1,$dlt='='){
	if(strstr($str,$dlt)) $res=explode($dlt,$str);
	else $res[0]=$str;
	if(isset($res[$n])) return $res[$n];
	else return $res[0];
}

function part_texts($str){
	if(strstr($str,'=')) $res=explode('=',$str);
	else $res[0]=$str;
	return $res;
}

function mainHeader($str,$h='h2'){
    return '<'.$h.'>'.part_name($str).'</'.$h.'><p>'.part_text($str).'</p>';
}

function listContent($arr, $Pth='',$nb=0,$ne=0, $clas='', $h='h4' ,$selector='div'){
    $cont = '';
    //debug($arr);
    if($ne == 0) $ne = count($arr);
    foreach($arr as $i=>$val) {
        if($i >= $nb && $i < $ne) $cont .= Maket::spanclasstr(mainHeader($arr[$i],$h), $Pth, $clas, $selector);
    }
    return $cont;
}

function lisImages($arr, $Pth='',$nb=0,$ne=0, $clas='' ){
    $cont = '';
    if($ne == 0) $ne = count($arr);
    foreach($arr as $i=>$val) {
        if($i >= $nb && $i < $ne  && file_exists('./images/'.$arr[$i])) $cont .= Maket::spanclasstr('<img class="img-responsive" src="./images/'.$arr[$i].'" alt="photo '.$i.'">',$Pth,$clas,'div');
    }
    return $cont;
}

function listCards($arr, $Pth, $nb=0, $ne=0, $clas=''){
    $cont = '';
    $all= '';
    $item='';
    if($ne == 0) $ne = count($arr);
    //debug($arr);
    //die();
    foreach($arr['img'] as $i=>$val) {
        if($i >= $nb && $i < $ne  && file_exists('./images/'.$arr['img'][$i])) {
            $item = Maket::spanclasstr('<img class="img-responsive" src="./images/'.$arr['img'][$i].'" alt="photo '.$i.'">',$Pth,$clas,'div')
        .Maket::spanclasstr(mainHeader($arr['cont'][$i].'-'.$i,'h4'), $Pth, $clas, 'div');
        $cont = Maket::spanclasstr($item, $Pth, 'container__Cards card_'.$i,'div');
        $all .=$cont;
        }

    }
    
    return $all;
}

function whileSelect($select,$arr,$j,$nameClass,$style='',$id='id'){
	$i=0;
	$str='';
	
	$str.='<select style="'.$style.'" name="'.$nameClass.'00">';
	if(isset($select[$id])){
	while ($elem=each($select['nam'])){
		if ($select[$id][$i] == $arr[$j] ) $str.='<option selected value="'.$arr[$j].'">'.$select['nam'][$i].'</option>';
		else $str .='<option value="'.$select[$id][$i].'">'.$select['nam'][$i].'</option>';
		$i++;
		}
	}
	else {
		while ($elem=each($type_input)){
						
		if ($elem['value'] === $val) echo '<option selected value="'.$elem['value'].'">'.$name_type_input[$elem['key']].'</option>';
		else echo '<option value="'.$elem['value'].'">'.$name_type_input[$elem['key']].'</option>';
		$i++;
		}
echo '</select>';
	}
	$str .=	'</select>';
	return $str;	
}