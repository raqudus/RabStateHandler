/*
 * Trigger.cpp
 *
 *  Created on: 15 okt 2012
 *      Author: RAQ
 */

#include "Trigger.h"

Trigger::Trigger(TriggerType::type trigger, RabInfo::rabType rabType, RabInfo::ulRate ul, RabInfo::dlRate dl, string rabName):
		_trigger(trigger), _rabType(rabType), _ul(ul), _dl(dl), _rabName(rabName){
	// TODO Auto-generated constructor stub


}

TriggerType::type Trigger::getTriggerType() {
	return _trigger;
}

RabInfo::rabType Trigger::getRabType() {
	return _rabType;
}

RabInfo::ulRate Trigger::getUl() {
	return _ul;
}

RabInfo::dlRate Trigger::getDl() {
	return _dl;
}

string Trigger::getRabName(){
	return _rabName;
}


Trigger::~Trigger() {
	// TODO Auto-generated destructor stub
}

