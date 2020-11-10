<?php

require_once('db_fns.php');

function login($username, $password)
// Проверяет, записаны ли в базе данных переданные имя пользователя и пароль.
// Если это так, возвращает значение true, в противном случае -- false.
{
  // Подключиться к базе данных
  $conn = db_connect();
  if (!$conn)
    return 0;

  // Проверить уникальность имени пользователя
  $result = $conn->query("select * from admin 
                         where username='$username'
                         and password = sha1('$password')");
  if (!$result)
     return 0;
  
  if ($result->num_rows>0)
     return 1;
  else 
     return 0;
}

function check_admin_user()
// Проверяет, вошел ли посетитель, и уведомляет, если нет
{
  if (isset($_SESSION['admin_user']))
    return true;
  else
    return false;
}

function change_password($username, $old_password, $new_password)
// Изменяет паполь для username с old_password на new_password.
// Возврвщвет true или false
{
  // Если старый пароль корректен, 
  // изменить его на новый пароль (new_password) и вернуть true.
  // В противном случае вернуть false
  if (login($username, $old_password))
  {
    if (!($conn = db_connect()))
      return false;
    $result = $conn->query( "update admin 
                            set password = sha1('$new_password')
                            where username = '$username'");
    if (!$result)
      return false;  // не изменен
    else
      return true;  // успешно изменен
  }
  else
    return false; // неправильный старый пароль
}

?>
