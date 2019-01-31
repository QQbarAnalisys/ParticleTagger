//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Nov 19 12:03:47 2018 by ROOT version 6.11/01
// from TTree Stats/My vertex tree!
// found on file: pid_l5.root
//////////////////////////////////////////////////////////

#ifndef kaontagger_h
#define kaontagger_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <iostream>
#include <TH1.h>
#include <vector>
#include <TString.h>
#include <TLegend.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include "../style/Style.C"
#include "../style/Labels.C"

// Header file for the classes stored in the TTree if any.

class kaontagger {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           nParticles;
   Int_t           tpcHits[91];   //[nParticles]
   Float_t         costheta[91];   //[nParticles]
   Float_t         theta[91];   //[nParticles]
   Float_t         momentum[91];   //[nParticles]
   Int_t           type[91];   //[nParticles]
   Int_t           tagType[91];   //[nParticles]
   Int_t           type_algo0[91];   //[nParticles]
   Int_t           type_algo1[91];   //[nParticles]
   Int_t           type_algo2[91];   //[nParticles]
   Int_t           type_algo3[91];   //[nParticles]
   Int_t           type_algo4[91];   //[nParticles]
   Float_t           likelihood_algo0[91];   //[nParticles]
   Float_t           likelihood_algo1[91];   //[nParticles]
   Float_t           likelihood_algo2[91];   //[nParticles]
   Float_t           likelihood_algo3[91];   //[nParticles]
   Float_t           likelihood_algo4[91];   //[nParticles]
   Int_t           trueType[91];   //[nParticles]
   Int_t           vtxType[91];   //[nParticles]
   Float_t         dEdx[91];   //[nParticles]

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
   TBranch        *b_vtxType;   //!
   TBranch        *b_trueType;   //!
   TBranch        *b_dEdx;   //!

   kaontagger(TTree *tree=0);
   virtual ~kaontagger();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Selection(bool,int);
   virtual void     Fill_histos_new_ID(int);
   virtual void     Fill_histos_DST_ID(int,int);
   virtual void     Plots(int);
   virtual void     SimplePlot(int);
   virtual void     Initialize();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

 private:
     
  TH2F *kaon_dEdx_truth;
  TH2F *proton_dEdx_truth;
  TH2F *pion_dEdx_truth;
  TH2F *electron_dEdx_truth;
  TH2F *muon_dEdx_truth;
  TH2F *other_dEdx_truth;

  TH2F *kaon_dEdx_id;
  TH2F *proton_dEdx_id;
  TH2F *pion_dEdx_id;

  TH2F *kaon_dEdx_good;
  TH2F *proton_dEdx_good;
  TH2F *pion_dEdx_good;

  TH2F *kaon_dEdx_bad;
  TH2F *proton_dEdx_bad;
  TH2F *pion_dEdx_bad;
  
  TH2F *kaon_dEdx_ID_DST_id;
  TH2F *proton_dEdx_ID_DST_id;
  TH2F *pion_dEdx_ID_DST_id;

  TH2F *kaon_dEdx_ID_DST_good;
  TH2F *proton_dEdx_ID_DST_good;
  TH2F *pion_dEdx_ID_DST_good;

  TH2F *kaon_dEdx_ID_DST_bad;
  TH2F *proton_dEdx_ID_DST_bad;
  TH2F *pion_dEdx_ID_DST_bad;

  float n_kaon, n_pion, n_proton, n_electron, n_muon, n_other;
  float cont_pi, cont_p, cont_e, cont_mu;
  float cont_DST_pi, cont_DST_p, cont_DST_e, cont_DST_mu;

};

#endif

#ifdef kaontagger_cxx
kaontagger::kaontagger(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/ilc/yokugawa/run_preset/root_merge/ParticleTagger_out/pid_012819.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/ilc/yokugawa/run_preset/root_merge/ParticleTagger_out/pid_012819.root");
      }
      f->GetObject("Stats",tree);

   }
   Init(tree);
}

kaontagger::~kaontagger()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t kaontagger::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t kaontagger::LoadTree(Long64_t entry)
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

void kaontagger::Init(TTree *tree)
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
   fChain->SetBranchAddress("vtxType", vtxType, &b_vtxType);
   fChain->SetBranchAddress("trueType", trueType, &b_trueType);
   fChain->SetBranchAddress("dEdx", dEdx, &b_dEdx);
   Notify();
}

Bool_t kaontagger::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void kaontagger::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t kaontagger::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef kaontagger_cxx
