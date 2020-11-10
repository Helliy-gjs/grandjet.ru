<?php
class Maket extends Singleton {
	private $mass_zags=array();
	private $mass_zakl=array();
	
public function __construct($id,$tabl,$Site,$np,$uid){
	$arrmaket=array();
	$sw = Singleton::getInstance('StructureW');
	$this->db = $sw->db;
	$mass=$sw->getMaketable($id,'maket');


if ($mass){
		$arrmaket=$mass[0];	
		//echo $Site->ids.'-'.$arrmaket['numpage'].'-'.$tabl['pages'];
		$what=$sw->isthatsite($Site->domen, $arrmaket['numpage'], $tabl['pages']);
		//print_r($what);
		if ($what){
		foreach ($arrmaket as $key=>$value) $this->MainAr[$key]=$value;
		return 	$this->MainAr;
}
else  {
	//echo '<div сlass="info">макеты отсутствуют</div>';
	return 	false;
}
}
else {
	//show::infosh('нет макета '.$mass[0]['Maket']);
	//echo '<div сlass="info"> нет макета '.$mass[0]['Maket'].'</div>';
	return 	false;
}
}

public function readystylearr($arrmaket,$linkmaket,$mode){
	$arrmakstyle['Maket']=$arrmaket['Maket'];
	$arrmakstyle['styles']=explode('|',$arrmaket['style']);
	$arrmakstyle['styles']['link']=$linkmaket[2];
	$arrmakstyle['numparams']=explode('|',$arrmaket['numparams']);
	$arrmakstyle['numparams']['link']=$linkmaket[3];
	$arrmakstyle['fonts']=explode('|',$arrmaket['fonts']);
	$arrmakstyle['fonts']['link']=$linkmaket[4];
	$arrmakstyle['video']=explode('|',$arrmaket['video']);
	$arrmakstyle['video']['link']=$linkmaket[5];
	$arrmakstyle['effects']=explode('|',$arrmaket['effects']);
	$arrmakstyle['effects']['link']=$linkmaket[6];
	$arrmakstyle['scripts']=explode('|',$arrmaket['scripts']);
	$arrmakstyle['scripts']['link']=$linkmaket[7];
	$arrmakstyle['ids']=$arrmaket['ids'];
	$arrmakstyle['ids']['link']=$linkmaket[8];
	$arrmakstyle['numaket']=$arrmaket['numaket'];
	$arrmakstyle['numaket']['link']=$linkmaket[9];
	$arrmakstyle['numpage']=$arrmaket['numpage'];
	$arrmakstyle['numpage']['link']=$linkmaket[10];
	$arrmakstyle['idauthor']=$arrmaket['idauthor'];
	$arrmakstyle['idauthor']['link']=$linkmaket[11];
	if($mode->level<4) $arrmakstyle['link']='';
	else $arrmakstyle['link']=show::p_link($arrmakstyle);
	return $arrmakstyle;
}

public function  getSitetable($ids,$table='allsites'){
	$res = array();
	//$return = array();
	if($id > 0) {
	//echo "SELECT * FROM '$table' WHERE `numpage` = ^Ni; ";
	$res = $this->db->query("SELECT * FROM `allsites` WHERE `id`=^Ni;", $ids);
	if($res === null) {
				return false;
			}
	else {
	
	if(!is_array($res)) {
		echo 'данные страницы загружены';echo '<br/>';
		if ($res->domen <> '') $return[] = array('ids' => $res->ids,'uid' => $res->uid, 'domen' => $res->domen,'nmpage' => $res->nmpage,'types' => $res->types,'strucs' => $res->istrucs,'appoint' => $res->appoint,'ids' => $res->ids,'css' => $res->css, 'script' => $res->script, 'images' => $res->images,'passwad' => $res->passwad,'logad' => $res->logad,
		'bd' => $res->bd, 'host' => $res->host, 'port' => $res->port,'pages' => $res->pages,
		'news' => $res->news,'element' => $res->element,'structure' => $res->structure,'desc_site' => $res->desc_site);
			}
			else 
			{
		foreach($res as $val)
			if ($val->domen <> '') $return[] = array('ids' => $val->ids,'uid' => $val->uid, 'domen' => $val->domen,'nmpage' => $val->nmpage,'types' => $val->types,'strucs' => $val->istrucs,'appoint' => $val->appoint,'ids' => $val->ids,'css' => $val->css, 'script' => $val->script, 'images' => $val->images,'passwad' => $val->passwad,'logad' => $val->logad,
		'bd' => $val->bd, 'host' => $val->host, 'port' => $val->port,'pages' => $val->pages,
		'news' => $val->news,'element' => $val->element,'structure' => $val->structure,'desc_site' => $val->desc_site);
			}
			return $return;
		}
		//ElementsW::Showobjtype($return['pages'][0]);
		return false;
	}	
}

public static function readysitearr($Site,$np,$clas){ 
	$sw = Singleton::getInstance('StructureW');
	$mass=$sw->getSitetable($Site->ids);
	//$mass=$sw->getMaketable($id);
	//print_r($mass[0]);
	if ($mass){
		$arrmaket=$mass[0];	
		//echo $Site->ids.'-'.$arrmaket['ids'].'-'.$tabl['pages'];
		$what=$sw->isthatsite($Site->domen, $np, $Site->pages);
		//print_r($what);
		if ($what){
		$arrrr=$sw->getPagelinks($Site->ids,'allsites','ids');	
		foreach ($arrmaket as $key=>$value) $MainAr[$key]=$value;
		
		foreach($MainAr as $key=> $val){
			$arrsite[$key]=$val;
			}	
			$arrsite['images']=explode(';',$MainAr['images']);
			$arrsite['desc_site']=explode('|',$MainAr['desc_site']);	
			//$arrsite['link']['uid']=$arrrr[2];
			//$arrsite['link']['ids']=$arrrr[1];
			//$arrsite['link']['domen']=$arrrr[3];
			$arrsite['link']['nmpages']=$arrrr[4];
			//$arrsite['link']['types']=$arrrr[5];
			//$arrsite['link']['strucs']=$arrrr[6];
			//$arrsite['link']['appoint']=$arrrr[7];
			$arrsite['link']['images']=$arrrr[10];
			$arrsite['link']['scripts']=$arrrr[9];
			//$arrsite['link']['css']=$arrrr[8];
			//$arrsite['link']['passwad']=$arrrr[11];
			//$arrsite['link']['logad']=$arrrr[12];
			//$arrsite['link']['bd']=$arrrr[13];
			//$arrsite['link']['host']=$arrrr[14];
			//$arrsite['link']['port']=$arrrr[15];
			//arrsite['link']['pages']=$arrrr[16];
			//$arrsite['link']['news']=$arrrr[17];
			//$arrsite['link']['element']=$arrrr[18];
			//$arrsite['link']['structure']=$arrrr[19];
			//$arrsite['link']['desc']=$arrrr[20];
			$arrsite['clas']=$clas;
		//print_r($arrsite['uid']['link']);	
		//echo '<br>';
		//print_r($arrsite);
		return 	$arrsite;
}
else  {
	//echo '<div сlass="info">макеты отсутствуют</div>';
	return 	false;
}
}
else {
	//show::infosh('нет макета '.$mass[0]['Maket']);
	//echo '<div сlass="info"> нет макета '.$mass[0]['Maket'].'</div>';
	return 	false;
	
}
}

static public function MaketParPage($arr1,$arr2){
	$PathCont='';
	if(is_array($arr2) && is_array($arr1) )
	foreach($arr2  as  $key=>$val){
		if ($val<>'' && isset($arr1[$key]) && isset($arr2[$key])) $PathCont.=$arr1[$key].':'.$val.';';
		}
	elseif($arr2<>'')$PathCont.=$arr1.':'.$arr2.';';

return  $PathCont;
	}
	
private static function readyinitstyle($maket_name){
	$j=0;
	foreach($maket_name as $key=>$value){
		$v_sub[$j]='';
		$num_sub[$j]=substr_count($value, '|');
		if ($num_sub[$j]>0) for ($k=0;$k<$num_sub[$j];$k++) $v_sub[$j].='|';
		//else $v_sub[$j]='';
		$j++;
	}
return $v_sub;
}	
	
static function addnewGlbMaket($i,$mak,$auth,$is,$db,$clas='',$form='',$script=''){
	//print_r($db->init_data);
	$db=Singleton::getInstanceinit('DB',1);
	$ew = Singleton::getInstance('ElementsW');
	$n0=$ew->getIdElement('allmakets','id','Maket','Maket');
	$maket_name=$ew->view_table('allmakets','id',$n0);
	$v_sub=Maket::readyinitstyle($maket_name);
	//print_r($v_sub);
	$v_sub[2]='stylemain|regStyle|AuthStyle|recStyle|userStyle|editStyle';
	//$v_sub[3]='display|flex-direction|flex-wrap|flex-flow|order|flex-grow|flex-shrink|flex-basis|justify-content|align-items|align-self|align-items|align-content';
	//$v_sub[4]='display|grid-template-columns|grid-template-rows|grid-auto-rows|grid-auto-columns|grid-column-start| grid-column-end|grid-row-start|grid-row-end| grid-column-gap|grid-row-gap|grid-area|grid-cell';
	$v_sub[5]='1;1.2;1.5;1.7;2;3;4;5|14px;16px;14px;24px;32px;46px;32px;60px;|0.1;0.2;0.5;0.8;0.9;1|0.1;0;2;0.5;0.8';
	$v_sub[6]='1|2|3|4|5|6|';
	$v_sub[7]='1|2|3|';
	$v_sub[8]='1|2|3|4|5|6|7|8|9|';
	if($script === '') $v_sub[9]='jquery.min|ddsmoothmenu|jquery-1.3.2.min|jquery.easing.1.3|jquery.kwicks-1.5.1.pack|common';
	else $v_sub[9] = $script;
	if($clas === '')$v_sub[10]='|main_container,main-header,main_menu,main_wrapper,sidebareL,sidebareR,sidebareC,wrapper,header-button,poisk,swpr,main_footer,sechead,edit,menu,menudown,item,header-content,button,#headline,logo,user,admin,main_banner|global';
	else $v_sub[10]='|'.$clas.'|general';
	if($form === '')$v_sub[11]='|||||';
	else $v_sub[11]=$form;
	//print_r($v_sub);
	$res=$db->query('SELECT `Maket`,`ids`,`author_mak` FROM  `allmakets` WHERE  `Maket`=^Ns  AND `author_mak`=^Ni  AND `ids`=^Ni ;',$mak,$auth,$is);
	//if($res === null)echo 'макетов нет';
	//else print_r($res);

	if($res === Null){
		$query ="INSERT INTO `allmakets` (`id`, `Maket`, `styles`, `flex`, `grid`, `numparams`, `fonts`, `video`, `effects`, `scripts`, `desc`, `ids`, `forms`, `author_mak`) VALUES
		('".$i."', '".$mak."', '".$v_sub[2]."', '".$v_sub[3]."', '".$v_sub[4]."', '".$v_sub[5]."', '".$v_sub[6]."', '".$v_sub[7]."', '".$v_sub[8]."', '".$v_sub[9]."','".$v_sub[10]."', '".$is."', '".$v_sub[11]."', '".$auth."');";
		//echo '<pre>';
		//echo $query;
		//echo '</pre>';
		$db->query($query);
	}
	//else echo 'there is this maket';
}
	
static function addnewStMaket2($id,$im,$np,$is,$iu,$db,$maket_clas=''){
//стандартные классы макета
$ew = Singleton::getInstance('ElementsW');
	$i=$id;
	$n0=$ew->getIdElement('maket','id','Maket','Maket');
	$maket_name=$ew->view_table('maket','id',$n0);
	$maket_style=$ew->view_table('allmakets','id',$im);
	//var_dump($maket_style);
	$pp8=explode('|',$maket_style->desc);
	if ($pp8[1]<>'')$Maket_site=explode(',',$pp8[1]);
	else $Maket_site=array(0=>'main_container',1=>'main-header',2=>'main_menu',3=>'main_wrapper',4=>'sidebareL',5=>'sidebareR',6=>'sidebareC',7=>'wrapper',8=>'header-button',9=>'poisk',10=>'swpr',11=>'main_footer',12=>'sechead',13=>'edit',14=>'menu',15=>'menudown',16=>'item',17=>'header-content',18=>'button',19=>'#headline',20=>'logo',21=>'user',22=>'admin',23=>'footer',24=>'main_banner',25=>'top_line');
	if(is_array($maket_clas))foreach($maket_clas as $val) $Maket_site[]=$val;
	$v_sub=Maket::readyinitstyle($maket_name);
	foreach ($Maket_site as $val){
	if(!$db->query('SELECT `id`,`Maket`,`numpage`,`ids`,`numaket`,`idauthor` FROM  `maket` WHERE  `Maket`=^Ns  AND  `numaket`=^Ni  AND  `ids`=^Ni ;',$val,$im,$is))
	{
		$db->query('INSERT INTO `maket`  VALUES (^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni, ^Ni);', $i,$val, $v_sub[2],$v_sub[3],$v_sub[4],$v_sub[5],$v_sub[6],$v_sub[7],$v_sub[8],$v_sub[9],$is,$np,$im,$iu);
		$i++;
	}
	}
	
}	

static function addnewStMaket($id,$im,$np,$is,$iu,$db){
//стандартные классы макета
	$i=$id;
	$Maket_site=array('container','main_header','main_menu','main_wrapper','sidebareL','sidebareR','sidebareC','wrapper','header-button','poisk','swpr','main_footer','sechead','edit','menu','menudown','item','header-content','button','#headline');
	foreach ($Maket_site as $val){
	if(!$db->query('SELECT `id`,`Maket`,`numpage`,`ids`,`numaket`,`idauthor` FROM  `maket` WHERE  `Maket`=^Ns  AND  `numpage`=^Ni  AND  `ids`=^Ni ;',$val,$np,$is))
	{
		$db->query('INSERT INTO `maket` (`id`,`Maket`,`numpage`,`ids`,`numaket`,`idauthor`) VALUES (^Ni,^Ns,^Ni,^Ni,^Ni, ^Ni);', $i,$val,$np,$is,$im,$iu);
		$i++;
	}
	}
	
}

private static function addinAllMaket($id,$nm,$is,$style,$db){
	
	$this->db->query('INSERT INTO `allmakets` (`id`,`Maket`,`ids`,`styles`) VALUES (^Ni,^Ns);', $id,$nm,$is,$style);
}

private static function addonestyle($style,$Pth){
	$ew = Singleton::getInstance('ElementsW');
	$db=Singleton::getInstance('DB');
	//print_r($db_unit);
	$id=$ew->getscountab('maket','id', 'f')+1;
	$n0=$ew->getIdElement('maket','id','Maket','Maket');
	$maket_name=$ew->view_table('maket','id',$n0);
	$v_sub=Maket::readyinitstyle($maket_name);
	if(!isset($Pth['adm']['ids']))return false;
	if(!$db->query('SELECT `id`,`Maket`,`numpage`,`ids`,`numaket`,`idauthor` FROM  `maket` WHERE  `Maket`=^Ns  AND  `numpage`=^Ni  AND  `ids`=^Ni AND  `numaket`=^Ni;',$style,$Pth['adm']['np'],$Pth['adm']['ids'],$Pth['adm']['idm'])){
	//show::infosh('Добавляем стиль '.$style);
	if ($style<>'')$res=$db->query('INSERT INTO `maket`  VALUES (^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni, ^Ni);', $id,$style, $v_sub[2],$v_sub[3],$v_sub[4],$v_sub[5],$v_sub[6],$v_sub[7],$v_sub[8],$v_sub[9],$Pth['adm']['ids'],$Pth['adm']['np'],$Pth['adm']['idm'],$Pth['adm']['uid']);	
	if(isset($res))return true;
	}
	else return false;
	}

static function initAllmaketsite($is,$id){
	
	$type_input=array(0=>'cont', 1=>'land', 2=>'gall', 3=>'blog', 4=>'mag', 5=>'cat',6=>'mob' ,7=>'tw', 8=>'fb');
	$this->id=$id;
	foreach($type_input as $val){
		Maket::addinAllMaket($this->id,$val,$is,'style'.$val,Singleton::getInstance('DB'));
		$this->id++;
	}
	}
	
static function divclass($clas='',$Pth='',$style='',$prefix='',$selector='div',$comment='',$s='',$h=''){
	//show::infosh($Pth['gall1-gall']);
	
	if (!isset($Pth[$clas]['styles']) && isset($Pth['adm'])) {
		if(is_array($Pth['adm']))$res=Maket::addonestyle($clas,$Pth);
	}
	
	$stl='';
	if($s<>'') $prefix.=' '.$s;
	if($h<>'') $prefix.=' '.$h;
	if(isset($Pth['adm'])){
		if($Pth['adm']<>'')$ttl=$clas.':'.$prefix;
		else $ttl=$comment;
	}
	else $ttl='';
	
	if (!strstr($clas,'#')) {
		if($clas <> '') $cls='class="'.trim($clas.$prefix).'"'; 
	}
	else {
		if ($prefix<>'') $cls='id="'.trim(substr($clas,1)).'" '.'class="'.trim($prefix).'"';
		else $cls='id="'.trim(substr($clas,1)).'"'; 
		}	
	//if(!isset($Pth[$clas]['styles']))$Pth[$clas]['styles']='';
	
	
	if ($style=='' && $clas == '' && !isset($Pth[$clas]['styles'])) {
		if($prefix<>'') echo '<'.$selector.' class="'.$prefix.'" title="'.$ttl.'">';
		else $return='<'.$selector.'">';
		return;
	}
	else {
	
	if($style== '1' && $Pth=='') $stl='';
	elseif(isset($Pth[$clas]['styles'])&& $Pth[$clas]['styles']<>'' ) $stl='style="'.$style.$Pth[$clas]['styles'].'"';
	elseif($style<>'' ) $stl='style="'.$style.'"';
	//elseif ($style=='' &&  $clas <> '' &&  $Pth[$clas]['styles']=='') $stl='<'.$selector.' '.$clas.' 3title="'.$ttl.'"/>';
	elseif(!isset($Pth[$clas]['styles'])) {
		echo '<'.$selector.' '.$cls.' title="'.$comment.'" style="'.$style.'">';
		return;
	}
	
	echo '<'.$selector.' '.trim($cls).' title="'.$ttl.'" '.$stl.' >';
	}
}

static function divclasstr($clas,$Pth,$style='',$prefix='',$selector='div',$comment='',$s='',$h=''){
	if($clas ==='' && $style ==='')return '<'.$selector.'>';
	if (!isset($Pth[$clas]['styles']) && isset($Pth['adm'])) {
		if(is_array($Pth['adm']))$res=Maket::addonestyle($clas,$Pth);
	}
	
	$stl='';
	if($s<>'') $prefix.=' '.$s;
	if($h<>'') $prefix.=' '.$h;
	$ttl='';
	if(isset($Pth['adm'])){
		if(!isset($Pth['adm']['noedit']))$ttl=$clas.$prefix;
		else $ttl=$comment;
	}
	if (!strstr($clas,'#')) {
		if($clas <> '') $cls=trim('class="'.$clas.$prefix.'"'); 
		elseif($prefix<>'')$cls=trim('class="'.$prefix.'"');
		else $cls='';
	}
	else {
		if ($prefix<>'') $cls=trim('id="'.trim(substr($clas,1)).' " '.'class="'.$prefix.'"');
		else $cls='id="'.trim(substr($clas,1)).'"'; 
		}	

	if($Pth=='' || !isset($Pth[$clas]['styles'])) {
		$return='<'.$selector.' '.$cls.' title="'.$ttl.'" style="'.$style.'">';
		return $return;
	}
	elseif ($style ==='' && $clas === '' && $Pth[$clas]['styles']===''){
		if($prefix<>'') $return='<'.$selector.' class="'.$prefix.'" title="'.$ttl.'">';
		else $return='<'.$selector.'">';
		}
	elseif ($style ==='' && $cls <> '' && $Pth[$clas]['styles']=='') $return='<'.$selector.'  '.$cls.'" title="'.$ttl.'">';	
	else {
	
	if($style== '1' && $Pth[$clas]['styles']=='') $stl='';
	elseif($Pth[$clas]['styles']<>'') $stl='style="'.$style.$Pth[$clas]['styles'].'"';
	elseif($style<>'' ) $stl='style="'.$style.'"';
	//$ttl='title="'.$clas.$prefix.'"'; 
	
	
	$return='<'.$selector.' '.trim($cls).' title="'.$ttl.'" '.$stl.'>';
	}
	return $return;
}

static function spanclasstr($str,$Pth,$clas='',$selector='span',$comment='',$style='',$prefix=''){
	$res=Maket::divclasstr($clas,$Pth,$style,$prefix,$selector,$comment).$str.'</'.$selector.'>';
	return $res;
}

static function divcltr($str,$Pth,$clas=''){
	$res=Maket::spanclasstr($str,$Pth,$clas,'div');
	return $res;
}

static function divcl($str,$Pth,$clas=''){
	$res=Maket::spanclass($str,$Pth,$clas,'div');
	echo $res;
}

static function spanclass($str,$Pth,$clas='',$selector='span',$comment='',$style='',$prefix=''){
	Maket::divclass($clas,$Pth,$style,$prefix,$selector,$comment);
	echo $str.' </'.$selector.'>';
}	

static function getvendor($table){
$retu=array();
$sql="select `vendor` from $table;";
//echo $sql;echo '<br>';
$find=$this->db->query($sql);
if (!$find == null){
		foreach ($find as $val){
			$retu[] = $val->vendor;
			}
$ac=array_count_values($retu);
$return[]='';
while ($elem=each($ac)) {
$return[]=$elem['key'];	
}
}
//else echo 'не найдено';
asort($return);
return $return;
}	

static function selmenstr($clas,$arropt,$chice,$img,$num,$ch='',$tich='Найти'){
	
	$str='<span>';
	$str.='<option value="" class="label">'.$arropt[$num].' :</option>';
		$str.='<select class="'.$clas.'" name="'.$ch.'">';
		$i=0;
		
		foreach($arropt as $key=>$val){	
			if(!is_array($chice))	$chice[$i]=$key;
			if ($i == $num ) $str.='<option selected name="'.$ch.'" value="'.$num.'">'.$val.'</option>';
			else $str.='<option value="'.$chice[$i].'">'.$val.'</option>';
			$i++;
		}
	$str.='</select>';	
	if($ch != ''){
		if(file_exists($img)) $str.='</select></span><span><input title="'.$tich.'" class="poisk-img" name="'.$ch.'" value="'.$ch.'" type="image" src="'.$img.'"/></span>';
	else $str.='<span><input class="'.$clas.'-butt" title="'.$tich.'" type="submit" value="'.$img.'"></span>';	
	}
	return $str;
	}

static function selmen($arropt,$chice,$img,$num,$ch='chice',$tich='Найти'){
	echo '<span>';
		echo '<select class="poisk-'.$ch.'" name="'.$ch.'">';
		$i=0;
		
		foreach($arropt as $key=>$val){	
			if(!is_array($chice))	$chice[$i]=$key;
			if ($i == $num ) echo '<option selected name="'.$ch.'" value="'.$num.'">'.$val.'</option>';
			else echo '<option value="'.$chice[$i].'">'.$val.'</option>';
			$i++;
		}
	echo '</select>';	
	if(file_exists($img)) echo '</select></span><span><input title="'.$tich.'" class="poisk-img" name="'.$ch.'" value="'.$ch.'" type="image" src="'.$img.'"/></span>';
	else echo '<span><input class="poisk-butt" title="'.$tich.'" type="submit" value="'.$img.'"></span>';	
	return $ch;
	}

static function getscountab($tab,$key,$mode){
		$db=Singleton::getInstance('DB');
		$order = ' ORDER BY ';
		$order .= '`numpage`';
		$order .= ' DESC ';
		//print_r($Site);
		if ($key <>''&& $mode =='f') {
			$d="SELECT * FROM `$tab` ORDER BY $key DESC";
			$res=$db->query($d);
		}
		//else { 
		//if ($tab == 'pages') $d='SELECT * FROM `pages` WHERE `site`=^Ns;,'.$Site->domen;
		elseif($mode == 't' && strstr($tab,'pages'))  {
			//$Site=$user->initbdF($_SERVER['HTTP_HOST']);
			$d="SELECT * FROM `$tab` WHERE `$key`=^Ns $order;";
			//echo 'зашли '.$d.','.$_SERVER['HTTP_HOST'];
			$res=$db->query($d,$_SERVER['HTTP_HOST']);
			//print_r($res);
			$key='numpage';
			}
		else {
			$d="SELECT * FROM `$tab` ";
			$mode='c';
			$res=$db->query($d);
			}
//echo '<br>'.$d.','.$GLOBALS['Site']->domen;
$l=0;
if (count($res) >1) {
while ($element =each($res)) {
	$result[$l]=$element['value'];
	$l++;
	}	
}
else $result[0]=$res;
//echo 'res '.$result[0]->$key;
//echo '<br>';
//print_r($result[0]);
if ($mode == 'c')	return count($res);				
else return $result[0]->$key;
}

static public function part_name($str,$dlt='='){
	if(strstr($str,$dlt)) $res=explode($dlt,$str);
	else $res[0]=$str;
	return $res[0];
}

static public function part_text($str,$n=1,$dlt='='){
	if(strstr($str,$dlt)) {
		$res=explode($dlt,$str);
		if(isset($res[$n]))return $res[$n];
	}
	else return $str;
}

static public function part_texts($str){
	if(strstr($str,'=')) $res=explode('=',$str);
	else $res[0]=$str;
	return $res;
}

static function getnamepage($pagename,$dlt='='){
	$l=explode('|',$pagename);
	if (!strstr($pagename,'.jpg') && !strstr($pagename,'.png') && !strstr($pagename,'.gif'))
		{
	if (count($l)>3)$result[3]=$l[3];
	elseif(count($l)>2) $result[2]=$l[2];
	elseif(count($l)>1) $result[1]=$l[1];
	else $result[0]=$l[0];
}
	else 
	{
	if (count($l)>2) $result[2]=$l[2];
	elseif(count($l)>1) $result[1]=$l[1];
	else $result[1]=$l[0];
	}
	$lst11=array_keys($result);
	$lst0=$result[$lst11[0]];
return Maket::part_name($lst0,$dlt);
}

static function getallpages($tab){
		$db=Singleton::getInstance('DB');
		$site=$_SERVER['HTTP_HOST'];
		$d="SELECT `numpage`, `namep` FROM $tab WHERE `site`=^Ns;";
		$res=$db->query($d,$site);
		if (count($res) >1) {
		$l=0;	
		//print_r($res);
		while ($element =each($res)) {
			$result['num'][$l]=$element['value']->numpage;
			if (strstr($element['value']->namep,'|')) {
				$NmPg=explode('|',$element['value']->namep);
				if(strstr($NmPg[2],':'))$NmPg[2]=Maket::getnamepage($element['value']->namep,':');
				if (is_array($NmPg) && isset($NmPg[2])) $result['nam'][$l]=$result['num'][$l].' '.$NmPg[2];
				elseif(!isset($NmPg[2]) && isset($result['num'][$l])) $result['nam'][$l]='страница '.$element['value']->numpage;
				elseif(isset($result['num'][$l])) $result['nam'][$l]=$result['num'][$l].' '.$NmPg[0];
				}
			else  $result['nam'][$l]=$element['value']->numpage.$element['value']->namep;
			if ($result['nam'][$l] == '') $result['nam'][$l]='страница '.$element['value']->numpage;
			$l++;
		}	
	}
	else $result[0]=$res->namep;
	return $result;
	}
	
static function getallstyles($tab,$ids,$idm,$np=0){
		$db=Singleton::getInstance('DB');
		
		if($np<>0){
			$d="SELECT `id`, `Maket` FROM $tab WHERE `ids`=^Ni AND `numpage`=^Ni AND `numaket`=^Ni;";
			$res=$db->query($d,$ids,$np,$idm);
		}
		else {
			$d="SELECT `id`, `Maket` FROM $tab WHERE `ids`=^Ni;";
			$res=$db->query($d,$ids);
		}
		if (count($res)<>0){
		if (count($res) >1) {//так как 1 занят по плейсхолдеры
		$l=0;	
		//print_r($res);
		while ($element =each($res)) {
			$result['id'][$l]=$element['value']->id;
			if (strstr($element['value']->Maket,'|')) {
				$NmPg=explode('|',$element['value']->Maket);
				//$result['nam'][$l]=$result['num'][$l].' '.substr($NmPg[1],0,15);
				if (is_array($NmPg) && isset($NmPg[2])) $result['Maket'][$l]=$result['id'][$l].' '.$NmPg[2];
				elseif($NmPg[2]=='') $result['Maket'][$l]='страница '.$element['value']->id;
				else $result['Maket'][$l]=$result['id'][$l].' '.$NmPg[0];
				}
			else  $result['Maket'][$l]=$element['value']->id.$element['value']->Maket;
			if ($result['Maket'][$l] == '') $result['Maket'][$l]='style '.$element['value']->Maket;
			$l++;
		}	
	}
	else {$result['Maket'][0]=$res->Maket;$result['id'][0]=$res->id;}
	return $result;
	}
	else return false;
	}	
	
static function selectors($arr,$Pth,$vendors,$mode='',$pth0='',$w='Найти',$t='text',$s=10,$m=50){
$tabl=$arr['tab'];	
	$size_pars1=12;
if ($numelem>0 && $arr['typmen'][5]<> 'nbf' && $mode==1) {
	$numelem=Maket::getscountab($tabl['elem'],'id','c');
	$numpage=$arr['nump'];	
	if (isset($_GET['vend'])) $vend=$_GET['vend'];
	else $vend='';	
	if(isset($Pth['global']['Sizes'][1]))$size_pars1=$Pth['global']['Sizes'][1];
	if (isset($_GET['np'])) $current=$_GET['np'];
	elseif (isset($_POST['np'])) $current=$_POST['np'];
	else $current=$numpage;	
	echo '<form style="align:left;" method="post" action="'.$pth0.'?np='.$numpage.'" target="_self">';
	//echo ' <span style="font-size:'.$size_pars1.'px;" >';
	Maket::spanclass(Maket::divclasstr('poisk-'.$Pth['global']['idmen'],$Pth,'','','input name="poisk-chice" placeholder="'.$w.'" maxlength="'.$m.'" size="'.$s.'" type="'.$t.'"').'</input>',$Pth,'poisk-chice');
	//<input class="poisk" name="poisk" placeholder="Найти" maxlength="20" size="15" type="text" /></span>';
	
	Maket::selmen($vendors,$vend,'./images/searchh.gif','','vend');
	echo '</form>';
}
elseif($mode==2){
	
	$allpags=Maket::getallpages('pages');
	$title_chice='Перейти';
	
	if (isset($_POST['chice'])) $current=$_POST['chice'];
	elseif(isset($_GET['np'])) $current=$_GET['np'];
	else $current=$numpage;
	$page='?';
	
	foreach($_GET as $key=>$val) {
			if($val)$ad='=';
			else $ad='';
			if($key<>'np')$page.=$key.$ad.$val.'&';
			
	}
	
	echo '<div style="display:flex; justify-content: center;">';
	Maket::divclass('contpage',$Pth,'display:flex; justify-content: center;');
	Maket::divclass('confmak',$Pth,'font-size:'.$size_pars1.'px');
	//echo '<div><span style="font-size:'.$size_pars1.'px;">';
	echo '<span>';
	Maket::divclass('confmak',$Pth,'font-size:'.$size_pars1.'px');
	if (isset($_POST['chice'])) echo '<form style="align:left;  " method="post" action="'.$pth0.'/'.$page.'" target="_self">';
	else echo '<form style="align:left;  " method="post" action="'.'./'.$page.'" target="_self">';
	Maket::selmen($allpags['nam'],$allpags['num'],'Page',($current-1),'chice',$title_chice);
	echo '</form></span></div></div>';
}
elseif($mode==3){
	$allsts=StructureW::getallstyles('maket',$Pth['adm']['ids'],$Pth['adm']['idm'],$Pth['adm']['np'],1);
	
	if ($allsts){
		//echo '<div><span style="font-size:'.$size_pars1.'px">';
		echo '<span>';
		Maket::divclass('confmak',$Pth,'font-size:'.$size_pars1.'px');
		if (isset($_POST['chice1'])) $current=$_POST['chice1'];
		else $current=$allsts['id'][0];
		$title_chice='изменить стиль ';
		echo '<form style="align:left;  " method="post" action="'.$pth0.'/'.$arr['hrefp'][0].'?editp=ok&tab=maket&par='.$current.'" target="_self">';
		$chice=Maket::selmen($allsts['Maket'],$allsts['id'],'Style',$current,'chice1',$title_chice);
		echo '<a title="добавить стиль" href="'.$arr['hrefp'][0].'?editp=new&tab=maket">  +</a>';
		echo '</form></span>';
		echo '<a title="добавить стиль" href="'.$arr['hrefp'][0].'?np='.$numpage.'&editp=new&tab=maket">  + style</a>';
		echo '</div>';
		}	
	}
	elseif($mode==4){
		$title_chice='изменить конфигурацию страницы';
		$numpage=$arr['nump'];
		$db = Singleton::getInstance('DB');	
		$res = $db->query('SELECT `id`,`name` FROM `configp` ');
		if($res){
		if(is_array($res))foreach ($res as $val ){
			$allcnfg['id'][]=$val->id;
			if(strstr($val->name,'|')){
				$arrcnm=explode('|',$val->name);
				$allcnfg['Maket'][]=$arrcnm[0];
			}
			else $allcnfg['Maket'][]=$val->name;
		}
		else {$allcnfg['id'][0]=$res->id;$allcnfg['Maket'][0]=$res->name;}
		//echo '<div><span style="font-size:'.$size_pars1.'px">';	
		//echo '<span>';
		Maket::divclass('confmak',$Pth,'font-size:'.$size_pars1.'px');
		if (isset($_POST['confp'])) $current=$_POST['confp']-1;
		else $current=$arr['conf'][0]-1;//$allcnfg['id'][0];
		echo '<form style="align:left;  " method="post" action="'.'./'.$arr['hrefp'][0].'?editp=ok&np='.$numpage.'&konstrS" target="_self">';
		$chice=Maket::selmen($allcnfg['Maket'],$allcnfg['id'],'Config',$current,'confp',$title_chice);
		//echo '<input type="submit" value="Изменить на странице"/>';
		echo '</form>';
		echo '<a title="добавить конфигурацию" href="./?editp=new&tab=configp">  +</a>';
		echo '<a href="./'.$arr['hrefp'][0].'?np='.$numpage.'&editp=ok&tab=configp&par='.$current.'">set</a>';
		echo '</div>';
		}
	}
	elseif($mode==5){
		$title_chice='изменить конфигурацию сайта';
		$numpage=$arr['nump'];
		$db = Singleton::getInstance('DB');	
		$res = $db->query('SELECT `id`,`name` FROM `configs` ');
		if($res){
		if(is_array($res))foreach ($res as $val ){
			$allcnfg['id'][]=$val->id;
			if(strstr($val->name,'|')){
				$arrcnm=explode('|',$val->name);
				$allcnfg['Maket'][]=$arrcnm[0];
			}
			else $allcnfg['Maket'][]=$val->name;
		}
		else {$allcnfg['id']=$res->id;$allcnfg['Maket']=$res->name;}
		//echo '<div><span style="font-size:'.$size_pars1.'px">';
		//echo '<span>';
		Maket::divclass('confmak',$Pth,'font-size:'.$size_pars1.'px');
		if (isset($_POST['confs'])) $current=$_POST['confs']-1;
		else $current=$allcnfg['id'][0]-1;
		echo '<form style="align:left;  " method="post" action="'.'./'.$arr['hrefp'][0].'?np='.$numpage.'&konstrS" target="_self">';
		$chice=Maket::selmen($allcnfg['Maket'],$allcnfg['id'],'Config',$current,'confs',$title_chice);
		echo '<a title="добавить конфигурацию" href="./?editp=new&tab=configs">  +</a>';
		echo '</form>';
		echo '<a href="./'.$arr['hrefp'][0].'?np='.$numpage.'&editp=ok&tab=configs&par='.$current.'">set</a>';
		echo '</div>';
		}
	}
	elseif($mode==6){
		$title_chice='изменить конфигурацию макета';
		$numpage=$arr['nump'];
		$db = Singleton::getInstance('DB');	
		$res = $db->query('SELECT `id`,`name` FROM `configm` ');
		if($res){
		if(is_array($res))foreach ($res as $val ){
			$allcnfg['id'][]=$val->id;
			if(strstr($val->name,'|')){
				$arrcnm=explode('|',$val->name);
				$allcnfg['Maket'][]=$arrcnm[0];
			}
			else $allcnfg['Maket'][]=$val->name;
		}
		else {$allcnfg['id']=$res->id;$allcnfg['Maket']=$res->name;}
		//echo '<div><span style="font-size:'.$size_pars1.'px">';	
		//echo '<span>';
		Maket::divclass('confmak',$Pth,'font-size:'.$size_pars1.'px');
		if (isset($_POST['confm'])) $current=$_POST['confm']-1;
		else $current=$allcnfg['id'][0]-1;
		echo '<form style="align:left;  " method="post" action="'.'./'.$arr['hrefp'][0].'?np='.$numpage.'&konstrS" target="_self">';
		$chice=Maket::selmen($allcnfg['Maket'],$allcnfg['id'],'Config',$current,'confm',$title_chice);
		echo '<a title="добавить конфигурацию" href="./?editp=new&tab=configm">  +</a>';
		echo '</form>';
		echo '<a href="./'.$arr['hrefp'][0].'?np='.$numpage.'&editp=ok&tab=configm&par='.$current.'">set</a>';
		echo '</div>';
		}
	}
	elseif($mode==7){
		$title_chice='изменить конфигурацию страницы';
		$numpage=$arr['nump'];
		$db = Singleton::getInstance('DB');	
		$res = $db->query('SELECT `id`,`name` FROM `configp` ');
		if($res){
		if(is_array($res))foreach ($res as $val ){
			$allcnfg['id'][]=$val->id;
			if(strstr($val->name,'|')){
				$arrcnm=explode('|',$val->name);
				$allcnfg['Maket'][]=$arrcnm[0];
			}
			else $allcnfg['Maket'][]=$val->name;
		}
		else {$allcnfg['id']=$res->id;$allcnfg['Maket']=$res->name;}
		//echo '<div><span style="font-size:'.$size_pars1.'px">';	
		//echo '<span>';
		Maket::divclass('confmak',$Pth,'font-size:'.$size_pars1.'px');
		if (isset($_POST['confp'])) $current=$_POST['confp']-1;
		else $current=$allcnfg['id'][0]-1;
		echo '<form style="align:left;  " method="post" action="'.'./'.$arr['hrefp'][0].'?np='.$numpage.'&konstrS" target="_self">';
		$chice=Maket::selmen($allcnfg['Maket'],$allcnfg['id'],'Config',$current,'confp',$title_chice);
		//echo '<input type="submit" value="Изменить на странице"/>';
		echo '</form>';
		echo '<a title="добавить конфигурацию" href="./?editp=new&tab=configp">  +</a>';
		echo '<a href="./'.$arr['hrefp'][0].'?np='.$numpage.'&editp=ok&tab=configp&par='.$current.'">set</a>';
		echo '</div>';
		}
	}
}

static  function currconfig ($tab,$field,$id=''){
	$allcnfg=array();
	$db = Singleton::getInstance('DB');	
		if(intval($id))$res = $db->query("SELECT `id`,`name` FROM $tab WHERE $field =^Ni;",$id);
		else $res = $db->query("SELECT `id`,`name` FROM $tab ");
		
		if($res){
		if(is_array($res))foreach ($res as $val ){
			$allcnfg['id'][]=$val->id+0;
			if(strstr($val->name,'|')){
				$arrcnm=explode('|',$val->name);
				$allcnfg['Maket'][]=$arrcnm[0];
			}
			else $allcnfg['Maket'][]=$val->name;
		}
		else {
			$allcnfg['id'][]=$res->id+0;
			if(strstr($res->name,'|')){
				$arrcnm=explode('|',$res->name);
				$allcnfg['Maket'][]=$arrcnm[0];
			}
			else $allcnfg['id'][]=$res->id;$allcnfg['Maket'][]=$res->name;
			
			}
		
		return $allcnfg;		
		}
		else return false;
}

static function showbackground($arr,$MP,$Pth,$selector='header',$selector1='div',$content){
	$img=$arr['clas']['img'].$arr['namep'][0];
	if(isset($arr['namep'][0])) if($Pth['type_access']=='local')echo $arr['link']['namep'][0];
	echo $content;
	/*Maket::divclass($MP[1],$Pth,'background-image: url('.$img.');',' grid',$selector);
	Maket::showmaket($arr,$MP,$Pth,$vendors,$service,$selector1);
	Maket::divclass($MP[8],$Pth);
	maket::showblocks($arr,$Pth);*/
	echo '</'.$selector1.'>';
	echo '</'.$selector.'>';
	
}

static function showblocks($arr,$Pth){
	switch ($arr['idmen'][0]){
		case 'land':{
			if ($arr['typmen'][2] == 'bt') {
				show::menumain($arr,$Pth,'butt',$arr['idmen'][0],0,4);
			}
			elseif($arr['typmen'][1] == 'mn'){
				show::menush($arr,$Pth,'list');	
			}	
			elseif($arr['typmen'][6]<>'sw'){
				show::menush($arr,$Pth,'list');	
				show::accordsh('Y','imgs',$arr,$Pth,'imgt',3);
			}
			else {
				show::shadowsh($arr,'imgt','list',0.1,1,1,0.5,100);	
			}
			break;
		}
	}
}

static function showheaderland($Pth,$clas_head,$arr_head,$clas){
	
	$nopt=count($clas_head);
	foreach ($clas_head as $key=>$val){
		if($val==$clas)$mode=1;
		else $mode=0;
		if($key<$nopt)Maket::showlogo($val,$arr_head[$key],$Pth,$mode);
	}
	
	return $nopt;

	
	/*$img=$arr['clas']['img'].$arr['namep'][0];
	Maket::divclass($MP[1],$Pth,'background-image: url('.$img.');',' grid',$selector);
	Maket::showmaket($arr,$MP,$Pth,$vendors,$service);
	Maket::divclass($MP[8],$Pth);
	if ($arr['typmen'][2] == 'bt') {
			show::menumain($arr,$Pth,'butt',$arr['idmen'][0],0,4);
			}
	elseif($arr['typmen'][1] == 'mn'){
			show::menush($arr,$Pth,'list');	
	}	
	elseif($arr['typmen'][6]<>'sw'){
		show::menush($arr,$Pth,'list');	
		show::accordsh('Y','imgs',$arr,$Pth,'imgt',3);
	}
	else {
		show::shadowsh($arr,'imgt','list',0.1,1,1,0.5,100);	
		
	}
	echo '</'.$selector1.'>';
	echo '</'.$selector.'>';
	//show::accordsh('N','imgs',$arr,$Pth,'imgt',6);*/
}

static function showemptyblock($Pth,$clas='',$w='200px',$h='100px',$color='#999'){
	echo Maket::divclasstr($clas,$Pth,'style="position: relative;background-color:'.$color.';width:'.$w.';height:'.$h.' ;"').'</div>';
}

static function showmaketempty($arr,$ownerdata,$service,$Pth,$MP,$style){
	Maket::divclass($MP[17].'-'.$arr['idmen'][0],$Pth,$style,' grid');
	Maket::divclass($MP[8],$Pth,$style);
	Maket::divclass($MP[12],$Pth,$style,' user','div');
		echo $ownerdata;
	echo '</div>';
	Maket::divclass($MP[12],$Pth,$style,' logo','div');
	echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			echo '<img class="logo" src="./images/logo.png"/>';
			echo '</div>';// s5
	echo '</div>';
	Maket::divclass($MP[12],$Pth,$style,' user','div');
		echo $service;
		$numelem=Maket::getscountab($arr['tab']['elem'],'id','c');
		if ($arr['typmen'][5]<> 'nbf' &&  $numelem>0) {
			Maket::showpoiskempty($Pth);
		}
	echo '</div></div></div>';
	
}

static function showdisplayblock($clas,$arr,$Pth,$disp=' flex',$style='',$prefix=''){
	foreach ($arr as $key=>$val)Maket::showlogo($clas[$key],$val,$Pth,$disp,$style,$prefix);
	
}

static function rasklad($grp,$itms){
	$maxbtns = $grp * $itms;
	//echo $itms;
	//if($count>$itms)$count = $itms;
	for($i=0;$i<$grp; $i++){
		$delta[$grp-$i] = $maxbtns - $i*$itms;
		//echo $count;
		if($delta[$grp-$i] > 0)$numbutt[$grp-$i-1] = $delta[$grp-$i];
		else {
			$numbutt[$grp-$i-1] = - $delta[$grp-$i];
			break;
		}
	}
	return $numbutt;
}

static function showdisplaybutton($arr,$Pth,$clas='button',$typelist='butt',$selector='button',$nb=0,$ne){
	
	foreach($arr[$typelist] as $key=>$val){
		if($key>=$nb && $key<$ne){ 
			if ($arr['idmen'][0] <> 'land') {
					$buthref='./?np='.$arr[$typelist.'href'][$key];	
				}
				else {
					$buthref='#zak'.$key;
				}
		if($val){
		Maket::divclass('item-'.$arr['idmen'][0],$Pth);
		Maket::spanclass('<a href="'.$buthref.'">'.$val.'</a>',$Pth,$clas,$selector);
		echo '</div>';
	}
	}
}
}

static function showdisplaymenu($arr,$Pth,$clas='menu',$typelist='butt',$selector='menu'){
	foreach($arr[$typelist] as $key=>$val){
	if ($arr['idmen'][0] <> 'land') {
					$buthref='./?np='.$arr[$typelist.'href'][$key];	
				}
				else {
					$buthref='#zak'.$key;
				}
	if($val){
		Maket::spanclass('<a href="'.$buthref.'">'.$val.'</a>',$Pth,$clas,$selector);
		}
}
}

private function get_image_type( $image_path_or_resource ) {
    $img = getimagesize( $image_path_or_resource );
    if ( !empty( $img[2] ) ) // returns an integer code
        return image_type_to_mime_type( $img[2] );
    return false;
}

static public function datacard($arr,$typelist,$key){
		//print_r($arr['n']);
		if($typelist === 'news'){
			$card_item = array('',$arr['n']['date'].' <br><b>'.$arr['n']['name'].'</b><br>'.$arr['n']['text'],$arr['n']['vend']);
			$arr[$typelist.'href'][$key]= $arr['n']['hrefn'];
		}
		else $card_item= Maket::part_texts($arr[$typelist][$key]);
		if($typelist === 'imgt')$card_img=$arr['imgs'][$key];
		elseif($typelist === 'news')$card_img=$arr['n']['imgn'];
		elseif($typelist === 'butt')$card_img=$arr['buttimg'][$key];
		else $card_img=$arr['clas']['img'];
		//print_r($card_item);
		if(isset($card_item[1])){
			$fulzag=$card_item[0];
			if(isset($card_item[2])){
				$buttnam=$card_item[2];
				$text=$card_item[1];
			}
			else {
				$buttnam='';
				$text=$card_item[1];
			}
		
		}
		else {
			$text =$card_item[0];
			$buttnam='';
			$fulzag='';
				}
	//print_r($arr[$typelist.'href']);		
	if($arr[$typelist.'href'][$key] === '')$buttnam = '';
	return array('fulzag_card'=>$fulzag,'text_card'=>$text ,'but_card'=>$buttnam,'img_card'=>$card_img,'href_card'=>$arr[$typelist.'href'][$key]);		
}

static function repl($str){
	if(strstr($str,'- ')){
		$dtr=explode('- ',$str);
		foreach($dtr as $val)$res.=$val;
	return $res;}
	else return $str;
}

static function showlogo($clas,$arr,$Pth,$mode=0,$key=0,$typelist1='',$typelist='butt',$n_simb=351,$disp=' flex',$style='',$prefix=''){
	if(is_array($arr)){
	if($prefix=='')$prefix=' '.$disp;
	if($typelist1 === '')$typelist1=$typelist.'href';
	else $typelist1=$typelist1.'href';
	if($typelist === 'news')$arr[$typelist][$key]=$arr['n']['text'];
	//echo  $arr['n'];
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
	}			
	//echo $typelist1.'='.$key.'='.$fulzag_card.' ='.$zagol.' ='.$text_card.' ='.$but_card.' ='.$img_card.' ='.$href_card.'<br>';			
	//echo $key.'='.$typelist1.'='.$img_card.' ='.$text_card;
	
	switch($mode){
		case '0':{//хедер простой
			if(isset($block_logo)){
				if(!is_array($arr))$block_logo=$arr;
				//Maket::divclass('head head-'.$clas,$Pth,'',$disp);
				echo Maket::spanclasstr(Maket::spanclasstr(Maket::spanclasstr($block_logo,$Pth,$clas,'li',$prefix,$style),$Pth,$clas,'ul',$style,$prefix),$Pth,$clas,'div',$prefix,$style);
			}
			//echo '</div>';
			break;	
		}
		case '1':{//хедер с логотипом
			if(is_array($arr)){
				//Maket::divclass('head head-'.$clas,$Pth,'',$disp);
				//вывод логотипов и главного лозунга
				if(Maket::get_image_type($arr['clas']['img'].$arr['namep'][1]))
					Page::scalimag3($arr,$arr['clas']['img'].$arr['namep'][1],'./?np='.$arr['nump'],$Pth,0);
			
			}
			break;
		}
		case '2':{//карточка элемента
		
		
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
			Maket::divclass($clas,$Pth,'',$disp);
			Maket::divclass($clas.'_item',$Pth);
			//echo 'here';
			//echo 'zagol '.$fulzag_card;
			if($zagol)echo '<li class="'.$clas.'-li hidyes"><h4><a href="'.$buthref.'">'.$zagol.'</a></h4></li>';
			if($fulzag_card && $fulzag_card != $zagol)echo Maket::spanclasstr('<h4><a href="'.$buthref.'">'.$fulzag_card.'</a></h4>',$Pth,$clas.'-li','','',' hidno');
			if($arr['clas']['img'].$img_card<>$arr['clas']['img'])echo Maket::spanclasstr($cardImg,$Pth,$clas.'-img'.$key,'li');	
			echo '<ul>';
			if($n_simb =strpos($text_card,'<>'))$text_card0=substr_replace($text_card,'...',$n_simb) ;
			else {$text_card0=$text_card;$n_simb=intval(strlen($text_card));}
			if($n_slimb !=0 && strlen($text_card)>$n_simb && !isset($_GET['konstrS'])){
				
			if($text_card0)echo Maket::spanclasstr($text_card0,$Pth,$clas.'_zagt'.$key,'li','','',' hidyes');
				//echo '<li class="hidyes">'.$text_card0.'</li>';
			if($text_card &&  $text_card != $text_card0)echo Maket::spanclasstr($text_card,$Pth,$clas.'_text'.$key,'li','','',' hidno');
				//echo '<li class="hidno">'.$text_card.'</li>';
			//echo '</ul>';
			}
			elseif($text_card<>'') Maket::spanclass($text_card,$Pth,'card_item-li_'.$key,'li');// echo '<li>'.$text_card.'</li>';
			if($but_card<>'' )echo '<li>'.Maket::divclasstr('button part-button_'.$key,$Pth,'','','button').'<a href="'.$buthref.'">'. $but_card.'</a></button></li>';
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
					//echo $fulzag_card0.$n_simb;
					if(strlen($fulzag_card)>intval($n_simb)){
						if($fulzag_card0){
							$zagol=$fulzag_card0;
							$fulzag_card=substr_replace(strstr($fulzag_card,'<>'),'',0,2);
						}
					}
					else {
						$zagol=$fulzag_card;
						$fulzag_card='';}
					//echo 'pic='.$cardImg;
					if($typelist === 'imgt')$img_card = $arr['clas']['img'].$arr['imgs'][$key];
				}
				else {
					$text_card=$arr['cont'][$key];
					if($img_card && isset($_GET['konstrS']))$cardImg='<div>'.$arr['link'][$typecard][$key].$cardImg.'</div>';
					}
				//echo $key.'='.$typelist1.'='.$img_card.' ='.$text_card.'=>';
				//echo $key.'='.$text_card.'='.$but_card;
				Maket::divclass($clas,$Pth,'',$disp);
				Maket::divclass('item_card_'.$key,$Pth);
				//echo 'there';
				echo '<ul>';
				if(!isset($_GET['konstrS'])){
					echo Maket::spanclasstr('<h4>'.$zagol.'</h4>',$Pth,$clas.'_zagt'.$key,'li','','',' hidyes');
					//echo '<li class="hidyes"><h4>'.$zagol.'</h4></li>';
					if($fulzag_card != '')echo Maket::spanclasstr('<h4>'.$fulzag_card.'</h4>',$Pth,$clas.'_zagt'.$key,'li','','',' hidyes');
					if($but_card === '')echo '<a href="'.$buthref.'">...</a>';
				}
				else {
					echo '<a href="'.$buthref.'">';
					echo  Maket::spanclasstr('<h4>'.$fulzag_card.'</h4>',$Pth,$clas.'_zagt'.$key,'li');
					//'<li class="hidyes"><h4>'.$fulzag_card.'</h4></li>';
				}
				if($img_card<>$arr['clas']['img'] )echo '<li>'.$cardImg.'</li>';
				//if(strlen($text_card)>$n_simb ){
					if(!isset($_GET['konstrS'])){
						if($n_simb =strpos($text_card,'<>')){
							$text_card=$text_card;
							$text_card0=substr_replace($text_card,'...',$n_simb) ;
							if($text_card0)echo Maket::spanclasstr($text_card0,$Pth,$clas.'_zagt'.$key,'li','','',' hidyes');
							if($text_card && $text_card !=$text_card0) echo Maket::spanclasstr($text_card,$Pth,$clas.'_text'.$key,'li','','',' hidno');
						}
						else {
							$text_card0=$text_card;
							$n_simb=strlen($text_card);
							if($text_card0)echo Maket::spanclasstr($text_card0,$Pth,$clas.'_zagt'.$key,'li');
							}
						
					}
					else {
						 echo Maket::spanclasstr($text_card,$Pth,$clas.'_text'.$key,'li');
					}
				//}	
				//elseif($text_card<>'') echo '<li>'.$text_card.'</li>';
				if(!isset($_GET['konstrS']))echo '</a>';
				if($but_card<>'' )echo '<li>'.Maket::divclasstr('button part-button_'.$key,$Pth,'','','button').'<a href="'.$buthref.'">'. $but_card.'</a></button></li>';
				}
				//elseif($img_card<>$arr['clas']['img'])echo '<li>'.$cardImg.'</li>'; 
				//elseif($text_card<>'') echo '<li>'.$text_card.'</li>';
				
						
				echo '</ul>';
				echo '</div></div>';
			
					break;
		}		
		case '3':{//заголовок блока class=zag-h1 + текст class=content-...
			if(isset($text_card) && $typelist=='loz'){
			if(strstr($clas,'-')){
				//echo $typelist1.' '.$arr[$typelist1][$key].' '.$key;
				$clas_zag=explode('-',$clas);
				if($href_card<>'')$text_card='<a class="'.$clas_zag[0].'" href="'.$buthref.'"><h2>'.$text_card.'</h2></a>';
				Maket::divclass('items part5',$Pth);
				echo Maket::spanclasstr($text_card,$Pth,'item',$clas_zag[1]);
				//echo '</div>';
			}
			else {
				if($zagol){
					echo Maket::spanclasstr($zagol,$Pth,'item','h2');
					}
				Maket::divclass('items part5',$Pth);
				if(!isset($_GET['konstrS'])){
				$n_simb=$Pth['hidyes']['effect']['crop'];
				Maket::spanclass('<h1>'.$text_card.'</h1>',$Pth,'hidyes '.$clas_zag[0].($key),'li');
				}
				else Maket::spanclass('<h1>'.$text_card.'</h1>',$Pth,$clas_zag[0].($key),'li');
			}
			}
			elseif($text_card<>'' && $typelist=='cont'){
				Maket::divclass('content'.$key,$Pth,'',' '.$arr['idmen'][0]);
				if($zagol){
					if($href_card) echo '<a class="'.$clas.$key.'" href="'.$buthref.'">'.Maket::spanclasstr($zagol,$Pth,'Hitem-'.$clas,'h3','',$style,$prefix).'</a>';
					else Maket::spanclass($zagol,$Pth,'Hitem-'.$clas,'h3','',$style,$prefix);
					}
					//echo $n_simb;
					if( $n_simb<0){
						echo Maket::spanclasstr(substr_replace($text_card,'...',-$n_simb),$Pth,'closes Titem-'.$clas,'div');
						if($href_card<>'')echo '<a title="Посмотреть все" href="./?np='.$href_card.'#zak'.$key.'"> ......</a>';
						$href='./?editp='.$Pth['Titem-'.$clas]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.$clas]['id'];
						if(isset($Pth['adm'])) echo '<a title="обрезать" href="javascript:new_window(\''.$href.'\')">.....</a>';
						return $key;
					}
					if(strlen($text_card)>$n_simb && $n_simb>0){
						if(!isset($_GET['konstrS'])){
							echo Maket::spanclasstr(substr_replace($text_card,'...',$n_simb),$Pth,'Titem-'.$clas,'div','','',' hidyes');
							Maket::spanclass($text_card,$Pth,'Titem-'.$clas,'div','','',' hidno');
							}
						else {
							echo Maket::spanclasstr(substr_replace($text_card,'...',$n_simb),$Pth,'Titem-'.$clas,'div');
							Maket::spanclass($text_card,$Pth,'Titem-'.$clas,'div','','',' hidno');	
							}
					$href='./?editp='.$Pth['Titem-'.$clas]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.$clas]['id'];
					if(isset($Pth['adm'])) echo '<a title="обрезать" href="javascript:new_window(\''.$href.'\')">...</a>';
					}
					elseif($href_card<>'')echo '<a class="'.$clas.'" href="./?np='.$href_card.'">'.Maket::spanclasstr($text_card,$Pth,'Titem-'.$clas,'div').'</a>';
					elseif($text_card<>'') Maket::spanclass($text_card,$Pth,'Titem-'.$clas,'div');
					//echo '</div>';
				}
				else echo Maket::spanclasstr($text_card,$Pth,'Titem-'.$clas,'div','',$style,$prefix);
			
			echo '</div>';
			break;
		}
		case '4':{//Двойной заголовок
			if($arr[$typelist1][$key]<>''){
				if(strstr($clas,'-')){ 
					$clas_zag=explode('-',$clas);
				}
				$clas=$clas_zag[0].'-'.$typelist.$key;
				$n_simb=$Pth['Titem-'.$clas]['effect']['crop'];
				Maket::showlogo($clas,$arr,$Pth,3,$key,$typelist1,$typelist,$Pth['Titem-'.$clas]['effect']['crop'],$disp,$style,$prefix);
				$key++;
				if(isset($arr[$typelist1][$key])&& isset($arr[$typelist][$key])){
					$clas=$clas_zag[0].'-'.$typelist.$key;
					Maket::divclass('Titem-'.$clas,$Pth,'',$disp);
					Maket::divclass('item-'.$clas,$Pth);
					echo '<ul>';
					
					//echo $clas;
					$n_simb=$Pth['Titem-'.$clas]['effect']['crop'];
					if(strlen($arr[$typelist][$key])>$n_simb && $n_simb>0){
						Maket::spanclass('<h3>'.substr_replace(Maket::part_text($arr[$typelist][$key]),'',$n_simb).'</h3>',$Pth,'Titem-'.$clas,'li','','',' hidyes');
						$href='./?editp='.$Pth['Titem-'.$clas]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.$clas]['id'];
						Maket::spanclass(Maket::spanclasstr(Maket::part_text($arr[$typelist][$key]),$Pth,$clas_zag[0],$clas_zag[1]),$Pth,'Titem-'.$clas,'li','','',' hidno');
						echo '<a href="javascript:new_window(\''.$href.'\')">обрезать...</a>';
						
						echo '</ul>';
					}
					elseif($arr[$typelist1][$key]<>'') echo '<a class="'.$clas.'" href="./?np='.$arr[$typelist1][$key].'">'.Maket::spanclasstr(Maket::spanclasstr(Maket::part_text($arr[$typelist][$key]),$Pth,$clas_zag[0],$clas_zag[1]),$Pth,'Titem-'.$clas).'</a>';
					else Maket::spanclass('<h3>'.Maket::part_text($arr[$typelist][$key]).'</h3>',$Pth,'Titem-'.$clas);
					echo '</ul>';
				echo '</div></div>';
				}
			}
			break;
		}
		case '5':{
			if ($arr['idmen'][0] <> 'land') {
					$buthref='./?np='.$arr[$typelist1.'href'][$key];	
				}
				else {
					$buthref='#zak'.$key;
				}
			$arr_cont=Maket::spanclasstr($arr[$typelist1][$key],$Pth,'logo','div','','',' flex');
			$arr_foot='<ul><li><a href="'.$buthref.'">'.$arr_cont.'</a></li></ul>';
			if($arr[$typelist1][$key] != '')echo Maket::spanclasstr(Maket::spanclasstr($arr_foot,$Pth,$clas.'-1','div'),$Pth,$clas.'s','div');
			break;
		}
		case '6':{
			echo '<div class="container__blog-head _container">
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
			echo '<div class="top-nav">
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
	}
	return $key;
	
}

