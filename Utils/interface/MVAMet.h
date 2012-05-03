//--------------------------------------------------------------------------------------------------
// $Id $
//
// Met Regression
//
// Authors: P. Harris
//--------------------------------------------------------------------------------------------------

#ifndef MITPHYSICS_UTILS_MVAMet_H
#define MITPHYSICS_UTILS_MVAMet_H
#include <TMatrixD.h>
#include "MitAna/DataTree/interface/PFJetFwd.h"
#include "MitAna/DataTree/interface/VertexFwd.h"
#include "MitAna/DataTree/interface/TrackFwd.h"
#include "MitAna/DataTree/interface/Met.h"
#include "MitAna/DataTree/interface/PFMet.h"
#include "MitAna/DataTree/interface/PFMetCol.h"
#include "MitAna/DataTree/interface/PFJet.h"
#include "MitAna/DataTree/interface/PFJetCol.h"
#include "MitAna/DataTree/interface/PFCandidateCol.h"
#include "MitAna/DataTree/interface/PileupEnergyDensityCol.h"
#include "MitCommon/MathTools/interface/MathUtils.h"

#include "MitPhysics/Utils/interface/RecoilTools.h"
#include "CondFormats/EgammaObjects/interface/GBRForest.h"

class TRandom3;
class GBRForest;

namespace mithep {
  class MVAMet {
  public:
    MVAMet();
    ~MVAMet();
    enum MVAType {
      kBaseline = 0
    };

    //void    setVariables(TMVA::Reader *iReader,bool iScale);
    //void    Initialize( TString iU1MethodName="U1MVA",
    //                    TString iPhiMethodName="PhiMVA",
    //			TString iJetMVAFile="$CMSSW_BASE/src/MitPhysics/data/mva_RecoilPhiRegress_baseline.weights.xml",
    //			TString iU1Weights="$CMSSW_BASE/src/MitPhysics/data/mva_RecoilRegress_baseline.weights.xml",
    //			TString iPhiWeights="$CMSSW_BASE/src/MitPhysics/data/mva_JetID.weights.xml", 
    //			MVAType iType=kBaseline);
    void    Initialize( 
		       TString iJetLowPtFile ="$CMSSW_BASE/src/MitPhysics/data/mva_RecoilPhiRegress_baseline.weights.xml",
		       TString iJetHighPtFile="$CMSSW_BASE/src/MitPhysics/data/mva_RecoilPhiRegress_baseline.weights.xml",
		       TString iJetCutFile   ="$CMSSW_BASE/src/MitPhysics/data/mva_RecoilPhiRegress_baseline.weights.xml",
		       TString iU1Weights    ="$CMSSW_BASE/src/MitPhysics/data/gbrmet.root",
		       TString iPhiWeights   ="$CMSSW_BASE/src/MitPhysics/data/gbrmetphi.root",
		       TString iCovU1Weights   ="$CMSSW_BASE/src/MitPhysics/data/gbrcovu1_52.root",
		       TString iCovU2Weights   ="$CMSSW_BASE/src/MitPhysics/data/gbrcovu2_52.root",
		       MVAMet::MVAType  iType=kBaseline);
        
    Bool_t   IsInitialized() const { return fIsInitialized; }
    Double_t evaluatePhi();
    Double_t evaluateU1();
    Double_t evaluateCovU1();
    Double_t evaluateCovU2();
    Double_t MVAValue(  bool iPhi,
			Float_t iPFSumEt, 
			Float_t iU      ,
			Float_t iUPhi   ,
			Float_t iTKSumEt,
			Float_t iTKU    ,
			Float_t iTKUPhi ,
			Float_t iNPSumEt,
			Float_t iNPU    ,
			Float_t iNPUPhi ,
			Float_t iPUSumEt,
			Float_t iPUMet  ,
			Float_t iPUMetPhi,
			Float_t iPCSumEt,
			Float_t iPCU    ,
			Float_t iPCUPhi ,
			Float_t iJSPt1  ,
			Float_t iJSEta1 ,
			Float_t iJSPhi1 ,
			Float_t iJSPt2  ,
			Float_t iJSEta2 ,
			Float_t iJSPhi2 ,
			Float_t iNJet   ,
			Float_t iNAllJet,
			Float_t iNPV    );

