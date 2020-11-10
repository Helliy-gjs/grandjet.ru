<?php
if($levelU<4)	{
	$ew = Singleton::getInstance('ElementsW');
//при наличии каталога 	
if($ew->view_table($tabl['elem'])){
	$numelem=$user->getscountab($tabl['elem'],'id','c');
if (isset($_GET['np'])) $current=$_GET['np'];
elseif (isset($_POST['np'])) $current=$_POST['np'];
else $current=$numpage;
if ($numelem>0 && $arrmain['typmen'][5]<> 'nbf') {
echo '<form style="align:left;" method="post" action="'.$PageM->MainAr['hrefp'].'?np='.$numpage.'" target="_self">';
echo ' </b><span style="font-size:'.$size_pars1.'px;" ><input class="poisk" name="poisk" placeholder="Найти" maxlength="20" size="15" type="text" /></span>';
	//$sw->list_choice($choice_vendors);
	$vendors=$ew->getvendor($tabl['elem']);
	$user->selmen($vendors,$vend,'./images/searchh.gif','');
	
echo '</form>';
}
}
}
else
{
	$allpags=$sw->getallpages('pages');
	$title_chice='Перейти';
	$allpags['num'][]='';
	$allpags['nam'][]='';
	if (isset($_POST['chice'])) $current=$_POST['chice'];
	elseif(isset($_GET['np'])) $current=$_GET['np'];
	else $current=$numpage;
	//echo '<div class="info">';
	echo '<div style="display:flex; justify-content: center;">';
	echo '<div><span style="font-size:'.$size_pars1.'px">';	
	if (isset($_POST['chice'])) echo '<form style="align:left;  " method="post" action="'.$arrmain['hrefp'][0].'" target="_self">';
	else echo '<form style="align:left;  " method="post" action="'.$arrmain['hrefp'][0].'" target="_self">';
	$user->selmen($allpags['nam'],$allpags['num'],'Page',$numpage,'chice',$title_chice);
	echo '</form></span></div>';
	$allsts=$sw->getallstyles('maket',$Site->ids,$idmaket,$numpage);
	//print_r($allsts);
	echo '<div><span style="font-size:'.$size_pars1.'px">';	
	if ($allsts){
		if (isset($_POST['chice1'])) $current=$_POST['chice1'];
		else $current=$allsts['id'][0];
		$title_chice='изменить стиль ';
		echo '<form style="align:left;  " method="post" action="'.$arrmain['hrefp'][0].'?editp=ok&tab=maket" target="_self">';
		$chice=$user->selmen($allsts['Maket'],$allsts['id'],'Style',$current,'chice1',$title_chice);
		echo '<a title="добавить стиль" href="'.$arrmain['hrefp'][0].'?editp=new&tab=maket">  +</a>';
		echo '</form></span></div>';
	}
	else  echo '<a title="добавить стиль" href="'.$arrmain['hrefp'][0].'?np='.$numpage.'&editp=new&tab=maket">  + style</a>';
	echo '</div>';// s5
	//echo '</div>';// info
}	
?>