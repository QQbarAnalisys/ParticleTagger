#define kaontagger_cxx
#include "kaontagger.h"
#include "TPad.h"

void kaontagger::Initialize() {

  Float_t bins_p[]={0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9,1,1.33,1.667,2,2.5,3,4,5,6,7,8,9,10,13.33,16.667,20,30,40,50,60,70,80,90,100};
  Int_t nbinnum_p=sizeof(bins_p)/sizeof(Float_t) - 1;

  Float_t binsy[200];
  binsy[0]=0.1;
  for(int i=1;i<200;i++) binsy[i]=binsy[i-1]+0.1/100.;
  Int_t nbinnumy=199;

  Float_t bins_costheta[200];
  bins_costheta[0]=0;
  for(int i=1;i<200;i++) bins_costheta[i]=bins_costheta[i-1]+1/200.;
  Int_t nbinnum_costheta=199;

  n_kaon=0;
  n_pion=0;
  n_proton=0;
  n_electron=0;
  n_muon=0;
  n_other=0;

  cont_pi=0;
  cont_p=0;
  cont_e=0;
  cont_mu=0;

  cont_DST_pi=0;
  cont_DST_p=0;
  cont_DST_e=0;
  cont_DST_mu=0;
  
  kaon_dEdx_truth = new TH2F("kaon_dEdx_truth","kaon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_truth = new TH2F("proton_dEdx_truth","proton_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_truth = new TH2F("pion_dEdx_truth","pion_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  electron_dEdx_truth = new TH2F("electron_dEdx_truth","electron_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  muon_dEdx_truth = new TH2F("muon_dEdx_truth","muon_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);
  other_dEdx_truth = new TH2F("other_dEdx_truth","other_dEdx_truth",nbinnum_p,bins_p,nbinnumy,binsy);

  //to fill with the new ID algorithm
  kaon_dEdx_id = new TH2F("kaon_dEdx_id","kaon_dEdx_id",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_id = new TH2F("proton_dEdx_id","proton_dEdx_id",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_id = new TH2F("pion_dEdx_id","pion_dEdx_id",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_good = new TH2F("kaon_dEdx_good","kaon_dEdx_good",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_good = new TH2F("proton_dEdx_good","proton_dEdx_good",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_good = new TH2F("pion_dEdx_good","pion_dEdx_good",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_bad = new TH2F("kaon_dEdx_bad","kaon_dEdx_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_bad = new TH2F("proton_dEdx_bad","proton_dEdx_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_bad = new TH2F("pion_dEdx_bad","pion_dEdx_bad",nbinnum_p,bins_p,nbinnumy,binsy);


  //to fill with the ID algorithm in the DST (dEdxID)
  kaon_dEdx_ID_DST_id = new TH2F("kaon_dEdx_ID_DST_id","kaon_dEdx_ID_DST_id",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_ID_DST_id = new TH2F("proton_dEdx_ID_DST_id","proton_dEdx_ID_DST_id",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_ID_DST_id = new TH2F("pion_dEdx_ID_DST_id","pion_dEdx_ID_DST_id",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_ID_DST_good = new TH2F("kaon_dEdx_ID_DST_good","kaon_dEdx_ID_DST_good",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_ID_DST_good = new TH2F("proton_dEdx_ID_DST_good","proton_dEdx_ID_DST_good",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_ID_DST_good = new TH2F("pion_dEdx_ID_DST_good","pion_dEdx_ID_DST_good",nbinnum_p,bins_p,nbinnumy,binsy);

  kaon_dEdx_ID_DST_bad = new TH2F("kaon_dEdx_ID_DST_bad","kaon_dEdx_ID_DST_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  proton_dEdx_ID_DST_bad = new TH2F("proton_dEdx_ID_DST_bad","proton_dEdx_ID_DST_bad",nbinnum_p,bins_p,nbinnumy,binsy);
  pion_dEdx_ID_DST_bad = new TH2F("pion_dEdx_ID_DST_bad","pion_dEdx_ID_DST_bad",nbinnum_p,bins_p,nbinnumy,binsy);

  

}

void kaontagger::Fill_histos_new_ID(int i) {

  
      bool isproton = false;
      bool ispion = false;
      bool iselectron = false;
      bool iskaon = false;
      
      //proton
      if( (  momentum[i]<2 && type_algo3[i]==2212)  || (type_algo4[i]==2212 && momentum[i]>2 ) )  isproton=true;
      //pion
      if( (type_algo0[i]==211 ) || (momentum[i]>0.8 && type_algo4[i]==211)   ) ispion=true;
      //electron
      if( (type_algo0[i]==11 || type_algo0[i]==211) && dEdx[i]*1e6>0.22  )  iselectron=true;
      //kaon
      if( (momentum[i]>2 && type_algo4[i]==321 )  ||  (momentum[i]<2 && type_algo3[i]==321) ) iskaon=true;
      if(dEdx[i]*1e6>0.20 && momentum[i]<5 ) iskaon=false;
    
      if(ispion==true || isproton==true || iselectron==true) iskaon=false;

      
      if(ispion) {
	pion_dEdx_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if(isproton) {
	proton_dEdx_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if( iskaon==true ) {
	kaon_dEdx_id->Fill(momentum[i],dEdx[i]*1e6);
	if(trueType[i]==2212) cont_p++;
	else if(trueType[i]==211) cont_pi++;
	else if(trueType[i]==11) cont_e++;
	else if(trueType[i]==13) cont_mu++;
      }
      
      if(isproton && trueType[i]==2212) proton_dEdx_good->Fill(momentum[i],dEdx[i]*1e6);
      if(isproton && trueType[i]!=2212) proton_dEdx_bad->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]==211) pion_dEdx_good->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]!=211) pion_dEdx_bad->Fill(momentum[i],dEdx[i]*1e6);

      if(iskaon && trueType[i]==321) kaon_dEdx_good->Fill(momentum[i],dEdx[i]*1e6);
      if(iskaon && trueType[i]!=321) kaon_dEdx_bad->Fill(momentum[i],dEdx[i]*1e6);

}


void kaontagger::Fill_histos_DST_ID(int i,int algo) {

  
      bool isproton = false;
      bool ispion = false;
      bool iselectron = false;
      bool iskaon = false;

      //algorithms are
      //0 LikelihoodPID
      //1 LowMomentumID
      //2 BasixVariablePID
      //3 dEdxPID
      if(algo==0) {
	if( type_algo0[i]==2212 )  isproton=true;
	if( type_algo0[i]==211  ) ispion=true;
	if( type_algo0[i]==11 )  iselectron=true;
	if( type_algo0[i]==321 ) iskaon=true;
      }
      if(algo==1) {
	if( type_algo1[i]==2212 )  isproton=true;
	if( type_algo1[i]==211  ) ispion=true;
	if( type_algo1[i]==11 )  iselectron=true;
	if( type_algo1[i]==321 ) iskaon=true;
      }
      if(algo==2) {
	if( type_algo2[i]==2212 )  isproton=true;
	if( type_algo2[i]==211  ) ispion=true;
	if( type_algo2[i]==11 )  iselectron=true;
	if( type_algo2[i]==321 ) iskaon=true;
      }
      
      if(algo==3) {
	if( type_algo3[i]==2212 )  isproton=true;
	if( type_algo3[i]==211  ) ispion=true;
	if( type_algo3[i]==11 )  iselectron=true;
	if( type_algo3[i]==321 ) iskaon=true;
      }
   
      if(ispion==true || isproton==true || iselectron==true) iskaon=false;

      if(ispion) {
	pion_dEdx_ID_DST_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if(isproton) {
	proton_dEdx_ID_DST_id->Fill(momentum[i],dEdx[i]*1e6);
      }
      if( iskaon==true ) {
	kaon_dEdx_ID_DST_id->Fill(momentum[i],dEdx[i]*1e6);
	if(trueType[i]==2212) cont_DST_p++;
	else if(trueType[i]==211) cont_DST_pi++;
	else if(trueType[i]==11) cont_DST_e++;
	else if(trueType[i]==13) cont_DST_mu++;
      }
      
      if(isproton && trueType[i]==2212) proton_dEdx_ID_DST_good->Fill(momentum[i],dEdx[i]*1e6);
      if(isproton && trueType[i]!=2212) proton_dEdx_ID_DST_bad->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]==211) pion_dEdx_ID_DST_good->Fill(momentum[i],dEdx[i]*1e6);
      if(ispion && trueType[i]!=211) pion_dEdx_ID_DST_bad->Fill(momentum[i],dEdx[i]*1e6);

      if(iskaon && trueType[i]==321) kaon_dEdx_ID_DST_good->Fill(momentum[i],dEdx[i]*1e6);
      if(iskaon && trueType[i]!=321) kaon_dEdx_ID_DST_bad->Fill(momentum[i],dEdx[i]*1e6);

}

  
void kaontagger::Selection(bool secondary=false, int algo=3)
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

      bool selection= (vtxType[i]==2 && abs(costheta[i])<0.95 && tpcHits[i]>60);
      if (secondary==false) selection=true;
      if (selection == false) continue;


      if(trueType[i]==321) {
       	kaon_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_kaon++;
      }
      if(trueType[i]==2212) {
       	proton_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_proton++;
      }
      if(trueType[i]==211) {
       	pion_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_pion++;
      }
      if(trueType[i]==13) {
       	muon_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_muon++;
      }
      if(trueType[i]==11) {
       	electron_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_electron++;
      }
      if(trueType[i]==11) {
       	other_dEdx_truth->Fill(momentum[i],dEdx[i]*1e6);
       	n_other++;
      }

      Fill_histos_DST_ID(i,algo);
      Fill_histos_new_ID(i);
	  
    }//for
    // }
    // if (Cut(ientry) < 0) continue;
  }

   std::cout<<"  "<<std::endl;
   std::cout<<"  ############### algorithm "<<algo<<" DST ###############  "<<std::endl;
  std::cout<<"Simulated kaons: "<<n_kaon<<", pions: "<<n_pion<<", protons: "<<n_proton<<", electrons: "<<n_electron<<", muons: "<<n_muon<<", other: "<<n_other<<std::endl;
  std::cout<<"Reco, kaons: "<<kaon_dEdx_ID_DST_id->GetEntries()<<", pions: "<<pion_dEdx_ID_DST_id->GetEntries()<<", protons: "<<proton_dEdx_ID_DST_id->GetEntries()<<std::endl;
  std::cout<<"Well Reco, kaons: "<<kaon_dEdx_ID_DST_good->GetEntries()<<", pions: "<<pion_dEdx_ID_DST_good->GetEntries()<<", protons: "<<proton_dEdx_ID_DST_good->GetEntries()<<std::endl;
  std::cout<<"Contamination in kaons id, pions:: "<<cont_DST_pi<<", protons: "<<cont_DST_p<<", electrons: "<<cont_DST_e<<", muons: "<<cont_DST_mu<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;
  std::cout<<"KAON ID: eff ="<<kaon_dEdx_ID_DST_id->GetEntries()/n_kaon<<"  purity="<<kaon_dEdx_ID_DST_good->GetEntries()/kaon_dEdx_ID_DST_id->GetEntries()<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;

  std::cout<<"  "<<std::endl;
  std::cout<<"  ############### new ID ###############  "<<std::endl;
  std::cout<<"Simulated kaons: "<<n_kaon<<", pions: "<<n_pion<<", protons: "<<n_proton<<", electrons: "<<n_electron<<", muons: "<<n_muon<<", other: "<<n_other<<std::endl;
  std::cout<<"Reco, kaons: "<<kaon_dEdx_id->GetEntries()<<", pions: "<<pion_dEdx_id->GetEntries()<<", protons: "<<proton_dEdx_id->GetEntries()<<std::endl;
  std::cout<<"Well Reco, kaons: "<<kaon_dEdx_good->GetEntries()<<", pions: "<<pion_dEdx_good->GetEntries()<<", protons: "<<proton_dEdx_good->GetEntries()<<std::endl;
  std::cout<<"Contamination in kaons id, pions:: "<<cont_pi<<", protons: "<<cont_p<<", electrons: "<<cont_e<<", muons: "<<cont_mu<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;
  std::cout<<"KAON ID: eff ="<<kaon_dEdx_id->GetEntries()/n_kaon<<"  purity="<<kaon_dEdx_good->GetEntries()/kaon_dEdx_id->GetEntries()<<std::endl;
  std::cout<<"  -------------------------------------------------------------------- "<<std::endl;

  Plots(algo);
  SimplePlot(algo);
}

void kaontagger::Plots(int algo) {

  TString title = "LikelihoodPID";
  if(algo==1) title = "LowMomMuID";
  if(algo==2) title = "BasicVariablePID";
  if(algo==3) title = "dEdxPID";

  gStyle->SetOptStat(0);
  
  TCanvas* c_dEdx_truth = new TCanvas("c_dEdx_new_vs_"+title,"c_dEdx_new_vs_"+title,2400,1200);
  c_dEdx_truth->Divide(4,2);
  c_dEdx_truth->cd(1);
  gPad->SetLogx();

  pion_dEdx_truth->SetMarkerColor(4);
  pion_dEdx_truth->SetLineColor(4);
  pion_dEdx_truth->SetTitle("Truth");
  pion_dEdx_truth->Draw("");

  other_dEdx_truth->SetMarkerColor(6);
  other_dEdx_truth->SetLineColor(6);
  other_dEdx_truth->Draw("same");

  kaon_dEdx_truth->SetMarkerColor(2);
  kaon_dEdx_truth->SetLineColor(2);
  kaon_dEdx_truth->Draw("same");

  proton_dEdx_truth->SetMarkerColor(3);
  proton_dEdx_truth->SetLineColor(3);
  proton_dEdx_truth->Draw("same");

  electron_dEdx_truth->SetMarkerColor(1);
  electron_dEdx_truth->SetLineColor(1);
  electron_dEdx_truth->Draw("same");

  muon_dEdx_truth->SetMarkerColor(5);
  muon_dEdx_truth->SetLineColor(5);
  muon_dEdx_truth->Draw("same");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.85);
  leg->AddEntry(electron_dEdx_truth,"e","lp");
  leg->AddEntry(pion_dEdx_truth,"pi","lp");
  leg->AddEntry(kaon_dEdx_truth,"K","lp");
  leg->AddEntry(proton_dEdx_truth,"p","lp");
  leg->AddEntry(muon_dEdx_truth,"mu","lp");
  leg->AddEntry(other_dEdx_truth,"other","lp");
  leg->Draw();


  c_dEdx_truth->cd(2);
  gPad->SetLogx();
  
  pion_dEdx_id->SetMarkerColor(4);
  pion_dEdx_id->SetLineColor(4);
  pion_dEdx_id->SetTitle("ID-optimized");
  pion_dEdx_id->Draw("");

  kaon_dEdx_id->SetMarkerColor(2);
  kaon_dEdx_id->SetLineColor(2);
  kaon_dEdx_id->Draw("same");

  proton_dEdx_id->SetMarkerColor(3);
  proton_dEdx_id->SetLineColor(3);
  proton_dEdx_id->Draw("same");

  TLegend *leg2 = new TLegend(0.6,0.55,0.8,0.85);
  leg2->AddEntry(pion_dEdx_truth,"pi","lp");
  leg2->AddEntry(kaon_dEdx_truth,"K","lp");
  leg2->AddEntry(proton_dEdx_truth,"p","lp");
  leg2->Draw();

  c_dEdx_truth->cd(3);
  gPad->SetLogx();
  
  pion_dEdx_good->SetMarkerColor(4);
  pion_dEdx_good->SetLineColor(4);
  pion_dEdx_good->SetTitle("Well Id (ID-optimized)");
  pion_dEdx_good->Draw("");

  kaon_dEdx_good->SetMarkerColor(2);
  kaon_dEdx_good->SetLineColor(2);
  kaon_dEdx_good->Draw("same");

  proton_dEdx_good->SetMarkerColor(3);
  proton_dEdx_good->SetLineColor(3);
  proton_dEdx_good->Draw("same");

  leg2->Draw();

  c_dEdx_truth->cd(4);
  gPad->SetLogx();
  
  pion_dEdx_bad->SetMarkerColor(4);
  pion_dEdx_bad->SetLineColor(4);
  pion_dEdx_bad->SetTitle("Badly Id (ID-optimized)");
  pion_dEdx_bad->Draw("");

  kaon_dEdx_bad->SetMarkerColor(2);
  kaon_dEdx_bad->SetLineColor(2);
  kaon_dEdx_bad->Draw("same");

  proton_dEdx_bad->SetMarkerColor(3);
  proton_dEdx_bad->SetLineColor(3);
  proton_dEdx_bad->Draw("same");
  leg2->Draw();


  c_dEdx_truth->cd(5);
  gPad->SetLogx();
  pion_dEdx_truth->Draw("");
  other_dEdx_truth->Draw("same");
  kaon_dEdx_truth->Draw("same");
  proton_dEdx_truth->Draw("same");
  electron_dEdx_truth->Draw("same");
  muon_dEdx_truth->Draw("same");

 
  leg->Draw();
  c_dEdx_truth->cd(6);
  gPad->SetLogx();
  
  pion_dEdx_ID_DST_id->SetMarkerColor(4);
  pion_dEdx_ID_DST_id->SetLineColor(4);
  pion_dEdx_ID_DST_id->SetTitle(title);
  pion_dEdx_ID_DST_id->Draw("");

  kaon_dEdx_ID_DST_id->SetMarkerColor(2);
  kaon_dEdx_ID_DST_id->SetLineColor(2);
  kaon_dEdx_ID_DST_id->Draw("same");

  proton_dEdx_ID_DST_id->SetMarkerColor(3);
  proton_dEdx_ID_DST_id->SetLineColor(3);
  proton_dEdx_ID_DST_id->Draw("same");

  leg2->Draw();

  c_dEdx_truth->cd(7);
  gPad->SetLogx();
  
  pion_dEdx_ID_DST_good->SetMarkerColor(4);
  pion_dEdx_ID_DST_good->SetLineColor(4);
  pion_dEdx_ID_DST_good->SetTitle("Well Id "+title);
  pion_dEdx_ID_DST_good->Draw("");

  kaon_dEdx_ID_DST_good->SetMarkerColor(2);
  kaon_dEdx_ID_DST_good->SetLineColor(2);
  kaon_dEdx_ID_DST_good->Draw("same");

  proton_dEdx_ID_DST_good->SetMarkerColor(3);
  proton_dEdx_ID_DST_good->SetLineColor(3);
  proton_dEdx_ID_DST_good->Draw("same");

  leg2->Draw();

  c_dEdx_truth->cd(8);
  gPad->SetLogx();
  
  pion_dEdx_ID_DST_bad->SetMarkerColor(4);
  pion_dEdx_ID_DST_bad->SetLineColor(4);
  pion_dEdx_ID_DST_bad->SetTitle("Badly Id "+title);
  pion_dEdx_ID_DST_bad->Draw("");

  kaon_dEdx_ID_DST_bad->SetMarkerColor(2);
  kaon_dEdx_ID_DST_bad->SetLineColor(2);
  kaon_dEdx_ID_DST_bad->Draw("same");

  proton_dEdx_ID_DST_bad->SetMarkerColor(3);
  proton_dEdx_ID_DST_bad->SetLineColor(3);
  proton_dEdx_ID_DST_bad->Draw("same");


  leg2->Draw();
  c_dEdx_truth->Print("plots_secondary/c_dEdx_new_vs_"+title+".png");
  
}




void kaontagger::SimplePlot(int algo) {

  TString title = "LikelihoodPID";
  if(algo==1) title = "LowMomMuID";
  if(algo==2) title = "BasicVariablePID";
  if(algo==3) title = "dEdxPID";
  
  gStyle->SetOptStat(0);
  TCanvas* c_dEdx = new TCanvas("c_dEdx_"+title,"c_dEdx_"+title,800,800);
  c_dEdx->cd(1);
  gPad->SetLogx();


  kaon_dEdx_truth->SetMarkerColor(2);
  kaon_dEdx_truth->SetLineColor(2);
  kaon_dEdx_truth->Draw("");
  
  kaon_dEdx_ID_DST_id->SetMarkerColor(3);
  kaon_dEdx_ID_DST_id->SetLineColor(3);
  kaon_dEdx_ID_DST_id->Draw("same");

  kaon_dEdx_id->SetMarkerColor(1);
  kaon_dEdx_id->SetLineColor(1);
  kaon_dEdx_id->Draw("same");

  TLegend *leg = new TLegend(0.6,0.55,0.8,0.85);
  leg->AddEntry(kaon_dEdx_truth,"K","lp");
  leg->AddEntry(kaon_dEdx_ID_DST_id,"K,"+title,"lp");
  leg->AddEntry(kaon_dEdx_id,"K, new ID","lp");
  leg->Draw();
  c_dEdx->Print("plots_secondary/c_dEdx_"+title+".png");
}
