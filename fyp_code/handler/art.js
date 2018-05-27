const mqtt = require ('mqtt');

var client  = mqtt.connect('mqtt://192.168.1.100');

var timer = 0.1, intervalMins = timer * 60 * 1000;

var MongoClient = require('mongodb').MongoClient;
var url = 'mongodb://luke1:luke1@ds227740.mlab.com:27740/indefyp';

var sendData;

client.on('connect', function(){
  setInterval(function(){
    MongoClient.connect(url, function(err, db) {
    if (err) throw err;
    db.collection('waterusage', function (err, collection) {

             collection.find({}, {_id: 0, liters : 1 }).sort({$natural: -1}).limit(1).toArray(function(err, items) {
                if(err) throw err;
                var sendData = JSON.stringify(items);
                sendData = sendData.slice(12);
                sendData = sendData.substring(0, sendData.length - 3);
                sendData = sendData.replace(/\s/g,'');
                console.log(sendData);
                client.publish('waterUsage3',sendData);
          });
        });
      });
  },intervalMins);
});




/*MongoClient.connect(url, function(err, db) {
if (err) throw err;
db.collection('waterusage', function (err, collection) {

         collection.find({}, {_id: 0, liters : 1 }).sort({$natural: -1}).limit(1).toArray(function(err, items) {
            if(err) throw err;
            var sendData = JSON.stringify(items);
            sendData = sendData.slice(14);
            sendData = sendData.substring(0, sendData.length - 3);
            console.log(sendData);
      });
    });
  });*/
