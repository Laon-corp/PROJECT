//***************************************************************************
// Filename:  orb_glob.h         Creation Date: 10.10.97       Language: C
// Author:    paul dorrell   
// Project:   orbit interface software
// Copyright: (c) Solartron Group Limited 1997
//                Solartron Metrology, Steyning Way, Bognor Regis, Sussex, UK. 
//                Tel + 44 (0)1243 825011,  Fax + 44 (0)1243 861244
//***************************************************************************
// Purpose:
// To define symbolic constants shared between orbit interface software and
// an orbit application software.
//***************************************************************************
// Modification History.
//***************************************************************************
// Name:                                                   Date: xx/xx/xx
// Version:
// Mod Details:
//
// Name:                                                   Date: xx/xx/xx
// Version:
// Mod Details:
//
//***************************************************************************

// Constant string definitions
#define NUMBER_OF_CHARS_IN_IF_VERSION 31
#define DEFAULT_IF_VERSION_STRING "Orbit Network DLL - Version x.x"
#define NUMBER_OF_CHARS_IN_NETWORK_NAME 30
#define DEFAULT_NETWORK_NAME "******************************"
#define NUMBER_OF_CHARS_IN_PROBE_ID 10
#define DEFAULT_PROBE_ID "**********"
#define NUMBER_OF_CHARS_IN_DEVICE_TYPE 12
#define DEFAULT_DEVICE_TYPE "************"
#define NUMBER_OF_CHARS_IN_SOFTWARE_VERSION 5
#define DEFAULT_SOFTWARE_VERSION "V****"
#define NUMBER_OF_CHARS_IN_MODULE_TYPE 4
#define DEFAULT_MODULE_TYPE "****"
#define NUMBER_OF_CHARS_IN_MODULE_INFO 32
#define DEFAULT_MODULE_INFO "********************************"
#define NUMBER_OF_CHARS_IN_ERROR_STRING 80
#define SIZE_OF_READINGS_ARRAY 25
#define SIZE_OF_BUFFER_ARRAY 32
#define MAX_NUMBER_OF_PROBES_IN_NETWORK 31
//#define NUMBER_OF_CHARS_IN_CARD_NAME 10
#define DEFAULT_CARD_NAME "**********"
#define MAX_NUMBER_OF_ORBIT_NETWORK_CARDS 4
#define NUMBER_OF_NETWORKS_PER_CARD 2
#define MAX_NUMBER_OF_ISA_NETWORKS MAX_NUMBER_OF_ORBIT_NETWORK_CARDS * NUMBER_OF_NETWORKS_PER_CARD
#define MAX_NUMBER_OF_232_NETWORKS 2
#define MAX_NUMBER_OF_NETWORKS MAX_NUMBER_OF_ISA_NETWORKS + MAX_NUMBER_OF_232_NETWORKS

// Bit masking defininitions
#define PROBE_TYPE_MASK 0xc000

#define BIT_0	0x0001
#define BIT_1	0x0002
#define BIT_2	0x0004
#define BIT_3	0x0008
#define BIT_4	0x0010
#define BIT_5	0x0020
#define BIT_6	0x0040
#define BIT_7	0x0080
#define BIT_8	0x0100
#define BIT_9	0x0200
#define BIT_10	0x0400
#define BIT_11	0x0800
#define BIT_12	0x1000
#define BIT_13	0x2000
#define BIT_14	0x4000
#define BIT_15	0x8000

#define LE_DIRECTION	  	BIT_2
#define LE_REFMARK_FOUND	BIT_3
#define LE_REFMARK_READ		BIT_4
#define LE_REFMARK_SOUGHT	BIT_5
#define LE_NEW_READING		BIT_11
#define LE_DIFF_STOPPED		BIT_14
#define LE_DIFF_STARTED		BIT_15

// Type enumerations for Orbit controllers
enum NETWORK_CONTROLLER_TYPE {
   UNDEFINED_NETWORK_CONTROLLER,
   ISA,
   RS232,
   PCI
};

// Enumeration for Orbit Interface DLL returns
enum ORBIT_STATUS_ERRORS {
   ORBIT_STATUS_OK = 0,

   // network controller errors
   NETWORK_CONTROLLER_NOT_FOUND     = 1,
   NETWORK_CONTROLLER_TIMEOUT       = 2,
   NETWORK_CONTROLLER_WRITE_TIMEOUT = 3,
   NETWORK_CONTROLLER_READ_TIMEOUT  = 4,
   NOT_CONNECTED_TO_ORBIT_NETWORKS  = 5,    //MOD1V1 added 
   UNRECOGNISED_NETWORK_CONTROLLER  = 6,
   BAD_RS232_SETTING_BYTE           = 7,
   BAD_ORBIT_SPEED_BYTE             = 8,
   MISSING_PROBE_ACKNOWLEDGEMENT    = 9,

   // passed parameter errors
   BAD_NETWORK_NUMBER                   = 10,
   BAD_PROBE_ADDRESS                    = 11,
   BAD_ID_STRING_LENGTH                 = 12,
   BAD_MODULE_TYPE_STRING_LENGTH        = 13,
   BAD_SOFTWARE_VERSION_STRING_LENGTH   = 14,
   NETWORK_ADDRESS_ALREADY_ALLOCATED    = 15,
   BAD_NETWORK_STRING_LENGTH            = 16,
   BAD_DEVICE_TYPE_STRING_LENGTH        = 17,
   BAD_MODULE_INFO_STRING_LENGTH        = 18,
   BAD_IF_VERSION_STRING_LENGTH         = 19,
   BAD_ERROR_STRING_LENGTH              = 20,

