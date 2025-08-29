//#include <iostream>
//#include "defines.h"

#include "NotLinearInternalZI.cpp"
#include "NotLinearIntegrator.cpp"


//namespace NotLinearZI
//{

enum ECurrentPart { eAny = 0, eNotLinearFinish };

enum EInValueDirection { eNo_razg_torm = 0, eP_razg, eP_torm, eM_razg, eM_torm };


    class CNotLinearFourTempZI
    {

    public:
        int16_t     in;
        int16_t     out;

        uint16_t*   pTemp_p_razg;
        uint16_t*   pTemp_p_torm;
        uint16_t*   pTemp_m_razg;
        uint16_t*   pTemp_m_torm;
        uint16_t*   pTime_parabola_start;
        uint16_t*   pTime_parabola_finish;
        uint16_t*   pTime_null_zone;

    //private:
        int16_t     in_2;
        float32_t   calc_cikle;
        float32_t   time_null_zone;
        int16_t     out_accuracy;

        //---

        bool        is_out_accuracy_reached;

        CNotLinearInternalZI    internal_zi;
        CNotLinearIntegrator   out_integrator;

        int16_t     predicted_out;
        float32_t   temp_of_linear_part;
        float32_t   temp_of_internal_zi;
        float32_t   temp_of_internal_zi_start;
        float32_t   temp_of_internal_zi_finish;
        float32_t   temp_of_current_part;

        ECurrentPart        eCurrent_part;
        EInValueDirection   eDirection;

        float32_t   timer_null_zone;
        uint16_t    switch_null_zone_pos;
        uint16_t    switch_null_zone_neg;
        //---
        bool        startInit;
        uint16_t    time_parabola_start_old;
        uint16_t    time_parabola_finish_old;
        float32_t   temp_of_linear_part_old;
        uint16_t    calcCikle_old;
        uint16_t    time_null_zone_old;
        ECurrentPart eCurrent_part_old;
 
        //CNotLinearFourTempZI()   
        void Constructor() // init for CM3
        {
            in = 0;
            in_2 = 0;
            out = 0;
            //--
            pTemp_p_razg = 0;
            pTemp_p_torm = 0;
            pTemp_m_razg = 0;
            pTemp_m_torm = 0;
            pTime_parabola_start = 0;
            pTime_parabola_finish = 0;
            pTime_null_zone = 0;
            calc_cikle = 0;
            time_null_zone = 0;
            out_accuracy = 0;
            //---
            is_out_accuracy_reached = false;
            predicted_out = 0;
            temp_of_linear_part = 0;
            temp_of_internal_zi = 0;
            temp_of_internal_zi_start = 0;
            temp_of_internal_zi_finish = 0;
            temp_of_current_part = 0;
            eCurrent_part = eAny;
            eDirection = eNo_razg_torm;
            timer_null_zone = 0;
            switch_null_zone_pos = 0;
            switch_null_zone_neg = 0;

            //---
            startInit = true;
            time_parabola_start_old = -1;
            time_parabola_finish_old = -1;
            temp_of_linear_part_old = -1;
            calcCikle_old = 0;
            time_null_zone_old = 0;
            eCurrent_part_old = eAny;
        }

    public:

        CNotLinearFourTempZI* init(
            uint16_t* pTemp_p_razg,
            uint16_t* pTemp_p_torm,
            uint16_t* pTemp_m_razg,
            uint16_t* pTemp_m_torm,
            uint16_t* pTime_parabola_start,
            uint16_t* pTime_parabola_finish,
            uint16_t  calc_cikle,
            uint16_t* pTime_null_zone = 0,
            int16_t  out_value_accuracy = 2)  // 2 ��������, �� 2 �������, ��� ����� ������ "_Skor_nom(0.001)"
        {
            Constructor();
            //---
            this->pTemp_p_razg = pTemp_p_razg;
            this->pTemp_p_torm = pTemp_p_torm;
            this->pTemp_m_razg = pTemp_m_razg;
            this->pTemp_m_torm = pTemp_m_torm;
            this->pTime_parabola_start = pTime_parabola_start;
            this->pTime_parabola_finish = pTime_parabola_finish;
            this->pTime_null_zone = pTime_null_zone,
            this->out_accuracy = out_value_accuracy;
            this->set_calc_cikle(calc_cikle);
            //---
            internal_zi.init(&temp_of_internal_zi, this->calc_cikle);
            out_integrator.init(&temp_of_current_part, this->calc_cikle);

            return this;
        }

        CNotLinearFourTempZI* init(
            uint16_t* pTemp_p_razg,
            uint16_t* pTemp_p_torm,
            uint16_t* pTime_parabola_start,
            uint16_t* pTime_parabola_finish,
            uint16_t  calc_cikle,
            uint16_t* pTime_null_zone = 0,
            uint16_t  out_value_accuracy = 2)  // 2 ��������, �� 2 �������, ��� ����� ������ "_Skor_nom(0.001)"
        {
            return init(pTemp_p_razg, pTemp_p_torm, pTemp_p_razg, pTemp_p_torm, 
                pTime_parabola_start, pTime_parabola_finish,
                calc_cikle, pTime_null_zone, out_value_accuracy);
        }

        CNotLinearFourTempZI* init(
            uint16_t* pTemp_p_razg,
            uint16_t* pTime_parabola_start,
            uint16_t* pTime_parabola_finish,
            uint16_t  calc_cikle,
            uint16_t* pTime_null_zone = 0,
            uint16_t  out_value_accuracy = 2)  // 2 ��������, �� 2 �������, ��� ����� ������ "_Skor_nom(0.001)"
        {
            return init(pTemp_p_razg, pTemp_p_razg, pTemp_p_razg, pTemp_p_razg, 
                pTime_parabola_start, pTime_parabola_finish,
                calc_cikle, pTime_null_zone, out_value_accuracy);
        }


        CNotLinearFourTempZI* zad_intens()
        {
            create_null_zone() ->
            calc_direction()->
            calc_linear_temp()->
            calc_temp_of_internal_zi()->
            predict_out()->
            calc_current_part()->
            check_overrun_and_reset_temp()->
            select_temp_of_internal_zi()->
            calc_internal_zi()->
            calc_integrator()->
            calc_out_accuracy()->
            limit_integrator()->
            calc_out();

            return this;
        }

        CNotLinearFourTempZI* zad_intens(int16_t in_value)
        {
            set_in(in_value)->
            zad_intens();

            return this;
        }

        CNotLinearFourTempZI* set_zi(int16_t out_value)
        {
            in = out_value;
            in_2 = out_value;
            out = out_value;
            out_integrator.set_integrator(CTools::conv_to_float(out_value));
            internal_zi.set_zi(0);

            return this;
        }

        CNotLinearFourTempZI* set_in(int16_t in_value)
        {
            in = in_value;
            return this;
        }

        CNotLinearFourTempZI* set_calc_cikle(uint16_t calc_cikle)
        {
            if (calc_cikle != calcCikle_old)
            {
                calcCikle_old = calc_cikle;
                //---
                this->calc_cikle = CTools::conv_mksec_to_sec(calc_cikle);
                internal_zi.calc_cikle = this->calc_cikle;
                out_integrator.calc_cikle = this->calc_cikle;
            }
            return this;
        }


        //============================================

    private:

        // to create S-cross trough "0" divide all interval betwee in and out to parts above "0" and below "0"
        CNotLinearFourTempZI* create_null_zone()
        {
            if ( pTime_null_zone == 0 || *pTime_null_zone == 0)
            {
                in_2 = in;
                switch_null_zone_pos = 0;
                switch_null_zone_neg = 0;
                return this;
            }
            //---

            if (time_null_zone_old !=  *pTime_null_zone)
            {
                time_null_zone_old = *pTime_null_zone;
                //---
                time_null_zone = CTools::conv_sec_to_sec(*pTime_null_zone);
            }
            //---

            in_2 = in;

            if (in < 0)
            {
                switch_null_zone_pos = 0;
                //---
                switch (switch_null_zone_neg)
                {
                default:
                case 0:
                    if (out > 0)
                    {
                        in_2 = 0;
                        switch_null_zone_neg++;
                    }
                    break;

                case 1:
                    in_2 = 0;
                    if (out <= (0 + out_accuracy))
                    {
                        timer_null_zone = 0;
                        switch_null_zone_neg++;
                    }
                    break;

                case 2:
                    in_2 = 0;
                    timer_null_zone += calc_cikle;
                    if (timer_null_zone >= time_null_zone) switch_null_zone_neg = 0;
                    break;
                }
              
            }
            else if (in > 0)
            {
                switch_null_zone_neg = 0;
                //---
                switch (switch_null_zone_pos)
                {
                default:
                case 0:
                    if (out < 0)
                    {
                        in_2 = 0;
                        switch_null_zone_pos++;
                    }
                    break;

                case 1:
                    in_2 = 0;
                    if (out >= (0 - out_accuracy))
                    {
                        timer_null_zone = 0;
                        switch_null_zone_pos++;
                    }
                    break;

                case 2:
                    in_2 = 0;
                    timer_null_zone += calc_cikle;
                    if (timer_null_zone >= time_null_zone) switch_null_zone_pos = 0;
                    break;
                }

            }
            else
            {
                switch_null_zone_pos = 0;
                switch_null_zone_neg = 0;
            }

            return this;
        }

           
        CNotLinearFourTempZI* calc_direction()
        {
            if (in_2 != out)
            {
                // если вход и выход ЗИ положительны
                if (in_2 >= 0 && out >= 0)
                {
                    // если вход больше выхода ЗИ используется темп разгона в "+".
                    if (in_2 > out)  eDirection = eP_razg;
                    // если вход меньше выхода ЗИ используется темп торможения в "+".
                    else           eDirection = eP_torm;
                }
                // иначе если вход и выход ЗИ отрицательны
                else if (in_2 <= 0 && out <= 0)
                {
                    // если вход меньше выхода ЗИ (по знаку) используется темп разгона в "-".
                    if (in_2 < out )  eDirection = eM_razg;
                    // если вход больше выхода ЗИ (по знаку) используется темп торможения в "-".
                    else           eDirection = eM_torm;
                }
                // если вход отрицательный, а выход положительный
                else if (in_2 <= 0 && out >= 0)  eDirection = eP_torm;
                // если вход положительный, а выход отрицательный
                else if (in_2 >= 0 && out <= 0) eDirection = eM_torm;
            }
            else eDirection = eNo_razg_torm;

            return this;
        }

        CNotLinearFourTempZI* calc_linear_temp()
        {
            switch (eDirection)
            {
                case eP_razg:  temp_of_linear_part = CTools::conv_to_float(*pTemp_p_razg);
                    break;
                case eP_torm:  temp_of_linear_part = -CTools::conv_to_float(*pTemp_p_torm);
                    break;
                case eM_razg:  temp_of_linear_part = -CTools::conv_to_float(*pTemp_m_razg);
                    break;
                case eM_torm:  temp_of_linear_part = CTools::conv_to_float(*pTemp_m_torm);
                    break;
                default:
                case eNo_razg_torm:  temp_of_linear_part = 0;
                    break;
            }

            return this;
        }

        CNotLinearFourTempZI* calc_temp_of_internal_zi()
        {

            if (temp_of_linear_part !=0)
            {
                if (time_parabola_start_old != *pTime_parabola_start || 
                    temp_of_linear_part_old != temp_of_linear_part ||
                    startInit == true) // якщо уставка не змінювалася то не перераховуємо її
                {
                    time_parabola_start_old = *pTime_parabola_start;
                    temp_of_internal_zi_start = internal_zi.calc_temp_by_time(*pTime_parabola_start, temp_of_linear_part);
                }

                if (time_parabola_finish_old != *pTime_parabola_finish ||
                    temp_of_linear_part_old != temp_of_linear_part ||
                    startInit == true) // якщо уставка не змінювалася то не перераховуємо її
                {
                    time_parabola_finish_old = *pTime_parabola_finish;
                    temp_of_internal_zi_finish = internal_zi.calc_temp_by_time(*pTime_parabola_finish, temp_of_linear_part);
                }

                startInit = false;
                temp_of_linear_part_old = temp_of_linear_part;
            }

            return this;
        }

        // прискорення нелінійного темпу якщо зменшили завдання поки ми до нього йшли - інакше буде перегулювання.
        CNotLinearFourTempZI* check_overrun_and_reset_temp()
        {
            if (out > in_2 && internal_zi.out > 0)
            {
                internal_zi.set_zi(0);
            }
            else if (out < in_2 && internal_zi.out < 0)
            {
                internal_zi.set_zi(0);
            }

            return this;
        }


        CNotLinearFourTempZI* predict_out()
        {
            //if (eCurrent_part != ECurrentPart::eNotLinearFinish) � ����� ������� ����� �� ������� �� ��������� �������� ����� ��� �������.
            //{
                float32_t sum = internal_zi.calc_sum_while_discharge_out(temp_of_internal_zi_finish);
                predicted_out = (int16_t)(out + sum);
            //}

            return this;
        }


        CNotLinearFourTempZI* calc_current_part()
        {
            eCurrent_part = eAny;
            switch (eDirection)
            {
            case eP_razg:
            case eM_torm:
                if (predicted_out >= in_2 ) eCurrent_part = eNotLinearFinish;
                //else if (predicted_out < in- out_accuracy) eCurrent_part = eAny;
                break;
            case eP_torm:
            case eM_razg:
                if (predicted_out <= in_2 ) eCurrent_part = eNotLinearFinish;
                //else if (predicted_out > in + out_accuracy) eCurrent_part = eAny;
                break;
            default:
            case eNo_razg_torm:
                //eCurrent_part = eAny;
                break;
            }

            return this;
        }


        CNotLinearFourTempZI* select_temp_of_internal_zi()
        {

            switch (eCurrent_part)
            {
            case eNotLinearFinish:
                temp_of_internal_zi = temp_of_internal_zi_finish;
                break;
            default:
                temp_of_internal_zi = temp_of_internal_zi_start;
                break;
            }

            eCurrent_part_old = eCurrent_part;

            return this;
        }

  
        CNotLinearFourTempZI* calc_internal_zi()
        {
            if (eCurrent_part == eNotLinearFinish)
            {
                temp_of_current_part = internal_zi.calc_zi(0)->out;
            }
            else
            {
                temp_of_current_part = internal_zi.calc_zi(temp_of_linear_part)->out;
            }
            return this;
        }

        CNotLinearFourTempZI* calc_integrator()
        {
            out_integrator.calc_integrator();

            return this;
        }

        CNotLinearFourTempZI* calc_out_accuracy()
        {
            is_out_accuracy_reached = (out_integrator.out <= in_2 + out_accuracy)
                                    &&
                            (out_integrator.out >= in_2 - out_accuracy);

            return this;
        }

        CNotLinearFourTempZI* limit_integrator()
        {
            if (is_out_accuracy_reached) // fine check
            {
               out_integrator.set_integrator( in_2 );
            }
            else
            {
                switch (eDirection)
                {
                case eP_razg:
                case eM_torm:
                    out_integrator.set_integrator ( out_integrator.out >= in_2 ? in_2 : out_integrator.out );
                    break;
                case eP_torm:
                case eM_razg:
                    out_integrator.set_integrator ( out_integrator.out <= in_2 ? in_2 : out_integrator.out );
                    break;
                default:
                case eNo_razg_torm:
                    break;
                }
            }

            return this;
        }

        CNotLinearFourTempZI* calc_out()
        {
            out = (int16_t)out_integrator.out;
            return this;
        }

    };

//}
