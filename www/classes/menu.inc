<?php
class Menu {
const LOZUNG = 'Что нужно знать о сайтах;Твой сайт уже готов.;Просто подключись.;Изменяй, развивай его сам или вместе с нами.|';
private $numopt=3,
		$typemenu="",
		$idmenu="store",
		$levelmenu=0,
		$numpage="",
		$cont='<ul class=',
		$node='Node',
		$ex=' Expand',
        $list1=array(),
		$list2=array(),
		$a='',
		$b='',
		$on='onclick';
public $namemenu='ВСЕ, что нужно для надежной и эффективной работы офиса Вашей корпорации';		
public function __get($name)
  {
  return $this->$name;
  }
  
  public function __set($name, $value)
  {
    $this->$name = $value;
  }	

public function __construct($levelmenu, $namemenu, $ids, $numpage, $tabl,$typemenu='', $uid=1,$brow=0){
	if (isset($levelmenu)) $this->levelmenu=$levelmenu;
	if (isset($namemenu)) $this->namemenu=$namemenu;
	if (isset($numpage)) $this->numpage=$numpage;
	if (isset($typemenu)) $this->typemenu=$typemenu;
	if (isset($idmenu)) $this->idmenu=$idmenu;
	if (isset($tabl)) $this->tabl=$tabl;
	echo '<div onclick="tree_toggle(arguments[0],arguments[1]); return false;" id="box">';
					//<span id="store">Товары</span>
			$sw = Singleton::getInstance('StructureW');
			//echo ' lev '.$this->levelmenu.' tab '.$tabl['elem'];
			$arr = $sw->getData($this->levelmenu,$tabl['elem'],$uid,$ids);
			//print_r($this->levelmenu);
				if (isset($arr['this']['menu'])) $this->namemenu=$arr['this']['menu'];
				else $this->namemenu="";
			//print_r($arr);	
			$arr = $arr['sections'];
			
			echo '<ul class="Container">';
						$i = count($arr)-1;
						$num = 0;
						foreach($arr as $k => $val) {
							$num += $val['numEl'];
							if($k == $i) echo '<li class="Node ExpandClosed isLast" id="'.$val['id'].'">';
							else echo '<li class="Node ExpandClosed" id="'.$val['id'].'">';
							if ($brow == 0) echo '<a class="Expand" href="'.$this->numpage.'&id='.$val['id'].'">'.$val['name'].'</a></li>';			
							else echo '<a class="Expand" href="'.$this->numpage.'&id='.$val['id'].'">'.$val['name'].'&nbsp;('.$val['numEl'].')</a></li>';
						}
						echo '</ul>';
						//echo '<script type="text/javascript">document.getElementById("store").firstChild.nodeValue += " ('.$num.')";</script>';
					
					echo '</div>';

}
  
public function Mtree($levelmenu, $namemenu, $idmenu, $numpage, $typemenu) {
if (isset($levelmenu)) $this->levelmenu=$levelmenu;
if (isset($namemenu)) $this->namemenu=$namemenu;
if (isset($numpage)) $this->numpage=$numpage;
if (isset($typemenu)) $this->typemenu=$typemenu;
if (isset($idmenu)) $this->idmenu=$idmenu;
	//echo "тип меню ".$this->typemenu;
	switch ($typemenu){
	case 'Menu':{
	//$this->ex.='Menu';
	$func='tree_toggle2';
	$this->cont.='"'.$this->typemenu.'"';
	$this->on='onmouseover';
	break;}
	case 'Container':{
	$func='tree_toggle';
	$this->cont.='"'.$this->typemenu.'"';
	$this->on='onclick';
	break;}
	case 'Tree':{
	$this->typemenu=$this->node;
	$func='tree_toggle3';
	$this->cont.='Container';
	$this->on='onclick';
	}
	}
	//$this->cont.='"'.$this->typemenu.'"';
	//echo $this->cont;
	echo '<div '.$this->on.'="'.$func.'(arguments[0]); return false;" id="box">';
						$sw = Singleton::getInstance('StructureW');
						$arr = $sw->getData($this->levelmenu,'');
						if (isset($arr['this']['menu'])) $this->namemenu=$arr['this']['menu'];
						else $this->namemenu="";
						//echo '<span id="'.$this->idmenu.'" class="'.$this->typemenu.'" >'.$this->namemenu.'</span>';
						$PageM->zagtab=$this->namemenu.' '.$arr[0]["name"];
						//echo $PageM->zagtab;
						$namemenu=$PageM->zagtab;
						$arr = $arr['sections'];
						//echo $this->levelmenu;
						//$sqt=ElementsW::Showobjtype($arr[$this->levelmenu]);
						//echo $this->cont;
						echo '<ul class="Container">';
						$i = count($arr)-1;
						$num = 0;
						foreach($arr as $k => $val) {
							$num += $val['numEl'];
							if($k == $i) echo '<li class="'.$this->typemenu.$this->ex.'Closed isLast" id="'.$val['id'].'">';
							else echo '<li class="'.$this->typemenu.$this->ex.'Closed" id="'.$val['id'].'">';
							echo '<a class="'.trim($this->ex).'" href="'.$this->numpage.'?id='.$val['id'].'">'.$val['name'].'&nbsp;('.$val['numEl'].')</a></li>';			
						}
						echo '</ul>';
						//echo '<script type="text/javascript">document.getElementById("'.$this->idmenu.'").firstChild.nodeValue += " ('.$num.')";</script>';
						//echo $arr['0']['name'];
						//echo '<script type="text/javascript">document.getElementById("storeDiv").firstChild.createTextNode(" ('.$arr['0']['name'].')");</script>';
					//echo '<td><div id="storeDiv1" class="ListOpened"><br /></div></td>';
					echo '</div>';
					//echo 'construct Menu OK';
					return $namemenu;
	
}
	
public function menucss($list1,$list2,$tabl,$cl1='item',$cl2='menulevel'){

if(isset($list1)) $Menu->list1=$list1;
if(isset($list2)) $Menu->list2=$list2;
if (isset($tabl['pages'])) $Menu->tabl=$tabl['pages'];
//echo $Menu->tabl;
$Menu->list3=Elementsw::viewlistnew($Menu->list2,'list',$tabl);
//echo 'list1=';
//print_r($Menu->list1);
//echo count($Menu->list3).'-'.$Menu->list3[0][0].'-'.$Menu->list3[1][0];
for ($j=0; $j<count($Menu->list3[1]);$j++) $Menu->lp[$j]=explode(';',$Menu->list3[1][$j]);
//print_r($Menu->lp[1]);
//echo ' lp это<br>';

echo '<nav>';
if ($Menu->list2[0]=='') {
	
	for ($i=0;$i<count($Menu->list1); $i++) {
	$Menu->list2[$i]='#';
	echo '<li class="item">'.$Menu->list1[$i].'</li>';
	if ($nn==1) echo "<br>";
}
}
else {
	for ($i=0; $i<count($Menu->list1); $i++){
//$page= new Page($list2[$i],$tabl['pages'], $tabl['news']);
	$pagelist= new Page($Menu->list2[$i],$tabl);
	$Menu->list1[$i]=$pagelist->getnamepage($pagelist);
	/*if (!strstr($pagelist->MainAr["namep"],'.jpg')) {
	$Menu->list1[$i]=$pagelist->MainAr['namep'];
}
	else 
	{
	$l=explode('|',$pagelist->MainAr['namep']);
	$Menu->list1[$i]=$l[1];
	}*/
	$sp=explode(';',$pagelist->MainAr['numpage']);
	if ($sp[0] == '') $Menu->list2[$i]="";
	else $Menu->list2[$i]=$pagelist->MainAr['hrefp'].'?np='.$sp[0]; 
	echo '<ul><li class="item"><a href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'';
	echo '<ul class="menulevel">';
	$k=0;
	for ($k=0; $k<count($Menu->lp[$i]); $k++) {
		$pagelist= new Page($Menu->lp[$i][$k],$tabl);
		$sp=explode(';',$pagelist->MainAr['numpage']);
		$np=$pagelist->getnamepage($pagelist);
	if ($sp[0] == $PageM->MainAr['numpage']) $Menu->lp[$i][$k]="";
	else $Menu->lp[$i][$k]=$pagelist->MainAr['hrefp'].'?np='.$sp[0];
		if (count($Menu->lp[$i])>1) {
			//echo '<ul class="menulevel">';
			echo '<a href="'.$Menu->lp[$i][$k].'">'.$np.'</a></li>';
		}
		//else echo '<ul class="menulevel">';
	}
	echo '</ul></li></a>';
	}	
}
echo '</li></ul></nav>';
}
public function menulistarr($arr,$typelist) {
	$list1=$arr[$typelist];
	$list2=$arr[$typelist.'href'];
	$a_link=$arr['link'];
	unset($list1['link']);
	unset($list2['link']);
	$nopt=count($list2);
	Menu::menulist(1,$list1,$list2,$arr['tab'],$arr['clas'],$typelist);
}

public function menulist($nn,$list1,$list2,$tabl,$clas,$typelist) {
$Menu->list1=$list1;
$Menu->list2=$list2;
if ($Menu->list2=='' && $Menu->list1<>'') {
for ($i=0;$i<count($Menu->list1); $i++) {
		$Menu->list2[$i]='#';
		echo '<span>'.$Menu->list1[$i].'</span>';
		if ($nn==1) echo "<br>";
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
		if ($Menu->list1[$i]<>'')echo '<li><a  class="'.$clas.'" href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a></li>';
}
	else{ 
		$Menu->list2[$i]='./'.$pagelist->MainAr['hrefp'].'?np='.$Menu->list2[$i]; 
	if ($Menu->list1[$i]<>'') echo '<li><a class="'.$clas.'" href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a></li>';
	}
	//if ($nn==1) echo "<br>";
}	
}
}
//echo '</div>';
//Elementsw::Showobjtype($Menu->list1);
return;
}

