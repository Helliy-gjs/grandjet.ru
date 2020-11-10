<?php
class Page extends Singleton {
  // атрибуты класса Page 
  //private $a='',$b='',$c='',$d='',$w=0,$h=0; 
  
  public $content,$numpage, $namenews, $zagtab=' ',$new;
  public $MainAr=array();
  public $title = 'GrandJet Service Ltd';
  //public $namepage, $tablepages, $tablenews;
  public $lozung= 'РЎРѕРІСЂРµРјРµРЅРЅР°СЏ СЌР»РµРєС‚СЂРѕРЅРЅР°СЏ С‚РµС…РЅРёРєР°';
  // операции класса Page 
  

public function __construct($numpage,$tabl,$uid=1){	
$this->table=array();
//$this->table[]=$tabl;
$arrpage=array();
$arrnews=array();
$LG=array();
$sw = Singleton::getInstance('StructureW');
$user = Singleton::getInstance('User');
$user->check();
//echo $user->getscountab('elemap','id','t');
$mode=$user->areyouAdmin($_SERVER['HTTP_HOST'],$user->getuserid());
$startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$_SERVER['HTTP_HOST'],$tabl['pages']);
$allpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_all',$tabl['pages']);
//if($mode)echo 'Вы администратор сайта';
//else echo 'Вы не администратор старт '.$startpage;
if($mode || $user->getscountab('elemap','id','t') == 0){//|| 
	$tab=$tabl['pages'];
	if(isset($numpage))$mass=$sw->getPagetable($numpage,$tabl['pages']);
	elseif(isset($allpage)) $mass=$sw->getPagetable($allpage,$tabl['pages']);
	elseif(isset($startpage)) $mass=$sw->getPagetable($startpage);
	else exit('Страницы сайта не найдены');
	$arrpage = $mass['pages'];
	if($arrpage[0]['namep'] !== ''){
		if($arrpage[0]['namep'] !== 'new_page' && $arrpage[0]['namep'] !== 'empty_page'){
			$what=$sw->isthatsite($arrpage['0']['site'], $arrpage['0']['numpage'], $tabl['pages']);
		}
		else {
			$config=Utils::getConfig($startpage);
			$mode=false;
			$arrpage[0]['namep']='banmain.jpg|logo.png|||';
			$arrpage[0]['site']= $_SERVER['HTTP_HOST'];
			$arrpage[0]['idauthor' ]=$user->getuserid();
			if($numpage != $startpage)$arrpage[0]['title' ]='title_gra_'.$_SERVER['HTTP_HOST'].'_'.$arrpage[0]['numpage'];
			else $arrpage[0]['title' ]='main_gra_'.$_SERVER['HTTP_HOST'];
			$arrpage[0]['configpage']=utils::getConfig(3,'configp',1);
			$what= true;
		}
	}
	else $what = false;
	//print_r($what);echo $arrpage['0']['numpage'].'-------|<br>';
	//if($arrpage['0']['numpage']=='')echo 'пустое значение';
	//if(is_object($what))$startpage=$sw->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$what->site,$tabl['pages']);
}
else {
	//$startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$_SERVER['HTTP_HOST'],$tabl['pages']);
	$tab='elemap';
	//print_r($numpage);
	if(isset($numpage))$mass=$user->getPagetable($numpage);
	elseif(isset($startpage)) $mass=$user->getPagetable($startpage);
	elseif(isset($allpage)) $mass=$user->getPagetable($allpage);
	else $mass=false;
	if(!$arrpage[0]['configpage'])$arrpage[0]['configpage']=utils::getConfig($allpage);
	if($mass){
		$arrpage = $mass['pages'];
		//print_r($arrpage['0']['site']);
		if($arrpage['0']['numpage']<>''){
		$what=$user->isthatsite($arrpage['0']['site'], $arrpage['0']['numpage'], $tabl['pages']);
		//echo '-------|'.$arrpage['0']['numpage'].'-------|'.$what->site;
		//if($arrpage['0']['numpage']=='')echo 'пустое значение';
		
	}
	else $what = false;
		
	}
	else { //echo "<script type='text/javascript'>window.top.location='http://start.php#rebuild';</script>";exit('No page');
	//header('Location: https://'.$_SERVER['HTTP_HOST'].'/start.php');exit();
	}
}

//print_r($mass);
//$what=$sw->isthatsite($arrpage['0']['site'], $arrpage['0']['numpage'], $tabl['pages']);


if (isset($numpage)) $this->numpage=$numpage;
else $this->numpage=$startpage;

if (isset($what)){
	//print_r($what);
// Cоздаем массив данных загруженных из таблицы бд
$this->MainAr['hreflist']='';
$this->MainAr['numpage']=$arrpage['0']['numpage'];
$this->MainAr['idmenu']=$arrpage['0']['idmenu'];
$this->MainAr['idauthor']=$arrpage['0']['idauthor'];
$this->MainAr['list']=$arrpage['0']['list'];
$this->MainAr['confp']=$arrpage[0]['configpage'];
if($this->MainAr['idmenu']<>'land'){
	$this->MainAr['hreflist']=$arrpage['0']['list_href'];
}
else {
	$AL=explode(';',$arrpage['0']['list']);
	foreach($AL as $val)$this->MainAr['hreflist'].=$startpage.';';
}

$this->MainAr['buttimg']=$arrpage['0']['buttimg'];
$this->MainAr['buttons']=$arrpage['0']['buttons'];
$this->MainAr['content']=$arrpage['0']['content'];
$this->MainAr['lozung']=$arrpage['0']['lozungp'];
$this->MainAr['namep']=$arrpage['0']['namep'];
$this->MainAr['hrefimage']=$arrpage['0']['hrefimage'];
$this->MainAr['imgtext']=$arrpage['0']['imgtext'];
$this->MainAr['hrefp']=$arrpage['0']['hrefp'];
$this->MainAr['typemenu']=$arrpage['0']['typemenu'];
$this->MainAr['hrefscripts']=$arrpage['0']['hrefscripts'];
$this->MainAr['hrefstyle']=$arrpage['0']['hrefstyle'];
$this->MainAr['title']=$arrpage['0']['title'];
$this->MainAr['levelmenu']=$arrpage['0']['levelmenu'];
$this->MainAr['zagtab']=Menu::LOZUNG;
$this->MainAr['butthref']=$arrpage['0']['butthref'];
$this->MainAr['imagehref']=$arrpage['0']['hrefimage'];
if($user->getLevelnew($uid)>4 ) $this->MainAr['configpage']=$arrpage['0']['configpage'];

if($arrpage['0']['idnews']<>''){
	if(strstr($arrpage['0']['idnews'],';'))$this->MainAr['idnews']=explode(';',$arrpage['0']['idnews']);
	else $this->MainAr['idnews']=$arrpage['0']['idnews'];
}	
$this->MainAr['keywords']=$arrpage['0']['keywords'];
$this->MainAr['site']=$arrpage['0']['site'];
if ($arrpage['0']['lozungp']<>'') $LG=explode('|',$arrpage['0']['lozungp']);
//установка значений по умолчанию
//Технический укникальный тайтл
//if ($this->MainAr['title'] == '' ) $this->MainAr['title']='main_gra_'.$this->MainAr['site'].'_'.$this->MainAr['numpage'];
//Удаление пустых элементов массивов, если они есть
//из лозунгов
//$sw = Singleton::getInstance('StructureW');
if($tab==$tabl['pages']) {
//echo 'lozung';
if (strstr($this->MainAr['lozung'],'|') && $mode) {
	$mass2=$sw->reloadmass($LG['1'],$LG['0'],';',';',$tabl['pages']);
	$LG['1']=$mass2[0];
	$LG['0']=$mass2[1];
	$this->MainAr['lozung']=$LG[0].'|'.$LG[1];
}	
//из кнопок и списков
//echo 'buttons';
if (strstr($this->MainAr['buttons'],'|') && $mode) {
	$balv=explode('|',$this->MainAr['buttons']);
	if($balv[1]<>'') {
		$mass2=$sw->reloadmass($balv[1],$balv[0],';',';',$tabl['pages']);	
		$this->MainAr['buttons']=$mass2[1].'|'.$mass2[0];
	}
	}
//echo 'footers';	
if (strstr($this->MainAr['butthref'],'|') && $mode) {
	$balv=explode('|',$this->MainAr['butthref']);
	if($balv[1]<>'') {
		$mass2=$sw->reloadmass($balv[1],$balv[0],';',';',$tabl['pages']);	
		$this->MainAr['butthref']=$mass2[1].'|'.$mass2[0];
	}
	}	
//echo 'list';
if($this->MainAr['hreflist']<>'' && $mode){
	$mass2=$sw->reloadmass($this->MainAr['hreflist'],$this->MainAr['list'],';',';',$tabl['pages']);
	//$this->MainAr['hreflist']=$mass2[0];
	//$this->MainAr['list']=$mass2[1];
}
}

// параметры новости или блога
if($this->MainAr['idnews']>0){
	
	$news=$sw->getnews($this->MainAr['idnews'],$tabl['news']);
	$arrnews = $news;
	$this->MainAr['namenews']=$arrnews['0']['name'];
	$this->MainAr['datenews']=$arrnews['0']['date'];
	$this->MainAr['textnews']=$arrnews['0']['text'];
	$this->MainAr['vendnews']=$arrnews['0']['vendor'];
	$this->MainAr['grnews']=$arrnews['0']['group'];
	$this->MainAr['imgnews']=$arrnews['0']['imgnews'];
	$this->MainAr['hrefnew']=$arrnews['0']['hrefnew'];
}
}
//else exit();

return $this->MainAr;
}


/*
public function viewer_page_head($t){
echo '<div style="position: relative; top: 0px; left: 50px; color: rgb(0, 0, 102)" ><h3>'.$t.'</h3></div>';
}*/


public function __get($name){
  return $this->name;
  }
  
public function __set($name, $value)
  {
    $this->name = $value;
  }
public function namebutthref($np,$tabl){
	if ($np) $Page_np=new Page($np, $tabl);
	foreach ($Page_np->butthref as $val){
		$Page_np1=new Page($val, $tabl);
		$namepage[$val]=$Page_np1->namep;
		}
	return $namepage;
}

function part_name($str,$dlt='='){
	if(strstr($str,$dlt)) $res=explode($dlt,$str);
	else $res[0]=$str;
	return $res[0];
}

function part_text($str,$n=1,$dlt='='){
	if(strstr($str,$dlt)) $res=explode($dlt,$str);
	else $res[0]=$str;
	return $res[$n];
}

function part_texts($str){
	if(strstr($str,'=')) $res=explode('=',$str);
	else $res[0]=$str;
	return $res;
}

public function getnamepage2($pagelist){
	
	$l=explode('|',$pagelist);
	if (!strstr($pagelist,'.jpg') && !strstr($pagelist,'.png') && !strstr($pagelist,'.gif'))
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
	
return $result;
}


public function getnamepage($pagelist,$dlt='='){
	if(isset($pagelist->MainAr['namep'])){
		$l=explode('|',$pagelist->MainAr['namep']);
		if (!strstr($pagelist->MainAr['namep'],'.jpg') && !strstr($pagelist->MainAr['namep'],'.png') && !strstr($pagelist->MainAr['namep'],'.gif'))
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
	}
	else return false;
return $lst0;
}

