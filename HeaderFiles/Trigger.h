/*
 * Trigger.h
 *
 *  Created on: 15 okt 2012
 *      Author: RAQ
 */

#ifndef TRIGGER_H_
#define TRIGGER_H_

#include "Constants.h"

class Trigger {
public:


	Trigger(TriggerType::type trigger, RabInfo::rabType rabType, RabInfo::ulRate ul, RabInfo::dlRate dl, string rabName);
	TriggerType::type getTriggerType();
	RabInfo::rabType getRabType();
	RabInfo::ulRate getUl();
	RabInfo::dlRate getDl();
	string getRabName();

	virtual ~Trigger();

private:
	Trigger();
	TriggerType::type _trigger;
	RabInfo::rabType _rabType;
	RabInfo::ulRate _ul;
	RabInfo::dlRate _dl;
	string _rabName;

};

#endif /* TRIGGER_H_ */
