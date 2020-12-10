//
//	George O'Neill, University of York 2020
//
#include "TrackingAction.hh"


void TrackingAction::PreUserTrackingAction( const G4Track *aTrack ){

	TrackInformation *trackInfo = (TrackInformation *)( aTrack->GetUserInformation() );	//	create trajectory

	if( !trackInfo ){	//	if track does not exist

		trackInfo = new TrackInformation();	//	make a new track
		trackInfo->SetIsFirstCrystalX( true );	//	set as in region before sending to aTrack
		aTrack->SetUserInformation( trackInfo );	//	inform program of track

	}

	trackInfo->SetIsFirstCrystalX( true );	//	set in region

}	//	end PreUserTrackingAction( G4Track* )


void TrackingAction::PostUserTrackingAction( const G4Track *aTrack ){

	G4TrackVector *secondaries = fpTrackingManager->GimmeSecondaries();	//	get the created particles
	size_t nSeco = 0;	//	initialise nSeco

	if( secondaries )
		nSeco = secondaries->size();	//	get number of secondary particles

	if( nSeco > 0 ){	//	if there are secondary created particles

		TrackInformation *info = (TrackInformation *)( aTrack->GetUserInformation() );	//	get track information

		for( size_t i = 0; i < nSeco; i++ ){	//	for each particle

			TrackInformation *infoNew = new TrackInformation( info );	//	create new track information from existing aTrack
			( *secondaries )[i]->SetUserInformation( infoNew );	//	inform program of secondary

		}	//	end for each particle

	}	//	end secondary particle steps

}	//	end PostUserTrackingAction( G4Track* )