var HOST = null; // localhost
var PORT = 8001;

var fu = require("./fu"),
        sys = require("util"),
        url = require("url"),
        qs = require("querystring"),
        SerialPort = require('serialport2').SerialPort,
        sf = require('sf');



//Initialize host
fu.listen(Number(process.env.PORT || PORT), HOST);
console.log("Service started on: " + HOST + ":" + Number(process.env.PORT || PORT));

//Initialize static pages
fu.get("/", fu.staticHandler("staticfiles/index.html"));
fu.get("/style.css", fu.staticHandler("staticfiles/style.css"));
fu.get("/client.js", fu.staticHandler("staticfiles/client.js"));
fu.get("/arrow-left.png", fu.staticHandler("staticfiles/arrow-left.png"));
fu.get("/arrow-right.png", fu.staticHandler("staticfiles/arrow-right.png"));
fu.get("/jquery-1.2.6.min.js", fu.staticHandler("staticfiles/jquery-1.2.6.min.js"));



fu.get("/funcleft",
    function (req, res) {
        console.log("funcleft");
        if (v == null) {
            res.simpleJSON(200, { status: "fail", message: "Not connected" });
            return;
        }
        v.write("f");
        res.simpleJSON(200, { status: "ok" });
    }
);

fu.get("/funcright",
    function (req, res) {
        console.log("funcright");
        if (v == null) {
            res.simpleJSON(200, { status: "fail" , message:"Not connected" });
            return;
        }
        v.write("j");
        res.simpleJSON(200, { status: "ok" });
    }
);

fu.get("/ports",
    function (req, res) {
        var sp = require('serialport2');
        sp.list(function (err, ports) {
            if (err) {
                res.simpleJSON(200, { status: "fail", message: err.message });
                return;
            }
            for (var i = 0; i < ports.length; i++) {
                var item = ports[i];
                console.log(sf('{comName,-15} {pnpId,-20} {manufacturer}', item));
            }
            res.simpleJSON(200, { status: "ok", ports: ports });
        });

        console.log("ports");
    }
);

    fu.get("/connect",
    function (req, res) {
        var query = url.parse(req.url, true).query;

        if (v != null) {
            console.log("Closing");
            v.close();
            v = null;
        }


        openConnection(query.port, res);


    }
);

function openConnection(port, res) {
    console.log("Connect to " + port);
    v = new SerialPort();
    v.on('data', function (data) {

        console.log("data:", data.toString());
    });

    v.on('error', function (err) {
        console.log("ERROR:", err);
    });
    v.open(port, {
        baudRate: 9600,
        dataBits: 8,
        parity: 'none',
        stopBits: 1
    }, function (err) {
        if (err) {
            console.log("ERROR:", err);
            res.simpleJSON(200, { status: "fail", message: err.message });
            return;
        }
        res.simpleJSON(200, { status: "ok" });
    });
}
var v = null;    
    //Initialize static pages
/*
    var port = new SerialPort();
    port.on('data', function (data) {
        console.log("data:", data.toString());
    });

    port.on('error', function (err) {
        console.log("ERROR:", err);
    });


    console.log("Connect to CSDSDS");
    
    port.open('COM7', {
        baudRate: 9600,
        dataBits: 8,
        parity: 'none',
        stopBits: 1
    }, function (err) {
        console.log("Connected");
        port.write("hello world");
        
    });*/






