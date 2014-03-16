/*
 * UeRcState.cpp
 *
 *  Created on: 15 okt 2012
 *      Author: RAQ
 */

#include "UeRcState.h"

UeRcState::UeRcState(): _ueRcId(UeRc::UERC_0), _noPsRab(0),_noCsRab(0) {
	_csRab=NULL;
	for(int i=0;i<MAXPSRAB;++i){
		_psRab[i]=NULL;
	}
}

UeRcState::~UeRcState() {
	deleteAllRabs();

}

UeRc::Id UeRcState::getId(){
	return _ueRcId;
}

void UeRcState::setId(UeRc::Id newId){
	_ueRcId = newId;
}

bool UeRcState::addRab(Rab* rab){

	if((_noPsRab + _noCsRab) < (MAXPSRAB + MAXCSRAB))
	{
		if(rab->_type == RabInfo::CS_CONV && _noCsRab < MAXCSRAB)
		{
			_csRab=rab;
			++_noCsRab;
			return true;
		}
		else if (rab->_type == RabInfo::PS_INT && _noPsRab < MAXPSRAB)
		{
			_psRab[_noPsRab]=rab;
			++_noPsRab;
			return true;
		}

	}
	return false;
}
bool UeRcState::deleteRab(Rab *rabToDelete){
	if(rabToDelete == NULL){
		return false;
	}

	if(_csRab != NULL && rabToDelete->_id == _csRab->_id){
		delete _csRab;
		_csRab = NULL;
		--_noCsRab;
		return true;
	}

	for(int i=0; i<_noPsRab;i++){
		if(_psRab[i] != NULL && rabToDelete->_id == _psRab[i]->_id){
			delete _psRab[i];
			_psRab[i] = NULL;
			--_noPsRab;
			return true;
		}
	}
	return false;

}

void UeRcState::deletePsRabs() {

	for(int i=0;i<_noPsRab;++i){
		if(_psRab[i]!=NULL){
			delete _psRab[i];
			_psRab[i]=NULL;

		}
		_noPsRab = 0;
	}
}

void UeRcState::deleteCsRab() {
	if(_csRab != NULL){
		delete _csRab;
		_csRab = NULL;
		_noCsRab = 0;
	}

}

void UeRcState::deleteAllRabs(){

	deletePsRabs();
	deleteCsRab();
	setId(UeRc::UERC_0);
}

Rab* UeRcState::getCsRab(){
	return _csRab;

}
Rab* UeRcState::getPsRab(int id){

	for(int i=0; i<_noPsRab;i++){
		if(_psRab[i]->_id == id){
			return _psRab[i];
		}
	}
	return NULL;

}

Rab** UeRcState::getPsRabs(){
	return _psRab;
}

int UeRcState::getNoOfRabs() {
	return _noPsRab + _noCsRab;
}

int UeRcState::getNoOfPsRabs(){
	return _noPsRab;
}

int UeRcState::getNoOfCsRabs(){
	return _noCsRab;
}

bool UeRcState::hasCsRab() {
	if(_noCsRab!=0){
		return true;
	}
	return false;
}

bool UeRcState::hasCsRab(int id){
	if(_noCsRab!=0){
		return _csRab->_id == id;
	}
	return false;
}
bool UeRcState::hasPsRab(int id){
	for(int i=0;i<_noPsRab;++i){
		if((_psRab[i]!=NULL) && (_psRab[i]->_id == id)){
			return true;
		}
	}
	return false;
}
void UeRcState::trace(){
	cout<<"UeRc: "<<_ueRcId<<endl;
	if (_csRab != NULL){
		_csRab->trace();
	}

	for(int i=0;i<_noPsRab;++i){
		if(_psRab[i]!=NULL){
			_psRab[i]->trace();
		}
	}
}


