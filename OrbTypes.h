//***************************************************************************
// Filename:  OrbTypes.h         Creation Date: 15.01.98       Language: C
// Author:    Kevin Snoad   
// Project:   tOrbit interface software
// Copyright: (c) Solartron Group Limited 1997
//                Solartron Metrology, Steyning Way, Bognor Regis, Sussex, UK. 
//                Tel + 44 (0)1243 825011,  Fax + 44 (0)1243 861244
//***************************************************************************
// Purpose:
// To declare tOrbit interface functions so that they can be called from an 
// application program.
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

/* Comms tOrbit Interface Routines */

typedef int (WINAPI * tOrbitRst)(int network);

typedef int (WINAPI * tOrbitNotify)(int network,
                                    char id[]);

typedef int (WINAPI *tOrbitSetaddr)(int network,
                                    int oaddr,
                                    char id[],
                                    int *opt);

typedef int (WINAPI *tOrbitClr)(int network,
                                int oaddr);

typedef int (WINAPI *tOrbitIdentify)(int network,
                                     int oaddr,
                                     char id[],
                                     char devtype[],
                                     char ver[],
                                     int *stroke);

typedef int (WINAPI *tOrbitGetinfo)(int network,
                                    int oaddr,
                                    char moduletype[],
                                    int *hwtype,
                                    int *reso,
                                    char moduleinfo[]);

typedef int (WINAPI *tOrbitGetstatus)(int network,
                                      int oaddr,
                                      int *errcode,
                                      int *status);

typedef int (WINAPI *tOrbitRead1)(int network,
                                  int oaddr,
                                  int *rd);

typedef int (WINAPI *tOrbitRead2)(int network,
                                  int oaddr,
                                  long *rdlong);

typedef int (WINAPI *tOrbitAcquire)(int network,
                                    int oaddr,
                                    int *rdgs,
                                    int *dly);

typedef int (WINAPI *tOrbitTrigger)(int network);

typedef int (WINAPI *tOrbitReadia)(int network,
                                   int oaddr,
                                   int rdarray[]);

typedef int (WINAPI *tOrbitDifference)(int network,
                                       int oaddr);

typedef int (WINAPI *tOrbitStartdiff)(int network);

typedef int (WINAPI *tOrbitStopdiff)(int network);

typedef int (WINAPI *tOrbitReaddiff1)(int network,
                                      int oaddr,
                                      int *min,
                                      int *max,
                                      double *sum,
                                      long *num);

typedef int (WINAPI *tOrbitReaddiff2)(int network,
                                      int oaddr,
                                      long *minlong,
                                      long *maxlong);

typedef int (WINAPI *tOrbitPreset)(int network,
                                   int oaddr,
                                   long *pst);

typedef int (WINAPI *tOrbitRefmark)(int network,
                                    int oaddr);

typedef int (WINAPI *tOrbitDirection)(int network,
                                      int oaddr);

typedef int (WINAPI *tOrbitControl) (int network,
                                    int *action);

typedef int (WINAPI *tOrbitSetmode) (int network,
                                    int oaddr,
                                    int *mode,
                                    int *dly);
typedef int (WINAPI *tOrbitReadbuffer1) (int network,
                                        int oaddr,
                                        int *NumReadings1,
                                        int ReadingBuffer1[]);


/* "Non 485 comms" tOrbit Interface Routines */

typedef int (WINAPI *tConnectToOrbitNetworks)(int* NumberOfOrbitNetworks);

typedef int (WINAPI *tDisconnectFromOrbitNetworks)(void);

typedef int (WINAPI *tResetNetworkController)(int NetworkNumber);

typedef int (WINAPI *tGetOrbitNetworkNameAndType)(int NetworkNumber,
                                                  char* NetworkName,
                                                  int* NetworkType);

typedef int (WINAPI *tReportOrbitProbeAssignment)(int NetworkNumber,
             struct PROBE_ASSIGNMENT* ReportAssignment);

typedef int (WINAPI *tReportOrbitInterfaceVersion)(int* RevisionNumbers,
             char* VersionStr);

typedef int (WINAPI *tReportOrbitError)(int* ErrorCode,
             char* ErrorStr);


