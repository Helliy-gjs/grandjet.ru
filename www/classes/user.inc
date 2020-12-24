<?php
//Объект пользователь
class User extends Singleton {
	
	const GUEST = 0;
	const USER = 1;
	const CLIENT = 2;
	const EDIT_USER = 3;
	const MANAGER = 4;
	const LOCADM = 5;
	const ADMIN = 6;
	const GENERALMANAGER = 6;
	const PRODUCTMANAGER = 5;
	const ANALITICMANAGER = 4;
	const CONTENTMANAGER = 3;
	const SEOMANAGER = 2;
	const DESIGNMANAGER =1;
	const PAYCLIENT = 0;
	
	const LOGIN_SUCCESS = 1;
	const INCORRECT_LOGIN_PASS = -1;
	const NONE = 0;
	
	private $id = 0;
	private $uid = 0;
	private $level = -1;
	private $login = '';
	private $loginM = '';
	private $ms = 0;
	private $email = '';
	private $balans = 0;
	private $db = null;
	private $key = 'SecKey0x0777';
	private $numErrors = '';
	private $customerid=0;
	private $source,$dest;
	private $init=array();
	private $status;
	private $domen;
	private $graphp='';
	
	protected function __construct() {
		$this->db = Singleton::getInstance('DB');
	}
public function namesitepage($domen){
	if (isset($domen)) $this->domen=$domen;
		if (!strstr($this->domen,'www')) {
			$pgs=substr($this->domen,0,3).'.php';
		}
	else {
	 $pgs=substr(strstr($this->domen,'www'),4,3).'.php';
	 }
	 return $pgs;
}

public function getlookforfields($for1,$for2,$table) {
//$res = array();
//echo '----';
$res=$this->db->query('SELECT `numpage`,`title`,`site` FROM `'.$table.'`  WHERE `site` = ^Ns and `title` = ^Ns;', $for1, $for2);
//echo $res->numpage;
if (isset($res->numpage)){return $res->numpage;}
else  {return false;}
}

function readyplace($place){
	if (realpath($place)) $this->place=realpath($place);
	else $this->place='/';
	$dfs=disk_free_space($this->place)/1000000;
	$tds=disk_total_space($this->place)/1000000;
	if ($dfs>0) {
		//echo '<br>Общий размер каталога (MB)'.$tds/1000000;
		//echo '<br>Свободное место (MB)'.$dfs;
		return true;}
	else {
		echo '<br>Недостаточно дискового пространства. Свободно '.$dfs.' Всего '.$tds; 
		return false;} 
}
	function copydistfiles($source, $dest,$upd='',$choose=''){
		chdir($source);
		//echo 'запущена copydistfiles';
		//echo '<br>Копируем '.$choose.' из '.$source.'<br>в '.$dest.'<br>';
		if (isset($source)) $this->source=$source;
		if (isset($dest)) $this->dest=$dest;
		$i=$j=0;
		$erorrfiles='Не записаны файлы';
		//echo $choose; 
		if($upd<>'update' && $choose=='')$FD=array(0=>'ADDsite.php',1=>'map.csv',2=>'index.php',3=>'start.php',4=>'info.php',5=>'logo.png',6=>'logo.jpg',7=>'logo.gif',8=>'banmain.jpg',9=>'banmain.png',10=>'DBinst.php',11=>'favicongjs.png',12=>'img.php',13=>'detail.php',14=>'upgrade.php',15=>'loader2019.php',16=>'robots.txt',17=>'sitemap.xml',18=>'metrica.php',19=>'update.php',20=>'loadstyles.php',21=>'registrator.php',22=>'functions.php',23=>'CREATEMPTYBD.php');
		elseif($choose=='' && $upd=='update')$FD=array(0=>'favicongjs.png',1=>'img.php',2=>'index.php',3=>'detail.php',4=>'DBinst.php',5=>'loader2019.php',6=>'robots.txt',7=>'sitemap.xml',8=>'metrica.php',9=>'update.php',10=>'loadstyles.php',11=>'registrator.php',12=>'ADDsite.php',13=>'upgrade.php',14=>'functions.php');
		elseif(strstr($choose,','))$FD=explode(',',$choose);
		else $FD[0]=$choose;
		if( $upd=='update'){ 
			unset($FD[2]);
			unset($FD[4]);
			unset($FD[5]);
			unset($FD[12]);
			unset($FD[11]);
		}
		//if($_SERVER['HTTP_HOST'] === 'deltar.ru') unset($FD[2]);
		foreach ($FD as $val){
			$j++;
			if (!file_exists($this->dest.'/'.$val) || $upd<>'') {
			//echo $val.' is no OK<br>';
			//echo 'Копируем '.$val.' из '.$source.'  в  '.$dest.'<br>';	
				if (copy($this->source.'/'.$val, $this->dest.'/'.$val)) {
				//show::infosh($val);//echo $val.' copies OK<br>';
				$i++;
				}
			}
			elseif($upd=='upgrade') {
				if (copy($this->source.'/'.$val, $this->dest.'/'.$val)) {
				//show::infosh($val);//echo $val.' copies OK<br>';
				$i++;
			}
			else	//echo 'не скопировано '.$this->source.'/'.$val.','.$this->dest.'/'.$val.'<br>';
				$erorrfiles.=$val.' ';
			}
		}
	if ($i == $j) {
		//show::infosh('all files were loaded success in'.$dest);
		return true;
	}
		else  {
			//show::infosh($erorrfiles); 
			return $erorrfiles;
			}
	}

	function checkdistfiles($domen){
	if (isset($domen)) $this->domen=$domen;
	//проверка файлов
	$i=$j=0;
	$erorrfiles='Не найдены файлы ';
	
	$FD=array(0=>'ADDsite.php',16=>'DBinst.php',17=>'favicongjs.png',18=>'img.php',19=>'index.php',20=>'detail.php',22=>'loader2019.php',23=>'robots.txt',24=>'sitemap.xml',25=>'metrica.php',26=>'update.php');
	if(chdir($domen)){
	foreach ($FD as $val){
		$file=$val;
		$j++;
		$F=fopen($file,"r");
		if ($F ) $i++; //echo $file.' is OK<br>'; 
		else $erorrfiles.=$file.'/'. fileowner($file).'|';
		}
		if ($i == $j) return true; 
		else  {
			show::infosh($erorrfiles); 
			return false;
			}
	}
	}
	
	function getstylesfiles($clas,$mainmaket,$m,$min=''){
		//print_r($mainmaket[$m]);
		if(!isset($mainmaket[$m]))return false;
		if (strstr($mainmaket[$m],';')) {
			$MMP=explode(';',$mainmaket[$m]);
			 
			foreach($MMP as $val)  {
					if($val)$Styles[]=$clas['img'].$val.$min.'.css';
				}
			}
		elseif($mainmaket[$m]<>'') $Styles[$m]=$clas['img'].$mainmaket[$m].$min.'.css';
		else $Styles='';
		//show::infosh($Styles);	
		return $Styles;
	}
	
	function checkdistdir($source=''){
	//проверка файлов
	$i=$j=0;
	chdir($source);
	$erorrfiles='Не найдены директории ';
	$DD= array(1=>"ajax",2=>"auth",3=>"classes",4=>"detail",5=>"fonts",6=>"images",7=>"recovery",8=>"registration",9=>"scripts",10=>"settings",11=>"market_dist",12=>"whois",13=>"libs");	
	foreach ($DD as $val){
		$file=$val;
		$j++;
		getcwd();
		if (chdir($source.'/'.$file)) {
			chdir('../');
			$i++; 
		}
		else $erorrfiles.=$file.' ';
		}
		if ($i == $j) return true; 
		else return $erorrfiles;
	}
	
	function recurse_copy($src,$dst) {
	if ($this->readyplace('/')){
	$dir = opendir($src);
	@mkdir($dst);
	while(false != ( $file = readdir($dir)) ) {
		if (( $file != '.' ) && ( $file != '..' )) {
		if ( is_dir($src . '/' . $file) ) {
		echo 'Копируем директорию '.$src . '/' . $file.'<br>';	
		$this->recurse_copy($src . '/' . $file,$dst . '/' . $file);
		}
		else {
			echo 'Копируем файл '.$src . '/' . $file.'<br>';	
			$res=copy($src . '/' . $file,$dst . '/' . $file);
			//show::infosh($file);
			//if($res) echo ' success<br>';
			//else echo ' unlucky<br>';
		}
		if(!res){echo 'Копирпование рекурсивное не выполнено';die;}
		}
	}
	closedir($dir);
	return $res;
	}
	return false;
	}
	
	public function copydirfiles($soucer,$dest){
	if (isset($soucer)) $this->soucer=$soucer;
	if (isset($dest)) $this->dest=$dest;
	//echo $this->soucer.'->'.$this->dest.'<br>';
	if($this->checkdistdir($this->soucer)){
			$i=$j=0;
			$erorrfiles='Не найдены директории ';
			$DD= array(1=>"ajax",2=>"auth",3=>"classes",4=>"detail",5=>"fonts",6=>"images",7=>"recovery",8=>"registration",9=>"scripts",10=>"settings",11=>"market_dist",12=>"whois",13=>"libs");	
			foreach ($DD as $val){
				//echo 'Копируем  директорию '.$this->soucer.'/'.$val.'<br>';
				//echo 'В директорию '.$this->dest.'/'.$val.'<br>';
				//if ($this->readyplace($val)){
				$file=$val;
				$j++;
				$this->recurse_copy($this->soucer.'/'.$file,$this->dest.'/'.$file);
				//}
				//else exit('Недостаточно дискового пространства ');
		}
		show::infosh('all directories were loaded  success'.$this->dest);
	}
}

	public function upgradesite($domen,$upd=false,$soucer=HOST_DIST,$choose=''){
		if($upd){
		//echo 'архивируем сайт '.$domen.' в папку archive '.HOST_DIST.'<br>';	
		$res=$this->archdatesite($choose);
		//echo '====архивирование выполнено, переходим к обновлению из '.HOST_DIST.' <br> в '.$domen;
		$result=$this->copyalldatesite($domen,HOST_DIST);
		return $result;
			}
		else return false;
	}

	public function updatesite($domen,$upd=false,$soucer=HOST_DIST,$choose=''){
		if($upd){
		//echo 'архивируем сайт '.$domen.' в папку archive '.HOST_DIST.'<br>';	
		$res=$this->archdatesite($choose);
		//echo '====архивирование выполнено, переходим к обновлению из '.HOST_DIST.' <br> в '.$domen;
		$result=$this->copydatesite($domen,HOST_DIST);
		return $result;
			}
		else return false;
	}

	public function updatfile($dest,$file,$soucer=HOST_DIST){
		//echo 'запущена updatfile';
		$result=$this->archdatesite($file);
		if($result) $result=$this->copydistfiles($soucer, $dest,'update',$file);
		if($result) return true;
		else return false;
	}

	public function copyalldatesite($domen,$soucer=HOST_DIST){
		if ($this->checkdistfiles($soucer)) {
		//echo 'Копирование....'.$soucer.' -> '.$domen.'<br>';
		$result=$this->copydistfiles($soucer,$domen,'upgrade');
		if($result){
		 $result=$this->copydirfiles($soucer,$domen);
		if($result) return true;
	}
	}
	return false;
}

	public function copydatesite($domen,$soucer=HOST_DIST){
		if ($this->checkdistfiles($soucer)) {
		//echo 'Копирование....'.$soucer.' -> '.$domen.'<br>';
		$result=$this->copydistfiles($soucer,$domen,'update');
		if($result){
		 $result=$this->copydirfiles($soucer,$domen);
		if($result) return true;
	}
	}
	return false;
}
	
	public function archdatesite($choose=''){
		echo HOST_ARCH. ' <br>';
		echo HOST_ROOT. ' архивируем... <br>';

		if (!chdir(HOST_ARCH)) {
			mkdir(HOST_ARCH,0777);
			echo 'Создана директория '.HOST_ARCH;
			
			}
		else echo '<br>Директория archive exist';	
		if (!chdir(HOST_ARCH.'/'.$_SERVER['HTTP_HOST'])){
			mkdir(HOST_ARCH.'/'.$_SERVER['HTTP_HOST'],0777);
			echo '<br>Создана в archive директория '.$_SERVER['HTTP_HOST'];
		}
		else {
			echo '<br>Директория archive/'.$_SERVER['HTTP_HOST'].' exist';	
		}
		echo '<br>Копируем в архивную папку ('.HOST_ARCH.'/'.$_SERVER['HTTP_HOST'].') домена '.HOST_ROOT.'<br>';
		
		if($choose===''){
			$result=$this->copydistfiles(HOST_ROOT,HOST_ARCH.'/'.$_SERVER['HTTP_HOST'],'update');
		if($result){
		 $result=$this->copydirfiles(HOST_ROOT,HOST_ARCH.'/'.$_SERVER['HTTP_HOST']);
		return $result;
	}
	}	
	else $result=$this->copydistfiles(HOST_ROOT, HOST_ARCH.'/'.$_SERVER['HTTP_HOST'],'update',$choose);
	return $result;
	}
	
