var Defered=function(){this.chain=[];this.fired=-1;this.paused=0;this.results=[null,null];this.silentlyCancelled=false;this._fire=function(){var d=this.chain;var h=this.fired;var c=this.results[h];var b=this;var a=null;while((d.length>0)&&(this.paused==0)){var g=d.shift()[h];if(!g){continue}try{c=g(c);h=((c instanceof Error)?1:0);if(c instanceof Defered){a=function(f){b._resback(f);b.paused--;if((b.paused==0)&&(b.fired>=0)){b._fire()}};this.paused++}}catch(e){h=1;c=e}}this.fired=h;this.results[h]=c;if((a)&&(this.paused)){c.addBoth(a)}};this._resback=function(a){this.fired=((a instanceof Error)?1:0);this.results[this.fired]=a;this._fire()};this._check=function(){if(this.fired!=-1){if(!this.silentlyCancelled){throw new Error("already called!")}this.silentlyCancelled=false;return}};this.callback=function(a){this._check();this._resback(a)};this.errback=function(a){this._check();if(!(a instanceof Error)){a=new Error(a)}this._resback(a)};this.addBoth=function(a){return this.addCallbacks(a,a)};this.addCallback=function(a){return this.addCallbacks(a)};this.addErrback=function(a){return this.addCallbacks(null,a)};this.addCallbacks=function(a,b){this.chain.push([a,b]);if(this.fired>=0){this._fire()}return this}};function getXmlHttp(){try{return new ActiveXObject("Msxml2.XMLHTTP")}catch(b){try{return new ActiveXObject("Microsoft.XMLHTTP")}catch(a){}}if(typeof XMLHttpRequest!="undefined"){return new XMLHttpRequest()}}function makePostRequest(a,d){var b=getXmlHttp();var c=new Defered();if(!b){alert("Проверьте настройки браузера");return}b.open("POST",a,true);b.onreadystatechange=function(){if(b.readyState!=4){return}if(b.status==200){var f=b.responseXML;if(f.documentElement==null){try{f.loadXML(b.responseText)}catch(g){alert("Загрузка не удалась")}}c.callback(f)}else{c.errback(b.statusText)}};b.setRequestHeader("Content-Type","application/x-www-form-urlencoded");b.send(d);return c};