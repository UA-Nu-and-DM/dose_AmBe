#include "ExN03RunAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

#include <vector>


#include <TFile.h>
#include <TTree.h>
#include <TString.h>


ExN03RunAction::ExN03RunAction()
{
 out = new TFile("out.hist","RECREATE");

 t = new TTree("t","tree");
 
 // t->Branch("particle_name",&particle_name,"particle_name/S");
 t->Branch("particle_pdg_id",&particle_pdg_id,"particle_pdg_id/I");
 t->Branch("particle_costheta",&particle_costheta,"particle_costheta/D");
 t->Branch("particle_ke",&particle_ke,"particle_ke/D");
}

void ExN03RunAction::RecordParticle(G4int idum2,G4double dum3, G4double dum4){
  particle_pdg_id=idum2;
  particle_ke=dum3;
  particle_costheta=dum4;
  t->Fill();
}
  

ExN03RunAction::~ExN03RunAction()
{
 out->cd();
 t->Write();
}



void ExN03RunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

}


void ExN03RunAction::EndOfRunAction(const G4Run* aRun)
{

 out->cd();
 t->Write();
 out->Close();
}
