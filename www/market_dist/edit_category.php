<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Редактирование сведений о категории');
if (check_admin_user())
{ 
  if (filled_out($_POST)) 
  {
    if(update_category($_POST['catid'], $_POST['catname']))
      echo 'Сведения о категории обновлены.<br />';
    else
      echo 'Невозможно обновить сведения о категории.<br />';
  } 
  else 
    echo 'Вы ввели не все данные.  Пожалуйста, повторите попытку.';
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else 
  echo 'Вам не разрешен доступ на эту страницу.'; 

do_html_footer();

?>
