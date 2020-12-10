//
//	George O'Neill, University of York 2020
//
#include "MyActionInitialization.hh"


MyActionInitialization::MyActionInitialization(): G4VUserActionInitialization(){}	//	default constructor
MyActionInitialization::~MyActionInitialization(){}	//	default destructor does not need to do anything

void MyActionInitialization::BuildForMaster() const{	//	create simple action

	SetUserAction( new RunAction() );	//	create and run a new action

}	//	end BuildForMaster()


void MyActionInitialization::Build() const{	//	create fancy action

	PrimaryGeneratorAction *primary = new PrimaryGeneratorAction();	//	initialise a generator
	SetUserAction( primary );	//	pass this to user action role
	SetUserAction( new RunAction( primary ) );	//	make a new run with this
	SetUserAction( new SteppingAction() );	//	monitor step
	SetUserAction( new TrackingAction );	//	monitor track

}