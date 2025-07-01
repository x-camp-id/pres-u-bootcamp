// Define temperature threshold
const threshold = {
    good: { min: 18, max: 25 },    // 18-25°C is good
    moderate: { min: 15, max: 30 } // 15-30°C is moderate
}

// Obtain Flow Context on Temperature Status
var tempStatus = flow.get("temp_status") || "";

// Extract temperature from message
var value = parseFloat(msg.payload) || 0.0;

// Evaluate temperature status
if (value >= threshold.good.min && value <= threshold.good.max) {
    tempStatus = "good";
    
} else if (value >= threshold.moderate.min && value <= threshold.moderate.max) {
    tempStatus = "moderate";
} else {
    tempStatus = "critical";
}

// Set Status
flow.set("temp_status", tempStatus);

// Set msg payload and return msg
msg.payload = value;               
return msg;