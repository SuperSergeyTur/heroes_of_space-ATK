#ifndef  _841_win_h
#define  _841_win_h

#include "IOcan.h"
#include "maindat.h"

       //   Приводим имя структуры CAN-объекта сообщения CAN-драйвера
       // под WINDOWS к принятому имени в функциях согласования.
    typedef  TCANIO::MSG_STRUCT  MSG_STRUCT_WIN;

typedef struct {
        byte acc_code;
        byte acc_mask;
        byte bt0;
        byte bt1;
}CAN_STRUCT;

#endif
