//ROOT macro for reading in the TNtuple
{
 // TFile *f = new TFile("newgain.txt.root");
  //TFile *f = new TFile("AZUREOut_aa=2_R=2.extrap.root");
 

  // (++) = 1
  // (-+) = 0
  // (1/2)(3/2) interference, as Bardayan 2015 Fig 3
  //TFile *f = new TFile("AZUREOut_Bardayan_++_++.root");
  c1 = new TCanvas();
  c1->SetLogy();
  c1->cd(1);
//  const Int_t datasets = 7;
  const Int_t datasets = 4;
  const Int_t entries = 1091;
  //const Int_t entries = 990;
  //const Int_t entries = ntuple->GetEntries();
  // shared
  Float_t p[entries];
  char parameter[5];
  const Int_t columns=5;

  TFile *file[datasets];
  TNtuple *myNTuple[datasets];
  TGraph *gSfactor[datasets];
  
  //TLegend *legend = new TLegend(0.7,0.5,0.89,0.89);
  TLegend *legend = new TLegend(0.18,0.7,0.48,0.89);
  //TLegend *legend = new TLegend(0.2,0.2,0.4,0.4);
  legend->SetTextSize(0.035);
  legend->SetBorderSize(0);
  legend->SetFillColor(0);
  legend->SetMargin(0.5);

  Float_t energy[datasets][entries], sfactor[datasets][entries];
  for(int dataset=0;dataset<datasets;dataset++){ 
    file[dataset] = new TFile(Form("%01d.root",dataset));
    myNTuple[dataset] = (TNtuple*)(file[dataset]->Get("ntuple"))->Clone(Form("myNTuple%d",dataset));
    for (Int_t i=0;i<columns;i++){
      sprintf(parameter,"p%d",i);
      myNTuple[dataset]->SetBranchAddress(parameter,&p[i]);
    }
    for (Int_t i=0;i<entries;i++){
      myNTuple[dataset]->GetEntry(i);
      energy[dataset][i]=p[0];
      sfactor[dataset][i]=p[4];
    }
    gSfactor[dataset] = new TGraph(entries,energy[dataset],sfactor[dataset]);
    if (dataset == 0){
      gSfactor[dataset]->SetTitle("Test 13: ^{18}F(p,#alpha) S-factors - several 1/2+ and 3/2+ states");
      gSfactor[dataset]->GetXaxis()->SetTitle("E_{c.m.} (MeV)");
      gSfactor[dataset]->GetXaxis()->SetTitleSize(0.06);
      gSfactor[dataset]->GetXaxis()->SetLabelSize(0.05);
      gSfactor[dataset]->GetXaxis()->SetTitleOffset(0.9);
      gSfactor[dataset]->GetXaxis()->CenterTitle(true);
      gSfactor[dataset]->GetXaxis()->SetRangeUser(0,1.0);
      gSfactor[dataset]->GetYaxis()->SetTitle("S-factor (MeV b)");
      gSfactor[dataset]->GetYaxis()->SetTitleSize(0.06);
      gSfactor[dataset]->GetYaxis()->SetLabelSize(0.05);
      gSfactor[dataset]->GetYaxis()->SetTitleOffset(0.9);
      gSfactor[dataset]->GetYaxis()->CenterTitle(true);
      gSfactor[dataset]->GetYaxis()->SetRangeUser(1,1e5);
      gSfactor[dataset]->SetMarkerStyle(20);
      gSfactor[dataset]->SetMarkerColor(kBlue);
      gSfactor[dataset]->SetMarkerSize(0.5);
      gSfactor[dataset]->Draw("AL");
      gPad->SetBottomMargin(0.12);
      gPad->SetLeftMargin(0.12);
      gPad->Update();
      c1->Update();
      if (dataset == 0) gSfactor[dataset]->SetLineStyle(1);
    }else{
      if (dataset == 1) gSfactor[dataset]->SetLineStyle(2);
      if (dataset == 2) gSfactor[dataset]->SetLineStyle(1);
      if (dataset == 3) gSfactor[dataset]->SetLineStyle(2);
      if (dataset == 4) gSfactor[dataset]->SetLineStyle(9);
      gSfactor[dataset]->Draw("SAMEL");
    }
    if (dataset > 6) {
      gSfactor[dataset]->SetLineWidth(4.0);
    }else{
      gSfactor[dataset]->SetLineWidth(2.0);
    }
    if (dataset==0 || dataset==1) gSfactor[dataset]->SetLineColor(kBlue);
    //if (dataset>=2 && dataset<5) gSfactor[dataset]->SetLineColor(kBlue);
    if (dataset==6) gSfactor[dataset]->SetLineColor(kRed);
    //if (dataset==0) legend->AddEntry(gSfactor[dataset],Form("Constructive #frac{3}{2}^{+}"),"l");
    //if (dataset==1) legend->AddEntry(gSfactor[dataset],Form("Destructive #frac{3}{2}^{+}"),"l");
    //if (dataset==2) legend->AddEntry(gSfactor[dataset],Form("Dufour 2007 #frac{1}{2}^{+}"),"l");
    //if (dataset==3) legend->AddEntry(gSfactor[dataset],Form("Energy shifted #frac{1}{2}^{+}"),"l");
    //if (dataset==4) legend->AddEntry(gSfactor[dataset],Form("Energy & ANC shifted #frac{1}{2}^{+}"),"l");
    
    
    // segmentation fault in root6, what a joke
    //myNTuple[dataset]->Clear();
    //delete myNTuple[dataset];
    file[dataset]->Close();
  }
  legend->AddEntry(gSfactor[0],Form("1/2+, 3/2+, Constructive"),"l");
  legend->AddEntry(gSfactor[1],Form("1/2+, 3/2+, Destructive"),"l");
  legend->AddEntry(gSfactor[2],Form("3/2+, 1/2+, Constructive"),"l");
  legend->AddEntry(gSfactor[3],Form("3/2+, 1/2+, Destructive"),"l");
  //legend->AddEntry(gSfactor[6],Form("(+ +)(+ + +) with 1/2-"),"l");
  
  double energy_exp[1], energy_exp_error[1];
  energy_exp[0]=0.250;
  energy_exp_error[0]=0.0001;
  double sfactor_exp[1], sfactor_exp_error_low[1], sfactor_exp_error_high[1];
  sfactor_exp[0]=110;
  sfactor_exp_error_low[0]=70;
  sfactor_exp_error_high[0]=120;
  double *x = energy_exp;
  double *exl = energy_exp_error;
  double *exh = energy_exp_error;
  double *y = sfactor_exp;
  double *eyl = sfactor_exp_error_low;
  double *eyh = sfactor_exp_error_high;

  TGraphAsymmErrors *beer = new TGraphAsymmErrors(1,x,y,exl,exh,eyl,eyh);
  beer->SetMarkerStyle(33);
  beer->SetMarkerSize(2);
  beer->SetMarkerColor(kRed);
  beer->SetLineColor(kRed);
  beer->Draw("SAMEP");
  legend->AddEntry(beer,"Beer et al. (2011)","p");
  
  legend->Draw();
  return;

}
