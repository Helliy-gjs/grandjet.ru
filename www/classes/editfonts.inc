<?php
//редактор шрифтов
//show::infosh($all_maket_par->fonts);
$Maket_num_fonts=explode('|',$all_maket_par->fonts);
foreach($Maket_num_fonts as $val){
	$PthGl['fonts'][]=$ew->getallfonts($val);
}
show::infosh($PthGl['fonts']);
echo '<p style="'.$PthGl['fonts'][0].';">Текст обычный '.$PthGl['fonts'][0].'</p>';
echo '<p style="'.$PthGl['fonts'][1].';"><a>Текст ссылок '.$PthGl['fonts'][1].'</a></p>';
echo '<p style="'.$PthGl['fonts'][2].';"><h1>Текст заголовка h1 '.$PthGl['fonts'][2].'</h1></p>';
echo '<p style="'.$PthGl['fonts'][1].';"><h2>Текст заголовка  h2 '.$PthGl['fonts'][1].'</h2></p>';
echo '<p style="'.$PthGl['fonts'][2].';"><h3>Текст заголовка h3 '.$PthGl['fonts'][2].'</h3></p>';
echo '<p style="'.$PthGl['fonts'][1].';"><h4>Текст заголовка  h4 '.$PthGl['fonts'][1].'</h4></p>';
echo '<p style="'.$PthGl['fonts'][2].';"><h5>Текст заголовка h5 '.$PthGl['fonts'][2].'</h5></p>';
echo '<p style="'.$PthGl['fonts'][1].';"><h6>Текст заголовка  h6  '.$PthGl['fonts'][1].'</h6> ';
echo '<div class="menu"><p style="'.$PthGl['fonts'][3].';">Текст пункта меню '.$PthGl['fonts'][3].'</p></div>';
echo '<div class="button"><p style="'.$PthGl['fonts'][4].';">Текст кнопки '.$PthGl['fonts'][4].'</p></div>';
?>