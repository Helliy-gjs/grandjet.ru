<?php
class Pay extends Singleton {
	private $balans=0;
	protected function __construct() {
		$this->db = Singleton::getInstance('DB');
	}
	
	function payform($class,$Pth,$balans,$summ,$txt){
		if(!isset($Pth['adm']['idm']))$Pth['adm']['idm']='';
		if(!is_array($txt))$txt=array('','',$txt);
		Maket::divclass($class,$Pth,'font-size:14px;font-style: bold;display:flex;justify-content:space-between;vertical-alighn: center;');
		if($balans>0)$str_bal=Maket::spanclasstr($txt[0].'  '.$balans,$Pth,'balans-'.$Pth['adm']['idm']);
		else $str_bal='';
		echo $str_bal.Maket::spanclasstr($txt[1],$Pth,'loz-balans-'.$Pth['adm']['idm']);
		
	Maket::spanclass(Pay::oplataYD('pay-'.$Pth['adm']['idm'],$txt[2].'  ',$summ),$Pth);
	
		echo '</div>';
	}
	
	function sponsorpay($Pth,$order_id,$targets,$summ){
		if(!isset($Pth['adm']['idm']))$Pth['adm']['idm']='';
		Maket::divclass('sponsor-'.$Pth['adm']['idm'],$Pth,'display:flex;justify-content:center;flex-direction:column;');
		echo 'Если вам нравится проект grandjetstudio вы можете поддержать его тут';
		show::oplataYD($order_id,$targets,$summ);
		echo '</div>';

	}
	
	function promocodpay($Pth, $summ, $bals,$uid){
		if(!isset($Pth['adm']['idm']))$Pth['adm']['idm']='';
		$user = Singleton::getInstance('User');
		$user->check();
		Maket::divclass('promocod-'.$Pth['adm']['idm'],$Pth,'display:flex;justify-content:center;flex-direction:column;');
		if(!isset($_POST['creditType']) && !$user->isGuest() && !$user->isManager()){
			if($user->getLevelnew() < USER::EDIT_USER)$str='Введите ваш промокод';
			elseif($user->getLevelnew() < USER::MANAGER)$str='Изменить роль';
			echo '<form method="POST" action="">';
			echo '<input class="button" type="submit" value="   Отправить  ">';
			echo '<label><input type="text" name="creditType" value="">'.$str.$uid.'</label></form>';
			}
			elseif(isset($_POST['creditType'])) {
				if($bals < 1000){
					$bals=$user->add_balans($summ,$uid);
				} 
				elseif($bals > 1000 && $user->getLevelnew() < USER::MANAGER && $_POST['creditType']==='productmanager'){
				if($user->addManagerRights($uid))
					$user->changeMs($uid, USER::PRODUCTMANAGER);
					else echo 'You are not productmanager yet';
						
				}
				elseif($bals > 1000 && $_POST['creditType']==='payclient') {
					if($user->getMs()!==0 ){
						$user->changeMs($uid, USER::PAYCLIENT);
						echo 'You are not any manager now';
					}
					else echo 'You are not payclient  yet';
				}
				elseif($bals > 1000 && $user->getLevelnew() == USER::EDIT_USER && $_POST['creditType']==='seomanager') {
					if($user->getMs()==0 ){
						$user->addClientRights($uid);
						$user->changeMs($uid, USER::SEOMANAGER);
						echo 'You are seomanager now';
					}
					else echo 'You are not seomanager yet';
				}
				elseif($bals > 1000 && $user->getLevelnew() == USER::EDIT_USER  && $_POST['creditType']==='designmanager') {
						if($user->getMs() == 0 ){
							$user->changeMs($uid, USER::DESIGNMANAGER);
							$user->addClientRights($uid);
							echo 'You are designmanager now';
						}
						else echo 'You are not designmanager yet';
				}
				elseif($bals > 1000 && $user->getLevelnew() == USER::EDIT_USER  && $_POST['creditType']==='contentmanager') {
						if($user->getMs()==0 ){
							$user->changeMs($uid, USER::CONTENTMANAGER);
							$user->addClientRights($uid);
							echo 'You are contentmanager now';
						}
						else echo 'You are not contentmanager yet';
				}
				elseif($bals > 1000 && $user->getLevelnew() == USER::EDIT_USER && $_POST['creditType']==='analiticmanager') {
						if($user->getMs()==0 ){
							$user->changeMs($uid, USER::ANALITICMANAGER);
							$user->addClientRights($uid);
							echo 'You are analiticmanager now';
						}
						else echo 'You are not analiticmanager yet';
				}
				elseif($bals > 1000 && $user->getLevelnew() == USER::EDIT_USER  && $_POST['creditType']==='manager') {
						if($user->getMs()==0  ){
							$user->changeMs($uid, USER::MANAGER);
							$user->addManagerRights($uid);
							echo 'You are productmanager now';
						}
						else echo 'You are not productmanager yet';
				}
				elseif($bals > 1000 && $user->getLevelnew() > USER::MANAGER && $_POST['creditType']==='generalmanager') {
						if($user->getMs()==0 ){
							$user->changeMs($uid, USER::GENERALMANAGER);
							$user->addManagerRights($uid);
							echo 'You are generalmanager now';
						}	
						else echo 'You are not generalmanager yet';
					}
				}	
				else {
				header('Location https://'.$_SERVER['HTTP_HOST']);
				exit();
			}
		
		echo '</div>';
	}
	
