var nodeA = [];
var storeTableCache = [];
var namepage = '';
var typemenu = '';
var ex='Expand';
var adr='';

//ex= ex + ' '+typemenu;

function defind(namepg,typemn, table){
 namepage = namepg;
 typemenu = typemn;
 tabl=table;
 return typemenu;
} 

function tree_toggle(event) {
    event = event || window.event;
    var clickedElem = event.target || event.srcElement;

    if (!hasClass(clickedElem, 'Expand')) {
        if(clickedElem.tagName == "A" && clickedElem.className == "") {
            window.open(clickedElem.href, '', '');
			//pic=document.getElementById('pictext');
			//document.getElementById("pictext").style.visibility="hidden";
			//pic.setAttribute('attribute', 'block')
        }
		//else pic.setAttribute('display', 'block');
        return;
    }

    var node = clickedElem.parentNode;
	//alert(node.id);
    if (node.lastChild != clickedElem) {
        var newClass = hasClass(node, 'ExpandOpen') ? 'ExpandClosed' : 'ExpandOpen';
        var re = /(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;
        node.className = node.className.replace(re, '$1' + newClass + '$3');
		
    } else {
        nodeA[node.id] = node;
		//alert(nodeA[node.id].id);
		getData(node.id);
		    }
}

function tree_toggle2(event) {
    event = event || window.event;
    var clickedElem = event.target || event.srcElement;

    if (!hasClass(clickedElem, 'Expand')) {
        if(clickedElem.tagName == "A" && clickedElem.className == "") {
            window.open(clickedElem.href, '', '');
        }
        return;
    }

    var node = clickedElem.parentNode;

    if (node.lastChild != clickedElem) {
        var newClass = hasClass(node, 'ExpandOpen') ? 'ExpandClosed' : 'ExpandOpen';
        var re = /(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;
        node.className = node.className.replace(re, '$1' + newClass + '$3');
    } else {
        nodeA[node.id] = node;
        getData2(node.id);
    }
}

function tree_toggle3(event) {
    event = event || window.event;
    var clickedElem = event.target || event.srcElement;

    if (!hasClass(clickedElem, 'Expand')) {
        if(clickedElem.tagName == "A" && clickedElem.className == "") {
            window.open(clickedElem.href, '', '');
        }
        return;
    }

    var node = clickedElem.parentNode;
	
    if (node.lastChild != clickedElem) {
        var newClass = hasClass(node, 'ExpandOpen') ? 'ExpandClosed' : 'ExpandOpen';
        var re = /(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;
        node.className = node.className.replace(re, '$1' + newClass + '$3');
		
    } else {
        nodeA[node.id] = node;
		getData2(node.id);
		    }
}

function recDataB(res) {
    var node = nodeA[res.documentElement.getElementsByTagName("id")[0].firstChild.nodeValue];
    var doc = res.documentElement.getElementsByTagName("s");
    var j = doc.length;
    var ul = document.createElement("UL");
    ul.className = "Container";
    node.appendChild(ul);
    var el, le;
    var k = j - 1;
    for (var i = 0; i < j; i++) {
        el = document.createElement("A");
        el.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
        el.className = "Expand";
        el.setAttribute("href", "index.php?id=" + doc[i].getAttribute("id"));
        le = document.createElement("LI");
        le.className = "Node ExpandClosed";
        if (i == k)
            le.className += " isLast";
        le.id = doc[i].getAttribute("id");
        le.appendChild(el);
        ul.appendChild(le);
    }
    doc = res.documentElement.getElementsByTagName("e");
    j = doc.length;
    if(j != 0) {
    	var storeDiv = document.getElementById("storeDiv");
        var table = document.createElement("TABLE");
        table.className = "goods";
        var tb = document.createElement("TBODY");
        table.appendChild(tb);
        var tr = document.createElement("TR");
        var td = document.createElement("TD");
        var span = document.createElement("SPAN");
        span.appendChild(document.createTextNode("Артикул"));
        td.appendChild(span);
        td.onclick = function() {
            sort(0);            
        };
        if(sortType == 0) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }        
        tr.appendChild(td);
        td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Наименование";
        td.onclick = function() {
            sort(1);            
        };
        if(sortType == 1) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }
        tr.appendChild(td);
        td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Стоимость";
        td.onclick = function() {
            sort(2);            
        };
        if(sortType == 2) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }
        tr.appendChild(td);
        tr.className = "head";
        tb.appendChild(tr);
        tr = tr.cloneNode(false);
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        var a;
        for(var i = 0; i < j; i++) {
            tr = tr.cloneNode(true);
            tr.className = 'a'+i%2;
            td = tr.firstChild;
            td.firstChild.nodeValue = doc[i].getAttribute("art");
            td = td.nextSibling;
            td.removeChild(td.firstChild);
            a = document.createElement("A");
            a.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
            a.setAttribute("href", "/detail/?eid=" + doc[i].getAttribute("id"));
            a.setAttribute("target", "_blank");
            td.appendChild(a);
            td = td.nextSibling;
            td.style.cursor = "default";
            td.firstChild.nodeValue = doc[i].getAttribute("price");
            td.className = "r";
            tb.appendChild(tr);
        }
        storeDiv.replaceChild(table, storeDiv.firstChild);
        //storeDiv.appendChild(table);
    }
    var re = /(^|\s)(ExpandLoading)(\s|$)/;
    node.className = node.className.replace(re, '$1' + 'ExpandOpen' + '$3');
    return res;
}
function new_window(adr) {
	window.open(adr,'newwin','top=15, left=20, menubar=0, toolbar=0, location=0, directories=0, status=0, scrollbars=0, resizable=0, width=400, height=300');
	//window.open('http://shop.deltar.ru','newwin','top=15, left=20, menubar=0, toolbar=0, location=0, directories=0, status=0, scrollbars=0, resizable=0, width=400, height=300');
}

