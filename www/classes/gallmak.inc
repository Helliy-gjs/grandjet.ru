<?php

	//echo '<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Open+Sans:300,400,600">';    
    //echo '<link rel="stylesheet" href="libs/gallery/Font-Awesome-4.7/css/font-awesome.min.css">';            
     
    //echo '<link rel="stylesheet" href="libs/gallery/css/bootstrap.css">';
	//echo '<link rel="stylesheet" href="css/magnific-popup.css">';
	//echo '<link rel="stylesheet" href="css/magnific-popup.css">';
	//echo '<link rel="stylesheet" href="css/templatemo-style.css">';
	//echo'<script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script><script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script><script src="libs/gallery/js/jquery-1.11.3.min.js"></script>';
foreach($Maks_Page as $key=>$val){
		$MP[$key]=$val;
		
	}
	if(isset($Pth[$MP[0]][5])){
		if($Pth[$MP[0]][5] > 0) $prefix=' grid';
		elseif($Pth[$MP[0]][5]==0 && $arrmain['idmen'][0]=='flex')$prefix=' flex';
	}
	else $prefix='';
		
		$clas_modul=array($MP[110],$MP[111],$MP[112],$MP[114],$MP[131],$MP[133],$MP[135],$MP[137],$MP[139]);
		//$clas_modul=array('cd-hero','cd-slider-nav','navbar','navbar-toggler','navbar-toggleable','navbar-nav','nav-item','nav-link','sr-only');
		//$arrmod=array(1,6,20,8,20,7,12,14,20,15,10,21,22);
		if(isset($_GET['GM'])){
		echo '<h3>Топология галереи</h3>';	
		Maket::divclass($clas_modul[0],$Pth);
		Maket::divclass($clas_modul[1],$Pth);
		Maket::divclass($clas_modul[2],$Pth,'',$prefix,'nav');
		Maket::divclass('tm-'.$clas_modul[2].'-bg',$Pth);
		echo '<a class="'.$clas_modul[2].'-brand text-uppercase" href="../index.html"><img style="width:9%;" src="images/creative-writing.png" alt="creative writing" class="img-responsive"><h2>'.$arrmain['loz'][0].'</h2></a>';
		Maket::spanclass('&#9776;',$Pth,$clas_modul[3].' hidden-lg-up','button type="button" data-toggle="collapse" data-target="#tmNavbar"');
        Maket::divclass('collapse '.$clas_modul[4].'-md text-xs-center text-uppercase tm-navbar',$Pth,'','','div id="tmNavbar"');
		Maket::divclass('nav '.$clas_modul[5],$Pth,'','','ul');		 
		$opt=array('Макеты','Радио','Видео','Клиенты','Сообщения');
                  foreach($opt as $key=>$val){			
                          if($key==0) echo '<li class="'.$clas_modul[6].' active selected">';
			else 	echo '<li class="'.$clas_modul[6].'">';			   
                          echo '<a class="'.$clas_modul[7].' "  href="#'.$key.'" data-no="'.$key.'">'.$val;
			if($key==0)echo '<span class="'.$clas_modul[8].' ">(current)</span>' ;
			echo '</a></li> ';   
			}
		echo ' </ul></div></div></nav></div> ';
		$choose_Page='selected';
		Maket::divclass($clas_modul[0].'-slider',$Pth,'width:100%;','','ul');
		Maket::divclass($choose_Page,$Pth,'','','li');
		Maket::divclass('cd-full-width',$Pth);
		Maket::divclass('container-fluid js-tm-page-content',$Pth,'','','div data-page-no="1" data-page-type="gallery"');
		Maket::divclass('tm-img-gallery-container',$Pth);
		Maket::divclass('tm-img-gallery gallery-one',$Pth);
		
		for($i=1;$i<17;$i++){
			$str0='<figcaption>'.Maket::spanclasstr($i.'IKEA'.'<strong>РАЗ</strong>',$Pth,'tm-figure-title','h2').Maket::spanclasstr('We need sanguines',$Pth,'tm-figure-description','p').Maket::spanclasstr('View more',$Pth,'','a href="img/tm-img-0'.$i.'.jpg"').'</figcaption>';
			Maket::divclass('grid-item',$Pth);
			Maket::divclass('effect-sadie',$Pth,'','','figure');
			if($i<10)echo '<img src="libs/gallery/img/tm-img-0'.$i.'-tn.jpg" alt="Image" class="img-fluid tm-img">';
			else echo '<img src="libs/gallery/img/tm-img-'.$i.'-tn.jpg" alt="Image" class="img-fluid tm-img">';
			echo $str0;
			echo '</figure></div>';
			
		}
		Maket::closediv(4);
		echo '</li>';
       	echo '</ul>';	
		//$ncontainer=$MP[3];
	}
?>