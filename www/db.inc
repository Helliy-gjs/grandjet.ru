<?php
class DB extends Singleton {
	private $key = 'SecKey0x0777';
	private $content = array();
	
private function namebasedata(){
	if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}	
	
	
	if(strstr($_SERVER['HTTP_HOST'],'.'))$name_domen=explode('.',$_SERVER['HTTP_HOST']);
	else $name_domen[0]=$_SERVER['HTTP_HOST'];
	if(isset($name_domen[1]) && !isset($name_domen[2]))$this->dbname=$namebd=$name_domen[0].'_'.$name_domen[1];
	elseif(isset($name_domen[1]) &&  isset($name_domen[2]))$this->dbname=$namebd=$name_domen[1].'_'.$name_domen[2];
	return $namebd;
	}	
	
function namecurbd(){
	return $this-> namebasedata();
	}
	private $location = 'baze.grandjet.ru',
			$user = 'grandjet_ru',
			$pass = 'XtG6DmEP',
			$dbname = 'grandjet_ru',
			$port = 64000,
			$conn = null, 
			$query = '', 
			$result = null;
	/*private $location = 'mysql.baze.deltar.ru',
			$user = 'gjs_deltar_ru',
			$pass = 'ittBudB5',
			$dbname = 'grandjet_ru',
			$port = 63917,
			$conn = null, 
			$query = '', 
			$result = null;*/
/*	
private $location = 'sportshop.loc',
	$user = 'root',
	$pass = 'root',
	$dbname = 'sportshop_loc',
	$port = 3306,
	$conn = null, 
	$query = '', 
	$result = null;*/
			
	private $location0 = 'mysql.baze.deltar.ru',
			$user0 = 'gjs_deltar_ru',
			$pass0 = 'ittBudB5',
			$dbname0 = 'grandjet_ru',
			$port0 = 63917,
			$conn0 = null, 
			$query0 = '', 
			$result0 = null;
	/*
	private $location1 = 'mysql.baze.deltar.ru',
			$user1 = 'gjs_deltar_ru',
			$pass1 = 'ittBudB5',
			$dbname1 = 'grandjetstudio_ru',
			$port1 = 63917,
			$conn1 = null, 
			$query1 = '', 
			$result1 = null;
			
	private $location2 = 'baze.grandjet.ru',
			$user2 = 'grandjet_ru',
			$pass2 = 'XtG6DmEP',
			$dbname2 = 'grandjet_ru',
			$port2 = 64000,
			$conn2 = null, 
			$query2 = '', 
			$result2 = null;
	
	private $location3 = 'baze.deltar.ru',
			$user3 = 'deltar_ru',
			$pass3 = '3iii4eradC',
			$dbname3 = 'deltar_ru',
			$port3 = 64000,
			$conn3 = null, 
			$query3 = '', 
			$result3 = null;
			
	private $location4 = 'baze.grandjetstudio.com',
			$user4 = 'grandjetstudio_com',
			$pass4 = 'jj2e7jQcwxkm',
			$dbname4 = 'grandjetstudio_com',
			$port4 = 64000,
			$conn4 = null, 
			$query4 = '', 
			$result4 = null;
			
	private $location = 'mysql.baze.deltar.ru',
			$user = 'gjs_deltar_ru',
			$pass = 'ittBudB5',
			$dbname = 'deltar_ru',
			$port = 63917,
			$conn = null, 
			$query = '', 
			$result = null;*/ 
			
protected function __construct()    {
        $a = func_get_args();
        $i = func_num_args();
       if (method_exists($this,$f='__construct'.$i) && $i>0) {
            call_user_func_array(array($this,$f),$a);
        }
		elseif(method_exists($this,$f='__construct0')){
			call_user_func_array(array($this,$f),array());
		}
    }		
	
