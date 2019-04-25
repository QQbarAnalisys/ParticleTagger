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

void plot2models() {
      
  TFile *f = new TFile("l5.root");

  TGraphErrors *mean1_pion = (TGraphErrors*)f->Get("mean_pion");
  TGraphErrors *mean1_proton = (TGraphErrors*)f->Get("mean_proton");
  TGraphErrors *mean1_kaon = (TGraphErrors*)f->Get("mean_kaon");

  TGraphErrors *RMSnorm1_pion = (TGraphErrors*)f->Get("RMSnorm_pion");
  TGraphErrors *RMSnorm1_proton = (TGraphErrors*)f->Get("RMSnorm_proton");
  TGraphErrors *RMSnorm1_kaon = (TGraphErrors*)f->Get("RMSnorm_kaon");
  
  Double_t* mean1_pion_x = mean1_pion->GetX();
  Double_t* mean1_pion_ex = mean1_pion->GetEX();

  Double_t* mean1_pion_y = mean1_pion->GetY();
  Double_t* mean1_proton_y = mean1_proton->GetY();
  Double_t* mean1_kaon_y = mean1_kaon->GetY();

  Double_t* RMSnorm1_pion_y = RMSnorm1_pion->GetY();
  Double_t* RMSnorm1_proton_y = RMSnorm1_proton->GetY();
  Double_t* RMSnorm1_kaon_y = RMSnorm1_kaon->GetY();

  double x1[100], y1pion[100], ex1[100], ey1pion[100];
  double y1proton[100], ey1proton[100];
  int n=0;
  for(int i=0; i<mean1_pion->GetN(); i++) {
    if(mean1_pion_x[i]>2) {
      x1[n]=mean1_pion_x[i];
      ex1[n]=0;//mean1_pion_ex[i];
      
      y1pion[n]= 1000*fabs(mean1_pion_y[i]-mean1_kaon_y[i])/sqrt(pow(RMSnorm1_pion_y[i],2)+pow(RMSnorm1_kaon_y[i],2));
      y1proton[n]= 1000*fabs(mean1_proton_y[i]-mean1_kaon_y[i])/sqrt(pow(RMSnorm1_proton_y[i],2)+pow(RMSnorm1_kaon_y[i],2));
      n++;
    }
  }
  TGraphErrors *proton_l5 = new TGraphErrors(n,x1,y1proton,ex1,ey1proton);
  TGraphErrors *pion_l5 = new TGraphErrors(n,x1,y1pion,ex1,ey1pion);

  // ------------------------------------------------------
  TFile *f2 = new TFile("s5.root");

  TGraphErrors *mean2_pion = (TGraphErrors*)f2->Get("mean_pion");
  TGraphErrors *mean2_proton = (TGraphErrors*)f2->Get("mean_proton");
  TGraphErrors *mean2_kaon = (TGraphErrors*)f2->Get("mean_kaon");

  TGraphErrors *RMSnorm2_pion = (TGraphErrors*)f2->Get("RMSnorm_pion");
  TGraphErrors *RMSnorm2_proton = (TGraphErrors*)f2->Get("RMSnorm_proton");
  TGraphErrors *RMSnorm2_kaon = (TGraphErrors*)f2->Get("RMSnorm_kaon");

  Double_t* mean2_pion_x = mean2_pion->GetX();
  Double_t* mean2_pion_ex = mean2_pion->GetEX();

  Double_t* mean2_pion_y = mean2_pion->GetY();
  Double_t* mean2_proton_y = mean2_proton->GetY();
  Double_t* mean2_kaon_y = mean2_kaon->GetY();

  Double_t* RMSnorm2_pion_y = RMSnorm2_pion->GetY();
  Double_t* RMSnorm2_proton_y = RMSnorm2_proton->GetY();
  Double_t* RMSnorm2_kaon_y = RMSnorm2_kaon->GetY();

  double x2[100], y2pion[100], ex2[100], ey2pion[100];
  double y2proton[100], ey2proton[100];
  n=0;
  for(int i=0; i<mean2_pion->GetN(); i++) {
    if(mean2_pion_x[i]>2) {
      x2[n]=mean2_pion_x[i];
      ex2[n]=0;//mean2_pion_ex[i];
      
      y2pion[n]= 1000*fabs(mean2_pion_y[i]-mean2_kaon_y[i])/sqrt(pow(RMSnorm2_pion_y[i],2)+pow(RMSnorm2_kaon_y[i],2));
      y2proton[n]= 1000*fabs(mean2_proton_y[i]-mean2_kaon_y[i])/sqrt(pow(RMSnorm2_proton_y[i],2)+pow(RMSnorm2_kaon_y[i],2));
      n++;
    }
  }
  TGraphErrors *proton_s5 = new TGraphErrors(n,x2,y2proton,ex2,ey2proton);
  TGraphErrors *pion_s5 = new TGraphErrors(n,x2,y2pion,ex2,ey2pion);


  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetMarkerSize(1.5);
  
  TCanvas * canvas0 = new TCanvas("canvas0","canvas0",1000,800);
  canvas0->cd(1);
  //  gPad->SetGridy();
  //gPad->SetGridx();
  gPad->SetLogx();
  proton_s5->SetTitle("Kaon ID");//#frac{dE}{dx} x 10^{-6}");
  proton_s5->GetYaxis()->SetTitle("separation power");//#frac{dE}{dx} x 10^{-6}");
  proton_s5->GetXaxis()->SetTitle("p [GeV]");
  proton_s5->GetYaxis()->SetRangeUser(0,6);
  proton_s5->SetLineColor(kGray);
  proton_s5->SetLineWidth(1);
  proton_s5->SetLineStyle(2);
  proton_s5->Draw("ac");
  pion_s5->SetLineColor(2);
  pion_s5->SetLineWidth(6);
  pion_s5->SetLineStyle(2);
  pion_s5->Draw("c");

  proton_l5->SetLineColor(kGray);
  proton_l5->SetLineWidth(1);
    
  proton_l5->Draw("c");
  pion_l5->SetLineColor(4);
  pion_l5->SetLineWidth(6);
  pion_l5->Draw("c");

  QQBARLabel(0.2,0.85,"Preliminary",1);
  // QQBARLabel(0.2,0.85,"",1);

  TLegend *leg0 = new TLegend(0.6,0.6,0.9,0.85);
  leg0->SetTextFont(42);
  leg0->SetHeader("e^{-}_{L}e^{+}_{R}#rightarrow b#bar{b} @ 500 GeV");
  leg0->AddEntry(pion_l5,"K/#pi, IDR-L","l");
  leg0->AddEntry(pion_s5,"K/#pi, IDR-S","l");
  leg0->AddEntry(proton_l5,"K/p, IDR-L","l");
  leg0->AddEntry(proton_s5,"K/p, IDR-S","l");
  leg0->SetFillColor(0);
  leg0->SetLineColor(0);
  leg0->SetShadowColor(0);
  leg0->Draw();

  
  return 0;
  TCanvas * canvas = new TCanvas("canvas","canvas",1600,800);
  canvas->Divide(2,1);
  
  canvas->cd(1);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogx();
       
  mean1_pion->GetYaxis()->SetTitle("");//#frac{dE}{dx} x 10^{-6}");
  mean1_pion->GetXaxis()->SetTitle("p [GeV]");
  mean1_pion->GetXaxis()->SetRangeUser(0,1);
  mean1_pion->Draw("al");
  
  mean1_proton->Draw("l");
  mean1_kaon->Draw("l");

  mean2_pion->SetLineStyle(2);
  mean2_proton->SetLineStyle(2);
  mean2_kaon->SetLineStyle(2);
  mean2_pion->Draw("l");
  mean2_proton->Draw("l");
  mean2_kaon->Draw("l");

  TLegend *leg = new TLegend(0.6,0.2,0.9,0.5);
  leg->AddEntry(mean1_pion,"#pi, l5","l");
  leg->AddEntry(mean2_pion,"#pi, s5","l");
  leg->AddEntry(mean1_kaon,"K, l5","l");
  leg->AddEntry(mean2_kaon,"K, s5","l");
  leg->AddEntry(mean1_proton,"p, l5","l");
  leg->AddEntry(mean2_proton,"p, s5","l");
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetShadowColor(0);
  leg->Draw();

  canvas->cd(2);
  gPad->SetGridy();
  gPad->SetGridx();
  gPad->SetLogx();

  RMSnorm1_pion->Draw("al");
  RMSnorm1_proton->Draw("l");
  RMSnorm1_kaon->Draw("l");

  RMSnorm2_pion->SetLineStyle(2);
  RMSnorm2_proton->SetLineStyle(2);
  RMSnorm2_kaon->SetLineStyle(2);
  RMSnorm2_pion->Draw("l");
  RMSnorm2_proton->Draw("l");
  RMSnorm2_kaon->Draw("l");

  leg->Draw();

 
  
}

