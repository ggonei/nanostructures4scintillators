//
//	George O'Neill, University of York 2020
//
//  This is the code that sets up the environment to run simulations
//	It is a bit dull but note where the rest of the custom code hooks in on USER lines
//

//  Geant libraries
#include "G4Types.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
typedef G4RunManager G4MTRunManager;
#endif
#include "G4UImanager.hh"
#include "G4String.hh"
#include "FTFP_BERT_HP.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmLivermorePhysics.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//  My libraries
#include "MyDetectorConstruction.hh"
#include "MyActionInitialization.hh"

//	main MUST provide G4RunManager, and classes inheriting from G4VUserDetectorConstruction, G4VUserPhysicsList, G4VUserPrimaryGeneratorAction
int main( int argc, char **argv ){

	G4UIExecutive *ui = nullptr;	//	initialise interactive mode to false

	if( argc == 1 )
		ui = new G4UIExecutive( argc, argv );	//	initialise interactive mode if we have one

	G4MTRunManager *rMan = new G4MTRunManager;	//	create run manager
	rMan->SetNumberOfThreads( std::min( G4Threading::G4GetNumberOfCores(), 4 ) );	//	use multicore
	MyDetectorConstruction *det = new MyDetectorConstruction();	//	MANDATORY	//	create detector	//	CUSTOM
	rMan->SetUserInitialization( det );	//	detector parameters
	G4VModularPhysicsList *physList = new FTFP_BERT_HP;	//	MANDATORY	//	Fritiof Model + Bertini Cascade Model + High Precision Neutron Model
	physList->ReplacePhysics( new G4EmLivermorePhysics() );	//	alter the physics used to Livermore model which is better at sub-GeV processes
	G4OpticalPhysics *optPhys = new G4OpticalPhysics();	//	We are interested in the optical physics
	optPhys->SetWLSTimeProfile( "exponential" );	//	delta function is more accurate than default exponential for signal decay time only in wave length shifting fibre
	optPhys->SetScintillationYieldFactor( 1. );	//	set a simple crystal yield
	optPhys->SetScintillationExcitationRatio( 0. );	//	set a simple excitation ratio
	optPhys->SetTrackSecondariesFirst( kScintillation, true );	//	track our interesting photons before next step of primary particle produces more
	physList->RegisterPhysics( optPhys );	//	add optical physics to our simulation physics
	rMan->SetUserInitialization( physList );	//	update in run manager
	rMan->SetUserInitialization( new MyActionInitialization() );	//	initialise simulation	//	CUSTOM
	G4VisManager *visualiser = new G4VisExecutive;	//	fetch a window to use
	visualiser->Initialize();	//	open window
	G4UImanager *visualiserUI = G4UImanager::GetUIpointer();	//	get pointer to possible real window

	if( ui ){	//	if there is a real window

		visualiserUI->ApplyCommand( "/control/execute macros/runrunrun.mac" );	//	execute initial visualiser macro
		ui->SessionStart();	//	open window for user
		delete ui;	//	we are done with creating a user interface

	} else	//	program is running in batch mode
		visualiserUI->ApplyCommand( "/control/execute " + (G4String)argv[1] );	//	so just execute the macro requested

	delete visualiser;	//	clean up window
	delete rMan;	//	clean up manager
	return 0;	//	return a successful operation

}	//	main( int, int )