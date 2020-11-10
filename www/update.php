 <?php
if(isset($_GET['update'])){$update=true;$upgrade=false;} 
elseif(isset($_GET['recover']))  {$update=false;$upgrade=false;}
elseif (isset($_GET['upgrade'])) {$update=false;$upgrade=true;}
if(isset($update)){
	$inf='';
	
	if($update) {
		//show::infosh('имется обновление '.$_SERVER['HTTP_HOST'].' в '.HOST_DIST.'<br>',$inf);
		if($_GET['update']=='')$user->updatesite(HOST_ROOT,$update,HOST_DIST);
		else {
			$downloadfile=$_GET['update'];
			$user->updatfile(HOST_ROOT,$downloadfile,HOST_DIST);
			echo 'Обновление файлов '.$_GET['update'].'<br>';
		}
		}
	elseif($upgrade){
		if($_GET['upgrade']=='')$user->updatesite(HOST_ROOT,$upgrade,HOST_DIST);
	}	
	else {
		$recoverfile=$_GET['recover'];
		show::infosh('восстановление сайта из архива');
		$user->recoversite($_SERVER['HTTP_HOST'],$recoverfile);
	}
	//echo '<a href="/?guest" >Обновление выполенено</a>  ';
	header('Location: https://'.$_SERVER['HTTP_HOST']);
}	
?>