// 1. Get Voltage from Message
var voltage = msg.payload;
if (typeof voltage !== 'number') {
    voltage = parseFloat(voltage);
    if (isNaN(voltage)) {
        voltage = 5.0; // Default VCC value
    }
}

// Return the raw voltage
msg.payload = voltage;
return msg;
