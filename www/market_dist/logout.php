<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();
$old_user = $_SESSION['admin_user'];  // ��������� ��� ��������, ��� �� ��� ��������������� ����������
unset($_SESSION['admin_user']);
session_destroy();

// ������ ����� html-����
do_html_header('�����');

if (!empty($old_user))
{
  echo '�������� �����.<br />';
  do_html_url('login.php', '����');
}
else
{
  // ���� ���-�� �� ������ � �������, �� �����-�� ������� ����� �� ��� ��������
  echo '�� �� ������� � �������, ������� � �������� �� ��� �� �����.<br />';
  do_html_url('login.php', '����');
}

do_html_footer();

?>
