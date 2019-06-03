

TH1D* initTH1D( std::string varname, std::string name, int bins, double xlow, double xup){
	return new TH1D( varname.c_str(), name.c_str(), bins, xlow, xup);
}
TH2D* initTH2D( std::string varname, std::string name, int xbins, double xlow, double xup, int ybins, double ylow, double yup){
	return new TH2D( varname.c_str(), name.c_str(),xbins,xlow,xup,ybins,ylow,yup); 
}
void plot( TH1D* h , std::string cname , std::string tag, bool save){
	TCanvas *c = new TCanvas(cname.c_str(),"m",800,600);
	h->Draw();
	if(!save) return;
	c->Print((tag+cname+".pdf").c_str());
}
void plot( TH2D* h, std::string cname, std::string opt, std::string tag, bool save){
	TCanvas *c = new TCanvas(cname.c_str(), "m",800,600);
	h->Draw(opt.c_str());
    if(!save) return;
	c->Print((tag+cname+".pdf").c_str());
}
void plotsuper( std::vector<TH1D*> hvec, std::vector<int> colors, std::vector<std::string> hlegdesc,std::string legheader, std::string cname, std::string tag, bool save){
	
	TCanvas* c = new TCanvas(cname.c_str(),"m",800,600);
	int color =1;
	for(unsigned int i=0; i< colors.size(); i++){
		hvec.at(i)->SetLineColor(colors.at(i));
	}	
	hvec.at(0)->Draw();
	for(unsigned int i=0; i< hvec.size(); i++){
		if(i==2) hvec.at(i)->SetLineStyle(10);
		if(i==2) hvec.at(i)->SetLineWidth(3);
		hvec.at(i)->Draw("SAMES");
	}
	float ymax=800.0; float xlmin=0.35; float ylmin=0.58;
	const float dx=0.36;
	const float dy=0.26;
	TLegend* leg = new TLegend(xlmin,ylmin,xlmin+dx,ylmin+dy);
	leg->SetHeader(legheader.c_str(),"C");

	for(unsigned int i=0; i< hlegdesc.size(); i++){
		leg->AddEntry( hvec.at(i), hlegdesc.at(i).c_str(), "l");
	}

	leg->SetBorderSize(1);                          // Include border
	//leg->Draw();
    if(!save) return;
    c->Print((tag+cname+".pdf").c_str());
}
