// ascii2ntuple.C version 0.2
//Fill a TNtuple with ASCII data
//User specifies the name of the file and number of columns
//As a TNtuple, all fields are taken as Float_t
//daid kahl 2011
#include "Riostream.h"

// How should the user invoke the macro?
void Usage(){
  printf ("Usage:\nascii2ntuple.C(const Int_t columns=0,const char *file)\n");
  printf ("\tcolumns: Number of columns.  Default: 0 (this message)\n");
  printf ("\tfile: Name of file (must be in double quotes as in \"goatface.dat\")\n");
  return;
}

// The macro
void ascii2ntuple(const Int_t columns=0, const char *file="") {
   if (columns==0){
     Usage();
     return;
   }
   if (columns>=15){
     printf ("TNtuple class cannot handle more than 14 parameters.  Try again with less data.\n");
     return;
   }
   //Checking if the file exists.
   ifstream ifile(file);
   if (!ifile.is_open()) {
     printf("Could not open the file \"%s\"\nPlease make sure the file exists and can be read\nExiting on error.\n",file);
     return; // exit with fail status
   }   
   ifile.close();
   
   ifstream in;
   in.open(file);
   Float_t p[columns];
   char varlist[200]="p0";
   char rootout[200];
   sprintf(rootout,"%s.root",file);
   TFile *f = new TFile(rootout,"RECREATE");
   for (Int_t i=0;i<columns;i++) {
       p[i] = 0.;
       if (i>0) sprintf(varlist,"%s%s%d",varlist,":p",i);
     }
   TNtuple *ntuple = new TNtuple("ntuple","data from ascii file",varlist);
   Int_t nlines = 0;
   while (1) { // run until we break
      for (Int_t i=0;i<columns;i++) in >> p[i]; // read in
      if (!in.good()) break; // break once the input is exhausted
      for (Int_t i=0;i<columns;i++) printf("%8f\t",p[i]); // print to stdout 
      cout << endl;
      // Now we are filling the ntuple
      // how to parameterize this one?
      // well, eventually I found out TNtuple only has max of 14 (at least in ROOT 5).  what a strange number.
      if (columns==1) ntuple->Fill(p[0]);
      if (columns==2) ntuple->Fill(p[0],p[1]);
      if (columns==3) ntuple->Fill(p[0],p[1],p[2]);
      if (columns==4) ntuple->Fill(p[0],p[1],p[2],p[3]);
      if (columns==5) ntuple->Fill(p[0],p[1],p[2],p[3],p[4]);
      if (columns==6) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5]);
      if (columns==7) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6]);
      if (columns==8) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7]);
      if (columns==9) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8]);
      if (columns==10) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9]);
      if (columns==11) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10]);
      if (columns==12) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11]);
      if (columns==13) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12]);
      if (columns==14) ntuple->Fill(p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],p[9],p[10],p[11],p[12],p[13]);
      nlines++;
   }
   printf(" found %d entries\n",nlines);
   in.close();
   f->Write();
}
