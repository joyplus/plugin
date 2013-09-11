// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

document.write("<scri"+"pt src='jquery.js'></scr"+"ipt>"); 
document.write("<scri"+"pt src='jquery.cookie.js'></scr"+"ipt>"); 

safari.application.addEventListener("validate", validateHandler, true);
safari.application.addEventListener("popover", handlePopoverEvent, true);

var md5_code;
var version = safari.extension.displayVersion;
var client = "Plugin";

function validateHandler(event)
{
	//console.log("validateHandler called");
}
function handlePopoverEvent(event)
{
	//console.log("popoverEvent called");
	if (event.target.identifier !== "showkeyPopovers") return;
	safari.extension.popovers[0].contentWindow.location.reload();
}

function setLocalStorage(name,value)
{
	sessionStorage.md5_code = value;
/*
	try {
    	localStorage.setItem(name, value);
	} catch (e) {
		if (e == QUOTA_EXCEEDED_ERR) 
		{
			alert('Unable to save preferred md5_code.');
		}
	}
*/
}

function removeLocalStorge(name)
{
sessionStorage.clear();
	//sessionStorage.md5_code = null;
}

function getLocalStorage(name)
{
	return sessionStorage.md5_code;
}

function prevalidPinCode() { 

    var pincode = document.getElementById('pingCode').value; 
    if (pincode != '' && pincode.length == 6)
    {
    	//console.log("begin validate pin code");
   		document.getElementById('errorMsg').innerHTML = '验证中...';
 	    document.getElementById('pingCode').disabled = true; 
        
		var xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
		//console.log(xhr);
			if (xhr.readyState==4 && xhr.status==200)
			{

				if (xhr.responseText !== 'false')
				{
					console.log("PIN码正确");
					document.getElementById('errorMsg').innerHTML = 'PIN码验证成功';
					document.getElementById('errorMsg').style.color = "#8ac";
					document.getElementById('pin_statue_empty').style.display = "none";
					document.getElementById('pin_statue_success').style.display = "block";
					document.getElementById('pin_statue_fail').style.display = "none";
					
					//var resp = xhr.responseText;
					//var resp = eval("("+ xhr.responseText + ")");
					var resp = JSON.parse(xhr.responseText);
					//console.log(resp);
					var device = resp.device;
					var channel =  resp.channel;
					var mac = resp.mac;
					var md5 = resp.md5_code;
					
					//$.cookie('md5_code', md5, {expires: 30,path: '/',domain: 'com.joyplus.showkeyassistant-qra5akhkhe'});//com.joyplus.showkeyassistant-qra5akhkhe
					setLocalStorage("md5_code",md5);
	        		
	        		setVideoUrl();
				}
				else
				{
					document.getElementById('currentUrl').value = "";
					console.log("PIN码错误");
					document.getElementById('errorMsg').innerHTML = 'PIN码验证失败,请重新输入';
					document.getElementById('errorMsg').style.color = "#f00";
					document.getElementById('pin_statue_empty').style.display = "none";
					document.getElementById('pin_statue_success').style.display = "none";
					document.getElementById('pin_statue_fail').style.display = "block";
					
					document.getElementById('pingCode').disabled = false;
				}

			}
			else
			{
				console.log("请求失败");
				document.getElementById('errorMsg').innerHTML = '验证请求失败';
				document.getElementById('errorMsg').style.color = "#f00";
				document.getElementById('pin_statue_empty').style.display = "none";
				document.getElementById('pin_statue_success').style.display = "none";
				document.getElementById('pin_statue_fail').style.display = "block";
				
				document.getElementById('pingCode').disabled = false;
			}

		}
		xhr.onerror = function(){
			console.log("请求失败");
			document.getElementById('pin_statue_empty').style.display = "none";
			document.getElementById('pin_statue_success').style.display = "none";
			document.getElementById('pin_statue_fail').style.display = "block";
			document.getElementById('errorMsg').innerHTML = '验证请求失败';
			document.getElementById('pingCode').disabled = false;
		}
		var requestURL = 'http://tt.showkey.tv/preValidatePinCode?pin_code=' + pincode + '&client=' + client +'&version=' + version;
		xhr.open("GET", requestURL, true);
		xhr.send(null);
    }

}

