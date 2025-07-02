// Define humidity threshold
const threshold = {
    good: { min: 40, max: 60 },    // 40-60% is good
    moderate: { min: 30, max: 70 } // 30-70% is moderate
}

// Obtain Flow Context on Humidity Status
var humStatus = flow.get("humidity_status") || "";

// Extract humidity from message
var value = parseFloat(msg.payload) || 0.0;

// Evaluate humidity status
if (value >= threshold.good.min && value <= threshold.good.max) {
    humStatus = "good";
    
} else if (value >= threshold.moderate.min && value <= threshold.moderate.max) {
    humStatus = "moderate";
} else {
    humStatus = "critical";
}

// Set Status
flow.set("humidity_status", humStatus);

// Set msg payload and return msg
msg.payload = value;               
return msg;

