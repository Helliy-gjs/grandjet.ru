<?php
class Utils {
	static function calcNumEl() {
		Utils::calc(0, Singleton::getInstance('DB'));	
	}
	
	private static function calc($id, $db) {
		$numEl = 0;
		$typeF = 0;
		if($id != 0)
			$typeF = $db->query('SELECT `typeF` FROM `structure` WHERE id = ^Ni;', $id);
		$res = $db->query('SELECT `id` FROM `structure` WHERE pid = ^Ni;', $id);
		if($res !== null) {
			if(!is_array($res)) {
				$numEl += Utils::calc($res->id, $db);
			} else {
				foreach($res as $val) {
					$numEl += Utils::calc($val->id, $db);
				}
			}
		}
		if($typeF) {
			$numEl += $db->query('SELECT COUNT(*) FROM `type-elements` WHERE `tid` = ^Ni;', $id);
		}
		$db->query('UPDATE `structure` SET `numEl` = ^Ni WHERE `id` = ^Ni;', $numEl, $id);
		return $numEl;
	}
	
	static function generalcalcNumEl($id=0,$str_tab='structure',$type_tab='type-elements') {
		Utils::generalcalc($id, Singleton::getInstance('DB'),$str_tab,$type_tab);	
	}
	
	private static function generalcalc($id, $db,$str_tab='structure',$type_tab='type-elements') {
		$numEl = 0;
		$typeF = 0;
		if($id != 0)
			$typeF = $db->query('SELECT `typeF` FROM `'.$str_tab.'` WHERE `id` = ^Ni;', $id);
		$res = $db->query('SELECT `id` FROM `'.$str_tab.'` WHERE `pid` = ^Ni;', $id);
		if($res !== null) {
			if(!is_array($res)) {
				$numEl += Utils::calc($res->id, $db);
			} else {
				foreach($res as $val) {
					$numEl += Utils::calc($val->id, $db);
				}
			}
		}
		if($typeF) {
			$numEl += $db->query('SELECT COUNT(*) FROM `'.$type_tab.'` WHERE `tid` = ^Ni;', $id);
		}
		$db->query('UPDATE `'.$str_tab.'` SET `numEl` = ^Ni WHERE `id` = ^Ni;', $numEl, $id);
		return $numEl;
	}
	
	static function sendMail($to, $subject, $message, $from = 0, $headers = "") {
		$subject = "=?utf-8?B?".base64_encode($subject)."?=";
		if($from == 0) $from = "grandjetstudio@gmail.com";
		$lheaders = "From: $from\r\nContent-type: text/plain; charset=UTF-8\r\n".$headers;
		return mail($to, $subject, $message, $lheaders);
	}
	
	static function sendajaxMail($Pth,$class,$arrform,$name_button,$tarif,$nform=0){
		$tarifname=array('VPS/VDN','Все включено','Почтовый','Профи','Активный','Конструктор','Готовые решения','Тестовый');
		//$tarif=count($arrform['host']);
		
		for($i=0;$i<=$tarif;$i++){$arridmen[$i]=$i;$tarif_name[$i]=$tarifname[7-$i];}
		if ($nform == 0) $nform=count($arrform['name']);
		//echo '<a href="#callback1" class="'.$class.' fancybox">'.$name_button.'</a>';
		echo Maket::divclasstr($class,$Pth,'',' fancybox','a href="#callback"').$name_button[1].'</a>';
		//echo '<div class="hidden">';
		echo '<form id="callback" href="#order" class="pop_form"';
		//echo '<h3>'.$name_button[1].'</h3>';
		show::formoneshow($arrform);
		User::selmen($tarif_name,'',$arridmen,'',$tarif,'tarif','Выбрать');
		echo '<button type="submit" class="button">'.$name_button[2].'</button>';
		echo '</form>';
		//echo '</div>';
		}
		
