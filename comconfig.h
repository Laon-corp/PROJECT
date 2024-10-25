#ifndef		COMCONFIG_H
#define		COMCONFIG_H

/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/* Copyright (c) National Instruments 2002. All Rights Reserved.          */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  COMCONFIG                       1
#define  COMCONFIG_COMPORT               2
#define  COMCONFIG_CTSMODE               3
#define  COMCONFIG_XMODE                 4
#define  COMCONFIG_BAUDRATE              5
#define  COMCONFIG_PARITY                6
#define  COMCONFIG_DATABITS              7
#define  COMCONFIG_STOPBITS              8
#define  COMCONFIG_INPUTQ                9       /* callback function: InputQ */
#define  COMCONFIG_OUTPUTQ               10
#define  COMCONFIG_TIMEOUT               11
#define  COMCONFIG_CLOSE                 12
#define  COMCONFIG_TIMEOUT_MSG1          13


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK InputQ(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
#endif
