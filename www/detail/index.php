<?php
global $pathToClasses;
$pathToClasses = '../classes/';
include_once($pathToClasses.'autoload.inc');
$eid = 0;
$ok = 0;
if(isset($_GET['eid']))
	$eid = $_GET['eid'];
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ru" lang="ru" dir="ltr">
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
		<title>Описание товара</title>
		<link rel="stylesheet" type="text/css" href="/images/detailStyle.css" />  
		<script src="/scripts/tube.js" type="text/javascript"></script>
	</head>
	<body>
	<?php 
		if($eid != 0) {
			$ew = Singleton::getInstance('ElementsW');
			$el = $ew->getElement($eid);
			if($el !== null) {
				echo '<div class="head">'.$el['art'].' - <b>'.$el['name'].'</b><a id="close" href="#" onclick="self.close();">X</a></div>
				<table>
					<tr class="s0">
						<td class="c1">Описание:</td>
						<td class="c2">'.$el['desc'].'</td
					</tr>
					<tr class="s1">
						<td class="c1">Стоимость:</td>
						<td class="c2">'.$el['price'].' р.</td>
					</tr>
				</table>';
				$ok = 1;
			} 
		} 
		if(!$ok) {
			echo 'нет такого товара';
		}
	?>		
	</body>
</html>