function recData(res) {
	//var typemenu = defind("index.php","Container");
	//alert(document.getElementByTagName("id")[0].innerHTML);
	//alert(res.documentElement.getElementsByTagName("id")[0].firstChild.nodeValue);
	var node = nodeA[res.documentElement.getElementsByTagName("id")[0].firstChild.nodeValue];
    var doc = res.documentElement.getElementsByTagName("s");
	//alert(recData.arguments.length);
    var j = doc.length;
    var ul = document.createElement("UL");
    ul.className = "Container";
	//ul.setAttribute("class", typemenu);
    node.appendChild(ul); 
    var el, le;
    var k = j - 1;
    for (var i = 0; i < j; i++) {
        el = document.createElement("A");
        el.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
        el.className = "Expand";
        el.setAttribute("href", namepage + "?id=" + doc[i].getAttribute("id"));
        le = document.createElement("LI");
		/*le.onload = function{
		alert("загружен")};*/
		//le.className = typemenu + ' ' + ex + "Closed";
        le.className = "Node ExpandClosed";
        if (i == k)
            le.className += " isLast";
        le.id = doc[i].getAttribute("id");
        le.appendChild(el);
        ul.appendChild(le);
    }
    doc = res.documentElement.getElementsByTagName("e");
    j = doc.length;
	//alert(j);
    if(j != 0) {
		//var storeDiv = document.getElementById("storeDiv");
        var table = document.createElement("TABLE");
        table.className = "goods";
        var tb = document.createElement("TBODY");
        table.appendChild(tb);
        var tr = document.createElement("TR");
        var td = document.createElement("TD");
        var span = document.createElement("SPAN");
        span.appendChild(document.createTextNode("Код производителя"));
        td.appendChild(span);
        td.onclick = function() {
            sort(0);            
        }
        if(sortType == 0) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }        
        tr.appendChild(td);
        td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Наименование";
        td.onclick = function() {
            sort(1);            
        }
        if(sortType == 1) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }
        tr.appendChild(td);
        td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Цена,$USA";
        td.onclick = function() {
            sort(2);            
        }
        if(sortType == 2) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }
		tr.appendChild(td);
		var td2 = document.createElement("TD");
		var span2 = document.createElement("SPAN");
        span2.appendChild(document.createTextNode("Доступность"));
        td2.appendChild(span2);
		tr.appendChild(td2);
		var td3 = document.createElement("TD");
		var span3 = document.createElement("SPAN");
        span3.appendChild(document.createTextNode("для заказа"));
        td3.appendChild(span3);
		tr.appendChild(td3);
		var td4 = document.createElement("TD");
		var span4 = document.createElement("SPAN");
        span4.appendChild(document.createTextNode("Дата транзита"));
        td4.appendChild(span4);
		tr.appendChild(td4);
		tr.className = "head";
        tb.appendChild(tr);
        tr = tr.cloneNode(false);
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
		tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
		tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
		tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        var a;
        for(var i = 0; i < j; i++) {
            tr = tr.cloneNode(true);
            tr.className = 'a'+i%2;
            td = tr.firstChild;
            td.firstChild.nodeValue = doc[i].getAttribute("art");
            td = td.nextSibling;
            td.removeChild(td.firstChild);
            a = document.createElement("A");
            a.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
            //a.setAttribute("href", "./book/show_book.php?isbn=" + doc[i].getAttribute("codeGJS"));
			a.setAttribute("href", "./detail.php?eid=" + doc[i].getAttribute("id"));
            //a.setAttribute("target", "_blank");
            td.appendChild(a);
            td = td.nextSibling;
            td.style.cursor = "default";
            td.firstChild.nodeValue = doc[i].getAttribute("price");
			td = td.nextSibling;
			td.style.cursor = "default";
			if (doc[i].getAttribute("ls") > 2)	{doc[i].setAttribute("stock","?");text_order="Уточнить условия поставки";}		
			else {text_order="Заказать";
			if (doc[i].getAttribute("stock") > 10)  {doc[i].setAttribute("stock","|||||||"); text_order+=" со склада";}
			else {if (doc[i].getAttribute("stock") > 2)  {doc[i].setAttribute("stock","|||||");}
					else {if (doc[i].getAttribute("stock") > 1)  {doc[i].setAttribute("stock","|||");text_order+=" со склада";}
					else {if (doc[i].getAttribute("stock") > 0)  {doc[i].setAttribute("stock","|");text_order+=" со склада";}
					else  {doc[i].setAttribute("stock","?");text_order+=" из транзита";}}}}}
			
            td.firstChild.nodeValue = doc[i].getAttribute("stock");
			td = td.nextSibling;
			td.removeChild(td.firstChild);
			a = document.createElement("A");
			a.appendChild(document.createTextNode(text_order));
			//a.setAttribute("href", "./?new=" + doc[i].getAttribute("codeGJS"));
			a.setAttribute("href", "./book/show_cart.php?new=" + doc[i].getAttribute("codeGJS"));
			a.setAttribute("target", "newcart");
			// вариант открытия корзины 
			//a.setAttribute("href", new_window("./book/show_cart.php?new=" + doc[i].getAttribute("codeGJS")));
			//конец варианта
			td.appendChild(a);
			td = td.nextSibling;
            td.style.cursor = "default";
			if (doc[i].getAttribute("date2")=="1900-01-00") doc[i].setAttribute("date2","");
			if (doc[i].getAttribute("date2")=="1900-01-01") doc[i].setAttribute("date2","");
            td.firstChild.nodeValue = doc[i].getAttribute("date2");
			td.className = "r";
            tb.appendChild(tr);
			}
        //storeDiv.replaceChild(table, storeDiv.firstChild);
		//document.getElementById("storeDiv").style.visibility="hidden";
		//alert(document.getElementById("storeDiv").className);
        document.getElementById(node.id).lastChild.appendChild(table);
		//storeDiv.replaceChild(table, storeDiv.firstChild);
    }
    var re = /(^|\s)(ExpandLoading)(\s|$)/;
    node.className = node.className.replace(re, '$1' + 'ExpandOpen' + '$3');
    return res;
}

