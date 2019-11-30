const express = require('express');
const app = express();
const server = require('http').Server(app);
const io = require('socket.io')(server);


// ________________________________________________CONFIGURATION____________________________________________
const PORT = process.env.PORT || 5000;

var ESP8266 = "";

app.use(express.static('./webSource'));

app.set('view engine', 'ejs');
app.set('views', './webSource/views');

server.listen(PORT, function(){
    console.log("SERVER RUNNING ON "+ PORT);
})

// _______________________________________________REAL TIME ALL ACTION________________________________________

io.on('connection', function(socket){
    console.log("CONNECTION:\t" + socket.id);
    if (ESP8266 != ""){
        console.log("ESP CONNECTED");
        socket.broadcast.emit('esp-connected',socket.id)
    }
    socket.on('espid', function(){
        ESP8266 = socket.id;
        console.log("ESP CONNECTED");
        socket.broadcast.emit('esp-connected',socket.id)
    })
    socket.on('disconnect', function(){
        if(socket.id == ESP8266){
            ESP8266 = "";
            socket.broadcast.emit('esp-connected',socket.id)
            console.log("ESP DISCONNECTED \n");
        }
        console.log(socket.id + " DISCONNECTED");
    });
    socket.on('response', function(data){
        if (ESP8266 != ""){
            io.sockets.emit('server-response-esp',data);
            console.log(data);
        }
    })
})


// ________________________________________________METHOD____________________________________________________

app.get('/', function(req,res){
    res.render('index');
})

