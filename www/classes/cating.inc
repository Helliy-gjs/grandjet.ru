<?php
echo '<section>';
if ($poisk<>'' && $arrmain['typmen'][5]<> 'nfb') {
	if ($vend=='all') $vend='';
	//5
	echo '<div style="clear: both;" class="s10">';
		$a=$ew->viewer($ew->getlookfor($poisk,$vend),$sort=1,$vend);
	echo '</div>';// s5	
		}
else{
	Maket::divclass('Container-'.$arrmain['idmen'][0],$Pth); 
		for ($m=0;$m<count($arrmain['levmen']);$m++) {
			if ($arrmain['levmen'][$m]>0 && $arrmain['levmen'][$m]!='') {
			//if ($a_link<>'') echo $a_link['levmen'][$m];
			Maket::divclass('Cataloug-'.$arrmain['idmen'][0],$Pth); 
			echo '<a class="zag" name="z'.$m.'">'.$ew->getnameSection($arrmain['levmen'][$m]).'</a>';	
			$menuleft[$m] = new MENU($arrmain['levmen'][$m],$arrmain['typmen'][$m],$Site->ids,$PageM->MainAr['hrefp'].'?np='.$numpage,$tabl,'', $uid,0);
			echo '</div>';//echo '</td></tr>';
		}
	}	
	echo '</div>';
	//echo '</div>';
	echo '</section>';
}		