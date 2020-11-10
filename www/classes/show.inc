<?php
class Show {
	static function infosh($v){
echo '<div class="info" >';print_r($v);echo '</div>';	
} 
static function pauza($vari='Продолжить',$href=''){
	echo '<form><input action="'.$href.'" type="submit" value="'.$vari.'"/></form>';
}

static function layoutshadow($selector,$content,$Pth,$idmen,$prefix = ' grid'){
	
	if(is_array($content)){
		$img=$content['img'];
		$cont = $content['cont'];
		$clas = $content['clas'];
		$opac = $content['opac'];
		$styl = $content['styl'];
		if(isset($Pth[$clas]['effect']['hhead']))$n = $Pth[$clas]['effect']['hhead'];
	else $n=9;
	if($n == '') $n=9;
		$cont = Maket::spanclasstr($cont,$Pth,$clas,'div',$styl,$prefix);
		Maket::spanclass($cont,$Pth,$selector.'-'.trim($idmen).$n,$selector,'','opacity:'.$opac.';margin:5px;z-index: 0;background-image: url('.$img.');',$prefix);
		
	}
	else {
		
		$content = Maket::spanclasstr($content,$Pth,$selector.'_'.$idmen.$n,'div','color: #fff; background-color:#000 ;opacity: 1;z-index: 2;','',$prefix);
		Maket::spanclass($content,$Pth,$selector.'-'.$idmen.$n,$selector,'comment','opacity:1;margin:5px;z-index: 1;background-image: url('.$img.');',$prefix);
	}
	
}
static function layoutheaderland($MP,$Pth,$arr_head){
	
	foreach($arr_head as $val)$clas_head[] = $val;
	return show::showheaderflex($Pth,$clas_head,$arr_head,'');
}

static function layoutbuttonland($MP,$Pth,$arr_head){
	foreach ($arr_head as $val)$clas_head[] = $MP[19];
	return show::showbuttonflex($Pth,$clas_head,$arr_head,'');
}

static function layoutlistland($MP,$Pth){
	
	$clas_head = array($MP[14],$MP[14],$MP[14],$MP[14],$MP[14]);
	$arr_head = array($MP[14],$MP[14],$MP[14],$MP[14],$MP[14]);
	return show::showlistflex($Pth,$clas_head,$arr_head,'');
}

static function showheaderflex($Pth,$clas_head,$arr_head,$clas){
	$content='';
	$nopt=count($clas_head)-1;
	foreach ($clas_head as $key=>$val){
		if($val==$clas)$mode=1;
		else $mode=0;
		if($key<$nopt)$content.=show::showlogo($val,$arr_head[$key],$Pth,$mode,$key);
	}	
	return $content;
}

static function showbuttonflex($Pth,$clas_head,$arr_head,$clas){
	$content='';
	$nopt=count($clas_head)-1;
	foreach ($clas_head as $key=>$val){
		$mode=0;
		if($key<$nopt)$content.=show::showlogo($val,$arr_head[$key],$Pth,$mode,$key);
	}	
	return $content;
}
static function showlistflex($Pth,$clas_head,$arr_head,$clas){
	$content='';
	$nopt=count($clas_head)-1;
	foreach ($clas_head as $key=>$val){
		$mode=0;
		if($key<$nopt)$content.=show::showlogo($val,$arr_head[$key],$Pth,$mode,$key,'listhref','list');
	}	
	return $content;
}

static function layoutcontent($MP,$Pth,$content){
	$cont='';
	$cont=Maket::spanclasstr($content['Sleft'],$Pth,$MP[4],'div').Maket::spanclasstr($content['Scentr'],$Pth,$MP[6],'div').Maket::spanclasstr($content['Sright'],$Pth,$MP[5],'div');
	$cont1=Maket::spanclasstr($content['Wleft'],$Pth,$MP[7].'-Left','div').Maket::spanclasstr($content['Wcentr'],$Pth,$MP[7].'-Center','div').Maket::spanclasstr($content['Wright'],$Pth,$MP[7].'-Right','div');
	$cont2=Maket::spanclasstr($content['subhead'],$Pth,$MP[8],'div');
	$cont1=Maket::spanclasstr($cont1.$cont2.$cont,$Pth,$MP[7],'div');
	$result=Maket::spanclasstr($cont1,$Pth,$MP[3],'div'); 
	return $result;
}

static function showcontentland($content,$MP,$Pth,$idmen){
	if(isset($Pth[$main_clas]['numpar']['Grid']))$ngrid=$Pth[$main_clas]['numpar']['Grid'];
	else $ngrid = count($clas);
	return Maket::divclasstr($MP[3].$ngrid,$Pth,'',$idmen).show::layoutcontent($MP,$Pth,$content).'</div>';	
}

static function showlogo($clas,$arr,$Pth,$mode=0,$key=0,$typelist1='butthref',$typelist='butt',$n_simb=351,$disp='',$style='',$prefix=''){
	if($prefix=='')$prefix=' '.$disp;
	$str='';
	switch($mode){
		case '0':{//хедер простой
			if(!is_array($arr) )$block_logo=$arr;
			if(isset($block_logo)){
				//$style = 'z-index: 2;position:relative;';
				$str.=Maket::spanclasstr(Maket::spanclasstr($block_logo,$Pth,$clas.'-ul'.$prefix,'ul'),$Pth,$clas,'div');
			}
			break;	
		}
		case '1':{//хедер с логотипом
			
			if(is_array($arr)){
				if(show::get_image_type($arr['clas']['img'].$arr['namep'][1]))
					$str.=show::scalimag3($arr,$arr['clas']['img'].$arr['namep'][1],'./?np='.$arr['nump'],$Pth,0);
			
			}
			break;
		}
	case '2':{//карточка элемента
		$str='';
		//print_r($arr['n']);
		if($typelist1 === '')$typelist1=$typelist.'href';
	else $typelist1=$typelist1.'href';
	if($typelist === 'news')$arr[$typelist][$key]=$arr['n']['text'];
	//echo $arr[$typelist][$key];
	if(!isset($_GET['konstrS'])){
		if(isset($arr[$typelist][$key]))extract(maket::datacard($arr,$typelist,$key));
		//echo 'fzag'.$fulzag_card.'link '.$href_card;
		$n_slimb=intval(strpos($fulzag_card,'<>'));
		if(strlen($fulzag_card)>$n_slimb && $n_slimb != 0)$zagol=substr_replace($fulzag_card,'...',floor($n_simb/10));
		else {$zagol=$fulzag_card;$fulzag_card='';}
		//echo 'zagol '.$zagol.$n_slimb;
		$cardImg='<img class="img-responsive" src="'.$arr['clas']['img'].$img_card.'"/>';	
	}
	else {
		$fulzag_card=$zagol=$but_card='';
		$n_simb=strlen($arr[$typelist][$key]);
		$text_card=$arr[$typelist][$key];
		if($arr[$typelist1][$key])$href_card=$arr[$typelist1][$key];
		else $href_card = '';
		$img_card=$arr['imgs'][$key];
		$cardImg='<img class="img-responsive" src="'.$arr['clas']['img'].$img_card.'"/>';	
		if($typelist === 'imgt'){
			$img_card=$arr['imgs'][$key];
			$typecard='imgs';
		}
		elseif($typelist === 'butt'){
			$img_card=$arr['buttimg'][$key];
			$typecard='buttimg';
		}
		else $img_card='';
		
		
	}
	
	if ($arr['idmen'][0] <> 'land' && $href_card != '') {
					$buthref='./?np='.$href_card;	
				}
				else {
					$buthref='#zak'.$key;
				}
		if($typelist1<>'conthref' ){
			$n_simb =intval(strpos($fulzag_card,'<>'));
			if($n_simb =strpos($fulzag_card,'<>') && $n_slimb != 0)$fulzag_card0=substr_replace($fulzag_card,'...',$n_simb) ;
					if(strlen($fulzag_card)>$n_simb){
						$zagol=$fulzag_card0;
						$fulzag_card=substr_replace(strstr($fulzag_card,'<>'),'',0,2);
					}
					else {
						$zagol=$fulzag_card;
						$fulzag_card='';}
			if($img_card && isset($_GET['konstrS']))$cardImg='<div>'.$arr['link'][$typecard][$key].$cardImg.'</div>';
			$str.=Maket::divclasstr($clas,$Pth,'',$disp);
			$str.=Maket::divclasstr($clas.'_item',$Pth);
			//echo 'here';
			//echo 'zagol '.$fulzag_card;
			if($zagol)$str.=Maket::spanclasstr('<h4><a href="'.$buthref.'">'.$zagol.'</a></h4>',$Pth,$clas.'-li hidyes');
			//'<li class="'.$clas.'-li hidyes"><h4><a href="'.$buthref.'">'.$zagol.'</a></h4></li>';
			if($fulzag_card && $fulzag_card != $zagol)$str.=Maket::spanclasstr('<h4><a href="'.$buthref.'">'.$fulzag_card.'</a></h4>',$Pth,$clas.'-li','','',' hidno');
			if($arr['clas']['img'].$img_card<>$arr['clas']['img'])$str.=Maket::spanclasstr($cardImg,$Pth,$clas.'-img'.$key,'li');	
			$str.='<ul>';
			if($n_simb =strpos($text_card,'<>'))$text_card0=substr_replace($text_card,'...',$n_simb) ;
			else {$text_card0=$text_card;$n_simb=intval(strlen($text_card));}
			if($n_slimb !=0 && strlen($text_card)>$n_simb && !isset($_GET['konstrS'])){
				
			if($text_card0)$str.=Maket::spanclasstr($text_card0,$Pth,$clas.'_zagt'.$key,'li','','',' hidyes');
				//$str.='<li class="hidyes">'.$text_card0.'</li>';
			if($text_card &&  $text_card != $text_card0)$str.=Maket::spanclasstr($text_card,$Pth,$clas.'_text'.$key,'li','','',' hidno');
				//$str.='<li class="hidno">'.$text_card.'</li>';
			//$str.='</ul>';
			}
			elseif($text_card<>'') $str.=Maket::spanclasstr($text_card,$Pth,'card_item-li_'.$key,'li');// $str.='<li>'.$text_card.'</li>';
			if($but_card<>'' )$str.='<li>'.Maket::divclasstr('button part-button_'.$key,$Pth,'','','button').'<a href="'.$buthref.'">'. $but_card.'</a></button></li>';
				}
			elseif(isset($arr['cont'][$key]) && $arr['cont'][$key]!= '' ) {
				if ($arr['idmen'][0] <> 'land' && $href_card != '') {
					$buthref='./?np='.$href_card;	
				}
				else {
					$buthref='#zak'.$key;
				}
				if(!isset($_GET['konstrS']) ){
					extract(Maket::datacard($arr,'cont',$key));
					
					if($n_simb =strpos($fulzag_card,'<>'))$fulzag_card0=substr_replace($fulzag_card,'...',$n_simb) ;
					//$str.=$fulzag_card0.$n_simb;
					if(strlen($fulzag_card)>intval($n_simb)){
						if(isset($fulzag_card0)){
							$zagol=$fulzag_card0;
							$fulzag_card=substr_replace(strstr($fulzag_card,'<>'),'',0,2);
						}
					}
					else {
						$zagol=$fulzag_card;
						$fulzag_card='';}
					//$str.='pic='.$cardImg;
					if($typelist === 'imgt')$img_card = $arr['clas']['img'].$arr['imgs'][$key];
				}
				else {
					$text_card=$arr['cont'][$key];
					if($img_card && isset($_GET['konstrS']))$cardImg='<div>'.$arr['link'][$typecard][$key].$cardImg.'</div>';
					}
				//$str.=$key.'='.$typelist1.'='.$img_card.' ='.$text_card.'=>';
				//$str.=$key.'='.$text_card.'='.$but_card;
				$str.=Maket::divclasstr($clas,$Pth,'',$disp);
				$str.=Maket::divclasstr('item_card_'.$key,$Pth);
				//$str.='there';
				$str.='<ul>';
				if(!isset($_GET['konstrS'])){
					$str.=Maket::spanclasstr('<h4>'.$zagol.'</h4>',$Pth,$clas.'_zagt'.$key,'li','','',' hidyes');
					//$str.='<li class="hidyes"><h4>'.$zagol.'</h4></li>';
					if($fulzag_card != '')$str.=Maket::spanclasstr('<h4>'.$fulzag_card.'</h4>',$Pth,$clas.'_zagt'.$key,'li','','',' hidno');
					if($but_card === '')$str.='<a href="'.$buthref.'">...</a>';
				}
				else {
					$str.='<a href="'.$buthref.'">';
					$str.= Maket::spanclasstr('<h4>'.$fulzag_card.'</h4>',$Pth,$clas.'_zagt'.$key,'li');
					//'<li class="hidyes"><h4>'.$fulzag_card.'</h4></li>';
				}
				if($img_card<>$arr['clas']['img'] )$str.='<li>'.$cardImg.'</li>';
				//if(strlen($text_card)>$n_simb ){
					if(!isset($_GET['konstrS'])){
						if($n_simb =strpos($text_card,'<>')){
							$text_card=$text_card;
							$text_card0=substr_replace($text_card,'...',$n_simb) ;
							if($text_card0)$str.=Maket::spanclasstr($text_card0,$Pth,$clas.'_zagt'.$key,'li','','',' hidyes');
							if($text_card && $text_card !=$text_card0) $str.=Maket::spanclasstr($text_card,$Pth,$clas.'_text'.$key,'li','','',' hidno');
						}
						else {
							$text_card0=$text_card;
							$n_simb=strlen($text_card);
							if($text_card0)$str.=Maket::spanclasstr($text_card0,$Pth,$clas.'_zagt'.$key,'li');
							}
						
					}
					else {
						 $str.=Maket::spanclasstr($text_card,$Pth,$clas.'_text'.$key,'li');
					}
				//}	
				//elseif($text_card<>'') $str.='<li>'.$text_card.'</li>';
				if(!isset($_GET['konstrS']))$str.='</a>';
				if($but_card<>'' )$str.='<li>'.Maket::divclasstr('button part-button_'.$key,$Pth,'','','button').'<a href="'.$buthref.'">'. $but_card.'</a></button></li>';
				}
				//elseif($img_card<>$arr['clas']['img'])$str.='<li>'.$cardImg.'</li>'; 
				//elseif($text_card<>'') $str.='<li>'.$text_card.'</li>';
				
						
				$str.='</ul>';
				$str.='</div></div>';
			
					break;
		}	
	case '3':{//заголовок блока class=zag-h1 + текст class=content-...
			$str='';
			$style = 'z-index: 2;position:relative;';
			if(isset($arr[$typelist][$key]) && $typelist=='loz'){
			if(strstr($clas,'-')){
				$clas_zag=explode('-',$clas);
				if($arr[$typelist1][$key]<>'')$arr[$typelist][$key]='<a class="'.$clas_zag[0].'" href="./?np='.$arr[$typelist1][$key].'"><h2>'.$arr[$typelist][$key].'</h2></a>';
				Maket::divclass('items part-'.$clas_zag[0],$Pth,'',$disp);
				$str.=Maket::spanclasstr($arr[$typelist][$key],$Pth,'item-'.$clas_zag[0].$key,$clas_zag[1],'',$style,$prefix);
				
			}
			else {
				if(Maket::part_name($arr[$typelist][$key])){
					if(!isset($_GET['konstrS']))$str.=Maket::spanclasstr(Maket::part_name($arr[$typelist][$key]),$Pth,'item-'.$clas,'h2','',$style,$prefix);
					else $str.=Maket::spanclasstr($arr[$typelist][$key],$Pth,'item-'.$clas,'h2','',$style,$prefix);
					}
				$str.=Maket::divclasstr('items part-'.$clas,$Pth,'',$disp);
				$n_simb=$Pth['hidyes']['effect']['crop'];
				if(!isset($_GET['konstrS']))$str.=Maket::spanclasstr('<h1>'.Maket::part_text($arr[$typelist][$key]).'</h1>',$Pth,'hidyes '.$clas_zag[0].($key),'li');
				else $str.=Maket::spanclasstr('<h1>'.$arr[$typelist][$key].'</h1>',$Pth,'hidyes '.$clas_zag[0].($key),'li');
			}
			}
			elseif($arr[$typelist][$key]<>'' && $typelist=='cont'){
				$str.=Maket::divclasstr('content'.$key,$Pth,'',' '.$arr['idmen'][0]);
				if(Maket::part_name($arr[$typelist][$key])){
					if(!isset($_GET['konstrS'])){
						if($arr[$typelist1][$key]<>'') $str.='<a class="'.$clas.$key.'" href="./?np='.$arr[$typelist1][$key].'">'.Maket::spanclasstr(Maket::part_name($arr[$typelist][$key]),$Pth,'Hitem-'.$clas,'h3','',$style,$prefix).'</a>';
						else $str.=Maket::spanclasstr(Maket::part_name($arr[$typelist][$key]),$Pth,'Hitem-'.$clas,'h3','',$style,$prefix);
					}
					else {
						if($arr[$typelist1][$key]<>'') $str.='<a class="'.$clas.$key.'" href="./?np='.$arr[$typelist1][$key].'">'.Maket::spanclasstr($arr[$typelist][$key],$Pth,'Hitem-'.$clas,'h3','',$style,$prefix).'</a>';
						else $str.=Maket::spanclasstr($arr[$typelist][$key],$Pth,'Hitem-'.$clas,'h3','',$style,$prefix);
					}
					}
					//echo $n_simb;
					if( $n_simb<0){
						if(!isset($_GET['konstrS'])){
							$str.=Maket::spanclasstr(substr_replace(Maket::part_text($arr[$typelist][$key]),'...',-$n_simb),$Pth,'closes Titem-'.$clas,'div');
							if($arr[$typelist1][$key]<>'')$str.= '<a title="Посмотреть все" href="./?np='.$arr[$typelist1][$key].'#zak'.$key.'"> ......</a>';
							$href='./?editp='.$Pth['Titem-'.$clas]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.$clas]['id'];
							if(isset($Pth['adm'])) $str.='<a title="обрезать" href="javascript:new_window(\''.$href.'\')">.....</a>';
						}
						//return $key;
					}
					if(!isset($_GET['konstrS'])){
						if(strlen($arr[$typelist][$key])>$n_simb && $n_simb>0){
						$str.=Maket::spanclasstr(substr_replace(Maket::part_text($arr[$typelist][$key]),'...',$n_simb),$Pth,'Titem-'.$clas,'div','','',' hidyes');
						Maket::spanclass(Maket::part_text($arr[$typelist][$key]),$Pth,'Titem-'.$clas,'div','','',' hidno');
						$href='./?editp='.$Pth['Titem-'.$clas]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.$clas]['id'];
						if(isset($Pth['adm'])) $str.='<a title="обрезать" href="javascript:new_window(\''.$href.'\')">...</a>';
						}
						elseif($arr[$typelist1][$key]<>'')$str.='<a class="'.$clas.'" href="./?np='.$arr[$typelist1][$key].'">'.Maket::spanclasstr(Maket::part_text($arr[$typelist][$key]),$Pth,'Titem-'.$clas,'div').'</a>';
						elseif($arr[$typelist][$key]<>'') $str.=Maket::spanclasstr(Maket::part_text($arr[$typelist][$key]),$Pth,'Titem-'.$clas,'div');
					}
					else {
						 $str.=Maket::spanclasstr($arr[$typelist][$key],$Pth,'Titem-'.$clas,'div');
					}
				}
				else {
					if(!isset($_GET['konstrS']))
					$str.=Maket::spanclasstr(Maket::part_text($arr[$typelist][$key]),$Pth,'Titem-'.$clas,'div','',$style,$prefix);
					else $str.=Maket::spanclasstr($arr[$typelist][$key],$Pth,'Titem-'.$clas,'div','',$style,$prefix);
				}
			
			$str.='</div>';
			
			break;
		}
		case '6':{
			$str.= '<div class="container__blog-head _container">
                    <div class="body__avatar"><img src="/images/img/avatar.png"><span class="nickname">nickname</span></div>
                    <div class="body__icons">
                        <div class="menu__icon icon-menu">
                            <span><i class="fas fa-user-circle"></i></span>
                            <span><i class="fas fa-compass"></i></span>
                            <span><img style="width: 21px;"src="./images/img/icons/chalkboard-teacher-solid.svg" alt="user-header"></span>
                            <span><img style="width: 21px;"src="./images/img/icons/splotch-solid.svg" alt="user-header"></span>
                            <span><img style="width: 21px;"src="./images/img/icons/globe-americas-solid.svg" alt="user-header"></span>
						</div>
					</div>
				</div>';
			break;
		}
		case '7':{
			$str.='<div class="top-nav">
                        <ul class="memenu skyblue"><li class="active"><a href="index.html">Home</a></li>
                            <li class="grid"><a href="#">Men</a>
                                <div class="mepanel">
                                    <div class="row">
                                        <div class="col1 me-one">
                                            <h4>Shop</h4>
                                            <ul>
                                                <li><a href="products.html">New Arrivals</a></li>
                                                <li><a href="products.html">Blazers</a></li>
                                                <li><a href="products.html">Swem Wear</a></li>
                                                <li><a href="products.html">Accessories</a></li>
                                                <li><a href="products.html">Handbags</a></li>
                                                <li><a href="products.html">T-Shirts</a></li>
                                                <li><a href="products.html">Watches</a></li>
                                                <li><a href="products.html">My Shopping Bag</a></li>
                                            </ul>
                                        </div>
                                        <div class="col1 me-one">
                                            <h4>Style Zone</h4>
                                            <ul>
                                                <li><a href="products.html">Shoes</a></li>
                                                <li><a href="products.html">Watches</a></li>
                                                <li><a href="products.html">Brands</a></li>
                                                <li><a href="products.html">Coats</a></li>
                                                <li><a href="products.html">Accessories</a></li>
                                                <li><a href="products.html">Trousers</a></li>
                                            </ul>	
                                        </div>
                                        <div class="col1 me-one">
                                            <h4>Popular Brands</h4>
                                            <ul>
                                                <li><a href="products.html">499 Store</a></li>
                                                <li><a href="products.html">Fastrack</a></li>
                                                <li><a href="products.html">Casio</a></li>
                                                <li><a href="products.html">Fossil</a></li>
                                                <li><a href="products.html">Maxima</a></li>
                                                <li><a href="products.html">Timex</a></li>
                                                <li><a href="products.html">TomTom</a></li>
                                                <li><a href="products.html">Titan</a></li>
                                            </ul>		
                                        </div>
                                    </div>
                                </div>
                            </li>
                            <li class="grid"><a href="#">Women</a>
                                <div class="mepanel">
                                    <div class="row">
                                        <div class="col1 me-one">
                                            <h4>Shop</h4>
                                            <ul>
                                                <li><a href="products.html">New Arrivals</a></li>
                                                <li><a href="products.html">Blazers</a></li>
                                                <li><a href="products.html">Swem Wear</a></li>
                                                <li><a href="products.html">Accessories</a></li>
                                                <li><a href="products.html">Handbags</a></li>
                                                <li><a href="products.html">T-Shirts</a></li>
                                                <li><a href="products.html">Watches</a></li>
                                                <li><a href="products.html">My Shopping Bag</a></li>
                                            </ul>
                                        </div>
                                        <div class="col1 me-one">
                                            <h4>Style Zone</h4>
                                            <ul>
                                                <li><a href="products.html">Shoes</a></li>
                                                <li><a href="products.html">Watches</a></li>
                                                <li><a href="products.html">Brands</a></li>
                                                <li><a href="products.html">Coats</a></li>
                                                <li><a href="products.html">Accessories</a></li>
                                                <li><a href="products.html">Trousers</a></li>
                                            </ul>
                                        </div>
                                        <div class="col1 me-one">
                                            <h4>Popular Brands</h4>
                                            <ul>
                                                <li><a href="products.html">499 Store</a></li>
                                                <li><a href="products.html">Fastrack</a></li>
                                                <li><a href="products.html">Casio</a></li>
                                                <li><a href="products.html">Fossil</a></li>
                                                <li><a href="products.html">Maxima</a></li>
                                                <li><a href="products.html">Timex</a></li>
                                                <li><a href="products.html">TomTom</a></li>
                                                <li><a href="products.html">Titan</a></li>
                                            </ul>	
                                        </div>
                                    </div>
                                </div>
                            </li>
                            <li class="grid"><a href="#">Kids</a>
                                <div class="mepanel">
                                    <div class="row">
                                        <div class="col1 me-one">
                                            <h4>Shop</h4>
                                            <ul>
                                                <li><a href="products.html">New Arrivals</a></li>
                                                <li><a href="products.html">Blazers</a></li>
                                                <li><a href="products.html">Swem Wear</a></li>
                                                <li><a href="products.html">Accessories</a></li>
                                                <li><a href="products.html">Handbags</a></li>
                                                <li><a href="products.html">T-Shirts</a></li>
                                                <li><a href="products.html">Watches</a></li>
                                                <li><a href="products.html">My Shopping Bag</a></li>
                                            </ul>
                                        </div>
                                        <div class="col1 me-one">
                                            <h4>Style Zone</h4>
                                            <ul>
                                                <li><a href="products.html">Shoes</a></li>
                                                <li><a href="products.html">Watches</a></li>
                                                <li><a href="products.html">Brands</a></li>
                                                <li><a href="products.html">Coats</a></li>
                                                <li><a href="products.html">Accessories</a></li>
                                                <li><a href="products.html">Trousers</a></li>
                                            </ul>	
                                        </div>
                                        <div class="col1 me-one">
                                            <h4>Popular Brands</h4>
                                            <ul>
                                                <li><a href="products.html">499 Store</a></li>
                                                <li><a href="products.html">Fastrack</a></li>
                                                <li><a href="products.html">Casio</a></li>
                                                <li><a href="products.html">Fossil</a></li>
                                                <li><a href="products.html">Maxima</a></li>
                                                <li><a href="products.html">Timex</a></li>
                                                <li><a href="products.html">TomTom</a></li>
                                                <li><a href="products.html">Titan</a></li>
                                            </ul>	
                                        </div>
                                    </div>
                                </div>
                            </li>
                            <li class="grid"><a href="typo.html">Blog</a>
                            </li>
                            <li class="grid"><a href="contact.html">Contact</a>
                            </li>
                        </ul>
                    </div>
                    <div class="clearfix"> </div>';
			
			break;
		}
		case '8':{
			$str = '<div class="top-header__column top-header__column_logo">
			<div class="top-header__logo"><a href="" ><img src="images/logo.png" alt="logo"></a>
			<span>Современные сайты для людей</span></div>
		</div>';

			break;
		}
		case '9':{
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		break;
		}
	}

