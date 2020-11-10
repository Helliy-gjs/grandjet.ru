<?php

class DBException extends Exception {
	
	const CONNECT_ERROR = 0;
	const QUERY_ERROR = 1;
	const QUERY_PARSING_ERROR = 2;
	const SET_CHARSET_ERROR = 3;	
	private $MySQLerrno = 0; 
	
	function __construct($message, $code = 0, $nerr = -1) {
		parent::__construct($message, $code);
		$this->MySQLerrno = $nerr;
	}
	
	function getErrno() {
		return $this->MySQLerrno;
	}

	function __toString() {
		return $this->file.':'.$this->line.' '.$this->code.':'.$this->message;
	}
	
}
?>