public function Page_Composite($np,$typelist,$arr,$tabl,$i=0){
$arrN=array();
$arrC=array();
$arrI=array();
$arrB=array();
$arrL=array();
$Page_ar=array();
$buttons=array('','');
$content=array('','');
$butthref=array('','');
$hrefimag=array('','');
$textimage=array('','');
//print_r($tabl);
if ($np) $Page_np=new Page($np, $tabl);
//print_r($Page_np);
$Page_np->MainAr['hreflist'] = '';
$Page_np->MainAr['content'] = '';
$Page_np->MainAr['hrefimage'] = '';
$Page_np->MainAr['butthref'] = '';
$Page_np->MainAr['buttons'] = '';
$Page_np->MainAr['imgtext'] = '';
$arrH['lozung']='';
$arrV['lozung']='';
//print_r($arr);
//echo '<br>';
if ($arr) {
	//echo 'массив страниц ';
	foreach($arr as $val){
		//echo $val;
		if ($val) {$PageC= new Page($val, $tabl);
			$Page_ar[$val]=$PageC->MainAr;
			//print_r($Page_ar[$val]);echo '<br>';
		}
	}
		//echo 'создан';	
		//print_r($Page_ar);
foreach ($arr as $key=>$value) {
		
		$arrN=explode('|',$Page_ar[$value]['namep']);
		if (count($arrN)>1) $k=1;
		else $k=0;
		//раскладываем содержимое страницы по массивам
		if($Page_ar[$value]['imgtext']<>''){
			$imgtext=explode('|',$Page_ar[$value]['imgtext']);
			$arrIT[0]=explode(';',$imgtext[0]);
			$arrIT[1]=explode(';',$imgtext[1]);
		}
		if($Page_ar[$value]['lozung']<>''){
			$L=explode('|',$Page_ar[$value]['lozung']);
			$arrL[0]=explode(';',$L[0]);
			$arrL[1]=explode(';',$L[1]);
		}
		if($Page_ar[$value]['buttons']<>''){
			$butt=explode('|',$Page_ar[$value]['buttons']);
			$arrB[0]=explode(';',$butt[0]);
			$arrB[1]=explode(';',$butt[1]);
		}
		if($Page_ar[$value]['content']<>''){
			$cont=explode('|',$Page_ar[$value]['content']);
			$arrC[0]=explode(';',$cont[0]);
			$arrC[1]=explode(';',$cont[1]);
		}
		if($Page_ar[$value]['hrefimage']<>'')$arrI=explode(';',$Page_ar[$value]['hrefimage']);
		if($Page_ar[$value]['butthref']<>'')$arrBH=explode(';',$Page_ar[$value]['butthref']);
		if($Page_ar[$value]['list']<>'')$arrLS=explode(';',$Page_ar[$value]['list']);
		else $arrLS[0]=$Page_ar[$value]['list'];
		//формируем значения композитной страницы
		if (isset($arrLS[$i])){
			$list=$arrLS[$i];
			if ($key < count($arr)-1) $list.= ';';
			if ($Page_ar[$value]['hreflist']<>'')$arrLH=explode(';',$Page_ar[$value]['hreflist']);
			else $arrLH=$Page_ar[$value]['hreflist'];
			if(isset($arrLH[$i]))$listhref=$arrLH[$i];
			if ($key < count($arr)-1) $listhref.= ';';
		}
		if ($arrN[$k]<> '') $buttons[0] .= $arrN[$k];
		else $buttons[0].=$Page_ar[$value]['namep'];//$this->namebutthref($arrBH[$i],$tabl);
		if ($key < count($arr)-1) $buttons[0] .= ';';
		$content[0] .= $arrC[0][$i];
		if ($key < count($arr)-1) $content[$i] .= ';';
		$content[1] .= $arrC[1][$i];
		if ($key < count($arr)-1) $content[1] .= ';';
		$buttons[1].= $Page_ar[$value]['numpage'];
		if ($key < count($arr)-1) $buttons[1].= ';';
		if(isset($arrBH[$i])) $butthref.=$arrBH[$i];
		if ($key < count($arr)-1) $butthref.= ';';
		if(isset($arrI[$i]))$hrefimag.=$arrI[$i];
		if ($key < count($arr)-1) $hrefimag.= ';';
		//$Page_np->MainAr['hrefimage'] .= $Page_ar[$value]['hrefimage'];
		//if ($key < count($arr)-1) $Page_np->MainAr['hrefimage'] .= '|';
		if(isset($arrIT[0][$i]))$textimage[0].= $arrIT[0][$i];
		if(isset($arrIT[1][$i]))$textimage[1].= $arrIT[1][$i];
		if ($key < count($arr)-1) {$textimage[0] .= ';';$textimage[1] .= ';';	}
		if($Page_np->MainAr['lozung'] == '') {
			if ($arrL[0][$i]<> '') $arrV ['lozung'] .= $arrL[0][$i];
			if ($arrL[1][$i]<> '') $arrH ['lozung'].=$arrL[1][$i];
			if ($key < count($arr)-1 && $arrV<>'' && $arrH<>'') {
				$arrV ['lozung'] .= ';';
				$arrH ['lozung'].=';';
			}
			}
	}
$Page_np->MainAr['lozung'] .=$arrV ['lozung'].'|'.$arrH ['lozung'];
$Page_np->MainAr['buttons']=$buttons[0].'|'.$buttons[1];
$Page_np->MainAr['butthref']=$butthref;
$Page_np->MainAr['hrefimage']=$hrefimag;
$Page_np->MainAr['list']=$list;
$Page_np->MainAr['list_href']=$listhref;
$Page_np->MainAr['imgtext']=$textimage[0].'|'.$textimage[1];
$Page_np->MainAr['cont']=$content[0].'|'.$content[1];


}
return $Page_np->MainAr;
}
  
function intoperation($param) {
  $this->content = $param;
  echo $this->content;
  }
  
