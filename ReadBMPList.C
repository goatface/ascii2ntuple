//### ROOT Libirary ##
#include <TH2F.h>
#include <TH2.h>
#include <TString.h>
#include <TImage.h>
#include <TMath.h>

//### C++ Libtary
#include <iostream>
#include <fstream>
using namespace std;

int ReadBMPList(){
	
  const int nbit = 8;//8bit BMP are used
	TString bmplist = "BMPlist.txt";//List of The BMP Data
  TString imgfile  ;

	TImage *img;
	TH2F *h2d = new TH2F("h2d","h2d",2500,0,2500,2500,0,2500);
	
	int ifile = 0;
	ifstream flist1;
	flist1.open(bmplist);
 
	UInt_t xmax_pix = 0 ;
	UInt_t ymax_pix = 0 ;
	UInt_t *rgb ;
	
	float zval = 0.0;
	int index = 0;
	int xcor = 0;
	int ycor = 0;
	int norm = TMath::Power(2,nbit);

	while(flist1 >> imgfile){
		img = TImage::Open(imgfile);
		xmax_pix = img->GetWidth();
		ymax_pix = img->GetHeight();
		rgb = img->GetArgbArray();
		for(UInt_t row = 0 ; row < xmax_pix; row ++){
			for(UInt_t col = 0; col < ymax_pix; col ++){
				index = col*xmax_pix + row;			
				zval = float(rgb[index]&0xff)/float(norm);
				xcor = row;
				ycor = ymax_pix - col;
				if(ifile == 0) h2d ->Fill(xcor,ycor,zval);
			}
		}
		ifile ++;
	}
	flist1.close();
	
	cout << "# of y pix = " << img->GetHeight() << " pixels" << endl;
	cout << "# of x pix = " << img->GetWidth()  << " pixels" << endl;

	h2d->GetXaxis()->SetRangeUser(0,xmax_pix);
	h2d->GetYaxis()->SetRangeUser(0,ymax_pix);
	h2d->Draw("colz");

	return 0;
}

