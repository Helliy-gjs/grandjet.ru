<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('���������� ����� ���������');
if (check_admin_user())
{ 
  if (filled_out($_POST)) 
  {
    $catname = $_POST['catname'];
    if(insert_category($catname))
      echo "��������� '$catname' ��������� � ���� ������.<br />";
    else
      echo "��������� '$catname' �� ����� ���� ��������� � ���� ������.<br />";
  } 
  else 
    echo '�� ����� �� ��� ������.  ����������, ��������� �������.';
  do_html_url('admin.php', '����� � ���� �����������������');
}
else 
  echo '��� �� �������� ������ � ������� ��������������.';

do_html_footer();

?>
