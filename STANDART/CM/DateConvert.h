#ifndef _DATECONVERT_H
#define _DATECONVERT_H
//#include <rtc.h>
/**
 * @class DateConverter
 * @brief Класс для вычисления количества секунд с опорной даты (22.03.2022 0:00:00).
 *
 * Класс предоставляет функциональность для преобразования даты и времени, представленных
 * в двоично-десятичном коде (BCD), в количество секунд, прошедших с опорной даты.
 */

class DateConverter {
public:
    /**
     * @brief Конструктор класса DateConverter.
     *
     * Инициализирует опорную дату: 01.01.2025 0:00:00.
     */
    DateConverter() : refYear(2024), refMonth(1), refDay(1), refHour(0), refMinute(0), refSecond(0) {}

     /**
     * @brief Вычисляет количество секунд с опорной даты.
     *
     * Принимает массив из 7 байтов, представляющих дату и время в специальном формате BCD,
     * и возвращает количество секунд, прошедших с опорной даты.
     *
     * @param  ptr указатель на структуру I2C_time
     * @param  adjustForDST Учет перехода на летнее/зимнее время (true/false).
     * @param  BCD_on время в десятичном(false) / двоично-десятичном(true) формате.
     * @return Количество секунд, прошедших с опорной даты.
     */
    lword secondsSinceReferenceDate(I2C_time* ptr,  bool adjustForDST = false, bool BCD_on = false ); 

private:
    // Опорная дата
    word refYear;  ///< Год опорной даты (2022).
    word refMonth; ///< Месяц опорной даты (2).
    word refDay;   ///< День опорной даты (24).
    word refHour;  ///< Час опорной даты (0).
    word refMinute;///< Минута опорной даты (0).
    word refSecond;///< Секунда опорной даты (0).

    /**
     * @brief Преобразует байт в двоично-десятичном коде (BCD) в десятичное число.
     *
     * @param bcd Байт в формате BCD.
     * @return Десятичное число.
     */
    word bcdToDec(byte bcd); 
    /**
     * @brief Проверяет, является ли год високосным.
     *
     * @param year Год для проверки.
     * @return true, если год високосный, иначе false.
     */
    bool isLeapYear(word year); 

    /**
     * @brief Возвращает количество дней в указанном месяце.
     *
     * @param month Месяц (1-12).
     * @param year Год (для проверки високосного года в феврале).
     * @return Количество дней в месяце.
     */
    word daysInMonth(word month, word year); 

    /**
     * @brief Вычисляет количество дней, прошедших с опорной даты.
     *
     * @param year Год текущей даты.
     * @param month Месяц текущей даты.
     * @param day День текущей даты.
     * @return Количество дней, прошедших с опорной даты.
     */
    lword calculateDaysSinceReference(word year, word month, word day) ;
    /**
     * @brief Проверяет, действует ли летнее время для указанной даты и часа.
     *
     * @param year Год.
     * @param month Месяц.
     * @param day День.
     * @param hour Час.
     * @return true, если действует летнее время, иначе false.
     */
    bool isDST(word year, word month, word day, word hour);
    
    
/**
     * @brief Возвращает день последнего воскресенья в указанном месяце и году.
     *
     * @param month Месяц.
     * @param year Год.
     * @return День последнего воскресенья.
     */
    word getLastSunday(word month, word year);
    
};

#endif