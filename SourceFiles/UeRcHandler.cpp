/*
 * UeRcHandler.cpp
 *
 *  Created on: 15 okt 2012
 *      Author: RAQ
 */

#include "UeRcHandler.h"

UeRcHandler UeRcHandler::instance;

bool UeRcHandler::setState(UeRc::Id uerc) {
	TRACE_ENTER("");

	return Common::createUeRcState(uerc, currentState);
}

UeRc::Id UeRcHandler::checkState(){
	TRACE_ENTER("");
	return Common::checkUeRcState(currentState);
}

void UeRcHandler::trace(){
	currentState.trace();
}

UeRcHandler::UeRcHandler() {
	//currentState = new UeRcState();
}

UeRcState& UeRcHandler::getUeRcState(){
	return currentState;
}

UeRcHandler& UeRcHandler::getInstance() {
	//if(instance == NULL)
	//	instance = new UeRcHandler();
	return instance;
}

UeRcHandler::~UeRcHandler() {
//	delete currentState;
//	currentState = NULL;
//	delete instance;
//	instance = NULL;
}

bool UeRcHandler::doTransition(Trigger &trigger, UeRc::Id src_id, UeRc::Id dest_id) {
	//TODO: Fix Implementation with UeRcs Future updates
	TRACE_ENTER("");

	UeRc::Id resultUeRc = UeRc::UERC_UNKNOWN;
	TriggerType::type trigType = (TriggerType::type) trigger.getTriggerType();

	Rab *rab = NULL;

	if(currentState.getId() != src_id){
		TRACE("setting up source id");
		currentState.deleteAllRabs();
		setState(src_id);
	}

	switch (trigType) {
	case TriggerType::RAB_EST:
		rab = Common::createRabFromString(trigger.getRabName());
		resultUeRc = handleRabEst(src_id, dest_id, rab);

		break;
	case TriggerType::RAB_REL:
		rab = Common::createRabFromString(trigger.getRabName());
		resultUeRc = handleRabRel(src_id, dest_id, rab);
		break;
	case TriggerType::CH_SWITCH:
		rab = Common::createRabFromString(trigger.getRabName());
		resultUeRc = handleChSwitch(src_id, dest_id, rab);
		break;
	case TriggerType::UNKNOWN:
		TRACE_ERROR("Invalid Trigger type");
		resultUeRc = UeRc::UERC_UNKNOWN;
		break;
	}

	if(resultUeRc == dest_id){
		TRACE("Transition successful!");
		return true;
	}
	TRACE_ERROR("Transition unsuccessful!");
	return false;
}

UeRc::Id UeRcHandler::handleRabEst(UeRc::Id src_id, UeRc::Id dest_id, Rab* rab){
	// TODO: Write implementation
	TRACE_ENTER("");
	currentState.addRab(rab);
	currentState.setId(checkState());
	return currentState.getId();
//	return UeRc::UERC_UNKNOWN;
}
UeRc::Id UeRcHandler::handleRabRel(UeRc::Id src_id, UeRc::Id dest_id, Rab* rab){
	// TODO: Write implementation
	TRACE_ENTER("");
	if(!currentState.deleteRab(rab))
		TRACE_ERROR("Unable to delete rab");
	delete rab;
	currentState.setId(checkState());
	return currentState.getId();
	//return UeRc::UERC_UNKNOWN;
}
UeRc::Id UeRcHandler::handleChSwitch(UeRc::Id src_id, UeRc::Id dest_id, Rab* rab){
	// TODO: Write implementation
	TRACE_ENTER("");
	int noPsRab = currentState.getNoOfPsRabs();
	currentState.deletePsRabs();
	currentState.addRab(rab);
	currentState.setId(checkState());
	return currentState.getId();
	//return UeRc::UERC_UNKNOWN;
}

bool UeRcHandler::execute(string inputFileName = "transition_table.txt") {
	TRACE_ENTER("");
	ifstream inputfile(inputFileName.c_str());


	if (inputfile.is_open()) {
		string line;
		while (getline(inputfile, line)) {
			cout<<line<<endl;

			string srcConnType;
			string destConnType;
			string actionTrigger;
			string rabData;

			int i = 0;
			while (i < 4) {
				int pos = line.find(";");
				string lineFragment = line.substr(0, pos);

				switch (i) {
				case 0:
					srcConnType = lineFragment;

					break;
				case 1:
					destConnType = lineFragment;
					break;
				case 2:
					actionTrigger = lineFragment;

					break;
				case 3:
					rabData = lineFragment;
					break;
				default:
					break;
				}

				line.erase(0, pos + 1);
				i++;
			}

			TRACE("Input Data: " + srcConnType + " -> " + destConnType + " | " + actionTrigger + ": " + rabData);
			//cout<<"Input Data: "<<srcConnType<<" -> "<<destConnType<<" | "<<actionTrigger<<": "<<rabData<<endl;

			RabInfo::ulRate ul;
			RabInfo::dlRate dl;
			RabInfo::rabType rabType;
			UeRc::Id srcUeRc;
			UeRc::Id destUeRc;
			TriggerType::type trigType;

			Common::getRabRatesFromString(rabData,ul,dl);
			rabType = Common::getRabTypeFromString(rabData);
			srcUeRc = Common::getUeRcFromString(srcConnType);
			destUeRc = Common::getUeRcFromString(destConnType);
			trigType = Common::getTriggerTypeFromString(actionTrigger);
			//TRACE("Converted Data:" + srcUeRc + " " + destUeRc + " " + trigType + " " + rabType + " " + ul + "/" + dl);
			cout<<"Converted Data:"<<srcUeRc<<" "<<destUeRc<<" "<<trigType<<" "<<rabType<<" "<<ul<<"/"<<dl<<endl;

			Trigger newTrigger(trigType, rabType, ul, dl, rabData);

			bool result = doTransition(newTrigger, srcUeRc, destUeRc);

			if(!result){
				TRACE_ERROR("Input Data: " + srcConnType + " -> " + destConnType + " | " + actionTrigger + ": " + rabData);
			}

		}
		inputfile.close();
		return true;
	}
	cerr << "Unable to open file!";
	return false;
}
