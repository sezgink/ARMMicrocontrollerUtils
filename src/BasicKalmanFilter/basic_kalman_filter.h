#pragma once

#define F 1.0 // State transition coefficient for a simple scalar system
#define F_transpose 1.0 // Transpose of F, same as F for scalars
#define B 1.0 // Control matrix coefficient

typedef struct {
    float Q; // Process noise covariance
    float R; // Measurement noise covariance
    float x; // Estimated state
    float P; // Estimated covariance
    float K; // Kalman gain
} KalmanFilter;

void KalmanFilter_Init(KalmanFilter *kf, float Q, float R, float initial_estimate, float initial_error) {
    kf->Q = Q;
    kf->R = R;
    kf->x = initial_estimate;
    kf->P = initial_error;
}

// Prediction step
float KalmanFilter_Update(KalmanFilter *kf, float measurement) {

    // Update covariance prediction
    kf->P += kf->Q;

    // Compute Kalman Gain
    kf->K = kf->P / (kf->P + kf->R);

    // Update estimate with measurement
    kf->x += kf->K * (measurement - kf->x);

    // Update covariance
    kf->P *= (1 - kf->K);

    return kf->x;
}

// Prediction step with dynamics
void KalmanFilter_Predict(KalmanFilter *kf, float u) {
    // Predict the next state based on the system dynamics
    kf->x = F * kf->x + B * u;
    
    // Predict the next covariance
    kf->P = F * kf->P * F_transpose + Q;
}
