<?php
class StructureW extends Singleton {
	private $numpage,
			$db = null;
	private $numnews = 0;		
	private $sectionsArr = array();
	
	protected function __construct() {
		$this->db = Utils::loadbdsite($_SERVER['HTTP_HOST']); 
		//echo 'construct SWE OK';
	}
	
	public function getBDloaded(){
		return $this->db->init_data;
	}
	
	private function checkpid($pid) {
		if($this->db->query('SELECT `id` FROM `structure` WHERE `id` = ^Ni;', $pid) === null) return true;
		else return false;
			//throw new StructureWException('pid doesn\'t exist', StructureWException::PID_ERROR);
	}
	
	private function checkid($id,$tab='structure') {
		if($id != 0 && $this->db->query('SELECT `id` FROM `'.$tab.'` WHERE `id` = ^Ni;', $id) === null)
			return false;
			//throw new StructureWException('id does\'t exist', StructureWException::ID_ERROR);		
	}
	
	/*private function checkid($id) {
		if($id != 0 && $this->db->query('SELECT `id` FROM `structure` WHERE `id` = ^Ni;', $id) === null)
			throw new StructureWException('id does\'t exist', StructureWException::ID_ERROR);		
	}*/
	
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

	private function addSectionPage($id,$pid, $name,$uid,$ids) {
		$this->db->query('INSERT INTO `mapsites` (`id`,`name`, `pid`,`typeF`,`NumEl`,`idauthor`,`ids`) VALUES (^Ni,^Ns,^Ni,^Ni,^Ni,^Ni,^Ni);',$id,$name,$pid,0,1,$uid,$ids);
		return $id++;	
	}
	
	private function addSectionsPages($pids, $names) {
		foreach($pids as $key=>$val) {
			if($key==0)$id=$val;
			else $id=$this->addSectionPage($id, $name[$key]);
		}
		
		return $id;	
	}
	
