// kalman_filter.cpp
#include "kalman_filter.h"
#include <cmath>

KalmanFilter::KalmanFilter(float initial_angle, float initial_velocity, float p_noise, float m_noise)
    : angle(initial_angle), velocity(initial_velocity),
      angle_var(1.0f), velocity_var(1.0f),
      process_noise(p_noise), measurement_noise(m_noise) {}

void KalmanFilter::predict(float dt) {
    // Предсказание состояния
    angle += velocity * dt;
    // Обновление ковариации
    angle_var += dt * dt * velocity_var + process_noise;
    velocity_var += process_noise;
}

void KalmanFilter::update(float measurement) {
    // Коэффициент Калмана
    float kalman_gain = angle_var / (angle_var + measurement_noise);
    // Коррекция оценки
    angle += kalman_gain * (measurement - angle);
    angle_var *= (1 - kalman_gain);
}

float KalmanFilter::get_angle() const { return angle; }
float KalmanFilter::get_velocity() const { return velocity; }