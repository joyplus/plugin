function clickHandler (e) {
    var url = e.pageUrl;
    var basePostUrl = "http://tt.showkey.tv/?";

    if (e.linkUrl) {
        // The user wants to click a link.
        url = e.linkUrl;
        if (url.indexOf('tt.showkey.tv/?url=') > 0) {
            // 26 is the index value of htttp://tt.showkey.tv/?url=
            url = url.slice(26);
        }
    }

    basePostUrl += "url=" + encodeURIComponent(url);

    // Open the page up.
    chrome.tabs.create({"url" : basePostUrl });
};

chrome.contextMenus.removeAll();
chrome.contextMenus.create({
    "title": "转屏推电视",
    "type": "normal",
    "contexts":["page","link","video"],
    "onclick": clickHandler
});