return $str;
}
 
 static function get_image_type( $image_path_or_resource ) {
    $img = getimagesize( $image_path_or_resource );
    if ( !empty( $img[2] ) ) // returns an integer code
        return image_type_to_mime_type( $img[2] );
    return false;
}
 
static function scalimag3($arr,$img, $bbb,$Pth ,$numclass,$i=0,$typelist='namep',$typelist1='loz',$typelist2='list'){
$cla=$arr['clas'];
$clas=$cla['clas'][$numclass];
$PthCl12=$cla['clas'][12];
$PthCl13=$cla['clas'][13];
$PthCl14=$cla['clas'][14];
$PthC0=$clas.'-'.$arr['idmen'][0];
$Pth12=$arr["idmen"][0].'-'.$PthCl12;	
$Pth14=$arr["idmen"][0].'-'.$PthCl12.'4-'.$PthCl14;
$Pth13=$arr["idmen"][0].'-'.$PthCl12.'4-'.$PthCl13;
if(isset($Pth[$clas]))	$size_par['pics']=$Pth[$clas]['numpar']['Pics'];

if(isset($Pth[$clas.'-item'.$i]))$PthL0='font-size:'.$Pth[$clas.'-item'.$i]['numpar']['Sizes'].'px;';
elseif(isset($Pth[$clas]['numpar']['Sizes'])) $PthL0='font-size:'.$Pth[$clas]['numpar']['Sizes'].'px;';
else $PthL0='14px';
if(isset($Pth[$PthC0]['numpar']['Sizes']))$PthL1='font-size:'.$Pth[$PthC0]['numpar']['Sizes'].'px;';
else $PthL1=$PthL0;
if(isset($Pth[$PthC0]['Sizes']))$PthS0='font-size:'.(2*$Pth[$PthC0]['Sizes']).'px;';
else $PthS0=$PthL0;
if(isset($Pth[$clas]['numpar']['Sizes']))$PthS1='font-size:'.(2*($Pth[$clas]['numpar']['Sizes']+2)).'px;';
else $PthS1=$PthL0;
//echo $clas;
if ($clas=='main-banner'){
	if(isset($size_par['pics'][0]))$n=$size_par['pics'][0];
	//echo '<style> style="display:none;"</style> ' ;
}
elseif($clas=='logo'){
	if(isset($size_par['pics'][0]))$n=$size_par['pics'][0];
}



if(isset($PthL1)) $size_parfs13=$PthL1;
else$size_parfs13='14px';
if(isset($PthS0)) $size_parfsC0=$PthS0;
else $size_parfsC0='12px';
if(isset($PthS1)) $size_parfs14=$PthS1;
else $size_parfs14='16px';

//стили
 


//if(isset($arr['link'])) $a_link=$arr['link'];
//else
$a_link = '';
if (file_exists($img) )
      {
         $size = GetImageSize($img); 
		 if($size[0]>0 && $size[1]>0)
         { 
if($clas == 'logo') $ww=200;
elseif($clas == 'main-banner') $ww=700;
else $ww=200;

if ($size[0]>=$size[1]) $n=ceil($size[0]/$ww);
else $n=ceil($size[1]/$ww);

$str = '';
$str .= Maket::divclasstr( $clas.'-'.$arr['idmen'][0],$Pth);
if (is_array($bbb)) {
	$img=$cla['img'].$bbb[4];
	$str .=  Maket::divclasstr($Pth13,$Pth,$PthL0,$prefix,'li').'<p>'.$bbb[0].'</p><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'><a  href="'.$bbb[3].'"><span>'.$bbb[1].'</span></a></li>'.Maket::divclasstr($Pth14,$Pth,$PthS0,$prefix,'li').$bbb[2].'</li>';
}
else { 
	if ($clas == 'logo') {
			
			$str .=  Maket::divclasstr($clas.'-logo'.'-'.$arr['idmen'][0],$Pth).'<a href="'.$bbb.'"><img  src="'.$img.'"  width:"'.intval($size[0]/$n).'px;"  height:"'.intval($size[1]/$n).'px;"></img></a></div>';
			
			 if (isset($arr[$typelist][$i+3])) $str .=  Maket::divclasstr($clas.'-item-'.$arr['idmen'][0],$Pth).Maket::divclasstr($clas.'-li-'.$arr['idmen'][0],$Pth,'','','li').Maket::spanclasstr($arr[$typelist][$i+3],$Pth,$clas.'-span-'.$arr['idmen'][0],'span').'</li></div>';
			 
			if ($arr['idmen'][0]<>'land') {
				if(isset($arr[$typelist][$i+2]))$str .=  Maket::divclasstr($clas.'-item-'.$arr['idmen'][0],$Pth).Maket::divclasstr($PthC0.'-li',$Pth,'','','li').'<b>'.$arr[$typelist][$i+2].'</b></li></div>';
				
			}
			
		}
		elseif($clas == 'main-banner') $str .=  '<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></img></li>';
		else {
		if (isset($arr[$typelist1][$i+1])) $str .= Maket::divclasstr($Pth13,$Pth,'font-size:'.$size_parfs13,'li').'<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'><a href="./?np='.$arr[$typelist1.'href'][$i+1].'">'.Maket::divclasstr($clas,$Pth,$PthL0,'','span').$arr[$typelist1][$i+1].'</span></a></img>';
		$str .=  '</li>';
		$str .=  Maket::divclasstr($Pth14,$Pth,'font-size:'.$size_parfs14,'li');
		$str .=  '<a href="./?np='.$arr[$typelist1.'href'][$i].'">'.$arr[$typelist1][$i].'</a>';
		$str .=  '</li>';
		}
		
	}
	$str .= '</div>';
}
}
return $str;
}
 
static function shinf($a){
	return $a.'&info';
}

static function p_link($arrmakstyle){
	$gt='изменить ';
	foreach ($arrmakstyle as $key=>$val) {
		$j=0;
		if(is_array($val)){
			foreach ($val as $value){
				$p_link[$key][$j]='';
				$ft='текст ';
				$im='up.gif';
				$cl='turn180deg';
				if ($value=='') $gt='добавить ';
				if (isset($arrmakstyle[$key]['link'][$j]) && isset($arrmakstyle[$key][$j]))
					$p_link[$key][$j]='<a title="'.$gt.$ft.' '.$arrmakstyle[$key][$j].' " href="?'.'&editp='.$arrmakstyle[$key]['link'][$j].'&tab=maket"><img src="./images/'.$im.'" class="'.$cl.'" ></a>';
				$gt='изменить ';
				unset($ft);
				$j++;
			}
		}
}
return $p_link;
}

static function a_link($arr){ 
	$gt='изменить ';
	foreach ($arr as $key=>$val) {
		$j=0;
		if(is_array($val) && $key != 'link' && $key != 'site' && $key != 'typmen'){
		foreach ($val as $value){
			$cl='edit ';
			$a_link[$key][$j]='';
			if (!is_array($value)) $value1=$value;
			else $value1='';
			if (strstr($key,'href')) {$ft='ссылку ';$im='down.gif';$cl='turn90deg';}
			elseif (strstr($key,'nam') && !strstr($value1,'.jpg') && !strstr($value1,'.gif') && !strstr($value1,'.png')) {$ft='текст ';$im='down.gif';$cl.='turn180deg';}
			elseif (strstr($key,'cont') || strstr($key,'imgt')) {$ft='текст ';$im='up.gif';$cl.='turn90deg';}
			elseif (strstr($key,'loz') ) {$ft='текст ';$im='up.gif';$cl.='turn40deg';}
			elseif (strstr($key,'list')) {$ft='текст ';$im='down.gif';$cl.='turn40deg';}
			elseif(strstr($key,'imgs') ) {$ft='картинку';$im='AG00090_.gif';$cl.='turn40deg';}		
			elseif(strstr($value1,'.jpg') || strstr($value1,'.gif') || strstr($value1,'.png')) {$ft='картинку';$im='AG00090_.gif';$cl.='turn70deg';}
			elseif (strstr($key,'butt') || strstr($key,'foot')) {$ft='текст ';$im='down.gif';$cl.='turn90deg';}
			else {$ft='значение';$im='down.gif';$cl.='turn270deg';}
			if ($value=='') $gt='добавить ';
		if (isset($arr['link'][$key][$j]) && isset($arr[$key][$j]) && $j<>19) {
			$hrf='?np='.$arr['nump'].'&editp='.$arr['link'][$key][$j];
			$a_link[$key][$j]='<a title="'.$gt.$ft.' '.$value.'" href="javascript:new_window(\''.$hrf.'\')"><img src="./images/'.$im.'" class="'.$cl.'" ></a>';
		}
		$gt='изменить ';
		unset($ft);
	$j++;
	}
	}
	else {
		$ft='значение';$im='up.gif';$cl='turn90deg';
		if ($val=='') $gt='добавить ';
		if (isset($arr['link'][$j])) $a_link[$j]='<a title="'.$gt.$ft.' '.$val[$j].' " href="?np='.$arr['nump'].'&editp='.$val['link'][$j].'"><img src="./images/'.$im.'" class="'.$cl.'" ></a>';
		$gt='изменить ';
		unset($ft);
		$j++;
	}
	
	}
	return $a_link;
	}
	
private function readyshowpage(){
		
}

static function iconstr($clas,$img,$styl,$alt=''){
	$str= '<span><img class="'.$clas.'" style="'.$styl.'"src="'.$img.'" alt="'.$alt.'">
	</span>';
	return $str;
}

static function menumainstr($arr,$clas,$clas1,$Pth,$typelist,$clasI='',$nb=0,$no=0){
	$i=0;
	$str='';
	if($clasI != '')$str.=show:: iconstr($clasI,'./images/img/icons/asterisk-solid.svg','width: 18px;','user-header');
	$numpage=$arr['nump'];
	$typesite=$arr['idmen'][0];
	if($no==0)$no=count($arr[$typelist])-1;
	$str.=Maket::divclasstr($clas,$Pth,'','','ul');
	foreach ($arr[$typelist] as $val){
		if ($val=='') $ed='addnew';
		if ($i>=$nb && $i<($nb+$no) && $val <> '') {
				if ($typesite <> 'land') $href='href="./?np='.$arr[$typelist.'href'][$i].'"';
				else $href='href="./?np='.$numpage.'#zak'.$i.'"';
				$str.=Maket::divclasstr($clas1,$Pth,'','','li');
				$str.=Maket::spanclasstr($val,$Pth,'button','a '.$href,'','',' part2');
				$str.='</li>';
		}
	$i++;
	}
	$str.='</ul>';
	return $str;	
}	

static function menumain($arr,$Pth,$typelist,$nb,$no=0,$selector='div'){
	$i=0;
	$numpage=$arr['nump'];
	$typesite=$arr['idmen'][0];
	if($no==0)$no=count($arr[$typelist])-1;
	foreach ($arr[$typelist] as $val){
		if ($val=='') $ed='addnew';
		if ($i>=$nb && $i<($nb+$no) && isset($arr[$typelist][$i]) && $val <> '') {
				if ($typesite <> 'land') $href='href="./?np='.$arr[$typelist.'href'][$i].'"';
				else $href='href="./?np='.$numpage.'#zak'.$i.'"';
				echo Maket::spanclasstr($val,$Pth,'button','a '.$href,'','',' part2');
			//echo '</div>';
		}
		elseif($val <> '') { 
			echo '<a '.$href.' class="button '.$arr['clas'][$i].'">'.$val.'</a>'; 	
		}
	$ed='edit';
	$i++;
	}
	return $no;	
}	

static function headersh($arr,$Pth,$typelist,$clas,$nb,$no=0){
$numpage=$arr['nump'];	
//Задаем стили		
$arr['clas']=array('','',$clas['clas'][5]);
//print_r($arr);
//Подготовка режима редактирования
if(isset($arr['link']))$a_link=$arr['link'];
else $a_link = '';
unset($arr['link']);
//print_r($arr); 
if ($Pth['type_access']==='local' && isset($a_link['namep'][0])) echo $a_link['namep'][0]; 	
//формируем фон background	
	$img=$clas['img'].$arr['namep'][0];
	
	Maket::divclass('main-header-'.$arr['idmen'][0],$Pth,'background-image: url('.$img.');',' grid','header');
	Maket::divclass('header-content-'.$arr['idmen'][0],$Pth,'',' grid');
	
//Выводим заголовок	

if ($arr['typmen'][4] <> 'hd'){
	
	if (isset($a_link['namep'])){
		Maket::spanclass('<h1>'.$a_link['namep'][2].'</h1>',$Pth,'zag-land');
	}
	
}
if($a_link==='')Maket::spanclass('<h1>'.$arr['namep'][2].'</h1>',$Pth,'zag-land');
//выводим кнопочное меню	
if ($arr['typmen'][3] <> 'bt'){
	Maket::divclass('header-button',$Pth);
	 show::menumain($arr,$Pth,$typelist,$nb,$no);
	echo '</div>';
}
	echo '</div></header>';
	}

