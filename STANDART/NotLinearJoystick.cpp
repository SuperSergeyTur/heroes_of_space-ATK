//#include <iostream>
//#include "defines.h"

//using namespace std;

//int16_t part_k1_k2_x_max_value = _Skor_nom(1.0);
//int16_t part_k1_x_max_value = _Skor_nom(0.2);
//int16_t part_k1_factor = 0.25 * 256;
//
//CNotLinearJoystick notLinearJoystick;
//notLinearJoystick.init(&part_k1_k2_x_max_value, &part_k1_x_max_value, &part_k1_factor);
//float out = notLinearJoystick.calc_out(in)->out;

//namespace NotLinearZI
//{

    class CNotLinearJoystick
    {
    public:
        int16_t  in;
        int16_t  out;
        int16_t* pPart_k1_k2_x_max_value;
        int16_t* pPart_k1_x_max_value;
        int16_t* pPart_k1_factor;

    private:
        int16_t  part_k1_k2_x_max_value_old;
        int16_t  part_k1_x_max_value_old;
        int16_t  part_k1_factor_old;
        //---
        float32_t part_k1_max_y_value;
        float32_t part_k1_factor;
        float32_t part_k2_factor;
        //---
        bool new_settings;
        float32_t  part_k1_current_value;
        float32_t  part_k2_current_value;

    public:
        //CNotLinearJoystick() 
        void Constructor() // init for CM3
        {
            in = 0;
            out = 0;
            pPart_k1_k2_x_max_value = 0;
            pPart_k1_x_max_value = 0;
            pPart_k1_factor = 0;
            //---
            part_k1_k2_x_max_value_old = 0;
            part_k1_x_max_value_old = 0;
            part_k1_factor_old = 0;
            //---
            part_k1_max_y_value = 0;
            part_k1_factor = 0;
            part_k2_factor = 0;
            //---
            new_settings = true;
            part_k1_current_value = 0;
            part_k2_current_value = 0;
        }

        CNotLinearJoystick* init(int16_t* max_in_value, int16_t* pNotlinear_part_value, int16_t* pNotlinear_part_factor)
        {
            Constructor();
            //---
            this->pPart_k1_k2_x_max_value = max_in_value;
            this->pPart_k1_x_max_value = pNotlinear_part_value;
            this->pPart_k1_factor = pNotlinear_part_factor;
            return this;
        }

        //----------------------------

        CNotLinearJoystick* calc_out(int16_t in_value)
        {
            in = in_value;
            //---

            if (*pPart_k1_x_max_value == 0 || 
                *pPart_k1_factor == 0 ||
                  *pPart_k1_k2_x_max_value == 0) 
            {
                out = in;
            }
            else
            {
                refresh_settings()->
                    calc_k1_k2()->
                    calc_part_k1(in)->
                    calc_part_k2(in);
                out = part_k1_current_value + part_k2_current_value;
            }

            return this;
        }        

    private:

        CNotLinearJoystick* refresh_settings()
        {
            if (part_k1_k2_x_max_value_old != *pPart_k1_k2_x_max_value ||
                part_k1_x_max_value_old != *pPart_k1_x_max_value ||
                part_k1_factor_old != *pPart_k1_factor)
            {
                part_k1_k2_x_max_value_old = *pPart_k1_k2_x_max_value;
                part_k1_x_max_value_old = *pPart_k1_x_max_value;
                part_k1_factor_old = *pPart_k1_factor;
                new_settings = true;
            }
            else new_settings = false;

            return this;
        }

        CNotLinearJoystick* calc_k1_k2()
        {
            if (new_settings == true)
            {
                part_k1_factor = *pPart_k1_factor / 256.;
                //---
                part_k1_max_y_value = *pPart_k1_x_max_value * part_k1_factor;
                int16_t left_by_y = *pPart_k1_k2_x_max_value - part_k1_max_y_value;
                int16_t left_by_x = *pPart_k1_k2_x_max_value - *pPart_k1_x_max_value;
                part_k2_factor = (float32_t)left_by_y / left_by_x;
            }
            return this;
        }


        CNotLinearJoystick* calc_part_k1(int16_t in)
        {
            if ( (in >= 0 ? in : -in) <= *pPart_k1_x_max_value)
            {
                part_k1_current_value = in * part_k1_factor;
            }
            else
            {
                part_k1_current_value = in >= 0 ? part_k1_max_y_value : -part_k1_max_y_value;
            }

            return this;
        }

        CNotLinearJoystick* calc_part_k2(int16_t in)
        {
            if ( (in >= 0 ? in : -in) <= *pPart_k1_x_max_value)
            {
                part_k2_current_value = 0;
            }
            else
            {
                int16_t y = in >= 0 ? *pPart_k1_x_max_value : -*pPart_k1_x_max_value;
                part_k2_current_value = (in - y ) * part_k2_factor;
            }

            return this;
        }
    };
//}
