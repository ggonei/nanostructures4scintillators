//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	Talk to gunny
//
#ifndef PrimaryGeneratorMessenger_h
#define PrimaryGeneratorMessenger_h 1

//	Geant libraries
#include <G4SystemOfUnits.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIdirectory.hh>
#include <G4UImessenger.hh>
#include <globals.hh>

//	My libraries
#include "PrimaryGeneratorAction.hh"


class PrimaryGeneratorAction;
//class G4UIdirectory;
//class G4UIcmdWithADoubleAndUnit;
class PrimaryGeneratorMessenger: public G4UImessenger{

public:
	PrimaryGeneratorMessenger( PrimaryGeneratorAction* );	//	default constructor
	virtual ~PrimaryGeneratorMessenger();	//	default destructor

	virtual void SetNewValue( G4UIcommand *, G4String );	//	command communicator

private:
	PrimaryGeneratorAction *fPrimaryAction;	//	user action
	G4UIdirectory *fGunDir;	//	gun command prefix
	G4UIcommand *fPolarCmd;	//	polarisation updater

};	//	end PrimaryGeneratorMessenger
#endif
