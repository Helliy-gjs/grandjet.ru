<?php

class StructureW extends Singleton {
	private $numpage,
			$db = null;
	private $sectionsArr = array();
	
	protected function __construct() {
		$this->db = Singleton::getInstance('DB'); 
		//echo 'construct SW OK';
	}
	
	private function checkpid($pid) {
		if($this->db->query('SELECT `id` FROM `structure` WHERE `id` = ^Ni;', $pid) === null)
			throw new StructureWException('pid doesn\'t exist', StructureWException::PID_ERROR);
	}
	
	private function checkid($id) {
		if($id != 0 && $this->db->query('SELECT `id` FROM `structure` WHERE `id` = ^Ni;', $id) === null)
			throw new StructureWException('id does\'t exist', StructureWException::ID_ERROR);		
	}
	
	private function addSection($pid, $name) {
		$this->db->query('INSERT INTO `structure` (`name`, `pid`) VALUES (^Ns, ^Ni);', $name, $pid);
		return $this->db->id();	
	}
	
	private function setSubSectTypeF($id) {
		$this->db->query('UPDATE `structure` SET `typeF` = ^Ni WHERE `id` = ^Ni;', 2, $id);
	}
	
	
	private function addSections($pid, $arr) {
		foreach($arr as $val) {
			$id = $this->addSection($pid, $val['name']);
			if(!empty($val['subSect'])) {
				$this->addSections($id, $val['subSect']);
				$this->setSubSectTypeF($id);
			}
		}			
	}
	
	private function getSection(&$sections, &$num, $level, &$end) {
		$return = array();
		while($num != $end) {
			$numTabs = substr_count($sections[$num], "\t");
			if($numTabs == $level) {
				$return[] = array('name' => str_replace("\t", "", $section[$num]), 'subSect' => array());
				$num++;
				continue;
			} elseif($numTabs == $level+1) {
				$return[count($return)-1]['subSect'] = $this->getSection($sections, $num, $level+1, $end);
				continue;
			} elseif($numTabs < $level) {
				break;
			}	
		}
		return $return;		
	} 
	
	function add($tabList) {
		$sections = explode("\n", $tabList);
		$num = 0;
		$end = count($sections);
		$this->sectionsArr = $this->getSection($sections, $num, 0, $end);
		$this->addSections(0, $this->sectionsArr);		
	}
	
	function getData($id,$tab) {
		$ret=array();
		$typeF = 0;
		if($id != 0) {
		//значениe флага typeF для группы товаров  передается в массив return
		//выводятся только группы со значением флага 1
		
			$res = $this->db->query('SELECT `typeF` FROM `structure` WHERE `id` = ^Ni;', $id);
			if($res === null) 
				throw new StructureWException('id does\'t exist', StructureWException::ID_ERROR);	
			$typeF = $res;
		}
/*$n=0;
if (!$tab == '')	{
	$result=$this->db->query('SELECT `eid` FROM `type-elements` WHERE `tid` = ^Ni;', $id);
	
	foreach ($result as $value)	{
		$result2=$this->db->query('SELECT `eid` FROM `'.$tab.'` WHERE `eid` = ^Ni;', $value->eid);
		if($result2 > 0) $n++;
	}
	
if ($n>0) $typeF = 1;
else $typeF = 0;
}*/
$return = array();
//значение флага записывается в возвращаемый массив return
$return['this']['typeF'] = $typeF;		
// из таблицы считываем поля групп, для которых id является корневой группой pid
$return['sections'] = array();
switch ($tab){
	case 'elements':{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numElst` FROM `structure` WHERE `pid` = ^Ni AND `NumElst` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numElst);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numElst);		
			}
			}
		break;}
	case 'elemarch':{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `structure` WHERE `pid` = ^Ni AND `NumEl` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEl);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEl);		
			}
		}
		break;}
	case 'elemspec':{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEls` FROM `structure` WHERE `pid` = ^Ni AND `NumEls` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEls);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEls);		
			}
		}
		break;}	
		default :{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `structure` WHERE `pid` = ^Ni AND `numEl` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEl);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEl);		
			}
		}
		}
}
/*
if ($tab == 'elements') {
	$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEls` FROM `structure` WHERE `pid` = ^Ni AND `numEls` != \'0\' ORDER BY `name`;', $id);
	$resnumEl='s';
}
else {
	$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `structure` WHERE `pid` = ^Ni AND `numEl` != \'0\' ORDER BY `name`;', $id);
	$resnumEl='';
}


//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => "$res->numEl.$resnumEl");				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => "$res->numEl.$resnumEl");		
			}
		}*/
// изменяем значение поля numEl на значение k - количество товаров вендора 
return $return;			
	}	
	
function getDataIE($id,$tab) {
		$typeF = 0;
		if($id != 0) {
			$res = $this->db->query('SELECT `typeF` FROM `structure` WHERE `id` = ^Ni;', $id);
			if($res === null) 
				throw new StructureWException('id does\'t exist', StructureWException::ID_ERROR);	
			$typeF = $res;
		}
		$return = array();
		$return['this']['typeF'] = $typeF;		
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `structure` WHERE `pid` = ^Ni AND `numEl` != \'0\' ORDER BY `name`;', $id);
		$return['sections'] = array();
		switch ($tab){
	case 'elements':{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numElst` FROM `structure` WHERE `pid` = ^Ni AND `NumElst` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numElst);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numElst);		
			}
		}
		break;}
	case 'elemarch':{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `structure` WHERE `pid` = ^Ni AND `NumEl` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEl);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEl);		
			}
		}
		break;}
	case 'elemspec':{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEls` FROM `structure` WHERE `pid` = ^Ni AND `NumEls` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEls);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEls);		
			}
		}
		break;}	
		default :{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `structure` WHERE `pid` = ^Ni AND `numEl` != \'0\' ORDER BY `name`;', $id);
		//результат заносим в массив return	
		if($res !== null ) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEl);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEl);		
			}
		}
		}
}
		/*if($res !== null) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEl);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEl);		
			}
		}*/
		return $return;			
	}		
	
