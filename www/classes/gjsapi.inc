<?php
if(!isset($number_pages)) $number_pages = 0;

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
		elseif($table=== $tabl['pages']) {
			$fields=array('id','namep','lozungp','keywords','buttons','hrefp','typemenu','hrefscripts','hrefstyle','title','content','idmenu','levelmenu','hrefimage','list','list_href','butthref','buttimg','imgtext','idnews','site','configpage');
			$close_field=2;
			}
		elseif($table=== 'maket') {
			$fields=array('id','Maket','styles','flex','grid','numparams','fonts','video','effects','scripts','ids','numpage','numaket','idauthor');
			$close_field=4;
			$numpage=$uid;
		}
		elseif($table=== 'allmakets') {
			$fields=array('id','Maket','styles','flex','grid','numparams','fonts','video','effects','scripts','desc','ids','forms','author_mak');
			$close_field=4;
			$numpage=$uid;
			$field='id';
		}
		elseif($table=== 'namparams') {
			$fields=array('tab','codparams','nampars','types','delimiter','reqr','ids','idauthor','region');
			$close_field=2;
			$numpage=$uid;
			$field=$fields[1];
			}
		elseif($table=== 'scripts'){
			$fields=array('id','Maket','flag','type','scripts','needs','ids','uid','idm');
			$close_field=3;
			$numpage=$uid;
			$field=$fields[0];
			$numaket=$idmaket;
			$typmen='us;nbl';
		}	
		elseif($table=== 'fonts'){
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
		elseif(strstr($table,'config')){
			$fields0=$sw->getallfieldtable($table);
			$fields=$fields0['field'];
			$close_field=2;
			//$numpage=$ids;
			$field=$fields[0];
		}
		elseif($table=== 'allsites') {
			$arridmen=array(0=>'Music', 1=>'Joy', 2=>'Sport', 3=>'Personal', 4=>'Land', 5=>'Trade',6=>'Info', 7=>'News', 8=>'Study');//начальное значение check поля
			$arrfields=$sw->getallfieldtable($_GET['tab']);
			$fields=$arrfields['field'];
			$close_field=2;
			$numpage=$uid;		
			$field=$fields[1];
			}	
		//$numpar=$_GET['par'];
		break;
	}
}
if (!isset($fields)) {
	$arrfields=$sw->getallfieldtable($table);
	$fields=$arrfields['field'];
}

switch($table) {
	case 'pages':
	{
	//print_r($arr);
		if ($arr[0] == $numpage){
			if (!$startpage) 	$arr[9]='main_'.substr('grandjet.ru',0,3).'_'.$Site->domen;
			elseif ($arr[9]=== 'main_gra_'.$Site->domen) $arr[9]='title_'.substr('grandjet.ru',0,3).'_'.$Site->domen.'_'.$numpage;
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
					,`idnews`='".$arr[19]."',`configpage`='".$arr[22]."' WHERE `numpage`=".$arr[0].";";
					$sql=$db->query($z);
				}
			}
		}
	else {	
	$_POST[0]=$number_pages+1;
	//echo 'добавление записи '.$_POST[0];
	if (!$startpage) 	$arr[9]='main_gra_'.$Site->domen;
	elseif ($arr[9]=== 'main_gra_'.$Site->domen) $arr[9]='title_gra_'.$Site->domen.'_'.$arr[0];
		$z="INSERT INTO `pages` VALUES ('$arr[0]','$arr[1]','$arr[2]','$arr[3]','$arr[4]','$arr[5]','$arr[6]','$arr[7]','$arr[8]','$arr[9]','$arr[10]','$arr[11]','$arr[12]','$arr[13]','$arr[14]','$arr[15]','$arr[16]','$arr[17]','$arr[18]','$arr[19]','$Site->domen','$uid','$arr[22]');";
		$sql=$db->query($z);
	 echo 'добавлена новая запись '.$arr[0];
	
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
		if ($action<>'new'){
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
			echo $table.' '.$field.' '.$numpost.'<br>';
			///print_r($fields);
			$z= "UPDATE `$table` SET $y WHERE `$field`=".$arr[$numpost].";";
			//echo $z;
			//show::pauza();
			$sql=$db->query($z);
	}
	else {
		//print_r($arr);echo '<br>';
		//print_r($_POST);
		//echo '<input type="submit" name="Пауза"/>';
	
	$arr[0]=$number_value_tab+1;	
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
					
		echo $y;		
		$z1="INSERT INTO $table VALUES ('$arr[0]',$y,$Site->ids,$numpage,$numaket);";
		//echo $z1;
		if($close_field == 4 && $table=='allmakets') $z="INSERT INTO $table VALUES ($arr[0],".$y."$Site->ids,$arr[10],$idmaket,$numpage);";
		elseif($close_field == 4) $z="INSERT INTO $table VALUES ($arr[0],".$y."$Site->ids,$numpage,$idmaket,$uid);";
		elseif($close_field == 3) $z="INSERT INTO $table VALUES ($arr[0],".$y."$Site->ids,$numaket,$numpage);";
		elseif($close_field == 2) $z="INSERT INTO $table VALUES ($arr[0],".$y."$Site->ids,$numpage);";
		elseif($close_field == 1) $z="INSERT INTO $table VALUES ($arr[0],".$y."$Site->ids);";
		elseif($close_field == 0) $z="INSERT INTO $table VALUES ($arr[0],".$y.");";
		$sql=$db->query($z);
		echo 'добавлена новая запись '.$arr[0];
		}
		}
		break;	
	}
	}
