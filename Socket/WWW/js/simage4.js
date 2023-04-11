var my_imgs = new Array();
var my_imgs_text = new Array();
var my_imgs_alt = new Array();
var the_controls = new Array();

/* Set as 1 to turn the timer on, 0 (or anything else) to turn off
   and have user controls only */
var timer_set = 1;

/* Set timer interval (in milliseconds) */
var timer_intv = 3000;

/* Set image URLs */
my_imgs[0] = "../../images/scare.jpg";
my_imgs[1] = "../../images/scare2.jpg";
my_imgs[2] = "../../images/scare3.jpg";
my_imgs[3] = "../../images/scare4.jpg";
my_imgs[4] = "../../images/scare5.jpg";

/* Set text to display under each image */
my_imgs_text[0] = "Face";
my_imgs_text[1] = "Face 2";
my_imgs_text[2] = "Face 3. Yikes!";
my_imgs_text[3] = "Face 4";
my_imgs_text[4] = "Face 5";

/* Set alt text for each image */
my_imgs_alt[0] = "Face";
my_imgs_alt[1] = "Face 2";
my_imgs_alt[2] = "Face 3";
my_imgs_alt[3] = "Face 4";
my_imgs_alt[4] = "Face 5";


if (document.getElementById && document.createTextNode) {

  var slide_div = document.getElementById("slide_show");
  var my_controls = document.getElementsByTagName("input");
  
  for (var a=0; a<my_controls.length; a++) {
    if (my_controls[a].className == "controls") {
	  the_controls.push(my_controls[a]);
    }
  }
  
  var slide_count = 0;
  var keep_going = 1;
  var slide_HTML = "";
  
  function change_slide() {
    slide_count +=1;
	if (slide_count >= my_imgs.length) {
		slide_count = 0;
	}
	slide_HTML = "<img src=\""+my_imgs[slide_count]+"\" class=\"flip\"";
	slide_HTML += " alt=\""+my_imgs_alt[slide_count]+"\" /><br />";
	slide_HTML += my_imgs_alt[slide_count];
	slide_div.innerHTML = slide_HTML;
	keep_going = setTimeout("change_slide()",timer_intv);
  }
  
  if (timer_set == 1) {
    setTimeout("change_slide()",timer_intv);	
  }
  
  
  function pause_slide() {
	if (keep_going != 1) {
	  clearTimeout(keep_going);
	}
  }
  
  function g_back() {
	if (keep_going != 1) {
      clearTimeout(keep_going);
	}
	slide_count -=1;
	if (slide_count < 0) {
	    slide_count = my_imgs.length - 1;
	}
	slide_HTML = "<img src=\""+my_imgs[slide_count]+"\" class=\"flip\"";
	slide_HTML += " alt=\""+my_imgs_alt[slide_count]+"\" /><br />";
	slide_HTML += my_imgs_alt[slide_count];
	slide_div.innerHTML = slide_HTML;
  }
  
  function g_forward() {
	if (keep_going != 1) {  
	  clearTimeout(keep_going);
	}
	slide_count +=1;
	if (slide_count >= my_imgs.length) {
		slide_count = 0;
	}
	slide_HTML = "<img src=\""+my_imgs[slide_count]+"\" class=\"flip\"";
	slide_HTML += " alt=\""+my_imgs_alt[slide_count]+"\" /><br />";
	slide_HTML += my_imgs_alt[slide_count];
	slide_div.innerHTML = slide_HTML;
  }
  
  function r_start() {
	keep_going = setTimeout("change_slide()",timer_intv); 
  }
  
  function newEvent(c) {
    
    function which_func() {
	  var the_id = the_controls[c].id;
	  if (the_id == "goback"){
	    g_back();
	  }
	  if (the_id == "pause_slide"){
	    pause_slide();
	  }
	  if (the_id == "goforward"){
	    g_forward();
	  }
	  if (the_id == "restart"){
	    r_start();
	  }
	}
	  
    if (typeof the_controls[c].addEventListener != "undefined") {	
      the_controls[c].addEventListener("click", which_func, false);
    }

    else if (typeof the_controls[c].attachEvent != "undefined" ) {
      the_controls[c].attachEvent("onclick", which_func );
    }

    else {
      the_controls[c].onclick = which_func;
    }
	
  }
  
  for (var d=0; d<the_controls.length; d++) {
    newEvent(d);
  }
  
} 