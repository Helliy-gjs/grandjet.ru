<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Добавление новой категории');
if (check_admin_user())
{
  display_category_form();
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else
  echo 'Вам не разрешен доступ в область администратора.';

do_html_footer();

?>
