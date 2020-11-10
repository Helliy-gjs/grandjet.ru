<?php

// Включить библиотеки функций для этого приложения
require_once('book_sc_fns.php'); 
session_start();

if ($_POST['username'] && $_POST['passwd'])
// Пользователь только что попытался войти в систему
{
    $username = $_POST['username'];
    $passwd = $_POST['passwd'];

    if (login($username, $passwd))
    {
      // Если пользователь записан в базе данных, зарегистрировать его идентификатор
      $_SESSION['admin_user'] = $username;
    }  
    else
    {
      // Неудачный вход в систему
      do_html_header('Проблема:');
      echo 'Вход в систему невозможен. 
            Для просмотра этой страница необходимо войти в систему.';
      do_html_url('login.php', 'Вход');
      do_html_footer();
      exit;
    }      
}

do_html_header('Администрирование');
if (check_admin_user())
  display_admin_menu();
else
  echo 'У вас нет прав для доступа на страницу администрирования.';

do_html_footer();

?>
