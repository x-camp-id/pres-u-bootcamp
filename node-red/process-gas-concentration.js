// Define gas concentration threshold
const threshold = {
    good: {max: 300},
    moderate: {max: 500}
}

// Obtain Flow Context on gas Status
var gasStatus = flow.get("gas_status") || "";

// Extract gas from message
var value = parseFloat(msg.payload) || 0.0;

// Evaluate gas status
if (value <= threshold.good.max) {
    gasStatus = "good";
    
} else if (value <= threshold.moderate.max) {
    gasStatus = "moderate";
} else {
    gasStatus = "critical";
}

// Set Status
flow.set("gas_status", gasStatus);

// Set msg payload and return msg
msg.payload = value;               
return msg;