<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Обновление сведений о книге');
if (check_admin_user())
{ 
  if (filled_out($_POST)) 
  {
    $oldisbn = $_POST['oldisbn'];
    $isbn = $_POST['isbn'];
    $title = $_POST['title'];
    $author = $_POST['author'];
    $catid = $_POST['catid'];
    $price = $_POST['price'];
    $description = $_POST['description'];

    if(update_book($oldisbn, $isbn, $title, $author, $catid,
                      $price, $description))
      echo 'Сведения о книге обновлены.<br />';
    else
      echo 'Невозможно обновить сведения о книге.<br />';
  } 
  else 
    echo 'Вы ввели не все данные.  Пожалуйста, повторите попытку.';
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else 
  echo 'Вам не разрешен доступ на эту страницу.'; 

do_html_footer();

?>
