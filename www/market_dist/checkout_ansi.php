<?php
  // �������� ��� ����� �������
  require ('book_sc_fns.php');

  // ��� �������������� ������� ���������� ��������� �����
  session_start();

  do_html_header('������������� ������');
  
  if($_SESSION['cart']&&array_count_values($_SESSION['cart']))
  {
    display_cart($_SESSION['cart'], false, 0);
    display_checkout_form();
  }
  else
    echo '<p>���� ������� �����</p>';
 
  display_button('../index.php', 'continue-shopping', '���������� �������');  

  do_html_footer();
?>
