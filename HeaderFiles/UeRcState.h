/*
 * UeRcState.h
 *
 *  Created on: 15 okt 2012
 *      Author: RAQ
 */


#ifndef UERCSTATE_H_
#define UERCSTATE_H_

#include "Trigger.h"
#include "Rab.h"
#include "Constants.h"

class UeRcState {
public:


	virtual ~UeRcState();
	UeRcState();
	UeRc::Id getId();
	void setId(UeRc::Id);
	bool addRab(Rab*);
	bool deleteRab(Rab*);
	void deleteAllRabs();
	void deletePsRabs();
	void deleteCsRab();
	Rab* getCsRab();
	Rab* getPsRab(int);
	Rab** getPsRabs();
	int getNoOfRabs();
	int getNoOfPsRabs();
	int getNoOfCsRabs();
	bool hasCsRab();
	bool hasCsRab(int id);
	bool hasPsRab(int id);
	void trace();



private:

	UeRc::Id _ueRcId;
	int _noPsRab;
	int _noCsRab;
	Rab *_csRab;
	Rab *_psRab[MAXPSRAB];

};

#endif /* UERCSTATE_H_ */





