/*
 * UeRcHandler.h
 *
 *  Created on: 15 okt 2012
 *      Author: RAQ
 */


#ifndef UERCHANDLER_H_
#define UERCHANDLER_H_

//#include "Constants.h"
#include "Common.h"
#include "Trigger.h"
#include "UeRcState.h"



using namespace std;
class UeRcHandler {
public:

	virtual ~UeRcHandler();
	static UeRcHandler& getInstance();
	UeRcState& getUeRcState();

	bool doTransition(Trigger &trigger, UeRc::Id src_id, UeRc::Id dest_id);
	UeRc::Id handleRabEst(UeRc::Id src_id, UeRc::Id dest_id, Rab* rab);
	UeRc::Id handleRabRel(UeRc::Id src_id, UeRc::Id dest_id, Rab* rab);
	UeRc::Id handleChSwitch(UeRc::Id src_id, UeRc::Id dest_id, Rab* rab);
	bool setState(UeRc::Id uerc);
	UeRc::Id checkState();
	void trace();
	bool execute(string inputFile);


private:
	UeRcHandler();
	UeRcHandler(const UeRcHandler&);
	UeRcHandler& operator=(const UeRcHandler&);

	UeRcState currentState;
	static UeRcHandler instance;


};

#endif /* UERCHANDLER_H_ */
