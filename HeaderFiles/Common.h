#ifndef COMMON_H_
#define COMMON_H_



#include "Constants.h"
#include "UeRcState.h"
#include "Rab.h"
#include <fstream>

using namespace std;
class Common{

public:

	static UeRc::Id getUeRcFromString(string ueRcStr){

		int pos = ueRcStr.find(":");
		string ueRcNumPart = ueRcStr.substr(pos+1);
		//cout<<ueRcNumPart<<endl;
		stringstream ss(ueRcNumPart);
		int ueRcNum;
		ss >> ueRcNum;
		return (UeRc::Id)ueRcNum;

	}

	static void getRabRatesFromString(string rab_data, RabInfo::ulRate &ul_rate, RabInfo::dlRate &dl_rate)
	{

		ul_rate = RabInfo::UL_UNKNOW;
		dl_rate = RabInfo::DL_UNKNOW;
		int posStart = 0, posEnd = 0, posSlash = 0;
		posStart = rab_data.find("(");
		posEnd = rab_data.find(")");
		posSlash = rab_data.find("/");
		string ulRateStr = rab_data.substr(posStart+1,posSlash-posStart-1);
		string dlRateStr = rab_data.substr(posSlash+1,posEnd-posSlash-1);
		//cout<<ulRateStr<<endl<<dlRateStr<<endl;
		if(ulRateStr.compare("RACH") == 0 || dlRateStr.compare("FACH") == 0){

			ul_rate = RabInfo::UL_RACH;
			dl_rate = RabInfo::DL_FACH;
			return;
		}
		if(ulRateStr.compare("EUL") == 0){
			ul_rate = RabInfo::UL_EUL;
			dl_rate = RabInfo::DL_HS;
			return;
		}

		if(dlRateStr.compare("HS") == 0){

			dl_rate = RabInfo::DL_HS;
		}
		else{
			stringstream dlSs(dlRateStr);
			int dlRateInt = -1;
			dlSs >> dlRateInt;
			dl_rate = (RabInfo::dlRate) dlRateInt;
		}

		stringstream ulSs(ulRateStr);
		int ulRateInt = -1;
		ulSs >> ulRateInt;
		ul_rate = (RabInfo::ulRate) ulRateInt;

	}

	static RabInfo::rabType getRabTypeFromString(string rab_data){

		int pos = rab_data.find("(");
		string rabStr = rab_data.substr(0,pos-1);
		//cout<< "rabStr is "<<rabStr<<endl;


		if(rabStr.compare("Conversational CS Speech") == 0 || rabStr.compare("CONV_CS_SPEECH") == 0){
			return RabInfo::CS_CONV;
		}
		if(rabStr.compare("Interactive PS") == 0 || rabStr.compare("INT_PS") == 0){
			return RabInfo::PS_INT;
		}
		if(rabStr.compare("Streaming PS") == 0 || rabStr.compare("STR_PS") == 0){
			return RabInfo::PS_STRM;
		}

		return RabInfo::UNKNOWN_RAB;
	}


	static TriggerType::type getTriggerTypeFromString(string trigger){

		//cout<<trigger<<endl;
		if (trigger.compare("Establish") == 0) {
			return TriggerType::RAB_EST;
		}
		else if (trigger.compare("Release") == 0) {
			return TriggerType::RAB_REL;
		}
		else if(trigger.compare("Channel switch") == 0){
			return TriggerType::CH_SWITCH;
		}

		return TriggerType::UNKNOWN;
	}


	static int generateRabIdFromString(string rabData){
		int id = 0;
		string name = rabData;

		RabInfo::rabType type = getRabTypeFromString(rabData);

		RabInfo::ulRate ul;
		RabInfo::dlRate dl;
		getRabRatesFromString(rabData,ul,dl);

		id = type+ul+dl;
		return id;
	}

	static Rab* createRabFromString(string rabData){

		int id = 0;
		string name = rabData;

		RabInfo::rabType type = getRabTypeFromString(rabData);

		RabInfo::ulRate ul;
		RabInfo::dlRate dl;
		getRabRatesFromString(rabData,ul,dl);

		id = type+ul+dl;
		Rab *rab = new Rab(id, name, type, ul, dl);
		return rab;
	}


