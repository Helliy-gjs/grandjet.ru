<?php

// �������� ���������� ������� ��� ����� ����������
require_once('book_sc_fns.php'); 
session_start();

do_html_header('�������������� �������� � ���������');
if (check_admin_user())
{
  if ($catname = get_category_name($_GET['catid']))
  {
    $catid = $_GET['catid'];
    $cat = compact('catname', 'catid');
    display_category_form($cat);
  }
  else
    echo '���������� �������� �������� � ���������.<br />';
  do_html_url('admin.php', '����� � ���� �����������������');
}
else
  echo '��� �� �������� ������ �� ��� ��������.'; 

do_html_footer();

?>
