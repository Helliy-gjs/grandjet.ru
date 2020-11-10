<?php
$conn=mysql_connect("localhost:3306","grandjetUser","aere");
if (!conn)
{
echo "Не могу подключиться к серверу MySQL MySQL";
echo "ERROR ".mysql_errrno()." ".mysql_error()."/n";
exit;
}
else 
{
echo "Успешное подключение к базе данных";
echo "<BR>";
}
$db="grandjetShop";
mysql_select_db($db);
$file="./menu.csv";
$F=fopen($file,"r");
if ($F) 
{
echo "Файл открыт $file";
echo "<BR>";
$a="structure";

set_time_limit(1000);
$array=fgetcsv($F,128,';');
for($i=0;$array=fgetcsv($F,128,';'); $i++)
{

$z="INSERT INTO `structure` (`pid`, `name`, `typeF`,`constrF`,`ms`,`numEl`) VALUES ('$array[1]','$array[2]','$array[3]','$array[4]','$array[5]','$array[6]');";
if ($array[2]=="0"||$array[2]=="1"||$array[2]=="") {
	echo "i=".$i."-".$array[2];
	echo '<br/>';
	}
	else $sql=mysql_query($z);
//$query[] = "INSERT INTO `structure` (`pid`, `name`, `typeF`) VALUES ('$array[0]','$array[1]','$array[2]')";
//echo "<BR>";
//$j=count($array);

}
fclose($F);
}
else
echo "Ошибка открытия файла";
?>