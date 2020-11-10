<?php
 require_once("book_sc_fns.php");
 session_start();
 do_html_header("Изменение пароля администратора");
 check_admin_user();
 
 display_password_form();

 do_html_url("admin.php", "Назад в меню администрирования");
 do_html_footer();
?>
