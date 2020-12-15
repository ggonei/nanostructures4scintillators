//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	This controls the event making process
//
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

//	Geant libraries
#include <globals.hh>
#include <Randomize.hh>
#include <G4Event.hh>
#include <G4ParticleDefinition.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <G4VUserPrimaryGeneratorAction.hh>

//	My libraries
#include "PrimaryGeneratorMessenger.hh"

//class G4Event;
class PrimaryGeneratorMessenger;
class PrimaryGeneratorAction: public G4VUserPrimaryGeneratorAction{

public:
	PrimaryGeneratorAction();	//	default constructor
	virtual ~PrimaryGeneratorAction();	//	default destructor

	virtual void GeneratePrimaries( G4Event * );	//	make sure correct function calls to generate particles

	G4ParticleGun *GetParticleGun(){	//	return gun to code

		return fParticleGun;	//	particle firer

	};	//	end *GetParticleGun()

	void SetOptPhotonPolar();	//	polarise photons


private:
	G4ParticleGun *fParticleGun;	//	particle firer
	PrimaryGeneratorMessenger *fGunMessenger;	//	understand gun

};	//	end PrimaryGeneratorAction
#endif