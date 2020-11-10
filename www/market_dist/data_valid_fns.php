<?php

function filled_out($form_vars)
{
  // Проверить, что каждая переменная имеет значение
  foreach ($form_vars as $key => $value)
  {
     if (!isset($key) || ($value == '')) 
        return false;
  } 
  return true;
}

function valid_email($address)
{
  // Проверить допустимость адреса электронной почты
  if (ereg("^[a-zA-Z0-9_\.\-]+@[a-zA-Z0-9\-]+\.[a-zA-Z0-9\-\.]+$", $address))
    return true;
  else 
    return false;
}

?>
