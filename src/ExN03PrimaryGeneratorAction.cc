#include "ExN03PrimaryGeneratorAction.hh"
#include "ExN03PrimaryGeneratorMessenger.hh"
#include "ExN03DetectorConstruction.hh"
#include <math.h>
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"
#include "globals.hh"
#include "G4HEPEvtInterface.hh"
#include "G4UnitsTable.hh"
#include "G4Tubs.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"

G4VPrimaryGenerator* HEPEvt;

ExN03PrimaryGeneratorAction::ExN03PrimaryGeneratorAction(ExN03DetectorConstruction* ExN03DC):ExN03Detector(ExN03DC)
{
    HEPEvt = new G4HEPEvtInterface("generator.data");
    G4cout << "Opened generator data file " << G4endl;
}

ExN03PrimaryGeneratorAction::~ExN03PrimaryGeneratorAction()
{
    delete HEPEvt;
}

void ExN03PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{


   float unit=1*CLHEP::mm;

   float ssShieldTopVoidHeight = 0.89*unit;

   float ssShieldBottomVoidHeight = 0.25267*unit; // ssShieldInnerDia/2*tg(22.5deg) if the bore was made with 135deg point angle drill bit
   float ssShieldCentralVoidHeight = 5.11*unit-ssShieldBottomVoidHeight;
   float ssShieldHeight = 6.50*unit;


   float wShieldHeight = 4.19*unit;
   float wShieldBoreHeight = 4*unit;


   float wWireHeight = 1.8*unit;
   float wWireTop = 0.3*unit;


   float srcCoreHeight = wShieldBoreHeight-(wWireHeight-wWireTop);
   float srcCoreOffset = 0.5*wShieldHeight - (wWireHeight-wWireTop)-0.5*srcCoreHeight;





   auto srcGenOffsetZ = srcCoreOffset+0.5*ssShieldHeight-ssShieldTopVoidHeight-0.5*ssShieldCentralVoidHeight;//when source is w/o the outer W capsule


   



    auto sourcePV  = ExN03Detector->GetSrcCorePV();
    auto sourceLV = sourcePV->GetLogicalVolume();
    auto sourceS = sourceLV->GetSolid();
    auto srcCtrInCvtyCord =  G4ThreeVector(0*CLHEP::mm,0*CLHEP::mm,0*CLHEP::mm);
   

    auto source = (G4Tubs*)sourceS;
    auto rSource = source->GetOuterRadius();
    auto hSource=source->GetZHalfLength();
    auto rSourceRnd = rSource*G4UniformRand();
    auto alpha = CLHEP::twopi*G4UniformRand();   
   
    auto xRnd = rSourceRnd*std::cos(alpha);
    auto yRnd = rSourceRnd*std::sin(alpha);
    auto zRnd = hSource*(2*G4UniformRand()-1)+srcGenOffsetZ;



    G4ThreeVector position(srcCtrInCvtyCord.getX()+xRnd, srcCtrInCvtyCord.getY()+yRnd, srcCtrInCvtyCord.getZ()+zRnd);



    HEPEvt->SetParticlePosition(position);
    HEPEvt->GeneratePrimaryVertex(anEvent);
}
