#ifndef _DATECONVERT_H
#define _DATECONVERT_H
//#include <rtc.h>
/**
 * @class DateConverter
 * @brief ����� ��� ���������� ���������� ������ � ������� ���� (22.03.2022 0:00:00).
 *
 * ����� ������������� ���������������� ��� �������������� ���� � �������, ��������������
 * � �������-���������� ���� (BCD), � ���������� ������, ��������� � ������� ����.
 */

class DateConverter {
public:
    /**
     * @brief ����������� ������ DateConverter.
     *
     * �������������� ������� ����: 01.01.2025 0:00:00.
     */
    DateConverter() : refYear(2024), refMonth(1), refDay(1), refHour(0), refMinute(0), refSecond(0) {}

     /**
     * @brief ��������� ���������� ������ � ������� ����.
     *
     * ��������� ������ �� 7 ������, �������������� ���� � ����� � ����������� ������� BCD,
     * � ���������� ���������� ������, ��������� � ������� ����.
     *
     * @param  ptr ��������� �� ��������� I2C_time
     * @param  adjustForDST ���� �������� �� ������/������ ����� (true/false).
     * @param  BCD_on ����� � ����������(false) / �������-����������(true) �������.
     * @return ���������� ������, ��������� � ������� ����.
     */
    lword secondsSinceReferenceDate(I2C_time* ptr,  bool adjustForDST = false, bool BCD_on = false ); 

private:
    // ������� ����
    word refYear;  ///< ��� ������� ���� (2022).
    word refMonth; ///< ����� ������� ���� (2).
    word refDay;   ///< ���� ������� ���� (24).
    word refHour;  ///< ��� ������� ���� (0).
    word refMinute;///< ������ ������� ���� (0).
    word refSecond;///< ������� ������� ���� (0).

    /**
     * @brief ����������� ���� � �������-���������� ���� (BCD) � ���������� �����.
     *
     * @param bcd ���� � ������� BCD.
     * @return ���������� �����.
     */
    word bcdToDec(byte bcd); 
    /**
     * @brief ���������, �������� �� ��� ����������.
     *
     * @param year ��� ��� ��������.
     * @return true, ���� ��� ����������, ����� false.
     */
    bool isLeapYear(word year); 

    /**
     * @brief ���������� ���������� ���� � ��������� ������.
     *
     * @param month ����� (1-12).
     * @param year ��� (��� �������� ����������� ���� � �������).
     * @return ���������� ���� � ������.
     */
    word daysInMonth(word month, word year); 

    /**
     * @brief ��������� ���������� ����, ��������� � ������� ����.
     *
     * @param year ��� ������� ����.
     * @param month ����� ������� ����.
     * @param day ���� ������� ����.
     * @return ���������� ����, ��������� � ������� ����.
     */
    lword calculateDaysSinceReference(word year, word month, word day) ;
    /**
     * @brief ���������, ��������� �� ������ ����� ��� ��������� ���� � ����.
     *
     * @param year ���.
     * @param month �����.
     * @param day ����.
     * @param hour ���.
     * @return true, ���� ��������� ������ �����, ����� false.
     */
    bool isDST(word year, word month, word day, word hour);
    
    
/**
     * @brief ���������� ���� ���������� ����������� � ��������� ������ � ����.
     *
     * @param month �����.
     * @param year ���.
     * @return ���� ���������� �����������.
     */
    word getLastSunday(word month, word year);
    
};

#endif