static public function menulistr($nn,$list1,$list2,$clas) {
$tabl=$clas['tabl'];
$clas=$clas['clas'][19];
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
		if ($Menu->list1[$i]<>'')$str.='<div><a  class="'.$clas.'" href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a></div>';
}
	else{
		$Menu->list2[$i]='./'.$pagelist->MainAr['hrefp'].'?np='.$Menu->list2[$i]; 
	if ($Menu->list1[$i]<>'') $str.='<div><a class="'.$clas.'" href="'.$Menu->list2[$i].'">'.$Menu->list1[$i].'</a></div>';
	}
	//if ($nn==1) echo "<br>";
}	
}
}

//Elementsw::Showobjtype($Menu->list1);
return $str;
}

public function menulist2($nn, $list1) {
if ($nn==0){
	if (isset($list1)) $Menu->list1=$list1;
	for ($i=0; $i<count($Menu->list1); $i++){
	echo '<td class="zag2"><li class="listmenu" id="list">'.$Menu->list1[$i].'</li></td>';
		}
}
else {
if (isset($list1)) $Menu->list1=$list1;
	for ($i=0; $i<count($Menu->list1); $i++){
	echo '<li class="listmenu" >'.$Menu->list1[$i].'</li>';
		}
}
}

public function rasklad($value, $uLevel){
$value2=explode(';',$value);
	foreach ($value2 as $val)	{
		$pg= new Page($val,$tabl['pages'], $tabl['news']);
		$list3=explode(';',$pg->MainAr['butthref']);//массив номеров страниц, на которые ссылается массив alt названий кнопок
		$list4=explode('|',$pg->MainAr['buttimg']);//массив адресов картинок кнопок страницы
		$list5=explode('|',$pg->MainAr['buttons']);//массив alt названий кнопок страницы
		self::menulist(1,$list5,$list3,$hh,$gg,$uLevel());
	}

}