	static bool createUeRcState(UeRc::Id target_uerc, UeRcState &state){
		if(target_uerc == UeRc::UERC_0)
		{
			state.deleteAllRabs();
		}
		string inputFileName = "uerc_ref.txt";
		ifstream inputfile(inputFileName.c_str());

		bool uercFound = false;

		if (inputfile.is_open()) {
			string line;
			while (getline(inputfile, line)) {
				//TRACE(line);
				string uerc_str;
				int pos = line.find('#');
				uerc_str = line.substr(0, pos - 1);
				UeRc::Id uerc_id =getUeRcFromString(uerc_str);
				if(uerc_id != target_uerc){
					continue;
				}

				string rab[4];
				int rabCount = 0;
				line.erase(0, pos + 2);
				line.erase(line.find(']'),line.length());
				int posPlus = line.find('+');
				while(posPlus != -1){
					rab[rabCount] = line.substr(0,posPlus-1);
					cout<<rab[rabCount]<<" | id: "<<generateRabIdFromString(rab[rabCount])<<endl;
					rabCount++;
					line.erase(0, posPlus + 2);
					posPlus = line.find('+');
				}

				rab[rabCount] = line;
				cout<<rab[rabCount]<<" | id: "<<generateRabIdFromString(rab[rabCount])<<endl;
				rabCount++;
				cout<<uerc_str<<" : #Rabs = "<<rabCount<<endl;
				uercFound = true;
				for(int i=0;i<rabCount;++i){
					Rab *r = createRabFromString(rab[i]);
					//r->trace();
					if(!state.addRab(r)){
						TRACE("Too many Rabs");
					}
				}

				break;
			}
			inputfile.close();
		}
		return uercFound;
	}

	static UeRc::Id checkUeRcState(UeRcState &state){
		if(state.getNoOfRabs() == 0){
			TRACE("UeRc:0 : #Rabs = 0");
			return UeRc::UERC_0;
		}
		string inputFileName = "uerc_ref.txt";
		ifstream inputfile(inputFileName.c_str());
		UeRc::Id uercid = UeRc::UERC_UNKNOWN;
		if (inputfile.is_open()) {
			string line;
			while (getline(inputfile, line)) {
				TRACE(line);
				string uerc_str;
				string rab[4];
				bool hasCsRab = false;
				int rabCount = 0;
				int pos = line.find('#');
				uerc_str = line.substr(0, pos - 1);
				line.erase(0, pos + 2);
				line.erase(line.find(']'),line.length());
				int posPlus = line.find('+');
				while(posPlus != -1){
					rab[rabCount] = line.substr(0,posPlus-1);
					cout<<rab[rabCount]<<" | id: "<<generateRabIdFromString(rab[rabCount])<<endl;
					rabCount++;
					line.erase(0, posPlus + 2);
					posPlus = line.find('+');
				}

				rab[rabCount] = line;
				cout<<rab[rabCount]<<" | id: "<<generateRabIdFromString(rab[rabCount])<<endl;
				rabCount++;
				cout<<uerc_str<<" : #Rabs = "<<rabCount<<endl;
				hasCsRab = rab[0].find("CS") != -1;

				if((!state.hasCsRab() && hasCsRab) || (state.hasCsRab() && !hasCsRab)){
					continue;
				}
				int i = 0;
				//Check the CS Rab
				if(state.getNoOfRabs()!=rabCount){
					//TRACE("No Rabs Not Equal");
					continue;
				}
				if(state.hasCsRab() && hasCsRab){

					if(generateRabIdFromString(rab[0]) != (state.getCsRab()->getId())){
						continue;
					}
					else{
						//TRACE("CS Rab Matched");
						++i;
					}
				}


				//Check the PS Rabs
				Rab** psRab = state.getPsRabs();
				int psRabCount = state.getNoOfPsRabs();
				bool * match = new bool[psRabCount]{false};

				for(; i < rabCount; ++i){
					for (int j = 0; j < psRabCount; ++j){
						//cout<<"currnet Rab is: "<< rab[i]<<endl;
						if(!match[j] && psRab[j]->_id == generateRabIdFromString(rab[i])){
							//TRACE("Matched PS Rab");
							match[j] = true;
						}
					}

				}
				int k;
				for(k=0; k<psRabCount; ++k){
					if(!match[k]){
						break;
					}
				}


				if(k == psRabCount){
					 uercid = getUeRcFromString(uerc_str);
					 break;
				}
				delete[] match;
			}
			inputfile.close();

		}
		return uercid;
	}

};

#endif /* COMMON_H_ */


