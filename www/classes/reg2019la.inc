<?php
//файл относится к загрузке верхней части сайта header
//определяется режим загрузки лого и баннера	
//show::infosh($arrmain);
//echo $type_access;
//флаг загрузка хедера
	
$img=$arrmain['clas']['img'].$arrmain['namep'][0];
$clas_head=array('user','logo','serv');
$arr_head=array($ownerdata,$arrmain,$service);
Maket::divclass($Maks_Page[1],$Pth,'background-image: url('.$img.');',' grid','header');
	Maket::divclass($Maks_Page[8],$Pth);
		Maket::divclass('header_land',$Pth);
			$nLast=Maket::showheaderland($Pth,$clas_head,$arr_head,'logo');
			
		echo '</div>';
	echo '</div>';
	Maket::divclass($Maks_Page[8],$Pth);
		Maket::divclass('advers_land',$Pth);
			if($arrmain['loz'][0]===''){
				Maket::showlogo($clas_head[$nLast],$arr_head[$nLast],$Pth,0);
			}
			
			if (is_array($arrmain['link']) && isset($arrmain['link']['namep'][0]) && $type_access=='local') echo Maket::divclasstr('edit',$Pth).$arrmain['link']['namep'][0]; 
			echo '</div>';
			echo '</div>';
			echo '</header>';	
		echo '</div>';			
			

?>