	function addElemap($codeGJS, $name, $desc, $keywords, $titles, $price, $tid) {
		$this->db->query('INSERT INTO `elements` (`codeGJS`, `name`, `desc`, `art`, `vendor`, `price`) VALUES (^Ns, ^Ns, ^Ns, ^Ns, ^Ns, ^Ni);', $codeGJS, $name, $desc, $keywords, $titles, $price);	
		$id = $this->db->id();	
		//$tids = explode(';', $tid);
		$this->db->query('INSERT INTO `type-elements` (`tid`, `eid`) VALUES (^Ni, ^Ni);', $tid, $id);
		
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
	
	public function getallfieldtable($table){
		$result = $this->db->query("SHOW COLUMNS FROM `$table`");
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
	
	public function files_load($namfil,$nuload,$FILs,$clas){
	//echo '----<br>';echo $FILs[$namfil]['name'];echo '<br>----';
	//echo '<br>--'.$POS.'--<br>';
	if (file_exists($clas['img'].$FILs[$namfil]['name']) && !$_POST[$namfil]) {
		$size = GetImageSize($clas['img'].$FILs[$namfil]['name']);
		if($size[0]>0 && $size[1]>0) {
		echo 'Файл '.$FILs[$namfil]['name'].' существует <br>';
		if ($FILs[$namfil]['name']<> '') $_POST[$namfil]=$FILs[$namfil]['name'];
		//elseif ($_POST[$nuload] <> '') $_POST[$namfil]=$_POST[$nuload];
		}
		//echo '<br>'.$namfil.'-=-'.$_POST[$namfil].'-=-<br>';
	}
	else {
	$uploadInfo = $FILs[$namfil];
	echo 'Перемещаем файл '.$uploadInfo['name'].' из временной папки в указанную';	
	$newFilename = $clas['img'].$uploadInfo['name'];
    //Перемещаем файл из временной папки в указанную
    if (!move_uploaded_file($uploadInfo['tmp_name'], $newFilename)) {
        echo 'Не удалось осуществить сохранение файла';
		
	}
		else {
			echo '<img src="'.$newFilename.'">';	
			
		}
	if ($FILs[$namfil]['error'] == 4 && $FILs[$namfil]['name'] && $_POST[$nuload])  $_POST[$namfil]=$_POST[$nuload];	
	else $_POST[$namfil]=$FILs[$namfil]['name'];
	}
	}
	
	public function type_files_load($Files_Load,$var,$clas='',$newname='',$load=true){
		if($newname === 'libs'){
					if($var === 'myscrpt')$dir='js';
					elseif($var === 'mystyle')$dir='css';
					elseif($var === 'logo' || $var === 'banmain') $dir='img';
					else $dir='csv';
					$clas[$dir]=$clas['lib'].$dir.'/';
					$newname=$Files_Load[$var]['name'];
				}
				elseif($newname === '') $newname=$Files_Load[$var]['name'];
		
		if(isset($Files_Load[$var])){
		if($Files_Load[$var]['error']==0){		
			if(isset($Files_Load[$var])) {
			if($Files_Load[$var]['type']=='image/jpeg') {$resolu[$var]='.jpg';$tyfi='img';}
			elseif($Files_Load[$var]['type']=='image/png') {$resolu[$var]='.png';$tyfi='img';}
			elseif($Files_Load[$var]['type']=='image/gif') {$resolu[$var]='.gif';$tyfi='img';}
			elseif($Files_Load[$var]['type']=='text/css') {$resolu[$var]='.css';$tyfi='css';}
			elseif($Files_Load[$var]['type']=='application/vnd.ms-excel') {$resolu[$var]='.csv';$tyfi='csv';}
			elseif($Files_Load[$var]['type']=='text/javascript') {$resolu[$var]='.js';$tyfi='js';}
			elseif($load) {
				$res=explode('.',$Files_Load[$var]['name']);
				$resolu[$var]='.'.$res[1];
				$tyfi='oth';
			}
		else return false;
		}
		if($newname  === '')$newname = $var;
		//echo $clas[$tyfi].$var.$resolu[$var];
		if(!strstr($Files_Load[$var]['name'],'.'))return $clas[$tyfi].$newname.$resolu[$var];
		else return $clas[$tyfi].$newname;
		}	
	}
	else return false;
}
	
	public function all_files_load($namfil,$nuload,$FILs='',$clas='',$newname=''){
	
	if($FILs<>''){
	if (file_exists($clas['img'].$FILs[$namfil]['name']) && !isset($_POST[$namfil]) && $newname=='') {
		$size = GetImageSize($clas['img'].$FILs[$namfil]['name']);
		if($size[0]>0 && $size[1]>0) {
		echo 'Файл '.$FILs[$namfil]['name'].' существует <br>';
		if ($FILs[$namfil]['name']<> '') $_POST[$namfil]=$FILs[$namfil]['name'];
		//elseif ($_POST[$nuload] <> '') $_POST[$namfil]=$_POST[$nuload];
		}
		//echo '<br>'.$namfil.'-=-'.$_POST[$namfil].'-=-<br>';
	}
	elseif(file_exists($clas['csv'].$FILs[$namfil]['name']) && $newname=='' ){
		return;
		//echo 'Файл '.$FILs[$namfil]['name'].' существует <br>';
	}
	else {
	$uploadInfo = $FILs[$namfil];
	
	if($newname<>'') $uploadInfo['name']=$newname;
	//echo 'Перемещаем файл '.$uploadInfo['name'].' из временной папки в указанную ';
	if($newname == '')$newFilename=$this->type_files_load($FILs,$namfil,$clas);
	else $newFilename = $newname;
		//echo 'имя файла '.$newFilename;
	
    //Перемещаем файл  из временной папки в указанную
	//echo $newFilename;
    if (!move_uploaded_file($uploadInfo['tmp_name'], $newFilename)) {
       // 
		return false;
		
	}
		else {
			$sizeP=getimagesize($newFilename);	
			if($sizeP[0]>0 && $sizeP[1]>0) echo '<img src="'.$newFilename.'">Файл '.$newFilename.' загружен';
			return true;
		}
	if ($FILs[$namfil]['error'] == 4 && $FILs[$namfil]['name'] && $_POST[$nuload])  $_POST[$namfil]=$_POST[$nuload];	
	else $_POST[$namfil]=$FILs[$namfil]['name'];
	}
	}
	}
	
	function getscripts($id,$fl,$tp){
		$db=Singleton::getInstance('DB');
		$site=$_SERVER['HTTP_HOST'];
		$d="SELECT `id`, `scripts` FROM `scripts` WHERE `id`=^Ni; AND `flag`-^Ns AND `type`=^Ns";
		$res=$db->query($d,$id,$fl,$tp);
		if($res) $result=$res->scripts;
		else $result='no script';
		return $result;	
	}
	
	function getallformsite($tabl,$ida,$idsite){
		$tab='nameform';
		$db=Singleton::getInstance('DB');
		//if($site=='')$site=$_SERVER['HTTP_HOST'];
		$d="SELECT `idform`, `namform` FROM $tab WHERE `ids`=^Ni AND `idauthor`=^Ni;";
		$res=$db->query($d,$idsite,$ida);
		if (count($res) >1) {
		$l=0;	
		while ($element = each($res)) {
			$result['idform'][$l]=$element['value']->idform;
			$result['namform'][$l]=$element['value']->namform;
			$l++;
		}	
	}
	else {$result['id'][0]=$res->idform;$result['name'][0]=$res->namform;}
	return $result;
}
	
	function getallnewsite($tabl,$ida,$idsite){
		$tab=$tabl['news'];
		$db=Singleton::getInstance('DB');
		//if($site=='')$site=$_SERVER['HTTP_HOST'];
		$d="SELECT `idnews`, `name` FROM $tab WHERE `site`=^Ni AND `idauthor`=^Ni;";
		$res=$db->query($d,$idsite,$ida);
		if (count($res) >1) {
		$l=0;	
		while ($element = each($res)) {
			$result['id'][$l]=$element['value']->idnews;
			$result['nam'][$l]=$element['value']->name;
			$l++;
		}	
	}
	elseif(is_object($res)) {
		$result['id'][0]=$res->idnews;
		$result['name'][0]=$res->name;
		return $result;
		}
	else 	return null;
	
}
	function namepagenum($namep){
		if (strstr($namep, '|')){
			$NPG=explode('|',$namep);
			$res=$NPG1[1];
		}
		else $res=$namep;
	return $res;
	}
	
	function selectAllProperties($tab,$f1=0,$f2=1,$f3=3,$order='DESC',$nonum=''){
		$sw=Singleton::getInstance('StructureW');
		$arrfields=$sw->getallfieldtable($tab);
		$ord = ' ORDER BY '.$arrfields['field'][$f3].' '.$order;
		$d="SELECT `".$arrfields['field'][$f1]."` as id, `".$arrfields['field'][$f2]."` as Maket FROM $tab ";
		$res=$sw->db->query($d.$ord);
		
		if ($res != null){
		if (count($res) >1) {
		$l=0;	
		//print_r($res);
		//while ($element =each($res)) {
		foreach($res as $value){	
			$result['id'][$l]=$value->id;
			if (strstr($value->Maket,'|')) {
				$NmPg=explode('|',$value->Maket);
				//$result['nam'][$l]=$result['num'][$l].' '.substr($NmPg[1],0,15);
				if (is_array($NmPg) && isset($NmPg[2])) $result['Maket'][$l]=$result['id'][$l].' '.$NmPg[2];
				elseif($NmPg[2]=='') $result['Maket'][$l]='страница '.$value->id;
				elseif($nonum=='') $result['Maket'][$l]=$NmPg[0];
				else $result['Maket'][$l]=$NmPg[0].'('.$result['id'][$l].')';
				}
			elseif($nonum=='')  $result['Maket'][$l]=$value->Maket;
			else $result['Maket'][$l]=$value->Maket.'('.$value->id.')';
			if ($result['Maket'][$l] == '') $result['Maket'][$l]='style '.$value->Maket;
			$l++;
		}	
	}
	else {
		$result['Maket'][0]=$res->Maket;
		$result['id'][0]=$res->id;
		}
	//print_r($result);	
	return $result;
	}
	else return false;
	}
	
	static function selmenstr($clas,$arropt,$chice,$num,$ch='',$img='',$tich='Найти'){
	
	$str='<span>';
	//$str.='<option value="" class="label">'.$arropt[$num].' :</option>';
		$str.='<select id="selmen" class="'.$clas.'" name="'.$ch.'">';
		$i=0;
		
		foreach($arropt as $key=>$val){	
			if(!is_array($chice))	$chice[$i]=$key;
			if ($i != $num ) $str.='<option value="'.$arropt[$i].'">'.$val.'</option>';//$str.='<option selected name="'.$ch.'" value="'.$num.'">'.$val.'</option>';

			$i++;
		}
	$str.='</select>';	
	if($ch != ''){
		if(file_exists($img)) $str.='</select></span><span><input title="'.$tich.'" class="poisk-img" name="'.$ch.'" value="'.$ch.'" type="image" src="'.$img.'"/></span>';
	else $str.='<small><input class="'.$clas.'-butt" title="'.$tich.'" type="submit" value="'.$img.'"></small>';	
	}
	return $str;
	}
	
	function getallstyles($tab,$ids,$idm,$np=0,$nonum=''){
		$db=Singleton::getInstance('DB');
		
		if($np<>0){
			$d="SELECT `id`, `Maket` FROM $tab WHERE `ids`=^Ni AND `numpage`=^Ni AND `numaket`=^Ni;";
			$res=$db->query($d,$ids,$np,$idm);
		}
		else {
			$d="SELECT `id`, `Maket` FROM $tab WHERE `ids`=^Ni;";
			$res=$db->query($d,$ids);
		}
		if (count($res)<>0){
		if (count($res) >1) {//так как 1 занят по плейсхолдеры
		$l=0;	
		//print_r($res);
		while ($element =each($res)) {
			$result['id'][$l]=$element['value']->id;
			if (strstr($element['value']->Maket,'|')) {
				$NmPg=explode('|',$element['value']->Maket);
				//$result['nam'][$l]=$result['num'][$l].' '.substr($NmPg[1],0,15);
				if (is_array($NmPg) && isset($NmPg[2])) $result['Maket'][$l]=$result['id'][$l].' '.$NmPg[2];
				elseif($NmPg[2]=='') $result['Maket'][$l]='страница '.$element['value']->id;
				elseif($nonum=='') $result['Maket'][$l]=$NmPg[0];
				else $result['Maket'][$l]=$NmPg[0].'('.$result['id'][$l].')';
				}
			elseif($nonum=='')  $result['Maket'][$l]=$element['value']->Maket;
			else $result['Maket'][$l]=$element['value']->Maket.'('.$element['value']->id.')';
			if ($result['Maket'][$l] == '') $result['Maket'][$l]='style '.$element['value']->Maket;
			$l++;
		}	
	}
	else {
		$result['Maket'][0]=$res->Maket;
		$result['id'][0]=$res->id;
		}
	return $result;
	}
	else return false;
	}
	
	function getallpages($tab){
		$db=Singleton::getInstance('DB');
		$site=$_SERVER['HTTP_HOST'];
		$d="SELECT `numpage`, `namep` FROM $tab WHERE `site`=^Ns;";
		$res=$db->query($d,$site);
		if (count($res) >1) {
		$l=0;	
		//print_r($res);
		while ($element =each($res)) {
			$result['num'][$l]=$element['value']->numpage;
			if (strstr($element['value']->namep,'|')) {
				$NmPg=explode('|',$element['value']->namep);
				//$result['nam'][$l]=$result['num'][$l].' '.substr($NmPg[1],0,15);
				if (is_array($NmPg) && isset($NmPg[2])) $result['nam'][$l]=$result['num'][$l].' '.$NmPg[2];
				elseif(!isset($NmPg[2]) && isset($result['num'][$l])) $result['nam'][$l]='страница '.$element['value']->numpage;
				elseif(isset($result['num'][$l])) $result['nam'][$l]=$result['num'][$l].' '.$NmPg[0];
				}
			else  $result['nam'][$l]=$element['value']->numpage.$element['value']->namep;
			if ($result['nam'][$l] == '') $result['nam'][$l]='страница '.$element['value']->numpage;
			//if(strlen($result['nam'][$l])>16) $result['nam'][$l]=substr($result['nam'][$l],0,20);
			//$result['nam'][$l]=preg_replace ("/[^a-zA-ZА-Яа-я0-9\s]/","", $result['nam'][$l]);
			$l++;
		}	
	}
	else $result[0]=$res->namep;
	return $result;
	}
	
	public function editpartpage($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$c,$r,$s,$m,$t){
	$allpags=$this->getallpages('pages');
	
	//print_r($allpags['nam']);
	echo '<form method="POST" action="./?np='.$array[0].'" enctype="multipart/form-data">';
	//print_r($arrdelem);
	//print_r($array);echo '<br>';
	if (!$_GET['addp']){
	//echo '<h1> Редактор ('.$array[0].') </h1><table class="inp">';
	}
	else {
	//echo '<h1> Новая страница </h1><table class="inp">';	
	}
	echo '<tr>';
	$l=0;
	//print_r($array);	echo '  array <br>----------------------<br>';	
	$n=0;$m=0;
	$this->editpartBD($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$c,$r,$s,$m,$t);
	echo '<td class="l"><input size="'.$s.'" id="p" class="inpZ" name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.$_SERVER['HTTP_HOST'].'"></td></tr>';
	echo '</table>';
	echo '<input id="regBut" type="submit"  tabindex="'.$k.'" value=" Записать " />';
	echo '</form>';	
		
	}
	
	
	public function editpagesBD($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$tabl,$fields,$c,$r,$s,$m,$t){
	$allpags=$this->getallpages('pages');
	$table=$tabl['pages'];
	$type_input=array(0=>'cont', 1=>'land', 2=>'gall', 3=>'flex', 4=>'mag', 5=>'cat',6=>'mob' ,7=>'tw', 8=>'fb',9=>'qw',10=>'sh',11=>'blog');
	if (!isset($_GET['cust']) && !isset($_GET['in']) &&  $table <> 'namparams' &&  $table <> 'pages' &&  $table <> $tabl['elem'] &&  $table <> 'str'){
	$this->y=$this->ready_str_field($fields,2,1);
	//echo '<div class="info">';echo $table;print_r($this->y);echo '</div>';
	$res0=$this->db->query('SELECT '.$this->y.'   FROM '.$table.' WHERE Maket=^Ns;','Maket');
	$i=2;
	}
	if(isset($res0)){
	foreach($res0 as $values){
	if($values){
		$arrstl[$i]=explode('|',$values);
		}
	else 	$arrstl[$i]='';
	$i++;
	}
	}
	else for ($i=0;$i<count($array);$i++) $arrstl[$i]='';
	//print_r($arrstl);
	echo '<h1> Запись страницы </h1>';
	
	$l=0;
	//print_r($array);	echo '  array <br>----------------------<br>';	
	$n=0;$m=0;$zn=0;
	echo '<div class="formsection4">';
	if ($_GET['editp']=='new') echo '<form method="POST" action="#" enctype="multipart/form-data">';
	else echo '<form method="POST" action="#" enctype="multipart/form-data">';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
		
	$n=0;$m=0;
	for ($k=0;$k<(count($arrname)-1);$k++) {
		if ($arrtype[$k]>10) $maxlen[$k]=$arrtype[$k];
		elseif(is_int($arrtype[$k])) $maxlen[$k]=50;
		$this->editpartBD($arrname, $arrtype, $array,$arrdelem,$k,$arrayk,$clas,$c,$r,$s,$m,$t);
	}	
	echo '<td class="l"><input size="'.$s.'" id="p" class="inpZ" name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.$_SERVER['HTTP_HOST'].'"></td></tr>';
	echo '</table>';
	echo '<input id="regBut" type="submit"  tabindex="'.$k.'" value=" Записать " />';
	echo '</form>';	
		
	}
	
	public function editpartBD($arrname, $arrtype, $array,$arrdelem,$k,$arrayk,$clas,$c,$r,$s,$m,$t){
	if ($arrtype[$k]>10) $maxlen[$k]=$arrtype[$k];
	elseif(is_int($arrtype[$k])) $maxlen[$k]=50;
	if (is_array($arrayk))	{
		$k0=@ $arrayk[0];
		$k1=@ $arrayk[1];
		$k2=@ $arrayk[2];
		$k3=@ $arrayk[3];
		//echo '------'.$k0.' '.$k1.' '.$k2.' '.$k3;	
	}
	if ($array[$k]) $s=2*strlen($array[$k]);
		if ($arrtype[$k]<10) $s=$arrtype[$k];
		elseif ($arrtype[$k]>30) $s=30;
	if ($arrdelem[$k][0]== '' &&  $arrdelem[$k][1] == '') {
			//echo '<br>первый <br>';///////////////////////////////////////////
			//echo 'ar1 1 '.$arrname[$k].' '.$array[$k];echo '<br>';
			//echo '-0-( '.$arrdelem[$k][0].' )--| '.' |-1-( '.$arrdelem[$k][1].' )--';echo '<br>';
			if ($k === $k0 && $arrtype[$k] !== 'hid') echo '<tr><td><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		//$m=0;	
		//echo '<br>';
		//echo '$array['.$k.']-'.$array[$k];//repair
				
			switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td><input size="'.$arrtype[$k].'"  name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td><textarea placeholder="'.$arrname[$k].'" rows="'.$r.'" cols="'.$c.'"  name="'.$k.'" tabindex="'.$k.'" >'.htmlspecialchars($array[$k]).'</textarea></td>';
				break;
			}
			case 'news':
			{
				$ans=$this->getallnewsite('news');
				//print_r($ans);
				if($ans !== null){
				$ans['id'][]='';
				$ans['nam'][]='нет';
				echo '<td>';
					//print_r($allpags['num']);
					echo '<span>';
					echo '<select style="max-width:200px;" name="'.$k.'">';
					$i=0;
					while ($elem=each($ans['nam'])){
						if ($ans['id'][$i] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						else echo '<option value="'.$ans['id'][$i].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						$i++;
					}
				echo '</select></span></td>';
				}
				break;
			}
			case 'typ':
			{
				//$type_input=array(0=>'cont', 1=>'land', 2=>'gall', 3=>'blog', 4=>'mag', 5=>'cat');
				echo '<td title="'.$arrname[$k].'" class="l">';	
				//print_r($allpags[$m1]['num']);
				echo '<select style="max-width:200px;" name="'.$k.'">';
				$i=0;
				while ($elem=each($type_input)){
						if ($elem['value'] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$elem['value'].'">'.$elem['value'].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
				echo '<td><input title="'.$arrname[$k].'" size="'.$s.'"  name="'.$k.'" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
		}
	//if ($zn<1) $zn=1;
	}
	elseif ($arrdelem[$k][0] <> '' && $arrdelem[$k][1] == '') {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= $array[$k];
		//if ($arr1[count($arr1)-1] <> '') $arr1[count($arr1)]='';
		if ($arrtype[$k] !== 'hid') echo '<tr><td><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		$m=0;$m1=0;
		if (is_array($arr1)) {
		//if ($arrtype[$k] == 'check') echo '<td>';
		//echo '<br>ar1----------'.$k.'------------<br>';print_r($arr1);	
		foreach ($arr1 as $val){
			$m++;	
		if ($k === $k0) {
		$replat=$arrtype[$k];
		if (!$m1 === $k1) $arrtype[$k]='hid';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td><input  name="'.$k.$m1.'00" type="hidden" value="'.htmlspecialchars($val).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td><textarea placeholder="'.$arrname[$k].'" rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.$m1.'00" tabindex="'.$k.'" >'.htmlspecialchars($val).'</textarea></td>';
				break;
			}
			case 'check':
			{
				echo '<td>';
				$checkval=array(0=>'bl', 1=>'mn', 2=>'bt', 3=>'ft', 4=>'hd', 5=>'bf', 6=>'sw');
				$namcheckarr=array(0=>'контент', 1=>'меню', 2=>'кнопки', 3=>'футер', 4=>'хедер', 5=>'поиск',6=>'карусель');
				//echo $checkval[$m1].'  '.$val.'<br>';
				//echo '<label> '.$namcheckarr[$m1];
				if ($val == $checkval[$m1]){
				echo '<input type="hidden" name="'.$k.$m1.'00" value="n'.$checkval[$m1].'"></input>';	
				echo '<input title="'.$namcheckarr[$m1].'" type="checkbox" checked name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				else {
				echo '<input  type="hidden" name="'.$k.$m1.'00" value="'.$val.'"></input>';
				echo '<input title="'.$namcheckarr[$m1].'" width="5px" type="checkbox"  name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				echo ' </label></td>';
				break;
			}
			case 'pags':
			{
				$allpags[$m1]=$this->getallpages('pages');
				$allpags[$m1]['num'][]='';
				$allpags[$m1]['nam'][]='';
				echo '<td>';	
				//print_r($allpags[$m1]['num']);
				echo '<select style="max-width:200px;" name="'.$k.$m1.'00">';
				$i=0;
				while ($elem=each($allpags[$m1]['nam'])){
						if ($allpags[$m1]['num'][$i] == $val ) echo '<option selected value="'.$val.'">'.$allpags[$m1]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m1]['num'][$i].'">'.$allpags[$m1]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
			//echo $arrtype[$k].'-'.$m.'-'.count($arr1).'>'.$val;
			//print_r($clas);	
			if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				$arrtype[$k]=$arrt[1];
				//else $arrtype[$k]='';
				}
			if($arrtype[$k] == 'pcs') $arrt[0]='pic';
				if ($arrt[0] == 'pic')
				{
					if($arrtype[$k] == 'pcs' && $m < count($arr1)-1) $arrt[0]='pic';
					elseif($m==1 && $arrtype[$k] == 'pcs') {$arrt[0]='pic';}
					else $arrt[0]='';
					if (file_exists($clas['img'].$val) && $val<>'')
					{
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<td colspan="2" class="l" style="width: auto; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">'.$val.'
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input title="'.$arrname[$k].'" name="'.$k.$m1.'00" type="file"></input></td>';
						}
					}
					else {
					echo '<td><input name="'.$k.$m1.'00" type="file">';
					echo '<input title="'.$arrname[$k].'" type="text" name="'.$k.$m1.'00" value="'.$val.'"></td>';	
					echo '<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.' "></td>';	
					}
				}
				elseif($arrtype[$k]>0) 
				{
					echo '<td colspan="3" ><input title="'.$arrname[$k].'" size="'.$s.'" name="'.$k.$m1.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($val).'"></td>';
				}
				break;
			}
		}
		$arrtype[$k]=$replat;
		$m1++;
		}
		echo '</td>';
		}
		//if ($m1>$zn) $zn=$m1;
		}
	}
	else {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= @ $array[$k];
		//print_r($arr1);	echo '<br>ar2----------------------<br>';
			for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		if ($k === $k0 && $arrtype[$k] !== 'hid') echo '<td><label>'.$arr0[$k][0].'</label></td>';
		else echo '<td></td>';
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
		//echo '<BR> arr2--';
		//echo mb_detect_encoding($array[$k]).'-'.$k.'-'.$m.'-'.$j.'-'.$arr2[$m][$j];//repair
		//print_r($arr2[$m][$j]);
		$allpags[$m]=$this->getallpages('pages');
		$allpags[$m]['num'][]='';
		$allpags[$m]['nam'][]='';		
		//print_r($allpags[$m]['nam']);
		if ($k === $k0) {
		$replat=$arrtype[$k];
		if (!$m1 === $k1) $arrtype[$k]='hid';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td><input  name="'.$k.$m.$j.'00" type="hidden"  value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';
				break;
			}
			case 'text':
			{
				
				if($m == 0)
					echo '<td><textarea placeholder="'.$arrname[$k].'" rows="'.$r.'" cols="'.$c.'"  name="'.$k.$m.$j.'00" tabindex="'.$k.'" >'.htmlspecialchars($arr2[$m][$j]).'</textarea></td>';
				else { 
					echo '<td>';	
					//print_r($allpags[$m]['num']);
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				//echo '<td class="l"><input size="4" id="p" class="inp1" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="10" value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';	
				}
				break;
			}
			default:
			{
				
				if($m == 0)
					echo '<td><input title="'.$arrname[$k].'" size="'.$s.'" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';	
				else {
					echo '<td>';
					//print_r($allpags[$m]['num']);
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>'.' ';
						$i++;
						}
				echo '</select></td>';
					
				}
				break;
			}
		}
		$arrtype[$k]=$replat;
		}
		$n++;
		if ($n==count($arr2[$m])) {echo '<tr><td></td>';$n=0;}//
			} 
		}
	}
		$l++;
		if ($l>$t) {$l=0; echo '</tr>';}
}

	
	public function formpartpage($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$c,$r,$s,$m,$t){
	$type_input=array(0=>'cont', 1=>'land', 2=>'gall', 3=>'flex', 4=>'mag', 5=>'cat',6=>'mob' ,7=>'tw', 8=>'fb',9=>'qw',10=>'sh',11=>'blog');
	if (is_array($arrayk))	{
		echo '---------';
		$k0=@ $arrayk[0];
		$k1=@ $arrayk[1];
		$k2=@ $arrayk[2];
		$k3=@ $arrayk[3];
	}
	else {
		$k0=substr($arrayk,1,1)*1;
		$k1=substr($arrayk,2,1)*1;
		$k2=substr($arrayk,3,1)*1;
		$k3=substr($arrayk,4,1)*1;
		echo '++++'.$k0.' '.$k1.' '.$k2.' '.$k3;	
	}
	for ($k=0;$k<(count($arrname)-1);$k++) {
		if ($array[$k]) $s=2*strlen($array[$k]);
		if ($arrtype[$k]<10) $s=$arrtype[$k];
		elseif ($arrtype[$k]>30) $s=30;
	if ($arrdelem[$k][0]== '' &&  $arrdelem[$k][1] == '') {
		if ($k === $k0)	{
			//echo '{1-';print_r($k0);echo '-'.$k;echo '}';
			if ($arrtype[$k] !== 'hid') echo '<tr><td class="r"><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		if (isset($arrt[1])) $sizeF=$arrt[1];
		else $sizeF=$arrtype[$k];
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td class="h"><input size="'.$sizeF.'" id="p" class="inp" name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.'" tabindex="'.$k.'" >'.htmlspecialchars($array[$k]).'</textarea></td>';
				break;
			}
			case 'news':
			{
				$ans=$this->getallnewsite('news');
				$ans['id'][]='';
				$ans['nam'][]='нет';
				echo '<td class="l">';
					echo '<span>';
					echo '<select style="max-width:200px;" name="'.$k.'">';
					$i=0;
					while ($elem=each($ans['nam'])){
						if ($ans['id'][$i] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						else echo '<option value="'.$ans['id'][$i].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						$i++;
					}
				echo '</select></span></td>';
				break;
			}
			case 'typ':
			{
				//$type_input=array(0=>'cont', 1=>'land', 2=>'gall', 3=>'blog', 4=>'mag', 5=>'cat');
				echo '<td class="l">';	
				echo '<select style="max-width:200px;" name="'.$k.'">';
				$i=0;
				while ($elem=each($type_input)){
						if ($elem['value'] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$elem['value'].'">'.$elem['value'].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
				echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.'" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
		}
		}
		else echo '<input name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	}
	elseif ($arrdelem[$k][0] <> '' && $arrdelem[$k][1] == '') {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= $array[$k];
		if ($k === $k0 && $arrtype[$k] !== 'hid') echo '<tr><td class="r"><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		$m=0;$m1=0;
		if (is_array($arr1)) {
		if ($arrtype[$k] == 'check') echo '<td colspan="4">';
		foreach ($arr1 as $val){
			$m++;	
	if ($k === $k0) {
		$replat=$arrtype[$k];
		if ($m1 <> $k1) $arrtype[$k]='hid';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td class="h"><input  id="p" class="inp" name="'.$k.$m1.'00" type="hidden" value="'.htmlspecialchars($val).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.$m1.'00" tabindex="'.$k.'" >'.htmlspecialchars($val).'</textarea></td>';
				break;
			}
			case 'check':
			{ 
				$checkval=array(0=>'bl', 1=>'mn', 2=>'bt', 3=>'ft', 4=>'hd', 5=>'bf');
				$namcheckarr=array(0=>'контент', 1=>'меню', 2=>'кнопки', 3=>'футер', 4=>'хедер', 5=>'поиск');
				echo '<label> '.$namcheckarr[$m1].' </label>';
				if ($val == $checkval[$m1]){
				echo '<input type="hidden" name="'.$k.$m1.'00" value="n'.$checkval[$m1].'"></input>';	
				echo '<input type="checkbox" checked name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				else {
				echo '<input type="hidden" name="'.$k.$m1.'00" value="'.$val.'"></input>';
				echo '<input type="checkbox"  name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				break;
			}
			case 'pags':
			{
				$allpags[$m1]=$this->getallpages('pages');
				$allpags[$m1]['num'][]='';
				$allpags[$m1]['nam'][]='';
				echo '<td class="l">';	
				echo '<select style="max-width:200px;" name="'.$k.$m1.'00">';
				$i=0;
				while ($elem=each($allpags[$m1]['nam'])){
						if ($allpags[$m1]['num'][$i] == $val ) echo '<option selected value="'.$val.'">'.$allpags[$m1]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m1]['num'][$i].'">'.$allpags[$m1]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
			if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				$arrtype[$k]=$arrt[1];
				}
			if($arrtype[$k] == 'pcs') $arrt[0]='pic';
				if ($arrt[0] == 'pic')
				{
					if($arrtype[$k] == 'pcs' && $m < count($arr1)-1) $arrt[0]='pic';
					elseif($m==1 && $arrtype[$k] == 'pcs')$arrt[0]='pic';
					else $arrt[0]='';
					if (file_exists($clas['img'].$val) && $val<>'')
					{
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<td class="l" style="width: auto; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">'.$val.'
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input name="'.$k.$m1.'00" type="file"></input></td>';
						}
					}
					else {
					echo '<td>'.$clas['img'].$val.' не найден <input name="'.$k.$m1.'00" type="file">';
					if ($val) echo '<input type="text" name="'.$k.$m1.'00" value="'.$val.'"></td>';	
					else echo '<input type="hidden" name="noupload'.$k.$m1.'" value=" "></td>';	
					}
				}
				elseif($arrtype[$k]>0) 
				{
					echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.$m1.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($val).'"></td>';
				}
				break;
			}
		}
		$arrtype[$k]=$replat;
		if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				$arrtype[$k]=$arrt[1];
				$arrt[0]='';
				//echo $arrtype[$k].'=-=-='.$arrt[0];
				}
	}
	else echo '<input name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	$m1++;
}
		echo '</td>';
		}
		
		}
	else {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= @ $array[$k];
		for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		if ($k === $k0 && $arrtype[$k] !== 'hid') echo '<td class="r"><label>'.$arr0[$k][0].'</label></td>';
		else echo '<td class="h"></td>';
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
		$allpags[$m]=$this->getallpages('pages');
		$allpags[$m]['num'][]='';
		$allpags[$m]['nam'][]='';	
		
	if ($k === $k0) {
		$replat=$arrtype[$k];
		//echo '{3-';print_r($k0);echo '-'.$k;echo '}';
		if ($m == $k2 || $m == $k2+1){
			if($j<>$k3)$arrtype[$k]='hid';
			}
		
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td class="h"><input id="p" class="inpH" name="'.$k.$m.$j.'00" type="hidden"  value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';
				break;
			}
			case 'text':
			{
				
				if($m == 0)
					echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inpT" name="'.$k.$m.$j.'00" tabindex="'.$k.'" >'.htmlspecialchars($arr2[$m][$j]).'</textarea></td>';
				else { 
					echo '<td class="l">';	
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				}
				break;
			}
			default:
			{
				
				if($m == 0)
					echo '<td class="l"><input size="'.$s.'" id="p" class="inpS" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';	
				else {
					echo '<td class="l">';
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>'.' ';
						$i++;
						}
				echo '</select></td>';
					
				}
				break;
			}
		}
	$arrtype[$k]=$replat;
	}
	else echo '<input name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	$n++;
	if ($n==count($arr2[$m])) {echo '<tr><td></td>';$n=0;}
			} 
		}
	}
	
	$l++;
	if ($l>$t) {$l=0; echo '</tr>';}
	}
	echo '<td class="l"><input size="'.$s.'" id="p" class="inpZ" name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.$_SERVER['HTTP_HOST'].'"></td></tr>';
}
	
	public function editpartsBD($arrname, $arrtype, $array,$arrdelem, $arrayk,$clas,$table,$fields,$ida,$idsite,$href='#') {
	$allpags=$this->getallpages('pages');
	//$table=$tabl['pages'];
	$resu=$this->read_namparams('setMaketPage',0);
	$type_input=$resu[1];
	//array(0=>'cont', 1=>'land', 2=>'gall', 3=>'flex', 4=>'mag', 5=>'cat',6=>'mob' ,7=>'tw', 8=>'fb',9=>'qw',10=>'sh',11=>'blog');
	if (!isset($_GET['cust']) && !isset($_GET['in']) &&  ($table =='maket'  || $table =='allmakets' )){
	$this->y=$this->ready_str_field($fields,2,1);
	//echo '<div class="info">';echo $table;print_r($this->y);echo '</div>';
	$res0=$this->db->query('SELECT '.$this->y.'   FROM '.$table.' WHERE Maket=^Ns;','Maket');
	$i=2;
	}
	if(isset($res0)){
	foreach($res0 as $values){
	if($values){
		$arrstl[$i]=explode('|',$values);
		}
	else 	$arrstl[$i]='';
	$i++;
	}
	}
	else for ($i=0;$i<count($array);$i++) $arrstl[$i]='';
	//print_r($arrstl);
	
	$l=0;
	//print_r($array);	echo '  array <br>----------------------<br>';	
	$n=0;$m=0;$zn=0;
	//if (isset($_GET['editp']))echo '<iframe src="'.$href.'?editp=6000&tab=maket&par=612" width="300" height="50" align ="left" scrolling="auto" align="top" frameborder="1" ></iframe>';
	echo '<div class="formsection4">';
	echo '<form method="POST" action="'.$href.' "  enctype="multipart/form-data">';
	
	echo '<input type="hidden" name="sucss" value="nogood"/>';
	echo '<input class="button"   id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	$l=0;
	//print_r($array);	echo '  array <br>----------------------<br>';	
	$n=0;$m=0;$zn=0;
	//$arrayk=array(4,0,1,2)
	//$this->formpartpage($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$c,$r,$s,$m,$t);
	if (is_array($arrayk))	{
		//echo '---------';
		$k0=@ $arrayk[0];
		$k1=@ $arrayk[1];
		$k2=@ $arrayk[2];
		$k3=@ $arrayk[3];
		//echo '++++'.$k0.' '.$k1.' '.$k2.' '.$k3;	
	}
	else {
		$k0=substr($arrayk,1,1)*1;
		$k1=substr($arrayk,2,1)*1;
		$k2=substr($arrayk,3,1)*1;
		$k3=substr($arrayk,4,1)*1;
		//echo '++++'.$k0.' '.$k1.' '.$k2.' '.$k3;	
	}
	for ($k=0;$k<(count($arrname)-1);$k++) {
		$arrname[$k]='';
		if ($arrtype[$k]>10) $maxlen[$k]=$arrtype[$k];
		elseif(is_int($arrtype[$k])) $maxlen[$k]=50;
		if ($arrtype[$k]<10) $s=$arrtype[$k]+10;
		elseif ($arrtype[$k]>30) $s=30;
		if ($array[$k]) $s=2*strlen($array[$k]);
	if ($arrdelem[$k][0]== '' &&  $arrdelem[$k][1] == '') {
		if ($k === $k0)	{
			//echo '{1-';print_r($k0);echo '-'.$k;echo '}';
			if ($arrtype[$k] !== 'hid') echo '<tr><td class="r"><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td class="h"><input size="'.$arrtype[$k].'" id="p" class="inp" name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.'" tabindex="'.$k.'" >'.htmlspecialchars($array[$k]).'</textarea></td>';
				break;
			}
			case 'news':
			{
				$ans=$this->getallnewsite($tabl,$ida,$idsite);
				$ans['id'][]='';
				$ans['nam'][]='нет';
				echo '<td class="l">';
					echo '<span>';
					echo '<select style="width:200px;" name="'.$k.'">';
					$i=0;
					while ($elem=each($ans['nam'])){
						if ($ans['id'][$i] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						else echo '<option value="'.$ans['id'][$i].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						$i++;
					}
				echo '</select></span></td>';
				break;
			}
			case 'typ':
			{
				//$type_input=array(0=>'cont', 1=>'land', 2=>'gall', 3=>'blog', 4=>'mag', 5=>'cat');
				echo '<td class="l">';	
				echo '<select style="max-width:200px;" name="'.$k.'">';
				$i=0;
				while ($elem=each($type_input)){
						if ($elem['value'] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$elem['value'].'">'.$elem['value'].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
				echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.'" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
		}
		}
		else echo '<input name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	if ($zn<1) $zn=1;
	}
	elseif ($arrdelem[$k][0] <> '' && $arrdelem[$k][1] == '') {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= $array[$k];
		if ($k === $k0 && $arrtype[$k] !== 'hid') echo '<tr><td class="r"><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		$m=0;$m1=0;
		if (is_array($arr1)) {
		if ($arrtype[$k] == 'check') echo '<td colspan="4">';
		foreach ($arr1 as $val){
			$m++;	
	if ($k === $k0) {
		$replat=$arrtype[$k];
		if ($m1 <> $k1) $arrtype[$k]='hid';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td class="h"><input  id="p" class="inp" name="'.$k.$m1.'00" type="hidden" value="'.htmlspecialchars($val).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.$m1.'00" tabindex="'.$k.'" >'.htmlspecialchars($val).'</textarea></td>';
				break;
			}
			case 'check':
			{
				$checkval=array(0=>'bl', 1=>'mn', 2=>'bt', 3=>'ft', 4=>'hd', 5=>'bf');
				$namcheckarr=array(0=>'контент', 1=>'меню', 2=>'кнопки', 3=>'футер', 4=>'хедер', 5=>'поиск');
				echo '<label> '.$namcheckarr[$m1].' </label>';
				if ($val == $checkval[$m1]){
				echo '<input type="hidden" name="'.$k.$m1.'00" value="n'.$checkval[$m1].'"></input>';	
				echo '<input type="checkbox" checked name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				else {
				echo '<input type="hidden" name="'.$k.$m1.'00" value="'.$val.'"></input>';
				echo '<input type="checkbox"  name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				break;
			}
			case 'pags':
			{
				$allpags[$m1]=$this->getallpages('pages');
				$allpags[$m1]['num'][]='';
				$allpags[$m1]['nam'][]='';
				echo '<td class="l">';	
				echo '<select style="max-width:200px;" name="'.$k.$m1.'00">';
				$i=0;
				while ($elem=each($allpags[$m1]['nam'])){
						if ($allpags[$m1]['num'][$i] == $val ) echo '<option selected value="'.$val.'">'.$allpags[$m1]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m1]['num'][$i].'">'.$allpags[$m1]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
			if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				if($arrt[1]<>'pic')$arrtype[$k]=$arrt[1];
				else $arrtype[$k]=$arrt[1].'='.$arrt[2];
				}
			if($arrtype[$k] == 'pcs') $arrt[0]='pic';
				if ($arrt[0] == 'pic')
				{
					if($arrtype[$k] == 'pcs' && $m < count($arr1)-1) $arrt[0]='pic';
					elseif($m==1 && $arrtype[$k] == 'pcs')$arrt[0]='pic';
					else $arrt[0]='';
					if (file_exists($clas['img'].$val) && $val<>'')
					{
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<td class="l" style="width: auto; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">'.$val.'
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input name="'.$k.$m1.'00" type="file"></input></td>';
						}
					}
					else {
					//echo '<td>'.$clas['img'].$val.' не найден <input name="'.$k.$m1.'00" type="file">';
					echo '<ul style="text-align: center; width: auto; padding: 20px; margin: 10px; background-image: url('.'./images/error.gif'.');background-repeat: no-repeat"><input name="'.$k.$m1.'00" type="file">';
					echo '<input type="text" name="'.$k.$m1.'00" value="'.$val.'"></td>';	
					echo '<input type="hidden" name="noupload'.$k.$m1.'" value=" "></td>';	
					}
				}
				elseif($arrtype[$k]>0) 
				{
					$sizeP=getimagesize($clas['img'].$val);
					if($sizeP[0]==0 && $sizeP[1]==0){
					echo '<span><input style="margin-right: 10px;margin-bottom: 10px;" placeholder="'.$placeholder.'" size="'.$s.'"  name="'.$k.$m1.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($val).'"></span>';
					}
					else {
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<ul style="width: auto; padding: 20px; margin: 10px; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input name="'.$k.$m1.'00" type="file"></input>';
						echo '</ul>';
						}
					}
				}
				break;
			}
		}
		$arrtype[$k]=$replat;
		if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				if($arrt[1]<>'pic')$arrtype[$k]=$arrt[1];
				elseif(isset($arrt[2])) $arrtype[$k]=$arrt[1].'='.$arrt[2];
				//$arrtype[$k]=$arrt[1];
				$arrt[0]='';
				//echo $arrtype[$k].'=-=-='.$arrt[0];
				}
	}
	else echo '<input name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	$m1++;
}
		echo '</td>';
		}
		if ($m1>$zn) $zn=$m1;
		}
	else {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= @ $array[$k];
		for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		if ($k === $k0 && $arrtype[$k] !== 'hid') echo '<td class="r"><label>'.$arr0[$k][0].'</label></td>';
		else echo '<td class="h"></td>';
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
		$allpags[$m]=$this->getallpages('pages');
		$allpags[$m]['num'][]='';
		$allpags[$m]['nam'][]='';	
		
	if ($k === $k0) {
		$replat=$arrtype[$k];
		//echo '{3-';print_r($k0);echo '-'.$k;echo '}';
		if ($m <> $k2 || $j <> $k3) $arrtype[$k]='hid';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td class="h"><input id="p" class="inpH" name="'.$k.$m.$j.'00" type="hidden"  value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';
				break;
			}
			case 'text':
			{
				
				if($m == 0)
					echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inpT" name="'.$k.$m.$j.'00" tabindex="'.$k.'" >'.htmlspecialchars($arr2[$m][$j]).'</textarea></td>';
				else { 
					echo '<td class="l">';	
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				}
				break;
			}
			default:
			{
				
				if($m == 0)
					echo '<td class="l"><input size="'.$s.'" id="p" class="inpS" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';	
				else {
					echo '<td class="l">';
					echo '<select style="max-width:200px;" class="select_opt" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>'.' ';
						$i++;
						}
				echo '</select></td>';
					
				}
				break;
			}
		}
	$arrtype[$k]=$replat;
	}
	else echo '<input name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	$n++;
	if ($n==count($arr2[$m])) {echo '<tr><td></td>';$n=0;}
			} 
		}
	if ($j>$zn) $zn=$j;
	}
	
	$l++;
	if ($l>$t) {$l=0; echo '</tr>';}
	}
