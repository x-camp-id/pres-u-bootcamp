var blynkLed = msg.payload
var ledStatus = flow.get("led_status") || "OFF";

if (blynkLed == 1) {
    ledStatus = "ON";
} else {
    ledStatus = "OFF";
}

flow.set("led_status", ledStatus);
msg.payload = ledStatus;

return msg;