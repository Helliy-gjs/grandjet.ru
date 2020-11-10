<?php
class Site extends Singleton {
	private $sitename='';
	private $siteid=1;
	private $db=null;
	private $siteadmin=array();
	private $sitetype=array();
	private $sitehosting=array();
	private $sitepage=array();
	private $sitearray=array();
	private $linkpages=null;
	private $sitelink=null;
	private $sitemaket;
	private $envirsite=array();
	private $startPage=1;
	private $siteowner;
	private $siteuser;
	private $tarif;
	private $claspath=array();
	private $tabsite;
	private $simlink=null;
	private $localhost = '';
	protected function __construct() {
		$this->db = Singleton::getInstance('DB');
	}
	
function create_css_classes(){
	$this->claspath['clas']=array('0'=>'logo','1'=>'container','3'=>'img','2'=>'main-banner','4'=>'button','5' => 'menu','6' => 'portfolio','7' => 'ready','8' => 'news','9' => 'section','10' => 'footer-sec','11' => 'home','12' => 'item','13' => 'img','14' => 'content','15' =>'main_footer','16'=>'main_footer','17' => 'footer','18' => 'wrapper',
 '19' => 'footmenu', '20' => 'top_line','21'=>'menuup','22'=>'adm','23'=>'user');
	$this->claspath['img']='./images/';
	$this->claspath['csv']='./';
	$this->claspath['js']='./js/';
	$this->claspath['lib']='./libs/';
	$this->claspath['css']='./css/';
	$this->claspath['font']='./font/';
	$this->localpath ='.';
}
	
function initbdF($domen,$np,$Pth, $mode=false){
	$this->siteuser=Singleton::getInstance('User');
	$this->create_css_classes();
	if (isset($domen)) $this->sitename=$domen;
	if (strstr($this->sitename,'www')) {
			$this->sitename=substr($this->sitename,4);
		}
	if ($this->sitename <> '') {
		//if($Pth['adm']['uid']==1)	$Pth['adm']['idm']=1;
	$res=$this->db->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`css`,`script`,`images`,`pages`, `news`,`element`,`structure`,`desc_site` FROM `allsites` WHERE `domen` = ^Ns;', $this->sitename);	
	$res1['css']=$this->db->query('SELECT * FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni AND `type`=^Ns;',intval($Pth['adm']['ids']),intval($Pth['adm']['idm']),'css');
	$res1['js']=$this->db->query('SELECT * FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni AND `type`=^Ns;',intval($Pth['adm']['ids']),intval($Pth['adm']['idm']),'js');
	if($res){
		$ret=explode('/',$res->domen);
		if(count($ret)>1) {
			//$res->domen='gjs.'.$ret[0];
			$res->simlink=$ret[1];	
			}
		$this->sitename = $res->domen;
		$this->siteid = $res->ids;
		$this->sitepage = $res->nmpage;
		$this->siteadmin = $res->uid;
		$desc=explode('|',$res->desc_site);
		$this->sitetype = array('nmp'=>$res->nmpage,'type'=>$res->types,'struc'=>$res->strucs,'app'=>$res->appoint,'GA'=>$desc[0],'YM'=>$desc[1],'https'=>$desc[2]);
		$mainpages=explode(';',$res->images);
		$this->envirsite = array('banmain'=>$mainpages[0],'logo'=>$mainpages[1],'css'=>$res->css,'scrjs'=>$res->script,'loaded'=>$res1);
		$this->tabsite=array('pages'=>$res->pages,'elem'=>$res->element,'str'=>$res->structure,'news'=>$res->news,'elemap'=>'elemap');
		$this->getCurrentPage($np);
		if($mode)$this->linkpages = $this->getPagelinks($np,$this->tabsite['pages'],'numpage');
		else $this->linkpages= null;
		if($mode)$this->sitelink=$this->getLinkSite($this->siteid);
		else $this->sitelink=null;
		$this->sitearray = $this->sitepage->readypagearr($this->sitepage->MainAr,$this->claspath,$this->linkpages,$this->OwnerSite(),Utils::getConfig(),$this->tabsite);
		if(!$mode)unset($this->sitearray['link'] );
		$this->sitemaket = $this->allmaketsite($this->siteid,$this->sitearray['idmen'][0].'-'.$np);
		if(isset($res->simlink))$this->simlink = $res->simlink;
		
		return $this;
	}	
	//else echo 'Сайт <'.$domen.'> в базе данных не найден';
	}
	return false;
	}
	
	function getEnvirSite(){
		return $this->envirsite;
	}
	