static function sectionsh($typelist,$arr,$Pth,$typelist1='imgt',$ns=0){
$clas=$arr['clas'];
//print_r($arr);
//print_r($arr['imgs']);
$a_img=show::cleanmasspic($clas,$arr,$typelist,$typelist1);
//show::infosh($arr[$typelist1]);
//print_r($a_img);
$numpage=$arr['nump'];
if ($arr['idmen'][0] <> 'land') $buthref=$arr[$typelist1.'href'][$ns];
else $buthref=$numpage.'#zak1';
$butname=$arr[$typelist][$ns];
if ($a_img){
	
	$a_link=$arr['link'];	
	$a_imgs=$a_img[0];
	$a_text=$a_img[1];
	//print_r($a_text);
	$nim=count($a_imgs)-1;
	if ($nim>9) $nim=9;
	if($ns<=0)$ns=1;
	switch ($nim){
	case 9 : {$ngr=4;break;}
	case 8 : {$ngr=4;break;}	
	case 7 : {$ngr=4;break;}
	case 6 : {$ngr=3;break;}
	case 5 : {$ngr=3;break;}
	case 4 : {$ngr=4;break;}
	case 3 : {$ngr=3;break;}
	case 2 : {$ngr=4;break;}
	case 1 : {$ngr=2;break;}
	}
	$levelgrid=1;
	if ($levelgrid == 0) $levelgrid='';
	Maket::divclass($clas['clas'][6].'-section'.$ngr,$Pth,'',' grid','section');
	//echo '<section class="'.$clas['clas'][6].'-section'.$ngr.' grid">';
	$i=1;
	//$butt=$a_text[0];
	if (strlen($butname)<10 && $nim>4) $ncol=3;
		elseif (strlen($butname)<30 && $nim>4) $ncol=2;
		else $ncol=1;
	if ($nim>$ncol)$nbutt=$nim-$ncol;
		else $nbutt=$ngr;
	//print_r($arr['imgt']);	
	//$i=$ns;	
	foreach ($a_text as $key=>$val){
	if ($arr[$typelist.'href'][$key] == '' || $key<$ns ) $arr[$typelist.'href'][$key]='';
	if($key<$nim+1 && $key>$ns) {
		if ($arr['idmen'][0] <> 'land') $href[$key]='href="./?np='.$arr[$typelist.'href'][$key].'"';
				else $href[$key]='href="./?np='.$numpage.'#zak'.$key.'"';
		if ($a_link <> '') {
	if ($arr[$typelist][$key]<>'') {
				//echo '<div class="edit">';	
				echo Maket::divclasstr($clas['clas'][6].'-item'.$levelgrid.($nim-$ns),$Pth,'background-image: url('.$a_imgs[$key],' grid').$a_link[$typelist][$key].'<a '.$href[$key].'">'
				.'<span>'.$arr[$typelist][$key].'</span></a>';
			//if($a_link[$typelist.'href'][$i] <> '') 
				echo '<span>'.$a_link[$typelist.'href'][$key].'</span><span>'.$a_link['imgs'][$key].'</span>';
				echo '</div>';
				//echo '</div>';
				}			
			}
				else { 
					if ($arr[$typelist][$key]<>'') echo Maket::divclasstr($clas['clas'][6].'-item'.$levelgrid.($nim-$ns),$Pth,'background-image: url('.$a_imgs[$key].')',' grid').//echo '<div class="'.$clas['clas'][6].'-item'.$levelgrid.($nim-$ns).' grid" style="background-image: url('.$a_imgs[$key].')">
					'<a '.$href[$key].'"><span>'.$arr[$typelist][$key].'</span></a>';
					echo '</div>';
				}
			//$i++;
		}	
	}	
	Maket::divclass('buttoncase'.$ncol.$nbutt,$Pth,'','');
	//echo '<div class="buttoncase'.$ncol.$nbutt.' text-center">';
	if ($a_link <> ''){
		echo '<div class="edit">';	
		echo $a_link[$typelist.'href'][0].'<a href="./?np='.$buthref.'" class="button">'.$butname.'</a>'.$a_link[$typelist][0];
		echo '</div>';
	}	
	elseif($butname<>'') {
	 	echo '<a href="./?np='.$buthref.'" class="button">'.$butname.'</a>';
	}
	
	 	echo '</div></section>';
unset($a_imgs);	
unset($a_text);	
unset($href);
}
}

static function groupsh_elements($arr,$Pth,$nl=0,$ne=1){
	$clas=$arr['clas'];
	$numpage=$arr['nump'];
	$a_link=$arr['link'];
	//print_r($arr['loz']);
	//echo $a_link['loz'][$nl];
	if (isset($a_link['loz'][$nl])){
		echo '<div class="edit">';	
	if (isset($arr['loz'][$nl]) && $nl<$ne)  echo '<span>'.$a_link['loz'][$nl].'</span><h1>'.$arr['loz'][$nl].'</h1>';
	elseif($a_link['loz'][0]) echo '<span>'.$a_link['loz'][0].'</span><h1>'.$arr['loz'][0].'</h1>'; 
	echo '</div>';
	}	
	else echo '<span><h1>'.$arr['loz'][0].'</h1></span>';  
	Maket::divclass('section-'.$clas['clas'][7],$Pth,'',' landing-section','section');
	//echo '<section class="section-'.$clas['clas'][7].' landing-section">';
		Maket::divclass($clas['clas'][1],$Pth,'',' grid');
		//echo '<div class="container grid">';
		//show::infosh($arr['cont']);
		for ($i=$ne;$i<count($arr['imgt']);$i++) {
			if (strlen($arr['imgt'][$i]>20)) $arr['imgt']=substr($arr['imgt'][$i],0,21);
			if ($arr['idmen'][0] <> 'land') $href='href="./?np='.$arr['conthref'][$i].'"';
				else $href='href="./?np='.$numpage.'#zak'.$i.'"';
			if ($arr['cont'][$i] <> ''){
			if ($a_link <> '') {	
			echo '<div class="edit">';
			Maket::divclass($clas['clas'][7].'-left',$Pth);
			//echo '<div class="'.$clas['clas'][7].'-left ">';
				echo '<ul><a  name="zak'.$i.'"><span>'.$a_link['loz'][$i].'<h2>'.$arr['loz'][$i].'</h2><h3>'.$arr['imgt'][$i].'</h3></span>'.$a_link['imgt'][$i].'</a></ul>';
				echo '<ul><span>'.$a_link['conthref'][$i].'</span><span class="text-center"><a '.$href.'>'.$arr['cont'][$i].'</a></span>'.$a_link['cont'][$i].'</ul>';
				echo '</div>';
			Maket::divclass($clas['clas'][7].'-right',$Pth);	
			//echo '<div class="'.$clas['clas'][7].'-right">';
				echo '<span>'.$a_link['imgs'][$i].'</span>';
				echo '<img src="'.$clas['img'].$arr['imgs'][$i].'" alt="Example" class="img-responsive">';
			echo '</div></div>';
			}
			else {
			Maket::divclass($clas['clas'][7].'-left',$Pth);	
			//echo '<div class="'.$clas['clas'][7].'-left">';
				echo '<ul><a '.$href.' name="zak'.$i.'"><h2>'.$arr['loz'][$i].'</h2><h3>'.$arr['imgt'][$i].'</h3></span></a></ul>';
				if (!strstr($arr['cont'][$i],'https')) echo '<ul><span class="text-center"><a '.$href.'>'.$arr['cont'][$i].'</a></span></ul>';
				
				echo '</div>';
			Maket::divclass($clas['clas'][7].'-right',$Pth);	
			//echo '<div class="'.$clas['clas'][7].'-right">';
				if (!strstr($arr['cont'][$i],'https')) echo '<img src="'.$clas['img'].$arr['imgs'][$i].'" alt="Example" class="img-responsive">';
				else {
	echo '<div class="relation video">';
	echo '<div class="relation_ration_16x9"></div>';
		echo '<iframe class="relation_content" src="'.$arr['cont'][$i].'" allow="autoplay; encrypted-media" allowfullscreen></iframe>';
	echo '</div>';
	}	
			echo '</div>';	
		}
		
}
		}
		echo '</div>';
	echo '</section>';			
}	

static function formoneshowstr($arr){
			//for ($i=$nbegin;$i<($nbegin+$nform+3);$i++){
			$i=0;
			$res='';
			if(is_array($arr['name'])){
			foreach($arr['name'] as $val){	
				echo '<div class="'.$arr['cls'].'">';
				if ($arr['type'][$i]<>'textarea' && $arr['type'][$i]<>'hidden' ) $res.='<div><input type="'.$arr['type'][$i].'" name="'.$val.'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
				elseif($arr['type'][$i]== 'hidden') $res.='<div style="display:none;"><input type="'.$val.'" name="'.$arr['name'][$i].'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
				else $res.='<div><textarea placeholder="'.$arr['place'][$i].'" name="'.$val.'" ></textarea></div>';
			$i++;
			echo '</div>';
			}
			}
			elseif($arr['name']<>'') {
				echo '<div class="'.$arr['cls'].'">';
				if ($arr['type'][$i]<>'textarea' && $arr['type'][$i]<>'hidden' ) $res.='<div><input type="'.$arr['type'][$i].'" name="'.$arr['name'].'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
				elseif($arr['type'][$i]== 'hidden') $res.='<div style="display:none;"><input type="'.$arr['name'].'" name="'.$arr['name'][$i].'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
				else $res.='<div><textarea placeholder="'.$arr['place'][$i].'" name="'.$arr['name'].'" ></textarea></div>';
				echo '</div>';
			}
	return $res;
}

static function formoneshow($arr){
			//for ($i=$nbegin;$i<($nbegin+$nform+3);$i++){
			$i=0;
			if(is_array($arr['name'])){
			foreach($arr['name'] as $val){	
			if($arr['type'][$i]<>'select' && $arr['type'][$i]<>'check'){
				echo '<div class="'.$arr['cls'][$i].'">';
				if ($arr['type'][$i]<>'textarea' && $arr['type'][$i]<>'hidden' ) echo '<input id="'.$arr['id'][$i].'" type="'.$arr['type'][$i].'" name="'.$val.'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'>';
				elseif($arr['type'][$i]== 'hidden') echo '<div style="display:none;"><input id="'.$arr['id'][$i].'" type="'.$arr['type'][$i].'" name="'.$val.'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
				else echo '<textarea id="'.$arr['id'][$i].'" placeholder="'.$arr['place'][$i].'" name="'.$val.'" ></textarea>';
			$i++;
			echo '</div>';
			}
			}
			}
			elseif($arr['name']<>'') {
				if($arr['type'][$i]<>'select' && $arr['type'][$i]<>'check'){
				echo '<div class="'.$arr['cls'].'">';
				if ($arr['type'][$i]<>'textarea' && $arr['type'][$i]<>'hidden' ) echo '<input id="'.$arr['id'][$i].'"  type="'.$arr['type'][$i].'" name="'.$arr['name'].'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'>';
				elseif($arr['type'][$i]== 'hidden') echo '<div style="display:none;"><input type="'.$arr['type'].'" name="'.$arr['name'][$i].'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
				else echo '<textarea id="'.$arr['id'][$i].'" placeholder="'.$arr['place'][$i].'" name="'.$arr['name'].'" ></textarea>';
				echo '</div>';
				}
			}
}


static function formsh($arr, $name='Записать', $nform=0) {
	$Pth='';
	$arr['type']=array('text','text','text','text','text','text','text','text','text','text');
	$arr['place']=array('You...1','You...2','You...3','You...4','You...5','You...6','You...7','You...8','You...9','You...10');
	$arr['req']=array('required','','','','','required','','','','');
	//$arr=show::formshtab($db,$tab);
	if ($nform == 0) $nform=count($arr['name']);
	$nim=count($arr['type']);
	//echo 'nform='.$nform;
	switch ($nform){
					case 2 :
					{
					$lop=21;
					break;
				}
					case 3 :
					{
					$lop=22;
					break;
				}
					case 4 :
					{
					$lop=36;
					break;
				}
					case 5 :
					{
					$lop=37;
					break;
				}
					case 6 :
					{
					$lop=7;
					break;
				}
					case 7 :
					{
					$lop=6;
					break;
				}
					case 8 :
					{
					$lop=4;
					break;
				}
					case 9 :
					{
					$lop=7;
					break;
				}
					default:
				{
					$lop=4;	
					break;	
				}
		}
		Maket::divclass('formsection'.$lop,$Pth,'','','section');//echo '<section class="formsection'.$lop.'">';
		Maket::divclass('container',$Pth);//echo '<div class="container">';
			echo '<form method="POST" class="grid">';
			
		show::formoneshow($arr);
				switch ($nform){
					case 2 :
					{
					$kl=21;
					break;
				}
					case 3 :
					{
					$kl=22;
					break;
				}
					case 4 :
					{
					$kl=36;
					break;
				}
					case 5 :
					{
					$kl=37;
					break;
				}
				case 6 :
					{
					$kl=37;
					break;
				}
				case 7 :
					{
					$kl=37;
					break;
				}
				case 8 :
					{
					$kl=37;
					break;
				}
				default:
				{
					$kl=37;	
					break;	
				}
			}
			Maket::divclass('buttoncase'.$kl,$Pth,'',' text-center');
			echo '<div>'.Maket::divclasstr('button',$Pth,'','','a').$name.'</a></div></form>';
		echo '</div></section>';
}

static function cleanmasstxt($clas,$arr,$typelist,$typelist1){
	
	//$nl-номер с которого рассматриваем входной массив
	//$ne-номер с котого записываем в выходной массив
	//if ($clas=='')$clas['img']='';
	
	if(is_array($arr[$typelist])){
	foreach ($arr['buttimg'] as $key=>$value){
		if (isset($arr[$typelist][$key])) $a_img[$key]=$arr['buttimg'][$key];
		//echo $a_img[$i];echo '<br>';
		if(isset($a_img[$key]) && isset($arr[$typelist][$key]) && $value<>'') {
			$return_txt[0][$key]=$clas['img'].$a_img[$key];
			//echo $a_imgs[$j];echo '<br>';
			$return_txt[1][$key]=$arr[$typelist1][$key];
			}	
	}
	return $return_txt;
	}
	else return false;
}

static function cleanmasspic($clas,$arr,$typelist,$typelist1){
	
	//$nl-номер с которого рассматриваем входной массив
	//$ne-номер с котого записываем в выходной массив
	if ($clas=='')$clas=array('img'=>'');
	if(is_array($arr['imgs'])){
	
	foreach ($arr[$typelist] as $key=>$value){
		if (isset($arr['imgs'][$key])) $a_img[$key]=$arr['imgs'][$key];
		//echo $a_img[$key];echo '<br>';
		if(isset($a_img[$key]) && isset($value[$key]) && $value<>'') {
			$return_img[0][$key]=$clas['img'].$a_img[$key];
			//echo $return_img[0][$key];echo '<br>';
			$return_img[1][$key]=$arr[$typelist1][$key];
			//echo $return_img[1][$key];echo '<br>';
			}	
	}
	//print_r($return_img);
	return $return_img;
	}
	else return false;
}

static function blogsh($arr,$Pth,$typelist,$typelist1,$nl=1,$ne=0){//заголовки, тексты
	//$i=0;$j=0;
	$clas=$arr['clas'];
	$numpage=$arr['nump'];
	//print_r($a_link);
$a_img=show::cleanmasstxt($clas,$arr,$typelist,$typelist1);
if($a_img) {
	$a_link=$arr['link'];
	$a_imgs=$a_img[0];
	$a_text=$a_img[1];
	//print_r($a_imgs);echo '<br>';
	//print_r($a_text);
	$i=0;
	if ($ne==0 || $ne < $nl) $ne=count($arr[$typelist1]);
	//else $ne=$ne+1;
	$nim=count($a_imgs)-1;
	//echo 'nim '.($ne-$nl).'<br>';
	switch ($ne-$nl){
	case 10 : {$ngr=3;break;}
	case 9 : {$ngr=4;break;}
	case 8 : {$ngr=4;break;}	
	case 7 : {$ngr=4;break;}
	case 6 : {$ngr=3;break;}
	case 5 : {$ngr=4;break;}
	case 4 : {$ngr=3;break;}
	case 3 : {$ngr=2;break;}
	case 2 : {$ngr=2;break;}
	case 1 : {$ngr=2;break;}
	}
	$levelgrid=0;
	if ($levelgrid == 0) $levelgrid='';
	//echo 'ngr '.$ngr;echo '<br>';
	//echo 'ne '.$ne;echo '<br>';
	//echo 'nl '.$nl;
	//print_r($arr['loz']);
	//echo '<br>----'.$arr['loz'][$nl];
	$st=$ne-$nl-1;
	//echo 'st '.$st;echo '<br>';
	Maket::divclass('landing-section',$Pth,'',' section-blog','section');//echo '<section class="landing-section section-blog">';
	Maket::divclass('container',$Pth);//echo '<div class="container">';
	if ($a_link <> '') echo '<ul>'.$a_link['loz'][$nl].'<h2>'.$arr['loz'][$nl].'</h2></ul>';
	else echo '<h2>'.$arr['loz'][$nl].'</h2>';
	Maket::divclass('blog-'.$clas['clas'][11].$levelgrid.$ngr,$Pth,'',' grid');//echo '<div class="blog-'.$clas['clas'][11].$levelgrid.$ngr.' grid">';
	foreach ($arr[$typelist1] as $key=>$val){
		if ($val <> '' && $key < $ne && $key > $nl && $arr[$typelist][$i]<>''){
			if ($a_link <> '') { 
				echo '<div class="edit">';
				if ($arr['idmen']<> 'land') echo '<ul><a href="./?np='.$arr[$typelist.'href'][$i].'" class="blog-item'.$nim.' grid">';
				else echo '<ul><a href="./#zak'.$i.'" class="blog-item'.$nim.' grid">';
				echo Maket::divclasstr('blog-'.$clas['clas'][12].$levelgrid.$st.'-'.$clas['clas'][13],$Pth,'background-image: url('.$a_imgs[$i].')','','span').'</span>';//
				//echo '<span class="blog-'.$clas['clas'][12].$levelgrid.$st.'-'.$clas['clas'][13].'" style="background-image: url('.$a_imgs[$i].')"></span>';	
				Maket::divclass('blog-'.$clas['clas'][12].$levelgrid.$st.'-'.$clas['clas'][14],$Pth,'',' grid');//
				//echo '<span class="blog-'.$clas['clas'][12].$levelgrid.$st.'-content grid">';
	 			echo $a_link[$typelist][$i].'<h4>'.$arr[$typelist][$i].'</h4>';
				//echo '<h4>'.$val.'</h4>';
	 				echo '<p>'.$a_text[$i].$a_link[$typelist1][$i].'</p>';
	 				//echo '</span>';
				echo $a_link['imgs'][$i].'</ul>';
				echo '</a>'.$a_link[$typelist.'href'][$i];
				echo '</div>';
			}
	 		else {
				echo '<a href="./?np='.$arr[$typelist.'href'][$i].'#zak'.$i.'" class="blog-'.$clas['clas'][12].$ngr.' grid">';
	 			//echo '<span class="blog-item'.$levelgrid.$st.'-img" style="background-image: url('.$a_imgs[$i].')"></span>';
	 			echo Maket::divclasstr('blog-'.$clas['clas'][12].$levelgrid.$st.'-'.$clas['clas'][13],$Pth,'background-image: url('.$a_imgs[$i].')','','span').'</span>';
				Maket::divclass('blog-'.$clas['clas'][12].$levelgrid.$st.'-'.$clas['clas'][14],$Pth,'',' grid','span');
				//echo '<span class="blog-'.$clas['clas'][12].$levelgrid.$st.'-content grid">';
				echo '<h4>'.$arr[$typelist][$i].'</h4>';
	 			//echo '<h4>'.$val.'</h4>';
	 					
						if (!strstr($a_text[$i],'https')) echo '<p>'.$a_text[$i].'</p>';
				else {
					Maket::divclass('blog-'.$clas['clas'][12].$levelgrid.$st.'-'.$clas['clas'][13],$Pth);
					Maket::divclass('relation video',$Pth);//'<div class="relation video">';
					Maket::divclass('relation_ration_16x9',$Pth);//echo '<div class="relation_ration_16x9"></div>';
					Maket::divclass('relation_content',$Pth,'','','iframe');//echo '<iframe class="relation_content" src="'.$a_text[$i].'" allow="autoplay; encrypted-media" allowfullscreen>
					echo '</iframe>';
					echo '</div></span>';
			}	
	 				echo '</span>';
				echo '</a>';
			}
		}
				$i++;
	}
	Maket::divclass('buttoncase'.$levelgrid.$ngr,$Pth,'',' text-center');
	//echo '<div class="buttoncase34 text-center">';
	if ($arr[$typelist][0]<> '')	{
		if ($arr['idmen'][0] <> 'land') $buthref='?np='.$arr[$typelist1.'href'][$ns];
		else $buthref=$numpage.'#zak1';
	if ($a_link <> '') {
		//print_r($arr['loz']);
	
		echo $a_link[$typelist][$nl].'<a href="./'.$buthref.' class="button">'.$arr[$typelist][$nl].'</a>';
		echo $a_link[$typelist.'href'][$nl];
	}
	else {
		echo '<a href="./'.$buthref.'" class="button">'.$arr[$typelist][$nl].'</a>';
		
	}
	}
	else {
		if ($arr['idmen'][0] <> 'land') $buthref='?np='.$arr[$typelist1.'href'][$ns];
		else $buthref=$numpage.'#zak1';
		if ($a_link <> '') {
		//print_r($arr['loz']);
		echo $a_link[$typelist1][$nl].'<a href="./?'.$buthref.'" class="button">'.$arr[$typelist1][$nl].'</a>';
		echo $a_link[$typelist1.'href'][$nl];
	}
	else {
		echo '<a href="./?'.$buthref.'" class="button">'.$arr[$typelist1][$nl].'</a>';
		
	}
		
	}
		echo '</div></div></div></section>';
}	
else $ne=0;	
return $ne;
}


