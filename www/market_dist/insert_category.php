<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Добавление новой категории');
if (check_admin_user())
{ 
  if (filled_out($_POST)) 
  {
    $catname = $_POST['catname'];
    if(insert_category($catname))
      echo "Категория '$catname' добавлена в базу данных.<br />";
    else
      echo "Категория '$catname' не может быть добавлена в базу данных.<br />";
  } 
  else 
    echo 'Вы ввели не все данные.  Пожалуйста, повторите попытку.';
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else 
  echo 'Вам не разрешен доступ в область администратора.';

do_html_footer();

?>
