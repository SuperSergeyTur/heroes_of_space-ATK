#ifndef kalman_filter_h
#define kalman_filter_h

class KalmanFilter {
private:
    float angle;      // ������� ������ ����
    float velocity;   // ������� ������ ��������
    float angle_var;  // ��������� ����
    float velocity_var; // ��������� ��������
    float process_noise; // ��� ��������
    float measurement_noise; // ��� ���������

public:
    KalmanFilter(float initial_angle, float initial_velocity, float p_noise, float m_noise);
    void predict(float dt);
    void update(float measurement);
    float get_angle() const;
    float get_velocity() const;
};

#endif