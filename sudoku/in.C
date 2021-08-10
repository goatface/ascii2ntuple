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
  
  Float_t puzzle_entry[datasets][rows][columns] = {0};

  Float_t energy[datasets][entries], sfactor[datasets][entries];
  for(int dataset=0;dataset<datasets;dataset++){ 
    file[dataset] = new TFile(Form("%01d.root",dataset));
    myNTuple[dataset] = (TNtuple*)(file[dataset]->Get("ntuple"))->Clone(Form("myNTuple%d",dataset));
    for (Int_t i=0;i<columns;i++){
      sprintf(parameter,"p%d",i);
      myNTuple[dataset]->SetBranchAddress(parameter,&p[i]);
    }
    cout << "This is the puzzle number: " << dataset<<  endl;
    for (Int_t thisrow=0;thisrow<rows;thisrow++){
      myNTuple[dataset]->GetEntry(thisrow);
      for (Int_t rowitem=0;rowitem<9;rowitem++){
        puzzle_entry[dataset][thisrow][rowitem]=p[rowitem];
        cout << puzzle_entry[dataset][thisrow][rowitem] << " " ;
      }
      cout << endl;
    }
    file[dataset]->Close();
  cout << "This is a solver array initialization" << endl; 
  const Int_t number_of_values=9;
  int solver[columns][rows][number_of_values] = {0};

  for (int i=0;i<rows;i++) {
    for (int j=0;j<columns;j++) {
      for (int k=0;k<number_of_values;k++) {
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