public function  menulist3($tt,$list1, $list2, $numpg){
$arr=explode($tt,$list2);
foreach ($arr as $key => $val) {
	
	$page= new Page($val,$tabl['pages'], $tabl['news']);
	$list1[$key]=$page->getnamepage($pagelist);
echo $list1[$key];echo "<BR>";
$sp=explode(';',$page->MainAr['list']);
if ($sp[0] == $numpg) $list2="";
else $list2[$key]=$page->MainAr['hrefp'].'?np='.$sp[0]; 
echo $list2[$key];echo "<BR>";
}
return $list2;
}

public function menubuttarr($tabl,$arr,$clas, $nc1,$levuser,$butt=true,$img=''){
	$list1=$arr['butt'];
	$list2=$arr['butthref'];
	$a_link=$arr['link'];
	
if (isset($list1)) $Menu->list1=$list1;
if (isset($list2)) $Menu->list2=$list2;
if (count($img)>1) $Menu->img=$img;
else for ($i=0;$i<count($Menu->list1);$i++) $Menu->img[$i]=$img[$i];
if ($Menu->list1[0]==""){
for ($i=0; $i<count($Menu->list2); $i++){
$page= new Page($Menu->list2[$i],$tabl);
$Menu->list1[$i]=$page->getnamepage($pagelist);
}	
}
for ($i=0; $i<8; $i++){
	$page= new Page($Menu->list2[$i],$tabl);
	$Menu->list2[$i]='?np='.$page->MainAr['numpage']; 
	//echo $a_link['butt'][$i];
if ($Menu->list1[$i] <> '' && $levuser>3) $page->DisplayButArr($a_link['butt'][$i],$a_link['butthref'][$i],$a_link['imgs'][$i],$Menu->list1[$i], $Menu->list2[$i],$clas,$nc1,count($Menu->list1),$levuser,$butt,$Menu->img[$i]); 
elseif($Menu->list1[$i] <> '') $page->DisplayButDiv($Menu->list1[$i], $Menu->list2[$i],$clas,$nc1,count($Menu->list1),$butt,$Menu->img[$i]);
}
echo '------------------------------';
return;
}