	function loadenviroment($clas,$source = 'img'){
		$envirSite = $this->getEnvirSite();
		$slsw='';
		$sgsw='';
		$lsw='';
		$gsw='';
if(isset($envirSite['loaded'])){
	if(!empty($envirSite['loaded']['css'])){
	if(is_array($envirSite['loaded']['css'])){
		for($i=0;$i<count( $envirSite['loaded']['css']);$i++){
			$scrjs[0][$i] = $envirSite['loaded']['css'][$i]->scripts;
			$scrjs[1][$i] = $envirSite['loaded']['css'][$i]->flag;
			$scrjs[2][$i] = $envirSite['loaded']['css'][$i]->Maket;
			if($envirSite['loaded']['css'][$i]->needs === 'us;nbl')$scrjs[3][$i] =1;
			else $scrjs[3][$i] =0;
			if($scrjs[3][$i]== 1){
			if(!strstr($scrjs[0][$i],'|')){
			if($scrjs[1][$i] === 'f' && $scrjs[0][$i]!= ''){
				
					echo '<link rel="stylesheet" href="'.$this->localpath.'/'.$clas[$source].'/'.$scrjs[0][$i].'.css" ></script>';
					$slsw.=$scrjs[1][$i].'|'.$scrjs[2][$i];
			}	
			elseif($scrjs[1][$i] === 'h' && $scrjs[0][$i]!= ''){
				if($scrjs[3][$i]== 1){
				echo '<link rel="stylesheet" href="'.$scrjs[0][$i].'"></script>';
				$sgsw.=$scrjs[1][$i].'|'.$scrjs[2][$i];
				}
			}
		}
		else{
			$arr=explode('|',$scrjs[0][$i]);
			//$this->InfoEssence($arr);
			foreach($arr as $val){
				if($scrjs[1][$i] === 'f' && $val!= ''){
				echo '<link rel="stylesheet" href="'.$this->localpath.'/'.$clas[$source].'/'.$val.'.css" ></script>';
				}
			elseif($scrjs[1][$i] === 'h' && $val!= '') {
				echo '<link rel="stylesheet" href="'.$val.'"></link>';
					}
				$slsw.=$scrjs[1][$i].'|'.$val;	
				}
			}
		}
	}
	}
	else {
		$scrjs[0] = $envirSite['loaded']['css']->scripts;
			$scrjs[1]= $envirSite['loaded']['css']->flag;
			$scrjs[2] = $envirSite['loaded']['css']->Maket;
			if($envirSite['loaded']['css']->needs === 'us;nbl')$scrjs[3] =1;
			else $scrjs[3] =0;
				
				
				if($scrjs[3]== 1){
					if(!strstr($scrjs[0],'|')){
						if($scrjs[1] === 'f' && $scrjs[0]!= ''){
							echo '<link rel="stylesheet" href="'.$this->localpath.'/'.$clas[$source].'/'.$scrjs[0].'.css" ></link>';
							$slsw.=$scrjs[1].'|'.$scrjs[2];
						}
						elseif($scrjs[1] === 'h' && $scrjs[0]!= ''){
							echo '<link rel="stylesheet" href="'.$scrjs[0].'"></link>';	
							$sgsw.=$scrjs[1].'|'.$scrjs[2];
						}
					}
					else {
						$arr=explode('|',$scrjs[0]);
						if($scrjs[1] === 'f' && $scrjs[0]!= ''){
							foreach($arr as $val)echo '<link rel="stylesheet" href="'.$this->localpath.'/'.$clas['img'].'/'.$val.'.css" ></link>';
							$slsw.=$scrjs[1].'|'.$val;
						}
						elseif($scrjs[1] === 'h' && $scrjs[0]!= '') {
							foreach($arr as $val)echo '<link rel="stylesheet" href="'.$val.'"></link>';
							$sgsw.=$scrjs[1].'|'.$val;
						}
					}
					
				}
			}	
		}		
	

	unset($scrjs);
	$lsw='';
	$gsw='';
	//if($source === 'lib')	$this->envirsite['scrjs']='libs';
	//debug($envirSite);
	if(!empty($envirSite['loaded']['js'])){
	if(is_array($envirSite['loaded']['js'])){
		for($i=0;$i<count( $envirSite['loaded']['js']);$i++){
			$scrjs[0][$i] = $envirSite['loaded']['js'][$i]->scripts;
			$scrjs[1][$i] = $envirSite['loaded']['js'][$i]->flag;
			$scrjs[2][$i] = $envirSite['loaded']['js'][$i]->Maket;
			if($envirSite['loaded']['js'][$i]->needs === 'us;nbl')$scrjs[3][$i] =1;
			else $scrjs[3][$i] =0;
			if($scrjs[3][$i]== 1){
				if(!strstr($scrjs[0][$i],'|')){
					if($scrjs[1][$i] === 'f' && $scrjs[0][$i]!= ''){
						if(file_exists($this->localpath.'/'.$this->envirsite['scrjs'].'/'.$scrjs[0][$i].'.js')){
							echo '<script  src="'.$this->localpath.'/'.$this->envirsite['scrjs'].'/'.$scrjs[0][$i].'.js" type=text/javascript ></script>';
							$lsw.=$scrjs[1][$i].'|'.$scrjs[2][$i];
						}
						else echo $this->localpath.'/'.$this->envirsite['scrjs'].'/'.$scrjs[0][$i].'.js';
					}	
					elseif($scrjs[1][$i] === 'h'&& $scrjs[0][$i]!= ''){
						echo '<script type=text/javascript src="'.$scrjs[0][$i].'"></script>';
						$gsw.=$scrjs[1][$i].'|'.$scrjs[2][$i];
					}
				}
				else {
					$arr=explode('|',$scrjs[0][$i]);
					foreach($arr as $val){
						if($scrjs[1][$i] === 'f' && $val!= ''){
							if(file_exists($this->localpath.'/'.$this->envirsite['scrjs'].'/'.$val.'.js')){
								echo '<link rel="stylesheet" href="'.$this->localpath.'/'.$this->envirsite['scrjs'].'/'.$val.'.js" ></script>';
								$slsw.=$scrjs[1][$i].'|'.$val;
							}
							else echo $this->localpath.'/'.$this->envirsite['scrjs'].'/'.$val.'.js';
						}
						elseif($scrjs[1][$i] === 'h' && $val!= '') {
							echo '<script type=text/javascript src="'.$scrjs[0][$i].'"></script>';
							$glsw.=$scrjs[1][$i].'|'.$val;
						}
					}
				}
			}
		}
	}
	else {
		$scrjs[0] = $envirSite['loaded']['js']->scripts;
		$scrjs[1] = $envirSite['loaded']['js']->flag;
		$scrjs[2] = $envirSite['loaded']['js']->Maket;
		if($envirSite['loaded']['js']->needs === 'us;nbl')$scrjs[3] =1;
		else $scrjs[3] =0;
		
		$gsw.='|'.$scrjs[2];
		if($scrjs[3]== 1){
			if($scrjs[1] === 'f'&& $scrjs[0]!= ''){
				if(file_exists($this->localpath.'/'.$this->envirsite['scrjs'].'/'.$scrjs[0].'.js')){
					echo '<script type=text/javascript src="'.$this->localpath.'/'.$this->envirsite['scrjs'].'/'.$scrjs[0].'.js" ></script>';
					$lsw.=$scrjs[1].'|'.$scrjs[2];
				}
				else echo $this->localpath.'/'.$this->envirsite['scrjs'].'/'.$scrjs[0].'.js';
			}	
			elseif($scrjs[1] === 'h'&& $scrjs[0]!= ''){
				echo '<script type=text/javascript src="'.$scrjs[0].'"></script>';
				$gsw.=$scrjs[1].'|'.$scrjs[2];
				}	
			}
		}
	}
}
	return array($slsw,$sgsw,$lsw,$gsw);
}

	
	function getLinkSite($siteid){
		$return = $this->linksite=$this->getPagelinks($siteid,'allsites','ids');
		
		return $return;
	}
	
