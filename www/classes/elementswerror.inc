<?php

class ElementsW extends Singleton {
	
	//const SORT_ART = 0;
	const SORT_VEND = 0;
	const SORT_NAME = 1;
	const SORT_PRICE = 2;
	
	
	private $db = null;
	private $opt = array();
	private $const = array();
	private $constopt = array();
	private $codeGJS = array();
	private $stock=0;
	private $vendor='';
	private $tab='';
	private $d='';
	
	protected function __construct() {
		$this->db = Singleton::getInstance('DB');
		//echo 'construct EW OK';
	}
 public function Showobjtype($p) {
  echo '<br/>';
  while ($element = each($p))
  {
  echo "ключ ".$element['key'];
  echo '-';
  echo "значение ".$element['value'];
  echo '<br/>';
  }
  }
public function Shownametype($p) {
  echo '<br/>';
  while ($element = each($p))
  {
  echo "ключ ".$this->getnameSection($element['key']);
  echo '-';
  echo "значение ".$element['value'];
  echo '<br/>';
  }
  }
  
	function prepare() {
		$this->db->query('TRUNCATE TABLE `elements`;');
		$this->db->query('TRUNCATE TABLE `elements-elements`;');
		$this->db->query('TRUNCATE TABLE `type-elements`;');
		echo 'prepare OK';echo "<BR>";
	}	

	function prepare_table($a) {
		$this->name=$a;
		$this->db->query('TRUNCATE TABLE `'.$this->name.'`;');
		echo 'prepare OK';echo "<BR>";
		}
	public function view_table($a,$b){
		echo "вывод таблицы -".$a;echo "<BR>";
		if ($a<>''){
		$d='select * from '.$a.';';
		//echo $d;
		$g=mysql_query('select * from '.$a.';');
		echo "В таблице $a ".mysql_num_rows($g)." записи и ".mysql_num_fields($g)." полей";
		if(mysql_num_rows($g)>0) echo '------->';
		echo "<BR>";
		}
	}
	
	function get_book_details($isbn,$tab)
{
  // Выполняет запрос в базу данных детальной информации о книге
  if (!$isbn || $isbn=='')
     return false;
$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `'.$tab.'` WHERE `codeGJS` = ^Ni;', $isbn);
		if($res != null) {
			return array('title' => $res->name, 'art' => $res->art, 'author' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'isbn' => $res->codeGJS);
		} else {
			return false;
			}
   /*$conn = db_connect();
   $query = "select books.id as catid, codeGJS as isbn, vendor as author, name as title, art, price from elements as books where codeGJS ='$isbn'";
   $result = @$conn->query($query);
   //$result = $conn->query($query);
   if (!$result)
     return false;
   $result = @$result->fetch_assoc();
   
   return $result;*/
}

//функция выбирает элементы группы удовлетворяющие условиям: у товара имеется картинка, элемент находится в таблице спец предложений (по умолчанию)
function geteltidpics ($tid, $spec=1) {
	$ar=array();
	$return=array();
	$i=0;
	$ar=$this->geteids($tid);//получаем все eid товаров группы с tid
	if ($ar[0] <> '') {
	//$this->Showobjtype($ar);
	foreach ($ar as $val) {
		if ($spec <> 1) $ret=$this->getElement($val,'elemarch');
		else $ret=$this->getElement($val,'elemspec');
		if ($ret <> null) {
			
			//echo $ret['id'];
			$image=$this->gjspics($ret['codeGJS']);
			//$this->Showobjtype($image);
		if ($image[0] <> null) {
			if (is_array($image)) {
				$return[$i]['pics']=$image[0];
				$return[$i]['GJS']=$ret['codeGJS'];
				$return[$i]['eid']=$ret['id'];
				$return[$i]['name']=$ret['name'];
				$return[$i]['art']=$ret['art'];
				$return[$i]['vendor']=$ret['vendor'];
				$return[$i]['ms']=$ret['ms'];
				$return[$i]['ls']=$ret['ls'];
				$return[$i]['stock']=$ret['stock'];
				$return[$i]['price']=$ret['price'];
				$return[$i]['date2']=$ret['date2'];
				$return[$i]['desc']=$ret['desc'];
				//echo 'есть картинка '.$i.'<br>';
				//$this->Showobjtype($return[$i]);
				}
				$i++;
				//else $return[$i]['pics']=$image;
				}
			
		//else echo 'нет картинка '.$i.'<br>';
		}
		
	
	}
}
	//echo 'I='.$i;
	if ($i == 0) $return=null;
	return $return;
	}


	function addElement($codeGJS, $name, $desc, $art, $vendor, $price, $tid, $opt, $const, $constopt) {
		$this->db->query('INSERT INTO `elements` (`codeGJS`, `name`, `desc`, `art`, `vendor`, `price`) VALUES (^Ns, ^Ns, ^Ns, ^Ns, ^Ns, ^Ni);', $codeGJS, $name, $desc, $art, $vendor, $price);	
		$id = $this->db->id();	
		$tids = explode(';', $tid);
		foreach($tids as $val) {
			$this->db->query('INSERT INTO `type-elements` (`tid`, `eid`) VALUES (^Ni, ^Ni);', $val, $id);
		}
		if(!empty($opt) && $opt != ' ') {
			$opts = explode(',', $opt);	
			$this->opt[$id] = $opts; 
		}
		if(!empty($const) && $const != ' ') {
			$consts = explode(',', $const);		
			$this->const[$id] = $consts; 
		}
		if(!empty($constopt) && $constopt != ' ') {
			$constopts = explode(',', $constopt);		
			$this->constopt[$id] = $constopts; 
		}
	}

