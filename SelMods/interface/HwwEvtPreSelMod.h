//--------------------------------------------------------------------------------------------------
// $Id: HwwEvtPreSelMod.h,v 1.2 2008/11/28 13:40:17 loizides Exp $
//
// HwwEvtSelMod
//
// A module for pre-selection of H->WW events. Apply very loose cuts in order to reduce the 
// number of irrelevent events that we have to process.
//
// Authors: S.Xie, C.Loizides
//--------------------------------------------------------------------------------------------------

#ifndef MITPHYSICS_MODS_HWWEVTPRESELMOD_H
#define MITPHYSICS_MODS_HWWEVTPRESELMOD_H

#include "MitAna/TreeMod/interface/BaseMod.h" 
#include "MitAna/DataTree/interface/Collections.h"

namespace mithep 
{
  class HwwEvtPreSelMod : public BaseMod
  {
    public:
      HwwEvtPreSelMod(const char *name="HwwEvtPreSelMod", 
                      const char *title="Pre-selection module for HWW analysis");
      ~HwwEvtPreSelMod() {}

      const char        *GetMuonName()       const { return fMuonName;       }
      const char        *GetElectronName()   const { return fElectronName;   }
      Int_t              GetNLeptons()       const { return fNLeptonsMin;    }
      Double_t           GetLeptonMinPt()    const { return fLeptonMinPt;    }
      Double_t           GetLeptonMinMaxPt() const { return fLeptonMinMaxPt; }
      Bool_t             GetLoadBranch()     const { return fLoadBranch;     }
      void               SetMuonName(const char *name)     { fMuonName      = name; }
      void               SetElectronName(const char *name) { fElectronName  = name; }
      void               SetNLeptons(Int_t n)              { fNLeptonsMin   = n;    }
      void               SetLeptonMinPt(Double_t pt)       { fLeptonMinPt   = pt;   }
      void               SetLeptonMinMaxPt(Double_t pt)    { fLeptonMinMaxPt= pt;   }
      void               SetLoadBranch(Bool_t b)           { fLoadBranch = b;       }

    protected:
      TString            fMuonName;             //name of muon collection
      TString            fElectronName;         //name of electron collection
      Int_t              fNLeptonsMin;          //minimum number of leptons (def=2)
      Double_t           fLeptonMinPt;          //minimum pt required (def=5GeV)
      Double_t           fLeptonMinMaxPt;       //minimum pt for max lepton pt (def=20GeV)
      Bool_t             fLoadBranch;           //=true then load collections from branch
      const MuonCol     *fMuons;                //!muon branch
      const ElectronCol *fElectrons;            //!electron branch

      void               Process();
      void               SlaveBegin();
      void               SlaveTerminate();

      ClassDef(HwwEvtPreSelMod,1) // Pre-selection module for HWW analysis
  };
}
#endif
