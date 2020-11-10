<?php
echo 'Content lay page';

//$nbeg=0;//опция  1 не входят
//$nend=0;// олция 0 1 2 3 входят
//print_r($Maks_Page);
//Maket::showheadergall($arrmain,$Maks_Page,$Pth,'',$service);
Layer::showheadergall($arrmain,$Pth,'butt',0,0);//logo+menu
//Layer::showheadergall($arrmain,$Pth,'list',0,0);//logo+menu

Maket::divclass('paralax',$Pth);

$ncont=Layer::showheadergall($arrmain,$Pth,'cont');//header

Maket::divclass('#second-section',$Pth);
Maket::divclass('bg__second',$Pth);
	
Maket::closediv(2);

Layer::showheadergall($arrmain,$Pth,'imgt',0,4);

Layer::showheadergall($arrmain,$Pth,'imgs',$ncont);

Layer::showheadergall($arrmain,$Pth,'form_get');

Layer::showfooter($arrmain,$Pth,4,9);
Maket::closediv(6);

?>	