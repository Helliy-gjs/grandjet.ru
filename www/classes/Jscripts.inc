<?php
	//echo $scripts;
	if(isset($Scrpt_libs) && $scripts === 'libs'){
	if(is_array($Scrpt_libs)){
	foreach($Scrpt_libs as $value){
		if($value != '' && file_exists($pathheader.'/'.$scripts.'/'.$value.'.js')) echo '<script src="'.$scripts.'/'.$value.'.js" type="text/javascript"></script>';
		//else echo $pathheader.'/'.$scripts.'/'.$value.'.js';
		}
	}
}
//debug($Scrpt_page);
if(isset($Scrpt_page)) {
	if(is_array($Scrpt_page)){
		foreach($Scrpt_page as $value){
			if($value != '' && file_exists('./'.$Site->script.'/'.$value.'.js')) echo '<script src="'.'/'.$Site->script.'/'.$value.'.js" type="text/javascript"></script>';
			elseif($value != '' && file_exists($pathheader.'/js/'.$value.'.js')) echo '<script src="'.'js/'.$value.'.js" type="text/javascript"></script>';
			//else echo 'не загружен '.$pathheader.'/'.$Site->script.'/'.$value.'.js';
		}
	}
	else {
		if($Scrpt_page != '' && file_exists('./'.$Site->script.'/'.$Scrpt_page.'.js')) echo '<script src="'.'/'.$Site->script.'/'.$Scrpt_page.'.js" type="text/javascript"></script>';
		//else echo 'не загружен '.$pathheader.'/'.$Site->script.'/'.$Scrpt_page.'.js';
	}
}	

	if(!isset($mysite)){
		$mysite = Singleton::getInstance('Site');
		$SiteCurr=$mysite->initbdF($_SERVER['HTTP_HOST'],$numpage,$Pth,$mode_edit);
	}
	//$envirSite = $mysite->getEnvirSite();
	//$mysite->InfoEssence($envirSite);
	//$envir_list=$mysite->loadenviroment($clas);
	//debug($envir_list);
	if(isset($_GET['envirS']) && isset($envir_list)){
		if($envir_list[0]!=='') echo 'loaded local css-scripts of this page '.$envir_list[0].'<br>';
		if($envir_list[1]!=='') echo 'loaded global css-scripts of this page '.$envir_list[1].'<br>';
		if($envir_list[2]!=='') echo 'loaded local js-scripts of this page '.$envir_list[2].'<br>';
		if($envir_list[3]!=='') echo 'loaded global js-scripts of this page '.$envir_list[3].'<br>';
	}
	//echo '<script src="https://deltar.ru/libs/jquery/jquery-1.11.1.min.js" type="text/javascript"></script>';
	//echo '<script  src="/js/common.js"  type="text/javascript" ></script>';
?>