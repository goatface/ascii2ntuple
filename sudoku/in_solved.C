//ROOT macro for reading in the TNtuple
{
  bool flag_verbose = false;
  const int datasets = 1;
  const int entries = 81;
  float p[entries];
  char parameter[5];
  const int columns=9;
  const int rows=9;

  TFile *file[datasets];
  TNtuple *myNTuple[datasets];
  
  float puzzle_entry[datasets][rows][columns] = {0};

  float energy[datasets][entries], sfactor[datasets][entries];
  for(int dataset=0;dataset<datasets;dataset++){ 
    file[dataset] = new TFile(Form("%01d.root",dataset));
    myNTuple[dataset] = (TNtuple*)(file[dataset]->Get("ntuple"))->Clone(Form("myNTuple%d",dataset));
    for (int i=0;i<columns;i++){
      sprintf(parameter,"p%d",i);
      myNTuple[dataset]->SetBranchAddress(parameter,&p[i]);
    }
    cout << "This is the puzzle number: " << dataset<<  endl;
    for (int thisrow=0;thisrow<rows;thisrow++){
      myNTuple[dataset]->GetEntry(thisrow);
      for (int thiscolumn=0;thiscolumn<9;thiscolumn++){
        puzzle_entry[dataset][thisrow][thiscolumn]=p[thiscolumn];
        cout << puzzle_entry[dataset][thisrow][thiscolumn] << " " ;
      }
      cout << endl;
    }
    file[dataset]->Close();
    //cout << "This is a solver array initialization" << endl; 
    const int number_of_values=9;
    int solver[columns][rows][number_of_values] = {0};

    for (int thisrow=0;thisrow<rows;thisrow++) {
      for (int thiscolumn=0;thiscolumn<columns;thiscolumn++) {
        for (int thisvalue=0;thisvalue<number_of_values;thisvalue++) {
          solver[thisrow][thiscolumn][thisvalue]=-1;
          if (flag_verbose) cout << solver[thisrow][thiscolumn][thisvalue];
        }
        if (flag_verbose) cout << " ";
      }
      if (flag_verbose) cout << endl;
    }

    int loopcounter=0;
    int solversum=0;
    bool solved=false;
    cout << "Solver sum:\t";
    while(!solved){ 
      solversum=0;
      for (int thisrow=0;thisrow<rows;thisrow++) {
        for (int thiscolumn=0;thiscolumn<columns;thiscolumn++) {
          int boxsum=0;
          for (int thisvalue=0;thisvalue<number_of_values;thisvalue++) {
            // thisvalue+1 is used because our puzzle_entry valyes goes from 1 to 9 as in Sudoku;
	    // thisvalue goes from 0 to 8 as in a standard C++ array element access
	    if (puzzle_entry[dataset][thisrow][thiscolumn]==thisvalue+1 && solver[thisrow][thiscolumn][thisvalue]<0 ) {
              solver[thisrow][thiscolumn][thisvalue]=1;
	      // As thisvalue at thisrow and thiscolumn was determined, exclude all other thisvalue in solver
              for (int pushthisvalue=0;pushthisvalue<number_of_values;pushthisvalue++) {
                if (pushthisvalue!=thisvalue){
                  solver[thisrow][thiscolumn][pushthisvalue]=0;
                }
              }
	      // Exclude thisvalue throughout pushthisrow
              for (int pushthisrow=0;pushthisrow<rows;pushthisrow++) {
                if (puzzle_entry[dataset][pushthisrow][thiscolumn]<1 && solver[pushthisrow][thiscolumn][thisvalue]<0 && pushthisrow!=thisrow ) {
                  solver[pushthisrow][thiscolumn][thisvalue]=0;
                }
              }
	      // Excluse thisvalue throught pushthiscolumn
              for (int pushthiscolumn=0;pushthiscolumn<columns;pushthiscolumn++) {
                if (puzzle_entry[dataset][thisrow][pushthiscolumn]<1 && solver[thisrow][pushthiscolumn][thisvalue]<0 && pushthiscolumn!=thiscolumn ) {
                  solver[thisrow][pushthiscolumn][thisvalue]=0;
                }
              }
	      // Exclude thisvalue in the local 3x3 matrix, the boundaries of which are determined dynamically
              int boxrow=thisrow%3;
              int boxcolumn=thiscolumn%3;
              for (int pushthisrow=(thisrow-boxrow);pushthisrow<thisrow+(3-boxrow);pushthisrow++) {
                for (int pushthiscolumn=thiscolumn-boxcolumn;pushthiscolumn<thiscolumn+(3-boxcolumn);pushthiscolumn++) {
                  if (puzzle_entry[dataset][pushthisrow][pushthiscolumn]<1 && solver[pushthisrow][pushthiscolumn][thisvalue]<0 && pushthisrow!=thisrow && pushthiscolumn!=thiscolumn ) {
                    solver[pushthisrow][pushthiscolumn][thisvalue]=0;
                  }
                }
              }
            }
	    // Track solversum which is exactly 81 for a solved puzzle
            solversum+=solver[thisrow][thiscolumn][thisvalue];
	    // Track boxsum which is exactly -1 for a box with 8 excluded values
            boxsum+=solver[thisrow][thiscolumn][thisvalue];
          }
          if (boxsum==-1){
            for (int thisvalue=0;thisvalue<number_of_values;thisvalue++) {
              if (solver[thisrow][thiscolumn][thisvalue]==-1){
                puzzle_entry[dataset][thisrow][thiscolumn]=thisvalue+1;
              }
            }
          }
        }
      }
      loopcounter++;
      if (loopcounter>100 || solversum==81){
        solved=true;
      }
      cout << solversum << "\t";
    }
    cout << endl << "Finished in " << loopcounter << " iterations" << endl;
    
    // for debugging the solver
    if (flag_verbose) {
      cout << "This is the solver status" << endl; 
          							 
      for (int thisrow=0;thisrow<rows;thisrow++) {
        for (int thiscolumn=0;thiscolumn<columns;thiscolumn++) {
          for (int thisvalue=0;thisvalue<number_of_values;thisvalue++) {
            if (solver[thisrow][thiscolumn][thisvalue]==1){
              cout << "+" << solver[thisrow][thiscolumn][thisvalue];
            }else if(solver[thisrow][thiscolumn][thisvalue]==0){
              cout << " " << solver[thisrow][thiscolumn][thisvalue];
            }else{
              cout << solver[thisrow][thiscolumn][thisvalue];
            }
          }
          cout << " ";
        }
        cout << endl;
      }
    } 
    for (int thisrow=0;thisrow<rows;thisrow++){
      for (int thiscolumn=0;thiscolumn<9;thiscolumn++){
        cout << puzzle_entry[dataset][thisrow][thiscolumn] << " " ;
      }
      cout << endl;
    }
  }
  return;
}