protected function __construct5($par0,$par1,$par2,$par3,$par4) {
		$this->location=$par0;
		$this->user=$par1;
		$this->pass=$par2;
		$this->dbname=$par3;
		$this->port=$par4;
		//echo '-------'.$this->port;	
		//$this->conn=new mysqli($db_load['loc'],$db_load['user'],$db_load['pass'],$db_load['dbname'],$db_load['port']);
		$this->conn = new mysqli($par0, $par1, $par2, $par3, $par4);
		if(mysqli_connect_errno()) {
			throw new DBException(mysqli_connect_errno().', '.mysqli_connect_error(), DBException::CONNECT_ERROR, mysqli_connect_errno());
		}
		else '5-Соединение установлено '.$this->dbname;
		if(!$this->conn->set_charset('utf8')) {
			throw new DBException('Set charset error', DBException::SET_CHARSET_ERROR);
		}
		
		return $this->init_data=array($this->user,$this->pass,$this->location,$this->dbname,$this->port);
	}
	
protected function __construct1($par1) {
	if($par1==1)	$this->dbname=$this->namebasedata();
	elseif($part1==2)$this->dbname='deltar_ru';
	else return false;
	
	$this->conn = new mysqli($this->location, $this->user, $this->pass, $this->dbname, $this->port);
	if(mysqli_connect_errno()) {
		throw new DBException(mysqli_connect_errno().', '.mysqli_connect_error(), DBException::CONNECT_ERROR, mysqli_connect_errno());			
	}
	else '1-Соединение установлено '.$this->dbname;
		if(!$this->conn->set_charset('utf8')) {
			throw new DBException('Set charset error', DBException::SET_CHARSET_ERROR);
		}
		return $this->init_data=array($this->user,$this->pass,$this->location,$this->dbname,$this->port);
		
	}
	
protected function __construct0($par='') {
		$namebd=$this->namebasedata();
		if(!$this->existbd($namebd))$this->dbname=$this->dbname0;
		else $this->dbname=$namebd;
		$this->conn = new mysqli($this->location, $this->user, $this->pass, $this->dbname, $this->port);	
		if(mysqli_connect_errno()) {
			throw new DBException(mysqli_connect_errno().', '.mysqli_connect_error(), DBException::CONNECT_ERROR, mysqli_connect_errno());
		}
		else '0-Соединение установлено '.$this->dbname;
		if(!$this->conn->set_charset('utf8')) {
			throw new DBException('Set charset error', DBException::SET_CHARSET_ERROR);
		}
		return $this->init_data=array($this->user,$this->pass,$this->location,$this->dbname,$this->port);
	}
	
private function existbd($db){
		$this->conn = new mysqli($this->location0, $this->user0, $this->pass0, $this->dbname0, $this->port0);
		$sql = 'SELECT COUNT(*) AS `exists` FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMATA.SCHEMA_NAME="'.$db.'"';
		// execute the statement
		$query = $this->conn->query($sql);
		if ($query === false) {
		throw new Exception($mysqli->error, $mysqli->errno);
	}

		// extract the value
		$row = $query->fetch_object();
		$dbExists = (bool) $row->exists;
	return $dbExists;
	}
	
private function  whatisbd($domen){
		if (strstr($domen,'www')) {
			$domen=substr($domen,4);
		}
		if(strstr($domen,'.'))$name_domen=explode('.',$domen);
		else $name_domen[0]=$domen;
		if(isset($name_domen[1]) && !isset($name_domen[2]))$this->dbname=$namebd=$name_domen[0].'_'.$name_domen[1];
		return $this->dbname;
	}
	
