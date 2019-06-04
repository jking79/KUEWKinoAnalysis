
#include "ewk.C"
#include <iostream>
#include <string>
#include "plotter.C"

// run like this :  root -l -q "processData.C(\"abc\",\"def\")"
//root -l -q -b processData.C\(\"def.root\",\"def.root\"\) 
//dont need to actually use interpreter
void processData(std::string infilename, std::string treename, std::string outfilename, std::string tag){
	
	std::cout<<"Using Tag: "<<tag<<std::endl;
	ewk mclass(infilename, treename);
	TFile* outfile = new TFile(outfilename.c_str(), "RECREATE");
	plotter( mclass, outfile, tag);
	outfile->Write();
}
