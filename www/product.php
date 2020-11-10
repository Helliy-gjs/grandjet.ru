<?php
//Загрузочная страница сайта
ini_set('display_errors',1);
error_reporting(E_ALL & ~E_NOTICE);
global $inf,$arrmain,$Site,$mode_edit, $pathToClasses,$pathheader, $spisok,$vend, $tabl,$tablepages, $tablenews, $numrecbd,$loz,$hh,$disp;
$clas=array(); 

define('SCRIPT_NAME',    dirname($_SERVER['SCRIPT_NAME']));
define('HTTP_FOLDER',    substr(SCRIPT_NAME,1));
define('HOST_SYSTEM','/bhome/part2/01/ritondel/');
define('HOST_DIST',    HOST_SYSTEM.'/distributive');
define('HOST_MYDOMEN',     HOST_SYSTEM.$_SERVER['HTTP_HOST'].'/www/');
define('HOST_MY',     HOST_SYSTEM.$_SERVER['HTTP_HOST']);
//echo $_SERVER["DOCUMENT_ROOT"].HTTP_FOLDER;
$clas=array();
//header('Content-Type: text/html; charset="utf-8"');
//Загрузка внутрених библиотек
//$pathToClasses = '/classes/';
//$pathheader='.';
$pathToClasses = 'classes/';
$pathheader='';//$_SERVER["DOCUMENT_ROOT"];
if (strstr($_SERVER['HTTP_HOST'],'www')) {
			$_SERVER['HTTP_HOST']=substr($_SERVER['HTTP_HOST'],4);
		}
//$_SERVER['HTTP_HOST']='grandjs.loc';
define('CLASSES', $pathheader.$pathToClasses);
if($arrdom[1] ===  'deltar.ru')include_once($pathheader.$arrdom[0].'/'.$pathToClasses.'autoload.inc');
else include_once(CLASSES.'autoload.inc');
if(file_exists('functions.php'))include_once('functions.php');
//debug($_SERVER['REQUEST_URI']);
if(strstr(trim($_SERVER['REQUEST_URI'],'/'),'api') ){	
	try {
		if(strstr($_GET['q'],'api/users')){
		$api = new UsersApi();
    }
    elseif(strstr($_GET['q'],'api/structure')){
        $api = new StrucsApi();
    }
    elseif(strstr($_GET['q'],'api/elements')){
            $api = new ElemsApi();
		}
	elseif(strstr($_GET['q'],'api/maket')){
		$api = new MaketApi();
	}	
	elseif(strstr($_GET['q'],'api/brends')){
		$api = new brendsApi();
	}	
	elseif(strstr($_GET['q'],'api/news')){
		$api = new NewsApi();
	}
	elseif(strstr($_GET['q'],'api/infos')){
		$api = new infosApi();
	}
	elseif(strstr($_GET['q'],'api/blogs')){
		$api = new blogsApi();
	}
	elseif(strstr($_GET['q'],'api/quiz')){
		$api = new quizApi();
	}
	elseif(strstr($_GET['q'],'api/params')){
		$api = new paramsApi();
	}
	elseif(strstr($_GET['q'],'api/pic')){
		$api = new picApi();
	}
	elseif(strstr($_GET['q'],'api/allmakets')){
		$api = new allmaketsApi();
	}
	elseif(strstr($_GET['q'],'api/allsites')){
		$api = new allsitesApi();
	}	
	elseif(strstr($_GET['q'],'api/pages')){
		$api = new PagesApi();
	}																																															
    echo $api->run();
	} catch (Exception $e) {
	echo json_encode(Array('error' => $e->getMessage()));
	}
	die();
}
//	
$db=Utils::loadbdsite($_SERVER['HTTP_HOST']);
//else  $db = Singleton::getInstance('DB',1);
if(file_exists(CLASSES.'/Begin.inc')) include(CLASSES.'/Begin.inc');
//Расчет рабочих параметров сайта
if(!isset($Pth)) $Pth = array();
$type_access = 'general';
if(file_exists(CLASSES.'/Defmass.inc') && isset($numpage) && $type_access != 'general') include(CLASSES.'/Defmass.inc');
else {
	if(file_exists(CLASSES.'/Defshort.inc')) include(CLASSES.'/Defshort.inc');
}
$glsr = glossary();
//print_r($Pth);
//! Загрузка данных каталога
//!Параметры настройки макета

