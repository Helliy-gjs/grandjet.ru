<?php
//!Данные и параметры с верстки
$arrloz = array(0 => 'Профессиональное создание сайтов в grandjetstudio', 1 => 'Самые современные технологии',2=>'Backend / Frontend разработчик, создатель grandjetstudio');
$dat['dat'][0] = $arrloz; 
$dat['dat'][1] = $glsr['bd'].': 2 января 1962 года';
$dat['dat'][2]= $glsr['tn'].': +79255053421';
$dat['dat'][3] = $glsr['el'].': <a href="mailto:ruslan@deltar.ru">ruslan@deltar.ru</a>';
$dat['dat'][4] = $glsr['ws'].': <a href="//land.deltar.ru" target="_blank">land.deltar.ru</a>';
//$dat['typesite'] = 'spa';
$img = array(0=>'photo.jpg');
$datSoc['dat'] = array('twitter' => '<i class="fa fa-twitter"></i>',
'vk' => '<i class="fa fa-vk"></i>',
'fb' => '<i class="fa fa-facebook"></i>',
'gh' => '<i class="fa fa-github"></i>');
$datSoc['icon'][0] = '<i class="icon-basic-case"></i>';
$datSoc['icon'][1] = '<i class="icon-basic-book-pen"></i>';
$datSoc['icon'][2] = 'icon-basic-geolocalize-05';
$datSoc['icon'][3] ='icon-basic-smartphone';
$datSoc['icon'][4] ='icon-basic-webpage-img-txt';
//!Заготовки данных для стандартных процедур
if(isset($contentSite['owner']['telmain'])) $dat['dat'][2] =$glsr['tn'].$contentSite['owner']['telmain'];
if(isset($contentSite['owner']['email'])) $dat['dat'][3] = $glsr['el'].': <a href="mailto:'.$contentSite['owner']['email'].'">'.$contentSite['owner']['email'].'</a>';
if(isset($contentSite['owner']['dborn'])) $dat['dat'][1] = $glsr['bd'].': <a href="//'.$contentSite['owner']['dborn'].'" target="_blank">'.$contentSite['owner']['dborn'].'</a>';
if(isset($arrmain['namep'][4])) $dat['dat'][4] = $glsr['ws'].': <a href="//'.$arrmain['namep'][4].'" target="_blank">'.$arrmain['namep'][4].'</a>';
if(isset($contentSite['owner']['cfio'])) $firstname = $contentSite['owner']['cfio'];
else $firstname = 'Руслан Серегин';
$datM = array($firstname,$arrloz[2],$glsr['am'],$glsr['rm'],$glsr['pf'],$glsr['ct']);	
$dataIcons1 = array(0=>'<i class="icon-basic-case"></i>',
1=>'<i class="icon-basic-book-pen"></i>'); 
$dataIcons2['dat'] = array(1=>$datSoc['dat']['vk'],2=>$datSoc['dat']['fb'],3=>$datSoc['dat']['gh']);
//идентификаторы
$id = array('#about','#resume','#portfolio','#contacts');
//классы
$clas0 = array('main_head','s_portfolio bg_'.$dark,'s_contacts bg_'.$light,
'main_footer bg_'.$dark);
$clas2 = array('s_about bg_'.$light,'s_resume','section_header',
's_descr_wrap','s_descr','section_content','#portfolio_grid');
$clas1 = array('filter','data-filter="all"','data-filter=".category-1"','data-filter=".category-2"','data-filter=".category-3"');
	$about = array('Погрузись в мир сайтов с удовольствием.=Вот уже 25 лет я занимаюсь бизнесом в IT-сфере, пройдя путь от торговли и производства компьютеров, до оказание сервисных услуг корпоративным клиентам. Создание сайтов было необходимым условием. И поэтому уже более 10 лет я занимаюсь разработкой своего подхода к их созданию.',
	'Думай о своем.=Больше не нужно думать о не понятном и сложном. Оригинальных подход к решению базовых задач сочетается с использованием самых современных достижений в этой области; Используй опыт других не заметно для себя. Просто выбирай то, что тебе близко и понятно.');	