    Met GetMet( 	Bool_t iPhi,Float_t iPtVis,Float_t iPhiVis,Float_t iSumEtVis,
			const PFMet            *iMet  ,
			const PFCandidateCol   *iCands,
			const Vertex *iVertex,const VertexCol *iVertices,
			const PFJetCol         *iJets ,
			FactorizedJetCorrector *iJetCorrector,
			const PileupEnergyDensityCol *iPileupEnergyDensity,
			int iNPV,
			Bool_t printDebug=false);

    Met GetMet( 	Bool_t iPhi,Float_t iPtVis,Float_t iPhiVis,Float_t iSumEtVis,
			const PFMet            *iMet  ,
			const PFCandidateCol   *iCands,
			const Vertex *iVertex,const VertexCol *iVertices,Double_t iRho,
			const PFJetCol         *iJets ,
			int iNPV,
			Bool_t printDebug=false);

    Met GetMet(	        Bool_t iPhi,
			Float_t iPt1,Float_t iPhi1,Float_t iEta1,
			Float_t iPt2,Float_t iPhi2,Float_t iEta2,
			const PFMet            *iMet  ,
			const PFCandidateCol   *iCands,
			const Vertex *iVertex,const VertexCol *iVertices,
			const PFJetCol         *iJets ,
			FactorizedJetCorrector *iJetCorrector,
			const PileupEnergyDensityCol *iPUEnergyDensity,
			int iNPV,
			Bool_t printDebug=false);

    Met GetMet(	        Bool_t iPhi,
			Float_t iPt1,Float_t iPhi1,Float_t iEta1,
			Float_t iPt2,Float_t iPhi2,Float_t iEta2,
			const PFMet            *iMet  ,
			const PFCandidateCol   *iCands,
			const Vertex *iVertex,const VertexCol *iVertices,Double_t iRho,
			const PFJetCol         *iJets ,
			int iNPV,
			Bool_t printDebug=false);

    TMatrixD*   GetMetCovariance() { return fCov;         }
    Float_t     GetSignificance () { return fSignificance;}
    Float_t     GetUncertainty  () { return fUncertainty;}
    RecoilTools *fRecoilTools;
    
  protected:
    TString      fPhiMethodName;
    TString      fU1MethodName;
    TString      fCovU1MethodName;
    TString      fCovU2MethodName;
    Bool_t       fIsInitialized;
    MVAType      fType;
    Bool_t       f42;
    
    Float_t fSumEt  ;
    Float_t fU      ;
    Float_t fUPhi   ;
    Float_t fTKSumEt;
    Float_t fTKU    ;
    Float_t fTKUPhi ;
    Float_t fNPSumEt;
    Float_t fNPU    ;
    Float_t fNPUPhi ;
    Float_t fPUSumEt;
    Float_t fPUMet  ;
    Float_t fPUMetPhi ;
    Float_t fPCSumEt;
    Float_t fPCU    ;
    Float_t fPCUPhi ;
    Float_t fJSPt1  ;
    Float_t fJSEta1 ;
    Float_t fJSPhi1 ;
    Float_t fJSPt2  ;
    Float_t fJSEta2 ;
    Float_t fJSPhi2 ;
    Float_t fNJet   ;
    Float_t fNAllJet;
    Float_t fNPV    ;
    Float_t fUPhiMVA;
    Float_t fUMVA;
    
    Float_t* fPhiVals;
    Float_t* fU1Vals;
    Float_t* fCovVals;
    
    GBRForest *fPhiReader;
    GBRForest *fU1Reader;
    GBRForest *fCovU1Reader;
    GBRForest *fCovU2Reader;

    Float_t   fSignificance;
    Float_t   fUncertainty;
    TMatrixD *fCov;

    //TMVA::Reader* fPhiReader;
    //TMVA::Reader* fU1Reader;
    ClassDef(MVAMet,0)
  };
}
#endif
