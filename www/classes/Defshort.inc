<?php
$resu=$user->read_namparams('setMaketPage');
$arridmen=$resu[1];
foreach($arridmen as $value){
	$maket=$value.'-'.$numpage; 
	$YourMakets[$maket]=$sw->allmakets($Site->ids,$maket);
}
//проверка режима ремонта
if(isset($control_mode)){
    echo '<div class="info">';
    include($pathheader.$pathToClasses.'repaire.inc');
    echo '</div>';
}
//var_dump($number_allmakets);
if(is_object($number_allmakets))$idmaket = $number_allmakets->id + 1;
else $idmaket = 1;
$Pth['adm']=array('np'=>$numpage,'uid'=>$uid,'ids'=>$Site->ids,'idm'=>$idmaket,'sp'=>$startpage);
$contentSite['titles'] = $arrmain['titles'];
$contentSite['description']=$arrmain['descr'];
$contentSite['keywords']= explode('>',$arrmain['keywds']);
$contentSite['titles'] = $arrmain['titles'];
$contentSite['description']=$arrmain['descr'];
$contentSite['keywords']= explode('>',$arrmain['keywds']);
if(isset($Pth['adm']))$contentSite['admin']=$Pth['adm'];

foreach ($Owner_site as $key=>$val)$contentSite['owner'][$key]=$val;
$contentSite['owner']['block']=$user->Ownerviewer($arrmain, $Pth,0);

if(isset($ownerdata))$contentSite['admin']['block']=$ownerdata;

if($uid > 0)foreach($user->idUserF($uid) as $key=>$val)$contentSite['user'][$key]=$val;
$contentSite['user']['login']=$user->getLogin();
$contentSite['user']['email']=$user->getEmail();
if($arrmain['owner']->telmain != '')$contentSite['owner']['tel']=$arrmain['owner']->telmain;
else $contentSite['owner']['tel']='+79255053421';
if($arrmain['owner']->email != '')$contentSite['owner']['email']=$arrmain['owner']->email;
else $contentSite['owner']['email']= 'ruslan@grandjet.ru';
if($arrmain['owner']->uradr != '')$contentSite['owner']['adr']=$arrmain['owner']->uradr;
else $contentSite['owner']['adr']= '';
$contentSite['owner']['name']=$arrmain['owner']->name;
$contentSite['user']['block']=$user->Userviewer($arrmain,'',$Pth,0);
$contentSite['manag']['status']=$user->whoareyouhere($user->getMs(),false);
$contentSite['manag']['block']='';
$contentSite['deliv']['block']='<div class="block-footer__delivery delivery-footer">
<div class="block-footer__title">Доставка транспортными компаниями</div>
<div class="block-footer__items"><div class="block-footer__item"><img src="./images/tklogo.png" alt="">
        </div>
    </div>
</div>';
$contentSite['pay']='<div data-da="widgets-footer, first, 680" class="footer__payment">
<img src="./images/paysystems.png" alt="paysystems">
</div>';
$contentSite['widget']='<div class="footer-widgets widgets-footer">
<div class="widgets-footer__column">
    <img src="./images/widgets.jpg" alt="">
</div>
<div class="widgets-footer__column">
    <img src="./images/widgets.jpg" alt="">
</div>
</div>';
$contentSite['copy'] = '<div class="footer__copy"><img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzOAAAABmJLR0QA/wD/AP+gvaeTAAACWUlEQVRIiaXWS29NURQH8F+bMtG0xKD1GlY9Bh6tocSEIcoEX0IiHhMilE5F0yHxASQiIaGKxBfwGiEiaJNOKEm1Jq5rsNdxTo5zb6/bf7Kzz1mPvdZee621d4elMYjD2I8N2BT0acxgCnfxroW1KjGMJ6i3OB5j6H8MrMAEfscCX3EDB6XdrYoxiEO4GTL10BlH11JG1uBpKC1gFD0tONeDK1iU7251s51koZqRQve/2IGPscYzrKwSmgiBz1jfhpEM66VEqeN6mTksxXcBuyqU+zGGl/gRcq+lcPVXyO+WwliL77/IQjZaoXQ8Fm+Ubd9xtELvavCnMsKgPLvKB39Cnn23sVfKuLVSXT0IXk3KwCJ6MRf8ATgXPzdLgv2YD97JCo8zXCw4urbEuxW8M2Jr9QqPxgo7WQoPQ/ZCiT4S9EfwNn42l4ReBX1vC4YaITuWN+Th6S4JZfRVyzDUHWvMd8ZHM3Qsw1BnzL87MRs/5SL9EPNu7WNdzLOdUieArSWh+zE3y7gMWTKcL9G3xfwJzqpO7z75OZ1qYuRSyHzROL1P07xgj8kL9g72yQv2ACaD90u6Ror4p2BJbb0u9a4yjhV2VjW+4UiFXlaHk0XiUHi+qPrw+8KJ52F0AS9wOXhlDOOn1Jp2lpnj4cG09DZoFxvk18S1KoEueQhnsKcNIzulDMu6dsMrfXXB2KLU6ntbMNArnclPeW9reJVn6JJuxloozUlpehhbpLbSHd8jwcuyqyaFa8nHSRHbcU/rz60pTbpIK31sQP6A3ISNQZ+OkT0g3zdb5A8/hMrojAwclgAAAABJRU5ErkJggg=="/>
grandjetstudio copyright 2020
</div>';
$contentSite['soc']='<div class="footer__social social-footer">
<a href="" class="social-footer__item">
    <img src="https://img.icons8.com/cute-clipart/64/000000/facebook-new.png"/>