echo '<input name="zn" value="'.$zn.'" type="hidden"';	
	echo '<td class="l"><input size="'.$s.'" id="p" class="inpZ" name="'.$k.'" type="hidden"   value="'.$_SERVER['HTTP_HOST'].'"></td></tr>';
	echo '</table>';
	//echo '<input id="regBut" type="submit"  tabindex="'.$k.'" value=" Записать " />';
	echo '</form>';
}		

	public function editpartsDBD($arrname, $arrtype, $array,$arrdelem, $arrayk,$i,$clas,$table,$fields,$ida,$idsite,$c=50,$r=2,$s=30,$t=1) {
	$allpags=$this->getallpages('pages');
	$table=$tabl['ed'];
	if($table<>'allsites'){
		$resu=$this->read_namparams('setMaketPage',0);
		$type_input=$resu[1];
		//array(11=>'cont', 0=>'land', 1=>'gall', 7=>'flex', 8=>'mag', 9=>'cat',6=>'mob' ,4=>'fb', 3=>'tw',5=>'qw',10=>'shop',2=>'blog');
	}
	if (!isset($_GET['cust']) && !isset($_GET['in']) &&  $table <> 'namparams' &&  $table <> 'pages' &&  $table <> $tabl['elem'] &&  $table <> 'str' &&  $table <> 'allsites' && !strstr($table,'config')){
	$this->y=$this->ready_str_field($fields,2,1);
	
	$mak='Maket';
	$res0=$this->db->query('SELECT '.$this->y.'   FROM `'.$table.'` WHERE `Maket`=^Ns;',$mak);
	//$i=0;
	}
	
	$arrstl=$this->issetMaket($res0,count($array));
	
	$l=0;
	//print_r($array);	echo '  array <br>----------------------<br>';	
	$n=0;$m=0;$zn=0;
	//$arrayk=array(4,0,1,2)
	//$this->formpartpage($arrname, $arrtype, $array,$arrdelem,$arrayk,$clas,$c,$r,$s,$m,$t);
	if (is_array($arrayk))	{
		foreach($arrayk as $val){ 
		if(is_array($val)){
			$k0[$i]=@ $val[0];
			$k1[$i]=@ $val[1];
			$k2[$i]=@ $val[2];
			$k3[$i]=@ $val[3];
		}
		else {
			$k0=substr($val,1,1)*1;
			$k1=substr($val,2,1)*1;
			$k2=substr($val,3,1)*1;
			$k3=substr($val,4,1)*1;
		}
		}
		//echo '++++'.$k0.' '.$k1.' '.$k2.' '.$k3;	
	}
	else {
		$k0=substr($arrayk,1,1)*1;
		$k1=substr($arrayk,2,1)*1;
		$k2=substr($arrayk,3,1)*1;
		$k3=substr($arrayk,4,1)*1;
		//echo '++++'.$k0.' '.$k1.' '.$k2.' '.$k3;	
	}
	
	$vok=$k0[$i];
	
	for ($k=0;$k<(count($arrname)-1);$k++) {
		$arrname[$k]='';
		/*if ($arrtype[$k]>10) $maxlen[$k]=$arrtype[$k];
		elseif(is_int($arrtype[$k])) $maxlen[$k]=50;
		if ($arrtype[$k]<10) $s=$arrtype[$k]+10;
		elseif ($arrtype[$k]>30) $s=30;*/
		//if ($array[$k]) $s=2*strlen($array[$k]);
	if ($arrdelem[$k][0]== '' &&  $arrdelem[$k][1] == '') {
		if ($k === $vok)	{
			
		switch ($arrtype[$k])
		{
			case 'hid': {
				 if($i==0) echo '<input size="'.$arrtype[$k].'" id="p" class="inp" name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'">';
				break;
			}
			case 'text':
			{
				echo '<textarea rows="'.$r.'" cols="'.$c.'" id="p1" class="inp" name="'.$k.'" tabindex="'.$k.'">'.htmlspecialchars($array[$k]).'</textarea>';
				break;
			}
			case 'news':
			{
				$ans=$this->getallnewsite($tabl,$ida,$idsite);
				$ans['id'][]='';
				$ans['nam'][]='нет';
				
					echo '<span>';
					echo '<select style="max-width:200px;" class="select_opt" name="'.$k.'">';
			
					while ($elem=each($ans['nam'])){
						if ($ans['id'][$elem['key']] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$elem['value'].'('.$ans['id'][$elem['key']].')</option>';
						else echo '<option value="'.$ans['id'][$elem['key']].'">'.$elem['value'].'('.$ans['id'][$elem['key']].')</option>';
						
					}
				echo '</select></span>';
				break;
			}
			case 'typ':
			{
				
				echo '<select style="max-width:200px;" class="select_opt" name="'.$k.'">';
			
				while ($elem=each($type_input)){
						if ($elem['value'] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$elem['value'].'">'.$elem['value'].'</option>';
						
						}
				echo '</select>';
				break;
			}
			default:
			{
				echo '<input size="'.$s.'" id="p" class="inp" name="'.$k.'" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'">';
				break;
			}
		}
		}
		elseif($i==0)  echo '<input name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	if ($zn<1) $zn=1;
	}
	//один разделитель
	elseif ($arrdelem[$k][0] <> '' && $arrdelem[$k][1] == '') {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= $array[$k];
		//if ($k === $vok && $arrtype[$k] !== 'hid') echo '<label>'.$arrname[$k].'</label>';
		$m=0;$m1=0;
		if (is_array($arr1)) {
		foreach ($arr1 as $val){
			$m++;	
	if ($k === $vok) {
		$replat=$arrtype[$k];
		if ($m1 <> $k1[$i]) $arrtype[$k]='hid';
		switch ($arrtype[$k])
		{
			case 'hid': {
				if($i==0) echo '<input class="hideblock" id="p2" class="inp" name="'.$k.$m1.'00" type="hidden" value="'.htmlspecialchars($val).'">';
				break;
			}
			case 'text':
			{
				echo '<textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.$m1.'00" tabindex="'.$k.'">'.htmlspecialchars($val).'</textarea>';
				break;
			}
			case 'check':
			{
				if($table===$tabl['pages']){
					$rest=$this->read_namparams('setTypesPage',0);
					$checkval=$rest[1];
					print_r($rest);
					//$checkval=array(0=>'bl', 1=>'mn', 2=>'bt', 3=>'ft', 4=>'hd', 5=>'bf', 6=>'sw',7=>'fm');
					$namcheckarr=$rest[0];
					//$namcheckarr=array(0=>'контент', 1=>'меню', 2=>'кнопки', 3=>'футер', 4=>'хедер', 5=>'поиск',6=>'карусель',7=>'форма');
				}
				elseif($table==='scripts'){
					$checkval=array(0=>'us',1=>'bl');
					$namcheckarr=array(0=>'used',1=>'blocked');
				}
				elseif($table==='customers'){
					$rest=$this->read_namparams('setHosting',0);
					//$checkval=$rest[1];
					$namcheckarr=$rest[0];
					$checkval=array( 0=>'y', 1=>'y', 2=>'y', 3=>'y', 4=>'y', 5=>'y',6=>'y', 7=>'y', 8=>'y');
					//$namcheckarr=array('Подключение','Редактор контента','Домен второго уровня SSL','Конструктор','SEO','Почта','Персональная база','Объем диска','Тип размещения');
				}
				echo '<label> '.$namcheckarr[$m1].' </label>';
				if ($val === $checkval[$m1]){
				if($i==0) echo '<input type="hidden" name="'.$k.$m1.'00" value="n'.$checkval[$m1].'"></input>';	
				echo '<input type="checkbox" checked name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				else {
				if($i==0) echo '<input type="hidden" name="'.$k.$m1.'00" value="'.$val.'"></input>';
				echo '<input type="checkbox"  name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				break;
			}
			case 'pags':
			{
				$allpags[$m1]=$this->getallpages('pages');
				$allpags[$m1]['num'][]='';
				$allpags[$m1]['nam'][]='';
				//echo '<td class="l">';	
				echo '<select style="max-width:200px;" class="select_opt" name="'.$k.$m1.'00">';
				while ($elem=each($allpags[$m1]['nam'])){
						if ($allpags[$m1]['num'][$elem['key']] == $val ) echo '<option selected value="'.$val.'">'.$elem['value'].'</option>';
						else echo '<option value="'.$allpags[$m1]['num'][$elem['key']].'">'.$elem['value'].'</option>';
						}
				echo '</select>';
				break;
			}
			default:
			{
			if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				if($arrt[1]<>'pic')$arrtype[$k]=$arrt[1];
				else $arrtype[$k]=$arrt[2];
				}
			if($arrtype[$k] == 'pcs') $arrt[0]='pic';
				if ($arrt[0] == 'pic')
				{
					if($arrtype[$k] == 'pcs' && $m < count($arr1)-1) $arrt[0]='pic';
					elseif($m==1 && $arrtype[$k] == 'pcs')$arrt[0]='pic';
					else $arrt[0]='';
					if (file_exists($clas['img'].$val) && $val<>'')
					{
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<ul class="l" style="width:'.$size[0].' px; height: auto; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat"/><ul><li>
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'"></li>
						<li><input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input></li>';	
						echo '<li><input name="'.$k.$m1.'00" type="file"></input></li></ul>';
						}
					}
					else {
					if($i==0){
						//echo '<ul>'.$clas['img'].$val.' не найден <input name="'.$k.$m1.'00" type="file">';
						echo '<ul style="text-align: center; width: auto; padding: 20px; margin: 10px; background-image: url('.'./images/error.gif'.');background-repeat: no-repeat"><input name="'.$k.$m1.'00" type="file">';
						echo '<input type="text" name="'.$k.$m1.'00" value="'.$val.'"></ul>';	
						echo '<input type="hidden" name="noupload'.$k.$m1.'" value=" "></ul>';	}
					}
				}
				elseif($arrtype[$k]>0) 
				{
					$sizeP=getimagesize($clas['img'].$val);
					if($sizeP[0]==0 && $sizeP[1]==0)
					echo '<span><input style="margin-right: 10px;margin-bottom: 10px;" placeholder="'.$placeholder.'" size="'.$s.'"  name="'.$k.$m1.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($val).'"></span>';
					}
					else {
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<ul style="width: auto; padding: 20px; margin: 10px; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input name="'.$k.$m1.'00" type="file"></input>';
						echo '</ul>';
						}
						else{
							echo '<ul style="text-align: center; width: auto; padding: 20px; margin: 10px; background-image: url('.'./images/error.gif'.');background-repeat: no-repeat"><input name="'.$k.$m1.'00" type="file">';
						}
					}
				
				break;
			}
		}
		if($arrt[1]<>'pic')$arrtype[$k]=$replat;
		else $arrtype[$k]=$arrt[1].'='.$arrt[2];
		if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				$arrtype[$k]=$arrt[1];
				$arrt[0]='';
				//echo $arrtype[$k].'=-=-='.$arrt[0];
				}
	}
	elseif($i==0) echo '<input class="hideblock" name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	$m1++;
}
		
		}
		if ($m1>$zn) $zn=$m1;
		}
	//два разделителя	
	else {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= @ $array[$k];
		for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		if ($k === $vok && $arrtype[$k] !== 'hid') echo '<label>'.$arr0[$k][0].'</label>';
		//else echo '<ul>';
		//print_r($arr2[0][0]);
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
		$allpags[$m]=$this->getallpages('pages');
		$allpags[$m]['num'][]='';
		$allpags[$m]['nam'][]='';	
		
	if ($k === $vok) {
		$replat=$arrtype[$k];
		//echo '{3-';print_r($vok);echo '-'.$k;echo '}';
		if ($m <> $k2[$i] || $j <> $k3[$i]) $arrtype[$k]='hid';
		switch ($arrtype[$k])
		{
			case 'hid': {
				//if($i==0) echo '<input class="hideblock" id="p" class="inpH" name="'.$k.$m.$j.'00" type="hidden"  value="'.htmlspecialchars($arr2[$m][$j]).'">';
				break;
			}
			case 'text':
			{
				
				if($m == 0)
					echo '<textarea style="margin-right: 10px;margin-bottom: 10px;" rows="'.$r.'" cols="'.$c.'" id="p" class="inpT" name="'.$k.$m.$j.'00" tabindex="'.$k.'"  value="'.htmlspecialchars($arr2[$m][$j]).'">'.htmlspecialchars($arr2[$m][$j]).'</textarea>';
				else { 
					//echo '<td class="l">';	
					echo '<select style="max-width:200px;" class="select_opt" name="'.$k.$m.$j.'00">';
				
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$elem['key']] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$elem['key']].'">'.$elem['value'].'</option>';
						
						}
				echo '</select>';
				}
				break;
			}
			default:
			{
				
				if($m == 0)
					echo '<input size="'.$s.'" id="p" class="inpS" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($arr2[$m][$j]).'">';	
				else {
					//echo '<td class="l">';
					echo '<select style="max-width:200px;" class="select_opt" name="'.$k.$m.$j.'00">';
					
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$elem['key']] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$elem['key']].'">'.$elem['value'].'</option>'.' ';

						}
				echo '</select>';
					
				}
				break;
			}
		}
	$arrtype[$k]=$replat;
	}
	elseif($i==0) echo '<input class="hideblock" name="'.$k.'" type="hidden" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">';	
	$n++;
	
			} 
		}
	if ($j>$zn) $zn=$j;
	}
	
	}
