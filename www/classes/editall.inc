<?php
//print_r($_POST);
//show::pauza();
//print_r($sw->read_namparams('setMaketPage',0));
$word='';
if (isset($_POST['chice1'])){ 
	$_GET['editp']='ok';
	$_GET['par'] = $_POST['chice1'];
	//$_GET['tab']='maket';
	$table=$_GET['tab'];
	}
elseif($_GET['editp']<>'ok' && $_GET['editp']<>'yes' && $_GET['editp']<>'new' && isset($_GET['np'])){
	$word='редактируем фрагмент';
	$table=$tabl['pages'];
	$field='numpage';
	$_GET['par']=$_GET['editp'];
	$numpar=$_GET['par'];
}
elseif ( isset($_GET['tab']) &&  isset($_GET['par'])){//редактирование любых таблиц
		$table=$_GET['tab'];
		$numpar=$_GET['par'];//порядковый номер записи в редактируемой таблице 
		$word='редактируем ';
		if (isset($_GET['field'])) $field=$_GET['field'];
		elseif($_GET['tab']=='maket' || $_GET['tab']=='allmakets' || $_GET['tab']=='scripts' || strstr($_GET['tab'],'config')) $field='id';
		
	}
elseif (isset($_GET['in']) ){//редактирование блога
	$table=$tabl['news'];
	$field='idnews';
	$word='редактируем ';
	$numpar=$_GET['in'];
}
elseif($_GET['editp']=='ok' || $_GET['editp']=='yes'  ) {//режим редактирования страниц сайта
	if(!isset($_GET['tab'])){
		$table=$tabl['pages'];
		$field='numpage';
		$word='редактируем ';
		$numpar=$_GET['np'];
	}
	else {
		if(isset($_GET['tab'])) $table=$_GET['tab'];
		elseif($_GET['cust'])$table='customers';
		//elseif($_GET['allmakets']) $table='allmakets';
		else $table=$tabl['news'];
		if ($table==$tabl['news']) $field='idnews';
		elseif($_GET['cust'])$field='customerid';
		elseif($table=='namparams') $field='codparams';
		$word='редактируем ';
	}
	if(isset($_GET['cust'])){//редактирование данных клиента
	
		$table='customers';
		$field='customerid';
		$numpar=$_GET['cust'];
		$_GET['par']=$numpar;
		$word='редактируем ';
	}	
}
elseif( !isset($_GET['par'])){//добавление новых записей в таблицы
	if($_GET['tab']) {//записей в любую таблицу
		$table=$_GET['tab'];
		$word='добавляем';
	}
	elseif(!isset($_GET['tab'])){//страниц
		$table=$tabl['pages'];
		$field='numpage';
		$word='добавляем';
	}
	elseif($_GET['editp']=='new') {//записей в блог
		$table=$tabl['news'];
		//echo 'добавляем в '.$table;
		$word='добавляем';
		}
	
}
else {
	exit();
}
//echo '<div class="info"> да '.$word.' '.$table.'<br></div>';
switch ($table){//особые параметры редактирорвания
	case 'pages':
	{	
		$numpar=$numpage;//порядковый номер редактируемой записи
		$field='numpage';//ключевое поле таблицы
		//$typmen='bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac';//значение select поля
		$rest=$sw->read_namparams('setTypesPage',$numpage);
		$typmen=$rest[2];
		//print_r($typmen);//-------
		$resu=$sw->read_namparams('setMaketPage',0);
		
		foreach($resu[1] as $key=>$val){
			if(strstr($val,'&')) $resw[$key]=explode('&',$val);
			$resu[1][$key]=$resw[$key][1];
		}
		//print_r($resu);
		$arridmen0=$resu[2];
		//array(11=>'cont', 0=>'land', 1=>'gall', 7=>'flex', 8=>'mag', 9=>'cat',6=>'mob' ,4=>'fb', 3=>'tw',5=>'qw',10=>'shop',2=>'blog');//начальное значение check поля
		
		for($i=0;$i<$Site->types;$i++){
			$arridmen1[0][$i]=$resu[1][$i];
			$arridmen1[1][$i]=$resu[0][$i];
		}
		if ($_GET['editp']=='ok' || $_GET['editp']=='yes') $_GET['par']=$numpar;
		$fields='';
		break;
	}
	case 'news':
	{
		$arridmen=array(0=>'blg', 1=>'new', 2=>'ins', 3=>'book', 4=>'fb', 5=>'tw', 6=>'vid');//начальное значение check поля7
		//$typmen='blg;new;ins;book;fb;tw;vid';//значение select поля
		$field='idnews';//ключевое поле таблицы
		if ($_GET['in']>0) $numpar=$_GET['in'];//номер страницы к которой привязана новость
		//$_GET['par']=$numpar;
		$fields='';
		break;
	}
	case 'namparams':
	{
		$field='codparams';
		$fields=array('tab','codparams','nampars','types','delimiter','reqr','ids','idauthor','region');
		$numpar=$_GET['par'];//порядковый номер записи в редактируемой таблице 
		$_GET['par']=$numpar;
		$close_field=3;
		$numpage=$uid;
		$numaket='';
		break;
	}
	case 'customers':
	{
		$field='customerid';
		$fields='';
		$numpar=$_GET['cust'];//порядковый номер записи в редактируемой таблице 
		$_GET['par']=$numpar;
		break;
	}
	case $tabl['elem']:
	{
		$field='id';
		$fields=array('id','codeGJS','name','desc','art','vendor','price','ms','ls','stock','date1','date2','ids','idauthor');
		$numpar=$_GET['id'];//порядковый номер записи в редактируемой таблице 
		$_GET['par']=$numpar;
		$close_field=2;
		break;
	}
	case $tabl['str']:
	{
		$table=$tabl['str'];
		$field='id';
		$fields=array('id','pid','name','typeF','constrF','ms','ls','ms','numEl','numEls','numElst','desc','ids','idauthor');
		$numpar=$_GET['id'];//порядковый номер записи в редактируемой таблице 
		$_GET['par']=$numpar;
		$close_field=2;
		break;
	}
	default:
	{
		if (isset($_GET['field']) && $_GET['tab']<>'maket') $fields=explode(',',$_GET['field']);
		elseif($_GET['tab']=== $tabl['pages']) {
			$fields=array('id','namep','lozungp','keywords','buttons','hrefp','typemenu','hrefscripts','hrefstyle','title','content','idmenu','levelmenu','hrefimage','list','list_href','butthref','buttimg','imgtext','idnews','site','configpage');
			$close_field=2;
			}
		elseif($_GET['tab']=== 'maket') {
			$fields=array('id','Maket','styles','flex','grid','numparams','fonts','video','effects','scripts','ids','numpage','numaket','idauthor');
			$close_field=4;
			$numpage=$uid;
		}
		elseif($_GET['tab']=== 'allmakets') {
			$fields=array('id','Maket','styles','flex','grid','numparams','fonts','video','effects','scripts','desc','ids','forms','author_mak');
			$close_field=4;
			$numpage=$uid;
			$field='id';
		}
		elseif($_GET['tab']=== 'namparams') {
			$fields=array('tab','codparams','nampars','types','delimiter','reqr','ids','idauthor','region');
			$close_field=2;
			$numpage=$uid;
			$field=$fields[1];
			}
		elseif($_GET['tab']=== 'scripts'){
			$fields=array('id','Maket','flag','type','scripts','needs','ids','uid','idm');
			$close_field=3;
			$numpage=$uid;
			$field=$fields[0];
			$numaket=$idmaket;
			$typmen='us;nbl';
		}	
		elseif($_GET['tab']=== 'fonts'){
			$arridmen1[0]=array('serif','sans-serif','cursive','fantasy','monospace','inherit');
			$arridmen1[1]=array('шрифты с засечками','рубленные шрифты','курсивные шрифты','декоративные шрифты','моноширинные шрифты','Наследует значение');
			$fields0=$sw->getallfieldtable($table);
			$fields= $fields0['field'];
			$close_field=3;
			//$numpage=$uid;
			$field=$fields[0];
			$numaket=$idmaket;
			$typmen='';
		}		
		elseif(strstr($_GET['tab'],'config')){
			$fields0=$sw->getallfieldtable($table);
			$fields=$fields0['field'];
			$close_field=2;
			//$numpage=$ids;
			$field=$fields[0];
		}
		elseif($_GET['tab']=== 'allsites') {
			$arridmen=array(0=>'Music', 1=>'Joy', 2=>'Sport', 3=>'Personal', 4=>'Land', 5=>'Trade',6=>'Info', 7=>'News', 8=>'Study');//начальное значение check поля
			$arrfields=$sw->getallfieldtable($_GET['tab']);
			$fields=$arrfields['field'];
			$close_field=2;
			$numpage=$uid;		
			$field=$fields[1];
			}	
		$numpar=$_GET['par'];
		break;
	}
}
if (!isset($fields)) {
	$arrfields=$sw->getallfieldtable($table);
	$fields=$arrfields['field'];
}