public function yourbd($domen){
		$ret=$this->whatisbd($domen);
		$retu=array(0=>$ret);
		if($ret<>'')return $retu[0];
	}
		
	public function destruct() {
		$this->conn->close();
	}

	private function makeQuery() {
		if(($this->result = $this->conn->query($this->query)) === false) {
			throw new DBException($this->conn->errno.', '.$this->conn->error.' Query: '.$this->query, DBException::QUERY_ERROR, $this->conn->errno);
		}
		return $this->parseResult();
	}

	private function parseResult() {
		if(true === $this->result) {
			$return = true;
		} else {
			switch($this->result->num_rows) {
				case 0:
					$return = null;
					break;
				case 1:
					if(1 != $this->result->field_count)
						$return = $this->result->fetch_object();
					else {
						$row = $this->result->fetch_row();
						$return = $row[0];
					}
					break;
				default:
					$return = array();
					while($obj = $this->result->fetch_object())
						$return[] = $obj;
			}
			$this->result->close();
		}		
		return $return;
	}

	function id() {
		return $this->conn->insert_id;
	}
	
	//p - столбцы, таблицы.
	//l - параметры для поиска через LIKE
	function queryA($query, $args) {
		$this->query = $query;
		$var = null;
		$numargs = count($args);
		$i = 0;
		while(($pos = strpos($this->query, '^N'))&&($i<$numargs)) {
			$var = $args[$i];
			switch($this->query{$pos+2}) {
				case 'i':
					$var = '\''.(int)$var.'\'';
					break;
				case 's':
					$var = '\''.$this->conn->real_escape_string($var).'\'';
					break;
				case 'p':
					$var = '`'.$this->conn->real_escape_string($var).'`';
					break;
				case 'l':
					$var = '\''.addcslashes($this->conn->real_escape_string(str_replace('\\', '\\\\', $var)), '_%').'\'';
					break;
				default:
					throw new DBException('Query parsing error. Query:'.$this->query.', var:'.$var, DBException::QUERY_PARSING_ERROR);
			}
			$this->query = substr($this->query, 0, $pos).$var.substr($this->query, $pos+3);
			$i++;
		}
		return $this->makeQuery();		
	}

	function query() {
		if(func_num_args()==0) return null;
		$args = func_get_args();
		return $this->queryA(array_shift($args), $args);		
	}
	
	function start() {
		$this->conn->query('START TRANSACTION;');
	}
	
	function commit() {
		$this->conn->query('COMMIT;');
	}
	
	function autocommit($mode){
		if ($mode) $this->conn->query('SET autocommit=1');
		else $this->conn->query('SET autocommit=0');
	}
	
	function rollback() {
		$this->conn->query('ROLLBACK;');
	}
	function showtables(){
		$l=0;
		$result=$this->conn->query('SHOW TABLES;');
		while($res=$result->fetch_array(MYSQL_ASSOC)){
		$array[$l]=$res;
		$rrr[$l]=$array[$l][Tables_in_grandjetstudio_ru];
		
	    $l++;
		}
		return $rrr;
	}

