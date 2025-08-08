#ifndef led_control_h
#define led_control_h


extern  void  LED_control ( word code ) ;

#define  Set_LED3( color1, time1, color2, time2, color3, time3 )  LED_con.color1 = color1, LED_con.time1 = time1, \
                                                                  LED_con.color2 = color2, LED_con.time2 = time2, \
                                                                  LED_con.color3 = color3, LED_con.time3 = time3


#define  Set_LED2( color1, time1, color2, time2 )                 LED_con.color1 = color1, LED_con.time1 = time1, \
                                                                  LED_con.color2 = color2, LED_con.time2 = time2, \
                                                                                             LED_con.time3 = 0

#define  Set_LED1( color1 )                                       LED_con.color1 = color1, LED_con.time1 = 0,     \
                                                                                           LED_con.time2 = 0,     \
                                                                                           LED_con.time3 = 0



struct  LED_CONTROL {
                      byte color1, time1 ;
                      byte color2, time2 ;
                      byte color3, time3 ;
                    } ;


#define  _LED_RED        0x01
#define  _LED_GREEN      0x02
#define  _LED_BLUE       0x03
#define  _LED_YELLOW     0x04
#define  _LED_CYAN       0x06
#define  _LED_PURPLE     0x07
#define  _LED_WHITE      0x09
#define  _LED_BLACK      0x0B
#define  _LED_OFF        0x0B


/*------------------------------------------------*/
#ifdef _MAIN_INCLUDE
/*------------------------------------------------*/

struct  LED_CONTROL  LED_con, led_con ;

#else  // _MAIN_INCLUDE

extern  struct  LED_CONTROL  LED_con, led_con ;

#endif // _MAIN_INCLUDE
#endif
