<?php
  // �������� ��� ����� �������
  require ('book_sc_fns.php');
  // ��� �������������� ������� ���������� ��������� �����
  session_start();

  do_html_header('������������� ������');

  // ������� �������� ����� ����������
  $card_type = $_POST['card_type'];
  $card_number = $_POST['card_number'];
  $card_month = $_POST['card_month'];
  $card_year = $_POST['card_year'];
  $card_name = $_POST['card_name'];

  if($_SESSION['cart']&&$card_type&&$card_number&&
     $card_month&&$card_year&&$card_name )
  {
    // ������� ������� ��� ����������� ������ � �� �������� ���������
    display_cart($_SESSION['cart'], false, 0);

    display_shipping(calculate_shipping_cost());  

    if(process_card($_POST))
    {
      // �������� �������������� �������
      session_destroy();
      echo '������� �� ��, ��� ��������������� ����� ������ ��� ���������� 
        �������.  ��� ����� ��������.';
      display_button('../index.php', 'continue-shopping', '���������� �������');  
    }
    else
    {
    echo '���������� ���������� ���� ��������� ��������.';
    echo '����������, ��������� � �������� �� ������������ ���� 
          ��������� ����.';
      display_button('purchase.php', 'back', '�����');
    }
  }
  else
  {
    echo '�� ��������� �� ��� ����. ����������, ��������� �������.<hr />';
    display_button('purchase.php', 'back', '�����');
  } 
 
  do_html_footer();
?>
