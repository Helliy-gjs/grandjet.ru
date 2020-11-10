$(function(){
	$('.menu_simpleToggle').on('click', function(){
		$('.menu_simple').slideToggle(300, function(){
			if($(this).css('display') === 'none'){
			$(this).removeAttr('style')
			}
		});
	});
}); 