function getscountab($tab,$key,$mode,$field='',$valu=''){
		//$db = Singleton::getInstance('DB');
		$order = ' ORDER BY ';
		$order .= '`numpage`';
		$order .= ' DESC ';
		if ($key <>''&& $mode =='f') {
			if($field == '') {
				$d="SELECT `$key` FROM `$tab` ORDER BY $key DESC";
				$res=$this->query($d);	
			}
			else if($valu !=''){
				$d="SELECT `$key` FROM `$tab` WHERE `$field`=^Ns ORDER BY $key DESC;";
				$res=$this->query($d,$valu);	
			}
			else {
				$d="SELECT `$key`,`$field` FROM `$tab` ORDER BY $key DESC";
				$res=$this->query($d);	
			}
		}
		elseif($mode == 't' && strstr($tab,'pages'))  {
			$d="SELECT `$key` FROM `$tab` WHERE `$key`=^Ns $order;";
			$res=$this->query($d,$_SERVER['HTTP_HOST']);
			$key='numpage';
		}
		elseif($mode == 't' && strstr($tab,'map'))  {
			$site=$this->initbd($_SERVER['HTTP_HOST'],$db);
			$d="SELECT `$key` FROM `$tab` WHERE `domen`=^Ns;";
			$res=$this->query($d,$site->domen);
			}	
		else {
			$d="SELECT * FROM `$tab` ";
			$mode='c';
			$res=$this->query($d);
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

public function initbd($domen,$db){
	
	if (isset($domen)) $this->domen=$domen;
	
	//$db = Singleton::getInstance('DB');	
	if ($this->domen <> "") {
	$res=$db->query('SELECT `bd`,`passwad`,`logad`,`host`,`port`,`domen`,`ids` FROM `allsites` WHERE `domen` = ^Ns;', $this->domen);	
	if($res){
		$ret=explode('/',$res->domen);
		if(count($ret)>1) {
			//$res->domen='gjs.'.$ret[0];
			$res->simlink=$ret[1];	
			}
		return $res;	
	}	
	//else echo 'Сайт <'.$domen.'> в базе данных не найден';
	}
	return false;
	}	
	
public function initbdF($domen){
	if (isset($domen)) $this->domen=$domen;
	if (strstr($this->domen,'www')) {
			$this->domen=substr($this->domen,4);
		}
	if ($this->domen <> "") {
	$res=$this->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`css`,`script`,`images`,`pages`, `news`,`element`,`structure`,`desc_site` FROM `allsites` WHERE `domen` = ^Ns;', $this->domen);	
	if($res){
		$ret=explode('/',$res->domen);
		if(count($ret)>1) {
			//$res->domen='gjs.'.$ret[0];
			$res->simlink=$ret[1];	
			}
		return $res;	
	}	
	//else echo 'Сайт <'.$domen.'> в базе данных не найден';
	}
	return false;
	}

function set( $data, $seconds = 3600){
    if($seconds){
        $content['data'] = $data;
        $content['end'] = $seconds;
        if(file_put_contents(CACHE . '/' . md5($this->key) . '.txt',serialize($content))) {
            return true;
        }
        return false;
    }
    }

function get(){
        $file = CACHE . '/'. md5($this->key) . '.txt';
        if(file_exists($file)){
            $content = unserialize(file_get_contents($file));
            if(time() <= $content['end']) return $content;
            unlink($file);
        }
        return false;
    }

public function delete(){
        $file = CACHE . '/'. md5($this->key) . '.txt';
                if(file_exists($file)){
                    unlink($file);
                }
				echo 'cache clean';
    }

public function getCurrencies(){
            $query = 'SELECT * FROM `currency` ORDER BY `base` DESC';
            return $this->query($query);
        }

public function getCurrency($currencies){
           if(isset($_COOKIE['currency']))
		   {
			   foreach($currencies as $k=>$v) {
				   if($_COOKIE['currency'] === $v->code) {
				   $key = $k;
				   break;
			  	 }
			   else continue;
			   } 
		   }
		   else {
			   $key = key($currencies);
		   }
		   //print_r($currencies[0]);
		   //echo 'key='.$key;
		   $currency = $currencies[$key];
		   $currency->symbol_left .= ' '; 
		   $currency->symbol_right =' '.$currency->symbol_right; 
		   //$currenc->code = $key;
		   //debug($currency);
		   return $currency;
        }

public function getlookforfields($for1,$for2,$table) {
			//$res = array();
			//echo '----';
			$res=$this->query('SELECT `numpage`,`title`,`site` FROM `'.$table.'`  WHERE `site` = ^Ns and `title` = ^Ns;', $for1, $for2);
			//echo $res->numpage;
			if (isset($res->numpage)){return $res->numpage;}
			else  {return false;}
			}		

public function insert_tab($Pth,$elem,$array,$type_site='land',$ogran=20000){
	if(isset($Pth['adm']['ids']))$ids=$Pth['adm']['ids'];
	else $ids =1;
	if(isset($Pth['adm']['uid'])) $uid=$Pth['adm']['uid'];
	else $uid = 1;
	if(isset($Pth['adm']['idm']))$idm=$Pth['adm']['idm'];
	else $idm = 1;
	$tabl=Utils::getsitetables($_SERVER['HTTP_HOST']);
	
	switch ($elem)	{
		case $tabl["elem"]:	{
		$ts=date('U');
		$now=getdate($ts);
		$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
		$date1=explode('.',$array[10]);
		$date2=explode('.',$array[11]);
		if($array[10]<>''){
			$tt=$date1[2].'-'.$date1[1].'-'.$date1[0];
			$tt2=$date2[2].'-'.$date2[1].'-'.$date2[0];
				}
			else {
				$tt='';//'0000-00-00';
				$tt2=$date2[2].'-'.$date2[1].'-'.$date2[0];
					}
		$lpg=$this->getscountab($tabl['elem'],'', 'c');//последняя страница в elements
		if($this->getscountab('type-'.$tabl['elem'],'', 'c') != $lpg )return;
		$cnt=0;
				
		for($i=$lpg+1;$i<count($array); $i++) {
		if ($i<$ogran) {	
			$cnt++;
			$this->query('INSERT INTO '.$tabl["elem"].'  
			VALUES (^Ni,^Ni,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni,^Ni,^Ns,^Ns,^Ni,^Ni);',
			$i,$array[1],$array[3],$array[6],$array[2],$array[5],$array[4],$array[7],$array[8],$array[9],$tt,$tt2,1,1);
		
			if ($mysqli->errno<>'') 
			{
				echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
				echo "<BR>";
			}
			else {
				if(!$lps=$user->getscountab($tabl['str'],'id', 'c'));$lps=0;
				if(isset($array[13]))$db->query('INSERT INTO `type-elements` (`eid`, `tid`) VALUES (^Ni,^Ni);',$i,$array[13]+$lps);
				if(isset($array[14]))$db->query('INSERT INTO `type-elemarch` (`eid`, `tid`) VALUES (^Ni,^Ni);',$i,$array[14]+$lps);
				if(isset($array[15]))$db->query('INSERT INTO `type-elemspec` (`eid`, `tid`) VALUES (^Ni,^Ni);',$i,$array[15]+$lps);
				if ($mysqli->errno<>'') {
					echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
					echo "<BR>";
							}
						}
					//}	
				}
			}
			$ttt='элементов';
			break;
		}
		case "elemap":	{
			$ts=date('U');
			$now=getdate($ts);
			$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
			$lpg=$this->getscountab('elemap','id', 'f');//последняя страница в elements
			$cnt=0;
			for($i=$lpg+1;$i<count($array); $i++) {
			if ($i<$ogran) {	
				$cnt++;
				$this->query('INSERT INTO `elemap`  
				VALUES (^Ni,^Ni,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni,^Ni,^Ns,^Ni,^Ns,^Ni);',
				$i,$array[1],$array[3],$array[6],$array[2],$array[5],$array[4],$array[7],$array[8],$array[9],$tt,$idm,$domen,$uid);
				if ($mysqli->errno<>'') 
				{
					echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
					echo "<BR>";
				}
				else {
					$lps=$this->getscountab($tabl['elemap'],'', 'c');
					$this->query('INSERT INTO `type-pages` (`eid`, `tid`) VALUES (^Ni,^Ni);',$i,$array[13]+$lps);
					if ($mysqli->errno<>'') {
						echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
						echo "<BR>";
						}
					}				
				}
			}
			$ttt='элементов';
			break;
		}
		case $tabl["pages"]: {
			$lpg=$this->getscountab($tabl['pages'],'numpage', 'f');//последняя страница в pages
			$startpage=$this->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$_SERVER['HTTP_HOST'],$tabl["pages"]);			
			//echo 'Всего страниц '.$lpg.' стартовая'.$startpage;
			if(isset($startpage)) $link_pages=$startpage.';'.$startpage.';'.$startpage.';'.$startpage.';'.$startpage;
			else  $link_pages = ';;;;';
			$array[0] = $lpg+1;
			$array[1] = 'banmain.jpg|logo.png|'.substr($array[1],0,240).'||';
			if($array[2]=='')$array[2]=$text2.';'.$text1.';'.$text5.';'.$text4.';'.$text3.';|'.$link_pages;
			
			if($array[3]=='')$array[3]='keywords1>keywords2>keywords3;title_page;description_page';
			if($array[4]=='')$array[4]='Button1;Button2;Button3;Button4;Button5;|'.$link_pages;
			
			if($array[6]==='')$array[6]='nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac';		
			if (!$startpage) $array[9]='main_gra_'.$_SERVER['HTTP_HOST'];
			else $array[9]='title_gra_'.$_SERVER['HTTP_HOST'].'_'.$array[0];
			if($array[10]=='')$array[10]=$text2.';'.$text1.';'.$text5.';'.$text4.';'.$text3.';|;;;;;';
			
			if($array[11]==='')$array[11]=$type_site;
			if($array[13]==='')$array[13]='1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg';
			if($array[14]==='')$array[14]='Menu1;Menu2;Menu3;Menu4;Menu5;';
			if($array[15]==='')$array[15]=$link_pages;
			
			if($array[16]==='')$array[16]='footer1;footer2;footer3;footer4;footer5;|'.$link_pages;
			
			if($array[17]=='')$array[17]='butt.jpg;butt.jpg;butt.jpg;butt.jpg;butt.jpg;';
			if($array[18]=='')$array[18]=$text1.';'.$text2.';'.$text3.';'.$text4.';'.$text5.';|'.$link_pages;
			
			if($array[19]=='')$array[19]=1;
			if($array[22]=='')$array[22]='1|unlimit|'.utils::getConfig(4,'configp',1);
					if ($array[0]<$ogran) {
						$this->query('INSERT INTO '.$tabl["pages"].' VALUES (^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ni,^Ns);',$lpg+1,$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],$array[10],$array[11],$array[12],$array[13],$array[14],$array[15],$array[16],$array[17],$array[18],$array[19],$_SERVER['HTTP_HOST'],$uid,$array[22]);
						// if ($mysqli->errno<>'') 
						// {
							// echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
							// echo "<BR>";
						// }	
						$ttt=' страниц ';
					}
				
				break;
			}
		case $tabl["news"]: {
			$lpg=$this->getscountab($tabl['news'],'', 'c');//последняя страница в news
			$cnt=0;
		for($i=$lpg+1;$i<count($array); $i++) {
			if ($i<$ogran) {
				$cnt++;
				$this->query('INSERT INTO '.$tabl["news"].' VALUES (^Ni,^Ns,^Ns,^Ns,^Ni,^Ns,^Ni,^Ns,^Ns,^Ns,^Ni,^Ns);',$uid,$array[0],$array[1],$array[2],$i,$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],$domen);
			if ($mysqli->errno<>'') {
				echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
				echo "<BR>";
					}	
			$ttt=' новостей ';
				}
			}	 
			break;
		}
		case $tabl["str"]: {
			$lpg=$this->getscountab($tabl['str'],'', 'c');//последняя страница в structure
			$cnt=0;
			for($i=$lpg+1;$i<count($array); $i++) {
				if ($i<$ogran) {
					$cnt++;
					$this->query('INSERT INTO '.$tabl["str"].' VALUES (^Ni,^Ni,^Ns,^Ni,^Ni,^Ni,^Ni,^Ni,^Ni,^Ns,^Ni,^Ni);',$i,$array[1]+$lpg,$array[2],$array[3],$array[4],$array[5],0,$array[7],$array[8],$array[9],$ids,$uid);
			if ($mysqli->errno<>'') {
				echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
				echo "<BR>";
			}	
			$ttt=' групп ';
				}
			} 
			break;
		}
		case $tabl["mapsites"]:	{	
			$lpg=$this->getscountab($tabl['mapsites'],'', 'c');//последняя страница в mapsites
			$lpp=$this->getscountab($tabl['pages'],'numpage', 'f');
			$cnt=0;
		if($lpp==1 && $lpg==0){	
		for($i=$lpp+1;$i<count($array); $i++) {
			if ($i<$ogran) {
				$cnt++;
			$this->query('INSERT INTO '.$tabl["pages"].' VALUES (^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ni);',$i,$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],$array[10],$array[11],$array[12],$array[13],$array[14],$array[15],$array[16],$array[17],$array[18],$array[19],$domen,$uid);
			if ($mysqli->errno<>'') {
				echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
				echo "<BR>";
				}	
			$ttt=' групп ';
			}
		} 
		}
			break;
		}
		case 'allnampars':
		{
			$a="namparams";
			$b="codparams";
			$c="nampars";
			$d='tab';
			$e='types';
			$f='delimiter';
			$cnt=0;
			$lpg=$this->getscountab($a,$b, 'f');
			for($i=$lpg;$i<count($array); $i++){
				if ($i<$ogran) {
				$cnt++;	
				$this->query('INSERT INTO '.$a.' ('.$d.','.$b.','.$c.','.$e.','.$f.') VALUES (^Ns,^Ni,^Ns,^Ns,^Ns);', $array[0],$array[1]+$lpg,$array[2],$array[3],$array[4]);	
			if ($mysqli->errno<>'') {
				echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
				echo "<BR>";
			}
			$ttt=' заголовков параметров';
				}
			}
		break;	
		}
		case 'nampars':
		{
			$a="namparams";
			$b="codparams";
			$c="nampars";
			$d='tab';
			$e='types';
			$f='delimiter';
			$lpg=$this->getscountab($a,$b, 'f');
			$cnt=0;
			for($i=$lpg;$i<count($array); $i++){
				if ($i<$ogran) {
					$cnt++;
					$this->query('INSERT INTO '.$a.' ('.$d.','.$b.','.$c.','.$e.','.$f.') VALUES (^Ns,^Ni,^Ns,^Ns,^Ns);', 'namepar',$array[1]+$lpg,$array[2],'','');	
			if ($mysqli->errno<>'') {
				echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
				echo "<BR>";
			}
			$ttt=' заголовков параметров';
				}
			}
		break;	
		}
		case 'params':	{
			$a="params";
			$b="GJScode";
			$c="nampars";
			$lpg=$this->getscountab($a,$b, 'f');
			set_time_limit(1000);
			$cnt=0;
			for($i=$lpg+1;$i<count($array); $i++){
				if ($i<$ogran) {
				$cnt++;	
				$this->query('INSERT INTO '.$a.' ('.$b.','.$c.') VALUES (^Ni,^Ns);',$array[0],$array[1]);	
			//$z="INSERT INTO `$a` (`$b`, `$c`) VALUES ('$array[0]','$array[1]');";
			if ($mysqli->errno<>'') {
				echo "ERROR ".$mysqli->errno." ".$mysqli->error."\n";
				echo "<BR>";
			}
			$ttt=' параметров ';
				}
			}
			break;	
		}
		}
	//return $mysqli->errno;
	}
