<?php

class StructureWException extends Exception {
	
	const ID_ERROR = 0;
	const PID_ERROR = 1;
	
	function __construct($message, $code = 0) {
		parent::__construct($message, $code);
	}

	function __toString() {
		return $this->file.':'.$this->line.' '.$this->code.':'.$this->message;
	}
	
}

?>