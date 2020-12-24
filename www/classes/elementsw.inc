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
	private $fields;
	private $field1;
	private $field2;
	
	protected function __construct() {
		$this->db = Singleton::getInstanceinit('DB',1);
		//echo 'construct EW OK';
	}
 public function Showelement($p) {
  echo '<br/>';
  while ($element = each($p))
  {
  $elem=$this->getElement($element['key']);
  echo "ключ ".$element['key'].'---'.$elem['vendor'];
  echo '-';
  echo "значение ".$element['value'].'---'.$this->getnameSection($element['value']);
  echo '<br/>'; 
  }
 }
 
  public function Showobjtype($p) {
  while ($element = each($p)){
  if($element['value']){
	echo '['.$element['key'].']';
	echo '-';
	if(is_array($element['value'])) print_r($element['value']);
	else  echo $element['value'];
	echo '<br/>';
  }
 }
}
public function Showobjtab($p,$n,$m,$mode=0) {
$shobj='';
  while ($element = each($p)){
  if($element["value"] && $element["value"]<>''){
	if ($element['key']<>'') echo '<tr><td colspan='.$n.'>'.$element["key"].'</td>';
	if(is_array($element["value"]) && $element["value"]<>'') {
		if($mode==0)	{
			echo '<td colspan='.$m.'>';
			print_r($element['value']);
			echo '</td></tr>';
		}
		elseif(is_object($element['value'])) $shobj.='<td colspan='.$m.'>'.$this->Showobjtab($element['value'],$n,$m,1).'</td></tr>';
		}
	elseif($element['value']<>'')  {
		if($mode==0){
		echo '<td colspan='.$m.'>'.$element["value"];
		echo '</td></tr>';
		}
		else $shobj.='<td colspan='.$m.'>'.$element["value"].'</td></tr>';
	}
  }
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
  	function getscountab($tab,$key,$mode){
		$db = Singleton::getInstance('DB');
		$order = ' ORDER BY ';
		$order .= '`numpage`';
		$order .= ' DESC ';
		if ($key <>''&& $mode =='f') {
			$d="SELECT `$key` FROM `$tab` ORDER BY $key DESC";
			$res=$this->db->query($d);	
		}
		elseif($mode == 't' && strstr($tab,'pages'))  {
			$d="SELECT `$key` FROM `$tab` WHERE `$key`=^Ns $order;";
			$res=$this->db->query($d,$_SERVER['HTTP_HOST']);
			$key='numpage';
		}
		elseif($mode == 't' && strstr($tab,'map'))  {
			$site=$this->initbd($_SERVER['HTTP_HOST'],$db);
			$d="SELECT `$key` FROM `$tab` WHERE `domen`=^Ns;";
			$res=$this->db->query($d,$site->domen);
			}	
		else {
			$d="SELECT * FROM `$tab` ";
			$mode='c';
			$res=$this->db->query($d);
		}
$l=0;
//var_dump($res);
if($res){
	if (is_array($res)) {
		if(count($res) >1) 	foreach($res as $l=>$val)$result[$l]=$val;
	}
	else {
		$result[0] = new ArrayObject;
		$result[0]->key=$res;
	}

if($mode <> '' && $key<>'' && isset($result[0]->$key)) return $result[0]->$key; 
elseif(is_array($res)) return count($res);
else return $res;			
}			
else return 0;
}
	private function addSection($id,$pid, $name,$tabl,$typeF=1) {
		$Page= new Page($id,$tabl);
		$name=$Page->getnamepage($Page);
		//$name='page'.$id;
		$table=$tabl['mapsites'];
		$res=$this->db->query('INSERT INTO `'.$table.'` (`id`,`name`, `pid`,`typeF`) VALUES (^Ni,^Ns,^Ni,^Ni);',$id, $name, $pid,1);
		return $res;//$this->db->id();	
	}
	
	private function checkid($id,$tabl,$str_type) {
		$table=$tabl[$str_type];
		if($id != 0 && $res=$this->db->query('SELECT `id` FROM `'.$table.'` WHERE `id` = ^Ni;', $id) === null)	return false;
		else return true;
			//throw new StructureWException('id does\'t exist', StructureWException::ID_ERROR);		
	}
	
	private function checkpid($pid,$tabl,$str_type) {
		$table=$tabl[$str_type];
		if($this->db->query('SELECT `id` FROM `'.$table.'` WHERE `id` = ^Ni;', $pid) === null)return false;
		else return true;
			//throw new StructureWException('pid doesn\'t exist', StructureWException::PID_ERROR);
	}
	
	function prepare_table($a,$s,$mode) {
		$this->name=$a;
		$this->site=$s;
	if ($mode == 10001){
		$this->db->query('TRUNCATE TABLE `'.$this->name.'`;');
		}
	else {
		$this->db->query('DELETE FROM `'.$this->name.'` WHERE `'.$this->site.'` = ^Ns;', $Site->domen);
		//Utils::prepare_pages($Site->domen,getscountab('pages','numpage', 'c'));
	}
		echo 'prepare OK';echo "<BR>";
		}
	public function getallfieldtable($tab){	
	//просмотр классов и методов
	//$conn=mysqli_connect("mysql.baze.deltar.ru:63917","gjs_deltar_ru","ittBudB5");
	$result = $this->db->query("SHOW COLUMNS FROM $tab");
	if (!$result) {
		echo 'Ошибка при выполнении запроса: ' . mysql_error();
		exit;
	}
	print_r(get_class_methods($result));
	/*if ($result->field_count > 0) {
		while ($row = $result->fetch_assoc) {
			print_r($row);
    }*/
}

	public function view_table($a,$b='',$c='',$d='',$e=''){
		if ($a<>'' && $b=='')$g=$this->db->query("select * from `$a`");
		elseif($d<>'' && $e<>'')$g=$this->db->query("select * from `$a` where `$b` = '$c' AND `$d`=$e;");
		else $g=$this->db->query("select * from `$a` where `$b` = '$c';");
	return $g;
	}
	
	public function get_fields_tab($tab){
		if ($tab<>''){
			$g=$this->db->query("select * from $tab");
			if (mysql_num_fields($g)>0){
			for($i=0;$i<=mysql_num_fields($g);$i++)
			 $res[$i]= mysql_field_name($g,$i);
			}
			return $res;
		}
		else return false;
	}
	
	public function getAll($tab){
		$db = Singleton::getInstance('DB');
		$res =$db->query('SELECT * from `'.$tab.'`');
		if($res) return $res;
		else return false;
	}
	public function getById($tab,$id){
			$res = $this->db->query('SELECT * FROM `'.$tab.'` WHERE `id`=^Ni',$id);
			if($res) return $res;
			else return false;
	}

	public function createFullCategory($tab, $arr, $field='id',$close_field=0){
		$ids = 1;
		$numpage = 1;
		$nummaket = 1;
		$uid = 1;
		$numpost=0;
		$fld = $this->getallfieldtable($tab);
		$fields = $fld['field'];
		while(isset($fields[$numpost]) && $fields[$numpost]<>$field){
			$numpost++;
		}
		$y='';
		$NN=count($fields)-$close_field;
		if($close_field == 0 )$NB=0;
		else $NB = 1;
		for ($i=$NB;$i<$NN;$i++){
			if( $i<$NN-1)$y.="'". $arr[$i]."',";
			elseif($close_field == 0) $y.="'". $arr[$i]."'";
			else $y.="'". $arr[$i]."',";
		}
		//echo $y;
		if($close_field == 4 && $table=='allmakets') $z="INSERT INTO $table VALUES ($arr[0],".$y."$Site->ids,$arr[10],$idmaket,$numpage);";
		elseif($close_field == 4) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids,$numpage,$idmaket,$uid);";
		elseif($close_field == 3) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids,$numaket,$numpage);";
		elseif($close_field == 2) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids,$numpage);";
		elseif($close_field == 1) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids);";
		elseif($close_field == 0) $z="INSERT INTO $tab VALUES (".$y.");";
		$sql=$this->db->query($z);
	}

	function getallfonts($F,$default=''){
		if (!$F || $F<1)return false;
		else {
			$res = $this->db->query('SELECT * FROM  `fonts` WHERE `id` = ^Ni;', $F);
			if($res){
				if($res->style=='')$res->style=$default;
				if($res->variant=='')$res->variant=$default;
				if($res->weight=='')$res->weight=$default;
				if($res->family=='')$res->family=',sans-serif';
				else $res->family=','.$res->family;
				if($res->size=='')$res->size='small';
				if($res->lh==0)$res->lh=$default;
				else $res->size.='/'.$res->lh;
				if($res->faces=='')$res->faces='';
				else $res->faces.='';
			}	
			$retF='font:';
			if($res != null) {
				$arrr=array($res->size,$res->family,$res->style,$res->weight,$res->variant);
				foreach($arrr as $val) if ($val)$retF.=$val.' ';
				if($res->stretch)$retFS='font-stretch:'.$res->stretch.';';
				if ($retFS)$return=$retF.=';'.$retFS;
				elseif($retF) $return=$retF.';';
				else $return='';
				return $return;
		} 
		else {
			return false;
			}
		}
	} 
	
	function get_book_details($isbn,$tab,$img=false)
{
  // Выполняет запрос в базу данных детальной информации о книге
  if (!$isbn || $isbn=='')
     return false;
$res = $this->db->query('SELECT `id`,`name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM '.$tab.' WHERE `codeGJS` = ^Ni;', $isbn);
		if($res != null) {
			return array('id' => $res->id,'title' => $res->name, 'art' => $res->art, 'author' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'isbn' => $res->codeGJS);
		if($img) $res->pic=$this->gjspics($isbn);	
		} else {
			return false;
			}
}

