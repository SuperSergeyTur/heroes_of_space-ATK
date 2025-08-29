//#include <iostream>
//#include "defines.h"

//using namespace std;

// Цей класс э одним з двох Додатків до S-подібного ЗІ "CNotLinearFourTempZI"

//namespace NotLinearZI
//{
    class CTools
    {
    public:
        //--- РљРѕРЅРІРµСЂС‚РµСЂРё РґР»СЏ РїРµСЂРµРІРµРґРµРЅРЅСЏ С–СЃРЅСѓСЋС‡РёС… РЅРѕРјС–РЅР°Р»С–РІ Сѓ РїСЂРѕРіСЂР°РјС– Р· "word" Сѓ "float"  -------
        //
        // С†С– РґРІР° РјРµС‚РѕРґРё Р·СЂРѕР±Р»РµРЅРѕ С‰РѕР± Р±СѓР»Рѕ Р»РµРіС€Рµ С€СѓРєР°С‚Рё РґРµ Сѓ РїСЂРѕРіСЂР°РјРјС– СЂРѕР±Р»СЏС‚СЊСЃСЏ
        // РїРµСЂРµС…РѕРґРё РІС–Рґ Р·РѕРІРЅС–С€РЅС–С… "word" РґРѕ РІРЅСѓС‚СЂС–С€РЅС–С… "float"
        static float32_t conv_to_float(uint16_t value)
        {
            return (float32_t)value;
        }

        static float32_t conv_to_float(int16_t value)
        {
            return (float32_t)value;
        }

        //  _MkSec(...) -> Р·РІРёС‡Р°Р№РЅС– float-СЃРµРєСѓРЅРґРё
        static float32_t conv_mksec_to_sec(uint16_t MkSec)
        {
            return conv_to_float(MkSec) / conv_to_float(_MkSec(1000)) / 1000; // РїРµСЂРµРєР»Р°Рґ Р· РґС–СЃРєСЂРµС‚ РјС–РєСЂРѕСЃРµРєСѓРЅРґ Сѓ СЃРµРєСѓРЅРґРё
        }

        //  _Sec(...) -> Р·РІРёС‡Р°Р№РЅС– float-СЃРµРєСѓРЅРґРё
        static float32_t conv_sec_to_sec(uint16_t sec)
        {
            return conv_to_float(sec) / conv_to_float(_Sec(1.0)); // РїРµСЂРµРєР»Р°Рґ Р· РґС–СЃРєСЂРµС‚ СЃРµРєСѓРЅРґ Сѓ СЃРµРєСѓРЅРґРё
        }
        //---

    };
    //--------------------------------------------------


    class CNotLinearInternalZI
    {
    public:
        float32_t in;           // одиниці виміру: одиниці (будь які одиниці: номінали, дискрети)
        float32_t out;          // одиниці виміру: одиниці (будь які одиниці: номінали, дискрети)
        float32_t* pTemp; // одиниці виміру: одиниці/cекунду
        float32_t calc_cikle;   // одиниці виміру: секунди (справжні секунди, не _Sec(), не _MkSec())
        float32_t   step;
        //---
        float32_t out_internal_linear;          // одиниці виміру: одиниці (будь які одиниці: номінали, дискрети)
    public:
        //CNotLinearInternalZI() 
        void Constructor() // init for CM3
        {
            in = 0;           
            out = 0;          
            out_internal_linear = 0;
            pTemp = NULL; 
            calc_cikle = 0;   
            step = 0;
        }

        CNotLinearInternalZI* init(float32_t* pTemp, float32_t calc_cikle)
        {
            Constructor();
            //---
            this->pTemp = pTemp;
            this->calc_cikle = calc_cikle;
            return this;
        }

 /*   variant of linear zi 
        
 CNotLinearInternalZI* calc_zi_original(float32_t in_value)
        {
            in = in_value;

            float32_t direction = in - out;

            calc_step();

            if (direction > 0)
            {
                out += step;
                if (out > in) out = in;
            }
            else if (direction < 0)
            {
                out -= step;
                if (out < in) out = in;
            }

            return this;
        }

        CNotLinearInternalZI* set_zi(float32_t out_value)
        {
            out = out_value;
            out2 = out_value;

            return this;
        }

        CNotLinearInternalZI* calc_step()
        {
            step = calc_step(*pTemp);
            return this;
        }

        float32_t calc_step(float32_t temp)
        {
            return  temp * calc_cikle;
        }

        float32_t count_iterations_to_discharge_out(uint16_t temp_to_discharge)
        {
            float32_t   iterations_count = 0;
            float32_t   step = calc_step(temp_to_discharge);
            if (step != 0)      iterations_count = abs(out / step);
            else if (out == 0)  iterations_count = 0;
            else                iterations_count = NAN;

            return iterations_count;
        }

        float32_t calc_sum_while_discharge_out(uint16_t temp_to_discharge)
        {
            float32_t iterations_count = count_iterations_to_discharge_out(temp_to_discharge);
            float32_t sum_step = calc_step(this->out);
            float32_t sum = 0;
            if (!isnan(iterations_count))
            {
                sum = sum_step / 2 * iterations_count;
            }

            return sum;
        }

        float32_t calc_temp_by_time(uint16_t time, float32_t value_per_time)
        {
            float32_t time_f = CTools::conv_sec_to_sec(time);
            float32_t time2 = (float32_t)(time_f < 0.02 ? 0.02 : time_f);
            return abs(value_per_time) / time2;
        }*/

 //----------------------------

 //     variant of quadratic parabola zi

        CNotLinearInternalZI* calc_zi(float32_t in_value)
        {
            in = in_value;

            float32_t direction = in - out;

            calc_step();

            if (direction > 0)
            {
                out_internal_linear += step;
                out = out_internal_linear * out_internal_linear;
                if (out_internal_linear < 0) out = -out;
                if (out > in) { out = in; out_internal_linear -= step; }
            }
            else if (direction < 0)
            {
                out_internal_linear -= step;
                out = out_internal_linear * out_internal_linear;
                if (out_internal_linear < 0) out = -out;
                if (out < in) { out = in; out_internal_linear += step; }
            }

            return this;
        }

        CNotLinearInternalZI* set_zi(float32_t out_value)
        {
            out = out_value;
            out_internal_linear = sqrt(abs(out_value));
            if (out < 0) out_internal_linear = -out_internal_linear;

            return this;
        }

        CNotLinearInternalZI* calc_step()
        {
            step = calc_step(*pTemp);
            return this;
        }

        float32_t calc_step(float32_t temp)
        {
            return  temp * calc_cikle;
        }

        float32_t count_iterations_to_discharge_out(uint16_t temp_to_discharge)
        {
            float32_t   iterations_count = 0;
            float32_t   step = calc_step(temp_to_discharge);
            if (step != 0)       iterations_count = abs(out_internal_linear / step);
            else if (out_internal_linear == 0)  iterations_count = 0;
            else                 iterations_count = NAN;

            return iterations_count;
        }

        // https://elementy.ru/problems/2068/Summy_kvadratov_summy_kubov
        // 1*1 + 2*2 + 3*3 + … + n*n = (n*(n + 1)/2) * ((2n + 1)/3) = n*(n + 1)*(2n + 1)/6.
        // but in our case "step != 1" : for example: "10*10 + 20*20 + 30*30" where "step = 10"
        // so sum = (n*(n + 1)*(2n + 1)/6) * step*step * calc_cikle
        float32_t calc_sum_formula(float32_t n, float32_t step, float32_t calc_cikle)
        {
            float32_t sum = 0;
            //step += 1;
            if (!isnan(n))
            {
                sum = n * (n + 1) * (2 * n + 1) / 6 * (step * step) * calc_cikle;
            }
            return sum;
        }


        float32_t calc_sum_while_discharge_out(float32_t temp_to_discharge)
        {
            float32_t iterations_count = count_iterations_to_discharge_out(temp_to_discharge);
            float32_t step = calc_step(abs(temp_to_discharge));
            float32_t sum = calc_sum_formula(iterations_count, step, calc_cikle);
            if (this->out_internal_linear < 0) sum = -sum;
            return sum; 
        }

        float32_t calc_temp_by_time(uint16_t time, float32_t value_per_time)
        {
            float32_t time_f = CTools::conv_sec_to_sec(time);
            float32_t time2 = (float32_t)(time_f < 0.02 ? 0.02 : time_f);
            float32_t value2 = sqrt(abs(value_per_time)); 
            return abs(value2) / time2;
        }

    };
//}
