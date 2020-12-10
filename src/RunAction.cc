//
//	George O'Neill, University of York 2020
//
#include "RunAction.hh"


RunAction::RunAction( PrimaryGeneratorAction *prim ): G4UserRunAction(), fTimer( nullptr ), fRun( nullptr ), fHistoManager( nullptr ), fPrimary( prim ){	//	default constructor

	fTimer = new G4Timer;	//	create timer
	fHistoManager = new HistoManager();	//	create histogrammer

}	//	end default constructor


RunAction::~RunAction(){	//	clean up commands

	delete fTimer;
	delete fHistoManager;

}	//	end destructor


G4Run *RunAction::GenerateRun(){	//	create run

	fRun = new Run();	//	initialse run stored in object
	return fRun;	//	return run to program

}	//	end GenerateRun()


void RunAction::BeginOfRunAction( const G4Run *aRun ){	//	action at start of run

	G4cout << aRun->GetRunID() << " run started" << G4endl;	//	let user know the run is happening

	if( fPrimary )	//	if we have everything initialised
		fRun->SetPrimary( fPrimary->GetParticleGun()->GetParticleDefinition(), fPrimary->GetParticleGun()->GetParticleEnergy() );	//	set a primary event

	if( analysisManager->IsActive() )	//	if there is an active analysis manager
		analysisManager->OpenFile();	//	open it for output

	fTimer->Start();	//	start timer

}	//	end BeginOfRunAction( G4Run* )


void RunAction::EndOfRunAction( const G4Run *aRun ){	//	action at end of run

	fTimer->Stop();	//	stop timer
	G4cout << aRun->GetNumberOfEvent() << " finished with time " << *fTimer << G4endl;	//	let user know which run has ended

	if( isMaster )	//	if run action is master
		fRun->EndOfRun();	//	end run

	if( analysisManager->IsActive() ){	//	if there is an active analysis manager

		analysisManager->Write();	//	write this run
		analysisManager->CloseFile();	//	close output

	}	//	end check for active analysis manager

}	//	end EndOfRunAction( G4Run* )