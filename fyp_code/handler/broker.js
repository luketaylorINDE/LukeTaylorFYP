var mosca = require ('mosca');
var settings = {
  port:1883
}

var server = new mosca.Server(settings);

server.on('ready', function () {
  console.log("Broker ready!");
})

server.on('clientConnected', function(client) {
    console.log('client connected', client.id);
  });

  server.on('clientDisconnected', function(client) {
    console.log('client disconnected', client.id);
  });

  server.on('published', function(packet, client) {
    console.log(packet);
  });

  server.on('subscribed', function(topic, client) {
    console.log('subscribed: ' + client.id);
  });

  server.on('unsubscribed', function(topic, client) {
    console.log('unsubscribed: ' + client.id);
  });