$text = array(
	1=>'МГУ имени Ломоносова', 0=>'Физический факультет',
	3=>'', 2 => 'Языки программирования Basic,Fortran',
	5=>'', 4 => 'Диплом по КХД. Программирование на SCOONSHIP',
	7=>'РНИИ КП ', 6=>'Курсы по программированию Assembler, Fortran, Pascal',
	9=>'Самообразование',8 => 'Программист на Clipper',
	11=>'',10=>'Веб программирование HTML',
	13=>'',12=>'Программирование на PHP',
	15=>'', 14=>'Изучение CSS,JS-фреймворков, gulp, nodejs, sass',
	16=>'РНИИКП',17=>'Инженер-исследователь',
	18=>'Ассоциация СПЕЙС ТВ"',19=>'Зам. генерального по IT',
	20=>'ЗАО "Дельта-Р"',21=>'Президент',
	22=>'ООО "ГрандДжет Сервис"', 23=>'Генеральный директор',
	24=>'',25=>'Разработчик ПО');
	$dats = array(0=>"1979-1985",2=>'',4=>'',6=>'1985-1990',8=>'1990-1994',10 =>'1994-2003'
	,12=>'2008-2012',14=>'2012-2020',16=>'1985-1990',18=>'1990-1993',20=>'1993-2006',22=>'2007-2017',24=>'2012-2020');

	$blog = array(0	=>'1979-1985=Первое знакомство с программирование произошло на первом курсе. Изучал Basic, Фортран. ',
	2=> '=С тех пор, программирование постоянно сопровождало меня в моей карьере. И хотя, как штатный программист, я не проработал ни одного дня. Написаны были тысячи страниц кода.',
	4=> '=Первое серьезное применение программных решений было на дипломе при выполнении расчетов в квантовой хромодинамике.',
	6 => '1985-1990=Здесь повышал квалификацию, как программист, изучая Macroassembler и Pascal.',
	8=> '1990-1994=Придя в бизнес, изучил Clipper для создания деловых приложений. ',
	10=> '1994-2003=Открыв свой собственный бизнес. Изучал языки и средства создания сайтов.',
	12=> '2008-2012=Для создания серьезных решений понял, что необходимо изучить языки используемые для создания backend части сайта. Выбор пал на PHP, который я знаю очень не плохо для самобразования.',
	14=> '2012-2020=Разработал ряд технологий и концепций создания сайтов нового поколения. Вместо парадигмы: Дизайн, Верстка, backend, frontend, предложил ООП парадигму: Контент, Страница, Макет, Сайт, в рамках которой проще осуществлять разработку и поддержку сайта на уровне Контента, настройку сайта выполняем на уровне Страница, изменение дизайна на уровне Макет, транформацию сайта на уровне Сайт.',
	16=> '1985-1990=Программировал на Pascal, моделируя процессы деградации поупроводников под радиационым воздействием.',
	18=> '1990-1993=Как программист разработал на Clipper систему учета договоров МЦ "БАЗИС"',
	20=> '1993-2006=Как программист разрабатывал сайт компании DeltaR с интернет магазином shop.deltar.ru, приложения для управления бизнесом: Обязательства, Склад, Документы, Платежи. ',
	22=> '2007-2017=Продолжил работу над интернет-магазином. Расширил функционал. Сформулировал концепцию создания сайта в рамка ООП подхода. Разработал основные принципы, которые впоследствии положил в основу системы grandjetstudio. Заморозил бизнес по обслуживанию корпоративных клиентов в связи осложнениями ведения бизнеса в РФ. Полностью посвятил все время раззработки системы grandjetstudio.',
	24=> '2012-2020=Сегодня в своих разработках использую современые технологии: препроцессоры (sass), сборки проектов с применением nodejs, webpack, gulp. Хотя и являюсь разработчиком backend, освоил фрейворки для разработки frontend части сайта такие как Vue+Nuxt, ReactJS, Angular');

	
	$dat1['dat'] = array('Все работы','Сайты','Технологии','Решения'); 
	
	
	$blog1 = array('Импорт данных=Одной кнопкой='.'Одна из самых затратных и по времени, и по человеским затратам часть создания и обслуживания сайта связана с наполнением его контентом. 
	В системе grandjetstudio применяются такие технологические решения, которые позволяют разделить процессна две стадии. На первой в одобном формате (обычно это таблицы Excel) формируется файл, на второй этот файл импортируется в базу данных сайта, как только вы загрузите на сайт.',
	'Иерархическое строение=Альтернативное решение='.'Очень значительную часть данных (самых разных) удобно хранить в виде иерархической системы каталога. Такая система, во-первых, обеспечивает путь, по которому вы можете находить нужные данные в интерактивном режиме, во-вторых, в иерахию удобно размещать структуру сайтов и отдельтных страниц 
	так как сама структура HTML реализует иерархию вложеных тегов, в-треьих, информационные данные описывающие любые объекты также удобно каталогизировать, в-четвертых, единая структура 
	применяемая для всех данных позволяет использовать унисерсальные инструменты для обработки и представления этих данных.',
	'Модульная загрузка данных=По потребности='.'Модульная система сегодня используется во всех современых фреймвоках, так как это позволяет легче оптимизировать всю систему. В grandjetstudio модульность также одна из важнейших технологий. Однако я считаю, что модульность системы должнва быть строго регламентирована. Главным, опять же как в импорте данных, является простота и общность форматов.
	Для подключения внешних и внутрених модулей должна быть веская причина, и подключение это должно происходить самым простом способом. Даже если модуль является кусочком кода, пользователь должен иметь возможность не только его быстро подкючить, но и отключить без нарушения работы всей системы.',
	'Фоновая загрузка окружения=Быстро и не заметно='.'Под окружением сайта я понимаю все те элементы системы, которые обслуживают работу сайта: базы данных, скрипты, конфигурационные файлы, глоссарии, библиотеки и т.д. Пользователь сайта не должен видеть процесс подключение того окружения, которое не относится к его компетенции пользователя.
	Все базы данных, и свойста в них хранящиеся должны создаваться автоматически в соответствии с заложенными алгоритмами. Ручной ввод данных является основным источником ошибок м сбоев в работе систем. Поэтому он должен минимизирован, выполняться в удобной для контроля форме,
	и должен польностью отсутствовать там на самых критических участках.',
	'Удобная классификация=Ключевая технология='.'Разнообразие сайтов велико и обширно, хотя у них есть много общих характеристик и свойств. Важно в начеле процесса создания сайта хорошо понимать какие свойства являются ключевыми именно для вашего сайта, а какие позволяют его отнести
	к какой-то большой категории или семейству сайтов. Классификация сайтов в grandjetstudio также относится к технологиям, используемым в системе. Главная задача ее сделать классификацию наиболее универсальной и простой',
	'Скорость разработки=Без потери качества='.'Важнейшей технолоической задачей, решаемой grandjetstudio является много кратно ускорить создание и сопровождения сайтов пользователей системы. В первой версии системы, являющейся пилотной, эта задача номер 1. Вопросы оптимизации и производельности выйдут на пеервый план когда
	будет создан концептуальное решение поставленных задач.',
	'ООП модель=Ясность проектирования='.'Сайт это объект и поэтому ООП весьма полно позволяет его описывать. Современые сайты не являются объектами в точном понимании этого слова. Так как нет одиного конструктра создания такого объекта. Разные стороны сата сущностно не являются свойтвами
	чего-то целого. Просто существет слишком много способов никак не связанных подходов к сайту. Это породило существование большого 
	количества инструментов, решающих отдельные проблемы. Такой подход еще уместен сегодня, но завтра, понятно, его должен сменить другой подход. Сегодня уже очень много фреймворков, хороших инструментов разработки, но они страются  все время 
	снизить планку входа в разработку. В итоге же 80% сайтов оказываются ненужным баластом в сети, потому что плохо выполняют возложенную на них задачу.',
	'Трансформация=Настоящее удовольствие='.'Сайты grandjetstudio, по моему замыслу, должны легко транфомироваться, расширяться и дополнять друг друга. Именно все перечисленные здесь требования к системе должны обеспечить это. Легкий импорт, Четкая иерархия, Модульность,
	Фоновая работа, Универсальная модель. В своем портфолио я буду иллюстрировать на реальных проектах создание и развитие системы. Много уже сделано, но предстоит сделать еще больше. Присоединяйтесь.');
	//! Картинки галереии
	$imgs = array('1.jpg','2.jpg','3.jpg','4.jpg','5.jpg','2.jpg','3.jpg','2.jpg');	
	//! адрес, телефон, сайт
	$blogC = array(0=> 'Руслан Серегин',1=>'г. Королев ул. Кооперативная, д.7',
	2=>'+7 925 505 34 21',3=>'<a href="//deltar.ru" target="_blank">www.deltar.ru</a>');