static function divShopOptions($Pth,$clas,$title,$priceold,$price,$stock=0){
	$str = '';
	$str1 = maket::part_texts($title);
	$str .= '<div class="'.$clas.'__body">
	<a href="" class="'.$clas.'__title"><span>'.$str1 [0].'</span>
	'.$str1 [1].'</a>
	<div class="'.$clas.'__footer">
	<div class="'.$clas.'__oldprice">'.$priceold.'</div>
		<div>';
		if($stock>0)$str .= '<a href="" class="'.$clas.'__add">
				<img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
			</a>';
		else $str .='<img class="pass" style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">';	
		$str .= '</div>        
		<div class="'.$clas.'__price">'.$price.'</div>        
	</div>     
	</div>';
	return $str;
}

static function divHoverOptions($Pth,$clas,$title,$arrnam,$arrpar,$priceold,$price,$stock){
	$glsr = glossary();
	if (intval($stock>0)) $skld = $glsr['stc'];
	else $skld = $glsr['pzk'];
	$str = '';
	$str1 = maket::part_texts($title);
	$str .= maket::div2Blockstr2($Pth,'<a><span>'.$str1[0].'</span>'.$str1[1].'</a>','',$clas.'__hover hover-'.$clas,'hover-'.$clas.'__title');
	$str .= '<div class="hover-'.$clas.'__options options-'.$clas.'">';
	foreach($arrnam as $k=>$val) {
		$str .='<div class="options-'.$clas.'__item">
    		<div class="options-'.$clas.'__label">'.$val.'</div>
    		<div class="options-'.$clas.'__value">'.$arrpar[$k].'</div> 
			</div>';
	}
	$str .= '</div>';
	$str .= '<a href="" class="hover-'.$clas.'__cart">
</a>
<div class="hover-'.$clas.'__footer">
    <div class="hover-'.$clas.'__old-price">'.$priceold.'</div>
    <div class="hover-'.$clas.'__stock">'.$skld.' '.$stock.'</div>
    <div class="hover-'.$clas.'__price">'.$price.'</div>
</div>';
return $str;
}

