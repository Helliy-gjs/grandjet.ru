<?php
$pathToClasses = '/classes/';
$pathheader=$_SERVER["DOCUMENT_ROOT"];
define('CLASSES', $pathheader.$pathToClasses);
include_once(CLASSES.'autoload.inc');
$db=Utils::loadbdsite($_SERVER['HTTP_HOST']);
echo 'ШАГ: 2. Создаем таблицы пустой базы данных... <br>';

//Структура таблицы `Allsites`-- Создание: Мар 21 2019 г., 13:38
$query[] = "DROP TABLE IF EXISTS `allsites`;";
$query[] = "CREATE TABLE `allsites` (
  `keyid` int(10) NOT NULL auto_increment,
  `ids` int(10) NOT NULL default '1',
  `uid` int(6) NOT NULL,
  `domen` varchar(50) NOT NULL,
  `nmpage` varchar(20) NOT NULL,
  `types` int(10) NOT NULL,
  `strucs` int(10) NOT NULL,
  `appoint` int(10) NOT NULL,
  `css` varchar(50) NOT NULL,
  `script` varchar(50) NOT NULL,
  `images` varchar(100) NOT NULL,
  `passwad` varchar(100) NOT NULL,
  `logad` varchar(50) NOT NULL,
  `bd` varchar(200) NOT NULL,
  `host` varchar(100) NOT NULL,
  `port` int(6) NOT NULL,
  `pages` varchar(25) NOT NULL,
  `news` varchar(25) NOT NULL,
  `element` varchar(25) NOT NULL,
  `structure` varchar(25) NOT NULL,
  `desc_site` varchar(250) NOT NULL,
  PRIMARY KEY  (`keyid`),
  UNIQUE KEY `ids` (`ids`),
  UNIQUE KEY `domen` (`domen`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";



// Структура таблицы макетов сайта-`allmakets`-- Создание: Мар 15 2019 г., 17:40
$query[] = "DROP TABLE IF EXISTS `allmakets`;";
$query[] = "CREATE TABLE IF NOT EXISTS`allmakets` (
  `id` int(12) NOT NULL,
  `Maket` varchar(50) NOT NULL,
  `styles` text,
  `flex` text,
  `grid` text,
  `numparams` varchar(200) NOT NULL,
  `fonts` varchar(200) NOT NULL,
  `video` text NOT NULL,
  `effects` varchar(200) NOT NULL,
  `scripts` text NOT NULL,
  `desc` text NOT NULL,
  `ids` int(12) NOT NULL,
  `forms` varchar(50) NOT NULL,
  `author_mak` int(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

$query[] ="INSERT INTO `allmakets` (`id`, `Maket`, `styles`, `flex`, `grid`, `numparams`, `fonts`, `video`, `effects`, `scripts`, `desc`, `ids`, `forms`, `author_mak`) VALUES
(0, 'Maket', 'Основной|Регистрация|Авторизация|Восстановление|Пользовательский|', 'display|flex-direction|flex-wrap|flex-flow|order|flex-grow|flex-shrink|flex-basis|justify-content|align-items|align-self|align-items|align-content', 'display|grid-template-columns|grid-template-rows|grid-auto-rows|grid-auto-columns|grid-column-start| grid-column-end|grid-row-start|grid-row-end| grid-column-gap|grid-row-gap|grid-area|grid-cell', 'Pics|Sizes|Scale|Transparent|Transition|Grid|Bootstr', 'Текст|Ссылки|Заголовки|Меню|Лозунги|', 'Источник|Формат|Размер|', 'Тень|Скругления|Исчезновение|Анимация|', 'Скрипт1|Скрипт2|Скрипт3|Скрипт4|', '|Заголовки в таблице Allmakerts|type_access', 0, 'Форма|Форма|Форма|Форма|Форма|Форма|Форма|Форма', 1);";
// Структура таблицы `block` Создание: Мар 15 2019 г., 17:40

$query[] = "DROP TABLE IF EXISTS `block`;";
$query[] = "CREATE TABLE IF NOT EXISTS `block` (
  `ip` char(15) NOT NULL,
  `errors` tinyint(3) unsigned default NULL,
  `time` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  PRIMARY KEY  (`ip`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

$query[] = "DROP TABLE IF EXISTS `brends`;";
$query[] = "CREATE TABLE IF NOT EXISTS `brends` (
  `id` int(19) UNSIGNED NOT NULL,
  `name` varchar(255) DEFAULT NULL,
  `alias` varchar(255) DEFAULT NULL,
  `img` varchar(255) DEFAULT NULL,
  `description` text NOT NULL,
  `idauthor` int(9),
  `ids` int(9),
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// Структура таблицы `config` конфигурации сайта 

$query[] = "DROP TABLE IF EXISTS `configs`;";
$query[] = "CREATE TABLE IF NOT EXISTS `configs` (
  `id` int(9) NOT NULL,
  `name` varchar(30) NOT NULL,
  `current_idm` int(9) NOT NULL,
  `current_blog` int(9) NOT NULL,
  `current_cat` int(9) NOT NULL,
  `current_gal` int(9) NOT NULL,
  `current_news` int(9) NOT NULL,
  `current_type` smallint(3) NOT NULL,
  `current_str` smallint(3) NOT NULL,
  `current_app` smallint(3) NOT NULL,
  `current_host` smallint(3) NOT NULL,
  `current_tarif` smallint(3) NOT NULL,
  `max_sites` mediumint(5) NOT NULL,
  `max_pages` mediumint(5) NOT NULL,
  `max_makets` mediumint(5) NOT NULL,
  `max_pics` int(9) NOT NULL,
  `max_scripts` mediumint(5) NOT NULL,
  `max_styles` mediumint(5) NOT NULL,
  `curent_mode` smallint(3) NOT NULL,
  `topogy` text NOT NULL,
  `configm` mediumint(5) NOT NULL,
  `configp` mediumint(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";


// Структура таблицы `config` конфигурации макета страницы 
$query[] = "DROP TABLE IF EXISTS `configm`;";
$query[] = "CREATE TABLE IF NOT EXISTS `configm` (
  `id` varchar(9) NOT NULL,
  `name` varchar(30) NOT NULL,
  `current_typ` varchar(70) NOT NULL,
  `curent idmen` varchar(10) NOT NULL,
  `current_level` varchar(30) NOT NULL,
  `current_access` varchar(10) NOT NULL,
  `current_header` varchar(10) NOT NULL,
  `current_wrapper` varchar(10) NOT NULL,
  `current_footer` varchar(10) NOT NULL,
  `current_galery` varchar(10) NOT NULL,
  `current_slider` varchar(10) NOT NULL,
  `bootstrap` varchar(10) NOT NULL,
  `smartgrid` varchar(10) NOT NULL,
  `jquery` varchar(10) NOT NULL,
  `framework` varchar(10) NOT NULL,
  `current_ids` int(9) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// Структура таблицы `config` конфигурации контент страницы 

$query[] = "DROP TABLE IF EXISTS `configp`;";
$query[] = "CREATE TABLE IF NOT EXISTS `configp` (
  `id` int(11) NOT NULL auto_increment,
  `name` varchar(30) NOT NULL,
  `sznames` tinyint(2) NOT NULL,
  `szpats` tinyint(3) NOT NULL,
  `szlozs` tinyint(3) NOT NULL,
  `szbuttons` tinyint(3) NOT NULL,
  `szbutgrp` tinyint(3) NOT NULL,
  `szconts` tinyint(3) NOT NULL,
  `szcontgrp` tinyint(3) NOT NULL,
  `szlists` tinyint(3) NOT NULL,
  `szlistgrp` tinyint(3) NOT NULL,
  `szimg` tinyint(3) NOT NULL,
  `szimggrp` tinyint(3) NOT NULL,
  `szimgbut` tinyint(3) NOT NULL,
  `szimgbutgrp` tinyint(3) NOT NULL,
  `szfoots` tinyint(3) NOT NULL,
  `szlevel` tinyint(3) NOT NULL,
  `szimgtexts` tinyint(3) NOT NULL,
  `szimgtxtgrp` tinyint(3) NOT NULL,
  `szstyles` tinyint(3) NOT NULL,
  `szscrpt` tinyint(3) NOT NULL,
  `szsites` tinyint(3) NOT NULL,
  `szusers` int(9) NOT NULL,
  `szpics` int(9) NOT NULL,
  `ids` int(6) NOT NULL,
  `np` int(11) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";

$query[] = "INSERT INTO `configp` (`id`, `name`, `sznames`, `szpats`, `szlozs`, `szbuttons`, `szbutgrp`, `szconts`, `szcontgrp`, `szlists`, `szlistgrp`, `szimg`, `szimggrp`, `szimgbut`, `szimgbutgrp`, `szfoots`, `szlevel`, `szimgtexts`, `szimgtxtgrp`, `szstyles`, `szscrpt`, `szsites`, `szusers`, `szpics`, `ids`, `np`) VALUES
(1, 'standart', 3, 5, 10, 8, 3, 6, 10, 12, 3, 6, 3, 4, 3, 5, 5, 5, 3, 3, 3, 3, 1000, 0, 0, 0),
(2, 'minimum', 2, 1, 3, 5, 2, 4, 6, 10, 2, 4, 2, 2, 2, 3, 1, 3, 3, 1, 1, 1, 100, 200, 0, 0),
(3, 'large', 3, 10, 16, 10, 5, 10, 5, 16, 5, 10, 5, 6, 4, 7, 10, 10, 10, 6, 6, 5, 10000, 1000, 0, 0),
(4, 'unlimit', 4, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 100000, 0, 1, 1),
(5, 'customers', 4, 4, 4, 4, 4, 4, 6, 8, 2, 8, 2, 6, 2, 5, 6, 6, 4, 2, 2, 5, 100, 50, 0, 0);";


// Структура таблицы валют `currency` Мар 15 2019 г., 17:40
$query[] = "DROP TABLE IF EXISTS `currency`;";
$query[] = "CREATE TABLE  IF NOT EXISTS `currency` (
  `id` tinyint(3) NOT NULL,
  `name` varchar(10) NOT NULL,
  `code` varchar(3) NOT NULL,
  `symbol_left` varchar(1) NOT NULL,
  `symbol_right` varchar(20) NOT NULL,
  `value` float NOT NULL,
  `base` int(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// Структура таблицы `customers` Мар 15 2019 г., 17:40

$query[] = "DROP TABLE IF EXISTS `customers`;";
$query[] = "CREATE TABLE  IF NOT EXISTS `customers` (
  `keyid` int(10)   NOT NULL auto_increment,
  `customerid` int(10) UNSIGNED ,
  `name` char(60) NOT NULL,
  `address` char(80) NOT NULL DEFAULT 'адрес',
  `city` char(30) NOT NULL DEFAULT 'г.',
  `state` char(20) DEFAULT 'область',
  `zip` char(10) DEFAULT 'индекс',
  `country` char(20) NOT NULL DEFAULT 'страна',
  `uradr` varchar(80) DEFAULT NULL,
  `telmain` varchar(30) DEFAULT NULL,
  `cinn` varchar(10) DEFAULT '',
  `ckpp` varchar(9) DEFAULT '',
  `crs` varchar(20) DEFAULT 'РС',
  `cbik` varchar(9) DEFAULT 'БИК',
  `cbank` varchar(80) DEFAULT 'Банк',
  `cks` varchar(20) DEFAULT 'КС',
  `tels` varchar(30) DEFAULT NULL,
  `fax` varchar(300) DEFAULT NULL,
  `email` varchar(50) DEFAULT NULL,
  `icq` varchar(300) DEFAULT NULL,
  `userid` int(9) DEFAULT NULL,
  `cfio` varchar(50) DEFAULT NULL,
  `hosting` int(2) DEFAULT NULL,
  PRIMARY KEY  (`keyid`),
  UNIQUE KEY (`customerid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";

// Структура таблицы `cust_choice` Создание: Мар 15 2019 г., 17:40


$query[] = "DROP TABLE IF EXISTS `cust_choice`;";
$query[] = "CREATE TABLE IF NOT EXISTS `cust_choice` (
  `customerid` int(5) NOT NULL,
  `eid` int(6) NOT NULL,
  PRIMARY KEY  (`customerid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// Структура таблицы `elemarch` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `elemarch`;";
$query[] = "CREATE TABLE IF NOT EXISTS `elemarch` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `codeGJS` int(10) default NULL,
  `name` varchar(255) NOT NULL,
  `desc` text,
  `art` varchar(50) default NULL,
  `vendor` varchar(255) default NULL,
  `price` int(10) unsigned default NULL,
  `ms` tinyint(3) unsigned default '0',
  `ls` int(10) unsigned default '0',
  `stock` int(10) unsigned default '0',
  `date1` date default NULL,
  `date2` date default NULL,
  `ids` int(6) NOT NULL default '1',
  `idauthor` int(6) NOT NULL default '1',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

//Структура таблицы `elemarch-elemarch` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `elemarch-elemarch`";
$query[] = "CREATE TABLE IF NOT EXISTS `elemarch-elemarch` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `eid1` int(10) unsigned NOT NULL,
  `eid2` int(10) unsigned NOT NULL,
  `f` tinyint(2) unsigned default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `eid1_2` (`eid1`,`eid2`),
  KEY `eid1` (`eid1`),
  KEY `eid2` (`eid2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `elements` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `elements`;";
$query[] = "CREATE TABLE IF NOT EXISTS `elements` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `codeGJS` int(10) unsigned default NULL,
  `name` varchar(255) NOT NULL,
  `desc` text,
  `art` varchar(50) default NULL,
  `vendor` varchar(255) default NULL,
  `price` int(10) unsigned default NULL,
  `ms` tinyint(3) unsigned default '0',
  `ls` int(10) unsigned default '0',
  `stock` int(10) unsigned default '0',
  `date1` date default NULL,
  `date2` date default NULL,
  `ids` int(6) NOT NULL default '1',
  `idauthor` int(6) NOT NULL default '1',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";

// Структура таблицы `elements-elements` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `elements-elements`;";
$query[] = "CREATE TABLE `elements-elements` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `eid1` int(10) unsigned NOT NULL,
  `eid2` int(10) unsigned NOT NULL,
  `f` tinyint(2) unsigned default '0',
  PRIMARY KEY  (`id`),
  UNIQUE KEY `eid1_2` (`eid1`,`eid2`),
  KEY `eid1` (`eid1`),
  KEY `eid2` (`eid2`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `elemspec` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `elemspec`;";
$query[] = "CREATE TABLE IF NOT EXISTS `elemspec` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `codeGJS` int(10) unsigned default NULL,
  `name` varchar(255) NOT NULL,
  `desc` text,
  `art` varchar(50) default NULL,
  `vendor` varchar(255) default NULL,
  `price` int(10) unsigned default NULL,
  `ms` tinyint(3) unsigned default '0',
  `ls` int(10) unsigned default '0',
  `stock` int(10) unsigned default '0',
  `date1` date default NULL,
  `date2` date default NULL,
  `ids` int(6) NOT NULL default '1',
  `idauthor` int(6) NOT NULL default '1',
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

//

$query[] = "DROP TABLE IF EXISTS `fonts`";
$query[] = "CREATE TABLE IF NOT EXISTS `fonts` (
  `id` int(6) NOT NULL auto_increment,
  `faces` text NOT NULL,
  `family` varchar(100) NOT NULL,
  `size` varchar(100) NOT NULL,
  `stretch` varchar(130) NOT NULL,
  `style` varchar(100) NOT NULL,
  `variant` varchar(100) NOT NULL,
  `weight` varchar(100) NOT NULL,
  `lh` float NOT NULL,
  `url` text NOT NULL,
  `ids` int(8) NOT NULL,
  `idm` int(8) NOT NULL,
  `numpage` int(9) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";

//
$query[] = "DROP TABLE IF EXISTS `nameform`;";
$query[] = "CREATE TABLE IF NOT EXISTS `nameform` (
  `id` int(9) NOT NULL auto_increment,
  `namform` varchar(24) NOT NULL,
  `method` varchar(4) NOT NULL,
  `handler` varchar(100) NOT NULL,
  `idauthor` int(9) NOT NULL,
  `ids` int(9) NOT NULL,
  `idm` int(9) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";


$query[] = "DROP TABLE IF EXISTS `forms`;";
$query[] = "CREATE TABLE IF NOT EXISTS `forms` (
  `id` int(9) NOT NULL auto_increment,
  `idform` int(9) NOT NULL,
  `name_field` text NOT NULL,
  `type_field` varchar(10) NOT NULL,
  `place_field` varchar(150) NOT NULL,
  `req_field` varchar(10) NOT NULL,
  `id_field` varchar(30) NOT NULL,
  `clas_field` varchar(100) NOT NULL,
  `method` varchar(100) NOT NULL,
  `default` varchar(100) NOT NULL,
  `label` varchar(100) NOT NULL,
  `ids` int(9) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
";


$query[] = "DROP TABLE IF EXISTS `kurs`;";
$query[] = "CREATE TABLE IF NOT EXISTS `kurs` (
  `datcurs` date NOT NULL,
  `dol` varchar(10) character set utf8 default NULL,
  `evro` varchar(10) character set utf8 default NULL,
  `gbp` varchar(10) character set utf8 NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// -- Структура таблицы `maket` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `maket`";
$query[] = "CREATE TABLE IF NOT EXISTS `maket` (
  `id` int(12) NOT NULL default '0',
  `Maket` varchar(50) NOT NULL,
  `styles` text,
  `flex` text NOT NULL,
  `grid` text NOT NULL,
  `numparams` varchar(200) NOT NULL,
  `fonts` varchar(200) NOT NULL,
  `video` text NOT NULL,
  `effects` varchar(200) NOT NULL,
  `scripts` text NOT NULL,
  `ids` int(12) NOT NULL,
  `numpage` int(12) NOT NULL,
  `numaket` int(6) NOT NULL,
  `idauthor` int(12) NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

$query[] = "INSERT INTO `maket` (`id`, `Maket`, `styles`, `flex`, `grid`, `numparams`, `fonts`, `video`, `effects`, `scripts`, `ids`, `numpage`, `numaket`, `idauthor`) VALUES
(1, 'Maket', 'display|width|height|margin|padding|background-color|background|border|border-top| border-bottom|border-left|border-right|color|position|top|bottom|right|left|text-align|word-spacing|float|list-style|outline|cursor|max-height|min-height|max-width|min-width|vertical-align|visibility|opacity|z-index|border-radius|overflow|text-transform|text-overflow|transition|transform|direction', 'display|flex-direction|flex-wrap|flex-flow|order|flex-grow|flex-shrink|flex-basis|justify-content|align-items|align-self|align-items|align-content', 'display|grid-template-columns|grid-template-rows|grid-auto-rows|grid-auto-columns|grid-column-start| grid-column-end|grid-row-start|grid-row-end| grid-column-gap|grid-row-gap|grid-area|grid-cell', 'Pics|Sizes|Scale|Transparent|Transition|Grid|Bootstr', 'font-style|font-weight|font-size|line-height|font-family', 'src|allow|allowfullscreen|', 'crop|hhead|effect3|effect4|effect5', 'script1|script2|script3|script4|script5|script6|', 0, 0, 0, 0);";

// Структура таблицы `mapsites` Создание: Май 23 2019 г., 12:54

$query[] = "DROP TABLE IF EXISTS `mapsites`";
$query[] = "CREATE TABLE IF NOT EXISTS `mapsites` (
  `id` int(10) unsigned NOT NULL,
  `pid` int(10) unsigned NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `typeF` tinyint(2) unsigned default '0',
  `constrF` tinyint(1) unsigned default '0',
  `ms` tinyint(3) unsigned default '0',
  `numEl` mediumint(8) unsigned default '0',
  `numEls` mediumint(8) unsigned default '0',
  `numElst` mediumint(8) unsigned default '0',
  `desc` text,
  `ids` int(6) NOT NULL,
  `idauthor` int(6) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `pid` (`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";


// Структура таблицы `elemap` Создание: Май 23 2019 г., 12:54

$query[] = "DROP TABLE IF EXISTS `elemap`";
$query[] = "CREATE TABLE IF NOT EXISTS `elemap` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `codeGJS` int(10) unsigned default NULL,
  `name` varchar(255) NOT NULL,
  `desc` text,
  `keywords` varchar(200) default NULL,
  `titles` varchar(255) default NULL,
  `price` int(10) unsigned default NULL,
  `ms` tinyint(3) unsigned default '0',
  `ls` int(10) unsigned default '0',
  `links` varchar(100) default '0',
  `date1` date default NULL,
  `idm` int(9) default NULL,
  `domen` varchar(100) NOT NULL default '1',
  `idauthor` int(6) NOT NULL default '1',
  `configpage` text character set ucs2 NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1;";

$query[] = "DROP TABLE IF EXISTS `type-elemap`;";
$query[] = "CREATE TABLE IF NOT EXISTS `type-elemap` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `tid` int(10) unsigned NOT NULL,
  `eid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
";


// Структура таблицы `namparams` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `namparams`;";
$query[] = "CREATE TABLE IF NOT EXISTS `namparams` (
  `tab` varchar(25) NOT NULL,
  `codparams` int(3) NOT NULL,
  `nampars` text,
  `types` text NOT NULL,
  `delimiter` varchar(100) NOT NULL,
  `reqr` varchar(100) default NULL,
  `ids` int(10) NOT NULL,
  `idauthor` varchar(100) default NULL,
  `region` varchar(200) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// загрузка структуры хранения данных о страницах сайта
$query[] = "INSERT INTO `namparams` (`tab`, `codparams`, `nampars`, `types`, `delimiter`, `reqr`, `ids`, `idauthor`, `region`) VALUES
('pages', 1, 'Номер страницы|Название страницы|Лозунги|Ключи|Имена кнопок|Адрес страницы|Тип вывода|Скрипты|Стили|Заголовок|Содержание|ИдентификаторМ|ИдентификаторL|Ссылки на картинки|Список меню|Привязка списка меню|Привязка футтера|Картинки кнопок|Текст картинок|Привязка к новостям|Сайт|автор|Конфиг', 'hid|pic=60|text|text|50|10|check|text|100|hid|text|typ|10|pcs|100|pags|50|pcs|text|news|hid|hid|hid', ',|,|;,;,|;,,;,;,;,;,|;,,;,;,;,;,|;,;,|;,,,,|;,', 'h|v|v|v|v|u|v|u|u|hid|v|v|v|v|v|v|v|v|v|v|hid|hid|hid', 0, '0', '0'),
('elements', 2, 'Порядковый номер|Код|Наименование|Описание|Код производителя|Производитель|Цена|Маркетинговый флаг|Логистический флаг|Склад|Дата|Транзит|Сайт|Автор', 'hid|10|255|pic=text|50|255|10|3|10|10|10|10|hid|hid', ',,,|,,,,,,,,,,,', 'h|u|v|v|v|v|v|u|u|v|u|v|h|h', 1, '1', ''),
('news', 3, 'id|Дата|Заголовок|Текст|Порядковый номер|Источник|Группа|Картинка|Элемент|Ссылка|Страница|Сайт', 'hid|10|100|text|hid|hid|typ|pcs|40|text|5|hid|', ',,,,,,,;,;,;,,', 'h|v|v|v|h|h|v|v|v|v|v|h', 0, '', ''),
('customers', 4, 'keyid|customerid|Название|Адрес|Город|Страна|Индекс|Регион|Юр.Адрес|Телефон основной|ИНН|КПП|Расчетный счет|БИК|Банк|Корсчет|Телефон лица|Соцсети|Эл. Почта лица|Хостинг|Автор|ФИО|Тариф', 'hid|hid|60|80|30|20|10|20|80|30|10|9|20|9|80|20|30|50|50|check|hid|50|hid', ',,,,,,,,,,,,,,,,,;,,;,,,', 'h|h|r|v|v|v|v|v|r|r|r|v|v|v|v|v|r|v|r|u|h|r|h', 0, '', ''),
('namparams', 5, 'Таблица|код|Имена|Тип|Разделители|Обязательные|автор|область', '20|hid|100|100|2|100|hid|hid', ',,|,|,,|,', 'u|h|v|v|u|v|h|h', 1, NULL, ''),
('maket', 6, 'classid|Класс|Стили|flex|grid|Параметры|Шрифты|Видео|эффекты|Скрипты|Сайт|Страница|Numaket|Author', 'hid|50|100|100|100|100|100|100|100|200|hid|hid|hid|hid', ',,|,|,|,|,|,|,|,|,,,,', 'h|v|v|v|v|v|v|v|v|v|h|h|h|h', 1, '1', ''),
('allmakets', 7, 'id|Name|Стили|Flex|Grid|Параметры|Шрифты|Видео|Эффекты|Скрипты|Описание|Сайт|Автор|', 'hid|20|100|100|100|100|100|100|100|100|100|hid|hid|', ',,|,|,|,|,|,|,|,|,|,,', 'h|v|v|v|v|v|v|v|v|v|v|h|h|', 1, '', ''),
('structure', 8, 'id|pid|name|typeF|constrF|ms|numEl|numEls|numElst|desc|ids|idauthor', 'hid|hid|255|hid|hid|hid|hid|hid|hid|text|hid|hid', ',,,,,,,,,|,,', 'h|h|v|u|u|u|u|u|v|h|h', 1, '1', ''),
('elements-elements', 9, 'id|Основной код|Зависимый код|Флаг|', 'hid|10|10|2|', ',,,,', 'h|u|u|u|', 1, '', ''),
('users-users', 10, 'id|uid1|uid2|f|', 'hid|12|12|2|', ',,,|,', 'h|u|u|u|', 1, '', ''),
('allsites', 0, 'ключ|Номер|idU|Сайт|Страница|Тип|Структура|Назначение|Стили|Скрипты|Картинки||||||TC|TN|TE|TS|desc', 'hid|hid|hid|hid|hid|typ|typ|typ|50|50|pcs|hid|hid|hid|hid|hid|10|10|10|10|100', ',,,,,,,,,,;,,,,,,,,,,|', 'h|h|h|u|u|h|h|h|v|v|v|h|h|h|h|h|u|u|u|u|v', 1, '1', '1'),
('elemap', 11, 'Порядковый номер|Код|Наименование|Описание|Ключевые слова|Заголовки|Цена|Маркетинговый флаг|Логистический флаг|Ссылки|Дата|Макет|Сайт|Автор', 'hid|hid|hid|hid|hid|hid|hid|hid|hid|hid|hid|hid|hid|hid', ',,,|,|,|,,,,,|,,,,', 'h|h|h|h|h|h|h|h|h|h|h|h|h|h', 1, '1', ''),
('mapsites', 12, 'id|pid|name|typeF|constrF|ms|numEl|numEls|numElst|desc|ids|idauthor', 'hid|hid|255|hid|hid|hid|hid|hid|hid|text|hid|hid', ',,,,,,,,,|,,', 'h|h|u|h|h|h|h|h|h|u|h|h', 1, '1', ''),
('forms', 13, 'id|idform|name|type|place|required|idformclass|classform|default|ids', 'hid|hid|50|50|50|50|50|50|50|hid', ',,|,,,,,,,', 'h|h|v|v|v|v|v|v|v|h', 1, '1', ''),
('nameform', 14, 'id|name|method|handler|idauthor|ids|idm', 'hid|50|50|50|hid|hid|hid', ',,,,,,', 'h|v|v|v|h|h|h', 1, '1', ''),
('scripts', 15, 'id|Name|flag|type|scripts|used|site|user|maket', 'hid|10|6|6|text|check|hid|hid|hid', ',,,,,;,,,,', 'h|v|v|v|v|v|h|h|h', 0, '1', ''),
('setUser', 16, 'Учетная запись|Мои сайты|Новый сайт|Тарифы|Профиль', 'account|mysite|hosting|plan|other', 'account', 'settings/', 0, NULL, ''),
('setPageBlockS', 17, 'Название|Лозунги|Кнопки|Меню|Тексты|Иллюстрации|Баннер|Логотип|Подвал|Карта', 'nameS|lozS|buttonS|menuS|textS|picS|bannerS|logoS|footS|mapS', 'blockS', NULL, 0, NULL, ''),
('setMaketPage', 18, 'Лендинг|Галлерея|Блог|Твитинг|Фибинг|Квизинг|Мобильный|Адаптив|Многостраничный|Иерархический|Интернет-магазин|Слоеный|Магический', 'land|gall|blog|tw|fb|qw|mob|flex|cont|cat|shop|lay|mag', 'maketS', NULL, 1, '1', '1'),
('setSEO', 19, 'Поисковые системы|Заголовки|Ключевые слова|Описания', 'findS|titleS|keywordS|descS', 'seoS', NULL, 0, NULL, ''),
('setContentMaket', 20, 'Опции|Заголовок|Текст|Баннер|Блог|Шапка|Макет|Подвал|Меню|Кнопки', 'Options|Headtext|Maintext|Banner|Blog|Header|Maket|Footer|Menu|Button', 'contentS', NULL, 1, '1', '1'),
('setgridS', 21, 'Макет|Шапка|Контент|Подвал', 'layoutG|headerG|contentG|footerG', 'gridS', NULL, 1, '1', '1'),
('setMaket', 22, 'Топология|Хедер|Кнопки|Меню|Контент|Галереи|Слайдеры|Аккордион|Формы|Футер|Блог|Новости', 'GM|HD|BT|MN|CT|GL|SL|AC|FM|FT|BL|NW', 'maketS', NULL, 0, NULL, ''),
('setTypesPage', 23, 'Content|Blog|Menu|Button|Header|Footer|Find|Slider|Form|Galery|SidebarR|sidebarL|sidebarC|Accordion', 'wr|bl|mn|bt|hd|ft|fb|sw|fo|ga|sr|sl|sc|ac', '', NULL, 0, NULL, ''),
('setHosting', 24, 'Подключение|Редактор контента|Домен второго уровня SSL|Конструктор|SEO|Почта|Персональная база|Объем диска|Тип размещения', 'y|y|y|y|y|y|y|y|y', '', NULL, 0, NULL, ''),
('setTypesSite', 25, 'Визитка|Лента новостей|Видеоблог|Галерея|Мобильный|Адаптивный|Компактный|Дизайнерский|Структурный|Каталог|Корпоративный', 'vizcard|lentanews|videoblog|galery|mobile|flex|compact|design|stuctur|cataloug|corp', '', NULL, 0, NULL, ''),
('setTypesWork', 26, 'Новости|Наука|Обучение|Интернет|Презентация|Музыка|Литература|Спорт|Развлечения|Торговля|Соцсеть|Маркетинг|Производство|Дистрибуция|Культура|Арт|Реклама', 'news|sience|study|internet|presentation|music|literature|sport|entertainment|trade|social|production|distributiuon|culture|art|advertising', '', NULL, 0, NULL, ''),
('setTarifPlan', 27, 'VPS/VDN|Все включено|Почтовый|Профи|Активный|Конструктор|Готовые решения|Тестовый', 'vs|allinc|post|proff|active|constuctor|readysol|test', '', NULL, 0, NULL, ''),
('setEnvir', 28, 'Стили|Скрипты|Шрифты|Иконки|Карты|Библиотеки|Фреймворки', 'styleS|scriptS|fontS|ikonS|mapS|libS|framwS', 'envirS', NULL, 0, NULL, ''),
('setAdmin', 29, 'Окружение|Макет|Контент|Конструктор|Вид |Блоки|Сетка|SEO|Настройки', 'envirS|maketS|contentS|konstrS||blockS|gridS|seoS|settingS', '', NULL, 1, '1', '1'),
('configs', 30, 'id|name|current_idm|current_blog|current_cat|current_gal|current_news|current_type|current_str|current_app|current_host|current_tarif|max_sites|max_pages|max_makets|max_pics|max_scripts|max_styles|curent_mode|topogy|configm|configp|', 'hid|30|9|9|9|9|9|3|3|3|3|3|5|5|5|9|5|5|3|text|hid|hid', ',,,,,,,,,,,,,,,,,,,,,,', 'h|v|u|v|v|v|v|v|v|v|u|h|u|u|u|u|u|u|u|v|h|h', 1, '1', ''),
('configm', 31, 'id|name|current_typ|curent idmen|current_level|current_access|current_header|current_wrapper|current_footer|current_galery|current_slider|bootstrap|smartgrid|jquery|framework|current_ids', 'hid|30|70|10|30|10|10|10|10|10|10|10|10|10|10|hid', ',,,,,,,,,,,,,,,,', 'h|v|v|v|v|v|v|v|v|v|v|v|v|v|v|h', 1, '1', ''),
('configp', 32, 'id|name|sznames|szpats|szlozs|szbuttons|szbutgrp|szconts|szcontgrp|szlists|szlistgrp|szimg|szimggrp|szimgbut|szimgbutgrp|szfoots|szlevel|szimgtexts|szimgtxtgrp|szstyles|szscrpt|szsites|szusers|szpics|ids|np', 'hid|30|2|3|3|3|3|3|3|3|3|3|3|3|3|3|3|3|3|3|3|3|9|9|hid|hid', ',,,,,,,,,,,,,,,,,,,,,,,,,', 'h|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|v|h|h', 1, '1', ''),
('fonts', 33, 'id|faces|family|size|stretch|style|variant|weight|lh|url|ids|idm|numpage', 'hid|text|typ|100|typ|typ|typ|typ|10|text|hid|hid|hid', ',;,;,;,;,;,;,;,;,;,,,', 'h|v|v|v|v|v|v|v|v|v|h|h|h', 1, '1', ''),
('alloptionS', 34, 'Владелец|Админа|Пользователь|Магазина|Статьи|Ленты|Галерея|Слайдера|Менеджера|SEO|Соцсеть|Виджеты|Плагины', 'ownerS|adminS|userS|shopS|articalS|newS|galS|swipS|managS|seoS|socialS|widgetS|pluginS', 'contentS&Options', NULL, 0, NULL, '');";


// Структура таблицы `news` Создание: Мар 25 2019 г., 18:13


$query[] = "DROP TABLE IF EXISTS `news`;";
$query[] = "CREATE TABLE IF NOT EXISTS `news` (
  `idauthor` int(10) default NULL,
  `date` date NOT NULL,
  `name` char(100) NOT NULL,
  `newstext` text NOT NULL,
  `idnews` int(5) NOT NULL auto_increment,
  `vendor` varchar(50) NOT NULL,
  `group` varchar(50) NOT NULL,
  `imgnews` varchar(30) NOT NULL,
  `codgjsnews` char(40) default NULL,
  `hrefnew` tinytext NOT NULL,
  `numpagat` tinyint(5) default NULL,
  `site` int(5) NOT NULL,
  UNIQUE KEY `idnews` (`idnews`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `blogs` Создание: Май 23 2019 г., 12:54

$query[] = "DROP TABLE IF EXISTS `blogs`;";
$query[] = "CREATE TABLE IF NOT EXISTS `blogs` (
  `idauthor` int(10) default NULL,
  `date` date NOT NULL,
  `name` char(100) NOT NULL,
  `newstext` text NOT NULL,
  `idnews` int(5) NOT NULL auto_increment,
  `vendor` varchar(50) NOT NULL,
  `group` int(5) NOT NULL,
  `imgnews` varchar(30) NOT NULL,
  `codgjsnews` char(40) default NULL,
  `hrefnew` tinytext NOT NULL,
  `numpagat` tinyint(5) default NULL,
  `site` int(5) NOT NULL,
  UNIQUE KEY `idnews` (`idnews`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `blogs` Создание: Май 23 2019 г., 12:54

$query[] = "DROP TABLE IF EXISTS `infos`;";
$query[] = "CREATE TABLE IF NOT EXISTS `infos` (
  `idauthor` int(10) default NULL,
  `date` date NOT NULL,
  `name` char(100) NOT NULL,
  `newstext` text NOT NULL,
  `idnews` int(5) NOT NULL auto_increment,
  `vendor` varchar(50) NOT NULL,
  `group` int(5) NOT NULL,
  `imgnews` varchar(30) NOT NULL,
  `codgjsnews` char(40) default NULL,
  `hrefnew` tinytext NOT NULL,
  `numpagat` tinyint(5) default NULL,
  `site` int(5) NOT NULL,
  UNIQUE KEY `idnews` (`idnews`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `orders` Создание: Мар 15 2019 г., 17:41


$query[] = "DROP TABLE IF EXISTS `orders`;";
$query[] = "CREATE TABLE IF NOT EXISTS `orders` (
  `orderid` int(10) unsigned NOT NULL auto_increment,
  `customerid` int(10) unsigned NOT NULL,
  `amount` float(10,2) default NULL,
  `date` date NOT NULL,
  `order_status` char(10) character set utf8 default NULL,
  `ship_name` char(60) character set utf8 NOT NULL,
  `ship_address` char(80) character set utf8 NOT NULL,
  `ship_city` char(30) character set utf8 NOT NULL,
  `ship_tels` char(30) character set utf8 default NULL,
  `ship_em` char(30) character set utf8 default NULL,
  `ship_cfio` char(50) character set utf8 default NULL,
  PRIMARY KEY  (`orderid`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// 


// Структура таблицы `order_items` Создание: Мар 15 2019 г., 17:41


$query[] = "DROP TABLE IF EXISTS `order_items`;";
$query[] = "CREATE TABLE IF NOT EXISTS `order_items` (
  `orderid` int(10) unsigned NOT NULL,
  `isbn` char(13) character set utf8 NOT NULL,
  `item_price` float(10,2) NOT NULL,
  `quantity` tinyint(3) unsigned NOT NULL,
  PRIMARY KEY  (`orderid`,`isbn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// 


// Структура таблицы `pages` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `pages`;";
$query[] = "CREATE TABLE IF NOT EXISTS `pages` (
  `numpage` int(10) NOT NULL auto_increment,
  `namep` char(100) NOT NULL,
  `lozungp` text NOT NULL,
  `keywords` char(250) NOT NULL,
  `buttons` text NOT NULL,
  `hrefp` char(100) NOT NULL,
  `typemenu` char(60) NOT NULL,
  `hrefscripts` text NOT NULL,
  `hrefstyle` char(100) NOT NULL,
  `title` char(130) NOT NULL,
  `content` text NOT NULL,
  `idmenu` char(70) NOT NULL,
  `levelmenu` varchar(50) NOT NULL,
  `hrefimage` text NOT NULL,
  `list` text NOT NULL,
  `list_href` char(100) NOT NULL,
  `butthref` char(100) NOT NULL,
  `buttimg` char(100) NOT NULL,
  `imgtext` text NOT NULL,
  `idnews` int(5) NOT NULL,
  `site` varchar(200) NOT NULL default 'deltar.ru',
  `idauthor` int(6) NOT NULL,
  `configpage` text NOT NULL,
  PRIMARY KEY  (`numpage`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `params` Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `params`;";
$query[] = "CREATE TABLE IF NOT EXISTS `params` (
  `nampars` text character set utf8,
  `GJScode` int(6) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// Структура таблицы `pics` Мар 15 2019 г., 17:41


$query[] = "DROP TABLE IF EXISTS `pics`;";
$query[] = "CREATE TABLE IF NOT EXISTS `pics` (
  `idpic` int(6) NOT NULL auto_increment,
  `gjs` int(6) NOT NULL,
  `code` int(6) NOT NULL,
  `istoch` int(1) NOT NULL,
  `variant` varchar(3) character set utf8 NOT NULL,
  `exist` tinyint(1) default NULL,
  PRIMARY KEY  (`idpic`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

$query[] = "DROP TABLE IF EXISTS `qiuz`;";
$query[] = "CREATE TABLE  IF NOT EXISTS `quiz` (
  `id` int(10) NOT NULL,
  `name` varchar(30) NOT NULL,
  `quest` varchar(250) NOT NULL,
  `group_quest` int(6) NOT NULL,
  `type_answer` varchar(10) NOT NULL,
  `comment` text NOT NULL,
  `link` varchar(250) NOT NULL,
  `level` int(6) NOT NULL,
  `uid` int(10) NOT NULL,
  `ids` int(10) NOT NULL,
  `key` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
";


// Структура таблицы `scripts` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `scripts`";
$query[] = "CREATE TABLE IF NOT EXISTS `scripts` (
  `id` int(6) NOT NULL,
  `Maket` varchar(50) NOT NULL,
  `flag` varchar(8) NOT NULL,
  `type` varchar(3) NOT NULL,
  `scripts` text NOT NULL,
  `needs` varchar(7) NOT NULL,
  `ids` int(9) NOT NULL,
  `uid` int(9) NOT NULL,
  `idm` int(9) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";


$query[] = "DROP TABLE IF EXISTS `social`;";
$query[] = "CREATE TABLE  IF NOT EXISTS `social` (
  `id` int(10) NOT NULL,
  `netname` varchar(6) NOT NULL,
  `nettype` varchar(6) NOT NULL,
  `idnote` int(10) NOT NULL,
  `textnote` text NOT NULL,
  `typenote` int(6) NOT NULL,
  `imgnote` varchar(400) NOT NULL,
  `group` int(10) NOT NULL,
  `level` int(10) NOT NULL,
  `link` varchar(200) NOT NULL,
  `uid` int(10) NOT NULL,
  `ids` int(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

// Структура таблицы `structure` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `structure`;";
$query[] = "CREATE TABLE IF NOT EXISTS `structure` (
  `id` int(10) unsigned NOT NULL,
  `pid` int(10) unsigned NOT NULL default '0',
  `name` varchar(255) NOT NULL,
  `typeF` tinyint(2) unsigned default '0',
  `constrF` tinyint(1) unsigned default '0',
  `ms` tinyint(3) unsigned default '0',
  `numEl` mediumint(8) unsigned default '0',
  `numEls` mediumint(8) unsigned default '0',
  `numElst` mediumint(8) unsigned default '0',
  `desc` text,
  `ids` int(6) NOT NULL,
  `idauthor` int(6) NOT NULL,
  PRIMARY KEY  (`id`),
  KEY `pid` (`pid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";


// Структура таблицы `type-elements` Создание: Мар 15 2019 г., 17:41
$query[] = "DROP TABLE IF EXISTS `type-elemspec`;";
$query[] = "CREATE TABLE IF NOT EXISTS `type-elemspec` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `tid` int(10) unsigned NOT NULL,
  `eid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;
";


$query[] = "DROP TABLE IF EXISTS `type-elements`;";
$query[] = "CREATE TABLE IF NOT EXISTS `type-elements` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `tid` int(10) unsigned NOT NULL,
  `eid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `type-elemarch` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `type-elemarch`;";
$query[] = "CREATE TABLE IF NOT EXISTS `type-elemarch` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `tid` int(10) unsigned NOT NULL,
  `eid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";


//Структура таблицы `type-pages` Создание: Май 23 2019 г., 18:37
 

$query[] = "DROP TABLE IF EXISTS `type-pages`;";
$query[] = "CREATE TABLE IF NOT EXISTS `type-pages` (
  `id` int(10) unsigned NOT NULL auto_increment,
  `tid` int(10) unsigned NOT NULL,
  `eid` int(10) unsigned NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";

// Структура таблицы `userActivate` Создание: Мар 15 2019 г., 17:41 


$query[] = "DROP TABLE IF EXISTS `userActivate`;";
$query[] = "CREATE TABLE IF NOT EXISTS `userActivate` (
  `uid` int(10) unsigned NOT NULL,
  `code` char(32) character set utf8 collate utf8_bin NOT NULL,
  `time` timestamp NOT NULL default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  KEY `code` (`code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";


//  Структура таблицы взаимных пользователей Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `users-users`;";
$query[] = "CREATE TABLE IF NOT EXISTS `users-users` (
  `id` int(12) NOT NULL,
  `uid1` int(12) NOT NULL,
  `uid2` int(12) NOT NULL,
  `f` tinyint(2) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;";

//Структура таблицы `users` Создание: Мар 15 2019 г., 17:41

$query[] = "DROP TABLE IF EXISTS `users`;";
$query[] = "CREATE TABLE IF NOT EXISTS `users` (
  `keyid` int(10) NOT NULL auto_increment,
  `id` int(10) unsigned default '1',
  `login` varchar(255) NOT NULL,
  `pass` char(32) character set utf8 collate utf8_bin NOT NULL,
  `email` varchar(255) NOT NULL,
  `level` int(10) unsigned NOT NULL,
  `time` int(10) unsigned default NULL,
  `ms` tinyint(3) unsigned default '0',
  `ciid` int(10) unsigned default NULL,
  `activate` tinyint(1) unsigned default '0',
  `customerid` varchar(20) default NULL,
  `siid` int(6) NOT NULL,
  `balans` int(9) NOT NULL,
  PRIMARY KEY  (`keyid`),
  UNIQUE KEY  (`login`),
  UNIQUE KEY  (`email`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ;";
if(isset($_GET['site']) && $_GET['site'] >0)$strucs = $_GET['site'];
else $strucs = 0;
$typesite = 1;
try {
		foreach($query as $val)
			$db->query($val);
	} catch(DBException $e) {
		exit($e.' from '.__FILE__.':'.__LINE__);
	}
	$user = Singleton::getInstance('User');
	$desc = array('own' =>'','ownbd' =>'Y','cym'=>'','cga' =>'');
	if($user->addAdmin('admin', 'veravolf','ruslan@grandjet.ru')){
			$control_summa=$user->regbd($_SERVER['HTTP_HOST'],1,'',$typesite,$strucs);
			if($control_summa>0) echo '<br>Сайт подключен за номером '.$control_summa.'<br>';
			
		}
echo '<table><tr><td class="center">';		
echo '<br>Администртор базы :'.$user->getlogin();
echo '<br>DONE<br>';
echo '<form id="first" action="http://'.$_SERVER["HTTP_HOST"].'" method="post">';
echo '<br><input name="site" value="'.$_POST["site"].'" type="hidden">';
echo '<span><input type="submit"  value="ШАГ: 3. Готово!..."/><br><br>';
echo '</form></td></tr></table>';		
?>