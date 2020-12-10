//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	This defines histograms we are filling
//
#ifndef HistoManager_h
#define HistoManager_h 1
#define VERBOSE 1

#include <g4root.hh>	//	change this for different types of files
#include <G4UnitsTable.hh>
#include <globals.hh>


class HistoManager{

public:
	HistoManager(): fFileName( "n4s_histos" ){
		Book();
	};	//	default constructor
	~HistoManager(){
		delete G4AnalysisManager::Instance();
	};	//	default destructor

private:
	void Book();	//	histogram collection
	G4String fFileName;	//	root file name

};	//	end HistoManager
#endif