<?php

function do_html_header($title = '')
{
  // Выводит HTML-заголовок
 
  // Объявить переменные сеанса
  if(!$_SESSION['items']) $_SESSION['items'] = '0';
  if(!$_SESSION['total_price']) $_SESSION['total_price'] = '0.00';
?>
  <html>
  <head>
    <title><?php echo $title; ?></title>
    <style>
      h2 { font-family: Arial, Helvetica, sans-serif; font-size: 22px; color = red; margin = 6px }
      body { font-family: Arial, Helvetica, sans-serif; font-size: 13px }
      li, td { font-family: Arial, Helvetica, sans-serif; font-size: 13px }
      hr { color: #FF0000; width=70%; text-align=center}
      a { color: #000000 }
    </style>
  </head>
  <body>
  <table width='100%' border=0 cellspacing = 0 bgcolor='#cccccc'>
  <tr>
  <td rowspan = 2>
  <a href = 'index.php'><img src='images/Book-O-Rama.gif' alt='Магазин БУКВОФИЛ' border=0
       align='left' valign='bottom' height = 55 width = 325></a>
  </td>
  <td align = 'right' valign = 'bottom'>
  <?php if(isset($_SESSION['admin_user']))
       echo '&nbsp;';
     else
       echo 'Всего книг = '.$_SESSION['items']; 
  ?>
  </td>
  <td align = 'right' rowspan = 2 width = 135>
  <?php if(isset($_SESSION['admin_user']))
       display_button('logout.php', 'log-out', 'Выход');
     else
       display_button('show_cart.php', 'view-cart', 'Показать тележку');
  ?>
  </tr>
  <tr>
  <td align = right valign = top>
  <?php if(isset($_SESSION['admin_user']))
       echo '&nbsp;';
     else
       echo 'Общая сумма = $'.number_format($_SESSION['total_price'],2); 
  ?>
  </td>
  </tr>
  </table>
<?php
  if($title)
    do_html_heading($title);
}

function do_html_footer()
{
  // Выводит завершыющие HTML-дескрипторы
?>
  </body>
  </html>
<?php
}

function do_html_heading($heading)
{
  // Выводит заголовок
?>
  <h2><?php echo $heading; ?></h2>
<?php
}

function do_html_URL($url, $name)
{
  // Выводит URL в виде ссылки и дескриптор новой строки
?>
  <a href="<?php echo $url; ?>"><?php echo $name; ?></a><br />
<?php
}

function display_categories($cat_array)
{
  if (!is_array($cat_array))
  {
     echo 'В настоящий момент нет доступных категорий<br />';
     return;
  }
  echo '<ul>';
  foreach ($cat_array as $row)
  {
    $url = 'show_cat.php?catid='.($row['catid']);
    $title = $row['catname']; 
    echo '<li>';
    do_html_url($url, $title); 
    echo '</li>';
  }    
  echo '</ul>';
  echo '<hr />';
}

function display_books($book_array)
{
  // Выводит все книги, переданные в массиве
  if (!is_array($book_array))
  {
     echo '<br />В настоящий момент нет доступных книг в этой категории<br />';
  }
  else
  {
    // Создать таблицу
    echo '<table width = \"100%\" border = 0>';
    
    // Создать строку таблицы для каждой книги 
    foreach ($book_array as $row)
    {
      $url = 'show_book.php?isbn='.($row['isbn']);
      echo '<tr><td>';
      if (@file_exists('images/'.$row['isbn'].'.jpg'))
      {
        $title = '<img src=\'images/'.($row['isbn']).'.jpg\' border=0 />';
        do_html_url($url, $title);
      }
      else
      {
        echo '&nbsp;';
      }
      echo '</td><td>';
      $title =  $row['title'].' PN '.$row['art'];
      do_html_url($url, $title);
      echo '</td></tr>';
    }
    echo '</table>';
  }
  echo '<hr />';
}

function display_book_details($book)
{
  // Выводит детальную информацию по конкретной книге
  if (is_array($book))
  {
    echo '<table><tr>'; 
    // Вывести изображение обложки, если оно имеется 
    if (@file_exists('images/'.($book['isbn']).'.jpg'))
    {
      $size = GetImageSize('images/'.$book['isbn'].'.jpg');
      if($size[0]>0 && $size[1]>0)
        echo '<td><img src=\'images/'.$book['isbn'].'.jpg\' border=0 '.$size[3].'></td>';
    }
    echo '<td><ul>';
    echo '<li><b>Автор:</b> ';
    echo $book['author'];
    echo '</li><li><b>ISBN:</b> ';
    echo $book['isbn'];
    echo '</li><li><b>Наша цена:</b> ';
    echo number_format($book['price'], 2);
    echo '</li><li><b>Аннотация:</b> ';
    echo $book['description'];
    echo '</li></ul></td></tr></table>'; 
  }
  else
    echo 'Невозможно вывести сведения о данной книге.';
  echo '<hr />';
}

function display_checkout_form()
{
  // Выводит форму, которая запрашивает ФИО и адрес
?>
  <br />
  <table border = 0 width = '100%' cellspacing = 0>
  <form action = 'purchase.php' method = 'post'>
  <tr><th colspan = 2 bgcolor='#cccccc'>Информация о вас</th></tr>
  <tr>
    <td>ФИО</td>
    <td><input type = 'text' name = 'name' value = "" maxlength = 40 size = 40></td>
  </tr>
  <tr>
    <td>Адрес</td>
    <td><input type = 'text' name = 'address' value = "" maxlength = 40 size = 40></td>
  </tr>
  <tr>
    <td>Город/село</td>
    <td><input type = 'text' name = 'city' value = "" maxlength = 20 size = 40></td>
  </tr>
  <tr>
    <td>Область</td>
    <td><input type = 'text' name = 'state' value = "" maxlength = 20 size = 40></td>
  </tr>
  <tr>
    <td>Почтовый индекс</td>
    <td><input type = 'text' name = 'zip' value = "" maxlength = 10 size = 40></td>
  </tr>
  <tr>
    <td>Страна</td>
    <td><input type = 'text' name = 'country' value = "" maxlength = 20 size = 40></td>
  </tr>
  <tr><th colspan = 2 bgcolor='#cccccc'>Адрес для доставки (не заполняйте поля, если совпадает с указанным выше)</th></tr>
  <tr>
    <td>ФИО</td>
    <td><input type = 'text' name = 'ship_name' value = "" maxlength = 40 size = 40></td>
  </tr>
  <tr>
    <td>Адрес</td>
    <td><input type = 'text' name = 'ship_address' value = "" maxlength = 40 size = 40></td>
  </tr>
  <tr>
    <td>Город/село</td>
    <td><input type = 'text' name = 'ship_city' value = "" maxlength = 20 size = 40></td>
  </tr>
  <tr>
    <td>Область</td>
    <td><input type = 'text' name = 'ship_state' value = "" maxlength = 20 size = 40></td>
  </tr>
  <tr>
    <td>Почтовый индекс</td>
    <td><input type = 'text' name = 'ship_zip' value = "" maxlength = 10 size = 40></td>
  </tr>
  <tr>
    <td>Страна</td>
    <td><input type = 'text' name = 'ship_country' value = "" maxlength = 20 size = 40></td>
  </tr>
  <tr>
    <td colspan = 2 align = 'center'>
      <b>Пожалуйста, щелкните на кнопке "Purchase" для того, чтобы подтвердить покупку,
         либо на кнопке "Continue Shopping" для продолжения покупок.</b> 
     <?php display_form_button('purchase', 'Приобрести выбранное'); ?>
    </td>
  </tr>
  </form>
  </table><hr />
<?php
}

function display_shipping($shipping)
{
  // Выводит строку таблицы со стоимостью доставки и общей стоимостью заказа, включая доставку
?>
  <table border = 0 width = '100%' cellspacing = 0>
  <tr><td align = 'left'>Доставка</td>
      <td align = 'right'> <?php echo number_format($shipping, 2); ?></td></tr>
  <tr><th bgcolor='#cccccc' align = 'left'>ВСЕГО, ВКЛЮЧАЯ ДОСТАВКУ</th>
      <th bgcolor='#cccccc' align = 'right'>$<?php echo number_format($shipping+$_SESSION['total_price'], 2); ?></th>
  </tr>
  </table><br />
<?php
}

function display_card_form($name)
{
  // Выводит форму, запрашивающую сведения о кредитной карточке
?>
  <table border = 0 width = '100%' cellspacing = 0>
  <form action = 'process.php' method = 'post'>
  <tr><th colspan = 2 bgcolor="#cccccc">Сведения о кредитной карточке</th></tr>
  <tr>
    <td>Вид</td>
    <td><select name = 'card_type'><option>VISA<option>MasterCard<option>American Express</select></td>
  </tr>
  <tr>
    <td>Номер</td>
    <td><input type = 'text' name = 'card_number' value = "" maxlength = 16 size = 40></td>
  </tr>
  <tr>
    <td>AMEX-код (если необходим)</td>
    <td><input type = 'text' name = 'amex_code' value = "" maxlength = 4 size = 4></td>
  </tr>
  <tr>
    <td>Дата истечения</td>
    <td>Месяц <select name = 'card_month'><option>01<option>02<option>03<option>04<option>05<option>06<option>07<option>08<option>09<option>10<option>11<option>12</select>
    Год <select name = 'card_year'><option>00<option>01<option>02<option>03<option>04<option>05<option>06<option>07<option>08<option>09<option>10</select></td>
  </tr>
  <tr>
    <td>Держатель карточки</td>
    <td><input type = 'text' name = 'card_name' value = "<?php echo $name; ?>" maxlength = 40 size = 40></td>
  </tr>
  <tr>
    <td colspan = 2 align = 'center'>
      <b>Пожалуйста, щелкните на кнопке "Purchase" для того, чтобы подтвердить покупку,
         либо на кнопке "Continue Shopping" для продолжения покупок.</b> 
     <?php display_form_button('purchase', 'Приобрести выбранное'); ?>
    </td>
  </tr>
  </table>
<?php
}

function display_cart($cart, $change = true, $images = 1)
{
  // Выводит элементы, находящиеся в покупательской тележке.
  // Дополнительно получает параметр $change, разрешающий (true)
  // или запрещающий (false) внесение изменений.
  // Дополнительно получает параметр $images, разрешающий (true)
  // или запрещающий (false) вывод изображений товаров.

  echo '<table border="0" width="100%" cellspacing="0">
        <form action="show_cart.php" method="post">
        <tr><th colspan="'. (1+$images) .'" bgcolor="#cccccc">Товар</th>
        <th bgcolor="#cccccc">Цена</th><th bgcolor="#cccccc">Количество</th>
        <th bgcolor="#cccccc">Всего</th></tr>';

  // Отобразить каждый элемент в виде строки таблицы
  foreach ($cart as $isbn => $qty)
  {
    $book = get_book_details($isbn);
    echo '<tr>';
    if($images ==true)
    {
      echo '<td align="left">';
      if (file_exists("images/$isbn.jpg"))
      {
         $size = GetImageSize('images/'.$isbn.'.jpg');  
         if($size[0]>0 && $size[1]>0)
         {
           echo '<img src="images/'.$isbn.'.jpg" border=0 ';
           echo 'width = '. $size[0]/3 .' height = ' .$size[1]/3 . '>';
         }
      }
      else
         echo '&nbsp;';
      echo '</td>';
    }
    echo '<td align="left">';
    echo '<a href="show_book.php?isbn='.$isbn.'">'.$book['title'].
         '</a> by '.$book['author'];
    echo '</td><td align="center">$'.number_format($book['price'], 2);
    echo '</td><td align="center">';
    // Если разрешены изменения, представить количества в текстовых полях ввода
    if ($change == true)
      echo "<input type='text' name=\"$isbn\" value=\"$qty\" size=\"3\">";
    else
      echo $qty;
    echo '</td><td align="center">$'.number_format($book['price']*$qty,2).
         "</td></tr>\n";

  }
  // Вывести строку общего количества и суммы заказа
  echo "<tr>
          <th colspan=". (2+$images) ." bgcolor=\"#cccccc\">&nbsp;</td>
          <th align = \"center\" bgcolor=\"#cccccc\"> 
              ".$_SESSION['items']."
          </th>
          <th align = center bgcolor=\"#cccccc\">
              \$".number_format($_SESSION['total_price'], 2).
          '</th>
        </tr>';
  // Вывести кнопку сохранения изменений
  if($change == true)
  {
    echo '<tr>
            <td colspan="'. (2+$images) .'">&nbsp;</td>
            <td align="center">
              <input type="hidden" name="save" value="true">  
              <input type="image" src="images/save-changes.gif" 
                     border="0" alt="Сохранить изменения">
            </td>
            <td>&nbsp;</td>
        </tr>';
  }
  echo '</form></table>';
}

function display_login_form()
{
  // Выводит форму, запрашивающую имя пользователя и пароль
?>
  <form method='post' action="admin.php">
 <table bgcolor='#cccccc'>
   <tr>
     <td>Имя пользователя:</td>
     <td><input type='text' name='username'></td></tr>
   <tr>
     <td>Пароль:</td>
     <td><input type='password' name='passwd'></td></tr>
   <tr>
     <td colspan=2 align='center'>
     <input type='submit' value="Войти"></td></tr>
   <tr>
 </table></form>
<?php
}

function display_admin_menu()
{
?>
<br />
<a href="index.php">Перейти на основной сайт</a><br />
<a href="insert_category_form.php">Добавить новую категорию</a><br />
<a href="insert_book_form.php">Добавить новую книгу</a><br />
<a href="change_password_form.php">Изменить пароль администратора</a><br />
<?php

}

function display_button($target, $image, $alt)
{
  echo "<left><a href=\"$target\"><img src=\"$image".".gif\" 
           alt=\"$alt\" border=0 height = 50 width = 135></a></center>";
}

function display_form_button($image, $alt)
{
  echo "<center><input type = image src=\"images/$image".".gif\" 
           alt=\"$alt\" border=0 height = 50 width = 135></center>";
}

?>
