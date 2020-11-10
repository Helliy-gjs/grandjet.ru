<?php
//echo $pathheader.$pathToClasses.'reg2019_'.$ind_scr.'.inc';
$clas_head=array('user','logo','serv','shop','adver');
$arr_head=array($ownerdata,$arrmain,$service,$shop,'Место для вашей рекламы');
Maket::divclass('main_header',$Pth,'background:  url('.$img.') no-repeat scroll 0% 0%;background-size:cover;-moz-background-clip: initial; -moz-background-origin: initial; -moz-background-inline-policy: initial;width:100%; height:auto;');
Maket::divclass('header',$Pth);
Maket::divclass('heads',$Pth,'',' flex');
echo show::showheaderflex($Pth,$clas_head,$arr_head,'logo');
//$nLast=Maket::showheaderflex($Pth,$clas_head,$arr_head,'logo');
debug($ownerdata);
debug($service);
debug($shop);

Maket::closediv(2);

echo '</div>';