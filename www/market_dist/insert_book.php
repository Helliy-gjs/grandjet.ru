<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('���������� �����');
if (check_admin_user())
{ 
  if (filled_out($_POST)) 
  {
    $isbn = $_POST['isbn'];
    $title = $_POST['title'];
    $author = $_POST['author'];
    $catid = $_POST['catid'];
    $price = $_POST['price'];
    $description = $_POST['description'];

    if(insert_book($isbn, $title, $author, $catid, $price, $description))
      echo "����� '".stripslashes($title)."' ��������� � ���� ������.<br />";
    else
      echo "����� '".stripslashes($title).
           "' �� ����� ���� ��������� � ���� ������.<br />";
  } 
  else 
    echo '�� ��������� �� ��� ���� �����. ����������, ��������� �������.';

  do_html_url('admin.php', '����� � ���� �����������������');
}
else 
  echo '� ��� ��� ���� ��� ������� �� �������� �����������������.'; 

do_html_footer();

?>