static function div3Blocks($word1,$word2){
	echo '<div class="'.$word1.'-container">
		<div class="'.$word1.'-wrapper">
		<div class="'.$word1.'-'.$word2.'">';
}

static function div2Blocks($word1,$word2){
	
	echo '<div class="container-'.$word1.'">
		<div class="wrapper-'.$word2.'">';
}

static function div2Blockstr($Pth,$content,$hz1='',$word1='container',$word2=''){
	$str = Maket::divclasstr($word1,$Pth);
	if($hz1 != '' && !strstr($hz1, 'div'))	{
		$str .= Maket::spanclasstr($hz1,$Pth,'','h3');		
	}
	else $str .= $hz1;
	if($word2 != '') $str .= Maket::divclasstr($word2,$Pth);
	$str .= $content.Maket::closedivstr(1);
	if($word2 != '') $str .= Maket::closedivstr(1);
	return $str;
}

static function div2Blockstr2($Pth,$content,$hz1='',$word1='container',$word2='',$dataIcon='',$rev=0){
	$str = Maket::divclasstr($word1,$Pth);
	if($hz1 != '')	{
		$str .= Maket::spanclasstr($hz1,$Pth,'','h3');		
	}
	
	if($word2 != '' && $dataIcon !='') $str .= Maket::divclasstr($word2,$Pth).$dataIcon.Maket::closedivstr(1);
	else $str .= Maket::divclasstr($word2,$Pth);
	if($rev == 0) $str .= $content.Maket::closedivstr(1);
	else $str .= Maket::closedivstr(1).$content;
	if($word2 != '' && $rev == 1) $str .= Maket::closedivstr(1);
	return $str;
}

