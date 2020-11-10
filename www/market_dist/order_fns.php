<?php
function process_card($card_details)
{
  // Подключается к платежному шлюзу, либо
  // с использованием gpg шифрует и отправляет информацию, либо
  // сохраняет информацию в базе данных, если это настоятельно необходимо

  return true;
}

function sendemail($order_details,$choice,$orderid){
extract($order_details);
$date = date('Y-m-d');
$el = Singleton::getInstance('ElementsW');
switch( $choice ) {
 case 0: { 
	$condition = 'ORDER';
	$type_order=' заказ ';
	break;
	}
 case 1: { 
	$condition = 'SAVE';
	$type_order=' предварительный заказ ';
	break;
	}
  case 2: {
	$condition = 'COND';
	$type_order=' запрос на условия поставки ';
	break;		
  }
  case 3: {
  $condition = 'RESERV';
  $type_order=' запрос на резервирвание товаров ';
	break;
  }
  case 4: {
  $condition = 'LIST';
  $type_order=' запрос на внесение товаров в личный лист предпочтений ';
	break;
  }
  case 5: {
  $condition = 'DEL_ORDER';
  $type_order='запрос на удаление  заказа из списка активных)';
	break;
  }
  case 6: {
  $condition = 'REGISTR_USER';
  $type_order='запрос на регистрацию нового пользователя ';
	break;
  }
	}
$subject="Размещен $type_order на shop.deltar.ru";
if ($choice<5)	{
$rr=$condition[0];
$message="Дата размещения : $date.\n\nНомер заказа: E$rr-000$orderid-\n\nЗаказчик: $ship_name.\nКонтактное лицо(тел.): $ship_cfio ($ship_tels).\nАдрес доставки $ship_city $ship_address.\n\n СОДЕРЖАНИЕ:.\n\n";
$content='';
 $summ=0;
  foreach($_SESSION['cart'] as $isbn => $quantity)
  {
    $detail = $el->get_book_details($isbn,'elements');
	//echo "цена товара ".$isbn." ".$detail['price']."<br>";
	$summ +=$detail['price']*$quantity;
	//$content .=$detail['isbn'].' |'.iconv("windows-1251","utf-8",$detail['title']).' |'.$detail['price'].' |'.$quantity.' | итого '.$detail['price']*$quantity.' руб.';
	$content .=$detail['isbn'].' |'.$detail['title'].' |'.$detail['price'].' |'.$quantity.' | итого '.$detail['price']*$quantity.' руб.';
	$content= "$content \n";
      }
if (isset($message)) {
  $message.="$content \n\n сумма заказа $summ руб. \n\n\n Благодарим Вас обращения к услугам ресурса shop.deltar.ru ! ";
  if (choice <> 6){
  if (Utils::sendMail($ship_em, $subject, $message, 'info@grandjet.ru')) {
  $resmail="На указанный E-mail: $ship_em отправленно сообщение о размещении запроса";
   Utils::sendMail('ruslan@grandjet.ru', 'Внимание!!! Заказ! '.$subject, 'Уведомление -'.$message, $ship_em);
   //}
   //else if (Utils::sendMail($ship_em, $subject, $message, 'info@grandjet.ru')) {
  //$resmail="На указанный E-mail: $ship_em отправленно сообщение о размещении запроса";
  //}
   //session_destroy();
  }
  else $resmail="На указанный E-mail: $ship_em не удалось отправить сообщение о размещении запроса";
}
//if (isset($resmail))echo $resmail;
}
}
if ($chioce==6){
	$message="Дата регистрации : $date.\n\nНомер пользователя: $orderid.\n\nЛогин: $login E-mail: $email";
	$content='На указанный E-mail отправлено письмо со строкой активации';
}
return $resmail;
}

function delet_find($order_details,$choice){
	extract($order_details);
	while ($elem = each ($order_details))
		{
			echo $elem['key'];
			echo " - ";
			echo $elem['value'];
			echo '<br/>';
	}
try {
	$conn = Singleton::getInstance('DB');
} catch(DBException $e) {
	exit($e);
}
//$conn = db_connect();
if ($conn) {
  // Вставка заказа должна выполняться в виде транзакции,
  // поэтому необходимо отключить autocommit
 $conn->autocommit(FALSE);
$conn->start();
if ($choice==5){
	//$query = "UPDATE orders SET order_status = 'DEL' WHERE orderid = $_POST['choice'];";
	//$result = $conn->query($query);

 if (!$result){
	echo "Заказ удален";
		}
		}
	// конец транзакции
  $conn->commit();
  $conn->autocommit(TRUE);
	}
}

