//
//	George O'Neill, University of York 2020
//
#include "PrimaryGeneratorAction.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction(), fParticleGun( 0 ){	//	default constructor

	G4int n_particle = 1;	//	number of particles
	fParticleGun = new G4ParticleGun( n_particle );	//	create a new gun for this many particles
	fGunMessenger = new PrimaryGeneratorMessenger( this );	//	create a corresponding messenger
	fParticleGun->SetParticleDefinition( G4ParticleTable::GetParticleTable()->FindParticle( "e+" ) );	//	set particle type
	fParticleGun->SetParticleTime( 0.0 * ns );	//	set initial particle time
	fParticleGun->SetParticlePosition( G4ThreeVector( 0.0 * cm, 0.0 * cm, 0.0 * cm ) );	//	put particle at origin
	fParticleGun->SetParticleMomentumDirection( G4ThreeVector( 1., 0., 0. ) );	//	give particle momentum-x
	fParticleGun->SetParticleEnergy( 500.0 * keV );	//	give particle initial energy

}	//	end default constructor


PrimaryGeneratorAction::~PrimaryGeneratorAction(){	//	clean up commands

	delete fParticleGun;
	delete fGunMessenger;

}	//	end destructor


void PrimaryGeneratorAction::GeneratePrimaries( G4Event *anEvent ){	//	create main particles

	fParticleGun->GeneratePrimaryVertex( anEvent );	//	fire event

}	//	end GeneratePrimaries( G4Event )


void PrimaryGeneratorAction::SetOptPhotonPolar(){	//	add polarisation to photons

	if( fParticleGun->GetParticleDefinition()->GetParticleName() != "opticalphoton" ){	//	if particle is not a photon

		G4cout << "*** WARNING *** Polarising a non-photon...exiting function" << G4endl;	//	inform user
		return;	//	exit gracefully

	}	//	end particle type check

	G4double angle = G4UniformRand() * 360.0 * deg;	//	get a random angle
	G4ThreeVector normal( 1., 0., 0. );	//	x focused vector
	G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();	//	get particle momentum
	G4ThreeVector product = normal.cross( kphoton );	//	get resultant momentum-x for photon
	G4double modul2 = product * product;	//	remove direction
	G4ThreeVector e_perpend( 0., 0., 1. );	//	initialise a vector
	if( modul2 > 0. )	//	if momentum-x is positive as it should be
		e_perpend = ( 1. / std::sqrt( modul2 ) ) * product;	//	use it to get the perpendicular vector
	G4ThreeVector e_paralle = e_perpend.cross( kphoton );	//	get a parallel vector to our original photon
	fParticleGun->SetParticlePolarization( std::cos( angle ) * e_paralle + std::sin( angle ) * e_perpend );	//	set particle polarisation in polar coordinates

}	//	end SetOptPhotonPolar()