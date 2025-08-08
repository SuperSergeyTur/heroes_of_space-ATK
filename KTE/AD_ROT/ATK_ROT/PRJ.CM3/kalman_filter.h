#ifndef kalman_filter_h
#define kalman_filter_h

class KalmanFilter {
private:
    float angle;      // Текущая оценка угла
    float velocity;   // Текущая оценка скорости
    float angle_var;  // Дисперсия угла
    float velocity_var; // Дисперсия скорости
    float process_noise; // Шум процесса
    float measurement_noise; // Шум измерений

public:
    KalmanFilter(float initial_angle, float initial_velocity, float p_noise, float m_noise);
    void predict(float dt);
    void update(float measurement);
    float get_angle() const;
    float get_velocity() const;
};

#endif