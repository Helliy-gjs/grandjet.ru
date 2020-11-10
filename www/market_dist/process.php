<?php
  
  // Включить наш набор функций
  define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']).'/');
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));
/*echo 'HOST_ROOT-'.HOST_ROOT;echo "<BR>";
echo 'HTTP_FOLDER-'.HTTP_FOLDER;echo "<BR>";
echo 'SYS_HTTP-'.SYS_HTTP;echo "<BR>";
echo '_SERVER["DOCUMENT_ROOT"]-'.$_SERVER["DOCUMENT_ROOT"];echo "<BR>";*/
  //require ('book_sc_fns.php');
 		
//echo 'Работа с удаленным сервером';echo "<BR>";
	$pathToClasses = '/classes/';
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	include($pathheader.$pathToClasses.'autoload.inc');
	
	
require (HOST_ROOT.'book_sc_fns.php');
  //require ('book_sc_fns.php');
  // Для покупательской тележки необходимо запустить сеанс
  session_start();
  //$PageM= new Page(1);
		echo '<head>';
		echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
		//echo '<title>'.$PageM->MainAr['title'].'</title>';
		echo '<link rel="stylesheet" type="text/css" href="../images/style.css" /></head><body>';
		if(!$_SESSION['items']) $_SESSION['items'] = '0';
		if(!$_SESSION['total_price']) $_SESSION['total_price'] = '0.00';
		//верхний колонтитул лозунг
		$user = Singleton::getInstance('User');	
		$user->check();
		$uid=$user->getuserid();
		$cid=$user->getusercid();
		echo '<div class="head">'.'Окончательный расчет'.'</div>';
		//область информации о пользователе и состоянии его корзины-->
		echo '<div class="user">';
		$user->stringusermen('user','');
					/*echo '|<a href="../new.php?np=97">Каталог товаров</a>';	
					echo '|<a href="../index.php?np=1">На стартовую</a>';
					$user = Singleton::getInstance('User');
					if ($user->getLevel()>3) echo '|<a href="../settings/">Настройки</a>';
					echo '|<a href="/auth/?logout">Выйти</a>';*/
					
					echo $num_page.' Сегодня: '.date("d m Y").' |'.'<span>'.$user->getLogin().'</span>';
					if (!$cid==0) echo '|Заказчик:'.$user->idCust($cid)->name;
					
  
  
  // Создать короткие имена переменных
  $rs_num = $_POST['rs'];
  $bank_name = $_POST['cbank'];
  $person = $_POST['fio'];
  $telphone = $_POST['tels'];
  $email = $_POST['email'];
/*while ($element = each($_POST))
  {
  echo "ключ ".$element['key'];
  echo '-';
  echo "значение ".$element['value'];
  echo '<br/>';
  }*/
  if($_SESSION['cart'] && $person && $telphone && $email )
  {
  $a=0;
	foreach ($_SESSION['cart'] as $key=>$val) $a=+$key*$val;
	// Вывести тележку без изображений товара и не разрешая изменения
    display_cart($_SESSION['cart'], false, 0);
	
    display_shipping(calculate_shipping_cost($a));  

    if(process_card($_POST))
    {
      // добавить сеанс в бд пользователя
	  
	  //ElementsW::addseansuser($uid,$_SESSION['stat']);
	  // Очистить покупательскую тележку
	  session_destroy();
      echo 'Спасибо за то, что воспользовались нашим сайтом для совершения 
        покупок.  Ваш заказ размещен.';
      display_button('../', 'continue-shopping', 'Продолжить покупки');  
    }
    else
    {
    echo 'Невозможно обработать вашу кредитную карточку.';
    echo 'Пожалуйста, свяжитесь с выдавшей ее организацией либо 
          повторите ввод.';
      display_button('purchase.php', 'back', 'Назад');
    }
  }
  else
  {
    echo 'Вы заполнили не все поля. Пожалуйста, повторите попытку.<hr />';
    display_button('purchase.php', 'back', 'Назад');
  } 
 
  do_html_footer();
?>