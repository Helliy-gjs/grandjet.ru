<?php

class ElementsW extends Singleton {
	
	const SORT_ART = 0;
	const SORT_NAME = 1;
	const SORT_PRICE = 2;
	
	
	private $db = null;
	private $opt = array();
	private $const = array();
	private $constopt = array();
	private $codeGJS = array();
	
	protected function __construct() {
		$this->db = Singleton::getInstance('DB'); 	
	}
	
	function prepare() {
		$this->db->query('TRUNCATE TABLE `elements`;');
		$this->db->query('TRUNCATE TABLE `elements-elements`;');
		$this->db->query('TRUNCATE TABLE `type-elements`;');		
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
	
	function getData($id, $sort = self::SORT_NAME, $sortOrder = 0) {
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
		$res = $this->db->query('SELECT t1.id, `name`, `art`, `price` FROM `elements` as t1, `type-elements` as t2 WHERE t2.tid = ^Ni AND t2.eid = t1.id'.$order.';', $id);
		$return = array();
		if($res !== null) {
			if(!is_array($res)) {
				$return[] = array('id' => $res->id, 'name' => $res->name, 'art' => $res->art, 'price' => $res->price);		
			} else {
				foreach($res as $val) {
					$return[] = array('id' => $val->id, 'name' => $val->name, 'art' => $val->art, 'price' => $val->price);
				}
			}
		}
		return $return;				 
	}
	
	function getElement($id) {
		$res = $this->db->query('SELECT `name`, `desc`, `art`, `price` FROM `elements` WHERE `id` = ^Ni;', $id);
		if($res != null) {
			return array('name' => $res->name, 'desc' => $res->desc, 'art' => $res->art, 'price' => $res->price);
		} else {
			return null;
		}
	}
	
}

?>