static function accordshstr($typelist,$arr,$Pth,$typelist1='imgt',$ns=0,$n=0){
$str='';	
$str.='<link rel="stylesheet" type="text/css" href="./images/accordion.css" /><link rel="stylesheet" type="text/css" href="./images/ddsmoothmenu.css" /><script type="text/javascript" src="./scripts/jquery.min.js"></script>
<script type="text/javascript" src="./scripts/ddsmoothmenu.js"></script>
<script type="text/javascript">
ddsmoothmenu.init({
	mainmenuid: "templatemo_menu", 
	orientation: "h", 
	classname: "ddsmoothmenu", 
	contentsource: "markup" 
})
</script><script type="text/javascript" src="./scripts/jquery-1.3.2.min.js"></script><script type="text/javascript" src="./scripts/jquery.easing.1.3.js"></script><script type="text/javascript" src="./scripts/jquery.kwicks-1.5.1.pack.js"></script>';

$str.="<script type='text/javascript'>$().ready(function() {
		$('.slider').kwicks({
			max : 740,
			spacing : 1
		});
	});</script>";
$clas=$arr['clas'];
$a_img=show::cleanmasspic($clas,$arr,$typelist,$typelist1);
//print_r($a_img);
$numpage=$arr['nump'];
if ($arr['idmen'][0] <> 'land') $buthref=$arr[$typelist1.'href'][$ns];
else $buthref=$numpage.'#zak1';
$butname=$arr[$typelist1][$ns];
if ($a_img){
$a_link=$arr['link'];	
//show::infosh($a_link);

$a_imgs=$a_img[0];
$a_text=$a_img[1];
//show::infosh($a_text);
$nim=count($a_imgs);
//if ($nim>9) {$nim=count($a_imgs);$width_acc=98;}
//else $width_acc=198+(count($a_imgs)-$nim)*10;

	$str.='<div id="gallary_accordion" class="accordion">';
	//Maket::divclass('#templatemo_main_wrapper',$Pth);
	//Maket::divclass('#templatemo_slider_wrapper',$Pth);
	$str.='<div id="templatemo_main_wrapper">';
	$str.='<div id="templatemo_slider_wrapper">';
	$str.='<ul class="slider horizontal" >
            <li id="slide_1"><img src="images/1.jpg" alt="Slider 01" /></li>
            <li id="slide_2"><img src="images/2.jpg" alt="Slider 02" /></li>
            <li id="slide_3"><img src="images/3.jpg" alt="Slider 03" /></li>
            <li id="slide_4"><img src="images/4.jpg" alt="Slider 04" /></li>
            <li id="slide_5"><img src="images/5.jpg" alt="Slider 05" /></li>
        </ul>';
	
	$str.='</ul></div></div></div>';

}
return $str;
}	

static function slideSwipstr($Pth,$contSw,$pagn="Y",$swbut="Y", $nsl=1,$spbetw=10,$spg=1,$pagn_type="fraction",$loop=true){
	$str='<style>
		.swiper-container {
		  
		}
		.swiper-slide {
		  text-align: center;
		  font-size: $normFS;
		  background: white;
		  display: -webkit-box;
		  display: -ms-flexbox;
		  display: -webkit-flex;
		  display: flex;
		  -webkit-box-pack: center;
		  -ms-flex-pack: center;
		  -webkit-justify-content: center;
		  justify-content: center;
		  -webkit-box-align: center;
		  -ms-flex-align: center;
		  -webkit-align-items: center;
		  align-items: center;
	}
	</style>';
	$str.='<div class="swiper-container">';
	$str.='<div class="swiper-wrapper">';
	foreach($contSw as $k=>$val){
		$str.='<div class="swiper-slide">';
		$str.=$val;
		$str.='</div>';//swiper-slide
	}
			
	$str.= '</div>';//swiper-wrapper
	// Add Pagination -->
    if ($pagn <> '') $str.='<div class="swiper-pagination"></div>';
    //Add Arrows -->
    if ($swbut <> '' ) {
		$str.='<div class="swiper-button-next"></div>';
		$str.='<div class="swiper-button-prev"></div>';
	}
	$str.='</div>';//swiper-container
	//<!-- Swiper JS -->
  $str.='<script src="./scripts/swiper.min.js"></script>';
	//<!-- Initialize Swiper -->
  $str.="<script>
    var swiper = new Swiper('.swiper-container', {
	  fadeEffect: {
    crossFade: true
  },	
  autoplay: {
    delay: 5000,
  },
      slidesPerView: $nsl,
      spaceBetween: $spbetw,
      slidesPerGroup: $spg,
      loop: $loop,
      loopFillGroupWithBlank: $loop,
	  direction: 'vertical',
      pagination: {
        el: '.swiper-pagination',
        clickable: true,
		type: '$pagn_type',
      },
      navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
      },
    });
  </script>";
  return $str;
  
}

static function slidesh($Pth,$arr,$clas='',$key=0,$pagn="Y",$swbut="Y", $nsl=1,$spbetw=10,$spg=1,$pagn_type="fraction",$loop=true){

echo '<style>
.swiper-container {
  width: 100%;
  height: 100%;
}
.swiper-slide {
  text-align: center;
  font-size: $normFS;
  background: white;
  display: -webkit-box;
  display: -ms-flexbox;
  display: -webkit-flex;
  display: flex;
  -webkit-box-pack: center;
  -ms-flex-pack: center;
  -webkit-justify-content: center;
  justify-content: center;
  -webkit-box-align: center;
  -ms-flex-align: center;
  -webkit-align-items: center;
  align-items: center;
}
</style>';
echo '<div class="swiper-container">';
echo '<div class="swiper-wrapper">';
		for ($i=1;$i<6;$i++){	
			echo '<div class="swiper-slide">';
			if($key==0)show::viewSlide($Pth,$arr,$i);
			else show::viewSlide($Pth,$arr,1,0);
			echo '</div>';//swiper-slide
			
	}
	echo '</div>';//swiper-wrapper
	// Add Pagination -->
    if ($pagn <> '') echo '<div class="swiper-pagination"></div>';
    //Add Arrows -->
    if ($swbut <> '' ) {
		echo '<div class="swiper-button-next"></div>';
		echo '<div class="swiper-button-prev"></div>';
	}
	echo '</div>';//swiper-container
	//<!-- Swiper JS -->
  echo  '<script src="./scripts/swiper.min.js"></script>';
	//<!-- Initialize Swiper -->
  echo "<script>
    var swiper = new Swiper('.swiper-container', {
	  cubeEffect: {
    slideShadows: true,
  },	
  autoplay: {
    delay: 5000,
  },
      slidesPerView: $nsl,
	 direction: 'vertical',
      spaceBetween: $spbetw,
      slidesPerGroup: $spg,
      loop: $loop,
      loopFillGroupWithBlank: $loop,
      pagination: {
        el: '.swiper-pagination',
        clickable: true,
	   type: '$pagn_type',
      },
      navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
      },
    });
  </script>";
}


static function viewSlide($Pth,$arr,$i,$key=0,$typelist='imgs',$typelist1='imgt') {
	//show::infosh($arr[$typelist1.'href']);
	if ($arr['link']<>''){
		$a_link1=$arr['link'][$typelist1][$key];
		$a_link2=$arr['link'][$typelist1.'href'][$key];
		$a_link3=$arr['link'][$typelist][$key];
	}
	else {
		$a_link1='';
		$a_link2='';
		$a_link3='';
	}
	if ($arr['idmen'][0] <> 'land') $href='./?np='.$arr[$typelist1.'href'][$key].'';
		else $href='./#zak'.$key;
	//show::infosh($href);	
	$imgt=$arr[$typelist1][$key];
	$img=$arr['clas']['img'].$arr[$typelist][$key];
	//$soucer_img=imagecreatefromjpeg($img1);
	//$dest_img = imagecreatetruecolor($newwidth, $newheight);
	//imagecopyresized ($dest_img, $soucer_img,0, 0, 0, 0, 300, 300, 200, 200);
	//$img=imagejpeg($dest_img);
	switch ($i){
		case 0 :
		{
		echo show::showlogo('items part-card',$arr,$Pth,2,$key,'cont','cont',351);
		break;	
		}
		case 1 :
		{
		if($a_link1<>'' && $a_link2 <> '')	{
		if ($imgt)echo '<div class="float_l">'.$a_link1.'<a href="'.$href.'">'.$imgt.'</a>'.$a_link2.'</div>';	
		echo $a_link3.'<div class="photo" style="background-size:cover"><a href="'.$href.'">
		<img  class="img-responsive" src="'.$img.'"/></div></a>';
		}
		else {
			if ($imgt)echo '<div class="float_l"><a href="'.$href.'">'.$imgt.'</a></div>';	
			echo '<div class="photo" style="background-size:cover"><a href="'.$href.'">
		<img  src="'.$img.'"/></a></div>';
		}
		break;	
		}
		case 2 :
		{
		show::formsh($arr, 'Yes! Ready!',6);
		break;	
		}
		case 3 :
		{
		$nblog=5;
		$next=show::blogsh($clas,$arr,'imgt','cont',0,$nblog+1);
		break;	
		}
		case 4 :
		{
		show::headersh($arr,'butt',$clas,0,5);
		break;	
		}
		case 5 :
		{
		show::sectionsh('imgt',$clas,$arr);
		break;	
		}
}
}
private static function hidenelement($input_block,$i,$opbeg1,$opend1,$opbeg2,$opend2,$trans) {
	// Создаем правило изменения прозрачности: задаем имя правила, начальную и конечную прозрачность, а также необязательный параметр задержки влияющий на скорость смены прозрачности	
	echo '<script type="text/javascript" src="./scripts/opacity.js"></script>';
	echo "<script type='text/javascript'>
		fadeOpacity.addRule('oR1', $opbeg1, $opend1, $trans);
		fadeOpacity.addRule('oR2', $opbeg2, $opend2, $trans);
		</script>";
	echo '<div id="fImg1'.$i.'" class="button" onmouseover="fadeOpacity(this.id, `oR1`)" onmouseout="fadeOpacity.back(this.id)" src="'.$val.'" alt="" >';	
		$input_block;
	echo '</div>';
}

static function shadowsh($arr,$Pth,$t,$l,$apm){
$clas=$arr['clas'];
$typelist=$t;
$typelist1=$l;
if($typelist1=='') $typelist1=$typelist;
$nhigh=9;
if(isset($Pth['main-header'.$nhigh]['numpar']['Grid'])) $grid=$Pth['main-header'.$nhigh]['numpar']['Grid'];
//if(isset($arr['link']))$a_link=show::a_link($arrmain);
//if(isset($arr['link']['imgs']))unset($arr['link']['imgs']);
//if(isset($arr['link']['buttimg']))unset($arr['link']['buttimg']);

$opbeg1=$apm[1];
$opend1=$apm[2];
$opbeg2=$apm[3];
$opend2=$apm[4];
$trans=$apm[5];
$nhigh=$apm[6];
echo '<script type="text/javascript" src="./scripts/opacity.js"></script>';
echo "<script type='text/javascript'>
		fadeOpacity.addRule('oR1', $opbeg1, $opend1, $trans);
		fadeOpacity.addRule('oR2', $opbeg2, $opend2, $trans);
		</script>";
	
if(count($arr['buttimg'])>2) {
	//echo '---------imgt<br>';
	$a_img=show::cleanmasstxt($clas,$arr,$typelist,$typelist1);
	//print_r($a_img);
	}
elseif(count($arr['imgs'])>1) {
	//echo '---------imgs';
	$a_img=show::cleanmasspic($clas,$arr,$typelist,$typelist1);
	//print_r($a_img);
	}
else {
	//print_r($arr['typelist']);
	foreach ($arr[$typelist] as $val) {
		if($val)$a_img[0][]='';
		if($val)$a_img[1][]=$val;
	}
}
//echo 'shadowsh';
//print_r($a_img);
if ($a_img) {
	$a_imgs=$a_img[0];
	$a_text=$a_img[1];
foreach ($a_text as $key=>$val) if(strstr($val,'=')) $a_text[$key]=Page::part_name($val);		
//формируем фон background	
	$img0=$clas['img'].$arr['imgs'][0];	
//if ($a_link <> '') echo $a_link['imgs'][0]; 	
	Maket::divclass('main-header'.$nhigh,$Pth,'background-image: url('.$img0.');','','header');
	//echo '<header class="main-header9 grid" style="background-image: url('.$img0.');" >';		
//echo '<div style="position: relative; top: 0px; left: 0px;">';
	
	echo '<div class="header-content-cont">';
	//print_r($a_text);
	if (count($a_text) > 7) $nim=2;
	else $nim=0;
	echo '<div class="header-button grid option'.$nim.'">';
	foreach ($a_text as $key=>$val){
	if ($val <> '' && $key > $nim) {
		echo '<div id="fImg1'.$key.'" class="button" onmouseover="fadeOpacity(this.id, `oR1`)" onmouseout="fadeOpacity.back(this.id)" style="background-image:url('.$a_imgs[$key].');" alt="" >';
		echo '<a href="./?np='.$arr[$typelist1.'href'][$key].'" >'.$val.'</a>'; 	
	echo '</div>';
	
	}
	}
	echo '</div>';
	echo '</div>';
	//
	echo '</header>';
	}	
}

static function simple_adap_menu($arr='',$typelist,$Pth,$nimg=0,$extarr1='',$extarr2=''){
if($typelist=='') {
	$typelist='empty';
}
if (is_array($arr)){
$a_link=$arr['link'];
//Page::scalimag3($arr,'./images/logo.png','./?np='.$arr['nump'],$Pth,1);
}
else {
	$arr=array();
	$a_link='';
	if(isset($extarr1['link']))unset($extarr1['link']);
	if(isset($extarr2['link']))unset($extarr2['link']);
	if($extarr1<>''){
		foreach($extarr1 as $key=>$val) {
			if($val<>'')$arr['empty'][$key+1]=$val;
		}
	}
	else {
		$arr['empty'][0]="Меню";
		$arr['empty'][1]="Гостевой вход";
		$arr['empty'][2]="Регистрация";
		$arr['empty'][3]="Забыли пароль";
		$arr['empty'][4]="На главную";
	}
	if($extarr2<>''){
		foreach($extarr2 as $key=>$val) {
			if($extarr1[$key]<>'')$arr['emptyhref'][$key+1]=$val;
		}
	}
	else {
		$arr['emptyhref'][1]="/auth/?guest";
		$arr['emptyhref'][2]="/registration/";
		$arr['emptyhref'][3]="/recovery/";
		$arr['emptyhref'][4]="/";
	}
}
$arr['empty'][0]="Меню";
$arr['emptyhref'][0]='';
//print_r($arr);

//$a_img=show::cleanmass(0,0,$clas,$arr,$typelist,$typelist);
//$a_imgs=$a_img[0];
//$a_text=$a_img[1];
//print_r($a_text);
	echo '<nav>';
		echo '<div class="wrapper_simple">';
		if ($a_link <> '' && $typelist<>'empty'){
		$ed='editor';	
		echo '<label class="menu_simpleToggle" for="menu_simpleCheck">'.$arr[$typelist][$nimg].' '.$a_link[$typelist][$nimg].'</label>';
		echo '<input id="menu_simpleCheck" type="checkbox">';
		echo '<ul class="menu_simple clearfix">';	
if(is_array($arr[$typelist]))	{	
	foreach ($arr[$typelist] as $key=>$val){
	if ($val=='') $ed='addnew';
	if ($key > $nimg){
		echo '<li class="'.$ed.'"><a href="./?np='.$arr[$typelist.'href'][$key].'">'.$val.'</a>'.$a_link[$typelist][$key].'-'.$a_link[$typelist.'href'][$key].'</li>';
		}				
		$ed='editor';
		}
		}
else {
	$key=0;
	if ($arr[$typelist][$key]=='') $ed='addnew';
	echo '<li class="'.$ed.'"><a href="./?np='.$arr[$typelist.'href'][$key].'">'.$arr[$typelist][$key].'</a>'.$a_link[$typelist][$key].'-'.$a_link[$typelist.'href'][$key].'</li>';
	$ed='editor';
}		
}
		else {
		echo '<label class="menu_simpleToggle" for="menu_simpleCheck">'.$arr[$typelist][$nimg].'</label>';	
		echo '<input id="menu_simpleCheck" type="checkbox">';	
	echo '<ul class="menu_simple clearfix">';
if(is_array($arr[$typelist]))	{	
	foreach ($arr[$typelist] as $key=>$val){	
		if ($key > $nimg){
			if ($typelist<>'empty') echo '<li><a href="./?np='.$arr[$typelist.'href'][$key].'">'.$val.'</a></li>';
			else echo '<li><a href="'.$arr[$typelist.'href'][$key].'">'.$val.'</a></li>'; 
		}
	}
	}
else {
	$key=0;
	if ($typelist<>'empty') echo '<li><a href="./?np='.$arr[$typelist.'href'][$key].'">'.$arr[$typelist][$key].'</a></li>';
	else echo '<li><a href="'.$arr[$typelist.'href'][$key].'">'.$arr[$typelist][$key].'</a></li>'; 
	}	
}
echo '</ul></div></nav>';
echo '<script type="text/javascript" src="./scripts/new.js">';

}

