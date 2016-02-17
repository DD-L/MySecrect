
$(document).ready(function(){
  $("div#keyplain").hide();
  //$("a#disconnect").hide();

  // webchannel
  var baseUrl = (/[?&]webChannelBaseUrl=([A-Za-z0-9\-:/\.]+)/.exec(location.search)[1]);
  output("Connecting to WebSocket server at " + baseUrl + ".");
  var socket = new WebSocket(baseUrl);

  // make baseUrl and socket aceessible globally
  window.baseUrl = baseUrl;
  window.socket  = socket;

  socket.onclose = function() {
    $("input#clientState").val('Disconnect');
    var message = "web channel closed";
    $("div#clientStateMessage").html(message);
    console.error(message);
  };
  socket.onerror = function(error) {
    $("input#clientState").val('Disconnect');
    var message = "web channel error: " + error;
    $("div#clientStateMessage").html(message);
    console.error(message);
  };
  socket.onopen = function() {
    output("WebSocket connected, setting up QWebChannel.");
    new QWebChannel(socket, function(channel) {
      // make commun_object object accessible globally
      window.commun_object  = channel.objects.commun_object;

      commun_object.sendStatus.connect(function(message){
        output('Recevied message: ' + message);
      });
      commun_object.sendResults.connect(function(message){
        $("textarea#results").val(message);
      });
      /*
      commun_object.appExit.connect(function(code){
        output('Quit!');
      });
      */

      $("input#clientState").val('Connected');
      commun_object.receiveStatus("Client connected.\n");
      output("Connected to WebChannel, ready to send/receive messages!");
      $("div#clientStateMessage").html('Connected to WebChannel');
    });
  }

  // event

  $("a#keytextmode").click(function(){
    var $a_keytextmode = $("a#keytextmode");
    var $input_keyvalue = $("input#keyvalue");
    var $input_keyplain = $("input#keyplain");
    var $input_keycipher = $("input#keycipher");
    var $div_keyplain = $("div#keyplain");
    var $div_keycipher = $("div#keycipher");

    var mode = $a_keytextmode.text();
    var key = $input_keyvalue.val();
    switch(mode) {
    case "cipher":
      $a_keytextmode.text("plain");
      // sync key
      key = $input_keyplain.val();
      $input_keyvalue.val(key);
      $input_keycipher.val(key);

      $div_keyplain.hide();
      $div_keycipher.show();
    break;
    case "plain":
    defualt:
      $a_keytextmode.text("cipher");
      // sync key
      key = $input_keycipher.val();
      $input_keyvalue.val(key);
      $input_keyplain.val(key);

      $div_keycipher.hide();
      $div_keyplain.show();
    break;
    }
  });

  $("input#keycipher").on('input', function(){
    var key = $("input#keycipher").val();
    $("input#keyplain").val(key);
    $("input#keyvalue").val(key);
  });

  $("input#keyplain").on('input', function(){
    var key = $("input#keyplain").val();
    $("input#keycipher").val(key);
    $("input#keyvalue").val(key);
  });

  $("#encrypt").click(function(){
    var text = $("#info").val();
    if ( (!text) || isKeyEmpty()) {
      return;
    }
    var key = $("input#keyvalue").val();
    commun_object.receiveKey(key);

    commun_object.receiveInfo2Encrypt(text);
  });
  $("#decrypt").click(function(){
    var text = $("#info").val();
    if ( (!text) || isKeyEmpty()) {
      return;
    }
    var key = $("input#keyvalue").val();
    commun_object.receiveKey(key);

    commun_object.receiveInfo2Decrypt(text);
  });


  $("a#clientState").click(function(){
      output(getClientStateMessage());
  });

  $("a#connect").click(function(){
      var state = $("input#clientState").val();
      switch(state) {
      case 'Connecting':
      case 'Connected':
          break;
      case 'Disconnect':
      default:
          socket = new WebSocket(baseUrl);
          break;
      }
      output(getClientStateMessage());
  });

  $("#copy").click(function(){
    var $div_copiedState = $("div#copiedState");
    var $textarea_results = $("textarea#results");
    var results = $textarea_results.val();
    if (results) {
        commun_object.copy2clipboard(results);
        $div_copiedState.html('Copied !');
    }
    else {
        $div_copiedState.html('Empty !');
    }
  });

  $("#exit").click(function(){
    commun_object.appQuit();
  });
  $("#quit").click(function(){
    // test
    commun_object.appQuit();
  });

  $("a#clearStatus").click(function(){
    $("textarea#status").val('');
  });
  $("a#clearResults").click(function() {
    $("textarea#results").val('');
    output("Clear Results");
  });
  $("a#clearClipboard").click(function() {
    commun_object.clearClipboard();
    output("Clear Clipboad");
  });

});

function output(message) {
  var $psconsole = $("textarea#status");
  //$psconsole.append(message + '\n');
  var text = $psconsole.val();
  message = text + message + '\n';
  $psconsole.val(message);
  // Scroll to down in textarea
  if($psconsole.length) {
    $psconsole.scrollTop($psconsole[0].scrollHeight - $psconsole.height());
  }
}

function isKeyEmpty() {
  var key = $("input#keyvalue").val();
  if (!key) {
     var message = "'Secret key' cannot be empty !";
     output('Warning: ' + message);
     alert(message);

     if ($("a#keytextmode").text() === 'plain') {
        $("input#keycipher").focus();
     } else {
        $("input#keyplain").focus();
     }
     return true;
  }
  return false;
}

function getClientStateMessage() {
  var message = $("div#clientStateMessage").html();
  if (message) {
    return message;
  }
  else {
    return 'State Unknown';
  }
}
