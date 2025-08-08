#ifndef  _MCO_SDO_H
  #define  _MCO_SDO_H

//************************************   Описание SDO-посылок   *************************
//#pragma pack(1)

#ifndef _Union_FR

typedef union
{
	byte  all;
	struct
	{
	   byte  s		: 1;
	   byte  e		: 1;
	   byte  n		: 2;
	   byte  res	: 1;
	   byte  cs	    : 3;
	}_;
}TServInit;

typedef union
{
	byte all;
	struct
	{
	   byte  c		: 1;
	   byte  n		: 3;
	   byte  t		: 1;
	   byte  cs	    : 3;
	}_;
}TServLoad;

typedef union
{
	byte all;
	struct
	{
	   byte  ss	    : 1;
	   byte  s		: 1;
	   byte  cc	    : 1;
       byte  res	: 2;
	   byte  cs	    : 3;
	}_;
}TBlockServInit;

typedef union
{
	byte all;
	struct
	{
	   byte  seq 	: 7;
	   byte  c		: 1;
	}_;
}TBlockServLoadReq;

typedef union
{
	byte all;
	struct
	{
    	byte  ss	: 2;
    	byte  res	: 3;
     	byte  cs	: 3;
	}_;
}TBlockServLoadRes;

typedef struct
{
   word		index;
   byte 	subindex;
   byte   	data[4];
}TSegmentData;

typedef struct
{
   byte 	ack[2];
   byte		blksize;
   byte		res[4];
}TAckData;

typedef struct
{
   byte 	crc[2];
   byte		res[5];
}TEndData;

typedef union
{
	byte  all[8];
	struct
	{
	   byte srv;
	   byte data[7];

	}_;
}TSDO_msg;

#else   // _Union_FR

typedef union
{
	byte  all;
	struct
	{
	   byte  cs	    : 3;
	   byte  res	: 1;
	   byte  n		: 2;
	   byte  e		: 1;
	   byte  s		: 1;
	}_;
}TServInit;

typedef union
{
	byte all;
	struct
	{
	   byte  cs	    : 3;
	   byte  t		: 1;
	   byte  n		: 3;
	   byte  c		: 1;
	}_;
}TServLoad;

typedef union
{
	byte all;
	struct
	{
	   byte  cs	    : 3;
       byte  res	: 2;
	   byte  cc	    : 1;
	   byte  s		: 1;
	   byte  ss	    : 1;
	}_;
}TBlockServInit;

typedef union
{
	byte all;
	struct
	{
	   byte  c		: 1;
	   byte  seq 	: 7;
	}_;
}TBlockServLoadReq;

typedef union
{
	byte all;
	struct
	{
     	byte  cs	: 3;
    	byte  res	: 3;
    	byte  ss	: 2;
	}_;
}TBlockServLoadRes;

typedef struct
{
   word		index;
   byte 	subindex;
   byte   	data[4];
}TSegmentData;

typedef struct
{
   byte 	ack[2];
   byte		blksize;
   byte		res[4];
}TAckData;

typedef struct
{
   byte 	crc[2];
   byte		res[5];
}TEndData;

typedef union
{
	byte  all[8];
	struct
	{
	   byte srv;
	   byte data[7];

	}_;
}TSDO_msg;

#endif

//***************************************************************************************

//****************************   Описание Кодов ошибок   ********************************
#define  _ERR_SDO_t_state			0x05030000	// t-бит не изменил своего состояния

#define  _ERR_SDO_timeout			0x05040000	// Таймаут SDO-протокола
#define  _ERR_SDO_command			0x05040001	// Указатель команды содержит неизвестную команду
#define  _ERR_SDO_size_block		0x05040002	// Неверный размер блока
#define  _ERR_SDO_num_seg			0x05040003	// Неверный порядковый номер сегмента
#define  _ERR_SDO_crc				0x05040004	// Несовпадение CRC
#define  _ERR_SDO_memory			0x05040005	// Недостаточно памяти

#define  _ERR_SDO_access_sw			0x06010000	// Неподдерживаемый доступ к объекту
#define  _ERR_SDO_write_only		0x06010001	// Попытка считать объект с параметром WRITE_ONLY
#define  _ERR_SDO_read_only			0x06010002	// Попытка считать объект с параметром READ_ONLY

#define  _ERR_SDO_object			0x06020000	// Несуществующий объект словаря

#define  _ERR_SDO_object_pdo		0x06040041	// Объект не может быть сопоставлен с PDO
#define  _ERR_SDO_length_pdo		0x06040042	// Количество и длина превышают длину сопоставимую с PDO
#define  _ERR_SDO_parameter			0x06040043	// Общая несовместимость параметра
#define  _ERR_SDO_int_parameter		0x06040047	// Общая несовместимость внутри устройства

#define  _ERR_SDO_access_hw			0x06060000	// Отказ в доступе из-за аппаратной ошибки

#define  _ERR_SDO_type_data_length	0x06070010	// Несоответствие типа данных, несовпадение длины
#define  _ERR_SDO_type_data_max		0x06070012	// Несоответствие типа данных, длина слишком велика
#define  _ERR_SDO_type_data_min		0x06070013	// Несоответствие типа данных, длина слишком мала

#define  _ERR_SDO_subindex        	0x06090011	// Подиндекс не существует
#define  _ERR_SDO_parameter_limit 	0x06090030	// Превышен диапазон значения (только при записи)
#define  _ERR_SDO_value_max       	0x06090031	// Значение записанного параметра велико
#define  _ERR_SDO_value_min       	0x06090032	// Значение записанного параметра мало
#define  _ERR_SDO_max_min         	0x06090036	// Максимальное значение меньше чем минимальное

#define  _ERR_SDO_error				0x08000000	// Общая ошибка
#define  _ERR_SDO_data				0x08000020	// Данные не могут быть переданы
#define  _ERR_SDO_data_local		0x08000021	// Данные не могут быть переданы, из-за запрета модуля локального контроля???
#define  _ERR_SDO_data_state		0x08000022	// Данные не могут быть переданы, из-за текущего состояния
#define  _ERR_SDO_data_dict			0x08000023	// Ошибка динамического создания словаря или его отсутствие
//***************************************************************************************

#ifdef _CANOPEN_INCLUDE

union SDO_FLAG
{
   byte all;
   struct
   {
      byte  init_dl     : 1 ;
      byte  init_ul     : 1 ;
      byte  t_bit       : 1 ;
      byte  blok_dl     : 1 ;
      byte  blok_ul     : 1 ;
   }_;
};

union SDO_FLAG flag_sdo;

TSDO_msg	sdo;


#else

extern union SDO_FLAG flag_sdo;
extern TSDO_msg	sdo;

#endif

#endif  //_SDO_H

