#include <iostream>
#include <fstream>
#include <iomanip>
void analysis_txt(string logfilename, string outhistfilename, float xedge){
  ifstream inlogfile;
gStyle->SetOptStat(1001111);
gStyle->SetOptFit(111);
 Double_t x,y,z,edep;
 Double_t exyz[70][60][200],exyz2[70][60][200];
 Int_t n[70][60][200];
 Double_t xa[70], ya[60], za[200];
 int ia,ja,ka;
 string pN;
 const Float_t QFer=1.0;
 const Float_t QFnr=10.0;
 Float_t QF;
 for(ia=0;ia<70;ia++){
   xa[ia]=xedge+0.25+ia*0.5;
 }
 for(ja=0;ja<60;ja++){
   ya[ja]=-14.75+0.5*ja;
 }
 for(ka=0;ka<200;ka++){
   za[ka]=-49.75+ka*0.5;
 }
 for(ia=0;ia<70;ia++){
   for(ja=0;ja<60;ja++){
     for(ka=0;ka<200;ka++){
       exyz[ia][ja][ka]=0.;
       exyz2[ia][ja][ka]=0.;
       n[ia][ja][ka]=0;
     }
   }
 }
 inlogfile.open(logfilename);
   
 TH2F* hxy=new TH2F("hxy","x-y hit distribution",400,-100.,100.,400,-100.,100.);
 TH2F* hrcz=new TH2F("hrcz","rc-z hit distribution",200,0.,100.,400,-100.,100.);
 TH1F* hrewt=new TH1F("hrewt","Absorbed energy equivalent (keV) deposited versus distance",100,0.,100.);
 TH1F* hxewt=new TH1F("hxewt","Absorbed energy equivalent (keV) deposited versus x",400,-100.,100.);
 TH1F* hyewt=new TH1F("hyewt","Absorbed energy equivalent (keV) deposited versus y",400,-100.,100.);
 TH1F* hzewt=new TH1F("hzewt","Absorbed energy equivalent  (keV) deposited versus z",400,-100.,100.);
 TH1F* hrewter=new TH1F("hrewter","Absorbed energy (keV) deposited versus distance-ER",100,0.,100.);
 TH1F* hxewter=new TH1F("hxewter","Absorbed energy (keV) deposited versus x-ER",400,-100.,100.);
 TH1F* hyewter=new TH1F("hyewter","Absorbed energy (keV) deposited versus y-ER",400,-100.,100.);
 TH1F* hzewter=new TH1F("hzewter","Absorbed energy (keV) deposited versus z-ER",400,-100.,100.);
 TH1F* hrewtnr=new TH1F("hrewtnr","Absorbed energy (keV) deposited versus distance-NR",100,0.,100.);
 TH1F* hxewtnr=new TH1F("hxewtnr","Absorbed energy (keV) deposited versus x-NR",400,-100.,100.);
 TH1F* hyewtnr=new TH1F("hyewtnr","Absorbed energy (keV) deposited versus y-NR",400,-100.,100.);
 TH1F* hzewtnr=new TH1F("hzewtnr","Absorbed energy (keV) deposited versus z-NR",400,-100.,100.);
 char crootfilename[72], couthistfilename[72],ctreename[72];
 // Loop over files containing histogram to convert.
 // ifstream histfile(histfilelist);
 Int_t louthistfilename=outhistfilename.length();
 for (Int_t k=0;k<louthistfilename;k++){
   couthistfilename[k]=outhistfilename[k];
 }
 couthistfilename[louthistfilename]='\0';
 Float_t r,rc;
 Int_t counter=0;
 Int_t nmissed=0;
 while(!inlogfile.eof()){
   counter++;
     if (fmod(counter,1000000) == 0) cout << "Processed " << counter << " lines " << exyz[4][30][100] << " keV" << endl;
     inlogfile >> edep >> x >> y >> z >> pN;
   r=x*x+y*y+z*z;
   r=sqrt(r);
   rc=sqrt(x*x+y*y);
   hxy->Fill(x,y);
   hrcz->Fill(rc,z);
   if(pN == "e-"){
     hrewter->Fill(r,edep);
     hxewter->Fill(x,edep);
     hyewter->Fill(y,edep);
     hzewter->Fill(z,edep);
     QF=QFer;
   }
   else{
     hrewtnr->Fill(r,edep);
     hxewtnr->Fill(x,edep);
     hyewtnr->Fill(y,edep);
     hzewtnr->Fill(z,edep);
     QF=QFnr;
   }     
   hrewt->Fill(r,QF*edep);
   hxewt->Fill(x,QF*edep);
   hyewt->Fill(y,QF*edep);
   hzewt->Fill(z,QF*edep);
   ia=((x-xedge)/0.5);
   ja=(y+15)/0.5;
   ka=(z+50)/0.5;
   if(ia >= 0 && ia < 70 && ja >= 0 && ja < 60 && ka >= 0 && ka < 200){
     exyz[ia][ja][ka]=exyz[ia][ja][ka]+QF*edep;
     exyz2[ia][ja][ka]=exyz2[ia][ja][ka]+QF*edep*QF*edep;
     n[ia][ja][ka]++;
     //     if(counter > 173400){
     //       cout << edep << " " << x << " " << y << " " << z <<endl;
     //     }
   }
   else{
     //        cout << "ia,ja,ka: " << ia << " " << ja << " " << ka << endl;
     nmissed++;
     // Print the coordinates of the out-of-range hit
     //cout << "Hit out of range: " << x << " " << y << " " << z << endl;
   }
 }
 //Find the top 8000 cells
 Double_t emax[8000],xmax[8000],ymax[8000],zmax[8000],emax2[8000];
 Int_t nmax[8000];
 for(ia=0;ia<8000;ia++){
   emax[ia]=-1.;
 }
 Double_t relmax;
 for(Int_t la=0;la<8000;la++){
   if(la==0){
     relmax=1.e20;
   }
   else{
     relmax=emax[la-1];
   }
   for(ia=0;ia<70;ia++){
     for(ja=0;ja<60;ja++){
       for(ka=0;ka<200;ka++){
	 if(exyz[ia][ja][ka] > emax[la] && exyz[ia][ja][ka] < relmax){
	   emax[la]=exyz[ia][ja][ka];
	   emax2[la]=exyz2[ia][ja][ka];
	   nmax[la]=n[ia][ja][ka];
	   xmax[la]=xa[ia];
	   ymax[la]=ya[ja];
	   zmax[la]=za[ka];
       }
       }
     }
   }
 }
 //Sum over energy deposited in all cells
 Double_t topedepall=0;
   for(ia=0;ia<70;ia++){
     for(ja=0;ja<60;ja++){
       for(ka=0;ka<200;ka++){
	 topedepall=topedepall+exyz[ia][ja][ka];
       }
     }
   }
 //Sum over energy deposited in top 8000 cells (~1 kg)
 Double_t topedep1000g=0.;
 for(ia=0;ia<8000;ia++){
   topedep1000g=topedep1000g+emax[ia];
 }
 //Sum over energy deposited in top 800 cells (~100 g)
 Double_t topedep100g=0.;
 for(ia=0;ia<800;ia++){
   topedep100g=topedep100g+emax[ia];
 }
 //Sum over energy deposited in top 80 cells (~10 g)
 Double_t topedep10g=0.;
 for(ia=0;ia<80;ia++){
   topedep10g=topedep10g+emax[ia];
 }
 //Sum over energy deposited in top 8 cells (~1 g)
 Double_t topedep1g=0.;
 for(ia=0;ia<8;ia++){
   topedep1g=topedep1g+emax[ia];
 }
 cout << "Number of hits out of range: " << nmissed << endl;
 cout << "Number of hits in run: " << counter << endl;
 cout << "Total equivalent energy deposited in phantom: " << topedepall << " keV" << endl;
 cout << "Total equivalent energy deposited in hottest 1000 g: " << topedep1000g << " keV" << endl;
 cout << "Total equivalent energy deposited in hottest 100 g: " << topedep100g << " keV" << endl;
 cout << "Total equivalent energy deposited in hottest 10 g: " << topedep10g << " keV" << endl;
 cout << "Total equivalent energy deposited in hottest 1 g: " << topedep1g << " keV" << endl;
 for(ia=0;ia<10;ia++){
   Double_t unc=sqrt(emax2[ia]/nmax[ia] - pow(emax[ia]/nmax[ia],2.0));
   //   cout << "emax, emax2, n: " << emax[ia] << "," << emax2[ia] << "," << nmax[ia] << endl;
     cout << "rank, total equivalent energy (keV),(uncertainty (keV)),x,y,z: " << ia << " " << emax[ia] << " " << "(" << unc << ")" << " " << xmax[ia] << " " << ymax[ia] << " " << zmax[ia] << endl;
 }
     TFile *outfile = new TFile(couthistfilename,"NEW");
     outfile->cd();
     hxy->Write();
     hrcz->Write();
     hrewt->Write();
     hxewt->Write();
     hyewt->Write();
     hzewt->Write();
     hrewter->Write();
     hxewter->Write();
     hyewter->Write();
     hzewter->Write();
     hrewtnr->Write();
     hxewtnr->Write();
     hyewtnr->Write();
     hzewtnr->Write();
     outfile->Close();
 inlogfile.close();
}