static function div3Blockstr($Pth,$content,$word1,$hz='',$word2='',$word3='',$content1=''){
	$str=Maket::divclasstr($word1,$Pth);
		if($hz != '')$str.=Maket::spanclasstr($hz,$Pth,'','h2');
		if($word2 != '')$str.=Maket::divclasstr($word2,$Pth);
		if($word3 != '')$str.=Maket::divclasstr($word3,$Pth);
		if($content1 === '')$str.=$content.Maket::closedivstr(3);
		else $str.=$content.Maket::closedivstr(2).$content1.Maket::closedivstr(1);
	return $str;	
}

static function blogItemRight($Pth, $card, $word1='',$word2='',$word3=''){
	$str = Maket::divclasstr($word1,$Pth).Maket::divclasstr($word2,$Pth)
	.$card[0].Maket::closedivstr(1).Maket::divclasstr($word3,$Pth)
	.'<p>'.$card[1].'<p><strong>'.$card[2].'</strong>'.Maket::closedivstr(1)
	.'<p>'.$card[3].'</p>'.Maket::closedivstr(1);
	return $str;
}

static function blogItemLeft($Pth, $card, $word1='',$word2='',$word3=''){
	$str = Maket::divclasstr($word1,$Pth).Maket::divclasstr($word2,$Pth)
	.$card[0].Maket::closedivstr(1).Maket::divclasstr($word3,$Pth)
	.'<strong>'.$card[2].'</strong><p>'.$card[1].'</p>'.Maket::closedivstr(1)
	.$card[3].Maket::closedivstr(1);
	return $str;
}


