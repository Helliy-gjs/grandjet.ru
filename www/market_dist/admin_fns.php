<?php
// ���� ���� �������� �������, ������� ������������ � ���������� ��������������
// ��� �������������� ������� �������� "��������".

function display_category_form($category = '')
// ���������� ����� ��� ����� ���������.
// ��� ����� ������������ ��� ���������� � �������������� ���������.
// ��� ���������� ����� ��������� ��������� ������� ��� ����������. � ����������
// $edit ������ �������� false � ����� ��������� � insert_category.php.
// ��� ���������� ���������� � ��������� ��������� � �������� ��������� ������,
// ���������� ���������. ����� ���������� ������������� ������� � ��������� �
// update_category.php. � ���� ������ ����� ��������� ������ �������� ���������.
{
  // ���� ���������� ������������ ���������, ���������� � "������ ��������������"
  $edit = is_array($category);

  // ����������� ����� ������������ ����� ������� HTML-��� � �����������
  // ��������������� PHP-�����������
?>
  <form method='post' 
      action="<?php echo $edit?'edit_category.php':'insert_category.php'; ?>"> 
  <table border=0>
  <tr>
    <td>������������ ���������:</td>
    <td><input type='text' name='catname' size=40 maxlength=40
          value="<?php echo $edit?$category['catname']:''; ?>"></td>
   </tr>
  <tr>
    <td <?php if (!$edit) echo 'colspan=2'; ?> align=center>
      <?php if ($edit) 
         echo '<input type="hidden" name="catid" 
                value="'.$category['catid'].'">';
      ?>
      <input type='submit' 
       value="<?php echo $edit?'��������':'��������'; ?> ���������"></form>
     </td>
     <?php if ($edit)
       // ��������� �������� ������������ ��������� 
       {
          echo '<td>';
          echo '<form method="post" action="delete_category.php">';
          echo '<input type="hidden" name="catid" value="'.$category['catid'].'">';
          echo '<input type="submit" value="������� ���������">';
          echo '</form></td>';
       }
     ?>
  </tr>
  </table>
<?php
}

function display_book_form($book = '')
// ���������� ����� ��� �����.
// ��� ����� �� ������ ������� ����� ��� ���������.
// ����� ����� ����������� ��� ������� � �������������� ���������� � �����.
// ��� ������� ���������� �������� �� �����. � ���������� $edit
// ������� �������� false � ����� ������� �������� insert_book.php.
// ��� ���������� ������ ������� �������� ������, ���������� ������ � �����.
// ����� ��������� ���������� ������ � ������, ���������� � ������ update_book.php.
// ����� ����, ����������� ������ �������� �����.
{
  // ���� ���������� ������������ �����, ������� � "����� ��������������"
  $edit = is_array($book);

// ������� ����� ����� ������������ ����� ������� HTML-���
// � ���������� ��������� PHP-����.
?>
  <form method='post'
        action="<?php echo $edit?'edit_book.php':'insert_book.php';?>">
  <table border="0">
  <tr>
    <td>ISBN:</td>
    <td><input type='text' name='isbn' 
         value="<?php echo $edit?$book['isbn']:''; ?>"></td>
  </tr>
  <tr>
    <td>��������:</td>
    <td><input type='text' name='title' 
         value="<?php echo $edit?$book['title']:''; ?>"></td>
  </tr>
  <tr>
    <td>�����:</td>
    <td><input type='text' name='author' 
         value="<?php echo $edit?$book['author']:''; ?>"></td>
   </tr>
   <tr>
      <td>���������:</td>
      <td><select name='catid'>
      <?php
          // ��������� �� ���� ������ ������ ��������� ���������
          $cat_array=get_categories();
          foreach ($cat_array as $thiscat)
          {
               echo '<option value="';
               echo $thiscat['catid'];
               echo '"';
               // ���� ����� ����������, ��������� �� � ������� ���������
               if ($edit && $thiscat['catid'] == $book['catid'])
                   echo ' selected';
               echo '>'; 
               echo $thiscat['catname'];
               echo "</option>\n"; 
          }
          ?>
          </select>
        </td>
   </tr>
   <tr>
    <td>����:</td>
    <td><input type='text' name='price' 
               value="<?php echo $edit?$book['price']:''; ?>"></td>
   </tr>
   <tr>
     <td>��������:</td>
     <td><textarea rows='3' cols='50' 
          name='description'>
          <?php echo $edit?$book['description']:''; ?>
          </textarea></td>
    </tr>
    <tr>
      <td <?php if (!$edit) echo 'colspan=\'2\''; ?> align="center">
         <?php 
            if ($edit)
             // ���� ��� �������� ����� ISBN, ��� ������ �����
             // � ���� ������ ����������� ������ ����� ISBN
             echo '<input type="hidden" name="oldisbn" 
                    value="'.$book['isbn'].'">';
         ?>
        <input type='submit'
               value="<?php echo $edit?'��������':'��������'; ?> �����">
        </form></td>
        <?php 
           if ($edit)
           {  
             echo '<td>';
             echo '<form method="post" action="delete_book.php">';
             echo '<input type="hidden" name="isbn" 
                    value="'.$book['isbn'].'">';
             echo '<input type="submit" 
                    value="������� �����">';
             echo '</form></td>';
            }
          ?>
         </td>
      </tr>
  </table>
  </form>
<?php
}

