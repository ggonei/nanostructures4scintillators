//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	This class allows for macros to do useful things
//
#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1


//  C++ libraries
#include <sstream>
#include <iostream>

//  Geant libraries
#include <globals.hh>
#include <G4OpticalSurface.hh>
#include <G4UIcmdWithADouble.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithAnInteger.hh>
#include <G4UIcmdWithAString.hh>
#include <G4UIcmdWithoutParameter.hh>
#include <G4UIcommand.hh>
#include <G4UIdirectory.hh>
#include <G4UImessenger.hh>
#include <G4UIparameter.hh>

//	My libraries
#include "MyDetectorConstruction.hh"

class MyDetectorConstruction;
//class G4UIdirectory;
//class G4UIcommand;
//class G4UIcmdWithAString;
//class G4UIcmdWithAnInteger;
//class G4UIcmdWithADouble;
//class G4UIcmdWithADoubleAndUnit;
//class G4UIcmdWithoutParameter;

class MyDetectorMessenger: public G4UImessenger{

public:
	MyDetectorMessenger( MyDetectorConstruction* );	//	default constructor
	~MyDetectorMessenger();	//	destructor definition

	virtual void SetNewValue( G4UIcommand *, G4String );	//	make sure correct function is called

private:
	MyDetectorConstruction *fMyDetector;	//	detector
	G4UIdirectory *fOpticalDir;	//	path to optical libraries
	G4UIcmdWithAString *fWorldMatCmd;	//	set entire detector material
	G4UIcmdWithAString *fWorldMatPropConstCmd;	//	set entire detector material property with nunber
	G4UIcmdWithAString *fWorldMatPropVectorCmd;	//	set entire detector material property with vector
	G4UIcmdWithAString *fCrystalMatCmd;	//	set scintillating crystal material
	G4UIcmdWithAString *fCrystalMatPropConstCmd;	//	set scintillating crystal material property with number
	G4UIcmdWithAString *fCrystalMatPropVectorCmd;	//	set scintillating crystal material property with vector
	G4UIcmdWithAString *fSurfFinishCmd;	//	set scintillating crystal material property with vector
	G4UIcmdWithAString *fSurfMatPropConstCmd;	//	set scintillating surface material property with number
	G4UIcmdWithAString *fSurfMatPropVectorCmd;	//	set scintillating surface material property with vector
	G4UIcmdWithAString *fSurfModelCmd;	//	set scintillating surface interaction model
	G4UIcmdWithADouble *fSurfPolishCmd;	//	set scintillating surface polish type
	G4UIcmdWithADouble *fSurfSigmaAlphaCmd;	//	set scintillating surface roughness
	G4UIcmdWithAString *fSurfTypeCmd;	//	set scintillating surface interface

};	//	end MyDetectorMessenger{}
#endif