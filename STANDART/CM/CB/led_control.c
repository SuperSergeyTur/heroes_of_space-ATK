

//      ПРОГРАММА УПРАВЛЕНИЯ СВЕТОДИОДОМ ПУЛЬТОВОГО ТЕРМИНАЛА.
//----------------------------------------------------------------



void  LED_control ( word code )
{
  static word time ;

    if ( code == 0 )
    {
      time = Timer1_Ovr ;

      led_con.color1 = _LED_OFF,  led_con.time1 = 0 ;
      led_con.color2 = _LED_OFF,  led_con.time2 = 0 ;
      led_con.color3 = _LED_OFF,  led_con.time3 = 0 ;

      LED_con = led_con ;

      output_c ( led_con.color1 ) ;
      Restart_Output ()  ;

      return ;
    }
    //---


    //if ( time != (b)Timer1_Ovr )
    //time = Timer1_Ovr ;
    if ( (u)(w)(Timer1_Ovr - time) >= _Sec(0.5) )
    {
      time = Timer1_Ovr; //- _Sec(1.0) ;   
    
      //---
            //  Блокируем программу во время Link, CodeReadWriter и т.д.
    if (  Pult_Prog_Addr == _Case ( 'I' ,  0  )  ||
                Mon.Pult == 1                    ||           //   При медленном выводе вешается в А1 на ожидании выдержки
          Pult_Prog_Addr == _Case ( 'J' ,  0  )  ||
          Pult_Prog_Addr == _Case ( 'K' ,  0  )  ||
          Pult_Prog_Addr == _Case ( 'L' ,  0  )  ||
          Pult_Prog_Addr == _Case ( 'M' ,  0  )  ||
          Mon.UartCAN_Connect == 1
       ) return ;  //     2сек между сообщениями - led сбивает ее.

          //---
            //  Если изменили цвет, то сразу переходим к нему.
      //if ( LED_con.color1 != led_con.color1 )
      //{
        //if ( LED_con.time1 == 0 )  output_c ( led_con.color1 ) ;   // Для прямого управления через "Set_LED1 ( color )"
          //---
        //led_con.time1 = 0,  led_con.time2 = 0,  led_con.time3 = 0 ;
      //}

      if ( led_con.time1 != 0 )
      {                            // чтобы не засорять порт посылаем код только в начале выдержки.
        if ( led_con.time1 == LED_con.time1 )
        {
          output_c ( led_con.color1 ) ;
          Restart_Output ()  ;
        }
           //---
        led_con.time1-- ;
      }
      else if ( led_con.time2 != 0 )
      {
        if ( led_con.time2 == LED_con.time2 )
        {
          output_c ( led_con.color2 ) ;
          Restart_Output ()  ;
        }
           //---
        led_con.time2-- ;
      }
      else if ( led_con.time3 != 0 )
      {
        if ( led_con.time3 == LED_con.time3 )
        {
          output_c ( led_con.color3 ) ;
          Restart_Output ()  ;
        }
           //---
        led_con.time3-- ;
      }
      else  led_con = LED_con ;
    }

  return ;
}

