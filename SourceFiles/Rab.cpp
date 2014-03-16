/*
 * Rab.cpp
 *
 *  Created on: 17 okt 2012
 *      Author: RAQ
 */

#include "Rab.h"


Rab::Rab(int id, string name, RabInfo::rabType type, RabInfo::ulRate ul, RabInfo::dlRate dl):_id(id), _name(name),_type(type), _ul(ul), _dl(dl){

}
Rab::~Rab() {
	// TODO Auto-generated destructor stub
}

int Rab::getId(){
	return _id;
}

string Rab::getName(){
	return _name;
}


RabInfo::rabType Rab::getType(){
	return _type;
}

RabInfo::ulRate Rab::getUl(){
	return _ul;
}

RabInfo::dlRate Rab::getDl(){
	return _dl;
}

void Rab::trace(){
	cout<<"Rab ID: "<< _id<<endl;
	TRACE("Rab Name: " + _name);
}
