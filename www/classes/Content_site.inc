<?php
$nb=0;
$n_card=0;
$n_loz=0;
$n_cards=3;
$n_lozes=5;
$n_list=0;	
//хедер - шапка страницы, предназначена для вывода информации о владельце сайта, о пользователе открывшем страницу, а также такие элементы контента как лозунги, контактные данные, информации о состоянии работы пользователя, например заказы, уведомления и прочие служебные данные
//print_r($arrmain);
$resuB=$PageM->read_namparams('setContentMaket',0);
//$resuB[0]=$resuB[1];
if(isset($_GET['contentS'])) foreach($resuB[1] as $key=>$val) $resuB[1][$key]=$resuB[1][$key].'&contentS';
//print_r($resuB);
echo '<div class="menu flex">';
echo show::work_pages('serv',$Pth,$resuB,'./'.$graphp);
echo '</div>';
Maket::divclass('menu '.$arrmain['idmen'][0],$Pth,'',' flex');
if (!isset($_GET['editp'])){
		if($Site->types<>5) {
		}
		else show::work_pages('serv',$Pth,$resuB);
	}
//echo '</div>';
echo '</div>';
echo '</div>';
echo '<hr>';

unset($arrmain['link']);
$clas_head=array('user','logo','serv','shop');
$arr_head=array($ownerdata,$arrmain,$service,$shop);
$arr_zag=array('Информация о владельце сайта','Логотип и лозунги','Базовый сервис','Интернет-магазин');
//print_r($Pth['logo']['styles']);
if(isset($_GET['Options'])){
	$resuO=$PageM->read_namparams('alloptionS',0);
	foreach($resuO[1] as $key=>$val) $resuO[1][$key]=$resuO[1][$key].'&contentS&Options';
	echo '<div class="menu flex">';
	echo show::work_pages('serv',$Pth,$resuO,'./'.$graphp);
	echo '</div>';
	Maket::divclass('menu '.$arrmain['idmen'][0],$Pth,'',' flex');
	if (!isset($_GET['editp'])){
			if($Site->types<>5) {
			}
			else show::work_pages('option',$Pth,$resuO);
		}
	if(isset($_GET['ownerS'])){	
		echo '<h3>Информация о владельце (суперадминистраторе) сайта </h3>';
		echo '<br>Блок (вид для пользователя)<br>';
		echo $contentSite['owner']['block'];
		echo '<hr/>';	
		echo 'Все данные владельца  сайта (owner)<br>';
		debug($contentSite['owner']);
	}
	elseif(isset($_GET['adminS'])){
		echo '<h3>Информация об администраторе сайта </h3>';
		echo '<br>Блок (вид для пользователя)<br>';
		debug($ownerdata);
		echo '<hr/>';	
		echo 'Все данные  (admin)<br>';
		debug($contentSite['admin']);
		echo '<hr/>';	
		echo '<h3>Сервис блок '. $user->whoareyouhere(5,false).'</h3>';
		$service=$user->Serviceblock($startpage,5,$Site,$Pth);
		echo $service;
	}
	elseif(isset($_GET['managS'])){
		echo '<h3>Информация об менеджерах сайта </h3>';
		debug($contentSite['manag']['block']);
		echo '<hr/>';	
		echo '<h3>Сервис блок '. $user->whoareyouhere(4,false).'</h3>';
		$service=$user->Serviceblock($startpage,4,$Site,$Pth);
		echo $service;
	}
	elseif(isset($_GET['userS'])){
		echo '<h3>Информация о клиенте сайта </h3>';
		echo '<h3>Сервис блок '. $user->whoareyouhere(3,false).'</h3>';
		$service=$user->Serviceblock($startpage,3,$Site,$Pth);
		echo $service;
		echo '<hr/>';	
		echo '<h3>Информация о пользователе сайта </h3>';
		debug($contentSite['user']['block']);
		echo '<h3>Сервис блок '. $user->whoareyouhere(2,false).'</h3>';
		$service=$user->Serviceblock($startpage,2,$Site,$Pth);
		echo $service;
		echo '<hr/>';	
		echo '<h3>Информация о посетителе сайта </h3>';
		debug($contentSite['user']['block']);
		echo '<h3>Сервис блок '. $user->whoareyouhere(1,false).'</h3>';
		$service=$user->Serviceblock($startpage,1,$Site,$Pth);
		echo $service;
		echo '<hr/>';
		echo '<h3>Информация о госте сайта </h3>';
		debug($contentSite['user']['block']);
		echo '<h3>Сервис блок '. $user->whoareyouhere(0,false).'</h3>';
		$service=$user->Serviceblock($startpage,0,$Site,$Pth);
		echo $service;
		echo '<hr/>';	
		echo 'Все данные  (user)<br>';
		debug($contentSite['user']);
		
	}
	elseif(isset($_GET['shopS'])){
		echo '<h3>Блок регистрации   '. $user->whoareyouhere(2,false).' shop</h3>';
		debug($contentSite['shop']);
		echo '<hr/>';	
		echo '<h3>Блок состояния заказа  '. $user->whoareyouhere(3,false).' order</h3>';
		debug($contentSite['order']);
		echo '<hr/>';	
		echo '<h3>Блок поиска search</h3>';
		debug($contentSite['search']);
		echo '<hr/>';	
		echo '<h3>Блок выбора валют curr</h3>';
		debug($contentSite['curr']['block']);
	}
	elseif(isset($_GET['articalS'])){
		debug($contentSite['blog']);
	}
	elseif(isset($_GET['newS'])){		
		echo '<h3>Новость страницы '.$numpage.'</h3>';
		
		echo $contentSite['newp'];
		echo '<hr/>';	
		echo '<h3>Новости сайта </h3>';
		for ($i=1; $i<$ew->numrec($tabl['news'])+1; $i++){
			echo $contentSite['new'][$i];
		}
		
		echo '<hr/>';	
		echo '<h3>Блок новостей сайта </h3>';
		
		echo $contentSite['news'];
		echo '<hr/>';	
		debug($contentSite['newp']);
		echo '<hr/>';	
		debug($contentSite['new']);
		echo '<hr/>';	
		debug($contentSite['news']);
	}
	elseif(isset($_GET['swipS'])){
		$n_card=0;
		$n_cards=4;
		
		if($arrmain['typmen'][7] === 'sw')echo show:: slideSwipstr($Pth,$contentSite['gal'],'Y','',1,20,1,'progressbar',true);//$pagn="Y",$swbut="Y", $nsl=1,$spbetw=10,$spg=1,$pagn_type="fraction,progressbar",$loop=true
		elseif($arrmain['typmen'][13] === 'ac')echo show::accordshstr('imgs',$arrmain,$Pth);
	}
	
	else {
		echo 'Опции ';
		debug($contentSite);
	}
}
if(isset($_GET['Maintext'])){
	$disp=' '.$disp;
	$style='';
	unset($arrmain['conthref']['link']);
	unset($arrmain['cont']['link']);
	echo '<div>';
	$key=0;
	if(strlen($arrmain['cont'][$key])> 20)$n_simb=$Pth['Titem-'.'content'.$key.'-cont'.$key]['effect']['crop'];
	else $n_simb=0;
	echo '<h3>Текст основной (без обрезки)</h3>';
	echo '<div>';	
	Maket::showlogo('content'.$key,$arrmain,$Pth,4,$key,'conthref','cont',0,$disp,$style);
	echo '<h3>Текст основной (с обрезкой после '.$n_simb.' символа )</h3>';
	echo '<div class="flex">';
	$href='./?editp='.$Pth['Titem-content'.$key.'-cont'.$key]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-content'.$key.'-cont'.$key]['id'];
		Maket::showlogo('content'.$key,$arrmain,$Pth,3,$key,'conthref','cont',$n_simb,$disp,$style);
		if($n_simb==0)echo '<a href="javascript:new_window(\''.$href.'\')">обрезать...</a>';
	echo '</div>';
	
	echo '<h3>Текст кнтента cont</h3>';
	Maket::view_text_key($arrmain,'cont',$Pth,0);
	echo '<h3>Текст cont</h3>';
	Maket::view_text_key($arrmain,'cont',$Pth);
	echo '<h3>Текст лозунгов loz</h3>';
	Maket::view_text_key($arrmain,'loz',$Pth,1);
}	
if(isset($_GET['Logo'])){
	echo '<h3>Логотип сайта с лозунгами</h3>';
	echo show::showlogo($clas_head[1],$arrmain,$Pth,1);
	//echo show::scalimag3($arrmain,$arr['clas']['img'].$arrmain['namep'][1],'./?np='.$arrmain['nump'],$Pth,0);
}
if(isset($_GET['Banner'])){
//Информация о владельце сайта соднржится в объекте Owner_site
	echo $type_access.'<h3>Основной баннер '.$clas['img'].$arrmain['namep'][0].'</h3>';
	echo '<div>';
	//print_r($Pth['global']);
	//print_r($Pth['header']['link_numpar']);
	if($type_access=='global'){
		$razmer=$Pth['global']['Pics'];
		echo '<a href="./?editp='.$Pth['global']['numparams']['link'][0].'00&tab=allmakets&par='.$Pth['global']['id'].'" title="Изменить размер">Размер баннера '.$razmer[0].'.....</a>';
	}
	else {
		$clhere=$clas['clas'][2];
		$razmer=$Pth[$clhere]['numpar']['Pics'];
		print_r($Pth[$clhere]['link_numpar']['Pics']);
		Maket::divclass($clhere,$Pth);
		echo '<a href="./?editp='.$Pth[$clhere]['link_numpar']['Pics'].'00&tab=maket&par='.$Pth[$clhere]['id'].'" title="Изменить размер">Размер баннера '.$razmer[0].'.....</a>';
		echo '</div>';
	}
	//print_r($razmer);
	
	$res=$sw->getnews(14, $tabl['news']);
//echo '<h3>scalimag4-short</h3>';

	Page::scalimag4($clas['img'].$arrmain['namep'][0],$Pth,$clas,2,'div',$razmer[0]);
	echo '</div>';
}
if(isset($_GET['Header'])){
	Maket::divclass('header',$Pth);
		Maket::divclass('heads',$Pth,'',' flex');
			echo show::showlogo($clas_head[0],$ownerdata,$Pth,0);
			echo show::showlogo($clas_head[1],$arrmain,$Pth,1);
			echo show::showlogo($clas_head[2],$service,$Pth,0);
			echo show::showlogo($clas_head[3],$shop,$Pth,0);
	Maket::closediv(2);
	
}
if(isset($_GET['Blog'])){
	$res=$sw->getnews(14, $tabl['news']);
	$bbb=array('0'=>$res[0]['date'],'1'=>$res[0]['name'],'2'=>$res[0]['text'],'3'=>$res[0]['hrefnew'],'4'=>$res[0]['imgnews']);
	echo '<div>';
	//Page::scalimag5($arrmain,$Pth,$bbb);
	echo '</div>';
	echo '<div>';
	Page::scalimag4($clas['img'].$arrmain['namep'][0],$Pth,$clas,'block','div',$razmer[6],300,$bbb);
	echo '</div>';
	//echo '<h3>cardforblog</h3>';
	echo '<div>';
	//print_r($arrmain['n']);
	echo Maket::cardforblog($arrmain,$Pth,'logo',0,' card',14,1,$bbb);
	echo '</div>';

	echo '<div>';
	Maket::cardforblog($arrmain,$Pth,'blog_card','',12);
	echo '</div>';
	//echo '<h3>scalimag1</h3>';
	echo '<div>';
	Page::scalimag1($arrmain,$Pth,'logo',0,' card',14,0,$bbb);
	echo '</div>';
	//echo '<h3>showcard</h3>';
	echo '<div>';
	Maket::showlogo('card',$arrmain,$Pth,2);
	echo '</div>';
}
if(isset($_GET['Headtext'])){
	//print_r($Pth['hidyes']['link_effect']['crop']);
	$disp=' '.$arrmain['idmen'][0];
	$style='';
	$typelist='loz';
	$typelist1='lozhref';
	$key=0;
	
	unset($arrmain[$typelist]['link']);
	unset($arrmain[$typelist1]['link']);
	//Print_r($arrmain['lozhref']);
	echo '<div>';
	echo '<h3>Заголовок H1 без ссылки</h3>';
	Maket::showlogo('zag-h1',$arrmain,$Pth,3,$key,'lozhref','loz',0,$disp,$style);
	echo '</div>';
	echo '<div>';
	echo '<div>';
	echo '<h3>Заголовок H1 с ссылкой</h3>';
	Maket::showlogo('zag-h1',$arrmain,$Pth,3,$key+1,'lozhref','loz',1,$disp,$style);
	echo '</div>';
	echo '<div>';
	echo '<h3>Заголовок H2 с ссылкой</h3>';
	Maket::showlogo('zag-h2',$arrmain,$Pth,3,$key+2,'lozhref','loz',1,$disp,$style);
	echo '</div>';
	echo '<div>';
	echo '<h3>Заголовок H3 с ссылкой</h3>';
	Maket::showlogo('zag-h3',$arrmain,$Pth,3,$key+3,'lozhref','loz',1,$disp,$style);
	echo '</div>';
	echo '<div>';
	echo '<h3>Заголовок H4 с ссылкой</h3>';
	Maket::showlogo('zag-h4',$arrmain,$Pth,3,$key,'lozhref','loz',1,$disp,$style);
	echo '</div>';
	echo '<div>';
	echo '<h3>Заголовок H5 с ссылкой</h3>';
	Maket::showlogo('zag-h5',$arrmain,$Pth,3,$key,'lozhref','loz',1,$disp,$style);
	echo '</div>';
	echo '<div>';
	echo '<h3>Двойной заголовок h2, h3 с ссылкой</h3>';
	Maket::view_loz_key($arrmain,$Pth,$key,3,'zag','h4');
	//Maket::view_loz_key($arrmain,$Pth,$key,2,'zag','h4');
	echo '</div>';
	echo '</div>';
}
if(isset($_GET['Button'])){
	echo '<div class="flex">';
	Maket::showlogo('card',$arrmain,$Pth,5,0,'butt');
	Maket::showlogo('card',$arrmain,$Pth,5,1,'butt');
	Maket::showlogo('card',$arrmain,$Pth,5,2,'butt');
	Maket::showlogo('card',$arrmain,$Pth,5,3,'butt');
	echo '</div>';
}
if(isset($_GET['Menu'])){
	echo '<div class="flex">';
	Maket::showlogo('card',$arrmain,$Pth,5,0,'list');
	Maket::showlogo('card',$arrmain,$Pth,5,1,'list');
	Maket::showlogo('card',$arrmain,$Pth,5,2,'list');
	Maket::showlogo('card',$arrmain,$Pth,5,3,'list');
	echo '</div>';
}
if(isset($_GET['Content'])){
	echo '<div class="flex">';
	Maket::showlogo('logo',$arrmain,$Pth,5,0,'cont');
	Maket::showlogo('logo',$arrmain,$Pth,5,1,'cont');
	Maket::showlogo('logo',$arrmain,$Pth,5,2,'cont');	
	Maket::showlogo('logo',$arrmain,$Pth,5,3,'cont');
	echo '</div>';
}
if(isset($_GET['Footer'])){
	//echo '<h3>showfooter</h3>';
	echo '<div class="flex">';
	Maket::showlogo('card',$arrmain,$Pth,5,0,'foot');
	Maket::showlogo('card',$arrmain,$Pth,5,1,'foot');
	Maket::showlogo('card',$arrmain,$Pth,5,2,'foot');
	echo '</div>';
}
if(isset($_GET['Maket'])){	
	//echo '<h3>showMaket</h3>';
	echo '<div class="flex">';
	Maket::showlogo($clas_head[0],$ownerdata,$Pth,0);
	Maket::showlogo($clas_head[1],$arrmain,$Pth,1);
	Maket::showlogo($clas_head[2],$service,$Pth,0);
	Maket::showlogo($clas_head[3],$shop,$Pth,0);
	echo '</div>';
	echo '<div class="flex">';
	Maket::showlogo('card',$arrmain,$Pth,5,0,'butt');
	Maket::showlogo('card',$arrmain,$Pth,5,1,'butt');
	Maket::showlogo('card',$arrmain,$Pth,5,2,'butt');
	Maket::showlogo('card',$arrmain,$Pth,5,3,'butt');
	echo '</div>';
	echo '<div class="flex">';
	echo '<div>';
	Maket::showlogo('card',$arrmain,$Pth,5,0,'list');
	Maket::showlogo('card',$arrmain,$Pth,5,1,'list');
	Maket::showlogo('card',$arrmain,$Pth,5,2,'list');
	Maket::showlogo('card',$arrmain,$Pth,5,3,'list');
	echo '</div>';
	Maket::cardforblog($arrmain,$Pth,'logo',0,' card',14,0,$bbb);
	echo '<div>';
	Maket::showlogo('logo',$arrmain,$Pth,5,0,'cont');
	Maket::showlogo('logo',$arrmain,$Pth,5,1,'cont');
	Maket::showlogo('logo',$arrmain,$Pth,5,2,'cont');	
	Maket::showlogo('logo',$arrmain,$Pth,5,3,'cont');
	echo '</div>';
	echo '<div class="flex">';
	Maket::showlogo('zag-h1',$arrmain,$Pth,3);
	echo '<div>';
	Maket::showlogo('logo',$arrmain,$Pth,2);
	echo '</div>';
	echo '</div>';
	echo '</div>';
	echo '<div class="flex">';
	Maket::showlogo('card',$arrmain,$Pth,5,0,'foot');
	Maket::showlogo('card',$arrmain,$Pth,5,1,'foot');
	Maket::showlogo('card',$arrmain,$Pth,5,2,'foot');
	echo '</div>';
}
else {
	//print_r($arrmain['list']);
	/*extract(maket::datacard($arrmain,'loz',0));
	echo $fulzag_card.' '.$text_card.' '.$but_card.' '.$img_card.' '.$href_card.'<br>';
	extract(maket::datacard($arrmain,'imgt',0));
	echo $fulzag_card.' '.$text_card.' '.$but_card.' '.$img_card.' '.$href_card.'<br>';
	extract(maket::datacard($arrmain,'butt',0));
	echo $fulzag_card.' '.$text_card.' '.$but_card.' '.$img_card.' '.$href_card.'<br>';
	extract(maket::datacard($arrmain,'cont',0));
	echo $fulzag_card.' '.$text_card.' '.$but_card.' '.$img_card.' '.$href_card.'<br>';*/
	//$card_item= Maket::part_texts($arrmain['loz'][0]);
	
	//Maket::spanclass('<h1>'.Maket::part_name($arrmain['loz'][0]).'</h1>',$Pth,'hidyes','li');
	//Maket::showlogo('items part-card',$arrmain,$Pth,2,0,'','imgt',351);
}	
/*foreach ($clas_head as $key=>$val){
	if($val==$clas['clas'][0])$mode=1;
	else $mode=0;
	echo '</div>';
	echo '<h3>'.$arr_zag[$key].'</h3>';
	Maket::showlogo($val,$arr_head[$key],$Pth,$mode);
	echo '</div>';
		}*/
?>