function DisplayConnBD($conn){
  if (!conn){
	echo "РќРµ РјРѕРіСѓ РїРѕРґРєР»СЋС‡РёС‚СЊСЃСЏ Рє СЃРµСЂРІРµСЂСѓ MySQL";
	echo "ERROR ".mysql_errrno()." ".mysql_error()."/n";
	exit;
	}
	else 
	{
		echo "РЈСЃРїРµС€РЅРѕРµ РїРѕРґРєР»СЋС‡РµРЅРёРµ Рє Р±Р°Р·Рµ РґР°РЅРЅС‹С…";
	echo "<BR>";
	echo "Р’ Р±Р°Р·Рµ СЃСѓС‰РµСЃС‚РІСѓСЋС‚ СЃР»РµРґСѓСЋС‰РёРµ С‚Р°Р±Р»РёС†С‹:";
	echo "<BR>";
}
$result = mysql("grandjetShop","SHOW TABLES",$conn);
while (list($table) = mysql_fetch_row($result)) {
print("$table<br>\n");
}
}
/*
public function DisplayHead(){
  echo "<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='ru' lang='ru' dir='ltr'>\n<head>\n";
	//echo '<meta content="text/html; charset=UTF-8" http-equiv="Content-Type" />';
	echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
    $this -> DisplayTitle(); 
    $this -> DisplayKeywords(); 
    $this -> DisplayStyles(); 
	echo "<script language='Javascript' src='./scripts/message.js' type='text/javascript'></script>";
	echo "<script language='Javascript' src='./scripts/proba.js' type='text/javascript'></script>";
	echo "<link rel='STYLESHEET' href='./images/message.css' type='text/css'/>";
	echo "<link rel='STYLESHEET' href='./images/style.css' type='text/css'/>";
    echo "</head>\n"; 
    }
	
public function Display()   { 
    $this->DisplayHead();
    echo "<body>\n"; 
    $this -> DisplayHeader(); 
    //$this -> DisplayLine();
	echo $this->content; 
	$this -> DisplayFooter(); 
    echo "</body>\n</html>\n";
	} 
  public function DisplayTitle()   { 
    echo '<title> '.$this->title.' </title>';
  } 
  public function DisplayLine() {
  ?>
  <table style="text-align: left; width: 900px; height: 30px;" border="0" cellpadding="0" cellspacing="0">
   <tr>
      <td style="width: 16px; height: 27px;" background="http://location/CorpaZona/images/1/cross1.jpg"></td>
      <td style="width: 816px; height: 27px;" background="./images/1/line6.jpg"> <img src = "./images/1/line6.jpg" /></td>
      <td style="width: 29px; height: 27px; background-image: ./images/1/corner1righttop.jpg"></td>
    </tr></table>
  <?php
  }
  
  public function DisplayKeywords()  
  { 
echo "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\"/>";
//    echo "<meta name=\"keywords\" content=\"".htmlentities($this->keywords)."\" />";

    echo "<meta name=\"keywords\" content=\"".htmlentities($this->keywords)."\" />";
  } 
  public function DisplayStyles()   { 
?>  
<meta http-equiv="Content-Type" content="text/html charset=UTF-8"/> 
  <style>
    h1 {color:blue; font-size:24pt; text-align:center; 
        font-family:arial,sans-serif}
    .menu {color:white; font-size:12pt; text-align:center; 
           font-family:arial,sans-serif; font-weight:bold}
    td {background:white}
    p {color:red; font-size:12pt; text-align:justify; 
       font-family:arial,sans-serif}
    p.foot {color:red; font-size:7pt; text-align:center; 
            font-family:arial,sans-serif; font-weight:bold}
    a:link,a:visited,a:active {color:red}
  </style>
<?php
  } 

  public function DisplayHeader() 
  { 
?>   
<style> 
p.head {color:white; background: red; font-size:9pt; text-align:justify; 
       font-family:arial,sans-serif}
	   </style>
      <span class="head">РЎРѕРІСЂРµРјРµРЅРЅР°СЏ СЌР»РµРєС‚СЂРѕРЅРЅР°СЏ С‚РµС…РЅРёРєР°  
	<?php 
	$this -> DisplayMenuMain(); 
	?>
	</span>
	 <?php
  } 

  public function DisplayMenu($buttons) 
  { 
    echo "<table width = '50%' bgcolor = 'white' cellpadding = '4' 
           cellspacing = 4>\n"; 
    echo "  <tr>\n"; 

    // вычисление размеров кнопки 
    $width = 50/count($buttons); 
    while (list($name, $url) = each($buttons)) 
    { 
      $this -> DisplayButton($name, $url, 
                             !$this->IsURLCurrentPage($url)); 
    } 
    echo "  </tr>\n"; 
    echo "</table>\n"; 
  } 

  public function IsURLCurrentPage($url) 
  { 
    if(strpos( $_SERVER['PHP_SELF'], $url )==false) 
    { 
      return false; 
    } 
    else 
    { 
      return true; 
    } 
  } 
  
  public function structDIV_page ($width, $h, $cs, $img, $width2, $list1,$list2  ) {
 $nstr=count($list1);
  echo '<div background='.$img[0].'height='.(4*$h-3).' border=0 width='.$width.'px cellpading=0 cellspacing=0 style="margin-right:auto;margin-left:auto;">';
echo '<table border=0 width='.$width.'px cellpading=0 cellspacing=0 style="margin-right:auto;margin-left:auto;">';
   echo '<tr height='.(4*$h-3).'><td colspan='.$cs.' background='.$img[0].'></td></tr>';
   echo '<tr height='.($nstr*$h*$cs*2).'px><td valign=top width='.$width2.'px background='.$img[1].'><td></td><br>';
   echo '<center><div width='.($width2-20).'px height='.$h.'px border=0 CELLPADDING=1>';
   for ($i=0; $i<count($list1); $i++){
   $page= new Page($list2[$i], $tabl);
   $name=explode('|',$page->MainAr['namep']);
   $sp=explode(';',$page->MainAr['numpage']);
   if(!$levuser==0) $list2[$i]=$page->MainAr['hrefp'].'?np='.$sp[0];
		else {
			if($sp[0]==7) $list2[$i]='?new=1';
		else $list2[$i]='?np='.$sp[$i];
		}
    echo '<tr height=5><td></td></tr><tr height='.($h/2+2).'><td class=menu>';
	echo '<a class=menu href="'.$list2[$i].'">'.$list1[$i].'</a></td></tr>';
     }
	  echo '<tr><td><br><br><A class=menu HREF="index.php?id=28">Архив новостей</A>';
	 echo '</div></td><td ALIGN=center VALIGN=top width=750 background=./images/Images/bg2.gif></td></tr>';
echo  '</div>';
  
  }	 
  
 public function structure_page ($width, $h, $cs, $img, $width2, $list1,$list2  ) {
   //if (isset($list1)) $Menu->list1=$list1;
   //if (isset($list2)) $Menu->list2=$list2;
   //Elementsw::Showobjtype($list2);
   $nstr=count($list1);
   echo '<table border=0 width='.$width.'px cellpading=0 cellspacing=0 style="margin-right:auto;margin-left:auto;">';
   echo '<tr height='.(4*$h-3).'><td colspan='.$cs.' background='.$img[0].'></td></tr>';
   echo '<tr height='.($nstr*$h*$cs*2).'px><td valign=top width='.$width2.'px background='.$img[1].'><td></td><br>';
   echo '<center><table width='.($width2-20).'px height='.$h.'px border=0 CELLPADDING=1>';
   for ($i=0; $i<count($list1); $i++){
   $page= new Page($list2[$i], $tablepages,$tablenews);
   $name=explode('|',$page->MainAr['namep']);
   $sp=explode(';',$page->MainAr['numpage']);
   if(!$levuser==0) $list2[$i]=$page->MainAr['hrefp'].'?np='.$sp[0];
		else {
			if($sp[0]==7) $list2[$i]='?new=1';
		else $list2[$i]='?np='.$sp[$i];
		}
    echo '<tr height=5><td></td></tr><tr height='.($h/2+2).'><td class=menu>';
	echo '<a class=menu href="'.$list2[$i].'">'.$list1[$i].'</a></td></tr>';
     }
	 echo '<tr><td><br><br><A class=menu HREF="index.php?id=28">Архив новостей</A>';
	 echo '</table></td><td ALIGN=center VALIGN=top width=750 background=./images/Images/bg2.gif></td></tr>';
	
	 //echo '<table border=0><tr><td></td><td></td><td><A class=menu HREF="index.php?id=28">Архив новостей</A></center></td></tr>';
}  
*/
  public function DisplayButton($name,$width,$pic, $url, $active = true) 
  { 
    if ($active) 
    { 
      echo "<div width ='".htmlentities($width)."%'>
            <a href ='".htmlentities($url)."'>
            <img src ='".$pic."' alt ='".htmlentities($name)."' border
             ='0' /></a>
            </div>";
    } 
    else 
    { 
      echo '<a href ="'.htmlentities($url).'"><span class="button">'.$name.'"</span></a>';
    } 
  } 

  public function DisplayButDiv($name, $url,$clas, $nc,$nopt, $active = true,$img='') 
  { 
  	if ($nopt>7) $nopt=7;
		
	if ($active) 
    { 
		
     if ($img == './images/') echo '<div class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($url).'">'.$name.'</a></div>';
	 else echo '<div class="menu-'.$clas['clas'][$nc].'" style="background-image: url('.$img.')"><a href ="'.htmlentities($url).'">'.$name.'</a></div>'; 
	    } 
    else 
    { 
		
       echo '<li class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($url).'"> '.$name.' </a>
            </li>';
    } 
	
  }   
  
  public function DisplayButArr($butt_link,$butthref_link,$img_link,$name, $url,$arr, $nc,$nopt,$active = true,$img='') { 
  	$clas=$arr['clas'];
	if ($nopt>9) $nopt=9;
	
	if ($active) { 
     if ($img == './images/') echo '<div class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($url).'">'.$butt_link.$name.'</a>';
	 else {
		echo '<div class="menu-'.$clas['clas'][$nc].'" style="background-image: url('.$img.')">';
		if ($img_link <> '' ) echo $img_link;
		
		echo '<a href ="'.htmlentities($url).'">'.$name.'</a>';
		if ($butt_link<>'') echo $butt_link;
		}
	    if ($butthref_link <> '') echo $butthref_link; 	
		echo '</div>';
		} 
    else 
    { 
		if ($butt_link<>'' ) echo $butt_link;
       echo '<li class="'.$clas['clas'][$nc].'"><a href ="'.htmlentities($url).'"> '.$name.' </a>';
       if ($butthref_link <> '') echo $butthref_link.'</li>';     
    } 	
  }   
 /* 
  public function DisplayFooter()   { 
?> 
    <table colspan="2" width = "50%" bgcolor = "red" cellpadding ="12" border ="0"> 
    <tr> 
      <td> 
        <p class="foot">&copy; Grandjet Service Ltd.</p>
        <p class="foot">РџРѕР¶Р°Р»СѓР№СЃС‚Р°, Р·Р°СЂРµРіРёСЃС‚СЂРёСЂСѓР№С‚РµСЃСЊ Рё  РїСЂРѕСЃРјРѕС‚СЂРёС‚Рµ
      <a href="./registration/index.php">РЅР°С€Сѓ СЃС‚СЂР°РЅРёС†Сѓ СЃ РѕС„РёС†РёР°Р»СЊРЅРѕР№ РёРЅС„РѕСЂРјР°С†РёРµР№ </a></p> 
      </td> 
    </tr> 
    </table>
<?php 
  } 
  
public function DisplayOptMenu($Val, $mes1, $mes2, $mes3, $mes4, $optmenu, $sdvigh, $sdvigw,$i){
echo "<td><div class='center' id='".$this->Mid[$i]."'><input type='text' value='$Val' size='16' onclick="."'showmenu2("."\"$mes1\"".","."\"$mes2\"".","."\"$mes3\"".","."\"$mes4\"".","."$optmenu".","."$sdvigh".","."$sdvigw".","."\"$Val\"".")'/></div>";
}

public function DisplayOM($Val, $array, $optmenu, $sdvigw,$i){
	echo "<td><div class='center' ><input type='text' value='$Val' size='16' onclick="."'showmenu2("."\"$array[0]\"".","."\"$array[1]\"".","."\"$array[2]\"".","."\"$array[3]\"".","."$optmenu".","."$sdvigh".","."$sdvigw".","."\"$Val\"".")'/></div>";
}

public function DisplayMenuMain(){
$this->DisplayOptMenu($this->Mmes[0],'РСЃС‚РѕСЂРёСЏ', 'РљР»РёРµРЅС‚С‹','РђСЃСЃРѕСЂС‚РёРјРµРЅС‚','РњРёСЃСЃРёСЏ', 1, 12, 162,0);
$this->DisplayOptMenu($this->Mmes[1],'РџРѕСЃС‚Р°РІРєРё', 'РћР±СЃР»СѓР¶РёРІР°РЅРёРµ','РњР°СЂРєРµС‚РёРЅРі','РРЅС‚РµСЂРіР°С†РёСЏ', 2, 12, 349,1);
$this->DisplayOptMenu($this->Mmes[2],'Р“РѕСЃС‚РµРІРѕР№ РІС…РѕРґ', 'Р РµРіРёСЃС‚СЂР°С†РёСЏ','РџСЂР°РІРёР»Р°','РџР°СЂС‚РЅРµСЂСЃС‚РІРѕ', 3, 12, 494,2);
$this->DisplayOptMenu($this->Mmes[3],'РљРѕРјРїСЊСЋС‚РµСЂС‹', 'РџРµСЂРёС„РµСЂРёСЏ','РЎРµС‚Рё','РљРѕРјРїРѕРЅРµРЅС‚С‹', 4, 12, 640,3);
$this->DisplayOptMenu($this->Mmes[4],'РРЅС„РѕСЂРјР°С†РёСЏ', 'Р РµР·РµСЂРІС‹','Р—Р°РєР°Р·С‹','РћРїР»Р°С‚Р°', 5, 12, 786,4);
//echo '<script type="text/javascript">taginput("Меню6","сообщение6", "содержание6","описание6","результат6", 1, 136, -216)</script>';
}


public function BeginShowMenu($mes1, $mes2, $mes3, $mes4, $optmenu, $sdvigh, $sdvigw){
echo "<input type='text' class='opt-menu' value='РџРѕРєР°Р·Р°С‚СЊ РіР»Р°РІРЅРѕРµ РјРµРЅСЋ'  size='30' onclick='DisplayMenuMain()'/>";
}
public function DisplayOptMenu2($Val, $mes1, $mes2, $mes3, $mes4, $optmenu, $sdvigh, $sdvigw){
$str="";
foreach ($buttons as $key=>$val)
	{
$str=$str."\'".$key."\'".",";
	}
//$str="\"$mes1\"".","."\"$mes2\"".","."\"$mes3\"".","."\"$mes4\"".",";
echo "<input type='text' name='butt1' value="."$Val"." size='30' onmouseover="."'showmenu2(".$str."$optmenu".","."$sdvigh".","."$sdvigw".")'/>";
}
*/
public function inpbl($aaa,$w,$h){
   	if ($aaa['2']<>'') echo '<td width="'.$w.'px" height="'.$h.'"><div class="block4"><img alt="" src="'.'./images/'.$aaa[10].'"><b>'.$aaa['2'].'</b></div>';
    if ($aaa['3']<>'') echo '<div style="background: rgb(245, 245, 245)" class="block1">'.$aaa['3'].'</div>';
	if ($aaa['4']<>'') echo '<div style="background: rgb(230, 230, 230)" class="block1">'.$aaa['4'].'</div>';
	if ($aaa['5']<>'') echo '<div style="background: rgb(245, 245, 245)" class="block1">'.$aaa['5'].'</div>';
	echo '</td>';
	}
	
public function inpbl2($aaa,$w,$h){
   	if ($aaa['2']<>'') echo '<td valign="top" width="'.$w.'px" height="'.$h.'"><div class="block4">'.$aaa['2'].'</div>';
    if ($aaa['3']<>'') echo '<div style="background: rgb(245, 245, 245)" class="block1">'.$aaa['3'].'</div>';
	if ($aaa['4']<>'') echo '<div style="background: rgb(230, 230, 230)" class="block1">'.$aaa['4'].'</div>';
	if ($aaa['5']<>'') echo '<div style="background: rgb(245, 245, 245)" class="block1">'.$aaa['5'].'</div>';
	if ($aaa['10']<>'') echo '<div><img alt="" src="'.'./images/'.$aaa[10].'">'.$aaa['12'].'</div>';
	if ($aaa['11']<>'') echo '<div><img alt="" src="'.'./images/'.$aaa[11].'">'.$aaa['13'].'</div></td>';
	}
	
public function inpblsp($aaa, $block, $clas,$numclass,$var){
	echo '<div class="'.$clas['clas'][$numclass].'">';
if ($var==1) {
   	for($i=0;$i<count($aaa['c']);$i++) if ($aaa['c'][$i]<>'') echo'<p>'.$aaa['c'][$i].'</p>';
    
}
else {
	for ($i=0;$i<count($aaa['g']);$i++)
	if ($aaa['g'][$i]<>'') echo '<div style="float:left"><img alt="" src="'.'./images/'.$aaa['g'][$i].'">'.$aaa['t'][$i].'</div>';
	}
echo '</div>';
	}	
	
public function inpbldiv($aaa, $block){
   	if ($aaa['2']<>'') echo '<div class="'.$block.'">'.$aaa['2'].'</div>';
    if ($aaa['3']<>'') echo '<div class="'.$block.'">'.$aaa['3'].'</div>';
	if ($aaa['4']<>'') echo '<div class="'.$block.'">'.$aaa['4'].'</div>';
	if ($aaa['5']<>'') echo '<div class="'.$block.'">'.$aaa['5'].'</div>';
	if ($aaa['10']<>'') echo '<div style="float:left"><img alt="" src="'.'./images/'.$aaa[10].'">'.$aaa['12'].'</div>';
	if ($aaa['11']<>'') echo '<div><img alt="" src="'.'./images/'.$aaa[11].'">'.$aaa['13'].'</div>';
	}	
	 
public function inpbldiv2($arr,$aaa, $block, $var,$n=0.5){
if ($var=='c') {
	for ($i=0;$i<count($aaa['g']);$i++){
		$bbb[0]=$aaa['l'][$i];
	if ($aaa['c'][$i]<>'') Page::scalimag3($arr,'./images/'.$aaa['g'][$i], $bbb, '10*'.$n.'','');
		   	}
	}
else {	
	for ($i=0;$i<count($aaa['g']);$i++){
	if ($aaa['t'][$i]<>'') echo '<div class="'.$block.'-img"><img class="'.$block.'-img" alt="" src="'.'./images/'.$aaa['g'][$i].'">'.$aaa['t'][$i].'</div>';
   	}
	}
}		
	
public function info1($aaa,$w,$h){
   	if ($aaa['2']<>'') echo '<td width="'.$w.'px" height="'.$h.'"><div class="block1">'.$aaa['2'].'</div>';
    if ($aaa['3']<>'') echo '<div class="block1"><img align="left" style=" width: 81px; height: 90px;"alt="" src="./images/'.$aaa['10'].'">'.$aaa['3'].'</div>';
	if ($aaa['4']<>'') echo '<div class="block1"><img align="right" style="width: 81px; height: 90px;"alt="" src="./images/'.$aaa['11'].'">'.$aaa['4'].'</div>';
	if ($aaa['5']<>'') echo'<div class="block1">'.$aaa['5'].'</div></td>';
	}	