function insert_find($order_details,$choice){
	extract($order_details);
	/*while ($elem = each ($order_details))
		{
			echo $elem['key'];
			echo " - ";
			echo $elem['value'];
			echo '<br/>';
		}*/
	try {
	$conn = Singleton::getInstance('DB');
} catch(DBException $e) {
	exit($e);
}
$el = Singleton::getInstance('ElementsW');
//$conn = db_connect();
if ($conn) {
  // Вставка заказа должна выполняться в виде транзакции,
  // поэтому необходимо отключить autocommit
 $conn->autocommit(FALSE);
$conn->start();
  // Вставить почтовый адрес клиента
  $date = date('Y-m-d');
  //echo $date;
 switch( $choice ) {
 case 0: { 
	$condition = 'ORDER';
	$type_order=' заказ ';
	break;
	}
 case 1: { 
	$condition = 'SAVE';
	$type_order=' предварительный заказ ';
	break;
	}
  case 2: {
	$condition = 'COND';
	$type_order=' запрос на условия поставки ';
	break;		
  }
  case 3: {
  $condition = 'RESERV';
  $type_order=' заявка на резервирвание товаров ';
	break;
  }
  case 4: {
  $condition = 'LIST';
  $type_order=' заявка на внесение товаров в личный лист предпочтений ';
	break;
  }
	}

if ($choice <>4) {
//Запись в таблицу orders БД информации о сумме заказа дате и адреса пункта доставки
// если такого заказа уже нет
if(isset($name))$ship_name=$name;
if(isset($address))$ship_address=$address;
if(isset($city))$ship_city=$city;
if(isset($em))$ship_em=$em;
if(isset($tels))$ship_tels=$tels;
if(isset($cfio))$ship_cfio=$cfio;
if(isset($cusid))$customerid=$cusid;
$query = "select orderid from orders where 
               customerid = $customerid and 
               amount > ".$_SESSION['total_price']."-.001 and
               amount < ".$_SESSION['total_price']."+.001 and
               date = '$date' and
               order_status = '$condition' and
               ship_name = '$ship_name' and
               ship_address = '$ship_address' and
               ship_city = '$ship_city' and
               ship_tels = '$ship_tels' and
               ship_em = '$ship_em' and
               ship_cfio = '$ship_cfio'";
 $result = $conn->query($query);
 if (!$result){
	$query = "insert into orders values
            ('', $customerid, ".$_SESSION['total_price'].", '$date', 
             '$condition', '".$ship_name."',
             '$ship_address','$ship_city','$ship_tels','$ship_em',
              '$ship_cfio')";
         $result = $conn->query($query) ;
	
 	 if (!$result){
	echo 'результат запроса 2=0';
   	 return false;
	}
	  else {
	  $query = "select orderid from orders where 
               customerid = $customerid and 
               amount > ".$_SESSION['total_price']."-.001 and
               amount < ".$_SESSION['total_price']."+.001 and
               date = '$date' and
               order_status = '".$condition."' and
               ship_name = '$ship_name' and
               ship_address = '$ship_address' and
               ship_city = '$ship_city' and
               ship_tels = '$ship_tels' and
               ship_em = '$ship_em' and
               ship_cfio = '$ship_cfio'";
	$result = $conn->query($query);
	$orderid=$result;
	echo '<div class="button" >Размещен заказ номер № '.$orderid.'</div>';
	echo '<div class="ank">';	
	echo "Размещен заказ номер № $orderid<br>";
	echo "Дата размещения: $date<br>";
	echo "Заказчик: $ship_name<br>";
	echo "Контактное лицо(тел.): $ship_cfio ($ship_tels)";
	echo "Адрес доставки $ship_city $ship_address";
	echo '</div>';
	echo '<span class="razdel">СОДЕРЖАНИЕ:<br></span>';
	display_cart($_SESSION['cart'], false, 0);
	
	  //echo "<br>";
	  $subject="Размещен $type_order на shop.deltar.ru";
	  //"Здравствуйте $login.\n\nСпасибо за регистрацию на http://{$_SERVER['HTTP_HOST']}.\n\nДля активации вашей учетной записи пройдите по ссылке:\nhttp://{$_SERVER['HTTP_HOST']}/registration/?actcode=$code\n\nЛогин: $login\n\nПароль: $pass";
	  $message="Дата размещения : $date.\n\nНомер заказа: ER-000$orderid.\n\nЗаказчик: $ship_name.\nКонтактное лицо(тел.): $ship_cfio ($ship_tels).\nАдрес доставки $ship_city $ship_address.\n\n СОДЕРЖАНИЕ:.\n\n";
	  
	  //echo $message;
	  }
}
else echo 'такой заказ уже существует<br>';
//echo $_SESSION['total_price']."<br>";
// определяем номер заказа
  $query = "select orderid from orders where 
               customerid = $customerid and 
               amount > ".$_SESSION['total_price']."-.001 and
               amount < ".$_SESSION['total_price']."+.001 and
               date = '$date' and
               order_status = '".$condition."' and
               ship_name = '$ship_name' and
               ship_address = '$ship_address' and
               ship_city = '$ship_city' and
               ship_tels = '$ship_tels' and
               ship_em = '$ship_em' and
               ship_cfio = '$ship_cfio'";
 $result = $conn->query($query);
//$result=mysqli_query($conn,$query);
 // echo "уже заказов для этого клиента ".mysqli_num_rows($result)."<br>";
  if(count($result)>0)
  {
    $orderid = $result;
   // $orderid = $order['orderid'];
	//echo "номер заказа ".$orderid."<br>";
  }
  else {
	echo 'результат запроса 2=0';
    return false; 
	}

  // Вставить каждую книгу из числа заказанных
 $content='';
 $summ=0;
  foreach($_SESSION['cart'] as $isbn => $quantity)
  {
    $detail = $el->get_book_details($isbn,'elements');
	//echo "цена товара ".$isbn." ".$detail['price']."<br>";
	$summ +=$detail['price']*$quantity;
	//$content .=$detail['isbn'].' |'.iconv("windows-1251","utf-8",$detail['title']).' |'.$detail['price'].' |'.$quantity.' | итого '.$detail['price']*$quantity.' руб.';
	$content .=$detail['isbn'].' |'.$detail['title'].' |'.$detail['price'].' |'.$quantity.' | итого '.$detail['price']*$quantity.' руб.';
	$content= "$content.\n";
    $query = "delete from order_items where  
              orderid = '$orderid' and isbn = '$isbn'";
    $result =$conn->query($query);
	$query = "insert into order_items values
              ('$orderid', '$isbn',".$detail['price'].", $quantity)";
	//echo $query."<br>";
    $result = $conn->query($query);
    if(!$result)
	{
	echo 'результат запроса 3=0';
      return false;
	  }
  }
if (isset($message)) {
  $message.="$content.\n\n сумма заказа $summ руб. .n\n\n Благодарим Вас обращения к услугам ресурса shop.deltar.ru ! ";
  
  if (Utils::sendMail($ship_em, $subject, $message, 'info@grandjet.ru')) {
  $resmail="На указанный E-mail: $ship_em отправленно сообщение о размещении запроса";
  Utils::sendMail('ruslan@grandjet.ru', 'Внимание!!! Заказ! '.$subject, 'Уведомление -'.$message, $ship_em);
  // Очистить покупательскую тележку
      session_destroy();
  }
  else $resmail="На указанный E-mail: $ship_em не удалось отправить сообщение о размещении запроса";
}
}
else {
	 foreach($_SESSION['cart'] as $isbn => $quantity) {
		// определить код eid для isbn
		// если товар из корзины отсутсвует в личном списке внести его туда
		$query="select * from `cust_choice` where 'eid` = ";
		}
///////////////////////////////////////////////////продолжить
}

  // конец транзакции
  $conn->commit();
  $conn->autocommit(TRUE);
  //echo $message.'<br>';
  if (isset($resmail))echo $resmail;
}
  return $orderid;
}

