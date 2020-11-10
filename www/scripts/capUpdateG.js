var timerId;
var loop = 0;
var loadTimeWait = 30;
var obj = new Image;
var path = '/bhome/part2/01/ritondel/deltar.ru/www/';

function toggle(event) {
	event = event || window.event;
	var clickedElem = event.target || event.srcElement;

	if (clickedElem.tagName == "A" || clickedElem.tagName == "IMG") {
		updateCap();
	}
}

function tm(obj) {
	if (obj.complete) {
		if (obj.width == 0) {
			clearInterval(timerId);
			loop = 0;
			updateCap();
		} else {
			clearInterval(timerId);
			loop = 0;
			document.getElementById("cap").src = obj.src;
		}
	} else {
		loop++;
		if (loop > loadTimeWait) {
			loop = 0;
			clearInterval(timerId);
			updateCap();
		}
	}
}

function updateCapLocal() {
	document.getElementById("cap").src = '/images/caploading.gif';
	var val = new Date().getTime();
	obj.src = "/img.php?" + val;
	clearInterval(timerId);
	tm(obj);
	timerId = setInterval("tm(obj)", 1000);
}


function updateCap() {
	document.getElementById("cap").src = path + '/images/caploading.gif';
	var val = new Date().getTime();
	obj.src = path + "/img.php?" + val;
	clearInterval(timerId);
	tm(obj);
	timerId = setInterval("tm(obj)", 1000);
}

function timeOutUpdate() {
	setInterval('updateCap()', 280000);	
}

function timeOutUpdateLocal() {
	setInterval('updateCapLocal()', 280000);	
}