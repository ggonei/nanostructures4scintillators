//
//	George O'Neill, University of York 2020
//
#include "MyDetectorMessenger.hh"


MyDetectorMessenger::MyDetectorMessenger( MyDetectorConstruction *Det ):G4UImessenger(), fMyDetector( Det ){	//	construct messenger

	fOpticalDir = new G4UIdirectory( "/MyDetector/" );	//	set directory
	fOpticalDir->SetGuidance( "Parameters for optical simulation." );	//	inform user why

	//	entire detector
	fWorldMatCmd = new G4UIcmdWithAString( "/MyDetector/WorldMat", this );	//	set entire detector material
	fWorldMatCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fWorldMatCmd->SetGuidance( "Set material of world." );	//	inform user why
	fWorldMatCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fWorldMatPropConstCmd = new G4UIcmdWithAString( "/MyDetector/worldConstProperty", this );	//	add entire detector material property as number
	fWorldMatPropConstCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fWorldMatPropConstCmd->SetGuidance( "Set material constant property for the world." );	//	inform user why
	fWorldMatPropConstCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fWorldMatPropVectorCmd = new G4UIcmdWithAString( "/MyDetector/worldProperty", this );	//	add entire detector material property
	fWorldMatPropVectorCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fWorldMatPropVectorCmd->SetGuidance( "Set material property vector for the world." );	//	inform user why
	fWorldMatPropVectorCmd->SetToBeBroadcasted( false );	//	do not send to worker threads

	//	scintillating crystal
	fCrystalMatCmd = new G4UIcmdWithAString( "/MyDetector/boxMaterial", this );	//	set scintillator crystal material
	fCrystalMatCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fCrystalMatCmd->SetGuidance( "Set material of box." );	//	inform user why
	fCrystalMatCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fCrystalMatPropConstCmd = new G4UIcmdWithAString( "/MyDetector/boxConstProperty", this );	//	add scintillator crystal material property as number
	fCrystalMatPropConstCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fCrystalMatPropConstCmd->SetGuidance( "Set material constant property for the box." );	//	inform user why
	fCrystalMatPropConstCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fCrystalMatPropVectorCmd = new G4UIcmdWithAString( "/MyDetector/boxProperty", this );	//	add scintillator crystal material property
	fCrystalMatPropVectorCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fCrystalMatPropVectorCmd->SetGuidance( "Set material property vector for the box." );	//	inform user why
	fCrystalMatPropVectorCmd->SetToBeBroadcasted( false );	//	do not send to worker threads

	//	scintillating surface
	fSurfFinishCmd = new G4UIcmdWithAString( "/MyDetector/surfaceFinish", this );	//	set scintillator surface finish
	fSurfFinishCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fSurfFinishCmd->SetGuidance( "Surface finish." );	//	inform user why
	fSurfFinishCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fSurfMatPropConstCmd = new G4UIcmdWithAString( "/MyDetector/surfaceConstProperty", this );	//	add scintillator surface material property as number
	fSurfMatPropConstCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fSurfMatPropConstCmd->SetGuidance( "Set material constant property for the surface." );	//	inform user why
	fSurfMatPropConstCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fSurfMatPropVectorCmd = new G4UIcmdWithAString( "/MyDetector/surfaceProperty", this );	//	add scintillator surface material property
	fSurfMatPropVectorCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fSurfMatPropVectorCmd->SetGuidance( "Set material property vector for the surface." );	//	inform user why
	fSurfMatPropVectorCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fSurfModelCmd = new G4UIcmdWithAString( "/MyDetector/surfaceModel", this );	//	set scintillator surface model
	fSurfModelCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fSurfModelCmd->SetGuidance( "Surface model." );	//	inform user why
	fSurfModelCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fSurfPolishCmd = new G4UIcmdWithADouble( "/MyDetector/SurfacePolish", this );	//	set scintillator surface polish type
	fSurfPolishCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fSurfPolishCmd->SetGuidance( "surface polish parameter (for Glisur model)." );	//	inform user why
	fSurfPolishCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fSurfSigmaAlphaCmd = new G4UIcmdWithADouble( "/MyDetector/surfaceSigmaAlpha", this );	//	set scintillator surface roughness
	fSurfSigmaAlphaCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fSurfSigmaAlphaCmd->SetGuidance( "Surface sigma alpha parameter." );	//	inform user why
	fSurfSigmaAlphaCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
	fSurfTypeCmd = new G4UIcmdWithAString( "/MyDetector/surfaceType", this );	//	set scintillator surface type
	fSurfTypeCmd->AvailableForStates( G4State_PreInit, G4State_Idle );	//	restrict application
	fSurfTypeCmd->SetGuidance( "Surface type." );//	inform user why
	fSurfTypeCmd->SetToBeBroadcasted( false );	//	do not send to worker threads
}	//	end constructor( MyDetectorConstruction* )