public function info2($aaa, $brow){
if ($brow==1) {
echo '<div class="block2">';
for ($i=1;$i<5;$i++) echo '<b>'.$aaa[$i].'</b><br>';
echo '</div>';
}
else {
	for ($i=1;$i<5;$i++) {
	echo '<div class="block2">'.$aaa[$i].'</div>';
	
		}
	}

}	

public function info3div($aaa, $bbb, $brow,$sdv,$sdh){
//$sdv=-300;

if ($brow==1) {
echo '<div class="block2" style="top:-300px;left: 50px; " >';
for ($i=1;$i<count($aaa);$i++) {
$pg= new Page($bbb[$i], $tablepages,$tablenews);
$b[$i]=$pg->MainAr["hrefp"];
 echo '<a href="'.$b[$i].'?np='.$bbb[$i].'"><b>'.$aaa[$i].'</b></a><br>';
 }
echo '</div>';
}
else {
	$sdv=$sdv-count($aaa)*3;
	for ($i=1;$i<count($aaa);$i++) {
	$pg= new Page($bbb[$i], $tablepages,$tablenews);
	$b[$i]=$pg->MainAr["hrefp"];
	echo '<div class="block2" style="top:'.$sdv.'px;left: '.$sdh.'px; "><a href="'.$b[$i].'?np='.$bbb[$i].'">'.$aaa[$i].'</a></div>';
}
	}

}	

public function info3($aaa, $bbb, $brow,$sdv,$sdh){
//$sdv=-300;

if ($brow==1) {
echo '<div style="top:-300px;left: 50px; " >';
for ($i=1;$i<count($aaa);$i++) {
$pg= new Page($bbb[$i], $tabl);
$b[$i]=$pg->MainAr["hrefp"];
 echo '<a href="'.$b[$i].'?np='.$bbb[$i].'"><b>'.$aaa[$i].'</b></a><br>';
 }
echo '</div>';
}
else {
	$sdv=$sdv-count($aaa)*3;
	for ($i=1;$i<count($aaa);$i++) {
	$pg= new Page($bbb[$i], $tabl);
	$b[$i]=$pg->MainAr["hrefp"];
	echo '<div style="top:'.$sdv.'px;left: '.$sdh.'px; "><a href="'.$b[$i].'?np='.$bbb[$i].'">'.$aaa[$i].'</a></div>';
}
	}

}	

public function scalimag($img, $aaa, $t,$nam,$img2,$idnews, $styll='center', $tabl) {

if ($aaa['n']["2"]=='') 
{
if (strlen($aaa['n'][3])<500) $dlstr=strlen($aaa['n'][3]);
else $dlstr=500;
$wpic=350;
}
else {
$dlstr=300;
$wpic=270;
}
$sw=Singleton::getInstance('StructureW');
$mark=$sw->getnews($idnews, $tabl['news']);
$arrm=$mark['news'][0];
//ElementsW::Showobjtype($arrm);
//echo $idnews;
$styll='block1';
if ($idnews==0) {
if (file_exists($img))
      {
         $size = GetImageSize($img); 
		 if($size[0]>0 && $size[1]>0) 
         {   
	 if ($size[0]< 250 && $size[1]< 250) $m=1;
	 else $m=1;
	//echo '<form style="padding:5px; align:left;" method="post" action="'.$PageM->MainAr["hrefp"].'?np=7&new=1#new1" target="_self">';
	//echo '<form method="post" action="'.$PageM->MainAr["hrefp"].'?np=1&new=1#new1" target="_self">';
	//echo '<div class="'.$styll.'" width="'.$wpic.'"><img src="'.'./images/'.$aaa["9"].'" border="0" width = '.intval($size[0]/3).' height= '.intval($size[1]/3).'>'.$aaa["7"].'<br><b>'.$aaa["6"].'</b><br>'.substr($aaa["8"],0,$dlstr).'<a href="'.$PageM->MainAr["hrefp"].'?np=2&new='.$arrm[0]["group"].'#new'.$idnews.'">........<br></a><input style="color:rgb(100, 180, 245);"value="'.$t.' '.$nam.'" type="image" src="'.$img2.' "/><input type="hidden" name="new" value="yes"></input>';
	echo '<div class="'.$styll.'" width="'.$wpic.'"><form method="post" 
	action="'.$PageM->MainAr["hrefp"].'?" target="_self"><img src="'.'./images/'.$aaa['n'][5].'"
	border="0" width = '.intval($size[0]/$m).' height= '.intval($size[1]/$m).'>'.$aaa['n'][2].'
	<br><b>'.$aaa['n'][1].'</b><br>'.substr($aaa['n'][3],0,$dlstr).'<a href="'.$PageM->MainAr["hrefp"].'
	#new'.$idnews.'">...</a><input style="color:rgb(100, 180, 245);"value="'.$t.' '.$nam.'
	" type="image" src="'.$img2.' "/><input type="hidden" name="new" value="yes"></input>';
	echo "<input type='hidden' name='new' value='yes'/>";
	}
			}
			else {
			echo '<div class="'.$styll.'" width="'.$wpic.'"><form style="padding:5px; align:left;" 
			method="post" action="'.$PageM->MainAr["hrefp"].'#new1" target="_self">';
			//echo $aaa["7"].'<br><b>'.$aaa["6"].'</b><br>'.substr($aaa["8"],0,$dlstr).'<a href="'.$PageM->MainAr["hrefp"].'?np=1&new='.$arrm["group"].'#new'.$idnews.'">...</a><input style="color:rgb(100, 180, 245);"value="'.$t.' '.$nam.'" type="image" src="'.$img2.' "/>';
			echo $aaa['n'][2].'<br><b>'.$aaa['n'][1].'</b><br>'.substr($aaa['n'][3],0,$dlstr).'
			<a href="'.$PageM->MainAr["hrefp"].'#new'.$idnews.'">.......<br></a>
			<a href="./?hd=5"><input style="color:rgb(100, 180, 245);value:'.$t.' '.$nam.';" type="image" 
			src="'.$img2.'"/></a><input type="hidden" name="new" value="yes"></input>';
			} 
	echo '</form></div>';	
}
else {
	//echo '-'.$idnews.'-';	
	//echo "yes".$arrm["imgnews"];
	//echo './images/'.$arrm["imgnews"];
	if (file_exists('./images/'.$arrm["imgnews"]))
      {
	 
	$size = GetImageSize('./images/'.$arrm["imgnews"]); 
		 if($size[0]>0 && $size[1]>0)
			 if ($size[0]< 250 && $size[1]< 250) $m=1;
	 else $m=1;
         {   
	//echo '<form style="padding:5px; align:left;" method="post" action="'.$PageM->MainAr["hrefp"].'?np=1&new=1#new1" target="_self">';
	echo '<div class="'.$styll.'" width="'.$wpic.'"><form style="padding:5px; align:left;" method="post" action="'.$PageM->MainAr["hrefp"].'#new'.$idnews.'" target="_self"><img src="'.$clas['img'].'./images/'.$arrm["imgnews"].'" border="0" width = '.intval($size[0]/3).' height= '.intval($size[1]/3).'></div>'.$arrm["date"].'<br><b>'.$arrm["name"].'</b><br>'.substr($arrm["text"],0,$dlstr).'<a href="'.$PageM->MainAr["hrefp"].'?new='.$arrm["group"].'#new'.$idnews.'">.....<br></a><input style="color:rgb(100, 180, 245);"value="'.$t.' '.$nam.'" type="image" src="'.$img2.' "/>';
	echo '<input type="hidden" name="new" value="yes"/>';
	}

			}
			else {
			//echo '+'.$idnews.'+';	
			echo '<div class="'.$styll.'" width="'.$wpic.'"><form style="padding:5px; align:left;" 
			method="post" action="'.$PageM->MainAr["hrefp"].'#new1" target="_self">';
			echo $arrm["date"].'<br><b>'.$arrm["name"].'</b><br>'.substr($arrm["text"],0,$dlstr).'
			<input type="hidden" name="new" value="yes"></input><a href="'
			.$PageM->MainAr["hrefp"].'#new'.$idnews.'">...</a>
			<input style="color:rgb(100, 180, 245);" value="'.$t.' '.$nam.'" type="image" src="'.$img2.'"</input>';
			//echo "<input type='hidden' name='new' value='yes'/>";
			}
	echo '</form></div>';	

}

}

public function razmer($img,$n=0,$ww=200){
	if (file_exists($img) ){
			$size = GetImageSize($img); 
				if($size[0]>0 && $size[1]>0){
		if($n==0){
			if ($size[0]>=$size[1]) $n=ceil($size[0]/$ww);
		else $n=ceil($size[1]/$ww);
}
}
}
return $n;
}
//вывод записи блога за номером nbl i-номер в списке параметров
public function scalimag1($arr,$Pth,$clas,$mode=0,$bbb='',$prefix=''){
	//print_r($arr['n']);
	if ($bbb=='')$bbb=array('0'=>$arr['n']['date'],'1'=>$arr['n']['name'],'2'=>$arr['n']['text'],'3'=>$arr['n']['hrefn'],'4'=>$arr['n']['imgn']);
	elseif(!is_array($bbb)) $bbb=array('0'=>'','1'=>'','2'=>'','3'=>'','4'=>$bbb);
	//print_r($bbb);
	$Pth14=$arr["idmen"][0].'-'.$clas.'-text';
	$Pth13=$arr["idmen"][0].'-'.$clas.'-date';
	$Pth15=$arr["idmen"][0].'-'.$clas.'-img';
	if($Pth[$Pth14]['numpar']['Sizes'])$PthL=$Pth[$Pth14]['numpar']['Sizes'];
	else $PthL=18;
	if($Pth[$Pth13]['numpar']['Sizes'])$PthM=$Pth[$Pth13]['numpar']['Sizes'];
	else $PthM=14;
	if($Pth[$Pth15]['numpar']['Pics'])$PthP=$Pth[$Pth15]['numpar']['Pics'];
	else $PthP=5;
	$PthL0='font-size:'.$PthL.'px;';
	$PthS0='font-size:'.$PthM.'px;';
	$n=$PthP;
	//print_r($PthP);
	//echo $n;
	if($bbb[4]<>''){
	$img=$arr['clas']['img'].$bbb[4];
	$size = GetImageSize($img);
	if($size[0]>0 && $size[1]>0){
		if($bbb[2]<>''){
			$cardblog=Maket::divclass($clas.'-card',$Pth);
			$cardblog.=Maket::divclasstr($Pth13,$Pth,$PthL0,$prefix,'li').'<p>'.$bbb[0].'</p>'.Maket::divclasstr($Pth15,$Pth,'',$prefix,'img src="'.$img.'" width:"'.intval($size[0]/$n).'px;" height:"'.intval($size[1]/$n).'px;"').
			Maket::spanclasstr(Maket::spanclasstr($bbb[1],$Pth,$clas.'-div','div'),$Pth,$clas.'-a','a href="'.$bbb[3].'"').'</li>'.Maket::divclasstr($Pth14,$Pth,$PthS0,$prefix,'li').$bbb[2].'</li></div>';
		}
		else $cardblog=Maket::divclasstr($Pth15,$Pth,'',$prefix,'img src="'.$img.'" width:"'.intval($size[0]/$n).'px;" height:"'.intval($size[1]/$n).'px;"');
	}
	}
	if($mode==0) Maket::spanclass($cardblog,$Pth,$prefix,'div');
	else return $cardblog;
}

public function scalimag5($arr,$Pth,$bbb){
	
	$PthP=explode(';',$Pth['logo']['numpar']['Pics']);
	$href_link=$Pth['logo']['link_numpar']['Sizes'];
	$PthCl13=$cla['clas'][13];
	$PthCl14=$cla['clas'][14];
	$Pth14=$arr["idmen"][0].'-'.$PthCl12.'4-'.$PthCl14;
	$Pth13=$arr["idmen"][0].'-'.$PthCl12.'4-'.$PthCl13;
	$img=$arr['clas']['img'].$bbb[4];
	$size = GetImageSize($img);
	$n=Page::razmer($img);
	$plns=$Pth['logo']['numpar']['Sizes']+4;
	$PthL0='font-size:'.$plns.'px;';
	$PthS0='font-size:'.(2*$Pth['logo']['numpar']['Sizes']).'px;';
	echo Maket::divclasstr($Pth13,$Pth,$PthL0,$prefix,'li').'<p>'.$bbb[0].'</p><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'><a  href="'.$bbb[3].'"><span>'.$bbb[1].'</span></a></li>'.Maket::divclasstr($Pth14,$Pth,$PthS0,$prefix,'li').$bbb[2].'</li>';
}

