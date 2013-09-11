(function(a) {
    var domain = "tvupdate.joyplus.tv/ipad_plugin",
    //var domain = "localhost:3000",
    baseUrl = "http://" + domain ,
    imgUrl = baseUrl,
    codeUrl = "http://" + domain ,
    siteDomain = domain,
    jQueryloaded = false,
    ua = navigator.userAgent.toLowerCase(),
    currp = "",
    markpic_text = "\u8f93\u5165\u6587\u5b57\u5185\u5bb9",
    curr = null,
    currdesc = "",
    userbuf = {},
    desc = "",
    scurr = 3,
    skip = !1,
    __getElement,
    __getElements;
    function in_array($, _, A) {
        var C = false,
        B, A = !!A;
        for (B in _) {
            if ((A && _[B] === $) || (!A && _[B] == $)) {
                C = true;
                break
            }
        }
        return C
    }
    var baseenc = baseenc || {};
    baseenc.isInt = function($) {
        return /^[0-9]+$/.test($) == false ? false: true
    };
    baseenc.escape = function(_) {
        var $ = this.base64encode(_);
        if ($.indexOf("=") != -1) {
            $ = $.replace(/=/g, "|")
        }
        if ($.indexOf("/") != -1) {
            $ = $.replace(/\//g, "$")
        }
        return $
    };
    baseenc.base64encode = function(B) {
        var D = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
        _, $, A, H, L, J, G, E, C = 0,
        F = 0,
        K = "",
        I = [];
        if (!B) {
            return B
        }
        B = this.utf8_encode(B + "");
        do {
            _ = B.charCodeAt(C++);
            $ = B.charCodeAt(C++);
            A = B.charCodeAt(C++);
            E = _ << 16 | $ << 8 | A;
            H = E >> 18 & 63;
            L = E >> 12 & 63;
            J = E >> 6 & 63;
            G = E & 63;
            I[F++] = D.charAt(H) + D.charAt(L) + D.charAt(J) + D.charAt(G)
        } while ( C < B . length );
        K = I.join("");
        switch (B.length % 3) {
        case 1:
            K = K.slice(0, -2) + "==";
            break;
        case 2:
            K = K.slice(0, -1) + "=";
            break
        }
        return K
    };
    baseenc.utf8_encode = function(A) {
        A = (A + "").replace(/\r\n/g, "\n");
        var C = "",
        _, E, D = 0;
        _ = E = 0;
        D = A.length;
        for (var B = 0; B < D; B++) {
            var $ = A.charCodeAt(B),
            F = null;
            if ($ < 128) {
                E++
            } else {
                if (($ > 127) && ($ < 2048)) {
                    F = String.fromCharCode(($ >> 6) | 192) + String.fromCharCode(($ & 63) | 128)
                } else {
                    F = String.fromCharCode(($ >> 12) | 224) + String.fromCharCode((($ >> 6) & 63) | 128) + String.fromCharCode(($ & 63) | 128)
                }
            }
            if (F != null) {
                if (E > _) {
                    C += A.substring(_, E)
                }
                C += F;
                _ = E = B + 1
            }
        }
        if (E > _) {
            C += A.substring(_, A.length)
        }
        return C
    };
    function addClass(_, $) {
        var A = new RegExp("(^|\\s)" + $ + "(\\s|$)", "g");
        if (A.test(_.className)) {
            return
        }
        _.className = (_.className + " " + $).replace(/\s+/g, " ").replace(/(^ | $)/g, "")
    }
    function httpGet(_) {
        var $ = null;
        return $ = new XMLHttpRequest,
        $.open("GET", _, !1),
        $.send(null),
        $.responseText
    }
    function getHref($) {
        return $ = $ || "",
        $.indexOf("//") == 0 ? $ = location.protocol + $: $.indexOf("http") < 0 && ($ = location.protocol + "//" + location.hostname + $),
        $
    }
    function getAttribute(_, $) {
        return _ && _.getAttribute && _.getAttribute($) || ""
    }
    function getClass($) {
        return getAttribute($, "class")
    }
    function hasClass(_, $) {
        return getClass(_).indexOf($) >= 0
    }
    function isValidImage($) {
        return $.style.display == "none" || $.className == "ImageToPin" || $.width < 31 || $.height < 31 ? !1 : !0
    }
    function tagName($) {
        return ($ && $.tagName || "").toLowerCase()
    }
    
    
    if (!window.$zcoder) {
        window.$zcoder = {
            jq: function(A) {
                if (typeof jQuery == "undefined") {
                    var B = document.getElementsByTagName("head")[0],
                    $ = document,
                    _;
                    _ = $.createElement("script");
                    _.type = "text/javascript";
                    if (this.v == 6) {
                        _.src = "//ajax.aspnetcdn.com/ajax/jQuery/jquery-1.7.js"
                    } else {
                        _.src = "https://ajax.googleapis.com/ajax/libs/jquery/1.7.2/jquery.min.js"
                    }
                    if (typeof B == "undefined") {
                        document.body.appendChild(_)
                    } else {
                        B.appendChild(_)
                    }
                    setTimeout("$zcoder.jq(" + A + ")", 50)
                } else {
                    if (A == 1) {
                        $zcoder.init()
                    }
                }
            },
            isie: function() {
                return /msie/i.test(navigator.userAgent) && !/opera/i.test(navigator.userAgent)
            },
            isch: function() {
                return /Chrome/.test(navigator.userAgent)
            },
            issa: function() {
                return /Safari/.test(navigator.userAgent) && !this.isch()
            },
            isios: function() {
                return navigator.userAgent.match(/iPad/i) != null || navigator.userAgent.match(/iPhone/i) != null || navigator.userAgent.match(/iPod/i) != null || navigator.userAgent.match(/iPod/i) != null
            },
            hdn: function() {
                if ($zcoder.userlist) {
                    $zcoder.userlist.css("display", "none")
                }
            },
            v: /msie/.test(ua) ? parseFloat(ua.match(/msie ([\d.]+)/)[1]) : false,
            addURL: function(B) {
                var A = $___$_z("#markpiccontent"),
                $ = window.location.href,
                _ = "  " + $;
                A.focus();
                if (B.checked) {
                    A.val(A.val().replace("\n", "") + _)
                } else {
                    A.val(A.val().replace(_, ""))
                }
            },
            jsonp: function(_) {
                var $ = document.createElement("script");
                $.setAttribute("type", "text/javascript");
                $.setAttribute("src", _ + "#" + (new Date).getTime());
                document.body.appendChild($);
                this._jp && this._jp.parentNode.removeChild(this._jp);
                return this._jp = $
            },
            init: function() {
                $___$_z = jQuery;
                var panelDiv = document.createElement("div");
                panelDiv.style.textAlign = "center";
                this.panel = $___$_z(panelDiv);
                this.panel.addClass("loading");
               
                $___$_z("body").append(this.panel);

                this.mpWindow = $___$_z(document.createElement("div"));
                this.mpWindow.addClass("mpWindow");
                this.panel.append(this.mpWindow);
                  
                var $ = '<div id="close_button" class="close_button" onClick = "$zcoder.close()"></div><div id="issue" class="issue" onClick = "$zcoder.issue()"></div><div id="videoItems" class="scroll">'
                +'</div>';
                this.mpWindow.html($);
                allUrls = getCurrentPageMagnetsorEd2kUrs();
                initUrlsList(allUrls);
                
            },
            back: function($) {
                
                if ($.op == "login") {
                    userbuf = $.result;
                    if (typeof $zcoder.panel == "undefined") {
                        this.jq(1)
                    } else {
                        
                    }
                } 
            },
            css: function() {
                var _ = [],
                $ = "\u8f93\u5165\u6587\u5b57\u5185\u5bb9";
                _.push(".loading {background: url('" + imgUrl + "/img/back.png'); width:610px; height:484px; position:absolute;z-index: 2147483645; top:50%;left:50%; margin-left:-305px;margin-top:-242px;padding-top: 10px;padding-left: 10px;}");
                _.push(".close_button{     /*padding-top: 130px;*/     /*padding-left: 1225px;*/     margin-right: -18px;     margin-top: -30px;     float: right;     width:48px;     height:48px;     z-index: 2147483646;    background: url('"+ imgUrl + "/img/close.png'); }");
                _.push(".issue{     float: left;     margin-top: 420px;     width:170px;     height:71px;     background:url('"+ imgUrl + "/img/questions.png');     z-index: 2147483646; }");
                _.push(".scroll{     position:absolute; overflow-x:hidden;     overflow-y:auto;     height: 230px;     width: 520px;     margin-left: 50px;     margin-top: 150px;     z-index: 2147483646; }");
                _.push(".filename{     margin-top: 0px;     margin-left: -120px;     left: 70px;     width: 160px;     height: 44px;     position: absolute;     background: url('"+ imgUrl + "/img/filename.png');     z-index: 2147483647; }");
                _.push(".filearea{     margin-top: 0px;     line-height: 44px;     padding-left: 120px;     position: absolute;     float: left;     width: 300px;     overflow: hidden; font-size:15px; color:#76a9d6;     white-space:nowrap; z-index: 2147483647;} ");
                _.push(".switch{     width: 68px;     height: 44px;     margin-top: 0px;     margin-right: 0px;     border: none;     background: url('"+ imgUrl + "/img/button.png') no-repeat center center;     cursor: pointer;     position: absolute;     right: 0; z-index: 2147483647;}");
                _ = _.join("\n");
                $zcoder.style = document.createElement("style");
                $zcoder.style.type = "text/css";
                $zcoder.style.media = "screen";
                if (this.isie()) {
                    $zcoder.style.styleSheet.cssText = _;
                    document.getElementsByTagName("head")[0].appendChild($zcoder.style)
                } else {
                    if (navigator.userAgent.lastIndexOf("Safari/") > 0 && parseInt(navigator.userAgent.substr(navigator.userAgent.lastIndexOf("Safari/") + 7, 7)) < 533) {
                        $zcoder.style.innerText = _
                    } else {
                        $zcoder.style.innerHTML = _
                    }
                    document.body.appendChild($zcoder.style)
                }
            },
            callback: function($) {
                
                if ($.op == "login") {
                    if (typeof $zcoder.panel == "undefined") {
                        this.jq(1)
                    } else {
                        $zcoder.panel.css("display", "block");
                       
                         this.info("", "")
                    }
                } 
            },
            close: function() {
                $zcoder.panel.css("display", "none");
                $zcoder.proceed = false;
                this.info("", "");
            },
            issue: function(){
                var targetUrl = 'http://www.showkey.tv/normal-questions';
                window.open(targetUrl);
            },
            selected: function (m){
                var urlStr = allUrls[m].replace(/\"/g,'');
                var baseurl =  "http://tt.showkey.tv/?url=";
                var encodedUrl =  encodeURIComponent(urlStr);
                var targetUrl = baseurl + encodedUrl;
                
                window.open(targetUrl);
            },
            reverttemphide: function() {
                if (!$zcoder.hiddenTag) {
                    return
                }
                for (var $ = 0; $ < $zcoder.hiddenTag.length; $++) {
                    $zcoder.hiddenTag[$][0].style.display = $zcoder.hiddenTag[$][1]
                }
                $zcoder.hiddenTag = []
            },
            
            info: function($, A) {
                   
                var x=1000;
                var y=1000;               
                if (A == "end") {
                        $zcoder.close()
                }
                
            },
            filters: {

            }
        }
    }
    function getCurrentPageMagnetsorEd2kUrs(d, eImages, opts) {

        var _document = d || document;
        var bodyStr = document.getElementsByTagName("*")[0].innerHTML;
        var reg1 = /"magnet:.+?"/gim;
        var reg2 = /"ed2k:.+?"/gim;
        //|"ed2k:.+"
        //var results = reg.exec(bodyStr);
        var allItems = new Array(document.URL);

        var magnet_matchs = bodyStr.match(reg1);
        var ed2k_matchs = bodyStr.match(reg2)
        return allItems.concat(magnet_matchs,ed2k_matchs);
    }
    function initUrlsList(urls){
        var scroll = document.getElementById("videoItems");   
        for(var url in urls){
            var item = document.createElement("div");
            scroll.appendChild(item);
            var urlStr = urls[url];
            var reg_n = /dn=.*?;/gim;
            var typeName  = '';
            if (url == 0) {
               typeName = urls[0];
            }
            else{
                    if (urlStr.indexOf('magnet')>= 0){
                        typeName = reg_n.exec(urlStr);
                        typeName = decodeURI(typeName);
                        typeName = typeName.replace(/dn=/g,'');
                        if (typeName == null || typeName == "null") {
                           typeName = '磁力链'+(url.toString());
                        }
                    }
                    if (urlStr.indexOf('ed2k')>= 0){
                        typeName = '电驴'+(url.toString());   
                    }
                
                   

            }
            
            item.innerHTML = '<div id = "filename" class="filename" top = "0px"></div>'
                             +'<div class="filearea">'+typeName+'</div>'
                               +'<input type="button" class="switch" onClick = "$zcoder.selected('+ url +')"></input>';
           if(url == 0){
            var f = document.getElementById("filename");
            var currentPage = imgUrl + '/img/webpage.png';
            f.style.background = 'url('+currentPage+')';
           }
            
            item.style.height = "44px";
       }
       // return true;

    }
    function _init() {
        window.scrollTo(0,0);
        if ($zcoder.proceed) {
            $zcoder.close();
            return false
        }
        $zcoder.proceed = true;
        if (typeof $zcoder.panel == "undefined") {
            $zcoder.css();
            
        }
        $zcoder.callback({
            op: "login",
            result: []
        });
        
    }
    var allUrls = null;
    global = "__showkeyassistant";
    document[global] = document[global] || {};
    _init(); 
    (function() {
        document[global].init = _init
    })()
})();