	public function recoversite($domen,$choose=''){
		if($choose==''){
			$result=$this->copydistfiles(HOST_ARCH.'/'.$_SERVER['HTTP_HOST'],HOST_ROOT,'update');
		if($result){
		 $result=$this->copydirfiles(HOST_ARCH.'/'.$_SERVER['HTTP_HOST'],HOST_ROOT);
		return $result;
			//$result=$this->copydatesite(HOST_ROOT,HOST_ARCH.'/'.$domen);
		}
	}
	else $result=$this->copydistfiles(HOST_ARCH.'/'.$_SERVER['HTTP_HOST'],HOST_ROOT,'recover',$choose);
		return $result;
	}
	
	public function createsitedir($domen,$soucer=HOST_ROOT){
	//echo $domen;
	if($soucer==HOST_ROOT)$name_domen=explode('.',$domen);
	else $name_domen[0]=$domen;
	$soucer1=HOST_ROOT.'/';
	//$soucer=HOST_ROOT;
	if($soucer==HOST_DIST) $soucer1='';
	$newdir='no';
	//echo 	$name_domen[0].'---------------------'.$soucer1.$name_domen[0].'<br>';
	if ($this->readyplace('/')){
	if (mkdir($name_domen[0],0777)){
		echo 'Создана директория '.$soucer1.$name_domen[0];
		$newdir='yes';
		}
	elseif (chdir($name_domen[0])){ 
	//echo '<div class="info"> Директория уже существует <br>'.getcwd().'</div>';
	if (!$this->checkdistfiles($soucer1.$name_domen[0])) {
		//echo 'Копирование1....<br>';
		$result=$this->copydistfiles($soucer,$soucer1.$name_domen[0]);
		if($result){
		 $result=$this->copydirfiles($soucer,$soucer1.$name_domen[0]);
			}
		}
	}
	else exit('Не удалось создать директорию '.$name_domen[0]);
	if ($newdir == 'yes'){
	//echo '<br>Копирование2....<br>';
	$result=$this->copydistfiles($soucer,$soucer1.'/'.$name_domen[0]);
	if($result){
		$result=$this->copydirfiles($soucer,$soucer1.'/'.$name_domen[0]);
	}
	return $result;
	}
}
else {
	show::infosh('Извините. Не хватает дискового пространства.');	
	return 0;}
}

	private function str2hex($str) {
		return bin2hex($str);
	}

	private function hex2str($hex) {
		return pack("H*", $hex);
	}

	private function encode($str, $key) { 
		$len = strlen($str);
		$klen = strlen($key);
		$code = '';
		$tmp = 0;
		for($i = 0; $i < $len; $i++) {
			$tmp = ord($str{$i}) + 71 * ord($key{$i % $klen}) % 121;
			$code .= $this->str2hex(pack("c*", $tmp));
		}
		return $code;
	}

	private function decode($str, $key) {
		$len = strlen($str);
		$klen = strlen($key);
		$tmp = 0;
		$code = '';
		$j = 0;
		for($i = 0; $i < $len; $i++) {
			$tmp = ord($this->hex2str($str{$i++}.$str{$i})) - 71 * ord($key{($i - ++$j) % $klen}) % 121;
			$code .= chr($tmp);
		}
		return $code;
	}

	private function setCoo($id, $login, $pass) {
		$time = time();
		$tkey = md5(date('Y-m-dH:i:s', $time));
		$passLogin = md5($pass.date('Y-m-dH:i:s', $time)).$this->encode($login, $tkey);
		$crc = md5($passLogin.$this->key);
		setcookie('hash', $passLogin.$crc.$tkey, time() + 172800, '/');
		$this->db->query('UPDATE `users` SET `time` = ^Ni WHERE `id` = ^Ni;', $time, $id);
	}
	
	private function setCoo_main($id,$mass) {
		$time = time();
		$tkey = md5(date('Y-m-dH:i:s', $time));
		$passLogin = md5($mass[1].date('Y-m-dH:i:s', $time)).$this->encode($mass[0], $tkey);
		$crc = md5($passLogin.$this->key);
		//setcookie('hash', $passLogin.$crc.$tkey, time() + 172800, '/');
		//$this->db->query('UPDATE `users` SET `time` = ^Ni WHERE `id` = ^Ni;', $time, $id);
		$this->init['hash']=$passLogin.$crc.$tkey;
		return $this->init;
	}
	
	function getallpages($tab){
		$db=Singleton::getInstance('DB');
		$site=$_SERVER['HTTP_HOST'];
		$d="SELECT `numpage`, `namep` FROM $tab WHERE `site`=^Ns;";
		$res=$db->query($d,$site);
		if (count($res) >1) {
		$l=0;	
		//while ($element =each($res)) {
		foreach($res as $val){
			$result['num'][$l]=$val['value']->numpage;
			if (strstr($val['value']->namep,'|')) {
				$NmPg=explode('|',$val['value']->namep);
				$result['nam'][$l]=$result['num'][$l].' '.substr($NmPg[1],0,15);
				}
			else  $result['nam'][$l]=$val['value']->numpage.' '.substr($val['value']->namep,0,15);
			if ($result['nam'][$l] == '') $result['nam'][$l]='страница '.$val['value']->numpage;
			$l++;
		}	
}
	else $result[0]=$res;
	return $result;
		
	}
	
