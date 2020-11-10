<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

do_html_header('Редактирование сведений о категории');
if (check_admin_user())
{
  if ($catname = get_category_name($_GET['catid']))
  {
    $catid = $_GET['catid'];
    $cat = compact('catname', 'catid');
    display_category_form($cat);
  }
  else
    echo 'Невозможно получить сведения о категории.<br />';
  do_html_url('admin.php', 'Назад в меню администрирования');
}
else
  echo 'Вам не разрешен доступ на эту страницу.'; 

do_html_footer();

?>
