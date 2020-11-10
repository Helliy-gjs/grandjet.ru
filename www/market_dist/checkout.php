<?php
ini_set('display_errors',0);
error_reporting(E_ALL);
global $pathToClasses;
define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']).'/');
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));
/*echo 'HOST_ROOT-'.HOST_ROOT;echo "<BR>";
echo 'HTTP_FOLDER-'.HTTP_FOLDER;echo "<BR>";
echo 'SYS_HTTP-'.SYS_HTTP;echo "<BR>";
echo '_SERVER["DOCUMENT_ROOT"]-'.$_SERVER["DOCUMENT_ROOT"];echo "<BR>";*/
	
//echo 'Работа с удаленным сервером';echo "<BR>";
	$pathToClasses = '/classes/';
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	include($pathheader.$pathToClasses.'autoload.inc');
	
//echo HOST_ROOT.'book_sc_fns.php';
  require (HOST_ROOT.'book_sc_fns.php');
 @ $par=$_GET['par'];
$user = Singleton::getInstance('User');
$user = Singleton::getInstance('User');
$user->check();
$uid=$user->getuserid();
$cid=$user->getusercid();
$user->stringusermen('user');
/*if($user->getLevel() > 0) {
	echo '<span>';
	echo ' Сегодня: '.date("d m Y").' '.'|Логин:';
	echo '-'.$user->getLogin().'</span>';
	if (!$cid==0) echo '|Заказчик:'.$user->idUser($uid)->name;
	}*/
  // Для покупательской тележки необходимо запустить сеанс
  session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<?php
		//$PageM= new Page(1);
		echo '<head>';
		echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
		if (!$user->check_firm($uid))	echo '<meta http-equiv="refresh" content="0; url=../?editp=ok&cust='.$cid.'">';
		//echo '<title>'.$PageM->MainAr['title'].'</title>';
		echo '<link rel="stylesheet" type="text/css" href="../images/style.css"/></head><body>';
  //do_html_header('Ваша тележка');
  //область информации о пользователе и состоянии его корзины-->
					echo '<div class="user">';
						
						
						
 // do_html_header('Окончательный расчет');
  //@ $cid=$_GET['cid'];
  if($_SESSION['cart']&&array_count_values($_SESSION['cart']))
  {
	display_cart($_SESSION['cart'], false, 0);
 ?><table border = 0 width = '100%' cellspacing = 0><tr><td>
 
<?php
//echo $uid;
 if ($user->isExistCust($uid)) { 
		//$user->CustExist ($uid);
		$find=$user->idUserF($uid);
		//print_r($find);
	if ($par == 'b') display_find_form($find);
	if ($par == 's') {
	$order_detail=array('name'=>$find->name, 'address'=>$find->address,'city'=>$find->city,'tels'=>$find->tels,'em'=>$find->email,'cfio'=>$find->cfio,'cusid'=>$find->customerid);
		//print_r($order_detail);//$order_detail['ship_name']=$word[0].'"'.$order_detail['ship_name'].'"'.$word[2];
	echo '<form action="purchase.php" method="post"> ';
	//echo $order_detail['ship_name'];
	if($user->getLevel() > 2) echo '<input  name="choice"  value="1" type="radio"  />Сохранить заказ ';
	echo '<input  name="choice" value="2" type="radio" checked="checked" />Уточнение цен и сроков поставки товаров';
	if ($_SESSION['total_price']>0) echo '<input  name="choice" value="3" type="radio"  />Резервирование товаров на складе и транзите';
	//echo '<input  name="choice" value="4" type="radio"  />Сохранить товар в списке предпочтений';
	echo '<input type="hidden" name="store" value="true" /><br>';
	foreach ($order_detail as $key=>$val){
		echo "<input type='hidden' name='".$key."' value='".$val."'/>";
			}
	echo '<input type="image" src="../images/butt.jpg"  border="0" alt="Отправить запрос">';
	//display_hidden_form($order_detail);
	echo '</form>';
		}
		}
	else {
    			echo '------------';
				display_checkout_form();
		}
	
 }
  else     echo '<p>Ваша тележка пуста</p>';
 //display_form_button('../images/contin.jpg', 'Продолжить покупки');
  display_button('../', 'images/butt.jpg', 'Продолжить покупки');  

  do_html_footer();
?>