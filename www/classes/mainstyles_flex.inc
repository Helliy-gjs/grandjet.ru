<?php
?>
<style>
			/*Обнуление*/
*{padding:0;margin:0;border:0;}
*,*:before,*:after{-moz-box-sizing:border-box;-webkit-box-sizing:border-box;box-sizing:border-box;}
:focus,:active{outline:none;}
a:focus,a:active{outline:none;}
nav,footer,header,aside{display:block;}
html,body{height:100%;width:100%;font-size:100%;line-height:1;font-size:14px;-ms-text-size-adjust:100%;-moz-text-size-adjust:100%;-webkit-text-size-adjust:100%;}
input,button,textarea{font-family:inherit;}
input::-ms-clear{display:none;}
button{cursor:pointer;}
button::-moz-focus-inner{padding:0;border:0;}
a,a:visited{text-decoration:none;}
a:hover{text-decoration:none;}
ul li{list-style:none;}
img{vertical-align:top;}
}
<?php
if($Pth['global']['Sizes'][0])$h0f=$Pth['global']['Sizes'][0];
else $h0f= '16px';
if($Pth['global']['Sizes'][1])$h1f=$Pth['global']['Sizes'][1];
else $h1f= '60px';
if($Pth['global']['Sizes'][2])$h2f=$Pth['global']['Sizes'][2];
else $h2f= '42px';
if($Pth['global']['Sizes'][3])$h3f=$Pth['global']['Sizes'][3];
else $h3f= '36px';
if($Pth['global']['Sizes'][4])$h4f=$Pth['global']['Sizes'][4];
else $h4f= '28px';
if($Pth['global']['Sizes'][5])$h5f=$Pth['global']['Sizes'][5];
else $h5f= '24px';
if($Pth['global']['Sizes'][6])$h6f=$Pth['global']['Sizes'][6];
else $h6f= '20px';

echo "<style>
body {
	 font-family: Arial, 'Helvetica Neue', Helvetica, sans-serif; 
	 font-size: $h0f ;  
  }
h1 {
	font-size: $h1f ; 
 }
h2 {
	font-size: $h2f ;
 }
h3 {
	 font-size: $h3f;
 }
h4 {
	 font-size: $h4f ;
 }
h5 {
	 font-size: $h5f;
 }
 h6 {
	 font-size: $h6f;
 }
 
</style>";