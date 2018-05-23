const mqtt = require ('mqtt');

var client  = mqtt.connect('mqtt://192.168.1.2');

var data;
var timer = 0.5, intervalMins = timer * 60 * 1000;

var moment = require('moment');


var MongoClient = require('mongodb').MongoClient;
var url = 'mongodb://luke1:luke1@ds227740.mlab.com:27740/indefyp';

client.on('connect', function () {
  client.subscribe('waterUsage2');
  console.log('client has subscribed successfully');

});

client.on('connect', function(){
  setInterval(function(){client.publish('waterUsage1','1');},intervalMins);
});

client.on('message', function (topic, message){
  var data = (message.toString());
  //console.log("liters: "+ data);

  var time = moment();
  var time_format = time.format('YYYY-MM-DD HH:mm:ss Z');

  var mongoLog = [{
    time: time_format,
    liters: data
  }]

  MongoClient.connect(url, function (err, db){
    var col = db.collection('waterusage');
    col.insert(mongoLog, function(err, result){
      db.close();
    });
    console.log("Saved to db");
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

});
