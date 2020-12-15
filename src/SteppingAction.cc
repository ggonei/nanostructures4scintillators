//
//	George O'Neill, University of York 2020
//
#include "SteppingAction.hh"

void SteppingAction::UserSteppingAction( const G4Step *step ){	//	create action executed every step

	G4AnalysisManager *analysisMan = G4AnalysisManager::Instance();	//	fetch this instance
	Run *run = static_cast<Run *>( G4RunManager::GetRunManager()->GetNonConstCurrentRun() );	//	fetch this run
	G4StepPoint *endPoint = step->GetPostStepPoint();	//	get end of step
	G4StepPoint *startPoint = step->GetPreStepPoint();	//	get start of step
	G4Track *track = step->GetTrack();	//	get particle track
	G4String particleName = track->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();	//	get particle name
	TrackInformation *trackInfo = (TrackInformation *)( track->GetUserInformation() );	//	get track information
	G4int whichH = 3;	//	momentum histogram switcher

	if( particleName == "opticalphoton" ){	//	all should be optical photons for now

		const G4VProcess *pds = endPoint->GetProcessDefinedStep();	//	get process of step

		if( pds->GetProcessName() == "OpAbsorption" ){	//	if our particle was absorbed

			run->AddOpAbsorption();	//	increment absorption counter

			if( trackInfo->GetIsFirstCrystalX() )	//	check if particle is in first crystal
				run->AddOpAbsorptionPrior();	//	increment absorption prior to edge counter

		}

		if( endPoint->GetStepStatus() == fGeomBoundary ){	//	if particle has scattered to boundary

			const G4DynamicParticle *theParticle = track->GetDynamicParticle();	//	fetch particle
			G4ThreeVector oldMomentumDir = theParticle->GetMomentumDirection();	//	fetch previous direction
			G4ThreeVector m0 = startPoint->GetMomentumDirection();	//	fetch starting momentum direction
			G4ThreeVector m1 = endPoint->GetMomentumDirection();	//	fetch ending momentum direction
			G4OpBoundaryProcessStatus thisState = Undefined;	//	initialise status
			G4ProcessManager *OpManager = G4OpticalPhoton::OpticalPhoton()->GetProcessManager();	//	fetch optical photon
			G4int loopMax = OpManager->GetPostStepProcessVector()->entries();	//	maximum number of steps to loop over
			G4ProcessVector *postStepDoItVector = OpManager->GetPostStepProcessVector( typeDoIt );	//	process vector at end of steps
/*			G4ThreeVector momdir = endPoint->GetMomentumDirection();	//	fetch momentum now
			G4double px1 = momdir.x();	//	momentum x
			G4double py1 = momdir.y();	//	momentum y
			G4double pz1 = momdir.z();	//	momentum z
*/
			if( trackInfo->GetIsFirstCrystalX() ){	//	if we are in the first crystal

				trackInfo->SetIsFirstCrystalX( false );	//	set flag so we do not fill again
				run->AddTotalSurf();	//	increment surface

				for( G4int i = 0; i < loopMax; ++i ){	//	loop over track parts

					G4VProcess *currentProcess = ( *postStepDoItVector )[i];	//	fetch process from step
					G4OpBoundaryProcess *opProc = dynamic_cast<G4OpBoundaryProcess *>( currentProcess );	//	fetch boundary process

					if( opProc ){	//	if we have a boundary process

						thisState = opProc->GetStatus();	//	get state of particle
						analysisMan->FillH1( 1, thisState );	//	fill state histogram

						if( thisState == Transmission )	//	if transmission event
							run->AddTransmission();	//	increment transmission count

						//	for a variety of surface events...
						else if( thisState == Absorption )
							run->AddAbsorption();
						else if( thisState == BackScattering )
							run->AddBackScattering();
						else if( thisState == Detection )
							run->AddDetection();
						else if( thisState == Dichroic )
							run->AddDichroic();
						else if( thisState == EtchedAirReflection )
							run->AddEtchedAirReflection();
						else if( thisState == EtchedLumirrorAirReflection )
							run->AddEtchedLumirrorAirReflection();
						else if( thisState == EtchedLumirrorGlueReflection )
							run->AddEtchedLumirrorGlueReflection();
						else if( thisState == EtchedTeflonAirReflection )
							run->AddEtchedTeflonAirReflection();
						else if( thisState == EtchedTiOAirReflection )
							run->AddEtchedTiOAirReflection();
						else if( thisState == EtchedTyvekAirReflection )
							run->AddEtchedTyvekAirReflection();
						else if( thisState == EtchedVM2000AirReflection )
							run->AddEtchedVM2000AirReflection();
						else if( thisState == EtchedVM2000GlueReflection )
							run->AddEtchedVM2000AirReflection();
						else if( thisState == FresnelReflection )
							run->AddFresnelReflection();
						else if( thisState == GroundAirReflection )
							run->AddGroundAirReflection();
						else if( thisState == GroundLumirrorAirReflection )
							run->AddGroundLumirrorAirReflection();
						else if( thisState == GroundLumirrorGlueReflection )
							run->AddGroundLumirrorGlueReflection();
						else if( thisState == GroundTeflonAirReflection )
							run->AddGroundTeflonAirReflection();
						else if( thisState == GroundTiOAirReflection )
							run->AddGroundTiOAirReflection();
						else if( thisState == GroundTyvekAirReflection )
							run->AddGroundTyvekAirReflection();
						else if( thisState == GroundVM2000AirReflection )
							run->AddGroundVM2000AirReflection();
						else if( thisState == GroundVM2000GlueReflection )
							run->AddGroundVM2000AirReflection();
						else if( thisState == LambertianReflection )
							run->AddLambertianReflection();
						else if( thisState == LobeReflection )
							run->AddLobeReflection();
						else if( thisState == NoRINDEX )
							run->AddNoRINDEX();
						else if( thisState == NotAtBoundary )
							run->AddNotAtBoundary();
						else if( thisState == PolishedAirReflection )
							run->AddPolishedAirReflection();
						else if( thisState == PolishedLumirrorAirReflection )
							run->AddPolishedLumirrorAirReflection();
						else if( thisState == PolishedLumirrorGlueReflection )
							run->AddPolishedLumirrorGlueReflection();
						else if( thisState == PolishedTeflonAirReflection )
							run->AddPolishedTeflonAirReflection();
						else if( thisState == PolishedTiOAirReflection )
							run->AddPolishedTiOAirReflection();
						else if( thisState == PolishedTyvekAirReflection )
							run->AddPolishedTyvekAirReflection();
						else if( thisState == PolishedVM2000AirReflection )
							run->AddPolishedVM2000AirReflection();
						else if( thisState == PolishedVM2000GlueReflection )
							run->AddPolishedVM2000AirReflection();
						else if( thisState == SameMaterial )
							run->AddSameMaterial();
						else if( thisState == SpikeReflection )
							run->AddSpikeReflection();
						else if( thisState == StepTooSmall )
							run->AddStepTooSmall();
						else if( thisState == TotalInternalReflection )
							run->AddTotalInternalReflection();
						//	...increment the right counter
						else	//	something is not right...
							G4cout << "***Unknown Action***" << G4endl;	//	let user know

					}	//	end boundary operations

				}	//	end for loop over steps

			}	//	end first crystal check
/*			else{

				if( px1 < 0 )	//	if we have negative momentum
					whichH = 0;	//	fill in the correct histogram

				analysisMan->FillH1( 2 + whichH, px1 );	//	fill final momentum x histogram
				analysisMan->FillH1( 3 + whichH, py1 );	//	fill final momentum y histogram
				analysisMan->FillH1( 4 + whichH, pz1 );	//	fill final momentum z histogram

			}

*/		}	//	end boundary check

	}	//	end optical photon check

}	//	end UserSteppingAction( G4Step* )