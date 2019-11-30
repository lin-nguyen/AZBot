
// ............................................GLOBAL ACTION...........................................

// VARIABLE CONFIGURATION

var directionBool = true;

function sendObj() {
    socket.emit('response', JSON.stringify(Obj));
}

var socket = io("http://localhost:5000");

// var socket = io("https://azbot-iot-demo.herokuapp.com");

socket.on('esp-connected', function (data) {
    console.log("ESP8266 CONNECTED \t " + data);
    document.getElementById("device-exist").style.display = "inline-block";
    sendObj();
})
socket.on('esp-disconnected', function (data) {
    console.log("ESP8266 DISCONNECTED \t " + data);
    document.getElementById("device-exist").style.display = "none";
})
socket.on('data-will-send', function (data) {
    console.log("DATA SEND \t" + data);
})

var Obj = {
    beltObj: {
        status: 4,
        speed: 0
    },
    armObj: {
        x: 0,
        y: 0,
        z: 10,
        joint1: 0,
        joint2: 0,
        joint3: 0,
        joint4: 0,
        joint5: 0,  
        joint6: 0
    }
}

// FUNCTION CONFIRGURATION

// --------------------------------------------CODING..................................................
var homepage = document.getElementById('span-homepage');
var functionn = document.getElementById('span-function');
var contact = document.getElementById('span-contact');
var description = document.getElementById('span-description');
var icon = document.getElementById('icon-div');
var list = document.getElementById('mini-guide');
var managerment = document.getElementById('main-manager');


// ...............................................FUNCTION................................................


// CONFIGURATION VIEW
function miniGuide(boolean) {
    if (boolean) {
        setTimeout(function () {
            homepage.style.display = "inline-block";
            functionn.style.display = "inline-block";
            contact.style.display = "inline-block";
            description.style.display = "inline-block";
        }, 10)
        list.style.width = "13vw";
        managerment.style.marginLeft = "13vw";
        managerment.style.width = "87vw";
    }
    else {
        homepage.style.display = "none";
        functionn.style.display = "none";
        contact.style.display = "none";
        description.style.display = "none";
        list.style.width = "3vw";
        managerment.style.marginLeft = "3vw"
        managerment.style.width = "97vw";
    }
}

icon.addEventListener('click', function (event) {
    this.style.backgroundColor = "#dcdcdc";
    setTimeout(function () {
        icon.style.backgroundColor = "#1d1d1d";
    }, 100)
    miniGuide(directionBool)
    directionBool = !directionBool;
})

document.getElementById('belt-speed-id').addEventListener('pointermove', function () {
    document.getElementById('belt-speed').textContent = "Conveyor belt speed: " + this.value;
})

document.getElementById('arm-joint-i1').addEventListener("pointermove", function () {
    document.getElementById('arm-j1-value').textContent = this.value;
})
document.getElementById('arm-joint-i2').addEventListener('pointermove', function () {
    document.getElementById('arm-j2-value').textContent = this.value;
})
document.getElementById('arm-joint-i3').addEventListener('pointermove', function () {
    document.getElementById('arm-j3-value').textContent = this.value;
})
document.getElementById('arm-joint-i4').addEventListener('pointermove', function () {
    document.getElementById('arm-j4-value').textContent = this.value;
})
document.getElementById('arm-joint-i5').addEventListener('pointermove', function () {
    document.getElementById('arm-j5-value').textContent = this.value;
})
document.getElementById('arm-joint-i6').addEventListener('pointermove', function () {
    document.getElementById('arm-j6-value').textContent = this.value;
})

// CONTROLLER 

document.getElementById('belt-status-id').addEventListener('click', function (event) {
    event.preventDefault();
    if (this.value == "On") {
        this.value = "Off";
        document.getElementById('belt-status-name-id').textContent = "Now status: On";
        Obj.beltObj.status = 1;
    }
    else {
        this.value = "On";
        document.getElementById('belt-status-name-id').textContent = "Now status: Off";
        Obj.beltObj.status = 0;
    }
    sendObj()
})

document.getElementById('belt-speed-id').addEventListener('change', function (event) {
    event.preventDefault();
    Obj.beltObj.speed = this.value;
    sendObj()
})

document.getElementById('arm-auto-id').addEventListener('click', function (event) {
    event.preventDefault();
    Obj.armObj.x = document.getElementById('arm-x-id').value;
    Obj.armObj.y = document.getElementById('arm-y-id').value;
    Obj.armObj.z = document.getElementById('arm-z-id').value;
    sendObj()
})

document.getElementById('arm-joint-i1').addEventListener('change', function (event) {
    Obj.armObj.joint1 = this.value;
    sendObj()
})
document.getElementById('arm-joint-i2').addEventListener('change', function (event) {
    Obj.armObj.joint2 = this.value;
    sendObj()
})
document.getElementById('arm-joint-i3').addEventListener('change', function (event) {
    Obj.armObj.joint3 = this.value;
    sendObj()
})
document.getElementById('arm-joint-i4').addEventListener('change', function (event) {
    Obj.armObj.joint4 = this.value;
    sendObj()
})
document.getElementById('arm-joint-i5').addEventListener('change', function (event) {
    Obj.armObj.joint5 = this.value;
    sendObj()
})
document.getElementById('arm-joint-i6').addEventListener('change', function (event) {
    Obj.armObj.joint6 = this.value;
    sendObj()
})
