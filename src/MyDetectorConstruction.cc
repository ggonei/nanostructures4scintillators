//
//	George O'Neill, University of York 2020
//
#include "MyDetectorConstruction.hh"

MyDetectorConstruction::MyDetectorConstruction(): G4VUserDetectorConstruction(), fMyDetectorMessenger( nullptr ){	//	default constructor

	fWorldX = fWorldY = fWorldZ = 200. * cm;	//	20x20x20 crystal
	fCrystalX = fCrystalY = fCrystalZ = 100. * cm;	//	10x10x10 world
	fWorldLogi = nullptr;	//	initialise world
	fCrystalLogi = nullptr;	//	initialise crystal
	fCrystal = nullptr;	//	no crystal to begin with
	fSurf = new G4OpticalSurface( "Surf" );	//	new optical surface
	fCrystalMat = G4NistManager::Instance()->FindOrBuildMaterial( "G4_CESIUM_IODIDE" );	//	crystal material
	fWorldMat = G4NistManager::Instance()->FindOrBuildMaterial( "G4_AIR" );	//	detector is in normal atmosphere
	fWorldMPT = new G4MaterialPropertiesTable();	//	plain properties for entire detector
	fCrystalMPT = new G4MaterialPropertiesTable();	//	plain properties for scintillating crystal
	fSurfMPT = new G4MaterialPropertiesTable();	//	plain properties for scintillating surface
	fSurf->SetType( dielectric_LUTDAVIS );	//	this is the best optical type
	fSurf->SetFinish( polishedair );	//	basic polished air finish
	fSurf->SetModel( DAVIS );	//	best optical model
	fSurf->SetMaterialPropertiesTable( fSurfMPT );	//	set basic properties
	fMyDetectorMessenger = new MyDetectorMessenger( this );	//	create messenger to set properties via macro

}	//	end default constructor

G4VPhysicalVolume *MyDetectorConstruction::Construct(){	//	construct basic detector

	fWorldMat->SetMaterialPropertiesTable( fWorldMPT );	//	add realproperties to world
	G4Box *worldBox = new G4Box( "World", fWorldX, fWorldY, fWorldZ );	//	detector dimensions
	fWorldLogi = new G4LogicalVolume( worldBox, fWorldMat, "World", 0, 0, 0 );	//	detector logical setup but the numbers are not positions
	G4VPhysicalVolume *worldPhys = new G4PVPlacement( 0, G4ThreeVector(), fWorldLogi, "World", 0, false, 0 );	//	place detector at origin

	fCrystalMat->SetMaterialPropertiesTable( fCrystalMPT );	//	add realproperties to scintillating crystal
	fCrystalMat->GetIonisation()->SetBirksConstant( BIRKS_CONSTANT );	//	default 0.126, SP suggested to ignore for now
	G4Box *CrystalBox = new G4Box( "Crystal", fCrystalX, fCrystalY, fCrystalZ );	//	scintillating crystal dimensions
	fCrystalLogi = new G4LogicalVolume( CrystalBox, fCrystalMat, "Crystal", 0, 0, 0 );	//	scintillating crystal logical setup
	fCrystal = new G4PVPlacement( 0, G4ThreeVector(), fCrystalLogi, "Crystal", fWorldLogi, false, 0 );	//	place scintillating crystal in detector

	G4LogicalBorderSurface *surf = new G4LogicalBorderSurface( "Surf", fCrystal, worldPhys, fSurf );	// create scintillating surface in our detector
	G4OpticalSurface *opticalSurf = (G4OpticalSurface *)( surf->GetSurface( fCrystal, worldPhys )->GetSurfaceProperty() );	//	add optical properties to surface

	if( opticalSurf )	//	check pointer exists to object
		opticalSurf->DumpInfo();	//	inform user of object
	else	//	we have no object
		G4cout << "ERROR: You have no optical surface!" << G4endl;	//	user should worry

	return worldPhys;	//	return a basic detector

}	//	end Construct()


void MyDetectorConstruction::SetSurfSigmaAlpha( G4double v ){	//	set surface roughness

	fSurf->SetSigmaAlpha( v );	//	get current roughness
	G4RunManager::GetRunManager()->GeometryHasBeenModified();	//	inform manager because it is good practice
	G4cout << "Surf sigma alpha set to: " << fSurf->GetSigmaAlpha() << G4endl;	//	let user know

}	//	end SetSurfSigmaAlpha( double )


void MyDetectorConstruction::SetSurfPolish( G4double v ){	//	set surface polish factor

	fSurf->SetPolish( v );	//	make the change
	G4RunManager::GetRunManager()->GeometryHasBeenModified();	//	inform manager because it is good practice
	G4cout << "Surf polish set to: " << fSurf->GetPolish() << G4endl;	//	let user know

}	//	end SetSurfPolish( double )


void MyDetectorConstruction::SetMat( G4Material *fMat, const G4String &mat ){	//	set material of a type

	G4Material *pmat = G4NistManager::Instance()->FindOrBuildMaterial( mat );	//	get the material type requested

	if( pmat && fMat != pmat ){	//	if requested material is not that material
		fMat = pmat;	//	set requested material to specified
		if( ( fMat == fCrystalMat && fCrystalLogi ) ){	//	if we have a scintillating crystal
			fCrystalLogi->SetMaterial( fCrystalMat );	//	update logical volume scintillatng crystal
			fCrystalMat->SetMaterialPropertiesTable( fCrystalMPT );	//	update material properties
			fCrystalMat->GetIonisation()->SetBirksConstant( BIRKS_CONSTANT );	//	reset Birks constant
		} else if( fMat == fWorldMat && fWorldLogi ){	//	else if we have the entire detector
			fWorldLogi->SetMaterial( fWorldMat );	//	update logical volume of entire detector
			fWorldMat->SetMaterialPropertiesTable( fWorldMPT );	//	update material properties
		}	//	end material and logical check
	}	//	end material check

	G4RunManager::GetRunManager()->PhysicsHasBeenModified();	//	inform manager because it is good practice
	G4cout << "Material set to " << fMat->GetName() << G4endl;	//	let user know

}	//	end SetMat( G4Material*, G4String )


void MyDetectorConstruction::AddAnotherMPV( G4MaterialPropertiesTable *mpt, const char *c, G4MaterialPropertyVector *mpv ){	//	add another material property vector

	mpt->AddProperty( c, mpv );	//	add property to material
	G4cout << "Added a new property: " << G4endl;	//	Useful output to prefix dump
	mpt->DumpTable();	//	show user table so that nothing is missed

}	//	end AddAnotherMPV ( G4MaterialPropertiesTable*, char*, G4MaterialPropertyVector* )

void MyDetectorConstruction::AddAnotherMPC( G4MaterialPropertiesTable *mpt, const char *c, G4double v ){	//	Add another material property constant

	mpt->AddConstProperty( c, v );	//	add property to mateiral
	G4cout << "The MPT for this is now: " << G4endl;	//	Useful output to prefix dup
	mpt->DumpTable();	//	show user so that nothing is missed

}	//	end AddAnotherMPC ( G4MaterialPropertiesTable, char*, double )