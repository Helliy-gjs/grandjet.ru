<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('�������������� �������� � �����');
if (check_admin_user())
{
  if ($book = get_book_details($_GET['isbn']))
  {
    display_book_form($book);
  }
  else
    echo '���������� �������� �������� � �����.<br />';
  do_html_url('admin.php', '����� � ���� �����������������');
}
else
  echo '��� �� �������� ������ � ������� ��������������.';

do_html_footer();

?>
