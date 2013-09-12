
//cross-browser event handling for IE5+, NS6 and Mozilla
//This addEvent function we are using for external class use
this.addEvent = function(elm, evType, fn, useCapture) {
    if (elm.addEventListener) { // Mozilla, Netscape, Firefox
        elm.addEventListener(evType, fn, useCapture);
        return true;
    } else if (elm.attachEvent) {  // IE5 +
        var r = elm.attachEvent('on' + evType, fn);
        return r;
    } else {
        elm['on' + evType] = fn;
    }
}

function myPopup(className) {
    var matchedElement = document.getElementsByClassName(className);
    for (var i = 0; i < matchedElement.length; i++) {
        addEvent(matchedElement[i], 'click', elementClicked, false);
        var magnetUrl = matchedElement[i].href;
    }
    console.log('matchedElement', matchedElement)
}

function stopBubble(e) {
    if(e && e.stopPropagation){
        e.stopPropagation();
    } else {
        // IE method
        window.event.cancelBubble = true;
    }
}

function getElement(id) {
    return document.getElementById(id);
}

function elementClicked(clickedElement) {
    var clickedWindowLeft = clickedElement.pageX + 'px';
    var clickedWindowTop = clickedElement.pageY + 'px';
    var container = getElement('popupContainer');
    var iframebox = getElement('iframebox');

    // http://tvupdate.joyplus.tv/tt_popup
    iframebox.src = 'http://localhost:8030/popup.html';
    clickedElement.toElement.parentNode.appendChild(container);
    container.style.display = 'block';
    container.style.top = clickedWindowTop;
    container.style.left = clickedWindowLeft;
    stopBubble(clickedElement);
}

addEvent(document, 'click', documentClick, false);

function documentClick() {
    var container = getElement('popupContainer');
    container.style.display = 'none';
    stopBubble(document);
}