static function showFormBlog($Pth){
	$glsr = glossary();
	$act = 'http://formspree.io/agragregra@ya.ru';
	$text = array($glsr['yn'].':',$glsr['ye'].':',$glsr['ym'].':',$glsr['sd']);
	$name = array('name','email','message');
	$type = array('text','email','textarea');
	
	$clas = array('main_form','form-group','color_element','help-block text-danger');
	$datajs = array('data-validation-required-message','data-validation-required-message','data-validation-required-message');
	$textvalid = array($glsr['en'],$glsr['ee'],$glsr['em']);
	$requi = array('required','required','required');
	$str = '<form action="'.$act.'" class="'.$clas[0].'" novalidate target="_blank" method="post">';
	for($i=0;$i<count($name);$i++) {
		$str .='<label class="'.$clas[1].'">
		<span class="'.$clas[2].'">*</span> '.$text[$i];
		if($type[$i] != "textarea") $str .='<input type="'.$type[$i].'" name="'.$name[$i].'" placeholder="'.$text[$i].'" '.$datajs[$i].'="'.$textvalid[$i].'" '.$requi[$i].' />';
		else $str .='<textarea name="'.$name[$i].'" placeholder="'.$text[$i].'" '.$datajs[$i].'="'.$textvalid[$i].'" '.$requi[$i].'></textarea>';
		$str .= '<span class="'.$clas[3].'"></span></label>';
		}	
		$str .= '<button>'.$text[count($name)].'</button>
</form>';
return $str;
}

static function viewdatapage($dat,$clas,$Pth,$hrf,$selector='span',$pref='__list',$link='__link',$body=''){
	$str = '';
	if($body === '' && $pref != '') $body = '__list';
	elseif($pref == '' && $link == '') {
		$str = maket:: viewdatapageold($dat,$clas,$Pth,$hrf,$selector);
		return $str;
	}
	if(is_array($clas)){
		$clas0 = array_shift($clas);
		if(count($clas)>1) $datajs = $clas;
			$clas1 = array_shift($clas);
			$clas = $clas0.' '.$clas1;
	}
	else {
		$clas1 = $clas;
	}
	
	if(isset($datajs) && $selector === 'ul') foreach($datajs as $k=>$val) $selectorjs[$k] ='li '.$val; 
	if(is_array($dat)){
		if(isset($dat['typesite'])){
			if($dat['typesite'] != 'spa') $hr = '?np=';
			else $hr = '';
		}
		else $hr = '';
		if(!isset($_GET['editp']))$pp='';
		else $pp='&editp='.$_GET['editp'];
		if($selector=='span' || $selector=='p')foreach ($dat['dat'] as $k=>$val) $str .= Maket::divclasstr($clas.'_item'.' item_'.$k,$Pth,'','',$selector).$val.'</'.$selector.'>';	
		elseif($selector=='ul') {
			if($clas === '') $str .= '<ul>';
			else $str .= '<ul class="'.$clas.$body.'">';
			$i=0;
			foreach ($dat['dat'] as $key=>$val){
				if($key>0 && !isset($datajs) && $hr != '') {
					$key=$hr.$key.$pp;
				}
				if($clas != '' && !isset($datajs) && $hr != '') $str .= Maket::divclasstr($clas1.$pref,$Pth,'',' ','li').Maket::divclasstr($clas1.$link,$Pth,'','','a id="submenu_'.$key.'" href="'.$hrf.$key.'" target="_blank"').$val.'</a></li>';
				elseif(isset($dat['href'][$key]) && $dat['href'][$key] != '' ) $str .= Maket::divclasstr($clas1.$pref,$Pth,'',' ','li').Maket::divclasstr($clas1.$link,$Pth,'','','a id="submenu_'.$key.'" href="'.$dat['href'][$key].'" target="_blank"').$val.'</a></li>';
				elseif(isset($dat['href'][$key]) && $dat['href'][$key] == '' ) $str .= Maket::divclasstr($clas1.$pref,$Pth,'',' ','li').Maket::spanclasstr($val,$Pth,$clas1.'__item').'</li>';
				elseif(!isset($datajs) && $hr != '') $str .= Maket::divclasstr('',$Pth,'','','li').Maket::divclasstr($clas.'__link',$Pth,'','item_'.$key,'a id="submenu_'.$key.'" href="'.$hrf.$key.'" target="_blank').$val.'</a></li>'; 
				elseif($hr === '' && isset($selectorjs)) $str .= Maket::divclasstr($clas,$Pth,'',$clas1,$selectorjs[$key]).$val.'</li>'; 
				elseif(!isset($datajs) && $hr != '') $str .= Maket::divclasstr($clas,$Pth,'',$clas1,'li href="'.$key.'"').$val.'</li>';  
				else $str .= Maket::divclasstr('',$Pth,'',$pref,'li').$val.'</li>';  
				if(isset($dat['val'][$i])) $str .= $dat['val'][$i];
				$i++;
			}
			$str .= '</ul>';
			if($clas != '' && $body != ''){
				$str = '<nav class="'.$clas.'__body">'.$str.'</nav>';
			}
			else $str = '<nav class="'.$clas.'">'.$str.'</nav>';
		}
	}
	elseif($dat != '') $str .= Maket::divclasstr($clas,$Pth,'','',$selector).$dat.'</'.$selector.'>';
	else return false;
	return $str;
}

static function viewdatapageold($dat,$clas,$Pth,$hrf,$selector='span'){
	
	$str = '';
	if(is_array($clas)){
		$clas0 = array_shift($clas);
		$datajs = $clas;
		$clas = $clas0;
	}
	if(isset($datajs) && $selector=== 'ul') foreach($datajs as $k=>$val) $selectorjs[$k] ='li '.$val; 
	if(is_array($dat)){
		if(isset($dat['typesite'])){
			if($dat['typesite'] != 'spa') $hr = '?np=';
			else $hr = '';
		}
		else $hr = '';
		if(!isset($_GET['editp']))$pp='';
		else $pp='&editp='.$_GET['editp'];
		if($selector==='span' || $selector==='p' )foreach ($dat['dat'] as $k=>$val) $str .= Maket::divclasstr($clas.'_item'.' item_'.$k,$Pth,'','',$selector).$val.'</'.$selector.'>';	
		elseif($selector=='ul') {
			$str .= '<ul>';
			foreach ($dat['dat'] as $key=>$val){
				
				if($key>0 && !isset($datajs) && $hr != '') $key=$hr.$key.$pp;
				if($clas != '' && !isset($datajs)) $str .= Maket::divclasstr($clas,$Pth,'',' active','li').Maket::divclasstr('item',$Pth,'','_'.$key,'a href="'.$hrf.$key.'" target="_blank').$val.'</a></li>';
				elseif(!isset($datajs) && !isset($dat['href'])) $str .= Maket::divclasstr('',$Pth,'','','li').Maket::divclasstr('item',$Pth,'','_'.$key,'a href="'.$hrf.$key.'" target="_blank').$val.'</a></li>'; 
				elseif(!isset($datajs) && isset($dat['href'])) $str .= Maket::divclasstr('',$Pth,'','','li').Maket::divclasstr('item',$Pth,'','_'.$key,'a href="http://'.$dat['href'][$key].'" target="_blank').$val.'</a></li>'; 
				elseif($hr === '') $str .= Maket::divclasstr($clas,$Pth,'','',$selectorjs[$key]).$val.'</li>'; 
				elseif(!isset($datajs)) $str .= Maket::divclasstr($clas,$Pth,'','','li href="'.$key.'"').$val.'</li>';  
				else $str .= Maket::divclasstr($clas,$Pth,'','','li').$val.'</li>';  
			}
			$str .= '</ul>';
		}
	}
	elseif($dat != '') $str .= Maket::divclasstr($clas,$Pth,'','',$selector).$dat.'</'.$selector.'>';
	else return false;
	return $str;
}

// static function viewdatapage($dat,$clas,$Pth,$hrf,$selector='span',$pref='__list',$link='__link',$body=''){
	// $str = '';
	// if($body === '' && $pref != '') $body = '__list';
	// if(is_array($clas)){
		// $clas0 = array_shift($clas);
		// if(count($clas)>1) $datajs = $clas;
			// $clas1 = array_shift($clas);
			// $clas = $clas0.' '.$clas1;
	// }
	// else {
		// $clas1 = $clas;
	// }
	// if(isset($datajs) && $selector === 'ul') foreach($datajs as $k=>$val) $selectorjs[$k] ='li '.$val; 
	// if(is_array($dat)){
		// if(isset($dat['typesite'])){
			// if($dat['typesite'] != 'spa') $hr = '?np=';
			// else $hr = '';
		// }
		// else $hr = '';
		// if(!isset($_GET['editp']))$pp='';
		// else $pp='&editp='.$_GET['editp'];
		// if($selector==='span' || $selector==='p')foreach ($dat['dat'] as $k=>$val) $str .= Maket::divclasstr($clas.'_item'.' item_'.$k,$Pth,'','',$selector).$val.'</'.$selector.'>';	
		// elseif($selector=='ul') {
			// if($clas === '') $str .= '<ul>';
			// else $str .= '<ul class="'.$clas.$body.'">';
			// $i=0;
			// foreach ($dat['dat'] as $key=>$val){
				// if($key>0 && !isset($datajs) && $hr != '') {
					// $key=$hr.$key.$pp;
				// }
				// if($clas != '' && !isset($datajs) && $hr != '') $str .= Maket::divclasstr($clas1.$pref,$Pth,'',' ','li').Maket::divclasstr($clas1.$link,$Pth,'','','a id="submenu_'.$key.'" href="'.$hrf.$key.'" target="_blank"').$val.'</a></li>';
				// elseif(isset($dat['href'][$key])) $str .= Maket::divclasstr($clas1.$pref,$Pth,'',' ','li').Maket::divclasstr($clas1.$link,$Pth,'','','a id="submenu_'.$key.'" href="'.$dat['href'][$key].'" target="_blank"').$val.'</a></li>';
				// elseif(!isset($datajs) && $hr != '') $str .= Maket::divclasstr('',$Pth,'','','li').Maket::divclasstr($clas.'__link',$Pth,'','item_'.$key,'a id="submenu_'.$key.'" href="'.$hrf.$key.'" target="_blank').$val.'</a></li>'; 
				// elseif($hr === '' && isset($selectorjs)) $str .= Maket::divclasstr($clas,$Pth,'',$clas1,$selectorjs[$key]).$val.'</li>'; 
				// elseif(!isset($datajs) && $hr != '') $str .= Maket::divclasstr($clas,$Pth,'',$clas1,'li href="'.$key.'"').$val.'</li>';  
				// else $str .= Maket::divclasstr('',$Pth,'',$pref,'li').$val.'</li>';  
				// if(isset($dat['val'][$i])) $str .= $dat['val'][$i];
				// $i++;
			// }
			// $str .= '</ul>';
			// if($clas != ''){
				// $str = '<nav class="'.$clas.'__body">'.$str.'</nav>';
			// }
		// }
	// }
	// elseif($dat != '') $str .= Maket::divclasstr($clas,$Pth,'','',$selector).$dat.'</'.$selector.'>';
	// else return false;
	// return $str;
// }

static function showPersonLandMaket($Pth, $id, $content){
	foreach ($content as $key=>$val){
	$str = Maket::spanclasstr($val,$Pth,$id[$key],'section','','',$clas[$key]);
	}
	return $str;
}

