var blynkLed = msg.payload
var ledStatus = flow.get("led_status") || false;

if (blynkLed == 1) {
    ledStatus = true;
} else {
    ledStatus = false;
}

flow.set("led_status", ledStatus);
msg.payload = ledStatus.toString();

return msg;