function display_password_form()
{
// ������� HTML-����� ��������� ������
?>
   <br />
   <form action="change_password.php" method="post">
   <table width=250 cellpadding=2 cellspacing=0 bgcolor="#cccccc">
   <tr><td>������ ������:</td>
       <td><input type="password" name="old_passwd" size=16 maxlength=16></td>
   </tr>
   <tr><td>����� ������:</td>
       <td><input type="password" name="new_passwd" size=16 maxlength=16></td>
   </tr>
   <tr><td>������������� ������ ������:</td>
       <td><input type="password" name="new_passwd2" size=16 maxlength=16></td>
   </tr>
   <tr><td colspan=2 align="center"><input type="submit" value="�������� ������">
   </td></tr>
   </table>
   <br />
<?php
};

function insert_category($catname)
// ��������� � ���� ������ ����� ���������
{
   $conn = db_connect();

   // ���������, �� ���������� �� ��� ����� ���������
   $query = "select *
             from categories
             where catname='$catname'";
   $result = $conn->query($query);
   if (!$result || $result->num_rows!=0)
     return false;  

   // �������� ����� ��������� 
   $query = "insert into categories values
            ('', '$catname')"; 
   $result = $conn->query($query);
   if (!$result)
     return false;
   else
     return true;
}

function insert_book($isbn, $title, $author, $catid, $price, $description)
// ��������� � ���� ������ ����� �����
{
   $conn = db_connect();

   // ���������, �� ���������� �� ��� ����� �����
   $query = "select *
             from books 
             where isbn='$isbn'";

   $result = $conn->query($query);
   if (!$result || $result->num_rows!=0)
     return false;
 
   // �������� ����� �����
   $query = "insert into books values
            ('$isbn', '$author', '$title', '$catid', $price, '$description')";
  
   $result = $conn->query($query);
   if (!$result)
     return false;
   else
     return true;
}

function update_category($catid, $catname)
// �������� � ���� ������ �������� ��������� � ���������������� catid
{
   $conn = db_connect();

   $query = "update categories
             set catname='$catname'
             where catid='$catid'";
   $result = @$conn->query($query);
   if (!$result)
     return false;
   else
     return true; 
}

function update_book($oldisbn, $isbn, $title, $author, $catid, 
                     $price, $description)
// �������� � ���� ������ ���������� � ����� � $oldisbn
// �� �����, ������� ���������� � ����������
{
   $conn = db_connect();

   $query = "update books
             set isbn='$isbn',
             title ='$title',
             author = '$author',
             catid = '$catid',
             price = '$price',
             description = '$description'
             where isbn='$oldisbn'";

   $result = @$conn->query($query);
   if (!$result)
     return false;
   else
     return true; 
}

function delete_category($catid)
// ������� �� ���� ������ ��������� � ���������������� catid.
// ���� ��������� �������� �����, �� ��� �� ���������
// � ������� ������ �������� false.
{
   $conn = db_connect();
   
   // ���������, ���� �� ����� � ���������, 
   // �� ��������� �������� �������� 
   $query = "select *
             from books
             where catid='$catid'";
   $result = @$conn->query($query);
   if (!$result || @$result->num_rows>0)
     return false;

   $query = "delete from categories 
             where catid='$catid'";
   $result = @$conn->query($query);
   if (!$result)
     return false;
   else
     return true; 
}


function delete_book($isbn)
// ������� �� ���� ������ �����, ���������������� $isbn
{
   $conn = db_connect();

   $query = "delete from books
             where isbn='$isbn'";
   $result = @$conn->query($query);
   if (!$result)
     return false;
   else
     return true;
}

?>