//12/07/2020

public function gjsapi($Pth,$table,$arr,$fields,$act='new',$field='id',$close_field=1)
{
	$number_value_tab = $this->getscountab($table,$field, 'f');
	$nummaket = $Pth['adm']['idm'];	
	$ids = $Pth['adm']['ids'];	
	$uid = $Pth['adm']['uid'];	
	$numpage = $Pth['adm']['np'];	
	if ($act<>'new'){
		//echo 'обновление  '.$_POST[1];
		$i=0;$y='';
		//print_r($arr);
		foreach($fields as $val) {
			if ($i<count($fields)-1 ) $y.= '`'.$val.'` = "'.$arr[$i].'",';
			else $y.= '`'.$val.'` = "'.$arr[$i].'"';
		$i++;
		}
		//print_r($y);
		$numpost=0;
		while(isset($fields[$numpost]) && $fields[$numpost]<>$field){
			$numpost++;
		}
		//echo $table.' '.$field.' '.$numpost.'<br>';
		///print_r($fields);
		$z= "UPDATE `$table` SET $y WHERE `$field`=".$arr[$numpost].";";
		//echo $z;
		//show::pauza();
		$sql=$this->query($z);
}
else {
	//print_r($arr);echo '<br>';
	//print_r($_POST);
	//echo '<input type="submit" name="Пауза"/>';

$arr[0]=$number_value_tab+1;	
//if($arr[1]<>''){//обязательное условие добавления новой записи
	
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
	//$z1="INSERT INTO $table VALUES ('$arr[0]',$y,$Site->ids,$numpage,$numaket);";
	//echo $z1;
	if($close_field == 4 && $table=='allmakets') $z="INSERT INTO $table VALUES ($arr[0],".$y."$Site->ids,$arr[10],$idmaket,$numpage);";
	elseif($close_field == 4) $z="INSERT INTO $table VALUES ($arr[0],".$y."$ids,$numpage,$idmaket,$uid);";
	elseif($close_field == 3) $z="INSERT INTO $table VALUES ($arr[0],".$y."$ids,$numaket,$numpage);";
	elseif($close_field == 2) $z="INSERT INTO $table VALUES ($arr[0],".$y."$ids,$numpage);";
	elseif($close_field == 1) $z="INSERT INTO $table VALUES ($arr[0],".$y."$ids);";
	elseif($close_field == 0) $z="INSERT INTO $table VALUES ($arr[0],".$y.");";
	$sql=$this->query($z);
	//echo 'добавлена новая запись '.$arr[0];
			//}
		}
	}
