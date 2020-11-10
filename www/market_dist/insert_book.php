<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Добавление книги');
if (check_admin_user())
{ 
  if (filled_out($_POST)) 
  {
    $isbn = $_POST['isbn'];
    $title = $_POST['title'];
    $author = $_POST['author'];
    $catid = $_POST['catid'];
    $price = $_POST['price'];
    $description = $_POST['description'];

    if(insert_book($isbn, $title, $author, $catid, $price, $description))
      echo "Книга '".stripslashes($title)."' добавлена в базу данных.<br />";
    else
      echo "Книга '".stripslashes($title).
           "' не может быть добавлена в базу данных.<br />";
  } 
  else 
    echo 'Вы заполнили не все поля формы. Пожалуйста, повторите попытку.';

  do_html_url('admin.php', 'Назад в меню администрирования');
}
else 
  echo 'У вас нет прав для доступа на страницу администрирования.'; 

do_html_footer();

?>
