<?php

class ElementsWException extends Exception {
	
	function __construct($message, $code = 0) {
		parent::__construct($message, $code);
	}

	function __toString() {
		return $this->file.':'.$this->line.' '.$this->code.':'.$this->message;
	}
}

?>