
#ifndef ExN03DetectorConstruction_h
#define ExN03DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


//class G4Tubs;
class G4LogicalVolume;
class G4VPhysicalVolume;
/*
//keele
class G4Box;

*/

class ExN03DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    ExN03DetectorConstruction();
   ~ExN03DetectorConstruction();

  public:
     
  
     
     G4VPhysicalVolume* Construct();
         
     G4double GetWorldSize() {return worldsize;};
    


     G4VPhysicalVolume* GetSSShieldPV() const; //added for LZ AmBe source
     G4VPhysicalVolume* GetWShieldPV() const; //added for LZ AmBe source
     G4VPhysicalVolume* GetSrcCorePV() const; //added for LZ AmBe source
     G4VPhysicalVolume* GetwCapsuleBasePV() const; //added for LZ AmBe source 
     G4VPhysicalVolume* GetwCapsuleCapPV() const; //added for LZ AmBe source 

  private:
  G4VPhysicalVolume *world_phys, *source_phys, *innercapsule_phys, *middlecapsule_phys, *outercapsule_phys, *waterslug_phys,*tissueslug_phys, *safe_phys, *pet_phys, *liner_phys, *air_phys, *outercapsule1_phys, *outercapsule2_phys, *outercapsule3_phys; 


     G4VPhysicalVolume * ssShield_phys;//added for LZ AmBe src
     G4VPhysicalVolume * wShield_phys;//added for LZ AmBe src
     G4VPhysicalVolume * ssShieldLid_phys;//added for LZ AmBe src
     G4VPhysicalVolume * wShieldLid_phys;//added for LZ AmBe src
     G4VPhysicalVolume * srcCore_phys;//added for LZ AmBe src
     G4VPhysicalVolume * wCapsuleBase_phys;//added for LZ AmBe src
     G4VPhysicalVolume * wCapsuleCap_phys;//added for LZ AmBe src

  //  G4VPhysicalVolume *holes_phys[4], *tubes_phys[4], *counters_phys[4], *cylinder_phys, *box_phys, *crete_phys1a, *crete_phys1b, *crete_phys2a, *crete_phys2b, *crete_phys3;
          G4double worldsize;

          G4VPhysicalVolume* ConstructCounter();     
};

inline G4VPhysicalVolume* ExN03DetectorConstruction::GetSSShieldPV() const {
     return ssShield_phys;     //added for AmBe
}

inline G4VPhysicalVolume* ExN03DetectorConstruction::GetWShieldPV() const {
     return wShield_phys;     //added for AmBe
}

inline G4VPhysicalVolume* ExN03DetectorConstruction::GetSrcCorePV() const {
     return srcCore_phys;     //added for AmBe
}

inline G4VPhysicalVolume* ExN03DetectorConstruction::GetwCapsuleBasePV() const {
     return wCapsuleBase_phys;     //added for AmBe

}

inline G4VPhysicalVolume* ExN03DetectorConstruction::GetwCapsuleCapPV() const {
     return wCapsuleCap_phys;     //added for AmBe

}
#endif

