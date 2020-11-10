<?php
class Routes extends Singleton {
	
	protected static $routes=array();
	protected static $route=array();
	
	public static function add($regexp, $route = array()){
		self::$routes[$regexp]= $route; 
	}
	public static function getRoutes(){
		return self::$routes;
	}
	public static function getRoute(){
		return self::$route;
	}
	
	public static function dispatch($url){
		 $url = self::removeQueryString($url);
		 print_r(self::$route);
        if(self::matchRoute($url)){
           $controller = 'app\controllers\\' . self::$route['prefix'] . self::$route['controller'] . 'Controller';
            if(class_exists($controller)){
                $controllerObject = new $controller(self::$route);
                $action = self::lowerCamelCase(self::$route['action']) . 'Action';
                if(method_exists($controllerObject, $action)){
                    $controllerObject->$action();
                    $controllerObject->getView();
                }else{
                    throw new \Exception("Метод $controller::$action не найден", 404);
                }
            }else{
                throw new \Exception("Контроллер $controller не найден", 404);
            }
        }else{
            throw new \Exception("Страница $url не найдена", 404);
        }
    }

	public  static function matchRoute($url){
		foreach(self::$routes as $pattern => $route){
			if(preg_match("#{$pattern}#",$url,$matches)){
				print_r($matches);
				return true;
			}
		}
		return false;
	}
}