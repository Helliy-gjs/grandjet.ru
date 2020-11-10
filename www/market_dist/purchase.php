<?php
ini_set('display_errors',0);
error_reporting(E_ALL);
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
				echo '<div class="head">'.'Заказы и резервы'.'</div>';
				//область информации о пользователе и состоянии его корзины-->
					echo '<div class="user">';
				
					$user = Singleton::getInstance('User');
					$user->check();
					$uid=$user->getuserid();
					$cid=$user->getusercid();
					$user->stringusermen('user');
					/*if(!$user->isGuest()) {
							$user->stringusermen('user',$Pth);
							if ($user->getLevel()>3) echo '|<a href="../settings/">Настройки</a>';
							echo '|<a href="../auth/?logout">Выйти</a>';
						}
					echo ' Сегодня: '.date("d m Y").' |'.'Логин:<span>'.$user->getLogin().'</span>';*/
					if (!$cid==0) echo '|Заказчик:'.$user->idUserF($uid)->name;
					
  
  

  //do_html_header("Окончательный расчет");
   if(isset($_POST['store'])&&($user->getLevel()>2)) {
	 extract($_POST);
	 if($_SESSION['cart']&& $choice)
    {
	//echo " форма заполнена верно";
    // Можно ли вставлять в базу данных?
echo '<br>';
switch ($choice) {
	case 1:	{
			 $orderid=insert_find($_POST, $choice);
			//echo $orderid.'<br>';
			if (!$orderid==false )	echo 'Заказ  сохранен для работы с ним в личном кабинете.';
			else echo 'Заказ не сохранены ';
			//echo 'Сохранение предпочтений';
			 //$user->view_orderid($orderid);
			break;
			
	}
	case 2:	{
			echo 'Уточнение сроков поставки';
			if( insert_find($_POST, $choice)!=false )	{
			echo 'Заказ  сохранен для работы с ним в личном кабинете.<br>';
			echo 'Справку о доступности для заказа выбранных товаров Вы получите  по электронной почте в ближайщее время';
													
			}
			else echo 'Информация не отправлена. Повторите Ваш запрос. ';
			break;

	}
	case 3:	{
			echo 'Резервирование товара';
			if( insert_find($_POST, $choice)!=false ) {
		echo 'Заказ  сохранендля работы с ним в личном кабинете.<br>';
		echo 'Подтверждение о резервировании товаров Вы получите по электронной почте';
			}
			else echo 'Информация не отправлена. Повторите Ваш запрос. ';
			break;
	}
	case 4:	{
			 $orderid=insert_find($_POST, $choice);
			echo $orderid.'<br>';
			if (!$orderid==false )	echo 'Товары сохранены в Вашем личном списке предпочтений';
			else echo 'Заказ не сохранены ';
			echo 'Сохранение предпочтений';
			 break;
	}
}

}
// $user->view_orders_cust($cid);
}
else {
	//print_r($_POST);
  // Создать короткие имена переменных
  	$name = $_POST['name'];
  	$address = $_POST['address'];
  	$city = $_POST['city'];
  	$tels = $_POST['tels'];
  	$em = $_POST['em'];
  	$cfio = $_POST['cfio'];
	$customerid=$_POST['cusid'];
/*while ($elem = each ($_POST))
{
echo $elem['key'];
echo " - ";
echo $elem['value'];
echo '<br/>';
}*/
    // Если форма заполнена
  if($_SESSION['cart']&&$name&&$address&&$city&&$tels&&$em&&$cfio)
    {
	echo " форма заполнена верно";
    // Можно ли вставлять в базу данных?
    if( insert_order($_POST)!=false )
	    {
		$a=0;
      // Вывести тележку без изображений товаров и не разрешая изменения
      $a=display_cart($_SESSION['cart'], false, 0);
		
      display_shipping(calculate_shipping_cost($a));  

      // Получить информацию по кредитной карточке
     // display_rs_form($cid);

 // Выводит форму, запрашивающую сведения о платильщике
 if ($user->check_firm($uid)) {
  echo '<table border = 0 width = "100%" cellspacing = 0>';
  echo '<form action = "process.php" method = "post"><tr><th colspan = 2 bgcolor="#cccccc">Сведения о платильщике</th></tr>';
  echo '<tr><td>ИНН  '.$user->idUserF($uid)->cinn.'</td></tr>';
   echo '<tr><td>КПП  '.$user->idUserF($uid)->ckpp.'</td></tr>';
   echo '<tr><td>Наименование организации  '.$user->idUserF($uid)->name.'</td></tr>';
   echo '<tr><td>Юридический адрес:  '.$user->idUserF($uid)->uradr.'</td></tr>';
 
if ($user->idUserF($uid)->crs <> ''){
	echo '<tr><th colspan = 2 bgcolor="#cccccc">Сведения о банковских реквизитах</th></tr>';
    echo '<tr><td>Расчетный счет  '.$user->idUserF($uid)->crs.'</td></tr>';
    echo '<tr><td>Наименование банка  '.$user->idUserF($uid)->cbank.'</td></tr>';
    echo '<tr><td>Корреспондетский счет  '.$user->idUserF($uid)->cks.'</td></tr>';
    echo '<tr><td>БИК  '.$user->idUserF($uid)->cbik.'</td></tr>';
	}
else '<tr><td>в системе нет данных о счетах '.$user->idUserF($uid)->name.'</td></tr>';
	echo '<tr><th colspan = 2 bgcolor="#cccccc">Контактные данные</th></tr>';
  
    echo '<tr><td>ФИО контактного лица  '.$user->idUserF($uid)->cfio.'<input type="text"  name="fio" value="'.$user->idUserF($uid)->cfio.'"/>необходимо заполнить</td></tr>';
    echo '<tr><td>Телефон '.$user->idUserF($uid)->tels.'<input type="text"  name="tels" value="'.$user->idUserF($uid)->tels.'"/>необходимо заполнить</td></tr>';
    echo '<tr><td>Электронная почта '.$user->idUserF($uid)->email.'<input type="text"  name="email" value="'.$user->idUserF($uid)->email.'"/>необходимо заполнить</td></tr>';
    echo '<tr><td>icq  '.$user->idUserF($uid)->icq.'<input type="text"  name="icq" value="'.$user->idUserF($uid)->icq.'"/></td></tr>';
  
   
   ?><td colspan = 2 align = 'center'>
      <b>Пожалуйста, щелкните на кнопке "Отправить запрос" для того, чтобы подтвердить покупку,
         либо на кнопке "Продолжить покупки" для продолжения покупок.</b> 
     <?php 
	 display_form_button('../images/order.jpg', 'Завершить '); 
	 //display_button('purchase.php', '../images/butnoch', 'Завершить');
	 ?>
    </td><?php
	echo '</form>';
	
   }
else  {
	echo 'При регистрации представлены не все данные необходимые для оформления счетов <br>';
	display_button('../?editp=ok&cust='.$cid, 'registration', 'Регистрация юридического лица (завершение)');   
	
}
    display_button('../', 'continue-shopping', 'Продолжить покупки'); 
	
	  
    }
    else
    {
      echo 'Невозможно сохранить данные. Пожалуйста, повторите попытку позже.';
      //display_button('checkout.php', 'back', 'Назад');
    }
  }
  else {
  
  echo 'Вы заполнили не все поля. Пожалуйста, повторите попытку.<hr />';
    //display_button('checkout.php', 'back', 'Назад');
	}
	}
  do_html_footer();
?>