$YourMakets = $sw->allmakets(1,$disp.'-'.$arrmain['nump']);
$scripts=$Site->script;
$arrloz[0] = 'Категория товара';
$dark = 'dark';
$light = 'light';
$type_site = 'shop';
$email = 'ruslan@grandjet.ru';

$dat1['typesite'] = 'pwa';
$dat2['typesite'] = 'pwa';
$dat4['typesite'] = 'pwa';
$navMenu['typesite'] = 'pwa';
$Scrpt_page = $arrmain['scripts'];	
$Style_pages = $arrmain['style'];
$pgExist = false;
if(!$pgExist){
//!Загрузка персональных данных макета сайта  из верстки
	
if(file_exists(CLASSES.'/personalProdData.inc') && isset($numpage)) include(CLASSES.'/personalProdData.inc');
if(file_exists(CLASSES.'/personalProdMaket.inc') && isset($numpage)) include(CLASSES.'/personalProdMaket.inc');
}
else {	
    //!Преобразование стандартных массивов в данные маета формата верстки	
    $d="SELECT `id`, `Maket`, `scripts`, `flag` ,`type`,`needs` FROM `scripts` WHERE `ids`=^Ni AND `idm`=^Ni";
    $scrs=$db->query($d,$YourMakets[0][11],$YourMakets[0][0]);
        //print_r($scrs);
    if($scrs){	
        foreach($scrs as $val)	{
            if($val->type === 'js')$Scrpt_libs[] = $val->scripts;
            if($val->type === 'css')$Style_libs[] = $val->scripts;
            }
            //print_r($arrmain['style']);
            
            
    
        }
        
        
    }
    //debug($Style_pages);
    
    //!формирование html кода страницы
    ?>
    <!DOCTYPE html>
    <html>
    <head>
    <meta charset="utf-8" />
    <title><?=$arrmain['titles']?></title>
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <link rel="shortcut icon" href="favicon.png" />
    <?php
    
    //!Подключение css окружения
    if(isset($Style_libs) && $pgExist){
        if(is_array($Style_libs)){
            foreach($Style_libs as $value){
                if($value && file_exists($pathheader.'/'.$scripts.'/'.$value.'.css')) echo '<link rel="stylesheet" href="'.$scripts.'/'.$value.'.css" />';
                //else echo $pathheader.'/'.$scripts.'/'.$value.'.css';
            }
        }
    }
    if(isset($Style_pages) && $pgExist){
        if(is_array($Style_pages)){
            foreach($Style_pages as $value){
                if($value != '' && file_exists('css/'.$value.'.css')) echo '<link rel="stylesheet" href="css/'.$value.'.css" />';
                //else echo 'css/'.$value.'.css	';
            }
        }
        echo '</head><body>';
    }
    
    if(!$pgExist){
    //!первая загрузка сайта 
    //первая загрузка окружения	css
    echo '<link rel="stylesheet" href="./css/style.css">
        <link rel="stylesheet" href="./css/main.css">
        <link rel="stylesheet" href="./css/product.css">
        <link rel="stylesheet" href="./css/footer.css">';
    
    echo '<script src="https://kit.fontawesome.com/40fe3b38f8.js" crossorigin="anonymous"></script>';
    echo '</head><body>';
    //первая загрузка сайта из html верстки
    echo 'Первая загрузка Интернет магазин sportshop';
    $contentShop = array('contact' => $contscts,'addcont'=>$contactadd,'logo'=>$contLogo,'top'=>$contenTop,'nav'=>$navMenu,'cat'=>$dat4);
    
    echo show::showShopHeader($Pth,'',$clasShop,$contentShop,$optMenu,$Icons);
?>
<main class="page">
<div class="page__container _container">
        <aside class="page__side">
		<?php		
echo '<div data-da="page__content,last,992" class="page__content-side">';
echo maket::div2Blockstr($Pth,$contentNews,'<a href="'.$hrefnews.'" class="news-side__title side-title">'.$glsr['nw'].'</a>','page__news-side news-side','news-side__items');    
echo maket::div2Blockstr($Pth,$contentOtz,'<a href="'.$hrefozs.'" class="reviews-side__title side-title">'.$glsr['oz'].'</a>','page__reviews-side reviews-side','reviews-side__items');
echo '</div>';
?>          
</aside>                  
<div class="page__content">
<?php
echo show::showformSearches('categories-search',$contentCategories);

echo maket::viewdatapage($breadcrumbs,'breadcrumbs',$Pth,'','ul','__list','__link','');    

echo '<section class="product">
        <h1 class="product__title">BH Fitness G645S<span>Беговая дорожка</span></h1>
        <div class="product__content">
            <div class="product__images images-product">'
            .show::showSwipSliderCard($arrProductCard,'images-product__mainslider','','')
            .show::showSwipSliderCard($arrProductCard,'images-product__subslider','','').'</div>';

?>          
            <div class="product__body body-product">
                <div class="body-product__top">
                    <a href="" class="body-product__compare"><span>Сравнить</span></a>
                    <div class="body-product__stock">в наличии</div>
                </div>
                <div class="body-product__actions actions-product">
                    <div class="actions-product__row">
                        <div class="actions-product__column">
                            <div class="actions-product__price actions-product__price_old">64 990</div>
                            <div class="actions-product__price actions-product__price">62 900</div>
                        </div>
                        <div class="actions-product__column">
                            <div class="actions-product__quantity quantity">
                                <div class="quantity__button_minus"></div>
                                <div class="quantity__input">
                                    <input  autocomplete="off" type="text" name="form[]" value="1">
                                </div>
                                <div class="quantity__button_plus"></div>
                            </div>
                        </div>
                        <div class="actions-product__column">
                            <a href="" class="actions-product__cart">
                                <span>В корзину</span>
                            </a>
                        </div>
                    </div>    
                </div>
                <div class="body-product__include include-product">
                    <div class="include-product__title">В стоимость товара включено:</div>
                    <div class="include-product__items">
                        <div class="include-product__item">
                            <div class="include-product__icon">
                                <img src="../images/icons/asterisk-solid.svg" alt="">
                            </div>
                            <div class="include-product__text">Бесплатная сборка</div>
                        </div>
                        <div class="include-product__item">
                            <div class="include-product__icon">
                                <img src="../images/icons/asterisk-solid.svg" alt="">
                            </div>
                            <div class="include-product__text">Бесплатная доставка</div>
                        </div>
                        <div class="include-product__item">
                            <div class="include-product__icon">
                                <img src="../images/icons/asterisk-solid.svg" alt="">
                            </div>
                            <div class="include-product__text">Гарантия</div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="product__info info-product _tabs">
            <nav class="info-product__nav">
                <div class="info-product__item _tabs-item _active"><span>Описание</span></div>
                <div class="info-product__item _tabs-item"><span>Характеристики</span></div>
            </nav>
            <div class="info-product__body">
                <div class="info-product__block _tabs-block _active">Lorem ipsum dolor sit amet consectetur, adipisicing elit. 
                    Modi, temporibus architecto voluptatibus vel iusto odio reprehenderit omnis explicabo accusamus. Itaque.
                    Modi, temporibus architecto voluptatibus vel iusto odio reprehenderit omnis explicabo accusamus. Itaque.
                    Modi, temporibus architecto voluptatibus vel iusto odio reprehenderit omnis explicabo accusamus. Itaque.
                    Modi, temporibus architecto voluptatibus vel iusto odio reprehenderit omnis explicabo accusamus. Itaque.
                <h3>Рекомендации</h3>
                <p>Lorem ipsum dolor, sit amet consectetur adipisicing elit. Non eaque optio esse consectetur labore velit 
                    autem minus ipsum. Ullam itaque illum quidem. At est nihil error quas ipsa, officia fuga!</p>
                
                <h3>Преимущества</h3>
                <p>Lorem ipsum dolor, sit amet consectetur adipisicing elit. Non eaque optio esse consectetur labore velit 
                    autem minus ipsum. Ullam itaque illum quidem. At est nihil error quas ipsa, officia fuga!</p>
                
                <h3>Недостатки</h3>
                <p>Lorem ipsum dolor, sit amet consectetur adipisicing elit. Non eaque optio esse consectetur labore velit 
                    autem minus ipsum. Ullam itaque illum quidem. At est nihil error quas ipsa, officia fuga!</p>
                </div>
                <div class="info-product__block _tabs-block">
                    <table class="info-product__table">
                        <tr>
                            <td>
                                <div class="info-product__label">Использование</div>
                            </td>
                            <td>
                                <div class="info-product__value">Профессиональное</div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="info-product__label">Тип беговой дооржки</div>
                            </td>
                            <td>
                                <div class="info-product__value">Стационарная</div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="info-product__label">Использование</div>
                            </td>
                            <td>
                                <div class="info-product__value">Профессиональное</div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="info-product__label">Тип беговой дооржки</div>
                            </td>
                            <td>
                                <div class="info-product__value">Стационарная</div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="info-product__label">Использование</div>
                            </td>
                            <td>
                                <div class="info-product__value">Профессиональное</div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="info-product__label">Тип беговой дооржки</div>
                            </td>
                            <td>
                                <div class="info-product__value">Стационарная</div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="info-product__label">Использование</div>
                            </td>
                            <td>
                                <div class="info-product__value">Профессиональное</div>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div class="info-product__label">Тип беговой дооржки</div>
                            </td>
                            <td>
                                <div class="info-product__value">Стационарная</div>
                            </td>
                        </tr>
                    </table>
                </div>
            </div>
        </div>
        <section class="product__same same-products">
            <h2 class="same-products__title">Похожие товары</h2>
            <div class="same-products__items items-products">
                <div class="items-products__column">
                    <div class="item-product">
                        <a href="" class="item-product__image">
                            <img src="./images/runroad.jpg" alt="Теннисный стол. Зеленый">
                        </a>
                        <div class="item-product__body">
                            <a href="" class="item-product__title"><span>BH Fitness G645S</span>
                                Беговая дорожка</a>
                            <div class="item-product__footer">
                                <div>
                                        <a href="" class="item-product__add">
                                            <img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
                                        </a>
                                </div>        
                                <div class="item-product__price">62 000р</div>        
                            </div>     
                        </div>
                        <div class="item-product__hover hover-item-product">
                            <div class="hover-item-product__title">
                                <a><span>BH Fitness G645S</span>
                                Беговая дорожка</a>
                            </div>
                            <div class="hover-item-product__options options-item-product">
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Тип</div>
                                    <div class="options-item-product__value">Электрическая</div> 
                                </div>
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Скорость (км/ч)</div>
                                    <div class="options-item-product__value">22</div> 
                                </div>
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Складывание</div>
                                    <div class="options-item-product__value">Есть</div> 
                                </div> 
                            </div>
                            <div class="hover-item-product__body">
                                <a href="" class="hover-item-product__compare"><span>Сравнить</span></a>
                            </div>
                            <div class="hover-item-product__footer">
                                <div class="hover-item-product__old-price">34 990</div>
                                <a href="" class="hover-item-product__cart hover-item-product__cart_catalog"></a>
                                <div class="hover-item-product__price">33 000</div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="items-products__column">  
                    <div class="item-product">
                        <a href="" class="item-product__image">
                            <img src="./images/runroad.jpg" alt="Теннисный стол. Зеленый">
                        </a>
                        <div class="item-product__body">
                            <a href="" class="item-product__title">Домашний Теннисный стол Donic Indoor</a>
                            <div class="item-product__footer">
                                <div class="item-product__oldprice">64 990р</div>
                                <div>
                                        <a href="" class="item-product__add">
                                            <img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
                                        </a>
                                </div>        
                                <div class="item-product__price">62 000р</div>        
                            </div>     
                        </div>
                        <div class="item-product__hover hover-item-product">
                            <div class="hover-item-product__title">
                                <a><span>BH Fitness G645S</span>
                                Беговая дорожка</a>
                            </div>
                            <div class="hover-item-product__options options-item-product">
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Тип</div>
                                    <div class="options-item-product__value">Электрическая</div> 
                                </div>
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Скорость (км/ч)</div>
                                    <div class="options-item-product__value">22</div> 
                                </div>
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Складывание</div>
                                    <div class="options-item-product__value">Есть</div> 
                                </div> 
                            </div>
                            <div class="hover-item-product__body">
                                <a href="" class="hover-item-product__compare"><span>Сравнить</span></a>
                            </div>
                            <div class="hover-item-product__footer">
                                <div class="hover-item-product__old-price">34 990</div>
                                <a href="" class="hover-item-product__cart hover-item-product__cart_catalog"></a>
                                <div class="hover-item-product__price">33 000</div>
                            </div>
                        </div>
                    </div>
                </div>
                <div class="items-products__column">
                    <div class="item-product">
                    
                        <a href="" class="item-product__image">
                            <img src="./images/runroad.jpg" alt="Теннисный стол. Зеленый">
                        </a>
                        <div class="item-product__body">
                            <a href="" class="item-product__title">Домашний Теннисный стол Donic Indoor</a>
                            <div class="item-product__footer">
                                <div class="item-product__oldprice">64 990р</div>
                                <div>
                                        <a href="" class="item-product__add">
                                            <img style="width: 20px;"src="./images/icons/user-circle-regular.svg" alt="user-header">
                                        </a>
                                </div>        
                                <div class="item-product__price">62 000р</div>        
                            </div>     
                        </div>
                        <div class="item-product__hover hover-item-product">
                            <div class="hover-item-product__title">
                                <a><span>BH Fitness G645S</span>
                                Беговая дорожка</a>
                            </div>
                            <div class="hover-item-product__options options-item-product">
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Тип</div>
                                    <div class="options-item-product__value">Электрическая</div> 
                                </div>
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Скорость (км/ч)</div>
                                    <div class="options-item-product__value">22</div> 
                                </div>
                                <div class="options-item-product__item">
                                    <div class="options-item-product__label">Складывание</div>
                                    <div class="options-item-product__value">Есть</div> 
                                </div> 
                            </div>
                            <div class="hover-item-product__body">
                                <a href="" class="hover-item-product__compare"><span>Сравнить</span></a>
                            </div>
                            <div class="hover-item-product__footer">
                                <div class="hover-item-product__old-price">34 990</div>
                                <a href="" class="hover-item-product__cart hover-item-product__cart_catalog"></a>
                                <div class="hover-item-product__price">33 000</div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </section>
    </section>
</div>  
</div>
<?php
echo maket::div3Blockstr($Pth,$contentInfo.$contentHelp,'page__info-menu info-menu','','page__info-menu info-menu','info-menu__body');
echo '<footer class="footer">'.$contentFooter.'</footer>';
?>
</main>
<?php
    }
else {
        
	if(file_exists(CLASSES.'/showMainProdPage.inc')) include(CLASSES.'/showMainProdPage.inc');
    //загрузка js	
        if($pgExist && file_exists(CLASSES.'/Jscripts.inc'))include(CLASSES.'/Jscripts.inc');
}  
?>
<script src="./scripts/swiper.min.js" type="text/javascript"></script>
<script src="./scripts/script.min.js" type="text/javascript"></script>
</body>
</html>