function recData2(res) {
	//var typemenu = defind("index.php","Menu");
	var node = nodeA[res.documentElement.getElementsByTagName("id")[0].firstChild.nodeValue];
    var doc = res.documentElement.getElementsByTagName("s");
	
	function innermenu(aa){
	var storeDiv = document.getElementById("storeDiv");
	var table = document.createElement("TABLE");
        table.className = "goods";
        var tb = document.createElement("TBODY");
        table.appendChild(tb);
        var tr = document.createElement("TR");
        var td = document.createElement("TD");
        var span = document.createElement("SPAN");
		for(var i = 0; i < j; i++) {
        span.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
        td.appendChild(span);
		tr.appendChild(td);
		tb.appendChild(tr);
		//tr = tr.cloneNode(false);
		}
		document.getElementById(node.id).lastChild.appendChild(table);
		storeDiv.appendChild(table);
	}
	
	function innerFM(aa) {
	var storeDiv = document.getElementById("storeDiv");
    var table = document.createElement("TABLE");
	var a;
	var ul = document.createElement("UL");
    //ul.className = "Container";
	ul.setAttribute("class", typemenu);
    node.appendChild(ul);
    table.className = "block1";
    var tb = document.createElement("TBODY");
    table.appendChild(tb);
    var tr = document.createElement("TR");
    var td = document.createElement("TD");
	for(var i = 0; i < j; i++) {
		a = document.createElement("A");
        a.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
		a.setAttribute("href", "./detail.php/?eid=" + doc[i].getAttribute("id"));
        a.setAttribute("target", "_blank");
        td.appendChild(a);
		tr.appendChild(td);
		tb.appendChild(tr);
		tr = tr.cloneNode(false);
		td = document.createElement("TD");
		}
        document.getElementById(node.id).lastChild.appendChild(table);
		//storeDiv.appendChild(table);
		/*var index=0;
		if (!index) {
		storeDiv.removeChild(storeDiv.firstChild);
		index++;*/
    }
	
function inner2(aa) {
		var storeDiv = document.getElementById("storeDiv");
        var table = document.createElement("TABLE");
        table.className = "goods";
        var tb = document.createElement("TBODY");
        table.appendChild(tb);
        var tr = document.createElement("TR");
        var td = document.createElement("TD");
        var span = document.createElement("SPAN");
        span.appendChild(document.createTextNode("PN"));
        td.appendChild(span);
        td.onclick = function() {
            sort(0);            
        }
        if(sortType == 0) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }        
        tr.appendChild(td);
        td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Наименование";
        td.onclick = function() {
            sort(1);            
        }
        if(sortType == 1) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }
        tr.appendChild(td);
        td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Стоимость";
        td.onclick = function() {
            sort(2);            
        }
        if(sortType == 2) {
        	if(sortOrder == 1) {
        		td.firstChild.className = "sortU";	
        	} else {
        		td.firstChild.className = "sortD";
        	}
        }
		tr.appendChild(td);
		var td2 = document.createElement("TD");
		var span2 = document.createElement("SPAN");
        span2.appendChild(document.createTextNode("Cклад"));
        td2.appendChild(span2);
		tr.appendChild(td2);
		var td3 = document.createElement("TD");
		var span3 = document.createElement("SPAN");
        span3.appendChild(document.createTextNode("Заказ"));
        td3.appendChild(span3);
		tr.appendChild(td3);
		var td4 = document.createElement("TD");
		var span4 = document.createElement("SPAN");
        span4.appendChild(document.createTextNode("codeGJS"));
        td4.appendChild(span4);
		tr.appendChild(td4);
		tr.className = "head";
        tb.appendChild(tr);
        tr = tr.cloneNode(false);
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
		tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
		tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
		tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        var a;
        for(var i = 0; i < j; i++) {
            tr = tr.cloneNode(true);
            tr.className = 'a'+i%2;
            td = tr.firstChild;
            td.firstChild.nodeValue = doc[i].getAttribute("art");
            td = td.nextSibling;
            td.removeChild(td.firstChild);
            a = document.createElement("A");
            a.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
            a.setAttribute("href", "./book/show_book.php?isbn=" + doc[i].getAttribute("codeGJS"));
			//a.setAttribute("href", "./detail/?eid=" + doc[i].getAttribute("codeGJS"));
            a.setAttribute("target", "_blank");
            td.appendChild(a);
            td = td.nextSibling;
            td.style.cursor = "default";
            td.firstChild.nodeValue = doc[i].getAttribute("price");
			td = td.nextSibling;
			td.style.cursor = "default";
            td.firstChild.nodeValue = doc[i].getAttribute("ms");
			td = td.nextSibling;
			td.removeChild(td.firstChild);
			a = document.createElement("A");
			a.appendChild(document.createTextNode("Заказать"));
			a.setAttribute("href", "./book/show_cart.php?new=" + doc[i].getAttribute("codeGJS"));
            a.setAttribute("target", "_blank");
			td.appendChild(a);
			td = td.nextSibling;
            td.style.cursor = "default";
            td.firstChild.nodeValue = doc[i].getAttribute("codeGJS");
            td.className = "r";
            tb.appendChild(tr);
			}
        //storeDiv.replaceChild(table, storeDiv.firstChild);
		//document.getElementById("storeDiv").style.visibility="hidden";
		//alert(document.getElementById("storeDiv").className);
        document.getElementById(node.id).lastChild.appendChild(table);
		//storeDiv.replaceChild(table, storeDiv.firstChild);
		storeDiv.appendChild(table);
		var index=0;
		if (!index) {
		storeDiv.removeChild(storeDiv.firstChild);
		index++;
		}
    }
	function inner3(aa) {
		var storeDiv = document.getElementById("storeDiv");
        var table = document.createElement("TABLE");
        table.className = "goods";
        var tb = document.createElement("TBODY");
        table.appendChild(tb);
        var tr = document.createElement("TR");
        var td = document.createElement("TD");
        var span = document.createElement("SPAN");
        span.appendChild(document.createTextNode(doc[0].getAttribute("desc")));
        td.appendChild(span);
        tr.appendChild(td);
        tr.className = "head";
        tb.appendChild(tr);
        //tr = tr.cloneNode(true);
        /*tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode("ИБП не обеспечивают безопасность Ваших компьютеров в проблемных электрических сетях "));
        //var a;
        //for(var i = 0; i < j; i++) {
            tr = tr.cloneNode(true);
            tr.className = 'desc';
            td = tr.firstChild;
			td.firstChild.nodeValue = doc[0].getAttribute("desc");
			/*a = document.createElement("A");
            a.appendChild(document.createTextNode(doc[0].firstChild.nodeValue));
			td.appendChild(a);*/
			tr.appendChild(td);
            td.className = "r";
            tb.appendChild(tr);
		//	}
        document.getElementById(node.id).lastChild.appendChild(table);
		//storeDiv.replaceChild(table, storeDiv.firstChild);
		storeDiv.appendChild(table);
		//var index=0;
		//if (!index) {
		storeDiv.removeChild(storeDiv.firstChild);
		//index++;
		//}
    }
	
	function inneright(aa) {
		var storeDiv = document.getElementById("storeDiv");
		storeDiv.innerHTML='источник';
        var table = document.createElement("TABLE");
        table.className = "goods";
        var tb = document.createElement("TBODY");
        table.appendChild(tb);
        var tr = document.createElement("TR");
        var td = document.createElement("TD");
        var span = document.createElement("SPAN");
        span.appendChild(document.createTextNode("PN"));
        td.appendChild(span);
		tr.appendChild(td);
		td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Наименование";
		tr.appendChild(td);
        td = td.cloneNode(true);
        td.firstChild.className = null;
        td.firstChild.firstChild.nodeValue = "Стоимость";
		tr.className = "head";
        tb.appendChild(tr);
		tr = tr.cloneNode(false);
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
        tr.appendChild(document.createElement("TD"));
        tr.lastChild.appendChild(document.createTextNode(" "));
		var a;
            tr = tr.cloneNode(true);
            tr.className = 'a'+i%2;
            td = tr.firstChild;
            td.firstChild.nodeValue = doc[0].getAttribute("art");
            td = td.nextSibling;
            td.removeChild(td.firstChild);
            a = document.createElement("A");
            a.appendChild(document.createTextNode(doc[0].firstChild.nodeValue));
            //a.setAttribute("href", "./book/show_book.php?isbn=" + doc[0].getAttribute("codeGJS"));
			a.setAttribute("href", "./detail/?eid=" + doc[i].getAttribute("id"));
            a.setAttribute("target", "_blank");
            td.appendChild(a);
		tb.appendChild(tr);
		
		document.getElementById(node.id).lastChild.appendChild(table);
		storeDiv.replaceChild(table, storeDiv.firstChild);
	}
	
	//alert(recData.arguments.length);
    var j = doc.length;
	var ul = document.createElement("UL");
    //ul.className = "Container";
	ul.setAttribute("class", typemenu);
    node.appendChild(ul); 
    var el, le;
    var k = j - 1;
	
    for (var i = 0; i < j; i++) {
        el = document.createElement("A");
        el.appendChild(document.createTextNode(doc[i].firstChild.nodeValue));
        /*if (typemenu=='Menu'){
		ex=ex+typemenu; 
		alert(ex);
		el.className = ex;
		}
		else {
		alert(ex);*/
		el.className = ex;
		ex='Expand';
        el.setAttribute("href", namepage + "?id=" + doc[i].getAttribute("id"));
        le = document.createElement("LI");
		if (typemenu=="Node"){
		le.className = typemenu + ' ' + ex + "Closed";
		}
		else {
        le.className = typemenu + ' ' + ex + "Closed";
		}
        if (i == k)
            le.className += " isLast";
        le.id = doc[i].getAttribute("id");
        le.appendChild(el);
        ul.appendChild(le);
		//if(j != 0) {inneright(doc)}
    }
	
    doc = res.documentElement.getElementsByTagName("e");
    j = doc.length;
	if(j != 0) {
	//alert(typemenu);
	if(typemenu == "Menu") innerFM(doc); 
	else inner2(doc);
	}
			    var re = /(^|\s)(ExpandLoading)(\s|$)/;
    node.className = node.className.replace(re, '$1' + 'ExpandOpen' + '$3');
    return res;
}

