// WEBSOCKET FUNCTIONS -----------------------------------
	
	//var serverURL = "ws://johannes.homeip.net:8008/ws";
	
	function doConnect()
	{
		websocket = new WebSocket(document.getElementById("url").value);
		websocket.onopen = function(evt) { onOpen(evt) };
		websocket.onclose = function(evt) { onClose(evt) };
		websocket.onmessage = function(evt) { onMessage(evt) };
		websocket.onerror = function(evt) { onError(evt) };
		
	}

	function onOpen(evt)
	{
		writeToScreen("connected\n");
		document.getElementById('connectButton').disabled = true;
		document.getElementById('sendButton').disabled = false;

	}

	function onClose(evt)
	{
		writeToScreen("state: disconnected\n");
		document.getElementById('connectButton').disabled = false;
		document.getElementById('sendButton').disabled = true;
	}

	

	function onError(evt)
	{
		writeToScreen('error (' + document.getElementById("url").value + ') ' + evt.data + '\n');
		websocket.close();
		connectButton.disabled = false;
		document.getElementById("sendButton").disabled = true;
	}

	function doSend(message)
	{
		// how to check if websocket is open?
		if (websocket.readyState == 1) {
			websocket.send(message);
			writeToScreen("sent: " + message + '\n');
		} else 
			writeToScreen("WebSocket is not open!");
	}
	
	

	
	function writeToScreen(message)
	{
	//alert(message);
	var outputtext = document.getElementById("outputtext");
	outputtext.value += message;
	outputtext.scrollTop = outputtext.scrollHeight;
	}