#ifndef REMOTETYPES_H
#define REMOTETYPES_H

#define NUM_DISP_CHANS ( 14 )

typedef vector<unsigned char> TMsgData;

typedef queue<TMsgData> TMsgDataQueue;

typedef vector<unsigned char> TMsgBody;

typedef vector<TThread *> ThreadArray;

typedef vector<int> TIntArr;

typedef enum { eSimIdle=0x01, eSimLocal=0x02, eSimScen=0x03 } eRciSimMode;

typedef enum { eIntGpib=0, eIntSerial=1, eIntEthernet=2 } eIntType;

#endif
 