//24/07/2020
public function allmakets($ids,$maket='Maket'){
	
	if ($ids > 0)	
		if($maket<>'')$res = $this->query("SELECT * FROM `allmakets` WHERE `Maket`=^Ns AND `ids`=^Ni;",$maket,$ids);
		else $res = $this->query("SELECT * FROM `allmakets` WHERE `ids`=^Ni;",$ids);
	if($res !== null) {
	if(!is_array($res)) { 
//show::infosh('Найден макет '.$maket);
	$return[]=array($res->id,$res->Maket,$res->styles,$res->flex,$res->grid,$res->numparams,$res->fonts,$res->video,$res->effects,$res->scripts,$res->desc,$res->ids);
	}
	else {
		foreach($res as $val) $return[]=array($val->id,$val->Maket,$val->styles,$val->flex,$val->grid,$val->fonts,$val->numparams,$val->video,$val->effects,$val->scripts,$val->desc,$val->ids);
	}
	return $return;
	}
	}

	public function right_access($ds) {
	
	$arrdesc=explode('|',$ds);		
	if($arrdesc[0]<>'') $ret['GA']=$arrdesc[0];
	else $ret['GA']=false;
	if($arrdesc[1]<>'') $ret['YM']=$arrdesc[1];
	else $ret['YM']=false;	
	if($arrdesc[2]=='N')$ret['PR']='http://';
	else $ret['PR']='https://';	
	if(!isset($arrdesc[3]))$ret['metr']=false;
	else $ret['metr']=true;
	
	return $ret;
}

