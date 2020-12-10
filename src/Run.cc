//
//	George O'Neill, University of York 2020
//
#include "Run.hh"
#include "MyDetectorConstruction.hh"


Run::Run(): G4Run(){

	int n = 50;	//	number of conditions
	fBoundaryProcs.clear();	//	reset boundary conditions
	fBoundaryProcs.resize( n );	//	resize boundary processes
	fEk = -1.;	//	set to a non physical energy
	fOpAbs = 0;	//	absorption amount set to nothing
	fOpAbsPrior = 0;	//	prior absorption
	fParticle = nullptr;	//	initialise particle
	fRayleighN = 0;	//	number of rayleigh photons initialised
	fScintN = 0;	//	number of scintillated photons initialised
	fScintE = 0.0;	//	scintillation energy not moving
	fTotSurf = 0;	//	total surface amount initilaised

	for( G4int i = 0; i < n; ++i )	//	loop over boundary processes
		fBoundaryProcs[i] = 0;	//	set boundary processes to zero

}	//	end default constructor


void Run::SetPrimary( G4ParticleDefinition *particle, G4double energy ){	//	set primary particle

	fEk = energy;	//	set energy
	fParticle = particle;	//	set particle

}	//	end SetPrimary( G4ParticleDefinition*, G4double )


void Run::Merge( const G4Run *R ){	//	merge particles

	const Run *localR = static_cast<const Run *>( R );	//	redefine run
	fEk = localR->fEk;	//	set energy from particle
	fOpAbs += localR->fOpAbs;	//	add absorption amount from particle
	fOpAbsPrior += localR->fOpAbsPrior;	//	add amount absorbed previous from particle
	fParticle = localR->fParticle;	//	set particle from particle
	fScintN += localR->fScintN;	//	add scintillation count from particle
	fScintE += localR->fScintE;	//	add scintillation energy from particle
	fTotSurf += localR->fTotSurf;	//	add surface from particle

	for( size_t i = 0; i < fBoundaryProcs.size(); ++i )	//	for each boundary process
		fBoundaryProcs[i] += localR->fBoundaryProcs[i];	//	add processes

	G4Run::Merge( R );	//	merge particle in main geant class

}	//	end Merge( G4run* )


