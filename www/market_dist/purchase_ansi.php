<?php

  // Включить наш набор функций
  require ('book_sc_fns.php');
  // Для покупательской тележки необходимо запустить сеанс
  session_start();

  do_html_header("Окончательный расчет");
  
  // Создать короткие имена переменных
  $name = $_POST['name'];
  $address = $_POST['address'];
  $city = $_POST['city'];
  $state = $_POST['state'];
  $zip = $_POST['zip'];
  $country = $_POST['country'];
    // Если форма заполнена
  if($_SESSION['cart']&&$name&&$address&&$city&&$state&&$zip&&$country)
  {
    // Можно ли вставлять в базу данных?
    if( insert_order($_POST)!=false )
    {
      // Вывести тележку без изображений товаров и не разрешая изменения
      display_cart($_SESSION['cart'], false, 0);

      display_shipping(calculate_shipping_cost());  

      // Получить информацию по кредитной карточке
      display_card_form($name);

      display_button('../index.php', 'continue-shopping', 'Продолжить покупки');  
    }
    else
    {
      echo 'Невозможно сохранить данные. Пожалуйста, повторите попытку позже.';
      display_button('checkout.php', 'back', 'Назад');
    }
  }
  else
  {
    echo 'Вы заполнили не все поля. Пожалуйста, повторите попытку.<hr />';
    display_button('checkout.php', 'back', 'Назад');
  } 
 
  do_html_footer();
?>