static function menush($arr,$Pth,$typelist){
$tabl=$arr['tab'];	
$numpage=$arr['nump'];	
//echo 'numpage is = '.$numpage;
$Menu=(object)array();
$Menu->list1=$arr[$typelist];
$Menu->list2=$arr[$typelist.'href'];

if(isset($arr['link']))$a_link=$arr['link'];
else $a_link='';
//print_r($a_link);
unset($Menu->list1['link']);
unset($Menu->list2['link']);
$nopt=count($Menu->list2);
//print_r($Menu->list2);echo '<br>';
//echo 'nopt is = '.$nopt;echo '<br>';
//$typelist1='buttons';

$i=0;
//print_r($Menu->list2);
foreach($Menu->list2 as $val) if ($val<>'') $i++;
if ($i<8) $nopt=$i-1;
else $nopt=6;
if ($nopt < 4) $just='SB';
if ($nopt < 6) $just='C';
if ($nopt > 5) $just='SA';
if (isset($tabl['pages'])) $Menu->tabl=$tabl['pages'];
$Menu->list3=Elementsw::viewlistnew($Menu->list2,'buttons',$tabl);
//print_r($Menu->list3);
for ($j=0; $j<count($Menu->list3);$j++) $Menu->linkp[$j]=explode('|',$Menu->list3[$j]);
//print_r($Menu->linkp);
for ($i=0;$i<$nopt;$i++) $Menu->lp[$i]=explode(';',$Menu->linkp[$i][1]);
if($arr['idmen'][0]<> 'land') Maket::divclass('main-header9',$Pth,'','','header');
Maket::divclass('menudown'.$just,$Pth);//echo '<div class="menudown'.$just.'">';	
if ($Menu->list2[0]=='') {
	//echo '---------------------';
	for ($i=0;$i<count($Menu->list1); $i++) {
	$Menu->list2[$i]='#';
	Maket::divclass('menudown'.$just,$Pth,'','','li');//echo '<li class="menudown'.$just.'">'.$Menu->list1[$i].'</li>';
	}
}
else {
	$bott='yes';
	for ($i=0; $i<$nopt; $i++){
	if ($Menu->list2[$i]) $pagelist= new Page($Menu->list2[$i],$tabl);
	if ($Menu->list1[$i] == '' && $bott == 'yes') {
	$Menu->list1[$i]=$pagelist->getnamepage($pagelist);
	}
	else $bott='no';	
	if ($pagelist->MainAr['numpage'] == $numpage) $Menu->list2[$i]="";
	else $Menu->list2[$i]=$pagelist->MainAr['hrefp'].'?np='.$pagelist->MainAr['numpage']; 
	if ($Menu->list1[$i]) {
		$Menu->list1[$i]=$pagelist->part_name($Menu->list1[$i]);
		if (isset($a_link[$typelist][$i])) echo '<ul>'.Maket::divclasstr('menudown'.$just.'-item',$Pth,'','','li').'<a href="'.$Menu->list2[$i].'">'.$a_link[$typelist][$i].$Menu->list1[$i].$a_link[$typelist.'href'][$i].'</a>';
		else echo '<ul>'.Maket::divclasstr('menudown'.$just.'-item',$Pth,'','','li').'<a href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a>'; 
		Maket::divclass('menulevel',$Pth,'','','ul');//echo '<ul class="menulevel">';
	$k=0;
	//print_r($Menu->lp[$i]);
	$NP=count($Menu->lp[$i]);
	//echo $NP;
	//for ($k=0; $k<$NP; $k++) {
	foreach ($Menu->lp[$i] as $k=>$val1){
		if ($Menu->lp[$i][$k]) {
			$pagelist= new Page($Menu->lp[$i][$k],$tabl);
			$nmp=$pagelist->getnamepage($pagelist);
			$nu=array_keys($nmp);
			$option_menu=$pagelist->part_name($nmp[$nu[0]]);
			
		$Menu->lp[$i][$k]=$pagelist->MainAr['hrefp'].'?np='.$pagelist->MainAr['numpage'];
		if ($NP>1) echo '<a href="'.$Menu->lp[$i][$k].'">'.$option_menu.'</a>';
		else	{
			echo '<a href="'.$Menu->lp[$i][$k].'">'.$option_menu.'</a>';
			}
		}	
			
		}
	}
	echo '</ul></li></ul>';
	}
}
echo '</div>';
 
if($arr['idmen'][0]<> 'land') echo '</header>';
}

static function menushstr($arr,$Pth,$typelist){
$tabl=$arr['tab'];	
$numpage=$arr['nump'];	
//echo 'numpage is = '.$numpage;
$Menu=(object)array();
$Menu->list1=$arr[$typelist];
$Menu->list2=$arr[$typelist.'href'];
$str='';
if(isset($arr['link']))$a_link=$arr['link'];
else $a_link='';
//print_r($a_link);
unset($Menu->list1['link']);
unset($Menu->list2['link']);
$nopt=count($Menu->list2);
//print_r($Menu->list2);echo '<br>';
//echo 'nopt is = '.$nopt;echo '<br>';
//$typelist1='buttons';

$i=0;
//print_r($Menu->list2);
foreach($Menu->list2 as $val) if ($val<>'') $i++;
if ($i<8) $nopt=$i-1;
else $nopt=6;
if ($nopt < 4) $just='SB';
if ($nopt < 6) $just='C';
if ($nopt > 5) $just='SA';
if (isset($tabl['pages'])) $Menu->tabl=$tabl['pages'];
$Menu->list3=Elementsw::viewlistnew($Menu->list2,'buttons',$tabl);
if(!$Menu->list3) return null;
//print_r($Menu->list3);
for ($j=0; $j<count($Menu->list3);$j++) $Menu->linkp[$j]=explode('|',$Menu->list3[$j]['buttons']);
//print_r($Menu->linkp);
foreach($Menu->linkp as $k=>$val) $Menu->lp[$k]=explode(';',$val[0]);
//for ($i=0;$i<$nopt;$i++) $Menu->lp[$i]=explode(';',$Menu->linkp[$i]['namep']);
if($arr['idmen'][0]<> 'land') $str.=Maket::divclasstr('main-header9',$Pth,'','','header');
$str.=Maket::divclasstr('menudown'.$just,$Pth);//echo '<div class="menudown'.$just.'">';	
if ($Menu->list2[0]=='') {
	//echo '---------------------';
	for ($i=0;$i<count($Menu->list1); $i++) {
	$Menu->list2[$i]='#';
	$str.=Maket::divclasstr('menudown'.$just,$Pth,'','','li');//echo '<li class="menudown'.$just.'">'.$Menu->list1[$i].'</li>';
	}
}
else {
	$bott='yes';
	for ($i=0; $i<$nopt; $i++){
	if ($Menu->list2[$i]) $pagelist= new Page($Menu->list2[$i],$tabl);
	if ($Menu->list1[$i] == '' && $bott == 'yes') {
	$Menu->list1[$i]=$pagelist->getnamepage($pagelist);
	}
	else $bott='no';	
	if ($pagelist->MainAr['numpage'] == $numpage) $Menu->list2[$i]="";
	else $Menu->list2[$i]=$pagelist->MainAr['hrefp'].'?np='.$pagelist->MainAr['numpage']; 
	if ($Menu->list1[$i]) {
		$Menu->list1[$i]=$pagelist->part_name($Menu->list1[$i]);
		if (isset($a_link[$typelist][$i])) $str.= '<ul>'.Maket::divclasstr('menudown'.$just.'-item',$Pth,'','','li').'<a href="'.$Menu->list2[$i].'">'.$a_link[$typelist][$i].$Menu->list1[$i].$a_link[$typelist.'href'][$i].'</a>';
		else $str.= '<ul>'.Maket::divclasstr('menudown'.$just.'-item',$Pth,'','','li').'<a href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a>'; 
		$str.=Maket::divclasstr('menulevel',$Pth,'','','ul');//echo '<ul class="menulevel">';
	$k=0;
	//print_r($Menu->lp[$i]);
	$NP=count($Menu->lp[$i]);
	//echo $NP;
	//for ($k=0; $k<$NP; $k++) {
	foreach ($Menu->lp[$i] as $k=>$val1){
		if ($Menu->lp[$i][$k]) {
			$pagelist= new Page($Menu->lp[$i][$k],$tabl);
			$nmp=$pagelist->getnamepage($pagelist);
			$nu=array_keys($nmp);
			$option_menu=$pagelist->part_name($nmp[$nu[0]]);
			
		$Menu->lp[$i][$k]=$pagelist->MainAr['hrefp'].'?np='.$pagelist->MainAr['numpage'];
		if ($NP>1) $str.='<a href="'.$Menu->lp[$i][$k].'">'.$option_menu.'</a>';
		else	{
			$str.='<a href="'.$Menu->lp[$i][$k].'">'.$option_menu.'</a>';
			}
		}	
			
		}
	}
	$str.='</ul></li></ul>';
	}
}
$str.='</div>';
 
if($arr['idmen'][0]<> 'land') $str.='</header>';
return $str;
}


static function viewtextvideo($arr,$typelist,$typelist1){
	echo '<section>';
	foreach($arr[$typelist1] as $key=>$val) {
	if (!strstr($val,'https')){	
		if (!is_array($arr[$typelist][$key]) && !is_array($val)){
		echo '<div class="wrapper"><p><h2>'.$arr[$typelist][$key].'</h2></p></div>';
		echo '<section>';
		echo '<p>'.$val.'</p>';
		}
	}
	else {
	echo '<div class="relation video">';
	echo '<div class="relation_ration_16x9"></div>';
		if (!is_array($val)) echo '<iframe class="relation_content" src="'.$val.'" allow="autoplay; encrypted-media" allowfullscreen></iframe>';
	echo '</div>';
	}
	}
	echo '</section>';
}

static function showallmenu($mode_work,$arr,$Pth,$typelist='butt',$typelist1=''){
//$tabl=$arr['tab'];
$clas=$arr['clas'];	
//$a_link=show::a_link($arr);
$just='SA';
if ($arr['butthref']<>'') { //если есть ссылки с кнопок берем из buttons
//echo '<div class="menu">';
$arrparmenu=array($just,0.1,1,1,0.5,100,10);
// Зона MENU
$image=$arr['clas']['img'].$arr['buttimg'][0];
//echo $image;
if ($arr['typmen'][3]<> 'nbt' ){
	
	show::shadowsh($arr,$Pth,$typelist,$typelist1,$arrparmenu);	
	
}
 
elseif($arr['typmen'][2]<> 'nmn') {//если картинок нет и если нет названий кнопок берем название страниц и ссылки из list
			if(!$mode_work && isset($_GET['contentS'])){
				//show::showinputlink($arr,60);
				
				echo 'Блок меню <hr>';//comment
			
			}
			echo '<ul class="menudown'.$just.'">';
			show::menush($arr,$Pth,'butt');
			//show::menubuttarr($arr,$nc,false,'');
			echo '</ul>';
		}
elseif($arr['typmen'][3]== 'nbt') {//если картинки кнопок есть
		echo 'accordion <br>';
		if(!$mode_work && isset($_GET['contentS']))echo 'Блок слайдера/аккордиона<hr>';//comment
		show::accordsh('Y','imgs',$arr,$Pth,'imgt',3);
		
	}
	}
}


static function menubuttarr($arr, $nc,$active=true,$img=''){
$tabl=$arr['tab'];	
$clas=$arr['clas'];	
$list1=$arr['butt'];
$list2=$arr['butthref'];
$list3=$arr['imgs'];
unset($list3['link']);
$a_link=$arr['link'];
if (isset($list1)) $Menu->list1=$list1;
if (isset($list2)) $Menu->list2=$list2;
if ($img=='') $Menu->img=$list3;
elseif (count($img)>1) $Menu->img=$img;
else for ($i=0;$i<count($Menu->list1);$i++) $Menu->img[$i]=$img;
//print_r($Menu->list1);
if ($Menu->list1[0]==""){
for ($i=0; $i<count($Menu->list2); $i++){
	$pagel= new Page($Menu->list2[$i],$tabl);
	$Menu->list1[$i]=$pagel->getnamepage($pagel);
	}	
}
//print_r($Menu->img);
for ($i=0; $i<count($Menu->img); $i++){
	if (isset($img) && isset($Menu->list1[$i]) && isset($Menu->list2[$i])){	
	if ($img=='' ) {
		$Menu->img[$i]=$clas['img'].$Menu->img[$i];
	}
	$page= new Page($Menu->list2[$i],$tabl);
	$Menu->list2[$i]='?np='.$page->MainAr['numpage']; 
	if (!file_exists($Menu->img[$i])) $Menu->img[$i]='';
	if (isset($Menu->list1[$i]) && isset($a_link['butt'][$i])){
		//Page::DisplayButArr($a_link['butt'][$i],$a_link['butthref'][$i],$a_link['imgs'][$i],$Menu->list1[$i], $Menu->list2[$i],$arr,$nc1,count($Menu->list1),$butt,$Menu->img[$i]); 
	
	//if ($nopt>9) $nopt=9;
	if ($active) { 
     if ($Menu->img[$i] == './images/') echo '<div class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($Menu->list2[$i]).'">'.$a_link['butt'][$i].$Menu->list1[$i].'</a>';
	 else {
		echo '<div class="menu-'.$clas['clas'][$nc].'" style="background-image: url('.$Menu->img[$i].')">';
		if ($a_link['imgs'][$i]<> '' ) echo $a_link['imgs'][$i];
		
		echo '<a href ="'.htmlentities($url).'">'.$Menu->list1[$i].'</a>';
		if ($a_link['butt'][$i]<>'') echo $a_link['butt'][$i];
		}
	    if ($a_link['butthref'][$i] <> '') echo $a_link['butthref'][$i]; 	
		echo '</div>';
		} 
    else 
    { 
		if ($a_link['butt'][$i]<>'' ) echo $a_link['butt'][$i];
       echo '<li class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($Menu->list2[$i]).'"> '.$Menu->list1[$i].' </a>';
       if ($a_link['butthref'][$i] <> '') echo $a_link['butthref'][$i].'</li>';     
    } 	
	
	}
	elseif($Menu->list1[$i] <> '')  {
		//Page::DisplayButDiv($Menu->list1[$i], $Menu->list2[$i],$clas,$nc1,count($Menu->list1),$butt,$Menu->img[$i]);
		if ($active) { 
		
     if ($Menu->img[$i] == './images/') echo '<div class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($url).'">'.$name.'</a></div>';
	 else echo '<div class="menu-'.$clas['clas'][$nc].'" style="background-image: url('.$Menu->img[$i].')"><a href ="'.htmlentities($Menu->list2[$i]).'">'.$Menu->list1[$i].'</a></div>'; 
	    } 
    else 
    { 
		
       echo '<li class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($Menu->list2[$i]).'"> '.$Menu->list1[$i].' </a>
            </li>';
    } 
	
	}
	//$butt=true;
	}
}
	echo 'ready';
}

static function oplataYD($order_id,$targets,$summ){

echo '<form method="POST" action="https://money.yandex.ru/quickpay/confirm.xml">
    <input type="hidden" name="receiver" value="410016460239306">
    <input type="hidden" name="formcomment" value="Проект «grandjetstudio»: сайты нового поколения">
    <input type="hidden" name="short-dest" value="Проект «grandjetstudio»">
    <input type="hidden" name="quickpay-form" value="donate">
    <input type="hidden" name="targets" value="транзакция{'.$targets.'} {'.$order_id.'}">
    <input type="hidden" name="comment" value="Что вы ожидаете от проекта для себя?">
    <input type="hidden" name="need-fio" value="true">
    <input type="hidden" name="need-email" value="true">
    <input type="hidden" name="need-phone" value="false">
    <input type="hidden" name="need-address" value="false">';
	
    if ($order_id<>'donat') {
		echo '<input type="disabled" name="sum" value="'.$summ.'" data-type="number">(руб.)   ';
		echo '<input type="hidden" name="label" value=" Донат ">';
	}
	else {
		echo '<input type="hidden" name="label" value="По заказу '.$order_id.'">';
		echo '<input size="10" type="text" name="sum" value="'.$summ.'" data-type="number">(руб.)   '; 
	}
	echo '<input type="submit" value="   Перевести  ">';
	echo '<label><input type="radio" name="paymentType" value="PC"> Яндекс.Деньгами </label>
    <label><input type="radio" name="paymentType" value="AC"> Банковской картой </label></form>';
	}
	
static function accordsh($act,$typelist,$arr,$Pth,$typelist1='imgt',$ns=0,$n=0){
echo '<link rel="stylesheet" type="text/css" href="./images/accordion.css" />';
echo '<link rel="stylesheet" type="text/css" href="./images/ddsmoothmenu.css" />';
echo '<script type="text/javascript" src="./scripts/jquery.min.js"></script>
<script type="text/javascript" src="./scripts/ddsmoothmenu.js"></script>';
echo '<script type="text/javascript">
ddsmoothmenu.init({
	mainmenuid: "templatemo_menu", 
	orientation: "h", 
	classname: "ddsmoothmenu", 
	contentsource: "markup" 
})
</script>';
echo '<script type="text/javascript" src="./scripts/jquery-1.3.2.min.js"></script>';
echo '<script type="text/javascript" src="./scripts/jquery.easing.1.3.js"></script>';
echo '<script type="text/javascript" src="./scripts/jquery.kwicks-1.5.1.pack.js"></script>';

echo "<script type='text/javascript'>$().ready(function() {
		$('.slider').kwicks({
			max : 740,
			spacing : 1
		});
	});</script>";