static public function scalimag3($arr,$img, $bbb,$Pth ,$numclass,$i=0,$typelist='namep',$typelist1='loz',$typelist2='list'){
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


if (is_array($bbb)) {
	$img=$cla['img'].$bbb[4];
	echo Maket::divclasstr($Pth13,$Pth,$PthL0,$prefix,'li').'<p>'.$bbb[0].'</p><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'><a  href="'.$bbb[3].'"><span>'.$bbb[1].'</span></a></li>'.Maket::divclasstr($Pth14,$Pth,$PthS0,$prefix,'li').$bbb[2].'</li>';
}
else { 
	if($a_link <> ''){	
		if (isset($a_link[$typelist][$i+1]) && $clas == 'logo') echo Maket::divclasstr($clas.' '.$arr['idmen'][0],$Pth).$a_link[$typelist][$i+1];
		elseif(isset($a_link[$typelist][$i]) && $clas == '') echo $a_link[$typelist][$i];
		else echo $a_link[$typelist][$i];
		if (is_array($cla)) echo '<li class="'.$Pth12.'4">';	
		if ($clas == 'logo' ) { 
			if (isset($arr[$typelist][$i+2]) && $arr['idmen'][0]<>'land') echo '<div><li class="'.$clas.'"><a href="'.$bbb.'">'.Maket::divclasstr($clas,$Pth,'border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n),'-'.$n,'img  src="'.$img.'"').'</img></a></li><li class="'.$clas.'">'.$arr[$typelist][$i+2].$a_link[$typelist][$i+2].'</li></div>';
		    else echo '<div><li class="'.$clas.'" style="margin:50px;"><a href="'.$bbb.'">'.Maket::divclasstr($clas,$Pth,'border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n),'-'.$n,'img  src="'.$img.'"').'</img></a></li></div>';
		   if (isset($arr[$typelist][$i+3])) echo '<div><li class="'.$clas.' '.$arr['idmen'][0].'">'.Maket::divclasstr($clas,$Pth,$PthL0,'','span').$arr[$typelist][$i+3].'</span>';
		   if (isset($a_link[$typelist][$i+3])) echo $a_link[$typelist][$i+3].'</li></div>';
			//echo '</div>';
		}
		elseif($clas == '') echo '<a href="'.$bbb.'"><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'>';
		elseif(isset($arr[$typelist2][$i])) echo Maket::divclasstr($Pth13,$Pth,$PthS0,'','li').'<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'>'.$a_link[$typelist2][$i].'<a href="./?np='.$arr[$typelist2.'href'][$i].'">'.Maket::divclasstr($clas,$Pth,$PthL0,'','span').$arr[$typelist2][$i].'</span></a>'.$a_link[$typelist2.'href'][$i];
		echo '</img></a></li>';
		if ($clas <> 'logo' && isset($a_link[$typelist1][$i]) && $clas <> '') {
			echo Maket::divclasstr($Pth14,$Pth,$PthL1,'','li');
			echo $a_link[$typelist1][$i].'<a href="./?np='.$arr[$typelist1.'href'][$i].'">'.$arr[$typelist1][$i].'</a>';
			echo '</li>';
		}
		}
	else {
		//echo'-------------'.$arr[$typelist][$i+2];
		if ($clas == 'logo') {
			echo '<div class="logo">';
			echo Maket::divclasstr($clas.'-logo',$Pth).'<a href="'.$bbb.'"><img  src="'.$img.'" border="0" width:"'.intval($size[0]/$n).'px;"  height:"'.intval($size[1]/$n).'px;"></img></a></div>';
			
			 if (isset($arr[$typelist][$i+3])) echo Maket::divclasstr($clas.'-item'.$i,$Pth).Maket::divclasstr($clas.' '.$arr['idmen'][0],$Pth,'','','li').Maket::spanclasstr($arr[$typelist][$i+3],$Pth,$clas.'-cont'.$i,'span','',"padding-left:5px;margin-top: auto;margin-bottom: auto; $PthL0").'</li>';
			 
			if ($arr['idmen'][0]<>'land') {
				if(isset($arr[$typelist][$i+2]))echo Maket::divclasstr($PthC0,$Pth).Maket::divclasstr($PthC0.'-li',$Pth,'padding-left:20px;'.$PthL1,'','li').'<b>'.$arr[$typelist][$i+2].'</b></li></div>';
				//echo '</div>';
			}
		}
		elseif($clas == 'main-banner') echo '<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></img></li>';
		else {
		if (isset($arr[$typelist1][$i+1])) echo '<div>'.Maket::divclasstr($Pth13,$Pth,'font-size:'.$size_parfs13,'li').'<img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'><a href="./?np='.$arr[$typelist1.'href'][$i+1].'">'.Maket::divclasstr($clas,$Pth,$PthL0,'','span').$arr[$typelist1][$i+1].'</span></a></img>';
		echo '</li>';
		Maket::divclass($Pth14,$Pth,'font-size:'.$size_parfs14,'li');
		echo '<a href="./?np='.$arr[$typelist1.'href'][$i].'">'.$arr[$typelist1][$i].'</a>';
		echo '</li></div>';
		}
	
	}
	}
	echo '</div>';	
}
}
}

static public  function get_image_type( $image_path_or_resource ) {
    $img = getimagesize( $image_path_or_resource );
    if ( !empty( $img[2] ) ) // returns an integer code
        return image_type_to_mime_type( $img[2] );
    return false;
}

static public function scalimag4($arr,$Pth='',$clas='',$ncl='',$selector='div', $n=0, $ww=250,$bbb=''){

if ($bbb=='' && is_array($arr)){
	$bbb=array('0'=>$arr['n']['date'],'1'=>$arr['n']['name'],'2'=>$arr['n']['text'],'3'=>$arr['n']['hrefn'],'4'=>$arr['n']['imgn']);
	if(Page::get_image_type($clas['img'].$bbb[4])) $img=$clas['img'].$bbb[4];
}
elseif(Page::get_image_type($arr)) $img=$arr; 
if(is_int($ncl))$clas=$clas['clas'][$ncl];
else {$clas=$ncl;$img='';}
if (file_exists($img)){
         $size = GetImageSize($img); 
		 if($size[0]>0 && $size[1]>0){   
	 
	if($n==0){
	if ($size[0]>=$size[1]) $n=intval($size[0]/$ww);
	else $n=intval($size[1]/$ww);
	}
	//print_r($bbb);
	echo '<'.$selector.' class="'.$clas.' flex" style="justify-content: flex-start">';
	if (is_array($bbb)){
		echo '<div>';
		Maket::divclass($clas.'-data',$Pth,'','',$selector);
		if($bbb[0]<>'')Maket::spanclass(Maket::spanclasstr(Maket::spanclasstr($bbb[0],$Pth,$clas.'-data','div'),$Pth,$clas.'-a','a href="'.$bbb[3]));
		
		//Maket::divclass($clas,$Pth,'','',$selector);
		if($bbb[1]<>'')echo '<span class="'.$clas.'-bold"><b>'.$bbb[1].'</b></span></div>';
		
		echo '<div class="'.$clas.'-img">';
		if($img<>'') echo Maket::divclasstr($clas.'-img',$Pth,'width:'.intval($size[0]/$n).'px; height:'.intval($size[1]/$n).'px;','','img src="'.$img.'"').'</a>';
		echo '</div></div>';
		//echo '</'.$selector.'>';
		Maket::divclass($clas.'-text',$Pth,'',' flex',$selector);
		if($bbb[2]<>'')Maket::spanclass('<p>'.$bbb[2].'</p>',$Pth,$clas.'-text','span');
		echo '</'.$selector.'>';
	}
	elseif($img<>'')echo Maket::divclasstr($clas.'-img',$Pth,'width:'.intval($size[0]/$n).'px; height:'.intval($size[1]/$n).'px;','','img src="'.$img.'"').'</img>';
	echo '</'.$selector.'>';
	}
}
//else echo 'Изображение не найдено или не тот формат';
}

public function gallNpic($arr,$Pth,$nc,$nb=0) {
	$clas=$arr['clas']['img'];
	//print_r($arr);
	unset($arr['imgs']['link']);
	if (is_array($arr)){
		$imagH=$arr['imgs'];
		
	}
	$k=0;
	$kk=$nc;
	$ww=0;
	for ($i=0;$i<$nc;$i++){
	$imagH[$i]=$clas.$imagH[$i];	
	$size = GetImageSize($imagH[$i]);
	$ww=$ww+1000/$nc;//$size[0];
	
	}
	//if ($ww>500) $ww=510;
	//$ww =$ww+$brow*5;
	$imagH[]=$arr['clas']['imgext'].'Activia_bluberry_6x3_03c_logo.jpg';	
	
	for ($i=$nb;$i<count($imagH)+$nb;$i++){
	if ($k == 0) Maket::divclass('gall1',$Pth);//echo '<div class="gall1">'; 
	if ($k<($nc-1))echo '<div></div>';
	else echo '</div>'.Maket::divclasstr('gall2-'.$arr['idmen'][0],$Pth,'');//<div class="gall2">';
	if($i>=$nc)$j=$i-$nc;
	else $j=$i;
	if($imagH[$j]<>$clas)echo '<img alt="Изображение '.$j.'" src="'.$imagH[$j].'">';
	$k++;
	if ($k==$kk) {
	$k=0;
				}
		}
	
	echo '</div>';
	
}	

public function gallWpt($arr,$wid=300) {
	if (isset($imag))$imag['H']=$arr['imgs'];
	$imag['T']=$arr['imgt'];
	$imag['Z']=$arr['list'];
	$k=1;
	//$kk=$nc;
	$ww=0;
	for ($i=0;$i<count($imag['H']);$i++){
		$size[$i] = GetImageSize('./images/'.$imag['H'][$i]);
		}
	$i=0;
	$len=$wid;
	do {
		$len=$len-$size[$i][0];
		$i++;
	} while($len>0);
	$nc=$i-2;
	for ($k=1;$k<floor(count($imag['H'])/$nc);$k++){
	echo '<div class="gall1">';
	for ($i=($k-1)*$nc;$i<$k*$nc;$i++){
	
	echo '<ul class="menu"><li class="menulevel"><img padding="3px" alt="" src="'.'./images/'.$imag['H'][$i].'"></li>';
	echo '<li class="menulevel">'.$i.'-'.$k.' <b>'.$imag['Z'][$i].'</b> '.$imag['T'][$i].'</li></ul>';
	}
		echo '</div>';	
echo '<div class="gall2"></div>';	
}
}
		
public function scalimag2($img, $bbb, $n, $zag) {
	//echo 'does it exist ? '.$img;
	$styll='block1';
if (file_exists($img))
      {
		  //echo 'exist'.$img;
         $size = GetImageSize($img); 
		 if($size[0]>0 && $size[1]>0) {
if (count($bbb)<4) {		 
	if ($bbb[1] <> "" && $bbb[2] <>"") echo '<div class="'.$styll.'"><a  class="zag" target="_self" href="'.$bbb[0].'"><b>'.$bbb[1].'</b><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a><div class="'.$zag.'">'.$bbb[2].'</div>';
	else echo '<div class="'.$styll.'"><a target="_self" href="'.$bbb[0].'"><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a>';
	}
else 	{
	if ($size[0]>200 || $size[1]>200) $n=$n*2;
	if ($bbb[1] <> "" && $bbb[2] <>"" && $bbb[3] <> "" && $bbb[4] <>"") echo '<td  align="center" valign="top"><a  class="zag" target="_self" href="'.$bbb[0].'"><b>'.$bbb[1].'</b><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a><div class="'.$zag.'">'.$bbb[2].' <b>'.$bbb[3].' '.$bbb[4].'</b></div>';
	else echo '<div class="'.$styll.'"><a target="_self" href="'.$bbb[0].'"><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a>';
}
	}
		}
			else echo '</div>';
	//echo '</td>';	
}