	function finishAdd() {
		$res = $this->db->query('SELECT `id`, `codeGJS` FROM `elements`;');
		if($res !== null) {
			if(!is_array($res)) {
				$this->codeGJS[$res->codeGJS] = $res->id;			
			} else {
				foreach($res as $val)
					$this->codeGJS[$val->codeGJS] = $val->id;		
			}
		}
		foreach($this->opt as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `elements-elements` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'0\');', $id, $this->codeGJS[$v]);
			}		
		}
		foreach($this->const as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `elements-elements` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'1\');', $id, $this->codeGJS[$v]);
			}		
		}
		foreach($this->constopt as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `elements-elements` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'2\');', $id, $this->codeGJS[$v]);
			}		
		}
		Utils::calcNumEl();
	}
	
	public function addseansuser($uid,$stat=0){
		$find=$this->db->query('select `id`,`ciid` from `users` where `id`= ^Ni;', $uid);
		if (isset($find->ciid) && $stat>0) $statnew= $find->ciid +1;
		$this->db->query('UPDATE `users` SET `ciid` = ^Ni WHERE `id` = ^Ni;', $statnew, $uid);

	}
	public function calculate_price($cart)
{
  // Вычисляет общую стоимость всех элементов тележки
  $price = 0;
  if(is_array($cart))
  {
    //$conn = db_connect();
	$s=1;
    foreach($cart as $isbn => $qty)
    {  
      //$query = "select price from elemarch as books where `codeGJS`=^Ni';$isbn";
      $result = $this->db->query('select `price` from `elemarch` where `codeGJS`=^Ni;',$isbn);
      if ($result)
      {
		//$item = $result->fetch_object();
        //$item_price = $item->price;
		$item_price = $result; 
		$price +=$item_price*$qty;
		}
	  else $s=0;
    }
	$price=$price*$s;
  }
  return $price;
}

	function getDataG($id, $sort = self::SORT_NAME, $sortOrder = 0) {
		$order = ' ORDER BY ';
		switch($sort) {
			case self::SORT_NAME:
				$order .= '`name`';
				break;
			case self::SORT_ART:
				$order .= '`art`';
				break;
			case self::SORT_PRICE:
				$order .= '`price`';
				break;
			default:
				$order .= '`name`';	
		}
		if($sortOrder) {
			$order .= ' DESC';
		}
		$res = $this->db->query('SELECT t1.id, `name`, `art`, `price`, `stock`,`ms`,`ls`, `codeGJS`, `date2` FROM `elements` as t1, `type-elements` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
		$return = array();
		if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price, 'ms' => $res->ms, 'codeGJS' => $res->codeGJS, 'stock' => $res->stock, 'ls' => $res->ls, 'date2' => $res->date2);	
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms, 'codeGJS' => $val->codeGJS, 'stock' => $val->stock, 'ls' => $val->ls, 'date2' => $val->date2);
				}
			}
		}
		return $return;				 
	}
	function getDataIE($id, $sort = self::SORT_NAME, $sortOrder = 0, $tab) {
		$order = ' ORDER BY ';
		switch($sort) {
			case self::SORT_NAME:
				$order .= '`name`';
				break;
			case self::SORT_ART:
				$order .= '`art`';
				break;
			case self::SORT_PRICE:
				$order .= '`price`';
				break;
			default:
				$order .= '`name`';	
		}
		if($sortOrder) {
			$order .= ' DESC';
		}
		$res = $this->db->query('SELECT t1.id, `name`, `art`, `price`, `stock`,`ms`,`ls`, `codeGJS`, `date2` FROM `'.$tab.'` as t1, `type-elements` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
		$return = array();
		if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price, 'ms' => $res->ms, 'codeGJS' => $res->codeGJS, 'stock' => $res->stock, 'ls' => $res->ls, 'date2' => $res->date2);
				//$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price);		
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms, 'codeGJS' => $val->codeGJS, 'stock' => $val->stock, 'ls' => $val->ls, 'date2' => $val->date2);
					//$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price);
				}
			}
		}
		return $return;				 
	}
	
	function getData($id, $sort = self::SORT_VEND, $sortOrder = 0, $tab) {
		$order = ' ORDER BY ';
		switch($sort) {
			case self::SORT_NAME:
				$order .= '`name`';
				break;
			case self::SORT_VEND:
				$order .= '`vendor`';
				break;
			case self::SORT_PRICE:
				$order .= '`price`';
				break;
			default:
				$order .= '`vendor`';	
		}
		if($sortOrder) {
			$order .= ' DESC';
		}
		$res = $this->db->query('SELECT t1.id, `name`, `art`, `price`, `stock`,`ms`,`ls`, `codeGJS`, `desc`,`date2` FROM `'.$tab.'` as t1, `type-elements` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
		$return = array();
		if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price, 'ms' => $res->ms, 'codeGJS' => $res->codeGJS,'desc' => $res->desc, 'stock' => $res->stock, 'ls' => $res->ls, 'date2' => $res->date2);		
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms, 'codeGJS' => $val->codeGJS, 'desc' => $val->desc,'stock' => $val->stock, 'ls' => $val->ls, 'date2' => $val->date2);
				}
			}
		}
		return $return;				 
	}
	
	function getData1($id, $sort = self::SORT_VEND, $sortOrder = 0) {
		$order = ' ORDER BY ';
		switch($sort) {
			case self::SORT_NAME:
				$order .= '`name`';
				break;
			case self::SORT_VEND:
				$order .= '`vendor`';
				break;
			case self::SORT_PRICE:
				$order .= '`price`';
				break;
			default:
				$order .= '`vendor`';	
		}
		if($sortOrder) {
			$order .= ' DESC';
		}
		$res = $this->db->query('SELECT t1.id, `name`, `art`, `price`, `stock`,`ms`,`ls`, `codeGJS`, `date2` FROM `'.$tabl.'` as t1, `type-elements` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
		$return = array();
		if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price, 'ms' => $res->ms, 'codeGJS' => $res->codeGJS, 'stock' => $res->stock, 'ls' => $res->ls, 'date2' => $res->date2);		
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms, 'codeGJS' => $val->codeGJS, 'stock' => $val->stock, 'ls' => $val->ls, 'date2' => $val->date2);
				}
			}
		}
		else {
			$res = $this->db->query('SELECT t1.id, `name`, `art`, `price`, `stock`,`ms`,`ls`, `codeGJS`, `date2` FROM `elemarch` as t1, `type-elements` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
			if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price, 'ms' => $res->ms, 'codeGJS' => $res->codeGJS, 'stock' => $res->stock, 'ls' => $res->ls, 'date2' => $res->date2);		
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms, 'codeGJS' => $val->codeGJS, 'stock' => $val->stock, 'ls' => $val->ls, 'date2' => $val->date2);
				}
			}		
		}
		}
		return $return;				 
	}
	
	function getElement($id,$tab) {
		$res = $this->db->query('SELECT `id`,`name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `'.$tab.'` WHERE `id` = ^Ni;', $id);
		if($res != null) {
			return array('id' => $res->id,'name' => $res->name, 'stock' => $res->stock, 'art' => $res->art, 'vendor' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'codeGJS' => $res->codeGJS,'desc' => $res->desc,'date1' => $res->date1,'date2' => $res->date2);
		} else {
			return null;
		}
	}
	
	function checkdescription($cgjs,$field1,$field2,$table){
	$array=array();
	$res=$this->db->query('SELECT `'.$field1.'` FROM `'.$table.'` WHERE `'.$field2.'`= ^Ni;', $cgjs);
	if($res !== null) {
	$array=explode('|',$res);
	//echo $array[0].'---'.$array[1].'---'.$array[2].'---'.$array[3].'---'.$array[4].'<br/>';
	return $array;
	}
	else return null;
}
	
	public function showgood($el) {
			if($el !== null) {
			// в arr1 записываем данные из поля desc
			if (strstr($el['desc'],'|')) $arr1=explode('|',$el['desc']);
			else {
				 $arr1[0]=$el['desc'];
				  $arr1[1]='';
				}
			//  $this->Showobjtype($arr1);
			//	в arr запишим данные для описания товара : номер заголовков описния, и значения параметров 
				$arr=$this->checkdescription($el['codeGJS'],'nampars','GJScode','params');
				// если в params нет такого кода, то первй элемент массива arr заносим первый элемент из arr1
				//if ($arr == null) $arr[0]=$arr1[0];
				// в arr2 запишим названия  параметров
				$arr2=$this->checkdescription($arr[0],'nampars','codparams','namparams');
				if ($arr == null ) {
					//echo 'в params нет';//раскладываем название товара на параметры разделеные запятой
					$arr=explode(',',$el['name']);
					//если массив содержит более 1-го элемента, первый элемент становится названием товара в таблице параметров
					if (count($arr)>1) $el['name']=$arr[0];
					}
				}
				//$this->Showobjtype($arr2);
				//$this->Showobjtype($arr);
				// вывод таблицы парметров
				//$arr1[1]-руское название товара
				echo '<div class="head" >'.$arr1[1].' '.$el['art'].' - <b>'.$el['name'].'</b><a id="close" href="#" onclick="self.close();">X</a></div>
				<table>
					<tr class="s0">
						<td class="c1">Производитель</td>
						<td class="c2">'.$el['vendor'].'</td></tr>
						<tr class="s1">
						<td class="c1">Код для заказа</td>
						<td class="c2">'.$el['codeGJS'].'</td></tr>';
					if ($arr1[3] !=='') {
						echo '<tr class="s1"><td class="c1">Позиционирование:</td>
						<td class="c2">'.$arr1[3].'</td></tr>';
						}
					echo '<tr class="s2">
						<td class="c1">Стоимость:</td>
						<td class="c2">'.$el["price"].' $USA</td>
					</tr>
					<tr class="s3">
						<td class="c1">Доступность для заказа</td>';
			if ($el['stock']>5) { 
					echo '<td class="c2"><a href="http://shop.deltar.ru/book/show_cart.php?new='.$el['codeGJS'].'"> Товар на складе</a></td>';
					}
			else  {				
					if ($el['stock']<6 && $el['stock']>0) echo '<td class="c2">Товар на складе заканчивается</td>';
					else {
						if ($el['date2']>date('U')) echo '<td class="c2">Товар в транзите</td>';
						else echo '<td class="c2">Уточните состояние лигистики</td></tr>';
					}
					}
					if ($el['date2'] == ''  || $el['date2'] == '0000-00-00' || $el['date2'] == '1900-01-00') {
					echo '<tr class="s4">
						<td class="c1">Ближайшие транзиты (год,мес.,ден.):</td>
						<td class="c2">'.$el['date2'].'</td></tr>';
						}
					//	$arr1[4]-ссылка на сайт производителя
					if ($arr1[4] !== '') echo '<tr class="s5">
						<td class="c1">Ссылка на сайт производителя</td>
						<td class="c2"><a target="blanc" href="'.$arr1[4].'">'.$el['art'].'</td></tr>';	
					//	$arr1[5]-срок гарантии производителя
					if ($arr1[5] !== '') echo '<tr class="s5">
						<td class="c1">Гарантия производителя в месяцах</td>
						<td class="c2">'.$arr1[5].'</td></tr>';	
					if ($arr1[6] !== '') echo '<tr class="s5">
						<td class="c1">Размеры в см (ДхШхВ); Объем в л.; Вес в кг.</td>
						<td class="c2">'.$arr1[6].'</td></tr>';
				echo '</table>';
				if ($arr[0] > 0){
				echo '<div class="head"><b>Характеристики товара</b>';	
				echo '<table>';
				$l=1;
				for ($i=1;$i<count($arr2);$i++){
					if ($arr[$i] !== '' && $arr[$i] !== ' ') {
					$l=$l+1;
					echo '<tr class="s1">
						<td class="c1">'.$arr2[$i-1].'</td>';
					if ($arr[$i] == "Y") $a="Да";
					else {
						if ($arr[$i] == "N") $a="Нет";
						else $a=$arr[$i];
						}
						echo '<td class="c2">'.$a.'</td></tr>';
					}
				}
				echo '</table></div>';
				}
	//if (!isset($i)) $l=1;		
if (file_exists('./images/pics/'.$arr1[2].'.jpg'))
      {
         $size = GetImageSize('./images/pics/'.$arr1[2].'.jpg'); 
		 if($size[0]>50 || $size[1]>50){	
	$www=-$l*30;
	if ($arr1[2] !== '') echo '<div style="width: 300px; border: solid 1px #808080; position: relative; top:'.$www.'px; left: 800px;"><img  src="./images/pics/'.$arr1[2].'.jpg" width = '.intval($size[0]/2).' height= '.intval($size[1]/2).'alt="" style="width: 300px;" /></div>';
	}
	else if ($arr1[2] !== '') echo '<div style="width: 300px; border: solid 1px #808080; position: relative; top:'.$www.'px; left: 800px;"><img  src="./images/pics/'.$arr1[2].'.jpg" alt="" style="width: 300px;" /></div>';
	}
	$ok = 1;
return $ok;			
}	

