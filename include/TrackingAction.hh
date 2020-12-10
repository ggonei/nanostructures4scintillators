//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	This sets up tracking of particles
//
#ifndef TrackingAction_h
#define TrackingAction_h 1

//	Geant libraries
#include <G4UserTrackingAction.hh>
#include <G4TrackingManager.hh>
#include <G4Track.hh>

//	My libraries
#include "TrackInformation.hh"


class TrackingAction: public G4UserTrackingAction{

public:
	TrackingAction(){};	//	default constructor
	virtual ~TrackingAction(){};	//	default destructor

	virtual void PreUserTrackingAction( const G4Track * );	//	actions before tracking
	virtual void PostUserTrackingAction( const G4Track * );	//	actions after tracking

};	//	end TrackingAction{}
#endif