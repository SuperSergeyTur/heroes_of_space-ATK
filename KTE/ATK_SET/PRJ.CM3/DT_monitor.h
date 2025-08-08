#ifndef _DT_MONITOR_H_
#define _DT_MONITOR_H_

#include <math.h>
#include <prt_drv.h>

/**
 * @class TemperatureSensorMonitor
 * @brief Класс для мониторинга и диагностики датчиков температуры
 * 
 * Класс анализирует показания группы датчиков температуры и определяет
 * неисправные датчики по отклонению от медианного значения.
 */
class TemperatureSensorMonitor {
public:
  /**
   * @brief Конструктор класса
   * @param sensorCount Количество датчиков (максимум 16)
   * @param thresholdPtr Указатель на переменную порога срабатывания
   * 
   * Если thresholdPtr == nullptr, будет использовано значение по умолчанию (5.0)
   */
  TemperatureSensorMonitor(byte sensorCount = 6, const float* thresholdPtr = nullptr)
    : sensorCount_(sensorCount > 16 ? 16 : sensorCount), // Ограничиваем 16 битами
    thresholdPtr_(thresholdPtr) {
      if (thresholdPtr_ == nullptr) {
        thresholdPtr_ = &defaultThreshold_;
      }
    }    
  
  /**
   * @brief Проверка состояния датчиков
   * @param temperatureData Указатель на массив с текущими показаниями датчиков
   * 
   * Анализирует показания датчиков и обновляет битовую маску неисправностей
   */
  void checkSensors(const float* temperatureData) {
    if (!temperatureData) return;
    
    faultyFlags.all = 0; // Сброс всех флагов
    float globalMedian = calculateMedian(temperatureData, sensorCount_);
    float currentThreshold = *thresholdPtr_;
    
    for (uint8_t i = 0; i < sensorCount_; i++) {
      float medianWithoutCurrent = calculateMedian(temperatureData, i);
      float diff1 = fabsf(temperatureData[i] - globalMedian);
      float diff2 = fabsf(temperatureData[i] - medianWithoutCurrent);
      
      if ((diff1 > currentThreshold) && (diff2 > currentThreshold)) {
        setFaultFlag(i); // Устанавливаем соответствующий бит
      }
    }
  }
  
  /**
   * @brief Установка флага неисправности для конкретного датчика
   * @param sensorIndex Индекс датчика (0-15)
   */
  void setFaultFlag(uint8_t sensorIndex) {
    if (sensorIndex < 16) {
      faultyFlags.all |= (1 << sensorIndex);
    }
  }
  
  /**
   * @brief Сброс всех флагов неисправностей
   */
  void resetAllFlags() {
    faultyFlags.all = 0;
  }
  
  /**
   * @brief Проверка состояния датчика
   * @param sensorIndex Индекс проверяемого датчика
   * @return true если датчик неисправен, false в противном случае
   */
  bool isSensorFaulty(uint8_t sensorIndex) const {
    if (sensorIndex >= 16) return false;
    return (faultyFlags.all >> sensorIndex) & 0x1;
  }
  
  /**
   * @brief Получение битовой маски неисправностей
   * @return Структура Prt16 с битовой маской неисправностей
   */
  Prt16 getAllFaultFlags() const {
    return faultyFlags;
  }
  
  /**
   * @brief Установка нового порога срабатывания
   * @param newThresholdPtr Указатель на новое значение порога
   */
  void setThresholdPtr(const float* newThresholdPtr) {
    if (newThresholdPtr != nullptr) {
      thresholdPtr_ = newThresholdPtr;
    }
  }
  
  /**
   * @brief Получение текущего значения порога
   * @return Текущее значение порога срабатывания
   */
  float getCurrentThreshold() const {
    return *thresholdPtr_;
  }    
  
  /**
   * @brief Проверка наличия неисправностей
   * @return true если есть хотя бы один неисправный датчик
   */
  bool hasAnyFaults() const {
    return faultyFlags.all != 0;
  }    
  
  /**
   * @brief Получение количества датчиков
   * @return Количество отслеживаемых датчиков
   */
  uint8_t getSensorCount() const {
    return sensorCount_;
  }
  
  /**
   * @brief Подсчет количества неисправных датчиков
   * @return Количество неисправных датчиков (0-16)
   */
  uint8_t getFaultyCount() const {
    uint8_t count = 0;
    uint16_t mask = faultyFlags.all;
    
    // Быстрый подсчёт установленных битов
    while (mask) {
      count += mask & 0x1;
      mask >>= 1;
    }
    
    return count;
  }
  
private:
  const uint8_t sensorCount_;         ///< Количество датчиков (макс. 16)
  const float* thresholdPtr_;         ///< Указатель на переменную порога
  float defaultThreshold_ = 5.0f;     ///< Значение порога по умолчанию
  Prt16 faultyFlags;                  ///< Битовая маска неисправностей
  
  /**
   * @brief Сортировка массива методом пузырька
   * @param array Массив для сортировки
   * @param size Размер массива
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
   * @brief Вычисление медианного значения показаний датчиков
   * @param data Массив с показаниями датчиков
   * @param excludeIndex Индекс датчика, который нужно исключить из расчета
   * @return Медианное значение показаний
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