	static function button_reg_soc($Pth,$nambutt,$hrefnam,$namsoc,$hrefsoc){
	Maket::divclass('header_topline',$Pth);
	Maket::showbootstrap(12,'md');
	Maket::icon_button('auth_buttons','fa fa-user');
	Maket::divclass('top_links',$Pth);
	foreach($nambutt as $key=>$val){
			echo '<a href="'.$hrefnam[$key].'">'.$val.'</a>';
					}
	echo '</div>';
	Maket::divclass('soc_buttons',$Pth);
		foreach($hrefsoc as $key=>$val){
			echo '<a href="https://'.$val.'"><i class="fa fa-'.$namsoc[$key].'"></i></a>';
					}
	echo '</div>';
	Maket::closediv(4);								
}
	
	
	static function generatePass($len = 8) {
		$useChars = '23456789ABCDEFGHKMNPQRSTUVWXYZabcdefghkmnpqrstuvwxyz@#$%^&*';
		$ucl = strlen($useChars)-1;
		$res = '';
		for($i = 0; $i < $len; $i++) {
			$res .= $useChars[mt_rand(0, $ucl)];	
		}
		return $res;
	}
	static function prepare_pages($uid,$domen,$npg,$nn,$db,$typmen=0,$load_files=''){
	//Загрузка страниц в пустую таблицу
	$user=Singleton::getInstance('User');
	$resu=$user->read_namparams('setMaketPage');
	$arrstr=$resu[0];
	$arrlatstr=$resu[1];
	//$arrstr=array(11=>'Магический', 0=>'Лендинг', 1=>'Галлерея', 7=>'Адаптив', 8=>'Многостраничный', 9=>'Иерархический',6=>'Мобильный', 4=>'Фибинг', 3=>'Твитинг',5=>'Квизинг',10=>'Интернет-магазин',2=>'Блог',12=>'Слои');
	//$arrlatstr=array(8=>'cont', 0=>'land', 1=>'gall', 7=>'flex', 11=>'mag', 9=>'cat',6=>'mob' ,4=>'fb', 3=>'tw',5=>'qw',10=>'shop',2=>'blog',12=>'lay');
	$user->check();
	if(!Utils::getsitetables($domen)) {
		$tabl['pages']='pages';
		$tabl['news']='news';
		$tabl['str']='structure';
		$tabl['elem']='elements';
		$tabl['infos']='infos';
		$tabl['blogs']='blogs';
		$tabl['elemap']='elemap';
		$tabl['mapsites']='mapsites';

	}
	else $tabl=Utils::getsitetables($domen);
	
	//Загрузка из спецфайла подготовленного влальцем сайта или из шаблонного файла если нет шаблона открывается файл спецфайла загруженного при инсталяции, если есть шаблон, то загружается загруженный пользователем файл на первом этапе инсталляции
	if($load_files==='')$file='./'.$tabl["pages"].'.csv';	
	else $file=$domen.'/'.$load_files;
	if(file_exists($file))$F=fopen($file,"r");
	$db->autocommit(FALSE);
	$db->start();
	//если файл открылся для чтения
	$type_site=$arrlatstr[$typmen];
	if (isset($F)) {
		echo 'Загрузка страниц из файла '.$file.'<br>';	
		//Загрузка страниц из файла. Данные записываются в таблицу.
		Utils::add_tabs_file($domen,$user,$tabl['pages'],$db,$uid,20000,$load_files,$type_site);
		Utils::prepare_news($nn,$tabl,$db); 
		Utils::transakres($db);
		}
	//если страниц в таблице нет, т.е. первый сайт в системе
	elseif ($user->getscountab($tabl['pages'],'numpage', 'f')==0 && $uid==1 && $domen==='deltar.ru'){
		echo 'Файл страниц не найден, загружаются страницы первого сайта';
		$type_site=$arrlatstr[$typmen];
	//echo 'таблица страниц -'.$tabl["pages"];
		$titl0="main_gra_".$domen;
		$titl1="title_gra_".$domen;
		$titl2="main_gra_all";
		$txt0=array('Главная','О системе','Подключение','Возможности','Условия работы','История создания','Коротко о сайтах');
		$txt1='Grandjetstudio – это система, реализованная как сайт для создания себя. Это значит, что с помощью этой системы вы можете создать свою такую же систему по созданию сайтов. Для этого вам нужно быть суперъюзером системы. Если вы просто авторизованный пользователь этой системы вы можете создавать сайты любого типа, структуры и назначения.
		;Сайты grandjetstudio я называю грандджет (grandjet). Потому что они призваны ктегорически изменить подход к их созданию и главное к их использованию. Сегодня мы наблюдаем ситуацию когда одни и те же разработки дизайнеров и WEB-программистов много кратно продаются разным клиентам за не пропорциональные затратам деньги. При этом сопрвождение проекта и его развитие, которые действительно являются необходимой работой для любого продукта и его продвижения на рынок оказываются неоправданно дорогой опцией для клиента. Это приводит к тому, что услуги серьезных разработчиков рказываются достуаными только для коммерческих структур. Данный проект ориентирован в первую очередь на простых пользователей с творческими задатками, которые хотели бы иметь свой сайт, а не бесплатный аккаунт в социальной сети. ; Технологическая платформа для реализации этих возможностей создана.  По мере развития системы цены прейскуранта будут увеличиваться, вновь прешедшие клиенты будут всегда получать немного больший функционал, чем те кто зарегистрировался ранее. Последнии буду получать новый функционал по старым ценам до окончания календарного года. Поэтому очень выгодно зарегистроваться в первой половине  года. Тарифы будут пересмативаться два аз в год: в марте и в августе.|;';
		$txt2='Просто подключись.= Главное что получаете после регистрации - это возможность создание собственного сайта. Сайт может быть бесплатным только ограниченный период времени, но размер этого периода может расширяться, если вы активно принимаете участие в продвижении системы своим друзьям и знакомым, в том числе в социальных сетях.; Простота главное, что должен получить пользователь систем разрабатываемых grandjetstudio. И для того чтобы стать просто пользователем системы достаточно пройти стандартную регистрацию. Можно и зарегистроваться через соцсети.; У пользователей есть несколько типов ролей. После регистрации вы становитесь пользователем системы и получаете доступ ко всем ресурсам других пользователей в сотвествии с их Политикой предоставления доступа.;  ;|;;;';
		$txt3='Если вы создали в системе свой grandjet вы автоматически становитесь его администратором. Впрочем вы можете завести отдельный логин и пароль для себя как администратора.;Администратору вашего grandjet доступна функция редактирования сайта. Редактирование предполагает возможность, как изменения и дополнения контента, так и изменение дизайна, типа и оформления.; Кроме того вы можете создать свой сайт в виде таблицы Exel и загрузив ее на сайт автоматически импортировать в него содержимое этого файла.  Также возможно автоматическое импортирование каталогов (например) товаров и создание интернет магазина без ограничений по количеству товаров и функционала. Разумеется, для создание большого интернет магазина, нужно будет выбрать соотвествующий тарифный план.;|;;;';
		$txt4='Регистрация пользователя сводится к стандартной процедуре заполнения и отправки формы, или загрузку ваших данных с вашего аккаунта в социальной сети. При этом ваши данные записываются в базу системы grandjetstudio и используются для вашей идентификации. Для создания своего  grandjet нужно получить доменное имя вашего сайта. Это может быть выбранное вам латинское название <name>. Тогда ваше доменное имя будет выглядеть как: <name>.<our_domen> . Где <our_domen> тот домен на котором вы прошли регистрацию. Для того чтобы ваш  домен был доступен в сети интернрет он должен быть зарегистрован на хостинге grandjetstudio. ;Выбрав в форме имя вы отправите заявку на регистрацию, и через некоторое небольшок время ( в пределах часа двух) ваш домен будет зарегистрован. Теперь вы сможете войти на свой грандджет через интернет. И там вам будут предложены формы дальнейшей работы с ресурсом. ;Первым условием будет внесение регстрационного взноса для оплаты хостинга на 1 месяц или более длительный срок. После оплаты этого взноса вы получите полный доступ к предусмотренному тарифным планом функционалу. Внимание! Деньги переведенные на оплату месяца невозвращаются. Деньги переведенные на последующие месяцы могут быть возвращены если оплачеевый период не начался. Т.е. если вы оплатили 2 месяца 3 марта, то до 31 марта можно вернуть только уже произведенную оплату за апрель, но не за март. При этом предусмотрена комиссия в размере 10%. Эти условия вы подписываете когда отправляете заявку на создание своего сайта, о чем получаете уведомление по электронной почте.; Для работы с вашим сайтом Вам нет необходимости в отдельном хостинге;|;;';
		$txt5='Когда была задумана система?=Впервые автор системы задался задачей создания подобной системы в 2010 году. Тогда же были созданы первые части системы, и интернет магазин shop.deltar.ru. По совокупности причин интернет магазин не имел коммерческого успеха, главным образом из-за отсутствия маркетинговой поддержки и рекламы. Автор тогда работал в другом бизнесе: был руководителем небольшой аутосорсинговой компании. Реализованный проект был очень далек от задуманного. ;В первую очередь проект ориентирована на творческих людей уже добившихся успеха в своей сфере.=А если вы медийный персонаж или у вас уже есть известность, ваша или вашего проекта, если ваше имя или названия уже активно заводится в строки поисковиков, то вам нужен только сам сайт. Вам не нужно думать о хостинге или seo. В этом случае вы можете воспользоваться одной из бесплатных систем, ну хоть бы и Wix. Но даже там нужно все-таки создавать сайт, ломать голову, получать дополнительную, но совсем вам не нужную информацию. И в итоге вы получаете сайт на домене третьего уровня сомнительного качества. Поэтому, вы все равно, если вам нужен сайт, пойдете к профессионалам. И они через не менее чем 3-4 месяца создадут вам добротный сайт. Сайт, который они уже по сути продали раз 10. Так как, если они профи, то они создают не сайты, а системы их производства. |;;;';
		$txt6='Сайт -представляет собой информоционно-программный продукт, обладающий следующими свойствами:;1. Это продукт имеющий свойства программного, а именно он представляет собой программный текст выполняемый на сервере интернет.;2. Результат, получаемый пользователем на компьютер, также является программный текст, называемый HTML-кодом.;3. Специальные программы приложения выводят на экран компьютера пользователя результат в виде информационного контента.;4. Контент выводимый в приложения также обладает интерактивными возможностями, а именно:;4.1. Пользователь может отправлять информацию на сервер, и таким образом вносить изменения в страницу и передавать данные на сервер;4.2. Пользователь может также управлять содержимом страницы без обращения к серверу с помощью поддерживаемых приложениями скриптов на языках программирования, Напрример JS.;4.3 Пользователь также может управлять контентом выводимым на экран приложения с помощью таблиц стилей.;4.4. Сайт пользователя может сам по заданному алгоритму выполнять все три  выше приведенные возможности.|;;;;;;;;';
		$name_page='banmain.jpg|logo.png|';
		$imag_href='1.jpg;2.jpg;3.jpg;4.jpg';
	$db->query('INSERT INTO '.$tabl["pages"].' (`namep`,`numpage`,`hrefp`,`typemenu`,`buttons`,`idmenu`,`title`,`site`,`lozungp`,`idauthor`,`list`,`list_href`,`hrefimage`,`butthref`,`imgtext`) VALUES (^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns);',$name_page.$txt0[0],($npg+1),'','nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac','Все готово!;Подключайся;Твори|'.($npg+2).';'.($npg+3).';'.($npg+4),'flex',$titl0,$domen,Menu::LOZUNG.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),$uid,';;;;;',($npg+2).';'.($npg+3).';'.($npg+4),'1.jpg;2.jpg;3.jpg;4.jpg;5.jpg',';;;|'.($npg+4).';'.($npg+2).';'.($npg+3),$txt2);	
	$db->query('INSERT INTO '.$tabl["pages"].' (`namep`,`hrefp`,`numpage`,`typemenu`,`buttons`,`idmenu`,`content`,`title`,`site`,`lozungp`,`idauthor`,`list`,`list_href`,`hrefimage`,`butthref`,`imgtext`) VALUES (^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ns,^Ns);',$name_page.$txt0[1],'',($npg+2),'nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac','Начальная;Подключайся;Все готово!;Твори|'.($npg+1).';'.($npg+3).';'.($npg+2).';'.($npg+4),'flex',$txt1,$titl1.'_'.($npg+2),$domen,Menu::LOZUNG.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),$uid,'Возможности;Условия работы;История создания;Главная',($npg+4).';'.($npg+5).';'.($npg+6).';'.($npg),';;;;;',';;;;;|'.($npg).';'.($npg+7).';'.($npg+3).';'.($npg+4).';'.($npg+5).';'.($npg+6),';;;;;|;;;;;');
	$db->query('INSERT INTO '.$tabl["pages"].' (`namep`,`hrefp`,`numpage`,`typemenu`,`buttons`,`idmenu`,`content`,`title`,`site`,`lozungp`,`idauthor`,`list`,`list_href`,`hrefimage`,`butthref`,`imgtext`) VALUES (^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns);',$name_page.$txt0[2],'',($npg+3),'nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac','Начальная;Все готово!;Подключайся;Твори|'.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),'flex',$txt2,$titl1.'_'.($npg+3),$domen,Menu::LOZUNG.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),$uid,';;;;;',($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),'4.jpg;5.jpg;6.jpg;7.jpg','1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg|;;;;;;;',';;;;;|;;;;;');		
	$db->query('INSERT INTO '.$tabl["pages"].' (`namep`,`hrefp`,`numpage`,`typemenu`,`buttons`,`idmenu`,`content`,`title`,`site`,`lozungp`,`idauthor`,`list`,`list_href`,`hrefimage`,`butthref`,`imgtext`) VALUES (^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns);',$name_page.$txt0[3],'',($npg+4),'nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac','Начальная;Твори;Все готово!;Подключайся|'.($npg+1).';'.($npg+4).';'.($npg+3).';'.($npg+2),'flex',$txt3,$titl1.'_'.($npg+4),$domen,Menu::LOZUNG.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),$uid,';;;;;',($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),'4.jpg;5.jpg;6.jpg;7.jpg','1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg|;;;;;;;;;',$txt4);		
	$db->query('INSERT INTO '.$tabl["pages"].' (`namep`,`hrefp`,`numpage`,`typemenu`,`buttons`,`idmenu`,`content`,`title`,`site`,`lozungp`,`idauthor`,`list`,`list_href`,`hrefimage`,`butthref`,`imgtext`) VALUES (^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns);',$name_page.$txt0[4],'',($npg+5),'nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac','Начальная;Твори;Все готово!;Подключайся|'.($npg+1).';'.($npg+4).';'.($npg+3).';'.($npg+2),'flex',$txt4,$titl1.'_'.($npg+4),$domen,Menu::LOZUNG.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),$uid,';;;;;',($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),'1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg','1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg|;;;;;;;;;',$txt4);
	$db->query('INSERT INTO '.$tabl["pages"].' (`namep`,`hrefp`,`numpage`,`typemenu`,`buttons`,`idmenu`,`content`,`title`,`site`,`lozungp`,`idauthor`,`list`,`list_href`,`hrefimage`,`butthref`,`imgtext`) VALUES (^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns);',$name_page.$txt0[5],'',($npg+6),'nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac','Начальная;Твори;Все готово!;Подключайся|'.($npg+1).';'.($npg+4).';'.($npg+3).';'.($npg+2),'flex',$txt5,$titl1.'_'.($npg+4),$domen,Menu::LOZUNG.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),$uid,';;;;;',($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),'1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg','1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg|;;;;;;;;;',$txt5);
	$db->query('INSERT INTO '.$tabl["pages"].' (`namep`,`hrefp`,`numpage`,`typemenu`,`buttons`,`idmenu`,`content`,`title`,`site`,`lozungp`,`idauthor`,`list`,`list_href`,`hrefimage`,`butthref`,`imgtext`) VALUES (^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ns,^Ns,^Ns,^Ns);',$name_page.$txt0[6],'',($npg+7),'wr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac','Начальная;Твори;Все готово!;Подключайся|'.($npg+1).';'.($npg+4).';'.($npg+3).';'.($npg+2),'flex',$txt6,$titl2,$domen,Menu::LOZUNG.($npg+1).';'.($npg+2).';'.($npg+3).';'.($npg+4),$uid,';;;;;',($npg+1).';'.($npg+5).';'.($npg+7).';'.($npg+4),'1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg','1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg|;;;;;;;;;',$txt6);
	Utils::prepare_news($nn,$tabl,$db);
	Utils::transakres($db);	
	}
	elseif($user->getscountab($tabl['pages'],'numpage', 'f')==0){
		//Если сайт не первый загружается одна стартовая страница
		echo 'Загрузка default страницы<br>';
		$text1='Donec lobortis egestas laoreet. Aenean commodo elementum dolor et eleifend. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Suspendisse sed dolor magna. Duis egestas porttitor ipsum ultrices accumsan. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nunc lacinia auctor eros, nec tincidunt sapien placerat et. Donec id quam nisl.';
		$text2='Donec lobortis egestas laoreet. Aenean commodo elementum dolor et eleifend. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Suspendisse sed dolor magna.';
		$text3='Donec lobortis egestas laoreet. Aenean commodo elementum dolor et eleifend.';
		$text_cont=$text2.';'.$text1.';'.$text3.';'.$text1.';'.' '.$text2;
		$text_img=$text2.';'.$text1.';'.$text3.';'.$text1.';'.$text2.';'.$text1.';'.$text3.';'.$text1.';'.$text2;
		$np=$npg+1;
		$styl='style'.$arrlatstr[$typmen].'min';
		$db->query("INSERT INTO `".$tabl['pages']."` (`numpage`, `namep`, `lozungp`, `keywords`, `buttons`, `hrefp`, `typemenu`, `hrefscripts`, `hrefstyle`, `title`, `content`, `idmenu`, `levelmenu`, `hrefimage`, `list`, `list_href`, `butthref`, `buttimg`, `imgtext`, `idnews`, `site`,`idauthor`,`configpage`) VALUES ('$np', 'empty', 'lozung1;lozung2;lozung3;|$np;$np;$np;', 'key1>key2>key3;title_page;description_page','button1;button2;button3;|$np;$np;$np;', '', 'wr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac', ';', ';', $titl0, '$text_cont;|$np;$np;$np;$np;$np;$np', 'flex', 0,'1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;', 'Menu;Menu;Menu;Menu', '$np;$np;$np;$np', 'Menu1;Menu2;Menu3;Menu4;Menu5;Menu6|$np;$np;$np;$np;$np;$np','Foot1;Foot2;Foot3;Foot4;Foot5;Foot6;|$np;$np;$np;$np;$np;$np','$text_img;|$np;$np;$np;', 0,'$domen',$uid,'' );");
	Utils::prepare_news($nn,$tabl,$db); 
	Utils::transakres($db);
	}
	//print_r($nn);
	
	//Если оперция прошла успешно закрываем транзакцию, если нет отменяем ее
	
}
	static function transakres($db){
		if (mysql_error() == '') {
		$db->commit(); 
		$db->autocommit(TRUE);
		if (mysql_error()) echo '<div class="info">ERROR commit-'.mysql_errno().'</div>';
			echo '<div class="info">Транзакция загрузки страниц закрыта</div>';
		}
	else {
		$db->rollback();
		echo '<div class="info">Транзакция отменена</div>';
	}
	}
	
	static function editPBD($arrname, $arrtype, $array,$c,$r,$s,$m,$t){	
    echo '<form id="edit" action="./'.$PageM->MainAr["hrefp"].'?editp=ok" method="post" ">';
    echo '<h1> Редактор </h1><table class="inp">';
    echo '<tr>';
	for ($k=0;$k<count($arrname)-2;$k++) {
		echo '<td class="r"><label>'.$arrname[$k].'</label></td>';
		if ($arrtype[$k] === 'text')
		echo '<td class="l"><textarea rows="'.$r.'" cols="'.$c.'" id="p" class="inp" name="'.$k.'" tabindex="'.$k.'" >'.htmlspecialchars($array[$k]).'</textarea></td>';
		else 
		echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.'" type="text" tabindex="1" maxlength="'.$m.'" value="'.htmlspecialchars($array[$k]).'"></td>';
	$l++;
	if ($l>$t) {$l=0; echo '</tr>';}
	}
	echo '<tr><td class="r"><label>'.$arrname[$k].'</label></td>';
	echo '<td class="l"><input size="'.$s.'" id="p" class="inp" name="'.$k.'" type="text" tabindex="1" maxlength="'.$m.'" value="'.$domen.'"></td></tr>';
	echo '</table>';
	echo '<input id="regBut" type="submit"  tabindex="7" value=" Записать " />';
	echo '</form>';
return $array;
	} 
	
	static function edit_page($np,$post,$user,$domen,$db, $record=false){
	$tabl=Utils::getsitetables($domen);
	if ($record) {
		$db->query('UPDATE '.$tabl["pages"].' SET `namep`='.$post[1].',`lozung`='.$post[2].'
		,`keywards`='.$post[3].' ,`buttons`='.$post[4].' ,`hrefp`='.$post[5].'
		,`typemenu`='.$post[6].',`hrefscripts`='.$post[7].',`hrefstyle`='.$post[8].' 
		,`title`='.$post[9].',`content`='.$post[10].' ,`idmenu`='.$post[11].' ,`levelmenu`='.$post[12].'
		,`hrefimage`='.$post[13].',`list`='.$post[14].',`list_href`='.$post[15].'
		,`buthref`='.$post[16].' ,`butimg`='.$post[17].' ,`imgtext`='.$post[18].'
		,`idnews`='.$post[19].',`site`='.$post[20].' WHERE `numpage`=^Ni;',$post[0]);
}
else {
	// определяем таблицы
	$lpg=$user->getscountab($tabl['pages'],'numpage', 'f');//последняя страница в pages	
	$res1=$db->query('SELECT * FROM '.$tabl["pages"].' WHERE `numpage`=^Ni;',$np);
	$l=0;
	foreach($res1 as $val){
	$array[$l]=$val;
	$l++;
	}
	$l=0;
	$res2=$db->query('SELECT * FROM `namparams` WHERE `codparams`=^Ni;',1);
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrname=explode('|',$arrnm);
	$arrtype=explode('|',$arrtp);
	Utils::editPBD($arrname, $arrtype, $array,50,3,50,50,1);
}	
}

	static function add_elements_file($domen,$user,$file,$db){
	$tabl=Utils::getsitetables($domen);// определяем таблицы
	
	$F=fopen($file,"r");
	if ($F) {
	set_time_limit(2500);
	$ts=date('U');
	$now=getdate($ts);
	$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
	$date1=explode('.',$array[10]);
	$date2=explode('.',$array[11]);
	if($array[10]<>''){
		$tt=$date1[2].'-'.$date1[1].'-'.$date1[0];
		$tt2=$date2[2].'-'.$date2[1].'-'.$date2[0];
			}
		else {
			$tt='0000-00-00';
			$tt2=$date2[2].'-'.$date2[1].'-'.$date2[0];
				}
	$lpg=$user->getscountab($tabl['elem'],'id', 'c');//последняя страница в elements
	echo $lpg.'--------------<br>';
	$array=fgetcsv($F,2048,';');
	for($i=$lpg+1;$array=fgetcsv($F,2048,';'); $i++) {
	$db->query('INSERT INTO '.$tabl["elem"].'  
	VALUES (^Ni,^Ni,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni,^Ni,^Ns,^Ns);',
	$i,$array[1],$array[3],$array[6],$array[2],$array[5],$array[4],$array[7],$array[8],$array[9],$tt,$tt2);
	if (mysql_error()<>'') 
	{
	echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
	echo "<BR>";
	}
	else {
		$db->query('INSERT INTO `type-elements` (`eid`, `tid`) VALUES (^Ni,^Ni);',$i,$array[13]);
			if (mysql_error()<>'') 
			{
				echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
				echo "<BR>";
				}
			}
	}
}
	fclose($F);
	$lpg=$i-$lpg;
	echo "DONE. Успешно загружены $lpg элементов из файла $file ";
	echo "<BR>";
	if (mysql_error() == '') rename($file,substr($file,0,-4).'.bak');
}
	private static function getid_domen($domen,$db){
		$res=$db->query("SELECT `uid` FROM `allsites` WHERE `domen`=^Ns;",$domen);
		if($res) {$return[$domen]=$res->uid; return $return;}
		else return false;
	}
	
	private static function getids_domen($domen,$db){
		$res=$db->query("SELECT `ids` FROM `allsites` WHERE `domen`=^Ns;",$domen);
		if($res) {$return[$domen]=$res; return $return;}
		else return false;
	}
	
	private static function maglink($larr0){
		$lb='';
		
		if(strstr($larr0,'|')){
			//если значение $larr0 разделенo | => array
			$larr=explode('|',$larr0);
			
			/*if(strstr($larr[0],';')){
			//если значение нулевой $larr0 разделен ; => array
			$lar = '';
			$link_butt=explode(';',$larr[0]);
			foreach($link_butt as $val){
				if(strlen($val)>500)$lar .= substr($val,0,500).';';
				else $lar .= $val.';';
			}
			//помещаем результат в нулевой $larr0
			$larr0[0] = $lar;
	}*/
	if(strstr($larr[1],';')){
		//если значение первыйй $larr0 разделен ; => array
				$link_butt=explode(';',$larr0);
				$lb='';
				foreach($link_butt as $val){
					if(strstr($val,'-')){
						$link_butt=explode('-',$val);	
						for ($j=intval($link_butt[0]);$j<intval($link_butt[1]);$j++)$lb.=($j).';';
						}
					else $lb.=$val.';';
				}	
		}
	else $lb=$larr[1];
	}
	elseif(strstr($larr0,';')){
		//если значение $larr0 разделенo ; => array
				$link_butt=explode(';',$larr0);
				
				foreach($link_butt as $val){
					if(strstr($val,'-')){
						$link_butt=explode('-',$val);	
						for ($j=intval($link_butt[0]);$j<intval($link_butt[1]);$j++)$lb.=($j).';';
						}
					else $lb.=$val.';';
				}	
				
		}
		elseif(strstr($larr0,'-')){
		//если значение $larr0 разделенo - => array
		$link_butt=explode('-',$larr0);	
		for ($j=intval($link_butt[0]);$j<intval($link_butt[1]);$j++)$lb.=($j).';';
	}	
	else $lb=$larr0;
	
	return $lb;
	}
	
	static function add_tabs_file($domen,$user,$elem,$db,$uid,$ogran=20000,$load_files='',$type_site='land'){	
	$ew = Singleton::getInstance('elementsW');
	if($user == null) $user = Singleton::getInstance('User');;
	$ids=Utils::getids_domen($domen,$db);
	$tabl=Utils::getsitetables($domen);// определяем таблицы
	//print_r($tabl);
	$pathheader=$_SERVER["DOCUMENT_ROOT"];
	if($load_files==''){
	if (isset($tabl[$elem])) $file=$pathheader.'/'.$tabl[$elem].'.csv';
	else $file=$elem.'.csv';
	}
	else $file=$load_files;
	$F=fopen($file,"r");
	if ($F) {
	set_time_limit(5000);
	//$lpg=$user->getscountab($tabl['pages'],'numpage', 'f');//последняя страница в pages
switch ($elem)
	{
	case $tabl["elem"]:
	{
	$ts=date('U');
	$now=getdate($ts);
	$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
	$date1=explode('.',$array[10]);
	$date2=explode('.',$array[11]);
	if($array[10]<>''){
		$tt=$date1[2].'-'.$date1[1].'-'.$date1[0];
		$tt2=$date2[2].'-'.$date2[1].'-'.$date2[0];
			}
		else {
			$tt='';//'0000-00-00';
			$tt2=$date2[2].'-'.$date2[1].'-'.$date2[0];
				}
	$lpg=$user->getscountab($tabl['elem'],'', 'c');//последняя страница в elements
	//echo $lpg.'--------------<br>';
	if($lpg<>0 && $load_files=='') return;
	$array=fgetcsv($F,2048,';');
	for($i=$lpg+1;$array=fgetcsv($F,2048,';'); $i++) {
	if ($i<$ogran) {	
		if($array[5]<>'' && $array[4]<>''){
		$db->query('INSERT INTO '.$tabl["elem"].'  
		VALUES (^Ni,^Ni,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni,^Ni,^Ns,^Ns,^Ni,^Ni);',
		$i,$array[1],$array[3],$array[6],$array[2],$array[5],$array[4],$array[7],$array[8],$array[9],$tt,$tt2,1,1);
	
		if (mysql_error()<>'') 
		{
			echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
			echo "<BR>";
		}
		else {
			$lps=$user->getscountab($tabl['str'],'id', 'c');
			$db->query('INSERT INTO `type-elements` (`eid`, `tid`) VALUES (^Ni,^Ni);',$i,$array[13]+$lps);
			if (mysql_error()<>'') {
				echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
				echo "<BR>";
				}
			}
		}	
	}
}
$ttt='элементов';
		break;
	}
	case "elemap":
	{
	$ts=date('U');
	$now=getdate($ts);
	$tt=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
	
	
	$lpg=$user->getscountab('elemap','id', 'f');//последняя страница в elements
	//echo $lpg.'--------------<br>';
	if($lpg<>0 && $load_files=='') return;
	$array=fgetcsv($F,2048,';');
	$idm=$array[11];
	for($i=$lpg+1;$array=fgetcsv($F,2048,';'); $i++) {
	if ($i<$ogran) {	
		
		$db->query('INSERT INTO `elemap`  
		VALUES (^Ni,^Ni,^Ns,^Ns,^Ns,^Ns,^Ni,^Ni,^Ni,^Ni,^Ns,^Ni,^Ns,^Ni);',
		$i,$array[1],$array[3],$array[6],$array[2],$array[5],$array[4],$array[7],$array[8],$array[9],$tt,$idm,$domen,$uid);
	
		if (mysql_error()<>'') 
		{
			echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
			echo "<BR>";
		}
		else {
			$lps=$user->getscountab($tabl['elemap'],'', 'c');
			$db->query('INSERT INTO `type-pages` (`eid`, `tid`) VALUES (^Ni,^Ni);',$i,$array[13]+$lps);
			if (mysql_error()<>'') {
				echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
				echo "<BR>";
				}
			}
			
	}
}
$ttt='элементов';
		break;
	}
	case $tabl["pages"]:
	{
		
		$text1='Donec lobortis egestas laoreet. Aenean commodo elementum dolor et eleifend. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Suspendisse sed dolor magna. Duis egestas porttitor ipsum ultrices accumsan. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nunc lacinia auctor eros, nec tincidunt sapien placerat et. Donec id quam nisl.';
		$text2='Fusce quis enim risus. Ut consectetur urna ac massa aliquet lobortis. Nunc tellus neque, condimentum vitae elementum quis, luctus nec sem. Maecenas dolor eros, consequat nec ultricies id, hendrerit in urna. Curabitur pulvinar aliquam sem, at lacinia mi vehicula ac. Mauris ante libero, porta a fermentum eget, aliquam et purus. Sed velit neque, iaculis a interdum quis, suscipit eget risus. Vestibulum gravida metus in libero feugiat ultricies sodales purus faucibus.';
		$text3='Ut ultricies laoreet porta. Donec mollis vehicula metus, sed vehicula mauris viverra id. Morbi dui ante, scelerisque quis sollicitudin a, imperdiet ac neque. Fusce ullamcorper nunc et nibh fringilla pellentesque. Praesent ullamcorper condimentum justo ut varius. Nam dui lectus, varius sed eleifend eu, vehicula non odio. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; In condimentum bibendum leo, a euismod purus sed.';
		$text4=$text1.' <br>'.$text2;
		$text5=substr($text3,0,120);
		$lpg=$user->getscountab($tabl['pages'],'numpage', 'f');//последняя страница в pages
		//if($lpg>0 && $load_files=='') return;
			$array=fgetcsv($F,5120,';');
			$startpage=$user->getlookforfields($_SERVER['HTTP_HOST'],'main_gra_'.$domen,$tabl["pages"]);
			$link_pages=$startpage.';'.$startpage.';'.$startpage.';'.$startpage.';'.$startpage.';';
			if (!$startpage ) $startpage=$lpg+1;
			for($i=$lpg+1;$array=fgetcsv($F,8120,';'); $i++) {
				if ($i<$ogran) {
					$array[1]='banmain.jpg|logo.png|'.substr($array[1],0,240).'||';
					if($array[2]=='')$array[2]=$text2.';'.$text1.';'.$text5.';'.$text4.';'.$text3.';|'.$link_pages;
					else $array[2]=Utils::maglink($array[2]);
					if($array[3]=='')$array[3]='keywords1>keywords2>keywords3;title_page;description_page';
					if($array[4]=='')$array[4]='Button1;Button2;Button3;Button4;Button5;|'.$link_pages;
					else $array[4]=Utils::maglink($array[4]);
					if($array[6]==='')$array[6]='nwr;bl;mn;bt;hd;ft;fb;sw;fo;ga;sr;sl;sc;ac';		
					if ($i == $startpage) $array[9]='main_gra_'.$domen;
					else $array[9]='title_gra_'.$domen.'_'.$i;
					if($array[10]=='')$array[10]=$text2.';'.$text1.';'.$text5.';'.$text4.';'.$text3.';|;;;;;';
					else $array[10]=Utils::maglink($array[10]);
					if($array[11]==='')$array[11]=$type_site;
					if($array[13]==='')$array[13]='1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg';
					if($array[14]==='')$array[14]='Menu1;Menu2;Menu3;Menu4;Menu5;';
					if($array[15]==='')$array[15]=$link_pages;
					else $array[15]=Utils::maglink($array[15]);
					if($array[16]==='')$array[16]='footer1;footer2;footer3;footer4;footer5;|'.$link_pages;
					else $array[16]=Utils::maglink($array[16]);
					if($array[17]=='')$array[17]='butt.jpg;butt.jpg;butt.jpg;butt.jpg;butt.jpg;';
					if($array[18]=='')$array[18]=$text1.';'.$text2.';'.$text3.';'.$text4.';'.$text5.';|'.$link_pages;
					else $array[18]=Utils::maglink($array[18]);
					if($array[19]=='')$array[19]=1;
					if($array[22]=='')$array[22]=utils::getConfig(3,'configp',1);
					$db->query('INSERT INTO '.$tabl["pages"].' VALUES (^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ni,^Ns);',$i,$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],$array[10],$array[11],$array[12],$array[13],$array[14],$array[15],$array[16],$array[17],$array[18],$array[19],$domen,$uid,$array[22]);
					if (mysql_error()<>'') 
					{
						echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
						echo "<BR>";
					}	
					$ttt=' страниц ';
				}
			} 
			break;
		}
	case $tabl["news"]:
	{
		$array=fgetcsv($F,2120,';');
		$lpg=$user->getscountab($tabl['news'],'', 'c');//последняя страница в news
		if($lpg<>0 && $load_files) return;
	for($i=$lpg+1;$array=fgetcsv($F,2120,';'); $i++) {
		if ($i<$ogran) {
		//echo $i.'<br>';Print_r($array[0]).'<br>';
		$db->query('INSERT INTO '.$tabl["news"].'  
		VALUES (^Ni,^Ns,^Ns,^Ns,^Ni,^Ns,^Ni,^Ns,^Ns,^Ns,^Ni,^Ns);',$uid,
		$array[0],$array[1],$array[2],$i,$array[4],$array[5],$array[6],
		$array[7],$array[8],$array[9],$domen);
		if (mysql_error()<>'') 
		{
		echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
		echo "<BR>";
		}	
	$ttt=' новостей ';
		}
	} 
		break;
	}
	case $tabl["str"]:
	{
		$array=fgetcsv($F,255,';');
		$lpg=$user->getscountab($tabl['str'],'', 'c');//последняя страница в structure
		if($lpg<>0 && $load_files) return;
	for($i=$lpg+1;$array=fgetcsv($F,255,';'); $i++) {
		if ($i<$ogran) {
		//echo $i.'<br>';Print_r($array[0]).'<br>';
		$db->query('INSERT INTO '.$tabl["str"].'  
		VALUES (^Ni,^Ni,^Ns,^Ni,^Ni,^Ni,^Ni,^Ni,^Ni,^Ns,^Ni,^Ni);',
		$i,$array[1]+$lpg,$array[2],$array[3],$array[4],$array[5],0,
		$array[7],$array[8],$array[9],$ids,$uid);
		if (mysql_error()<>'') 
		{
		echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
		echo "<BR>";
		}	
	$ttt=' групп ';
		}
	} 
	//Utils::generalcalcNumEl(0,$tabl["str"],'type-elements');
		break;
	}
	case $tabl["mapsites"]:
	{	
		//echo 'Загрузка в';print_r($tabl['mapsites']);
		$array=fgetcsv($F,255,';');
		$lpg=$user->getscountab($tabl['mapsites'],'', 'c');//последняя страница в mapsites
		$lpp=$user->getscountab($tabl['pages'],'numpage', 'f');
		if($lpg<>0 || $load_files=='') return;
		//echo $lpg.'--------------<br>'.$lpp;
	if($lpp==1 && $lpg==0){	
	for($i=$lpp+1;$array=fgetcsv($F,255,';'); $i++) {
		if ($i<$ogran) {
		$lb='';
		if(strstr($array[9],'-')){
			$link_butt=explode('-',$array[9]);
			
			for ($j=intval($link_butt[0]);$j<intval($link_butt[1]);$j++)$lb.=($j).';';
		}
		elseif(strstr($array[9],';')){
				$link_butt=explode(';',$array[9]);
				foreach($link_butt as $val)$lb.=($val).';';
			
		}
		else $lb=';;;;;';
		$textp='Ut ultricies laoreet porta. Donec mollis vehicula metus, sed vehicula mauris viverra id. Morbi dui ante, scelerisque quis sollicitudin a, imperdiet ac neque.';
		$textl=substr($textp,15,0);
		$textc=substr($textp,10,5).'='.$textp.' '.$textp;
		$array[4]='Button1;Butttton2;But tttton3;Buttton4;Buttton5;|'.$lb;
		$array[1]='banmain.jpg|logo.png|'.$array[2];
				$array[2]=$textl.';'.$textl.';'.$textl.';'.$textl.';'.$textl.';|;;;;;';
				$array[3]='key1>key2>key3;title page;description page';
				$array[5]='';
				$array[6]='bl;mn;bt;hd;ft;fb;sw;fo';
				$array[7]='';	
				$array[8]='';
				if ($i == $startpage) $array[9]='main_gra_'.$domen;
				else $array[9]='title_gra_'.$domen.'_'.($i+$lpp);
				$array[10]=$textc.';'.$textc.';'.$textc.';'.$textc.';'.$textc.';|;;;;;';
				$array[11]=$type_site;
				$array[12]=0;
				$array[13]='1.jpg;2.jpg;3.jpg;4.jpg;5.jpg;6.jpg;7.jpg;8.jpg;9.jpg';
				$array[14]='Menu1;Menu2;Menu3;Menu4;Menu5;';
				$array[15]=';;;;;';
				$array[16]='footer1;footer2;footer3;footer4;footer5;|;;;;;';
				$array[17]='butt.jpg;butt.jpg;butt.jpg;butt.jpg;butt.jpg;';
				$array[18]=$textp.';'.$textp.';'.$textp.';'.$textp.';'.$textp.';|;;;;;';
				$array[19]=0;
		$db->query('INSERT INTO '.$tabl["pages"].'  
			VALUES (^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns,^Ni);',
			$i,$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],
			$array[10],$array[11],$array[12],$array[13],$array[14],$array[15],$array[16],$array[17],$array[18],$array[19],$domen,$uid);
		if (mysql_error()<>'') {
			echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
			echo "<BR>";
		}	
	$ttt=' групп ';
		}
	} 
	}
		break;
	}
	case 'allnampars':
	{
		$a="namparams";
		$b="codparams";
		$c="nampars";
		$d='tab';
		$e='types';
		$f='delimiter';
		$lpg=$user->getscountab($a,$b, 'f');
		if($lpg>16 && $load_files=='') return;
		$array=fgetcsv($F,2048,';');
		for($i=$lpg;$array=fgetcsv($F,2048,';'); $i++){
			if ($i<$ogran) {
			$db->query('INSERT INTO '.$a.' ('.$d.','.$b.','.$c.','.$e.','.$f.') VALUES (^Ns,^Ni,^Ns,^Ns,^Ns);', $array[0],$array[1]+$lpg,$array[2],$array[3],$array[4]);	
		if (mysql_error()<>'') {
			echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
			echo "<BR>";
		}
		$ttt=' заголовков параметров';
			}
		}
	break;	
	}
	case 'nampars':
	{
		$a="namparams";
		$b="codparams";
		$c="nampars";
		$d='tab';
		$e='types';
		$f='delimiter';
		$lpg=$user->getscountab($a,$b, 'f');
		if($lpg>16 && $load_files=='') return;
		$array=fgetcsv($F,2048,';');
		for($i=$lpg;$array=fgetcsv($F,2048,';'); $i++){
			if ($i<$ogran) {
				$db->query('INSERT INTO '.$a.' ('.$d.','.$b.','.$c.','.$e.','.$f.') VALUES (^Ns,^Ni,^Ns,^Ns,^Ns);', 'namepar',$array[1]+$lpg,$array[2],'','');	
		if (mysql_error()<>'') {
			echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
			echo "<BR>";
		}
		$ttt=' заголовков параметров';
			}
		}
	break;	
	}
	case 'params':
	{
		$a="params";
		$b="GJScode";
		$c="nampars";
		$lpg=$user->getscountab($a,$b, 'f');
		if($lpg<>0 && $load_files=='') return;
		set_time_limit(1000);
		$array=fgetcsv($F,1256,';');
		//print_r($array);
		for($i=$lpg+1;$array=fgetcsv($F,2256,';'); $i++){
			if ($i<$ogran) {
				
			$db->query('INSERT INTO '.$a.' ('.$b.','.$c.') VALUES (^Ni,^Ns);',$array[0],$array[1]);	
		//$z="INSERT INTO `$a` (`$b`, `$c`) VALUES ('$array[0]','$array[1]');";
		if (mysql_error()<>'') {
			echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
			echo "<BR>";
		}
		$ttt=' параметров ';
			}
		}
		
	break;	
	}
	}
	fclose($F);
	}
	else 'Файл '.$file.' не найден';
	if($i<$ogran) $lpg=$i-$lpg;
	else $lpg=$ogran;
	echo 'DONE Успешно загружены '.$lpg.' '. $ttt.'  из файла  '. $file ;
	echo "<BR>";
	rename($file,substr($file,0,-4).'.bak');
	/*if(isset($mysqli)) {
		if (mysql_error() === '') rename($file,substr($file,0,-4).'.bak');
	}*/
