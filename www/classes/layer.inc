<?php
class Layer extends Singleton {
	protected function __construct() {
		$this->db = Singleton::getInstance('DB'); 
		//echo 'construct SWE OK';
	}
	
static function button_bars($n,$Pth,$navbar='navbar-toggle'){
	$str='<span class="sr-only">Toggle navigation</span>';
	for($i=0;$i<$n;$i++)$str.='<span class="icon-bar"></span>';
	Maket::spanclass($str,$Pth,$navbar,'button type="button" id="nav-toggle" data-toggle="collapse" data-target="#main-nav"',' bar_button');
    echo '</button>';
}

static function sub_menu($arr,$Pth,$clas="sub-menu",$mode=0){
	if($mode==1){
		Maket::divclass($clas,$Pth,'','','ul');
		foreach($arr['name'] as $key=>$val) Maket::spanclass('<a href="'.$arr['href'][$key].'#'.$key.'">'.$val.'</a>',$Pth,$clas.'-li','li');
		echo '</ul>';
	}
	else {
		$str='';
		$str.=Maket::divclasstr($clas,$Pth,'','','ul');
		foreach($arr['name'] as $key=>$val) $str.=Maket::spanclasstr('<a href="'.$arr['href'][$key].'#'.$key.'">'.$val.'</a>',$Pth,$clas.'-li','li');
		$str.='</ul>';
		return $str;
	}
}
static function menush($arr,$Pth,$typelist,$clas='',$nb,$ne){
$tabl=$arr['tab'];	
$numpage=$arr['nump'];	

$Menu->list1=$arr[$typelist];
$Menu->list2=$arr[$typelist.'href'];

$a_link=$arr['link'];

unset($Menu->list1['link']);
unset($Menu->list2['link']);
//
if($ne==0)$nopt=count($Menu->list1);
else $nopt=$ne-$nb;
if(!is_array($clas)){
	$i=0;
	foreach($Menu->list1 as $val) if ($val<>'') $i++;
	if ($i<8) $nopt=$i-1;
	else $nopt=6;
	if ($nopt < 4) $just='SB';
	if ($nopt < 6) $just='C';
	if ($nopt > 5) $just='SA';
	$clas[0]='menudown'.$just;
	$clas[2]='menulevel';
}
	
if (isset($tabl['pages'])) $Menu->tabl=$tabl['pages'];
$Menu->list3=Elementsw::viewlistnew($Menu->list2,'buttons',$tabl);
for ($j=0; $j<count($Menu->list3);$j++) $Menu->linkp[$j]=explode('|',$Menu->list3[$j]);
for ($i=$nb;$i<$nopt;$i++) $Menu->lp[$i]=explode(';',$Menu->linkp[$i][1]);
//if($arr['idmen'][0]<> 'land') Maket::divclass('main-header9',$Pth,'','','header');
Maket::divclass($clas[0],$Pth,'','collapse navbar-collapse'); 
if ($Menu->list2[0]=='') {
	for ($i=$nb;$i<($nopt+$nb); $i++) {
	$Menu->list2[$i]='#';
	Maket::divclass($clas[0],$Pth,'','','li');
	}
}
else {
	$bott='yes';
	for ($i=$nb; $i<($nopt+$nb); $i++){
	if ($Menu->list2[$i]) $pagelist= new Page($Menu->list2[$i],$tabl);
	if ($Menu->list1[$i] == '' && $bott == 'yes') {
	$Menu->list1[$i]=$pagelist->getnamepage($pagelist);
	}
	else $bott='no';	
	if ($pagelist->MainAr['numpage'] == $numpage) $Menu->list2[$i]='./?np='.$numpage.'#zak'.$i;
	else $Menu->list2[$i]=$pagelist->MainAr['hrefp'].'?np='.$pagelist->MainAr['numpage']; 
	if ($Menu->list1[$i]) {
		$Menu->list1[$i]=$pagelist->part_name($Menu->list1[$i]);
		if (isset($a_link[$typelist][$i])) echo '<ul class="'.$clas[1].'">'.Maket::divclasstr($clas[2].'-item'.$i,$Pth,'','','li').'<a href="'.$Menu->list2[$i].'">'.$a_link[$typelist][$i].$Menu->list1[$i].$a_link[$typelist.'href'][$i].'</a>';
		else echo '<ul class="'.$clas[1].'">'.Maket::divclasstr($clas[2].'-item'.$i,$Pth,'','','li').'<a href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a>'; 
		$k=0;
		$NP=count($Menu->lp[$i]);
		if($NP>1)Maket::divclass($clas[2],$Pth,'','','ul');
		foreach ($Menu->lp[$i] as $k=>$val1){
			if ($Menu->lp[$i][$k]) {
				$pagelist= new Page($Menu->lp[$i][$k],$tabl);
				$nmp=$pagelist->getnamepage($pagelist);
				$nu=array_keys($nmp);
				$option_menu=$pagelist->part_name($nmp[$nu[0]]);
				$Menu->lp[$i][$k]=$pagelist->MainAr['hrefp'].'?np='.$pagelist->MainAr['numpage'];
			if ($NP>1) echo '<li><a href="'.$Menu->lp[$i][$k].'">'.$option_menu.'</a></li>';
		}				
	}
}
	echo '</ul></li>';
	echo '</ul>';
	
	}
}
echo '</div>';
}

static function showrowbootstrap($Pth='',$row=1,$clas='',$screen='col-md-12',$container='container'){
	if ($row==1)echo '<div class="'.$container.'"><div class="row">'.Maket::divclasstr($clas,$Pth,'',' '.$screen);
	elseif($row==-1)echo '<div class="'.$container.'">'.Maket::divclasstr($clas,$Pth).'<div class="'.$screen.'"><div class="row">';
	else echo '<div class="'.$container.'">'.Maket::divclasstr($clas,$Pth,'',' '.$screen);
} 

static function showheadergall($arr,$Pth,$typelist,$nb=0,$ne=0){
switch($typelist){
		case 'list': {
			echo '<div class="row">';
			Maket::divclass('col-md-4 col-sm-4 col-xs-12');
			show::accordsh('Y','imgs',$arr,$Pth,'list',3);
			echo '</div>';
			echo '</div>';
			
			break;
		}
		case 'butt':{
			$clas_layer=array('#main-nav','nav navbar-nav navbar-right','sub-menu');
			$img=$arr['clas']['img'].$arr['namep'][1];//'gallery/images/logo.png';
			//echo $img;
			Maket::divclass('#top',$Pth,'','','div id="top"');//<div class="header" id="top">
			Maket::divclass('navbar',$Pth,'',' navbar','nav');// <nav class="navbar navbar-inverse" role="navigation">
			Maket::divclass('container',$Pth,'',' '.$arr['idmen'][0]);//<div class="container">
            Maket::divclass('navbar-header',$Pth,'',' '.$arr['idmen'][0]);//<div class="navbar-header">
            Layer::button_bars(3,$Pth);
			if(file_exists($img))Maket::spanclass('',$Pth,$arr['idmen'][0].'-img','img src="'.$img.'" alt="Logo"');
			else Maket::spanclass($arr['loz'][0],$Pth,'navbar-brand scroll-top','a href="./?np='.$arr['lozhref'][0].'"');
             echo '</div>';//</div><!--/.navbar-header-->
			Layer::menush($arr,$Pth,$typelist,$clas_layer,$nb,$ne);
			echo '</div>';//<!--/.container-->
			echo '</nav>';//  <!--/.navbar-->
			echo '</div>';//    <!--/.header-->
			break;
		}
		case 'cont':{
			$clas_layer=array('bg__first','container','templatemo-flexbox','wow animated','arrow text-center');
			$img='gallery/images/creative-writing.png';	
			$img2='images/first-bg.jpg';
			Maket::divclass($clas_layer[0],$Pth,'background-image:url('.$img2.');',' templatemo-position-relative');
			Maket::divclass($clas_layer[1],$Pth,'',' '.$arr['idmen'][0]);
			Maket::divclass($clas_layer[2],$Pth,'',' '.$arr['idmen'][0]);
			Maket::divclass('row');
			Maket::divclass('col-md-4 col-sm-4 col-xs-12');
			Maket::divclass('left-image',$Pth,'',' '.$clas_layer[3].' fadeInLeft');
			echo Maket::spanclasstr('',$Pth,'img-responsive','img src="'.$img.'" alt="LogoPic"');
			Maket::closediv(2);//.left-image .col
			Maket::divclass('col-md-8 col-sm-8 col-xs-12');
			Maket::divclass('right-caption',$Pth,'',' '.$clas_layer[3].' fadeInRight');
			$ncont=Layer::showcontext($arr,1,0);
			Maket::closediv(2);//.right-caption .col
			Maket::closediv(3);//.row .templatemo .container
			Layer::showarrow($clas_layer[4],$Pth,'second-section');
			Maket::closediv(1);//.bg__first
			break;
		}
		case 'imgt':{
			$clas_layer=array('fadeInUp','sevice-items','wow bounceInUp','single-item','service-arrow');
			if($ne==0)$nopt=count($arr['buttimg']);
			else $nopt=$ne-$nb;
			Layer::showrowbootstrap($Pth,1,$clas_layer[0]);
			Maket::divclass($clas_layer[1],$Pth);
			for($i=$nb;$i<$nopt+$nb;$i++){
				Maket::divclass('col-md-3 col-sm-6 '.$clas_layer[2]);
				echo Maket::divclasstr($clas_layer[3],$Pth).'<i class="fa '.$arr['buttimg'][$i].'"></i>';
				Layer::showimgtext($arr,$i);
				Maket::closediv(2);
			}
			Maket::closediv(3);
			echo '<div class="row"><div class="col-md-12">';
			Layer::showarrow($clas_layer[4],$Pth,'third-section');
			Maket::closediv(3);
			break;
		}
		case 'imgs':{
			$img3='images/second-bg.jpg';
			$clas_layer=array('bg__third','#third-section','wow animated fadeInLeft','left-text','fourth-arrow');
			Maket::divclass($clas_layer[0],$Pth,'background-image:url('.$img3.');',' templatemo-position-relative');
			Maket::divclass($clas_layer[1],$Pth);
			Layer::showrowbootstrap($Pth,1,$clas_layer[2],'col-md-4 col-sm-6 col-xs-10');
			Maket::divclass($clas_layer[3],$Pth);
			Layer::contbutttext($arr['cont'][$nb],$Pth,'далее');
			Maket::closediv(3);
			echo '<div class="row">';
			Maket::divclass('templatemo-position-relative',$Pth,'',' col-md-12');
			Layer::showarrow($clas_layer[4],$Pth,'fourth-section');
			Maket::closediv(5);
			
			$img4='images/third-bg.jpg';
			$clas_layer=array('bg__fourth','#fourth-section','wow animated fadeInRight','left-text','fourth-arrow');
			Maket::divclass($clas_layer[0],$Pth,'background-image:url('.$img4.');',' templatemo-position-relative');
			Maket::divclass($clas_layer[1],$Pth);
			Layer::showrowbootstrap($Pth,1,$clas_layer[2],'col-md-4 col-md-offset-8 col-sm-6 col-xs-10 col-xs-offset-1');
			Maket::divclass($clas_layer[3],$Pth);
			Layer::contbutttext($arr['cont'][$nb+1],$Pth,'далее');
			Maket::closediv(3);
			echo '<div class="row">';
			Maket::divclass('templatemo-position-relative',$Pth,'',' col-md-12');
			Layer::showarrow($clas_layer[4],$Pth,'fifth-section');
			Maket::closediv(5);
			
			$img5='images/fourth-bg.jpg';
			$clas_layer=array('bg__fifth','#fifth-section','wow animated fadeInLeft','left-text','fifth-arrow');
			Maket::divclass($clas_layer[0],$Pth,'background-image:url('.$img5.');',' templatemo-position-relative');
			Maket::divclass($clas_layer[1],$Pth);
			Layer::showrowbootstrap($Pth,1,$clas_layer[2],'col-md-4 col-sm-6 col-xs-10');
			Maket::divclass($clas_layer[3],$Pth);
			Layer::contbutttext($arr['cont'][$nb+2],$Pth,'далее');
			Maket::closediv(3);
			echo '<div class="row">';
			Maket::divclass('templatemo-position-relative',$Pth,'',' col-md-12');
			Layer::showarrow($clas_layer[4],$Pth,'sixth-section');
			Maket::closediv(5);
			break;
		}
		case 'form_get':{
			$img6='images/second-bg.jpg';
			$clas_layer=array('bg__sixth','#sixth-section','wow animated fadeInDown','left-text','sixth-arrow');
			Maket::divclass($clas_layer[0],$Pth,'background-image:url('.$img6.');',' templatemo-position-relative');
			Maket::divclass($clas_layer[1],$Pth);
			Layer::showrowbootstrap($Pth,1,$clas_layer[2],'col-md-6 col-md-offset-3 col-xs-12');
			Layer::formconttext();
			Maket::closediv(2);
			Layer::showform($arr,1);
			break;
		}
		case 'form_post':{
			$arr1['name']=$arr['list'];
			unset($arr1['name']['link']);
			$clas_layer=array('bg__sixth','#sixth-section','wow animated fadeInDown','left-text','sixth-arrow');
			Maket::divclass($clas_layer[0],$Pth,'background-image:url('.$img6.');',' templatemo-position-relative');
			Maket::divclass($clas_layer[1],$Pth);
			Layer::showrowbootstrap($Pth,1,$clas_layer[2],'col-md-6 col-md-offset-3 col-xs-12');
			echo '<form action="#" method="post">';
			echo '<div class="row">';
			Maket::divclass('col-md-8 col-md-offset-2',$Pth,'',' wow animated fadeInUp');
			Maket::divclass('submit-form',$Pth);//echo '<div class="submit-form">';
			Maket::divclass('col-md-12',$Pth);//	<div class="col-md-12">
			show:: formoneshow($arr1);
			break;
		}
}
return $ncont;
}

static function showcontext($arr,$nb=0,$nc=0,$remark='Подробности'){
	echo '<h4>'.$arr['loz'][$nb].'</h4>';
	if($remark  === '')$remark=$arr['cont'][$nc+3];
	Maket::spanclass('<h2><span class="yellow">'.$arr['loz'][$nb+1].'</span>'.$arr['loz'][$nb+2].'</h2>',$Pth,'yellow');
    Maket::spanclass($arr['cont'][$nc].' <span>template</span><span class="lightgreen">mo</span>.com. '.$arr['cont'][$nc+1].' <a rel="nofollow" href="http://grandjetstudio.com"><span class="text-yellow'.$nc.'">grabdjetstudio.com</span></a>. ' .$arr['cont'][$nc+2],$Pth,'cont'.$nc,'p');       
    echo  '<div class="stroked-button"><a href="#" class="scroll-link" data-id="second-section">'.$remark.'</a></div><br>';
	return $nc+5;
}

static function contbutttext($str,$Pth,$nbut='',$clas=''){
	$arr_str=Page:: part_texts($str);
	if(count($arr_str)>2){
	 Maket::spanclass('<h2>'.$arr_str[0].'</h2>',$Pth,$clas);	
	 echo  '<div class="line '.$clas.'"></div>';
	foreach($arr_str as $key=>$val)if($key>0)echo '<p>'.$val.'</p>';
	if($nbut<>'')Maket::spanclass('<a href="#">'.$nbut.'</a>',$Pth,'button ','div');//echo '<div class="button'.'-'.$clas.'"><a href="#">'.$nbut.'</a></div>';
	}
	else {
		echo '<h2>'.Page:: part_name($str).'</h2><div class="line '.$clas.'"></div>
                  <p>'.Page::part_text($str).'</p><div class="button '.$clas.'">
                    <a href="#">'.$nbut.'</a></div>';
	}				
}

static function formconttext(){
	echo '<h3>Отправь свой вопрос прямо сейчас!</h3>
              <div class="col-md-12">
                <p>Nulla aliquam felis mi, volutpat convallis lorem eleifend id. Interdum et malesuada fames ac ante ipsum primis in faucibus.</p>
              </div>';
	
}

static function showimgtext($arr,$nc=0){
	echo '<h4>'.$arr['loz'][$nb].'</h4>';
	Maket::spanclass($arr['imgt'][$nc],$Pth,'imgt'.$nc,'p'); 
return $nc;	
}

static function showarrow($clas,$Pth,$num_section,$downup='down',$zak='zak'){
echo Maket::divclasstr($clas,$Pth).'<a href="#'.$zak.'" class="scroll-link btn btn-dark" data-id="'.$num_section.'"><i class="fa fa-angle-'.$downup.'"></i></a></div>';
}

private static function getform($id){
	$layer= new Layer;
	$res=$layer->db->query("SELECT * FROM `forms` WHERE `idform`=^Ni;",$id);
	return $res;
}


static function showform($arr,$id ,$name='Записать', $nform=0){
	$res=Layer::getform($id);
	//print_r($res);
	foreach($res as $key=>$val){
		if($val->type_field<>'select' && $val->type_field<>'check' && $val->type_field<>'radio'){
			$arr['name'][]=$val->name_field;
			$arr['id'][]=$val->id_field;
		    $arr['cls'][]=$val->clas_field;
		}
		else {
			$optsel=explode('|',$val->clas_field);
			$selopt=$optsel;
			$ind=$optsel[0];
			unset($optsel[0]);
			$arr['cls'][]=$ind;
			$optsel=explode('|',$val->name_field);
			$selopt=$optsel;
			$ind=$optsel[0];
			unset($optsel[0]);
			$arr['name'][]=$selopt;
		}
		
		$arr['type'][]=$val->type_field;
		$arr['place'][]=$val->place_field;
		$arr['req'][]=$val->req_field;
	}
	
	echo '<form action="#" method="get">';
	echo '<div class="row">';
	Maket::divclass('col-md-8 col-md-offset-2',$Pth,'',' wow animated fadeInUp');
	Maket::divclass('submit-form',$Pth);// echo '<div class="submit-form">';
	Maket::divclass('col-md-12',$Pth);//<div class="col-md-12">
	show::formoneshow($arr);
	foreach($arr['name'] as $key=>$val){
		if($arr['type'][$key]=='select')Layer::selmen($val,'',$arr['cls'][$key],'',$arr['place'][$key],'','') ;
		if($arr['type'][$key]=='check' || $arr['type'][$key]=='radio')echo '<div class="flexbox"';
		if($arr['type'][$key]=='check'){
			Layer::checkmen($val,$arr['cls'][$key],1);
		}
		if($arr['type'][$key]=='radio') Layer::radiomen($val,$arr['cls'][$key],1);
		if($arr['type'][$key]=='check' || $arr['type'][$key]=='radio') echo '</div>';
	}
echo '</div>';
echo '</div>';
echo '<div class="row">';
Maket::divclass('wow animated fadeInUp',$Pth,'',' col-md-4 col-md-offset-5');
Maket::divclass('templatemo-submit',$Pth,'','input type="submit" value="Submit"');
echo '</div>';
echo '</div>';
echo '</form>';

    //Layer::selmen($arr['Gender'],'','col-md-3','','null','','') ;      
	//Layer::selmen($arr['Age'],'','col-md-3','','null','','') ;      	 
                ?>
              <!--  <div class="col-md-3">
                  <select name="gender" id="gender">
                    <option value="null">Gender</option>
                  	<option value="Male">Male</option>
                    <option value="Female">Female</option>
                </select>
                </div>
                
                <div class="col-md-3">
                  <select name="age" id="age">
                    <option value="null">Age</option>
                  	<option value="18-24">18 - 24</option>
                    <option value="25-30">25 - 30</option>
                    <option value="31-40">31 - 40</option>
                    <option value="41-60">41 - 60</option>
                </select>
                </div>
                
              </div><!-- submit form 
              
            </div>
            
            </div>
            
            <div class="row">
            
                <div class="col-md-4 col-md-offset-5 wow animated fadeInUp">
                    <input type="submit" value="Submit" class="templatemo-submit" />
                </div>
           	 
          	</div>
            
          </form>-->
		<?
}

