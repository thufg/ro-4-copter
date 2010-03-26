/***********************************************************************
JQUERY CSXGLOBAL
@author => Keegan Watkins

NOTE: This file is loaded into EVERY PAGE IN CLEARSPACE. Therefore, please be aware that errors, exceptions, or bugs here are likely to cause major
problems within CSX. This file is structured as a sub-library; all code here is executed without introducing any global variables or functions.
***********************************************************************/
/* $Change: 2290996 $ $DateTime: 2008/04/01 00:06:48 $ $Revision: #7 $ */

// This function is self-executing, and passes in jQuery as an argument. This allows all code here 
// to play nicely with other libs, because "$" is aliased to the jQuery object. See last line for details.
(function($) {
	
	// Create namespace for CSX:
	$.CSX = {};
	
	// Apply any global functionality here, fired on DOM ready:
	$(function() {
		// Select <a> tags with an HREF that contains "/feeds/", and apply the proxy
		/*$("a[@href*=/feeds/]").proxyFeedLinks();*/
		// Pull the background images from the dropdown links
		$("#jive-userbar-droplink").find("a[@class^=jive-link]").css("background","none"); 
		// Fix the seach bar on pages where it is descendant of <div class="jive-sidebar"/>
		$("div.jive-sidebar h4:contains('Community Search')").css("marginLeft","8px").parents("div.jive-widget").css({marginBottom: "25px","-moz-border-radius" : "5px"});
		// Add the required verbiage to the search box
		$("#jive-userbar-right").append("<span id='userbar-search-label'>Search within community:</span>");
		// Rewrite the <input/> tags which create custom feeds
		/*$("#tag, #username").css("margin", "0 3px").rewriteUserTagCells();*/
		// Override default tag building functions by reassigning to one handler.
		/*window.keyMaker = window.userKeyMaker = window.tagKeyMaker = jQuery.userTagInputHandler;*/
		// Find extenal links, and set their "target" attribute to "_blank"
		$("div.jive-rendered-content a").flagAsExternal();
	});
	
	// The window.location property needs to be cast as a string...
	var _location = window.location.toString();
	// Pull the "relative" location i.e. strip off the "http://decibel.ni.com"...
	var _domain = "http://" + window.document.domain;
	var _relative_location = _location.substring(_location.indexOf(_domain) + _domain.length, _location.length);
	// Extract the document's query string (if present, set to empty string '' otherwise)...
	var _locationQueryString = _location.lastIndexOf("?") > -1 ? _location.substring(_location.lastIndexOf("?"), _location.length) : "" ;
	var _needle = "/content/";
	var _loc_sub = _location.substring(_location.indexOf(_needle) + _needle.length, _location.length); 
	// ...and also the "keyword", i.e. "groups", "blogs", or "community"
	_key = _loc_sub.substring(0,_loc_sub.indexOf("/"));
	// Add cases: If the keyword is "people", use "community". If the keyword is empty and it appears we're on a search page, use "community"
	if (_key == "people" || (_key == "" && _location.indexOf("search.jspa") > -1)) { _key = "community" }
	$.CSX.pageData = {
		relativePath : _relative_location,
		documentQueryString : _locationQueryString,
		keyword : _key 
	};
	
	/* Wrapped set extensions, i.e. mthods to manipulate and return the wrapped set of elements */
	$.fn.extend({
		proxyFeedLinks : function() {
			return this.each(function() {
				var elem = $(this); // Only create the jQuery wrapper object once, store as local variable to increase performance.
				var original_href = elem.attr("href") // i.e 'http://decibel.ni.com/content/keyword/feeds/blahblah' or '/content/keyword/feeds/blahblah'
				// If there are [rel="alternate"] and [type="application/rss+xml"] attributes, this is a <link/> tag. Use this data to determine the first param of the proxied feed.
				var feedType = (elem.attr("rel") === "alternate" && elem.attr("type") === "application/rss+xml") ? "ad" : "s";
				// Define start and end flags
				var beforePhrase = "/content/";
				var afterPhrase = "/feeds/";
				// References to content before and after flags
				var beforeKeyWord = original_href.substring(original_href.indexOf(beforePhrase) + beforePhrase.length, original_href.length);
				var afterKeyWord = original_href.substring(original_href.indexOf(afterPhrase) + afterPhrase.length, original_href.length)
				// Reference to the keyword, defined as being between the flags
				var keyword = beforeKeyWord.substring(0, beforeKeyWord.indexOf(afterPhrase));
				var proxied_link = "http://nifeeds.ni.com/" + feedType + "?px_cs=data&px_code=" + keyword + "&px_path=" + encodeURI(afterKeyWord)
				// Set the HREF to the string above
				elem.attr("href", proxied_link);
				// If the link text looks like an HREF (by checking the text for the href string above) rewrite to match HREF
				if (elem.text().indexOf(original_href) > -1) {
					elem.text(proxied_link);
				}
			});
		},
		flagAsExternal : function() {
			return this.each(function() {
				
				// First, check for "ni.com" anywhere in the href...
				if (this.href.indexOf("ni.com") > -1) {
					// Store the matches
					var matches = parseURL(this.href);
					// If the RegExp found matches, and there is a third match...
					if (matches !== null && matches[2]) {
						// Check the third match (which represents the host) for presence of "ni.com"
						if (matches[2].indexOf("ni.com") === -1) {
							// If found, open this link in a new window
							$(this).attr("target", "_blank")
						}
					}
				// "ni.com" not in href, treat as external
				} else {
					$(this).attr("target", "_blank")
				}
				
				function parseURL(url/* :String */) {
					// ['url', 'protocol', 'host', 'port', 'path', 'query', 'hash'];
					return /^(?:([A-Za-z]+):)(?:\/{0,3})([0-9.\-A-Za-z]+)(?::(\d+))?(?:\/([^?#]*))(?:\?([^#]*))?(?:#(.*))?$/.exec(url);			
				}
			});
		},
		rewriteUserTagCells : function() {
			return this.each(function() {
				// Reference to the <input/> element
				var elem = $(this);
				// Store a cloned copy. NOTE: This only works because by default, the event handlers for these elements are stored as inline
				// attributes i.e. <input id='tags' keypress='userTagInputHandler'/>. If we remove the inline handlers, the clone() method WILL NOT
				// copy the registered events in IE.
				var clone = elem.clone().empty();
				// Reference to the parent <td> element
				var parent = elem.parents("td");
				// Reference to either "tag" or "users"
				var type = elem.attr("id") === "username" ? "users" : "tags"; 
				parent
					// ...then replace the text with the SimpleFeeds URL...
					.text("http://nifeeds.ni.com/s?px_cs=data&px_code=" + $.CSX.pageData.keyword + "&px_path=" + type + "/")
					// ...and then add the cloned <input/> tag...
					.append(clone)
					// ...and then add the query string
					.append($.CSX.pageData.documentQueryString);
			});
		}
	});
	
	/* jQuery Core extensions, i.e. properties of the jQuery object */
	$.extend({
		userTagInputHandler : function(e) {
			e = e || window.event;
			if (e.type == 'keypress' && e.keyCode == 13) {
				// Reference to the <input/> tag's value
				var query = $.browser.msie ?  e.srcElement.value : e.currentTarget.value;
				// Reference to the element
				var elem = $(e.srcElement) || $(e.currentTarget);
				// Reference to the type of feed
				var type = elem.attr("id") === "username" ? "users" : "tags";
				// Reconstruct the relative path as "/ {type} / {query} {documentQueryString}
				var search_path = type +"/"  + query + "/"+ $.CSX.pageData.documentQueryString;
				// Create SimpleFeeds URL in the form http://nifeeds.ni.com/s?px_cs=data&px_code=[keyword here]&px_path=[ /{type}/ {value of input} {query string}]
				var fullURL = "http://nifeeds.ni.com/s?px_cs=data&px_code=" + $.csxPageData.keyword + "&px_path=" +  encodeURI(search_path);
				// Finally, set the window location to the string above
				window.location.href = fullURL;
			}
		},
		docTypeSelected : function() {
			// Determine whether "Create Doc" or "Upload Doc" was chosen...
			var type = $(this).attr("id") == "jive-doc-type-write" ? "doc" : "upload";
			var isUpload = type == "upload" ? "true" : "false";
			// Reset the class to only match the current selection
			$("#jive-choose-container-quick").attr("class", "jive-choose-doc-type-" + type).slideDown("slow");
			// Reset the <input id='ni-doc-type-select'/> to reflect true {is an upload} of false {is a new doc}
			$("#ni-doc-type-select").val(isUpload);
		}
	});	
	
	/* Global functions, must be defined here as properties of the window object */
	
	// Called when the "New Document" link is selected from the userbar
	window.niCustomFlyoutPrep = function() {
		// Hide the bottom portion of the flyout, will be revealed when a choice is made
		$("#jive-choose-container-quick").hide();
		$("#jive-doc-type-write").click($.docTypeSelected);
		$("#jive-doc-type-upload").click($.docTypeSelected);
	}
	
})(jQuery); // Pass in jQuery to allow aliasing