return mysql_error();
}

	static function add_news_file($domen,$user,$file,$db){
	$tabl=Utils::getsitetables($domen);// определяем таблицы
	$lpg=$user->getscountab($tabl['pages'],'numpage', 'f');//последняя страница в pages
	$F=fopen($file,"r");
	if ($F) {
	set_time_limit(2500);
	for($i=$lpg+1;$array=fgetcsv($F,5120,';'); $i++) {
		$db->query('INSERT INTO '.$tabl["pages"].'  
		VALUES (^Ni,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ns,^Ni,^Ns);',
		$i,$array[1],$array[2],$array[3],$array[4],$array[5],$array[6],$array[7],$array[8],$array[9],
		$array[10],$array[11],$array[12],$array[13],$array[14],$array[15],$array[16],$array[17],$array[18],$array[19],$domen);
		if (mysql_error()<>'') 
		{
		echo "ERROR ".mysql_error()." ".mysql_errno()."\n";
		echo "<BR>";
		}	
	}
	fclose($F);
	if (mysql_error() == '') rename($file,substr($file,0,-4).'bak');
	$lpg=$i-$lpg;
	echo 'DONE. Успешно загружены $lpg страницы из файла $file ';
	echo "<BR>";
	}
}
	static function prepare_news(array $new,$tabl,$db,$direct='infos'){
	
	if (isset($new['date']) == ''){
	$ts=date('U');
	$now=getdate($ts);
	$tt1=$now['year'].'-'.$now['mon'].'-'.$now['mday'];
	}
	else $tt1=$new['date'];
	//echo '<br>new ';print_r($new);echo '<br>';
	foreach($new as $val) {
	//echo 'добовляем новость ';
	//$page='pages';
	if(isset($val["date"])) $tt2=$val["date"];
	else $tt2=$tt1;
	$table=$tabl[$direct];
	$db->query('INSERT INTO `'.$table.'` (`idauthor`,`date`,`name`,`newstext`,`idnews`,`vendor`,`group`, `imgnews`,`codgjsnews`,`hrefnew`,`numpagat`,`site`) 
	VALUES (^Ni,^Ns,^Ns,^Ns,^Ni,^Ns,^Ni,^Ns,^Ns,^Ns,^Ni,^Ns);',$val["idauthor"],$tt2,$val["name"],$val["newstext"],$val["idnews"],$val["vendor"],$val["group"],$val["imgnews"],$val["codgjsnews"],$val["hrefnew"],$val["numpagat"],$val["site"]);	
	if ($val["numpagat"] !='' && $table != 'infos') $db->query('UPDATE '.$tabl["pages"].' SET `idnews`='.$val["idnews"].' WHERE `numpage`='.$val["numpagat"].';');
	$db->query('ALTER TABLE `'.$table.'` AUTO_INCREMENT = 1');
	}
}
	static function getsitetables($domen){
		$db=Singleton::getInstance('DB');
		if ($domen <> '') {
			$Site=$db->query('SELECT `uid`,`ids`,`domen`,`nmpage`, `types`, `strucs`,`appoint`,`images`,`pages`, `news`,`element`,`structure` FROM `allsites` WHERE `domen` = ^Ns;', $domen);		
	}
	if ($Site) { 
		if ($Site->structure == '') $structure='structure';
		else $structure=$Site->structure ;
		$tabl=array('news'=>$Site->news, 'pages'=>$Site->pages,'elem'=>$Site->element,'str'=>$structure);
		if(isset($_GET['mapsites'])) {
			$tabl[$_GET['mapsites']]=$_GET['mapsites'];
			if(isset($_GET['elemap'])) $tabl[$_GET['elemap']]=$_GET['elemap'];
		}
		else {
			$tabl['elemap']='elemap';
			$tabl['mapsites']='mapsites';
		}
		$tabl['infos']='infos';
		$tabl['blogs']='blogs';
	return $tabl;
	}
	else return false;
		}
		
	static function GlobalNamPar($table,$numpar,$field='',$typmen='',$sizeInput=20)		
		{
	$db = Singleton::getInstance('DB');	
	
	$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	if($res2 && $numpar<>0){
		$arrnm=$res2->nampars;
		$arrtp=$res2->types;
		$arrdlm=$res2->delimiter;
		$arrname=explode('|',$arrnm);
		$arrtype=explode('|',$arrtp);
		foreach ($arrtype as $key=>$val) if (strstr($val,'type')) $arrtype[$key]=$sizeInput;
		if($arrdlm <> null) {
		$arrdelem=explode(',',$arrdlm);
		}
		else {
		for ($i=0;$i<count($arrtype);$i++)  {
			$arrdelem[$i][0]='|';
			$arrdelem[$i][1]=';';
			$arrdelem[$i]=$arrdelem[$i][0].$arrdelem[$i][1];
			}
		}
		}
		
	if($field<>''){
		$res1=$this->db->query('SELECT * FROM `'.$table.'` WHERE `'.$field.'`=^Ni;',$numpar);
		$l=0;
		foreach($res1 as $val){
		if($arrtype[$l] == 'check'  && $val=='') $array[$l]=$typmen;
		elseif($val == '') $array[$l]=$arrdelem[$l];
		else $array[$l]=$val;
		$l++;
	}
	$return=array($arrdelem,$arrname,$arrtype,$array);
}
else {
	$res2=$db->query("SELECT * FROM namparams WHERE tab=^Ns;",$table);
	$arrnm=$res2->nampars;
	$arrtp=$res2->types;
	$arrdlm=$res2->delimiter;
	$mass_zags=explode('|',$arrnm);
	$masszakls=explode('|',$arrtp);
	foreach($masszakls as $val) {
		if($numpar<>0){
		if($val) $mass_zakls[]='?np='.$numpar.'&'.$val;
		else $mass_zakls[]=$val.'?np='.$numpar;
			}
		else $mass_zakls[]=$val;
	}
	if($numpar<>0) {
			$mass_zakls[]='?np='.$numpar.'&'.'info';
			$mass_zags[]='Помощь';
			}
	$return=array($mass_zags,$mass_zakls,$arrdlm);
}

return $return;
}
	
	static function	loadbdsite($Sdomen,$isLocal = false){
		try { 
		//echo 'construct0';
		$db = Singleton::getInstanceinit('DB',1);
		$insi=$db->init_data;
		if(!strstr($_SERVER['HTTP_HOST'],$Sdomen))$Site0=$db->initbd($_SERVER['HTTP_HOST'],$db);
		//echo '<info class="hidno">Подключено</info>';
		} catch(DBException $e) {
		exit($e);
		}
	
	//print_r($insi);	
	//echo '<br>';print_r($Site0);
	if(isset($Site0)){
		$bdsite=array(0=>$Site0->bd,1=>$Site0->host,2=>$Site0->logad,3=>$Site0->passwad,4=>$Site0->port);
	//print_r($bdsite);
	if(is_object($Site0) && $Site0->bd !=  $insi[3] ){
	//echo '<info class="hidno">Сайт '.$_SERVER['HTTP_HOST'].' зарегистрирован в базе '.$bdsite[0].'</info>';
	//unset($db);
	//$bdname=explode('.',$_POST['owndomen']);
	$nameBD=$bdsite[0];
	$query = "CREATE DATABASE IF NOT EXISTS $nameBD";
	if($bdsite[0]<>'') $db->query($query);
	unset($db);
	try {
		//echo 'construct0';
		$db = Singleton::getInstancepar('DB',$bdsite[1],$bdsite[2],$bdsite[3],$bdsite[0],$bdsite[4]);
		$insi=$db->init_data;
		//echo '<info class="hidno">Подключение к базе '.$bdsite[0].'</info>';//$Site=$db->initbd($_SERVER['HTTP_HOST'],$db);
		} catch(DBException $e) {
		exit($e);
		}
	}
	else 'Сайт '.$_SERVER['HTTP_HOST'].' зарегистрирован не в базе '.$insi[3];
	}
	else {
	
	$query = "CREATE TABLE IF NOT EXISTS `allsites` (
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
$db->query($query);	//$_POST['chice']='owndomen';
	}
	return $db;
	}
	
public static function getConfig($conf=3,$tab='configp',$mode=0){
	
	$db = Singleton::getInstance('DB');	
	$res = $db->query("SELECT * FROM $tab WHERE id=^Ns;",$conf);
		if($res){
		foreach ($res as $key=>$val){
			if($key<>'name')$arrconf[$key] = 1*$val;
			else $arrconf[$key] = $val;
		}
		
			if($mode == 0)return $arrconf; 	
			else {
				$configpage='';
				$i=0;
				foreach ($arrconf as $val){
					if($i>1 && $i<20)$configpage.=$val.';';
					//else $configpage.=$val.'|';
					$i++;
				}
				if($configpage != '')return $configpage;
				else return false;
	}
}
else  return false;
}
}	

?>