public function scalimagD($img, $bbb, $n, $clas) {
if (file_exists($img))
      {
         $size = GetImageSize($img); 
		 if($size[0]>0 && $size[1]>0) {
if (count($bbb)<4) {		 
	if ($bbb[1] <> "" && $bbb[2] <>"") echo '<div class="'.$clas.'"><a target="_self" href="'.$bbb[0].'"><b>'.$bbb[1].'</b><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a><div class="'.$zag.'">'.$bbb[2].'</div>';
	else echo '<div border="1" class="'.$clas.'"><a target="_self" href="'.$bbb[0].'"><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a>';
	}
else 	{
	if ($size[0]>200 || $size[1]>200) $n=$n*2;
	if ($bbb[1] <> "" && $bbb[2] <>"" && $bbb[3] <> "" && $bbb[4] <>"") echo '<div  class="'.$clas.'"><a target="_self" href="'.$bbb[0].'"><b>'.$bbb[1].'</b><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a><div class="'.$zag.'">'.$bbb[2].' <b>'.$bbb[3].' '.$bbb[4].'</b></div>';
	else echo 'div class="'.$clas.'"><a target="_self" href="'.$bbb[0].'"><img  src="'.$img.'" border="0" width = '.intval($size[0]/$n).' height= '.intval($size[1]/$n).'></a>';
}
	}
		}
			else echo '<div';
	echo '</div>';	
}
	
public function inpspis($spis){
for ($i=0;$i<count($spis);$i++){
	echo $spis[$i].'<br />';
}

}

public function display_manual($nm){

switch ($nm) {
	case 1: {
		echo '<div class="button">Порядок оформления резервов и выписка счета</div>';
		break;
	}

}


}

public function FTframe($aaa){
echo '<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="700" height="500">';
 
  echo '<tr><td class="center"><div id="storeDiv"><b>Р’РЎР•, С‡С‚Рѕ РЅСѓР¶РЅРѕ РґР»СЏ РЅР°РґРµР¶РЅРѕР№ Рё СЌС„С„РµРєС‚РёРІРЅРѕР№ СЂР°Р±РѕС‚С‹ РѕС„РёСЃР° Р’Р°С€РµР№ РєРѕСЂРїРѕСЂР°С†РёРё</b><p align="right">'.$list7[1].'<br>'.$list7[2].'<br>'.$list7[3].'<br>'.$list7[4].'</p></div></td></tr><tr>';
  	 Page::inpbl($aaa,1000,90);
  echo '</tr></table>';
}

function idPage($id) {
	if($id != 0){
		$find=$this->db->query('select * from `pages` where `numpage`= ^Ni;', $id);
		if ($find) return $find;	
				else return false;
			}
	return false;	
}	

public static function PageExist ($pagenew) {
	$arr=array('Номер','Название','Лозунги','Ключевые слова','Название кнопок','URL страницы','Тип меню ', 'URL скриптов','URL scc','HTML заголовок',
	'Тексты','Идентификатор меню','уровень меню каталога','URL картинок', 'Список опций', 'Список ссылок на страницы опций', 'Ссылки кнопок на страницы', 
	'URL картинок кнопок','Тексты для картинок','Идентификатор новости');
	//$a=reset($arr);
    echo '<tr><td>       </td>';
	echo '<td><div class="button" >Страница (".$numpage.") ".$namep."</div><div class="ank">';	  		
			$page=self::idPage($pagenew);
			while(list($key, $val) = each($arr))
   {
      if (current($page)) echo $val.' - '.current($page).'<br>';
	  next($pagenew);
   }  
}   

public function checkPage ($pagenew) {
		if ($pagenew['namep']&& $pagenew['numpage']&& $pagenew['lozung1']&& $pagenew['mamebutt1']&& $pagenew['lozung2']&& $pagenew['namebutt2']&& $pagenew['lozung3']&& $pagenew['namebutt3'])
		return true;
	else return false;
	}
	
public function isExistPage($pagenew) {
	//if($pagenew !== 0){
	$sw = Singleton::getInstance('StructureW');	
	if(isset($pagenew)) {
		$find=$sw->gettables($pagenew,'numpage','pages');
		
		if ($find->namep) {
			echo 'numpage-->'.$find['numpage'];
		//echo $find->name.'<br>';
		return $find;	
		}
		else {echo 'numpage-->no';return false;}
			}
	return false;			
}
	
public function addPage($numpage, $pagenew) {
		if ($pagenew['namep']==''&& $pagenew['numpage']=='' && $pagenew['lozung1']=='') return false;
		if($this->checkPage($pagenew)) {
		try { 
			$conn = Singleton::getInstance('DB');
			} catch(DBException $e) {
			exit($e);
		}
		// Вставка заказа должна выполняться в виде транзакции,
		// поэтому необходимо отключить autocommit
	if ($conn) {
		$conn->autocommit(FALSE);
		$conn->start();
			try {
				$this->db->query('INSERT INTO `pages` (`namep`, `numpage`, `lozungp`, `keywords`, `buttons`) VALUES (^Ns, ^Ni, ^Ns, ^Ns, ^Ns);', $pagenew['namep'], 
				$pagenew['numpage'],$pagenew['lozung1'].','.$pagenew['lozung2'].','.$pagenew['lozung3'],$pagenew['keywords'], $pagenew['namebutt1'].'|'.$pagenew['namebutt2'].'|'.$pagenew['namebutt3'].'|'.$pagenew['namebutt4'].'|'.$pagenew['namebutt5'].'|'.$pagenew['namebutt6']);
				/*$this->addClientRights($id);
				$nc=$this->CustExist2($id);
				$this->addCusToUser($id, $nc);*/
				} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
			echo "<br>";
		// Данные записываются в базу данных таблица pages 
		//echo "даные занесены в базу данных клиентов";
			 // конец транзакции
			$conn->commit();
			$conn->autocommit(TRUE);
			}
			return true ;
		} else {
			return false;
		}	
	}
	
public function editPage($id, $pagenew) {
	if ($pagenew['namep']==''&& $pagenew['numpage']=='' && $pagenew['lozung1']=='');
if($this->checkPage($pagenew)) {
			try {
				$this->db->query('UPDATE  `pages` SET `namep`=^Ns, `numpage`=^Ni, `lozungp`=^Ns, `keywords`=^Ns, `buttons`=^Ns  WHERE `numpage`=^Ni;',$pagenew['namep'], 
				$pagenew['lozung1'].','.$pagenew['lozung2'].','. $pagenew['lozung3'], $pagenew['address'],$pagenew['keywords'], $pagenew['namebutt1'].'|'.$pagenew['namebutt2'].'|'.$pagenew['namebutt3'].'|'.$pagenew['namebutt4'].'|'.$pagenew['namebutt5'].'|'.$pagenew['namebutt6']) ;
				} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
			echo "<br>";
		// Данные записываются в базу данных таблица customers 
		//echo "даные занесены в базу данных клиентов";
			return true ;
		} else {
			return false;
		}	
	}
function spacen($n,$str=''){
	$arr=array();
	for($i=0; $i<$n;$i++){
		$arr[]=$str;
	}
	return $arr;
}

public static function prepare_spisok($alist,$hlist,$tabl,$dlt1=';',$dlt2=':'){
	if( strstr($hlist,';')){
		$LAN = '';
		$AL = explode($dlt1,$hlist);
		if( strstr($alist,';'))$LA = explode($dlt1,$alist);
		else $LA=$alist;
		if(is_array($LA)){
		foreach($AL as $key=>$val){
			if($LA[$key]=== $val)$LA[$key]='';
			if($key<count($AL)-1)$pref = $dlt1;
			else $pref = '';
			$pagel[$val] = new Page($val,$tabl);
			if(!isset($LA[$key]))$LAN.=$pagel[$val]->getnamepage($pagel[$val],$dlt2).$pref;
			elseif($LA[$key] !== '')$LAN.=$LA[$key].$pref;
			else $LAN.=$pagel[$val]->getnamepage($pagel[$val],$dlt2).$pref;
			}
			$alist=$LAN;
		}
	
}
return $alist;
}