	static function radiomen($arropt,$clas,$num){
	echo '<div class="'.$clas.'" style="display:flex; margin: 5px;">';
		$i=0;
		while ($elem=each($arropt)){
		
		if ($i == $num ) echo '<input class="radio_option" type="radio" checked name="checked" value="rad'.$i.'" title="'.$elem['value'].'"><span class="radio">'.$elem['value'].'</span></input>';
		else echo '<input class="radio_option" type="radio" name="unchecked'.$i.'" value="'.$i.'" title="'.$elem['value'].'"><span class="radio">'.$elem['value'].'</span> </input>';
		$i++;
		}
		
	echo '</div>';
	}

	static function checkmen($arropt,$clas,$num){
	echo '<div class="'.$clas.'" style="display:flex; margin: 5px;">';
		$i=0;
		while ($elem=each($arropt)){
		if ($i == $num ) echo '<input class="check_option" type="checkbox" checked name="checked" value="" title="'.$elem['value'].'"><span class="hidcheck">'.$elem['value'].'</span></input>';
		else echo '<input class="uncheck_option" type="checkbox" name="unchecked'.$i.'" value="" title="'.$elem['value'].'"><span class="hidcheck">'.$elem['value'].'</span> </input>';
		$i++;
		}
		
	echo '</div>';
	}
			


static function selmen($arropt,$chice,$clas,$img,$num,$ch='chice',$tich='Найти'){
	echo '<div class="'.$clas.'">';
	echo '<span>';
		echo '<select class="poisk-'.$ch.'" name="'.$ch.'">';
		$i=0;
		while ($elem=each($arropt)){
		if(!is_array($chice))	$chice[$i]=$elem['key'];
		if ($i == $num ) echo '<option selected name="'.$ch.'" value="'.$num.'">'.$elem['value'].'</option>';
		else echo '<option value="'.$chice[$i].'">'.$elem['value'].'</option>';
		$i++;
		}
	echo '</select>';	
	echo '</div>';
	/*if(file_exists($img)) echo '</select></span><span><input title="'.$tich.'" class="poisk-img" name="'.$ch.'" value="'.$ch.'" type="image" src="'.$img.'"/></span>';
	else echo '<span><input class="poisk-butt" title="'.$tich.'" type="submit" value="'.$img.'"></span>';
		*/
	}

static function showicons($arr,$Pth,$nb=0,$ne=0){
	if($ne==0)$nopt=count($arr['buttimg']);
	else $nopt=$ne-$nb;
	Layer::showrowbootstrap($Pth,1);
	Maket::divclass('social-icons',$Pth);
	echo '<ul>';
	for($i=$nb;$i<$nopt-1;$i++){
		echo '<li><a href="http://'.$arr['social'][$i].'">'.Maket::divclasstr('fa ',$Pth,'',$arr['buttimg'][$i],'i').'</i></a></li>';
		}	
	echo '</ul>';
	Maket::closediv(3);
	echo '<div class="row"><div class="copyright-text"><p>Copyright &copy; 2084 Company Name</p></div></div>';
	Maket::divclass('col-md-12',$Pth);
	Layer::showarrow('third-arrow',$Pth,'top','up');
	Maket::closediv(2);
} 

static function showfooter($arr,$Pth,$nb=0,$ne=0){
	echo ' <footer>';
	Layer::showicons($arr,$Pth,$nb);
        /*<div class="container">
          <div class="row">
            <div class="col-md-12">
              <div class="social-icons">
                <ul>
                  <li><a href="#"><i class="fa fa-facebook"></i></a></li>
                  <li><a href="#"><i class="fa fa-twitter"></i></a></li>
                  <li><a href="#"><i class="fa fa-linkedin"></i></a></li>
                  <li><a href="#"><i class="fa fa-rss"></i></a></li>
                  <li><a href="#"><i class="fa fa-dribbble"></i></a></li>
                  <li><a href="#"><i class="fa fa-google"></i></a></li>
                </ul>
              </div>
            </div>
          </div>
          <div class="row">
            <div class="copyright-text">
              <p>Copyright &copy; 2084 Company Name</p>
            </div>
          </div>
          <div class="col-md-12">
            <div class="third-arrow">
              <a href="#" class="scroll-link btn btn-dark" data-id="top"><i class="fa fa-angle-up"></i></a>
            </div>
          </div>
        </div>*/
      echo '</footer>';
	 
}
}
?>