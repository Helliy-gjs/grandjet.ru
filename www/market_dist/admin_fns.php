<?php
// Этот файл содержит функции, которые используются в интерфейсе администратора
// для покупательской тележки магазина "Буквофил".

function display_category_form($category = '')
// Отображает форму для ввода категории.
// Эта форма используется для добавления и редактирования категорий.
// Для добавления новой категории вызывайте функцию без параметров. В результате
// $edit примет значение false и форма обратится к insert_category.php.
// Для обновления информации о категории передайте в качестве параметра массив,
// содержащий категорию. Форма заполнится существующими данными и обратится к
// update_category.php. В этом случае также добавится кнопка удаления категории.
{
  // Если передается существующая категория, продолжить в "режиме редактирования"
  $edit = is_array($category);

  // Большинство формы представляет собой простой HTML-код с несколькими
  // дополнительными PHP-операторами
?>
  <form method='post' 
      action="<?php echo $edit?'edit_category.php':'insert_category.php'; ?>"> 
  <table border=0>
  <tr>
    <td>Наименование категории:</td>
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
       value="<?php echo $edit?'Обновить':'Добавить'; ?> категорию"></form>
     </td>
     <?php if ($edit)
       // Разрешить удаление существующих категорий 
       {
          echo '<td>';
          echo '<form method="post" action="delete_category.php">';
          echo '<input type="hidden" name="catid" value="'.$category['catid'].'">';
          echo '<input type="submit" value="Удалить категорию">';
          echo '</form></td>';
       }
     ?>
  </tr>
  </table>
<?php
}

function display_book_form($book = '')
// Отображает форму для книги.
// Эта форма во многом подобна форме для категорий.
// Форма может применяться для вставки и редактирования информации о книге.
// Для вставки передавать параметр не нужно. В результате $edit
// получит значение false и форма вызовет сценарий insert_book.php.
// Для обновления данных следует передать массив, содержащий данные о книге.
// Форма отобразит предыдущие данные и кнопку, приводящую к вызову update_book.php.
// Кроме того, добавляется кнопка удаления книги.
{
  // Если передается существующая книга, перейти в "режим редактирования"
  $edit = is_array($book);

// Большая часть формы представляет собой простой HTML-код
// с небольшими вставками PHP-кода.
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
    <td>Название:</td>
    <td><input type='text' name='title' 
         value="<?php echo $edit?$book['title']:''; ?>"></td>
  </tr>
  <tr>
    <td>Автор:</td>
    <td><input type='text' name='author' 
         value="<?php echo $edit?$book['author']:''; ?>"></td>
   </tr>
   <tr>
      <td>Категория:</td>
      <td><select name='catid'>
      <?php
          // Прочитать из базы данных список возможных категорий
          $cat_array=get_categories();
          foreach ($cat_array as $thiscat)
          {
               echo '<option value="';
               echo $thiscat['catid'];
               echo '"';
               // Если книга существует, поместить ее в текущую категорию
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
    <td>Цена:</td>
    <td><input type='text' name='price' 
               value="<?php echo $edit?$book['price']:''; ?>"></td>
   </tr>
   <tr>
     <td>Описание:</td>
     <td><textarea rows='3' cols='50' 
          name='description'>
          <?php echo $edit?$book['description']:''; ?>
          </textarea></td>
    </tr>
    <tr>
      <td <?php if (!$edit) echo 'colspan=\'2\''; ?> align="center">
         <?php 
            if ($edit)
             // Если был обновлен номер ISBN, для поиска книги
             // в базе данных понадобится старый номер ISBN
             echo '<input type="hidden" name="oldisbn" 
                    value="'.$book['isbn'].'">';
         ?>
        <input type='submit'
               value="<?php echo $edit?'Обновить':'Добавить'; ?> книгу">
        </form></td>
        <?php 
           if ($edit)
           {  
             echo '<td>';
             echo '<form method="post" action="delete_book.php">';
             echo '<input type="hidden" name="isbn" 
                    value="'.$book['isbn'].'">';
             echo '<input type="submit" 
                    value="Удалить книгу">';
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
// Выводит HTML-форму изменения пароля
?>
   <br />
   <form action="change_password.php" method="post">
   <table width=250 cellpadding=2 cellspacing=0 bgcolor="#cccccc">
   <tr><td>Старый пароль:</td>
       <td><input type="password" name="old_passwd" size=16 maxlength=16></td>
   </tr>
   <tr><td>Новый пароль:</td>
       <td><input type="password" name="new_passwd" size=16 maxlength=16></td>
   </tr>
   <tr><td>Подтверждение нового пароля:</td>
       <td><input type="password" name="new_passwd2" size=16 maxlength=16></td>
   </tr>
   <tr><td colspan=2 align="center"><input type="submit" value="Изменить пароль">
   </td></tr>
   </table>
   <br />
<?php
};

function insert_category($catname)
// Добавляет в базу данных новую категорию
{
   $conn = db_connect();

   // Проверить, не существует ли уже такая категория
   $query = "select *
             from categories
             where catname='$catname'";
   $result = $conn->query($query);
   if (!$result || $result->num_rows!=0)
     return false;  

   // Добавить новую категорию 
   $query = "insert into categories values
            ('', '$catname')"; 
   $result = $conn->query($query);
   if (!$result)
     return false;
   else
     return true;
}

function insert_book($isbn, $title, $author, $catid, $price, $description)
// Добавляет в базу данных новую книгу
{
   $conn = db_connect();

   // Проверить, не существует ли уже такая книга
   $query = "select *
             from books 
             where isbn='$isbn'";

   $result = $conn->query($query);
   if (!$result || $result->num_rows!=0)
     return false;
 
   // Добавить новую книгу
   $query = "insert into books values
            ('$isbn', '$author', '$title', '$catid', $price, '$description')";
  
   $result = $conn->query($query);
   if (!$result)
     return false;
   else
     return true;
}

function update_category($catid, $catname)
// Изменяет в базе данных название категории с интентификатором catid
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
// Изменяет в базе данных информацию о книге с $oldisbn
// на новую, которая передается в параметрах
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
// Удаляет из базы данных категорию с интентификатором catid.
// Если категория содержит книги, то она не удаляется
// и функция вернет значение false.
{
   $conn = db_connect();
   
   // Проверить, есть ли книги в категории, 
   // во избежание аномалий удаления 
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
// Удаляет из базы данных книгу, идентифицируемую $isbn
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