function unbindBtnUp(){
	document.getElementById('unbindImage').src = "http://tvupdate.joyplus.tv/showkeyextension/images/unbind_n.png";
	
	removeLocalStorge("md5_code");
	//setLocalStorage("md5_code",null);
	//$.cookie('md5_code', null, {expires: 30,path: '/',domain: 'com.joyplus.showkeyassistant-qra5akhkhe'});
	document.getElementById('pin_confirmed').style.display="none";
	document.getElementById('inputPinCode').style.display="block";
	document.getElementById('currentUrl').value = "";
	
}
function unbindBtnDown(){
	document.getElementById('unbindImage').src = "http://tvupdate.joyplus.tv/showkeyextension/images/unbind_f.png";
}
function unbindBtnOut(){
	document.getElementById('unbindImage').src = "http://tvupdate.joyplus.tv/showkeyextension/images/unbind_n.png";
}

function confirmBtnOut(){
	document.getElementById('confirmBtnImage').src = "http://tvupdate.joyplus.tv/showkeyextension/images/confirm_btn.png";
}

function confirmBtnDown(){
	document.getElementById('confirmBtnImage').src = "http://tvupdate.joyplus.tv/showkeyextension/images/confirm_btn_active.png";
}

function confirmBtnUp(){	
	document.getElementById('confirmBtnImage').src = "http://tvupdate.joyplus.tv/showkeyextension/images/confirm_btn.png";
	
	var inputurl = document.getElementById('currentUrl').value; 
	//funshion;youku；sina；56；QQ；pptv,letv,sohu,iqiyi
	if((inputurl.indexOf("letv") >= 0) 
	|| (inputurl.indexOf("sohu") >= 0) 
	||(inputurl.indexOf("iqiyi") >= 0) 
	||(inputurl.indexOf("funshion") >= 0) 
	||(inputurl.indexOf("youku") >= 0) 
	||(inputurl.indexOf("sina") >= 0) 
	||(inputurl.indexOf("56") >= 0) 
	||(inputurl.indexOf("qq") >= 0)
	||(inputurl.indexOf("pptv") >= 0)
	||(inputurl.indexOf("ed2k://")>=0)
	||(inputurl.indexOf("magnet:")>=0))
	{ 
/*
		document.getElementById('url_empty').style.display="none";
		document.getElementById('url_correct').style.display="block";
		document.getElementById('url_wrong').style.display="none";
*/		
		md5_code = getLocalStorage("md5_code");		
		//md5_code = $.cookie('md5_code');//getCookie('md5_code');
		console.log(md5_code);
		if (md5_code === undefined || md5_code == null)
		{
			
		}
		else
		{
			var xhr = new XMLHttpRequest();
			xhr.onreadystatechange = function() {
				if (xhr.readyState==4 && xhr.status==200)
				{
					console.log(xhr.responseText);
					if (xhr.responseText == '"allsuccess"')
					{
						console.log("推送成功");
						document.getElementById('url_empty').style.display="none";
						document.getElementById('url_correct').style.display="block";
						document.getElementById('url_wrong').style.display="none";
						document.getElementById('pushResultMsg').innerHTML = '视频推送成功';
						document.getElementById('pushResultMsg').style.color = "#8ac";
					}
					else
					{
						document.getElementById('url_empty').style.display="none";
						document.getElementById('url_correct').style.display="none";
						document.getElementById('url_wrong').style.display="block";
						document.getElementById('pushResultMsg').innerHTML = '解析视频地址失败';
						document.getElementById('pushResultMsg').style.color = "#f00";
					}
				}
			}
			xhr.onerror = function(){
				console.log("error");
				document.getElementById('url_empty').style.display="none";
				document.getElementById('url_correct').style.display="none";
				document.getElementById('url_wrong').style.display="block";
				document.getElementById('pushResultMsg').innerHTML = '解析视频地址失败';
				document.getElementById('pushResultMsg').style.color = "#f00";
			}
			var curTime = new Date().valueOf();
			var requestURL = 'http://tt.showkey.tv/switchScreen?md5_code='+md5_code+'&url='+inputurl+'&msg_type=5' + '&time=' + curTime + '&client=' + client +'&version=' + version;
			console.log(requestURL);
			xhr.open("GET", requestURL, true);
			xhr.send(null);
		}
    }
    else
    {
    	document.getElementById('url_empty').style.display="none";
		document.getElementById('url_correct').style.display="none";
		document.getElementById('url_wrong').style.display="block";
    }
}