$i=0;
	while(isset($arrtype[$k+$i]) && $k+$i <count($array)+1)	{
		if ($arrtype[$k+$i] !== 'hid') {
			echo '</li></ul><ul class="editor label"><label>'.$arrname[$k+$i].'</label></ul>';
			echo '<input style="margin-right: 10px;margin-bottom: 10px;" placeholder="'.$placeholder.'" size="'.$s.'" name="'.($k+$i).'" type="text" tabindex="'.($k+$i).'" maxlength="'.$maxlen[$k+$i].'" value="'.htmlspecialchars($array[$k+$i]).'">';
		}
		else echo '<input  type="hidden" " name="'.($k+$i).'" value="'.htmlspecialchars($array[$k+$i]).'">';
		if($k+$i < count($array)-1)$i++;
		else break;
	}
	//}
		echo '<input name="zn" value="'.$zn.'" type="hidden">';	
	
}

	public function editTBD($arrname, $arrtype, $array,$arrdelem,$clas,$tabl,$ida,$idsite,$c,$r,$s,$t){	
	$allpags=$this->getallpages('pages');
	$table=$tabl['pages'];
	$type_input=array(0=>'cont', 1=>'land', 2=>'gall', 3=>'flex', 4=>'mag', 5=>'cat',6=>'mob' ,7=>'tw', 8=>'fb',9=>'qw',10=>'sh',11=>'blog');
	if (!isset($_GET['cust']) && !isset($_GET['in']) &&  $table <> 'namparams' &&  $table <> 'pages' &&  $table <> $tabl['elem'] &&  $table <> 'str'){
	$this->y=$this->ready_str_field($fields,2,1);
	//echo '<div class="info">';echo $table;print_r($this->y);echo '</div>';
	$res0=$this->db->query('SELECT '.$this->y.'   FROM '.$table.' WHERE Maket=^Ns;','Maket');
	$i=2;
	}
	if(isset($res0)){
	foreach($res0 as $values){
	if($values){
		$arrstl[$i]=explode('|',$values);
		}
	else 	$arrstl[$i]='';
	$i++;
	}
	}
	else for ($i=0;$i<count($array);$i++) $arrstl[$i]='';
	//print_r($arrstl);
	echo '<h1> Запись страницы </h1>';
	echo '<table><tr>';
	$l=0;
	//print_r($array);	echo '  array <br>----------------------<br>';	
	$n=0;$m=0;$zn=0;
	for ($k=0;$k<(count($arrname)-1);$k++) {
		if ($arrtype[$k]>10) $maxlen[$k]=$arrtype[$k];
		elseif(is_int($arrtype[$k])) $maxlen[$k]=50;
		if (ctype_digit ($array[$k])){
		if ($array[$k]) $s=2*strlen($array[$k]);
		if ($arrtype[$k]<10) $s=$arrtype[$k];
		elseif ($arrtype[$k]>30) $s=30;
		}
	if ($arrdelem[$k][0]== '' &&  $arrdelem[$k][1] == '') {
			//echo '<br>первый <br>';///////////////////////////////////////////
			//echo 'ar1 1 '.$arrname[$k].' '.$array[$k];echo '<br>';
			//echo '-0-( '.$arrdelem[$k][0].' )--| '.' |-1-( '.$arrdelem[$k][1].' )--';echo '<br>';
			if ($arrtype[$k] !== 'hid') echo '<tr><td><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		//$m=0;	
		//echo '<br>';
		//echo '$array['.$k.']-'.$array[$k];//repair
				
			switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td><input size="'.$arrtype[$k].'"  name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td><textarea placeholder="'.$arrname[$k].'" rows="'.$r.'" cols="'.$c.'"  name="'.$k.'" tabindex="'.$k.'" value="'.htmlspecialchars($array[$k]).'">'.htmlspecialchars($array[$k]).'</textarea></td>';
				break;
			}
			case 'news':
			{
				$ans=$this->getallnewsite($tabl,$ida,$idsite);
				//print_r($ans);
				$ans['id'][]='';
				$ans['nam'][]='нет';
				echo '<td>';
					//print_r($allpags['num']);
					echo '<span>';
					echo '<select style="max-width:200px;" class="select_opt" name="'.$k.'">';
					$i=0;
					while ($elem=each($ans['nam'])){
						if ($ans['id'][$i] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						else echo '<option value="'.$ans['id'][$i].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						$i++;
					}
				echo '</select></span></td>';
				break;
			}
			case 'typ':
			{
				
				echo '<td title="'.$arrname[$k].'" class="l">';	
				//print_r($allpags[$m1]['num']);
				echo '<select style="max-width:200px;" name="'.$k.'">';
				$i=0;
				while ($elem=each($type_input)){
						if ($elem['value'] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$elem['value'].'">'.$elem['value'].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
				echo '<td><input title="'.$arrname[$k].'" size="'.$s.'"  name="'.$k.'" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
				break;
			}
		}
	if ($zn<1) $zn=1;
	}
	elseif ($arrdelem[$k][0] <> '' && $arrdelem[$k][1] == '') {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= $array[$k];
		//if ($arr1[count($arr1)-1] <> '') $arr1[count($arr1)]='';
		if ($arrtype[$k] !== 'hid') echo '<tr><td><label>'.$arrname[$k].'</label></td>';
		else echo '<td class="h"></td>';
		$m=0;$m1=0;
		if (is_array($arr1)) {
		if ($arrtype[$k] == 'check') echo '<td colspan="2" style="text-align: center">';
		//echo '<br>ar1----------'.$k.'------------<br>';print_r($arr1);	
		foreach ($arr1 as $val){
			$m++;	
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td><input  name="'.$k.$m1.'00" type="hidden" value="'.htmlspecialchars($val).'"></td>';
				break;
			}
			case 'text':
			{
				echo '<td><textarea placeholder="'.$arrname[$k].'" rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.$m1.'00" tabindex="'.$k.'" >'.htmlspecialchars($val).'</textarea></td>';
				break;
			}
			case 'check':
			{
				
				$checkval=array(0=>'bl', 1=>'mn', 2=>'bt', 3=>'ft', 4=>'hd', 5=>'bf', 6=>'sw');
				$namcheckarr=array(0=>'контент', 1=>'меню', 2=>'кнопки', 3=>'футер', 4=>'хедер', 5=>'поиск',6=>'карусель');
				//echo $checkval[$m1].'  '.$val.'<br>';
				//echo '<label> '.$namcheckarr[$m1];
				if ($val == $checkval[$m1]){
				echo '<input type="hidden" name="'.$k.$m1.'00" value="n'.$checkval[$m1].'"></input>';	
				echo '<input title="'.$namcheckarr[$m1].'" type="checkbox" checked name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				else {
				echo '<input  type="hidden" name="'.$k.$m1.'00" value="'.$val.'"></input>';
				echo '<input title="'.$namcheckarr[$m1].'" width="5px" type="checkbox"  name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				echo ' </label>';
				break;
			}
			case 'pags':
			{
				$allpags[$m1]=$this->getallpages('pages');
				//$allpags[$m1]=$allpags;
				$allpags[$m1]['num'][]='';
				$allpags[$m1]['nam'][]='';
				echo '<td>';	
				//print_r($allpags[$m1]['num']);
				echo '<select style="max-width:200px;"" name="'.$k.$m1.'00">';
				$i=0;
				while ($elem=each($allpags[$m1]['nam'])){
						if ($allpags[$m1]['num'][$i] == $val ) echo '<option selected value="'.$val.'">'.$allpags[$m1]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m1]['num'][$i].'">'.$allpags[$m1]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				break;
			}
			default:
			{
			//echo $arrtype[$k].'-'.$m.'-'.count($arr1).'>'.$val;
			//print_r($clas);	
			if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				$arrtype[$k]=$arrt[1];
				//else $arrtype[$k]='';
				}
			if($arrtype[$k] == 'pcs') $arrt[0]='pic';
				if ($arrt[0] == 'pic')
				{
					if($arrtype[$k] == 'pcs' && $m < count($arr1)-1) $arrt[0]='pic';
					elseif($m==1 && $arrtype[$k] == 'pcs') {$arrt[0]='pic';}
					else $arrt[0]='';
					if (file_exists($clas['img'].$val) && $val<>'')
					{
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<td  class="l" style="width: auto; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">'.$val.'
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input title="'.$arrname[$k].'" name="'.$k.$m1.'00" type="file"></input></td>';
						}
					}
					else {
					echo '<td><input name="'.$k.$m1.'00" type="file">';
					echo '<input title="'.$arrname[$k].'" type="text" name="'.$k.$m1.'00" value="'.$val.'"></td>';	
					echo '<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.' "></td>';	
					}
				}
				elseif($arrtype[$k]>0) 
				{
					echo '<td><input title="'.$arrname[$k].'" size="'.$s.'" name="'.$k.$m1.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($val).'"></td>';
				}
				break;
			}
		}
		$m1++;
		}
		if ($arrtype[$k] == 'check') echo '</td>';
		}
		if ($m1>$zn) $zn=$m1;
		}
	else {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= @ $array[$k];
		//print_r($arr1);	echo '<br>ar2----------------------<br>';
			for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		if ($arrtype[$k] !== 'hid') echo '<td><label>'.$arr0[$k][0].'</label></td>';
		else echo '<td></td>';
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
		//echo '<BR> arr2--';
		//echo mb_detect_encoding($array[$k]).'-'.$k.'-'.$m.'-'.$j.'-'.$arr2[$m][$j];//repair
		//print_r($arr2[$m][$j]);
		$allpags[$m]=$this->getallpages('pages');
		$allpags[$m]['num'][]='';
		$allpags[$m]['nam'][]='';		
		//print_r($allpags[$m]['nam']);
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<td><input  name="'.$k.$m.$j.'00" type="hidden"  value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';
				break;
			}
			case 'text':
			{
				
				if($m == 0)
					echo '<td><textarea placeholder="'.$arrname[$k].'" rows="'.$r.'" cols="'.$c.'"  name="'.$k.$m.$j.'00" tabindex="'.$k.'" >'.htmlspecialchars($arr2[$m][$j]).'</textarea></td>';
				else { 
					echo '<td>';	
					//print_r($allpags[$m]['num']);
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select></td>';
				//echo '<td class="l"><input size="4" id="p" class="inp1" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="10" value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';	
				}
				break;
			}
			default:
			{
				
				if($m == 0)
					echo '<td><input title="'.$arrname[$k].'" size="'.$s.'" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';	
				else {
					echo '<td>';
					//print_r($allpags[$m]['num']);
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>'.' ';
						$i++;
						}
				echo '</select></td>';
					
				}
				break;
			}
		}
		$n++;
		if ($n==count($arr2[$m])) {echo '<tr><td></td>';$n=0;}//
			} 
		}
	//}
		/*if ($arrtype[$k] === 'text') 
		echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.'" tabindex="'.$k.'" >'.htmlspecialchars($arr2[$j]).'</textarea></td>';
		elseif ($arrtype[$k] === 'hid') echo '<td class="h"><input size="'.$arrtype[$k].'" id="p" class="inp" name="'.$k.$j.'" type="hidden"  maxlength="'.$m.'" value="'.htmlspecialchars($arr2[$j]).'"></td>';
		else echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.$j.'00" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($arr2[$j]).'"></td>';*/
		
