



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
 TH1D* hm_ll; //post 2 ll cuts
 TH1D* hn_jets;

 //these plots depend on categorization
 TH1D* hptcm;
 TH1D* hptisr;
 TH1D* hrisr;


 
 
};

void plotter::initHists(std::string tag){

	std::string varname = "met";
	std::string name = "MET; GeV; Events Per 10 GeV Bin";
	int bins = 90;
	double xlow = 100.;
	double xup = 1000.;
	hmet = initTH1D( tag+varname, name, bins, xlow, xup );

	varname = "mll";
	name = "OSSF Lepton Pair Mass; GeV; Events Per 1 GeV Bin";
	xup = 200.;
	xlow = 0.;
	bins = 200;
	hm_ll = initTH1D( tag+varname, name, bins, xlow, xup); 

	varname = "njet";
	name = " ; N jets";
	xup = 10.5;
	xlow = -0.5;
	bins = 11;
	hn_jets = initTH1D( tag+varname, name, bins, xlow, xup);

	varname = "ptcm";
	name = " PTCM; pT GeV; Events Per 10 GeV Bin"; 
	xup = 500.;
	xlow = 0.;
	bins = 50;
	hptcm = initTH1D( tag+varname, name , bins, xlow, xup);

	varname = "ptisr";
	name = " PTISR; pT GeV; Events Per 10 GeV Bin";
	xup = 1000.;
	xlow = 0.;
	bins = 100;
	hptisr = initTH1D( tag+varname, name, bins, xlow, xup);

	varname = "risr";
	name = " RISR; ;a.u.";
	xup = 3.;
	xlow = -1.;
	bins = 40;
	hrisr = initTH1D( tag+varname, name, bins, xlow, xup);


}
bool isOSSFPair(ewk& mclass){
	if( mclass.Nlep == 2 ){
		if( mclass.Nmu ==2 || mclass.Nele ==2 ){
			int qtot = 0;
			for(unsigned int i=0; i< mclass.Charge_lep->size(); i++){
				qtot += mclass.Charge_lep.at(i);
			}
			if( qtot == 0){
				return true;
			}
		}
	}
	return false;
}	
TLorentzVector* get4vec(double pt, double eta, double phi, double m){
	double px = pt*cos(phi);
	double py = pt*sin(phi);
	double pz = pt*sinh(eta);
	TLorentzVector *v = new TLorentzVector();
	v.SetXYZM( px,py,pz,m );
	return v;	
}
TLorentzVector* add4vecs( vector<double> pt, vector<double> eta, vector<double> phi, vector<double> m){

	TLorentzVector* p = new TLorentzVector();
	for(unsigned int i=0; i<pt.size(); i++){
		TLorentzVector *c = new TLorentzVector();
		c = get4vec(pt.at(i), eta.at(i), phi.at(i), m.at(i) );
		*p += *c;
	}
	return p;

} 
plotter::plotter( ewk& mclass, TFile*& outfile, std::string tag, int category){

   f = outfile;
   _tag = tag;
   initHists(tag);

	///// number of cuts /////	
	int cut0 = 0;
	int cut1 = 0;
 
 //begin loop
   if (mclass.fChain == 0) return;

   Long64_t nentries = mclass.fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = mclass.LoadTree(jentry);
      if (ientry < 0) break;
      nb = mclass.fChain->GetEntry(jentry);   nbytes += nb;
		
		cut0++;
		if( isOSSFPair(mclass) ){
			cut1++;
	   		hmet->Fill( mclass.MET, mclass.weight );
			hn_jets->Fill( mclass.Njet, mclass.weight);				

			TLorentzVector* ll = add4vecs( *(mclass.PT_lep), *(mclass.Eta_lep), *(mclass.Phi_lep), *(M_lep) );
		
			hm_ll->Fill(ll->M(), mclass.weight);

			//categorically dependent
			hptcm->Fill( mclass.PTCM->at(category) , mclass.weight);
			hptisr->Fill( mclass.PTISR->at(category), mclass.weight);
			hrisr->Fill( mclass.RISR->at(category), mclass.weight);	

	    }



   }//end loop


	std::cout<<"Cutflow for "<<tag<<" "<<category<<" "<<cut0<<" "<<cut1<<std::endl;
	plot(hmet, "MET", tag, 0);
	

}
