var slider = document.getElementById("tick");
var output = document.getElementById("lenombre");
output.innerHTML = slider.ariaValueMax;

slider.oninput = function() {
    output.innerHTML = this.value;
}