public function kurs($t='null'){
if ($t == 'null') {
$ts=date('U');
$now=getdate($ts);
}
else $now=getdate($t);
$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
$res=$this->db->query('SELECT `dol`, `evro` FROM `kurs` WHERE `datcurs` = ^Ns;', $tt);
if (!$res === false) $ku=array('dol'=>$res->dol,'evr'=>$res->evro);
else $ku=false;
//echo $ku;
return $ku;
}
	
public function gjspics($gjs){
$codpic='';
$res=$this->db->query('SELECT `gjs`, `istoch`,`variant`,`exist` FROM `pics` WHERE `gjs` = ^Ni;', $gjs);
if (!$res === false) {
	if(!is_array($res)) $return[] = array('gjs' => $res->gjs, 'istoch' => $res->istoch, 'variant' => $res->variant);
	else {
			foreach ($res as $val) {
					$return[] = array('gjs' => $val->gjs, 'istoch' => $val->istoch, 'variant' => $val->variant);
					}
		}
}
if (is_array($return)) {
foreach ($return as $value) {
	$codepic[].=$value['gjs'].'_'.$value['istoch'].'_'.$value['variant'].'.jpg';
	}
	}
else 	$codepic=null;
return $codepic;
}	
	// вывод в массив результатов поиска в полях name art таблицы  `elements` записей с условием на поле vendor=vend

