<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('�������� ���������');
if (check_admin_user())
{
  if (isset($_POST['catid'])) 
  {
    if(delete_category($_POST['catid']))
      echo '��������� �������.<br />';
    else
      echo '���������� ������� ���������.<br />'
           .'������ �����, ��������� �� �����.<br />';
  } 
  else 
    echo '��������� �� �������.  ����������, ��������� �������.<br />';
  do_html_url('admin.php', '����� � ���� �����������������');
}
else 
  echo '��� �� �������� ������ �� ��� ��������.'; 

do_html_footer();

?>