	public function OwnerSite(){
		$this->siteowner=$this->siteuser->idUserF($this->siteadmin);
		$this->siteowner->ids=$this->siteid;
		$this->siteowner->start=$this->StartPage();
		if($this->siteowner->level>0){
		$hosting_params=$this->siteowner->hosting;
		$this->sitehosting=$hosting_params;
		$social_link=$this->siteowner->social;
		$code_host=0;
		foreach($hosting_params as $val)if($val<>'ny')$code_host++;
		$this->tarif=9-$code_host;
	}
	$this->siteowner->admin='Admin';
	return $this->siteowner;
	}
	
	public function getOwnerSite(){
		return $this->OwnerSite();
	}
	
	private function StartPage (){
		$this->startpage=$this->siteuser->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$this->sitename,$this->tabsite['pages']);
	}
	
	public function getstartpage(){
		return $this->startpage;
	}
	public function getSiteProp(){
		if($this->initbdF($_SERVER['HTTP_HOST'])){
			$arrs=array($this->siteid ,$this->sitename ,$this->siteadmin,$this->type ,$this->envirsite);
			return $arrs;
		}
		else return null;
	}
	
	function getCurrentPage($np){
		return $this->sitepage = new Page($np,$this->tabsite);
	}
	
	function getCurrentMaket(){
		return $this->sitemaket = new Maket($idm,$this->tabsite,$this->initbdF->siteuser->initbdF($_SERVER['HTTP_HOST']));
	}
	
	function InfoEssence($ess) {
	//Передан массив
	if(is_array($ess)){
		$var_arr = '<pre>'.print_r($ess, true).'</pre>';
		var_dump($var_arr);
	}
    //Передан объект
    if(is_object($ess)){
        $class = get_class($ess); //класс объекта
        $obj = $ess;
        $vars_obj = '<pre>' . print_r(get_object_vars($obj), true) . '</pre>';
		var_dump($vars_obj);
	//Передан класс
    } else {
        $class = $ess;
        $vars_obj = null;
    }  
}

