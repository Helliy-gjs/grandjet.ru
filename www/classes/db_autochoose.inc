<?php

class DB extends Singleton {
	private $location = 'mysql.baze.deltar.ru',
			$user = 'gjs_deltar_ru',
			$pass = 'ittBudB5',
			$dbname = 'deltar_ru',
			$port = 63917,
			$conn = null, 
			$query = '', 
			$result = null;
		
	private $location0 = 'mysql.baze.deltar.ru',
			$user0 = 'gjs_deltar_ru',
			$pass0 = 'ittBudB5',
			$dbname0 = 'gjs_deltar_ru',
			$port0 = 63917,
			$conn0 = null, 
			$query0 = '', 
			$result0 = null;
	
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
	
	private $location5 = 'mysql.baze.deltar.ru',
			$user5 = 'gjs_deltar_ru',
			$pass5 = 'ittBudB5',
			$dbname5 = 'grandjetstudio_com',
			$port5 = 63917,
			$conn5 = null, 
			$query5 = '', 
			$result5 = null;	
				
	protected function __construct() {
		if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
		if($_SERVER['HTTP_HOST']=='deltar.ru') {
			$this->location = $this->location0;
			$this->user = $this->user0;
			$this->pass = $this->pass0;
			$this->dbname = $this->dbname0;
			$this->port = $this->port0;
			$this->conn = $this->conn0; 
			$this->query = $this->query0; 
			
		}
		elseif($_SERVER['HTTP_HOST']=='grandjetstudio.ru'){
			$this->location = $this->location1;
			$this->user = $this->user1;
			$this->pass = $this->pass1;
			$this->dbname = $this->dbname1;
			$this->port = $this->port1;
			$this->conn = $this->conn1; 
			$this->query = $this->query1; 
		}	
		elseif($_SERVER['HTTP_HOST']=='grandjet.ru') {
			$this->location = $this->location2;
			$this->user = $this->user2;
			$this->pass = $this->pass2;
			$this->dbname = $this->dbname2;
			$this->port = $this->port2;
			$this->conn = $this->conn2; 
			$this->query = $this->query2; 
		} 
		elseif($_SERVER['HTTP_HOST']=='shop.deltar.ru') {
			$this->location = $this->location0;
			$this->user = $this->user0;
			$this->pass = $this->pass0;
			$this->dbname = $this->dbname0;
			$this->port = $this->port0;
			$this->conn = $this->conn0; 
			$this->query = $this->query0; 
		}
		elseif($_SERVER['HTTP_HOST']=='grandjet.deltar.ru') {
			$this->location = $this->location3;
			$this->user = $this->user3;
			$this->pass = $this->pass3;
			$this->dbname = $this->dbname3;
			$this->port = $this->port3;
			$this->conn = $this->conn3; 
			$this->query = $this->query3; 
		}
		elseif($_SERVER['HTTP_HOST']=='gjs.deltar.ru') {
			$this->location = $this->location0;
			$this->user = $this->user0;
			$this->pass = $this->pass0;
			$this->dbname = $this->dbname0;
			$this->port = $this->port0;
			$this->conn = $this->conn0; 
			$this->query = $this->query0; 
		}
		elseif($_SERVER['HTTP_HOST']=='grandjetstudio.com') {
			$this->location = $this->location5;
			$this->user = $this->user5;
			$this->pass = $this->pass5;
			$this->dbname = $this->dbname5;
			$this->port = $this->port5;
			$this->conn = $this->conn5; 
			$this->query = $this->query5; 
		}
		else {
			$this->location = 'mysql.baze.deltar.ru';
			$this->user = 'gjs_deltar_ru';
			$this->pass = 'ittBudB5';
			$this->dbname = 'adm_deltar_ru';
			$this->port = 63917;
			$this->conn = null; 
			$this->query = ''; 
			$this->result = null;
			
		}
		
		$this->conn = new mysqli($this->location, $this->user, $this->pass, $this->dbname, $this->port);
		if(mysqli_connect_errno()) {
			throw new DBException(mysqli_connect_errno().', '.mysqli_connect_error(), DBException::CONNECT_ERROR, mysqli_connect_errno());
		}
		if(!$this->conn->set_charset('utf8')) {
			throw new DBException('Set charset error', DBException::SET_CHARSET_ERROR);
		}
		return $this->init_data=array($this->user,$this->pass,$this->location,$this->dbname,$this->port);
	}
	
		
	function __destruct() {
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
	public function initbd($domen,$db){
	
	if (isset($domen)) $this->domen=$domen;
	
	//$db = Singleton::getInstance('DB');	
	if ($this->domen <> "") {
	$res=$db->query('SELECT `bd`,`passwad`,`logad`,`host`,`port`,`domen`,`ids` FROM `Allsites` WHERE `domen` = ^Ns;', $this->domen);	
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
}
?>
