<?php

function db_connect()
{
   $result = new mysqli('baze.deltar.ru:63917', 'gjs_deltar_ru', 'ittBudB5', 'deltar_ru');
   if (!$result)
      return false;
   return $result;
}

function db_result_to_array($result)
{
   $res_array = array();

   for ($count = 0; $row = $result->fetch_assoc(); $count++)
     $res_array[$count] = $row;

   return $res_array;
}

?>
