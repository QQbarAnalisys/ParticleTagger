//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 19 12:03:47 2018 by ROOT version 6.11/01
// from TTree Stats/My vertex tree!
// found on file: pid_s5.root
//////////////////////////////////////////////////////////

#ifndef CalculateParameters_h
#define CalculateParameters_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <TH1.h>
#include <TF1.h>
#include <vector>
#include <TString.h>
#include <TLegend.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include "style/Style.C"
#include "style/Labels.C"

// Header file for the classes stored in the TTree if any.

class CalculateParameters {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nParticles;
   Int_t           tpcHits[98];   //[nParticles]
   Float_t         costheta[98];   //[nParticles]
   Float_t         theta[98];   //[nParticles]
   Float_t         momentum[98];   //[nParticles]
   Int_t           type[98];   //[nParticles]
   Int_t           tagType[98];   //[nParticles]
   Int_t           type_algo0[98];   //[nParticles]
   Int_t           type_algo1[98];   //[nParticles]
   Int_t           type_algo2[98];   //[nParticles]
   Int_t           type_algo3[98];   //[nParticles]
   Int_t           type_algo4[98];   //[nParticles]
   Float_t         likelihood_algo0[98];   //[nParticles]
   Float_t         likelihood_algo1[98];   //[nParticles]
   Float_t         likelihood_algo2[98];   //[nParticles]
   Float_t         likelihood_algo3[98];   //[nParticles]
   Float_t         likelihood_algo4[98];   //[nParticles]
   /*   Float_t         TOFFirstHit[98];   //[nParticles]
   Float_t         TOFClosestHits[98];   //[nParticles]
   Float_t         TOFClosestHitsError[98];   //[nParticles]
   Float_t         TOFFlightLength[98];   //[nParticles]
   Float_t         TOFLastTrkHit[98];   //[nParticles]
   Float_t         TOFLastTrkHitFlightLength[98];   //[nParticles]*/
   Int_t           vtxType[98];   //[nParticles]
   Int_t           trueType[98];   //[nParticles]
   Float_t         dEdx[98];   //[nParticles]

   // List of branches
   TBranch        *b_nParticles;   //!
   TBranch        *b_tpcHits;   //!
   TBranch        *b_costheta;   //!
   TBranch        *b_theta;   //!
   TBranch        *b_momentum;   //!
   TBranch        *b_type;   //!
   TBranch        *b_tagType;   //!
   TBranch        *b_type_algo0;   //!
   TBranch        *b_type_algo1;   //!
   TBranch        *b_type_algo2;   //!
   TBranch        *b_type_algo3;   //!
   TBranch        *b_type_algo4;   //!
   TBranch        *b_likelihood_algo0;   //!
   TBranch        *b_likelihood_algo1;   //!
   TBranch        *b_likelihood_algo2;   //!
   TBranch        *b_likelihood_algo3;   //!
   TBranch        *b_likelihood_algo4;   //!
   /*   TBranch        *b_TOFFirstHit;   //!
   TBranch        *b_TOFClosestHits;   //!
   TBranch        *b_TOFClosestHitsError;   //!
   TBranch        *b_TOFFlightLength;   //!
   TBranch        *b_TOFLastTrkHit;   //!
   TBranch        *b_TOFLastTrkHitFlightLength;   //!*/
   TBranch        *b_vtxType;   //!
   TBranch        *b_trueType;   //!
   TBranch        *b_dEdx;   //!

   CalculateParameters(TTree *tree=0);
   virtual ~CalculateParameters();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Parameters(bool,float);
   virtual void     Initialize();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

 private:
     