unset($_POST['chice1']);

$l=0;
$fff=$sw->getallfieldtable($table);
//print_r($fff['field']);
$yyy='no';
foreach ($fff['field'] as $val)	if($yyy=='no' && $val=='Maket') $yyy='yes';
//echo $yyy;
if ($yyy=='yes') {
	$res0=$db->query('SELECT '.$sw->ready_str_field($fff['field'],0,0).'   FROM '.$table.' WHERE `Maket`=^Ns;','Maket');
	if ($res0){		
	 $arrstl=$sw->issetMaket($res0,count($res0));
	}
	else $arrstl='';
}
else $arrstl='';
	
	$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	if($res2){
		$arrnm=$res2->nampars;
		$arrtp=$res2->types;
		$arrdlm=$res2->delimiter;
		$arrrqr=$res2->reqr;
		$arrname=explode('|',$arrnm);
		$arrtype=explode('|',$arrtp);
		$arrrequer=explode('|',$arrrqr);
		//print_r($res2);
		foreach ($arrtype as $key=>$val) if (strstr($val,'type')) $arrtype[$key]=20;
		if($arrdlm <> null) {
			$arrdelem=explode(',',$arrdlm);
		}
		else {
		for ($i=0;$i<count($arrtype);$i++)  {
			$arrdelem[$i][0]='|';
			$arrdelem[$i][1]=';';
			$arrdelem[$i]=$arrdelem[$i][0].$arrdelem[$i][1];
			}
		}
	}
	else {
		//иницилизация таблицы в namparams при вызове GET
		$arrfields=$sw->getallfieldtable($table);
		//print_r($arrfields['field']);
		for ($i=0;$i<count($arrfields['field']);$i++){
		$arrnm.=$arrfields['field'][$i].'|';
		$arrtp.=$arrfields['type'][$i].'|';
		if (is_array($arrstl)) $arrdlm.='|,';
		else $arrdlm.=',';
		}
		$lpn=$user->getscountab('namparams',`codparams`, 'c')+1;
		$z="INSERT INTO namparams VALUES('$table','$lpn','$arrnm','$arrtp','$arrdlm','','$Site->ids','$uid','');";
		//echo $z;
		$sql=$db->query($z);
		//$arrdelem=explode(',',$arrdlm);
		//$arrname=explode('|',$arrnm);
		//$arrtype=explode('|',$arrtp);
		show::pauza('Таблица '.$table.' зарегистрована в реестре');break;
	}
	//echo $table.'-'.$field.'-'.$numpar;
	//var_dump($numpar*1);
	$lpg=$user->getscountab($table,$field, 'f');	
	
