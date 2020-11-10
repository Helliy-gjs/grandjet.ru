<?php
echo '<div id="root"></div>';

$name_button=array('Разработка сайтов - Джи-Джей','Выбрать тариф','Подключить к хостингу','Заказать');

$Pth='';
$stl='';
//if($mode_mang || $mode_edit) 

if($levelU>0) {
	$nambutt=array($levelU,' Восстановление пароля ',' Гостевой ход ');
	$hrefnam=array('./auth/','./recovery/','./auth/?guest');
}
else {
	$nambutt=array(' Вход ',' Регистрация ',' Выход ');
	$hrefnam=array('./auth/','./registration/','./auth/?logout');
}
$namsoc=array('vk','facebook-square','twitter-square');
$hrefsoc=array('vk.com/grandjetstudio','facebook.com/ruslan.serg','twitter.com/grandjetstudio');
$arr_form['type']=array('text','text','textarea','text','text','text','text','text','text','text');
$arr_form['place']=array('tel...','name...2','desc...3','You...4','You...5','You...6','You...7','You...8','You...9','You...10');
$arr_form['req']=array('required','required','','','','required','','','','');
$arr_form['name']=array('phone','name','text');
?>
<!--[if lt IE 7]><html lang="ru" class="lt-ie9 lt-ie8 lt-ie7"><![endif]-->
<!--[if IE 7]><html lang="ru" class="lt-ie9 lt-ie8"><![endif]-->
<!--[if IE 8]><html lang="ru" class="lt-ie9"><![endif]-->
<!--[if gt IE 8]><!-->
	<?php
$Pth['adm']='';	
print_r($Pth['adm']);	
Maket::divclass('top_header',$Pth,'','','header');
Utils::button_reg_soc($Pth,$nambutt,$hrefnam,$namsoc,$hrefsoc);
Maket::showbootstrap(12,'md');
Maket::showpic('','logo',$Pth,'grandjetstudio');
Maket::divclass('main_mnu',$Pth,'',' clearfix','nav');
Maket::icon_button('main_mnu_button','fa fa-bars','button',' hidden-md hidden-lg');
$data=array('#'=>'Главная','settings/'=>'Настройки','#blog'=>'Блог','#portfolio'=>'Портфолио','#callback'=>'Отзывы','#order'=>'Заявка');
show::viewdatapage($data,'menu',$Pth,'./','ul');
	if($arrmain['owner']->telmain<>'') echo Maket::divclasstr('user top_contacts',$Pth).'<i class="fa fa-mobile aria-hidden=true"></i>'.' '.$arrmain['owner']->telmain.'</div></nav>';
	echo Maket::divclasstr('#headline',$Pth,'','','h1').$arrmain['loz'][0].'</h1>';
	Maket::divclass('sider_container',$Pth);
	Maket::icon_button('next_button','fa fa-angle-right','div','');
	Maket::icon_button('prev_button','fa fa-angle-left','div','');
	Maket::divclass('carousel',$Pth);
		echo Maket::divclasstr('slide_item',$Pth).'<img src="./images/1.jpg"></img></div>';
				echo Maket::divclasstr('slide_item',$Pth).'<a class="fancybox" ><img src="./images/2.jpg"></img></a></div>';
				echo Maket::divclasstr('slide_item',$Pth).'<a class="fancybox" ><img src="./images/3.jpg"></img></a></div>';
				echo Maket::divclasstr('slide_item',$Pth).'<a class="fancybox" ><img src="./images/4.jpg"></img></a></div>';
				echo Maket::divclasstr('slide_item',$Pth).'<a class="fancybox" "><img src="./images/5.jpg"></img></a></div>';
				echo Maket::divclasstr('slide_item',$Pth).'<a class="fancybox" ><img src="./images/6.jpg"></img></a></div>';
	echo '</div>';
	Maket::closediv(3);
echo '</header>';	
?>
<?php	

//show::infosh($arrmain['link']);
echo '<section class="order">';
		Maket::divclass('container',$Pth);
			//Maket::divclass('row',$Pth);
			echo '<div class="row">';
				//Maket::divclass('col-md-7',$Pth);
				show::viewformajax($arr_form,$Pth,$name_button,0,5);
				
				echo '</div>';		
			echo '</div>';		
		echo '</section>';	
		//show::infosh($arrmain['list']);
echo '<section class="main_content">';
	Maket::divclass('container',$Pth);
		//Maket::divclass('col-md-8',$Pth);
		echo '<div class="col-md-8">';
		foreach($arrmain['cont'] as $key=>$val) 
		if ($arrmain['cont'][$key]<>'') show::viewblogpage($arrmain,$key,$clas,$Pth,' myblog',4);
			
		echo '</div>';
		echo '<div class="col-md-4">';
			
			Maket::divclass('sidebar_right',$Pth,'','','sidebar');
			echo '<div class="col-md-12" style="text-align: center">';
			echo '<div class="col-md-1"></div>';
			echo '<div class="col-md-11">';
			echo '<a href="#blog">';
			echo Maket::divclasstr('sidebar-head',$Pth,'','','h4').'Подробности разделах.</h4></div></a>';
			echo '</div>';
			echo '<div class="col-md-1"></div>';
			echo '<div class="col-md-10">';
			Maket::divclass('sidebar-list',$Pth);
			$data1=array(1=>'текст текст текст текст',2=>'текст текст текст текст',3=>'текст текст текст текст',4=>'текст текст текст текст текст текст текст текст',5=>'текст текст текст текст',6=>'текст текст текст текст текст текст текст текст');
			show::viewdatapage($data1,'',$Pth,'./','ul');
				
			echo '</div>';	
			echo '</div><div class="col-md-1"></div>';
			echo '</sidebar>';
		echo '</div>';
	echo '</div>';
echo '</section>';	
include($pathheader.$pathToClasses.'Jscripts.inc');
?>	
