<?php
global $pathToClasses, $pathheader;
define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']).'/');
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));
echo '_SERVER["DOCUMENT_ROOT"]-'.$_SERVER["DOCUMENT_ROOT"];echo "<BR>";
if (strstr(SYS_HTTP,'localhost')) {
	$pathToClasses ='Z:/home/localhost/www/CorpaZona/classes/';
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	//fclose($F);
	include_once(trim($pathToClasses).'autoload.inc');
		}
else {		
	$pathToClasses = '/classes/';
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	include($pathheader.$pathToClasses.'autoload.inc');
	session_start();
	}
require ('book_sc_fns.php');
// Для покупательской тележки необходимо запустить сеанс
  

  @ $new = $_GET['new'];

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
$PageM= new Page(1);
		
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<?php
		echo '<head>';
		echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
		echo '<title>CartGJS</title>';
		echo '<link rel="stylesheet" type="text/css" href=".'.$PageM->MainAr['hrefstyle'].'" />';
	//область информации о пользователе и состоянии его корзины-->
					echo '<div class="user">';
						if(strstr($pathToClasses,'localhost')){
						echo '<span>';
						echo $num_page.' Сегодня: '.date("d m Y").' '.'|Пользователь';
						}
						else {
						echo '<span>'.$user->getLogin().'</span>';
						}
 
  if($_SESSION['cart']&&array_count_values($_SESSION['cart']))
    display_cart($_SESSION['cart']);
  else
  {
    echo '<p>Ваша тележка пуста</p>';
    echo '<hr />';
  }
  $target = '../index.php';

  // Если в тележку был только что добавлен новый элемент,
  // продолжить покупки товаров данной категории
  if($new)
  {
    $details =  get_book_details($new);
    if($details['catid'])    
      $target = 'show_cat.php?catid='.$details['catid']; 
  }
  //display_button($target, 'continue-shopping', 'Продолжить покупки');  

  // Используйте это, только если настроено SSL-соединение
  // $path = $_SERVER['PHP_SELF'];
  // $server = $_SERVER['SERVER_NAME'];
  // $path = str_replace('show_cart.php', '', $path);
  // display_button('https://'.$server.$path.'checkout.php', 
  //                'go-to-checkout', 'Окончательный расчет');  

  // Используйте это, если SSL-соединение не установлено
  display_button('checkout.php', 'go-to-checkout', 'Окончательный расчет');  

  do_html_footer();	
?>		