function insert_order($order_details, $choice = 0)
{
   //Функция записи заказов в БД
  // Извлечь детальную информацию о заказе и поместить ее в переменные
  extract($order_details);
  $el = Singleton::getInstance('ElementsW');
echo " информация о заказе<br>";
while ($elem = each ($order_details))
{
echo $elem['key'];
echo " - ";
echo $elem['value'];
echo '<br/>';
}

  // Установить адрес доставки равным почтовому адресу
  if(!$ship_name && !$ship_address &&!$ship_city &&
     !$ship_tels && !$ship_em && !$ship_cfio) {
  //echo "Установлен адрес доставки равным почтовому адресу"."<br>";
    $ship_name = $name;
    $ship_address = $address;
    $ship_city = $city;
    $ship_tels = $tels;
    $ship_em = $em;
    $ship_cfio = $cfio;
    $customerid=$cusid;

/*echo " информация о доставке <br>";
echo 'ship_name -'. $ship_name."<br>";
echo 'ship_address -'. $ship_address."<br>";
echo 'ship_city -'. $ship_city."<br>";
echo 'ship_tels -'. $ship_tels."<br>";
echo 'ship_em -'. $ship_em."<br>";
echo 'ship_cfio -'. $ship_cfio."<br>";*/

  }
 else echo "Не установлен адрес доставки равным почтовому адресу"."<br>";


// $conn = db_connect();
try {
	$conn = Singleton::getInstance('DB');
} catch(DBException $e) {
	exit($e);
}

if ($conn) {
  // Вставка заказа должна выполняться в виде транзакции,
  // поэтому необходимо отключить autocommit
$conn->autocommit(FALSE);
$conn->start();
  // Вставить почтовый адрес клиента

  /*$query = "select customerid  userid from customers where  
            name = '$ship_name' and address = '$ship_address' 
            and city = '$ship_city' and tels = '$ship_tels' 
            and em = '$ship_em' and cfio = '$ship_cfio'";
//echo $query;
  $result = $conn->query($query);
  //db_result_to_array($result);
//echo $result;
while ($elem = each ($result ->fetch_assoc()))
{
echo $elem['key'];
echo " - ";
echo $elem['value'];
echo '<br/>';
}
  //echo "Заказчиков с этими реквизитам ".count($result )."<br>";
//echo mysqli_num_rows($result );echo '<br/>';
//точка останова
//echo var_dump($result);
  if($result >0)
  {
    //$customerid = $result;

	//ElementsW::Showobjtype( $result);
    //$customerid = $customer->customerid;//ошибка Trying to get property of non-object in
	//echo "код клиента ".$customerid."<br>";
  }
  else
  {
    $query = "insert into customers values
            ('','$name','$address','$city','$tels','$em','$cfio
			')";
    $result = $conn->query($query);
    if (!$result)
       return false;
	   $customerid =$conn->insert_id;
  //echo "код клиента ".$customerid."<br>";

  }
 */ 
  $date = date('Y-m-d');
  //echo $date;
 switch( $choice ) {
 case 0: { 
	$condition = 'ORDER';
	break;
	}
 case 1: { 
	$condition = 'SAVE';
	break;
	}
  case 2: {
	$condition = 'COND';
	break;		
  }
  case 3: {
  $condition = 'RESERV';
	break;
  }
	}
//Запись в таблицу orders БД информации о сумме заказа дате и адреса пункта доставки
// если такого заказа уже нет
$query = "select orderid from orders where 
               customerid = $customerid and 
               amount > ".$_SESSION['total_price']."-.001 and
               amount < ".$_SESSION['total_price']."+.001 and
               date = '$date' and
               order_status = '".$condition."' and
               ship_name = '$ship_name' and
               ship_address = '$ship_address' and
               ship_city = '$ship_city' and
               ship_tels = '$ship_tels' and
               ship_em = '$ship_em' and
               ship_cfio = '$ship_cfio'";
 $result = $conn->query($query);
 if (!$result){
	$query = "insert into orders values
            ('', $customerid, ".$_SESSION['total_price'].", '$date', 
             '$condition', '".$ship_name."',
             '$ship_address','$ship_city','$ship_tels','$ship_em',
              '$ship_cfio')";
         $result = $conn->query($query) ;
 	 if (!$result){
	echo 'результат запроса 2=0';
   	 return false;
	}
	  else 'данные записаны в БД с номером следующим orderid<br>';
}
else echo 'такой заказ уже существует<br>';
//echo $_SESSION['total_price']."<br>";

  $query = "select orderid from orders where 
               customerid = $customerid and 
               amount > ".$_SESSION['total_price']."-.001 and
               amount < ".$_SESSION['total_price']."+.001 and
               date = '$date' and
               order_status = '".$condition."' and
               ship_name = '$ship_name' and
               ship_address = '$ship_address' and
               ship_city = '$ship_city' and
               ship_tels = '$ship_tels' and
               ship_em = '$ship_em' and
               ship_cfio = '$ship_cfio'";
  $result = $conn->query($query);
  //echo "уже заказов для этого клиента ".$result->num_rows."<br>";
  if($result>0)
  {
    //$order = $result->fetch_object();
    $orderid = $result;
	//echo "номер заказа ".$orderid."<br>";
  }
  else
    return false; 

  // Вставить каждую книгу из числа заказанных
 /* while ($elem = each ($_SESSION['cart']))
{
echo $elem['key'];
echo " - ";
echo $elem['value'];
echo '<br/>';
}*/
  foreach($_SESSION['cart'] as $isbn => $quantity)
  {
    $detail = $el->get_book_details($isbn,'elements');
	//echo "цена товара ".$isbn." ".$detail['price']."<br>";
    $query = "delete from order_items where  
              orderid = '$orderid' and isbn = '$isbn'";
    $result =$conn->query($query);
	$query = "insert into order_items values
              ('$orderid', '$isbn',".$detail['price'].", $quantity)";
	//echo $query."<br>";
    $result = $conn->query($query);
    if(!$result) {echo "отправка запроса на счет не произошла<br>";return false;}
	else {echo "отправка запроса на счет <br>";sendemail($order_details,0,$orderid);}
  }

  // конец транзакции
  $conn->commit();
  $conn->autocommit(TRUE);
}
  return $orderid;
}
?>