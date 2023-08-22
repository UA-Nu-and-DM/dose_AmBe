#include "ExN03SteppingAction.hh"

#include "ExN03DetectorConstruction.hh"
#include "ExN03EventAction.hh"
#include "ExN03RunAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4TrackVector.hh"

//#include "ExN03.hh"

ExN03RunAction *info;

ExN03SteppingAction::ExN03SteppingAction(ExN03DetectorConstruction* det,
                                         ExN03EventAction* evt)
:detector(det), eventaction(evt)					 
{ }



ExN03SteppingAction::~ExN03SteppingAction()
{ }



void ExN03SteppingAction::UserSteppingAction(const G4Step* aStep)
{
  G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  //removed "const" from before the following line in an attempt to fix errors
  G4Track* track = aStep->GetTrack();
  const G4VProcess* pr = track->GetCreatorProcess();
 
  G4String pN = track->GetDefinition()->GetParticleName();
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep > 0){
  G4double xdep=track->GetVertexPosition().x()/CLHEP::cm;
  G4double ydep=track->GetVertexPosition().y()/CLHEP::cm;
  G4double zdep=track->GetVertexPosition().z()/CLHEP::cm;
  if(volume->GetName() == "tissueslug__phys"){
  G4cout << edep/CLHEP::keV << " " << xdep << " " << ydep << " " << zdep << " " << pN << G4endl;
}
}
/* comment out info on primary particle
  if(track->GetParentID()==0) {//primary
   if(track->GetCurrentStepNumber()==1) {
    G4double nke= (track->GetVertexKineticEnergy())/CLHEP::MeV;
  G4double xn=track->GetVertexPosition().x()/CLHEP::cm;
  G4double yn=track->GetVertexPosition().y()/CLHEP::cm;
  G4double zn=track->GetVertexPosition().z()/CLHEP::cm;
  G4cout << "Primary particle energy,vertex, and volume: " << nke << " " << xn << " " << yn << " " << zn << " " << volume->GetName() << G4endl;
    //    eventaction->SetE0(E0);
   }
}
*/
}