	public static function getscountab($tab,$key,$mode){
		$db = Singleton::getInstance('DB');
		$order = ' ORDER BY ';
		$order .= '`numpage`';
		$order .= ' DESC ';
		//print_r($Site);
		if ($key <>''&& $mode ==='f') {
			$d="SELECT `$key` FROM `$tab` ORDER BY $key DESC";
			$res=$db->query($d);
			
		}
		//else { 
		//if ($tab == 'pages') $d='SELECT * FROM `pages` WHERE `site`=^Ns;,'.$Site->domen;
		elseif($mode == 't' && strstr($tab,'pages'))  {
			//$Site=$user->initbdF($_SERVER['HTTP_HOST']);
			$d="SELECT `$key` FROM `$tab` WHERE `$key`=^Ns $order;";
			//echo 'зашли '.$d.','.$_SERVER['HTTP_HOST'];
			$res=$db->query($d,$_SERVER['HTTP_HOST']);
			//print_r($res);
			$key='numpage';
			}
		elseif($mode == 't' && strstr($tab,'map'))  {
			$site=$db->initbd($_SERVER['HTTP_HOST'],$db);
			$d="SELECT `$key` FROM `$tab` WHERE `domen`=^Ns;";
			//echo 'зашли '.$d.','.$site->ids;
			$res=$db->query($d,$site->domen);
			//if($tab=='mapsites')print_r(count($res));
			//$key='numpage';
			}	
		else {
			$d="SELECT * FROM `$tab` ";
			$mode='c';
			$res=$db->query($d);
			
			}
//echo '<br>'.$d.','.$GLOBALS['Site']->domen;
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

	
	private function setGuestCoo() {
		setcookie('guest', 1, time() + 172800, '/');	
	}
	
	function guestEnter() {
		$this->user_exit();
		$this->setGuestCoo();
	}
	
	private function parseHash_main($hash){
		$resultArr = array();
		$passMain = substr($hash, 0, strlen($hash)-64);
		$crc = substr($hash, -64, 32);
		if(md5($passLogin.$this->key) == $crc) {
			$resultArr['crcCheck'] = true;
			$resultArr['pass'] = substr($passMain, 0, 32);
			$resultArr['login'] = substr($passMain, -(strlen($passMain)-32));
			$resultArr['tkey'] = substr($hash, -32, 32);
		} else {
			$resultArr['crcCheck'] = false;
		}
		return $resultArr;
		
	}
	
	private function parseHash($hash) {
		$resultArr = array();
		$passLogin = substr($hash, 0, strlen($hash)-64);
		$crc = substr($hash, -64, 32);
		if(md5($passLogin.$this->key) == $crc) {
			$resultArr['crcCheck'] = true;
			$resultArr['pass'] = substr($passLogin, 0, 32);
			$resultArr['login'] = substr($passLogin, -(strlen($passLogin)-32));
			$resultArr['tkey'] = substr($hash, -32, 32);
		} else {
			$resultArr['crcCheck'] = false;
		}
		return $resultArr;
	}

	function check_main($init_data,$domen){
		//$hashArr = $this->parseHash_Main($this->setCoo_main($id,$mass));
		//if(!$hashArr['crcCheck']) return;
		//$loginM = $this->decode($hashArr['login'], $hashArr['tkey']);
		$res = $this->db->query('SELECT `logad`,`passwad` FROM `allsites` WHERE `domen` = ^Ns AND `logad` = ^Ns;',$domen, $init_data[0]);
		//if($hashArr['pass'] == md5($res->passwad.date('Y-m-dH:i:s', $res->time))) {
		//if($init_data[1]==$this->decode($res->passwad,$this->key)){
		//print_r($res);
		if($init_data[1]==$res->passwad){
			return true;
		}
		else return false;
	}
	
	function check($sum=0) {
		//echo 'куки ';print_r($_COOKIE);
		if(isset($_COOKIE['hash'])) {
			$hashArr = $this->parseHash($_COOKIE['hash']);
			if(!$hashArr['crcCheck']) return;
			$login = $this->decode($hashArr['login'], $hashArr['tkey']);
			$res = $this->db->query('SELECT `id`, `pass`, `time`, `level`, `ms`, `email`, `customerid`, `siid` FROM `users` WHERE `login` = ^Ns;', $login);
			if($res === null) return;
			if($hashArr['pass'] == md5($res->pass.date('Y-m-dH:i:s', $res->time))) {
				$this->setCoo($res->id, $login, $res->pass);
				$this->level = $res->level;
				$this->ms = $res->ms;
				$this->email = $res->email;
				$this->login = $login;
				$this->id = $res->id;
				$this->siid = $res->siid;
				$this->customerid = $res->customerid;
				$this->balans=$this->add_balans($sum,$this->id);
				}
		} else if(isset($_COOKIE['guest'])) {
			$this->level = self::GUEST;
			$this->login = 'Гость';
			$this->ms = 0;
			$this->id = 0;
			$this->customerid = 0;
			$this->siid=0;
			$this->balans=0;
		}
	}
 
	function checkusersite($sid) {//находитесь ли на сайте регистрации или регистрировались ли вы на этом сайте
		if ($sid<>0 && $this->siid == $sid && $this->isAdmin()) return true;
		else return false;
	
	}
	
	function areyouAdmin($domen,$uid){
		if ($this->whatauthorsite($domen,$uid)) {
			$this->status=$this->getLevelnew();
			if($this->status > self::MANAGER) return true;
			else return false;
			}
		else return false;	
	}
	
	function areyouManager($domen,$uid){
		if ($this->whatusersite($domen,$uid)) {
			$this->status=$this->getlevelnew();
			if($this->status > self::EDIT_USER) return true;
			else return false;
			}
		else return false;	
	}
	
	
	function whatauthorsite($domen,$uid=0){
		$site=$this->initbdF($domen);
		if ($uid == 0)$this->check();
		else $this->id = $uid;
		if($site->uid === $this->id) return true;
		else return false;
	}
	
	function whatusersite($domen,$uid){
		$site=$this->initbdF($domen);
		if($uid==1)$this->siid=1;
		if($site->ids == $this->siid) return true;
		else return false;
	}
		
	function isExistCust($id) {
	if($id <> 0){
		//echo '--------'.$id.'<br>';
		$find=$this->db->query('select * from `customers` where `userid`= ^Ni;', $id);
		//print_r($find);
		if ($find) {
		//echo 'find '.$find->name.'<br>';
		return true;	
		}
		else {
			//echo 'don"t find '.$find;
			return false;
			}
		}		
	return false;		
	}

		
	function isExistCustName($priv) {
	if(is_array($priv)){
		//echo '--------'.$id.'<br>';
		$find=$this->db->query('select * from `customers` where `name`= ^Ns AND `cfio`= ^Ns AND `email`= ^Ns ;', $priv['name'],$priv['cfio'],$priv['em']);
		//print_r($find);
		if ($find) {
		//echo 'find '.$find->name.'<br>';
		return true;	
		}
		else {
			//echo 'don"t find '.$find;
			return false;
			}
		}		
	return false;		
	}

	function addCusToUser($id,$cid){
	if($id !== 0){
		$find=$this->db->query('select `customerid` from `users` where `id`= ^Ni;', $id);
		if ($find == false)  {
		$this->db->query('UPDATE `users` SET `customerid` = ^Ni WHERE `id` = ^Ni;', $cid, $id);
		echo "<div class='info'>Пользователь $id зарегистрировал клиента лицо $cid  </div>";
		}
		}
	}
	
	
	
	function addSiteToUser($id, $sid){
	if($id !== 0){
		$this->db->query('UPDATE `users` SET `siid` = ^Ni WHERE `id` = ^Ni;', $sid, $id);
		}
	}
	
	function idCust($cid) {
	if($cid <> 0){
		$find=$this->db->query('select * from `users` where `customerid`= ^Ni;', $cid);
		if ($find) return $find;	
			else return false;
		}
		return false;		
	}
	
	function getuserall($id) {
	if($id != 0){
		$find=$this->db->query('select * `users` where `id`= ^Ni;', $id);
		if ($find) return $find;	
				else return false;
			}
	return false;			
}
	
	function idUser($id) {
	if($id != 0){
		$find=$this->db->query('select `customerid`,`name`, `uradr`, `telmain`, `cinn`, `cfio`, `email`  from `customers` where `userid`= ^Ni;', $id);
		if ($find) return $find;	
				else return false;
			}
	return false;		
	}	
	
	function CustExist ($cust) {
	$arr=array('Код фирмы','Наименование','Юридический адрес','Телефон организации','ИНН','Контактное лицо','Электронная почта ');
	//$a=reset($arr);
    echo '<tr><td>       </td>';
	//echo '<td><div class="button" >Регистрационные даные юридического лица </div><div class="ank">';	  		
			$firm=$this->idUser($cust);
			while(list($key, $val) = each($arr))
   {
      if (current($firm)) echo $val.' - '.current($firm).'<br>';
	  next($firm);
   }
}
	function idUserF2($id,$cid) {
	if($id != 0){
		$find=$this->db->query('select * from `customers` where `userid`= ^Ni && `customerid`= ^Ni;', $id, $cid);
		if ($find) return $find;	
				else return false;
			}
	return false;		
	}
	
	function activeUserSoc($id) {
	if($id != 0){
		$find=$this->db->query('select * from `users` where `id`= ^Ni;', $id);
		if ($find) return $find;	
				else return false;
			}
	return false;		
	}
	
	function idUserF($id) {
	if($id !== 0){
		$find=$this->db->query('select * from `customers` where `userid`= ^Ni;', $id);
		if ($find) {
			$find->level=$this->getLevel();
			$find->tarif=$find->hosting;
			if($find->icq){
				$find->social = array('facebook','twitter','vk','youtube');;
				$find->social_link = explode(';',$find->fax);
				$find->hosting=explode('|',$find->icq);
				
			}
			else {
				$find->social='';
				$find->hosting='';
			}
			return $find;	
		}
		else {
			return false;
		}
			}
	return false;		
	}	
	
	function CustExist2 ($cust) {
	$firm=$this->idUser($cust);	
    echo '<tr><td>       </td>';
	echo '<td><div class="button" >Регистрационные даные юридического лица №'.$firm->customerid.'</div><div class="ank">';	  		
	return  $firm->customerid;
}


	function CustExist3 ($cust) {
    //echo '<tr><td>       </td>';
	//echo '<td><div class="button" >Регистрационные даные юридического лица </div><div class="ank">';	  		
			$firm=$this->idUser($cust);		
	return  $firm;
}

function check_firm($uid) {
$firm=$this->idUser($uid);
	if ($firm) {
		foreach ($firm as $key=>$val) {
			if ($val=='') {
			return false;
			}
		}
		return true;
		}
	else return false;	

}

function view_orders_cust($cid, $par = 'SAVE') {
	//если клиент существует то
	// для клиента cid неоходимо выбрать заказы с order_status = par
	if (!$this->idCust($cid) == false) {
		$find=$this->db->query('select `orderid`  from `orders` where `customerid`= ^Ni and `order_status`=^Ns;', $cid, $par);
	// если есть результат, то в массив arr помещаем номера заказов клиента cid и статусом par
		if ($find) {
			$arr=array();
			foreach ($find as $val) {
				$arr[]=$val;
					} 
	//выбираем из oder_item соответсвующие строки товаров и помещаем их массив массивов find
	//в каждом массиве находится код товара и его количество
			$i=0;
			foreach ($arr as $value) {
				$find[$i]=$this->db->query('select  *  from `order_items` where `oderid`= ^Ni and `isbn`<>^Ns;', $value, '');
				$i++;
								}
	//выводим на экран список товаров
			$this->view_cust($find);
		}
		else return false;
		}	
	return false;		
	}
	
function view_cust ($find){
	$ng=count($find);
	echo 'Позиции заказов:<br>';
	for ($k=0;$k<$ng; $k++) {
			echo $find[$k]->isbn.'---'.$find[$k]->quantity.'---'.$find[$k]->item_price.'<br>';
			}
}
	
function view_orderid($orderid) {
	//если заказ не нуль
	//выбираем из oder_item соответсвующие строки товаров и помещаем их массив массивов find
	if (!$orderid == 0)  {
		$find=$this->db->query('select  *  from `order_items` where `orderid`= ^Ni ;', $orderid);
		//выбираем из oder_item соответсвующие строки товаров и помещаем их массив массивов find
	//в  массиве находится код товара и его количество
			$arr=array();
			foreach ($find as $value) {
				$arr[]= $value;
								}
	//выводим на экран список товаров
	$this->view_cust($arr);
	/*for ($k=0;$k<count($arr);$k++) {
		//echo $arr[$k].'<br>';
		echo $arr[$k]->isbn.'---'.$arr[$k]->quantity.'---'.$arr[$k]->item_price.'<br>';
		}*/
		}
		else return false;
	return false;		
	}

	function getNumErrors() {
		if($this->numErrors == '') {
			$this->db->query('DELETE FROM `block` WHERE `time` < DATE_SUB(NOW(), INTERVAL 60 MINUTE);');
			$res = $this->db->query('SELECT `errors` FROM `block` WHERE `ip` = ^Ns;', $_SERVER['REMOTE_ADDR']);
			if($res !== null) $this->numErrors = $res;
			else $this->numErrors = 0;
			return $this->numErrors;
		} else {
			return $this->numErrors;
		}
	}

	function setNumErrors() {
		$this->getNumErrors();
		if($this->numErrors != 0)	$query = 'UPDATE `block` SET `errors` = ^Ni WHERE `ip` = ^Ns;';
		else $query = 'INSERT INTO block (`errors`, `time`, `ip`) VALUES(^Ni, NULL, ^Ns);';
		$this->numErrors++;
		$this->db->query($query, $this->numErrors, $_SERVER['REMOTE_ADDR']);
	}
	
	private function checkLogin($login) {
		return preg_match('#^[a-z]{1}[a-z0-9]*$#i', $login);
	}
	
	private function checkEmail($email) {
		return preg_match('#^[a-z0-9.\-_]+@[a-z0-9.\-_]+\.[a-z]{2,4}$#i', $email);
	}
	
	private function checkPass($pass) {
		return preg_match('#^[A-Za-z0-9`~!@\#$%^&*\-_=+\\|\'";:/?.,><]*$#i', $pass);
	}
	
	function checkInPost($login, $email, $pass) {
		return $this->checkLogin($login) && $this->checkEmail($email) && $this->checkPass($pass);
	}
	function checkFirm ($firm) {
		if ($firm['name']&&$firm['uradr']&&$firm['cinn']&&$firm['telmain']&&$firm['cfio']&&$firm['tels']&&$firm['em'])
	{		return true;}
	else {return false;}
	}
		
	function isLoginExist($login) {
		$res = $this->db->query('SELECT `id` FROM `users` WHERE `login` = ^Ns;', $login);
		if($res === null) return false;
		else return true;
	}
	
	function idLoginExist($login) {
		$res = $this->db->query('SELECT `id` FROM `users` WHERE `login` = ^Ns;', $login);
		if($res === null) return $res->id;
		else return true;
	}
	
	function isEmailId($email,$site) {
		if ($this->isEmailExist($email)){
		//echo '----it is Email in BD here '.$email.'-+-'.$site.'<br>';
		$res = $this->db->query('SELECT `id` FROM `users` WHERE `email` = ^Ns;', $email);
		//echo '+++++++it is Email in BD here '.$email.'-+-'.$site.'<br>';
		//print_r($res); 
		if(!isset($res)) return false;
		else return $res;
	}
	else return false;
}

	function idLinksAll($id){
		if(id>0){
			$res = $this->db->query('SELECT `id` FROM `yoursius` WHERE `id` = ^Ni;', $id);
			if ($res) return $res;
			else return false;
	}
	else return null;	
	}
	
	function idLinkAdd($word,$id,$varriant1,$varriant2){
		if(id>0){
			$query='UPDATE `'.$varriant1.'` SET `'.$varriant2.'` = ^Ns WHERE `id` = ^Ni;';
			$res = $this->db->query($query,$word,$id);
		return $res;
		}
		else return null;	
	return $res;	
	}
	
	function idLinkDel($word,$id,$varriant1,$varriant2){
		if(id>0){
			$query='DELETE FROM `'.$varriant1.'` WHERE `'.$varriant2.'` = ^Ns WHERE `id` = ^Ni;';
			$res = $this->db->query($query,$word,$id);
			return $res;
		}
		else return null;		
	}
		
	function AddLinksUser($id1,$id2){
		if($id1>0 && $id2>0){
		//добавляем id2 в список имеющих доступ к ресурсам id1
		$rr1=$this->idLinksAll($id1);
		$rr1->readyou.=$id2.';';
		$res=$this->idLinkAdd($rr1->readyou,$id2,$id1,'readyou');
		return $res;
		}
		else return null;		
	}
	//блокировка пользователя id2  списке читающих id1
	function DelLinksUser($id1,$id2){
		if($id1>0 && $id2>0){
		$rr1=$this->idLinksAll($id1);
		$var=$id2.';';
		$rr1->readyou=str_replace($var, $rr1->readyou, '');
		$res=$this->idLinkAdd($rr1->readyou,$id2,$id1,'readyou');
		return $res;
		}
		else return null;			
	}
	
	//блокировка пользователя id2  к сайту sid1
	function DelLinksSite($id2,$sid1,$varriant){
		if($sid1>0 && $id2>0){
		$rr1=$this->idLinksAll($id1);
		$var=$id2.';';
		$rr1->readyou=str_replace($var, $rr1->$varriant, '');
		$res=$this->idLinkAdd($rr1.'->'.$varriant,$id2,$id1,$varriant);
		return $res;
		}
		else return null;			
	}
	
	function setlinksuser($id){
		if(!$this->idLinksAll($id)){
			$query='INSERT INTO `yoursius` (`id`) VALUES(^Ni);';
			$this->db->query($query,$id);
		}
	}
	
	function checklinks($id1,$id2,$varriant){
		
		$rr1=$this->idLinksAll($id1);
		$rr2=$this->idLinksAll($id2);
		$res=0;
		$areader1=explode($rr1->$varriant);
		$areader2=explode($rr2->$varriant);
		if($areader1[0]<>'all') {
			if(strstr($areader1[1],$id2)) $res=1;
			else $res=0;
		}
		else $res=1;
		if($areader2[0]<>'all') {
			if(strstr($areader2[1],$id1)) $res=$res-2;
			else $res++;
		}
		else $res++;		
		//res=-2 первый читает второго, второй нет
		//res=-1 взаимный доступ
		//res=1 взаимный недоступ
		//res=2 первый не читает второго, второй читает первого
	return $res;
	}
	
	//проверяет читает ли второй первого кто читает вас?
	function checkreadusers($id1,$id2){
		//проверяет состояние связи пользователей
		$res=$this->checklinks($id1,$id2,'readyou');
		if($res == -1 || $res == 2) $result= true;
		else $result = false;
		return $result;
	}
	//если вы id1 и ваш сайт sid1, id2 клиент sid2 сайт клиента 2
	//проверяет читает ли первый второго кого читаете вы?
	function checkusersread($id1,$id2){
		//проверяет состояние связи пользователей
		$res=$this->checklinks($id1,$id2,'youread');
		if($res == -1 || $res == 2) $result= true;
		else $result = false;
		return $result;
	}
	//к каким сайтам есть доступ?
	function checksiteuser($id1,$sid2){
		$res=$this->checklinks($id1,$sid,'whoseisite');
		if($res == -1 || $res == -2) $result= true;
		else $result = false;
		return $result;
		
	}
	
	//кому доступен ваш сайт?
	function userchecksite($id2,$sid1){
		$res=$this->checklinks($id1,$sid,'whoyoursite 	');
		if($res == -1 || $res == 2) $result= true;
		else $result = false;
		return $result;
		
	}
	
	function checklinksiteuser($sid,$id){
		//проверяет состояние связи сайта и пользователя
		
	}
	
	function checklinkusersite($id,$sid){
		//проверяет состояние пользователя и сайта
			
	}
	
	function your_test_sites($id){
		if($id<>0)$res=$this->db->query('SELECT `ids`,`domen` FROM `allsites` WHERE `uid`=^Ns;',$id);
		else return null;
		if($res){
			if(is_array($res))foreach($res as $val)$ret[$res->domen]=$res->$val;
			else $ret=$res;
			return $ret;
		}
		else return null;
	}
	
	function isEmailExist($email,$site=1) {
		$res = $this->db->query('SELECT `id` FROM `users` WHERE `email` = ^Ns AND `siid` = ^Ni;', $email,$site);
		if(!isset($res)) return false;
		else return true;
	}
	
	function whatemail($id,$site){
	$res = $this->db->query('SELECT `email` FROM `users` WHERE `id` = ^Ni AND `siid` = ^Ni;', $id,$site);
		if(!isset($res)) return false;
		else return $res;
	}
	
	
	function auth($login, $pass) {
		if($this->checkLogin($login)) {
			$res = $this->db->query('SELECT `id`, `ms`, `level`, `pass`, `email`, `customerid` FROM `users` WHERE `balans`> \'0\' AND`login` = ^Ns AND `activate` = \'1\';', $login);
			if($res !== null) {
				$hash = md5(md5($pass).md5($this->key));
				if($hash == $res->pass) {
					$this->guest_exit();
					$this->setCoo($res->id, $login, $res->pass);
					$this->level = $res->level;
					$this->ms = $res->ms;
					$this->login = $login;
					$this->email = $res->email;
					$this->id = $res->id;
					$this->customerid = $res->customerid;
					return self::LOGIN_SUCCESS;
				}
			}
		}
		$this->setNumErrors();
		return self::INCORRECT_LOGIN_PASS;
	}

	function getLevel() {
		return $this->level;
	}
	
	function getLevelnew($uid=0) { 
		if(isset($_GET['logout'])){
			//echo 'user logout';
			$this->level=self::INCORRECT_LOGIN_PASS;//Пользователь вышел из системы авторизации
		}
		else {
		//echo 'check user ';	
		$site=$this->initbdF($_SERVER['HTTP_HOST']);
		User::check();
		if($this->id == 0 )$this->level = 0;
		if($this->id == 1 && $this->siid == 1) $this->level = self::ADMIN;//6
		elseif($this->isLocAdmin() && $this->id == $site->uid && $this->siid == $site->ids)  $this->level = self::LOCADM;
		elseif($this->isManager() && $this->balans > 1000)$this->level = self::MANAGER;//4
		elseif($this->isUserEdit()&& $this->balans > 1000)$this->level = self::EDIT_USER;//3
		elseif($this->isClient() && $this->balans > 0)$this->level = self::CLIENT;//2
		elseif($this->isUser())$this->level = self::USER;//1
		else $this->level = self::GUEST;//0
		}
	return $this->level;
	}
/*	
	function getLevelnew($uid=0) { 
		if(isset($this->balans))
		if(isset($_GET['logout'])) $this->level=self::INCORRECT_LOGIN_PASS;//Пользователь вышел из системы авторизации
		else {
		$site=$this->initbdF($_SERVER['HTTP_HOST']);
		if($this->level === $this->id === $site->uid) $this->level=self::ADMIN;//Администратор сайта с полными правами изменений компонентов сайта
		elseif( $this->siid === $site->ids) $this->level=self::MANAGER;// Менеджер с правами изменений некоторых компонентов сайта
		elseif ($this->isUserEdit() && $this->balans > 999) $this->level=self::EDIT_USER;//Авторизованый пользователь сайта  с правами настройки пользовательского компонента
		elseif($this->id > 1) $this->level=self::CLIENT;//Зарегистрированый авторизованый пользователь
        elseif($this->id==1) $this->level=self::USER;//Зарегистрированый неавторизованый пользователь
        elseif($this->isGuest()) $this->level=self::GUEST;// Пользователь с правами Гость
		else $this->level=self::INCORRECT_LOGIN_PASS;//Незарегистрированый пользователь сайта
		}
		if($uid==1)$this->level=6;//Супереадминистратор
	return $this->level;	
	}
*/	
	function getuserid() {
		return $this->id;
	}
	
	function getusercid() {
		return $this->customerid;
	}
	
	function getusersid() {
		return $this->siid;
	}
	 
	function isGuest() {
		return $this->level == self::GUEST;
	}
	
	function isManager() {
		return $this->level & self::MANAGER;
	}
	
	function isAdmin() {
		return $this->level & self::ADMIN;
	}
	
	function isLocAdmin() {
		return $this->level & self::LOCADM;
	}
	
	function isClient() {
		return $this->level & self::CLIENT;
	}
	
	function isUserEdit() {
		return $this->level & self::EDIT_USER;
	}
	
	function isUser() {
		return $this->level & self::USER;
	}
	
	function getLogin() {
		return $this->login;
	}

	function getMs() {
		return $this->ms;
	}
	
	function getEmail() {
		return $this->email;
	}

	function user_exit() {
		setcookie("hash", '', 0, "/");
	}
	
	function guest_exit() {
		setcookie("guest", '', 0, "/");
	}
	
	function logout() {
		if($this->isGuest()) $this->guest_exit();
		else $this->user_exit();
		$this->level = -1;
	}

public function initbdF($domen){
	if (isset($domen)) $this->domen=$domen;
	if (strstr($this->domen,'www')) {
			$this->domen=substr($this->domen,4);
		}
	if ($this->domen <> "") {
		
	$res=$this->db->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`css`,`script`,`images`,`pages`, `news`,`element`,`structure`,`desc_site` FROM `allsites` WHERE `domen` = ^Ns;', $this->domen);	
	//$resu=$this->read_namparams('setMaketPage');
	//$arridmen=$resu[1];
	//if(isset($arridmen))$res->disp = $arridmen[$res->strucs];
	if($res){
		$ret=explode('/',$res->domen);
		if(count($ret)>1) {
			//$res->domen='gjs.'.$ret[0];
			$res->simlink=$ret[1];	
			}
		return $res;	
	}	
	//else echo 'Сайт --'.$this->domen.'-- в базе данных не найден';
	}
	return false;
	}	
	
public function getsitetables($domen){
		if ($domen <> "") {
		$Site=$this->db->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`images`,`pages`, `news`,`element` FROM `allsites` WHERE `domen` = ^Ns;', $domen);		
	}
	
	if ($Site->strucs == 0) $structure='structure';
	else $Structure=$Site->strucs;
	if (isset($Site)) { 
		$tabl=array('news'=>$Site->news, 'pages'=>$Site->pages,'elem'=>$Site->element,'str'=>'structure','elemap'=>'elemap','mapsites'=>'mapsites');
	return $tabl;
	}
	else return false;
}
		
private function ready_str_field($fields,$nb=0,$ne=0,$quot='`',$zap=','){
	$this->y='';
	if (is_array($fields)) {
	$NN=count($fields);
		for ($i=$nb;$i<$NN-$ne;$i++){
			if ($fields[$i]<>''){
			if ($i<$NN-1-$ne) $this->y.=$quot. $fields[$i].$quot.$zap;
			else $this->y.=$quot. $fields[$i].$quot;
			}
		} 
	
}
return $this->y;
}

public function getsitesuser($uid){
	if ($uid <> 0) { 
		$Sites=$this->db->query('SELECT `ids`,`uid`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`css`,`script`,`images`,`pages`, `news`,`element`, `structure`, `desc_site` FROM `allsites` WHERE `uid` = ^Ni;', $uid);	
		if($Sites){
		if(!is_array($Sites))$ress[0]=$Sites;
		else $ress=$Sites;	
		if (count($ress)>0) {
			return $ress;
	}
	}
	else return false;
	}
	else return false;	
}	

public function right_access($ds) {
	
	$arrdesc=explode('|',$ds);	
	//debug($arrdesc);	
	if($arrdesc[0]<>'') $ret['GA']=$arrdesc[0];
	else $ret['GA']=false;
	if($arrdesc[1]<>'') $ret['YM']=$arrdesc[1];
	else $ret['YM']=false;	
	if($arrdesc[2]=='N')$ret['PR']='http://';
	else $ret['PR']='https://';	
	if(!isset($arrdesc[3]))$ret['metr']=false;
	else $ret['metr']=true;
	if(!isset($arrdesc[4]))$ret['access']= 'global';
	else $ret['access']= $arrdesc[4];
	return $ret;
}

public function whatisbd(){
	$res=$this->db->init_data;
	return $res[2];
}
public function whatisall(){
	$res[]=$this->whatisbd();
	$res[]=$this->initbdF($_SERVER['HTTP_HOST']);
	return $res;
}

private function  whatisdatabase(){
		if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
		if(strstr($_SERVER['HTTP_HOST'],'.'))$name_domen=explode('.',$_SERVER['HTTP_HOST']);
		else $name_domen[0]=$domen;
		if(isset($name_domen[1]) && !isset($name_domen[2]))$this->dbname=$namebd=$name_domen[0].'_'.$name_domen[1];
		return $this->dbname;
	}
	
	public function yourbd(){
		$ret=$this->db->yourbd();
		if($ret<>'')return $ret;
	}
		
	public function destruct() {
		$this->conn->close();
	}
	
public function regbd($domen,$uid=1,$newsite='',$idmen=1,$typmen=0,$ippnt=0,$tarif=1,$desc_site='',$page_file=''){
	//debug($_POST);
	$db = Singleton::getInstance('DB');
	//$Site0=$db0->initbd($_SERVER['HTTP_HOST'],$db0);
	//$db = Singleton::getInstancepar('DB',$Site0->host,$Site0->logad,$Site0->passwad,$Site0->bd,$Site0->port);
	$dbname='nonchangebd';
	$insi=$db->init_data;
	if($desc_site === '') {
		$desc_site = array();
		$desc_site['cga']='';
		$desc_site['cym']='';
		$desc_site['own']='Y';
		$desc_site['ownbd'] ='yes';
	}
	$desc_site['seo'] ='N';
	if($idmen == 1) $desc_site['access'] = 'general';
	else $desc_site['access'] = 'global';
	if($desc_site['ownbd'] === 'yes' && $tarif<5)$dbname=$db->yourbd($domen);
	else $dbname=$insi[3];
	$resu = $this->read_namparams('setMaketPage');
	$arrlatstr=$resu[1];
	//$arrlatstr=array(11=>'cont', 0=>'land', 1=>'gall', 7=>'flex', 8=>'mag', 9=>'cat',6=>'mob' ,4=>'fb', 3=>'tw',5=>'qw',10=>'shop',2=>'blog',12=>'lay');
	echo '<div class="info">Тариф: '.$tarif.'Структура сайта:'.$arrlatstr[$typmen].' Тип сайта:'.$idmen.' Назначение:'.$ippnt.' </div>';
	$descSite = $_POST['cga'].'|'.$_POST['cym'].'|'.$_POST['prot'].'|'.$desc_site['seo'].'|'.$desc_site['access'];
	//debug($descSite);
	$imgdflt='banmain.jpg;logo.png;photo.jpg';
	if(!Utils::getsitetables($domen)) {
		$tabl['pages']='pages';
		$tabl['news']='news';
		$tabl['str']='structure';
		$tabl['elem']='elements';
	}
	else $tabl=Utils::getsitetables($domen);
	$npg=$db->getscountab($tabl['pages'],'numpage', 'f');
	if (isset($domen)) $this->domen=$domen;
	if (strstr($this->domen,'www')) {
			$this->domen=substr($this->domen,4);
		}
	if (isset($uid)) $this->uid=$uid;
	
	$priv['name']=$_POST['adms'];
	$priv['cfio']='Admin '.$this->domen;
	$priv['em']=$_POST['eml'];
	$priv['host']=$tarif;
	if(isset($_POST['telmain']))$priv['telmain']=$_POST['telmain'];
	else $priv['telmain']='+79255053421';
	if(isset($_POST['city']))$priv['city']=$_POST['city'];
	else $priv['city']='Moscow';
	if(isset($_POST['country']))$priv['country']=$_POST['country'];
	else $priv['country']='Russia';
	if(isset($_POST['site'])) $idsite = $_POST['site'];
	else $idsite = 1;
// добавление для пользователя сайта в базу	
	$db->start();
	$res=$this->db->query('SELECT `domen` FROM `allsites` WHERE `domen` = ^Ns;', $this->domen);		
	if (!$res) {
		if ($uid>1) //$this->addAdmin($priv['name'], $_POST['pass'], $priv['em']);
		$this->addManager($priv['name'], $_POST['pass'], $priv['em']);
		
		$res=$this->db->query('INSERT INTO `allsites` (`ids`,`uid`,`nmpage`,`domen`,`types`,`strucs`,`appoint`,`css`,`script`,`images`,	`passwad`,`logad`,`bd`,`host`,`port`,`pages`,`news`, `element`,`structure`,`desc_site`) 
		VALUES (^Ni,^Ni,^Ns,^Ns,^Ni,^Ni,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns);',
		$idsite,$this->uid,'',$this->domen,$idmen,$typmen,$ippnt,'style'.$arrlatstr[$typmen],'libs',$imgdflt,$insi[1],$insi[0],$dbname,$insi[2],$insi[4],$tabl['pages'],$tabl['news'],$tabl['elem'],$tabl['str'],$descSite);
		if($res)echo '<div class="info">Сайт '.$this->domen.' зарегистрован в '.$insi[3].'  за номером '.$_POST['site'].'</div>';
		else 'Регистрация '.$this->domen.'  не удалась' .$_POST['site'];
		$Site=$this->initbdF($this->domen);
		if (isset($Site)) $tabl=array('news'=>$Site->news, 'pages'=>$Site->pages,'elem'=>$Site->element);
//добавление клиента для пользователя  
//$cn=$this->getscountab('customers','customerid','f')+1;	
		$resa=$this->db->query('SELECT `userid` FROM `customers` WHERE `userid` = ^Ni;', $this->uid);//$this->idUserF($this->uid);//
		if ($resa == false){
			$cid=$this->addcustomer($uid,$priv);
			//print_r($cid);
			$find = $this->db->query('UPDATE `users` SET `siid` = ^Ni WHERE `id` = ^Ni;', $_POST['site'], $this->uid);
			if ($find) echo '<div class="info">Пользователь с сайтом '.$this->domen.' ассоцирован  </div>';	
			else echo '<div class="info">Пользователя с сайтом '.$this->domen.' ассоцировать не удалось  </div>';	 	
		}
		elseif($newsite==='') {
			$cid=$this-> idUserF($this->uid)->customerid;
			echo '<div class="info"> Клиент №'.$cid.' сайта '.$this->domen.' уже зарегистрован </div>';	
			$db->rollback();
		}
	//добавление значений параметров заголовков	таблиц и начальных страниц	
		$db->commit();
		echo '<div class="info">Транзакция создания сайта закрыта</div>';
		if(!isset($user)) $user = Singleton::getInstance('User');
		if(isset($page_file) && $page_file<>'')Utils::add_tabs_file($domen,$user,$tabl['pages'],$db,$this->uid,20000,$page_file,$arrlatstr[$typmen]);
		if($desc_site['ownbd'] === 'no'){
			
			if ($this->prepare_start_pages($this->uid,$this->domen,$tabl,$typmen))echo 'Запись стартовых страниц для сайта - '.$this->domen.'<br>  прошла успешно. Подключение сайта завершено.'; 
			else echo ' Подключение сайта завершено'; 
		}	
		else {
			echo ' Регистрация сайта  продолжается. <br> ШАГ3: Регистрация сайта в персональной базе данных.'; 
		}
		return  $Site->ids;
	}	
else {
	echo '<div class="info">Транзакция создания сайта отменена</div>';
	echo '<div class="info">Сайт '.$this->domen.' уже зарегистрован в базе  ранее за номером '.$_POST['site'].'</div>';	
	$this->db->rollback();
	return  0;
	}
	
}
	function idomen($domen){
		$idd=$this->db->query('SELECT `ids` from `allsites` WHERE `domen`=^Ns;',$domen);
	return $idd;
	}
	
	private function prepare_start_pages($uid,$domen,$tabl,$typmen=0,$loadfiles=''){
// добавление начальных страниц сайта пользователя
	$resp=$this->db->query('SELECT `numpage` FROM `'.$tabl['pages'].'` WHERE `site` = ^Ns;', $domen);
	if (!$resp) {
	$ip=$this->getscountab($tabl['pages'],'numpage', 't');
	$ln=$this->getscountab('infos','','c')+1;
	$nn[0]=array('idauthor'=>$uid,'name'=>' Иницилизация страниц '.$domen,'newstext'=>'Загрузка страниц на сайт '.$domen.' выполнена. ','idnews'=>$ln,'vendor'=>'service','group'=>'pages','imgnews'=>'faviconjpg.jpg','codgjsnews'=>'','hrefnew'=>$domen,'numpagat'=>($ip+1),'site'=> $this->idomen($domen));
	if(Utils::prepare_pages($uid,$domen,$this->getscountab($tabl['pages'],'', 'c'),$nn,Singleton::getInstanceinit('DB',1),$typmen,$loadfiles)){
			echo '<div class="info">Стартовые страницы сайта '.$domen.' зарегистрованы </div>';
			return true;
			}
			else{
				echo 'Загрузка из данного файла '.$loadfiles.' невыозможна.';
				return false;
			}
		}
	else {
		echo '<div class="info">Стартовые страницы сайта '.$domen.' уже зарегистрованы </div>';	
		return 	mysql_errno();
		}	
}
	function getBalans(){
		return $this->balans;
		
	}
	
	function add_balans($sum,$uid){
		$balans=$this->db->query('SELECT `balans` , `siid` FROM `users` WHERE `id` =^Ni;',$uid);
		if (!isset($balans->balans))$this->balans=0;
		if($sum>0){
			$this->balans+=$sum;
			$subject='Пополнение баланса ';
			$tabl['infos']='infos';
			$lpn=$this->getscountab($tabl['infos'],'idnews', 'f');
			$mes='Клиент '.$uid.' ('.$balans->balans.') пополняет баланс  на сумму '.$sum;
			$nn[0]=array('idauthor'=>$uid,'name'=>$subject,'newstext'=>$mes,'idnews'=>($lpn+1),'vendor'=>'service','group'=>'balans','imgnews'=>'faviconjpg.jpg','codgjsnews'=>'','hrefnew'=>'','numpagat'=>0,'site'=>$balans->siid);
			$this->db->autocommit(FALSE);
			$this->db->start();
			
			try {
				$this->db->query('UPDATE  `users` SET `balans`=^Ni WHERE `id`=^Ni;',$this->balans,$uid);
				Utils::prepare_news($nn,$tabl,$this->db);
				$emladm=$this->whatemail(1,1);
				Utils::sendMail($this->getEmail(), $subject, $mes, $emladm,$uid);
				}
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
			Utils::transakres($this->db);
		/*if (mysql_errno() == '') {
			$this->db->commit(); 
			$this->db->autocommit(TRUE);
			if (mysql_errno()) echo '<div class="info">ERROR commit-'.mysql_error().'</div>';
			echo '<info class="hidno">Транзакция пополнения баланса закрыта</info>';
			echo '<info class="hidno">Баланс пополнен:'.$this->balans.' </info>';
			}
		else {
			$this->db->rollback();
			echo '<div class="info">Транзакция пополнения баланса отменена</div>';
	}	*/
		}
	else return $balans->balans;
	}
	
	private function addUser($login, $pass, $email, $level, $activate = 0,$balans =1) {
		$email = strtolower($email);
		//$tabl['news']='news';
		if($this->checkInPost($login, $email, $pass)) {
			//echo 'CheckInPost good';
			$hash = md5(md5($pass).md5($this->key));
			try {
				$cn=$this->getscountab('customers','customerid','f')+1;
				$this->db->query('INSERT INTO `users` (`login`, `pass`, `level`, `email`, `customerid`,`id`,`activate`,`siid`,`balans`) VALUES (^Ns, ^Ns, ^Ni, ^Ns,^Ni, ^Ni,^Ni,^Ni,^Ni);', $login, $hash, $level, $email, $cn,$_POST['uid'], $activate,$_POST['site'],$balans);
				$this->id = $this->db->id();
				$this->login = $login;
				
			} catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
		
			return true;
		} else {
			echo 'no registratuion';
			return false;
		}	
	}
	
function OrderCust($cust, $a) {
		try {
				$tp=$this->db->query('SELECT SUM(`amount`) FROM `orders` WHERE `customerid`=^Ni AND `order_status`=^Ns;',$cust, $a);
				} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
return $tp;			
}	

function ReservCust($order) {
		try {
				$tr=$this->db->query('SELECT SUM(`quantity`) FROM `order_items` WHERE `orderid`=^Ni;',$order);
				} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
return $tr;			
}	

function ReservOrders($cust, $a) {
		try {
				$res=$this->db->query('SELECT `orderid` FROM `orders` WHERE `customerid`=^Ni AND `order_status`=^Ns;',$cust, $a);
				} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
			
return $res;	
}	
 
function checkPrivate ($firm) {
		if ($firm['name']<>'' && $firm['cfio']<>'' && $firm['em']<>'' && $firm['telmain'])
	{		return true;}
	else {return false;}
	}
	
function addcustomer($idu,$priv){
//echo 'form email in priv <br>';
$email = strtolower($priv['em']);
if($this->checkPrivate($priv)){
	
	if($this->add_balans(0,$idu)>0) {
		if($idu>1)$this->add_balans(1,$idu);
		if($this->getBalans()>100 || $idu==1)$hostpar='y';
		else $hostpar='ny';
		for($i=1;$i<9;$i++){
			if($i<$priv['host'])$hostpar.=';'.'y';	
			else $hostpar.=';'.'ny';	
		}
	}
}
else {
	$priv['name']='anonim'.$idu;
	$priv['cfio']='no';
	$priv['em']='no';
	$priv['telmain']='no';
	$priv['city']='';
	$priv['country']='';
	$priv['host']=1;
	$hostpar='ny;ny;ny;ny;ny;ny;ny;ny;ny';
}
	$find=$this->isExistCust($idu);
	$cid=$this->getscountab('customers','customerid','f')+1;
	if (!$find && !$this->isExistCustName($priv)){
	$this->db->query('INSERT INTO `customers` (`city`,`country`,`customerid`,`name`, `telmain`,`email`,`fax`,`icq`,`cfio`,`userid`,`hosting`) VALUES (^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni);',$priv['city'],$priv['country'],$cid,$priv['name'],$priv['telmain'],$email,';;;;',$hostpar,$priv['cfio'],$idu,$priv['host']);
	//echo '<br>added custid '.$this->idUser($idu)->customerid; 
	return $this->addCusToUser($idu,$this->idUser($idu)->customerid);
	}				
else return $find;				
					
}



function addUserPrivate($id, $firm) {
		$email = strtolower($firm['em']);
		if($this->checkPrivate($firm)) {
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
				
				$this->db->query('INSERT INTO `customers` (`customerid`,`name`, `telmain`,`email`,`cfio`, `userid`) VALUES (^Ni, ^Ns, ^Ns, ^Ns, ^Ns, ^Ni);',$id, $firm['name'], 
				$firm["telmain"],$email,$firm["cfio"],$id);
				$this->addClientRights($id);
				$nc=$this->CustExist2($id);
				$this->addCusToUser($id, $nc);
			} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
			echo "<br>";
		// Данные записываются в базу данных таблица customers при этом в поле userid заносится id пользователя
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

function addUserFirm($id, $firm) {
		$email = strtolower($firm['em']);
		if ($firm['address']=='') $firm['address']=$firm['uradr'];
		if($this->checkFirm($firm)) {
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
				$this->db->query('INSERT INTO `customers` (`name`, `uradr`, `city`, `state`, `zip`, `country`, `address`, `telmain`,`cinn`, `ckpp`,`crs`,`cbank`,`cbik`,`cks`, `tels`, `fax`, `email`,`icq`, `cfio`, `userid`) VALUES (^Ns, ^Ns, ^Ns, ^Ns, ^Ns,^Ns, ^Ns, ^Ns, ^Ns, ^Ns,^Ns, ^Ns, ^Ns, ^Ns, ^Ns,^Ns, ^Ns, ^Ns, ^Ns, ^Ni);', $firm['name'], 
				$firm['uradr'],$firm['city'],$firm['state'], $firm['zip'], $firm['country'], $firm['address'],$firm['telmain'],$firm['cinn'],$firm['ckpp'],$firm['crs'],$firm['cbank'],$firm['cbik'],$firm['cks'],$firm['tels'],$firm['fax'],$firm['em'],$firm['icq'],$firm['cfio'],$id);
				$this->addClientRights($id);
				$nc=$this->CustExist2($id);
				$this->addCusToUser($id, $nc);
				$this->setlinksuser($id);
				} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
			echo "<br>";
		// Данные записываются в базу данных таблица customers при этом в поле userid заносится id пользователя
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
	
function editUserFirm($id, $firm) {
$email = strtolower($firm['em']);
if ($firm['address']=='') $firm['address']=$firm['uradr'];
if($this->checkFirm($firm)) {
	//print_r($firm);
			try {
				$this->db->query('UPDATE  `customers` SET `name`=^Ns, `uradr`=^Ns, `city`=^Ns, `state`=^Ns,`zip`=^Ns,`country`=^Ns, `address`=^Ns, `telmain`=^Ns,`cinn`=^Ns,`ckpp`=^Ns,`crs`=^Ns,`cbank`=^Ns,`cbik`=^Ns,`cks`=^Ns, `tels`=^Ns, `fax`=^Ns, `email`=^Ns,`icq`=^Ns, `cfio`=^Ns WHERE `userid`=^Ni;',$firm['name'], $firm['uradr'],$firm['city'], $firm['state'],$firm['zip'],$firm['country'], $firm['address'],$firm['telmain'],$firm['cinn'],$firm['ckpp'],$firm['crs'],$firm['cbank'],$firm['cbik'],$firm['cks'],$firm['tels'],$firm['social'],$firm['em'],$firm['host'],$firm['cfio'],$id) ;
				} 
				catch(DBException $e) {
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
			echo "<br>";
			if($this->getLevel()== self::USER)$this->addUserRights($id);
		// Данные записываются в базу данных таблица customers 
		//echo "даные занесены в базу данных клиентов";
			return true ;
		} else {
		return false;
		}	


}	
	
	
	function addAdmin($login, $pass, $email) {
		return $this->addUser($login, $pass, $email, self::ADMIN,1,1000);
	}
	
	function addManager($login, $pass, $email) {
		return $this->addUser($login, $pass, $email, self::MANAGER,1);
	}
	
	function addClient($login, $pass, $email, $activate) {
		return $this->addUser($login, $pass, $email, self::CLIENT,$activate);
	}

	function changePass($pass) {
		$this->changePassUser($this->id, $pass);;
	}

	function changePassUser($id, $pass) {
		$hash = md5(md5($pass).md5($this->key));
		//$this->db->query('UPDATE `users` SET `pass` = ^Ns WHERE `id` = ^Ni;', $hash, $id);
		return $this->db->query('UPDATE `users` SET `pass` = ^Ns WHERE `id` = ^Ni;', $hash, $id);
	}
	
	function changeEmail($email) {
		if($this->checkEmail(($email=strtolower($email)))) {
			$this->db->query('UPDATE `users` SET `email` = ^Ns WHERE `id` = ^Ni;', $email, $this->id);
			return true;
		}
		return false;
	}
	
	private function changeLevel($id,$level, $add = 0) {
		$res = $this->db->query('SELECT `level` FROM `users` WHERE `id` = ^Ni;', $id);
		if($res !== null) {
			if($add) $level = $res+$add;
			else $level = $res;
			$this->db->query('UPDATE `users` SET `level` = ^Ni WHERE `id` = ^Ni;', $level, $id);
			return true;
		} else {
			var_dump($res);
			echo 'error';
			return false;
		}
	}
	
	function addManagerRights($id) {
		return $this->changeLevel($id, self::MANAGER, 2);
	}
	
	function addClientRights($id) {
		return $this->changeLevel($id, self::CLIENT, 1);
	}	
	
	function delClientRights($id) {
		return $this->changeLevel($id, self::EDIT_USER, -1);
	}

	function delManageRights($id) {
		return $this->changeLevel($id, self::MANAGER, -2);
	}
	
	function addUserEditRights($id) {
		return $this->changeLevel($id, self::EDIT_USER, 1);
	}
	
	function addUserRights($id) {
		return $this->changeLevel($id, self::USER, 1);
	}
	
	function delUserEditRights($id) {
		return $this->changeLevel($id, self::EDIT_USER, -1);
	}
	
	function changeMs($id, $ms) {
		$res=$this->db->query('UPDATE `users` SET `ms` = ^Ni WHERE `id` = ^Ni;', $ms, $id);
		if($res !== null)return true;
		else return false;
	}
	
	function addActivateCode() {
		if($this->id != 0) {
			$code = md5($this->login.md5($this->key).time());
			$this->db->query('INSERT INTO `userActivate` (`uid`, `code`) VALUES (^Ni, ^Ns);', $this->id, $code);
			return $code;		
		}
		return false;
	}
	
	private function clearOldActivateCode() {
		$this->db->query('DELETE FROM t1, t2 USING `userActivate` as t1, `users` as t2 WHERE t1.time < DATE_SUB(NOW(), INTERVAL 1 WEEK) AND t1.uid = t2.keyid;');	
	}
	
	function checkActivateCode($code) {
		$this->clearOldActivateCode();
		$res = $this->db->query('SELECT `uid` FROM `userActivate` WHERE `code` = ^Ns;', $code);
		if($res !== null) {
			$this->db->query('UPDATE `users` SET `activate` = \'1\' WHERE `keyid` = ^Ni;', $res);
			$this->db->query('DELETE FROM `userActivate` WHERE `code` = ^Ns;', $code);
			
			return true; 		
		}
		return false;
	}
	
	function getUinCode($time = 0) {
		if($time != 0) sleep($time);
		session_set_cookie_params(300);
		session_start();
		if(isset($_COOKIE[session_name()])) {
			setcookie(session_name(), $_COOKIE[session_name()], time() + 300, '/');	
		}
		if(!isset($_SESSION['uin'])) {
			$md = md5($_SERVER['REMOTE_ADDR'].time().$this->key);
			$_SESSION['uin'] = $md;
		}
		return $_SESSION['uin'];
	}
	
	function checkUinCode($code) {
		session_set_cookie_params(300);
		session_start();
		if($this->isGuest()) ini_set(session.use_strict_mode,1);
		if(isset($_SESSION['uin']) && $_SESSION['uin'] == $code) {
			$ret = true;
		} else {
			$ret = false;
		}
		$_SESSION = array();
		if(isset($_COOKIE[session_name()])) {
			setcookie(session_name(), '', 0, '/');
		}
		session_destroy();	
		return $ret;	
	}
	
	function clearUinCode() {
		session_set_cookie_params(300);
		session_start();
		$_SESSION = array();
		if(isset($_COOKIE[session_name()])) {
			setcookie(session_name(), '', 0, '/');
		}
		session_destroy();		
	}
	
	function checkLoginEmail($login, $email) {
		if($this->checkLogin($login) && $this->checkEmail($email)) {
			$res = $this->db->query('SELECT `id` FROM `users` WHERE `login` = ^Ns AND `email` = ^Ns;', $login, $email);
			if($res !== null) return $res;	
		}
		return 0;
	}
	
	public function selmenstr($arropt,$Pth,$chice,$img,$num,$ch='chice',$tich='Найти'){
	$str='<span>';
		//$str.='<select class="poisk" name="'.$ch.'">';
		$str.=Maket::divclasstr('poisk-'.$ch,$Pth,'','','select name="'.$ch.'"');
		$i=0;
		//print_r($arropt);
		foreach($arropt as $val){
			if ($chice[$i] == $num ) $str.='<option selected value="'.$num.'">'.$val.'</option>';
			else $str.='<option value="'.$chice[$i].'">'.$val.'</option>';
		$i++;
		}
		/*while ($elem=each($arropt)){
		if ($chice[$i] == $num ) $str.='<option selected value="'.$num.'">'.$elem['value'].'</option>';
		else $str.='<option value="'.$chice[$i].'">'.$elem['value'].'</option>';
		$i++;
		}*/
	$str.='</select>';	
	if(file_exists($img)) $str.='</select></span><span><input title="'.$tich.'" class="poisk-img" name="'.$ch.'" value="'.$ch.'" type="image" src="'.$img.'"/></span>';
	else $str.='<span><input class="poisk" title="'.$tich.'" type="submit" value="'.$img.'"></span>';	
	return $str;
	}

	
	public function selmen($arropt,$Pth,$chice,$img,$num,$ch='chice',$tich='Найти'){
	echo '<span>';
		//echo '<select class="poisk" name="'.$ch.'">';
		//Maket::divclass('poisk-'.$ch,$Pth,'','','select name="'.$ch.'"');
		echo '<select  class="poisk" name="'.$ch.'">';
		$i=0;
		foreach($arropt as $val){
			if ($i == $num  || $chice[$i]===$num) echo '<option selected value="'.$num.'">'.$val.'</option>';
			else echo '<option value="'.$chice[$i].'">'.$val.'</option>';
		$i++;
		}
		/*while ($elem=each($arropt)){		
		if ($i == $num  || $chice[$i]==$num) echo '<option selected value="'.$num.'">'.$elem['value'].'</option>';
		else echo '<option value="'.$chice[$i].'">'.$elem['value'].'</option>';
		$i++;
		}*/
	echo '</select>';	
	if(file_exists($img)) echo '</span><span><input title="'.$tich.'" class="poisk-img" name="'.$ch.'" value="'.$ch.'" type="image" src="'.$img.'"/></span>';
	elseif($img<>'') echo '<span><input class="poisk" title="'.$tich.'" type="submit" value="'.$img.'"></span>';	
	return $ch;
	}
	
	public function check_domen($domain){ 
		if($domain<>''){
			$whois = new whois;
			$whois->zonelookup($domain);
			echo($domain." - ");
			if($whois->ERROR==0)
				{
				if(is_array($whois->RAWINFO) && count($whois->RAWINFO)>7 && $whois->FOUND==1)
					{
						$res=0;
						echo('занят');
					}else
					{
						$res=1;
						echo('свободен');
						return true;
						}
			}else
			{
				echo('ошибка запроса');
			}
		}
		return false;
		}
	
	public function create_own_site($addres,$tarif){
		$domen='';
		if (strstr($_POST['owndomen'],'www')) {
				$nam_folder=substr($_POST['owndomen'],4);
				}
			else {
				$nam_folder=$_POST['owndomen'];
			}
		//print_r($_GET);
		$bdname=explode('.',$_POST['owndomen']);
		if(!isset($bdname[2]))$nameBD=$bdname[0].'_'.$bdname[1];
		if(strstr($_SERVER["HTTP_HOST"],'deltar.ru')){
			$arrts=array('owndomen','subdomen','sinonim','symlink');
			$arrcall=array('домен второго уровня','домен третьего уровня','без домена','без хостинга');
		}
		else {$arrts=array('owndomen');$arrcall=array('домен второго уровня');}
		//$arrcall=array('домен второго уровня','домен третьего уровня','без хостинга');
		//Придумайте короткое имя для вашего домена
		if(isset($_GET['buzzy']) && $_GET['buzzy']<>'exist') echo '<h2>Домен '.$_GET['buzzy'].' занят</h2>';
		elseif(isset($_GET['buzzy'])) echo '<h2>Домен уже зарегистрирован</h2>';
		echo'Придумайте короткое имя для вашего домена третьего уровня<br>';
		echo'Придумайте короткое имя для вашего домена второго уровня с указанием домена первого уровня, например .ru<br>';
		echo 'Введите в поле имя домена+".ххх"  указав нужную вам зону .ххх только для доменов второго уровня' ;
		echo 'Для домена третьего уровня не забудьте выбрать опцию "Домен третьего уровня"';
		echo '<form method="post" action="'.$addres.'" target="_self">';
		echo '<input type="text" size="15" name="owndomen" value="'.$domen.'">';
		if ($tarif<5) echo '<input type="hidden" name="createdatabase" value="yes">';
		else echo '<input type="hidden" name="createdatabase" value="no">';
		$this->selmen($arrcall,$Pth,$arrts,'Выбрать','owndomen','chice','Тариф');
		echo '</form>';
		if (!isset($_POST['chice'])){
			echo '<br>Для работы с сайтом Вам нет необходимости в отдельном хостинге <br>';
			echo 'В любом случае Ваш сайт располагается на защищеном хостинге надежного провайдера (20 лет мы вместе). <br>';
			echo 'Вам нужно только выбрать имя и тип домена, для доступа к сайту через интернет. <br>';
			echo 'Есть три уровня работы с сайтом: <br>';
			echo '<br>Первый (основной, платный):<br><br>';
			echo 'При использовании домена второго уровня платные условия представлены <a href="">здесь</a><br>';
			echo 'При использовании домена третьего уровня платные условия представлены <a href="">здесь</a><br>';
			echo '<br>Второй (начальный, бесплатный):<br><br>';
			echo 'Режимы без регистрации домена и тестовый являются бесплатными, но имеют ограничения по возможностям <a>см. здесь</a><br>';
			echo 'Без регистрации домена вы можете использовать готовые шаблоны,наполнять их своей информацией, но не можете изменять дизайн выбраного шаблона<br>';
			echo 'Данный режим позволяет вам создать свой сайт с акцентом на его содержание.<br>';
			echo 'После того как вы создали наполнение сайта вы можете перейти на другой уровень работы,<br>';
			echo 'зарегистрировав домен второго или третьего уровня на платной основе<br>';
			echo '<br>Третий (тестовый, ознакомительный):<br><br>';
			echo 'В тестовом режиме вы можете менять сайт в рамках предусмотренного алгоритма<br>';
			echo 'и знакомитесь с функционалом готового сайта<br>';
			echo 'Если Ваш домен второго уровня находится не на нашем хостинге,<br>';
			echo 'то нужно его перенести, отправив <a href="">Заявку</a>, <br>';
			echo 'а если вы хотите обращаться к сайту c другого ресурса<br>';
			echo 'установите на странице, с которой вы хотите переходить на главную страницу сайта<br>';
			echo 'следующий HTML-код:<!--<head>
						<title>redirect</title>
						<meta http-equiv=Refresh content="0; url=http://{Ваш_домен_второго уровня_}.deltar.ru;" 
						</head>--><br>'; 
			echo 'или организуйте переход на указанную страницу иным способом.';
			echo ' Затем вы просто региструете на сайте домен третьего уровня <br>';
			echo ' {Ваш_домен_второго уровня_}.deltar.ru';
			echo 'После чего вы сможете начать работу с сайтом.';
		}
		//Какой хостинг вы хотите использовать
if(isset($_POST['chice'])){
		switch ($_POST['chice']){
			case 'ownbd':
			//создается персональная база данных
			{
				
			
				
				
				break;
			}
			//вы региструете домен второго уровня на нашем хостинге 
			case 'owndomen':
			{
				echo 'Сайт на домене второго уровня вы можете создать если подключили его к нашему хостингу<br>';
				break;	
			}
			//вы региструете домен третьего уровня на 
			//нашем хостинге как субдомен одного из доменов второго уровня
			case 'subdomen':
			{
				
				break;		
			}
			// вырегистрируете синоним уже существующего домена
			case 'sinonim':
			{
				
			break;	
			}
			// Работаете с пробным сайтом по выбору. Тестовый режим.
			case 'symlink':
			{
				
			break;	
			}
		}
}		
		
		
		//Проверяется уникальность имени в системе
		
		//Делается запрос владельцу хостинга по регистрации имени
		
		//Если имя зарегистрировано, то происходит процедура
		//регистрации сайта в системе
		
		//Если выбран тестовый режим, то вы работаете с теситовым сайтом по выбору
		
	}
	
	public function grandeditor($table,$tabl,$np,$view=0){
			$str='';
			switch($table){
				case $tabl['pages']:
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?np='.$np.'&editp=ok" accesskey="p"> edit </a>';
						echo '<a title="Добавить" href="../'.$this->graphp.'?np='.$np.'&editp=new" accesskey="n"> p+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?np='.$np.'&editp=ok" accesskey="p"> edit </a><a title="Добавить" href="../'.$this->graphp.'?np='.$np.'&editp=new" accesskey="n"> p+ </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?np='.$np.'&editp=ok" accesskey="p"></a>';
						echo '<a type="hidden" href="../'.$this->graphp.'?np='.$np.'&editp=new" accesskey="n"></a>';
					}
					break;
				}	
				case 'allmakets':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=allmakets&par='.$np.'" accesskey="m"> Настройка макета сайта </a>';
						echo '<a title="Добавить" href="../'.$this->graphp.'?editp=new&tab=allmakets" accesskey="w"> m+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&tab=allmakets&par='.$np.'" accesskey="m"> Настройка макета сайта </a>
						<a href="../'.$this->graphp.'?editp=new&tab=allmakets" accesskey="w">m+</a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=ok&tab=allmakets&par='.$np.'" accesskey="m"></a>';
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab=allmakets" accesskey="w"></a>';
					}
					break;
				}	
				case 'configs':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=configs&par='.$np.'" accesskey="s"> Редактирование данных </a>';
						echo '<a title="Добавить" href="../'.$this->graphp.'?editp=new&tab=configs" accesskey="t"> cs+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&tab=configs&par='.$np.'" accesskey="s"> Редактирование данных </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab=configs" accesskey="t"></a>';
					}
					break;
				}
				case 'configm':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=configm&par='.$np.'" accesskey="s"> Редактирование данных </a>';
						echo '<a title="Добавить" href="../?editp=new&tab=configm" accesskey="t"> cs+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&tab=configm&par='.$np.'" accesskey="s"> Редактирование данных </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab=configm" accesskey="t"></a>';
					}
					break;
				}
				case 'configp':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=configp&par='.$np.'" accesskey="s"> Редактирование данных </a>';
						echo '<a title="Добавить" href="../?editp=new&tab=configp" accesskey="t"> cs+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&tab=configp&par='.$np.'" accesskey="s"> Редактирование данных </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab=configp" accesskey="t"></a>';
					}
					break;
				}
				case 'scripts':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=scripts&par='.$np.'" accesskey="s"> Редактирование данных </a>';
						echo '<a title="Добавить" href="../?editp=new&tab=scripts" accesskey="t"> cs+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&tab=scripts&par='.$np.'" accesskey="s"> Редактирование данных </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab=scripts" accesskey="t"></a>';
					}
					break;
				}
				case 'fonts':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=fonts&par='.$np.'" accesskey="s"> Редактирование данных </a>';
						echo '<a title="Добавить" href="../?editp=new&tab=fonts" accesskey="t"> cs+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&tab=fonts&par='.$np.'" accesskey="s"> Редактирование данных </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab=fonts" accesskey="t"></a>';
					}
					break;
				}
				case 'customers':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&cust='.$np.'" accesskey="c"> Редактирование данных </a>';
						//echo '<a title="Добавить" href="?np='.$np.'&editp=ok&tab=customers" accesskey="t"> c+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&cust='.$np.'" accesskey="c"> Редактирование данных </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&cust='.$np.'" accesskey="t"></a>';
						//echo '<a type="hidden" href="?np='.$np.'&editp=ok&tab=customers" accesskey="w"></a>';
					}
					break;
				}
			case $tabl['news']:
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=new&in='.$np.'" accesskey="b"> Редактирование блога </a>';
						echo '<a title="Добавить" href="../'.$this->graphp.'?editp=new&in" accesskey="t"> b+ </a>';
					}
					elseif($view==2)$str.='<a type="hidden" href="../'.$this->graphp.'?editp=ok&in='.$np.'" accesskey="b"></a><a type="hidden" href="../'.$this->graphp.'?editp=new&in" accesskey="t"></a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=ok&in='.$np.'" accesskey="b"></a>';
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&in" accesskey="t"></a>';
					}
					break;
				}	
				case 'namparams':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=namparams&par='.$np.'" accesskey="e"> Настройка таблицы </a>';
						//echo '<a title="Добавить" href="../'.$this->graphp.'?editp=new&tab=namparams" accesskey="n"> t+ </a>';
					}
					elseif($view==2)$str.='<a href="../'.$this->graphp.'?editp=ok&tab=namparams&par='.$np.'" accesskey="e"> Настройка таблицы </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=ok&par='.$np.'" ></a>';
						//echo '<a type="hidden" href="../'.$this->graphp.'?editp=newtab=namparams" ></a>';
					}
					break;
				}
				case $tabl['elem']:
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab='.$tabl['elem'].'&id='.$np.'" accesskey="e"> Настройка таблицы </a>';
						echo '<a title="Добавить" href="../'.$this->graphp.'?editp=new&tab='.$tabl['elem'].'&id=25" accesskey="r"> t+ </a>';
					}
					elseif($view==2)$str='<a type="hidden" href="../'.$this->graphp.'?editp=ok&tab='.$tabl['elem'].'&id='.$np.'" accesskey="e"></a><a type="hidden" href="../'.$this->graphp.'?editp=new&tab='.$tabl['elem'].'" accesskey="r"></a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=ok&tab='.$tabl['elem'].'&id='.$np.'" accesskey="e"></a>';
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab='.$tabl['elem'].'" accesskey="r"></a>';
					}
					break;
				}
				case $tabl['str']:
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab='.$tabl['str'].'&id='.$np.'" accesskey="s"> Настройка таблицы </a>';
						echo '<a title="Добавить" href="../'.$this->graphp.'?editp=new&tab='.$tabl['str'].'" accesskey="d"> t+ </a>';
					}
					elseif($view==2)$str.='<a href="../'.$this->graphp.'?editp=ok&tab='.$tabl['str'].'&id='.$np.'" accesskey="s"> Настройка таблицы </a>';
					else {
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=ok&tab='.$tabl['str'].'&id='.$np.'" accesskey="s"></a>';
						echo '<a type="hidden" href="../'.$this->graphp.'?editp=new&tab='.$tabl['str'].'" accesskey="d"></a>';
					}
					break;
				}
				case 'allsites':
				{
					if ($view==1) {
						echo '<a href="../'.$this->graphp.'?editp=ok&tab=allsites&par='.$np.'" > Настройка таблицы </a>';
						//echo '<a title="Добавить" href="../'.$this->graphp.'?editp=new&tab=allsites" > t+ </a>';
					}
					elseif($view==2) $str.='<a href="../'.$this->graphp.'?editp=ok&tab=allsites&par='.$np.'" > Настройка таблицы </a>';
					break;
				}
		}	
	if($view==2) return $str;
	}
	
	function isValidEmail($email){ 
    return filter_var($email, FILTER_VALIDATE_EMAIL) !== false;
}

	public function Ownerviewer($arr, $Pth,$mode=1){
		if($mode<>1) $str=' ';
		else $str='<br>';
		$ownerdata='';
		//print_r($arr['owner']);
		//print_r($Pth['adm']);
		if (isset($arr['owner']) && isset($Pth['adm']))	{
		//Вывод регистрационных данных пользователя
		$ownerdata.='<span>'.$arr['owner']->name.'</span>'.$str;
		if ($arr['owner']->telmain <> "" && $arr['owner']->email <> "") {
		if ($arr['owner']->telmain<>'no' && $arr['owner']->telmain<>'') $ownerdata.=$str.'<span>'.$arr['owner']->telmain.'</span>';
		if ($this->isValidEmail($arr['owner']->email )) $ownerdata.=$str.'<span>'.$arr['owner']->email .'</span>';  
		//
		}
		$ownerdata=maket::divcltr($ownerdata,$Pth,'owner');
		}
		elseif (isset($arr['user'])){
			$ownerdata.='</span><span>'.$arr['user'][2].'</span>'.$str;
			if ($arr['user'][3]<> '') {
			if ($this->isValidEmail($arr['user'][3])) $ownerdata.=$str.'<span>'.$arr['user'][3].'</span>';  
			}
		}
		else $ownerdata.=maket::divcltr('<span>'.date("d m Y").' '.'</span><span>Гость</span>',$Pth,'owner');
		//$ownerdata='<span>'.$ownerdata.'</span>';
		if($mode==1) echo $ownerdata;
	
	return $ownerdata;
	}
	
	public function Userviewer($arr,$clas,$Pth='',$mode=1){
		//вывод данных о пользователе над шапкой сайта
		if (isset($arr['user'])){
			$user_data=Maket::divclasstr($clas,$Pth,'','','span').$arr['user'][2].'</span>';
			if($mode==1) echo $user_data;
			return $user_data; 
		}
		return null;
	}
	
	public function Localviewer($Pth){
		$user_data=Maket::divclasstr('user',$Pth,'','','span').'LocalAdmin'.'</span>';
		return $user_data; 	
	}
	
	function showpoiskempty($Pth,$w='Найти',$t='text',$s=10,$m=50){
	$find='<form style="align:left;" method="post">';
	$find.=Maket::spanclasstr(Maket::divclasstr('poisk',$Pth,'','','input name="poisk-chice" placeholder="'.$w.'" maxlength="'.$m.'" size="'.$s.'" type="'.$t.'"').'</input>',$Pth,'poisk-chice');
	 
	$vendors=array('APC','HP');
	$vend=array('1','2');
	$find.=$this->selmenstr($vendors,$Pth,$vend,'./images/searchh.gif','');
	$find.='</form>';
	return $find;
}

	public function Maketblock(){
		
		
	}

	public function CartBlock($Pth,$mode=0){
		if(isset($_SESSION['items']) && $_SESSION['total_price']>0){
			$shop=Maket::divclasstr('cart',$Pth,'','','ul').'<li><a href="./book/show_cart.php"><img src="images/cart-1.png" alt="Посмотреть заказы" /> </a><a href="./book/show_cart.php?reset">x</a></li>';
			$shop.='<li> Общая сумма = '.number_format($_SESSION['total_price'],2).'</li></ul>';
		}
		else {
			$shop='<ul class="shop-butt0">';
			if(isset($_SESSION['total_price']))$shop.=$_SESSION['total_price'];
			else $shop.='0.00';
			$shop.=Maket::divclasstr('cart',$Pth,'','','ul').'<img src="images/cart-1.png" alt=" Empty Cart" /><p><a href="javascript:;" class="simpleCart_empty"></a></p></ul>';
		}
	if($mode==0)return $shop;	
	else echo $shop;
	}

	public function Shopblock($arr,$lev,$vendors,$Pth,$mode=0){
		if ($lev==2) {
			$shop='';
			$cust=$this->idUser($this->id);
			if(!$cust)return null;
			if($this->isExistCust($this->id) && $cust->cinn=='')$shop.=Maket::spanclasstr(Maket::spanclasstr('Регистрация',$Pth,'serv','a href="./?editp=ok&cust='.$this->customerid.'"','Анонимный доступ имеет ограниченную функциональность'),$Pth,'serv');
			elseif($cust->cinn<>'') $shop.=Maket::spanclasstr('ИНН:'.$cust->cinn,$Pth,'shop-inn');
		}
			$numpage=$arr['nump'];	
			if (isset($_GET['vend'])) $vend=$_GET['vend'];
			else $vend='';	
			$tabl=$arr['tabl'];
			//if(isset($Pth['global']['Sizes'][1]))$size_pars1=$Pth['global']['Sizes'][1];
			$numelem=$this->getscountab($tabl['elem'],'id','c');
			
			//$numelem['id'][]='';
			
			if($numelem) {
				if(!isset($shop))$shop='';
				if (isset($_GET['np'])) $current=$_GET['np'];
				elseif (isset($_POST['np'])) $current=$_POST['np'];
				else $current=$numpage;
				if (!$vend=='') $choice_vendors[]=$vend;
				$shop.='<form style="align:left; " method="post" action="/?np='.$numpage.'" target="_blanc">';
				$shop.='<input name="poisk" placeholder="Поиск" maxlength="20" size="10" type="text" /></span>';
				//if (!$vend=='') $shop.='Показывать продукцию только производителя:'.$vend.'  ';
				//else $shop.=' Выбрать производителя ';
				if(!empty($choice_vendors)){
					foreach($choice_vendors as $val)$shop.=$val['value'];	
					}
					//while ($elem=each($choice_vendors)) {$shop.=$elem['value'];	}		
				
				//echo '<span >';
				$shop.='<select name="vend">';
				foreach($vendors as $val)$shop.='<option>'.$val.'</option>';
				
				$shop.='<input value="" type="image" src="./images/searchh.gif"/></form>';
				
			}
			elseif($lev>4) {
				$shop='<li>'.$this->showpoiskempty($Pth).'</li>';
			}
			
		if(isset($shop)){
			$shop.='</ul>';
		if($mode==1)echo $shop;
		else return $shop;
		}
}
	
	public function linkp($arr){
		if($arr<>'')$buthref='href="'.$arr['hrefp'].'np='.$arr['numpage'].'"';
		else $buthref='href="#"';
		return $buthref;
	}
	
	public function Serviceblock($sp,$lev,$Site,$Pth,$mode=0){
		$this->uid=$this->getuserid();
		$cid = $this->getusercid();
		$serv='';
		if($lev >0 ){
		switch ($lev){
			case '2':{
				
			break;
			}
			case '1':{
			
			break;
			}
		}
		if($lev>1){
			 $serv.='<li>'.$this->whoareyouhere().' '.$this->getLogin().'</li><li>';
			}
		 else 	$serv.='<span>'.$this->whoareyouhere().'</span><span><a href="./?editp=ok&cust='.$cid.'" accesskey="c"> Подтверждение личности </a></span><li>'; 
		$serv.='<span><a href="./?np='.$sp.'"> Главная </a></span>';
		if($lev>0)$serv.='<span><a  href="./auth/?logout"> Выйти </a></span>';
		if($lev>2)$serv.='<span><a href="./settings/?account">Настройки</a>';	
		echo '</li>';
		}
	else {
	
	if ($lev==0) {
		$serv.='<li><span><a href="./registration/"> Регистрация </a></span>';
		$serv.='<span><a href="./auth/"> Войти </a></span></li>';
	}
	if ($lev<0) $serv.='<li><span><a href="./auth/"> Вход для пользователей</a></span></li>';
	
		
	}
	
	if($mode==1)echo $serv;
	else return $serv;
	}
	private function superadmin(){
		if($this->getuserid() == 1)return true;
		else return false;
	}
	
	function isSuperAdmin(){
		return $this->superadmin();
	}
	
	function whoareyouhere($lev='',$inlev=true){
		//print_r($this->db->init_data);
		if($lev === '')$lev=$this->getLevelnew();
		else $lev=intval($lev);
		if($this->isSuperAdmin() && $lev == 6)$you='Суперадмин';
		elseif($lev>4) {
			$you='Администратор';
			}
		elseif($lev>3) {
			$you='Менеджер';
			if($this->getMs() === USER::PRODUCTMANAGER) $you='Продакт менеджер';
			elseif($this->getMs() === USER::SEOMANAGER) $you='SEO менеджер';
			elseif($this->getMs() === USER::DESIGNMANAGER) $you='Дизайн менеджер';
			elseif($this->getMs() === USER::CONTENTMANAGER) $you='Контент менеджер';
			elseif($this->getMs() === USER::ANALITICMANAGER) $you='Аналитик менеджер';
			elseif($this->getMs() === USER::GENERALMANAGER) $you='Главный менеджер';
			$you .= ' ' .$this->getLogin();
			}
		elseif($lev>2) {
		 	$you='Клиент '.$this->getLogin();
			}
		elseif($lev>1) {
		 	$you='Пользователь '.$this->getLogin();
			}	
		elseif($lev==1) {
		 	$you='Посетитель' ;
			}		
		else $you='Гость';	
	if($inlev)return $you.'('.$lev.')';
	else return $you;
	}
	
	function stringusermen($clas='',$Pth='',$ngust=0,$Site,$numpage=''){
		if (isset($Pth['adm']['np']))$numpage=$Pth['adm']['np'];
		//elseif($numpage<>'') $numpage=$_GET['np'];
		$href=$Pth['prot'].$Site->domen;
		if($this->getLevelnew()>=5 && !isset($_GET['editp']) ) {
			if(!isset($_GET['other'])) {
			echo '<div class="serv">';
			if($Pth<>'' && $numpage !='')echo '<span><a href="'.$href.'/?editp=ok&np='.$numpage.'"> Изменить ('.$numpage.') </a>';
			echo '<a href="'.$href.'/?editp=new"> Добавить </a></span>';
			echo '<span><a href="'.$href.'/settings/?other"> Профиль </a>';
				}
			}
		elseif($this->getLevelnew()>3) {
			echo '<span><a href="'.$href.'/settings/?other">Настройки меджера</a></span>';
			}
		elseif($this->getLevelnew()>2) {
			echo '<span><a href="'.$href.'/settings/?other">Настройки клиента</a></span>';
			}
		else Maket::spanclass($this->whoareyouhere($ngust),$Pth,'user');	
		
		echo '<span class="user" ><a href="'.$href.'"> Главная </a></span>';
		if($this->getLevelnew()==0)echo '<span class="user" ><a href="'.$href.'/auth/">Войти</a></span>';
		else echo '<span class="user" ><a href="'.$href.'/auth/?logout">Выйти </a></span>';
		echo '</div>';	
		}

	
	function stringusermenOld($clas='',$Pth='',$ngust='',$localpth='',$numpage=''){
		if($Pth<>'')if (isset($Pth['adm']['np']))$numpage=$Pth['adm']['np'];
		//elseif($numpage<>'') $numpage=$_GET['np'];
		
		if($this->getLevelnew()>=5 && !isset($_GET['editp']) ) {
			if(!isset($_GET['other'])) {
			echo '<div class="serv">';
			if($Pth<>'' && $numpage !='')echo '<span><a href="/?editp=ok&np='.$numpage.'"> Изменить ('.$numpage.') </a>';
			echo '<a href="/?editp=new"> Добавить </a></span>';
			echo '<span><a href="../settings/?other"> Профиль </a>';
				}
			}
		elseif($this->getLevelnew()>3) {
			echo '<span><a href="../settings/?other">Настройки меджера '.$this->whoareyouhere().'</a></span>';
			}
		elseif($this->getLevelnew()>2) {
			echo '<span><a href="../settings/?other">Настройки клиента '.$this->whoareyouhere().'</a></span>';
			}
		else Maket::spanclass($this->whoareyouhere(),$Pth,'user');	
		
		echo '<span class="user" ><a href="/"> Главная </a></span>';
		if($this->getLevelnew()==0)echo '<span class="user" ><a href="'.$localpth.'/auth/">Войти</a></span>';
		else echo '<span class="user" ><a href="'.$localpth.'/auth/?logout">Выйти </a></span>';
		echo '</div>';	
		}
		
		
	function existfile_incepart($file,$comment){
		if(file_exists($file)) {include($file);return true;}
		else {echo '<info class="hidno">'.$comment.'</info>';return false;}
	}

	public function isthatsite($site, $np, $table){
	$res=$this->db->query('SELECT `numpage`,`site` FROM `'.$table.'` WHERE `numpage` = ^Ni and `site` = ^Ns;', $np, $site);
	if($res) return $res;
	else {
		$res=$this->db->query('SELECT `numpage`,`site` FROM `'.$table.'` WHERE `title` = ^Ns and `site` = ^Ns;', 'main_gra_all', $site);
		if($res) return $res;
		else return false;
	}
}
	
	function getPagetable($numpage){
		$tabl=$this->getsitetables($_SERVER['HTTP_HOST']);
		$res = array();
		if($numpage != 0) {
		//$this->numpage=$numpage;
		$res = $this->db->query('SELECT * FROM `elemap` WHERE `codeGJS` = ^Ni;', $numpage);
		//print_r($res->desc);
		if($res === null) 
				//echo ' '.$numpage; 
				//throw new StructureWException('numpage does\'t exist', StructureWException::ID_ERROR);	
				//exit('Ссылка на несуществующую страницу');
				return;
			}
			$return['pages'] = array();
			if (isset($res->desc))$arrpg=explode('>|<',$res->desc);
			else return false;
			$namepage=$arrpg[0].'|'.$arrpg[1].'|'.$res->name.'|'.$arrpg[18].'|'.$arrpg[19];
			if($res !== null) {
			if(!is_array($res)) {
				$return['pages'][] = array('numpage' => $res->codeGJS,'namep' => $namepage,'lozungp' => $arrpg[2], 'keywords' => $res->titles, 'buttons' => $arrpg[3],'hrefp' => $arrpg[17], 'typemenu' => $arrpg[12], 'hrefscripts' => $arrpg[14], 'hrefstyle' => $arrpg[15],'title' => $arrpg[16], 'content' => $arrpg[4], 'levelmenu' => $arrpg[13],'idmenu' => $arrpg[11], 'hrefimage' => $arrpg[10], 'list' => $arrpg[5], 'list_href' => $arrpg[6],'butthref' => $arrpg[7], 'buttimg' => $arrpg[9], 'imgtext' => $arrpg[8], 'idnews' => $res->links,'site' => $res->domen, 'idauthor' => $res->idauthor,'idm'=>$res->idm,'configpage'=>$res->configpage);				

			} else {
				foreach($res as $val){
					$arrpg=explode('>|<',$val->desc);
					$namepage=$arrpg[0].'|'.$arrpg[1].'|'.$val->name.'|'.$arrpg[18].'|'.$arrpg[19];
					$return['pages'][] = array('numpage' => $val->codeGJS,'namep' => $namepage,'lozungp' => $arrpg[2], 'keywords' => $val->titles, 'buttons' => $arrpg[3],'hrefp' => $arrpg[17], 'typemenu' => $arrpg[12], 'hrefscripts' => $arrpg[14], 'hrefstyle' => $arrpg[15],'title' => $arrpg[16], 'content' => $arrpg[4], 'levelmenu' => $arrpg[13],'idmenu' => $arrpg[11], 'hrefimage' => $arrpg[10], 'list' => $arrpg[5], 'list_href' => $arrpg[6],'butthref' => $arrpg[7], 'buttimg' => $arrpg[9], 'imgtext' => $arrpg[8], 'idnews' => $val->links,'site' => $val->domen,'idauthor' => $val->idauthor,'idm'=>$val->idm);			
				}
			}
	}
	else $return=false;	
	//print_r($return);
	return $return;
	}
	
	public function read_namparams($table){
		$res2=$this->db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
		$arrnm=$res2->nampars;
		$arrtp=$res2->types;
		$arrdlm=$res2->delimiter;
		$mass_zags=explode('|',$arrnm);
		$mass_zakls=explode('|',$arrtp);
		$return=array($mass_zags,$mass_zakls,$arrdlm);
		return $return;
	}
}
?>