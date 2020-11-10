<?php
function calculate_shipping_cost()
{
  // ѕоскольку доставка осуществл€етс€ по всему миру 
  // посредством телепортировани€, стоимость доставки фиксирована
  return 20.00;
}

function get_categories()
{
   // Ёапросить в базе данных список категорий
   $conn = db_connect();
   $query = 'select id as catid, name as catname
             from structure as categories
			 where typeF = 1'; 
   $result = @$conn->query($query);
   if (!$result)
     return false;
   $num_cats = $result->num_rows;
   if ($num_cats == 0)
      return false;  
   $result = db_result_to_array($result);
   
   return $result; 
}

function get_category_name($catid)
{
   // «апросить в базе данных им€ категории дл€ данного идентификатора категории
   $catid = intval($catid);
   $conn = db_connect();
   $query = "select name as catname, id as catid
             from structure as categories
             where id = $catid";
   $result = $conn->query($query);
   if (!$result)
     return false;
   $num_cats = $result->num_rows;
   if ($num_cats == 0)
     return false;
   $row = $result->fetch_object();
   return $row->catname;
}

function get_books($catid)
{
   // ¬ыполн€ет запрос в базу данных книг определенной категории
   if (!$catid || $catid=='')
     return false;
   
   $conn = db_connect();
   $query = "select books.id as catid, codeGJS as isbn, vendor as author, name as title, art, price from elements as books, `type-elements` as t2 where t2.tid=$catid and t2.eid = books.id";
   $result = @$conn->query($query);
   if (!$result)
     return false;
   $num_books = @$result->num_rows;
   if ($num_books ==0)
      return false;
   $result = db_result_to_array($result);
    
   return $result;
}

function get_book_details($isbn)
{
  // ¬ыполн€ет запрос в базу данных детальной информации о книге
  if (!$isbn || $isbn=='')
     return false;

   $conn = db_connect();
   $query = "select books.id as catid, codeGJS as isbn, vendor as author, name as title, art, price from elements as books where codeGJS ='$isbn'";
   $result = @$conn->query($query);
   
   if (!$result)
     return false;
   $result = @$result->fetch_assoc();
   
   return $result;
}

function calculate_price($cart)
{
  // ¬ычисл€ет общую стоимость всех элементов тележки
  $price = 0.0;
  if(is_array($cart))
  {
    $conn = db_connect();
    foreach($cart as $isbn => $qty)
    {  
      $query = "select price from elements as books where codeGJS='$isbn'";
      $result = $conn->query($query);
      if ($result)
      {
        $item = $result->fetch_object();
        $item_price = $item->price;
        $price +=$item_price*$qty;
      }
    }
  }
  return $price;
}

function calculate_items($cart)
{
  // ѕодсчитывает общее количество элементов в тележке
  $items = 0;
  if(is_array($cart))
  {
    $items=array_sum($cart);
  }
  return $items;
}

?>