MyDetectorMessenger::~MyDetectorMessenger(){	//	clean up commands
	delete fSurfFinishCmd;
	delete fSurfTypeCmd;
	delete fSurfModelCmd;
	delete fSurfSigmaAlphaCmd;
	delete fSurfPolishCmd;
	delete fSurfMatPropVectorCmd;
	delete fSurfMatPropConstCmd;
	delete fCrystalMatPropVectorCmd;
	delete fCrystalMatPropConstCmd;
	delete fCrystalMatCmd;
	delete fWorldMatPropVectorCmd;
	delete fWorldMatPropConstCmd;
	delete fWorldMatCmd;
}	//	end destructor



void MyDetectorMessenger::SetNewValue( G4UIcommand *cmd, G4String messStr ){	//	set parameters from commands

	G4ExceptionDescription e;	//	in case no options are valid

	if( cmd == fSurfFinishCmd ){//	set scintillating surface finish

		if( messStr == "polished" ){
			fMyDetector->SetSurfFinish( polished );
		} else if( messStr == "polishedfrontpainted" ){
			fMyDetector->SetSurfFinish( polishedfrontpainted );
		} else if( messStr == "polishedbackpainted" ){
			fMyDetector->SetSurfFinish( polishedbackpainted );
		} else if( messStr == "ground" ){
			fMyDetector->SetSurfFinish( ground );
		} else if( messStr == "groundfrontpainted" ){
			fMyDetector->SetSurfFinish( groundfrontpainted );
		} else if( messStr == "groundbackpainted" ){
			fMyDetector->SetSurfFinish( groundbackpainted );
		} else if( messStr == "polishedlumirrorair" ){
			fMyDetector->SetSurfFinish( polishedlumirrorair );
		} else if( messStr == "polishedlumirrorglue" ){
			fMyDetector->SetSurfFinish( polishedlumirrorglue );
		} else if( messStr == "polishedair" ){
			fMyDetector->SetSurfFinish( polishedair );
		} else if( messStr == "polishedteflonair" ){
			fMyDetector->SetSurfFinish( polishedteflonair );
		} else if( messStr == "polishedtioair" ){
			fMyDetector->SetSurfFinish( polishedtioair );
		} else if( messStr == "polishedtyvekair" ){
			fMyDetector->SetSurfFinish( polishedtyvekair );
		} else if( messStr == "polishedvm2000air" ){
			fMyDetector->SetSurfFinish( polishedvm2000air );
		} else if( messStr == "polishedvm2000glue" ){
			fMyDetector->SetSurfFinish( polishedvm2000glue );
		} else if( messStr == "etchedlumirrorair" ){
			fMyDetector->SetSurfFinish( etchedlumirrorair );
		} else if( messStr == "etchedlumirrorglue" ){
			fMyDetector->SetSurfFinish( etchedlumirrorglue );
		} else if( messStr == "etchedair" ){
			fMyDetector->SetSurfFinish( etchedair );
		} else if( messStr == "etchedteflonair" ){
			fMyDetector->SetSurfFinish( etchedteflonair );
		} else if( messStr == "etchedtioair" ){
			fMyDetector->SetSurfFinish( etchedtioair );
		} else if( messStr == "etchedtyvekair" ){
			fMyDetector->SetSurfFinish( etchedtyvekair );
		} else if( messStr == "etchedvm2000air" ){
			fMyDetector->SetSurfFinish( etchedvm2000air );
		} else if( messStr == "etchedvm2000glue" ){
			fMyDetector->SetSurfFinish( etchedvm2000glue );
		} else if( messStr == "groundlumirrorair" ){
			fMyDetector->SetSurfFinish( groundlumirrorair );
		} else if( messStr == "groundlumirrorglue" ){
			fMyDetector->SetSurfFinish( groundlumirrorglue );
		} else if( messStr == "groundair" ){
			fMyDetector->SetSurfFinish( groundair );
		} else if( messStr == "groundteflonair" ){
			fMyDetector->SetSurfFinish( groundteflonair );
		} else if( messStr == "groundtioair" ){
			fMyDetector->SetSurfFinish( groundtioair );
		} else if( messStr == "groundtyvekair" ){
			fMyDetector->SetSurfFinish( groundtyvekair );
		} else if( messStr == "groundvm2000air" ){
			fMyDetector->SetSurfFinish( groundvm2000air );
		} else if( messStr == "groundvm2000glue" ){
			fMyDetector->SetSurfFinish( groundvm2000glue );
		} else if( messStr == "Rough_LUT" ){
			fMyDetector->SetSurfFinish( Rough_LUT );
		} else if( messStr == "RoughTeflon_LUT" ){
			fMyDetector->SetSurfFinish( RoughTeflon_LUT );
		} else if( messStr == "RoughESR_LUT" ){
			fMyDetector->SetSurfFinish( RoughESR_LUT );
		} else if( messStr == "RoughESRGrease_LUT" ){
			fMyDetector->SetSurfFinish( RoughESRGrease_LUT );
		} else if( messStr == "Polished_LUT" ){
			fMyDetector->SetSurfFinish( Polished_LUT );
		} else if( messStr == "PolishedTeflon_LUT" ){
			fMyDetector->SetSurfFinish( PolishedTeflon_LUT );
		} else if( messStr == "PolishedESR_LUT" ){
			fMyDetector->SetSurfFinish( PolishedESR_LUT );
		} else if( messStr == "PolishedESRGrease_LUT" ){
			fMyDetector->SetSurfFinish( PolishedESRGrease_LUT );
		} else if( messStr == "Detector_LUT" ){
			fMyDetector->SetSurfFinish( Detector_LUT );
		} else{

			e << "Invalid surface finish: " << messStr;	//	tell user what failed	//	tell user what failed
			G4Exception( "MyDetectorMessenger", "MyDetector_003", FatalException, e );	//	send failure
		}	//	end string check

	}	//	end set scintillating surface finish
	else if( cmd == fSurfModelCmd ){	//	set scintillating surface model

		if( messStr == "glisur" ){
			fMyDetector->SetSurfModel( glisur );
		} else if( messStr == "unified" ){
			fMyDetector->SetSurfModel( unified );
		} else if( messStr == "LUT" ){
			fMyDetector->SetSurfModel( LUT );
		} else if( messStr == "DAVIS" ){
			fMyDetector->SetSurfModel( DAVIS );
		} else if( messStr == "dichroic" ){
			fMyDetector->SetSurfModel( dichroic );
		} else{
			e << "Invalid surface model: " << messStr;	//	tell user what failed
			G4Exception( "MyDetectorMessenger", "ONovice2_001", FatalException, e );	//	send failure
		}	//	end string check

	}	//	end set scintillating surface model
	else if( cmd == fSurfTypeCmd ){	//	set scintillating surface type

		if( messStr == "dielectric_metal" ){
			fMyDetector->SetSurfType( dielectric_metal );
		} else if( messStr == "dielectric_dielectric" ){
			fMyDetector->SetSurfType( dielectric_dielectric );
		} else if( messStr == "dielectric_LUT" ){
			fMyDetector->SetSurfType( dielectric_LUT );
		} else if( messStr == "dielectric_LUTDAVIS" ){
			fMyDetector->SetSurfType( dielectric_LUTDAVIS );
		} else{

			e << "Invalid surface type: " << messStr;	//	tell user what failed
			G4Exception( "MyDetectorMessenger", "MyDetector_002", FatalException, e );	//	send failure
		}

	} else if( cmd == fSurfSigmaAlphaCmd ){	//	set scintillating surface roughness
		fMyDetector->SetSurfSigmaAlpha( G4UIcmdWithADouble::GetNewDoubleValue( messStr ) );
	} else if( cmd == fSurfPolishCmd ){	//	set scintillating surface polish level
		fMyDetector->SetSurfPolish( G4UIcmdWithADouble::GetNewDoubleValue( messStr ) );
	} else if( cmd == fWorldMatPropVectorCmd || cmd == fCrystalMatPropVectorCmd || cmd == fSurfMatPropVectorCmd ){	//	add material property as a vector
		G4MaterialPropertyVector *mpv = new G4MaterialPropertyVector();	//	create new vector
		std::istringstream instring( messStr );	//	convert fetched string into stream
		G4String prop;	//	initialise property string
		instring >> prop;	//	read fetched string into property string
		const char *c = prop.c_str();	//	convert first part of string to character

		while( instring ){	//	while we still have string left
			G4String tmp;	//	create a temporary string
			instring >> tmp;	//	read into the temporary string
			if( tmp == "" )	//	exit if string is empty
				break;	//	exit while loop
			G4double en = G4UIcommand::ConvertToDouble( tmp );	//	convert and store string into double
			instring >> tmp;	//	read next part of string
			G4double val;	//	initialise value
			val = G4UIcommand::ConvertToDouble( tmp );	//	convert next part of string and store as corresponding value
			mpv->InsertValues( en, val );	//	insert new material property to vector
		}	//	end while loop

		if( cmd == fWorldMatPropVectorCmd ) fMyDetector->AddAnotherMPV( fMyDetector->GetWorldMatPropertiesTable(), c, mpv );	//	add new material property vector to entire detector
		else if( cmd == fCrystalMatPropVectorCmd ) fMyDetector->AddAnotherMPV( fMyDetector->GetCrystalMatPropertiesTable(), c, mpv );	//	add new material property vector to scintillating crystal
		else if( cmd == fSurfMatPropVectorCmd ) fMyDetector->AddAnotherMPV( fMyDetector->GetSurfMatPropertiesTable(), c, mpv );	//	add new material property vector to scintillating surface

	}
	else if( cmd == fWorldMatPropConstCmd || cmd == fCrystalMatPropConstCmd || cmd == fSurfMatPropConstCmd ){	//	add material property as a number

		std::istringstream instring( messStr );
		G4String prop;
		G4String tmp;
		instring >> prop;
		instring >> tmp;
		G4double val = G4UIcommand::ConvertToDouble( tmp );
		const char *c = prop.c_str();
		if( cmd == fWorldMatPropConstCmd )fMyDetector->AddAnotherMPC( fMyDetector->GetWorldMatPropertiesTable(), c, val );	//	add new material property to entire detector
		else if( cmd == fCrystalMatPropConstCmd )			fMyDetector->AddAnotherMPC( fMyDetector->GetCrystalMatPropertiesTable(), c, val );	//	add new material property to scintillating crystal
		else if( cmd == fSurfMatPropConstCmd )			fMyDetector->AddAnotherMPC( fMyDetector->GetSurfMatPropertiesTable(), c, val );	//	add new material property to scintillating surface

	} else if( cmd == fWorldMatCmd ){	//	set entire detector material
		fMyDetector->SetMat(fMyDetector->GetWorldMat(), messStr );
	} else if( cmd == fCrystalMatCmd ){	//	set scintillating crystal material
		fMyDetector->SetMat( fMyDetector->GetCrystalMat(), messStr );
	}

}	//	end SetNewValue( G4UIcommand*, string ) 