//#include <iostream>
//#include "defines.h"


// Цей класс э одним з двох Додатків до S-подібного ЗІ "CNotLinearFourTempZI".

//namespace NotLinearZI
//{

    class CNotLinearIntegrator
    {
    public:
        float32_t   out;
        float32_t* pTemp;
        float32_t   calc_cikle;
        float32_t   step;


        //CNotLinearIntegrator()
        void Constructor() // init for CM3
        {
            out = 0;
            pTemp = nullptr;
            calc_cikle = 0;
            step = 0;
        }

        CNotLinearIntegrator* init(float32_t* pTemp, float32_t calc_cikle)
        {
            Constructor();
            //---
            this->pTemp = pTemp;
            this->calc_cikle = calc_cikle;
            return this;
        }

        CNotLinearIntegrator* calc_integrator()
        {
            out += calc_step()->step;
            return this;
        }

        CNotLinearIntegrator* set_integrator(float32_t out_value)
        {
            out = out_value;
            return this;
        }

        CNotLinearIntegrator* calc_step()
        {
            step = *pTemp * calc_cikle;
            return this;
        }
    };
//}
