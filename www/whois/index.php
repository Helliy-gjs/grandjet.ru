<?
set_time_limit(0);
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
require_once($pathheader.$pathToClasses."whois.inc");
?>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Настройки</title>
<title>скрипт проверки занятости домена - пример использования</title>
</head>
<body>
<form method="post">
Домен: <input type="text" name="domain"><br>
<input type="checkbox" name="TLD[]" value=".ru" id="l1"><label for="l1">.RU</label><br>
<input type="checkbox" name="TLD[]" value=".info" id="l2"><label for="l2">.INFO</label><br>
<input type="checkbox" name="TLD[]" value=".org" id="l3"><label for="l3">.ORG</label><br>
<input type="checkbox" name="TLD[]" value=".com" id="l4"><label for="l4">.COM</label><br>
<input type="checkbox" name="TLD[]" value=".ua" id="l5"><label for="l5">.UA</label><br>
<input type="submit" value="Проверить">
</form>
<hr>
<?
if(isset($_POST["domain"]) && strlen($_POST["domain"])>0 && isset($_POST["TLD"]) && is_array($_POST["TLD"]))
{
$target=$_POST["domain"];
$whois=new whois();
foreach($_POST['TLD'] AS $tldz)
{
echo($target.$tldz." - ");
$whois->zonelookup($target.$tldz);
if($whois->ERROR==0)
{
if(is_array($whois->RAWINFO) && count($whois->RAWINFO)>7 && $whois->FOUND==1)
{
echo("занят");
}else
{
echo("свободен");
}
}else
{
echo("ошибка запроса");
}
echo("<br>");
}
}
?>
<hr>
<center>Copyright © 2004-2005 by <a href="/http://youon.ru/";>YouON.RU</a></center>
</body>
</html>
</body>
</html>
