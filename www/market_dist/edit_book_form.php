<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Редактирование сведений о книге');
if (check_admin_user())
{
  if ($book = get_book_details($_GET['isbn']))
  {
    display_book_form($book);
  }
  else
    echo 'Невозможно получить сведения о книге.<br />';
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else
  echo 'Вам не разрешен доступ в область администратора.';

do_html_footer();

?>
