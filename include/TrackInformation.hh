//
//	George O'Neill, University of York 2020
//
//  Make a basic cube that allows for addition of photonic objects
//
//	This contains information on the steps
//
#ifndef TrackInformation_h
#define TrackInformation_h 1

//	Geant libraries
#include <G4Allocator.hh>
#include <G4ios.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>    
#include <G4ThreeVector.hh>
#include <G4Track.hh>
#include <G4VUserTrackInformation.hh>
#include <globals.hh>


class TrackInformation: public G4VUserTrackInformation{

public:
	TrackInformation(): G4VUserTrackInformation(){
		fFirstCrystalX = true;
	};	//	default constructor
	TrackInformation( const TrackInformation *aTrackInfo ): G4VUserTrackInformation(){
		fFirstCrystalX = aTrackInfo->fFirstCrystalX;
	};	//	constructor with track information
	~TrackInformation(){};	//	default destructor

	inline void *operator new( size_t );	//	reference to overload operator new
	inline void operator delete( void *aTrackInfo );	//	reference to overload operator delete
	TrackInformation &operator =( const TrackInformation &aTrackInfo ){
		fFirstCrystalX = aTrackInfo.fFirstCrystalX; return *this;
	};	//	overload operator =
	void SetSourceTrackInformation(){
		fFirstCrystalX = true;
	};	//	inform where to fetch track information from
	virtual void Print() const{
		G4cout << "first time track incident on X: " << fFirstCrystalX << G4endl;
	};	//	print track information
	inline G4bool GetIsFirstCrystalX() const{	//	fetch first crystal flag
		return fFirstCrystalX;
	}
	inline void SetIsFirstCrystalX( G4bool b ){	//	set firstcrystal flag
		fFirstCrystalX = b;
	}


private:
	G4bool fFirstCrystalX;	//	first crystal flag

};	//	end TrackInformation


extern G4ThreadLocal	//	work on correct thread
G4Allocator<TrackInformation> *TIAllocator;	//	define allocator


inline void *TrackInformation::operator new( size_t ){	//	overload new operator for track information

	if( !TIAllocator )	//	if there is no allocator
		TIAllocator = new G4Allocator<TrackInformation>;	//	then make one

	return (void *)TIAllocator->MallocSingle();	//	allocate memory for new allocator

}	//	end operator new


inline void TrackInformation::operator delete( void *aTrackInfo ){	//	overload delete operator for track information

	TIAllocator->FreeSingle( (TrackInformation *)aTrackInfo );	//	release allocator memory

}	//	end operator delete
#endif