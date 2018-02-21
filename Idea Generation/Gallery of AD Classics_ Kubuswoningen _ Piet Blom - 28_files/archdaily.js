(function (w, d) {
  'use strict';
  var s1 = d.getElementsByTagName('script')[0],
  s = d.createElement('script'),
  attr,
  pageFn,
  types,
  onReady;

  types = {
    'Photo': true
  };

  s.src = '//tru.am/scripts/ta-pagesocial-sdk.js';

  attr = function (domQ, name) {
    var l = document.querySelector(domQ);
    if (l) {
      // Use getAttribute() to avoid encoded strings.
      return l.getAttribute(name);
    }
    return undefined;
  };

  pageFn = function () {
    var a = attr('meta[property="archdaily:type"]', 'content'),
        ogtype = attr('meta[property="og:type"]', 'content');
    if (w.TRUE_ANTHEM.isValidPageType(ogtype) && !types[a]) {
      return {
        'canonical': attr('link[rel="canonical"]', 'href'),
        'og:type': ogtype,
        'og:url': attr('meta[property="og:url"]', 'content')
      };
    }
    return {};
  };

  onReady = function () {
    var l = document.location,
        h = l.hostname.toLowerCase(),
        cid;
    if (h.indexOf('archdaily.com') > -1) {
       cid = '576';
    } 
    if (cid) {
      w.TRUE_ANTHEM.configure(cid, {page: pageFn});
    }
  };
  if (s.addEventListener) {
    s.addEventListener('load', onReady, false);
  } else {
    s.onreadystatechange = function () {
      if (s.readyState in {loaded: 1, complete: 1}) {
        s.onreadystatechange = null;
        onReady();
      }
    };
  }
  s1.parentNode.insertBefore(s, s1);
}(window, document));