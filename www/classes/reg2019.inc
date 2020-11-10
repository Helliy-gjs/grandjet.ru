<?php
//файл относится к загрузке верхней части сайта header
//определяется режим загрузки лого и баннера	
//show::infosh($arrmain);
//echo $type_access;
//флаг загрузка хедера



	if($arrmain['idmen'][0]=='cont' || $arrmain['idmen'][0]=='mag' || $arrmain['idmen'][0]=='cat' || $arrmain['idmen'][0]=='flex' ){
	
		if (file_exists($img_ban)) {
		$size = GetImageSize($img_ban);
		$ww=100;
		if($size[1]>0 && $size[1]>0) {
		$is_banner=true;	
		$n=0.8;
		if($mode_edit){
			if (is_array($arrmain['link']) && isset($arrmain['link']['namep'][0]) && $type_access==='local') echo $arrmain['link']['namep'][0];
		}
		elseif($type_access==='local')echo $arrmain['link']['namep'][0]; 
		Maket::divclass('main_header',$Pth,'background:  url('.$img_ban.') no-repeat scroll 0% 0%;background-size:cover;-moz-background-clip: initial; -moz-background-origin: initial; -moz-background-inline-policy: initial;width:100%; height:auto;');
		
		}
	  }
	}  	
	switch($arrmain['idmen'][0]){
		case 'land':
		{
			$img=$arrmain['clas']['img'].$arrmain['namep'][0];
			$clas_head=array('user','logo','serv');
			$arr_head=array($ownerdata,$arrmain,$service);
			Maket::divclass($Maks_Page[1],$Pth,'background-image: url('.$img.');',' grid','header');
			Maket::divclass($Maks_Page[8],$Pth);
			Maket::divclass('header_land',$Pth);
			$nLast=Maket::showheaderland($Pth,$clas_head,$arr_head,'logo');
			//Maket::showbackground($arrmain,$Maks_Page,$Pth);
			echo '</div>';
			echo '</div>';
			Maket::divclass($Maks_Page[8],$Pth);
			$nbutt=show::menumain($arrmain,$Pth,'butt',0,2);
			echo '</div>';
			Maket::divclass($Maks_Page[8],$Pth);
			Maket::divclass('advers_land',$Pth);
			if($arrmain['loz'][0]=='')Maket::showlogo($clas_head[$nLast],$arr_head[$nLast],$Pth,0);
			else {
			if($Pth['advers_banner']['numpar']['Pics'])$razmer=$Pth['advers_banner']['numpar']['Pics'];
			else $razmer=3;
			}
			Page::scalimag4($arrmain,$Pth,$clas,'block-advers','div',$razmer,300,'');
			if (is_array($arrmain['link']) && isset($arrmain['link']['namep'][0]) && $type_access=='local') echo Maket::divclasstr('edit',$Pth).$arrmain['link']['namep'][0]; 
			echo '</div>';
			echo '</div>';
			echo '</header>';
			//Maket::showheaderland($arrmain,$Maks_Page,$Pth,$vendors,$service,'header');
			break;
		}
		case 'cont':
		{
			//if(!$mode_work && isset($_GET['contentS'])) echo 'Блок хедера страницы типа cont<hr>';//comment	//Maket::showheadercont($arrmain,$Maks_Page,$Pth,$vendors,$service,'header');
			$clas_head=array('user','logo','serv','shop','adver');
			$arr_head=array($ownerdata,$arrmain,$service,$shop,'Место для вашей рекламы');
			$nLast=Maket::showheaderflex($Pth,$clas_head,$arr_head,'logo');
			echo '<section>';
			if($arrmain['loz'][0]=='')Maket::showlogo($clas_head[$nLast],$arr_head[$nLast],$Pth,0);
			else {
				Maket::showlogo('advers-h3',$arrmain,$Pth,3,0,'lozhref','loz');
			//$res=$sw->getnews(arrmain['idnews'][], $tabl['news']);
			//$bbb=array('0'=>$arrmain['n']['date'],'1'=>$arrmain['n']['name'],'2'=>$arrmain['n']['text'],'3'=>$arrmain['n']['hrefn'],'4'=>$arrmain['n']['imgn']);
			if($Pth['advers_banner']['numpar']['Pics'])$razmer=$Pth['advers_banner']['numpar']['Pics'];
			else $razmer=3;
			Page::scalimag4($arrmain,$Pth,$clas,'block-advers','div',$razmer,300,'');
			//Page::scalimag1($arrmain,$Pth,'advers',0,$bbb);
	
			}
			echo '</section>';
			break;
		}
		case 'gall':
		{
			//if(!$mode_work && isset($_GET['contentS'])) echo 'Блок хедера страницы типа gall<hr>';//comment
			if ($arrmain['typmen'][6] == 'sw')Maket:: showheadergall($arrmain,$Maks_Page,$Pth,$vendors,$service,'header');
			else {
				$clas_head=array('user','logo','serv','shop','adver');
				$arr_head=array($ownerdata,$arrmain,$service,$shop,'Место для вашей рекламы');
				$nLast=Maket::showheaderflex($Pth,$clas_head,$arr_head,'logo');
			}
			break;
		}
		case 'blog':
		{
			Maket:: showheaderblog($arrmain,$Maks_Page,$Pth,$vendors,$ownerdata,'header');
			break;
		}
		case 'mag':
		{
			Maket::showheadercont($arrmain,$Maks_Page,$Pth,$vendors,$service,'header');
			break;
		}
		case 'cat':
		{ 
			$clas_head=array('user','logo','serv','shop','adver');
			$arr_head=array($ownerdata,$arrmain,$service,$shop,'Место для вашей рекламы');
			$nLast=Maket::showheaderflex($Pth,$clas_head,$arr_head,'logo');
			echo '<section>';
			if($arrmain['loz'][0]=='')Maket::showlogo($clas_head[$nLast],$arr_head[$nLast],$Pth,0);
			else {
			if($Pth['advers_banner']['numpar']['Pics'])$razmer=$Pth['advers_banner']['numpar']['Pics'];
			else $razmer=3;
			Page::scalimag4($arrmain,$Pth,$clas,'block-advers','div',$razmer,300,'');
			//Page::scalimag1($arrmain,$Pth,'advers',0,$bbb);
			break;
}
echo '</section>';
			break;
		}
		case 'mob':
		{
			Maket::showheadermob($arrmain,$Maks_Page,$Pth,$vendors,$service,'header',9);
			break;
		}
		case 'fb':
		{
			Maket:: showheaderblog($arrmain,$Maks_Page,$Pth,$vendors,$ownerdata,'header');
			break;
		}
		case 'tw':
		{
			Maket:: showheaderblog($arrmain,$Maks_Page,$Pth,$vendors,$ownerdata,'header');
			break;
		}
		case 'flex':
		{
			$clas_head=array('user','logo','serv','shop','adver');
			$arr_head=array($ownerdata,$arrmain,$service,$shop,'Место для вашей рекламы');
			$nLast=Maket::showheaderflex($Pth,$clas_head,$arr_head,'logo');
			echo '<section>';
	if($arrmain['loz'][0]=='')Maket::showlogo($clas_head[$nLast],$arr_head[$nLast],$Pth,0);
	else {
	//Maket::showlogo('advers-h6',$arrmain,$Pth,3,0,'lozhref','loz');
	//$res=$sw->getnews(arrmain['idnews'][], $tabl['news']);
	//$bbb=array('0'=>$arrmain['n']['date'],'1'=>$arrmain['n']['name'],'2'=>$arrmain['n']['text'],'3'=>$arrmain['n']['hrefn'],'4'=>$arrmain['n']['imgn']);
	if(isset($Pth['advers_banner']['numpar']['Pics']))$razmer=$Pth['advers_banner']['numpar']['Pics'];
	else $razmer=3;
	Page::scalimag4($arrmain,$Pth,$clas,'block-advers','div',$razmer,300,'');
	//Page::scalimag1($arrmain,$Pth,'advers',0,$bbb);
	
}
echo '</section>';
			break;
		}
		case 'shop':
		{
			$clas_head=array('user','logo','serv','shop');
			$arr_head=array($ownerdata,$arrmain,$service,$shop);
			Maket::showheadershop($Pth,$clas_head,$arr_head,'logo');
			break;
		}
	}

$order_id='donat';
$targets='Спонсорская поддержка совершенствования системы grandjetstudio';
$summ=1000;
//$payuser->payform('adm-'.$arrmain['idmen'][0].'-'.$idmaket,$Pth,$user->getBalans(),500,$targets);

/*Maket::divclass('sponsor-'.$Site->ids.'-'.$idm,$Pth,'display:flex;justify-content:center;flex-direction:column;');
echo 'Если вам нравится проект grandjetstudio вы можете поддержать его тут';
show::oplataYD('promocod','Постоплата (доступ по промокоду на 7 дней)',$summ);
echo '</div>';*/
echo '</header>';

echo '</div>';	

?>