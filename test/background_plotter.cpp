void background_plotter(int rebin = 2, bool verbose = false, double lumi=36000.0){

	TFile* output = new TFile("stack_plots/stack_plots.root","RECREATE");

	vector<pair<TString,double> > backgrounds;
	vector<TString> datas;
	vector<TString> histos;
	vector<TString> leptontype;
	vector<pair<TString,double> > masspoint;

	// masspoint.push_back(make_pair("500",275.9*1.3/100000.0));
	// masspoint.push_back(make_pair("750",62.41*1.3/100000.0));
	// masspoint.push_back(make_pair("1000",20.05*1.3/98560.0));
	// masspoint.push_back(make_pair("2000",));
	// masspoint.push_back(make_pair("2500",));
	// masspoint.push_back(make_pair("3000",));
	// masspoint.push_back(make_pair("3500",));
	// masspoint.push_back(make_pair("4000",));
	// masspoint.push_back(make_pair("4500",));
	// masspoint.push_back(make_pair("5000",));

	backgrounds.push_back(make_pair("WJetsToLNu_Wpt-0To50.root",(1.0*57280.0)/(99983076.0*0.34)));
	backgrounds.push_back(make_pair("WJetsToLNu_Wpt-50To100.root",(1.0*3258.0)/(67082709.0*0.36)));
	backgrounds.push_back(make_pair("WJetsToLNu_Pt-100To250.root",(0.41*676.3)/(120124110.0*0.361348)));
	backgrounds.push_back(make_pair("WJetsToLNu_Pt-250To400.root",(0.43*23.94)/(12022587.0*0.368953)));
	backgrounds.push_back(make_pair("WJetsToLNu_Pt-400To600.root",(0.44*3.031)/(1939947.0*0.382909)));
	backgrounds.push_back(make_pair("WJetsToLNu_Pt-600ToInf.root",(0.44*0.4524)/(1974609.0*0.400576)));
	backgrounds.push_back(make_pair("singletop_schan.root",3.36/9651642.0));
	backgrounds.push_back(make_pair("singletop_tchan_top.root",136.02/5993676.0));
	backgrounds.push_back(make_pair("singletop_tchan_antitop.root",80.95/3928063.0));
	backgrounds.push_back(make_pair("singletop_tWchan_antitop.root",35.6/6952830.0));
	backgrounds.push_back(make_pair("singletop_tWchan_top.root",35.6/6933094.0));

	// backgrounds.push_back(make_pair("QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8.root",1.0));
	// backgrounds.push_back(make_pair("QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8.root",1.0));
	// backgrounds.push_back(make_pair("QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8.root",1.0));
	// backgrounds.push_back(make_pair("QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8.root",1.0));
	// backgrounds.push_back(make_pair("QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8.root",1.0));
	// backgrounds.push_back(make_pair("QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8.root",1.0));
	// backgrounds.push_back(make_pair("QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8.root",7823.0/4150588.0));

	backgrounds.push_back(make_pair("QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8.root",648.2/3959986.0));
	backgrounds.push_back(make_pair("QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8.root",186.9/3896412.0));
	backgrounds.push_back(make_pair("QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8.root",32.29/3992112.0));
	backgrounds.push_back(make_pair("QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8.root",9.418/2999069.0));
	backgrounds.push_back(make_pair("QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8.root",0.84265/396409.0));
	backgrounds.push_back(make_pair("QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8.root",0.114943/397660.0));
	backgrounds.push_back(make_pair("QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8.root",0.0068291/399226.0));
	backgrounds.push_back(make_pair("QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8.root",0.0001654/391735.0));

	datas.push_back("SingleElectron_2016_All.root");
	datas.push_back("singleMuon_ALL.root");

	leptontype.push_back("electron");
	leptontype.push_back("muon");

	histos.push_back("h_mttbar");
	// histos.push_back("h_mttbar_jes_down");
	// histos.push_back("h_mttbar_jes_up");
	// histos.push_back("h_mttbar_jer_down");
	// histos.push_back("h_mttbar_jer_up");
	// histos.push_back("h_mttbar_muon_down");
	// histos.push_back("h_mttbar_muon_up");
	// histos.push_back("h_mttbar_elec_down");
	// histos.push_back("h_mttbar_elec_up");

	for (unsigned l=0; l<leptontype.size(); l++){
	//Get ttbar and background hists
	TFile* f_ttbar = TFile::Open("output/" + leptontype[l] + "/background/ttbar_ALL.root");
		for (unsigned h=0; h<histos.size(); h++){
			TFile* f_back = TFile::Open("output/" + leptontype[l] + "/background/" + backgrounds[0].first);
			TH1D* h_ttbar = (TH1D*) f_ttbar->Get(histos[h]); h_ttbar->Scale(lumi*831.76/77081156.0);
			if (verbose) cout<<"output/" + leptontype[l] + "/background/ttbar_ALL.root"<<" "<<h_ttbar->GetEntries()<<endl;
			TH1D* h_back = (TH1D*) f_back->Get(histos[h]); h_back->Scale(lumi*backgrounds[0].second);
			if (verbose) cout<<"output/" + leptontype[l] + "/background/" + backgrounds[0].first<<" "<<h_back->GetEntries()<<endl;

			for (unsigned b=1; b<backgrounds.size(); b++){
			TFile* f_back = TFile::Open("output/" + leptontype[l] + "/background/" + backgrounds[b].first);
			TH1D* temp = (TH1D*) f_back->Get(histos[h]); 
			if (verbose) cout<<"output/" + leptontype[l] + "/background/" + backgrounds[b].first<<" "<<temp->GetEntries()<<endl;
			temp->Scale(lumi*backgrounds[b].second);
			// new TCanvas(); temp->Draw();
			h_back->Add(temp);

			}

			//Get signal
			TFile* f_signal = TFile::Open("output/" + leptontype[l] + "/signal/rsg_3000.root");
			TH1D* h_signal = (TH1D*) f_signal->Get(histos[h]); h_signal->Scale(lumi*0.1289*1.3/99755.0);
			if (verbose) cout<<"output/" + leptontype[l] + "/signal/rsg_3000.root"<<" "<<h_signal->GetEntries()<<endl;
			//Get data hist
			TFile* f_data = TFile::Open("output/" + leptontype[l] + "/data/" + datas[0]);

			TH1D* h_data = (TH1D*) f_data->Get(histos[h]);

			for (unsigned d=1; d<datas.size(); d++){
			f_data = TFile::Open("output/" + leptontype[l] + "/data/" + datas[d]);

			h_data->Add((TH1D*) f_data->Get(histos[h]));

			}

			if (rebin){
				h_data->Rebin(rebin);
				h_ttbar->Rebin(rebin);
				h_signal->Rebin(rebin);
				h_back->Rebin(rebin);
			}

			//Make stack
			TCanvas* c = new TCanvas("c_" + leptontype[l] + "_" + histos[h], "c_" + leptontype[l] + "_" + histos[h], 800,600);
			THStack* stack = new THStack(histos[h] + "_stack", histos[h] + ";" + h_ttbar->GetXaxis()->GetTitle() + ";" + h_ttbar->GetYaxis()->GetTitle());
			stack->SetMinimum(0);
			h_back->SetFillColor(kGreen);
			stack->Add(h_back);
			h_ttbar->SetFillColor(kRed);
			stack->Add(h_ttbar);
			h_data->SetMarkerStyle(2);
			stack->Draw("hist");
			h_data->SetMarkerStyle(8);
			h_data->Draw("samepe");
			h_signal->SetLineWidth(3);
			h_signal->Draw("samehist");
			TLegend* leg = new TLegend(0.55,0.55,0.9,0.9);
			leg->AddEntry(h_ttbar,"TTbar","f");
			leg->AddEntry(h_back,"Other backgrounds","f");
			leg->AddEntry(h_data,"Data","p");
			leg->AddEntry(h_signal,"Signal","l");
			leg->Draw();
			output->cd();
			c->Write();
			c->SaveAs("stack_plots/" + ((TString) c->GetName()) + ".png");


			cout<<"Data: "<<h_data->Integral()<<endl;
			cout<<"Background: "<<h_back->Integral()<<endl;
			cout<<"ttbar: "<<h_ttbar->Integral()<<endl;
			cout<<"Signal: "<<h_signal->Integral()<<endl;
		}
	}

	output->Write();

}