//}
		//echo '<td class="h"><input size="'.$arrtype[$k].'" id="p" class="inpL" name="'.$k.'" type="text"  maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'"></td>';
		if ($j>$zn) $zn=$j;
		}
		$l++;
		if ($l>$t) {$l=0; echo '</tr>';}
}
echo '<input name="zn" value="'.$zn.'" type="hidden">';
	if ($_GET['cust']) {
		echo '<tr><td><label>'.$arrname[$k].'</label></td>';
		echo '<td class="l"><input size="'.$s.'" name="'.$k.'"  maxlength="'.$maxlen[$k].'" value="'.$array[$k].'"></td></tr>';
	}
	/*echo '</table>';
	echo '<input id="regBut" type="submit"  tabindex="'.$k.'" value=" Записать " />';
	echo '</form>';*/
}
public function issetMaket($res0,$ncount,$n=0){
	$i=0;
		if($res0){
			foreach($res0 as $values){	
			if($values){
			$arrstl[$i]=explode('|',$values);
			}
			else 	$arrstl[$i]='';
		$i++;
		}
		
		}
		else for ($i=$n;$i<$ncount;$i++) $arrstl[$i]='';	
		//var_dump($arrstl);
	return $arrstl;
}

	public function editDBD($arrname, $arrtype, $array,$arrdelem,$clas,$tabl,$fields,$arridmen,$arrrequer,$ida,$idsite,$c,$r,$s,$t){	
	$allpags=$this->getallpages('pages');
	$table=$tabl['ed'];
	//if($table<>'allsites')$type_input=$arridmen[0];//array(11=>'cont', 0=>'land', 1=>'gall', 7=>'flex', 8=>'mag', 9=>'cat',6=>'mob' ,4=>'fb', 3=>'tw',5=>'qw',10=>'shop',2=>'blog');
	
	if(!isset($_GET['cust']) && !isset($_GET['in']) &&  ($table === 'allmakets' ||  $table === 'maket')){
	$this->y=$this->ready_str_field($fields,2,1);
	
	$mak='Maket';
	$res0=$this->db->query('SELECT '.$this->y.'   FROM `'.$table.'` WHERE `Maket`=^Ns;',$mak);
	$i=0;
	}
	
	if(isset($res0)){
	foreach($res0 as $values){
	if($values){
		$arrstl[$i]=explode('|',$values);
		}
	else 	$arrstl[$i]='';
	$i++;
	}
	}
	else for ($i=0;$i<count($array);$i++) $arrstl[$i]='';
	$l=0;
	$n=0;$m=0;$zn=0;
	echo '<div class="formsection4">';
	if ($_GET['editp']=='new') echo '<form method="POST" action="" enctype="multipart/form-data">';
	else echo '<form method="POST" action="" enctype="multipart/form-data">';
	echo '<input class="button" id="regBut1" type="submit"  tabindex="22" value=" Записать " />';
	//echo $localdomen;
	//print_r($arrrequer);
	echo '<input type="hidden" name="sucss" value="'.$_SERVER['HTTP_HOST'].'"/>';
	for ($k=0;$k<(count($arrname)-2);$k++) {
		if(strstr($arrrequer[$k],'r'))$requered[$k] = 'required';
		else $requered[$k] = '';
		if(strstr($arrrequer[$k],'u'))$arrtype[$k]= 'hid';
		//echo $arrtype[$k];
		if ($arrtype[$k]>10) $maxlen[$k]=$arrtype[$k];
		elseif(is_int($arrtype[$k])) $maxlen[$k]=$arrtype[$k];
		else $maxlen[$k]=50;
		if ($arrtype[$k]>0) $s=2*strlen($arrtype[$k]);
		if ($s<10) $s=200;
		elseif ($s>30) $s=100;
	//$arrdelem[$k][0]== '' &&  $arrdelem[$k][1] == ''
	if ($arrdelem[$k]== '') {
			
			if ($arrtype[$k] !== 'hid') echo '</li></ul><ul class="editor label"><label>'.$arrname[$k].'</label>';
		else echo '<ul>';
		echo '<li>';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<input '.$requered[$k].' size="'.$arrtype[$k].'" name="'.$k.'" type="hidden"  maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'">';
				break;
			}
			case 'text':
			{
				echo '<textarea '.$requered[$k].'  rows="'.$r.'" cols="'.$c.'"  name="'.$k.'" tabindex="'.$k.'" >'.htmlspecialchars($array[$k]).'</textarea>';
				break;
			}
			case 'forms':
			{
					$ans=$this->getallformsite('nameform',$ida,$idsite);
					
					$ans['idform'][]=0;
					$ans['namform'][]='нет';
					echo '<span>';
					echo '<select style="max-width:200px;" name="'.$k.'">';
					$i=0;
					while ($elem=each($ans['namform'])){
						if ($ans['idform'][$i] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$ans['namform'][$i].'('.$ans['idform'][$i].')</option>';
						else echo '<option value="'.$ans['idform'][$i].'">'.$ans['namform'][$i].'('.$ans['idform'][$i].')</option>';
						$i++;
					}
				echo '</select></span>';
				break;
			}
			case 'news':
			{
					$ans=$this->getallnewsite($tabl,$ida,$idsite);
					$ans['id'][]='';
					$ans['nam'][]='нет';
					echo '<span>';
					echo '<select style="max-width:200px;" name="'.$k.'">';
					$i=0;
					while ($elem=each($ans['nam'])){
						if ($ans['id'][$i] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						else echo '<option value="'.$ans['id'][$i].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						$i++;
					}
				echo '</select></span>';
				break;
			}
			case 'typ':
			{
				if($table=='allsites' && $k==7) $type_input=array(0=>'Новости',1=>'Наука',2=>'Учеба',3=>'Интернет',4=>'Презентация',5=>'Музыка',6=>'Литература',7=>'Спорт',8=>'Развлечения',9=>'Торговля',10=>'Соцсеть');
				elseif($table=='allsites' && $k==6) $type_input=array(6=>'Компактный',3=>'Галлерея',7=>'Дизайнерский',8=>'Структурированый',4=>'Мобильный',5=>'Адаптивный',9=>'Каталог',1=>'Лента новостей',2=>'Видеоблог',0=>'Визитка',10=>'Корпоративный');
				elseif($table=='allsites' && $k==5) $type_input=array(11=>'Многостраничный', 0=>'Лендинг', 1=>'Галлерея', 7=>'Адаптив', 8=>'Магический', 9=>'Иерархический',6=>'Мобильный', 4=>'Фибинг', 3=>'Твитинг',5=>'Квизинг',10=>'Интернет-магазин',2=>'Блог');
				elseif($table=='fonts' && $k==2) {
					$type_input=array('serif','sans-serif','cursive','fantasy','monospace','inherit');
					$name_type_input=array('шрифты с засечками','рубленные шрифты','курсивные шрифты','декоративные шрифты','моноширинные шрифты','Наследует значение');
				}
				elseif($table=='fonts' && $k==4) {
					$type_input=array('inherit','ultra-condensed','extra-condensed','condensed ','semi-condensed','normal','semi-expanded','expanded','extra-expanded ','ultra-expanded');
					$name_type_input=$type_input;
				}
				elseif($table=='fonts' && $k==5) {
					$type_input=array('normal','italic','oblique','inherit');
					$name_type_input=$type_input;
				}
				elseif($table=='fonts' && $k==6) {
					$type_input=array('normal','small-caps','inherit');
					$name_type_input=$type_input;
				}
				elseif($table=='fonts' && $k==7) {
					$type_input=array('bold','bolder','lighter','normal','100','200','300','400','500','600','700','800','900');
					$name_type_input=$type_input;
				}
				else  {
					$type_input=$arridmen[0];
					$name_type_input=$arridmen[1];
				}
				echo '<select style="max-width:200px;" name="'.$k.'">';
				$i=0;
				
				//echo $array[$k];
				while ($elem=each($type_input)){
						if($table<>'allsites'){
						if ($elem['value'] === $array[$k]) echo '<option selected value="'.$elem['value'].'">'.$name_type_input[$elem['key']].'</option>';
						else echo '<option value="'.$elem['value'].'">'.$name_type_input[$elem['key']].'</option>';
						}
						else {
							if($elem['key']<=$array[$k] || $k<>5){
							if ($elem['key'] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$elem['value'].'</option>';
						else echo '<option value="'.$elem['key'].'">'.$elem['value'].'</option>';
							}
						}
						$i++;
						}
				echo '</select>';
				break;
			}
			default:
			{
				echo '<input '.$requered[$k].'  placeholder="'.$placeholder.'" size="'.$s.'" name="'.$k.'" type="text" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($array[$k]).'">';
				break;
			}
		}
		echo '</li>';
	if ($zn<1) $zn=1;
	
	}
elseif ($arrdelem[$k][0] <> '' && !isset($arrdelem[$k][1])) {
		$arr0[$k]=explode(';',$arrname[$k]);
	if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
	//elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
	else $arr1= $array[$k];
	if ($arrtype[$k] !== 'hid') echo '</li></ul><ul class="editor label"><label>'.$arrname[$k].'</label>';
	else echo '<ul>';
	$m=-1;$m1=0;
	if (is_array($arr1)) {
	if ($arrtype[$k] == 'check') echo '</li></ul><ul class="editor label">';
	foreach ($arr1 as $val){
			$m++;	
			if (is_array($arrstl[$k])) $placeholder=$arrstl[$k-2][$m];
			else $placeholder='';
			//print_r($placeholder);
			if($m==0)echo '<li>';
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<input '.$requered[$k].' name="'.$k.$m1.'00" type="hidden" value="'.htmlspecialchars($val).'">';
				break;
			}
			case 'text':
			{
				echo '<textarea  '.$requered[$k].' placeholder="'.$placeholder.'" rows="'.$r.'" cols="'.$c.'" name="'.$k.$m1.'00" tabindex="'.$k.'" >'.htmlspecialchars($val).'</textarea>';
				break;
			}
			case 'check':
			{
				if($table===$tabl['pages']){
					$rest=$this->read_namparams('setTypesPage',0);
					//print_r($rest);
					$checkval=$rest[1];
					//$checkval=array(0=>'bl', 1=>'mn', 2=>'bt', 3=>'ft', 4=>'hd', 5=>'bf', 6=>'sw',7=>'fm');
					$namcheckarr=$rest[0];
					//$namcheckarr=array(0=>'контент', 1=>'меню', 2=>'кнопки', 3=>'футер', 4=>'хедер', 5=>'поиск',6=>'карусель',7=>'форма');
				}
				elseif($table==='scripts'){
					$checkval=array(0=>'us',1=>'bl');
					$namcheckarr=array(0=>'used',1=>'blocked');
				}
				elseif($table==='customers'){
					$rest=$this->read_namparams('setHosting',0);
					//$checkval=$rest[1];
					$namcheckarr=$rest[0];
					$checkval=array( 0=>'y', 1=>'y', 2=>'y', 3=>'y', 4=>'y', 5=>'y',6=>'y', 7=>'y', 8=>'y');
					//$namcheckarr=array('Подключение','Редактор контента','Домен второго уровня SSL','Конструктор','SEO','Почта','Персональная база','Объем диска','Тип размещения');
				}
				//echo $checkval[$m1].'  '.$val.'<br>';
				echo '<label> '.$namcheckarr[$m1].' </label>';
				if ($val === $checkval[$m1]){
				echo '<input type="hidden" name="'.$k.$m1.'00" value="n'.$checkval[$m1].'"></input>';	
				echo '<input style="margin-right: 20px;margin-bottom: 10px;" title="'.$namcheckarr[$m1].'" type="checkbox" checked name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				else {
				echo '<input type="hidden" name="'.$k.$m1.'00" value="'.$val.'"></input>';
				echo '<input style="margin-right: 20px;margin-bottom: 10px;"  title="'.$namcheckarr[$m1].'" type="checkbox"  name="'.$k.$m1.'00" value="'.$checkval[$m1].'">'.'    '.'</input>';
				}
				//echo '</div>';
				break;
			}
			case 'typ':
			{
				if($table=='fonts' && $k==2) {
					$type_input=array('','serif','sans-serif','cursive','fantasy','monospace','inherit');
					$name_type_input=array('','шрифты с засечками','рубленные шрифты','курсивные шрифты','декоративные шрифты','моноширинные шрифты','Наследует значение');
				}
				elseif($table=='fonts' && $k==4) {
					$type_input=array('','inherit','ultra-condensed','extra-condensed','condensed ','semi-condensed','normal','semi-expanded','expanded','extra-expanded ','ultra-expanded');
					$name_type_input=$type_input;
				}
				elseif($table=='fonts' && $k==5) {
					$type_input=array('','normal','italic','oblique','inherit');
					$name_type_input=$type_input;
				}
				elseif($table=='fonts' && $k==6) {
					$type_input=array('','normal','small-caps','inherit');
					$name_type_input=$type_input;
				}
				elseif($table=='fonts' && $k==7) {
					$type_input=array('','bold','bolder','lighter','normal','100','200','300','400','500','600','700','800','900');
					$name_type_input=$type_input;
				}
				else  {
					$type_input=$arridmen[0];
					$name_type_input=$arridmen[1];
				}
				echo '<select style="max-width:200px;" name="'.$k.$m1.'00">';
				$i=0;
				while ($elem=each($type_input)){
						
						if ($elem['value'] === $val) echo '<option selected value="'.$elem['value'].'">'.$name_type_input[$elem['key']].'</option>';
						else echo '<option value="'.$elem['value'].'">'.$name_type_input[$elem['key']].'</option>';
						$i++;
						}
				echo '</select>';
				break;
			}
			case 'forms':
			{
					$ans[$m1]=$this->getallformsite('nameform',$ida,$idsite);
					//print_r($ans);
					$ans[$m1]['idform'][]='';
					$ans[$m1]['namform'][]='нет';
					echo '<span>';
					echo '<select style="max-width:200px;" name="'.$k.$m1.'00">';
					$i=0;
					while ($elem=each($ans[$m1]['namform'])){
						if ($ans[$m1]['idform'][$i] == $val) echo '<option selected value="'.$val.'">'.$ans[$m1]['namform'][$i].'('.$ans[$m1]['idform'][$i].')</option>';
						else echo '<option value="'.$ans[$m1]['idform'][$i].'">'.$ans[$m1]['namform'][$i].'('.$ans[$m1]['idform'][$i].')</option>';
						$i++;
					}
				echo '</select></span>';
				break;
			}
			case 'news':
			{
					$ans=$this->getallnewsite($tabl,$ida,$idsite);
					$ans['id'][]='';
					$ans['nam'][]='нет';
					echo '<span>';
					echo '<select style="max-width:200px;" name="'.$k.$m1.'00">';
					$i=0;
					while ($elem=each($ans['nam'])){
						if ($ans['id'][$i] == $array[$k]) echo '<option selected value="'.$array[$k].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						else echo '<option value="'.$ans['id'][$i].'">'.$ans['nam'][$i].'('.$ans['id'][$i].')</option>';
						$i++;
					}
				echo '</select></span>';
				break;
			}
			case 'pags':
			{
				$allpags[$m1]=$this->getallpages('pages');
				$allpags[$m1]['num'][]='';
				$allpags[$m1]['nam'][]='';
				echo '<select style="max-width:200px;" style="margin-right: 20px;margin-bottom: 10px;"  name="'.$k.$m1.'00">';
				$i=0;
				while ($elem=each($allpags[$m1]['nam'])){
						if ($allpags[$m1]['num'][$i] == $val ) echo '<option selected value="'.$val.'">'.$allpags[$m1]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m1]['num'][$i].'">'.$allpags[$m1]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select>';
				break;
			}
			default:
			{
			
			if (strstr($arrtype[$k],'pic')) {
				$arrt=explode('=',$arrtype[$k]);
				$arrtype[$k]=$arrt[1];
				
				}
			if($arrtype[$k] === 'pcs') $arrt[0]='pic';
			else $arrt[0]='';
				if ($arrt[0] === 'pic')
				{
					if($arrtype[$k] == 'pcs' && $m < count($arr1)-1) $arrt[0]='pic';
					elseif($m==1 && $arrtype[$k] == 'pcs')$arrt[0]='pic';
					else $arrt[0]='';
					if (file_exists($clas['img'].$val) && $val<>'')
					{
						$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<ul style="width: auto; padding: 20px; margin: 10px; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input name="'.$k.$m1.'00" type="file"></input>';
						echo '</ul>';
						}
					}
					else {
					echo '<ul style="text-align: center; width: auto; padding: 20px; margin: 10px; background-image: url('.'./images/error.gif'.');background-repeat: no-repeat"><input name="'.$k.$m1.'00" type="file">';
					if ($val) echo '<input type="text" name="'.$k.$m1.'00" value="'.$val.'"></ul>';	
					else echo '<input type="hidden" name="noupload'.$k.$m1.'" value=" "></ul>';	
					}
				}
				elseif($arrtype[$k]>0) 
				{
					if(file_exists($clas['img'].$val))$sizeP=getimagesize($clas['img'].$val);
					if($sizeP[0]==0 && $sizeP[1]==0){
					echo '<span><input type="'.$arrtype[$k].'" style="margin-right: 10px;margin-bottom: 10px;" placeholder="'.$placeholder.'" size="'.$s.'"  name="'.$k.$m1.'00"  tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($val).'"></span>';
					}
					else {
						if(file_exists($clas['img'].$val))$size = GetImageSize($clas['img'].$val); 
						if($size[0]>0 && $size[1]>0){
						echo '<ul style="width: auto; padding: 20px; margin: 10px; background-size:contain; background-image: url('.$clas["img"].$val.');background-repeat: no-repeat">
						<input type="text" name="'.$k.$m1.'00" value="'.$val.'">
						<input type="hidden" name="noupload'.$k.$m1.'" value="'.$val.'"></input>';	
						echo '<input '.$requered[$k].' name="'.$k.$m1.'00" type="file"></input>';
						echo '</ul>';
						}
					}
				}
				break;
			}
		}
		if($m==count($arr1))echo '</li>';
		$m1++;
		}
		
		}
		if ($m1>$zn) {$zn=$m1;echo '</li></ul>';}
		
		}
else {
		$arr0[$k]=explode(';',$arrname[$k]);
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= @ $array[$k];
		//print_r($arr1);	echo '<br>ar2----------------------<br>';
			for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		if ($arrtype[$k] !== 'hid') echo '</li></ul><ul class="editor label"><label>'.$arr0[$k][0].'</label>';
		else echo '<ul>';
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		if($m==0)echo '<li>';
		for ($j=0;$j<count($arr2[$m]);$j++){ 
		//echo '<BR> arr2--';
		//echo mb_detect_encoding($array[$k]).'-'.$k.'-'.$m.'-'.$j.'-'.$arr2[$m][$j];//repair
		//print_r($arr2[$m][$j]);
		$allpags[$m]=$this->getallpages('pages');
		$allpags[$m]['num'][]='';
		$allpags[$m]['nam'][]='';		
		//print_r($allpags[$m]['nam']);
		
		switch ($arrtype[$k])
		{
			case 'hid': {
				echo '<input '.$requered[$k].' id="p" class="inpH" name="'.$k.$m.$j.'00" type="hidden"  value="'.htmlspecialchars($arr2[$m][$j]).'">';
				break;
			}
			case 'text':
			{
				
				if($m == 0)
					echo '<textarea type="'.$arrtype[$k].'" '.$requered[$k].' style="margin-right: 10px;margin-bottom: 10px;" rows="'.$r.'" cols="'.$c.'" id="p" class="inpT" name="'.$k.$m.$j.'00" tabindex="'.$k.'" >'.htmlspecialchars($arr2[$m][$j]).'</textarea>';
				else { 
					//echo '<div class="l s1">';	
					//print_r($allpags[$m]['num']);
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>';
						$i++;
						}
				echo '</select>';
				//echo '<td class="l"><input size="4" id="p" class="inp1" name="'.$k.$m.$j.'00" type="text" tabindex="'.$k.'" maxlength="10" value="'.htmlspecialchars($arr2[$m][$j]).'"></td>';	
				}
				
				break;
			}
			default:
			{
				if (is_array($arr2[$m])){
				if($m == 0)
					echo '<input '.$requered[$k].'  type="'.$arrtype[$k].'" style="margin-right: 10px;margin-bottom: 10px;" size="'.$s.'"  name="'.$k.$m.$j.'00" tabindex="'.$k.'" maxlength="'.$maxlen[$k].'" value="'.htmlspecialchars($arr2[$m][$j]).'">';	
				else {
					//echo '<div class="l s1">';
					//print_r($allpags[$m]['num']);
					echo '<select style="max-width:200px;" name="'.$k.$m.$j.'00">';
					$i=0;
					while ($elem=each($allpags[$m]['nam'])){
						if ($allpags[$m]['num'][$i] == $arr2[$m][$j] ) echo '<option selected value="'.$arr2[$m][$j].'">'.$allpags[$m]['nam'][$i].'</option>';
						else echo '<option value="'.$allpags[$m]['num'][$i].'">'.$allpags[$m]['nam'][$i].'</option>'.' ';
						$i++;
						}
				echo '</select>';
				//echo '</div>';	
				}
				}
				break;
			}
		}
		$n++;
		if ($n==count($arr2[$m])) 	echo '</ul>';$n=0;
	} 
	if($m==count($arr1))echo '</li></ul>';	
		}
	if ($j>$zn) $zn=$j;
	//echo '</div>';
	}
		//$l++;
		//if ($l>$t) {$l=0; echo '<div class="tr"></div>';}
	}
	//if (isset($_GET['cust']) || $_GET['tab']<>) ) {
	$i=0;
	while(isset($arrtype[$k+$i]) && $k+$i <count($array)+1)	{
		if ($arrtype[$k+$i] !== 'hid') {
			echo '</li></ul><ul class="editor label"><label>'.$arrname[$k+$i].'</label></ul>';
			echo '<input style="margin-right: 10px;margin-bottom: 10px;" placeholder="'.$placeholder.'" size="'.$s.'" name="'.($k+$i).'" type="text" tabindex="'.($k+$i).'" maxlength="'.$maxlen[$k+$i].'" value="'.htmlspecialchars($array[$k+$i]).'">';
		}
		else echo '<input  type="hidden" " name="'.($k+$i).'" value="'.htmlspecialchars($array[$k+$i]).'">';
		if($k+$i < count($array)-1)$i++;
		else break;
	}
	//}
		echo '<input name="zn" value="'.$zn.'" type="hidden">';	
echo '</div>';

}
	
	function chislo($t){
		$t1=array();
		$t1=explode('.',$t);
		if ($t1[1] <> null) $nc=strlen(trim($t1[1]));
		$tx=$t1[0]+$t1[1]/pow(10,$nc);
		//echo $nc.'  '.pow(10,$nc).'<br>';
		//echo $t1[0].'  '.$t1[1].'<br>';
		//echo $tx.'<br>';
		settype($tx,"float");
		if ($tx) return $tx;
		else return false;
	}
	
	function add($tabList) {
		$sections = explode("\n", $tabList);
		$num = 0;
		$end = count($sections);
		$this->sectionsArr = $this->getSection($sections, $num, 0, $end);
		$this->addSections(0, $this->sectionsArr);		
	}
	
	public function isthatsite($site, $np, $table){
	if($table==='elemap'){$field1='codeGJS';	$field2='domen';}
	else {$field1='numpage';	$field2='site';}
	$res=$this->db->query('SELECT `'.$field1.'`,`'.$field2.'` FROM `'.$table.'` WHERE `'.$field1.'` = ^Ni and `'.$field2.'` = ^Ns;', $np, $site);
	if($res !== null) return true;
	else {
		$res=$this->db->query('SELECT `'.$field1.'`,`'.$field2.'` FROM `'.$table.'` WHERE `'.$field1.'` = ^Ni and `'.$field2.'` = ^Ns;', $np, 'all');
		if($res) return $res;
		else return false;
	}
}

public function getlookforfields($for1,$for2,$table) {
//$res = array();
//echo '----';
$res=$this->db->query('SELECT `numpage`,`title`,`site` FROM `'.$table.'`  WHERE `site` = ^Ns and `title` = ^Ns;', $for1, $for2);
//echo $res->numpage;
if (isset($res->numpage)){return $res->numpage;}
else  {return false;}
} 

public function reloadmass($mass1,$mass2,$td,$tt,$table){
$return=array();
if (strstr($mass1,$td)) $mh=explode($td,$mass1);
else $mh= null;
//print_r($mh);
if (strstr($mass2,$tt)) $mt=explode($tt,$mass2);
else $mt=null;
//print_r($mt);
//echo '<br>';
//echo $table;
//echo '<br>';
$return[0]='';
$return[1]='';
if (is_array($mh) && is_array($mt)) {
for ($i=0; $i<count($mt); $i++){
	if (isset($mh[$i])) {
	if ($this->isthatsite($_SERVER['HTTP_HOST'], $mh[$i], $table)) {
	if ($i<count($mh)-1){	
		//echo '-'.$i.'-'.$mh[$i];
		if (isset($mh[$i])) $return[0].=$mh[$i].$td;//$mh[$i]<>''
		if (isset($mt[$i])) $return[1].=$mt[$i].$tt;
		}
	else {
		if (isset($mh[$i])) $return[0].=$mh[$i];
		if (isset($mt[$i])) $return[1].=$mt[$i];
	}	
	//echo $return[0].$return[1].'<br>';	
}
	elseif($mh[$i]=='' && $mt[$i]<>'') {
		$return[0].=$mh[$i].$td;
		$return[1].=$mt[$i].$tt;
	}	
	}
}
}
else {
	$return[0]=$mass1;
	$return[1]=$mass2;
}	
return $return;	
}

private function getdomenids($ids){
	if ($ids>0)	{
		$res=$this->db->query('SELECT `domen` FROM `allsites` WHERE `ids`=^Ni;',$ids);
		return $res;
	}
	else return false;
}

public function initbdF($domen){
	if (isset($domen)) $this->domen=$domen;
	if ($this->domen <> "") {
	$res=$this->db->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`css`,`script`,`images`,`pages`, `news`,`element`,`structure`,`desc_site` FROM `allsites` WHERE `domen` = ^Ns;', $this->domen);	
	if($res){
		$ret=explode('/',$res->domen);
		if(count($ret)>1) {
			//$res->domen='gjs.'.$ret[0];
			$res->simlink=$ret[1];	
			}
	}	
	//else echo 'Сайт <'.$domen.'> в базе данных не найден';
	}
	return $res;
	}	
	
function getDataS(){
	$mySite =  Singleton::getInstance('Site');
	//$SiteCurr=$mysite->initbdF($_SERVER['HTTP_HOST'],$numpage,$mode_edit);
	$maketSite = $mySite->getCurrentClas();
	//$mySite->InfoEssence($maketSite);
	return $maketSite;
}	

