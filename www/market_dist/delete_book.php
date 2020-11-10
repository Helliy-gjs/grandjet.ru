<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('�������� �����');
if (check_admin_user())
{
  if (isset($_POST['isbn'])) 
  {
    $isbn = $_POST['isbn'];
    if(delete_book($isbn))
      echo '����� '.$isbn.' �������.<br />';
    else
      echo '����� '.$isbn.' �� ����� ���� �������.<br />';
  } 
  else 
    echo '��� �������� ����� ���������� ������ ISBN.  ����������, ��������� �������.<br />';
  do_html_url('admin.php', '����� � ���� �����������������');
}
else 
  echo '��� �� �������� ������ �� ��� ��������.'; 

do_html_footer();

?>
