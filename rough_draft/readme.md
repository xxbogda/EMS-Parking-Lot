---- Parking lot capacity variables ---------------
carCount, carCapacity, FULL


---- Barrier status -------------------------------
B1, B2
// Kind of substitutes states, for handling of diff conditions when
// needed to lower/raise barriers


---- Debouncer variables --------------------------
lastStateIRx
thresholdTime: time where IRX should keep its state for barrier to change

(in loop)
IRxRising/LoweringTime: keeps track of the time of the signal change (low->high or viceversa)

StateIRx: current state
