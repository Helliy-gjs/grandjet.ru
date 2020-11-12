<?php
try {
	if(strstr($_GET['q'],'api/users')){
	$api = new usersapi();
	}
	elseif(strstr($_GET['q'],'api/structure')){
	$api = new strucsapi();
	}
	elseif(strstr($_GET['q'],'api/elements')){
	$api = new elemsapi();
	}
	elseif(strstr($_GET['q'],'api/elemap')){
            $api = new elemapapi();
		}
	elseif(strstr($_GET['q'],'api/maket')){
		$api = new maketapi();
	}	
	elseif(strstr($_GET['q'],'api/brends')){
		$api = new brendsapi();
	}	
	elseif(strstr($_GET['q'],'api/news')){
		$api = new newsapi();
	}
	elseif(strstr($_GET['q'],'api/infos')){
		$api = new infosapi();
	}
	elseif(strstr($_GET['q'],'api/blogs')){
		$api = new blogsapi();
	}
	elseif(strstr($_GET['q'],'api/quiz')){
		$api = new quizapi();
	}
	elseif(strstr($_GET['q'],'api/params')){
		$api = new paramsapi();
	}
	elseif(strstr($_GET['q'],'api/pics')){
		$api = new picsapi();
	}
	elseif(strstr($_GET['q'],'api/namparams')){
		$api = new namparsapi();
	}
	elseif(strstr($_GET['q'],'api/allmakets')){
		$api = new allmaketsapi();
	}
	elseif(strstr($_GET['q'],'api/allsites')){
		$api = new allsitesapi();
	}
	elseif(strstr($_GET['q'],'api/customer')){
		$api = new customsapi();
	}	
	elseif(strstr($_GET['q'],'api/pages')){
		$api = new pagesapi();
	}
	elseif(strstr($_GET['q'],'api/orders')){
		$api = new ordersapi();
	}
	elseif(strstr($_GET['q'],'api/kurs')){
		$api = new kursapi();
	}
	elseif(strstr($_GET['q'],'api/forms')){
		$api = new formsapi();
	}
	elseif(strstr($_GET['q'],'api/nameform')){
		$api = new nameformapi();
	}
	elseif(strstr($_GET['q'],'api/order_items')){
		$api = new orderitemsapi();
	}	
	elseif(strstr($_GET['q'],'api/elements-elements')){
		$api = new eeapi();
	}
	elseif(strstr($_GET['q'],'api/users-users')){
		$api = new uuapi();
	}																						
    echo $api->run();
	} catch (Exception $e) {
	echo json_encode(Array('error' => $e->getMessage()));
	}
	die();