static function showmaket($arr,$MP,$Pth,$vendors,$service,$ownerdata=''){
	$ts=$arr['idmen'][0];
	$sid=$arr['owner']->ids;
	$st=$arr['owner']->start;
	//print_r($sid.'-'.$st);
	$ownerdata='';
	$img=$arr['clas']['img'].$arr['namep'][1];
	
	switch($arr['idmen'][0]){
		case 'land': {
			$clas_head=array('user','logo','serv');
			$arr_head=array($ownerdata,$arr,$service);
			$nLast=Maket::showheaderflex($Pth,$clas_head,$arr_head,'logo');
			Maket::showbackground($arr,$MP,$Pth);
			echo '<section>';
			if($arr['loz'][0]=='')Maket::showlogo($clas_head[$nLast],$arr_head[$nLast],$Pth,0);
			else {
			if($Pth['advers_banner']['numpar']['Pics'])$razmer=$Pth['advers_banner']['numpar']['Pics'];
			else $razmer=3;
			Page::scalimag4($arr,$Pth,$clas,'block-advers','div',$razmer,300,'');
			}
			/*Maket::divclass($MP[17].'-'.$arr['idmen'][0],$Pth,'',' grid');
			Maket::divclass($MP[8],$Pth);
			Maket::divclass($MP[12],$Pth,'',' user','div','s2','h1');
			if (isset($arr['owner'])){
				
				//print_r($arr['owner']);
				//Вывод регистрационных данных пользователя
				$ownerdata.='<span>'.date("d m Y").' '.'</span><span>'.$arr['owner']->name.'<br></span>';
				if ($arr['owner']->telmain <> "" && $arr['owner']->email <> "") {
				if ($arr['owner']->telmain<>'no' && $arr['owner']->telmain<>'') $ownerdata.='<span>'.$arr['owner']->telmain.'</span>';
				if (filter_var($arr['owner']->email, FILTER_VALIDATE_EMAIL)) $ownerdata.='<span><br>'.$arr['owner']->email.'</span>';  
				}
			}
				elseif (isset($arr['user'])){
				$ownerdata.= '<span>'.date("d m Y").' '.'</span><span>'.$arr['user'][2].'</span>'.$str;
				if ($arr['user'][3]<> '') {
				if ($this->isValidEmail($arr['user'][3])) $ownerdata.= $str.'<span>'.$arr['user'][3].'</span>';  
					}
				}
				else $ownerdata='<span>'.date("d m Y").' '.'</span><span>Гость</span>';
				echo $ownerdata;
				echo '</div>';
			
			$rowhead=4;
			Maket::showlogo($MP[12],$arr,$Pth);
			/*Maket::divclass($MP[12],$Pth,'',' logo','div','s4','h1');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo $arr['owner']->name;
			echo '</div>';// s5
			echo '</div>';	
			Maket::divclass($MP[12],$Pth,'','','div','s4','h1');
			echo $service;
			if ($arr['link']<>'')Maket::selectors($arr,$Pth,$vendors,1);
			echo '</div>';
			echo '</div>';*/
			break;
		}
		case 'cont':{
			
			//Maket::divclass($MP[17].'-'.$disp,$Pth,'',' grid');
			//Maket::divclass($MP[8],$Pth);
			Maket::divclass($MP[12],$Pth,'',' user');
			$ownerdata='<ul>';
			if (isset($arr['owner'])){
				//print_r($arr['owner']);
				//Вывод регистрационных данных пользователя
				$ownerdata.='<span class="user"> '.$arr['owner']->name.' </span>';
				if ($arr['owner']->telmain <> "" && $arr['owner']->email <> "") {
				if ($arr['owner']->telmain<>'no' && $arr['owner']->telmain<>'') $ownerdata.='<span  class="user"> '.$arr['owner']->telmain.' </span>';
				if (filter_var($arr['owner']->email, FILTER_VALIDATE_EMAIL)) $ownerdata.='<span class="user"> '.$arr['owner']->email.' </span>';  
				}
			}
			elseif (isset($arr['user'])){
			$ownerdata= '<span  class="user">'.$arr['user'][2].'</span>';
			if ($arr['user'][3]<> '') {
			if ($this->isValidEmail($arr['user'][3])) $ownerdata.= '<span>'.$arr['user'][3].'</span>';  
					}
				}
			else $ownerdata='<span  class="user">Гость</span>';
			echo $ownerdata;
			echo '</ul></div>';
			Maket::divclass($MP[12],$Pth,'',' logo','div','s4','h1');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo '</div>';// s5
			echo '</div>';	
			Maket::divclass($MP[12],$Pth,'',' user','div','s4','h1');
			echo $service;
			if ($arr['link']<>'')Maket::selectors($arr,$Pth,$vendors,1);
			echo '</div>';
			//echo '</div>';
			break;
		}
		case 'mag':{
			
			//Maket::divclass($MP[17].'-'.$disp,$Pth,'',' grid');
			//Maket::divclass($MP[8],$Pth);
			Maket::divclass($MP[12],$Pth,'',' user');
			if (isset($arr['owner'])){
				//print_r($arr['owner']);
				//Вывод регистрационных данных пользователя
				$ownerdata.='<span>'.date("d m Y").' '.'</span><span>'.$arr['owner']->name.'</span>';
				if ($arr['owner']->telmain <> "" && $arr['owner']->email <> "") {
				if ($arr['owner']->telmain<>'no' && $arr['owner']->telmain<>'') $ownerdata.='<span>'.$arr['owner']->telmain.'</span>';
				if (filter_var($arr['owner']->email, FILTER_VALIDATE_EMAIL)) $ownerdata.= '<span>'.$arr['owner']->email.'</span>';  
				}
			}
			elseif (isset($arr['user'])){
			$ownerdata.= '<span>'.date("d m Y").' '.'</span><span>'.$arr['user'][2].'</span>'.$str;
			if ($arr['user'][3]<> '') {
			if ($this->isValidEmail($arr['user'][3])) $ownerdata.= '<span>'.$arr['user'][3].'</span>';  
					}
				}
			else $ownerdata='<span>'.date("d m Y").' '.'</span><span>Гость</span>';
			echo $ownerdata;
			
			echo '</div>';
			Maket::divclass($MP[12],$Pth,'',' logo','div','s4','h1');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo '</div>';// s5
			echo '</div>';	
			Maket::divclass($MP[12],$Pth,'',' user','div','s4','h1');
			echo $service;
			if ($arr['link']<>'')Maket::selectors($arr,$Pth,$vendors,1);
			echo '</div>';
			echo '</div>';
			break;
		}
		case 'cat':{
			
			//Maket::divclass($MP[17].'-'.$disp,$Pth,'',' grid');
			//Maket::divclass($MP[8],$Pth);
			Maket::divclass($MP[12],$Pth,'',' user');
			if (isset($arr['owner'])){
				//print_r($arr['owner']);
				//Вывод регистрационных данных пользователя
				$ownerdata.='<span>'.date("d m Y").' '.'</span><span>'.$arr['owner']->name.'</span>';
				if ($arr['owner']->telmain <> "" && $arr['owner']->email <> "") {
				if ($arr['owner']->telmain<>'no' && $arr['owner']->telmain<>'') $ownerdata.='<span>'.$arr['owner']->telmain.'</span>';
				if (filter_var($arr['owner']->email, FILTER_VALIDATE_EMAIL)) $ownerdata.='<span>'.$arr['owner']->email.'</span>';  
				}
			}
			elseif (isset($arr['user'])){
			$ownerdata.= '<span>'.date("d m Y").' '.'</span><span>'.$arr['user'][2].'</span>'.$str;
			if ($arr['user'][3]<> '') {
			if ($this->isValidEmail($arr['user'][3])) $ownerdata.= $str.'<span>'.$arr['user'][3].'</span>';  
					}
				}
			else $ownerdata='<span>'.date("d m Y").' '.'</span><span>Гость</span>';
			echo $ownerdata;
			
			
			echo '</div>';
			Maket::divclass($MP[12],$Pth,'',' logo','div','s4','h1');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo '</div>';// s5
			echo '</div>';	
			Maket::divclass($MP[12],$Pth,'',' user','div','s4','h1');
			echo $service;
			if ($arr['link']<>'')Maket::selectors($arr,$Pth,$vendors,1);
			echo '</div>';
			echo '</div>';
			break;
		}
		case 'gall':{
			Maket::divclass('swiper-slide',$Pth,'z-index:10;',' user');
			if (isset($arr['owner'])){
				//print_r($arr['owner']);
				//Вывод регистрационных данных пользователя
				
				$ownerdata.='<span>'.date("d m Y").' '.'</span><span>'.$arr['owner']->name.'</span>';
				if ($arr['owner']->telmain <>'' && $arr['owner']->email <> '') {
				if ($arr['owner']->telmain<>'no' && $arr['owner']->telmain<>'') $ownerdata.='<span>'.$arr['owner']->telmain.'</span>';
				if (filter_var($arr['owner']->email, FILTER_VALIDATE_EMAIL)) $ownerdata.='<span>'.$arr['owner']->email.'</span>';  
				}
			}
			elseif (isset($arr['user'])){
			$ownerdata.= '<span>'.date("d m Y").' '.'</span><span>'.$arr['user'][2].'</span>'.$str;
			if ($arr['user'][3]<> '') {
			if ($this->isValidEmail($arr['user'][3])) $ownerdata.= $str.'<span>'.$arr['user'][3].'</span>';  
					}
				}
			else $ownerdata='<span>'.date("d m Y").' '.'</span><span>Гость</span>';
			echo $ownerdata;
			
			echo '</div>';
			Maket::divclass('swiper-slide',$Pth,'z-index:10;',' logo');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo '</div>';// s5
			echo '</div>';	
			Maket::divclass('swiper-slide',$Pth,'z-index:10;',' user');
			echo $service;
			if ($arr['link']<>'') Maket::selectors($arr,$Pth,$vendors,1);
			echo '</div>';
						
			break;
		}
		case 'blog':{
			Maket::divclass($MP[12],$Pth,'',' logo','div','s6','h1');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo '</div>';// s5
			if (isset($arr['user'])){
				Maket::divclass($MP[12],$Pth,'',' user');
				echo $service;
				echo '</div>';
			}
			echo '</div>';	
			
			break;
			}
		case 'fb':{
			Maket::divclass($MP[12],$Pth,'',' logo','div','s6','h1');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo '</div>';// s5
			if (isset($arr['user'])){
				Maket::divclass($MP[12],$Pth,'',' user');
				echo $service;
				echo '</div>';
			}
			echo '</div>';	
			
			break;
			}
			case 'tw':{
			Maket::divclass($MP[12],$Pth,'',' logo','div','s6','h1');
			echo '<div style="display:flex; flex-direction: column; justify-content: space-between;">';
			//вывод логотипов и главного лозунга
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			echo '</div>';// s5
			if (isset($arr['user'])){
				Maket::divclass($MP[12],$Pth,'',' user');
				echo $service;
				echo '</div>';
			}
			echo '</div>';	
			
			break;
			}		
		case 'mob':{
			Maket::divclass($MP[12],$Pth,'',' logo'.$arr['idmen'][0]);
			echo '<div>';
			if (isset($arr['owner']))	{
				$ownerdata.='<span>'.date("d m Y").' '.'</span><span>'.$arr['owner']->name.'</span>';
				if ($arr['owner']->telmain <> "" && $arr['owner']->email <> "") {
				if ($arr['owner']->telmain<>'no' && $arr['owner']->telmain<>'') $ownerdata.='<span>'.$arr['owner']->telmain.'</span>';
				if (filter_var($arr['owner']->email, FILTER_VALIDATE_EMAIL)) $ownerdata.='<span>'.$arr['owner']->email.'</span>';  
				}
			}
			elseif (isset($arr['user'])){
			$ownerdata.= '<span>'.date("d m Y").' '.'</span><span>'.$arr['user'][2].'</span>'.$str;
			if ($arr['user'][3]<> '') {
			if ($this->isValidEmail($arr['user'][3])) $ownerdata.= $str.'<span>'.$arr['user'][3].'</span>';  
					}
				}
			else $ownerdata='<span>'.date("d m Y").' '.'</span><span>Гость</span>';
			echo $ownerdata;
			echo '</div>';// s5
			echo '<div>';
			Page::scalimag3($arr,$img,'./?np='.$arr['nump'],$Pth,0);
			//вывод логотипов и главного лозунга
			echo '</div>';	
			Maket::divclass($MP[12],$Pth,'',' user');
			echo $service;
			echo '</div>';
			break;
		}	
	}
}

static function showpoiskempty($Pth='',$w='Найти',$t='text',$s=200,$m=50){
	echo '<form style="align:left;" method="post">';
	Maket::spanclass(Maket::divclasstr('poisk-'.$Pth['global']['idmen'],$Pth,'','','input name="poisk-chice" placeholder="'.$w.'" maxlength="'.$m.'" size="'.$s.'" type="'.$t.'"').'</input>',$Pth,'poisk-chice');
	$vendors=array('APC','HP');
	$vend=array('1','2');
	Maket::selmen($vendors,$vend,'./images/searchh.gif','');
	echo '</form>';
}

static function showheadercont($arr,$MP,$Pth,$vendors,$service,$selector='div',$is_banner=false){
	Maket::divclass($MP[1].'9',$Pth,'','',$selector);
	Maket::divclass($MP[17].'-'.$arr['idmen'][0],$Pth,'',' grid');
	Maket::divclass($MP[8],$Pth);
	Maket::showmaket($arr,$MP,$Pth,$vendors,$service,$is_banner);
	echo '</div>';
	echo '</div>';
	echo '</header>';
}

static function showheadergall($arr,$MP,$Pth,$vendors,$service,$selector='div',$pagn="",$swbut="", $nsl=1,$spbetw=10,$spg=1,$pagn_type="fraction",$loop=true){
	//- spg сколько прокручиваем, nsl-сколько выводим за раз, swbut-видимость кнопок прокрутки,pagn-видимость нумерации
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
		Maket::divclass($MP[1].$Pth[$MP[1]]['effect']['hhead'],$Pth,0,'',$selector);
		Maket::divclass($MP[17].'-'.$arr['idmen'][0].$Pth[$MP[17].'-'.$arr['idmen'][0]]['effect']['hhead'],$Pth);
			Maket::divclass('swiper-container',$Pth);//echo '<div class="swiper-container ">';
			echo '<div class="swiper-wrapper">';
			Maket::showmaket($arr,$MP,$Pth,$vendors,$service);
			echo '</div>';//swiper-wrapper
			 // Add Pagination -->
			if ($pagn <> '') echo '<div class="swiper-pagination"></div>';
			//Add Arrows -->
			if ($swbut <> '' ) {
			echo '<div class="swiper-button-next"></div>';
			echo '<div class="swiper-button-prev"></div>';
			}
			echo '</div>';//swiper-container
			echo '</div>';
			echo '</header>';
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
	
}

static function showheaderblog($arr,$MP,$Pth,$vendors,$service,$selector='div'){
	Maket::divclass($MP[1],$Pth,'','',$selector);
	Maket::divclass($MP[17].'-'.$arr['idmen'][0],$Pth,'',' grid');
	Maket::divclass($MP[8],$Pth);
	Page::scalimag3($arr,$arr['clas']['img'].$arr['namep'][0],'./?np='.$arr['nump'],$Pth,1);
	echo '</div>';
	Maket::divclass($MP[8],$Pth);
	Maket::showmaket($arr,$MP,$Pth,$vendors,$service);
	echo '</div>';
	echo '</div>';
	echo '</header>';
}

static function showheadermob($arr,$MP,$Pth,$vendors,$service,$selector='div',$n=0){
	Maket::divclass($MP[1].$disp.$n,$Pth,'','',$selector);
	Maket::divclass($MP[17].'-'.$arr['idmen'][0],$Pth);
	Page::scalimag3($arr,$arr['clas']['img'].$arr['namep'][0],'./?np='.$arr['nump'],$Pth,1);
	Maket::divclass($MP[8],$Pth);
	Maket::showmaket($arr,$MP,$Pth,$vendors,$service);
	echo '</div>';
	echo '</div>';
	echo '</header>';
}

static function showheaderflex($Pth,$clas_head,$arr_head,$clas){
	
	Maket::divclass('header',$Pth);//<div class="header flex">
	Maket::divclass('heads',$Pth,'',' flex');//<div class="heads flex">
	$nopt=count($clas_head)-1;
	Maket::showlogo($clas_head[0],$arr_head[0],$Pth,0);
	Maket::showlogo($clas_head[1],$arr_head[1],$Pth,1);
	Maket::showlogo($clas_head[2],$arr_head[2],$Pth,0);
	Maket::showlogo($clas_head[3],$arr_head[3],$Pth,0);
	/*foreach ($clas_head as $key=>$val){
		if($val==$clas)$mode=1;
		else $mode=0;
		if($key<$nopt)Maket::showlogo($val,$arr_head[$key],$Pth,$mode);
	}*/
	Maket::closediv(1);
	Maket::closediv(1);
	return $nopt;
}

static function showheadershop($Pth,$clas_head,$arr_head,$clas){
	
	Maket::divclass('header',$Pth,'',' flex');//<div class="header flex">
	//Maket::divclass('heads',$Pth);//<div class="heads flex">
	foreach ($clas_head as $key=>$val){
		if($val==$clas)$mode=1;
		else $mode=0;
		Maket::showlogo($val,$arr_head[$key],$Pth,$mode);
	}
	Maket::closediv(1);
}

static function showbootstrap($n,$screen,$clas='',$Pth=''){
	if ($clas=='') echo '<div class="container"><div class="col-'.$screen.'-'.$n.'"><div class="row">';
	else echo Maket::divclasstr($clas,$Pth).'<div class="col-'.$screen.'-'.$n.'"><div class="row">';
} 

static function closediv($n){
	$d='';
	for($i=0;$i<$n;$i++) $d.='</diV>';
	echo $d;
}

static function closedivstr($n){
	$d='';
	for($i=0;$i<$n;$i++) $d.='</div>';
	return $d;
}

static function icon_button($clasB,$clasI,$selector='button',$media=' hidden-md hidden-lg hidden-sm'){
	//Maket::spanclass(Maket::spanclasstr('',$Pth,$clasI,'i'),$clasB,$Pth,$selector,'','',$media);
	echo '<'.$selector.' class="'.$clasB.' '.$media.'"><i class="'.$clasI.'"></i></'.$selector.'>';
}

static function showpic($img_ban,$clas,$Pth,$lozung=''){
	if (file_exists($img_ban)) {
		$size = GetImageSize($img_ban);
		$ww=100;
		if($size[1]>0 && $size[1]>0) {
		if($size[1]>1200) $ww=900;
		elseif($size[1]>900) $ww=500;
		elseif($size[1]>500) $ww=300;
		elseif($size[1]>400) $ww=200;
		if ($size[0]>=$size[1]) $n=intval($size[1]/$ww);
		else $n=intval($size[0]/$ww);	
		if (is_array($arrmain['link']) && isset($arrmain['link']['namep'][0]) && $type_access=='local') echo $arrmain['link']['namep'][0];
		echo '<div style="background:  url('.$img_ban.') no-repeat scroll 20% 100%;background-size:cover;
		-moz-background-clip: initial; -moz-background-origin: initial; -moz-background-inline-policy: initial;width:100%; height:'.intval($size[1]/$n).'px;">';
		echo Maket::divclasstr($clas,$Pth,'','','a').$lozung.'</a>';
		echo '</div>';
		}
	  }
	  else echo Maket::divclasstr($clas,$Pth,'','','a').$lozung.'</a>';
}

static function carousel($arr,$Pth,$nb=0,$ne=0,$pref='data-fancybox-group="group"'){
	echo '<link rel="stylesheet" href="libs/fancybox/jquery.fancybox.css" />';
	echo '<link rel="stylesheet" href="libs/owl-carousel/owl.carousel.css" />';
	$clas=$arr['clas'];
	$typelist='imgt';
	$typelist1='imgt';
	$a_img=show::cleanmass($nb,$ne,$clas,$arr,$typelist,$typelist1);
	Maket::divclass('sider_container'.$arr['idmen'][0],$Pth);
	Maket::icon_button('next_button','fa fa-angle-right','div','');
	Maket::icon_button('prev_button','fa fa-angle-left','div','');
	Maket::divclass('carousel',$Pth);
	if ($a_img) {
		$a_link=$arr['link'];
		$a_imgs=$a_img[0];
		$a_text=$a_img[1];
	foreach($a_imgs as $key=>$value){
		echo Maket::divclasstr('slide_item',$Pth,'').'<a class="fancybox" '.$pref.'><img  src="'.$value.'"></img></a></div>';
		}
	}	
	echo '</div>';
	echo '</div>';
}

