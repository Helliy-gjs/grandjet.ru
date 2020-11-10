<?php
 require_once('book_sc_fns.php');
 session_start();
 do_html_header('Изменение пароля');
 check_admin_user();
 if (!filled_out($_POST))
 {
   echo 'Вы заполнили не все поля формы.  Пожалуйста, повторите попытку.';
   do_html_url('admin.php', 'Назад в меню администрирования');
   do_html_footer();  
   exit;
 }
 else 
 {
    $new_passwd = $_POST['new_passwd'];
    $new_passwd2 = $_POST['new_passwd2'];
    $old_passwd = $_POST['old_passwd'];
    if ($new_passwd!=$new_passwd2)
       echo 'Введенные пароли не совпадают.  Пароль не изменен.';
    else if (strlen($new_passwd)>16 || strlen($new_passwd)<6)
       echo 'Новый пароль должен содержать не менее 6 символов.  Повторите попытку.';
    else
    {
        // попытка изменения
        if (change_password($_SESSION['admin_user'], $old_passwd, $new_passwd))
           echo 'Пароль изменен.';
        else
           echo 'Невозможно изменить пароль.';
    }


 }
  do_html_url('admin.php', 'Назад в меню администрирования');  
  do_html_footer();
?>
