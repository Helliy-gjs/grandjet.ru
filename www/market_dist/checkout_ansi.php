<?php
  // Включить наш набор функций
  require ('book_sc_fns.php');

  // Для покупательской тележки необходимо запустить сеанс
  session_start();

  do_html_header('Окончательный расчет');
  
  if($_SESSION['cart']&&array_count_values($_SESSION['cart']))
  {
    display_cart($_SESSION['cart'], false, 0);
    display_checkout_form();
  }
  else
    echo '<p>Ваша тележка пуста</p>';
 
  display_button('../index.php', 'continue-shopping', 'Продолжить покупки');  

  do_html_footer();
?>
