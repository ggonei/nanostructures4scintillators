//
//	George O'Neill, University of York 2020
//
#include "PrimaryGeneratorMessenger.hh"


PrimaryGeneratorMessenger::PrimaryGeneratorMessenger( PrimaryGeneratorAction *Gun ): G4UImessenger(), fPrimaryAction( Gun ){

	fGunDir = new G4UIdirectory( "/n4s/gun/" );	//	set gun prefix
	fGunDir->SetGuidance( "PrimaryGenerator control" );	//	inform user
	fPolarCmd = new G4UIcommand( "/n4s/gun/optPhotonPolar", this );	//	set polarisation amount command
	fPolarCmd->SetGuidance( "Set linear polarization angle w.r.t. (k,n) plane" );	//	inform user
	fPolarCmd->AvailableForStates( G4State_Idle );	//	only allow modification outside of active tracking

}	//	end default constructor( PrimaryGeneratorAction* )


PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger(){	//	clean up commands

	delete fPolarCmd;
	delete fGunDir;

}	//	end default destructor


void PrimaryGeneratorMessenger::SetNewValue( G4UIcommand *command, G4String newValue ){

	if( command == fPolarCmd ){	//	if sent a polarisation command
			fPrimaryAction->SetOptPhotonPolar();	//	create an angle

	}	//	end polarisation command check

}	//	end SetNewValue( G4UIcommand*, G4String )