<?php 

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
  if(!$_SESSION['items']) $_SESSION['items'] = '0';
		if(!$_SESSION['total_price']) $_SESSION['total_price'] = '0.00';
		/*верхний колонтитул лозунг
		$L=array();
		$L=explode('|',$PageM->MainAr['lozung']);
		$list['7']=explode(',',$L[0]);//массив лозунгов страницы
				echo '<div class="head">'.$list[7][0].'</div>';*/
				//область информации о пользователе и состоянии его корзины-->
					echo '<div class="user">';
					$user = Singleton::getInstance('User');
					$uid=$user->check();
					$cid=$user->getusercid();
					echo 'cid='.$cid;
					echo ' Сегодня: '.date("d m Y").' |'.'<span>Логин:'.$user->getLogin().'</span>';
					echo '|Общая сумма = (rub)'.number_format($_SESSION['total_price'],2);
				    echo '|Зарезервировано товаров- '.number_format($_SESSION['items'],0);
					if($cid == null) echo '|<a href="../regurl.php"> Регистрация юридического лица </a>';
					else 	if (!$cid==0) echo '|Заказчик:'.$user->idUserF($uid)->name;
						if(!$user->isGuest()) {
							if ($user->getLevel()>3) echo '|<a href="/settings/">Настройки</a>';
						}
						echo '|<a href="/auth/?logout">Выйти</a>';
						
					echo '</div>';
	//include($pathheader.$pathToClasses.'Cart.inc');
//do_html_header('Ваша тележка');
 
  if($_SESSION['cart']&&array_count_values($_SESSION['cart']))
    display_cart($_SESSION['cart']);
  else
  {
    echo '<p>Резервов нет</p>';
    echo '<hr />';
  }
  $target = "../?np=".$arrmain['numpage'];

  // Если в тележку был только что добавлен новый элемент,
  // продолжить покупки товаров данной категории
  if($new)
  {
  
    $details =  $el->get_book_details($new,'elemarch');
    if($details['catid'])    
      $target = "../?np=".$arrmain['numpage']; 
  }
$target2=  "../regurl.php";
echo '<table><tr>';
if (!$cid==0){
  if ($cid=$user->idCust($cid)->customerid)  {
	displaybutton($target, '../images/butnoch', 'Продолжить покупки');
	//echo '<a href="javascript:javascript:history.go(-1)">Продолжить покупки</a>';
	//echo '<form><input type="button" value="Назад на предыдущую страницу" onClick="history.back()"></form>';
	 if (strstr(SYS_HTTP,'localhost')) {
  		display_button(SYS_HTTP.'/checkout.php?cid='.$cid, 'images/go-to-checkout', 'Окончательный расчет'); 
  		}
		displaybutton('./checkout.php?par=s', '../images/butnoch', 'Оформить запрос');
	 if ($_SESSION['total_price']>0) {
	 
		//displaybutton('./checkout.php?par=d', '../images/butnoch', 'Удалить заказ');  
		displaybutton('./checkout.php?par=b', '../images/butnoch', 'Оформить счет на оплату с доставкой'); 
 	}
	}
}
else   display_button($target2, 'registration_url', 'Необходимо зарегистрировать хотя бы одну организацию - юридическое лицо');	
echo '<div class="head">Комментарий (из руководства пользователя shop.deltar.ru)</div>';
Page::display_manual($nman);
Page::display_manual(-1);
do_html_footer(); 
?>