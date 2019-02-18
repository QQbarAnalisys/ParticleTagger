#define CalculateParameters_cxx
#include "CalculateParameters.h"
#include "TPad.h"

void CalculateParameters::Initialize() {

  SetIrlesStyle();
  gStyle->SetOptFit(0); 
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(1);
  
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleStyle(0);
  gStyle->SetTitleX(0.3);
  gStyle->SetMarkerSize(0.1);


  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.33,1.667,2,2.5,3,4,5,6,7,8,9,10,13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  
  kaon_dEdx_truth = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_truth = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_truth = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  

}

  
void CalculateParameters::Parameters(bool secondary=false, float momentum_min =1.0)
{

  Initialize();
  if (fChain == 0) return;
   
  Long64_t nentries = fChain->GetEntriesFast();
 
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
      }
      if(trueType[i]==2212) {
       	proton_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
      }
      if(trueType[i]==211) {
       	pion_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
      }
      
    }//for
    // }
    // if (Cut(ientry) < 0) continue;
  }
  

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

  double a=f1->GetParameter(0);
  double b=f1->GetParameter(1);

  double a_up=0;
  double a_down=0;
  float max_purity=0;
  float max_eff=0;

  for(int j=0; j<100; j++) {
    for(int k=0; k<100; k++) {
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
      if((int_proton+int_pion+int_kaon)/int_kaon_total>0.5 ) {
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
  cout<<" CASE a (eff>0.5):     purity="<<max_purity<<" eff="<<max_eff<<";    slope="<<b<<" upper="<<a_up<<" lower="<<a_down<<endl;
    
  a_up=0;
  a_down=0;
  max_purity=0;
  max_eff= 0;

  
  for(int j=0; j<100; j++) {
    for(int k=0; k<100; k++) {
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
      if((int_proton+int_pion+int_kaon)/int_kaon_total>0.7 ) {
	// cout<<j<<" "<<k<< "  ->  eff: "<< int_kaon/int_kaon_total<<" purity: "<<1.-(int_proton+int_pion)/int_kaon<<" (pion:"<<1.-(int_pion)/int_kaon<<") (proton:"<<1.-(int_proton)/int_kaon<<")"<<endl;
	if( int_kaon/(int_proton+int_pion+int_kaon)  > max_purity) {
	  max_purity = int_kaon/(int_proton+int_pion+int_kaon);
	  max_eff= (int_proton+int_pion+int_kaon)/int_kaon_total;
	  a_up=a+ea;
	  a_down=a+ea2;
	}
      }
    }
  }
    cout<<" CASE b (eff>0.7):     purity="<<max_purity<<" eff="<<max_eff<<";    slope="<<b<<" upper="<<a_up<<" lower="<<a_down<<endl;

  
}