$clas=$arr['clas'];
$a_img=show::cleanmasspic($clas,$arr,$typelist,$typelist1);
//print_r($a_img);
$numpage=$arr['nump'];
if ($arr['idmen'][0] <> 'land') $buthref=$arr[$typelist1.'href'][$ns];
else $buthref=$numpage.'#zak1';
$butname=$arr[$typelist1][$ns];
if ($a_img){
$a_link=$arr['link'];	
//show::infosh($a_link);

$a_imgs=$a_img[0];
$a_text=$a_img[1];
//show::infosh($a_text);
$nim=count($a_imgs);
//if ($nim>9) {$nim=count($a_imgs);$width_acc=98;}
//else $width_acc=198+(count($a_imgs)-$nim)*10;
if ($act=='Y'){
	echo '<div id="gallary_accordion" class="accordion">';
	//Maket::divclass('#templatemo_main_wrapper',$Pth);
	//Maket::divclass('#templatemo_slider_wrapper',$Pth);
	echo '<div id="templatemo_main_wrapper">';
	echo '<div id="templatemo_slider_wrapper">';
	echo '<ul class="slider horizontal" >
            <li id="slide_1"><img src="images/1.jpg" alt="Slider 01" /></li>
            <li id="slide_2"><img src="images/2.jpg" alt="Slider 02" /></li>
            <li id="slide_3"><img src="images/3.jpg" alt="Slider 03" /></li>
            <li id="slide_4"><img src="images/4.jpg" alt="Slider 04" /></li>
            <li id="slide_5"><img src="images/5.jpg" alt="Slider 05" /></li>
        </ul>';
	/*Maket::divclass('slider',$Pth,'',' horizontal','ul');
	$ww=650;$n=0;
	foreach ($a_imgs as $key=>$val){
		$size = GetImageSize($val); 
		if ($size[0]>=$size[1]) $n=intval($size[0]/$ww);
		else $n=intval($size[1]/$ww);
		if($key<$nim && $key>$ns) {
		if ($arr['idmen'][0] <> 'land') $href[$key]='href="./?np='.$arr[$typelist1.'href'][$key].'"';
		else $href[$key]='href="./?np='.$numpage.'#zak'.$key.'"';
		if ($a_link <> '') {
			if ($arr[$typelist][$key]<>'') {
				Maket::divclass('#slide_'.($key-$ns),$Pth,'',' ','li');
				echo $a_link[$typelist][$key].'<img alt="Slider '.$key.'" src="'.$val.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'/></li>';
				}
			}
			else {
				Maket::divclass('#slide_'.($key-$ns),$Pth,'',' ','li');
				echo '<img alt="Slider '.$key.'" src="'.$val.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'/></li>';
			}
		}	
	}*/
	echo '</ul>';
	echo '</div>';
	echo '</div>';
	echo '</div>';
	}
	else {
		$pagn="Y";
$swbut="Y";
$nsl=1;
$spbetw=10;
$spg=1;
$pagn_type="fraction";
$loop=true;
echo '<style>
.swiper-container {
  width: 50%;
  height: 50%;
}
.swiper-slide {
  text-align: center;
  font-size: 20px;
  background: white;
  display: -webkit-box;
  display: -ms-flexbox;
  display: -webkit-flex;
  display: flex;
  -webkit-box-pack: center;
  -ms-flex-pack: center;
  -webkit-justify-content: center;
  justify-content: center;
  -webkit-box-align: center;
  -ms-flex-align: center;
  -webkit-align-items: center;
  align-items: center;
}
</style>';
		echo '<div class="swiper-container">';
		echo '<div class="swiper-wrapper">';
		foreach ($a_imgs as $key=>$val){
		$size = GetImageSize($val); 
		if ($size[0]>=$size[1]) $n=intval($size[0]/$ww);
		else $n=intval($size[1]/$ww);
		if($key<$nim && $key>$ns) {
		if ($arr['idmen'][0] <> 'land') $href[$key]='href="./?np='.$arr[$typelist1.'href'][$key].'"';
		else $href[$key]='href="./?np='.$numpage.'#zak'.$key.'"';	
		if ($a_link <> '') {	
			echo '<div class="swiper-slide">';
			show::viewSlide($arr,1,$key,$typelist,$typelist1);
			echo '</div>';//swiper-slide
		}
		else {
			echo '<div class="swiper-slide">';
			show::viewSlide($arr,1,$key,$typelist,$typelist1);
			echo '</div>';//swiper-slide
		}
		}
		}
		echo '</div>';//swiper-wrapper
		// Add Pagination -->
    echo '<div class="swiper-pagination"></div>';
    //Add Arrows -->
    
		echo '<div class="swiper-button-next"></div>';
		echo '<div class="swiper-button-prev"></div>';

	//<!-- Swiper JS -->
  echo  '<script src="./scripts/swiper.min.js"></script>';
	//<!-- Initialize Swiper -->
	echo "<script>
    var swiper = new Swiper('.swiper-container', {
      slidesPerView: $nsl,
      spaceBetween: $spbetw,
      slidesPerGroup: $spg,
      loop: $loop,
      loopFillGroupWithBlank: $loop,
      pagination: {
        el: '.swiper-pagination',
        clickable: true,
		type: '$pagn_type',
      },
      navigation: {
        nextEl: '.swiper-button-next',
        prevEl: '.swiper-button-prev',
      },
    });
  </script>";	
	echo '</div>';//swiper-container
	}
}
}


static function work_pages($clas,$Pth,$resu,$hrf='',$ready_host='Y',$base='',$anchor=''){
$mass_zags=$resu[0];	
$mass_zakls=$resu[1];
$menu='';
$page='';
if($hrf<>''){	
	foreach($mass_zakls as $key=>$val) {
		if(isset($_GET[$val])) $page = $val;
		}
	if($page==''){
		$page='?';
		foreach($_GET as $key=>$val) {
			if($val)$ad='=';
			else $ad='';
			$page.=$key.$ad.$val.'&';
		}
	}
	$cls=$clas;
	
	$menu.=Maket::divclasstr($clas.'-set',$Pth,'',' flex');
	$pv=0;
	foreach($mass_zakls as $key=>$value ){
		if(!strstr($value,'?')) $valu='?'.$value;
		$clas=$cls.' opt'.$key;
		if($base<>''){
			if($value==$page ){$menu.=Maket::spanclasstr($mass_zags[$key],$Pth,$clas.' active');$pv=1;}
		elseif($value<>$page && $value<>$base){$menu.=Maket::spanclasstr('<a href="'.$hrf.$value.'">'.$mass_zags[$key].'</a>',$Pth,$clas);$pv=1;}
			elseif($value==$base && $page==$anchor) $menu.=Maket::spanclasstr(Maket::divclasstr('user',$Pth,'','','a href="'.$hrf.'mysites=new&hosting='.$ready_host.'" ').$mass_zags[$key],$Pth,$clas);
			elseif($value<>$base) {$menu.=Maket::spanclastr($mass_zags[$key],$Pth,$clas.' active');$pv=1;}
		}
		else {
			
			if($value.'&'===$page ){
				$menu.=Maket::spanclasstr($mass_zags[$key],$Pth,$clas.' active');
				$pv=1;
			}
			else {
				$menu.=Maket::spanclasstr('<a href="'.$hrf.$value.'">'.$mass_zags[$key].'</a>',$Pth,$clas);
			}
		}
	}
	if($resu[2]<>'' && $pv==1)$menu.='<span class="serv"><a href="./?'.$resu[2].'"><img src="./images/up.gif" width="5px" ></img></a></span>';
	$menu.='</div>';
	
}

return $menu;
}

static function viewer_work_page($clas,$Pth,$mass_zags,$mass_zakls,$data){
	Maket::divclass($clas,$Pth);
	foreach($mass_zakls as $val) if(isset($_GET[$val])) $page = $val;
	foreach($mass_zakls as $key=>$value){
		
		if (isset($_GET[$value]))
			//show::infosh($data[$value]);
			echo Maket::divclasstr('admin',$Pth).$data[$value].'</div>';
			}
	echo '</div>';		
}

static function viewdatapage($dat,$clas,$Pth,$hrf,$selector='span'){
	if(is_array($dat)){
		if(!isset($_GET['editp']))$pp='';
		$pp='&editp='.$_GET['editp'];
		if($selector=='span')foreach ($dat as $val) Maket::divclasstr($clas,$Pth,'','',$selector).$val.'</'.$selector.'>';	
		elseif($selector=='ul') {
			echo '<ul>';
			foreach ($dat as $key=>$val){
				if($key>0) $key='?np='.$key.$pp;
				echo Maket::divclasstr('item',$Pth,'',' active','li').Maket::divclasstr('item',$Pth,'','_'.$key,'a href="'.$hrf.$key.'"').$val.'</a></li>';
			}
		echo '</ul>';
		}
	}
	else echo Maket::divclasstr($clas,$Pth,'','',$selector).$dat.'</'.$selector.'>';	
}

static function ViewblogText($arr,$clas,$Pth,$key,$prefix,$bootgrid,$type='all'){
	if ($type == 'o_pic') {$arr['list'][$key]='';$arr['cont'][$key]='';}
	if ($type == 'wo_pic') {$arr['imgs'][$key]='';$bootgrid=0;}
	if ($type == 'wo_text') {$arr['cont'][$key]='';$bootgrid=12;}
	if($arr['link']<>'')$a_link=$arr['link'];
	else {
		$a_link['conthref'][$key]='';
		$a_link['cont'][$key]='';
		$a_link['list'][$key]='';
	}
	echo '<a href="?np='.$arr['conthref'][$key].'">'.$a_link['conthref'][$key];
	if ($arr['list'][$key]) echo Maket::divclasstr('head-text',$Pth,'',$prefix,'h3').$arr['list'][$key].$a_link['list'][$key].'</h3></div>';
	if ($arr['imgs'][$key]) echo '<div class="col-md-'.$bootgrid.'"><img src="'.$clas['img'].$arr['imgs'][$key].'" alt="alt"/>'.$a_link['imgs'][$key].'</div></a>';
	echo '<div class="col-md-'.(12-$bootgrid).'"><p>'.$arr['cont'][$key].$a_link['cont'][$key].'</p>';
	echo '</div>';
	
}

static function viewformajaxstr($arr_form,$Pth,$name_button,$bootgrid){
	$res='';
	$res.='<div class="col-md-'.(12-$bootgrid).'">';
	$res.='<a href="#order"/>'.Maket::divclasstr('sell_descr',$Pth).'Разработка сайтов - Джи-Джей</div>';	
	$res.='</div>';	
	
	//Maket::divclass('col-md-5',$Pth);
	$res.='<div class="col-md-'.$bootgrid.'">';
	$res.=Maket::divclasstr('sell_right',$Pth);
	Utils::sendajaxMail($Pth,'button',$arr_form,$name_button);
	$res.='<a href="#callback" class="button fancybox">'.$name_button[1].'</a></div>';
	$res.='</div>';
	
	
}

static function viewformajax($arr_form,$Pth,$name_button,$bootgrid){
	echo '<div class="col-md-'.(12-$bootgrid).'">';
	echo '<a href="#order"/>'.Maket::divclasstr('sell_descr',$Pth).$name_button[0],'</div>';	
	echo '</div>';		
	//Maket::divclass('col-md-5',$Pth);
	echo '<div class="col-md-'.$bootgrid.'">';
	echo Maket::divclass('sell_right',$Pth);
	Utils::sendajaxMail($Pth,'button',$arr_form,$name_button);
	//echo '<a href="#callback" class="button fancybox">'.$name_button[2].'</a></div>';
	echo '</div>';
	
	
}

static function viewblogpage($arr,$key,$clas,$Pth,$prefix,$bootgrid){
	Maket::divclass($clas['clas'][14].'-text',$Pth);
				Maket::divclass('blog_item',$Pth,'',$prefix);
				echo '<div class="row">';
				echo '<div class="col-md-12">';
				show::ViewblogText($arr,$clas,$Pth,$key,$prefix,$bootgrid,'wo_text');
				/*echo '<a href="?np='.$arr['conthref'][$key].'">';
				echo Maket::divclasstr('head-text',$Pth,'',$prefix,'h3').$arr['list'][$key].'</h3></div>';
				echo '<div class="col-md-'.$bootgrid.'"><img src="./images/'.$arr['imgs'][$key].'" alt="alt"/></div></a>';
				echo '<div class="col-md-'.(12-$bootgrid).'">';
				echo '<p>'.$arr['cont'][$key].'</p>';
				echo '</div>';*/
				echo '</div>';
			echo '</div>';
			echo '</div>';
}

private function madearraylink($n){
	$arrayk='a'.$n.'00';
		$zz=strlen($arrayk);
		switch ($zz){
			case 5:
			{
			$zn=1;
			break;
			}
			case 6:
			{
			$zn=2;
			break;
			}
			case 7:
			{
			$zn=1;
			break;
			}
			case 8:
			{
			$zn=2;
			break;
			}
		}
	$k0=substr($arrayk,1,$zn)*1;
	$k1=substr($arrayk,$zn+1,1)*1;
	$k2=substr($arrayk,$zn+2,1)*1;
	$k3=substr($arrayk,$zn+3,1)*1;
	$arrayk=array($k0,$k1,$k2,$k3);
return $arrayk;	
}

static function showinputlink($arr,$nlink){
	$arrayk=show::madearraylink($nlink);
	$tabl=$arr['tab'];
	$table=$tabl['pages'];
	$db = Singleton::getInstance('DB');
	$sw = Singleton::getInstance('structureW');
	$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$arrname=explode('|',$arrnm);
	$arrtype=explode('|',$arrtp);
	foreach ($arrtype as $key=>$val) if (strstr($val,'type')) $arrtype[$key]=20;
	if($arrdlm <> null) {
		$arrdelem=explode(',',$arrdlm);
	}
	else {
	for ($i=0;$i<count($arrtype);$i++)  {
		$arrdelem[$i][0]='|';
		$arrdelem[$i][1]=';';
		$arrdelem[$i]=$arrdelem[$i][0].$arrdelem[$i][1];
		}
	}
	//print_r($arrayk);
	$res1=$db->query('SELECT * FROM '.$table.' WHERE `numpage`=^Ni;',$arr['nump']);
	//print_r($res1);
	foreach($res1 as $val){
	if($arrtype[$l] == 'check' ) $array[$l]=$typmen;
	elseif($val == '') $array[$l]=$arrdelem[$l];
	else $array[$l]=$val;
	//if ($arrtype[$l] == 'typ') $array[$l]=$arridmen;
	$l++;
	}
	//print_r($array);
	//$sw->editpartsBD($arrname, $arrtype, $array,$arrdelem,$arrayk,$table,$fields,$ida,$idsite,$clas,$c,$r,$s,$m,1);
	//$sw->editpagesBD($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$tabl,$fields,$c,$r,$s,$m,$t);
	$sw->editpartpage($arrname, $arrtype, $array,$arrdelem,$arrayk,$arr['clas'],$c,$r,$s,$m,1);
}

static function showImGal($i){
	if($i<10){
		$str.= '<div class="grid-item">
		<figure class="effect-sadie">
		<img src="gallery/img/tm-img-0'.$i.'-tn.jpg" alt="Image" class="img-fluid tm-img">
		<figcaption>
		<h2 class="tm-figure-title">Image <span><strong>One</strong></span></h2>
		<p class="tm-figure-description">Set true or false in HTML script tag for this page black and white.</p>
		<a href="gallery/img/tm-img-0'.$i.'.jpg">View more</a>
		</figcaption>           
		</figure>
		</div>';
	}
	else {
		$str.= '<div class="grid-item">
		<figure class="effect-sadie">
		<img src="gallery/img/tm-img-'.$i.'-tn.jpg" alt="Image" class="img-fluid tm-img">
		<figcaption>
		<h2 class="tm-figure-title">Image <span><strong>One</strong></span></h2>
		<p class="tm-figure-description">Set true or false in HTML script tag for this page black and white.</p>
		<a href="gallery/img/tm-img-'.$i.'.jpg">View more</a>
		</figcaption>           
		</figure>
		</div>';
	}
	return $str;
}

static function showGalery($part,$ord){
	$str.='<div class="cd-full-width">
        <div class="container-fluid js-tm-page-content" data-page-no="1" data-page-type="gallery">
        <div class="tm-img-gallery-container">
        <div class="tm-img-gallery gallery-'.$part.'">';
	for($i=1;$i<$ord;$i++) $str.=show::showImGal($i);	
    $str.= '</div></div></div></div> ';   
	return $str;
	}
	
	

//16/06/2020

static function aimgPopup($img, $clas='popup'){
	return '<a href="img/'.$img.'" class="'.$clas.'"><img src="img/'.$img.'" alt="Alt" /></a>';
}	

static function showAbout($Pth,$dat,$datSoc,$firstname,$about,$img){
	$glsr = glossary();
	$loz1 = explode('=',$about[0]);
	$loz2 = explode('=',$about[1]);
	$loz = Maket::spanclasstr($loz2[0],$Pth,'personal_header','h2').$loz2[1];
	$text = array(0=>$glsr['am'],1=>$glsr['ic']);
	$text[2] = $glsr['ft'];
	$text[3] = $glsr['lam'].Maket::spanclasstr($loz1[0],$Pth,'personal_header','h2').$loz1[1];
	$text[4] = $glsr['pi'].Maket::spanclasstr($firstname,$Pth,'personal_header','h2');
	$datSoc = Maket::divclasstr('social_wrap',$Pth).Maket::viewdatapage($datSoc,'',$Pth,'./','ul').Maket::closedivstr(1);
	$list = Maket::viewdatapage($dat,'',$Pth,'./','p').$datSoc;
	$content[0] = Maket::div3Blockstr($Pth,$text[1],'section_header',$text[0],'s_descr_wrap','s_descr');
	$content[1] = Maket::div2Blockstr($Pth,show::aimgPopup($img[0]),$text[2],'col-md-4 col-md-push-4 animation_1','person');
	$content[2] = Maket::div2Blockstr($Pth,$loz,'<p>'.$text[3].'</p>','col-md-4 col-md-pull-4 animation_2');
	$content[3] = Maket::div2Blockstr($Pth,$list,'<p>'.$text[4].'</p>','col-md-4 animation_3 personal_last_block');
	$str = $content[0];
	$str1='';
	for($i=1;$i<4; $i++){
		$str1 .= $content[$i];
	}
	$str .=Maket::div3Blockstr($Pth,$str1,'section_content','','container','row');

return $str;
}	

static function blogItem($Pth, $card, $word1='',$word2='',$word3=''){
	$str = Maket::divclasstr($word1,$Pth).Maket::divclasstr($word2,$Pth)
	.$card[0].Maket::closedivstr(1).Maket::divclasstr($word3,$Pth)
	.$card[1].'<strong>'.$card[2].'</strong>'.Maket::closedivstr(1)
	.$card[3].Maket::closedivstr(1);
	return $str;
}

static function showResume($Pth,$text,$blog,$dataIcons,$nb=0,$nc=1){
	$glsr = glossary();

	$content[0] = Maket::div3Blockstr($Pth,$glsr['kn'],'section_header',$glsr['rm'],'s_descr_wrap','s_descr');
	$contentRight = '';
	$contentLeft = '';
	for($i=0;$i<16;$i++){
		$dats[$i] = explode('=',$blog[$i]); 
		$card = array(0=>$dats[$i][0],1=>$text[$i],2=> $text[$i+1],3=>$dats[$i][1]);
		$contentRight .= Maket::blogItemRight($Pth, $card, 'resume_item','year','resume_description');
		$i++;
	}
	for($i=16;$i<26;$i++)	{
		$dats[$i] = explode('=',$blog[$i]); 
		$card = array(0=>$dats[$i][0],1=>$text[$i],2=> $text[$i+1],3=>$dats[$i][1]);
		$contentLeft .= Maket::blogItemLeft($Pth, $card, 'resume_item','year','resume_description');
		$i++;
	}
	$str = $content[0];
	$str1 = Maket::div2Blockstr2($Pth,$contentRight,$glsr['st'],'col-md-6 col-sm-6 left','resume_icon',$dataIcons[$nb])
	.Maket::div2Blockstr2($Pth,$contentLeft,$glsr['wr'],'col-md-6 col-sm-6 right','resume_icon',$dataIcons[$nb+$nc]);
	$str1 =Maket::divclasstr('resume_container',$Pth).$str1.'</div>';
	$str .=Maket::div3Blockstr($Pth,$str1,'section_content','','container','row');
return $str;
}



static function showPortfolio($Pth,$clas1,$clas,$dat,$blog,$imgs){
	$glsr = glossary();
	
	$content[0] = Maket::div3Blockstr($Pth,$glsr['lw'],$clas[2],$glsr['pf'],$clas[3],$clas[4]);
	$str = $content[0];
	
	
	
	$list = Maket::viewdatapageold($dat,$clas1,$Pth,'./','ul');

	foreach($blog as $k=>$val) {
		if(strstr($val,'=') && $val != '') {
			$text[$k] = explode('=',$val);
			if(isset($text[$k][2])) {$desc = $text[$k][1];$text[$k][1]=$text[$k][2];}
			else $desc = $glsr['dc'];

		}	
		elseif($val != '') {$text[$k][0] = $val;$text[$k][1]='';}
		if(isset($text[$k]))$card[$k] = array($imgs[$k],$text[$k][0],$desc,$glsr['lk'],$text[$k][1]);
	}	
	if(isset($card)) $str1 = $list.Maket::divclasstr($clas[6],$Pth)
	.Maket::portfolioItem($Pth,$card[0],1).Maket::portfolioItem($Pth,$card[1],2).
	Maket::portfolioItem($Pth,$card[2],2).Maket::portfolioItem($Pth,$card[3],3).
	Maket::portfolioItem($Pth,$card[4],3).Maket::portfolioItem($Pth,$card[5],1).
	Maket::portfolioItem($Pth,$card[6],1).Maket::portfolioItem($Pth,$card[7],2).
	'</div>';

	if(isset($str1))$str .=Maket::div3Blockstr($Pth,$str1,$clas[5],'','container','row');
	else return null;
return $str;
}

