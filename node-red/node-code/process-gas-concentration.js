// Sensor and circuit parameters for MQ-2 gas sensor
const RL_VALUE = 5.0; // 
const VCC = 5.0;      // Circuit voltage

// 2. Clean Air Resistance Ratio (Ro)
const RO_CLEAN_AIR = 10.0; // Calibrated resistance of the sensor in clean air (kOhms)

// 3. Gas Curve Parameters [slope, point(x,y)] for LPG/Propane
const LPG_CURVE = [-0.45, 1.32];

// 4. Detection Thresholds (in PPM)
const threshold = {
    good: { max: 400 },
    moderate: { max: 1000 }
};

// 1. Get Voltage from Message
var voltage = msg.payload;
if (typeof voltage !== 'number') {
    voltage = parseFloat(voltage);
    if (isNaN(voltage)) {
        voltage = VCC;
    }
}

// 2. Calculate Sensor Resistance (Rs)
var rs;
if (voltage <= 0) {
    rs = 1e6; // Represents a very high resistance in kOhms
} else {
    rs = (VCC * RL_VALUE) / voltage - RL_VALUE;
}


// 3. Calculate Rs/Ro Ratio
var rsRoRatio = rs / RO_CLEAN_AIR;

// 4. Calculate PPM from the Ratio
// Formula: log(y) = m*log(x) + b  =>  x = 10^((log(y) - b) / m)
// y: rsRoRatio, x: PPM, and m: slope.
var logRsRo = Math.log10(rsRoRatio);
var logPPM = (logRsRo - LPG_CURVE[1]) / LPG_CURVE[0];
var ppmValue = Math.pow(10, logPPM);

// 5. Clamp the value to 200-10000 PPM range
ppmValue = Math.max(200, Math.min(10000, ppmValue));

var gasStatus = flow.get("gas_status") || "";

// 6. Evaluate Gas Status
if (ppmValue <= threshold.good.max) {
    gasStatus = "good";
} else if (ppmValue <= threshold.moderate.max) {
    gasStatus = "moderate";
} else {
    gasStatus = "critical";
}

// 7. Set the status in flow context
flow.set("gas_status", gasStatus);

// 8. Return the calculated PPM value, rounded to an integer
msg.payload = Math.round(ppmValue);
return msg;