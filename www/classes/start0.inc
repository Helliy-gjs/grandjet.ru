<?php
if(!$startpage)
	echo 'no start page';
	//$mysite = Singleton::getInstance('Site');
	//$SiteCurr=$mysite->initbdF($_SERVER['HTTP_HOST'],$allpage,$Pth,$mode_edit);
	
	//$mysite->InfoEssence($SiteCurr);
	/*$href='?np='.$numpage;
	echo '<div onclick="tree_toggle(arguments[0],arguments[1]); return false;" id="box">';
	$sw = Singleton::getInstance('StructureW');
	$arr = $sw->getData(261,'elements');
	$arr = $arr['sections'];
	echo '<ul class="Container">';
	$i = count($arr)-1;
	$num = 0;
	foreach($arr as $k => $val) {
		$num += $val['numEl'];
		if($k == $i) echo '<li class="Node ExpandClosed isLast" id="'.$val['id'].'">';
		else echo '<li class="Node ExpandClosed" id="'.$val['id'].'">';
		if ($brow == 0) echo '<a class="Expand" href="'.$href.'&id='.$val['id'].'">'.$val['name'].'</a></li>';			
		else echo '<a class="Expand" href="'.$href.'&id='.$val['id'].'">'.$val['name'].'&nbsp;('.$val['numEl'].')</a></li>';
	}
		echo '</ul>';
	echo '</div>';	*/	
	$curMaket =  $sw->getData(17,'allmakets');
	echo '<div onclick="download();" id="site">' ;
	echo '</div>';
	
	
	
	
	