public function loadFormsData($Your_Forms){
	$d = "SELECT * FROM `nameform` WHERE `id`=^Ni;";
	$Namform = $this->query($d, $Your_Forms);
	$d = "SELECT * FROM `forms` WHERE `idform`=^Ni;";
	$Fieldform = $this->query($d,$Namform->id);
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
	return $arrF;
}

	public function getallfieldtable($table){
		$result = $this->query("SHOW COLUMNS FROM `$table`");
		//print_r(get_class_methods('mysqli_result'));
		//print_r($result);
		if ($result) {
			foreach($result as $val) {
				$arrfields['field'][]=$val->Field;
				//$arrfields['type'][]=$val->Type;
				$cond=strstr($val->Type,'(');
				$cond0=strrpos($val->Type,')')-strrpos($val->Type,'(');
				if($cond && $val->Type <> 'text') $val->Type=substr($cond,1,$cond0-1);
				$arrfields['type'][]=$val->Type;
			}
			return $arrfields;
		}
		else exit('Такой таблице нет');	
	}

	public function getAll($tab){
        $res =$this->query('SELECT * from `'.$tab.'`');
        if($res) return $res;
        else return false;
	}
	
	public function getById($tab,$id,$field='id'){
		$res = $this->query('SELECT * FROM `'.$tab.'` WHERE `'.$field.'`=^Ni',$id);
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
		if(!isset($arr[$i]))$arr[$i]='';
		if( $i<$NN-1)$y.="'". $arr[$i]."',";
		elseif($close_field == 0) $y.="'". $arr[$i]."'";
		else $y.="'". $arr[$i]."',";
	}
	//echo $y;
	if($close_field == 4 && $table=='allmakets') $z="INSERT INTO $tab VALUES ($arr[0],".$y."$Site->ids,$arr[10],$idmaket,$numpage);";
	elseif($close_field == 4) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids,$numpage,$idmaket,$uid);";
	elseif($close_field == 3) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids,$numaket,$numpage);";
	elseif($close_field == 2) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids,$numpage);";
	elseif($close_field == 1) $z="INSERT INTO $tab VALUES ($arr[0],".$y."$ids);";
	elseif($close_field == 0) $z="INSERT INTO $tab VALUES (".$y.");";
	$sql=$this->query($z);
	}

	public function updateCategory($tab, $arr, $field){
		$fld = $this->getallfieldtable($tab);
		$fields = $fld['field'];
		$i=0;$y='';
		foreach($fields as $val) {
			if(!isset($arr[$i]))$arr[$i]='';
			if ($i<count($fields)-1 ) $y.= '`'.$val.'` = "'.$arr[$i].'",';
			else $y.= '`'.$val.'` = "'.$arr[$i].'"';
		$i++;
		}
		$numpost=0;
		while(isset($fields[$numpost]) && $fields[$numpost]<>$field){
			$numpost++;
		}
		$z= "UPDATE `$tab` SET $y WHERE `$field`=".$arr[$numpost].";";
		$res  = $this->query($z);
		return $res;
	}

	public function deleteById($tab, $userId,$field='id'){
		$res = $this->query("DELETE FROM `".$tab."` WHERE `$field`=^Ni;",$userId);
	return $res;
	}

}