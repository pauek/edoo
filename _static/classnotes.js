
/* Sphinx ya incluye JQuery */

$(document).ready(function () {
  $("div.boxed > div.body").hide()

  $("div.boxed > p.first").click(function (ev) {
    $(this).next().toggle()
  })

  $("div.boxed > p.first").hover(function() {
    $(this).css("cursor", "pointer")
  });
})