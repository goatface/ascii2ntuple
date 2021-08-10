//ROOT macro for reading in the TNtuple
{
  const Int_t datasets = 1;
  const Int_t entries = 81;
  Float_t p[entries];
  char parameter[5];
  const Int_t columns=9;
  const Int_t rows=9;

  TFile *file[datasets];
  TNtuple *myNTuple[datasets];
  
  Float_t puzzle_entry[datasets][9][9] = {0};

  Float_t energy[datasets][entries], sfactor[datasets][entries];
  for(int dataset=0;dataset<datasets;dataset++){ 
    file[dataset] = new TFile(Form("%01d.root",dataset));
    myNTuple[dataset] = (TNtuple*)(file[dataset]->Get("ntuple"))->Clone(Form("myNTuple%d",dataset));
    for (Int_t i=0;i<columns;i++){
      sprintf(parameter,"p%d",i);
      myNTuple[dataset]->SetBranchAddress(parameter,&p[i]);
    }
    cout << "This is the puzzle number: " << dataset<<  endl;
    for (Int_t i=0;i<rows;i++){
      myNTuple[dataset]->GetEntry(i);
      for (Int_t goats=0;goats<9;goats++){
        puzzle_entry[dataset][i][goats]=p[goats];
        cout << puzzle_entry[dataset][i][goats] << " " ;
      }
      cout << endl;
    }
    file[dataset]->Close();
  cout << "This is a solver array initialization" << endl; 
  int solver[9][9][9] = {0};

  for (int i=0;i<9;i++) {
    for (int j=0;j<9;j++) {
      for (int k=0;k<9;k++) {
        solver[i][j][k]=-1;
        //solver[i][j][k]=solver[i][j][k]*-1;
        cout << solver[i][j][k];
      }
      cout << " ";
    }
    cout << endl;
  }

  // Now try to solve this
  



  }
  return;






















































}
