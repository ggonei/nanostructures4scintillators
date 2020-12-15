//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	!This class defines the mandatory extension of G4VUserDetectorConstruction and must be used!
//
//	It creates our detector, or a least the structure involved, allowing for actual values to be set by messenger macro
//
#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 1
#define BIRKS_CONSTANT 1 * mm / MeV	//	set to 1 as per SP

//  Geant libraries
#include <globals.hh>
#include <G4Box.hh>
#include <G4Element.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>
#include <G4LogicalVolume.hh>
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4OpticalSurface.hh>
#include <G4PVPlacement.hh>
#include <G4RunManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4ThreeVector.hh>
#include <G4VUserDetectorConstruction.hh>

//	My libraries
#include "MyDetectorMessenger.hh"

class MyDetectorMessenger;
class MyDetectorConstruction: public G4VUserDetectorConstruction{

public:

	MyDetectorConstruction();	//	default constructor
	~MyDetectorConstruction(){	//	destructor
		delete fMyDetectorMessenger;	//	delete the only thing we need to
	}	//	end destructor

	//	fetch world is implicit to simulation
	G4VPhysicalVolume *GetCrystal(){	//	fetch scintillating crystal
		return fCrystal;
	}
	G4OpticalSurface *GetSurf(){	//	fetch scintillating surface
		return fSurf;
	}
	G4OpticalSurfaceFinish GetSurfFinish(){	//	fetch scintillating surface type
		return fSurf->GetFinish();
	}
	G4OpticalSurfaceModel GetSurfModel(){	//	fetch scintillating surface model
		return fSurf->GetModel();
	}
	G4double GetCrystalXSize(){	//	fetch scintillating crystal length
		return fCrystalX;
	}
	G4MaterialPropertiesTable *GetCrystalMatPropertiesTable(){	//	fetch scintillating crystal properties
		return fCrystalMPT;
	}
	G4MaterialPropertiesTable *GetWorldMatPropertiesTable(){	//	fetch entire detector properties
		return fWorldMPT;
	}
	G4MaterialPropertiesTable *GetSurfMatPropertiesTable(){	//	fetch scintillating edge properties
		return fSurfMPT;
	}
	G4Material *GetWorldMat()const{	//	fetch entire detector material
		return fWorldMat;
	}
	G4Material *GetCrystalMat()const{	//	fetch scintillating crystal material
		return fCrystalMat;
	}
	void AddAnotherMPV( G4MaterialPropertiesTable *mpt, const char *c, G4MaterialPropertyVector *mpv );	//	add entire detector properties
	void AddAnotherMPC( G4MaterialPropertiesTable *mpt, const char *c, G4double v );	//	change material property table
	void SetMat( G4Material *fMat, const G4String & );	//	set material types
	void SetSurfFinish( const G4OpticalSurfaceFinish finish ){	//	change scintillating surface roughness and notify user
		fSurf->SetFinish( finish );
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}
	void SetSurfModel( const G4OpticalSurfaceModel model ){	//	change scintillating surface model and notify user
		fSurf->SetModel( model );
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}
	void SetSurfPolish( G4double v );	//	set surface smoothness
	void SetSurfSigmaAlpha( G4double v );	//	set surface alpha
	void SetSurfType( const G4SurfaceType type ){	//	change scintillating surface material and notify user
		fSurf->SetType( type );
		G4RunManager::GetRunManager()->GeometryHasBeenModified();
	}

	virtual G4VPhysicalVolume *Construct();	//	make sure correct function is called


private:
	//Volumes
	G4LogicalVolume *fWorldLogi;	//	entire detector
	G4LogicalVolume *fCrystalLogi;	//	scintillating crystal basics
	G4VPhysicalVolume *fCrystal;	//	scintillating crystal with materials
	G4LogicalVolume *fNanoLogi;	//	scintillating crystal basics
	G4VPhysicalVolume *fNano;	//	scintillating crystal with materials

	//Materials
	G4Material *fWorldMat;	//	entire detector
	G4Material *fCrystalMat;	//	scintillator crystal
	G4OpticalSurface *fSurf;	//	scintillator edge
	G4Material *fNanoMat;	//	scintillator crystal
	G4OpticalSurface *fNanoSurf;	//	scintillator edge

	//Material Properties
	G4MaterialPropertiesTable *fWorldMPT;	//	entire detector
	G4MaterialPropertiesTable *fCrystalMPT;	//	scintillating crystal
	G4MaterialPropertiesTable *fSurfMPT;	//	scintillator edge
	G4MaterialPropertiesTable *fNanoMPT;	//	scintillating crystal
	G4MaterialPropertiesTable *fNanoSurfMPT;	//	scintillator edge

	//Position Properties
	G4double fWorldX, fWorldY, fWorldZ;	//	entire detector
	G4double fCrystalX, fCrystalY, fCrystalZ;	// scintillating crystal

	//Messenger
	MyDetectorMessenger *fMyDetectorMessenger;	//	allow things to happen to this detector


};	//	end MyDetectorConstruction{}
#endif