function calculate_price($cart,$tab)
{
  // Вычисляет общую стоимость всех элементов тележки
  $price = 0.0;
  if(is_array($cart))
  {
    //$conn = db_connect();
	$s=1;
	
    foreach($cart as $isbn => $qty)
    {  
      //$query = "select price from elements as books where codeGJS='$isbn'";
	  $query = 'SELECT `price` FROM '.$tab.' WHERE `codeGJS` = ^Ni;';
      $result = $this->db->query($query, $isbn);
      if ($result)
      {
		//print_r($result);
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


function get_details_id($id,$tab)
{
  // Выполняет запрос в базу данных детальной информации о книге
  if (!$isbn || $isbn=='')
     return false;
$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM '.$tab.' WHERE `id` = ^Ni;', $id);
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

	function addElemap($codeGJS, $name, $desc, $keywords, $titles, $price, $tid) {
		$this->db->query('INSERT INTO `elemap` (`codeGJS`, `name`, `desc`, `art`, `vendor`, `price`) VALUES (^Ns, ^Ns, ^Ns, ^Ns, ^Ns, ^Ni);', $codeGJS, $name, $desc, $keywords, $titles, $price);	
		$id = $this->db->id();	
		//$tids = explode(';', $tid);
		$this->db->query('INSERT INTO `type-elements` (`tid`, `eid`) VALUES (^Ni, ^Ni);', $tid, $id);
		
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
	
	private function readyshowpage($np){
		
}
	
	private function getfieldstable($table){
		$result = $this->db->query("SHOW COLUMNS FROM `$table`");
		//print_r(get_class_methods('mysqli_result'));
		//print_r($result);
		if ($result) {
			foreach($result as $val) {
				$arrfields['field'][]=$val->Field;
				if (strstr($val->Type,'int')) $arrfields['int'][]= '^Ni';
				else $arrfields['int'][]= '^Ns';
				$cond=strstr($val->Type,'(');
				$cond0=strrpos($val->Type,')')-strrpos($val->Type,'(');
				if($cond && $val->Type <> 'text') $val->Type=substr($cond,1,$cond0-1);
				$arrfields['type'][]=$val->Type;
			}
			return $arrfields;
		}
		else exit('Такой таблице нет');	
	}
	
	private function readystrfield($fields,$nb=0,$ne=0){
	$y='';
	if (is_array($fields)) {
	$NN=count($fields);
		for ($i=$nb;$i<$NN-$ne;$i++){
			if ($fields[$i]<>''){
			if ($i<$NN-1-$ne) $y.="`". $fields[$i]."`,";
			else $y.="`". $fields[$i]."`";
			}
		} 
	
}
return $y;	
}

	private function readystrval($val,$nb=0,$ne=0){
	$y='';
	
	if (is_array($val)) {
	$NN=count($val);
	//echo $nb.'----'.$NN.'----'.$ne;
		for ($i=$nb;$i<$NN-$ne;$i++){
			if (isset($val[$i])){
			if ($i<$NN-1-$ne) {
				if(is_int($val[$i])) $y.= $val[$i].",";
				else $y.="'". $val[$i]."',";
			}
			else {
				if (is_int($val[$i])) $y.= $val[$i];
				else $y.="'". $val[$i]."'";
			}
			}
		} 
	
}
return $y;	
}

	function GeneraladdElement($tabl,$valelem,$tid,$nb=0,$ne=0,$opt='', $const='', $constopt='') {//($codeGJS, $name, $desc, $art, $vendor, $price, $tid, $opt, $const, $constopt)
	$table=$tabl['elemap'];
	$tabstrt=$tabl['mapsites'];
		$this->fields=$this->getfieldstable($table);
		$this->yy=$this->readystrfield($this->fields['field'],$nb,$ne);
		$this->x=$this->readystrfield($this->fields['int'],$nb,$ne);
		$this->z=$this->readystrval($valelem,$nb,$ne);
		$res=$this->db->query('INSERT INTO `'.$table.'` ('.$this->yy.') VALUES ('.$this->z.');',$this->z);	
		if($res)$result=true;
		else {$result=false;}
		$ide = $this->db->id();
		$id=$this->getscountab('type-'.$table,'','c');
		$tids = explode(';', $tid);
		$id++;
		$tid=$this->getscountab('type-'.$table,'tid','f')+1;
		//show::pauza($id);
		foreach($tids as $val) {
			if($val<>''){
				$res=$this->db->query('INSERT INTO `type-'.$table.'` (`id`,`tid`, `eid`) VALUES (^Ni,^Ni, ^Ni);',$id, $tid, $val);
				$id++;
				//if(!$this->checkid($val,$tabl,'mapsites'))$res=$this->addSection($val,$ide,$valelem[2],$tabl);
				if($res && $result)$result=true;
				else {$result=false;break;}
			}
		}
		//Utils::generalcalcNumEl( 'mapsites','type-elemap');
		if(!empty($opt) && $opt != ' ') {
			$opts = explode(',', $opt);	
			$this->opt[$id] = $opts; 
		}
		
		if(!empty($const) && $const != ' ') {
			$consts = explode(',', $const);		
			$this->const[$id] = $consts; 
		}
		//print_r($this->const);
		if(!empty($constopt) && $constopt != ' ') {
			$constopts = explode(',', $constopt);		
			$this->constopt[$id] = $constopts; 
		}
		//print_r($this->constopt);
		
	return $result;
	}
	
	function GeneralAdd($table,$field1,$field2,$str_tab,$idf=0){
		if ($idf<>0) $res = $this->db->query('SELECT `'.$field1.'`, `'.$field2.'` FROM `'.$table.'` WHERE `'.$field1.'`='.$idf.';');
		else $res = $this->db->query('SELECT '.$field1.', '.$field2.' FROM '.$table.';');
		//print_r($res[0]);
		if($res !== null) {
			if(!is_array($res)) {
				$this->$field2[$res->$field2] = $res->$field1;			
			} else {
				foreach($res as $val)
					$this->$field2[$val->$field2] = $val->$field1;		
			}
		}
		
		foreach($this->opt as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `'.$table.'-'.$table.'` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'0\');', $id, $this->$field2[$v]);
			}		
		}
		
		foreach($this->const as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `'.$table.'-'.$table.'` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'1\');', $id, $this->$field2[$v]);
			}		
		}
		foreach($this->constopt as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `'.$table.'-'.$table.'` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'2\');', $id, $this->$field2[$v]);
			}		
		}
		Utils::generalcalcNumEl($str_tab);
	}
	
	function finishAdd() {
		$res = $this->db->query('SELECT `id`, `codeGJS` FROM `elemarch`;');
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
				$this->db->query('INSERT INTO `elemarch-elemarch` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'0\');', $id, $this->codeGJS[$v]);
			}		
		}
		foreach($this->const as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `elemarch-elemarch` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'1\');', $id, $this->codeGJS[$v]);
			}		
		}
		foreach($this->constopt as $id => $val) {
			foreach($val as $v) {
				$this->db->query('INSERT INTO `elemarch-elemarch` (`eid1`, `eid2`, `f`) VALUES (^Ni, ^Ni, \'2\');', $id, $this->codeGJS[$v]);
			}		
		}
		Utils::calcNumEl();
	}
	
	public function addseansuser($uid,$stat=0){
		$find=$this->db->query('select `id`,`ciid` from `users` where `id`= ^Ni;', $uid);
		if (isset($find->ciid) && $stat>0) $statnew= $find->ciid +1;
		$this->db->query('UPDATE `users` SET `ciid` = ^Ni WHERE `id` = ^Ni;', $statnew, $uid);

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
		if($tab=='elements')$tpelm=$tab;
		else $tpelm='pages';
		$return = array();
		if($tpelm=='elements'){
			$res = $this->db->query('SELECT t1.id, `name`, `art`, `price`, `stock`,`ms`,`ls`, `codeGJS`, `desc`, `vendor`,`date2` FROM `'.$tab.'` as t1, `type-'.$tpelm.'` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
		if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price, 'ms' => $res->ms, 'codeGJS' => $res->codeGJS,'vendor' => $res->vendor,'desc' => $res->desc, 'stock' => $res->stock, 'ls' => $res->ls, 'date2' => $res->date2);		
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms, 'codeGJS' => $val->codeGJS,'vendor' => $val->vendor ,'desc' => $val->desc,'stock' => $val->stock, 'ls' => $val->ls, 'date2' => $val->date2);
				}
			}
		}
		}
		else {
			$res = $this->db->query('SELECT t1.id, `name`, `keywords`, `price`, `links`,`ms`,`ls`, `codeGJS`, `desc`, `titles`,`idm` FROM `'.$tab.'` as t1, `type-'.$tpelm.'` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
			if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->keywords, 'price' => $res->price, 'ms' => $res->ms, 'codeGJS' => $res->codeGJS,'vendor' => $res->titles,'desc' => $res->desc, 'stock' => $res->links, 'ls' => $res->ls, 'date2' => $res->idm);		
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->keywords, 'price' => $val->price, 'ms' => $val->ms, 'codeGJS' => $val->codeGJS,'vendor' => $val->titles, 'desc' => $val->desc,'stock' => $val->links, 'ls' => $val->ls, 'date2' => $val->idm);
				}
			}
		}	
		}
		//print_r($return);
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
	
	function getElement($id) {
		$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `elements` WHERE `id` = ^Ni;', $id);
		if($res != null) {
			return array('name' => $res->name, 'stock' => $res->stock, 'art' => $res->art, 'vendor' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'codeGJS' => $res->codeGJS,'desc' => $res->desc,'date1' => $res->date1,'date2' => $res->date2);
		} else {
			return null;
		}
	}
	
	function getElements($field,$value){
		switch($field){
			case 'ms':{

				break;
			}
			case 'ls':{
				$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `elements` WHERE `ls` = ^Ni;', $value);
				if($res != null) {
					return array('name' => $res->name, 'stock' => $res->stock, 'art' => $res->art, 'vendor' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'codeGJS' => $res->codeGJS,'desc' => $res->desc,'date1' => $res->date1,'date2' => $res->date2);
				} else {
					return null;
				}
				break;
			}
			case 'stock':{
				$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `elements` WHERE `stock` > ^Nl;', $value);
				if($res != null) {
					return array('name' => $res->name, 'stock' => $res->stock, 'art' => $res->art, 'vendor' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'codeGJS' => $res->codeGJS,'desc' => $res->desc,'date1' => $res->date1,'date2' => $res->date2);
				} else {
					return null;
				}
				break;
			}
			case 'price':{
				$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `elements` WHERE `price` > ^Nl;', $value);
				if($res != null) {
					return array('name' => $res->name, 'stock' => $res->stock, 'art' => $res->art, 'vendor' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'codeGJS' => $res->codeGJS,'desc' => $res->desc,'date1' => $res->date1,'date2' => $res->date2);
				} else {
					return null;
				}
				break;
			}
		}
		$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `elements` WHERE `ms` = ^Ni;', $value);
		if($res != null) {
			if(is_array($res)){
				foreach($res as $val){
					$return[] =  array('name' => $val->name, 'stock' => $val->stock, 'art' => $val->art, 'vendor' => $val->vendor,'price' => $val->price,'ls' => $val->ls,'ms' => $val->ms,'codeGJS' => $val->codeGJS,'desc' => $val->desc,'date1' => $val->date1,'date2' => $val->date2);
				}
				return $return;
			}
			else return array('name' => $res->name, 'stock' => $res->stock, 'art' => $res->art, 'vendor' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'codeGJS' => $res->codeGJS,'desc' => $res->desc,'date1' => $res->date1,'date2' => $res->date2);
		} else {
			return null;
		}
	}

	function getElementGJS($cgjs) {
		$res = $this->db->query('SELECT `name`, `stock`, `art`,`vendor`, `price`, `ls`,`ms`,`codeGJS`,`desc`,`date1`,`date2` FROM `elements` WHERE `codeGJS` = ^Ni;', $cgjs);
		if($res != null) {
			return array('name' => $res->name, 'stock' => $res->stock, 'art' => $res->art, 'vendor' => $res->vendor,'price' => $res->price,'ls' => $res->ls,'ms' => $res->ms,'codeGJS' => $res->codeGJS,'desc' => $res->desc,'date1' => $res->date1,'date2' => $res->date2);
		} else {
			return null;
		}
	}
	
	function getIdElement($table,$id,$field,$val) {//числовой идентификатор id по текстовому полю field и значению val
		$res = $this->db->query('SELECT `'.$id.'` FROM `'.$table.'` WHERE `'.$field.'` = ^Ns;', $val);
		//show::infosh($res);
		if(isset($res)) {
			
			return $res;
		} else {
			return false;
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
	public function showgood2($el) {
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
				echo '<div class="head" >'.$arr1[1].' '.$el['art'].'<br><b>'.$el['name'].'</b><a id="close" href="#" onclick="self.close();">X</a></div>
				<table>
					<tr class="s0">
						<td class="c1">Производитель</td>
						<td class="c2">'.$el['vendor'].'</td></tr>
						<tr class="s1">
						<td class="c1">Инвентарный номер</td>
						<td class="c2">'.$el['price'].'</td></tr>';
					if ($arr1[3] !=='') {
						echo '<tr class="s1"><td class="c1">Корпоративная почта:</td>
						<td class="c2">'.$arr1[3].'</td></tr>';
						}
					echo '<tr class="s2">
						<td class="c1">Стоимость:</td>
						<td class="c2">'.$el["price"].' $USA</td>
					</tr>
					<tr class="s3">
						<td class="c1">Срок службы</td>';
					
					echo $el['stock'];
					echo '</tr>';
				echo '<tr class="s4">
						<td class="c1">Пароль </td>';
						echo $arr1[4];
					echo '</tr>';
					
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
	elseif ($arr1[2] !== '') echo '<div style="width: 300px; border: solid 1px #808080; position: relative; top:'.$www.'px; left: 800px;"><img  src="./images/pics/'.$arr1[2].'.jpg" alt="" style="width: 300px;" /></div>';
	}
	$ok = 1;
return $ok;			
}
	
public function showgood3($el) {
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
						<td class="c1">Инвентарный номер</td>
						<td class="c2">'.$el['price'].'</td></tr>';
					if ($arr1[3] !=='') {
						echo '<tr class="s1"><td class="c1">Корпоративная почта:</td>
						<td class="c2">'.$arr1[3].'</td></tr>';
						}
					echo '<tr class="s2">
						<td class="c1">Стоимость:</td>
						<td class="c2">'.$el["price"].' $USA</td>
					</tr>
					<tr class="s3">
						<td class="c1">Срок службы</td>';
					
					echo $el['stock'];
					echo '</tr>';
				echo '<tr class="s4">
						<td class="c1">Пароль </td>';
						echo $arr1[4];
					echo '</tr>';
					
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

	
	public function showgood($el,$Pth) {
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
				
				// вывод таблицы парметров
				//$arr1[1]-руское название товара
				
				Maket::divclass('head-good',$Pth,'','','nav');
				echo '<div><span class="head-good">'.$arr1[1].' '.$el['art'].' - <b>'.$el['name'].'</b></span><span><a id="close" href="#"  onclick="self.close();">X</a></span></div>';
				echo '<div>
					<ul class="good-s0">
						<li class="good-c1">Производитель
						<span class="good-c2">'.$el['vendor'].'</span></li></ul>
						<ul class="good-s1">
						<li class="good-c1">Код для заказа
						<span class="good-c2">'.$el['codeGJS'].'</span></li></ul>';
					if ($arr1[3] !=='') {
						echo '<ul class="good-s1">Позиционирование:
						<span class="good-c2">'.$arr1[3].'</span</li></ul>';
						}
					echo '<ul class="good-s2">
						<li class="good-c1">Стоимость:
						<span class="good-c2">'.$el["price"].' $USA<span></li>
					</ul>
					<ul class="good-s3">
						<li class="good-c1">Доступность для заказа</li>';
			if ($el['stock']>5) { 
					echo '<span class="c2"><a href="./book/show_cart.php?new='.$el['codeGJS'].'"> Товар на складе</a></span></li>';
					}
			else  {				
					if ($el['stock']<6 && $el['stock']>0) echo '<li class="good-c2">Товар на складе заканчивается</li>';
					else {
						if ($el['date2']>date('U')) echo '<li class="good-c2">Товар в транзите</li>';
						else echo '<li class="good-c2">Уточните состояние лигистики</li></ul>';
					}
					}
					if ($el['date2'] == ''  || $el['date2'] == '0000-00-00' || $el['date2'] == '1900-01-00') {
					echo '<ul class="good-s4">
						<li class="good-c1">Ближайшие транзиты (год,мес.,ден.):</li>
						<li class="good-c2">'.$el['date2'].'</li></ul>';
						}
					//	$arr1[4]-ссылка на сайт производителя
					if ($arr1[4] !== '') echo '<ul class="good-s5">
						<li class="good-c1">Ссылка на сайт производителя</li>
						<li class="good-c2"><a target="blanc" href="'.$arr1[4].'">'.$el['art'].'</li></ul>';	
					//	$arr1[5]-срок гарантии производителя
					if ($arr1[5] !== '') echo '<ul class="good-s5">
						<li class="good-c1">Гарантия производителя в месяцах</li>
						<good- class="good-c2">'.$arr1[5].'</li></ul>';	
					if ($arr1[6] !== '') echo '<ul class="good-s5">
						<li class="good-c1">Размеры в см (ДхШхВ); Объем в л.; Вес в кг.</li>
						<li class="good-c2">'.$arr1[6].'</li></ul>';
				echo '</div></nav>';
				if ($arr[0] > 0){
					Maket::divclass('head-good',$Pth,'',' flex','nav');
					echo '<div class="head-character"><b>Характеристики товара</b>';	
				
				$l=1;
				for ($i=1;$i<count($arr2);$i++){
					if ($arr[$i] !== '' && $arr[$i] !== ' ') {
					$l=$l+1;
					echo '<ul class="good-s1">
						<li class="good-c1">'.$arr2[$i-1].'</li>';
					if ($arr[$i] == "Y") $a="Да";
					else {
						if ($arr[$i] == "N") $a="Нет";
						else $a=$arr[$i];
						}
						echo '<li class="c2">'.$a.'</li></ul>';
					}
				}
				echo '</div></nav>';
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
$res=$this->db->query('SELECT `gjs`, `code` FROM `pics` WHERE `gjs` = ^Ni;', $gjs);
if (!$res === false) $codepic=$res->code;
else $codepic=null;
return $codepic.'.jpg';
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
	//echo '<td></td></tr><tr><td>';
	$resfind='По запросу:'.$for.' '.$vend.' '.$nn.' совпадений';
	echo '<div class="button">'.$resfind.'</div>';
	//echo '<table class="goods"><tr class="head"><td width="200">Артикул</td><td width="100">Производитель</td><td width="400">Наименование</td><td>Цена</td><td>На складе</td><td>Код товара</td><td>Доступность</td></tr><tr>';
	//echo '<table class="goods"><tr class="head"><td width="200">Артикул</td><td width="100">Производитель</td><td width="400">Наименование</td><td>Цена</td><td>Доступность</td><td>для заказа</td><td>Транзит</td></tr><tr>';			}
	echo '<table class="goods"><tr class="head"><td width="200">Код для заказа</td><td width="100">Наименование</td><td>Цена,$USA </td><td>Доступность</td><td>для заказа</td><td>Дата ближайшего транзита</td></tr><tr>';			
	}
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
					$z.='<a href="#'.$el['key'].'">'.$this->getnameSection($el['key'],$vend).'</a>';
					$zz=$this->getnameSection($el['key'],$vend);
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
		
public function initbd($domen){
	if (isset($domen)) $this->domen=$domen;
	if ($this->domen <> "") {
	$res=$this->db->query('SELECT `ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`images`,`pages`, `news`,`element` FROM `allsites` WHERE `domen` = ^Ns;', $this->domen);		
	}
	else exit('Сайт в базе данных не найден');
	return $res;
	}
public function regbd($domen)	{
	if (isset($domen)) $this->domen=$domen;
	$res=$this->db->query('SELECT `ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`images`,`pages`, `news`,`element` FROM `allsites` WHERE `domen` = ^Ns;', $this->domen);		
	if (!$res) {
		$res=$this->db->query('INSERT INTO `allsites` (`domen`) VALUES (^Ns);',$domen);
	}
}

		
public function getlookforfields($for1,$for2,$for3,$table) {
$res = array();
$res=$this->db->query('SELECT `numpage`,`title`,`site` FROM `'.$table.'`  WHERE `site` = ^Ns and `title` = ^Ns and `idauthor`=^Ni;', $for1, $for2,$for3);
if (isset($res->numpage))return $res->numpage;
else return false;
}
		
public function getlookfortab($for,$vend,$tab) {
$k=0;
//создаем sql-запрос  записи с номером =k таблицы `elements` и удовлетврояющей условию на поле vendor=vend
//echo 'vendor -'.$vend.'-';
if ($vend=='') $res=$this->db->query('SELECT `id`,`name`,`art`, `vendor` FROM '.$tab.';');
else $res=$this->db->query('SELECT `id`,`name`,`art`, `vendor` FROM `'.$tab.'` where `vendor`=^Ns;',$vend);
//если запись существует, ищем в полях name art подстроку for
	if (!$res == false){
	//echo 'resultat +';echo '<br>';
	$return = array();
	foreach ($res as $val){	
	$result=stristr($val->name,$for);
	if ($result == false){
		//echo 'не найдено в позици name'.$val->id;
		$result=stristr($val->art,$for);
		if ($result == false){
		//echo 'не найдено в позици art'.$val->id;
		}
		else {
		//echo 'Найдено в позици art'.$val->id;
		$return[$k]=array('id' => $val->id,'tid' => $this->getSection($val->id), 'vendor' => $val->vendor);
		//echo '<br>';
		//echo $return[$k]['id'];
		//echo '<br>';
		$k++; //если запись не найдена переходит к следующему номеру k+1 и повторяет поиск
		
		}
	}
	else {
		//echo 'Найдено в позици name'.$val->id;
	// создаем элемент массива с индексом k, в который помещаем идентификационный номер записи и строку, в которой найден результат
	$return[$k]=array('id' => $val->id, 'tid' => $this->getSection($val->id) ,'vendor' => $val->vendor);
	//echo '<br>';//отладка
	//echo $return[$k]['id'].'  '.$return[$k]['tid'].'  '.$return[$k]['vendor'];
	//echo '<br>';
	$k++;//если запись не найдена переходит к следующему номеру k+1 и повторяет поиск
		
	}
	}
}

//return null;
// вывод результата поиска на экран
if (!isset($return)){//|| $result === false
	echo '<td>В каталоге нет совпадений с Вашим запросом.'.$for.'</td></tr><tr><td>';
	}
else {
	//$ret=array();		
	//$ret=$this->chioce_vendor($return, $vend);
	//echo '<br>---choice vendor';//отладка
	//$this->showelement($ret);
	//print_r($return);
	//$return=$ret;	
	$nn=count($return);
	//echo '<td>Для '.$vend.' найдено по запросу:'.$for.' '.$nn.' совпадений</td></tr><tr><td>';
	echo '<div class="button" href="#zak1">Результат поиска</div></tr></table>';
	//echo '<table class="goods"><tr class="head"><td width="200">Артикул</td><td width="100">Производитель</td><td width="400">Наименование</td><td>Цена</td><td>На складе</td><td>Код товара</td><td>Доступность</td></tr><tr>';
	echo '<table class="goods"><tr class="head"><td width="200">Код для заказа</td><td width="100">Наименование</td><td>Цена,$USA </td><td>Доступность</td><td>для заказа</td><td>Дата ближайшего транзита</td></tr><tr>';			
	}
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
/*
for($i=0;$i<=count($return);$i++){
	$arr=$return[$i];
	$k=$arr['id'];
	echo '<br>---';//отладка
	echo $k.'---'.$arr['vendor'];//отладка
	$res2 = $this->db->query('SELECT `id`,`vendor`,`codeGJS`,`name`, `art`, `price`,`ms`,`ls`,`stock` FROM `'.$tab.'` WHERE `id` = ^Ni;', $k);
	
	if($res2 !== null) {
				if(!is_array($res2)) {
					//$return1[$i] = array('tid' => $this->getSection($res2->id),'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					$return2[$i] = array('tid' => $this->getSection($res2->id),'art' => $res2->art,'name' => $res2->name,'price' => $res2->price,'stock' => $res2->stock, 'ms' => $res2->ms,'ls' => $res2->ls, 'id'=>$res2->id,'codeGJS' => $res2->codeGJS);
					
					if ($sort==0) $this->viewData($return2[$i],0);
					else {
						$ret['tid'][$i]=$return2[$i]['tid'];
						$ret['id'][$i]=$return2[$i]['id'];
						}
					} 
			else {
			foreach ($res2 as $val){
			$return2[] = array('id' => $val->id,'codeGJS' => $val->codeGJS, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price, 'ms' => $val->ms,'ls' => $val->ls, 'stock' => $val->stock, 'tid' => $this->getSection($val->id));
			$ret['tid'][$i]=$return2[$i]['tid'];
			$ret['id'][$i]=$return2[$i]['id'];			
						}
		}
	}
}*/

for($i=0;$i<count($return);$i++){
	$ret['tid'][$i]=$return[$i]['tid'];
	$ret['id'][$i]=$return[$i]['id'];
	$ret['vendor'][$i]=$return[$i]['vendor'];
}
//echo '<br>rettid '.count($ret['id']);//отладка
//$this->Showobjtype($ret['vendor']);
$array=array();
$l=count($ret['id']);

//$array[$ret['id'][$l]]=100000;
//echo '<br>-----array';//отладка
for ($j=0;$j<$l;$j++) {
	$array[$ret['id'][$j]]=$ret['tid'][$j];
	//echo $j.'-'.$ret['id'][$j].'-'.$ret['vendor'][$j].'+'.$ret['tid'][$j].'-+'.$this->getnameSection($ret['tid'][$j]).'--<br>';//отладка
}
					//$this->Showelement($array);
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
					$z.='<a href="#'.$el['key'].'">'.$this->getnameSection($el['key'],$vend).'</a>';
					$zz=$this->getnameSection($el['key'],$vend);
					$z.=' | ';
					echo '<tr class="head"><td colspan="7"><div><a name="'.$el['key'].'"><b>'.$zz.'</b></div></td></tr>';
					
					
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
if($tid <> 0){
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
		return $ret;
}
else return false;
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
public function numelements($tab){
	$this->table=$tabl;
	$res1 = $this->db->query('SELECT * FROM `'.$this->table.'`', $this->numnews);
	return count($res1);
	}

public function getnew($idnews,$table,$clas,$n,$m=1, $abc='...'){
	 $news=$this->getnews($idnews,$table);
	 $img=explode('|',$news[0]['imgnews']);
	 $aa[3]=$news[0]['idnews'];
	 $aa[6]=$news[0]['name'];
	 $aa[7]=$news[0]['date'];
	 $aa[8]=$news[0]['text'];
	 $aa[9]=$clas['img'].$img[0];
	 $aa[10]=$news[0]['hrefnew'];
	 if ($aa['10']<>"") $abc='Подробности';
	 else $abc='';
	 if (file_exists($aa[9]) && $img[0]<> '')
      {
         $size = GetImageSize($aa[9]); 
		 if($size[0]>0 && $size[1]>0)
			 {   
		 $newsstr.=Maket::divclasstr($clas['clas'][$n],$Pth).'<a href="#" name="new'.$aa[3].'"></a><img  src="'.$aa[9].'" class="'.$clas['clas'][$n].'-img" width = "'.intval($size[0]/$m).'" height= "'.intval($size[1]/$m).'"><br>'.$aa['7'].' <br><b>'.$aa['6'].'</b><br>'.$aa['8'].'<a href="'.$aa['10'].'">'.$abc.'</a></div>';
		 }
	
	}
	else $newsstr.=Maket::divclasstr($clas['clas'][$n],$Pth).$aa['7'].' <br><b><a href="#" name="new'.$aa[3].'">'.$aa['6'].'</a></b><br>'.$aa['8'].'<a href="'.$aa['10'].'">'.$abc.'</a></div>';
	
return $newsstr;
}

public function getnews($numnews, $table) {
		if($numnews > 0){	
						
			if($numnews <> 0) {
			//$res1 = new ArrayObject;
			$res1 = $this->db->query('SELECT * FROM `'.$table.'` WHERE `idnews` = ^Ni;', $numnews);
			//print_r($res1);
			if($res1 !== null)$res1->date = $this->db->query('SELECT DATE_FORMAT(`date`,"%d %m %Y") FROM `'.$table.'` WHERE `idnews` = ^Ni;', $numnews);
			
			if($res1 === null) 
				//throw new StructureWException('numnews does\'t exist', StructureWException::ID_ERROR);
				return false;
			}
			//if(is_array($res1))var_dump($res1);
			$return['news'] = array();
			if($res1 !== null) {
			if(!is_array($res1)) {
				$return['news'][] = array('name' => $res1->name,'text' => $res1->newstext, 'date' => $res1->date, 'vendor' => $res1->vendor,'group' => $res1->group, 'imgnews' => $res1->imgnews,'idnews' => $res1->idnews,'hrefnew' => $res1->hrefnew);					
			} else {
				foreach($res1 as $val)
					$return['news'][] = array('name' => $val->name, 'idn' => $val->idnews,'text' => $val->newstext, 'date' => $val->date, 'vendor' => $val->vendor, 'hrefnew' => $val->hrefnew, 'group' => $val->group, 'imgnews' => $val->imgnews);		
			}
			//print_r($return);
		return $return['news'];	
	}
		}
		else return null;
}		
	
public function allnews($tabl, $Pth,$clas,$n,$m=1){
$newsstr=Maket::divclasstr('container__news',$Pth);
$NN=$this->numrec($tabl['news'])+1;

for ($i=1; $i<$NN; $i++) {
	
	 $news=$this->getnews($NN-$i,$tabl['news']);
	 //print_r($news);
	 $arra=$news[0];
	// print_r($arra);
	 $img=explode('|',$arra['imgnews']);
	 $aa[3]=$arra['idnews'];
	 $aa[6]=$arra['name'];
	 $aa[7]=$arra['date'];
	 $aa[8]=$arra['text'];
	 $aa[9]=$clas['img'].$img[0];
	 $aa[10]=$arra['hrefnew'];
	 if ($aa['10']<>"") $abc='Подробности';
	 else $abc='';
	 if (file_exists($aa[9]) && $img[0]<> '')
      {
         $size = GetImageSize($aa[9]); 
		 if($size[0]>0 && $size[1]>0)
			 {   
		 $newsstr.=Maket::divclasstr($clas['clas'][$n],$Pth).'<a href="#" name="new'.$aa[3].'"></a><img  src="'.$aa[9].'" class="'.$clas['clas'][$n].'-img" width = "'.intval($size[0]/$m).'" height= "'.intval($size[1]/$m).'"><br>'.$aa['7'].' <br><b>'.$aa['6'].'</b><br>'.$aa['8'].'<a href="'.$aa['10'].'">'.$abc.'</a></div>';
		 }
	
	}
	else $newsstr.=Maket::divclasstr($clas['clas'][$n],$Pth).$aa['7'].' <br><b><a href="#" name="new'.$aa[3].'">'.$aa['6'].'</a></b><br>'.$aa['8'].'<a href="'.$aa['10'].'">'.$abc.'</a></div>';
}
$newsstr.='</div>';
return $newsstr;
}

public function inputdata1(){
	echo '<div class="section s10">';
		echo '</div>';// s10
		echo '</div>';
		echo '<div class="section s6">';
		echo '</div>';// s10
		echo '<div class="section s6">';
		echo '</div>';// s10
		for ($j=0;$j<6;$j++){
			echo '<div class="section s1">';
			echo '</div>';// s1
	
}
}

public function gallaries($aaa, $tabl, $clas,$Pth,$numclass,$sw){
	// проверка наличия галлереии на странице
	
	for ($i=0;$i<count($aaa['l']);$i++) {
		//if ($aaa['t'][$i]=="") $aaa['t'][$i]=$aaa['c'][$i];
		$page= new Page($aaa['l'][$i],$tabl);
		$list=Page::readypagelist($page->MainAr,$clas,$sw->getPagelinks($page->MainAr['numpage'],$tabl));
		//show::infosh($list);
		//$list[2][0][$i]=$page->MainAr["hrefpage"].'?np='.$page->MainAr["numpage"];
		//$bbb=array(0=>$list[2][0][$i],'1'=>$list['1'][0][$i],'2'=>$aaa['t'][$i]);
		$bbb[$i]=array(0=>$list['n'][2],'1'=>$list['n'][1],'2'=>$list['n'][3],'3'=>$list['n'][8],'4'=>$list['n'][5]);
		//Page::scalimag3($aaa,'', '',0,$clas,$numclass,$i,'imgs','loz');
		Page::scalimag3($aaa,'', '',$Pth,0,$clas,$numclass,$i,'imgs','cont');
		}
	//echo '</ul></nav>'; 
}

public function showblocksnew($arr,$hd,$list, $clas, $tabl,$numclas,$sw){
	//echo 'Показ блоков '.$arr['idmen'][0];
	if ($arr['idmen'][0]<> 'gall') {
	echo '<div class="'.$arr['idmen'][0].'-item3">';
		
		Page::scalimag3($arr,$img, '', 1,$clas);
		Menu::menulist(0,$list[1][0],$list[2][0],$tabl,'','imgtext');
		Page::scalimag3($arr,$img, '', 1,$clas);
	echo '</div>';
}
	switch ($hd) {
	case 6:
	{
		$this->gallaries($arr, $tabl, $clas,$numclas,$sw);
		//Page::gallWpt($arr);
	break;
	}
	case 5:
	{
	//echo '5+++++++++++++++++++++++++++++';
	
	echo '<div class="s7">';
		$this->allnews($tabl, $clas,8);	
	echo '</div>';
	echo '<div class="s6">';
			Menu::menulist(1,$list[1][0],$list[2][0],$levuser,'',$tabl,'zag','list');
			//Page::scalimag($clas['img'].$list['n'][5], $list, "",'','',$list['n'][4],$clas['class'][5],$tabl);
		//$this->inputdata1();
	echo '</div>';	
	break;
	}
	 case 4 :
		{
		if ($list['12'][0][0] <> 'banner') {
		//10
			echo '<div class="section">';
			Page::inpbldiv2($arr,$list,"blog-item",'');
			echo '</div>';
			echo '<div class="section">';;
			Page::inpbldiv2($arr,$list,"blog-item",'');
			echo '</div>';
			}
			else echo 'BANER';
		break;
		}
	case 3 :
		{
		if ($list['12'][0][0] <> 'banner'){
		echo '<div class="blog-item'.($hd+1).'">';
			Page::inpbldiv2($arrmain,$list,"blog-item",'');
		//echo '</div>';
		$nblog=3;
		$next=show::blogsh($clas,$arr,'imgt','cont',0,$nblog+1);
	//echo 'next ';echo $next.'<br>'; 
		/*echo '</div><div class="section">';
		Menu::menulist(0,$list[1][0],$list[2][0],$tabl,'','imgtext');
		Page::scalimag($clas['img'].$list['n'][5], $list, "Посмотреть",$namenews,'./images/butt1.gif',$list['n'][4],'blog-item-content',$tabl); 
		echo '</div>';*/
		}
		else {
		//13	
			echo 'BANER';
		}
		break;
		}
	case 2 :
		{
		//echo '2+++++++++++++++++++++++++++++';
	if ($list['12'][0][0] <> 'banner')			{
		//10
		echo '<div class="s8">';
		//Page::inpblsp($list,"block1",$clas,1,1);
		echo '</div>';
		//11
		echo '<div class="s7">';
			Menu::menulist(1,$list[1][0],$list[2][0],$tabl,'zag','list');
			//Page::scalimag($clas['img'].$list['n'][5], $list, "",'','',$list['n'][4],$clas['class'][5],$tabl);
		echo '</div>';
		}
		else {
		//13
			echo 'BANER';
		}
		break;
		}
	case 1 :
		{	
		//echo '1+++++++++++++++++++++++++++++';
		//10
		echo '<div class="s3">';
		
			Menu::menulist(1,$list[1][0],$list[2][0],$tabl,'zag','list');
			//Page::scalimag($clas['img'].$list['n'][5], $list, "",'','',$list['n'][4],$clas['class'][5],$tabl);
			echo '</div>';
		if ($list['12'][0][0] <> 'banner'){	
		//11
		echo '<div class="s8">';
			 //Page::inpblsp($list,"block1",$clas,1,1);
			
		echo '</div>';
		}
		else {
		//13
		echo 'BANER';
		}
		break;
		}	
	default :
		{	
		echo '<div ><a name="zak1"><h2>'.$list[8][0][1].'</h2></a>';	
		echo '<div class="section">';
				
		if ($list[1][0][0] <> '') Menu::menulist(1,$list[1][0],$list[2][0],$tabl,'zag','list');
			//echo '<div>-----';
			Menu::menulist(1,$list[1][0],$list[2][0],$tabl,'zag','list');
			//print_r($list[8]);
		    echo '</div>';// s3
			
			//Page::scalimag($clas['img'].$list['n'][5],$list, "Все новости",'','',$list['n'][4],$clas['class'][5],$tabl);
		echo '</div></div>';// s4
		//3
	echo '<div class=" s8">';
	
			//$this->inputdata1();
			//4
			echo '<div class="'.$clas['class'][20].'">';
			 //Page::inpblsp($list,"block1",$clas,1,1);
			echo '</div>';
			echo '</div>';//s8
			break;
		}	
}	
}

static public function viewpagetypelist($np,$typelist, $tabl){
	if ($np <> '') {
		//echo $typelist;
		$pg= new Page($np, $tabl);
		if(!empty($pg)){
		//var_dump($pg->MainAr[$typelist]);
		if($typelist === 'list')	{
			$list['buttons']=$pg->MainAr['hreflist'];
			$nlist=explode(';',$list['buttons']);
			$list['namep']='';
			foreach($nlist as $val) {
				$arn=Page::getnamepage($val);
				$nup=array_keys($arn);
				$list['namep'].=$arn[$nup[0]].';';
			}
			
		}
		elseif($typelist === 'buttons' || $typelist === 'content' || $typelist === 'imgtext' || $typelist === 'lozung' || $typelist === 'butthref') 
		{
			if(strstr($pg->MainAr[$typelist],'|')){
				$LB=explode('|',$pg->MainAr[$typelist]);
				$list['namep']=$LB[0];
				$list['buttons']=$LB[1];
			}
			else return null;
		}
		else return null;
		
	}
	else $list='';
	//debug($list);
	return $list;
}
return false;
	
}

static public function viewlistnew($lst,$typelist,$tabl){
//if (isset($lst)) $V->lst=$lst; 
//if (isset($lst)) $V->lst[1]=$lst[1];
//print_r($list[1]);
//print_r($V->lst); 	
$return=array();
//var_dump($lst);
foreach($lst as $val){ 
	if($val != '')
	if($val != ''){
		$k = intval($val);
		$list[]=ElementsW::viewpagetypelist($k,$typelist, $tabl);
	}

}	
if(isset($list)) return $list;
else return false;
}

static function getnamepage($np,$tabl){
	$pagelist = new Page($np,$tabl);
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
return $lst0;
}

public function socialBlock($arr,$Pth){
	$socialBlock=$this->socialbutt('small');
	$socialBlock.=Maket::divclasstr('user',$Pth).$arr['owner']->telmain.'</div>'.Maket::divclasstr('user',$Pth).$arr['owner']->email.'</div>';
	$socialBlock.=Maket::divclasstr('copiright',$Pth).'<small>~©2020~</small></div>';
	return $socialBlock;
}

public function showfooternew($tabl,$arr,$Pth,$typelist,$pos,$key_ch,$clas) {
	
$ARRR=array();
//print_r($arr);
if ($typelist === '' ) {
	$typelist='butt';
	$list1=$arr[$typelist];
	$list2=$arr[$typelist.'href'];
}
elseif ($typelist === 'foot'){
	$list1=$arr[$typelist];
	$list2=$arr[$typelist.'href'];
	
}
$str='';

if ($typelist === 'butt') $typelist1='buttons';
elseif($typelist === 'cont') $typelist1='content';
elseif($typelist === 'loz') $typelist1='lozung';
elseif($typelist === 'imgt') $typelist1='imgtext';
elseif($typelist === 'foot') $typelist1='butthref';
else $typelist1='list';
//echo $typelist1;
$ARRR=$this->viewlistnew($list2,$typelist1,$tabl);
//print_r($ARRR);
if($typelist == 'butt' || $typelist == 'cont' || $typelist == 'loz' || $typelist == 'imgt'  || $typelist == 'foot' ){ 
	//print_r($ARRR);echo '<br>';
	if(is_array($ARRR))foreach($ARRR as $j=>$val) $footerlist[$j]=explode(';',$val['buttons']);
	else $footerlist[0]=explode(';',$ARRR['buttons']);
	//echo '----';
$footerkey=array_keys($footerlist);

foreach ($ARRR as $key=>$val) { 
	if($val['buttons']<>'') $Menu->lp[]=explode(';',$val['buttons']);
	if($val['namep']<>'') $Menu->mp[]=explode(';',$val['namep']);
	}


$j=0;
$l=$pos;

if($j<$key_ch)$str.=Maket::divclasstr('footer-sec'.$key_ch,$Pth);
$str.='<nav>';
foreach ($Menu->lp[$pos] as $key=>$value) {
	if($value<>'') {
		if(is_array($value) && is_array($Menu->mp[$pos])) {
			$value2=explode(';',$value[$key]);
			$value3=explode(';',$Menu->mp[$pos][$key]);
		}
		else {
			$value2=explode(';',$value);
			$value3=explode(';',$Menu->mp[$pos][$key]);
		}	
	}
	else break;
	
	foreach ($value2 as $key1=>$val)	{
		if ($val<>'' ) {
		$pg= new Page($val,$tabl);	
		$lst0=$pg->MainAr['numpage'];
		if(isset($value3[$key1])){ 
			if($value3[$key1] != '')$lst1=$value3[$key1];
			//var_dump($lst1);
		}
		else $lst1=$pg->getnamepage($pg);
		
		//$lst1.=$footerkey[$pos];
		
		if (strstr($pg->MainAr[$typelist1],'|')) {
			$LB=explode('|',$pg->MainAr[$typelist1]);
			$lst3[0]=explode(';',$LB[1]);//массив номеров страниц, на которые ссылается массив alt названий кнопок
			$lst5[0]=explode(';',$LB[0]);//массив alt названий кнопок страницы
		}
		elseif(strstr($typelist1,'list')) {
			$lst3[0]=explode(';',$pg->MainAr['hreflist']);//массив номеров страниц, на которые ссылается массив alt названий кнопок
			$lst5[0]=explode(';',$pg->MainAr['list']);//массив alt названий кнопок страницы
		}
		elseif(strstr($typelist1,'butthref')) {
			$FT=explode('|',$pg->MainAr['butthref']);
			$lst3[0]=explode(';',$FT[1]);//массив номеров страниц, на которые ссылается массив alt названий кнопок
			$lst5[0]=explode(';',$FT[0]);//массив alt названий кнопок страницы
		}
		
		foreach($lst5[0] as $k=>$val){
			if($lst5[0][$k]==='')$lst5[0][$k]= ElementsW::getnamepage(intval($lst3[0][$k]),$tabl);
			
		}
		//var_dump($lst5[0]);
		//foreach($lst5[0] as $k=>$val)$lst5[0][$k].='-'.$val.'-'.$k;
		if(isset($lst1)){
			if($lst1 !='' && $key< $key_ch)
			$str.=Maket::spanclasstr(Maket::spanclasstr($lst1,$Pth,'zag','p').Maket::menulistr(1,$lst5[0],$lst3[0],$tabl,$clas['clas'][19].$key_ch,$typelist1),$Pth,$clas['clas'][19].$key_ch,'ul');
			}
			
		}
		$l++;
			}
		$str.='</ul>';	
		if ($j<$key_ch-1 && isset($lst0)) {
			$str.='</div>'.Maket::divclasstr('footer-sec'.$key_ch,$Pth);	
			$j++;
			$str.='</ul>';
		}
		//elseif($j === $key_ch)$str.='</div><div class="footer-sec'.$key_ch.'">'.$socialBlock;
		
		}	
	$str.='</nav></div>';	
	}
	return $str;
}//}
//}

public function footermenu($Pth,$val,$typelist1,$clas,$dir='row'){
	$str='';
	$tabl=$clas['tabl'];
	$pg= new Page($val,$tabl);
	if (strstr($pg->MainAr['namep'],'|')) {
			$lst0=explode('|',$pg->MainAr['namep']);
		}
		else $lst0=$pg->MainAr['namep'];
		if (strstr($pg->MainAr[$typelist1],'|')) {
			$LB=explode('|',$pg->MainAr[$typelist1]);
			$lst3[0]=explode(';',$LB[1]);//массив номеров страниц, на которые ссылается массив alt названий кнопок
			$lst5[0]=explode(';',$LB[0]);//массив alt названий кнопок страницы
		}
		elseif(strstr($typelist1,'list')) {
			$lst3[0]=explode(';',$pg->MainAr['hreflist']);//массив номеров страниц, на которые ссылается массив alt названий кнопок
			$lst5[0]=explode(';',$pg->MainAr['list']);//массив alt названий кнопок страницы
		}
		
		$str.=Maket::divclasstr('menu',$Pth,'display: flex; flex-direction: '.$dir.';justify-content: space-around;flex-basis:100%;border: 1px solid black;');
		$str.=Menu::menulistr(1,$lst5[0],$lst3[0],$clas);
		$str.='</div>';
	return $str;
}

public function geteids($tid) {
if($tid != 0){
		$find=$this->db->query('select `eid` from `type-elements` where `tid`= ^Ni;', $tid);
		if($find != null) {
		$i=0;
		if (!count($this->find)==1){		
		foreach ($find as $val){
			$return[$i] = array('id' => $val->eid);
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
		
public function getnameSection($tid,$vend='',$table='structure') {
	if($tid != 0){
		$find=$this->db->query('select `name`,`pid` from `'.$table.'` where `id`= ^Ni;', $tid);
		//echo 'tid-->'.$find;echo '<br>';
		if ($find->name==$vend)$res=$this->getnameSection($find->pid).' '.$vend;
		else $res=$find->name;
			}
	return $res;				
}		
public function getidgjs($gjs){
if($gjs != 0){
		$find=$this->db->query('select `id` from `elements` where `codeGJS`= ^Ni;', $gjs);
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
if($stock>20) {$ar['ms']=1;$ar['ls']=1;}
elseif($stock>10) {$ar['ms']=2;$ar['ls']=2;}
else {$ar['ms']=3;$ar['ls']=3;}
if($st==0){
while ($elements=each($ar)){
					$b=$elements['value'];
					switch ($i){
					case 0:
					{
						echo '<td><a href="./detail.php?eid='.$cod.'">GJS'.$b.'</a></td>';
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
							if ($stock < 5) $logtxt="|";
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

public function getvendor($table){
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
else $return[]='';
//else echo 'не найдено';
if(is_array($return)) asort($return);
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
//$numrecbd=$this->numrec('elemarch');
//echo 'число записей '.$vend.'  '.$numrecbd;

//$this->vendor=$vend;	
//echo '--'.$this->vendor.'--';		
if (!$vend==''){
	$l=0;
	
	for($i=0;$i<=count($return);$i++){
			
			if ($return[$i]['vendor'] == $vend) {
				
			$ret[$l]['id'] = $return[$i]['id'];
			$ret[$l]['tid']= $this->getSection($return[$i]['id']);
			$ret[$l]['vendor'] = $return[$i]['vendor'];
			//echo '---<br>';// отладка
			//echo $i.'-'.$l.'-'.$return[$i]['vendor'].'-'.$return[$i]['id'].'--'.$this->getSection($return[$i]['id']).'--<br>';//отладка
			$l++;
			}
			
			}
	}
else return $return;
$return=$ret;
return $return;
}

/*public function viewer1($return,$sort=0,$vend) {
$arr = array();
$return1 = array();
$return2 = array();
$ret['tid']=Array();
$ret['id']=Array();
$ret['num']=Array();
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
		}*/

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
	$bbb=array('0'=>'./detail.php?eid='.$dim[$i]['eid'],'1'=>$desc[3],'2'=>'<a href="./book/show_cart.php?new='.$dim[$i]['GJS'].'">Заказать код GJS'.$dim[$i]["GJS"].'</a><br>','3'=>$dim[$i]['name'].'<br>'.$dim[$i]['price'],'4'=>' $USA');
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
}
}

public function result_find_group($tid,$vend){
	if ($ew->gettF($tid)==1) $a=$ew->viewer($ew->viewertid($tid),$sort=1,$vend);
			else {
				if ($tid<>0){
					echo '<td class="zag2">'.$ew->getnameSection($tid).'</td></tr>';
				}
}	
}
/*
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
		
	}*/
	public function socialbutt($mode){
		$str="<script type=\"text/javascript\">(function(w,doc) {
if (!w.__utlWdgt ) {
    w.__utlWdgt = true;
    var d = doc, s = d.createElement('script'), g = 'getElementsByTagName';
    s.type = 'text/javascript'; s.charset='UTF-8'; s.async = true;
    s.src = ('https:' == w.location.protocol ? 'https' : 'http')  + '://w.uptolike.com/widgets/v1/uptolike.js';
    var h=d[g]('body')[0];
    h.appendChild(s);
}})(window,document);
</script>";
	switch ($mode){
		case 'small' : {
			$str.='<div data-mobile-view="true" data-share-size="20" data-like-text-enable="false" data-background-alpha="0.0" data-pid="1863228" data-mode="share" data-background-color="#ffffff" data-share-shape="round-rectangle" data-share-counter-size="12" data-icon-color="#ffffff" data-mobile-sn-ids="fb.vk.tw.wh.tm." data-text-color="#000000" data-buttons-color="#FFFFFF" data-counter-background-color="#ffffff" data-share-counter-type="disable" data-orientation="horizontal" data-following-enable="false" data-sn-ids="fb.vk.tw.wh.tm.ok.mr.lj." data-preview-mobile="false" data-selection-enable="true" data-exclude-show-more="false" data-share-style="1" data-counter-background-alpha="1.0" data-top-button="false" class="uptolike-buttons" ></div>';
			return $str;
		}
		case 'mid' : {
			$str.='<div data-mobile-view="true" data-share-size="30" data-like-text-enable="false" data-background-alpha="0.0" data-pid="1863228" data-mode="share" data-background-color="#ffffff" data-share-shape="round-rectangle" data-share-counter-size="12" data-icon-color="#ffffff" data-mobile-sn-ids="fb.vk.tw.wh.tm." data-text-color="#000000" data-buttons-color="#FFFFFF" data-counter-background-color="#ffffff" data-share-counter-type="disable" data-orientation="horizontal" data-following-enable="false" data-sn-ids="fb.vk.tw.wh.tm.ok.mr.lj." data-preview-mobile="false" data-selection-enable="true" data-exclude-show-more="false" data-share-style="1" data-counter-background-alpha="1.0" data-top-button="false" class="uptolike-buttons" ></div>';
			return $str;
		}
	}
	//print_r($str);
	
	}
}
?>