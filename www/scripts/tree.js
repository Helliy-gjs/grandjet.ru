var nodeA=[];function tree_toggle(d){d=d||window.event;var a=d.target||d.srcElement;if(!hasClass(a,"Expand")){if(a.tagName=="A"&&a.className==""){window.open(a.href,"","")}return}var c=a.parentNode;if(c.lastChild!=a){var e=hasClass(c,"ExpandOpen")?"ExpandClosed":"ExpandOpen";var b=/(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;c.className=c.className.replace(b,"$1"+e+"$3")}else{nodeA[c.id]=c;getData(c.id)}}function recData(n){var d=nodeA[n.documentElement.getElementsByTagName("id")[0].firstChild.nodeValue];var r=n.documentElement.getElementsByTagName("s");var h=r.length;var m=document.createElement("UL");m.className="Container";d.appendChild(m);var c,b;var f=h-1;for(var l=0;l<h;l++){c=document.createElement("A");c.appendChild(document.createTextNode(r[l].firstChild.nodeValue));c.className="Expand";c.setAttribute("href","index.php?id="+r[l].getAttribute("id"));b=document.createElement("LI");b.className="Node ExpandClosed";if(l==f){b.className+=" isLast"}b.id=r[l].getAttribute("id");b.appendChild(c);m.appendChild(b)}r=n.documentElement.getElementsByTagName("e");h=r.length;if(h!=0){var t=document.createElement("TABLE");t.className="goods";var g=document.createElement("TBODY");t.appendChild(g);var o=document.createElement("TR");var e=document.createElement("TD");var q=document.createElement("SPAN");q.appendChild(document.createTextNode("Артикул"));e.appendChild(q);e.onclick=function(){sort(0)};if(sortType==0){if(sortOrder==1){e.firstChild.className="sortU"}else{e.firstChild.className="sortD"}}o.appendChild(e);e=e.cloneNode(true);e.firstChild.className=null;e.firstChild.firstChild.nodeValue="Наименование";e.onclick=function(){sort(1)};if(sortType==1){if(sortOrder==1){e.firstChild.className="sortU"}else{e.firstChild.className="sortD"}}o.appendChild(e);e=e.cloneNode(true);e.firstChild.className=null;e.firstChild.firstChild.nodeValue="Стоимость";e.onclick=function(){sort(2)};if(sortType==2){if(sortOrder==1){e.firstChild.className="sortU"}else{e.firstChild.className="sortD"}}o.appendChild(e);o.className="head";g.appendChild(o);o=o.cloneNode(false);o.appendChild(document.createElement("TD"));o.lastChild.appendChild(document.createTextNode(" "));o.appendChild(document.createElement("TD"));o.lastChild.appendChild(document.createTextNode(" "));o.appendChild(document.createElement("TD"));o.lastChild.appendChild(document.createTextNode(" "));var p;for(var l=0;l<h;l++){o=o.cloneNode(true);o.className="a"+l%2;e=o.firstChild;e.firstChild.nodeValue=r[l].getAttribute("art");e=e.nextSibling;e.removeChild(e.firstChild);p=document.createElement("A");p.appendChild(document.createTextNode(r[l].firstChild.nodeValue));p.setAttribute("href","/detail/?eid="+r[l].getAttribute("id"));p.setAttribute("target","_blank");e.appendChild(p);e=e.nextSibling;e.style.cursor="default";e.firstChild.nodeValue=r[l].getAttribute("price");e.className="r";g.appendChild(o)}m.appendChild(t)}var s=/(^|\s)(ExpandLoading)(\s|$)/;d.className=d.className.replace(s,"$1ExpandOpen$3");return n}function errcb(a){alert(a)}function getData(d){var b=nodeA[d];var a=/(^|\s)(ExpandOpen|ExpandClosed)(\s|$)/;b.className=b.className.replace(a,"$1ExpandLoading$3");var c=makePostRequest("/ajax/getData.php","id="+d+"&sortType="+sortType+"&sortOrder="+sortOrder);c.addCallback(recData);c.addErrback(errcb)}function hasClass(b,a){return new RegExp("(^|\\s)"+a+"(\\s|$)").test(b.className)};