public function getlookfor($for,$vend) {
$return = array();
$k=0;

//создаем sql-запрос  записи с номером =k таблицы `elements` и удовлетврояющей условию на поле vendor=vend
$res=$this->db->query('SELECT `id`,`name`,`art`, `vendor` FROM `elements`;');
//если запись существует, ищем в полях name art подстроку for
	if (!$res === false)
{
	//echo 'resultat +';echo '<br>';
	foreach ($res as $val){
	$result=stristr($val->name,$for);
	if ($result === false){
		$result=stristr($val->art,$for);
		if ($result === false){
		
		}
		else {
		//echo 'Найдено в позици art'.$val->id;
		$return[$k]=array('id' => $val->id, 'vendor' => $val->vendor);
		//echo '<br>';
		//echo $return[$k]['id'];
		//echo '<br>';
		$k++;
		}
	}
	else {
	//echo 'Найдено в позици name'.$val->id;
	// создаем элемент массива с индексом k, в который помещаем идентификационный номер записи и строку, в которой найден результат
	$return[$k]=array('id' => $val->id, 'vendor' => $val->vendor);
	//echo '<br>';
	//echo $return[$k]['id'];
	//echo '<br>';
	$k++;
	}
	}
}
//если запись не найдена переходит к следующему номеру k+1 и повторяет поиск

//return null;
// вывод результата поиска на экран
if (!($result === false)){
	echo '<td>В каталоге нет совпадений с Вашим запросом.'.$for.'</td></tr><tr><td>';
	}
else {
	$ret=array();		
	$ret=$this->chioce_vendor($return, $vend);		
	$return=$ret;	
	$nn=count($return);
	echo '</tr><tr><td><div style="padding:0px 0px 0px 0px; margin:0px;"><b>Найдено по запросу:|</b> '.$for.'| '.$nn.' совпадений</div></td></tr>';
	echo '</table>';
	//echo '<table class="goods"><tr class="head"><td width="200">Артикул</td><td width="100">Производитель</td><td width="400">Наименование</td><td>Цена</td><td>На складе</td><td>Код товара</td><td>Доступность</td></tr><tr>';
	//echo '<table class="goods"><tr class="head"><td width="200">Артикул</td><td width="100">Производитель</td><td width="400">Наименование</td><td>Цена</td><td>Доступность</td><td>для заказа</td><td>Транзит</td></tr><tr>';			}
	echo '<table class="goods"><tr class="head"><td width="200">Код для заказа</td><td width="100">Наименование</td><td>Цена,$USA </td><td>Доступность</td><td>для заказа</td><td>Дата ближайшего транзита</td></tr><tr>';			}
	//отбор по вендору


//освобождаем память
unset($res);
unset($ret);
return $return;	//возвращает все идентификаторы найденных записей в виде массива	
}	
	