   // rs485 comms errors
   RS485_CHECKSUM_ERROR             = 0x00fd,   // from RS232IM.
   RS485_PARITY_ERROR               = 0x00fe,
   RS485_RX_TIMEOUT                 = 0x00ff,

   // General Errors
   ORB_MODULE_RECEIVE_PE            = 0x2101,
   BROADCAST_ADD_NOT_ALLOWED        = 0x2104,
   BROADCAST_ADDRESS_00_EXPECTED    = 0x2105,
   ADD_CHANGE_NOT_ALLOWED           = 0x2106,
   MISSED_READING                   = 0x2109,
   READING_HOLDOFF                  = 0x210a,


   // probe errors
   PROBE_CAL_OVERFLOW               = 0x2111,
   PROBE_OVER_RANGE                 = 0x2113,
   PROBE_UNDER_RANGE                = 0x2112,
   PROBE_MULTIPLY_OVERFLOW          = 0x2114,

   // buffer mode errors
   BUFFER_FULL                      = 0x2116,
   ORBITREADBUFFER_NOT_VALID        = 0x2117,
   ORBITREAD_NOT_VALID              = 0x2118,
   BUFFER_READ_WRITE_ERROR          = 0x2119,
   BUFFER_NOT_EMPTY                 = 0x211a,
   BUFFER_EMPTY_IN_STOPPED          = 0x211b,

   // difference mode errors
   NOT_IN_DIFF_MODE                 = 0x2121,
   WAITING_FOR_START_DIFF           = 0x2122,
   DIFF_NOT_ALLOWED                 = 0x2123,
   NUM_RDNGS_OVERFLOW               = 0x2124,
   SUM_RDNGS_OVERFLOW               = 0x2125,
   DIFF_MODE_ALREADY_SET            = 0x2126,

   // acquire mode errors
   NOT_IN_ACQUIRE_MODE              = 0x2131,
   WAITING_FOR_TRIGGER              = 0x2132,
   ACQUIRE_NOT_ALLOWED              = 0x2133,
   SYNC_NOT_ALLOWED                 = 0x2134,
   RDGS_PARAM_ERROR                 = 0x2135,
   DLY_PARAM_ERROR                  = 0x2136,
   ACQ_MODE_ALREADY_SET             = 0x2137,

   // sync mode errors
   MODE_NOT_VALID                   = 0x2140,
   DELAY_NOT_VALID                  = 0x2141,
   WAITING_FOR_SYNC_START           = 0x2142,
   SYNC_MODE_RUNNING                = 0x2143,

   // sample/capture mode errors
   SAMPLE_MODE_RUNNING              = 0x2151,

   // Misc Hardware Errors
   COIL_OUT_OF_RANGE                = 0x2102,
   PROBE_FAULT_2107                 = 0x2107,
   PROBE_FAULT_2108                 = 0x2108,
   PROBE_FAULT_2181                 = 0x2181,
   PROBE_FAULT_2182                 = 0x2182,
   PROBE_FAULT_2183                 = 0x2183,
   PROBE_FAULT_2184                 = 0x2184,
   PROBE_FAULT_2185                 = 0x2185,
   PROBE_FAULT_2186                 = 0x2186,
   PROBE_FAULT_2187                 = 0x2187,
   PROBE_FAULT_2188                 = 0x2188,
   PROBE_FAULT_2189                 = 0x2189,
   PROBE_FAULT_218A                 = 0x218A,
   PROBE_FAULT_218B                 = 0x218B,


   // special Linear Encoder errors
   LE_FAULT_21B0                    = 0x21B0,
   LE_FAULT_21B1                    = 0x21B1,
   LE_FAULT_21B2                    = 0x21B2,
   LE_FAULT_21B3                    = 0x21B3,
   LE_FAULT_21B4                    = 0x21B4,
   LE_FAULT_21B5                    = 0x21B5,
   LE_FAULT_21B6                    = 0x21B6,
   LE_FAULT_21B7                    = 0x21B7,
   LE_FAULT_21B8                    = 0x21B8,
   LE_FAULT_21B9                    = 0x21B9,
   LE_FAULT_21BA                    = 0x21BA,
   LE_FAULT_21BB                    = 0x21BB,
   LE_FAULT_21BC                    = 0x21BC,
   LE_FAULT_21BD                    = 0x21BD,
   LE_FAULT_21BE                    = 0x21BE,
   LE_FAULT_21BF                    = 0x21BF,
   LE_FAULT_21C0                    = 0x21C0,
   LE_FAULT_21C1                    = 0x21C1,
   LE_FAULT_21C2                    = 0x21C2,
   LE_FAULT_21C3                    = 0x21C3,
   LE_OVER_SPEED                    = 0x21C4,
   LE_LOW_SIGNAL                    = 0x21C5


};

// User defined data type for storing records of probe address assignments
struct PROBE_ASSIGNMENT
{
   int Assigned;
   char Id[NUMBER_OF_CHARS_IN_PROBE_ID + 1];
};

