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

void plot2models_bins() {
      
  TFile *f = new TFile("l5.root");

  TH1F *l5_proj_pion_2 = (TH1F*)f->Get("proj_pion_2");
  TH1F *l5_proj_proton_2 = (TH1F*)f->Get("proj_proton_2");
  TH1F *l5_proj_kaon_2 = (TH1F*)f->Get("proj_kaon_2");

  TH1F *l5_proj_pion_3 = (TH1F*)f->Get("proj_pion_3");
  TH1F *l5_proj_proton_3 = (TH1F*)f->Get("proj_proton_3");
  TH1F *l5_proj_kaon_3 = (TH1F*)f->Get("proj_kaon_3");

  TH1F *l5_proj_pion_4 = (TH1F*)f->Get("proj_pion_4");
  TH1F *l5_proj_proton_4 = (TH1F*)f->Get("proj_proton_4");
  TH1F *l5_proj_kaon_4 = (TH1F*)f->Get("proj_kaon_4");
  
  TH1F *l5_proj_pion_5 = (TH1F*)f->Get("proj_pion_5");
  TH1F *l5_proj_proton_5 = (TH1F*)f->Get("proj_proton_5");
  TH1F *l5_proj_kaon_5 = (TH1F*)f->Get("proj_kaon_5");

  l5_proj_pion_2->Rebin(5);
  l5_proj_proton_2->Rebin(5);
  l5_proj_kaon_2->Rebin(5);
  
  l5_proj_pion_3->Rebin(5);
  l5_proj_proton_3->Rebin(5);
  l5_proj_kaon_3->Rebin(5);

  l5_proj_pion_4->Rebin(5);
  l5_proj_proton_4->Rebin(5);
  l5_proj_kaon_4->Rebin(5);
  
  l5_proj_pion_5->Rebin(5);
  l5_proj_proton_5->Rebin(5);
  l5_proj_kaon_5->Rebin(5);

  f = new TFile("s5.root");

  TH1F *s5_proj_pion_2 = (TH1F*)f->Get("proj_pion_2");
  TH1F *s5_proj_proton_2 = (TH1F*)f->Get("proj_proton_2");
  TH1F *s5_proj_kaon_2 = (TH1F*)f->Get("proj_kaon_2");

  TH1F *s5_proj_pion_3 = (TH1F*)f->Get("proj_pion_3");
  TH1F *s5_proj_proton_3 = (TH1F*)f->Get("proj_proton_3");
  TH1F *s5_proj_kaon_3 = (TH1F*)f->Get("proj_kaon_3");

  TH1F *s5_proj_pion_4 = (TH1F*)f->Get("proj_pion_4");
  TH1F *s5_proj_proton_4 = (TH1F*)f->Get("proj_proton_4");
  TH1F *s5_proj_kaon_4 = (TH1F*)f->Get("proj_kaon_4");
  
  TH1F *s5_proj_pion_5 = (TH1F*)f->Get("proj_pion_5");
  TH1F *s5_proj_proton_5 = (TH1F*)f->Get("proj_proton_5");
  TH1F *s5_proj_kaon_5 = (TH1F*)f->Get("proj_kaon_5");

  s5_proj_pion_2->Rebin(5);
  s5_proj_proton_2->Rebin(5);
  s5_proj_kaon_2->Rebin(5);
  
  s5_proj_pion_3->Rebin(5);
  s5_proj_proton_3->Rebin(5);
  s5_proj_kaon_3->Rebin(5);

  s5_proj_pion_4->Rebin(5);
  s5_proj_proton_4->Rebin(5);
  s5_proj_kaon_4->Rebin(5);
  
  s5_proj_pion_5->Rebin(5);
  s5_proj_proton_5->Rebin(5);
  s5_proj_kaon_5->Rebin(5);

  f = new TFile("l5_ttbar.root");

  TH1F *l5_ttbar_proj_pion_2 = (TH1F*)f->Get("proj_pion_2");
  TH1F *l5_ttbar_proj_proton_2 = (TH1F*)f->Get("proj_proton_2");
  TH1F *l5_ttbar_proj_kaon_2 = (TH1F*)f->Get("proj_kaon_2");

  TH1F *l5_ttbar_proj_pion_3 = (TH1F*)f->Get("proj_pion_3");
  TH1F *l5_ttbar_proj_proton_3 = (TH1F*)f->Get("proj_proton_3");
  TH1F *l5_ttbar_proj_kaon_3 = (TH1F*)f->Get("proj_kaon_3");

  TH1F *l5_ttbar_proj_pion_4 = (TH1F*)f->Get("proj_pion_4");
  TH1F *l5_ttbar_proj_proton_4 = (TH1F*)f->Get("proj_proton_4");
  TH1F *l5_ttbar_proj_kaon_4 = (TH1F*)f->Get("proj_kaon_4");
  
  TH1F *l5_ttbar_proj_pion_5 = (TH1F*)f->Get("proj_pion_5");
  TH1F *l5_ttbar_proj_proton_5 = (TH1F*)f->Get("proj_proton_5");
  TH1F *l5_ttbar_proj_kaon_5 = (TH1F*)f->Get("proj_kaon_5");

  l5_ttbar_proj_pion_2->Rebin(5);
  l5_ttbar_proj_proton_2->Rebin(5);
  l5_ttbar_proj_kaon_2->Rebin(5);
  
  l5_ttbar_proj_pion_3->Rebin(5);
  l5_ttbar_proj_proton_3->Rebin(5);
  l5_ttbar_proj_kaon_3->Rebin(5);

  l5_ttbar_proj_pion_4->Rebin(5);
  l5_ttbar_proj_proton_4->Rebin(5);
  l5_ttbar_proj_kaon_4->Rebin(5);
  
  l5_ttbar_proj_pion_5->Rebin(5);
  l5_ttbar_proj_proton_5->Rebin(5);
  l5_ttbar_proj_kaon_5->Rebin(5);




  // --------------------
 
  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  gStyle->SetTitleY(0.93);
  gStyle->SetTitleX(0.2);


  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  gStyle->SetTitleFont(42,"t");

  
  TCanvas * canvas_2 = new TCanvas("canvas_2","canvas_2",1000,800);
  canvas_2->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();
  l5_proj_proton_2->Scale(1./( l5_proj_proton_2->GetEntries() + l5_proj_kaon_2->GetEntries() + l5_proj_pion_2->GetEntries() ) );
  l5_proj_pion_2->Scale(1./( l5_proj_proton_2->GetEntries() + l5_proj_kaon_2->GetEntries() + l5_proj_pion_2->GetEntries() ) );
  l5_proj_kaon_2->Scale(1./( l5_proj_proton_2->GetEntries() + l5_proj_kaon_2->GetEntries() + l5_proj_pion_2->GetEntries() ) );
   
  l5_proj_pion_2->SetTitle("#frac{dE}{dx} for hadrons with momentum of [2,2.5] GeV");

  l5_proj_pion_2->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_2->GetYaxis()->SetTitleOffset(1.45);

  l5_proj_pion_2->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_2->GetYaxis()->SetRangeUser(0,l5_proj_pion_2->GetMaximum()*1.15);
  l5_proj_pion_2->SetLineColor(kGray);
  l5_proj_pion_2->SetLineWidth(4);
  l5_proj_pion_2->SetLineStyle(1);
  l5_proj_pion_2->Draw("histo");
  
  l5_proj_proton_2->SetLineColor(kGray+3);
  l5_proj_proton_2->SetLineWidth(4);
  l5_proj_proton_2->SetLineStyle(1);				 
  l5_proj_proton_2->Draw("histosame");
  
  l5_proj_kaon_2->SetLineColor(kGray+1);
  l5_proj_kaon_2->SetLineWidth(4);
  l5_proj_kaon_2->SetLineStyle(1);
  l5_proj_kaon_2->Draw("histosame");


  s5_proj_proton_2->Scale(1./( s5_proj_proton_2->GetEntries() + s5_proj_kaon_2->GetEntries() + s5_proj_pion_2->GetEntries() ) );
  s5_proj_pion_2->Scale(1./( s5_proj_proton_2->GetEntries() + s5_proj_kaon_2->GetEntries() + s5_proj_pion_2->GetEntries() ) );
  s5_proj_kaon_2->Scale(1./( s5_proj_proton_2->GetEntries() + s5_proj_kaon_2->GetEntries() + s5_proj_pion_2->GetEntries() ) );
   
  s5_proj_pion_2->SetLineColor(kGray);
  s5_proj_pion_2->SetLineWidth(4);
  s5_proj_pion_2->SetLineStyle(2);
  s5_proj_pion_2->Draw("histosame");
  
  s5_proj_proton_2->SetLineColor(kGray+3);
  s5_proj_proton_2->SetLineWidth(4);
  s5_proj_proton_2->SetLineStyle(2);				 
  s5_proj_proton_2->Draw("histosame");
  
  s5_proj_kaon_2->SetLineColor(kGray+1);
  s5_proj_kaon_2->SetLineWidth(4);
  s5_proj_kaon_2->SetLineStyle(2);
  s5_proj_kaon_2->Draw("histosame");


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);

  TLegend *leg0 = new TLegend(0.6,0.55,0.9,0.85);
  leg0->SetTextFont(42);
  leg0->SetHeader("e^{-}_{L}e^{+}_{R}#rightarrow b#bar{b} @ 500 GeV");
  leg0->AddEntry(l5_proj_proton_2,"p, IDR-L","l");
  leg0->AddEntry(l5_proj_kaon_2,"K, IDR-L","l");
  leg0->AddEntry(l5_proj_pion_2,"#pi, IDR-L","l");
  leg0->AddEntry(s5_proj_proton_2,"p, IDR-S","l");
  leg0->AddEntry(s5_proj_kaon_2,"K, IDR-S","l");
  leg0->AddEntry(s5_proj_pion_2,"#pi, IDR-S","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  gPad->Modified();
  gPad->Update();
  canvas_2->Print("separation_had_2GeV_models_v2.C");
  canvas_2->Print("separation_had_2GeV_models_v2.eps");

   TCanvas * canvas_3 = new TCanvas("canvas_3","canvas_3",1000,800);
   canvas_3->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();
  l5_proj_proton_3->Scale(1./( l5_proj_proton_3->GetEntries() + l5_proj_kaon_3->GetEntries() + l5_proj_pion_3->GetEntries() ) );
  l5_proj_pion_3->Scale(1./( l5_proj_proton_3->GetEntries() + l5_proj_kaon_3->GetEntries() + l5_proj_pion_3->GetEntries() ) );
  l5_proj_kaon_3->Scale(1./( l5_proj_proton_3->GetEntries() + l5_proj_kaon_3->GetEntries() + l5_proj_pion_3->GetEntries() ) );
   
  l5_proj_pion_3->SetTitle("#frac{dE}{dx} for hadrons with momentum of [5,6] GeV");

  l5_proj_pion_3->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_3->GetYaxis()->SetTitleOffset(1.45);
  l5_proj_pion_3->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_3->GetYaxis()->SetRangeUser(0,l5_proj_pion_3->GetMaximum()*1.15);
  l5_proj_pion_3->SetLineColor(kGray);
  l5_proj_pion_3->SetLineWidth(4);
  l5_proj_pion_3->SetLineStyle(1);
  l5_proj_pion_3->Draw("histo");
  
  l5_proj_proton_3->SetLineColor(kGray+3);
  l5_proj_proton_3->SetLineWidth(4);
  l5_proj_proton_3->SetLineStyle(1);				 
  l5_proj_proton_3->Draw("histosame");
  
  l5_proj_kaon_3->SetLineColor(kGray+1);
  l5_proj_kaon_3->SetLineWidth(4);
  l5_proj_kaon_3->SetLineStyle(1);
  l5_proj_kaon_3->Draw("histosame");


  s5_proj_proton_3->Scale(1./( s5_proj_proton_3->GetEntries() + s5_proj_kaon_3->GetEntries() + s5_proj_pion_3->GetEntries() ) );
  s5_proj_pion_3->Scale(1./( s5_proj_proton_3->GetEntries() + s5_proj_kaon_3->GetEntries() + s5_proj_pion_3->GetEntries() ) );
  s5_proj_kaon_3->Scale(1./( s5_proj_proton_3->GetEntries() + s5_proj_kaon_3->GetEntries() + s5_proj_pion_3->GetEntries() ) );
   
  s5_proj_pion_3->SetLineColor(kGray);
  s5_proj_pion_3->SetLineWidth(4);
  s5_proj_pion_3->SetLineStyle(2);
  s5_proj_pion_3->Draw("histosame");
  
  s5_proj_proton_3->SetLineColor(kGray+3);
  s5_proj_proton_3->SetLineWidth(4);
  s5_proj_proton_3->SetLineStyle(2);				 
  s5_proj_proton_3->Draw("histosame");
  
  s5_proj_kaon_3->SetLineColor(kGray+1);
  s5_proj_kaon_3->SetLineWidth(4);
  s5_proj_kaon_3->SetLineStyle(2);
  s5_proj_kaon_3->Draw("histosame");
  leg0->Draw();


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);
  gPad->Modified();
  gPad->Update();
  canvas_3->Print("separation_had_5GeV_models_v2.C");
  canvas_3->Print("separation_had_5GeV_models_v2.eps");
    
  TCanvas * canvas_4 = new TCanvas("canvas_4","canvas_4",1000,800);
   canvas_4->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();
  l5_proj_proton_4->Scale(1./( l5_proj_proton_4->GetEntries() + l5_proj_kaon_4->GetEntries() + l5_proj_pion_4->GetEntries() ) );
  l5_proj_pion_4->Scale(1./( l5_proj_proton_4->GetEntries() + l5_proj_kaon_4->GetEntries() + l5_proj_pion_4->GetEntries() ) );
  l5_proj_kaon_4->Scale(1./( l5_proj_proton_4->GetEntries() + l5_proj_kaon_4->GetEntries() + l5_proj_pion_4->GetEntries() ) );
   
  l5_proj_pion_4->SetTitle("#frac{dE}{dx} for hadrons with momentum of [10,15] GeV");

  l5_proj_pion_4->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_4->GetYaxis()->SetTitleOffset(1.45);
  l5_proj_pion_4->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_4->GetYaxis()->SetRangeUser(0,l5_proj_pion_4->GetMaximum()*1.15);
  l5_proj_pion_4->SetLineColor(kGray);
  l5_proj_pion_4->SetLineWidth(4);
  l5_proj_pion_4->SetLineStyle(1);
  l5_proj_pion_4->Draw("histo");
  
  l5_proj_proton_4->SetLineColor(kGray+3);
  l5_proj_proton_4->SetLineWidth(4);
  l5_proj_proton_4->SetLineStyle(1);				 
  l5_proj_proton_4->Draw("histosame");
  
  l5_proj_kaon_4->SetLineColor(kGray+1);
  l5_proj_kaon_4->SetLineWidth(4);
  l5_proj_kaon_4->SetLineStyle(1);
  l5_proj_kaon_4->Draw("histosame");


  s5_proj_proton_4->Scale(1./( s5_proj_proton_4->GetEntries() + s5_proj_kaon_4->GetEntries() + s5_proj_pion_4->GetEntries() ) );
  s5_proj_pion_4->Scale(1./( s5_proj_proton_4->GetEntries() + s5_proj_kaon_4->GetEntries() + s5_proj_pion_4->GetEntries() ) );
  s5_proj_kaon_4->Scale(1./( s5_proj_proton_4->GetEntries() + s5_proj_kaon_4->GetEntries() + s5_proj_pion_4->GetEntries() ) );
   
  s5_proj_pion_4->SetLineColor(kGray);
  s5_proj_pion_4->SetLineWidth(4);
  s5_proj_pion_4->SetLineStyle(2);
  s5_proj_pion_4->Draw("histosame");
  
  s5_proj_proton_4->SetLineColor(kGray+3);
  s5_proj_proton_4->SetLineWidth(4);
  s5_proj_proton_4->SetLineStyle(2);				 
  s5_proj_proton_4->Draw("histosame");
  
  s5_proj_kaon_4->SetLineColor(kGray+1);
  s5_proj_kaon_4->SetLineWidth(4);
  s5_proj_kaon_4->SetLineStyle(2);
  s5_proj_kaon_4->Draw("histosame");
  leg0->Draw();


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);
  gPad->Modified();
  gPad->Update();
  canvas_4->Print("separation_had_10GeV_models_v2.C");
  canvas_4->Print("separation_had_10GeV_models_v2.eps");

  TCanvas * canvas_5 = new TCanvas("canvas_5","canvas_5",1000,800);
   canvas_5->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();
  l5_proj_proton_5->Scale(1./( l5_proj_proton_5->GetEntries() + l5_proj_kaon_5->GetEntries() + l5_proj_pion_5->GetEntries() ) );
  l5_proj_pion_5->Scale(1./( l5_proj_proton_5->GetEntries() + l5_proj_kaon_5->GetEntries() + l5_proj_pion_5->GetEntries() ) );
  l5_proj_kaon_5->Scale(1./( l5_proj_proton_5->GetEntries() + l5_proj_kaon_5->GetEntries() + l5_proj_pion_5->GetEntries() ) );
   
  l5_proj_pion_5->SetTitle("#frac{dE}{dx} for hadrons with momentum of [30,40] GeV");

  l5_proj_pion_5->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_5->GetYaxis()->SetTitleOffset(1.45);
  l5_proj_pion_5->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_5->GetYaxis()->SetRangeUser(0,l5_proj_pion_5->GetMaximum()*1.15);
  l5_proj_pion_5->SetLineColor(kGray);
  l5_proj_pion_5->SetLineWidth(4);
  l5_proj_pion_5->SetLineStyle(1);
  l5_proj_pion_5->Draw("histo");
  
  l5_proj_proton_5->SetLineColor(kGray+3);
  l5_proj_proton_5->SetLineWidth(4);
  l5_proj_proton_5->SetLineStyle(1);				 
  l5_proj_proton_5->Draw("histosame");
  
  l5_proj_kaon_5->SetLineColor(kGray+1);
  l5_proj_kaon_5->SetLineWidth(4);
  l5_proj_kaon_5->SetLineStyle(1);
  l5_proj_kaon_5->Draw("histosame");


  s5_proj_proton_5->Scale(1./( s5_proj_proton_5->GetEntries() + s5_proj_kaon_5->GetEntries() + s5_proj_pion_5->GetEntries() ) );
  s5_proj_pion_5->Scale(1./( s5_proj_proton_5->GetEntries() + s5_proj_kaon_5->GetEntries() + s5_proj_pion_5->GetEntries() ) );
  s5_proj_kaon_5->Scale(1./( s5_proj_proton_5->GetEntries() + s5_proj_kaon_5->GetEntries() + s5_proj_pion_5->GetEntries() ) );
   
  s5_proj_pion_5->SetLineColor(kGray);
  s5_proj_pion_5->SetLineWidth(4);
  s5_proj_pion_5->SetLineStyle(2);
  s5_proj_pion_5->Draw("histosame");
  
  s5_proj_proton_5->SetLineColor(kGray+3);
  s5_proj_proton_5->SetLineWidth(4);
  s5_proj_proton_5->SetLineStyle(2);				 
  s5_proj_proton_5->Draw("histosame");
  
  s5_proj_kaon_5->SetLineColor(kGray+1);
  s5_proj_kaon_5->SetLineWidth(4);
  s5_proj_kaon_5->SetLineStyle(2);
  s5_proj_kaon_5->Draw("histosame");
  leg0->Draw();


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);
  gPad->Modified();
  gPad->Update();
  canvas_5->Print("separation_had_30GeV_models_v2.C");
  canvas_5->Print("separation_had_30GeV_models_v2.eps");


  //****************************************************************************************************
  //***************************************************************************************************
  
  TCanvas * canvas2_2 = new TCanvas("canvas2_2","canvas2_2",1000,800);
  canvas2_2->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();
  l5_proj_pion_2->SetTitle("#frac{dE}{dx} for hadrons with momentum of [2,2.5] GeV");

  l5_proj_pion_2->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_2->GetYaxis()->SetTitleOffset(1.45);

  l5_proj_pion_2->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_2->GetYaxis()->SetRangeUser(0,l5_proj_pion_2->GetMaximum()*1.15);
  l5_proj_pion_2->SetLineColor(kGray);
  l5_proj_pion_2->SetLineWidth(4);
  l5_proj_pion_2->SetLineStyle(1);
  l5_proj_pion_2->Draw("histo");
  
  l5_proj_proton_2->SetLineColor(kGray+3);
  l5_proj_proton_2->SetLineWidth(4);
  l5_proj_proton_2->SetLineStyle(1);				 
  l5_proj_proton_2->Draw("histosame");
  
  l5_proj_kaon_2->SetLineColor(kGray+1);
  l5_proj_kaon_2->SetLineWidth(4);
  l5_proj_kaon_2->SetLineStyle(1);
  l5_proj_kaon_2->Draw("histosame");


  l5_ttbar_proj_proton_2->Scale(1./( l5_ttbar_proj_proton_2->GetEntries() + l5_ttbar_proj_kaon_2->GetEntries() + l5_ttbar_proj_pion_2->GetEntries() ) );
  l5_ttbar_proj_pion_2->Scale(1./( l5_ttbar_proj_proton_2->GetEntries() + l5_ttbar_proj_kaon_2->GetEntries() + l5_ttbar_proj_pion_2->GetEntries() ) );
  l5_ttbar_proj_kaon_2->Scale(1./( l5_ttbar_proj_proton_2->GetEntries() + l5_ttbar_proj_kaon_2->GetEntries() + l5_ttbar_proj_pion_2->GetEntries() ) );
   
  l5_ttbar_proj_pion_2->SetLineColor(kGray);
  l5_ttbar_proj_pion_2->SetLineWidth(4);
  l5_ttbar_proj_pion_2->SetLineStyle(3);
  l5_ttbar_proj_pion_2->Draw("histosame");
  
  l5_ttbar_proj_proton_2->SetLineColor(kGray+3);
  l5_ttbar_proj_proton_2->SetLineWidth(4);
  l5_ttbar_proj_proton_2->SetLineStyle(3);				 
  l5_ttbar_proj_proton_2->Draw("histosame");
  
  l5_ttbar_proj_kaon_2->SetLineColor(kGray+1);
  l5_ttbar_proj_kaon_2->SetLineWidth(4);
  l5_ttbar_proj_kaon_2->SetLineStyle(3);
  l5_ttbar_proj_kaon_2->Draw("histosame");


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);

  TLegend *leg1 = new TLegend(0.55,0.55,0.92,0.8);
  leg1->SetTextFont(42);
  leg1->SetHeader("e^{-}_{L}e^{+}_{R}#rightarrow q#bar{q} @ 500 GeV, IDR-L");
  leg1->AddEntry(l5_proj_proton_2,"p, b#bar{b}","l");
  leg1->AddEntry(l5_proj_kaon_2,"K, b#bar{b}","l");
  leg1->AddEntry(l5_proj_pion_2,"#pi, b#bar{b}","l");
  leg1->AddEntry(l5_ttbar_proj_proton_2,"p, t#bar{t}","l");
  leg1->AddEntry(l5_ttbar_proj_kaon_2,"K, t#bar{t}","l");
  leg1->AddEntry(l5_ttbar_proj_pion_2,"#pi, t#bar{t}","l");
  leg1->SetFillColor(0);
  leg1->SetLineColor(0);
  leg1->SetShadowColor(0);
  leg1->Draw();

  gPad->Modified();
  gPad->Update();
  canvas2_2->Print("separation_had_2GeV_bbbar_vs_ttbar_v2.C");
  canvas2_2->Print("separation_had_2GeV_bbbar_vs_ttbar_v2.eps");

   TCanvas * canvas2_3 = new TCanvas("canvas2_3","canvas2_3",1000,800);
   canvas2_3->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();
  l5_proj_pion_3->SetTitle("#frac{dE}{dx} for hadrons with momentum of [5,6] GeV");

  l5_proj_pion_3->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_3->GetYaxis()->SetTitleOffset(1.45);
  l5_proj_pion_3->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_3->GetYaxis()->SetRangeUser(0,l5_proj_pion_3->GetMaximum()*1.15);
  l5_proj_pion_3->SetLineColor(kGray);
  l5_proj_pion_3->SetLineWidth(4);
  l5_proj_pion_3->SetLineStyle(1);
  l5_proj_pion_3->Draw("histo");
  
  l5_proj_proton_3->SetLineColor(kGray+3);
  l5_proj_proton_3->SetLineWidth(4);
  l5_proj_proton_3->SetLineStyle(1);				 
  l5_proj_proton_3->Draw("histosame");
  
  l5_proj_kaon_3->SetLineColor(kGray+1);
  l5_proj_kaon_3->SetLineWidth(4);
  l5_proj_kaon_3->SetLineStyle(1);
  l5_proj_kaon_3->Draw("histosame");


  l5_ttbar_proj_proton_3->Scale(1./( l5_ttbar_proj_proton_3->GetEntries() + l5_ttbar_proj_kaon_3->GetEntries() + l5_ttbar_proj_pion_3->GetEntries() ) );
  l5_ttbar_proj_pion_3->Scale(1./( l5_ttbar_proj_proton_3->GetEntries() + l5_ttbar_proj_kaon_3->GetEntries() + l5_ttbar_proj_pion_3->GetEntries() ) );
  l5_ttbar_proj_kaon_3->Scale(1./( l5_ttbar_proj_proton_3->GetEntries() + l5_ttbar_proj_kaon_3->GetEntries() + l5_ttbar_proj_pion_3->GetEntries() ) );
   
  l5_ttbar_proj_pion_3->SetLineColor(kGray);
  l5_ttbar_proj_pion_3->SetLineWidth(4);
  l5_ttbar_proj_pion_3->SetLineStyle(3);
  l5_ttbar_proj_pion_3->Draw("histosame");
  
  l5_ttbar_proj_proton_3->SetLineColor(kGray+3);
  l5_ttbar_proj_proton_3->SetLineWidth(4);
  l5_ttbar_proj_proton_3->SetLineStyle(3);				 
  l5_ttbar_proj_proton_3->Draw("histosame");
  
  l5_ttbar_proj_kaon_3->SetLineColor(kGray+1);
  l5_ttbar_proj_kaon_3->SetLineWidth(4);
  l5_ttbar_proj_kaon_3->SetLineStyle(3);
  l5_ttbar_proj_kaon_3->Draw("histosame");
  leg1->Draw();


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);
  gPad->Modified();
  gPad->Update();
  canvas2_3->Print("separation_had_5GeV_bbbar_vs_ttbar_v2.C");
  canvas2_3->Print("separation_had_5GeV_bbbar_vs_ttbar_v2.eps");

    TCanvas * canvas2_4 = new TCanvas("canvas2_4","canvas2_4",1000,800);
   canvas2_4->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();
  l5_proj_pion_4->SetTitle("#frac{dE}{dx} for hadrons with momentum of [10,15] GeV");

  l5_proj_pion_4->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_4->GetYaxis()->SetTitleOffset(1.45);
  l5_proj_pion_4->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_4->GetYaxis()->SetRangeUser(0,l5_proj_pion_4->GetMaximum()*1.15);
  l5_proj_pion_4->SetLineColor(kGray);
  l5_proj_pion_4->SetLineWidth(4);
  l5_proj_pion_4->SetLineStyle(1);
  l5_proj_pion_4->Draw("histo");
  
  l5_proj_proton_4->SetLineColor(kGray+3);
  l5_proj_proton_4->SetLineWidth(4);
  l5_proj_proton_4->SetLineStyle(1);				 
  l5_proj_proton_4->Draw("histosame");
  
  l5_proj_kaon_4->SetLineColor(kGray+1);
  l5_proj_kaon_4->SetLineWidth(4);
  l5_proj_kaon_4->SetLineStyle(1);
  l5_proj_kaon_4->Draw("histosame");


  l5_ttbar_proj_proton_4->Scale(1./( l5_ttbar_proj_proton_4->GetEntries() + l5_ttbar_proj_kaon_4->GetEntries() + l5_ttbar_proj_pion_4->GetEntries() ) );
  l5_ttbar_proj_pion_4->Scale(1./( l5_ttbar_proj_proton_4->GetEntries() + l5_ttbar_proj_kaon_4->GetEntries() + l5_ttbar_proj_pion_4->GetEntries() ) );
  l5_ttbar_proj_kaon_4->Scale(1./( l5_ttbar_proj_proton_4->GetEntries() + l5_ttbar_proj_kaon_4->GetEntries() + l5_ttbar_proj_pion_4->GetEntries() ) );
   
  l5_ttbar_proj_pion_4->SetLineColor(kGray);
  l5_ttbar_proj_pion_4->SetLineWidth(4);
  l5_ttbar_proj_pion_4->SetLineStyle(3);
  l5_ttbar_proj_pion_4->Draw("histosame");
  
  l5_ttbar_proj_proton_4->SetLineColor(kGray+3);
  l5_ttbar_proj_proton_4->SetLineWidth(4);
  l5_ttbar_proj_proton_4->SetLineStyle(3);				 
  l5_ttbar_proj_proton_4->Draw("histosame");
  
  l5_ttbar_proj_kaon_4->SetLineColor(kGray+1);
  l5_ttbar_proj_kaon_4->SetLineWidth(4);
  l5_ttbar_proj_kaon_4->SetLineStyle(3);
  l5_ttbar_proj_kaon_4->Draw("histosame");
  leg1->Draw();


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);
  gPad->Modified();
  gPad->Update();
  canvas2_4->Print("separation_had_10GeV_bbbar_vs_ttbar_v2.C");
  canvas2_4->Print("separation_had_10GeV_bbbar_vs_ttbar_v2.eps");

  TCanvas * canvas2_5 = new TCanvas("canvas2_5","canvas2_5",1000,800);
   canvas2_5->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  //gPad->SetLogx();

  l5_proj_pion_5->SetTitle("#frac{dE}{dx} for hadrons with momentum of [30,40] GeV");

  l5_proj_pion_5->GetYaxis()->SetTitle("#frac{N_{i}}{N_{total}}");
  l5_proj_pion_5->GetYaxis()->SetTitleOffset(1.45);
  l5_proj_pion_5->GetXaxis()->SetTitle("#frac{dE}{dx} [MeV]");
  l5_proj_pion_5->GetYaxis()->SetRangeUser(0,l5_proj_pion_5->GetMaximum()*1.15);
  l5_proj_pion_5->SetLineColor(kGray);
  l5_proj_pion_5->SetLineWidth(4);
  l5_proj_pion_5->SetLineStyle(1);
  l5_proj_pion_5->Draw("histo");
  
  l5_proj_proton_5->SetLineColor(kGray+3);
  l5_proj_proton_5->SetLineWidth(4);
  l5_proj_proton_5->SetLineStyle(1);				 
  l5_proj_proton_5->Draw("histosame");
  
  l5_proj_kaon_5->SetLineColor(kGray+1);
  l5_proj_kaon_5->SetLineWidth(4);
  l5_proj_kaon_5->SetLineStyle(1);
  l5_proj_kaon_5->Draw("histosame");


  l5_ttbar_proj_proton_5->Scale(1./( l5_ttbar_proj_proton_5->GetEntries() + l5_ttbar_proj_kaon_5->GetEntries() + l5_ttbar_proj_pion_5->GetEntries() ) );
  l5_ttbar_proj_pion_5->Scale(1./( l5_ttbar_proj_proton_5->GetEntries() + l5_ttbar_proj_kaon_5->GetEntries() + l5_ttbar_proj_pion_5->GetEntries() ) );
  l5_ttbar_proj_kaon_5->Scale(1./( l5_ttbar_proj_proton_5->GetEntries() + l5_ttbar_proj_kaon_5->GetEntries() + l5_ttbar_proj_pion_5->GetEntries() ) );
   
  l5_ttbar_proj_pion_5->SetLineColor(kGray);
  l5_ttbar_proj_pion_5->SetLineWidth(4);
  l5_ttbar_proj_pion_5->SetLineStyle(3);
  l5_ttbar_proj_pion_5->Draw("histosame");
  
  l5_ttbar_proj_proton_5->SetLineColor(kGray+3);
  l5_ttbar_proj_proton_5->SetLineWidth(4);
  l5_ttbar_proj_proton_5->SetLineStyle(3);				 
  l5_ttbar_proj_proton_5->Draw("histosame");
  
  l5_ttbar_proj_kaon_5->SetLineColor(kGray+1);
  l5_ttbar_proj_kaon_5->SetLineWidth(4);
  l5_ttbar_proj_kaon_5->SetLineStyle(3);
  l5_ttbar_proj_kaon_5->Draw("histosame");
  leg1->Draw();


  //QQBARLabel(0.8,0.2,"Preliminary",1);
  QQBARLabel(0.8,0.2,"",1);

  gPad->Modified();
  gPad->Update();
  canvas2_5->Print("separation_had_30GeV_bbbar_vs_ttbar_v2.C");
  canvas2_5->Print("separation_had_30GeV_bbbar_vs_ttbar_v2.eps");

}

