<?php
ini_set('display_errors',0);
error_reporting(E_ALL);
define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']).'/');
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));

	$pathToClasses = '/classes/';
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	include($pathheader.$pathToClasses.'autoload.inc');
	
	
	
require (HOST_ROOT.'book_sc_fns.php');
$el = Singleton::getInstance('ElementsW');
  // Для покупательской тележки необходимо запустить сеанс
  session_start();
	$user = Singleton::getInstance('User');
	$uid=$user->check();
	$cid=$user->getusercid();
  @ $new = $_GET['new'];
	$nman=1;
  if($new)
  {
    // Выбран новый элемент
    if(!isset($_SESSION['cart']))
    {
      $_SESSION['cart'] = array();
      $_SESSION['items'] = 0;
      $_SESSION['total_price'] ='0.00';
    }
    if(isset($_SESSION['cart'][$new]))
      $_SESSION['cart'][$new]++;
    else 
      $_SESSION['cart'][$new] = 1;
    $_SESSION['total_price'] = calculate_price($_SESSION['cart']);
    $_SESSION['items'] = calculate_items($_SESSION['cart']);

  }
 //echo $new.'- ---'.$_SESSION['total_price'];

  if(isset($_POST['save']))
  {   
    foreach ($_SESSION['cart'] as $isbn => $qty)
    {
      if($_POST[$isbn]=='0')
        unset($_SESSION['cart'][$isbn]);
      else 
        $_SESSION['cart'][$isbn] = $_POST[$isbn];
    }
    $_SESSION['total_price'] = calculate_price($_SESSION['cart']);
    $_SESSION['items'] = calculate_items($_SESSION['cart']);
  }

?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<?php
		//$PageM= new Page(1);
		echo '<head>';
		echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
		if ($user->isGuest()) echo '<meta http-equiv="refresh" content="0; url=/registration">';
		echo '<title>newcart</title>';
		echo '<link rel="stylesheet" type="text/css" href="../images/style.css" />';
		?>
		<SCRIPT LANGUAGE="JavaScript">

function new_window(path_H,name_W,contr_Br)
{
window.open(path_H,name_W, contr_Br);
}
//
</SCRIPT> 
<?php
		echo '</head><body>';
		if(!$_SESSION['items']) $_SESSION['items'] = '0';
		if(!$_SESSION['total_price']) $_SESSION['total_price'] = '0.00';
		//верхний колонтитул лозунг
		//$L=array();
		//$L=explode('|',$PageM->MainAr['lozung']);
		//$list['7']=explode(',',$L[0]);//массив лозунгов страницы
				//echo '<div class="head">'.$list[7][0].'</div>';
				//область информации о пользователе и состоянии его корзины-->
					echo '<div class="user">';
					$user = Singleton::getInstance('User');
					$uid=$user->check();
					$cid=$user->getusercid();
					//echo 'cid='.$cid;
					$user->stringusermen('user');
					//echo ' Сегодня: '.date("d m Y").' |'.'<span>Логин:'.$user->getLogin().'</span>';
					echo '|Общая сумма = ($)'.number_format($_SESSION['total_price'],2);
				    echo '|Зарезервировано товаров- '.number_format($_SESSION['items'],0);
					if($cid == null) echo '|<a href="../?editp=ok&cust='.$cid.'"> Регистрация юридического лица </a>';
					elseif (!$cid==0) echo '|Заказчик:'.$user->idUserF($uid)->name;
					if(!$user->isGuest()) {
							if ($user->getLevel()>3) echo '|<a href="/settings/">Настройки</a>';
						}
						echo '|<a href="/auth/?logout">Выйти</a>';
						
					echo '</div>';
include($pathheader.$pathToClasses.'Cart.inc');
echo '<div class="head">Комментарий (из руководства пользователя )</div>';
Page::display_manual($nman);
Page::display_manual(-1);
do_html_footer();
?>
