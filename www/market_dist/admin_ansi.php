<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

if ($_POST['username'] && $_POST['passwd'])
// ������������ ������ ��� ��������� ����� � �������
{
    $username = $_POST['username'];
    $passwd = $_POST['passwd'];

    if (login($username, $passwd))
    {
      // ���� ������������ ������� � ���� ������, ���������������� ��� �������������
      $_SESSION['admin_user'] = $username;
    }  
    else
    {
      // ��������� ���� � �������
      do_html_header('��������:');
      echo '���� � ������� ����������. 
            ��� ��������� ���� �������� ���������� ����� � �������.';
      do_html_url('login.php', '����');
      do_html_footer();
      exit;
    }      
}

do_html_header('�����������������');
if (check_admin_user())
  display_admin_menu();
else
  echo '� ��� ��� ���� ��� ������� �� �������� �����������������.';

do_html_footer();

?>