function allmaketsite($ids,$maket='Maket'){
	
		if ($ids > 0)	
			if($maket<>'')$res = $this->db->query("SELECT * FROM `allmakets` WHERE `Maket`=^Ns AND `ids`=^Ni;",$maket,$ids);
			else $res = $this->db->query("SELECT * FROM `allmakets` WHERE `ids`=^Ni;",$maket,$ids);
		if($res !== null) {
		if(!is_array($res)) { 
	
		$return[]=array($res->id,$res->Maket,$res->styles,$res->numparams,$res->fonts,$res->video,$res->effects,$res->scripts,$res->desc,$res->ids);
		}
		else {
			foreach($res as $val) $return[]=array($val->id,$val->Maket,$val->styles,$val->fonts,$val->numparams,$val->video,$val->effects,$val->scripts,$val->desc,$val->ids);
		}
		$this->sitemaket = $return;
}
else {echo '<info class="hidno">макет не найден</info>';return false;}
return $return;
}

function getPagelinks($numpage,$t='pages',$f='numpage'){

	$return=array();
	$res2=$this->db->query("SELECT * FROM namparams WHERE tab=^Ns;",$t);
		
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$arrname=explode('|',$arrnm);
	$arrtype=explode('|',$arrtp);
	$lpg=User::getscountab($t,$f, 'f');//последняя страница в pages	
	$res1=$this->db->query('SELECT * FROM  `'.$t.'` WHERE `'.$f.'`=^Ni;',$numpage);
	$l=0;
	if(isset($arrdlm)) {
		$arrdelem=explode(',',$arrdlm);
	}
	else {
	for ($i=0;$i<count($array);$i++)  {
		$arrdelem[$i][0]='|';
		$arrdelem[$i][1]=';';
		$arrdelem[$i]=$arrdelem[$i][0].$arrdelem[$i][1];
		}
	}
if($res1){
	foreach($res1 as $key=>$val){	
	if($arrtype[$l] == 'check' && $val == '') 	{
		if($f=='numpage' && $t='pages'){
			$array[$l]='bl;mn;bt;ft;hd;bf;sw';
			$arraykey[$key]='bl;mn;bt;ft;hd;bf;sw';
		}
	}
	elseif($val == '') {
	$array[$l]=$arrdelem[$l];
	$arraykey[$key]=$arrdelem[$l];
	}
	else {
	$array[$l]=$val;
	$arraykey[$key]=$val;
	}
	$l++;
	}
}	
elseif(!isset($arraykey))	$arraykey[0]='';
	$k=0;
	foreach ($arraykey as $key=>$value){
		if (!isset($arrdelem[$k][0])) {
			$return1[]=$k;
			}
		if(isset($arrdelem[$k][0]) && !isset($arrdelem[$k][1])) {
			if (strstr($value,$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$value);
			else $arr1= $value;
			if(is_array($arr1)){
				$m1=0;
				foreach($arr1 as $valu){
					$return1[$k][]=$k.$m1;
					$m1++;
				}
			}
			else $return1[$k][]=$k.$m1;
	}
	else {
		if(isset($arrdelem[$k][0])) {
		if (strstr($value,$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$value);
		}
		elseif(isset($arrdelem[$k][1])) {
		if (strstr($value,$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$value);
		}
		else $arr1= @ $value;
		if(isset($arrdelem[$k][1])) {	
			for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		//}	
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
			$return1[$k][$m][]=$k.'0'.$m.$j;
			
						}
					}
				}
			}
		$k++;
		}
	return $return1;
}	

}
?>