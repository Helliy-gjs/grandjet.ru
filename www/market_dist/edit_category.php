<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('�������������� �������� � ���������');
if (check_admin_user())
{ 
  if (filled_out($_POST)) 
  {
    if(update_category($_POST['catid'], $_POST['catname']))
      echo '�������� � ��������� ���������.<br />';
    else
      echo '���������� �������� �������� � ���������.<br />';
  } 
  else 
    echo '�� ����� �� ��� ������.  ����������, ��������� �������.';
  do_html_url('admin.php', '����� � ���� �����������������');
}
else 
  echo '��� �� �������� ������ �� ��� ��������.'; 

do_html_footer();

?>
