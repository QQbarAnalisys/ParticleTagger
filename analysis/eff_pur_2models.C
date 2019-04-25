#include <TPaveStats.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TString.h>
#include <iostream>
#include <TFitResult.h>
#include <TF1.h>
#include <TSpectrum.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TH1.h"
#include "TF1.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TMath.h"
#include "TSystemFile.h"
#include "style/Style.C"
#include "style/Labels.C"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TLegend.h"


void eff_pur_2models() {
      
  TFile *f = new TFile("eff_pur_l5_valencia1.4.root");
  TGraphErrors *eff_pur_l5 = (TGraphErrors*)f->Get("eff_purity");
  eff_pur_l5->SetName("eff_pur_l5");
  
  // ------------------------------------------------------
  TFile *f2 = new TFile("eff_pur_s5_valencia1.4.root");
  TGraphErrors *eff_pur_s5 = (TGraphErrors*)f2->Get("eff_purity");
  eff_pur_s5->SetName("eff_pur_s5");

  f = new TFile("eff_pur_l5_ttbar.root");
  TGraphErrors *eff_pur_l5_ttbar = (TGraphErrors*)f->Get("eff_purity");
  eff_pur_l5_ttbar->SetName("eff_pur_l5_ttbar");

  // ------------------------------------------------------
  f2 = new TFile("eff_pur_s5_ttbar.root");
  TGraphErrors *eff_pur_s5_ttbar = (TGraphErrors*)f2->Get("eff_purity");
  eff_pur_s5_ttbar->SetName("eff_pur_s5_ttbar");

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);

  TCanvas * canvas0 = new TCanvas("canvas0","canvas0",1000,800);
  canvas0->cd(1);
  // gPad->SetGridy();
  //gPad->SetGridx();
  eff_pur_l5->SetTitle("Kaon ID");//#frac{dE}{dx} x 10^{-6}");
  eff_pur_l5->GetYaxis()->SetTitle("Kaon ID purity");//#frac{dE}{dx} x 10^{-6}");
  eff_pur_l5->GetXaxis()->SetTitle("Kaon ID efficiency");
  eff_pur_l5->GetYaxis()->SetRangeUser(0.6,1.0);
  //  eff_pur_l5->GetXaxis()->SetRangeUser(0.4,1);
  eff_pur_l5->SetLineColor(4);
  eff_pur_l5->SetLineWidth(1);
  eff_pur_l5->SetLineStyle(1);
  eff_pur_l5->Draw("ac");
  eff_pur_s5->SetLineColor(2);
  eff_pur_s5->SetLineWidth(1);
  eff_pur_s5->SetLineStyle(2);
  eff_pur_s5->Draw("c");

  eff_pur_l5_ttbar->SetLineColor(4);
  eff_pur_l5_ttbar->SetLineWidth(6);
  eff_pur_l5_ttbar->SetLineStyle(1);
  eff_pur_l5_ttbar->Draw("c");
  eff_pur_s5_ttbar->SetLineColor(2);
  eff_pur_s5_ttbar->SetLineWidth(6);
  eff_pur_s5_ttbar->SetLineStyle(2);
  eff_pur_s5_ttbar->Draw("c");
  // QQBARLabel(0.5,0.85,"Preliminary",1);
  QQBARLabel(0.8,0.85,"",1);



  TLegend *leg0 = new TLegend(0.23,0.25,0.53,0.5);
  leg0->SetTextFont(42);
  leg0->AddEntry(eff_pur_l5,"IDR-L b#bar{b} @ 500GeV","l");
  leg0->AddEntry(eff_pur_s5,"IDR-S b#bar{b} @ 500GeV","l");
  leg0->AddEntry(eff_pur_l5_ttbar,"IDR-L t#bar{t} @ 500GeV","l");
  leg0->AddEntry(eff_pur_s5_ttbar,"IDR-S t#bar{t} @ 500GeV","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();
  

  canvas0->Update();
  
  canvas0->Print("kaonIDeff_v2.eps");
  canvas0->Print("kaonIDeff_v2.C");

  
}

