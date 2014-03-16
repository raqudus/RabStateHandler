/*
 * Rab.h
 *
 *  Created on: 17 okt 2012
 *      Author: RAQ
 */

#ifndef RAB_H_
#define RAB_H_

#include "Constants.h"
#include <string>

using namespace std;
class Rab {
public:

	Rab(int id, string name,RabInfo::rabType type, RabInfo::ulRate ul, RabInfo::dlRate dl);
	virtual ~Rab();

	int getId();
	string getName();
	RabInfo::rabType getType();
	RabInfo::ulRate getUl();
	RabInfo::dlRate getDl();
	void trace();

public:

	Rab();
	int _id;
	string _name; //for testing purpose
	RabInfo::rabType _type;
	RabInfo::ulRate _ul;
	RabInfo::dlRate _dl;



};

#endif /* RAB_H_ */