static function showitemsmaket($arr,$Pth,$i,$type_item){
$clas=$arr['clas'];
$numpage=$arr['nump'];
$a_link=$arr['link'];
$href='./?np=';
$text[$i]=Maket::part_text($arr['cont'][$i]);
if($text[$i]){
	switch($type_item){
		case '0':{
			if ($a_link <> '') {	
				echo '<div class="edit">';
				echo '<ul><a  name="zak'.$i.'"><span>'.$a_link['loz'][0].'<h2>'.$arr['loz'][0].'</h2><h3>'.$arr['imgt'][0].'</h3></span>'.$a_link['imgt'][0].'</a></ul>';
				echo '<ul><span>'.$a_link['conthref'][0].'</span><span class="text-center"><a '.$href.'>'.$text[0].'</a></span>'.$a_link['cont'][0].'</ul>';
				echo '</div>';
			}
			else{
				echo '<ul><a '.$href.' name="zak'.$i.'"><h2>'.$arr['loz'][0].'</h2><h3>'.$arr['loz'][1].'</h3></span></a></ul>';
				echo '<ul><span class="text-center"><a '.$href.'>'.$text[0].'</a></span></ul>';
			}
		break;
		}
		case '1':{
			if ($a_link <> '') {	
			echo '<div class="edit">';
			echo '<ul><a  name="zak'.$i.'"><span>'.$a_link['loz'][$i].'<h2>'.$arr['loz'][$i].'</h2><h3>'.$arr['imgt'][$i].'</h3></span>'.$a_link['imgt'][$i].'</a></ul>';
			echo '<ul><span>'.$a_link['conthref'][$i].'</span><span class="text-center"><a '.$href.'>'.$text[$i].'</a></span>'.$a_link['cont'][$i].'</ul>';
			echo '</div>';
		}
		else {
			echo '<ul><a '.$href.' name="zak'.$i.'"><h2>'.$arr['loz'][$i].'</h2><h3>'.$arr['imgt'][$i].'</h3></span></a></ul>';
			if (!strstr($text[$i],'https')) echo '<ul><span class="text-center"><a '.$href.'>'.$text[$i].'</a></span></ul>';
		}
		break;	
		}
		case '2':{
			if ($a_link <> '') {	
			echo '<div class="edit">';
			echo '<span>'.$a_link['imgs'][$i].'</span>';
			echo '<img src="'.$clas['img'].$arr['imgs'][$i].'" alt="Example" class="img-responsive">';
			echo '</div>';
			}
			else {
				
				if (!strstr($arr['cont'][$i],'https')) echo '<img src="'.$clas['img'].$arr['imgs'][$i].'" alt="Example" class="img-responsive">';
				else {
					echo '<div class="relation video">';
					echo '<div class="relation_ration_16x9"></div>';
					echo '<iframe class="relation_content" src="'.$arr['cont'][$i].'" allow="autoplay; encrypted-media" allowfullscreen></iframe>';
					echo '</div>';
					
				}
			}
		break;	
		}
		case '3':{
			if ($a_link <> '') {	
			echo '<div class="edit">';
			echo '<span>'.$a_link['imgs'][$i].'</span>';
			echo '<img src="'.$clas['img'].$arr['imgs'][$i].'" alt="Example" class="img-responsive">';
			echo '</div>';
			}
			else {
				if (!strstr($arr['cont'][$i],'https')) echo '<img src="'.$clas['img'].$arr['imgs'][$i].'" alt="Example" class="img-responsive">';
				else {
					echo '<div class="relation video">';
					echo '<div class="relation_ration_16x9"></div>';
					echo '<iframe class="relation_content" src="'.$arr['cont'][$i].'" allow="autoplay; encrypted-media" allowfullscreen></iframe>';
					echo '</div>';
				}
			}
			if ($a_link <> '') {	
			echo '<div class="edit">';
				
				echo '<ul><a  name="zak'.$i.'"><span>'.$a_link['loz'][$i].'<h2>'.$arr['loz'][$i].'</h2><h3>'.$arr['imgt'][$i].'</h3></span>'.$a_link['imgt'][$i].'</a></ul>';
				echo '<ul><span>'.$a_link['conthref'][$i].'</span><span class="text-center"><a '.$href.'>'.$arr['cont'][$i].'</a></span>'.$a_link['cont'][$i].'</ul>';
			echo '</div>';
			
		}
		else {
			echo '<ul><a '.$href.' name="zak'.$i.'"><h2>'.$arr['loz'][$i].'</h2><h3>'.$arr['imgt'][$i].'</h3></span></a></ul>';
			if (!strstr($arr['cont'][$i],'https')) echo '<ul><span class="text-center"><a '.$href.'>'.$arr['cont'][$i].'</a></span></ul>';
		}
		break;
		}
				
		}
	}
}

static function cardforblog($arr,$Pth,$clas,$i,$prefix,$nbl=0,$mode=0,$bbb=''){

	if ($nbl==0)$bbb=array(0=>$arr['n'][2],'1'=>$arr['n'][1],'2'=>$arr['n'][3],'3'=>$arr['n'][8],'4'=>$arr['n'][5]);
	
	//print_r($bbb);
	$Pth14=$arr["idmen"][0].'-'.$clas.'-text';
	$Pth13=$arr["idmen"][0].'-'.$clas.'-date';
	$Pth15=$arr["idmen"][0].'-'.$clas.'-img';
	$PthL=explode(';',$Pth[$Pth14]['numpar']['Sizes']);
	$PthM=explode(';',$Pth[$Pth13]['numpar']['Sizes']);
	$PthP=explode(';',$Pth[$Pth15]['numpar']['Pics']);
	$PthL0='font-size:'.$PthM[$i].';';
	$PthS0='font-size:'.$PthL[$i].';';
	$n=$PthP[$i+1];
	
	if($bbb[4]<>''){
	$img=$arr['clas']['img'].$bbb[4];
	$size = GetImageSize($img);
	//$n=Page::razmer($img,0,100*$n);
	$cardblog=Maket::divclasstr($Pth13,$Pth,$PthL0,$prefix,'li').'<p>'.$bbb[0].'</p>'.Maket::divclasstr($Pth15,$Pth,'',$prefix,'img src="'.$img.'" width:"'.intval($size[0]/$n).'px;" height:"'.intval($size[1]/$n).'px;"').
	Maket::spanclasstr(Maket::spanclasstr($bbb[1],$Pth,$clas.'-div','div'),$Pth,$clas.'-a','a href="'.$bbb[3].'"').'</li>'.Maket::divclasstr($Pth14,$Pth,$PthS0,$prefix,'li').$bbb[2].'</li>';
	
	if($mode==0) Maket::spanclass($cardblog,$Pth,$prefix,'div');
	else return $cardblog;
		
	}
}

static function view_text_key($arr,$typelist,$Pth,$key='',$n_opt=0,$mode=1){
	if($n_opt==0)$n_opt=count($arr[$typelist]);
	if(is_int($key)){
		if(strlen($arr[$typelist][$key])> 20)$n_simb=$mode*$Pth['Titem-content'.$key.'-'.$typelist.$key]['effect']['crop'];
		else $n_simb=0;
		$href='./?editp='.$Pth['Titem-content'.$key.'-'.$typelist.$key.$key]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-content'.$key.'-'.$typelist.$key]['id'];
		$cur_key=Maket::showlogo('content'.$key,$arr,$Pth,3,$key,$typelist.'href',$typelist,$n_simb);
		if($n_simb==0)echo '<a href="javascript:new_window(\''.$href.'\')">обрезать...</a>';
		return $cur_key;
	}
	else {
		unset($arr[$typelist]['link']);
		unset($arr[$typelist.'href']['link']);
		foreach($arr[$typelist] as $key1=>$value){
			if(strlen($arr[$typelist][$key1])> 20)$n_simb=$mode*$Pth['Titem-'.'content'.$key1.'-'.$typelist.$key1]['effect']['crop'];
			else $n_simb=0;
			if($key1<$n_opt){
				$href='./?editp='.$Pth['Titem-'.'content'.$key1.'-'.$typelist.$key1]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.'content'.$key1.'-'.$typelist.$key1]['id'];
				Maket::showlogo('content'.$key1,$arr,$Pth,3,$key1,$typelist.'href',$typelist,$n_simb);
				if($n_simb==0 && isset($Pth['adm'])) echo '<a href="javascript:new_window(\''.$href.'\')">обрезать...</a>';
			}
		}
		return $n_opt-1;
	}
}

static function view_loz_key($arr,$Pth,$key,$mode=0,$clas,$h='h1'){
	$disp=' '.$arr['idmen'][0];
	//echo '<h3>Заголовок H1 без ссылки</h3>';
	switch($mode){
		case '0':{
			echo '<div>';
			Maket::showlogo($clas.'-'.$h,$arr,$Pth,4,$key,'lozhref','loz',0);
			echo '</div>';
			break;
		}
		//echo '<h3>Заголовок H1 с ссылкой</h3>';
		case '1':{
			$clas_zag=explode('-',$clas);
			$n_simb=$Pth['Titem-'.$clas_zag[0].'-loz'.$key]['effect']['crop'];
			echo '<div>';
			Maket::showlogo($clas_zag[0].'-'.$h,$arr,$Pth,3,$key,'lozhref','loz',$n_simb);
			echo '</div>';
			break;
		}
		case '2':{
			echo '<div>';
			$clas.='-'.$h;
			if(strstr($clas,'-')) $clas_zag=explode('-',$clas);
			else $clas_zag[0]=$clas;
			$n_simb=$Pth['Titem-'.$clas_zag[0].'-loz'.($key+1)]['effect']['crop'];
			
			Maket::showlogo($clas.'-'.$h,$arr,$Pth,4,$key,'lozhref','loz',$n_simb,$disp);
			//if($n_simb==0 && isset($clas_zag[0])&& isset($Pth['adm']))echo '<a href="./?editp='.$Pth['Titem-'.$clas_zag[0].'-loz'.($key+1)]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.$clas_zag[0].($key+1).'-loz'.($key+1)]['id'].'">обрезать...</a>';
			echo '</div>';
			break;
		}
		case '3':{
			if(strstr('zag-h2','-'))$clas_zag=explode('-','zag-h2');
			else $clas_zag[0]='zag';
	//print_r($Pth['Titem-'.$clas_zag[0].'-loz'.($key+2)]);
	//$n_simb=$Pth['Titem-'.$clas_zag[0].'-loz'.($key+1)]['effect']['crop'];
	//echo '=='.$n_simb;
	//echo strlen($arrmain['loz'][$key+1]);
			if(strlen($arr['loz'][$key+1])>20){
			$n_simb=$Pth['Titem-'.$clas_zag[0].'-loz'.($key+1)]['effect']['crop'];
		//echo $n_simb;
			Maket::showlogo('zag-h3',$arr,$Pth,4,$key,'lozhref','loz',$n_simb,$disp);
			$href='./?editp='.$Pth['Titem-'.$clas_zag[0].'-loz'.($key+1)]['link_effect']['crop'].'00&tab=maket&par='.$Pth['Titem-'.$clas_zag[0].'-loz'.($key+1)]['id'];
			if($n_simb==0 && isset($clas_zag[0])&& isset($Pth['adm']))echo '<a href="javascript:new_window(\''.$href.'\')">обрезать...</a>';
		}
			else {
			Maket::view_loz_key($arr,$key,2,'zag','h4');
		}
			break;
		}
	//echo '<div>';
	}
}
//Макеты для стандартных дизайн-макетов

static function main_moduls($type_moduls,$value,$Pth,$container,$clas,$key){
	if($container<>'')Maket::divclass($container.$clas[$key].' ',$Pth,'');
	Maket::divclass($clas[$key],$Pth);
	$str='';
	
	switch($type_moduls) {
		case 'blockHd':{
			echo 'Блок хедера'.'-'.$clas[$key];
			break;
		}	
		case 'spisokUL':{
			
			if(is_array($value))foreach ($value as $val)$str.='<li class="'.$clas[$key].'-li">'.$val.'</li>';
			else $str.='<li class="'.$clas[$key].'-li">'.$value.'</li>';
			break;
		}
		case 'blockUs':{
			
			echo 'Блок пользователя'.'-'.$clas[$key];
			break;
		}	
		case 'blockSr':{
			echo 'Блок сервисный'.'-'.$clas[$key];
			break;
		}	
		case 'blockAd':{
			echo 'Блок администратора'.'-'.$clas[$key];
			break;
		}
		case 'blockSh':{
			echo 'Блок магазина'.'-'.$clas[$key];
			break;
		}
		case 'blockBt':{
			$str='';
			if(is_array($value))foreach ($value as $val)$str.='<li class="button-">'.$val.'</li>';
			else $str.='<div class="'.$clas[$key].'">'.$value.'</li>';
			//echo 'Блок кнопок навигации';
			break;
		}
		case 'blockMn':{
			echo 'Блок доп. меню'.'-'.$clas[$key];
			break;
		}
		case 'blockSw':{
			echo 'Блок слайдера'.'-'.$clas[$key];
			echo $value;
			break;
		}
		case 'blockCd':{
			echo 'Блок карточки товара'.'-'.$clas[$key];
			break;
		}
		case 'blockFm':{
			echo 'Блок формы'.'-'.$clas[$key];
			break;
		}
		case 'blockPf':{
			echo 'Блок портфолио'.'-'.$clas[$key];
			break;
		}
		case 'blockGl':{
			echo 'Блок галереи'.'-'.$clas[$key];
			break;
		}
		case 'blockCt':{
			echo 'Блок каталога'.'-'.$clas[$key];
			break;
		}
		case 'blockBl':{
			echo 'Блок блога'.'-'.$clas[$key];
			break;
		}
		case 'blockNw':{
			echo 'Блок новости'.'-'.$clas[$key];
			break;
		}
		case 'blockAc':{
			echo $value;
			break;
		}
		case 'blockFd':{
			echo 'Блок поиска'.'-'.$clas[$key];
			break;
		}
		case 'blockBs':{
			echo 'Блок корзины товаров'.'-'.$clas[$key];
			break;
		}
		case 'blockOr':{
			echo 'Блок заказа'.'-'.$clas[$key];
			break;
		}
		case 'blockFt':{
			echo 'Блок футера'.'-'.$clas[$key];
			break;
		}
		case 'blockTx':{
			echo 'Блок текстовый'.'-'.$clas[$key];
			break;
		}
		case 'blockLg':{
			echo 'Блок лого'.'-'.$clas[$key];
			break;
		}
}
Maket::spanclass($str,$Pth,$clas[$key].'-ul','ul');
if($container<>'')Maket::closediv(2);
else Maket::closediv(1);
}

static function showmodules($main_clas,$clas,$Pth,$arr_modul,$typmen,$nmod,$container=''){
	//print_r($nmod);
	if(isset($Pth[$main_clas]['numpar']['Grid']))$ngrid=$Pth[$main_clas]['numpar']['Grid'];
	else $ngrid = count($clas);
		Maket::divclass($main_clas,$Pth,'',' '.$typmen);
			foreach($arr_modul['val'] as $key=>$val){
				if($key<$nmod){
					Maket::spanclass($val,$Pth,$arr_modul['typ'][$key],'div');
					continue;
				}
				break;		
			}
	Maket::closediv(1);	
}

