<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();
$old_user = $_SESSION['admin_user'];  // сохранить для проверки, был ли уже зарегистрирован посетитель
unset($_SESSION['admin_user']);
session_destroy();

// Начать вывод html-кода
do_html_header('Выход');

if (!empty($old_user))
{
  echo 'Успешный выход.<br />';
  do_html_url('login.php', 'Вход');
}
else
{
  // Если кто-то не входил в систему, но каким-то образом попал на эту страницу
  echo 'Вы не входили в систему, поэтому и выходить из нее не нужно.<br />';
  do_html_url('login.php', 'Вход');
}

do_html_footer();

?>
