#ifndef  _MCO_EMCY_H
  #define  _MCO_EMCY_H

//**********************************    Список ошибок согласно DS402   **************************************
#define _EMCY_No_error						0x0000	// No error
#define _EMCY_Generic_error					0x1000  // Generic error
#define _EMCY_Current		  				0x2000  // Current
#define _EMCY_Current_input					0x2100  // Current - Current on device input size
#define _EMCY_Current_scel					0x2110  // Current - Short circuit/earth leakage
#define _EMCY_Current_el		 			0x2120  // Current - Earth leakage
#define _EMCY_Current_el1		   			0x2121  // Current - Earth leakage phase L1
#define _EMCY_Current_el2		  			0x2122  // Current - Earth leakage phase L2
#define _EMCY_Current_el3					0x2123  // Current - Earth leakage phase L3
#define _EMCY_Current_sc					0x2130  // Current - Short circuit
#define _EMCY_Current_sc12	  				0x2131  // Current - Short circuit phases L1-L2
#define _EMCY_Current_sc23 					0x2132  // Current - Short circuit phases L2-L3
#define _EMCY_Current_sc31	   				0x2133  // Current - Short circuit phases L3-L1
#define _EMCY_IntCurrent	   				0x2200  // Internal current
#define _EMCY_IntCurrent1	   				0x2211  // Internal current - No.1
#define _EMCY_IntCurrent2	   				0x2212  // Internal current - No.2
#define _EMCY_IntCurrent_overramp			0x2213  // Internal current - Over-current in ramp function
#define _EMCY_IntCurrent_overseq			0x2214  // Internal current - Over-current in the sequence
#define _EMCY_IntCurrent_cont		  		0x2220  // Internal current - Continuous over current
#define _EMCY_IntCurrent_cont1  			0x2221  // Internal current - Continuous over current No.1
#define _EMCY_IntCurrent_cont2 		 		0x2222  // Internal current - Continuous over current No.2
#define _EMCY_IntCurrent_scel		  		0x2230  // Internal current - Short circuit/earth leakage
#define _EMCY_IntCurrent_el			  		0x2240  // Internal current - Earth leakage
#define _EMCY_IntCurrent_sc			  		0x2250  // Internal current - Short circuit
#define _EMCY_CurrentOut			  		0x2300  // Current on device output side (Output current)
#define _EMCY_CurrentOut_cont		  		0x2310  // Output current - Continuous over current
#define _EMCY_CurrentOut_cont1		  		0x2311  // Output current - Continuous over current No.1
#define _EMCY_CurrentOut_cont2		  		0x2312  // Output current - Continuous over current No.2
#define _EMCY_CurrentOut_scel		  		0x2320  // Output current - Short circuit/earth leakage
#define _EMCY_CurrentOut_el			  		0x2330  // Output current - Earth leakage
#define _EMCY_CurrentOut_elU		  		0x2331  // Output current - Earth leakage phase U
#define _EMCY_CurrentOut_elV		  		0x2332  // Output current - Earth leakage phase V
#define _EMCY_CurrentOut_elW		  		0x2333  // Output current - Earth leakage phase W
#define _EMCY_CurrentOut_sc			  		0x2340  // Output current - Short circuit
#define _EMCY_CurrentOut_scUV		  		0x2341  // Output current - Short circuit phases U-V
#define _EMCY_CurrentOut_scVW		  		0x2342  // Output current - Short circuit phases V-W
#define _EMCY_CurrentOut_scWU		  		0x2343  // Output current - Short circuit phases W-U
#define _EMCY_Voltage        		  		0x3000  // Voltage
#define _EMCY_Voltage_mains    		  		0x3100  // Voltage - Mains voltage
#define _EMCY_Voltage_mainsov  		  		0x3110  // Voltage - Mains over-voltage
#define _EMCY_Voltage_mainsov1 		  		0x3111  // Voltage - Mains over-voltage phase L1
#define _EMCY_Voltage_mainsov2 		  		0x3112  // Voltage - Mains over-voltage phase L2
#define _EMCY_Voltage_mainsov3 		  		0x3113  // Voltage - Mains over-voltage phase L3
#define _EMCY_Voltage_mainsuv  		  		0x3120  // Voltage - Mains under-voltage
#define _EMCY_Voltage_mainsuv1 		  		0x3121  // Voltage - Mains under-voltage phase L1
#define _EMCY_Voltage_mainsuv2 		  		0x3122  // Voltage - Mains under-voltage phase L2
#define _EMCY_Voltage_mainsuv3 		  		0x3123  // Voltage - Mains under-voltage phase L3
#define _EMCY_Voltage_phase    		  		0x3130  // Voltage - Phase failure
#define _EMCY_Voltage_phase1   		  		0x3131  // Voltage - Phase failure L1
#define _EMCY_Voltage_phase2   		  		0x3132  // Voltage - Phase failure L2
#define _EMCY_Voltage_phase3   		  		0x3133  // Voltage - Phase failure L3
#define _EMCY_Voltage_mainsfreq  	  		0x3140  // Voltage - Mains frequency
#define _EMCY_Voltage_mainsfreqg 	  		0x3141  // Voltage - Mains frequency too great
#define _EMCY_Voltage_mainsfreqs 	  		0x3142  // Voltage - Mains frequency too small
#define _EMCY_Voltage_dclink	 	  		0x3200  // Voltage - DC link
#define _EMCY_Voltage_dcover	 	  		0x3210  // Voltage - DC link over-voltage
#define _EMCY_Voltage_dcover1	 	  		0x3211  // Voltage - DC link over-voltage No.1
#define _EMCY_Voltage_dcover2	 	  		0x3212  // Voltage - DC link over-voltage No.2
#define _EMCY_Voltage_dcunder	 	  		0x3220  // Voltage - DC link under-voltage
#define _EMCY_Voltage_dcunder1	 	  		0x3221  // Voltage - DC link under-voltage No.1
#define _EMCY_Voltage_dcunder2	 	  		0x3222  // Voltage - DC link under-voltage No.2
#define _EMCY_Voltage_loaderror	 	  		0x3230  // Voltage - Load error
#define _EMCY_Voltage_outvolt	 	  		0x3300  // Voltage - Output voltage
#define _EMCY_Voltage_outover	 	  		0x3310  // Voltage - Output over-voltage
#define _EMCY_Voltage_outoverU	 	  		0x3311  // Voltage - Output over-voltage phase U
#define _EMCY_Voltage_outoverV	 	  		0x3312  // Voltage - Output over-voltage phase V
#define _EMCY_Voltage_outoverW	 	  		0x3313  // Voltage - Output over-voltage phase W
#define _EMCY_Voltage_arm		 	  		0x3320  // Voltage - Armature circuit
#define _EMCY_Voltage_armint	 	  		0x3321  // Voltage - Armature circuit interrupted
#define _EMCY_Voltage_field		 	  		0x3330  // Voltage - Field circuit
#define _EMCY_Voltage_fieldint	 	  		0x3331  // Voltage - Field circuit interrupted
#define _EMCY_Temp       		 	  		0x4000  // Temperature
#define _EMCY_Temp_ambient 		 	  		0x4100  // Temperature - Ambient temperature
#define _EMCY_Temp_examb   		 	  		0x4110  // Temperature - Excess ambient temperature
#define _EMCY_Temp_lowamb 		 	  		0x4120  // Temperature - Too low ambient temperature
#define _EMCY_Temp_supamb		 	  		0x4130  // Temperature - Temperature supply air
#define _EMCY_Temp_outamb		 	  		0x4140  // Temperature - Temperature air outlet
#define _EMCY_Temp_device		 	  		0x4200  // Temperature - Temperature device
#define _EMCY_Temp_exdev 		 	  		0x4210  // Temperature - Excess temperature device
#define _EMCY_Temp_lowdev		 	  		0x4220  // Temperature - Too low temperature device
#define _EMCY_Temp_drive 		 	  		0x4300  // Temperature - Temperature drive
#define _EMCY_Temp_exdrv 		 	  		0x4310  // Temperature - Excess temperature drive
#define _EMCY_Temp_lowdrv		 	  		0x4320  // Temperature - Too low temperature drive
#define _EMCY_Temp_supply 		 	  		0x4400  // Temperature - Temperature supply
#define _EMCY_Temp_exsup 		 	  		0x4410  // Temperature - Excess temperature supply
#define _EMCY_Temp_lowsup		 	  		0x4420  // Temperature - Too low temperature supply
#define _EMCY_Hardware     		 	  		0x5000  // Device Hardware
#define _EMCY_Hardware_supply	 	  		0x5100  // Device Hardware - Supply
#define _EMCY_Hardware_lowsup	 	  		0x5110  // Device Hardware - Supply low voltage
#define _EMCY_Hardware_lowsup1	 	  		0x5111  // Device Hardware - U1 = supply +/-15V
#define _EMCY_Hardware_lowsup2	 	  		0x5112  // Device Hardware - U2 = supply +24V
#define _EMCY_Hardware_lowsup3	 	  		0x5113  // Device Hardware - U3 = supply +5V
#define _EMCY_Hardware_lowsup4	 	  		0x5114  // Device Hardware - U4 = manufacturer specific
#define _EMCY_Hardware_lowsup5	 	  		0x5115  // Device Hardware - U5 = manufacturer specific
#define _EMCY_Hardware_lowsup6	 	  		0x5116  // Device Hardware - U6 = manufacturer specific
#define _EMCY_Hardware_lowsup7	 	  		0x5117  // Device Hardware - U7 = manufacturer specific
#define _EMCY_Hardware_lowsup8	 	  		0x5118  // Device Hardware - U8 = manufacturer specific
#define _EMCY_Hardware_lowsup9	 	  		0x5119  // Device Hardware - U9 = manufacturer specific
#define _EMCY_Hardware_supint	 	  		0x5120  // Device Hardware - Supply intermediate circuit
#define _EMCY_Hardware_control	 	  		0x5200  // Device Hardware - Control
#define _EMCY_Hardware_meas   	 	  		0x5210  // Device Hardware - Measurement circuit
#define _EMCY_Hardware_comp   	 	  		0x5220  // Device Hardware - Computing circuit
#define _EMCY_Hardware_operunit	 	  		0x5300  // Device Hardware - Operating unit
#define _EMCY_Hardware_power   	 	  		0x5400  // Device Hardware - Power section
#define _EMCY_Hardware_outstages 	  		0x5410  // Device Hardware - Output stages
#define _EMCY_Hardware_chopper 	 	  		0x5420  // Device Hardware - Chopper
#define _EMCY_Hardware_inpstages 	  		0x5430  // Device Hardware - Input stages
#define _EMCY_Hardware_contacts	 	  		0x5440  // Device Hardware - Contacts
#define _EMCY_Hardware_contact1	 	  		0x5441  // Device Hardware - Contact1 = manufacturer specific
#define _EMCY_Hardware_contact2	 	  		0x5442  // Device Hardware - Contact2 = manufacturer specific
#define _EMCY_Hardware_contact3	 	  		0x5443  // Device Hardware - Contact3 = manufacturer specific
#define _EMCY_Hardware_contact4	 	  		0x5444  // Device Hardware - Contact4 = manufacturer specific
#define _EMCY_Hardware_contact5	 	  		0x5445  // Device Hardware - Contact5 = manufacturer specific
#define _EMCY_Hardware_fuses   	 	  		0x5450  // Device Hardware - Fuses
#define _EMCY_Hardware_S1 		 	  		0x5451  // Device Hardware - S1 = manufacturer specific
#define _EMCY_Hardware_S2 		 	  		0x5452  // Device Hardware - S2 = manufacturer specific
#define _EMCY_Hardware_S3 		 	  		0x5453  // Device Hardware - S3 = manufacturer specific
#define _EMCY_Hardware_S4 		 	  		0x5454  // Device Hardware - S4 = manufacturer specific
#define _EMCY_Hardware_S5 		 	  		0x5455  // Device Hardware - S5 = manufacturer specific
#define _EMCY_Hardware_S6 		 	  		0x5456  // Device Hardware - S6 = manufacturer specific
#define _EMCY_Hardware_S7 		 	  		0x5457  // Device Hardware - S7 = manufacturer specific
#define _EMCY_Hardware_S8 		 	  		0x5458  // Device Hardware - S8 = manufacturer specific
#define _EMCY_Hardware_S9 		 	  		0x5459  // Device Hardware - S9 = manufacturer specific
#define _EMCY_Hardware_datastorage	  		0x5500  // Device Hardware - Data storage
#define _EMCY_Hardware_workmem    	  		0x5510  // Device Hardware - Working memory
#define _EMCY_Hardware_progrmem   	  		0x5520  // Device Hardware - Program memory
#define _EMCY_Hardware_nvmem      	  		0x5530  // Device Hardware - Non-volatile data memory
#define _EMCY_Software            	  		0x6000  // Device Software
#define _EMCY_Software_resetwd    	  		0x6010  // Device Software - Software reset (watchdog)
#define _EMCY_Software_intsoft    	  		0x6100  // Device Software - Internal software
#define _EMCY_Software_usersoft   	  		0x6200  // Device Software - User software
#define _EMCY_Software_datarec    	  		0x6300  // Device Software - Data record
#define _EMCY_Software_datarec1   	  		0x6301  // Device Software - Data record No.1
#define _EMCY_Software_datarec2   	  		0x6302  // Device Software - Data record No.2
#define _EMCY_Software_datarec3   	  		0x6303  // Device Software - Data record No.3
#define _EMCY_Software_datarec4   	  		0x6304  // Device Software - Data record No.4
#define _EMCY_Software_datarec5   	  		0x6305  // Device Software - Data record No.5
#define _EMCY_Software_datarec6   	  		0x6306  // Device Software - Data record No.6
#define _EMCY_Software_datarec7   	  		0x6307  // Device Software - Data record No.7
#define _EMCY_Software_datarec8   	  		0x6308  // Device Software - Data record No.8
#define _EMCY_Software_datarec9   	  		0x6309  // Device Software - Data record No.9
#define _EMCY_Software_datarec10  	  		0x630a  // Device Software - Data record No.10
#define _EMCY_Software_datarec11  	  		0x630b  // Device Software - Data record No.11
#define _EMCY_Software_datarec12  	  		0x630c  // Device Software - Data record No.12
#define _EMCY_Software_datarec13  	  		0x630d  // Device Software - Data record No.13
#define _EMCY_Software_datarec14  	  		0x630e  // Device Software - Data record No.14
#define _EMCY_Software_datarec15  	  		0x630f  // Device Software - Data record No.15
#define _EMCY_Software_lossparam  	  		0x6310  // Device Software - Loss of parameters
#define _EMCY_Software_paramerr   	  		0x6320  // Device Software - Parameter error
#define _EMCY_AddModule           	  		0x7000  // Additional modules
#define _EMCY_AddModule_power     	  		0x7100  // Additional modules - Power
#define _EMCY_AddModule_bc       	  		0x7110  // Additional modules - Brake chopper
#define _EMCY_AddModule_failbc         		0x7111  // Additional modules - Failure brake chopper
#define _EMCY_AddModule_overbc         		0x7112  // Additional modules - Over current brake chopper
#define _EMCY_AddModule_protbc         		0x7113  // Additional modules - Protective circuit brake chopper
#define _EMCY_AddModule_motor    	  		0x7120  // Additional modules - Motor
#define _EMCY_AddModule_motorblok	  		0x7121  // Additional modules - Motor blocked
#define _EMCY_AddModule_motorerr 	  		0x7122  // Additional modules - Motor error or communication malfunction
#define _EMCY_AddModule_motortilt	  		0x7123  // Additional modules - Motor tilted
#define _EMCY_AddModule_meas     	  		0x7200  // Additional modules - Measurement circuit
#define _EMCY_AddModule_sensor   	  		0x7300  // Additional modules - Sensor
#define _EMCY_AddModule_tachof   	  		0x7301  // Additional modules - Tacho fault
#define _EMCY_AddModule_tachopol 	  		0x7302  // Additional modules - Tacho wrong polarity
#define _EMCY_AddModule_resolv1  	  		0x7303  // Additional modules - Resolver 1 fault
#define _EMCY_AddModule_resolv2  	  		0x7304  // Additional modules - Resolver 2 fault
#define _EMCY_AddModule_sens1    	  		0x7305  // Additional modules - Incremental sensor 1 fault
#define _EMCY_AddModule_sens2    	  		0x7306  // Additional modules - Incremental sensor 2 fault
#define _EMCY_AddModule_sens3    	  		0x7307  // Additional modules - Incremental sensor 3 fault
#define _EMCY_AddModule_speed    	  		0x7310  // Additional modules - Speed
#define _EMCY_AddModule_pos      	  		0x7320  // Additional modules - Position
#define _EMCY_AddModule_comp     	  		0x7400  // Additional modules - Computation circuit
#define _EMCY_AddModule_com      	  		0x7500  // Additional modules - Communication
#define _EMCY_AddModule_ser1     	  		0x7510  // Additional modules - Serial interface No.1
#define _EMCY_AddModule_ser2     	  		0x7520  // Additional modules - Serial interface No.2
#define _EMCY_AddModule_data     	  		0x7600  // Additional modules - Data storage
#define _EMCY_Monitor            	  		0x8000  // Monitoring
#define _EMCY_Monitor_comm         	  		0x8100  // Monitoring - Communication
#define _EMCY_Monitor_canover    	  		0x8110  // Monitoring - CAN overrun (object lost)
#define _EMCY_Monitor_canepm     	  		0x8120  // Monitoring - CAN in Error Passive Mode
#define _EMCY_Monitor_hberr      	  		0x8130  // Monitoring - LifeGuard error or Heartbeat error
#define _EMCY_Monitor_recov      	  		0x8140  // Monitoring - Recovered from bus-off
#define _EMCY_Monitor_tcobid     	  		0x8150  // Monitoring - Transmit COB-ID
#define _EMCY_Monitor_protocol   	  		0x8200  // Monitoring - Protocol error
#define _EMCY_Monitor_pdoerror   	  		0x8210  // Monitoring - PDO not processed due to length error
#define _EMCY_Monitor_pdolength  	  		0x8220  // Monitoring - PDO length exceeded
#define _EMCY_Monitor_torque     	  		0x8300  // Monitoring - Torque control
#define _EMCY_Monitor_extorque     	  		0x8311  // Monitoring - Excess torque
#define _EMCY_Monitor_difstart  	  		0x8312  // Monitoring - Difficult start up
#define _EMCY_Monitor_standtorque	  		0x8313  // Monitoring - Standstill torque
#define _EMCY_Monitor_instorque  	  		0x8321  // Monitoring - Insufficient torque
#define _EMCY_Monitor_torquef    	  		0x8331  // Monitoring - Torque fault
#define _EMCY_Monitor_vlspeed    	  		0x8400  // Monitoring - Velocity speed controller
#define _EMCY_Monitor_pos        	  		0x8500  // Monitoring - Position controller
#define _EMCY_Monitor_posing     	  		0x8600  // Monitoring - Positioning controller
#define _EMCY_Monitor_folerr     	  		0x8611  // Monitoring - Following error
#define _EMCY_Monitor_reflim     	  		0x8612  // Monitoring - Reference limit
#define _EMCY_Monitor_sync       	  		0x8700  // Monitoring - Sync controller
#define _EMCY_Monitor_wind       	  		0x8800  // Monitoring - Winding controller
#define _EMCY_Monitor_pdm        	  		0x8900  // Monitoring - Process data monitoring
#define _EMCY_Monitor_control    	  		0x8A00  // Monitoring - Control
#define _EMCY_ExtError           	  		0x9000  // External error
#define _EMCY_AddFunc           	  		0xF000  // Additional functions
#define _EMCY_AddFunc_decel      	  		0xF001  // Additional functions - Deceleration
#define _EMCY_AddFunc_subsync   	  		0xF002  // Additional functions - Sub-synchronous run
#define _EMCY_AddFunc_stroke    	  		0xF003  // Additional functions - Stroke operation
#define _EMCY_AddFunc_control   	  		0xF004  // Additional functions - Control

//#define _EMCY_Manuf_     			  		0xFF00  // Manufacturer specific
//#define _EMCY_Manuf_     			  		0xFFFF  // Manufacturer specific



byte EMCY_Send( lword code );


#endif // _EMCY_H
