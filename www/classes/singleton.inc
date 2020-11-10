<?php

abstract class Singleton {

	private static $instanceMap = array();

	protected function __construct() {}

	private final function __clone() {}

	static function getInstance($className) {
		if(!isset(self::$instanceMap[$className])) {
			$object = new $className();
			if($object instanceof Singleton) {
				self::$instanceMap[$className] = $object;
			} else {
				return null;
			}
		}
		return self::$instanceMap[$className];
	}
	
	static function getInstanceinit($className,$par0) {
		//if(!isset(self::$instanceMap['DB'])) {
			unset(self::$instanceMap[$className]);
			$object = new $className($par0);
			if($object instanceof Singleton) {
				self::$instanceMap[$className] = $object;
			} else {
				return null;
			}
	
		return self::$instanceMap[$className];
	}
	
	static function getInstancepar($className,$par0,$par1,$par2,$par3,$par4) {
		//if(!isset(self::$instanceMap['DB'])) {
			unset(self::$instanceMap[$className]);
			$object = new $className($par0,$par1,$par2,$par3,$par4);
			if($object instanceof Singleton) {
				self::$instanceMap[$className] = $object;
			} else {
				return null;
			}
	
		return self::$instanceMap[$className];
	}
}
?>