function getData($id,$tab,$uid=1,$ids=1) {
		$ret=array();
		$typeF = 0;
		if($tab==='elements' || $tab==='elemarch' || $tab==='elemspec') $tab2='structure';
		elseif($tab === 'elemap' || $tab=='pages') $tab2='mapsites'; 
		elseif($tab === 'allmakets')$tab2='maket'; 
		//echo $tab2;
		if($id !== 0 && $tab2 != 'maket') {
		//значениe флага typeF для группы товаров  передается в массив return
		//выводятся только группы со значением флага 1
		$res = $this->db->query('SELECT `typeF` FROM `'.$tab2.'` WHERE `id` = ^Ni;', $id);
			//if($res === null) throw new StructureWException('id does\'t exist', StructureWException::ID_ERROR);	
			$typeF = $res;
		
		}	

$return = array();
//значение флага записывается в возвращаемый массив return
$return['this']['typeF'] = $typeF;		
// из таблицы считываем поля групп, для которых id является корневой группой pid
$return['sections'] = array();
switch ($tab){
	case 'pages':{
		$return['this']['typeF']=0;
		//$All_Pages=$this->getallpages($tabl['pages']);
		//foreach($All_Pages['num'] as $val){
		if($id>0)	{
			$arrother=$this->getPage($id);
			//print_r($arrother['pages'][0]['buttons']);
			$arrbutt=explode('|',$arrother['pages'][0]['buttons']);
			$arrbutlink=explode(';',$arrbutt[1]);
			//print_r($arrbutlink);
		}
		else {
			$Site=$this->initbdF($_SERVER['HTTP_HOST']);
			$arrbutlink=$this->getlookforfields($_SERVER['HTTP_HOST'],'main_'.substr('grandjet.ru',0,3).'_'.$Site->domen,$Site->pages);
		}
			if(is_array($arrbutlink)){
				foreach($arrbutlink as $val){
				$tabl['pages']=$tab;
				$tabl['news']='news';
				if($val<>''){
					$pg= new Page($val,$tabl);	
				//print_r($pg);
					//$lst0='';
					$lst1=$pg->getnamepage($pg);
					//$lst11=array_keys($lst1);
					//$lst0=$lst1[$lst11[0]];
					$return['sections'][] = array('id' => $val, 'name' => $lst1, 'typeF' => 0, 'constrF' => 0, 'ms' =>0, 'numEl' =>1);		
						}
					}
				}
		else { 
			$tabl['pages']=$tab;
			$tabl['news']='news';
				if($arrbutlink<>''){
					$pg= new Page($arrbutlink,$tabl);	
				//print_r($pg);
					$lst1=$pg->getnamepage($pg);
			$return['sections'][] = array('id' => $arrbutlink, 'name' => $lst1, 'typeF' => 0, 'constrF' => 0, 'ms' =>0, 'numEl' =>1);
		}		
		}
		break;
	}
	case 'elements':{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numElst` FROM `'.$tab2.'` WHERE `pid` = ^Ni AND `NumElst` != \'0\' ORDER BY `name`;', $id);
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
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `'.$tab2.'` WHERE `pid` = ^Ni AND `NumEl` != \'0\' ORDER BY `name`;', $id);
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
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEls` FROM `'.$tab2.'` WHERE `pid` = ^Ni AND `NumEls` != \'0\' ORDER BY `name`;', $id);
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
		case 'elemap':{
			$return['this']['typeF']=0;
		if($id>0)	{
			$arrother=$this->getPublPage($id);
			//print_r($arrother['pages']);
			$arrbutlink=explode(';',$arrother['pages'][0]['keywords']);
			
		}
		else {
			$Site=$this->initbdF($_SERVER['HTTP_HOST']);
			$arrbutlink=$this->getlookforfields($_SERVER['HTTP_HOST'],'main_'.substr('grandjet.ru',0,3).'_'.$Site->domen,$Site->pages);
		}
		//$tabl['pages']=$tab;
		$tabl=Utils::getsitetables($_SERVER['HTTP_HOST'],$this->db);
			if(is_array($arrbutlink)){
				//print_r($tabl);
				
				foreach($arrbutlink as $val){
				
				if($val<>''){
					$pg= new Page($val,$tabl);	
				//print_r($pg);
					//$lst0='';
					$lst1=$pg->getnamepage($pg);
					//$lst11=array_keys($lst1);
					//$lst0=$lst1[$lst11[0]];
					$return['sections'][] = array('id' => $val, 'name' => $lst1, 'typeF' => 0, 'constrF' => 0, 'ms' =>0, 'numEl' =>1);		
						}
					}
				}
		else { 
			
				if($arrbutlink<>''){
					$pg= new Page($arrbutlink,$tabl);	
				//print_r($pg);
					$lst1=$pg->getnamepage($pg);
			$return['sections'][] = array('id' => $arrbutlink, 'name' => $lst1, 'typeF' => 0, 'constrF' => 0, 'ms' =>0, 'numEl' =>1);
		}		
		}
		break;
		}
		case 'allmakets':{
			$res=$this->db->query('SELECT * FROM `allmakets` WHERE `id` = ^Ni ',$id);
			$return['section']=array('id'=>$res->id,'Maket'=>$res->Maket);
			$return['styles']=explode('|',$res->styles);
			$return['numparams']=explode('|',$res->numparams);
			$return['fonts']=explode('|',$res->fonts);
			$return['video']=explode('|',$res->video);
			$return['effects']=explode('|',$res->effects);
			$return['scripts']=explode('|',$res->scripts);
			$return['desc']=explode('|',$res->desc);
			$return['forms']=explode('|',$res->forms);
		break;
		}
		default :{
		$res = $this->db->query('SELECT `id`, `name`, `typeF`, `constrF`, `ms`, `numEl` FROM `'.$tab2.'` WHERE `pid` = ^Ni AND `numEl` != \'0\' ORDER BY `name`;', $id);
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
//print_r( $return);echo '<br>';
return $return;			
}	



function getmapsites($uid,$ids,$lpm=0,$mode=0){
	$domen=$this->getdomenids($ids);
	$tabl=Utils::getsitetables($domen,$this->db);
	//show::pauza($domen);
	$arraymap=array();
	$typeF=0;
	$numEl=1;
	//if($mode==1)$arraymap[$lpm]=array('id'=>$lpm,'name'=>'Карта сайта','typeF'=>$typeF,'numEl'=>$numEl,'idauthor'=>$uid,'ids'=>$ids);
	//elseif($domen)$id_group=$this->addSectionPage(1,0,'Карта сайта',$uid,$ids);
	$res=$this->db->query('SELECT `id`,`keywords`,`name` FROM `elemap` WHERE `domen`=^Ns AND `idauthor`=^Ni;',$domen,$uid); 
	//print_r($res);
	
	if($res){
		$id=$lpm+2;
		$id_group=$lpm;
		if(is_array($res)){
		foreach($res as $val){
			$typeF=0;
			$numEl=0;
			$id_group++;
		//print_r($val);
			if(!isset($arraymap[$id_group]))$arraymap[$id_group]=array();
			$pid=explode(';',$val->keywords);
			if($mode==1)$arraymap[$id_group][]=array('id'=>$val->id,'name'=>$val->name.'+','typeF'=>$typeF,'numEl'=>$numEl,'idauthor'=>$uid,'ids'=>$ids);
			elseif($domen)$idgroup=$this->addSectionPage($val->id,$id_group, $val->name.'+',$uid,$ids);
			print($arraymap);
		//$res1=$this->db->query('SELECT `name` FROM `elemap` WHERE `id`=^Ni',$id_group); 
		//print_r($res1);
		//echo $id_group.'  '.$res1->name;
			$id++;
			foreach($pid as $value){
				$typeF=1;
				$numEl=1;
				//if($value<>'')$Page= new Page($value,$tabl);
				//$name_group=$Page->getnamepage($Page);
				$res1=$this->db->query('SELECT `name` FROM `elemap` WHERE `id`=^Ni',$value); 
			//print_r($res1);
				if($res1){
					$name_group=$res1;	
				//echo $res2[0];
						if($value <> 0 ){
							if($mode==1)$arraymap[$id_group][]=array('id'=>$value,'name'=>$name_group,'typeF'=>$typeF,'numEl'=>$numEl,'idauthor'=>$uid,'ids'=>$ids);
							elseif($domen)$id=$this->addSectionPage($value,$id_group+$val->id,$name_group,$uid,$ids);
							$id++;
						}
						
					
		}
		}
		}
		}
		elseif($mode==1) $arraymap[$id_group][]=array('id'=>$res->id,'name'=>$res->name,'typeF'=>$typeF,'numEl'=>$numEl,'idauthor'=>$uid,'ids'=>$ids);
		else $id=$this->addSectionPage($res->id,$id_group+$res->id,$res->name,$uid,$ids);
	}
	if($mode==1)return $arraymap;
	elseif($domen)show::pauza();
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
		if($res !== null) {
			if(!is_array($res)) {
				$return['sections'][] = array('id' => $res->id, 'name' => $res->name, 'typeF' => $res->typeF, 'constrF' => $res->constrF, 'ms' => $res->ms, 'numEl' => $res->numEl);				
			} else {
				foreach($res as $val)
					$return['sections'][] = array('id' => $val->id, 'name' => $val->name, 'typeF' => $val->typeF, 'constrF' => $val->constrF, 'ms' => $val->ms, 'numEl' => $val->numEl);		
			}
		}
		return $return;			
	}		
	
public function getPublPage($numpage){
		$tabl=Utils::getsitetables($_SERVER['HTTP_HOST'],$this->db);
			$res = array();
			if($numpage != 0) {
			$this->numpage=$numpage;
			$res = $this->db->query('SELECT * FROM `elemap` WHERE `codeGJS` = ^Ni;', $this->numpage);
			
			if($res === null) 
				return;
			}
			$return['pages'] = array();
			if($res !== null) {
			//echo 'данные страницы загружены';echo '<br/>';
			if(!is_array($res)) {
				$Page= new Page($res->codeGJS,$tabl);
				$namepage=$Page->getnamepage($Page);
				//print_r($namepage);
				$return['pages'][] = array('numpage' => $res->codeGJS, 'name' => $namepage,'keywords' => $res->keywords);				
			} else {
				foreach($res as $val){
					$Page= new Page($tabl,$val->codeGJS);
					$namepage=$Page->getnamepage($Page);
					$return['pages'][] = array('numpage' => $val->numpage, 'namep' => $namepage,'keywords' => $val->keywords);		
				}	
			}
		}
		//ElementsW::Showobjtype($return['pages'][0]);
		return $return;
			}
	
	
	
public function getPage($numpage){
		$tabl=Utils::getsitetables($_SERVER['HTTP_HOST'],$this->db);
			$res = array();
			if($numpage != 0) {
			$this->numpage=$numpage;
			$res = $this->db->query('SELECT * FROM `'.$tabl['pages'].'` WHERE `numpage` = ^Ni;', $this->numpage);
			if($res === null) 
				//echo ' '.$numpage; 
				//throw new StructureWException('numpage does\'t exist', StructureWException::ID_ERROR);	
				return;
			}
			$return['pages'] = array();
			if($res !== null) {
				//print_r($res);
			//echo 'данные страницы загружены';echo '<br/>';
			if(!is_array($res)) {
				$Page= new Page($res->numpage,$tabl);
				$namepage=$Page->getnamepage($Page);
				//print_r($namepage);
				$return['pages'][] = array('numpage' => $res->numpage, 'namep' => $namepage,'lozungp' => $res->lozungp, 'keywords' => $res->keywords, 'buttons' => $res->buttons,'hrefp' => $res->hrefp, 'typemenu' => $res->typemenu, 'hrefscripts' => $res->hrefscripts, 'hrefstyle' => $res->hrefstyle,'title' => $res->title, 'content' => $res->content, 'levelmenu' => $res->levelmenu,'idmenu' => $res->idmenu, 'hrefimage' => $res->hrefimage, 'list' => $res->list, 'list_href' => $res->list_href,'butthref' => $res->butthref, 'buttimg' => $res->buttimg, 'imgtext' => $res->imgtext, 'idnews' => $res->idnews, 'confp' => $res->configpage);				
			} else {
				foreach($res as $val){
					$Page= new Page($tabl,$val->numpage);
					$namepage=$Page->getnamepage($Page);
					$return['pages'][] = array('numpage' => $val->numpage, 'namep' => $namepage,'lozungp' => $val->lozungp, 'keywords' => $val->keywords, 'buttons' => $val->buttons, 'hrefp' => $val->hrefp,				'typemenu' => $val->typemenu, 'hrefscripts' => $val->hrefscripts, 'hrefstyle' => $val->hrefstyle,'title' => $val->title, 'content' => $val->content, 'levelmenu' => $val->levelmenu,	'idmenu' => $val->idmenu, 'hrefimage' => $val->hrefimage, 'list' => $val->list,'list_href' => $val->list_href,		'butthref' => $val->butthref, 'buttimg' => $val->buttimg, 'imgtext' => $val->imgtext, 'idnews' => $val->idnews,'confp' => $val->configpage);		
				}	
			}
		}
		//ElementsW::Showobjtype($return['pages'][0]);
		return $return;
			}

function getsitetables($domen){
	$db=Singleton::getInstance('DB');
		if ($domen <> "") {
		$Site=$db->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`images`,`pages`, `news`,`element` FROM `allsites` WHERE `domen` = ^Ns;', $domen);		
	}
	if ($Site->strucs == 0) $structure='structure';
	if (isset($Site)) { 
		$tabl=array('news'=>$Site->news, 'pages'=>$Site->pages,'elem'=>$Site->element,'str'=>$structure);
	return $tabl;
	}
	else return false;
		}			

public function getPagelinks2($numpage,$tabl){
	//$db=Singleton::getInstance('DB');
	$return=array();
	//echo $_SERVER['HTTP_HOST'];
	//$tabl=$this->getsitetables($_SERVER["DOCUMENT_ROOT"],$db);
	$res2=$this->db->query("SELECT * FROM namparams WHERE tab=^Ns;",$tabl['pages']);
	//print_r($res2);
	//if (mysql_errno() == "") echo 'загружены параметры таблицы '.$tabl["pages"];
	//else echo "ERROR ".mysql_errno()." ".mysql_error()."\n";
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$arrname=explode('|',$arrnm);
	$arrtype=explode('|',$arrtp);
	$lpg=User::getscountab($tabl['pages'],'numpage', 'f');//последняя страница в pages	
	$res1=$this->db->query('SELECT * FROM '.$tabl['pages'].' WHERE `numpage`=^Ni;',$numpage);
	//if (mysql_errno() == "") echo 'загружены данные страницы '.$numpage."\n";
	//else echo "ERROR ".mysql_errno()." ".mysql_error()."\n";
	$l=0;
	//print_r($res1);echo '<br>';
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
	
	foreach($res1 as $key=>$val){
	if($arrtype[$l] == 'check' && $val == '') 	{
		$array[$l]='bl;mn;bt;ft;hd;bf;sw';
		$arraykey[$key]='bl;mn;bt;ft;hd;bf;sw';
	}
	elseif($val == '') {
	$array[$l]=$arrdelem[$l];
	$arraykey[$key]=$arrdelem[$l];
	}
	else {
	$array[$l]=$val;
	$arraykey[$key]=$val;
	}
	//echo 'array'.$l.'  '.$array[$l].'<br>';
	$l++;
	}
	$k=0;
	//print_r($arraykey);echo '<br>';
	foreach ($arraykey as $key=>$value){
		if ($k<>0 && $k<>20) {
		if (!isset($arrdelem[$k][0])) {
			$return[$key][]=$k;
			$return1[]=$k;
			}
		if(isset($arrdelem[$k][0]) && !isset($arrdelem[$k][1])) {
			if (strstr($value,$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$value);
			//elseif (strstr($value,$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$value);
			else $arr1= $value;
			$m1=0;
			foreach($arr1 as $valu){
				$return[$key][$k][]=$m1;
				$return1[$k][]=$k.$m1;
				$m1++;
		}
	}
	else {
		if(isset($arrdelem[$k][0])) {
		if (strstr($value,$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$value);
		}
		elseif(isset($arrdelem[$k][1])) {
		if (strstr($value,$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$value);
		}
		else $arr1= @ $value;
		//print_r($arr1);	echo '<br>ar2----------------------<br>';
		if(isset($arrdelem[$k][1])) {	
			for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		//}	
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
			$return[$key][$k][$m][]=$j;
			$return1[$k][$m][]=$k.'0'.$m.$j;
			
		}
		}
		}
		}
		//}
		//}
		//else $return1[$k]='';
		}
		$k++;
	}
	//$return1[12]=12;
	for ($k=0;$k<(count($arrname)-1);$k++) {
	if(isset($arrdelem[$k][0]) && isset($arrdelem[$k][1])){
	if (!isset($arrdelem[$k][0]) &&  !isset($arrdelem[$k][0])) {
		$return[]=$k;
		}
	elseif (isset($arrdelem[$k][0]) && !isset($arrdelem[$k][1])) {
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= $array[$k];
		$m1=0;
		foreach($arr1 as $value){
			$return[]=array($k,$m1);
			$m1++;
		}
		}
	else {
		if (strstr($array[$k],$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$array[$k]);
		elseif (strstr($array[$k],$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$array[$k]);
		else $arr1= @ $array[$k];
		//print_r($arr1);	echo '<br>ar2----------------------<br>';
			for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		for ($j=0;$j<count($arr2[$m]);$j++){ 
			$return[$k]=array($k,0,$m,$j);
		}
		}
		}
	}
	else $return[$k]='';
	}	
	return $return1;
}	

			
public function getPagelinks($numpage,$t='pages',$f='numpage'){
	//$db=Singleton::getInstance('DB');
	$return=array();
	//echo $_SERVER['HTTP_HOST'];
	//$tabl=$this->getsitetables($_SERVER["DOCUMENT_ROOT"],$db);
	$res2=$this->db->query("SELECT * FROM namparams WHERE tab=^Ns;",$t);
	//print_r($res2);
	//if (mysql_errno() == "") echo 'загружены параметры таблицы '.$tabl["pages"];
	//else echo "ERROR ".mysql_errno()." ".mysql_error()."\n";
	
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$arrname=explode('|',$arrnm);
	$arrtype=explode('|',$arrtp);
	$lpg=User::getscountab($t,$f, 'f');//последняя страница в pages	
	$res1=$this->db->query('SELECT * FROM  `'.$t.'` WHERE `'.$f.'`=^Ni;',$numpage);
	//if (mysql_errno() == "") echo 'загружены данные страницы '.$numpage."\n";
	//else echo "ERROR ".mysql_errno()." ".mysql_error()."\n";
	$l=0;
	//print_r($res1);echo '<br>';
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
	//echo 'array'.$l.'  '.$array[$l].'<br>';
	$l++;
	}
}	
elseif(!isset($arraykey))	$arraykey[0]='';
//}
//else $arraykey[0]=$res1;
	$k=0;
	//echo '   таблица '.$t.'<br>';
	//print_r($arraykey);echo '<br>';
	
	foreach ($arraykey as $key=>$value){
		if (!isset($arrdelem[$k][0])) {
			$return1[]=$k;
			}
		if(isset($arrdelem[$k][0]) && !isset($arrdelem[$k][1])) {
			if (strstr($value,$arrdelem[$k][0])) $arr1=explode($arrdelem[$k][0],$value);
			//elseif (strstr($value,$arrdelem[$k][1])) $arr1=explode($arrdelem[$k][1],$value);
			else $arr1= $value;
			$m1=0;
			if(is_array($arr1)){
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
		//print_r($arr1);	echo '<br>ar2----------------------<br>';
		if(isset($arrdelem[$k][1])) {	
			for ($n=0;$n<count($arr1);$n++) {
			if (!strstr($arr1[$n],$arrdelem[$k][1])) $arr2= @ $arr1;
			else $arr2[$n]=explode($arrdelem[$k][1],$arr1[$n]);//
			}
		//}	
		for ($m=0;$m<count($arr2);$m++){
		$n=0;	
		if(is_array($arr2[$m])){
		for ($j=0;$j<count($arr2[$m]);$j++){ 
			$return1[$k][$m][]=$k.'0'.$m.$j;
			}
		}
		else $return1[$k][$m][]=$k.'0'.$m.'0';
	}
}
}
		$k++;
}

	//else $return1=$k;
return $return1;
}	
		
public function getPagetable($numpage,$table,$Site){
	$res = array();
	if($table === '')$return['pages'] = array();
	if($numpage !== 0) {
	$this->numpage=$numpage;
	//echo "SELECT * FROM '$table' WHERE `numpage` = ^Ni; ";
	$res = $this->db->query("SELECT * FROM $table WHERE numpage=^Ni;", $this->numpage);
	
	if($res !== null && $res->namep !== '') {
			//echo 'данные страницы загружены';echo '<br/>';
	if(!is_array($res)) {
		if(!$this->getnews($res->idnews))$res->idnews = 0;
		$return['pages'][] = array('numpage' => $res->numpage, 'namep' => $res->namep,
		'lozungp' => $res->lozungp, 'keywords' => $res->keywords, 'buttons' => $res->buttons,
		'hrefp' => $res->hrefp, 'typemenu' => $res->typemenu, 'hrefscripts' => $res->hrefscripts, 'hrefstyle' => $res->hrefstyle,
		'title' => $res->title, 'content' => $res->content, 'levelmenu' => $res->levelmenu,
		'idmenu' => $res->idmenu, 'hrefimage' => $res->hrefimage, 'list' => $res->list, 'list_href' => $res->list_href,
		'butthref' => $res->butthref, 'buttimg' => $res->buttimg, 'imgtext' => $res->imgtext, 'idnews' => $res->idnews, 'site' => $res->site, 'idauthor' => $res->idauthor, 'configpage' => $res->configpage);				
			}
			else 
			{
		foreach($res as $key=>$val)
			if(!$this->getnews($val->idnews))$val->idnews = 0;	
			$return['pages'][] = array('numpage' => $val->numpage, 'namep' => $val->namep,
			'lozungp' => $val->lozungp, 'keywords' => $val->keywords, 'buttons' => $val->buttons, 'hrefp' => $val->hrefp,
			'typemenu' => $val->typemenu, 'hrefscripts' => $val->hrefscripts, 'hrefstyle' => $val->hrefstyle,
			'title' => $val->title, 'content' => $val->content, 'levelmenu' => $val->levelmenu,
			'idmenu' => $val->idmenu, 'hrefimage' => $val->hrefimage, 'list' => $val->list,'list_href' => $val->list_href,
			'butthref' => $val->butthref, 'buttimg' => $val->buttimg, 'imgtext' => $val->imgtext, 'idnews' => $val->idnews, 'site' => $val->site,'idauthor' => $val->idauthor, 'configpage' => $val->configpage);		
			}
		}
		
		else {
			
			$return['pages'][] = array('numpage' => $numpage, 'namep' => $Site->images.'|new_page','lozungp' => ';;;|;;;', 'keywords' => 'key1>key2>key3;title_page;description_page', 'buttons' => ';;;|;;;', 'hrefp' => '','typemenu' =>' wr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac', 'hrefscripts' => '', 'hrefstyle' => '','title' => '', 'content' => ';;;|;;;', 'levelmenu' => ';;;;;','idmenu' => $Site->types, 'hrefimage' => ';;;;;', 'list' =>';;;;;','list_href' => ';;;;;',
			'butthref' => ';;;|;;;', 'buttimg' => ';;;;;', 'imgtext' => ';;;|;;;', 'idnews' => '0', 'site' => '','idauthor' => 0,'configpage' =>'');		
		}
		//debug($return); 
		return $return;
	}	
		return null;
		
}

public function getSitetable($ids,$table='allsites'){
	$res = array();
	//$return = array();
	if($ids > 0) {
	//echo "SELECT * FROM '$table' WHERE `numpage` = ^Ni; ";
	$res = $this->db->query("SELECT * FROM `allsites` WHERE `ids`=^Ni;", $ids);
	//print_r($res);
	if(!$res) {
				return false;
			}
	else {
			
	if(!is_array($res)) {
		//echo 'данные страницы загружены';echo '<br/>';
		if ($res->domen <> '') $return[] = array('ids' => $res->ids,'uid' => $res->uid, 'domen' => $res->domen,'nmpage' => $res->nmpage,'types' => $res->types,'strucs' => $res->strucs,'appoint' => $res->appoint,'css' => $res->css, 'script' => $res->script, 'images' => $res->images,'passwad' => $res->passwad,'logad' => $res->logad,
		'bd' => $res->bd, 'host' => $res->host, 'port' => $res->port,'pages' => $res->pages,
		'news' => $res->news,'element' => $res->element,'structure' => $res->structure,'desc_site' => $res->desc_site);
			}
			else 
			{
		foreach($res as $val)
			if ($val->domen <> '') $return[] = array('ids' => $val->ids,'uid' => $val->uid, 'domen' => $val->domen,'nmpage' => $val->nmpage,'types' => $val->types,'strucs' => $val->strucs,'appoint' => $val->appoint,'css' => $val->css, 'script' => $val->script, 'images' => $val->images,'passwad' => $val->passwad,'logad' => $val->logad,'bd' => $val->bd, 'host' => $val->host, 'port' => $val->port,'pages' => $val->pages,	'news' => $val->news,'element' => $val->element,'structure' => $val->structure,'desc_site' => $val->desc_site);
			}
			//print_r($return);
			return $return;
		}
		
		//ElementsW::Showobjtype($return['pages'][0]);
		
	}	else return false;
}

public function getMaketable($id,$table='maket'){
	$res = array();
	//$return = array();
	if($id > 0) {
	//echo "SELECT * FROM '$table' WHERE `numpage` = ^Ni; ";
	$res = $this->db->query("SELECT * FROM `maket` WHERE `id`=^Ni;", $id);
	if($res === null) {
				return false;
			}
	else {
			//echo 'данные страницы загружены';echo '<br/>';
	if(!is_array($res)) {
		if ($res->Maket <> '') $return[] = array('id' => $res->id, 'Maket' => $res->Maket,
		'styles' => $res->styles, 'numparams' => $res->numparams, 'fonts' => $res->fonts,
		'video' => $res->video, 'effects' => $res->effects, 'scripts' => $res->scripts,
		'ids' => $res->ids,'numpage' => $res->numpage,'numaket' => $res->numaket,'idauthor' => $res->idauthor);
			}
			else 
			{
		foreach($res as $val)
			if ($val->Maket <> '') $return[] = array('id' => $val->id, 'Maket' => $val->Maket,
			'styles' => $val->styles, 'numparams' => $val->numparams, 'fonts' => $val->fonts,
			'video' => $val->video,'effects' => $val->effects, 'scripts' => $val->scripts,
		'ids' => $val->ids,'numpage' => $val->numpage,'numaket' => $val->numaket,'idauthor' => $val->idauthor);
			}
			return $return;
		}
		//ElementsW::Showobjtype($return['pages'][0]);
		return false;
	}	
}

public function allmakets($ids,$maket='Maket'){
	
		if ($ids > 0)	
			if($maket<>'')$res = $this->db->query("SELECT * FROM `allmakets` WHERE `Maket`=^Ns AND `ids`=^Ni;",$maket,$ids);
			else $res = $this->db->query("SELECT * FROM `allmakets` WHERE `ids`=^Ni;",$ids);
		if($res !== null) {
		if(!is_array($res)) { 
	//show::infosh('Найден макет '.$maket);
		$return[]=array($res->id,$res->Maket,$res->styles,$res->flex,$res->grid,$res->numparams,$res->fonts,$res->video,$res->effects,$res->scripts,$res->desc,$res->forms,$res->ids);
		}
		else {
			foreach($res as $val) $return[]=array($val->id,$val->Maket,$val->styles,$val->flex,$val->grid,$val->fonts,$val->numparams,$val->video,$val->effects,$val->scripts,$val->desc,$val->forms,$val->ids);
		}
return $return;
}
//else {echo '<info class="hidno">макет не найден</info>';return false;}
	
}

public function allmaketspage($np,$nm,$sp){
if (isset($np)) $this->np=$np;
if (isset($nm)) $this->nm=$nm;
$res = $this->db->query("SELECT * FROM maket WHERE numpage=^Ni AND numaket=^Ni;", $np,$nm);

if($res == null) {
	$res = $this->db->query("SELECT * FROM maket WHERE numpage=^Ni;", $sp);
	//if ($res)show::infosh($res);
	//else show::infosh(' special layuot for this page is absent');
}
elseif($res == null) return false;
if(is_array($res)){
foreach($res as $key=>$val) {
		//show::infosh($res);
		$spisok_maketov[$val->Maket]=array('id'=>$val->id,'idclas'=>$val->Maket,'styles'=>$val->styles,'flex'=>$val->flex,'grid'=>$val->grid,'numparams'=>$val->numparams,'fonts'=>$val->fonts,'video'=>$val->video,'effects'=>$val->effects,'scripts'=>$val->scripts);
	}
}
else {
	$spisok_maketov[$res->Maket]=array('id'=>$res->id,'idclas'=>$res->Maket,'styles'=>$res->styles,'flex'=>$res->flex,'grid'=>$res->grid,'numparams'=>$res->numparams,'fonts'=>$res->fonts,'video'=>$res->video,'effects'=>$res->effects,'scripts'=>$res->scripts);
	//show::infosh($spisok_maketov);
}
	return $spisok_maketov;
}	
		
public function gettables ($num, $field, $tab)	{
	$res1=array();
	if($num != 0) {
			$res1 = $this->db->query('SELECT * FROM `.$tab.` WHERE `.$field.` = ^Ni;', $num);
		if(isset($res1)) return $res1;	
				else return false;
	}
}

public function konv($tt){
	iconv("WINDOWS-1251","UTF-8",$tt);
}

public function gettexturl($url, $begin1, $begin2,$change ,$end, $code='utf-8'){
	//откуда будем парсить информацию
//$fcontents=file($url);
//if (!$fcontents) echo 'файл не загружен';	
$content = file_get_contents($url);//полный урл страницы с http:// с которого будем вырезать информацию');
//echo $content;
 if($code == 'win')  {
	$begin1=iconv("UTF-8","windows-1251", $begin1);
	$begin2=iconv("UTF-8","windows-1251", $begin2);
	$end=iconv("UTF-8","windows-1251", $end);
	}
// Определяем позицию строки, до которой нужно все отрезать
 $pos = strpos($content, $begin1);//'здесь кусок кода/текста который размещен перед нужным текстом');
 
//Отрезаем все, что идет до нужной нам позиции
 $content = substr($content, $pos);
$pos = strpos($content, $begin2);
$content = substr($content, $pos);
// Точно таким же образом находим позицию конечной строки
 $pos = strpos($content,$end);// 'здесь кусок кода/текста который стоит в конце нужного нам текста');

// Отрезаем нужное количество символов от нулевого
 $content = substr($content, 0, $pos);

//если в тексте встречается текст, который нам не нужен, вырезаем его
 $content = str_replace($begin1,'', $content);
 if ($begin2<>'') $content = str_replace($begin2,$change, $content);
 $content = str_replace('<br>','', $content);
// выводим спарсенный текст.
 if ($code == 'utf-8') echo $content;
elseif($code == 'win')  echo iconv("windows-1251", "UTF-8", $content); 
	
}

public function getcurs($ht, $begin, $end){
$fcontents=file($ht);
if (!$fcontents) echo 'файл не загружен';

//echo '<div>';
//echo '<div class="zag">             данные представлены www.inline.ru            </div>';
$q=0;
foreach ($fcontents as $key=>$val) {
	$find_curs=strstr(iconv("WINDOWS-1251","UTF-8",$val),$begin);
	$find_curs=strstr($val,$begin);
    $find_vers=strstr(iconv("WINDOWS-1251","UTF-8",$val),$end);
	//print_r($val);echo $key.'<br>';
	if ($find_vers) $versia=$key-4;
	if ($find_curs && $q==0) {$nachalo=$key+1;echo 'нашел';}
	else  $q++;
	}
$k=0;
//$arr=array();
//$nachalo=742;
//echo 'begin '.$nachalo;
if(isset($nachalo)){
foreach ($fcontents as $key=>$val){ 
if ($key>$nachalo && $key <$versia) {
		
			if (count($val)<>0) {
			//echo $key.'-'.iconv("WINDOWS-1251","UTF-8", strip_tags($val)).'<br>';
			$arr[$key]=iconv("WINDOWS-1251","UTF-8", strip_tags($val));}
			$k++;
	}
}
		
//echo '</div>';
$l=207;
$return[0]=Array('0'=>$this->$arr[$l],'1'=>$this->chislo($arr[$l+1]),'2'=>$arr[$l+2],'3'=>$arr[$l+3]);
$l=213;
$return[1]=Array('0'=>$arr[$l],'1'=>$this->chislo($arr[$l+1]),'2'=>$arr[$l+2],'3'=>$arr[$l+3]);
$l=219;
$return[2]=Array('0'=>$arr[$l],'1'=>$this->chislo($arr[$l+1]),'2'=>$arr[$l+2],'3'=>$arr[$l+3]);
//echo round($return[0][1],2);
//echo $nachalo;
//print_r($return[0]);
$ts=date('U')+1;
$now=getdate($ts);
$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
$find=$this->db->query('select `datcurs` from `kurs` where `datcurs`= ^Ns;', $tt);
settype($return[0][1],'float');
//echo gettype($return[0][1]);
$db="gjs_deltar_ru";
$conn=mysql_connect("mysql.baze.deltar.ru:63917","gjs_deltar_ru","ittBudB5");
mysql_select_db($db,$conn);
if (!$conn)
{
echo "Не могу подключиться к серверу MySQL";
echo "ERROR ".mysql_errrno()." ".mysql_error()."/n";
exit;
}
else 
{
//echo "Успешное подключение к базе данных";
echo "<BR>";
}
$gd="SELECT `datcurs` FROM `kurs` WHERE `datcurs`='".$tt."'";
$sqld=mysql_query($gd);		
if (mysql_num_rows($sqld)== 0) {
	echo 'курс добавляется';
	$gk="INSERT INTO `kurs` (`datcurs`,`dol`,`evro`,`gbp`) VALUES ('$tt','".$return[0][0]."','".$return[1][0]."','".$return[2][0]."');";
    $sqlk=mysql_query($gk);
	if (mysql_errno()<>0) {
	echo "ERROR ".mysql_errno()." ".mysql_error()."\n";echo '<br/>';
	echo $gk;echo "<BR>";
		}
}	
	
mysql_select_db($db,$conn);
if (!$find) $this->db->query('INSERT INTO `kurs` (`datcurs`,`dol`,`evro`, `gbp`) VALUES (^Ns, ^Ni, ^Ni, ^Ni);', $tt, round(1*$return[0][1],2),round($return[1][1],2),1*$return[2][1]);
return $return;
}
}	
			
public function getnews($numnews, $table='news') {
		if($numnews > 0){	
			//$this->numnews=$numnews;
			//$this->table=$tabl;
			//if (isset($table)) $this->table=$table;
			//else 
			//$this->table='news';
			
			if($numnews <> 0) {
			
			$res1 = $this->db->query('SELECT * FROM `'.$table.'` WHERE `idnews` = ^Ni;', $numnews);
			if($res1 !== null)$res1->date = $this->db->query('SELECT DATE_FORMAT(`date`,"%d %m %Y") FROM `'.$table.'` WHERE `idnews` = ^Ni;', $numnews);
			
			if($res1 === null) 
				//throw new StructureWException('numnews does\'t exist', StructureWException::ID_ERROR);
				return false;
			}
			//print_r($res1);
			$return['news'] = array();
			if($res1 !== null) {
			if(!is_array($res1)) {
				$return['news'][] = array('name' => $res1->name,'text' => $res1->newstext, 'date' => $res1->date, 'vendor' => $res1->vendor,
				'group' => $res1->group, 'imgnews' => $res1->imgnews,'idnews' => $res1->idnews,'hrefnew' => $res1->hrefnew);					
			} else {
				foreach($res1 as $val)
					$return['news'][] = array('name' => $val->name, 'idn' => $val->idnews,'text' => $val->newstext, 'date' => $val->date, 'vendor' => $val->vendor, 'hrefnew' => $val->hrefnew, 'group' => $val->group, 'imgnews' => $val->imgnews);		
			}
		return $return['news'];	
	}
		}
		else return null;
}		
			
public function getnews3($numnews) {
			$res1=array();
			if($numnews != 0) {
			$res1 = $this->db->query('SELECT * FROM `news` WHERE `idnews` = ^Ni;', $numnews);
			$res1->date = $this->db->query('SELECT DATE_FORMAT(`date`,"%d %m %Y") FROM `newsEES` WHERE `idnews` = ^Ni;', $numnews);
			if($res1 === null) 
				return false;
				//throw new StructureWException('numnews does\'t exist', StructureWException::ID_ERROR);	
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
				$res1 = $this->db->query('SELECT * FROM `news` WHERE `idnews` = ^Ni AND `group`=^Ns;', $numnews,$ng);
				$res1->date = $this->db->query('SELECT DATE_FORMAT(`date`,"%d %m %Y") FROM `news` WHERE `idnews` = ^Ni && `group`=^Ni;', $numnews,$ng);
			if($res1 === null) 
				throw new StructureWException('numnews does\'t exist', StructureWException::ID_ERROR);	
			}
			else{
				$res1 = $this->db->query('SELECT * FROM `news` WHERE  `group`=^Ns;', $ng);
				//$res1->date = $this->db->query('SELECT DATE_FORMAT(`date`,"%d %m %Y") FROM `news` WHERE `group`=^Ni;', $ng);
			}
			$return['news'] = array();
			if($res1 !== null) {
			if(!is_array($res1)) {
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
		return $return['news'];
			}	



public function gettextfile($File, $Cd){
$return=array();
$this->pathfile=$cd;
$this->file=$this->pathfile.$File;
$F=fopen($this->file,"r");// открываем и убеждаемся в наличии файла
if ($F) {
	$strtext=file_get_contents($this->file);
	//$strtext=fgetss($F, 100000);
	$return=explode('||',$strtext);
	$LF=strlen($strtext);
	foreach($return as $key=>$val){
		echo $key.'-------->'.$val.'<br>';
	}
	//echo $LF."-----".$strtext;
	}
echo '</td></tr><table>';	
return $return;	
}

public function ready_str_field($fields,$nb=0,$ne=0){
	$this->y='';
	if (is_array($fields)) {
	$NN=count($fields);
		for ($i=$nb;$i<$NN-$ne;$i++){
			if ($fields[$i]<>''){
			if ($i<$NN-1-$ne) $this->y.="`". $fields[$i]."`,";
			else $this->y.="`". $fields[$i]."`";
			}
		} 
	
}
return $this->y;	
}

public function getlookforalltab($for,$vend,$tab,$n1,$n2,$n3,$n4=0) {//n1 номер поля в котором индекса, n2 номер поля в котором ищем,n3 поле где ищем vend, n4 поле где ищем дополнительно
$ress=array();
$k=0;
$flds=$this->getallfieldtable($tab);
$fields=$flds['field'];
$fn1=$fields[$n1];
$fn2=$fields[$n2];
$fn3=$fields[$n3];
$fn4=$fields[$n4];
//show::infosh($fields);
$y=$this->ready_str_field($fields);
if(is_int($vend)) $ttt='i';
else $ttt='s';
if ($vend=='empty') $res=$this->db->query('SELECT '.$y.' FROM `'.$tab.'`;');
else $res=$this->db->query('SELECT * FROM '.$tab.' WHERE '.$fn3.'=^N'.$ttt.';',$vend);
//если запись существует, ищем в полях name art подстроку for
if (!$res == false){
//if($tab=='pages')show::infosh($res->buttons);
//print_r($res);
$return = array();
if(!is_array($res)) $ress[0]=$res;
else $ress=$res;
	foreach ($ress as $val){
	if ($val->$fn2<>'empty')$result=stristr($val->$fn2,$for);
	//if($result == false) show::infosh($for.' не найдено в '.$val->$fields[$n2]);
	//echo '<br>';
	if ($result == false ){
		//show::infosh('не найдено в позици '.$fields[1].' '.$val->id);;
		if ($val->$fn4<>'empty')  $result=stristr($val->$fn4,$for);
		if ($result == false){
		//echo 'не найдено в позици '.$fields[2].' '.$val->id;
		//show::infosh('Не найдено '.$return[$k][$fields[1]]);
		}
		else {
		//echo 'Найдено в позици '.$fields[2].' '.$val->id;
		if ($fields[$n1]<>'empty') $return[$k]=array($fields[$n4] => $val->$fn4, $fields[$n1] => $val->$fn1);
		else $return[$k]=array($fields[$n4] => $val->$fields[$n4]);
		//echo '<br>';
		//show::infosh('Найдено '.$return[$k][$fields[3]]);
		//echo '<br>';
		$k++; //если запись не найдена переходит к следующему номеру k+1 и повторяет поиск
		
		}
	}
	else {
		//show::infosh($for.' найдено в позици '.$fields[$n2].' '.$val->$fields[$n1]);
	// создаем элемент массива с индексом k, в который помещаем идентификационный номер записи и строку, в которой найден результат
	if($result){
	if ($fields[$n1]<>'empty')  $return[$k]=array($fields[$n2] => $val->$fn2, $fields[$n1] => $val->$fn1);
		else $return[$k]=array($fields[$n2] => $val->$fn2);
	}
	//echo '<br>';//отладка
	//echo $return[$k][$fields[$n1]].'    '.$return[$k][$fields[$n2]];
	//echo '<br>';
	$k++;//если запись не найдена переходит к следующему номеру k+1 и повторяет поиск
		
	}
	}

}

//return null;
// вывод результата поиска на экран
if (!isset($return)){
	//show::infosh('В '.$tab.' нет совпадений с Вашим запросом.'.$for);
	$return=false;
	}
else {
	$nn=count($return);
	}
//освобождаем память
unset($res);
unset($ret);
return $return;	//возвращает все идентификаторы найденных записей в виде массива	
	}	
	
public function  spec_array($arrayk){
	$zz=strlen($arrayk);
		switch ($zz){
			case 5:
			{
			$zn=1;
			break;
			}
			case 6:
			{
			$zn=2;
			break;
			}
			case 7:
			{
			$zn=1;
			break;
			}
			case 8:
			{
			$zn=2;
			break;
			}
		}
	$k0=substr($arrayk,1,$zn)*1;
	$k1=substr($arrayk,$zn+1,1)*1;
	$k2=substr($arrayk,$zn+2,1)*1;
	$k3=substr($arrayk,$zn+3,1)*1;
	$arrayk=array($k0,$k1,$k2,$k3);
	return $arrayk;
}	

public function read_namparams($table,$nmp,$field='',$typmen='',$sizeInput=20,$ta='global'){
	
	if($ta === 'global'){
		//echo '<info class="hidno">глобальные настройки параметров таблиц</info>';
		//$return=Utils::GlobalNamPar($table,$numpar,$field,$typmen,$sizeInput);
		$db = Singleton::getInstance('DB');	
		$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
		
	}
	else {
		$db = Singleton::getInstance('DB');	
		$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	}	
	//print_r($res2);//-------------
	
	if($res2 &&  $nmp !== 0  ){
			$arrnm=$res2->nampars;
			$arrtp=$res2->types;
			$arrdlm=$res2->delimiter;
			$arrname=explode('|',$arrnm);
			$arrtype=explode('|',$arrtp);
		foreach ($arrtype as $key=>$val) if (strstr($val,'type')) $arrtype[$key]=$sizeInput;
		if($arrdlm <> null) {
		$arrdelem=explode(',',$arrdlm);
		}
		else {
		for ($i=0;$i<count($arrtype);$i++)  {
			$arrdelem[$i][0]='|';
			$arrdelem[$i][1]=';';
			$arrdelem[$i]=$arrdelem[$i][0].$arrdelem[$i][1];
			}
		}	
	if($field<>''){
		$res1=$db->query('SELECT * FROM `'.$table.'` WHERE `'.$field.'`=^Ni;',$nmp);
		$l=0;
		foreach($res1 as $val){
		if($arrtype[$l] == 'check'  && $val=='') $array[$l]=$typmen;
		elseif($val == '') $array[$l]=$arrdelem[$l];
		else $array[$l]=$val;
		$l++;
		}
	}
	if(isset($array))$return=array($arrdelem,$arrname,$arrtype,$array);
	else return false;
}
else {
	$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$mass_zags=explode('|',$arrnm);
	$masszakls=explode('|',$arrtp);
	if($table !== 'setTypesPage'){
	foreach($masszakls as $val) {
		if($nmp<>0 ){
		if($val) $mass_zakls[]='?np='.$this->numpage.'&'.$val;
		else $mass_zakls[]=$val.'?np='.$this->numpage;
			}
		else $mass_zakls[]='?np='.$this->numpage.'&'.$val;
		}
	if($this->numpage<>0) {
		
			$mass_zakls[]='?np='.$this->numpage.'&'.'info';
			$mass_zags[]='Помощь';
		}
	}
	else $mass_zakls = $masszakls;
		
$return=array($mass_zags,$mass_zakls,$arrdlm);
}
return $return;
}

public function editabone($arr,$field1,$field2,$i,$numpage,$typemen,$tabl,$ida,$ids){
	$clas=$arr['clas'];
	if($field1=='numpage')	$table=$tabl['pages'];
	if($field1=='ids')$table='allsites';
	$arrfield=$this->getallfieldtable($table);
	$arrnampar=$this->read_namparams($table,$numpage,$field1,$typemen);
	$arrayk=$this->spec_array('a'.$arr[$field2]['link'][$i].'00');
	//print_r($arrayk);
	echo '<div>';
	$this->editpartsBD($arrnampar[1], $arrnampar[2], $arrnampar[3],$arrnampar[0],$arrayk,$clas,$tabl,$arrfield['field'],$ida,$ids,'#');	
	echo '</div>';
}

public function editaball($arr,$field1,$field2,$numpage,$typemen,$tabl,$ida,$ids){
	$clas=$arr['clas'];
	if($field1=='numpage')	$table=$tabl['pages'];
	if($field1=='ids')$table='allsites';
	if($field1=='id')$table='maket';
	$arrfield=$this->getallfieldtable($table);
	//print_r($arrfield);echo '<br>';
	$arrnampar=$this->read_namparams($table,$numpage,$field1,$typemen);
	echo '<div style="display:flex; flex-wrap: wrap;flex-basis:40%;justify-content: space-around; flex-direction: column; padding:0 20px;">';
	if(is_array($arr['link'][$field2])){
	foreach($arr['link'][$field2] as $key=>$val){
		//echo 'a'.$arr[$field2]['link'][$key].'00<br>';
		//echo 'a'.$val.'00<br>';
		$arrayk[]=$this->spec_array('a'.$val.'00');
		//print_r($arrayk);echo '<br>';
		echo '<div>';
		$this->editpartsDBD($arrnampar[1], $arrnampar[2], $arrnampar[3],$arrnampar[0],$arrayk,0,$clas,$tabl,$arrfield['field'],$ida,$ids,30,4);
		echo '</div>';
	}
	}
	else {
		$arrayk[]=$this->spec_array('a'.$arr['link'][$field2].'00');
		echo '<div>';
		$this->editpartsBD($arrnampar[1], $arrnampar[2], $arrnampar[3],$arrnampar[0],$arrayk,$clas,$tabl,$arrfield['field'],$ida,$ids,30,4);
		echo '</div>';
	}
	echo '</div>';
	if(is_array($arr['link'][$field2.'href'])){
		echo '<div style="display:flex; flex-wrap: wrap;flex-basis:40%;justify-content: space-around; flex-direction: column;">';
		foreach($arr['link'][$field2.'href'] as $key=>$val){
		//echo 'a'.$val.'00<br>';
		$arrayk1[]=$this->spec_array('a'.$val.'00');
		//print_r($arrayk1);echo '<br>';
		$this->editpartsDBD($arrnampar[1], $arrnampar[2], $arrnampar[3],$arrnampar[0],$arrayk1,1,$clas,$tabl,$arrfield['field'],$ida,$ids,30,4);
		//echo '</div>';
		}
	echo '</div>';	
	}
}

public function view_table($a,$b='',$c='',$d='',$e=''){
		if ($a<>'' && $b=='')$g=$this->db->query("select * from `$a`");
		elseif($d<>'' && $e<>'')$g=$this->db->query("select * from `$a` where `$b` = '$c' AND `$d`='$e';");
		else $g=$this->db->query("select * from `$a` where `$b` = '$c';");
	return $g;
	}

public function calculate_tarif($owner){
	if(isset($owner))$tarif=100;
	return $tarif;
	
}

public function ispublpages($uid,$domen,$tabl){
	$res=$this->db->query('SELECT `codeGJS` FROM `'.$tabl['elemap'].'` WHERE `domen`=^Ns AND `idauthor`=^Ni',$domen,$uid);
	if($res){
		if(is_array($res))foreach($res as $val)$result[]=array(0=>$val->codeGJS);
		else $result[0]=$res->codeGJS;
		$resu=false;
		foreach($result as $val){
			if($this->ispublicpage($val)<>'public'){$resu=true;continue;}
			else {$resu=false;break;}
		}
	}
		else $resu=false;
	return $resu;
}

public function ispublicpage($np){
	
	$res=$this->db->query('SELECT `date1`,`codeGJS` FROM `elemap` WHERE `codeGJS`=^Ni;',$np);
	$ts=date('U');
	$now=getdate($ts);
	//print_r($res);
	$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
	if($res){
		$result=$res->date1;
		if($result==='0000-00-00') return 'unpublic';
		elseif($result > $tt)return 'delayed';
		elseif($result <= $tt)return 'public';
	}
	else return 'absent';
}

public function unpublic($np,$tabl,$domen,$uid){
	$res=$this->db->query('UPDATE `'.$tabl.'`  SET `date1`=^Ns WHERE `codeGJS`=^Ni AND `domen`=^Ns AND `idauthor`=^Ni','0000-00-00',$np,$domen,$uid);
	if($res) return true;
	else return false;
}
 
function part_name($str){
	if(strstr($str,'=')) $res=explode('=',$str);
	else $res[0]=$str;
	return $res[0];
}

public function pagemaket($np,$uid,$domen,$tabl){
	$res=$this->db->query('SELECT `idmenu`,`numpage` FROM `'.$tabl['pages'].'` WHERE `numpage`=^Ni AND `site`=^Ns AND `idauthor`=^Ni',$np,$domen,$uid);
	$numpag=array(0=>$res->numpage);
	//echo $numpag.'<br>';
	//print_r($res);
	$name_maket=array(0=>$res->idmenu,1=>$res->numpage);
	$namemaket=$name_maket[0].'-'.$name_maket[1];
	//var_dump($namemaket);
	$res0=$this->db->query('SELECT `id` FROM `allmakets` WHERE `author_mak`=^Ni AND `Maket`=^Ns;',$uid,$namemaket);
	print_r($res0);
	return $res0;
}

public function allpublpage($ew,$tabl,$domen,$uid,$owner){
	$ts=date('U');
	$now=getdate($ts);
	$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
	$res=$this->db->query('SELECT `codeGJS` FROM `'.$tabl['elemap'].'` WHERE `domen`=^Ns AND `idauthor`=^Ni',$domen,$uid);
	if(is_array($res))foreach($res as $val)$result[]=array(0=>$val->codeGJS);
	else $result[0]=$res->codeGJS;
	if($res){
		foreach ($result as $val)
			$return=$this->db->query('UPDATE `'.$tabl['elemap'].'`  SET `date1`=^Ns WHERE `codeGJS`=^Ni AND `domen`=^Ns AND `idauthor`=^Ni',$tt,$val[0],$domen,$uid);
	//show::pauza();
	}
	else {
		$res=$this->db->query('SELECT `idmenu`,`numpage` FROM `'.$tabl['pages'].'` WHERE `site`=^Ns AND `idauthor`=^Ni',$domen,$uid);
		foreach($res as $val){
		$arrpag=array(0=>$val->idmenu,1=>$val->numpage);	
		$name_maket=$arrpag[0].'-'.$arrpag[1];	
		//echo $name_maket;
		$res0=$this->db->query('SELECT `id` FROM `allmakets` WHERE `author_mak`=^Ni AND `Maket`=^Ns;',$arrpag[1],$name_maket);
		//echo $this->pagemaket($arrpag[1],$uid,$domen,$tabl);
		//if($res0)var_dump($res0);
		//else 'no';
		$return=$this->publpage($ew,$val->numpage,$tabl,$owner,$res0);
		}
	}
	if($return) return true;
	else return false;
}

public function publpage($ew,$np,$tabl,$owner,$idm,$delay=0,$mfl=0,$lfl=0){
		//$ew=Singleton::getInstance('ElementsW');
		//$arr=$sw->getPage($np);
		$Page= new Page($np,$tabl);
		$ts=date('U')+ $delay;
		$now=getdate($ts);
		$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
		$lpg=User::getscountab('elemap','id', 'f');
		$array=array();
		$arr=$Page->MainAr;
		//print_r($arr);
		$FT=explode(';',$arr['keywords']);
		$array[0]=$arr['numpage'];
		$array[1]=$np;
		$FN=explode('|',$arr['namep']);
		$array[2]=$Page->getnamepage($Page);
		$array[3]=$FN[0].'>|<'.$FN[1].'>|<'.$arr['lozung'].'>|<'.$arr['buttons'].'>|<'.$arr['content'].'>|<'.$arr['list'].'>|<'.$arr['hreflist'].'>|<'.$arr['butthref'].'>|<'.$arr['imgtext'].'>|<'.$arr['buttimg'].'>|<'.$arr['hrefimage'].'>|<'.$arr['idmenu'].'>|<'.$arr['typemenu'].'>|<'.$arr['levelmenu'].'>|<'.$arr['hrefscripts'].'>|<'.$arr['hrefstyle'].'>|<'.$arr['title'].'>|<'.$arr['hrefp'].'>|<'.$FN[3].'>|<'.$FN[4];
		$as=explode('|',$arr['buttons']);
		$array[4]=$as[1];
		$array[5]=$arr['keywords'];//$FT[0].'>|<'.$FT[1].'>|<'.$FT[2];
		$array[6]=$this->calculate_tarif($owner);
		$array[7]=$mfl;
		$array[8]=$lfl;
		$array[9]=$arr['idnews'];
		$array[10]=$tt;
		$array[11]=$idm;
		$array[12]=$arr['site'];
		$array[13]=$arr['idauthor'];
		$array[14]=$arr['configpage'];
		//print_r($array[5]);
		if($this->view_table('elemap','codeGJS',$np,'domen',$array[12])){
			$res=$this->db->query('UPDATE `elemap`  SET `id`=^Ni,`codeGJS`=^Ni,`name`=^Ns,`desc`=^Ns,`keywords`=^Ns,`titles`=^Ns,`price`=^Ni,`ms`=^Ni,`ls`=^Ni,`links`=^Ni,`date1`=^Ns,`idm`=^Ni,`domen`=^Ns,`idauthor`=^Ni, `configpage`=^Ns WHERE `codeGJS`=^Ni;',
			$array[0],$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],$array[10],$array[11],$array[12],$array[13],$array[14],$array[1]);
		}
		else {
			//$array[0]=$lpg+1;
			$res=$ew->GeneraladdElement($tabl,$array,$array[4],0,0);
		}
		//Utils::generalcalcNumEl( 0,'mapsites','type-elemap');
		if($res)return true;
		else return false;
	}

public function publpagenew($ew,$np,$tabl,$owner,$idm,$delay=0,$mfl=0,$lfl=0){
		//$ew=Singleton::getInstance('ElementsW');
		//$arr=$sw->getPage($np);
		$Page= new Page($np,$tabl);
		$ts=date('U')+ $delay;
		$now=getdate($ts);
		$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
		$lpg=User::getscountab('elemap','id', 'f');
		$array=array();
		$arr=$Page->MainAr;
		//print_r($arr);
		$FT=explode(';',$arr['keywords']);
		$array[0]=$arr['numpage'];
		$array[1]=$np;
		$FN=explode('|',$arr['namep']);
		if(!isset($FN[3])) $FN[3]='';
		if(!isset($FN[4])) $FN[4]='';
		$array[2]=$Page->getnamepage($Page);
		$array[3]=$FN[0].'>|<'.$FN[1].'>|<'.$arr['lozung'].'>|<'.$arr['buttons'].'>|<'.$arr['content'].'>|<'.$arr['list'].'>|<'.$arr['hreflist'].'>|<'.$arr['butthref'].'>|<'.$arr['imgtext'].'>|<'.$arr['buttimg'].'>|<'.$arr['hrefimage'].'>|<'.$arr['idmenu'].'>|<'.$arr['typemenu'].'>|<'.$arr['levelmenu'].'>|<'.$arr['hrefscripts'].'>|<'.$arr['hrefstyle'].'>|<'.$arr['title'].'>|<'.$arr['hrefp'].'>|<'.$FN[3].'>|<'.$FN[4];
		$as=explode('|',$arr['buttons']);
		$array[4]=$as[1];
		$array[5]=$arr['keywords'];//$FT[0].'>|<'.$FT[1].'>|<'.$FT[2];
		$array[6]=$this->calculate_tarif($owner);
		$array[7]=$mfl;
		$array[8]=$lfl;
		$array[9]=$arr['idnews'];
		$array[10]=$tt;
		$array[11]=$idm;
		$array[12]=$arr['site'];
		$array[13]=$arr['idauthor'];
		//$array[14]=$arr['hrefp'];
		//print_r($array[5]);
		if($this->view_table('elemap','codeGJS',$np,'domen',$array[12])){
			$res=$this->db->query('UPDATE `elemap`  SET `id`=^Ni,`codeGJS`=^Ni,`name`=^Ns,`desc`=^Ns,`keywords`=^Ns,`titles`=^Ns,`price`=^Ni,`ms`=^Ni,`ls`=^Ni,`links`=^Ni,`date1`=^Ns,`idm`=^Ni,`domen`=^Ns,`idauthor`=^Ni WHERE `codeGJS`=^Ni;',
			$array[0],$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],$array[10],$array[11],$array[12],$array[13],$array[1]);
		}
		else {
			//$array[0]=$lpg+1;
			$res=$ew->GeneraladdElement($tabl,$array,$array[4],0,0);
		}
		//Utils::generalcalcNumEl( 0,'mapsites','type-elemap');
		if($res)return true;
		else return false;
	}
	
function showloadfiles($numpage='',$href='',$clas=''){
	if(isset($_FILES)){
		if($clas==='')$clas=array('csv'=>'./','img'=>'./images/','css'=>'./css/','js'=>'./js/','lib'=>'./libs/');
		//print_r($_FILES);
		//print_r($clas);
		//print_r($_POST);
		if($numpage != '' && $href != '')$href='./?'.$href.'&np='.$numpage;
		elseif($href == '' && $numpage != '' )$href='./?np='.$numpage;
		else $href='';
		
		foreach($_FILES as $key=>$val){	
			if(isset($_FILES[$key]) && isset($_POST[$key.'1'])){
				if($val['error']==0 && $val['size']<>0) {
					$load_pic=$this->all_files_load($key,$key.'1',$_FILES,$clas,$this->type_files_load($_FILES,$key,$clas,$_POST[$key.'1']));
					if($load_pic)show::pauza('Загрузка файла '.$val['name'].' завершена успешно',$href);
					else show::pauza('Не удалось осуществить сохранение файла'.$val['name'],$href);
				}	
			}
		}
		}	
}
}		
?>