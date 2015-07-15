// loads histograms from file the makes pretty plots

// C++                                             
#include <iostream>
#include <vector>

#include "TH1F.h"
#include "TFile.h"

#include "/home/users/bmarsh/Software/dataMCplotMaker/dataMCplotMaker.h"

void make_plots(){

    // muons

    TFile *muon_file = new TFile("mLL_mumu_histos.root");
    
    TH1F *mLL_mumu_u50 = (TH1F*) muon_file->GetObjectChecked("mLL_mumu_u50", "TH1F");
    mLL_mumu_u50->SetDirectory(0);
    TH1F *mLL_mumu_o50 = (TH1F*) muon_file->GetObjectChecked("mLL_mumu_o50", "TH1F");
    mLL_mumu_o50->SetDirectory(0);
    TH1F *mLL_mumu_ttb = (TH1F*) muon_file->GetObjectChecked("mLL_mumu_ttb", "TH1F");
    mLL_mumu_ttb->SetDirectory(0);
    TH1F *mLL_mumu_wpj = (TH1F*) muon_file->GetObjectChecked("mLL_mumu_wpj", "TH1F");
    mLL_mumu_wpj->SetDirectory(0);
    TH1F *mLL_mumu_data = (TH1F*) muon_file->GetObjectChecked("mLL_mumu_data", "TH1F");
    mLL_mumu_data->SetDirectory(0);

    vector<TH1F*> bkg;
    vector<string> titles;

    bkg.push_back(mLL_mumu_u50);
    bkg.push_back(mLL_mumu_o50);
    bkg.push_back(mLL_mumu_ttb);
    bkg.push_back(mLL_mumu_wpj);
    titles.push_back("DY (10<m_{LL}<50)");
    titles.push_back("DY (m_{LL}>50)");
    titles.push_back("ttbar");
    titles.push_back("W+jets");

    dataMCplotMaker(mLL_mumu_data, bkg, titles, "Dimuon invariant mass", "", "--outputName mLL_mumu_log.pdf --xAxisLabel M\\mu\\mu --lumi 20.6 --legendRight -0.50 --legendUp -0.04");
    dataMCplotMaker(mLL_mumu_data, bkg, titles, "Dimuon invariant mass", "", "--outputName mLL_mumu_lin.pdf --isLinear --xAxisLabel M\\mu\\mu --lumi 20.6 --legendRight -0.50 --legendUp -0.04");

    // j/psi

    TH1F *mLL_jpsi_u50 = (TH1F*) muon_file->GetObjectChecked("mLL_jpsi_u50", "TH1F");
    mLL_jpsi_u50->SetDirectory(0);
    TH1F *mLL_jpsi_o50 = (TH1F*) muon_file->GetObjectChecked("mLL_jpsi_o50", "TH1F");
    mLL_jpsi_o50->SetDirectory(0);
    TH1F *mLL_jpsi_ttb = (TH1F*) muon_file->GetObjectChecked("mLL_jpsi_ttb", "TH1F");
    mLL_jpsi_ttb->SetDirectory(0);
    TH1F *mLL_jpsi_wpj = (TH1F*) muon_file->GetObjectChecked("mLL_jpsi_wpj", "TH1F");
    mLL_jpsi_wpj->SetDirectory(0);
    TH1F *mLL_jpsi_data = (TH1F*) muon_file->GetObjectChecked("mLL_jpsi_data", "TH1F");
    mLL_jpsi_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_jpsi_u50);
    bkg.push_back(mLL_jpsi_o50);
    bkg.push_back(mLL_jpsi_ttb);
    bkg.push_back(mLL_jpsi_wpj);

    dataMCplotMaker(mLL_jpsi_data, bkg, titles, "\\mu\\mu invariant mass", "", "--outputName mLL_jpsi.pdf --xAxisLabel M\\mu\\mu --lumi 20.6 --isLinear --legendUp -0.06 --legendRight -0.05 --noOverflow --noDataMC");

    // upsilon

    TH1F *mLL_ups_data = (TH1F*) muon_file->GetObjectChecked("mLL_ups_data", "TH1F");
    mLL_ups_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_ups_data);
    titles.pop_back(); titles.pop_back(); titles.pop_back();
    
    dataMCplotMaker(new TH1F("","",1,0,1), bkg, titles, "\\mu\\mu invariant mass", "", "--outputName mLL_ups.pdf --xAxisLabel M\\mu\\mu --lumi 20.6 --isLinear --legendUp -0.06 --legendRight -0.05 --noOverflow --noDataMC --noLegend --noFill");

    // pfmet

    TH1F *pfmet_u50 = (TH1F*) muon_file->GetObjectChecked("pfmet_u50", "TH1F");
    pfmet_u50->SetDirectory(0);
    TH1F *pfmet_o50 = (TH1F*) muon_file->GetObjectChecked("pfmet_o50", "TH1F");
    pfmet_o50->SetDirectory(0);
    TH1F *pfmet_ttb = (TH1F*) muon_file->GetObjectChecked("pfmet_ttb", "TH1F");
    pfmet_ttb->SetDirectory(0);
    TH1F *pfmet_wpj = (TH1F*) muon_file->GetObjectChecked("pfmet_wpj", "TH1F");
    pfmet_wpj->SetDirectory(0);
    TH1F *pfmet_data = (TH1F*) muon_file->GetObjectChecked("pfmet_data", "TH1F");
    pfmet_data->SetDirectory(0);

    bkg.pop_back(); //bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(pfmet_u50);
    bkg.push_back(pfmet_o50);
    bkg.push_back(pfmet_ttb);
    bkg.push_back(pfmet_wpj);
    titles.push_back("DY (m_{LL}>50)");
    titles.push_back("ttbar");
    titles.push_back("W+jets");

    dataMCplotMaker(pfmet_data, bkg, titles, "pfmet (double muon)", "", "--outputName pfmet_mumu_log.pdf --xAxisLabel pfmet --lumi 20.6 --legendUp -0.06 --legendRight -0.05");

    // njets

    TH1F *njets_u50 = (TH1F*) muon_file->GetObjectChecked("njets_u50", "TH1F");
    njets_u50->SetDirectory(0);
    TH1F *njets_o50 = (TH1F*) muon_file->GetObjectChecked("njets_o50", "TH1F");
    njets_o50->SetDirectory(0);
    TH1F *njets_ttb = (TH1F*) muon_file->GetObjectChecked("njets_ttb", "TH1F");
    njets_ttb->SetDirectory(0);
    TH1F *njets_wpj = (TH1F*) muon_file->GetObjectChecked("njets_wpj", "TH1F");
    njets_wpj->SetDirectory(0);
    TH1F *njets_data = (TH1F*) muon_file->GetObjectChecked("njets_data", "TH1F");
    njets_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(njets_u50);
    bkg.push_back(njets_o50);
    bkg.push_back(njets_ttb);
    bkg.push_back(njets_wpj);

    dataMCplotMaker(njets_data, bkg, titles, "njets (double muon)", "p_{T}>40", "--outputName njets_mumu_log.pdf --xAxisLabel njets --lumi 20.6 --legendUp -0.06 --legendRight -0.05 --legendTextSize 0.025");

    // njets

    TH1F *nbtags_u50 = (TH1F*) muon_file->GetObjectChecked("nbtags_u50", "TH1F");
    nbtags_u50->SetDirectory(0);
    TH1F *nbtags_o50 = (TH1F*) muon_file->GetObjectChecked("nbtags_o50", "TH1F");
    nbtags_o50->SetDirectory(0);
    TH1F *nbtags_ttb = (TH1F*) muon_file->GetObjectChecked("nbtags_ttb", "TH1F");
    nbtags_ttb->SetDirectory(0);
    TH1F *nbtags_wpj = (TH1F*) muon_file->GetObjectChecked("nbtags_wpj", "TH1F");
    nbtags_wpj->SetDirectory(0);
    TH1F *nbtags_data = (TH1F*) muon_file->GetObjectChecked("nbtags_data", "TH1F");
    nbtags_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(nbtags_u50);
    bkg.push_back(nbtags_o50);
    bkg.push_back(nbtags_ttb);
    bkg.push_back(nbtags_wpj);

    dataMCplotMaker(nbtags_data, bkg, titles, "nbtags (double muon)", "p_{T}>40", "--outputName nbtags_mumu_log.pdf --xAxisLabel nbtags --lumi 20.6 --legendUp -0.06 --legendRight -0.05 --legendTextSize 0.025");


    // electrons

    TFile *ele_file = new TFile("mLL_ee_histos.root");
    
    TH1F *mLL_ee_u50 = (TH1F*) ele_file->GetObjectChecked("mLL_ee_u50", "TH1F");
    mLL_ee_u50->SetDirectory(0);
    TH1F *mLL_ee_o50 = (TH1F*) ele_file->GetObjectChecked("mLL_ee_o50", "TH1F");
    mLL_ee_o50->SetDirectory(0);
    TH1F *mLL_ee_ttb = (TH1F*) ele_file->GetObjectChecked("mLL_ee_ttb", "TH1F");
    mLL_ee_ttb->SetDirectory(0);
    TH1F *mLL_ee_wpj = (TH1F*) ele_file->GetObjectChecked("mLL_ee_wpj", "TH1F");
    mLL_ee_wpj->SetDirectory(0);
    TH1F *mLL_ee_data = (TH1F*) ele_file->GetObjectChecked("mLL_ee_data", "TH1F");
    mLL_ee_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_ee_u50);
    bkg.push_back(mLL_ee_o50);
    bkg.push_back(mLL_ee_ttb);
    bkg.push_back(mLL_ee_wpj);

    dataMCplotMaker(mLL_ee_data, bkg, titles, "ee invariant mass", "", "--outputName mLL_ee_log.pdf --xAxisLabel M_{ee} --lumi 19.9 --legendRight -0.50 --legendUp -0.04");
    dataMCplotMaker(mLL_ee_data, bkg, titles, "ee invariant mass", "", "--outputName mLL_ee_lin.pdf --isLinear --xAxisLabel M_{ee} --lumi 19.9 --legendRight -0.50 --legendUp -0.04");
    
 
}
