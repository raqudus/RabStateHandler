/*
 * main.cpp
 *
 *  Created on: 18 okt 2012
 *      Author: RAQ
 */

#include <stdio.h>
#include <Common.h>
#include "UeRcHandler.h"

using namespace std;
int main()
{
	//string input;
	//DEBUG_TRACE("nothing");

	TRACE("State Explosion Simulator");
	//int input;
	//cin>>input;
	//getline(cin,input);
	//RabInfo::ulRate _ul;
	//RabInfo::dlRate _dl;

	//getRabRatesFromString(input,_ul,_dl);
	//cout<<_ul<<endl<<_dl<<endl;
	//cout<<UeRc::UERC_80<<endl;
/*
	Rab *r = Common::createRabFromString(input);

	cout<<"main : "<<r->getId()<<endl;
	cout<<"main : "<<r->getName()<<endl;
	cout<<"main : "<<r->getType()<<endl;
	cout<<"main : "<<r->getUl() <<"/"<<r->getDl()<<endl;

	delete r;
*/

	UeRcHandler &ueRcH = UeRcHandler::getInstance();

	//ueRcH.execute("C:\\Users\\RAQ\\SkyDrive\\Documents\\Thesis\\Code\\RabStateHandler\\transition_table.txt");
	ueRcH.setState(UeRc::UERC_26);
	TRACE("----------------");
	ueRcH.trace();
	ueRcH.execute("transition_table.txt");
	//TRACE(ueRcH.checkState());
	//delete ueRcH;

	//Common::createUeRcState((UeRc::Id)input);


	return 0;
}

