
/* Sphinx ya incluye JQuery */

$(document).ready(function () {
  $("div.boxed > div.body").hide();

  $("div.boxed").click(function (ev) {
    $(this).find("> .body").toggle()
  })

  $("div.boxed > p.first").hover(function() {
    $(this).css("cursor", "pointer");
  });
})