function errcb(res) {
    alert(res);
}

function getData(id) {
    var node = nodeA[id];
    var re = /(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;
    node.className = node.className.replace(re, '$1' + 'ExpandLoading' + '$3');
	//alert(tabl);
    var def = makePostRequest('/ajax/getData.php', 'id=' + id + '&sortType=' + sortType + '&sortOrder=' + sortOrder + '&tabl=' + tabl);
    def.addCallback(recData);
	def.addErrback(errcb);
}

function getData2(id) {
    var node = nodeA[id];
    var re = /(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;
    node.className = node.className.replace(re, '$1' + 'ExpandLoading' + '$3');
    var def = makePostRequest('./ajax/getData.php', 'id=' + id + '&sortType=' + sortType + '&sortOrder=' + sortOrder );
    def.addCallback(recData2);
    def.addErrback(errcb);
}

function getData3(id) {
    var node = nodeA[id];
    var re = /(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;
    node.className = node.className.replace(re, '$1' + 'ExpandLoading' + '$3');
    var def = makePostRequest('./ajax/getData.php', 'id=' + id + '&sortType=' + sortType + '&sortOrder=' + sortOrder);
    def.addCallback(recData2);
    def.addErrback(errcb);
}

function hasClass(elem, className) {
    return new RegExp("(^|\\s)" + className + "(\\s|$)").test(elem.className);
}

function autorization() {
var container = document.createElement('a');
container.innerHTML = 'header(`Location: http://`.$_SERVER["HTTP_HOST"].`/auth/`);';
}