void Run::EndOfRun(){	//	when particle is done run processes

	const G4int prec = G4cout.precision( 3 ), sum = std::accumulate( fBoundaryProcs.begin(), fBoundaryProcs.end(), 0 ), totEvents = numberOfEvent;	//	set precision, accumulated number, total number of event

	if( totEvents == 0 )	//	if there are no events
		return;	//	do nothing

	const MyDetectorConstruction *det = (const MyDetectorConstruction *)( G4RunManager::GetRunManager()->GetUserDetectorConstruction() );	//	fetch detector
	std::ios::fmtflags mode = G4cout.flags();	//	fetch cout specialities

	G4cout << fParticle->GetParticleName() << " with energy " << G4BestUnit( fEk, "Energy" ) << " summary:" << G4endl;	//	header for user info
	G4cout << "Volume material:\t" << det->GetWorldMat()->GetName() << G4endl;	//	inform user of entire detector material
	G4cout << "Scintillator material:\t" << det->GetCrystalMat()->GetName() << G4endl;	//	inform user of scintillating crystal material
	G4cout << "# of primary particles (surface events):\t" << std::setw( 8 ) << totEvents << G4endl;	//	number of primary photons
	G4cout << "Average number of Rayleigh scattering per event:\t" << fRayleighN / totEvents << G4endl;	//	output rayleigh scattering information
	G4cout << "Average number of Absorption per event:\t" << fOpAbs / totEvents << G4endl;	//	output absorption information
	G4cout << "Absorption before surface:\t" << std::setw( 8 ) << fOpAbsPrior << G4endl;	//	output absorption before reaching surface
	G4cout << "Total # of surface events:\t" << std::setw( 8 ) << fTotSurf << G4endl;	//	total events at surface
	G4cout << "Sum:\t" << std::setw( 8 ) << sum << G4endl;	//	output sum of events
	G4cout << "Unaccounted for:\t" << std::setw( 8 ) << fTotSurf - sum << G4endl;	//	output untracked total events
	G4cout.setf( mode, std::ios::floatfield );	//	set flags
	G4cout.precision( prec );	//	set precision

	if( fParticle->GetParticleName() == "opticalphoton" )	//	for optical photons
		G4cout << "Unaccounted for:\t" << std::setw( 8 ) << fTotSurf + fOpAbsPrior - totEvents << G4endl;	//	output number not tracked to end

	G4cout << "\nSurf events by process:" << G4endl;	//	output surface events

	//	for a variety of surface events...
	if( fBoundaryProcs[Absorption] > 0 )
		G4cout << "\tAbsorption:\t" << std::setw( 8 ) << fBoundaryProcs[Absorption] << G4endl;
	if( fBoundaryProcs[BackScattering] > 0 )
		G4cout << "\tBackscattering:\t" << std::setw( 8 ) << fBoundaryProcs[BackScattering] << G4endl;
	if( fBoundaryProcs[Detection] > 0 )
		G4cout << "\tDetection:\t" << std::setw( 8 ) << fBoundaryProcs[Detection] << G4endl;
	if( fBoundaryProcs[EtchedAirReflection] > 0 )
		G4cout << "\tEtched Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedAirReflection] << G4endl;
	if( fBoundaryProcs[EtchedLumirrorAirReflection] > 0 )
		G4cout << "\tEtched Lumirror Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedLumirrorAirReflection] << G4endl;
	if( fBoundaryProcs[EtchedLumirrorGlueReflection] > 0 )
		G4cout << "\tEtched Lumirror Glue reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedLumirrorGlueReflection] << G4endl;
	if( fBoundaryProcs[EtchedTeflonAirReflection] > 0 )
		G4cout << "\tEtched Teflon Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedTeflonAirReflection] << G4endl;
	if( fBoundaryProcs[EtchedTiOAirReflection] > 0 )
		G4cout << "\tEtched TiO Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedTiOAirReflection] << G4endl;
	if( fBoundaryProcs[EtchedTyvekAirReflection] > 0 )
		G4cout << "\tEtched Tyvek Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedTyvekAirReflection] << G4endl;
	if( fBoundaryProcs[EtchedVM2000AirReflection] > 0 )
		G4cout << "\tEtched VM2000 Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedVM2000AirReflection] << G4endl;
	if( fBoundaryProcs[EtchedVM2000GlueReflection] > 0 )
		G4cout << "\tEtched VM2000 Glue reflection:\t" << std::setw( 8 ) << fBoundaryProcs[EtchedVM2000GlueReflection] << G4endl;
	if( fBoundaryProcs[FresnelReflection] > 0 )
		G4cout << "\tFresnel reflection:\t" << std::setw( 8 ) << fBoundaryProcs[FresnelReflection] << G4endl;
	if( fBoundaryProcs[FresnelRefraction] > 0 )
		G4cout << "\tFresnel refraction:\t" << std::setw( 8 ) << fBoundaryProcs[FresnelRefraction] << G4endl;
	if( fBoundaryProcs[GroundAirReflection] > 0 )
		G4cout << "\tGround Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundAirReflection] << G4endl;
	if( fBoundaryProcs[GroundLumirrorAirReflection] > 0 )
		G4cout << "\tGround Lumirror Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundLumirrorAirReflection] << G4endl;
	if( fBoundaryProcs[GroundLumirrorGlueReflection] > 0 )
		G4cout << "\tGround Lumirror Glue reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundLumirrorGlueReflection] << G4endl;
	if( fBoundaryProcs[GroundTeflonAirReflection] > 0 )
		G4cout << "\tGround Teflon Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundTeflonAirReflection] << G4endl;
	if( fBoundaryProcs[GroundTiOAirReflection] > 0 )
		G4cout << "\tGround TiO Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundTiOAirReflection] << G4endl;
	if( fBoundaryProcs[GroundTyvekAirReflection] > 0 )
		G4cout << "\tGround Tyvek Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundTyvekAirReflection] << G4endl;
	if( fBoundaryProcs[GroundVM2000AirReflection] > 0 )
		G4cout << "\tGround VM2000 Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundVM2000AirReflection] << G4endl;
	if( fBoundaryProcs[GroundVM2000GlueReflection] > 0 )
		G4cout << "\tGround VM2000 Glue reflection:\t" << std::setw( 8 ) << fBoundaryProcs[GroundVM2000GlueReflection] << G4endl;
	if( fBoundaryProcs[LambertianReflection] > 0 )
		G4cout << "\tLambertian reflection:\t" << std::setw( 8 ) << fBoundaryProcs[LambertianReflection] << G4endl;
	if( fBoundaryProcs[LobeReflection] > 0 )
		G4cout << "\tLobe reflection:\t" << std::setw( 8 ) << fBoundaryProcs[LobeReflection] << G4endl;
	if( fBoundaryProcs[NoRINDEX] > 0 )
		G4cout << "\tNo RINDEX:\t" << std::setw( 8 ) << fBoundaryProcs[NoRINDEX] << G4endl;
	if( fBoundaryProcs[NotAtBoundary] > 0 )
		G4cout << "\tNot at boundary:\t" << std::setw( 8 ) << fBoundaryProcs[NotAtBoundary] << G4endl;
	if( fBoundaryProcs[PolishedAirReflection] > 0 )
		G4cout << "\tPolished Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedAirReflection] << G4endl;
	if( fBoundaryProcs[PolishedLumirrorAirReflection] > 0 )
		G4cout << "\tPolished Lumirror Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedLumirrorAirReflection] << G4endl;
	if( fBoundaryProcs[PolishedLumirrorGlueReflection] > 0 )
		G4cout << "\tPolished Lumirror Glue reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedLumirrorGlueReflection] << G4endl;
	if( fBoundaryProcs[PolishedTeflonAirReflection] > 0 )
		G4cout << "\tPolished Teflon Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedTeflonAirReflection] << G4endl;
	if( fBoundaryProcs[PolishedTiOAirReflection] > 0 )
		G4cout << "\tPolished TiO Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedTiOAirReflection] << G4endl;
	if( fBoundaryProcs[PolishedTyvekAirReflection] > 0 )
		G4cout << "\tPolished Tyvek Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedTyvekAirReflection] << G4endl;
	if( fBoundaryProcs[PolishedVM2000AirReflection] > 0 )
		G4cout << "\tPolished VM2000 Air reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedVM2000AirReflection] << G4endl;
	if( fBoundaryProcs[PolishedVM2000GlueReflection] > 0 )
		G4cout << "\tPolished VM2000 Glue reflection:\t" << std::setw( 8 ) << fBoundaryProcs[PolishedVM2000GlueReflection] << G4endl;
	if( fBoundaryProcs[SameMaterial] > 0 )
		G4cout << "\tSame material:\t" << std::setw( 8 ) << fBoundaryProcs[SameMaterial] << G4endl;
	if( fBoundaryProcs[SpikeReflection] > 0 )
		G4cout << "\tSpike reflection:\t" << std::setw( 8 ) << fBoundaryProcs[SpikeReflection] << G4endl;
	if( fBoundaryProcs[StepTooSmall] > 0 )
		G4cout << "\tStep too small:\t" << std::setw( 8 ) << fBoundaryProcs[StepTooSmall] << G4endl;
	if( fBoundaryProcs[TotalInternalReflection] > 0 )
		G4cout << "\tTotal internal reflection:\t" << std::setw( 8 ) << fBoundaryProcs[TotalInternalReflection] << G4endl;
	if( fBoundaryProcs[Transmission] > 0 )
		G4cout << "\tTransmission:\t" << std::setw( 8 ) << fBoundaryProcs[Transmission] << G4endl;
	//	...	inform user

}	//	end EndOfRun()