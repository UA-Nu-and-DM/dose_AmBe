#include "ExN03EventAction.hh"

#include "ExN03RunAction.hh"

#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4VTrajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>




ExN03EventAction::ExN03EventAction(ExN03RunAction* run)
{

}


ExN03EventAction::~ExN03EventAction()
{
}


void ExN03EventAction::BeginOfEventAction(const G4Event* evt)
{
 G4int evtn = evt->GetEventID();
 
 // if(!(evtn%10000)) G4cout<<"EventID: "<<evtn<<G4endl;
 
 /* ECyl = 0;
 Evol.clear();
 for(int i=0;i<4;++i) {//for every hole 
  for(int j=0;j<3;++j)//for every module = {air_hole,stainless_wall,he-3_counter}
   Evol.push_back(0);
 }//redo with enums for clarity

 procArr.clear();
 pnameArr.clear();
 EstepArr.clear();
 np=0;
 for(int i=0;i<3;++i)
  x0[i]=0;
 E0=0;
 */


}

void ExN03EventAction::EndOfEventAction(const G4Event* evt)
{
//  G4cout << "End of event" << G4endl;

  G4int evtn = evt->GetEventID();
  //  G4int nsec = (G4int)pnameArr.size();
  /*
   for(int i=0;i<nsec;++i) 
    if( (!strcmp(pnameArr.at(i),"triton"))&&(!strcmp(procArr.at(i),"NeutronInelastic"))) {
     np=1;
     break;
    };
 
  runAct->fillPerEvent(ECyl, Evol, evtn, procArr,pnameArr,EstepArr,np,x0,E0,nsec);
  */
}  