static  function scalimag3($arr,$img, $bbb,$Pth ,$numclass,$i=0,$typelist='namep',$typelist1='loz',$typelist2='list'){
$cla=$arr['clas'];
$clas=$cla['clas'][$numclass];
$PthCl12=$cla['clas'][12];
$PthCl13=$cla['clas'][13];
$PthCl14=$cla['clas'][14];
$PthC0=$clas.' '.$arr['idmen'][0];
$Pth12=$arr["idmen"][0].'-'.$PthCl12;	
$Pth14=$arr["idmen"][0].'-'.$PthCl12.'4-'.$PthCl14;
$Pth13=$arr["idmen"][0].'-'.$PthCl12.'4-'.$PthCl13;
if(isset($Pth[$clas]))	$size_par['pics']=$Pth[$clas]['numpar']['Pics'];

if(isset($Pth[$clas.'-item'.$i]))$PthL0='font-size:'.$Pth[$clas.'-item'.$i]['numpar']['Sizes'].'px;';
else $PthL0='font-size:'.$Pth[$clas]['numpar']['Sizes'].'px;';
if(isset($Pth[$PthC0]))$PthL1='font-size:'.$Pth[$PthC0]['numpar']['Sizes'].'px;';
else $PthL1=$PthL0;
if(isset($Pth[$PthC0]))$PthS0='font-size:'.(2*$Pth[$PthC0]['Sizes']).'px;';
else $PthS0=$PthL0;
if(isset($Pth[$clas]))$PthS1='font-size:'.(2*($Pth[$clas]['numpar']['Sizes']+2)).'px;';
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

//стили
 


if(isset($arr['link'])) $a_link=$arr['link'];
else $a_link = '';
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

$showimag='';
if (is_array($bbb)) {
	$img=$cla['img'].$bbb[4];
	$showimag.=Maket::divclasstr($Pth13,$Pth,$PthL0,$prefix,'li').'<p>'.$bbb[0].'</p><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'><a  href="'.$bbb[3].'"><span>'.$bbb[1].'</span></a></li>'.Maket::divclasstr($Pth14,$Pth,$PthS0,$prefix,'li').$bbb[2].'</li>';
}
else { 
	if($a_link <> ''){	
		if (isset($a_link[$typelist][$i+1]) && $clas == 'logo') $showimag.=Maket::divclasstr($clas.' '.$arr['idmen'][0],$Pth).$a_link[$typelist][$i+1];
		elseif(isset($a_link[$typelist][$i]) && $clas == '') $showimag.=$a_link[$typelist][$i];
		else $showimag.=$a_link[$typelist][$i];
		if (is_array($cla)) $showimag.='<li class="'.$Pth12.'4">';	
		if ($clas == 'logo' ) { 
			if (isset($arr[$typelist][$i+2]) && $arr['idmen'][0]<>'land') $showimag.='<div><li class="'.$clas.'"><a href="'.$bbb.'">'.Maket::divclasstr($clas,$Pth,'border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n),'-'.$n,'img  src="'.$img.'"').'</img></a></li><li class="'.$clas.'">'.$arr[$typelist][$i+2].$a_link[$typelist][$i+2].'</li></div>';
		    else $showimag.='<div><li class="'.$clas.'" style="margin:50px;"><a href="'.$bbb.'">'.Maket::divclasstr($clas,$Pth,'border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n),'-'.$n,'img  src="'.$img.'"').'</img></a></li></div>';
		   if (isset($arr[$typelist][$i+3])) $showimag.='<div><li class="'.$clas.' '.$arr['idmen'][0].'">'.Maket::divclasstr($clas,$Pth,$PthL0,'','span').$arr[$typelist][$i+3].'</span>';
		   if (isset($a_link[$typelist][$i+3])) $showimag.=$a_link[$typelist][$i+3].'</li></div>';
			//$showimag.='</div>';
		}
		elseif($clas == '') $showimag.='<a href="'.$bbb.'"><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'>';
		elseif(isset($arr[$typelist2][$i])) $showimag.=Maket::divclasstr($Pth13,$Pth,$PthS0,'','li').'<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'>'.$a_link[$typelist2][$i].'<a href="./?np='.$arr[$typelist2.'href'][$i].'">'.Maket::divclasstr($clas,$Pth,$PthL0,'','span').$arr[$typelist2][$i].'</span></a>'.$a_link[$typelist2.'href'][$i];
		$showimag.='</img></a></li>';
		if ($clas <> 'logo' && isset($a_link[$typelist1][$i]) && $clas <> '') {
			$showimag.=Maket::divclasstr($Pth14,$Pth,$PthL1,'','li');
			$showimag.=$a_link[$typelist1][$i].'<a href="./?np='.$arr[$typelist1.'href'][$i].'">'.$arr[$typelist1][$i].'</a>';
			$showimag.='</li>';
		}
		}
	else {
		//echo'-------------'.$arr[$typelist][$i+2];
		if ($clas == 'logo') {
			$showimag.='<div class="logo">';
			$showimag.=Maket::divclasstr($clas.'-logo',$Pth).'<a href="'.$bbb.'"><img  src="'.$img.'" border="0" width:"'.intval($size[0]/$n).'px;"  height:"'.intval($size[1]/$n).'px;"></img></a></div>';
			
			 if (isset($arr[$typelist][$i+3])) $showimag.=Maket::divclasstr($clas.'-item'.$i,$Pth).Maket::divclasstr($clas.' '.$arr['idmen'][0],$Pth,'','','li').Maket::spanclasstr($arr[$typelist][$i+3],$Pth,$clas.'-cont'.$i,'span','',"padding-left:5px;margin-top: auto;margin-bottom: auto; $PthL0").'</li>';
			 
			if ($arr['idmen'][0]<>'land') {
				$showimag.=Maket::divclasstr($PthC0,$Pth).Maket::divclasstr($PthC0.'-li',$Pth,'padding-left:20px;'.$PthL1,'','li').'<b>'.$arr[$typelist][$i+2].'</b></li></div>';
				//$showimag.='</div>';
			}
		}
		elseif($clas == 'main-banner') $showimag.='<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></img></li>';
		else {
		if (isset($arr[$typelist1][$i+1])) $showimag.='<div>'.Maket::divclasstr($Pth13,$Pth,'font-size:'.$size_parfs13,'li').'<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'><a href="./?np='.$arr[$typelist1.'href'][$i+1].'">'.Maket::divclasstr($clas,$Pth,$PthL0,'','span').$arr[$typelist1][$i+1].'</span></a></img>';
		$showimag.='</li>';
		Maket::divclass($Pth14,$Pth,'font-size:'.$size_parfs14,'li');
		$showimag.='<a href="./?np='.$arr[$typelist1.'href'][$i].'">'.$arr[$typelist1][$i].'</a>';
		$showimag.='</li></div>';
		}
	
	}
	}
	//$showimag.='</div>';	
}
}
return $showimag;
}

static function accordsh($typelist,$arr,$Pth,$typelist1='imgt',$ns=0,$n=0){
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

static function slidersh($act,$typelist,$arr,$Pth,$typelist1='imgt',$ns=0,$n=0) {
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

static function swipersh($typelist,$arr,$Pth,$typelist1='imgt',$ns=0,$n=0){
	$pagn="Y";
	$swbut="Y";
	$nsl=1;
	$spbetw=10;
	$spg=1;
	$pagn_type="fraction";
	$loop=true;
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
$str='';
$str.='<style>
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
		$str.='<div class="swiper-container">';
		$str.='<div class="swiper-wrapper">';
		foreach ($a_imgs as $key=>$val){
			if ($arr['idmen'][0] <> 'land') $href='./?np='.$arr[$typelist1.'href'][$key].'';
			else $href='./#zak'.$key;
	//show::infosh($href);	
			$imgt=$arr[$typelist1][$key];
			$img=$arr['clas']['img'].$arr[$typelist][$key];
		$size = GetImageSize($val); 
		if ($size[0]>=$size[1]) $n=intval($size[0]/$ww);
		else $n=intval($size[1]/$ww);
		if($key<$nim && $key>$ns) {
		if ($arr['idmen'][0] <> 'land') $href[$key]='href="./?np='.$arr[$typelist1.'href'][$key].'"';
		else $href[$key]='href="./?np='.$numpage.'#zak'.$key.'"';	
		$str.='<div class="swiper-slide">';
		//$str.=show::viewSlide($arr,1,$key,$typelist,$typelist1);
		if ($imgt)$str.='<div class="float_l"><a href="'.$href.'">'.$imgt.'</a></div>';	
			$str.='<div class="photo" style="background-size:cover"><a href="'.$href.'">
		<img  src="'.$img.'"/></a></div>';
		$str.='</div>';//swiper-slide
		}
		}
		$str.='</div>';//swiper-wrapper
		// Add Pagination -->
    $str.='<div class="swiper-pagination"></div>';
    //Add Arrows -->
    
		$str.='<div class="swiper-button-next"></div>';
		$str.='<div class="swiper-button-prev"></div>';

	//<!-- Swiper JS -->
  $str.='<script src="./scripts/swiper.min.js"></script>';
	//<!-- Initialize Swiper -->
	$str.="<script>
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
	$str.='</div>';//swiper-container

}
return $str;
}

static function menulistr($nn,$list1,$list2,$tabl,$clas,$typelist) {
$Menu=(object)array();	
$Menu->list1=$list1;
$Menu->list2=$list2;
$str='';
if ($Menu->list2=='' && $Menu->list1<>'') {
for ($i=0;$i<count($Menu->list1); $i++) {
		$Menu->list2[$i]='#';
		$str.='<span>'.$Menu->list1[$i].'</span>';
		if ($nn==1) $str.="<br>";
}
return;
}
else {
for ($i=0; $i<count($Menu->list2); $i++){
	if ($Menu->list2[$i]<>''){
	$pagelist= new Page($Menu->list2[$i],$tabl);
	if ($Menu->list1[$i]==''){		
		if ($nn==0) $Menu->list1[$i]=Page::getnamepage($pagelist);
		$sp=explode(';',$pagelist->MainAr['numpage']);
		if ($pagelist->MainAr['hrefp'] <> '') $Menu->list2[$i]=$pagelist->MainAr['hrefp'];
		else $Menu->list2[$i]=$pagelist->MainAr['hrefp'].'?np='.$sp[0]; 
		if ($Menu->list1[$i]<>'')$str.='<li><a  class="'.$clas.'" href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a></li>';
}
	else{
		$Menu->list2[$i]='./'.$pagelist->MainAr['hrefp'].'?np='.$Menu->list2[$i]; 
	if ($Menu->list1[$i]<>'') $str.='<li><a class="'.$clas.'" href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a></li>';
	}
	//if ($nn==1) echo "<br>";
}	
}
}

//Elementsw::Showobjtype($Menu->list1);
return $str;
}

static function portfolioItem($Pth,$card,$cat){
	$str = '<div class="mix col-md-3 col-sm-6 col-xs-12 portfolio_item category-'.$cat.'">
	<img src="img/portfolio-images/'.$card[0].'" alt="Alt" />
	<div class="port_item_cont">
		<h3>'.$card[1].'</h3>
		<p>'.$card[2].'</p>
		<a href="#" class="popup_content">'.$card[3].'</a>
	</div>
	<div class="hidden">
		<div class="podrt_descr">
			<div class="modal-box-content">
				<button class="mfp-close" type="button" title="Закрыть (Esc)">×</button>
				<h3>'.$card[1].'</h3>
				'.$card[4].'<img src="img/portfolio-images/'.$card[0].'" alt="Alt" />
			</div>
		</div>
	</div>
</div>';

	return $str;
}
//12/07/2020

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

static function formoneshowstr($arr){
	//for ($i=$nbegin;$i<($nbegin+$nform+3);$i++){
	//debug($arr);
	$i=0;
	$str='';
	if(!isset($arr['cls'][3])) $arr['cls'][3] = 'help-block text-danger';
	if(is_array($arr['name'])){
	foreach($arr['name'] as $val){	
		$dat[$i] = $arr['js'][$i].'="'.$arr['valid'][$i].'"';
		$str .='<label class="'.$arr['cls'][1].'">
		<span class="'.$arr['cls'][2].'">*</span> '.$arr['label'][$i];
		if ($arr['type'][$i]<>'textarea' && $arr['type'][$i]<>'hidden' ) $str .='<div><input type="'.$arr['type'][$i].'" name="'.$val.'" placeholder="'.$arr['place'][$i].'" '.$dat[$i].' '.$arr['req'][$i].'></div>';
		elseif($arr['type'][$i]== 'hidden') $str .='<div style="display:none;"><input type="'.$val.'" name="'.$val.'" placeholder="'.$arr['place'][$i].'" '.$dat[$i].' '.$arr['req'][$i].'></div>';
		else $str .='<div><textarea placeholder="'.$arr['place'][$i].'" name="'.$val.'" '.$dat[$i].' '.$arr['req'][$i].'></textarea></div>';
		$str .= '<span class="'.$arr['cls'][3].'"></span></label>';
		$i++;
	//echo '</div>';
	}
	}
	elseif($arr['name']<>'') {
		if ($arr['type'][$i]<>'textarea' && $arr['type'][$i]<>'hidden' ) $str .='<div><input type="'.$arr['type'][$i].'" name="'.$arr['name'].'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
		elseif($arr['type'][$i]== 'hidden') $str .='<div style="display:none;"><input type="'.$arr['name'].'" name="'.$arr['name'][$i].'" placeholder="'.$arr['place'][$i].'"  '.$arr['req'][$i].'></div>';
		else $str .='<div><textarea placeholder="'.$arr['place'][$i].'" name="'.$arr['name'].'" ></textarea></div>';	
	}
return $str;
}

static function showForm($Pth,$arr){
	$glsr = glossary();
	$str = '<form action="'.$arr['act'][0].'" class="'.$arr['cls'][0].'" novalidate target="_blank" method="'.$arr['method'][0].'">';	
	$str .= Maket::formoneshowstr($arr);
	$str .= '<button>'.$glsr['sd'].'</button>';
	$str .= '</form>';
return $str;
}

static function showColumns($clas, $arr){
	$str ='';
	foreach($arr as $key=>$val){
		$str .= '<div class="'.$clas.'__column">';
		$str .= $val;
		$str .= '</div>';
	}
	return $str;
}

static function showOneSlide($contentSlider, $i, $clas='mainslider'){
	$str ='';
	$str .='<div class="'.$clas.'__content content-'.$clas.'">'.
	$contentSlider['head'][$i].$contentSlider['body'][$i].$contentSlider['foot'][$i].
'</div>'.$contentSlider['img'][$i];
return $str;
}
static function showPriceFilter(){
	$str = '';
	$str .= '<div class="price-filter">
    <div class="price-filter__slider"></div>
    <div class="price-filter__vulues values-price-filter">
        <div class="values-price-filter__column">
            <div class="values-price-filter__label">от</div>
            <div class="values-price-filter__input">
                <input id="price-start" type="text" name="form[]" class="input" value="0">
            </div>
        </div>
        <div class="values-price-filter__column">
            <div class="values-price-filter__label">до</div>
            <div class="values-price-filter__input">
                <input id="price-end"  type="text" name="form[]" class="input" value="100000">
            </div>
        </div>
        
    </div>
</div>';
return $str;
}

static function showCompareFilter(){
	$str = '';
	$str .= '<div class="compare-filter">
	<div class="compare-filter__items">
		<div class="compare-filter__item">
			<a href="" class="compare-filter__link">NordicTrack C1020</a>
			<a href="" class="compare-filter__remove"></a>
		</div>
		<div class="compare-filter__item">
			<a href="" class="compare-filter__link">Clear Fit Luxur test drive good port 56 level 1234 rtrtr ryetyt rt34534</a>
			<a href="" class="compare-filter__remove"></a>
		</div>
		<div class="compare-filter__item">
			<a href="" class="compare-filter__link">Ammity ATM 720</a>
			<a href="" class="compare-filter__remove"></a>
		</div>
		<div class="compare-filter__footer">
			<a href="" class="compare-filter__button"><span>Сравнить</span></a>
			<a href="" class="compare-filter__clean"></a>
		</div>
	</div>
	</div>';
	return $str;

}

static function checkParametrFilter($arrCheck){
	$str = '';
	foreach($arrCheck as $val) {
		$str .= '<label for="" class="section-filter__checkbox checkbox">
		<input data-error="Ошибка" type="checkbox" class="checkbox__input" value="1" name="form[]">
		<span class="checkbox__text">'.$val.'</span></label>';
	}
return $str;
}

static function setClassesMaket($clas){
	$Maket_Properties = '';
	if(is_array($clas)){
		foreach($clas as $value){
			if(is_array($value) && !empty($value)){
				$Maket['length'][] = count($value); 
				$Maket_Properties .= maderec($value,1,',');
			}
			else {
				$Maket['length'][]  = 1;
				$Maket_Properties .= maderec($value,1,',');
			}	
		}	
	}
	else {
		$Maket['length'][]  = 1;
		$Maket_Properties .=  $clas;
	}
	$Maket_Properties .= '*'.maderec($Maket['length'],1,',');
	return $Maket_Properties;
	//$Maket_length = array(1,count($clasShop['main']),count($clasShop['header']),count($clasShop['navmenu'])
	//,count($clasShop['cat']),count($clasShop['hover']),count($clasShop['search']),count($clasShop['footer']));
	//$Maket_Properties =','.maderec($clasShop['main'],1,',').maderec($clasShop['header'],1,',').maderec($clasShop['navmenu'],1,',')
	//.maderec($clasShop['cat'],1,',').maderec($clasShop['hover'],1,',').maderec($clasShop['search'],1,',')
	//.maderec($clasShop['footer'],1,',').'*'.maderec($Maket_length,1,',');
}

static function getClassesMaket ($YourMakets,$nameSection){
	$YourMaket = explode('|',$YourMakets[0][10]);	
	$arrClasNumber = explode('*',$YourMaket[1]);	
	$mainClas = explode(',',$arrClasNumber[0]);
	$numbClas = explode(',',$arrClasNumber[1]); 
	$nsClas[0]=0;
	foreach( $numbClas as $i=>$val){
		if($i == 0)$nsClas[$i]=intval($nsClas[0]) ;
		else $nsClas[$i]= $nsClas[$i-1] + intval($numbClas[$i]);
		
	}
	//debug($nsClas);
	//die();
	$k=0;
	//$nameSection = array('id','main','header','navmenu','cat','hover','search','footer');
	foreach($mainClas as $i=>$val){
		if($i <= $nsClas[$k]) $clasShop[$nameSection[$k]][] = $val;
		else {
			$k++;
			if($k<count($nameSection))$clasShop[$nameSection[$k]][] = $val;
		}
	}
	return $clasShop;
}

}	
