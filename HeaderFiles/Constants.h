
#ifndef CONST_H_
#define CONST_H_
#define TRACING 1


static const int MAXPSRAB = 3;
static const int MAXCSRAB = 1;

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#define TRACE_ENTER(msg) if(TRACING == 1) cout<<"--------ENTER: "<<__FUNCTION__<<": "<<msg<<" --------"<<endl;
#define TRACE_ERROR(msg) if(TRACING == 1) cout<<__FUNCTION__<<"("<<__LINE__<< ")"<<" ERROR: "<<msg<<endl;
#define TRACE(msg) if(TRACING == 1) cout<<msg<<endl;

class TriggerType {
	public:
	enum type {
		UNKNOWN,
		RAB_EST,
		RAB_REL,
		CH_SWITCH
	};
};

class RabInfo {
public:

	enum rabType {
		UNKNOWN_RAB,
		CS_CONV,
		PS_INT,
		PS_STRM

	};

	enum ulRate {
		UL_UNKNOW = 700,
		UL_URA = 600,
		UL_RACH = 400,
		UL_12_2 = 12,
		UL_0 = 0,
		UL_8 = 8,
		UL_16 = 16,
		UL_64 = 64,
		UL_128 = 128,
		UL_384 = 384,
		UL_EUL = 500
	};

	enum dlRate {
		DL_UNKNOW = 700,
		DL_URA = 600,
		DL_FACH = 401,
		DL_12_4 = 12,
		DL_0 = 0,
		DL_8 = 8,
		DL_16 = 16,
		DL_64 = 64,
		DL_128 = 128,
		DL_384 = 384,
		DL_HS = 501
	};
};

class UeRc {
	public:
	enum Id{
		UERC_0,
		UERC_1,
		UERC_2,
		UERC_3,
		UERC_4,
		UERC_5,
		UERC_6,
		UERC_7,
		UERC_8,
		UERC_9,
		UERC_10,
		UERC_11,
		UERC_12,
		UERC_13,
		UERC_14,
		UERC_15,
		UERC_16,
		UERC_17,
		UERC_18,
		UERC_19,
		UERC_20,
		UERC_21,
		UERC_22,
		UERC_23,
		UERC_24,
		UERC_25,
		UERC_26,
		UERC_27,
		UERC_28,
		UERC_29,
		UERC_30,
		UERC_31,
		UERC_32,
		UERC_33,
		UERC_34,
		UERC_35,
		UERC_36,
		UERC_37,
		UERC_38,
		UERC_39,
		UERC_40,
		UERC_41,
		UERC_42,
		UERC_43,
		UERC_44,
		UERC_45,
		UERC_46,
		UERC_47,
		UERC_48,
		UERC_49,
		UERC_50,
		UERC_51,
		UERC_52,
		UERC_53,
		UERC_54,
		UERC_55,
		UERC_56,
		UERC_57,
		UERC_58,
		UERC_59,
		UERC_60,
		UERC_61,
		UERC_62,
		UERC_63,
		UERC_64,
		UERC_65,
		UERC_66,
		UERC_67,
		UERC_68,
		UERC_69,
		UERC_71 = 71,
		UERC_72,
		UERC_73,
		UERC_74,
		UERC_75,
		UERC_76,
		UERC_77,
		UERC_78,
		UERC_79,
		UERC_80,
		UERC_94 = 94,
		UERC_95,
		UERC_113 = 113,
		UERC_123 = 123,
		UERC_124,
		UERC_125,
		UERC_126,
		UERC_127,
		UERC_128,
		UERC_176 = 176,
		UERC_UNKNOWN = 300

	};

};

#endif /* CONST_H_ */
