var tempStatus = flow.get("temp_status");
var humStatus = flow.get("hum_status");
var gasStatus = flow.get("gas_status");

// Set LED status
var ledStatus = flow.get("led_status") || false;

// check if all status is 'good'
if (tempStatus == "good" && humStatus == "good" && gasStatus == "good"){
    ledStatus = false;
} else {
    ledStatus = true;
}

msg.payload = ledStatus.toString();
flow.set("led_status", ledStatus);

return msg;