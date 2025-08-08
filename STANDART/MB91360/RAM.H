//------------------
#ifdef _RAM_INCLUDE
//------------------

  word Init_RAM(void);

//byte Proba_mas[100000];
//void Work_RAM();

//------------------
#else
//------------------

//extern byte Proba_mas[];
//extern void Work_RAM();

//------------------
#endif  // _RAM_INCLUDE
//------------------


#ifdef _32K_RAM
  #define RAM_START 0x380000
  #define RAM_END   0x3FFFFF
#else
  #define RAM_START 0x300000
  #define RAM_END   0x31FFFF
#endif

//------------------
#ifdef _TEST_RAM_INCLUDE
//------------------

  void Test_RAM(void);

//------------------
#endif  // _TEST_RAM_INCLUDE
//------------------