public function getPage($numpage){
			$res = array();
			if($numpage != 0) {
			$this->numpage=$numpage;
			$res = $this->db->query('SELECT * FROM `pages` WHERE `numpage` = ^Ni;', $this->numpage);
			if($res === null) 
				throw new StructureWException('numpage does\'t exist', StructureWException::ID_ERROR);	
			}
			$return['pages'] = array();
			if($res !== null) {
			//echo 'данные страницы загружены';echo '<br/>';
			if(!is_array($res)) {
				$return['pages'][] = array('numpage' => $res->numpage, 'namep' => $res->namep,
				'lozungp' => $res->lozungp, 'keywords' => $res->keywords, 'buttons' => $res->buttons,
				'hrefp' => $res->hrefp, 'typemenu' => $res->typemenu, 'hrefscripts' => $res->hrefscripts, 'hrefstyle' => $res->hrefstyle,
				'title' => $res->title, 'content' => $res->content, 'levelmenu' => $res->levelmenu,
				'idmenu' => $res->idmenu, 'hrefimage' => $res->hrefimage, 'list' => $res->list, 'list_href' => $res->list_href,
				'butthref' => $res->butthref, 'buttimg' => $res->buttimg, 'imgtext' => $res->imgtext, 'idnews' => $res->idnews);				
			} else {
				foreach($res as $val)
					$return['pages'][] = array('numpage' => $val->numpage, 'namep' => $val->namep,
					'lozungp' => $val->lozungp, 'keywords' => $val->keywords, 'buttons' => $val->buttons, 'hrefp' => $val->hrefp,
					'typemenu' => $val->typemenu, 'hrefscripts' => $val->hrefscripts, 'hrefstyle' => $val->hrefstyle,
					'title' => $val->title, 'content' => $val->content, 'levelmenu' => $val->levelmenu,
					'idmenu' => $val->idmenu, 'hrefimage' => $val->hrefimage, 'list' => $val->list,'list_href' => $val->list_href,
					'butthref' => $val->butthref, 'buttimg' => $val->buttimg, 'imgtext' => $val->imgtext, 'idnews' => $val->idnews);		
			}
		}
		//ElementsW::Showobjtype($return['pages'][0]);
		return $return;
			}

public function getnews($numnews) {
			$res1=array();
			if($numnews != 0) {
			$res1 = $this->db->query('SELECT * FROM `news` WHERE `idnews` = ^Ni;', $numnews);
			$res1->date = $this->db->query('SELECT DATE_FORMAT(`date`,"%m %Y") FROM `news` WHERE `idnews` = ^Ni;', $numnews);
			if($res1 === null) 
				throw new StructureWException('numnews does\'t exist', StructureWException::ID_ERROR);	
			}
			$return['news'] = array();
			if($res1 !== null) {
			if(!is_array($res1)) {
				$return['news'][] = array('name' => $res1->name,
				'text' => $res1->newstext, 'date' => $res1->date, 'vendor' => $res1->vendor,
				'group' => $res1->group, 'imgnews' => $res1->imgnews);				
			} else {
				foreach($res1 as $val)
					$return['news'][] = array('name' => $val->name,
					'text' => $val->newstext, 'date' => $val->date, 'vendor' => $val->vendor, 'group' => $val->group, 'imgnews' => $val->imgnews);		
			}
		}
		//ElementsW::Showobjtype($return['news'][0]);
		return $return;
			}			
			
public function getnews2($numnews,$ng) {
			if($numnews != 0) {
			$res1 = $this->db->query('SELECT * FROM `news` WHERE `idnews` = ^Ni && `group`=^Ni;', $numnews,$ng);
			$res1->date = $this->db->query('SELECT DATE_FORMAT(`date`,"%d %m %Y") FROM `news` WHERE `idnews` = ^Ni && `group`=^Ni;', $numnews,$ng);
			if($res1 === null) 
				throw new StructureWException('numnews does\'t exist', StructureWException::ID_ERROR);	
			}
			$return['news'] = array();
			if($res1 !== null) {
			if(!is_array($res)) {
				$return['news'][] = array('name' => $res1->name,
				'text' => $res1->newstext, 'date' => $res1->date, 'vendor' => $res1->vendor,
				'group' => $res1->group,'idnews' => $res1->idnews, 'imgnews' => $res1->imgnews, 'hrefnew' => $res1->hrefnew, 'numpagat' => $res1->numpagat);				
			} else {
				foreach($res1 as $val)
					$return['news'][] = array('name' => $val->name,
					'text' => $val->newstext, 'date' => $val->date, 'vendor' => $val->vendor, 'group' => $val->group, 'imgnews' => $val->imgnews, 'idnews' => $val->idnews);		
			}
		}
		//ElementsW::Showobjtype($return['news'][0]);
		return $return;
			}
}			
?>