//
//	George O'Neill, University of York 2020
//
#include "PrimaryGeneratorMessenger.hh"


PrimaryGeneratorMessenger::PrimaryGeneratorMessenger( PrimaryGeneratorAction *Gun ): G4UImessenger(), fPrimaryAction( Gun ){

	fGunDir = new G4UIdirectory( "/n4s/gun/" );	//	set gun prefix
	fGunDir->SetGuidance( "PrimaryGenerator control" );	//	inform user
	fPolarCmd = new G4UIcmdWithADoubleAndUnit( "/n4s/gun/optPhotonPolar", this );	//	set polarisation amount command
	fPolarCmd->SetGuidance( "Set linear polarization angle w.r.t. (k,n) plane" );	//	inform user
	fPolarCmd->SetParameterName( "angle", true );	//	set angle to be available
	fPolarCmd->SetUnitCategory( "Angle" );	//	set unit to correct category
	fPolarCmd->SetDefaultValue( -360.0 );	//	initialise angle
	fPolarCmd->SetDefaultUnit( "deg" );	//	set angle to be in degrees by default
	fPolarCmd->AvailableForStates( G4State_Idle );	//	only allow modification outside of active tracking

}	//	end default constructor( PrimaryGeneratorAction* )


PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger(){	//	clean up commands

	delete fPolarCmd;
	delete fGunDir;

}	//	end default destructor


void PrimaryGeneratorMessenger::SetNewValue( G4UIcommand *command, G4String newValue ){

	if( command == fPolarCmd ){	//	if sent a polarisation command

		G4double angle = fPolarCmd->GetNewDoubleValue( newValue );	//	Create new value for angle

		if( angle == -360.0 * deg )	//	if angle is not real
			fPrimaryAction->SetOptPhotonPolar();	//	create an angle
		else	//	otherwise if angle is physical
			fPrimaryAction->SetOptPhotonPolar( angle );	//	update polarisation

	}	//	end polarisation command check

}	//	end SetNewValue( G4UIcommand*, G4String )