static function showContacts($Pth,$blog,$arrF,$dat,$n){
	$glsr = glossary();
	$text = array($glsr['cn'],$glsr['lm'].':',$glsr['ad'].':',$glsr['tf'].':',$glsr['ws'].':');
	$dataIcons = array(1=>$dat[$n],2=>$dat[$n+1],3=>$dat[$n+2]);


	$content[0] = Maket::div3Blockstr($Pth,$text[1],'section_header',$text[0],'s_descr_wrap','s_descr');
	//for($i=1;$i<4;$i++) $content[i] = Maket::div2Blockstr2($Pth,'<h3>'.$text[$i+1].'</h3>'.'<p>'.$blog[$i].'</p>','','contact_box','contacts_icon '.$dataIcons[$i],'',1);
	//echo $content[1];
	$str = $content[0];

	$str1 = '<div class="col-md-6 col-sm-6">';
	for($i=1;$i<4;$i++) $str1 .= Maket::div2Blockstr2($Pth,'<h3>'.$text[$i+1].'</h3>'.'<p>'.$blog[$i].'</p>','','contact_box','contacts_icon '.$dataIcons[$i],'',1);
	$str1 .='</div>';
	$str1 .= '<div class="col-md-6 col-sm-6">';
	$str1 .= Maket::showForm($Pth,$arrF);
	$str1 .='</div>';
	
$str .=Maket::div3Blockstr($Pth,$str1,'section_content','','container','row');
return $str;
}

static function showFooter($Pth,$dat,$firstname){
	$datSoc = '&copy; 2015 '.$firstname.Maket::divclasstr('social_wrap',$Pth).Maket::viewdatapage($dat,'',$Pth,'./','ul').Maket::closedivstr(1);
	$str = Maket::div3Blockstr($Pth,$datSoc,'container','','row','col-md-12');
return $str;
}

static function showPersonLandMaket($Pth, $id, $clas, $content){
	$str = '';
	if(is_array($content)){
		foreach ($content as $key=>$val){
		$str.='<a href="'.$id[$key].'"></a>';	
		$str .= Maket::spanclasstr($val,$Pth,$id[$key],'section');
			}
		}
	else {
		$str = Maket::spanclasstr($content,$Pth,$id,'section');
		}	
	return $str;
}

static function showMenuBurger($Pth,$id,$dat,$firstName,$Proffesion){
	$glsr = glossary();
	$content[0]='<div class="logo_container">
	<svg
	xmlns="http://www.w3.org/2000/svg"
	viewBox="0 0 197.21155 197.21638"
	version="1.1"
	id="svg2">
	<path
	id="path3338"
	d="m 85.639184,196.34986 c -8.98123,-1.10864 -26.37065,-6.72944 -34,-10.98986 C 5.3202742,159.49442 -12.920616,103.30115 9.6507445,56.009515 35.258674,2.3556684 103.14827,-16.573789 152.80625,16.093889 c 9.38469,6.173749 22.09904,18.888095 28.27279,28.272782 24.99997,38.002345 20.5737,88.354329 -10.7064,121.792849 -11.28666,12.06547 -24.35624,20.32658 -40.73346,25.74709 -15.42819,5.10639 -28.18874,6.39499 -43.999996,4.44325 z m 38.999996,-11.29283 c 15.41119,-5.00098 25.17271,-10.7626 36.3615,-21.46194 11.70973,-11.19749 18.92933,-22.87913 24.14107,-39.06134 2.17289,-6.7467 2.84123,-11.07839 3.2401,-21 0.69381,-17.257746 0.53639,-17.635282 -4.13864,-9.925231 -14.18515,23.394141 -35.33853,44.351601 -55.10403,54.593711 -13.43669,6.96263 -20.99782,8.83672 -35.499996,8.79897 -13.86683,-0.0361 -20.46689,-1.69669 -29.96055,-7.53821 l -4.95062,-3.04614 -9.55314,3.57807 c -5.25423,1.96794 -11.79922,4.09652 -14.54442,4.73019 -2.7452,0.63367 -4.99127,1.45101 -4.99127,1.81632 0,1.15794 13.31395,13.48867 18,16.67071 16.64977,11.30596 31.44785,15.43875 53.499996,14.94144 13.09158,-0.29524 16.08144,-0.68921 23.5,-3.09655 z m -15.06389,-40.11066 c 24.5486,-5.9367 53.58095,-31.17002 71.03294,-61.73794 l 5.10375,-8.939432 -1.67558,-5.117626 C 179.80634,56.231758 171.74636,43.74801 161.00068,33.472398 149.77427,22.737083 138.02714,15.903199 123.10324,11.425586 113.07832,8.4178144 91.918094,7.6951014 80.549574,9.9721954 c -9.02888,1.8084666 -20.57318,6.3638476 -29.72893,11.7310296 -7.32612,4.294636 -24.71735,21.68586 -29.01198,29.01198 -10.1557,17.324373 -13.6655198,31.384748 -12.9128295,51.728935 0.55535,15.01039 2.1565895,21.68909 8.4727695,35.3396 3.22555,6.97107 3.86775,7.75 6.38955,7.75 3.17959,0 17.452,-3.221 23.19236,-5.23405 l 3.81134,-1.33658 -3.16228,-3.96468 c -9.74195,-12.21388 -14.69959,-32.39019 -12.08115,-49.167051 4.49452,-28.797162 26.36933,-55.777779 51.44164,-63.448647 10.25576,-3.137749 22.140686,-2.373203 31.013976,1.9951 20.82199,10.250635 25.47632,36.131513 11.11579,61.810536 -9.52176,17.026522 -32.857026,39.632002 -52.200646,50.568142 -2.8875,1.63248 -5.25,3.31405 -5.25,3.73683 0,0.80005 5.95989,3.23154 12,4.89571 5.51806,1.52033 18.753026,1.29443 25.936106,-0.44268 z M 68.417704,131.63644 c 24.85553,-12.58662 49.568806,-37.101981 57.354776,-56.895433 1.80033,-4.576813 2.25706,-7.787016 2.30585,-16.207261 0.0532,-9.179719 -0.24448,-11.115491 -2.36739,-15.394909 -2.93145,-5.909281 -7.65775,-10.810081 -13.34832,-13.841145 -3.47734,-1.852196 -5.81707,-2.250871 -13.244467,-2.256775 -8.155809,-0.0065 -9.651259,0.303093 -15.592069,3.227744 -11.4838,5.653457 -20.43389,15.358172 -27.91171,30.265085 -10.8455,21.620318 -12.44987,42.106384 -4.58144,58.500004 2.86279,5.96452 9.76074,15.5 11.21269,15.5 0.24782,0 3.02526,-1.30379 6.17208,-2.89731 z" />
	</svg>
	</div>';
	$burger = '<button class="toggle_mnu">
	<span class="sandwich">
		<span class="sw-topper"></span>
		<span class="sw-bottom"></span>
		<span class="sw-footer"></span>
	</span></button>';
	foreach($dat as $k=>$val)$dat['dat'][$id[$k]] = $dat[$k];
	$dat['typesite'] = 'spa';
	$authorName = '<div class="top_centered">
	<div class="top_text">
		<h1>'.$firstName.'</h1>
		<p>'.$Proffesion.'</p>
	</div>
</div>';
$str1 = $content[0].$burger.Maket::spanclasstr(Maket::viewdatapageold($dat,'',$Pth,'','ul'),$Pth,'top_mnu','nav');
$str2 = Maket::div2Blockstr($Pth,$authorName,'','top_wrapper','top_descr');
$str = 	Maket::div3Blockstr($Pth,$str1,'container','','row','col-md-12',$str2);
return $str;
}
//13/07/2020

static function showHeaderLand($Pth,$id,$dat,$clas,$param){
	$firstname = array_shift($dat);
	$lozName = array_shift($dat);
	$datM = $dat;
	$str = '<header class="'.$clas.'" '.$param.'>';
	$str .= show::showMenuBurger($Pth,$id,$datM,$firstname,$lozName);
	$str .= '</header>';
	return $str;
}

static function loaderLand(){
	$str = '<div class="loader">
	<div class="loader_inner"></div>
</div>';
return $str;
}
static function showLandPersonal($arrmain,$Pth,$YourMaket,$db){
//! адрес, телефон, сайт		
//!формируем классы и идентификаторы из макета
	$glsr = glossary();
	$arrloz = $arrmain['loz'];
	$dat['dat'][0] = $arrloz[0]; 
	$dat['dat'][1] = $glsr['bd'].': 2 января 1962 года';
	$dat['dat'][2]= $glsr['tn'].': +79255053421';
	$dat['dat'][3] = $glsr['el'].': <a href="mailto:ruslan@deltar.ru">ruslan@deltar.ru</a>';
	$dat['dat'][4] = $glsr['ws'].': <a href="//land.deltar.ru" target="_blank">land.deltar.ru</a>';
	$img = array(0=>'photo.jpg');
	$datSoc['dat'] = array('twitter' => '<i class="fa fa-twitter"></i>',
	'vk' => '<i class="fa fa-vk"></i>',
	'fb' => '<i class="fa fa-facebook"></i>',
	'gh' => '<i class="fa fa-github"></i>');
	$datSoc['icon'][0] = '<i class="icon-basic-case"></i>';
	$datSoc['icon'][1] = '<i class="icon-basic-book-pen"></i>';
	$datSoc['icon'][2] = 'icon-basic-geolocalize-05';
	$datSoc['icon'][3] ='icon-basic-smartphone';
	$datSoc['icon'][4] ='icon-basic-webpage-img-txt';
	$dataIcons1 = array(0=>'<i class="icon-basic-case"></i>',
	1=>'<i class="icon-basic-book-pen"></i>'); 
	$dataIcons2['dat'] = array(1=>$datSoc['dat']['vk'],2=>$datSoc['dat']['fb'],3=>$datSoc['dat']['gh']);
		
	$datM = array($arrmain['owner']->cfio,$arrloz[2],$glsr['am'],$glsr['rm'],$glsr['pf'],$glsr['ct']);	
	$blogC = array(0=>$arrmain['owner']->cfio,
	1=>$arrmain['owner']->uradr,
	2=>$arrmain['owner']->telmain,
	3=>'<a href="'.$arrmain['site'][0].'" target="_blank">'.$arrmain['site'][0].'</a>');
	//$YourMakets = $db->allmakets(1,$maket);
	//$YourMaket = $YourMakets[$arrmain['idmen'][0].'-'.$arrmain['nump']];
	//$YourMaket = explode('|',$YourMakets[0][10]);	
	$arrClasNumber = explode('*',$YourMaket[0][10]);	
	$mainClas = explode(',',$arrClasNumber[0]);
	$numbClas = explode(',',$arrClasNumber[1]);
	foreach($mainClas as $i=>$val){
		if($i < $numbClas[0]) $id[] = $val;
		elseif($i < $numbClas[0] + $numbClas[1]) $clas0[] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2]) $clas2[] = $val;
		elseif($i < $numbClas[0] + $numbClas[1] + $numbClas[2] + $numbClas[3]) $clas1[] = $val;
	}

//! Загружаем данные формы
$Your_Forms = explode('|',$YourMaket[0][11]);
$d = "SELECT * FROM `nameform` WHERE `id`=^Ni;";
$Namform = $db->query($d, $Your_Forms[0]);
//debug($Namform);
$d = "SELECT * FROM `forms` WHERE `idform`=^Ni;";
$Fieldform = $db->query($d,$Namform->id);
//debug($Fieldform);
foreach($Fieldform as $val){
	$arrF['js'][] = $val->method;
	$arrF['cls'][] = $val->clas_field;
	$arrF['type'][] = $val->type_field;
	$arrF['place'][] = $val->place_field;
	$arrF['req'][] = $val->req_field;
	$arrF['name'][] = $val->name_field;
	$arrF['label'][] = $val->label;
	$arrF['valid'][] = $val->default;
}
$arrF['act'][] = $Namform->handler;
$arrF['method'][] = $Namform->method;
//debug($arrF);
	//$arrloz = $arrmain['loz'];
		foreach($arrmain['butt'] as $val) if($val != '')$dat1['dat'][] = $val;
		$imgs = $arrmain['imgs'];
		//$text = $arrmain['list'];
		$blog1 =  $arrmain['imgt'];
		$k=0;
		for($i=2;$i<15;$i++){
			$blog[$k] = $arrmain['cont'][$i+1];
			$k+=2;
			
		}
		$about = array($arrmain['cont'][0],$arrmain['cont'][1]);
		for($i=0;$i<26;$i++){
			$text[$i] = $arrmain['list'][$i];
		}
	echo show::loaderLand();
	echo show::showHeaderLand($Pth,$id,$datM,'main_head','data-parallax="scroll" data-image-src="img/bg.jpg" data-z-index="1"``');

	$content = array(show::showAbout($Pth,$dat,$datSoc,$arrmain['owner']->cfio,$about,$img),
	show::showResume($Pth,$text,$blog,$dataIcons1,0,1));
	echo show::showPersonLandMaket($Pth,$id,$clas2,$content);

	echo '<section id="'.substr($id[2],1).'" class="'.$clas0[1].'">'.show::showPortfolio($Pth,$clas1,$clas2,$dat1,$blog1,$imgs).'</section>';

	echo show::showPersonLandMaket($Pth,$id[3],$clas0[2],show::showContacts($Pth,$blogC,$arrF,$datSoc['icon'],2));

	echo Maket::spanclasstr(show::showFooter($Pth,$dataIcons2,$arrmain['owner']->cfio),$Pth,$clas0[3],'footer');

}

static function showicon($img,$clas,$clas_icon,$style){
	$str = '<div class="'.$clas.'">
    <img class="'.$clas_icon.'" style="'.$style.'" src="'.$img.'" alt="">
	</div>';
	return $str;
}

static function shopCardItem($specLabel){
	$str = '<div class="submenu-page__product">
	<div class="item-product">
		<div class="item-product__labels">'
		.$specLabel.
		'</div>
		<a href="" class="item-product__image">
			<img src="./images/01.jpg" alt="Теннисный стол. Зеленый">
		</a>
		<div class="item-product__body">
			<a href="" class="item-product__title">Домашний Теннисный стол Donic Indoor</a>
			<div class="item-product__footer">
				<div class="item-product__oldprice">64 990р</div>
				<div>
					<a href="" class="item-product__add">
						<img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
					</a>
				</div>        
				<div class="item-product__price">62 000р</div>        
			</div>     
		</div>
	</div>
</div>';
return $str;
}


static function showBlogItem($clas, $callDat,$i,$datajs='',$selector='div',$direct='left'){
	$str = '<'.$selector.' href="'.$callDat['href'][$i].'" class="'.$clas.'-side__item">';
	if($direct === 'right'){
	$str .='<div class="'.$clas.'-side__header">
        <div class="'.$clas.'-side__label">'.$callDat['name'][$i].'</div>
        <div class="'.$clas.'-side__data">'.$callDat['date'][$i].'</div>              
    </div>';
	$str .='<div class="'.$clas.'-side__body">'.$callDat['text'][$i].'</div>';        
	}
	else {
		$str .= '<div class="'.$clas.'-side__label">'.$callDat['name'][$i].'</div>';
		$str .='<div class="'.$clas.'-side__header">';
		$str .='<div class="'.$clas.'-side__data">'.$callDat['date'][$i].'</div><div class="'.$clas.'-side__body">'.$callDat['text'][$i].'</div>              
	</div>';
	}
$str .= '</'.$selector.'>';
return $str;
}

static function showformSearches($clas,$contentCategories){
	$glsr = glossary();
	$str = '';
	$str .= '<form action="" class="page__search search-page">
    <div class="search-page__select">
        <div class="search-page__title">
            <span>'.$glsr['al'].'</span><span data-text="'.$glsr['cs'].'" class="choice-quant"><small></small></span>
        </div>
        <div class="search-page__categories '.$clas.'">
            <div class="'.$clas.'__row">'.
            maket::showColumns($clas,$contentCategories).'
            </div>
        </div>
    </div>
    <div class="search-page__input">
        <input autocomplete="on" type="text" name="form[]" data-error="'.$glsr['er'].'" data-value="" class="input">
    </div>
    <button type="submit" class="search-page__btn btn">'.$glsr['fd'].'</button>
	</form>';
return $str;
}

static function showSwipSlider($arr,$clas='mainslider',$clasPag='mainslider__dotts'){
	$str = '';
	switch($clas){
		case 'mainslider':{
			$str .= '<div class="page__slider '.$clas.'">';
			$str .= '<div class="'.$clas.'__body _swiper">';
			foreach($arr as $val){
				$str .= '<div class="'.$clas.'__slide">'.$val.'</div>';
			}
			$str .= '</div>';
			$str .= '<div class="'.$clasPag.'"></div></div>';
			break;
		}
		case 'products-slider':{
			$str .='<div class="products-slider__header">
			<div class="products-slider__title">Популярные товары</div>';
			$str .='<div class="'.$clas.'__control">
			<div class="'.$clas.'__arrow '.$clasPag.'_prev"></div>
			<div class="'.$clas.'__info"></div>
			<div class="'.$clas.'__arrow '.$clasPag.'_next"></div>        
			</div></div>';
			$str .='<div class="'.$clas.'__item _swiper">';
			$str .='<div class="'.$clas.'__slide">
				<div class="'.$clas.'__items items-products">';
				foreach($arr as $i=>$val){
					$str .= '<div class="items-products__column">
					<div class="item-product">'.$val.
					'</div></div>';
				}
			$str .= '</div></div>';
			$str .='<div class="'.$clas.'__slide">
				<div class="'.$clas.'__items items-products">';
			foreach($arr as $i=>$val){
			$str .= '<div class="items-products__column">
			<div class="item-product">'.$val.
			'</div></div>';
			}
			$str .= '</div>';
			$str .= '</div>';
				break;
			}
			case 'brands-slider':{
				$str = '<div class="page__brands '.$clas.'">
				<div class="'.$clas.'__container _container">
				<div class="'.$clas.'__body  _swiper">';
				foreach( $arr as $val) $str .= '<div class="'.$clas.'__slide">'.$val.'</div>';
			}
			$str .= '</div>';
			$str .= '<div class="'.$clasPag.'s">
			<div class="'.$clasPag.' '.$clasPag.'_prev"></div>
			<div class="'.$clasPag.' '.$clasPag.'_next"></div>
			</div>';
		$str .= '</div></div>';
		}
	return $str;
}

static function showSwipSliderCard($arr,$clas='mainslider',$clasPag='mainslider__dotts',$loz=''){
	$str = '';
	switch($clas){
		case 'images-product__mainslider':{
			$str .= '<div class="images-product__sale">-5%</div>';
			$str .= '<div class="'.$clas.' _swiper">';
			foreach($arr['img'] as $k=>$val){
				$str .= '<a href="" class="'.$clas.'">
					<div class="images-product__image _ibg">
					<img src="../images/'.$val.'" alt="'.$arr['alt'][$k].'">
					</div>
					</a>';
				}
				$str .= '</div>';
					
		}
		case 'images-product__subslider':{
			$str .= '<div class="'.$clas.' _swiper">';
			foreach($arr['img'] as $k=>$val){
				if(!isset($arr['alt'][$k])) $arr['alt'][$k] = '';
				if($val != ''){
					$str .='<div class="images-product__subslide">
				<div class="images-product__subimage _ibg"><img src="../images/'.$val.'" alt="'.$arr['alt'][$k].'">
				</div></div>';
				}
			}
		}
		$str .= '</div>';
	}
	return $str;
}