	private function add_balans($sum,$uid){
		
		$balans=$this->db->query('SELECT `balans` , `siid` FROM `users` WHERE `id` =^Ni;',$uid);
		echo 'Пополнение баланса '.$balans->balans.' по промокоду '.$_POST['creditType'];
		if (!isset($balans->balans))$this->balans=0;
		else $this->balans = $balans->balans;
		//if($sum>0){
			$this->balans+=$sum;
			$subject='Пополнение баланса ';
			$tabl['news']='news';
			$lpn=$this->getscountab($tabl['news'],'idnews', 'f');
			
			$mes='Клиент '.$uid.' ('.$balans->balans.') пополняет баланс  на сумму '.$sum;
			$nn[0]=array('idauthor'=>$uid,'name'=>$subject,'newstext'=>$mes,'idnews'=>($lpn+1),'vendor'=>'service','group'=>'balans','imgnews'=>'faviconjpg.jpg','codgjsnews'=>'','hrefnew'=>'','numpagat'=>0,'site'=>$balans->siid);
			$this->db->autocommit(FALSE);
			$this->db->start();
			
			try {
				$this->db->query('UPDATE  `users` SET `balans`=^Ni WHERE `id`=^Ni;',$this->balans,$uid);
				//Utils::prepare_news($nn,$tabl,$this->db);
				$emladm=$this->whatemail(1,1);
				Utils::sendMail($this->getEmail(), $subject, $mes, $emladm,$uid);
				}
				catch(DBException $e) {
				echo 'ERROR UPDATE';	
				if($e->getErrno() == 1062) return false;
				else throw $e;
			}
		if (mysql_errno() == '') {
			$this->db->commit(); 
			$this->db->autocommit(TRUE);
			if (mysql_errno()) echo '<div class="info">ERROR commit-'.mysql_error().'</div>';
			echo '<div class="hidno">Транзакция пополнения баланса закрыта</div>';
			echo '<div class="hidno">Баланс пополнен:'.$this->balans.' </div>';
			}
		else {
			$this->db->rollback();
			echo '<div class="info">Транзакция пополнения баланса отменена</div>';
	}	
		//}
	return $this->balans;
	}
	
	function getEmail() {
		$user=User::check();
		return $user->email;
	}
	
	function getBalans(){
		return $this->balans;
	}
	
	static function oplataYD($order_id,$targets,$summ){
		
		$form= '<form method="POST" action="https://money.yandex.ru/quickpay/confirm.xml">
		<input type="hidden" name="receiver" value="410016460239306">
		<input type="hidden" name="formcomment" value="Проект «grandjetstudio»: сайты нового поколения">
		<input type="hidden" name="short-dest" value="Проект «grandjetstudio»">
		<input type="hidden" name="quickpay-form" value="donate">
		<input type="hidden" name="targets" value="транзакция{'.$targets.'} {'.$order_id.'}">
		<input type="hidden" name="comment" value="Что вы ожидаете от проекта для себя?">
		<input type="hidden" name="need-fio" value="true">
		<input type="hidden" name="need-email" value="true">
		<input type="hidden" name="need-phone" value="false">
		<input type="hidden" name="need-address" value="false">';
		if ($order_id<>'donat') {
		$form.='<input type="disabled" name="sum" value="'.$summ.'" data-type="number">(руб.)   ';
		$form.='<input type="hidden" name="label" value=" Донат ">';
		}
		else {
		$form.='<input type="hidden" name="label" value="По заказу '.$order_id.'">';
		$form.='<input size="10" type="text" name="sum" value="'.$summ.'" data-type="number">(руб.)   '; 
	}
	$form.='<input type="submit" value="   Перевести  ">';
	$form.='<label><input type="radio" name="paymentType" value="PC"> Яндекс.Деньгами </label>
    <label><input type="radio" name="paymentType" value="AC"> Банковской картой </label></form>';
	return $form;
	}
	
	function whatemail($id,$site){
	$res = $this->db->query('SELECT `email` FROM `users` WHERE `id` = ^Ni AND `siid` = ^Ni;', $id,$site);
		if(!isset($res)) return false;
		else return $res;
	}
	
	function getscountab($tab,$key,$mode){
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


private function initbdF($domen){
	if (isset($domen)) $this->domen=$domen;
	if (strstr($this->domen,'www')) {
			$this->domen=substr($this->domen,4);
		}
	if ($this->domen <> "") {
	$res=$this->db->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`css`,`script`,`images`,`pages`, `news`,`element`,`structure`,`desc_site` FROM `Allsites` WHERE `domen` = ^Ns;', $this->domen);	
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