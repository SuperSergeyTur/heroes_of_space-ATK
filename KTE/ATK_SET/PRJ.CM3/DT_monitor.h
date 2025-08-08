#ifndef _DT_MONITOR_H_
#define _DT_MONITOR_H_

#include <math.h>
#include <prt_drv.h>

/**
 * @class TemperatureSensorMonitor
 * @brief ����� ��� ����������� � ����������� �������� �����������
 * 
 * ����� ����������� ��������� ������ �������� ����������� � ����������
 * ����������� ������� �� ���������� �� ���������� ��������.
 */
class TemperatureSensorMonitor {
public:
  /**
   * @brief ����������� ������
   * @param sensorCount ���������� �������� (�������� 16)
   * @param thresholdPtr ��������� �� ���������� ������ ������������
   * 
   * ���� thresholdPtr == nullptr, ����� ������������ �������� �� ��������� (5.0)
   */
  TemperatureSensorMonitor(byte sensorCount = 6, const float* thresholdPtr = nullptr)
    : sensorCount_(sensorCount > 16 ? 16 : sensorCount), // ������������ 16 ������
    thresholdPtr_(thresholdPtr) {
      if (thresholdPtr_ == nullptr) {
        thresholdPtr_ = &defaultThreshold_;
      }
    }    
  
  /**
   * @brief �������� ��������� ��������
   * @param temperatureData ��������� �� ������ � �������� ����������� ��������
   * 
   * ����������� ��������� �������� � ��������� ������� ����� ��������������
   */
  void checkSensors(const float* temperatureData) {
    if (!temperatureData) return;
    
    faultyFlags.all = 0; // ����� ���� ������
    float globalMedian = calculateMedian(temperatureData, sensorCount_);
    float currentThreshold = *thresholdPtr_;
    
    for (uint8_t i = 0; i < sensorCount_; i++) {
      float medianWithoutCurrent = calculateMedian(temperatureData, i);
      float diff1 = fabsf(temperatureData[i] - globalMedian);
      float diff2 = fabsf(temperatureData[i] - medianWithoutCurrent);
      
      if ((diff1 > currentThreshold) && (diff2 > currentThreshold)) {
        setFaultFlag(i); // ������������� ��������������� ���
      }
    }
  }
  
  /**
   * @brief ��������� ����� ������������� ��� ����������� �������
   * @param sensorIndex ������ ������� (0-15)
   */
  void setFaultFlag(uint8_t sensorIndex) {
    if (sensorIndex < 16) {
      faultyFlags.all |= (1 << sensorIndex);
    }
  }
  
  /**
   * @brief ����� ���� ������ ��������������
   */
  void resetAllFlags() {
    faultyFlags.all = 0;
  }
  
  /**
   * @brief �������� ��������� �������
   * @param sensorIndex ������ ������������ �������
   * @return true ���� ������ ����������, false � ��������� ������
   */
  bool isSensorFaulty(uint8_t sensorIndex) const {
    if (sensorIndex >= 16) return false;
    return (faultyFlags.all >> sensorIndex) & 0x1;
  }
  
  /**
   * @brief ��������� ������� ����� ��������������
   * @return ��������� Prt16 � ������� ������ ��������������
   */
  Prt16 getAllFaultFlags() const {
    return faultyFlags;
  }
  
  /**
   * @brief ��������� ������ ������ ������������
   * @param newThresholdPtr ��������� �� ����� �������� ������
   */
  void setThresholdPtr(const float* newThresholdPtr) {
    if (newThresholdPtr != nullptr) {
      thresholdPtr_ = newThresholdPtr;
    }
  }
  
  /**
   * @brief ��������� �������� �������� ������
   * @return ������� �������� ������ ������������
   */
  float getCurrentThreshold() const {
    return *thresholdPtr_;
  }    
  
  /**
   * @brief �������� ������� ��������������
   * @return true ���� ���� ���� �� ���� ����������� ������
   */
  bool hasAnyFaults() const {
    return faultyFlags.all != 0;
  }    
  
  /**
   * @brief ��������� ���������� ��������
   * @return ���������� ������������� ��������
   */
  uint8_t getSensorCount() const {
    return sensorCount_;
  }
  
  /**
   * @brief ������� ���������� ����������� ��������
   * @return ���������� ����������� �������� (0-16)
   */
  uint8_t getFaultyCount() const {
    uint8_t count = 0;
    uint16_t mask = faultyFlags.all;
    
    // ������� ������� ������������� �����
    while (mask) {
      count += mask & 0x1;
      mask >>= 1;
    }
    
    return count;
  }
  
private:
  const uint8_t sensorCount_;         ///< ���������� �������� (����. 16)
  const float* thresholdPtr_;         ///< ��������� �� ���������� ������
  float defaultThreshold_ = 5.0f;     ///< �������� ������ �� ���������
  Prt16 faultyFlags;                  ///< ������� ����� ��������������
  
  /**
   * @brief ���������� ������� ������� ��������
   * @param array ������ ��� ����������
   * @param size ������ �������
   */
  void bubbleSort(float array[], uint8_t size) const {
    uint8_t swapped;
    do {
      swapped = 0;
      for (uint8_t i = 1; i < size; i++) {
        if (array[i-1] > array[i]) {
          float temp = array[i-1];
          array[i-1] = array[i];
          array[i] = temp;
          swapped = 1;
        }
      }
      size--;
    } while (swapped);
  }
  
  /**
   * @brief ���������� ���������� �������� ��������� ��������
   * @param data ������ � ����������� ��������
   * @param excludeIndex ������ �������, ������� ����� ��������� �� �������
   * @return ��������� �������� ���������
   */
  float calculateMedian(const float* data, uint8_t excludeIndex) const {
    float values[16];
    uint8_t count = 0;
    
    for (uint8_t i = 0; (i < sensorCount_)&&(i < 16); i++) {
      if (i != excludeIndex) {
        values[count++] = data[i];
      }
    }
    
    bubbleSort(values, count);
    
    if (count % 2 == 0) {
      return (values[count/2 - 1] + values[count/2]) * 0.5f;
    } else {
      return values[count/2];
    }
  }
};

#endif