//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	This governs start and end of run actions
//
#ifndef RunAction_h
#define RunAction_h 1

//	Geant libraries
#include <globals.hh>
#include <G4UserRunAction.hh>
#include <G4Timer.hh>
#include <G4Run.hh>

//	My libraries
#include "HistoManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "Run.hh"

//class G4Timer;
//class Run;
//class HistoManager;
//class PrimaryGeneratorAction;

class RunAction: public G4UserRunAction{

public:
	RunAction( PrimaryGeneratorAction* = nullptr );	//	default constructor
	virtual ~RunAction();	//	default destructor

	virtual G4Run *GenerateRun();	//	formation of run
	virtual void BeginOfRunAction( const G4Run * );	//	actions at start of run
	virtual void EndOfRunAction( const G4Run * );	//	actions at end of run


private:
	G4Timer *fTimer;	//	clock
	Run *fRun;	//	actual run
	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();	//	analysis and initialisation
	HistoManager *fHistoManager;	//	histogrammer
	PrimaryGeneratorAction *fPrimary;	//	particle maker

};	//	end RunAction{}
#endif