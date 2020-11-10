<?php
  require ('book_sc_fns.php');
  // Для покупательской тележки необходимо запустить сеанс
  session_start();

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

  do_html_header('Ваша тележка');
 
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
