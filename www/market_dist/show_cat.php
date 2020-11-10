<?php
define('HOST_ROOT',     dirname($_SERVER['SCRIPT_FILENAME']).'/');
define('HTTP_FOLDER',    dirname($_SERVER['SCRIPT_NAME']));
define('SYS_HTTP',        'http://'.$_SERVER['HTTP_HOST'].(substr(HTTP_FOLDER,-1)=='/'?substr(HTTP_FOLDER,0,-1):HTTP_FOLDER));
  //require ('book_sc_fns.php');
  // Для покупательской тележки необходимо запустить сеанс
  if (strstr(SYS_HTTP,'localhost')) {
//echo 'Работа с локальным сервером';echo "<BR>";
	//$array=fgets($F,999);
	//$pathToClasses = $array;
	//$array=fgets($F,999);
	//$pathheader=$array;
	$pathToClasses ='Z:/home/localhost/www/CorpaZona/classes/';
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	//fclose($F);
	include_once(trim($pathToClasses).'autoload.inc');
	//echo trim($pathToClasses).'autoload.inc';echo "<BR>";
	//echo $pathheader;
	session_start();
		}
else {		
//echo 'Работа с удаленным сервером';echo "<BR>";
	$pathToClasses = '/classes/';
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	include($pathheader.$pathToClasses.'autoload.inc');
	//echo $pathToClasses.'autoload.inc';
	//require (HOST_ROOT.'book/book_sc_fns.php');
	//echo $pathheader.'/classes/autoload.inc';echo "<BR>";
	}
require (HOST_ROOT.'book/book_sc_fns.php');
  
  session_start();
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<?php
		$PageM= new Page(1);
		echo '<head>';
		echo '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
		echo '<title>'.$PageM->MainAr['title'].'</title>';
		echo '<link rel="stylesheet" type="text/css" href=".'.$PageM->MainAr['hrefstyle'].'" /></head>';
  
  $catid = $_GET['catid'];
  $name = get_category_name($catid);
 
  //do_html_header($name);

  // Извлечь из базы данных информацию о книге
  $book_array = get_books($catid);
	$ew->Showobjtype($book_array);
  display_books($book_array);
 
  // Если пользователь вошел в систему как администратор, вывести 
  // ссылки на добавление и удаление ссылок на книги
  if(isset($_SESSION['admin_user']))
  {
    display_button('http://localhost/grandjetshop/index.php', 'continue', 'Продолжить покупки');
    display_button('admin.php', 'admin-menu', 'Меню администрирования');
    display_button("edit_category_form.php?catid=$catid", 
     'edit-category', 'Редактировать категорию');
  }
  else
    display_button('../index.php', 'continue-shopping', 'Продолжить покупки');
  
  do_html_footer();
?>