public static function readypagearr($arr,$clas,$linkpages,$mode,$arrconf,$tabl){
	$arr['list']=Page::prepare_spisok($arr['list'],$arr['hreflist'],$tabl);
	$arbthr=explode('|',$arr['butthref']);
	$arrbt=Page::prepare_spisok($arbthr[0],$arbthr[1],$tabl);
	$arr['butthref']=$arrbt.'|'.$arbthr[1];
//Print_r($arr['list']);
//Print_r($arr['hreflist']);
	if($mode->admin<>'Admin' )for($i=0;$i<count($arr);$i++)$linkpages[$i]='';
	//определение переменных, значение которых отображается на странице
	//$imagH[0]=explode(';',$arr['hrefimage']);//массив адресов картинок страницы
	
	//if($linkpages[13]<>'')$imagH[1]=$linkpages[13];
	$arrmain['max']['imgs']=$arrconf['szimggrp']*$arrconf['szimg'];
	$arrmain['max']['imgt']=$arrconf['szimgtxtgrp']*$arrconf['szimgtexts'];
	$arrmain['max']['list'] = $arrconf['szlistgrp']*$arrconf['szlists'];
	$arrmain['max']['butt'] = $arrconf['szbutgrp']*$arrconf['szbuttons'];
	$arrmain['max']['buttimg'] = $arrconf['szimgbutgrp']*$arrconf['szimgbut'];
	$arrmain['max']['cont'] = $arrconf['szcontgrp']*$arrconf['szconts'];
	$arrmain['max']['loz'] = $arrconf['szlozs'];
	$arrmain['max']['foot'] = $arrconf['szfoots'];
	$ex=explode(';',$arr['hrefimage']);
	if(isset($arr['hrefimage']))$arrmain['imgs']=array_splice($ex,0,$arrmain['max']['imgs']);//массив адресов картинок страницы
	else $arrmain['imgs']=Page::spacen($arrconf['szimg']);
	if($linkpages[13]<>'')$arrmain['link']['imgs']=array_splice($linkpages[13],0,$arrmain['max']['imgs']);
	$IMT=explode('|',$arr['imgtext']);
	$ex=explode(';',$IMT[0]);
	if(isset($IMT[0]))$arrmain['imgt']=array_splice($ex,0,$arrmain['max']['imgt']);//массив текстов для картинок страницы
	else $arrmain['imgt']=Page::spacen($arrconf['szimgtexts']);
	$ex=explode(';',$IMT[1]);
	if(strstr($IMT[1],';'))$arrmain['imgthref']=array_splice($ex,0,$arrmain['max']['imgt']);
	else $arrmain['imgthref']=Page::spacen($arrconf['szimgtexts']);
	if(isset($IMT[1])){
		$ex=explode(';',$IMT[1]);
		if(strstr($IMT[1],';'))$IMAGL=array_splice($ex,0,$arrmain['max']['imgt']);
		$ex=explode(';',$IMT[0]);
		$imagT[0][0]=array_splice($ex,0,$arrconf['szimgtxtgrp']*$arrconf['szimgtexts']);//массив текстов для картинок страницы
		$ex=explode(';',$IMT[1]);
		$imagT[1][0]=array_splice($ex,0,$arrmain['max']['imgt']);
		if($linkpages[18]<>''){
		$arrmain['link']['imgt']=array_splice($linkpages[18][0],0,$arrmain['max']['imgt']);
		$arrmain['link']['imgthref']=array_splice($linkpages[18][1],0,$arrmain['max']['imgt']);
	}
		if($linkpages[18]<>'' ){
			$imagT[0][1]=array_splice($linkpages[18][0],0,$arrmain['max']['imgt']);
			$imagT[1][1]=array_splice($linkpages[18][1],0,$arrmain['max']['imgt']);	
		}
	}
		else {
			
			$ex=explode(';',$IMT[0]);
		$imagT[0][0]=array_splice($ex,0,$arrmain['max']['imgt']);//массив текстов для картинок страницы
		$imagT[1][0]='';
		if($linkpages[18]<>''){
			$imagT[0][1]=array_splice($linkpages[18][0],0,$arrmain['max']['imgt']);
			$imagT[1][1]=array_splice($linkpages[18][1],0,$arrmain['max']['imgt']);		
		}
		}
	
	
	$ex=explode(';',$arr['list']);
	if(isset($arr['list']))$arrmain['list']=array_splice($ex,0,$arrmain['max']['list']);
	else $arr['list']=Page::spacen($arrconf['szlists']);
	$ex=explode(';',$arr['hreflist']);
	if(isset($arr['hreflist']))$arrmain['listhref']=array_splice($ex,0,$arrmain['max']['list']);
	else $arrmain['listhref']=Page::spacen($arrconf['szlists']);
	if($linkpages[14]<>'')$arrmain['link']['list']=array_splice($linkpages[14],0,$arrmain['max']['list']);
	if($linkpages[15]<>'')$arrmain['link']['listhref']=array_splice($linkpages[15],0,$arrmain['max']['list']);
	
	$LB=explode('|',$arr['buttons']);
	$ex=explode(';',$LB[0]);
	$arrmain['butt']=array_splice($ex,0,$arrmain['max']['butt']);///массив alt названий кнопок страницы
	$ex=explode(';',$LB[1]);
	if(isset($LB[1]))$arrmain['butthref']=array_splice($ex,0,$arrmain['max']['butt']);//массив номеров страниц, на которые ссылается массив alt названий кнопок
	if($linkpages[4]<>''){
		$arrmain['link']['butt']=array_splice($linkpages[4][0],0,$arrmain['max']['butt']);
		$arrmain['link']['butthref']=array_splice($linkpages[4][1],0,$arrmain['max']['butt']);
	}
	$ex=explode(';',$arr['buttimg']);
	if(strstr($arr['buttimg'],';'))$arrmain['buttimg']=array_splice($ex,0,$arrmain['max']['buttimg']);
	else $arrmain['buttimg']=Page::spacen($arrconf['szimgbut']);
	
	//массив адресов картинок кнопок страницы
	if($linkpages[17]<>'')$arrmain['link']['buttimg']=array_splice($linkpages[17],0,$arrmain['max']['buttimg']);
	
	$T=	explode('|',$arr['content']);	
		$ex=explode(';',$T[0]);
		if(isset($T[0]))$arrmain['cont']=array_splice($ex,0,$arrmain['max']['cont']);//массив текстов страницы
		else $arrmain['cont']=Page::spacen($arrconf['szconts']);
		$ex=explode(';',$T[1]);
		if(isset($T[1]))$arrmain['conthref']=array_splice($ex,0,$arrmain['max']['cont']);
		else $arrmain['conthref']=Page::spacen($arrconf['szconts']);//массив ссылок текстов страницы
		if($linkpages[10]<>''){
			$arrmain['link']['cont']=array_splice($linkpages[10][0],0,$arrmain['max']['cont']);
			$arrmain['link']['conthref']=array_splice($linkpages[10][1],0,$arrmain['max']['cont']);
		}
		
		$FT=explode('|',$arr['butthref']);
		if (isset($FT[1])){
			$ex=explode(';',$FT[0]);
			$arrmain['foot']=array_splice($ex,0,$arrconf['szfoots']);
			$ex=explode(';',$FT[1]);
			$arrmain['foothref']=array_splice($ex,0,$arrconf['szfoots']);
			}
		else 	{
			$arrmain['foot']=array_splice($arr['butthref'],0,$arrconf['szfoots']);
			$arrmain['foothref']=Page::spacen($arrconf['szfoots']);
		}
		
		if($linkpages[16]<>''){
			$arrmain['link']['foot']=array_splice($linkpages[16][0],0,$arrconf['szfoots']);
			$arrmain['link']['foothref']=array_splice($linkpages[16][1],0,$arrconf['szfoots']);
		}
		
		$L=array();
		$L=explode('|',$arr['lozung']);
		$ex=explode(';',$L[0]);
		if(strstr($L[0],';'))$arrmain['loz']=array_splice($ex,0,$arrconf['szlozs']);//массив лозунгов страницы
		else $arrmain['loz']=Page::spacen($arrconf['szlozs']);
		$ex=explode(';',$L[1]);
		if(strstr($L[1],';'))$arrmain['lozhref']=array_splice($ex,0,$arrconf['szlozs']);//массив ссылок на страницы для лозунгов страницы
		else $arrmain['lozhref']=Page::spacen($arrconf['szlozs']);
		if($linkpages[2]<>''){
			$arrmain['link']['loz']=array_splice($linkpages[2][0],0,$arrconf['szlozs']);
			$arrmain['link']['lozhref']=array_splice($linkpages[2][1],0,$arrconf['szlozs']);
		}
		
		$FT=explode(';',$arr['keywords']);
		//print_r($FT[1]);
		if(isset($FT[1]))$arrmain['titles']=$FT[1];
		else $arrmain['titles']=$arr['title'];
		//print_r($arrmain['titles']);
		if(isset($FT[2]))$arrmain['descr']=$FT[2];
		else $arrmain['descr']='';
		if(isset($FT[0]))$arrmain['keywds']=$FT[0];
		else $arrmain['keywds']='>>>';
		if(isset($linkpages[3][1]) && isset($linkpages[3][2])){
			$arrmain['link']['kwd']=$linkpages[3][0];
			$arrmain['link']['ttl']=$linkpages[3][1];
			$arrmain['link']['dsc']=$linkpages[3][2];
		}
		$arrmain['scripts']=explode(';',$arr['hrefscripts']);
		if($linkpages[7]<>'') $arrmain['link']['scripts']=$linkpages[7];
		$arrmain['style']=explode(';',$arr['hrefstyle']);
		if($linkpages[8]<>'')$arrmain['link']['style']=$linkpages[8];
		$arrmain['title']=$arr['title'];
		$arrmain['tarif']=$mode->tarif;
		//$arrmain['title']['link']=$linkpages[9];
		//$arrmain['desc']=$FT[1];
		//$arrmain['desc']['link']=$linkpages[9][1];
		unset($FT);
		if(!empty($linkpages[9])){
			if(isset($linkpages[9][0]))$arrmain['title']['link']=$linkpages[9][0];
		}
		$arrmain['site']=explode(';',$arr['site']);
		$arrmain['idn']=$arr['idnews'];
		if($linkpages[19]<>''){
			if(!empty($linkpages[19][0]))$arrmain['idn']['link']=$linkpages[19][0];
		}
		$arrmain['levmen']=explode(';',$arr['levelmenu']);
		if($linkpages[12]<>'')$arrmain['link']['levmen']=$linkpages[12];
		$arrmain['typmen']=explode(';',$arr['typemenu']);
		if($linkpages[6]<>'')$arrmain['link']['typmen']=$linkpages[6][0];
		$arrmain['idmen']=explode(';',$arr['idmenu']);
		if(isset($linkpages[11][0]))$arrmain['link']['idmen']=$linkpages[11][0];
		$ex=explode('|',$arr['namep']);
		$arrmain['namep']=array_splice($ex,0,$arrconf['sznames']+2);
		if($linkpages[1]<>'')$arrmain['link']['namep']=array_splice($linkpages[1],0,$arrconf['sznames']+2);
		$arrmain['hrefp']=explode(';',$arr['hrefp']);
		if($linkpages[5]<>'')$arrmain['link']['hrefp']=$linkpages[5];
		$arrmain['nump']=$arr['numpage'];
		$arrmain['idauthor']=$arr['idauthor'];
		$arrmain['tabl']=$tabl;
		if($arr['confp'])$arrmain['conf']=explode('|',$arr['confp']);
		if($arr['idnews']>0){
			$arrmain['news']['name']=$arr['namenews'];
			$arrmain['news']['date']=$arr['datenews'];
			$arrmain['news']['text']=$arr['textnews'];
			$arrmain['news']['idn']=$arr['idnews'];
			$arrmain['news']['imgn']=$arr['imgnews'];
			$arrmain['news']['vend']=$arr['vendnews'];
			$arrmain['news']['group']=$arr['grnews'];
			$arrmain['news']['hrefn']=$arr['hrefnew'];
			$arrmain['n']=$arrmain['news'];
			unset($arrmain['news']);
			//unset($arrmain['n']['link']);
		}
		else $arrmain['n']=array('name'=>'','date'=>'','text'=>'','idn'=>'','imgn'=>'','vend'=>'','group'=>'','hrefn'=>'');
		for ($k=0; $k<count($imagH[0]);$k++) {
			if (isset($imagH[0][$k])) $arrmain['g'][$k]=$imagH[0][$k]; else $arrmain['g'][$k]='';
				}
		//$IMAGT=explode(';',$IMT[0]);
		
		for ($k=0; $k<count($imagT[0][0]);$k++) {
					if (isset($imagT[0][0][$k])) $arrmain['t'][$k]=$imagT[0][0][$k]; else $arrmain['t'][$k]='';
					if (isset($IMAGL[$k])) $arrmain['l'][$k]=$IMAGL[$k]; else $arrmain['l'][$k]='';
				}
	if ($mode->level<5 && $mode->admin<>'Admin' && !isset($_GET['konstrS'])) unset($arrmain['link']);
	else 	{
		//if(isset($_GET['contentS']) || isset($_GET['cm'])) $arrmain=Page::madearr($arrmain,$mode->start,'Lorem gth uiiojjjku',2);
		//$arrmain['link']=show::a_link($arrmain);
		}	
	if($clas<>'') $arrmain['clas']=$clas;
	if($mode<>'') {
		$arrmain['owner']=$mode;
		
	}
	unset($L);
	unset($T);
	unset($imagT);
	unset($imagH);
	unset($IMAGL);
	unset($LB);
	unset($imagT);
	unset($IMT);
	//print_r($arrmain['list']);
	return $arrmain;
	}	