static function showSwipSliderCatalog($arr,$clas='mainslider',$clasPag='mainslider__dotts',$loz=''){
	$str = '';
if(is_array($arr)){
	$str .='<div class="products-slider__header">
	<div class="products-slider__title">Категория товара</div>';
	$str .='<div class="'.$clas.'__control">';
	$str .='<div class="'.$clas.'__arrow '.$clasPag.'_prev"></div>
	<div class="'.$clas.'__info"></div>';
	// $str .='<div class="swiper-pagination '.$clasPag.'">';
	// $str .='</div>';
	$str .='<div class="'.$clas.'__arrow '.$clasPag.'_next"></div>';        
	$str .='<div class="container-swiper-bullets">
			<div class="swiper-pagination"></div>
		</div>';
	$str .= '</div></div>';
	$str .='<div class="'.$clas.'__item _swiper">';
	foreach($arr as $value){
		if(is_array($value)){
			$str .='<div class="'.$clas.'__slide">
			<div class="'.$clas.'__items items-products">';
			foreach($value as $i=>$val){
				$str .= '<div class="items-products__column">
				<div class="item-product">'.$val.
				'</div></div>';
			}
			$str .= '</div></div>';	
		}
		else {
			$str .='<div class="'.$clas.'__slide">
			<div class="'.$clas.'__items items-products">';
				$str .= '<div class="items-products__column">
				<div class="item-product">'.$value.
			'</div></div>';
			}
	}
	$str .= '</div></div>';	
	$str .= '</div>';
}
if($clasPag != ''){
	$str .= '<div class="'.$clasPag.'s">
		<div class="'.$clasPag.' '.$clasPag.'_prev"></div>
		<div class="'.$clasPag.' '.$clasPag.'_next"></div>
		</div>';
	$str .= '</div></div>';	
}
	
	return $str;
}

static function showSwipSliders($arr,$clas='mainslider',$clasPag='mainslider__dotts'){
	$str = '';
	switch($clas){
		case 'mainslider':{
			$str .= '<div class="page__slider '.$clas.'">';
			$str .= '<div class="'.$clas.'__body _swiper">';
			foreach($arr as $val){
				if($val != '')$str .= '<div class="'.$clas.'__slide">'.$val.'</div>';
			}
			$str .= '</div>';
			$str .= '<div class="'.$clasPag.'"></div></div>';
			break;
		}
		case 'products-slider':{
			$str .='<div class="products-slider__header">
			<div class="products-slider__title">Популярные товары</div>';
			$str .='<div class="'.$clas.'__control">
			<div class="'.$clas.'__arrow '.$clasPag.'_prev"></div>
			<div class="'.$clas.'__info"></div>
			<div class="'.$clas.'__arrow '.$clasPag.'_next"></div>        
			</div></div>';
			$str .='<div class="'.$clas.'__item _swiper">';
			$str .='<div class="'.$clas.'__slide">
				<div class="'.$clas.'__items items-products">';
				foreach($arr as $i=>$val){
					$str .= '<div class="items-products__column">
					<div class="item-product">'.$val.
					'</div></div>';
				}
			$str .= '</div></div>';
			$str .='<div class="'.$clas.'__slide">
				<div class="'.$clas.'__items items-products">';
			foreach($arr as $i=>$val){
			$str .= '<div class="items-products__column">
			<div class="item-product">'.$val.
			'</div></div>';
			}
			$str .= '</div>';
			$str .= '</div>';
				break;
			}
		case 'brands-slider':{
			$str = '<div class="page__brands '.$clas.'">
			<div class="'.$clas.'__container _container">
			<div class="'.$clas.'__body  _swiper">';
			foreach( $arr as $val) $str .= '<div class="'.$clas.'__slide">'.$val.'</div>';
		}
		$str .= '</div>';
		$str .= '<div class="'.$clasPag.'s">
		<div class="'.$clasPag.' '.$clasPag.'_prev"></div>
		<div class="'.$clasPag.' '.$clasPag.'_next"></div>
		</div>';
		$str .= '</div></div>';
		}
	return $str;
}

static function showShopHeader($Pth,$arrmain,$clasShop='',$contentShop='',$optMenu='',$Icons=''){
	$glsr = glossary();
	if($arrmain != ''){
		//echo 'страницы загружены';
		//debug($arrmain['owner']);
		$dat1['typesite'] = 'spa'; 
		$dat1['dat']=array($glsr['br'],$glsr['sl'],$glsr['dl'],$glsr['wr'],
		$glsr['py'],$glsr['cn']);
		$dat1['href'] = array('options.html','options.html#sale','options.html#movie',
		'options.html#warrant','options.html#pay','options.html#contacts');
		$numOrder = 12;
		if($arrmain['owner']->city !='' && $arrmain['owner']->telmain != 'no')$contscts = '<div class="contacts-header__label">'.$arrmain['owner']->city.'</div><a href="tel:'.$arrmain['owner']->telmain.'" class="contacts-header__phone">'.$arrmain['owner']->telmain.'</a>';		 
		if($arrmain['owner']->tels !='')$contactadd = '<a href="tel:'.$arrmain['owner']->tels.'" class="contacts-header__phone">'.$arrmain['owner']->tels.'</a>';
		$contLogo = $contLogo = show::showlogo('top-header__logo','',$Pth,8);
		if($arrmain['typmen'][3] != 'nbt')$contenTop = maket::viewdatapage($dat1,'menu',$Pth,'','ul');
		else $contenTop = '';
		if($arrmain['owner']->email != '')$navMenu['dat'] = array('<span>'.$glsr['in'].'</span>',
		'<span>'.$glsr['rg'].'</span>',
		'<span>'.$arrmain['owner']->email.'</span>');
		$navMenu['href'] = array('./auth/','./registration','mailto:'.$arrmain['owner']->email);
		$navMenu['typesite'] ='spa';
		$contentShop = array('contact' => $contscts,'addcont'=>$contactadd,'logo'=>$contLogo,'top'=>$contenTop,'nav'=>$navMenu);
		$navMenu1['dat'] = array('<span>'.$glsr['cl'].'</span>',
		'<span><p><span>'.$glsr['ww'].'</span>'.$glsr['dw'].'</p>'.
		'<p><span>'.$glsr['ss'].'</span>'.$glsr['ds'].'</p></span>');
		$optMenu = array();
		$optMenu['dat'] = array('<a href="" class="info-header__callback">
		<img class="user-header__icon"style="width: 16px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
		'.$navMenu1['dat'][0].'</a>',
		'<div class="info-header__schedule">
		<div>'.$navMenu1['dat'][1].'</div></div>');
		if($numOrder > 0)$optMenu['dat'][]=
		'<a href="" class="info-header__cart">
		<img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAB4AAAAeCAYAAAA7MK6iAAAABmJLR0QA/wD/AP+gvaeTAAADxklEQVRIib2VS0xcVRjH/+cehhkYOiOPDkYsJhiNaSEQFy7cddMmxoULd5ooxcw0xmDpQoWNk5RasDVt1KQyQGSh0cQmNmpMNG2MXRBjCi2PlmoZqETAeXHncee+zzmuxsAUhgsM/pObfOf7/vf+7uv7DgGArpGeOibXHnPL/oTE+eLlgVOLABHYR5GukZ46l6dm5pEqn1+OabNYOjAHgmZBaTDS3x3dL7BkkMpDtV6fp+Ppp7yS37aHBno6bSFC4GwsGBxy7Rv4i67BqbV8ZvTX27fGdcMKAsDowOl5IshPol47vl/gCgAYerX/nYcqHDeIhOMAftg38GYSVfZdQAy/NvreXcJ5lFAa/fzEuUS5wKRUMXjmvNl+NEBkNadklbypGTpjnOmESHEI/Klzc8I2rTkm6EI1W/srEopYZQGH+i9kXnj5iK/KU7khb1oWFE1DTlORU/NaOq/ks3mNGZYhOBc6pdI8CCbzmj4BTqKkQo+OdV5KOwafHBic7niuua2lJeD0QcA5/++msqpiZBU1m1YV2zBNxhjXBcSiaRqvb/mNAcCG9Xv8n+yRlpaA5BQsSRJ8Xi98Xi+acNAN4OD6+tXxGzUVdjpR8oIWwS/ppGYU52OyjLyuOY4L0kwTnJPFSChilQRXc/qjprCHPDE5BUXTHccFraaSjDHrCgCUBF/u7ZWZXb6RvRSPJS1ufr8tGAAIFUo2o+4ZKiAg53LGWOf5+47AoPz+ympmz+C0ooAQ3CystwXbYOPxeNbxYNhKK8mEpprq147BEsS1bMqw1+caa+tRU+VxHAPAUjyepsy+XliX7GMASOvWdco2/tmNtbU7ihnnMEwzM/rGxTXH4G/CYfPkmQt8JZUCKTnnttZqKqUyzq+sz20LBgDGcOu3yXsP4LFzuwFbnE1HF12RHYOJWXGVLfj+GD536rvdgDeToxksIGYJeGu5oM7BNp0RIP8/eOTD7r+JEE+Ew2HHu1RZwAAgCPl2Wfe/Wy7wDhpEkFDfpbNC4HlKqSXAk9wiU4SITXcRQkSdVEE7BOcLnOGBEOSryODbS4X6Dl4dEUMf9PR53J6a1sPPHG0+9PhLlR7aziEmig8m+D13ledEe1vrMb/f9wokolPi2tCKjtppwwku6dGmpsdowArQWCzx5PDAW9eKPcG+i882NNSjsTEAAAeUuTs1n77/prwnMLPFzzcnp17UdV0w2/5oU1OyeibuTi5Pz97BWkrWbc3+stiyqyEY6v34MJHszGdnTy9v5QkGh1xoUNvclXT+k3B3trj+L3N4AU8Y9iHuAAAAAElFTkSuQmCC"/>
		<span>'.$numOrder.'</span>
		</a>'; 
	}
	//$glsr = glossary();
	$opt = '';
	foreach ($optMenu['dat'] as $val){if($val)$opt .='<div class="info-header__column">'.$val.'</div>'; }
	if($opt)$opts=maket::spanclasstr($opt,$Pth,'bottom-header__info info-header','div');
	
	if($contentShop['contact'] != '')$str0 = maket::div2Blockstr($Pth,$contentShop['contact'],'',$clasShop['header'][0].'__column',$clasShop['header'][0].'__item_icon');
	else $str0 = '';
if($contentShop['addcont'] != '')$str1 = maket::div3Blockstr($Pth,$glsr['bp'].$contentShop['addcont'],$clasShop['header'][0].'__column','',$clasShop['header'][0].'__item',$clasShop['header'][0].'__label');
$str1 = '';

//$str2 = maket::div3Blockstr($Pth,$Icons[0],$clasShop['header'][1].'__header',$glsr['ct'],$clasShop['header'][1].'__title',$clasShop['header'][1].'__icon page-icon _active');
$cont = '';
$cont .= '<header class="'.$clasShop['header'][2].'">
<div class="'.$clasShop['header'][2].'__top top-'.$clasShop['header'][2].'">';

$str = maket::div2Blockstr($Pth,$str0.$str1,'','top-'.$clasShop['header'][2].'__column','top-'.$clasShop['header'][2].'__contacts contacts-'.$clasShop['header'][2]);
//$contenTop = $contentShop['logo'].$str;
$cont .= maket::div3Blockstr($Pth,$contentShop['top'].$contentShop['logo'].$str,'top-'.$clasShop['header'][2].'__content '.$clasShop['main'][0],'','top-'.$clasShop['header'][2].'__column','top-'.$clasShop['header'][2].'__menu menu','');


$cont .= '</div>';   

$cont1 = ''; 
$cont1 .= '<div class="'.$clasShop['header'][2].'__bottom bottom-'.$clasShop['header'][2].'">';
if(isset($arrmain['typmen'][2])) $lozung = $arrmain['typmen'][2];
else $lozung = 'mn';
if( $lozung!= 'nmn')$navList = maket::viewdatapage($contentShop['nav'],$clasShop['navmenu'],$Pth,'','ul','','__item');
$cont1 .= maket::div3Blockstr($Pth,$navList,'bottom-'.$clasShop['header'][2].'__content '.$clasShop['main'][0],'','bottom-'.$clasShop['header'][2].'__column _right-bottom-'.$clasShop['header'][2],'bottom-'.$clasShop['header'][2].'__column _left-bottom-'.$clasShop['header'][2].'',$opts);

$cont1 .= '</div>';
$result = $cont.$cont1;
$result .= '</header>';
	return $result;
}

static function showShopCatMain($Pth,$contentShopCat,$clasCat){
	$glsr = glossary();
	//$dat4['dat'] = $sw->getData(0,'elements')['sections'];
	// if($contentShopCat == ''){
		// $dat4['dat'] = array('Беговые дорожки','Эллиптические тренажеры','Велотренажеры',
			// 'Гребные тренажеры','Вибромассежеры','Баскетбол','Массажные кресла',
			// 'Силовые тренажеры','Батуты','Детские городки','Дачная мебель','Уличные комплексы','Аксессуары');
			// foreach($dat4['dat'] as $k=>$val ) $dat4['href'][$k] = '#cat1';
			// foreach($dat4['dat'] as $key=>$val){
				// $dat4['sub'][$key]['dat'] = array('Всепогодный ','Для помещений ','Профессиональный ','Любительский ');
				// $dat4['sub'][$key]['href'] = array('#opt1','#opt2','#opt3','#opt4');
			// }
			// $dat4['sub'][1]['dat'] = array('Всепогодный ','Для помещений ','Профессиональный ');
			// $dat4['sub'][3]['dat'] = array('Всепогодный ','Для помещений ','Профессиональный ','Любительский ','Универсальный');
			// $dat4['sub'][1]['href'] = array('#opt1','#opt2','#opt3');
			// $dat4['sub'][3]['href'] = array('#opt1','#opt2','#opt3','#opt4','#opt5');
			// 
			// for($i=0;$i<13;$i++) {
				// $dat3[$i] = array($glsr['td'],$glsr['nt'],$glsr['sd']);
				// $dat4['label'][$i] = '';
				// for($j=0;$j<3;$j++) $dat4['label'][$i] .= maket::spanclasstr($dat3[$i][$j],$Pth,'item-product__label','div');
			// }  
			// $contentShopCat=$dat4;	
		// }
	$clasEl= $clasCat[1].'-'.$clasCat[0];
	$Icons = '<img class="icon-page__icon"style="width: 24px;"src="./images/icons/align-justify-solid.svg" alt="user-header">
	<span class="close">&times;</span>';
	$str = '';
	$str .= '<nav class="'.$clasCat[0].'__'.$clasCat[1].' '.$clasEl.'">
	<div class="'.$clasEl.'__content">';
	$str .= maket::div3Blockstr($Pth,$Icons,$clasEl.'__header',$glsr['ct'],'menu-page__title','menu-page__icon page-icon _active');
	$str .= '<div class="'.$clasEl.'__body">
    <ul class="'.$clasEl.'__list">';
$i=0;
$contentCat=array();
foreach($contentShopCat['dat'] as $i=>$val) { 
	$contentCat[$i] = maket::viewdatapage($contentShopCat['sub'][$i],'submenu-page',$Pth,'./','ul','','__link','__menu').show::shopCardItem($contentShopCat['label'][$i]);                
    $str .= '<li class="'.$clasEl.'__parent">
        <a href="'.$contentShopCat['href'][$i].'" class="'.$clasEl.'__link" id="men'.$i.'">'.$val.'</a>'
        .maket::div2Blockstr($Pth,$contentCat[$i],'',''.$clasEl.'__'.$clasCat[2].' '.$clasCat[2].'-'.$clasCat[0].'',$clasCat[2].'-'.$clasCat[0].'__item').
        '</li>';
    $i++;
}      
$str .= '</ul></div></div></nav>';
return $str;
}

static function showMainShop(){
//! адрес, телефон, сайт		
//!формируем классы и идентификаторы из макета

//! Загружаем данные формы

}

static function showSortShop(){
	$str = '<div class="actions-catalog__order order-catalog">
    <div class="order-catalog__label">Сортировать по:</div>
    <div class="order-catalog__select">
        <select>
            <option value="1" selected="selected" id="">По умолчанию</option>
            <option value="2">По цене</option>
            <option value="3">По названию</option>
        </select>
    </div>    
</div>';
return $str;
}

static function quantyPageItems(){
	$str = '<div class="navi-catalog__show show-catalog">
    <div class="show-catalog__label">На странице:</div>
    <div class="show-catalog__select">
        <select name="" id="" class="show">
            <option class="show-catalog__select__option" value="1">
                <span>9</span> 
            </option>
            <option class="show-catalog__select__option" value="2">18</option>
            <option class="show-catalog__select__option" value="3">32</option>
            <option class="show-catalog__select__option" value="4">60</option>
        </select>
    </div>
</div>';
return $str;
}

static function showListCatalog(){
	$str = '<div class="navi-catalog__pages">
    <div class="show__pagging">
        <a href="" class="pagging__arrow"></a>
        <ul class="pagging__list">
            <li><a href="" class="pagging__item _active">1</a></li>
            <li><a href="" class="pagging__item">2</a></li>
            <li><a href="" class="pagging__item">3</a></li>
            <li><a href="" class="pagging__item">4</a></li>
            <li><a href="" class="pagging__item">5</a></li>
            <li><a href="" class="pagging__item">...</a></li>
            <li><a href="" class="pagging__item">10</a></li>
        </ul>
        <a href="" class="pagging__arrow"></a>
    </div>   
</div>';
return $str;
}

static function filterProducts($arrCheck){
	$str = '';
	$str .='<form action="" class="filter__form">
    <div class="filter">
        <div class="filter__title _spollers">Фильтр товаров</div>
        <div class="filter__content _spollers">
            <div class="filter__body _spollers">';
                foreach($arrCheck['spoller'] as $k=>$val) {
                    if($val == '1')$spol = '_spoller';
                    else $spol = '';
                    $str .='<div class="fiter__section section-filter">';
                    $str .='<div class="section-filter__title '.$spol.'">'.$arrCheck['Title'][$k].'</div>';
                    if($k == 0) $str .='<div class="section-filter__body '.$spol.'">'.maket::showPriceFilter().'</div>';
                    if($k == 1) $str .='<div class="section-filter__body '.$spol.'">'.maket::showCompareFilter().'</div>';
                    else $str .='<div class="section-filter__body '.$spol.'">'.maket::checkParametrFilter($arrCheck['section'][$k]).'</div>';
                    $str .='</div>';
				}
	        $str .='</div>
	        <div class="filter__footer">
	            <button type="submit" class="filter__btn btn">Подобрать</button>
	        	<button type="reset" class="filter__btn btn btn_grey">Сбросить</button>
	        </div>
	    </div>
	</div>
	</form>';	
	return $str;	
}

static function showCardProduct(){
	$str = '<div class="body-product__actions actions-product">
    <div class="actions-product__row">
        <div class="actions-product__column">
            <div class="actions-product__price actions-product__price_old">64 990</div>
            <div class="actions-product__price actions-product__price">62 900</div>
        </div>
        <div class="actions-product__column">
            <div class="actions-product__quantity quantity">
                <div class="quantity__button_minus"></div>
                <div class="quantity__input">
                    <input  autocomplete="off" type="text" name="form[]" value="1">
                </div>
                <div class="quantity__button_plus"></div>
            </div>
        </div>
        <div class="actions-product__column">
            <a href="" class="actions-product__cart">
                <span>В корзину</span>
            </a>
        </div>
    </div>    
</div>';
	return $str;
}

static function CommentCardProduct(){
	$str = '<div class="body-product__include include-product">
    <div class="include-product__title">В стоимость товара включено:</div>
    <div class="include-product__items">
        <div class="include-product__item">
            <div class="include-product__icon">
                <img src="../images/icons/asterisk-solid.svg" alt="">
            </div>
            <div class="include-product__text">Бесплатная сборка</div>
        </div>
        <div class="include-product__item">
            <div class="include-product__icon">
                <img src="../images/icons/asterisk-solid.svg" alt="">
            </div>
            <div class="include-product__text">Бесплатная доставка</div>
        </div>
        <div class="include-product__item">
            <div class="include-product__icon">
                <img src="../images/icons/asterisk-solid.svg" alt="">
            </div>
            <div class="include-product__text">Гарантия</div>
        </div>
    </div>
</div>';
	return $str;
}
}