if (isset($_GET['par'])) {
		$res1 = $db->query('SELECT * FROM `'.$table.'` WHERE `'.$field.'`=^Ni;',$numpar);
	
	if($res1->namep === '')	{
		if($numpage != $startpage)$titleP='title_gra_'.$_SERVER['HTTP_HOST'].'_'.$numpage;
		else $titleP='main_gra_'.$_SERVER['HTTP_HOST'];	
		$res1 = (object)array('numpage' => $numpage, 'namep' => 'banmain.jpg|logo.png|empty_page||','lozungp' => ';;;|;;;', 'keywords' => 'key1>key2>key3;title_page;description_page', 'buttons' => ';;;|;;;', 'hrefp' => '','typemenu' =>' wr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac', 'hrefscripts' => '', 'hrefstyle' => '','title' => $titleP, 'content' => ';;;|;;;', 'levelmenu' => ';;;;;','idmenu' => 'land', 'hrefimage' => ';;;;;', 'list' =>';;;;;','list_href' => ';;;;;',
			'butthref' => ';;;|;;;', 'buttimg' => ';;;;;', 'imgtext' => ';;;|;;;', 'idnews' => ';;;;;', 'site' => '','idauthor' => 0,'configpage' =>'');
		
	//echo 'arrtype';
		 	
	}
	foreach($res1 as $val){
	if($user->getLevelnew() <= USER::CLIENT)	{
		if($arrrequer[$l] === '' || $arrrequer[$l] === 'n')$arrtype[$l]='hid';
	}
	if($arrtype[$l] === 'check'  && $val=='') $array[$l]=$typmen;
elseif($table === $tabl['pages'] && ($l == 14 || $l ==4)){
		if($res1->list === '')$res1->list=$val->list_href;
		if($l == 14)$array[$l]=Page::prepare_spisok($res1->list,$res1->list_href,$tabl);
		elseif($l == 4){
			$LB = explode('|',$res1->buttons);
			$LB1 = Page::prepare_spisok($LB[0],$LB[1],$tabl);
			$array[$l] = $LB1.'|'.$LB[1];
		}
	}
elseif($table === $tabl['pages'] && $l== 22)	{
	if(strstr($val, '|'))$currconfp = explode('|',$val); 
	else $currconfp=array('','');
	if($val === '' ||  intval($currconfp[0]) !== $numcnfp['id'][0] ){
		if(isset($numcnfp['id'][0]))$currconfp [0]=$numcnfp['id'][0];
		if(isset($numcnfp['Maket'][0]))$currconfp [1]=$numcnfp['Maket'][0];
		$array[$l]= $currconfp [0].'|'.$currconfp [1].'|'.utils::getConfig($numcnfp['id'][0],'configp',1);
	}
	else $array[$l] = $val;
}	
elseif($val === '') $array[$l]=$arrdelem[$l];


else {
		if(isset($_POST[$l.'0'])){
			$arrobr=explode($arrdelem[$l],$val);
			$i=0;
			$j=$_POST['part']-10*$l;
			$arrobr[$j]='';
			while (isset($_POST[$l.$i])){
				if($_POST[$l.$i]<>'')$arrobr[$j].=$_POST[$l.$i].';';
				$i++;
			}	
			//print_r($arrobr);
			foreach ($arrobr as $val)$array[$l].=$val.$arrdelem[$l];
		}
		else $array[$l]=$val;
		//$arrtype[$l]='hid';
	}
	$l++;
	}
	//print_r($array);
}
	

	if (!isset($_POST[0]))	{
		
	//создание данных для новой записи в таблице	
	if (!isset($_GET['par']) &&  $_GET['editp']=='new') {
		//print_r($arrstl);
		if($table === $tabl['pages']){
			$pagenew = new Page($number_pages+1,$tabl);
			//print_r($pagenew->MainAr);
			$array[0]=$pagenew->MainAr['numpage'];
			$array[1]=$pagenew->MainAr['namep'];
			$array[2]=$pagenew->MainAr['lozung'];
			$array[3]=$pagenew->MainAr['keywords'];
			$array[4]=$pagenew->MainAr['buttons'];
			$array[5]=$pagenew->MainAr['hrefp'];
			$array[6]=$pagenew->MainAr['typemenu'];
			$array[7]=$pagenew->MainAr['scripts'];
			$array[8]=$pagenew->MainAr['hrefstyle'];
			$array[9]=$pagenew->MainAr['title'];
			$array[10]=$pagenew->MainAr['content'];
			$array[11]=$pagenew->MainAr['levelmenu'];
			$array[12]=$pagenew->MainAr['idmenu'];
			$array[13]=$pagenew->MainAr['hrefimag'];
			$array[14]=$pagenew->MainAr['list'];
			$array[15]=$pagenew->MainAr['list_href'];
			$array[16]=$pagenew->MainAr['butthref'];
			$array[17]=$pagenew->MainAr['buttimg'];
			$array[18]=$pagenew->MainAr['imgtext'];
			$array[19]=$pagenew->MainAr['idnews'];
			$array[20]=$pagenew->MainAr['site'];
			$array[21]=$pagenew->MainAr['idauthor'];
			$array[22]=$pagenew->MainAr['configpage'];
			//print_r($array);
			if (isset($typmen)) $array[6]=$typmen;
		}
		else {
		$l=0;
		foreach($arrdelem as $value){
			
		if (isset($value[1]) && $value[1]<>"") $array[$l]=$value[1].$value[1].$value[1].$value[0].$value[1].$value[1].$value[1];
		elseif(isset($value[0]) && $value[0]<>"") {
			if ($l <> 1) {
				$array[$l]='';
					for($i=0;$i<count($arrstl[$l]);$i++) $array[$l].=$value[0];
			}
			else $array[$l]=$value[0];
		}
		else $array[$l]='';
		
		if($arrtype[$l] == 'check' ) $array[$l]=$typmen;
		$l++;
		}
		if (isset($typmen)) $array[6]=$typmen;
		$array[0]=$user->getscountab($table,'id','f')+1;
		}
		}
	//print_r($array);
	$tabl['ed']=$table;
	//foreach($arrname as $key=>$val) $arrname[$key].='('.$key.')'.$arrdelem[$key];	
	if ($_GET['editp']<>'yes' &&  $_GET['editp']<>'ok' &&  $_GET['editp']<>'new' && !isset($_GET['cust']) ) { //редактирование элементов
		$arrayk='a'.$_GET['editp'].'00';
		$zz=strlen($arrayk);
		switch ($zz){
			case 5:
			{
			$zn=1;
			break;
			}
			case 6:
			{
			$zn=2;
			break;
			}
			case 7:
			{
			$zn=1;
			break;
			}
			case 8:
			{
			$zn=2;
			break;
			}
		}
	$k0=substr($arrayk,1,$zn)*1;
	$k1=substr($arrayk,$zn+1,1)*1;
	$k2=substr($arrayk,$zn+2,1)*1;
	$k3=substr($arrayk,$zn+3,1)*1;
	$arrayk=array($k0,$k1,$k2,$k3);
	//print_r($arrayk);
	$sw->editpartsBD($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$tabl,$fields,$uid,$Site->ids,'#');	
	} 
	elseif(isset($_GET['edn']) &&  $_GET['editp']<>'ok'){//редактирование подэлементов
		$arrayk='a'.$_GET['edn'].'00';
		$k0=substr($arrayk,1,1)*1;
		$k1=substr($arrayk,2,1)*1;
		$k2=substr($arrayk,3,1)*1;
		$k3=substr($arrayk,4,1)*1;
		$arrayk=array($k0,$k1,$k2,$k3);
		$sw->editpagesBD($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$tabl,$fields,$c,$r,$s,$m,$t);	
	} 
	else {//редактирование всех элементов
	if ( $_GET['editp']=='ok') {
			
			if($table==$tabl['pages']){
				$cond_pub=$sw->ispublicpage($numpage);
				echo '<h2> Редактирование записи '.$array[0].'</h2>'.$cond_pub;
			}
			else {
				//print_r($arrtype);
				$cond_pub='';
				echo '<h2>Редактирование записи '.$array[0].'</h2>';
			}
			$sw->editDBD($arrname, $arrtype, $array,$arrdelem,$clas,$tabl,$fields,$arridmen1,$arrrequer,$uid,$Site->ids,$c,$r,$s,$t);
			echo '<input class="button" id="regBut2" type="submit"  tabindex="22" value=" Записать" />';
			
			if($cond_pub === 'unpublic' || $cond_pub ==='absent'){
				Maket::spanclass(Maket::divclasstr('button',$Pth,'','','input type="submit" value="Опубликовать '.$numpage.'"').'</input>',$Pth);
			}
			elseif($cond_pub != '') {
			//echo $datepub;
			$strpub='Опубликовано ';
			Maket::spanclass(Maket::divclasstr('button',$Pth,'cursor:none;','','span type="button" value=""').$strpub.'</span>',$Pth);
			}
			echo '</form>';	
		}
	elseif ( $_GET['editp']=='yes'){
			$sw->editTBD($arrname, $arrtype, $array,$arrdelem,$clas,$tabl,$uid,$Site->ids,$c,$r,$s,$t);
			echo '<input class="button" id="regBut1" type="submit" tabindex="22" value=" Записать " />';
			echo '</form>';	
			echo '</table>';
		}
	else {
			echo '<h2> Добавление записи </h2>';
			
			$sw->editDBD($arrname, $arrtype, $array,$arrdelem,$clas,$tabl,$fields,$arridmen1,$arrrequer,$uid,$Site->ids,$c,$r,$s,$t);
			echo '<input class="button" id="regBut3" type="submit" tabindex="22" value=" Записать " />';
			echo '</form>';	
			echo '</table>';
		}	
	}
	//header('Location: https://'.$_SERVER['HTTP_HOST']);
}
else {
	//print_r($_POST);	
	for ($k=0;$k<count($arrname);$k++) {
	$j=0;	
	while ($j<$_POST['zn']+1){
		if($_FILES[$k.$j.'00']['name']=='') $_POST['noupload'.$k.$j]=$_POST[$k.$j.'00'];			
			if($_FILES[$k.$j.'00']['name']<>''){
				$sw->files_load($k.$j.'00','noupload'.$k.$j,$_FILES,$clas);
				}
			elseif($_POST['noupload'.$k.$j]<> '') {$_POST[$k.$j.'00']=$_POST['noupload'.$k.$j];}
		$j++;
		}
	}
	for ($k=0;$k<count($arrname);$k++) {
	if (strlen($arrdelem[$k]) > 1){
	$i=0;$j=0;	
	while (isset($_POST[$k.$i.$j.'00'])){
		while (isset($_POST[$k.$i.$j.'00'])){
			if ($j==0) $arr[$k].=$_POST[$k.$i.$j.'00']; else $arr[$k].=$arrdelem[$k][1].$_POST[$k.$i.$j.'00'];
			$j++;
		}
	if ($j==1 || $_POST[$k.$i.($j-1).'00'] <> '' ) $arr[$k].=$arrdelem[$k][1];
	$j=0;
	$i++;
	$arr[$k].=$arrdelem[$k][0];
	}
		$arr[$k]=substr($arr[$k],0,-1);
	}
	elseif(strlen($arrdelem[$k]) == 1 ) {
	
	$j=0;	
	while (isset($_POST[$k.$j.'00'])){
		if ($j==0) $arr[$k].=$_POST[$k.$j.'00']; else $arr[$k].=$arrdelem[$k][0].$_POST[$k.$j.'00'];
		$j++;
	}
	if ($j==1 || $_POST[$k.($j-1).'00']<>'' && $arrtype[$k]<>'check') $arr[$k].=$arrdelem[$k][0];
	}
	
	if ($arr[$k] == '') {
	$arr[$k]=$_POST[$k];
	}
}
$db->start();
if(file_exists(CLASSES.'/gjsapi.inc')) include(CLASSES.'/gjsapi.inc');
/*switch($table) {
	case 'pages':
	{
	//print_r($arr);
	if ($_POST[0] == $numpage){
	if ($numpage == $startpage) 	$arr[9]='main_'.substr('grandjet.ru',0,3).'_'.$Site->domen;
	elseif ($arr[9]='main_'.substr($Site->domen,0,3)) $arr[9]='title_'.substr('grandjet.ru',0,3).'_'.$Site->domen.'_'.$numpage;
	$is_change=false;
	foreach($array as $key=>$value)if($arr[$key]<>$value){
		$is_change=true;
		break;
		}
	if($is_change) {
		$arr[17]=str_replace (' ','',$arr[17]);
		$arr[13]=str_replace (' ','',$arr[13]);
		//echo "Изменения есть $numpage  $arr[20]  $uid  $idmaket";
		if($sw->unpublic($numpage,'elemap',$arr[20],$uid)){
			$z= "UPDATE `pages` SET `namep`='".$arr[1]."',`lozungp`='".$arr[2]."'
			,`keywords`='".$arr[3]."' ,`buttons`='".$arr[4]."' ,`hrefp`='".$arr[5]."'
			,`typemenu`='".$arr[6]."',`hrefscripts`='".$arr[7]."',`hrefstyle`='".$arr[8]."' 
			,`title`='".$arr[9]."',`content`='".$arr[10]."' ,`idmenu`='".$arr[11]."' ,`levelmenu`='".$arr[12]."'
			,`hrefimage`='".$arr[13]."',`list`='".$arr[14]."',`list_href`='".$arr[15]."'
			,`butthref`='".$arr[16]."' ,`buttimg`='".$arr[17]."' ,`imgtext`='".$arr[18]."'
			,`idnews`='".$arr[19]."',`configpage`='".$arr[22]."' WHERE `numpage`=".$_POST[0].";";
			$sql=$db->query($z);
		}
	}
		}
	else {	
	$_POST[0]=$number_pages+1;
	//echo 'добавление записи '.$_POST[0];
	if ($_POST[0] == $startpage) 	$arr[9]='main_'.substr('grandjet.ru',0,3).'_'.$Site->domen;
	elseif ($arr[9]='main_'.substr($Site->domen,0,3)) $arr[9]='title_'.substr('grandjet.ru',0,3).'_'.$Site->domen.'_'.$_POST[0];
		$z="INSERT INTO `pages` VALUES ('$_POST[0]','$arr[1]','$arr[2]','$arr[3]','$arr[4]','$arr[5]','$arr[6]','$arr[7]','$arr[8]','$arr[9]','$arr[10]','$arr[11]','$arr[12]','$arr[13]','$arr[14]','$arr[15]','$arr[16]','$arr[17]','$arr[18]','$arr[19]','$Site->domen','$uid','$arr[22]');";
		$sql=$db->query($z);
	if (mysql_errno()=='') echo 'добавлена новая запись '.$_POST[0];
	else echo "ERROR ".mysql_errno()." ".mysql_error()."\n";
		}
	
	break;
	}

	case 'customers':
	{
	if ($_POST[1] == $cid){
	//print_r($arr);
	$firm=array();
	$firm['keyid']=$arr[0];
	$firm['customerid']=$arr[1];
	$firm['name']=$arr[2];
	$firm['address']=$arr[3];
	$firm['city']=$arr[4];
	$firm['state']=$arr[5];
	$firm['zip']=$arr[6];
	$firm['country']=$arr[7];
	$firm['uradr']=$arr[8];
	$firm['telmain']=$arr[9];
	$firm['cinn']=$arr[10];
	$firm['ckpp']=$arr[11];
	$firm['crs']=$arr[12];
	$firm['cbik']=$arr[13];
	$firm['cbank']=$arr[14];
	$firm['cks']=$arr[15];
	$firm['tels']=$arr[16];
	$firm['social']=$arr[17];
	$firm['em']=$arr[18];
	$firm['host']=$arr[19];
	$firm['userid']=$arr[20];
	$firm['cfio']=$arr[21];
	
	if($user->editUserFirm($uid, $firm)){
		echo 'обновление записи '.$cid;
	
		
		}
	}
	break;	
	}

	default:
	{
		if ($_GET['editp']<>'new'){
			//echo 'обновление  '.$_POST[1];
			$i=0;$y='';
			//print_r($arr);
			foreach($fields as $val) {
				if ($i<count($fields)-1 ) $y.= '`'.$val.'` = "'.$arr[$i].'",';
				else $y.= '`'.$val.'` = "'.$arr[$i].'"';
			$i++;
			}
			//print_r($y);
			$numpost=0;
			while(isset($fields[$numpost]) && $fields[$numpost]<>$field){
				$numpost++;
			}
			//echo $table.' '.$field.' '.$numpost.'<br>';
			///print_r($fields);
			$z= "UPDATE `$table` SET $y WHERE `$field`=".$_POST[$numpost].";";
			//echo $z;
			//show::pauza();
			$sql=$db->query($z);
	}
	else {
		//print_r($arr);echo '<br>';
		//print_r($_POST);
		//echo '<input type="submit" name="Пауза"/>';
	
	$_POST[0]=$number_value_tab+1;	
	if($arr[1]<>''){//обязательное условие добавления новой записи
		
		$y='';
		$NN=count($fields)-$close_field;
		if($close_field == 0 )$NB=0;
		else $NB = 1;
		for ($i=$NB;$i<$NN;$i++){
			 if( $i<$NN-1)$y.="'". $arr[$i]."',";
			 elseif($close_field == 0) $y.="'". $arr[$i]."'";
			 else $y.="'". $arr[$i]."',";
		} 
					
		//echo $y;		
		$z1="INSERT INTO $tab VALUES ('$_POST[0]',$y,$Site->ids,$numpage,$numaket);";
		//echo $z1;
		if($close_field == 4 && $table=='allmakets') $z="INSERT INTO $table VALUES ($_POST[0],".$y."$Site->ids,$arr[10],$idmaket,$numpage);";
		elseif($close_field == 4) $z="INSERT INTO $table VALUES ($_POST[0],".$y."$Site->ids,$numpage,$idmaket,$uid);";
		elseif($close_field == 3) $z="INSERT INTO $table VALUES ($_POST[0],".$y."$Site->ids,$numaket,$numpage);";
		elseif($close_field == 2) $z="INSERT INTO $table VALUES ($_POST[0],".$y."$Site->ids,$numpage);";
		elseif($close_field == 1) $z="INSERT INTO $table VALUES ($_POST[0],".$y."$Site->ids);";
		elseif($close_field == 0) $z="INSERT INTO $table VALUES ($_POST[0],".$y.");";
		$sql=$db->query($z);
		if (mysql_errno()=='') echo 'добавлена новая запись '.$_POST[1];
		else echo "ERROR ".mysql_errno()." ".mysql_error()."\n";
		}
		}
		break;	
	}
	}*/
	Utils::transakres($db);
	//echo $localpath;
	if(isset($_POST['sucss']) && $_POST['sucss']=== 'good'){
		//echo "<script type='text/javascript'>window.close()';</script>";
		echo 'Данные записаны. Закрыть окно<a id="close" href="#"  onclick="self.close();">X</a>';
	}
	elseif($localdomen==='localhost'){
		echo "<script type='text/javascript'>window.top.location='$localpath';</script>";exit();
	}
	elseif ($_GET['editp']==='new' && $_GET['tab']==$tabl['pages']){		header('Location: https://'.$_SERVER['HTTP_HOST'].'/?np='.($number_pages+1));
			exit();
	}
	elseif(isset($_GET['cust'])){
		header('Location: https://'.$_SERVER['HTTP_HOST'].'/settings/?account');
		exit();
	}
	else {
		header('Location: https://'.$_SERVER['HTTP_HOST'].'/?konstrS&np='.$numpage);
		exit();
	}
}
?>