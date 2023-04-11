
if (document.getElementById && document.createTextNode) {
  
  var default_color = "#FFFFFF";
  
  var bg_colors = new Array()
    bg_colors[0] = "#FFCCFF"; // first link 
	bg_colors[1] = "#CCFFCC"; // second link
	bg_colors[2] = "#FFFFFF"; // third link
  
  var the_links = document.getElementsByTagName("a");
  var bg_links = new Array();
  
  for (var b=0; b<the_links.length; b++) {
	if (the_links[b].className == "change_bg") {
	  	bg_links.push(the_links[b]);
	}
  }

  if (bg_colors.length < bg_links.length) {
	while (bg_colors.length < bg_links.length) {
	  bg_colors.push(default_color);	  
	}
  }

  function newEvent(c) {

    if (typeof bg_links[c].addEventListener != "undefined") {
      bg_links[c].addEventListener("mouseover", function() { document.body.style.backgroundColor=bg_colors[c]; }, false);
    }

    else if (typeof bg_links[c].attachEvent != "undefined" ) {
      bg_links[c].attachEvent("onmouseover", function() { document.body.style.backgroundColor=bg_colors[c]; } );
    }
  
    else {
      bg_links[c].onmouseover = function() { document.body.style.backgroundColor=bg_colors[c]; };
    }

  }

  for (var d=0; d<bg_links.length; d++) {
    newEvent(d);
  }
 
}