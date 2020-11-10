<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Удаление книги');
if (check_admin_user())
{
  if (isset($_POST['isbn'])) 
  {
    $isbn = $_POST['isbn'];
    if(delete_book($isbn))
      echo 'Книга '.$isbn.' удалена.<br />';
    else
      echo 'Книга '.$isbn.' не может быть удалена.<br />';
  } 
  else 
    echo 'Для удаления книги необходимо ввести ISBN.  Пожалуйста, повторите попытку.<br />';
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else 
  echo 'Вам не разрешен доступ на эту страницу.'; 

do_html_footer();

?>