  TH2F *kaon_dEdx_truth;
  TH2F *proton_dEdx_truth;
  TH2F *pion_dEdx_truth;
  /*
  TH2F *kaon_TOFFirstHit_truth;
  TH2F *proton_TOFFirstHit_truth;
  TH2F *pion_TOFFirstHit_truth;

  TH2F *kaon_TOFClosestHits_truth;
  TH2F *proton_TOFClosestHits_truth;
  TH2F *pion_TOFClosestHits_truth;

  TH2F *kaon_TOFFlightLength_truth;
  TH2F *proton_TOFFlightLength_truth;
  TH2F *pion_TOFFlightLength_truth;

  TH2F *kaon_TOFLastTrkHit_truth;
  TH2F *proton_TOFLastTrkHit_truth;
  TH2F *pion_TOFLastTrkHit_truth;

  TH2F *kaon_TOFLastTrkHitFlightLength_truth;
  TH2F *proton_TOFLastTrkHitFlightLength_truth;
  TH2F *pion_TOFLastTrkHitFlightLength_truth;
  */

};

#endif

#ifdef CalculateParameters_cxx
CalculateParameters::CalculateParameters(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("pid.root");//p/home/irles/WorkArea/BBbar_tests/ntuples/kaontagger/pid_eL_s5_10107.root");//pid_eL_s5_valencia1.4.root");
      if (!f || !f->IsOpen()) {
	f = new TFile("pid.root");//p/home/irles/WorkArea/BBbar_tests/ntuples/kaontagger/pid_eL_s5_10107.root");//pid_eL_s5_valencia1.4.root");
	
      }
      f->GetObject("Stats",tree);

   }
   Init(tree);
}

CalculateParameters::~CalculateParameters()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t CalculateParameters::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t CalculateParameters::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void CalculateParameters::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);
   fChain->SetBranchAddress("nParticles", &nParticles, &b_nParticles);
   fChain->SetBranchAddress("tpcHits", tpcHits, &b_tpcHits);
   fChain->SetBranchAddress("costheta", costheta, &b_costheta);
   fChain->SetBranchAddress("theta", theta, &b_theta);
   fChain->SetBranchAddress("momentum", momentum, &b_momentum);
   fChain->SetBranchAddress("type", type, &b_type);
   fChain->SetBranchAddress("tagType", tagType, &b_tagType);
   fChain->SetBranchAddress("type_algo0", type_algo0, &b_type_algo0);
   fChain->SetBranchAddress("type_algo1", type_algo1, &b_type_algo1);
   fChain->SetBranchAddress("type_algo2", type_algo2, &b_type_algo2);
   fChain->SetBranchAddress("type_algo3", type_algo3, &b_type_algo3);
   fChain->SetBranchAddress("type_algo4", type_algo4, &b_type_algo4);
   fChain->SetBranchAddress("likelihood_algo0", likelihood_algo0, &b_likelihood_algo0);
   fChain->SetBranchAddress("likelihood_algo1", likelihood_algo1, &b_likelihood_algo1);
   fChain->SetBranchAddress("likelihood_algo2", likelihood_algo2, &b_likelihood_algo2);
   fChain->SetBranchAddress("likelihood_algo3", likelihood_algo3, &b_likelihood_algo3);
   fChain->SetBranchAddress("likelihood_algo4", likelihood_algo4, &b_likelihood_algo4);
   /*   fChain->SetBranchAddress("TOFFirstHit", TOFFirstHit, &b_TOFFirstHit);
   fChain->SetBranchAddress("TOFClosestHits", TOFClosestHits, &b_TOFClosestHits);
   fChain->SetBranchAddress("TOFClosestHitsError", TOFClosestHitsError, &b_TOFClosestHitsError);
   fChain->SetBranchAddress("TOFFlightLength", TOFFlightLength, &b_TOFFlightLength);
   fChain->SetBranchAddress("TOFLastTrkHit", TOFLastTrkHit, &b_TOFLastTrkHit);
   fChain->SetBranchAddress("TOFLastTrkHitFlightLength", TOFLastTrkHitFlightLength, &b_TOFLastTrkHitFlightLength);*/
   fChain->SetBranchAddress("vtxType", vtxType, &b_vtxType);
   fChain->SetBranchAddress("trueType", trueType, &b_trueType);
   fChain->SetBranchAddress("dEdx", dEdx, &b_dEdx);
   Notify();
   
}

Bool_t CalculateParameters::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void CalculateParameters::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t CalculateParameters::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef CalculateParameters_cxx