public function menubuttdiv($tabl,$list1,$list2,$clas, $nc1,$butt=true,$img=''){
if (isset($list1)) $Menu->list1=$list1;
if (isset($list2)) $Menu->list2=$list2;
if(is_array($img)){
if (count($img)>1) $Menu->img=$img;
else for ($i=0;$i<count($Menu->list1);$i++) $Menu->img[$i]=$img[$i];
}
else $Menu->img='';
if ($Menu->list1[0]==""){
for ($i=0; $i<count($Menu->list2); $i++){
$page= new Page($Menu->list2[$i],$tabl);
$Menu->list1[$i]=$page->getnamepage($pagelist);
}	
}
//print_r($Menu->list1);
for ($i=0; $i<8; $i++){
	if(isset($Menu->list2[$i])){
		$page= new Page($Menu->list2[$i],$tabl);
		if($img=='')$Menu->img[$i]=$Menu->img;
		$Menu->list2[$i]='?np='.$page->MainAr['numpage']; 
		if ($Menu->list1[$i] <> '') $page->DisplayButDiv($Menu->list1[$i], $Menu->list2[$i],$clas,$nc1,count($Menu->list1),$butt,$Menu->img[$i]); 
	}
}
return;
}


public function menubuttone($list1,$nn){
if (isset($list1)) $Menu->list1=$list1;
Page::DisplayButton($Menu->list1,1,false); 
if ($nn==1) echo "<br>";
}

public function menubutt($list1,$list2,$list3=null,$nn,$tabl){
if (isset($list1)) $Menu->list1=$list1;
if (isset($list2)) $Menu->list2=$list2;
if (isset($tabl)) $Menu->tabl=$tabl;

if ($list3 == null) {
	for ($i=0; $i<count($Menu->list1); $i++){
	$list3[$i]='./images/butnoch.jpg';
	}
}
else $Menu->list3=$list3;
$widt=200*count($Menu->list1);
//$ww=100*count($Menu->list1)*200/1200;
echo '<table border="0" cellpadding="0" cellspacing="0" style="border-collapse: collapse" bordercolor="#111111" width="'.$widt.'" height="18"><tr align="center">';
for ($i=0; $i<count($Menu->list1); $i++){
$page= new Page($list2[$i], $Menu->tabl);
$Menu->list1[$i]=$page->getnamepage($pagelist);
$sp=$page->MainAr['numpage'];
if ($sp == $PageM->MainAr['numpage']) {
	$Menu->list2[$i]="";
	$Menu->list3[$i]='./images/butch.jpg';
}
else $Menu->list2[$i]=$page->MainAr['hrefp'].'?np='.$sp;
Page::DisplayButton($Menu->list1[$i],100/count($Menu->list1), $Menu->list3[$i], $Menu->list2[$i]); 
if ($nn==1) echo "<br>";
}

}

public function showallmenu($tabl,$arrmain,$clas,$nc,$levuser){
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
	if ($arrmain['buttimg'][0]<>'./images/' && $arrmain['typmen'][2]<> 'nbt') {//если картинки кнопок есть
		echo 'id меню с картинками кнопок <br>';
		echo '<div id="menu'.$just.$nmo.'">';
		//Menu::menubutt($list[5][0],$list[3][0],null,1,$tabl);
		//Menu::menubuttdiv($tabl,$arrmain['butt'],$arrmain['butthref'],$clas,4,true,$a_imgs);
		//print_r($arrmain);
		Menu::menubuttarr($tabl,$arrmain,$clas,4,$levelU,true,$a_imgs);
		
		echo '------------------------------';
		
	echo '</div>';
	}
	else {//если картинок нет 
	//echo ' - '.$list['11'][2].' - ';
		if ($arrmain['typmen'][2]<> 'nbt'){//если нет названий кнопок берем название страниц и ссылки из list
			//7
			echo '<ul class="menudown">';
			Menu::menubuttdiv($tabl,$arrmain['butt'],$arrmain['butthref'],$clas,21,false,'');
		
		echo '</ul>';
		}
	elseif ($arrmain['typmen'][1]<> 'nmn') {//если есть названия кнопок и ссылки берем все из buttons
			show::menush($arrmain,'butt',$tabl);
			
			}
	}
}

}

}
?>