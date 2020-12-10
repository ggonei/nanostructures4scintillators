//
//	George O'Neill, University of York 2020
//
#include "HistoManager.hh"


void HistoManager::Book(){	//	create histograms

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();	//	fetch this analysis manager
	analysisManager->SetFileName( fFileName );	//	set filename root
	analysisManager->SetVerboseLevel( VERBOSE );	//	set verbosity
	analysisManager->SetActivation( true );    // enable inactivation of histograms
	G4int nbins = 100;	//	default histogram bins
	G4double vmin = 0.;	//	default histogram minimum
	G4double vmax = 100.;	//	default histogram maximum
	G4String id[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9","10","11","12","13" };	//	histogram indices
	G4String title[] = {	//	histogram titles
		"dummy",                                        // 0
		"Cerenkov spectrum",                            // 1
		"scintillation spectrum",                       // 2
		"boundary process status",                      // 3
		"X momentum dir of backward-going photons",     // 4
		"Y momentum dir of backward-going photons",     // 5
		"Z momentum dir of backward-going photons",     // 6
		"X momentum dir of forward-going photons",      // 7
		"Y momentum dir of forward-going photons",      // 8
		"Z momentum dir of forward-going photons",      // 9
		"X momentum dir of Fresnel-refracted photons",  //10
		"Y momentum dir of Fresnel-refracted photons",  //11
		"Z momentum dir of Fresnel-refracted photons",  //12
		"scintillation photons creation time",          //13
	};
	G4int nHists = sizeof( id ) / sizeof( id[0] );	//	number of histograms

	if( nHists != sizeof( title ) / sizeof( title[0] ) )	//	check histogram numbers
		G4cout << "Different number of histogram IDs to histogram titles" << G4endl;	//	inform user

	for( G4int k = 0; k < nHists; ++k ){	//	loop over histograms

		G4int ih = analysisManager->CreateH1( id[k], title[k], nbins, vmin, vmax );	//	create a histogram
		analysisManager->SetH1Activation( ih, false );	//	create histogram as inactivated

	}	//	end loop over histograms

}	//	end Book()