//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	Each time the particle does something then this file fills histograms and other assorted info
//
#ifndef SteppingAction_h
#define SteppingAction_h 1
#define VERBOSE 1

//	Geant libraries
#include <G4Event.hh>
#include <G4EventManager.hh>
#include <G4OpBoundaryProcess.hh>
#include <G4OpticalPhoton.hh>
#include <G4ProcessManager.hh>
#include <G4RunManager.hh>
#include <G4Scintillation.hh>
#include <G4Step.hh>
#include <G4SteppingManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Track.hh>
#include <G4UserSteppingAction.hh>
#include <globals.hh>

//	My libraries
#include "HistoManager.hh"
#include "Run.hh"
#include "TrackInformation.hh"


class SteppingAction: public G4UserSteppingAction{

public:
	SteppingAction(){};	//	default constructor does nothing
	~SteppingAction(){};	//	nothing to clean up

	virtual void UserSteppingAction( const G4Step * );	//	create action executed every step

private:

};	//	end SteppingAction{}
#endif