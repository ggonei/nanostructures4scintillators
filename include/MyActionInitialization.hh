//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	!This class defines the mandatory extension of G4VUserActionInitialization and must be used!
//
//	It is what controls our simulation actually doing things
//
#ifndef MyActionInitialization_h
#define MyActionInitialization_h 1

//	Geant libraries
#include <G4VUserActionInitialization.hh>

//	My libraries
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"
#include "TrackingAction.hh"

class MyActionInitialization: public G4VUserActionInitialization{

public:
	MyActionInitialization();	//	default constructor
	virtual ~MyActionInitialization();	//	destructor definition

	virtual void BuildForMaster() const;	//	make sure correct function is called to build simple action
	virtual void Build() const;	//	make sure correct function is called to build a fancier action

};	//	end MyActionInitialization{}
#endif