



//include histogram tools here
#include "plotTools.C"
//global hists?
class plotter{
 public:
 plotter( ewk& mclass, TFile*& outfile, std::string tag);
 void initHists(std::string tag);
 std::string _tag;
 TFile* f;
 TH1D* hmet;
 
};

void plotter::initHists(std::string tag){

	std::string varname = "met";
	std::string name = "MET; GeV; Events Per 1 GeV Bin";
	int bins = 100;
	double xlow = 100.;
	double xup = 200.;
	hmet = initTH1D( tag+varname, name, bins, xlow, xup );

}
plotter::plotter( ewk& mclass, TFile*& outfile, std::string tag){

   f = outfile;
   _tag = tag;
   initHists(tag);
 
 //begin loop
   if (mclass.fChain == 0) return;

   Long64_t nentries = mclass.fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = mclass.LoadTree(jentry);
      if (ientry < 0) break;
      nb = mclass.fChain->GetEntry(jentry);   nbytes += nb;
		
	   hmet->Fill( mclass.MET );	



   }//end loop


	plot(hmet, "MET", tag, 0);
	

}
