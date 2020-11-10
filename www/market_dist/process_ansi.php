<?php
  // Включить наш набор функций
  require ('book_sc_fns.php');
  // Для покупательской тележки необходимо запустить сеанс
  session_start();

  do_html_header('Окончательный расчет');

  // Создать короткие имена переменных
  $card_type = $_POST['card_type'];
  $card_number = $_POST['card_number'];
  $card_month = $_POST['card_month'];
  $card_year = $_POST['card_year'];
  $card_name = $_POST['card_name'];

  if($_SESSION['cart']&&$card_type&&$card_number&&
     $card_month&&$card_year&&$card_name )
  {
    // Вывести тележку без изображений товара и не разрешая изменения
    display_cart($_SESSION['cart'], false, 0);

    display_shipping(calculate_shipping_cost());  

    if(process_card($_POST))
    {
      // Очистить покупательскую тележку
      session_destroy();
      echo 'Спасибо за то, что воспользовались нашим сайтом для совершения 
        покупок.  Ваш заказ размещен.';
      display_button('../index.php', 'continue-shopping', 'Продолжить покупки');  
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
