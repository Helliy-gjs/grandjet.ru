<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('���������� ����� ���������');
if (check_admin_user())
{
  display_category_form();
  do_html_url('admin.php', '����� � ���� �����������������');
}
else
  echo '��� �� �������� ������ � ������� ��������������.';

do_html_footer();

?>