function validateMD5Code(md5){
var xhr = new XMLHttpRequest();
		xhr.onreadystatechange = function() {
			if (xhr.readyState==4 || xhr.status==200)
			{
				if (xhr.responseText !== '"fail"')
				{
					console.log("验证成功");
					var pin_confirmed = document.getElementById('pin_confirmed');
					var inputPin = document.getElementById('inputPinCode');
					pin_confirmed.style.display = 'block';
					inputPin.style.display = 'none';
					setVideoUrl();
/*
					var resp = JSON.parse(xhr.responseText);
					var device = resp.device;
					var channel =  resp.channel;
					var mac = resp.mac;
*/
				}
				else
				{
					console.log("验证失败");
					document.getElementById('pin_confirmed').style.display="none";
					document.getElementById('inputPinCode').style.display="block";
				}
			}
			else
			{
				console.log("验证失败");
				document.getElementById('pin_confirmed').style.display="none";
				document.getElementById('inputPinCode').style.display="block";
			}
		}
		xhr.onerror = function(){
			document.getElementById('pin_confirmed').style.display="none";
			document.getElementById('inputPinCode').style.display="block";
		}
		var requestURL = 'http://tt.showkey.tv/preValidateMd5Code?md5_code=' + md5 + '&client=' + client +'&version=' + version;
		console.log(requestURL);
		xhr.open("GET", requestURL, false);
		xhr.send(null);

}

function setVideoUrl(){
	var inputurl = safari.application.activeBrowserWindow.activeTab.url;
	
		if((inputurl.indexOf("letv") >= 0) 
		|| (inputurl.indexOf("sohu") >= 0) 
		||(inputurl.indexOf("iqiyi") >= 0) 
		||(inputurl.indexOf("funshion") >= 0) 
		||(inputurl.indexOf("youku") >= 0) 
		||(inputurl.indexOf("sina") >= 0) 
		||(inputurl.indexOf("56") >= 0) 
		||(inputurl.indexOf("qq") >= 0)
		||(inputurl.indexOf("pptv") >= 0))
		{
			document.getElementById('currentUrl').value = inputurl;
		}
}

document.addEventListener('DOMContentLoaded', function () {

	md5_code = getLocalStorage("md5_code");	
	//md5_code = $.cookie('md5_code');//getCookie('md5_code');//
	console.log(md5_code);
	if (md5_code === undefined || md5_code == null)
	{
		document.getElementById('pin_confirmed').style.display="none";
		document.getElementById('inputPinCode').style.display="block";
	}
	else
	{
		//setTimeout(validateMD5Code(md5_code),1000);
		validateMD5Code(md5_code);
	}
	
	  var pingCode = document.getElementById('pingCode');
	  //var pingCode = document.querySelectorAll('#pingCode');
	  pingCode.addEventListener('keyup', prevalidPinCode);
	  pingCode.addEventListener('blur', prevalidPinCode);
	  
	  
	  var unbindBtn = document.getElementById('unbindBtn');
	  unbindBtn.addEventListener('mouseup', unbindBtnUp);
	  unbindBtn.addEventListener('mouseout', unbindBtnOut);
	  unbindBtn.addEventListener('mousedown', unbindBtnDown);
	  
	  var confirmBtn = document.getElementById('confirmA');
	  confirmBtn.addEventListener('mouseup', confirmBtnUp);
	  confirmBtn.addEventListener('mouseout', confirmBtnOut);
	  confirmBtn.addEventListener('mousedown', confirmBtnDown);

  
  
/*
  var divs = document.querySelectorAll('div');
  for (var i = 0; i < divs.length; i++) {
    divs[i].addEventListener('click', click);
  }
*/
});