public function viewer($return,$sort=0,$vend) {
$arr = array();
$return1 = array();
$return2 = array();
$ret['tid']=Array();
$ret['id']=Array();
$ret['num']=Array();
for($i=0;$i<=count($return);$i++){
	$arr=$return[$i];
	$k=$arr['id'];
	
	$res2 = $this->db->query('SELECT `id`,`vendor`,`codeGJS`,`name`, `art`, `price`,`ms`,`ls`,`stock` FROM `elements` WHERE `id` = ^Ni;', $k);
	
	if($res2 !== null) {
				if(!is_array($res2)) {
					$return1[$i] = array('tid' => $this->getSection($res2->id),'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					$return2[$i] = array('tid' => $this->getSection($res2->id),'art' => $res2->art,'name' => $res2->name,'price' => $res2->price,'stock' => $res2->stock, 'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					
					if ($sort==0) $this->viewData($return2[$i],0);
					else {
						$ret['tid'][$i]=$return1[$i]['tid'];
						$ret['id'][$i]=$return2[$i]['id'];
						}
					} 
			else {
			foreach ($res2 as $val){
			$return2[] = array('id' => $val->id,'codeGJS' => $val->codeGJS, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms,'ls' => $val->ls, 'stock' => $val->stock, 'tid' => $this->getSection($val->id));
						
						}
		}
	}
}
//$this->Showobjtype($ret['id']);
$array=array();
$l=count($ret['id']);
for ($j=0;$j<$l;$j++) $array[$ret['id'][$j]]=$ret['tid'][$j];
$array[$ret['id'][$l]]=100000;
					asort($array);
					//$this->Showobjtype($array);
					asort($ret['tid']);
					//$this->Shownametype($ret['tid']);
					$ac=array_count_values($ret['tid']);
					//$this->Shownametype($ac);
					$ar=array();
					$k=0;
					$z='| ';
					set_time_limit(2500);
					$i=1;
					while ($el=each($ac)) {
					//$axe[$el['key']]=$this->getSection($el['key']);
					//echo $el['key'].'--'.$el['key'];echo '<br>';
					$z.='<a href="#'.$el['key'].'">'.$this->getnameSection($el['key']).'</a>';
					$zz=$this->getnameSection($el['key']);
					$z.=' | ';
					echo '<tr class="head"><td colspan="7"><div><a name="'.$el['key'].'"><b>'.$zz.'</b></div></td></tr>';
					//$this->Showobjtype($array);
					$l=2;
						while ($el1=each($array)){
							$t=$l%2;
							$b=$k+$el['value'];
							//echo $b;echo '<br>';
							//echo $i.'-'.$b;echo '<br>';
							if($i<=$b){
								$ar=$this->viewfindid($el1['key'],$vend);
								//$this->Showobjtype($ar[0]);
								//$this->Showobjtype($ar[0]);
								echo '<tr class="a'.$t.'">';
								$this->viewData($ar[0],0);
								$l++;
								$i++;
											}
								else {
								$el1=prev($array);
								break;}
}
							echo '</div>';		
			
							$k=$k+$el['value'];
											}
	if (count($ac)>1)	echo '<tr>'.$z.'</tr></table>';							
	set_time_limit(600);
	return $ret;
		}

public function getlookfortab($for,$vend,$tab) {
$return = array();
$k=0;

//создаем sql-запрос  записи с номером =k таблицы `elements` и удовлетврояющей условию на поле vendor=vend
$res=$this->db->query('SELECT `id`,`name`,`art`, `vendor` FROM `'.$tab.'`;');
//если запись существует, ищем в полях name art подстроку for
	if (!$res === false)
{
	//echo 'resultat +';echo '<br>';
	foreach ($res as $val){
	$result=stristr($val->name,$for);
	if ($result === false){
		$result=stristr($val->art,$for);
		if ($result === false){
		
		}
		else {
		//echo 'Найдено в позици art'.$val->id;
		$return[$k]=array('id' => $val->id, 'vendor' => $val->vendor);
		//echo '<br>';
		//echo $return[$k]['id'];
		//echo '<br>';
		$k++;
		}
	}
	else {
	//echo 'Найдено в позици name'.$val->id;
	// создаем элемент массива с индексом k, в который помещаем идентификационный номер записи и строку, в которой найден результат
	$return[$k]=array('id' => $val->id, 'vendor' => $val->vendor);
	//echo '<br>';
	//echo $return[$k]['id'];
	//echo '<br>';
	$k++;
	}
	}
}
//если запись не найдена переходит к следующему номеру k+1 и повторяет поиск

//return null;
// вывод результата поиска на экран
if (!($result === false)){
	echo '<td>В каталоге нет совпадений с Вашим запросом.'.$for.'</td></tr><tr><td>';
	}
else {
	$ret=array();		
	$ret=$this->chioce_vendor($return, $vend);		
	$return=$ret;	
	$nn=count($return);
	echo '<td>Найдено по запросу:'.$for.' '.$nn.' совпадений</td></tr><tr><td>';
	echo '<div class="button">Результат поиска</div></tr></table>';
	//echo '<table class="goods"><tr class="head"><td width="200">Артикул</td><td width="100">Производитель</td><td width="400">Наименование</td><td>Цена</td><td>На складе</td><td>Код товара</td><td>Доступность</td></tr><tr>';
	echo '<table class="goods"><tr class="head"><td width="200">Код для заказа</td><td width="100">Наименование</td><td width="400"></td><td>Цена,$USA </td><td>Доступность</td><td>для заказа</td><td>Дата ближайшего транзита</td></tr><tr>';			}
//отбор по вендору


//освобождаем память
unset($res);
unset($ret);
return $return;	//возвращает все идентификаторы найденных записей в виде массива	
}	
	
public function viewertab($return,$sort=0,$vend,$tab) {
$arr = array();
$return1 = array();
$return2 = array();
$ret['tid']=Array();
$ret['id']=Array();
$ret['num']=Array();
for($i=0;$i<=count($return);$i++){
	$arr=$return[$i];
	$k=$arr['id'];
	
	$res2 = $this->db->query('SELECT `id`,`vendor`,`codeGJS`,`name`, `art`, `price`,`ms`,`ls`,`stock` FROM `'.$tab.'` WHERE `id` = ^Ni;', $k);
	
	if($res2 !== null) {
				if(!is_array($res2)) {
					$return1[$i] = array('tid' => $this->getSection($res2->id),'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					$return2[$i] = array('tid' => $this->getSection($res2->id),'art' => $res2->art,'name' => $res2->name,'price' => $res2->price,'stock' => $res2->stock, 'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					
					if ($sort==0) $this->viewData($return2[$i],0);
					else {
						$ret['tid'][$i]=$return1[$i]['tid'];
						$ret['id'][$i]=$return2[$i]['id'];
						}
					} 
			else {
			foreach ($res2 as $val){
			$return2[] = array('id' => $val->id,'codeGJS' => $val->codeGJS, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms,'ls' => $val->ls, 'stock' => $val->stock, 'tid' => $this->getSection($val->id));
						
						}
		}
	}
}
//$this->Showobjtype($ret['id']);
$array=array();
$l=count($ret['id']);
for ($j=0;$j<$l;$j++) $array[$ret['id'][$j]]=$ret['tid'][$j];
$array[$ret['id'][$l]]=100000;
					asort($array);
					//$this->Showobjtype($array);
					asort($ret['tid']);
					//$this->Shownametype($ret['tid']);
					$ac=array_count_values($ret['tid']);
					//$this->Shownametype($ac);
					$ar=array();
					$k=0;
					$z='| ';
					set_time_limit(2500);
					$i=1;
					while ($el=each($ac)) {
					//$axe[$el['key']]=$this->getSection($el['key']);
					//echo $el['key'].'--'.$el['key'];echo '<br>';
					$z.='<a href="#'.$el['key'].'">'.$this->getnameSection($el['key']).'</a>';
					$zz=$this->getnameSection($el['key']);
					$z.=' | ';
					echo '<tr class="head"><td colspan="7"><div><a name="'.$el['key'].'"><b>'.$zz.'</b></div></td></tr>';
					//$this->Showobjtype($array);
					$l=2;
						while ($el1=each($array)){
							$t=$l%2;
							$b=$k+$el['value'];
							//echo $b;echo '<br>';
							//echo $i.'-'.$b;echo '<br>';
							if($i<=$b){
								$ar=$this->viewfindidtab($el1['key'],$vend,$tab);
								//$this->Showobjtype($ar[0]);
								//$this->Showobjtype($ar[0]);
								echo '<tr class="a'.$t.'">';
								$this->viewData($ar[0],0);
								$l++;
								$i++;
											}
								else {
								$el1=prev($array);
								break;}
}
							echo '</div>';		
			
							$k=$k+$el['value'];
											}
	if (count($ac)>1)	echo '<tr>'.$z.'</tr></table>';							
	set_time_limit(600);
	return $ret;
		}
		
function viewfindidtab($id,$vend,$tab){
		$return = array();
		$k=$id;
		if (isset($vend)&&!$vend=='') {
		$this->vendor=$vend;
		$res2 = $this->db->query('SELECT `id`,`codeGJS`,`vendor`,`name`, `art`, `price`,`ms`,`ls`,`stock`,`date2` FROM `'.$tab.'` WHERE `id` = ^Ni and `vendor`=^Ns;', $k, $this->vendor);			
							}
		else 				{
		$res2 = $this->db->query('SELECT `id`,`codeGJS`,`vendor`,`name`, `art`, `price`,`ms`,`ls`,`stock`,`date2` FROM `'.$tab.'` WHERE `id` = ^Ni;', $k);			
							}
		if($res2 !== null) { 
		//echo 'yes1';
			if(!is_array($res2)) {
				//echo 'yes2';
				$return[] = array('art' => $res2->art,'vendor' => $res2->vendor,'name' => $res2->name,'price' => $res2->price,'stock' => $res2->stock,'id'=>$res2->id,'codeGJS' => $res2->codeGJS,'ls'=>$res2->ls,'ms'=>$res2->ms,'date2'=>$res2->date2);
					} 
			else {
			//echo 'yes3';
			foreach ($res2 as $val){
			$return[] = array('id' => $val->id,'vendor' => $val->vendor,'codeGJS' => $val->codeGJS, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms,'ls' => $val->ls, 'stock' => $val->stock, 'tid' => $this->getSection($val->id), 'date2' => $val->date2);
							}
		}
	}
return $return;	
	}
		
public function getsubsection ($tid){
if($tid !== 0){
		$find=$this->db->query('select `pid` from `structure` where `id`= ^Ni;', $tid);
}
return $find;
}

public function getSection($id) {
	if($id !== 0){
		$find=$this->db->query('select `tid` from `type-elements` where `eid`= ^Ni;', $id);
		//echo 'tid-->'.$find;echo '<br>';
			}
	return $find;				
}
public function gettids($tid){
$return=array();
$find=$this->db->query('select `pid` from `structure` where `id`= ^Ni;', $tid);
$ret=$find->pid;
//echo $ret;
return $ret;
}

public function gettF($tid){
if($tid != 0){
		$ret=0;
		$find=$this->db->query('select `typeF` from `structure` where `id`= ^Ni;', $tid);
		if($find !== null) {
			$ret=$find;
			//echo '--'.$ret;
		}
		else {
		//echo '--'.$ret.'нет группы';
		$ret=0;
		}
		
}
return $ret;
}

public function getids($tid) {
if($tid != 0){
		$find=$this->db->query('select `id` from `type-elements` where `tid`= ^Ni;', $tid);
		if($find != null) {
		$i=0;
		if (!count($this->find)==1){		
		foreach ($find as $val){
			$return[$i] = array('id' => $val->id);
			$i++;}
				}
			}
		else 	$return[$i]=$find;		
		return $return;
			} 
		else {
			
			return null;
		}
}

public function geteids($tid) {
if($tid <> 0){
		$find=$this->db->query('select `eid` from `type-elements` where `tid`= ^Ni;', $tid);
		if($find <> null) {
		$i=0;
		//echo count($find);
		if (count($find) > 1){		
		foreach ($find as $val){
			$return[$i] = $val->eid;
			$i++;}
				}
			}
		else 	$return[$i]=$find;		
		return $return;
			} 
		else {
			
			return null;
		}
}
		
public function getnameSection($tid) {
	if($tid != 0){
		$find=$this->db->query('select `name` from `structure` where `id`= ^Ni;', $tid);
		//echo 'tid-->'.$find;echo '<br>';
			}
	return $find;				
}		

public function getidgjs($gjs){
if($gjs != 0){
		$find=$this->db->query('select `id` from `elemarch` where `codeGJS`= ^Ni;', $gjs);
		//echo 'tid-->'.$find;echo '<br>';
			}
	return $find;				
}
		
function viewfindid($id,$vend){
		$return = array();
		$k=$id;
		if (isset($vend)&&!$vend=='') {
		$this->vendor=$vend;
		$res2 = $this->db->query('SELECT `id`,`codeGJS`,`vendor`,`name`, `art`, `price`,`ms`,`ls`,`stock`,`date2` FROM `elements` WHERE `id` = ^Ni and `vendor`=^Ns;', $k, $this->vendor);			
							}
		else 				{
		$res2 = $this->db->query('SELECT `id`,`codeGJS`,`vendor`,`name`, `art`, `price`,`ms`,`ls`,`stock`,`date2` FROM `elements` WHERE `id` = ^Ni;', $k);			
							}
		if($res2 !== null) { 
		//echo 'yes1';
			if(!is_array($res2)) {
				//echo 'yes2';
				$return[] = array('art' => $res2->art,'vendor' => $res2->vendor,'name' => $res2->name,'price' => $res2->price,'stock' => $res2->stock,'id'=>$res2->id,'codeGJS' => $res2->codeGJS,'ls'=>$res2->ls,'ms'=>$res2->ms,'date2'=>$res2->date2);
					} 
			else {
			//echo 'yes3';
			foreach ($res2 as $val){
			$return[] = array('id' => $val->id,'vendor' => $val->vendor,'codeGJS' => $val->codeGJS, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms,'ls' => $val->ls, 'stock' => $val->stock, 'tid' => $this->getSection($val->id), 'date2' => $val->date2);
							}
		}
	}
return $return;	
	}

function viewertid($tid){
//if (!isset($c)) $this->c=$c;
$arr=array();
$arrr=array();
$return=array();
$name=$this->getnameSection($tid);
//echo $name;echo '<br>';
$arr=$this->getlookfortid($tid);
//$this->Showobjtype($arr[0]);

if(!$arr == null) {

$i=0;
//$this->Showobjtype($arr[$i]);
foreach ($arr as $val){
	if ($arr[$i]['typeF']==1) {
		$arrr[$i]=$this->getids($arr[$i]['id']);
		//echo count($arrr[0]);
		//$this->Showobjtype($arrr[$i]['id']);
		//echo '+';
		//echo "<br>";
		if(!$arrr[$i]== null) $i++;
		}
		//if (count($arrr[0][0]['id'])==1) $this->c=false;
		//$this->Showobjtype($arrr[0][0]);
		$i=0;
		foreach ($arrr as $val1){
			if (count($val1)>1){
			foreach($val1 as $val2){
			$return[$i]=$val2['id'];
			$return[$i]=array('id' => $val2['id']);
			$i++;
			}
			}
			else {
			$return[$i]=array('id' => $val1['id']);
			}
			}
			}
		}
		//$this->Showobjtype($return);
		if ($return==null){
		if ($name<>""){
		echo '<td class="zag2">'.$name.'</td></tr></table>';
		echo '<table class="goods"><tr class="head"></tr><tr>';
		}
		}
		else {
		//echo '<td class="zag2"></td>первый вывод</tr></table>';
		//echo '<table class="goods"><tr class="head"><td width="200">Артикул</td><td width="100">Производитель</td><td width="400">Наименование</td><td>Цена</td><td>На складе</td><td>Код товара</td><td>Доступность</td></tr><tr>';
		echo '<table class="goods"><tr class="head"><td width="200">Код для заказа</td><td width="100">Наименование</td><td>Цена,$USA</td><td>Доступность</td><td>для заказа</td><td>Дата ближайшего транзита</td></tr><tr>';	
		}
		return $return;
	}
		
	
function viewData($arr,$st)	{
$ar=array();
//if (!is_array($ar)) $this->ar=$ar;
//echo '<tr>+++'.$ar['tid'].'+++</tr>';
$i=0;
$cod=$arr['id'];
$codegjs=$arr['codeGJS'];
$stock=$arr['stock'];
$ar=array('gjs' => $arr['codeGJS'],'name' => $arr['name']."{".$arr['art']."}",'price' => $arr['price'],'ms' => $arr['ms'],'ls' => $arr['ls'],'date2' => $arr['date2']);
//$this->Showobjtype($ar);
if($st==0){
while ($elements=each($ar)){
					$b=$elements['value'];
					switch ($i){
					case 0:
					{
						echo '<td class="goods"><a href="./detail.php?eid='.$cod.'">GJS'.$b.'</a></td>';
						break;
					}
					case 1:
					{
						echo '<td><a href="./detail.php?eid='.$cod.'">'.$b.'</a></td>';
						break;
					}
					case 4:
					{
					switch ($b){
						case 1:{
						$markstatus='NEW';
						$marktext='Заказать со склада';
						break;
						}
						case 2:{
						$markstatus='REG';
						$marktext='Заказать со склада';
						break;
						}
						case 3:{
						$markstatus='EOL';
						$marktext='Заказать со склада';
						break;
						}
						case 4:{
						$markstatus='PRICE';
						$marktext='Уточнить условия поставки';
						break;
						}
						case 5:{
						$markstatus='ABS';
						$marktext='снят';
						break;
						}
					}
					echo '<td><a href="./book/show_cart.php?new='.$codegjs.'">'.$marktext.'</a></td>';
					break;
					}
					case 3:
					{
						switch ($b){
						case 1:
							{
							$logtxt="|||||";
							break;
							}
						case 2:
							{
							if ($stock < 2) $logtxt="|";
							else $logtxt="|||";
							break;
							}	
						case 3:
							{
							$logtxt="?";
							break;
							}	
						case 4:
							{
							$logtxt="?";
							break;
							}	
						}
						echo '<td><a href="./book/show_cart.php?new='.$codegjs.'">'.$logtxt.'</a></td>';
						break;
					}
					default :
					{
						if ($b<>"1900-01-01" && $b<>"1900-01-00") echo '<td>'.$b.'</td>';
						else echo '<td></td>';
						break;
					}
					}
					$i++;
							}
//if ($stock > $st) echo '<td><a href="./book/show_cart.php?new='.$codegjs.'">Заказать</a></td>';
//else echo '<td>Недоступен</td>';
					echo '</tr>';
					
				}	
			}
			
function getlookfortid($tid)	{
		$find=$this->db->query('select `id`,`name`,`typeF` from `structure` where `pid`= ^Ni;', $tid);
		//$return = array('id' => $find->id);
		$k=0;
		if (!$find == null){
			if(count($find)>1){
		foreach ($find as $val){
			if ($val->typeF==1) $return[$k]=array('id' => $val->id,'name' => $val->name,'typeF' => $val->typeF);
			else $this->gettids($tid);
			$k++;
								}
							}
				else {
				$return[$k]=array('id' => $find->id,'name' => $find->name,'typeF' => $find->typeF);
				}
				
			return $return;
			}
			else return null;
	}

public function getvendor(){
$retu=array();
$sql='select `vendor` from `elements`;';
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
else echo 'не найдено';
asort($return);
return $return;
}	

public function numrec($tab){
$a=$tab;
$d="select * from $a";
//echo count($this->db->query($d));
return  count($this->db->query($d));
}

public function numrec2($tab,$ng){
$a=$tab;
$d="select * from $a where `group`=^Ni;";
return  count($this->db->query($d,$ng));
}

public function chioce_vendor($return, $vend) {
$ret=array();
$numrecbd=ElementsW::numrec('elements');
//echo 'число записей '.$vend.'  '.$numrecbd;

$this->vendor=$vend;	
//echo '--'.$this->vendor.'--';		
if (!$this->vendor==''){
	$l=0;
	for ($i=0;$i<=$numrecbd;$i++){
			if ($return[$i]['vendor'] == $this->vendor) {
			$ret[$l]['id'] = $return[$i]['id'];
			$l++;
														}
							}
						}
else return $return;
$return=$ret;
return $return;
}

public function viewer1($return,$sort=0,$vend) {
$arr = array();
$return1 = array();
$return2 = array();
$ret['tid']=Array();
$ret['id']=Array();
$ret['num']=Array();
for($i=0;$i<=count($return);$i++){
	$arr=$return[$i];
	$k=$arr['id'];
	
	$res2 = $this->db->query('SELECT `id`,`vendor`,`codeGJS`,`name`, `art`, `price`,`ms`,`ls`,`stock` FROM `elements` WHERE `id` = ^Ni;', $k);
	
	if($res2 !== null) {
				if(!is_array($res2)) {
					$return1[$i] = array('tid' => $this->getSection($res2->id),'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					$return2[$i] = array('tid' => $this->getSection($res2->id),'art' => $res2->art,'name' => $res2->name,'price' => $res2->price,'stock' => $res2->stock, 'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					
					if ($sort==0) $this->viewData($return2[$i],0);
					else {
						$ret['tid'][$i]=$return1[$i]['tid'];
						$ret['id'][$i]=$return2[$i]['id'];
						}
					} 
			else {
			foreach ($res2 as $val){
			$return2[] = array('id' => $val->id,'codeGJS' => $val->codeGJS, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms,'ls' => $val->ls, 'stock' => $val->stock, 'tid' => $this->getSection($val->id));
						
						}
		}
	}
}
$this->Showobjtype($ret['id']);
$array=array();
$l=count($ret['id']);
for ($j=0;$j<$l;$j++) $array[$ret['id'][$j]]=$ret['tid'][$j];
$array[$ret['id'][$l]]=100000;
					asort($array);
					//$this->Showobjtype($array);
					asort($ret['tid']);
					//$this->Shownametype($ret['tid']);
					$ac=array_count_values($ret['tid']);
					//$this->Shownametype($ac);
					$ar=array();
					$k=0;
					$z='| ';
					set_time_limit(2500);
					$i=1;
					while ($el=each($ac)) {
					//$axe[$el['key']]=$this->getSection($el['key']);
					//echo $el['key'].'--'.$el['key'];echo '<br>';
					$z.='<a href="#'.$el['key'].'">'.$this->getnameSection($el['key']).'</a>';
					$zz=$this->getnameSection($el['key']);
					$z.=' | ';
					echo '<tr class="head"><td colspan="7"><div><a name="'.$el['key'].'"><b>'.$zz.'</b></div></td></tr>';
					//$this->Showobjtype($array);
					$l=2;
						while ($el1=each($array)){
							$t=$l%2;
							$b=$k+$el['value'];
							//echo $b;echo '<br>';
							//echo $i.'-'.$b;echo '<br>';
							if($i<=$b){
								$ar=$this->viewfindid($el1['key'],$vend);
								//$this->Showobjtype($ar[0]);
								//$this->Showobjtype($ar[0]);
								echo '<tr class="a'.$t.'">';
								$this->viewData($ar[0],0);
								$l++;
								$i++;
											}
								else {
								$el1=prev($array);
								break;}
}
							echo '</div>';		
			
							$k=$k+$el['value'];
											}
	if (count($ac)>1)	echo '<tr>'.$z.'</tr></table>';							
	set_time_limit(600);
	return $ret;
		}

public function choose_tabl_elem($tab){
$a=array();
switch ($tab){
		case 'e' :
		{
		$a['tabl_elem'] = 'elements';
		$a['cat_elem']  ='Каталог (склад-транзит)';
		break;
		} 
		case 'a' :
		{
		$a['tabl_elem'] = 'elemarch';
		$a['cat_elem']  ='Каталог (все товары)';
		break;
		}
		case 'c' :
		{
		$a['tabl_elem']= 'elemcat';
		$a['cat_elem'] ='Каталоги производителей';
		break;
		}
		case 's' :
		{
		$a['tabl_elem']= 'elemspec';
		$a['cat_elem'] ='Каталог спецпредложений';
		break;
		}
		default :
		{
		$a['tabl_elem'] = 'elements';
		$a['cat_elem'] ='Каталог (склад-транзит)';
		break;
		}
}
return $a;
}

public function viewspicsel($dim) {
echo '<table width="100%"><tr>';
if (!$dim === null) {
	$kk=3;
	$k=0;
	for ($i=0;$i<count($dim);$i++){
	$this->Showobjtype($dim[$i]).'<br>';
	$desc=explode('|',$dim[$i]['desc']);
	$bbb=array('0'=>'./detail.php?eid='.$dim[$i]['eid'],'1'=>$desc[3],'2'=>'<a href="http://shop.deltar.ru/book/show_cart.php?new='.$dim[$i]['GJS'].'">Заказать код GJS'.$dim[$i]["GJS"].'</a><br>','3'=>$dim[$i]['name'].'<br>'.$dim[$i]['price'],'4'=>' $USA');
	Page::scalimag2('./images/pics/'.$dim[$i]['pics'], $bbb,1,'block2');
	$k++;
		if ($k == $kk) {
		$k=0;
		echo "</tr><tr>";
		}
}

}
echo '</table>';
}

public function istabl($tab,$fil,$nr) {

	if($tab !== ''){
	
		$find=$this->db->query('select * from `'.$tab.'` where `'.$fil.'`= ^Ni;', $nr);
		if ($find) 		return $find;
						else return false;
			}
	return false;		
	}	

public function edit_tabl($tab,$fil,$nrec){

$tablica=$this->istabl($tab,$fil,$nrec);

if ($tablica) {
	
	$i=0;
	while ($element = each($tablica))  {
		$tbl[$i]=$element['value'];
		$i++;
   }
   $names_fields=$this->edit_tabl($tab,$fil,2);
	foreach($names_fields as $v) {
	$names_vrs[$j]= 'varib'.$j;
	$names_filds[$j]=explode('/',$v);
	$j++;
	}	 

if (!isset($registr)) $registr=true;
	if ($registr) {
	echo '<div class="ank">';		  
	echo '<form style="align:left; " method="post" action="./regurl.php?uid='.$uid.'" >';
	echo '<span class="razdel">Внесите данные юридического лица <br><br></span>';
	$names_vlue=$tbl;
	$i=0;
	echo '<table>';
	foreach($names_vlue as $val){
		echo '<tr>';
		if ($names_filds[$i][1]<>0)	Page::edit_field($names_filds[$i][0],$names_vrs[$i],'',$names_filds[$i][2],80,'text');
		$i++;
		echo '</tr>';
		}
		echo '</table>';
		echo '<span><input value="Отправить" size="10" type="submit" /><input value="Очистить все поля" size="30" type="reset" /><sup>4</sup><br><br></span>';
	echo '</form>';
	echo '</div></td><td><div class="zag">Наши комментарии</div><div class="block2">';
	echo '<span><sup>1</sup>  Наименование организации просьба написать полностью в соотвествии с учредительными документами, так как оно должно быть в счетах-фактуры, например ООО "ПРОГ", абревиатуры, отличные от ООО, ОАО, ЗАО просьба расшифровывать</span><br>';
	echo '<span><sup>2</sup>  В этих полях просьба указывать данные сотрудника вышеуказанной организации, к которому следует обращаться для передачи информации по заказам, оплате  счетов и отгрузки товаров. Указывайте любой сотовый или стационарный телефон наиболее удобный для связи </span><br>';
	echo '<span><sup>3</sup>  В этих полях просьба указывать через запятую номера стационарных телефонов, являющихся офицальными контактными телефонами вышеуказанной организации в следующем формате (код города)номер телефона</span><br>';
	echo '<span><sup>4</sup>  Выделенные жирным поля являются обязательными для регистрации</span><br>';
	echo '<span><sup>5</sup>  Если фактический адрес совпадает юридическим поле не заполняется</span><br>';
	echo '</div></td></tr>';
		
	}
}
}
}
?>