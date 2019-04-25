#define CalculateParameters_cxx
#include "CalculateParameters.h"
#include "TPad.h"
#include "TMath.h"

void CalculateParameters::Initialize() {

  SetQQbarStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetMarkerSize(0.1);


  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.33,1.667,2,2.5,3,4,5,6,7,8,9,10,13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[400];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  
  kaon_dEdx_truth = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_truth = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_truth = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  binsy[0]=0;
  for(int i=1;i<100;i++) binsy[i]=binsy[i-1]+100./100.;
  nbinnumy=99;

  /*  kaon_TOFFirstHit_truth = new TH2F("kaon_TOFFirstHit_truth","kaon_TOFFirstHit_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_TOFFirstHit_truth = new TH2F("proton_TOFFirstHit_truth","proton_TOFFirstHit_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_TOFFirstHit_truth = new TH2F("pion_TOFFirstHit_truth","pion_TOFFirstHit_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_TOFClosestHits_truth = new TH2F("kaon_TOFClosestHits_truth","kaon_TOFClosestHits_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_TOFClosestHits_truth = new TH2F("proton_TOFClosestHits_truth","proton_TOFClosestHits_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_TOFClosestHits_truth = new TH2F("pion_TOFClosestHits_truth","pion_TOFClosestHits_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  binsy[0]=-20000;
  for(int i=1;i<100;i++) binsy[i]=binsy[i-1]+25000./100.;
  nbinnumy=99;
    
  kaon_TOFFlightLength_truth = new TH2F("kaon_TOFFlightLength_truth","kaon_TOFFlightLength_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_TOFFlightLength_truth = new TH2F("proton_TOFFlightLength_truth","proton_TOFFlightLength_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_TOFFlightLength_truth = new TH2F("pion_TOFFlightLength_truth","pion_TOFFlightLength_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_TOFLastTrkHitFlightLength_truth = new TH2F("kaon_TOFLastTrkHitFlightLength_truth","kaon_TOFLastTrkHitFlightLength_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_TOFLastTrkHitFlightLength_truth = new TH2F("proton_TOFLastTrkHitFlightLength_truth","proton_TOFLastTrkHitFlightLength_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_TOFLastTrkHitFlightLength_truth = new TH2F("pion_TOFLastTrkHitFlightLength_truth","pion_TOFLastTrkHitFlightLength_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  
  binsy[0]=0;
  for(int i=1;i<100;i++) binsy[i]=binsy[i-1]+50./100.;
  nbinnumy=99;

  kaon_TOFLastTrkHit_truth = new TH2F("kaon_TOFLastTrkHit_truth","kaon_TOFLastTrkHit_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_TOFLastTrkHit_truth = new TH2F("proton_TOFLastTrkHit_truth","proton_TOFLastTrkHit_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_TOFLastTrkHit_truth = new TH2F("pion_TOFLastTrkHit_truth","pion_TOFLastTrkHit_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  */

}

  
void CalculateParameters::Parameters(bool secondary=false, float momentum_min =1.0)
{

  Initialize();
  if (fChain == 0) return;
   
  Long64_t nentries = fChain->GetEntriesFast();
  //  nentries = 10000;
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    for(int i=0;i<nParticles;i++) {

      bool selection= (vtxType[i]==2  && abs(costheta[i])<0.95 );
      if (secondary==false) selection=true;
      if (selection == false) continue;


      if(trueType[i]==321) {
       	kaon_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
	/*	kaon_TOFFirstHit_truth->Fill(momentum[i],TOFFirstHit[i]);
	kaon_TOFClosestHits_truth->Fill(momentum[i],TOFClosestHits[i]);
	kaon_TOFFlightLength_truth->Fill(momentum[i],TOFFlightLength[i]);
	kaon_TOFLastTrkHit_truth->Fill(momentum[i],TOFLastTrkHit[i]);
	kaon_TOFLastTrkHitFlightLength_truth->Fill(momentum[i],TOFLastTrkHitFlightLength[i]);*/
      }
      if(trueType[i]==2212) {
     	proton_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
	/*	proton_TOFFirstHit_truth->Fill(momentum[i],TOFFirstHit[i]);
	proton_TOFClosestHits_truth->Fill(momentum[i],TOFClosestHits[i]);
	proton_TOFFlightLength_truth->Fill(momentum[i],TOFFlightLength[i]);
	proton_TOFLastTrkHit_truth->Fill(momentum[i],TOFLastTrkHit[i]);
	proton_TOFLastTrkHitFlightLength_truth->Fill(momentum[i],TOFLastTrkHitFlightLength[i]);*/
      }
      if(trueType[i]==211) {
     	pion_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
	/*	pion_TOFFirstHit_truth->Fill(momentum[i],TOFFirstHit[i]);
	pion_TOFClosestHits_truth->Fill(momentum[i],TOFClosestHits[i]);
	pion_TOFFlightLength_truth->Fill(momentum[i],TOFFlightLength[i]);
	pion_TOFLastTrkHit_truth->Fill(momentum[i],TOFLastTrkHit[i]);
	pion_TOFLastTrkHitFlightLength_truth->Fill(momentum[i],TOFLastTrkHitFlightLength[i]);*/
      }
      
    }//for 
    // }
    // if (Cut(ientry) < 0) continue;
  }
  

    //----------------------------------------------------------------------------------------

  TCanvas* c_test = new TCanvas("c_test","c_test",1000,800);
  c_test->Divide(3,2);
  c_test->cd(1);
  
  gPad->SetLogx();
  /*
  for(int i=0; i<33; i++){
    for(int j=0; j<99; j++){
      if(pion_TOFFirstHit_truth->GetBinContent(i+1,j+1)>1) pion_TOFFirstHit_truth->SetBinContent(i+1,j+1,50./pion_TOFFirstHit_truth->GetBinContent(i+1,j+1));
      else  pion_TOFFirstHit_truth->SetBinContent(i+1,j+1,0);
      
      if(kaon_TOFFirstHit_truth->GetBinContent(i+1,j+1)>1) kaon_TOFFirstHit_truth->SetBinContent(i+1,j+1,50./kaon_TOFFirstHit_truth->GetBinContent(i+1,j+1));
      else  kaon_TOFFirstHit_truth->SetBinContent(i+1,j+1,0);

      if(proton_TOFFirstHit_truth->GetBinContent(i+1,j+1)>1) proton_TOFFirstHit_truth->SetBinContent(i+1,j+1,50./proton_TOFFirstHit_truth->GetBinContent(i+1,j+1));
      else  proton_TOFFirstHit_truth->SetBinContent(i+1,j+1,0);

    }
  }
  pion_TOFFirstHit_truth->SetMarkerColor(4);
  pion_TOFFirstHit_truth->SetLineColor(4);
  pion_TOFFirstHit_truth->SetTitle("0ps");
  pion_TOFFirstHit_truth->GetYaxis()->SetTitle("TOFFirstHit");
  pion_TOFFirstHit_truth->GetXaxis()->SetTitle("p");
  pion_TOFFirstHit_truth->Draw("p");
  kaon_TOFFirstHit_truth->SetMarkerColor(2);
  kaon_TOFFirstHit_truth->SetLineColor(2);
  kaon_TOFFirstHit_truth->Draw("psame");
  proton_TOFFirstHit_truth->SetMarkerColor(3);
  proton_TOFFirstHit_truth->SetLineColor(3);
  proton_TOFFirstHit_truth->Draw("psame");
  TLegend *leg= new TLegend(0.5,0.6,0.9,0.9);
  leg->AddEntry( pion_TOFFirstHit_truth,"#pi","lp");
  leg->AddEntry( kaon_TOFFirstHit_truth,"K","lp");
  leg->AddEntry( proton_TOFFirstHit_truth,"p","lp");
  leg->Draw();


  c_test->cd(2);
  gPad->SetLogx();
  for(int i=0; i<33; i++){
    for(int j=0; j<99; j++){
      if(pion_TOFClosestHits_truth->GetBinContent(i+1,j+1)>1) pion_TOFClosestHits_truth->SetBinContent(i+1,j+1,50./pion_TOFClosestHits_truth->GetBinContent(i+1,j+1));
      else  pion_TOFClosestHits_truth->SetBinContent(i+1,j+1,0);
      
      if(kaon_TOFClosestHits_truth->GetBinContent(i+1,j+1)>1) kaon_TOFClosestHits_truth->SetBinContent(i+1,j+1,50./kaon_TOFClosestHits_truth->GetBinContent(i+1,j+1));
      else  kaon_TOFClosestHits_truth->SetBinContent(i+1,j+1,0);

      if(proton_TOFClosestHits_truth->GetBinContent(i+1,j+1)>1) proton_TOFClosestHits_truth->SetBinContent(i+1,j+1,50./proton_TOFClosestHits_truth->GetBinContent(i+1,j+1));
      else  proton_TOFClosestHits_truth->SetBinContent(i+1,j+1,0);

    }
  }
  pion_TOFClosestHits_truth->SetMarkerColor(4);
  pion_TOFClosestHits_truth->SetLineColor(4);
  pion_TOFClosestHits_truth->SetTitle("0ps");
  pion_TOFClosestHits_truth->GetYaxis()->SetTitle("TOFClosestHits");
  pion_TOFClosestHits_truth->GetXaxis()->SetTitle("p");
  pion_TOFClosestHits_truth->Draw("p");
  kaon_TOFClosestHits_truth->SetMarkerColor(2);
  kaon_TOFClosestHits_truth->SetLineColor(2);
  kaon_TOFClosestHits_truth->Draw("psame");
  proton_TOFClosestHits_truth->SetMarkerColor(3);
  proton_TOFClosestHits_truth->SetLineColor(3);
  proton_TOFClosestHits_truth->Draw("psame");


  c_test->cd(3);
  gPad->SetLogx();
  for(int i=0; i<33; i++){
    for(int j=0; j<99; j++){
      if(pion_TOFFlightLength_truth->GetBinContent(i+1,j+1)>1) pion_TOFFlightLength_truth->SetBinContent(i+1,j+1,50./pion_TOFFlightLength_truth->GetBinContent(i+1,j+1));
      else  pion_TOFFlightLength_truth->SetBinContent(i+1,j+1,0);
      if(kaon_TOFFlightLength_truth->GetBinContent(i+1,j+1)>1) kaon_TOFFlightLength_truth->SetBinContent(i+1,j+1,50./kaon_TOFFlightLength_truth->GetBinContent(i+1,j+1));
      else  kaon_TOFFlightLength_truth->SetBinContent(i+1,j+1,0);
      if(proton_TOFFlightLength_truth->GetBinContent(i+1,j+1)>1) proton_TOFFlightLength_truth->SetBinContent(i+1,j+1,50./proton_TOFFlightLength_truth->GetBinContent(i+1,j+1));
      else  proton_TOFFlightLength_truth->SetBinContent(i+1,j+1,0);
    }
  }
  pion_TOFFlightLength_truth->SetMarkerColor(4);
  pion_TOFFlightLength_truth->SetLineColor(4);
  pion_TOFFlightLength_truth->SetTitle("0ps");
  pion_TOFFlightLength_truth->GetYaxis()->SetTitle("TOFFlightLength");
  pion_TOFFlightLength_truth->GetXaxis()->SetTitle("p");
  pion_TOFFlightLength_truth->Draw("p");
  kaon_TOFFlightLength_truth->SetMarkerColor(2);
  kaon_TOFFlightLength_truth->SetLineColor(2);
  kaon_TOFFlightLength_truth->Draw("psame");
  proton_TOFFlightLength_truth->SetMarkerColor(3);
  proton_TOFFlightLength_truth->SetLineColor(3);
  proton_TOFFlightLength_truth->Draw("psame");


  c_test->cd(4);
  gPad->SetLogx();
  for(int i=0; i<33; i++){
    for(int j=0; j<99; j++){
      if(pion_TOFLastTrkHit_truth->GetBinContent(i+1,j+1)>1) pion_TOFLastTrkHit_truth->SetBinContent(i+1,j+1,50./pion_TOFLastTrkHit_truth->GetBinContent(i+1,j+1));
      else  pion_TOFLastTrkHit_truth->SetBinContent(i+1,j+1,0);
      if(kaon_TOFLastTrkHit_truth->GetBinContent(i+1,j+1)>1) kaon_TOFLastTrkHit_truth->SetBinContent(i+1,j+1,50./kaon_TOFLastTrkHit_truth->GetBinContent(i+1,j+1));
      else  kaon_TOFLastTrkHit_truth->SetBinContent(i+1,j+1,0);
      if(proton_TOFLastTrkHit_truth->GetBinContent(i+1,j+1)>1) proton_TOFLastTrkHit_truth->SetBinContent(i+1,j+1,50./proton_TOFLastTrkHit_truth->GetBinContent(i+1,j+1));
      else  proton_TOFLastTrkHit_truth->SetBinContent(i+1,j+1,0);
    }
  }
  pion_TOFLastTrkHit_truth->SetMarkerColor(4);
  pion_TOFLastTrkHit_truth->SetLineColor(4);
  pion_TOFLastTrkHit_truth->SetTitle("0ps");
  pion_TOFLastTrkHit_truth->GetYaxis()->SetTitle("TOFLastTrkHit");
  pion_TOFLastTrkHit_truth->GetXaxis()->SetTitle("p");
  pion_TOFLastTrkHit_truth->Draw("p");
  kaon_TOFLastTrkHit_truth->SetMarkerColor(2);
  kaon_TOFLastTrkHit_truth->SetLineColor(2);
  kaon_TOFLastTrkHit_truth->Draw("psame");
  proton_TOFLastTrkHit_truth->SetMarkerColor(3);
  proton_TOFLastTrkHit_truth->SetLineColor(3);
  proton_TOFLastTrkHit_truth->Draw("psame");

  c_test->cd(5);
  //gPad->SetLogx();
  
  //   for(int i=0; i<33; i++){
  //  for(int j=0; j<99; j++){
  //    // if(j>80)  pion_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,0);
      
  //    if(pion_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)>1) pion_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,100./pion_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1));
  //    else  pion_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,0);
      
  //    if(kaon_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)>1) kaon_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,100./kaon_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1));
  //    else  kaon_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,0);
  //    if(proton_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)>1) proton_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,100./proton_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1));
  //    else  proton_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,0);
  //    
  //  }
 // }

  // for(int i=0; i<33; i++){
  //  double npion=0;
  //  double nkaon=0;
  //  double nproton=0;
  //  for(int j=0; j<99; j++){
  //    npion+=pion_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1);
  //    nkaon+=kaon_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1);
  //    nproton+=proton_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1);
   // }
  //  for(int j=0; j<99; j++){
  //    if(pion_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)>1) pion_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,pion_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)/npion);
  //    else  pion_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,0);
  //    
  //    if(kaon_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)>1) kaon_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,kaon_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)/nkaon);
  //   else  kaon_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,0);
  //    if(proton_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)>1) proton_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,proton_TOFLastTrkHitFlightLength_truth->GetBinContent(i+1,j+1)/nproton);
  //    else  proton_TOFLastTrkHitFlightLength_truth->SetBinContent(i+1,j+1,0);
  //  }
  //  }

  cout<<pion_TOFLastTrkHitFlightLength_truth->Integral(0,33,80,90)<<" "<<kaon_TOFLastTrkHitFlightLength_truth->Integral(0,33,80,90)<<" "<<proton_TOFLastTrkHitFlightLength_truth->Integral(0,33,80,90)<<endl;
  cout<<pion_TOFLastTrkHitFlightLength_truth->Integral()<<" "<<kaon_TOFLastTrkHitFlightLength_truth->Integral()<<" "<<proton_TOFLastTrkHitFlightLength_truth->Integral()<<endl;
    
  pion_TOFLastTrkHitFlightLength_truth->SetMarkerColor(4);
  pion_TOFLastTrkHitFlightLength_truth->SetLineColor(4);
  pion_TOFLastTrkHitFlightLength_truth->SetTitle("0ps");
  pion_TOFLastTrkHitFlightLength_truth->GetYaxis()->SetTitle("TOFLastTrkHitFlightLength");
  pion_TOFLastTrkHitFlightLength_truth->GetXaxis()->SetTitle("p");
  pion_TOFLastTrkHitFlightLength_truth->Draw("p");
  kaon_TOFLastTrkHitFlightLength_truth->SetMarkerColor(2);
  kaon_TOFLastTrkHitFlightLength_truth->SetLineColor(2);
  kaon_TOFLastTrkHitFlightLength_truth->Draw("psame");
  proton_TOFLastTrkHitFlightLength_truth->SetMarkerColor(3);
  proton_TOFLastTrkHitFlightLength_truth->SetLineColor(3);
  proton_TOFLastTrkHitFlightLength_truth->Draw("psame");
  //  return;
  */
  
  //kaon
  float x_kaon[100], y_kaon[100], ey_kaon[100];
  int n_kaon=0;
  for(int i=0; i<kaon_dEdx_truth->GetNbinsX(); i++) {
    if( kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1) >momentum_min  ) {
      TH1D * proj_kaon =kaon_dEdx_truth->ProjectionY("proj_kaon",i,i+1);
      
      x_kaon[n_kaon]=kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
      y_kaon[n_kaon]=proj_kaon->GetMean();
      ey_kaon[n_kaon]=proj_kaon->GetRMS();
      n_kaon++;
    }
  }
  TGraphErrors *kaonproj= new TGraphErrors(n_kaon,x_kaon,y_kaon,0,ey_kaon);
  //pion
  float x_pion[100], y_pion[100], ey_pion[100];
  int n_pion=0;
  for(int i=0; i<pion_dEdx_truth->GetNbinsX(); i++) {
    if( pion_dEdx_truth->GetXaxis()->GetBinCenter(i+1) > momentum_min ) {
      TH1D * proj_pion =pion_dEdx_truth->ProjectionY("proj_pion",i,i+1);
      
      x_pion[n_pion]=pion_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
      y_pion[n_pion]=proj_pion->GetMean();
      ey_pion[n_pion]=proj_pion->GetRMS();
      n_pion++;
    }
  }
  TGraphErrors *pionproj= new TGraphErrors(n_pion,x_pion,y_pion,0,ey_pion);
  //proton
  float x_proton[100], y_proton[100], ey_proton[100];
  int n_proton=0;
  for(int i=0; i<proton_dEdx_truth->GetNbinsX(); i++) {
    if( proton_dEdx_truth->GetXaxis()->GetBinCenter(i+1) > momentum_min ) {
      TH1D * proj_proton =proton_dEdx_truth->ProjectionY("proj_proton",i,i+1);
      
      x_proton[n_proton]=proton_dEdx_truth->GetXaxis()->GetBinCenter(i+1);
      y_proton[n_proton]=proj_proton->GetMean();
      ey_proton[n_proton]=proj_proton->GetRMS();
      n_proton++;
    }
  }
  TGraphErrors *protonproj= new TGraphErrors(n_proton,x_proton,y_proton,0,ey_proton);


  //----------------------------------------------------------------------------------------
  TCanvas* c_calculateparam = new TCanvas("c_calculateparam","c_calculateparam",1000,800);
  pionproj->SetMarkerColor(4);
  pionproj->SetLineColor(4);
  pionproj->SetTitle("dE/dx projection");
  pionproj->GetYaxis()->SetTitle("dE/dx#times10^{-6}");
  pionproj->GetXaxis()->SetTitle("p");
  pionproj->Draw("ap");

  kaonproj->SetMarkerColor(2);
  kaonproj->SetLineColor(2);
  kaonproj->Draw("p");

  protonproj->SetMarkerColor(3);
  protonproj->SetLineColor(3);
  protonproj->Draw("p"); 

  TF1 *f1= new TF1("f1","[0]+[1]*std::log(x)",2,100);
  f1->SetLineColor(2);
  kaonproj->Fit(f1,"REM");

  double x[100], y[100];
  

    for(int ieff=0; ieff<11; ieff++) {
    float eff=0.45+0.05*ieff;
    
    double a=f1->GetParameter(0);
    double b=f1->GetParameter(1);
    
    double a_up=0;
    double a_down=0;
    float max_purity=0;
    float max_eff=0;
    
    for(int j=0; j<50; j++) {
      for(int k=0; k<50; k++) {
	double ea=(0.1+0.1*j)*f1->GetParError(0);
	double ea2=-(0.1+0.1*k)*f1->GetParError(0);
	
	double int_pion=0;
	double int_kaon=0;
	double int_proton=0;
	double int_kaon_total=0;
	
	for(int i=0; i<kaon_dEdx_truth->GetNbinsX(); i++) {
	  TH1D * proj_kaon =kaon_dEdx_truth->ProjectionY("proj_kaon",i,i+1);
	  int_kaon_total+=proj_kaon->GetEntries();
	  if( kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1) > momentum_min ) {
	    TH1D * proj_pion =pion_dEdx_truth->ProjectionY("proj_pion",i,i+1);
	    TH1D * proj_proton =proton_dEdx_truth->ProjectionY("proj_proton",i,i+1);
	    
	    for(int j1=0; j1<proj_pion->GetNbinsX(); j1++) {
	      double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
	      double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
	      if(proj_pion->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_pion->GetXaxis()->GetBinCenter(j1)> yminus) int_pion+=proj_pion->GetBinContent(j1);
	    }
	    
	    for(int j1=0; j1<proj_kaon->GetNbinsX(); j1++) {
	      double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
	      double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
	      if(proj_kaon->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_kaon->GetXaxis()->GetBinCenter(j1)> yminus) int_kaon+=proj_kaon->GetBinContent(j1);
	    }
	    
	    for(int j1=0; j1<proj_proton->GetNbinsX(); j1++) {
	      double yplus = a+ea + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
	      double yminus = a+ea2 + b* std::log(kaon_dEdx_truth->GetXaxis()->GetBinCenter(i+1));
	      
	      if(proj_proton->GetXaxis()->GetBinCenter(j1)< yplus &&  proj_proton->GetXaxis()->GetBinCenter(j1)> yminus) int_proton+=proj_proton->GetBinContent(j1);
	    }	
	  }
	}
	
	if((int_proton+int_pion+int_kaon)/int_kaon_total>eff ) {
	  // cout<<j<<" "<<k<< "  ->  eff: "<< int_kaon/int_kaon_total<<" purity: "<<1.-(int_proton+int_pion)/int_kaon<<" (pion:"<<1.-(int_pion)/int_kaon<<") (proton:"<<1.-(int_proton)/int_kaon<<")"<<endl;
	  if( int_kaon/(int_proton+int_pion+int_kaon)  > max_purity) {
	    max_purity = int_kaon/(int_proton+int_pion+int_kaon);
	    max_eff= (int_proton+int_pion+int_kaon)/int_kaon_total;
	    a_up=a+ea;
	    a_down=a+ea2;
	    //	cout<<" purity="<<max_purity<<" eff="<<(int_proton+int_pion+int_kaon)/int_kaon_total<<";    slope="<<b<<" upper="<<a+ea<<" lower="<<a+ea2<<endl;
	  }
	}
      }
    }
    cout<<"eff_input>"<<eff<<":     purity="<<max_purity<<" eff="<<max_eff<<";    slope="<<b<<" upper="<<a_up<<" lower="<<a_down<<endl;
    x[ieff]=eff;
    y[ieff]=max_purity;
    a_up=0;
    a_down=0;
    max_purity=0;
    max_eff= 0;
  }

  TGraph *eff_purity = new TGraph(11,x,y);
  TFile *file = new TFile("eff_pur_s5_valencia1.4.root","RECREATE");
  file->cd();
  eff_purity->SetName("eff_purity");
  eff_purity->Write();

  
  file->Close();

  
    
}