/*	
public function readypagelist($arr,$clas,$linkpages){
	//if($linkpages == '') foreach ($linkpages as $val) $val='';
	//определение переменных, значение которых отображается на странице
	$imagH[0]=explode(';',$arr['hrefimage']);//массив адресов картинок страницы
	//$imagH[1]=$linkpages[13];
	$IMT=explode('|',$arr['imgtext']);
	$list['1'][0]=explode(';',$arr['list']);//массив списка ссылок страницы
	$list['2'][0]=explode(';',$arr['hreflist']);//массив номеров страниц, на которые ссылается массив списка ссылок
	$list['1'][1]=	$linkpages[14];
	$list['2'][1]=	$linkpages[15];
	$LB=explode('|',$arr['buttons']);
	if(isset($LB[1]))$list['3'][0]=explode(';',$LB[1]);//массив номеров страниц, на которые ссылается массив alt названий кнопок
	$list['5'][0]=explode(';',$LB[0]);//массив alt названий кнопок страницы
	$list['3'][1]=	$linkpages[4][1];
	$list['5'][1]=	$linkpages[4][0];
	$list['4'][0]=explode(';',$arr['buttimg']);//массив адресов картинок кнопок страницы
	$list['4'][1]=$linkpages[17];
	if (is_array($list['4'][0])) for ($j=0;$j<count($list['5']);$j++) if(isset($list['4'][0][$j])) $list['4'][0][$j]=$clas['img'].$list['4'][0][$j];
	else $list['4'][0][0]=$clas['img'].$list['4'][0];
	$T=	explode('|',$arr['content']);							
	$list[6][0]=explode(';',$T[1]);//массив ссылок текстов страницы
	$list[7][0]=explode(';',$T[0]);//массив текстов страницы
	$list[6][1]=$linkpages[10][1];
	$list[7][1]=$linkpages[10][0];
	$L=array();
	$L=explode('|',$arr['lozung']);
	$list[8][0]=explode(';',$L[0]);//массив лозунгов страницы
	$list[9][0]=explode(';',$L[1]);//массив ссылок на страницы для лозунгов страницы
	$list[8][1]=$linkpages[2][0];
	$list[9][1]=$linkpages[2][1];
	$list[10][0]=explode(';',$arr['levelmenu']);
	$list[10][1]=$linkpages[12];
	$list[11][0]=explode(';',$arr['typemenu']);
	$list[11][1]=$linkpages[6];
	$list[12][0]=explode(';',$arr['idmenu']);
	$list[12][1]=$linkpages[11];
	$list[13][0]=explode('|',$arr['namep']);
	$list[13][1]=$linkpages[1];
	$FT=explode('|',$arr['butthref']);
	if(isset($FT[1])){
		$list[14][0]=explode(';',$FT[0]);//массив названий футера страницы
		$list[15][0]=explode(';',$FT[1]);//массив ссылок футера страницы
	}
	else {
		$list[14][0]=$arr['butthref'];
		$list[15][0]='';
	}
	for ($k=1;$k<count($list['11']);$k++) $list['12'][$k]='idm'.$k;
		if (count($L)<2) $popravka=150;
		else $popravka=0;
	for ($k=0;$k<count($list[6][0]);$k++) {
		if (isset($list[6][0][$k])) $list['h'][$k]=$list[6][0][$k]; else $list['c'][$k]='';
		if (isset($list[7][0][$k])) $list['c'][$k]=$list[7][0][$k]; else $list['c'][$k]='';
		}
	$list['n'][1]=$arr['namenews'];
	$list['n'][2]=$arr['datenews'];
	$list['n'][3]=$arr['textnews'];
	$list['n'][4]=$arr['idnews'];
	$list['n'][5]=$arr['imgnews'];
	$list['n'][6]=$arr['vendnews'];
	$list['n'][7]=$arr['grnews'];
	$list['n'][8]=$arr['hrefnew'];
	for ($k=0; $k<count($imagH[0]);$k++) {
		if (isset($imagH[0][$k])) $list['g'][$k]=$imagH[0][$k]; else $list['g'][$k]='';
				}
	$IMAGT=explode(';',$IMT[0]);
	$IMAGL=explode(';',$IMT[1]);
		for ($k=0; $k<count($IMAGT);$k++) {
					if (isset($IMAGT[$k])) $list['t'][$k]=$IMAGT[$k]; else $list['t'][$k]='';
					if (isset($IMAGL[$k])) $list['l'][$k]=$IMAGL[$k]; else $list['l'][$k]='';
				}
	return $list;
}	
*/
public function showallmenupage($tabl,$arrmain,$clas,$nc,$levuser){
$a_img=show::cleanmass(0,0,$clas,$arrmain,'butt','butt');
//print_r($a_img);
$a_imgs=$a_img[0];
$a_text=$a_img[1];
$nmo=count($a_text);
if ($nmo > 7) $nmp=7;
if ($nmo < 3) $just='SB';
if ($nmo < 6) $just='C';
if ($nmo > 5) $just='SA';
if ($arrmain['butthref']<>'') { //если есть ссылки с кнопок берем из buttons
//echo '<div class="menu">';

// Зона MENU
//print_r($list[4]);
	if ($arrmain['buttimg'][0]<>'./images/' && $distype[2]<> 'nbt') {//если картинки кнопок есть
		echo 'id меню с картинками кнопок <br>';
		echo '<div id="menu'.$just.$nmo.'">';
		//Menu::menubutt($list[5][0],$list[3][0],null,1,$tabl);
		//Menu::menubuttdiv($tabl,$arrmain['butt'],$arrmain['butthref'],$clas,4,true,$a_imgs);
		//print_r($arrmain);
		Menu::menubuttarr($tabl,$arrmain,$clas,4,$levelU,true,$a_imgs);
		
		
		
	echo '</div>';
	}
	else {//если картинок нет 
	//echo ' - '.$list['11'][2].' - ';
		if ($distype[2]<> 'nbt'){//если нет названий кнопок берем название страниц и ссылки из list
			//7
			echo '<ul class="menudown">';
			Menu::menubuttdiv($tabl,$arrmain['butt'],$arrmain['butthref'],$clas,21,false,'');
		
		echo '</ul>';
		}
	elseif ($distype[1]<> 'nmn') {//если есть названия кнопок и ссылки берем все из buttons
			show::menush($arrmain,'butt',$tabl);
			
			}
	}
}

}
public function top_page_wraper($clas,$im,$Pth,$arr,$tabl,$typelist='list'){
$list1=$arr[$typelist];	
$list2=$arr[$typelist.'href'];	
$intro_clas=array('_top_wrapper','_top','_menu');	
Maket::divclass($clas.$intro_clas[0],$Pth);
	Maket::divclass($clas.$intro_clas[1],$Pth);
		Maket::divclass($clas.$intro_clas[2],$Pth,'','ddsmoothmenu');
		Menu::menucss($list1,$list2,$tabl);
		echo '</div>';//templatemo_top_menu	
	echo '</div>';//templatemo_top
echo '</div>';//templatemo_top_wrapper
}

public function madearr($arr,$start,$strings,$nword=1){
	
	foreach($arr as $key=>$value){
		
		if($key=='cont') $string[$key]=30*$nword;
		if($key=='imgt') $string[$key]=20*$nword;
		if($key=='butt' ||  $key=='list') $string[$key]=1;
		if($key=='foot') $string[$key]=1;
		foreach($value as $key1=>$val){
			if($key <> 'imgs' && $key<>'levmen' && $key<>'namep' && $key<>'scripts' && $key<>'style' && $key<>'link'){
				if(!strstr($key,'href') && $val=='') {
					$str='';
					if($arr[$key][$key1]<>''){
					for($i=0;$i<$string[$key];$i++){
						
							$strng=substr($strings,rand(1,4),rand(3,8));
							$str.=' '.$strng;	
					}
					$arr[$key][$key1]=$str;
					}
				}
			//elseif($val=='')  $arr[$key][$key1]=$start;
		}	
	}
	}
	if($arr['namep'][2]=='') $arr['namep'][2]=$strings;
	for($i=0;$i<10;$i++)if($arr['imgs'][$i]=='') $arr['imgs'][$i]=$i.'.jpg';
	
	return $arr;
	}
	
	public function readyadmarr($arr){
		$ret['idmen']=$arr['idmen'];
		unset($arr['n']);
		unset($arr['l']);
		unset($arr['g']);
		unset($arr['t']);
		if(isset($arr['link']))$a_link=show::a_link($arr);
		else $a_link='';
		unset($arr['link']);
		//print_r($a_link['imgs']);
		//print_r($arr['imgs']);
		if($a_link === ''){
			unset($arr['link']);
			$ret=$arr;
		}
		else {
			
			$ret['clas']=$arr['clas'];
			unset($arr['clas']);
			$ret['tab']=$arr['tab'];
			unset($arr['tab']);
			
		foreach($arr as $key=>$value) {
			if($key<>'scripts' && $key<>'style' && $key<>'title' && $key<>'site' && $key<>'idmen' && $key<>'n'&& $key<>'g' && $key<>'t' && $key<>'l'){
		if(is_array($value)){		
			foreach($value as $i=>$val){
			if(!strstr($key,'href') && !strstr($key,'men')&& !strstr($key,'imgs')){
				if($key<>'namep' && $key<>'buttimg' && isset($a_link[$key.'href'][$i]) && isset($a_link[$key][$i]))
					$ret[$key][$i]=$a_link[$key][$i].$arr[$key][$i].$a_link[$key.'href'][$i];
				elseif($key=='buttimg' && isset($a_link[$key][$i])){
					$ret['buttimg'][$i]=$val;
					$ret['link']['buttimg'][$i]=$a_link[$key][$i];
				}
				elseif($key==='namep' && isset($a_link[$key][$i])){
					if($i<2){
						$ret['link'][$key][$i]=$a_link[$key][$i];
					}
					else {
						$ret['link'][$key][$i]=$a_link[$key][$i].$val;
					}
					$ret['namep'][$i]=$val;
				}
				elseif(strstr($key,'href') && isset($a_link[$key][$i])){
					$ret[$key][$i]=$val;	
					$ret['link'][$key][$i]=$a_link[$key][$i];
				}
				else {
					$ret[$key][$i]=$val;
					
					
				}
			}
			elseif($key === 'imgs'){
				$ret[$key][$i]=$val;	
				if(isset($a_link[$key][$i]))$ret['link'][$key][$i]=$a_link[$key][$i];
			}
		}	
	}
	else {
		$ret[$key]=$value;	
		if(isset($a_link[$key]))$ret['link'][$key]=$a_link[$key];	
		}
	}	
	}	
}
//print_r($ret);
	return $ret;
	}
	
	public function publpage($np,$tabl,$tarif,$idm,$mfl=0,$lfl=0){
		$Page= new Page($np,$tabl);
		$ts=date('U');
		$now=getdate($ts);
		$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
		$lpg=User::getscountab('elemap','id', 'f');
		$array=array();
		$arr=$Page->MainAr;
		$FT=explode(';',$arr['keywords']);
		//print_r($FT[1]);
		$arrmain['titles']=$FT[1];
		//print_r($arrmain['titles']);
		$arrmain['descr']=$FT[2];
		$arrmain['keywds']=$FT[0];
		if($linkpages[3]<>''){
			$arrmain['kwd']['link']=$linkpages[3][0];
			$arrmain['ttl']['link']=$linkpages[3][1];
			$arrmain['dsc']['link']=$linkpages[3][2];
		}
		$array[0]=$lpg+1;
		$array[1]=$arr['numpage'];
		$array[2]=$arr['namep'];
		$array[3]=$arr['lozungp'].'>|<'.$arr['buttons'].'>|<'.$arr['content'].'>|<'.$arr['list'].'>|<'.$arr['hreflist'].'>|<'.$arr['butthref'].'>|<'.$arr['imgtext'].'>|<'.$arr['buttimg'].'>|<'.$arr['hrefimage'].'>|<'.$arr['idmenu'].'>|<'.$arr['typemenu'].'>|<'.$arr['levelmenu'].'>|<'.$arr['hrefscripts'].'>|<'.$arr['hrefstyle'].'>|<'.$arr['title'];
		$array[4]=$FT[0];
		$array[5]=$FT[1].'>|<'.$FT[2];
		$array[6]=$tarif;
		$array[7]=$mfl;
		$array[8]=$lfl;
		$array[9]=$arr['idnews'];
		$array[10]=$tt;
		$array[11]=$idm;
		$array[12]=$arr['site'];
		$array[13]=$arr['idauthor'];
		//print_r($array);
		$res=$this->db->query('INSERT INTO `elemap`  
		VALUES (^Ni,^Ni,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni,^Ni,^Ns,^Ni,^Ns,^Ni);',
		$array[0],$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],$array[10],$array[11],$array[12],$array[13]);
		if($res)return true;
		else return false;
	}
	
	public function readyuserarr(){
		
	}
	public function read_namparams($table,$nmp,$field='',$typmen='',$sizeInput=20,$ta='global'){
	
	if($ta === 'global'){
		
		//$return=Utils::GlobalNamPar($table,$numpar,$field,$typmen,$sizeInput);
		$db = Singleton::getInstance('DB');	
		$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
		
	}
	else {
		$db = Singleton::getInstance('DB');	
		$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	}	
	//print_r($res2);//-------------
	
	if($res2 &&  $nmp !== 0  ){
			$arrnm=$res2->nampars;
			$arrtp=$res2->types;
			$arrdlm=$res2->delimiter;
			$arrname=explode('|',$arrnm);
			$arrtype=explode('|',$arrtp);
		foreach ($arrtype as $key=>$val) if (strstr($val,'type')) $arrtype[$key]=$sizeInput;
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
	if($field<>''){
		$res1=$db->query('SELECT * FROM `'.$table.'` WHERE `'.$field.'`=^Ni;',$nmp);
		$l=0;
		foreach($res1 as $val){
		if($arrtype[$l] == 'check'  && $val=='') $array[$l]=$typmen;
		elseif($val == '') $array[$l]=$arrdelem[$l];
		else $array[$l]=$val;
		$l++;
		}
	}
	$return=array($arrdelem,$arrname,$arrtype,$array);
	//print_r($return);//-------
}
else {
	$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$mass_zags=explode('|',$arrnm);
	$masszakls=explode('|',$arrtp);
	//echo $this->numpage.'--'.$nmp;
	foreach($masszakls as $val) {
		if($nmp<>0 ){
		if($val) $mass_zakls[]='?np='.$this->numpage.'&'.$val;
		else $mass_zakls[]=$val.'?np='.$this->numpage;
			}
		else $mass_zakls[]='?np='.$this->numpage.'&'.$val;
		}
	if($this->numpage<>0) {
			$mass_zakls[]='?np='.$this->numpage.'&'.'info';
			$mass_zags[]='Помощь';
		}
		
$return=array($mass_zags,$mass_zakls,$arrdlm);
}
return $return;
}
}
?>