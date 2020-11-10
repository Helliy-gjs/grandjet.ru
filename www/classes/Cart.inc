<?php
//do_html_header('Ваша тележка');
foreach($_SESSION['cart']  as $key=>$val){
 if(isset($add) && $add==$key) $_SESSION['cart'][$key]++;
 if(isset($substr) && $substr==$key && $val>0) $_SESSION['cart'][$key]--;
 if(isset($reset) && $reset==$key)$_SESSION['cart'][$key]=0;
 elseif(isset($reset) && $reset=='')$_SESSION['cart'][$key]=0;
}

$_SESSION['total_price'] = calculate_price($_SESSION['cart']);
$_SESSION['items'] = calculate_items($_SESSION['cart']);
if($_SESSION['items']==0) {
	foreach ($_SESSION['cart'] as $isbn => $qty) unset($_SESSION['cart'][$isbn]);
	header('Location: http://'.$_SERVER['HTTP_HOST']);
}
  if($_SESSION['cart']&&array_count_values($_SESSION['cart']))
    display_cart($_SESSION['cart']);
  else
  {
    echo '<p>Резервов нет</p>';
    echo '<hr />';
  }
  $target = '../';

  // Если в тележку был только что добавлен новый элемент,
  // продолжить покупки товаров данной категории
  if($new)
  {
  
    $details =  $el->get_book_details($new,'elements');
    if($details['id'])    
      $target = "../"; 
  }
$target2= '../?editp=ok&cust='.$cid;
echo '<table><tr>';
if (!$cid==0){
  if ($cid=$user->idCust($cid)->customerid)  {
	displaybutton($target, '../images/butnoch', 'Продолжить покупки');
	//echo '<a href="javascript:javascript:history.go(-1)">Продолжить покупки</a>';
	//echo '<form><input type="button" value="Назад на предыдущую страницу" onClick="history.back()"></form>';
	 if (strstr(SYS_HTTP,'localhost')) {
  		display_button(SYS_HTTP.'/checkout.php?cid='.$cid, 'images/go-to-checkout', 'Окончательный расчет'); 
  		}
		display_button('./checkout.php?par=s', '../images/butnoch', 'Оформить запрос');
	 if ($_SESSION['total_price']>0) {
	 
		//displaybutton('./checkout.php?par=d', '../images/butnoch', 'Удалить заказ');  
		display_button('./checkout.php?par=b', '../images/butnoch', 'Оформить счет на оплату с доставкой'); 
 	}
	}
}
else   display_button($target2, 'registration_url', 'Необходимо зарегистрировать хотя бы одну организацию - юридическое лицо');
?>