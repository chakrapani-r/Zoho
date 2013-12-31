
(function ($) {

Drupal.behaviors.zoho_example = {
  attach: function (context) {
	$("#get-leads-form #edit-submit").click(function(){
		if (!Drupal.behaviors.zoho_example.isValidEmail($("input#edit-email").attr('value'))) {
		  error = true;
		  $('.messages.error').remove();
		  $('.lead-info').remove();
		  $("#get-leads-form").prepend("<div class='messages error'>Invalid email.</div>");
		  return false;
		}
		else {
		  $('.messages.error').remove();
		  $('.lead-info').remove();
		  var base_path = Drupal.settings.basePath;
		  var zoho_example_path = Drupal.settings.zoho_example_path;
		  var loader = '<img src="' + base_path + zoho_example_path +'/ajax-loader.gif"/>';
   	          $('#get-leads-form').append('<div class="lead-info">' + loader + '</div>');	     
		  $.ajax({	
		    type: 'POST',
	    	    url: base_path + '?q=get_leads_ajax',
        	    data: "email=" + $("input#edit-email").attr('value'),
		    success: function(data) {
			//alert(data);
			$("input#edit-email").attr('value', '');
			$('.lead-info').remove();	     
	   	        $('#get-leads-form').append('<div class="lead-info">'+data+'</div>');
		        //alert('Load was performed.');
		    },
		    error: function(jqXHR, textStatus, errorThrown){
			error = true;
			$('.messages.error').remove();
			$('.lead-info').remove();
			$("#get-leads-form").prepend("<div class='messages error'>" + textStatus + "</div>");
		    }
		  });
		  return false;
		}
        });
	$("#lead-form #edit-submit").click(function(){
		if (!Drupal.behaviors.zoho_example.isValidEmail($("input#edit-email").attr('value'))) {
		  error = true;
		  $('.messages.error').remove();
		  $("#lead-form").prepend("<div class='messages error'>Invalid email.</div>");
		  return false;
		}
		else {
		  $("form#lead-form").submit();
		  return false;
		}
        });

  },

  openlogin: function(){
  },
  /**
   * Tests a string is a valid email. NOT the most elegant function...
   */
  isValidEmail: function(str) {
    var s = $.trim(str);
    var at = "@";
    var dot = ".";
    var lat = s.indexOf(at);
    var lstr = s.length;
    var ldot = s.indexOf(dot);

    if (s.indexOf(at)==-1 ||
      (s.indexOf(at)==-1 || s.indexOf(at)==0 || s.indexOf(at)==lstr) ||
      (s.indexOf(dot)==-1 || s.indexOf(dot)==0 || s.indexOf(dot)==lstr) ||
      (s.indexOf(at,(lat+1))!=-1) ||
      (s.substring(lat-1,lat)==dot || s.substring(lat+1,lat+2)==dot) ||
      (s.indexOf(dot,(lat+2))==-1) ||
      (s.indexOf(" ")!=-1))
      {
	return false;
      }

    return true;
  }
};
})(jQuery);
