<?php
 require_once('book_sc_fns.php');
 session_start();
 do_html_header('��������� ������');
 check_admin_user();
 if (!filled_out($_POST))
 {
   echo '�� ��������� �� ��� ���� �����.  ����������, ��������� �������.';
   do_html_url('admin.php', '����� � ���� �����������������');
   do_html_footer();  
   exit;
 }
 else 
 {
    $new_passwd = $_POST['new_passwd'];
    $new_passwd2 = $_POST['new_passwd2'];
    $old_passwd = $_POST['old_passwd'];
    if ($new_passwd!=$new_passwd2)
       echo '��������� ������ �� ���������.  ������ �� �������.';
    else if (strlen($new_passwd)>16 || strlen($new_passwd)<6)
       echo '����� ������ ������ ��������� �� ����� 6 ��������.  ��������� �������.';
    else
    {
        // ������� ���������
        if (change_password($_SESSION['admin_user'], $old_passwd, $new_passwd))
           echo '������ �������.';
        else
           echo '���������� �������� ������.';
    }


 }
  do_html_url('admin.php', '����� � ���� �����������������');  
  do_html_footer();
?>
