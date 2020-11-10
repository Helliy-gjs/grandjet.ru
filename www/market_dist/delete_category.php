<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Удаление категории');
if (check_admin_user())
{
  if (isset($_POST['catid'])) 
  {
    if(delete_category($_POST['catid']))
      echo 'Категория удалена.<br />';
    else
      echo 'Невозможно удалить категорию.<br />'
           .'Скорее всего, категория не пуста.<br />';
  } 
  else 
    echo 'Категория не указана.  Пожалуйста, повторите попытку.<br />';
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else 
  echo 'Вам не разрешен доступ на эту страницу.'; 

do_html_footer();

?>
