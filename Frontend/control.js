// fetch api
const endpoint = 'http://localhost:5000/control1';
setInterval(function(){
    get_data();
}, 3000);
function get_data(){fetch(endpoint)
    .then((response) => response.json())
    .then((data) => handleData(data))
}
function handleData(data){
    var temp = document.getElementById("currentTemp").innerHTML = data['temp'];
    var humi = document.getElementById("currentHumi").innerHTML = data['humi'];
    var light = document.getElementById("currentLight").innerHTML = data['light'];
    var soil = document.getElementById("currentSoil").innerHTML = data['soil']
    noti_error(temp, humi, light, soil);
}
//get Id

// send control
function control_a(){
    var led_post, may_bom_post;
    var led = document.getElementById('led-status');
    var may_bom = document.getElementById('may-bom-status');
    if(led.checked == true) {led_post = 1;}
    else {led_post = 0;}    
    if(may_bom.checked == true) {may_bom_post = 1;}
    else {may_bom_post = 0;}
    const options = {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({led: led_post, relay: may_bom_post})
    };
    fetch(endpoint, options).then((response) => response.json()).then(data => console.log(data));  
}

//fetch(endpoint, options).then((response) => response.json()).then(data => console.log(data));

// ------------- RTC ------------
var timeDisplay = document.getElementById("time");

function refreshTime() {
    var dateString = new Date().toLocaleString("en-US", { timeZone: "Asia/Jakarta" });
    var formattedString = dateString.replace(", ", " - ");
    timeDisplay.innerHTML = formattedString;
}

setInterval(refreshTime, 1000);
// ------------------------------
function noti_error(temp, humi, light, soil){
    var noti = document.getElementById('warning');
    var led_back = document.getElementById('led-stt');
    var may_bom_back = document.getElementById('may-bom-stt');
/*
    if(temp > 32 || humi < 50){
        noti.classList.add('danger');
        led_back.classList.add('turn-on');
    }
    else{
        noti.classList.add('danger');
        led_back.classList.remove('turn-on');
    }
*/
    if(soil < 40 && light < 50){
        const options = {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({led: 0, relay: 0})
        };
        fetch(endpoint, options).then((response) => response.json()).then(data => console.log(data));
        var led_stt = document.getElementById('div_led');
        var may_bom_stt = document.getElementById('div_may_bom');
        led_stt.classList.add('turn-on');
        may_bom_stt.classList.add('turn-on');
    }

    if(soil > 40 && light > 50){
        const options = {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({led: 1, relay: 1})
        };
        fetch(endpoint, options).then((response) => response.json()).then(data => console.log(data));
        var led_stt = document.getElementById('div_led');
        var may_bom_stt = document.getElementById('div_may_bom');
        led_stt.classList.remove('turn-on');
        may_bom_stt.classList.remove('turn-on');
    }

    if(soil < 40 && light > 50){
        const options = {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({led: 0, relay: 1})
        };
        fetch(endpoint, options).then((response) => response.json()).then(data => console.log(data));
        var led_stt = document.getElementById('div_led');
        var may_bom_stt = document.getElementById('div_may_bom');
        led_stt.classList.add('turn-on');
        may_bom_stt.classList.remove('turn-on');
    }

    if(soil > 40 && light < 50){
        const options = {
            method: 'POST',
            headers: {'Content-Type': 'application/json'},
            body: JSON.stringify({led: 1, relay: 0})
        };
        fetch(endpoint, options).then((response) => response.json()).then(data => console.log(data));
        var led_stt = document.getElementById('div_led');
        var may_bom_stt = document.getElementById('div_may_bom');
        led_stt.classList.remove('turn-on');
        may_bom_stt.classList.add('turn-on');
    }


 
    if (temp > 34) {
        var warningSection1 = document.getElementById("temp_view")
        warningSection1.classList.add('warning-mode-on')
    } else {
        var warningSection1 = document.getElementById("temp_view")
        warningSection1.classList.remove('warning-mode-on')
    }

    if(humi < 50){
        var humi_view = document.getElementById('humi_view');
        humi_view.classList.add('warning-mode-on')
    }
    else{
        var humi_view = document.getElementById('humi_view');
        humi_view.classList.remove('warning-mode-on')
    }
    /*
    if(light > 70){
        var light_view = document.getElementById('light_view');
        light_view.classList.add('warning-mode-on')
    }
    else{
        var light_view = document.getElementById('light_view');
        light_view.classList.remove('warning-mode-on')
    }
    */
    if(soil < 30){
        var soil_view = document.getElementById('soil_view');
        soil_view.classList.add('warning-mode-on')
    }
    else{
        var soil_view = document.getElementById('soil_view');
        soil_view.classList.remove('warning-mode-on')
    }
     
}

// auto on off
function auto_on_off(){
    var today = new Date();
    var hours = today.getHours();
}
setInterval(auto_on_off, 2000);