</a>
<a href="" class="social-footer__item">
    <img src="data:image/png;base64,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"/>
</a>
<a href="" class="social-footer__item">
    <img src="data:image/png;base64,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"/>
</a>
<a href="" class="social-footer__item">
    <img src="data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAADAAAAAwCAYAAABXAvmHAAAABmJLR0QA/wD/AP+gvaeTAAAKMElEQVRoge2Za6xU1RXHf2vvM2ceFy4gUnkpFeHKS8WCgo/0kRYVH4CtQkPSxsbUpom1aVP6pWm16eODWKutbVKVpI1tbYIVqkaEYsRqRUACVKAgRFvkIS953rlzz8zZqx/2PjNz8c6t0CZ+YSUre+7Z5+z5/9f7zIWzclbOyln5KEU+7I0/unXlzYfy8oODcTypK7J5J2oip0QKOefIKUTqyDkl5xS/58g5iFSJnWK1sedX/KpKpK47l7I3Vn0xX9VfXffarRv/LwQWXre8bd9A89I7/YpXOBFAMKoYlJwDSwDrlJw6ojrI5s8aPtODVNRMwqk3glNyqmmU6mODKgfvmbr+a9UzJrDwuuVtuwdF2/eX4hGK4BRECAT8ap0jQrF1TzRb2hE1QBEFAh60C38rsSomxRNIqRPPOV5sSw7O7IuE6YvAsXZ54VhsR+RTR96lFDQl77zGLiXWlBgldo5YUyJNseqIXIrVFKMOqymWFIPD4vctDhPUohinWBSLw0qKQRFVBP1sEg9eeEYeeGj2c9e/1VZalhpEAURQABRUMQhGHUZ9GFn11rbaCJ8oCy8F61yId29h65Rc6u+PFe/B1HsycopNCd6jpkYuuXr1bdt6wxm1ItBpWBC7VBTBAUqIHxRRaG/P8cnrRzHp8iGcO7REnLd9GeoDUqvUOLH7JPvX7uNff95J7WgFiydiFaJ6qEqkjjuBBadFoGrM5LymqAMVUAUVRYBLpw1l7l2TyBdbPv5fJSpEDBozkEFjBjJmzhjevH8Nh17ejVXB4D1jAREBlRktz2m1YY22F7SGU08AAKdMnD6MefdMRgS2r9/Pmud2sm/nEdJKDYsPHaP4+KdRgaKQxFZ9mBRiy+COcxj7hQl8bNoIJt97DVvufYWjq97FqhCRxbcBGNUKZ685cNddv8ld+P55iYZthyICbQNivv6LGcTFiFVPbmbNku0IGdiwhhJr1ce7cRkRmq5BTp0PFwcXzb+Mi75yOWlnwqb5S0gPd2NVUDUoAirpFa/P79XYvV4cPrxDC4cO+6QVH/+KMu2GDuJixNtv7GXj05spoPWeIAG0CSXVh4CGuA4kwHsHGH/HVEbNmcjup7ewa9E6zhk3mEFXXcDQWzs48PgGFAOioAakdbHsdedTQMHVKGqVgksoakLJVRk7ZSgAW57dTEkTii6hqFWK6u8pklDQhKJ2U9CEgksoaDd5TchrlZhuCiQUSBg1ewK2EDFyzgRiqhxcvAmAQdecj5G0h/oy0rv0ngOroDgg8ZUHkOCB9qH9ADixYx8FTUK9BkPDC6X2PGNvuoShUy+k37ABAJT3HuXQ2nfY88wG0iNdRCq8t3QjQ+dM5sCSjeSpkmzbB0B+xACENFhfsyBvWe57JXBwyK+11H0DqOLEF1FQcoUcALnKSd89RUHBiiLqGHH1WC67ewZRMe5xXv/RQ+g/eggXzJrM2w8+z/FXt3Pgty9xeNEqDJBXQcq+2ZpSDiMpinq7K4ROdBoeAApa8c+KA6eIabixpN0YFHBhpHCcd9XFXPqdm0Dg/XU72LN0DeUde7AK/TqGM2z2NAZc2cHY781m14+fovzKNsSATQUwqDT6iEjqm2XIP9caf+8Ebp84UVeu60YE1DkEhzSd0qYVjCiqDqOOeGAbE78xEwTe/f1f2f/U37BOyeOTOd10jD0bt1Gd92nO/fIMRn77Fva8uRN3pIxKGCiarGykhiMK1u973mnpgRLdIQYdgiKaNgjQBRpmFlGG33gttpjn+LqtHFv8Am0IBhcqk2DE94byn16gcvEICtMmMHD2FRz73UocFhHFaU8CAA6bkWiZA72Tu+8+LWk3JanQ5iqU6KJEpYlcmbag/Sgz6MpxAHT+ZQVtUqbEycY9pkxJy+GMMpWlKwEoTB+PkRrW1DBSq4P2BNJwLUUk9Ul92h7QCqL+YcH1KGVtdPpBThyoEg891x+245/0164AIuvIoCIo1ofLjp3+3uGDsaaKUwdkhSIj0CAD4PqY+lsS6EcXaA0kxWjaI4n7ayciITckBfV7bXISkS584fUvPyrGd1RJcWrAhAqlYKRaB98MsScBoa/XlpYEYql4N1LDkPbIgZJ0BvC+EvHePrhwNHHHKNzmf4AGAhLGgUBCxGI6RgLg9u3HSjV4V3u0KiNpE2gJg0zv0msOCKiVKlaqWFPFmAQrSX3fSoI1CVa6sSaBN1b767Nmhb1ur/X7kvoZ+TkzAaitXY8xVYypeZXGS1eWEyIpEnLhtAj4Q6p1zYjUCZikrpFJkOWLoasTmTode/u8+vUMvF+rxHM/j536CbRcJn3+eTIjGfFE6gYMyVsfJ84kiT3wzBI9rWBNAlbwIyhQPQ6P3w933wdfvBPGTYBli5Ed25BUYfR4zM3zkCnTQJXaLx5CTryPkYjm5G18dxZCEkLvDAh48NW6O5stREH8K5MFTOg0W1+Fx34IX1oAk6/y2iQCUO7EPbIQ1q75APhmGkZqKIKoCWPFGSRx5tY6CZtCpQyFEgxsg1pXeO8LJATY/nf46Wa4djZMnA5DRvpmeGAPbFgNy57GHD4KJkJcBiuAK5U8kXLFgw7JLwgGg6IivQxFfRCoqZGaWKkhUQqxwMG9cP4Y6BgH72zyT2ceyLLJHYeXn4CXnoBUoQbUFKoKiUJeMEnwpmuUWzPWv3S5fftD/GczrkHU0aqU9pHEKUaqiA3g8wY2v+43P3ebD6OCgaJASaBovJbCtaKEe4Lme6pp6sBGasSzbwSgtnYDhqwC+Z9e+sqBPgjUMCYDL35dvRS6yzB+OsyYH4AG4HUi4Vqhac2fQiL2mpGI5t6GnToFLZdJnlvum2QYISTMYq2kZQiJqZ4gJ+3EArnwxdXjsOQBmPd9+MwdMGo8bFoKh96CWsV7WQGnkIoPHUsj2bN2pUCuCOMuxs6cC1OmgyrJw4/AiaOIxBi1qDhUHSLpSemtXPVJwLKLnEwiFyyWrW+/Bs/8BGZ+C0ZP8/q/SrmT2i9/jluzHiMxqg4Vh6jzHnC6q9WjrX/YsawgYhJRBp4GiV2vwZNb4LJZcMGV0D4CosLpga6UYf8eWL8afXYpHOuqg5dm8OoQ65afPgGJFhHpN4mwRKHu55pI6AnY+kfY+WSjJ2QhlFWeRKE7aMVBRYM66AqfuxxSAST2Q6G4U1atCebxVjBbJrH84cWtWB6pg8s80UwiS85Tk7l4SsJmz+TEm8xKo5NbAaP14VDCS5KQqXtk2LKfbT1tAgDUji3AsKLHl0UBREYibiYRSmsGPiOceTA7ozmxQyOU8CtsBhwURJcPOZB+ty+IfRKQR9dXOXbkZow8HKYq/0QGImoiURTfAwpN4JutnXXs5lWaNCsyooDWBPfgOe9Ft8j6R8/8HxzNog/MnECBr1IyMyjIxymatkYDC17ISYh3H9uUw9rVy9/lputdinabozUX/9u5eEWi+UXtzyze/mGxnZWzclbOykcn/wEvyw5egRmpIwAAAABJRU5ErkJggg=="/>
</a>
</div>';
//debug($arrmain['style']);
?>