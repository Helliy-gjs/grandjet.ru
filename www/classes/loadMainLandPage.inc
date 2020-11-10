<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8" />
<title>Интернет-магазин от grandjetstudio</title>
<meta http-equiv="X-UA-Compatible" content="IE=edge" />
<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<link rel="shortcut icon" href="favicon.png" />
<link rel="stylesheet" href="libs/bootstrap/bootstrap-grid.min.css" />
<link rel="stylesheet" href="libs/font-awesome/css/font-awesome.min.css" />
<link rel="stylesheet" href="libs/linea/styles.css" />
<link rel="stylesheet" href="libs/magnific-popup/magnific-popup.css" />
<link rel="stylesheet" href="libs/animate/animate.min.css" />
<link rel="stylesheet" href="css/fontsland.css" />
<link rel="stylesheet" href="css/mainland.css" />
<link rel="stylesheet" href="css/skins/pink.css" />
<link rel="stylesheet" href="css/medialand.css" />
<?php
$dark = 'dark';
$light = 'light';
$type_site = 'land';
if(!isset($Pth)) $Pth = '';
$dat1['typesite'] = 'spa';
if(file_exists(CLASSES.'/personalLandData.inc') && isset($numpage)) include(CLASSES.'/personalLandData.inc');
else echo 'не дoступен '.CLASSES.'/lpersonalLandData.inc';
if(file_exists(CLASSES.'/personalLandMaket.inc') && isset($numpage)) include(CLASSES.'/personalLandMaket.inc');
else echo 'не дoступен '.CLASSES.'/personalLandMaket.inc';
echo show::loaderLand();
echo show::showHeaderLand($Pth,$id,$datM,'main_head','data-parallax="scroll" data-image-src="img/bg.jpg" data-z-index="1"``');

$content = array(show::showAbout($Pth,$dat,$datSoc,$firstname,$about,$img),
show::showResume($Pth,$text,$blog,$dataIcons1,0,1));
echo show::showPersonLandMaket($Pth,$id,$clas2,$content);

echo '<section id="'.substr($id[2],1).'" class="'.$clas0[1].'">'.show::showPortfolio($Pth,$clas1,$clas2,$dat1,$blog1,$imgs).'</section>';

echo show::showPersonLandMaket($Pth,$id[3],$clas0[2],show::showContacts($Pth,$blogC,$arrFN,$datSoc['icon'],2));

echo Maket::spanclasstr(show::showFooter($Pth,$dataIcons2,$firstname),$Pth,$clas0[3],'footer');
?>
		<script src="libs/jquery/jquery-2.1.3.min.js"></script>
		<script src="libs/parallax/parallax.min.js"></script>
		<script src="libs/magnific-popup/jquery.magnific-popup.min.js"></script>
		<script src="libs/mixitup/mixitup.min.js"></script>
		<script src="libs/scroll2id/PageScroll2id.min.js"></script>
		<script src="libs/waypoints/waypoints.min.js"></script>
		<script src="libs/animate/animate-css.js"></script>
		<script src="libs/jqBootstrapValidation/jqBootstrapValidation.js"></script>
		<script src="js/common.js"></script>
<?php		
	