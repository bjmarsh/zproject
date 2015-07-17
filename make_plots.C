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

    dataMCplotMaker(mLL_mumu_data, bkg, titles, "Dimuon invariant mass", "p_{T}>20/10", "--outputName mumu_mLL_log.pdf --xAxisLabel M\\mu\\mu --lumi 21.3 --legendRight -0.50 --legendUp -0.04");
    dataMCplotMaker(mLL_mumu_data, bkg, titles, "Dimuon invariant mass", "p_{T}>20/10", "--outputName mumu_mLL_lin.pdf --isLinear --xAxisLabel M\\mu\\mu --lumi 21.3 --legendRight -0.50 --legendUp -0.04");

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

    dataMCplotMaker(mLL_jpsi_data, bkg, titles, "\\mu\\mu invariant mass", "", "--outputName mumu_mLL_jpsi.pdf --xAxisLabel M\\mu\\mu --lumi 21.3 --isLinear --legendUp -0.06 --legendRight -0.05 --noOverflow --noDataMC");

    // upsilon

    TH1F *mLL_ups_data = (TH1F*) muon_file->GetObjectChecked("mLL_ups_data", "TH1F");
    mLL_ups_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_ups_data);
    titles.pop_back(); titles.pop_back(); titles.pop_back();
    
    dataMCplotMaker(new TH1F("","",1,0,1), bkg, titles, "\\mu\\mu invariant mass", "", "--outputName mumu_mLL_ups.pdf --xAxisLabel M\\mu\\mu --lumi 21.3 --isLinear --legendUp -0.06 --legendRight -0.05 --noOverflow --noDataMC --noLegend --noFill");

    // pfmet mumu

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

    dataMCplotMaker(pfmet_data, bkg, titles, "pfmet (double muon)", "", "--outputName mumu_pfmet.pdf --xAxisLabel pfmet --lumi 21.3 --legendUp -0.02 --legendRight -0.05");

    // njets mumu

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

    dataMCplotMaker(njets_data, bkg, titles, "njets (double muon)", "p_{T}>40", "--outputName mumu_njets.pdf --xAxisLabel njets --lumi 21.3 --legendUp -0.06 --legendRight -0.05 --noXaxisUnit --nDivisions 10");

    // nbtags mumu

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

    dataMCplotMaker(nbtags_data, bkg, titles, "nbtags (double muon)", "p_{T}>40", "--outputName mumu_nbtags.pdf --xAxisLabel nbtags --lumi 21.3 --legendUp -0.06 --legendRight -0.05 --noXaxisUnit  --nDivisions 5");

    // jetpt mumu

    TH1F *jetpt_u50 = (TH1F*) muon_file->GetObjectChecked("jetpt_u50", "TH1F");
    jetpt_u50->SetDirectory(0);
    TH1F *jetpt_o50 = (TH1F*) muon_file->GetObjectChecked("jetpt_o50", "TH1F");
    jetpt_o50->SetDirectory(0);
    TH1F *jetpt_ttb = (TH1F*) muon_file->GetObjectChecked("jetpt_ttb", "TH1F");
    jetpt_ttb->SetDirectory(0);
    TH1F *jetpt_wpj = (TH1F*) muon_file->GetObjectChecked("jetpt_wpj", "TH1F");
    jetpt_wpj->SetDirectory(0);
    TH1F *jetpt_data = (TH1F*) muon_file->GetObjectChecked("jetpt_data", "TH1F");
    jetpt_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(jetpt_u50);
    bkg.push_back(jetpt_o50);
    bkg.push_back(jetpt_ttb);
    bkg.push_back(jetpt_wpj);

    dataMCplotMaker(jetpt_data, bkg, titles, "leading jet p_{T} (double muon)", "", "--outputName mumu_jetpt.pdf --xAxisLabel p_{T} --lumi 21.3 --legendUp -0.02 --legendRight -0.05 --legendTextSize 0.025");

    // ht mumu

    TH1F *ht_u50 = (TH1F*) muon_file->GetObjectChecked("ht_u50", "TH1F");
    ht_u50->SetDirectory(0);
    TH1F *ht_o50 = (TH1F*) muon_file->GetObjectChecked("ht_o50", "TH1F");
    ht_o50->SetDirectory(0);
    TH1F *ht_ttb = (TH1F*) muon_file->GetObjectChecked("ht_ttb", "TH1F");
    ht_ttb->SetDirectory(0);
    TH1F *ht_wpj = (TH1F*) muon_file->GetObjectChecked("ht_wpj", "TH1F");
    ht_wpj->SetDirectory(0);
    TH1F *ht_data = (TH1F*) muon_file->GetObjectChecked("ht_data", "TH1F");
    ht_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(ht_u50);
    bkg.push_back(ht_o50);
    bkg.push_back(ht_ttb);
    bkg.push_back(ht_wpj);

    dataMCplotMaker(ht_data, bkg, titles, "H_{T} (double muon)", "jet p_{T}>40", "--outputName mumu_ht.pdf --xAxisLabel H_{T} --lumi 21.3 --legendUp -0.0w --legendRight -0.05 --legendTextSize 0.025");

    // nvertices mumu

    TH1F *nvertices_u50 = (TH1F*) muon_file->GetObjectChecked("nvertices_u50", "TH1F");
    nvertices_u50->SetDirectory(0);
    TH1F *nvertices_o50 = (TH1F*) muon_file->GetObjectChecked("nvertices_o50", "TH1F");
    nvertices_o50->SetDirectory(0);
    TH1F *nvertices_ttb = (TH1F*) muon_file->GetObjectChecked("nvertices_ttb", "TH1F");
    nvertices_ttb->SetDirectory(0);
    TH1F *nvertices_wpj = (TH1F*) muon_file->GetObjectChecked("nvertices_wpj", "TH1F");
    nvertices_wpj->SetDirectory(0);
    TH1F *nvertices_data = (TH1F*) muon_file->GetObjectChecked("nvertices_data", "TH1F");
    nvertices_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(nvertices_u50);
    bkg.push_back(nvertices_o50);
    bkg.push_back(nvertices_ttb);
    bkg.push_back(nvertices_wpj);

    dataMCplotMaker(nvertices_data, bkg, titles, "nvertices (double muon)", "", "--outputName mumu_nvertices.pdf --xAxisLabel nvertices --lumi 21.3 --legendUp -0.01 --legendRight -0.05 --isLinear --noXaxisUnit --nDivisions 15");


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

    dataMCplotMaker(mLL_ee_data, bkg, titles, "ee invariant mass", "p_{T}>30/20", "--outputName ee_mLL_log.pdf --xAxisLabel M_{ee} --lumi 21.3 --legendRight -0.50 --legendUp -0.04");
    dataMCplotMaker(mLL_ee_data, bkg, titles, "ee invariant mass", "p_{T}>30/20", "--outputName ee_mLL_lin.pdf --isLinear --xAxisLabel M_{ee} --lumi 21.3 --legendRight -0.50 --legendUp -0.04");
    

    // pfmet ee

    pfmet_u50 = (TH1F*) ele_file->GetObjectChecked("pfmet_u50", "TH1F");
    pfmet_u50->SetDirectory(0);
    pfmet_o50 = (TH1F*) ele_file->GetObjectChecked("pfmet_o50", "TH1F");
    pfmet_o50->SetDirectory(0);
    pfmet_ttb = (TH1F*) ele_file->GetObjectChecked("pfmet_ttb", "TH1F");
    pfmet_ttb->SetDirectory(0);
    pfmet_wpj = (TH1F*) ele_file->GetObjectChecked("pfmet_wpj", "TH1F");
    pfmet_wpj->SetDirectory(0);
    pfmet_data = (TH1F*) ele_file->GetObjectChecked("pfmet_data", "TH1F");
    pfmet_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(pfmet_u50);
    bkg.push_back(pfmet_o50);
    bkg.push_back(pfmet_ttb);
    bkg.push_back(pfmet_wpj);

    dataMCplotMaker(pfmet_data, bkg, titles, "pfmet (double electron)", "", "--outputName ee_pfmet.pdf --xAxisLabel pfmet --lumi 21.3 --legendUp -0.02 --legendRight -0.05");

    // njets ee

    njets_u50 = (TH1F*) ele_file->GetObjectChecked("njets_u50", "TH1F");
    njets_u50->SetDirectory(0);
    njets_o50 = (TH1F*) ele_file->GetObjectChecked("njets_o50", "TH1F");
    njets_o50->SetDirectory(0);
    njets_ttb = (TH1F*) ele_file->GetObjectChecked("njets_ttb", "TH1F");
    njets_ttb->SetDirectory(0);
    njets_wpj = (TH1F*) ele_file->GetObjectChecked("njets_wpj", "TH1F");
    njets_wpj->SetDirectory(0);
    njets_data = (TH1F*) ele_file->GetObjectChecked("njets_data", "TH1F");
    njets_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(njets_u50);
    bkg.push_back(njets_o50);
    bkg.push_back(njets_ttb);
    bkg.push_back(njets_wpj);

    dataMCplotMaker(njets_data, bkg, titles, "njets (double electron)", "p_{T}>40", "--outputName ee_njets.pdf --xAxisLabel njets --lumi 21.3 --legendUp -0.06 --legendRight -0.05 --noXaxisUnit --nDivisions 10");

    // nbtags ee

    nbtags_u50 = (TH1F*) ele_file->GetObjectChecked("nbtags_u50", "TH1F");
    nbtags_u50->SetDirectory(0);
    nbtags_o50 = (TH1F*) ele_file->GetObjectChecked("nbtags_o50", "TH1F");
    nbtags_o50->SetDirectory(0);
    nbtags_ttb = (TH1F*) ele_file->GetObjectChecked("nbtags_ttb", "TH1F");
    nbtags_ttb->SetDirectory(0);
    nbtags_wpj = (TH1F*) ele_file->GetObjectChecked("nbtags_wpj", "TH1F");
    nbtags_wpj->SetDirectory(0);
    nbtags_data = (TH1F*) ele_file->GetObjectChecked("nbtags_data", "TH1F");
    nbtags_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(nbtags_u50);
    bkg.push_back(nbtags_o50);
    bkg.push_back(nbtags_ttb);
    bkg.push_back(nbtags_wpj);

    dataMCplotMaker(nbtags_data, bkg, titles, "nbtags (double electron)", "p_{T}>40", "--outputName ee_nbtags.pdf --xAxisLabel nbtags --lumi 21.3 --legendUp -0.06 --legendRight -0.05 --noXaxisUnit --nDivisions 5");

    // jetpt ee

    jetpt_u50 = (TH1F*) ele_file->GetObjectChecked("jetpt_u50", "TH1F");
    jetpt_u50->SetDirectory(0);
    jetpt_o50 = (TH1F*) ele_file->GetObjectChecked("jetpt_o50", "TH1F");
    jetpt_o50->SetDirectory(0);
    jetpt_ttb = (TH1F*) ele_file->GetObjectChecked("jetpt_ttb", "TH1F");
    jetpt_ttb->SetDirectory(0);
    jetpt_wpj = (TH1F*) ele_file->GetObjectChecked("jetpt_wpj", "TH1F");
    jetpt_wpj->SetDirectory(0);
    jetpt_data = (TH1F*) ele_file->GetObjectChecked("jetpt_data", "TH1F");
    jetpt_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(jetpt_u50);
    bkg.push_back(jetpt_o50);
    bkg.push_back(jetpt_ttb);
    bkg.push_back(jetpt_wpj);

    dataMCplotMaker(jetpt_data, bkg, titles, "leading jet p_{T} (double electron)", "", "--outputName ee_jetpt.pdf --xAxisLabel p_{T} --lumi 21.3 --legendUp -0.02 --legendRight -0.05 --legendTextSize 0.025");

    // ht ee

    ht_u50 = (TH1F*) ele_file->GetObjectChecked("ht_u50", "TH1F");
    ht_u50->SetDirectory(0);
    ht_o50 = (TH1F*) ele_file->GetObjectChecked("ht_o50", "TH1F");
    ht_o50->SetDirectory(0);
    ht_ttb = (TH1F*) ele_file->GetObjectChecked("ht_ttb", "TH1F");
    ht_ttb->SetDirectory(0);
    ht_wpj = (TH1F*) ele_file->GetObjectChecked("ht_wpj", "TH1F");
    ht_wpj->SetDirectory(0);
    ht_data = (TH1F*) ele_file->GetObjectChecked("ht_data", "TH1F");
    ht_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(ht_u50);
    bkg.push_back(ht_o50);
    bkg.push_back(ht_ttb);
    bkg.push_back(ht_wpj);

    dataMCplotMaker(ht_data, bkg, titles, "H_{T} (double electron)", "jet p_{T}>40", "--outputName ee_ht.pdf --xAxisLabel H_{T} --lumi 21.3 --legendUp -0.0w --legendRight -0.05 --legendTextSize 0.025");

    // nvertices ee

    nvertices_u50 = (TH1F*) ele_file->GetObjectChecked("nvertices_u50", "TH1F");
    nvertices_u50->SetDirectory(0);
    nvertices_o50 = (TH1F*) ele_file->GetObjectChecked("nvertices_o50", "TH1F");
    nvertices_o50->SetDirectory(0);
    nvertices_ttb = (TH1F*) ele_file->GetObjectChecked("nvertices_ttb", "TH1F");
    nvertices_ttb->SetDirectory(0);
    nvertices_wpj = (TH1F*) ele_file->GetObjectChecked("nvertices_wpj", "TH1F");
    nvertices_wpj->SetDirectory(0);
    nvertices_data = (TH1F*) ele_file->GetObjectChecked("nvertices_data", "TH1F");
    nvertices_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(nvertices_u50);
    bkg.push_back(nvertices_o50);
    bkg.push_back(nvertices_ttb);
    bkg.push_back(nvertices_wpj);

    dataMCplotMaker(nvertices_data, bkg, titles, "nvertices (double electron)", "", "--outputName ee_nvertices.pdf --xAxisLabel nvertices --lumi 21.3 --legendUp -0.00 --legendRight -0.05 --noXaxisUnit --isLinear --nDivisions 15");

    // muon-electron

    TFile *mue_file = new TFile("mLL_mue_histos.root");
    
    TH1F *mLL_mue_u50 = (TH1F*) mue_file->GetObjectChecked("mLL_mue_u50", "TH1F");
    mLL_mue_u50->SetDirectory(0);
    TH1F *mLL_mue_o50 = (TH1F*) mue_file->GetObjectChecked("mLL_mue_o50", "TH1F");
    mLL_mue_o50->SetDirectory(0);
    TH1F *mLL_mue_ttb = (TH1F*) mue_file->GetObjectChecked("mLL_mue_ttb", "TH1F");
    mLL_mue_ttb->SetDirectory(0);
    TH1F *mLL_mue_wpj = (TH1F*) mue_file->GetObjectChecked("mLL_mue_wpj", "TH1F");
    mLL_mue_wpj->SetDirectory(0);
    TH1F *mLL_mue_data = (TH1F*) mue_file->GetObjectChecked("mLL_mue_data", "TH1F");
    mLL_mue_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_mue_u50);
    bkg.push_back(mLL_mue_o50);
    bkg.push_back(mLL_mue_ttb);
    bkg.push_back(mLL_mue_wpj);

    dataMCplotMaker(mLL_mue_data, bkg, titles, "\\mu-e invariant mass", "p_{T}>20/20", "--outputName mue_mLL_log.pdf --xAxisLabel Me\\mu --lumi 21.3 --legendRight -0.05 --legendUp -0.02 --setMaximum 5000");
    dataMCplotMaker(mLL_mue_data, bkg, titles, "\\mu-e invariant mass", "p_{T}>20/20", "--outputName mue_mLL_lin.pdf --isLinear --xAxisLabel Me\\mu --lumi 21.3 --legendRight -0.06 --legendUp -0.04");

    // pfmet mue

    pfmet_u50 = (TH1F*) mue_file->GetObjectChecked("pfmet_u50", "TH1F");
    pfmet_u50->SetDirectory(0);
    pfmet_o50 = (TH1F*) mue_file->GetObjectChecked("pfmet_o50", "TH1F");
    pfmet_o50->SetDirectory(0);
    pfmet_ttb = (TH1F*) mue_file->GetObjectChecked("pfmet_ttb", "TH1F");
    pfmet_ttb->SetDirectory(0);
    pfmet_wpj = (TH1F*) mue_file->GetObjectChecked("pfmet_wpj", "TH1F");
    pfmet_wpj->SetDirectory(0);
    pfmet_data = (TH1F*) mue_file->GetObjectChecked("pfmet_data", "TH1F");
    pfmet_data->SetDirectory(0);

    pfmet_u50->Rebin(2);
    pfmet_o50->Rebin(2);
    pfmet_ttb->Rebin(2);
    pfmet_wpj->Rebin(2);
    pfmet_data->Rebin(2);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(pfmet_u50);
    bkg.push_back(pfmet_o50);
    bkg.push_back(pfmet_ttb);
    bkg.push_back(pfmet_wpj);

    dataMCplotMaker(pfmet_data, bkg, titles, "pfmet (muon-electron)", "", "--outputName mue_pfmet.pdf --xAxisLabel pfmet --lumi 21.3 --legendUp -0.00 --legendRight -0.05");

    // njets mue

    njets_u50 = (TH1F*) mue_file->GetObjectChecked("njets_u50", "TH1F");
    njets_u50->SetDirectory(0);
    njets_o50 = (TH1F*) mue_file->GetObjectChecked("njets_o50", "TH1F");
    njets_o50->SetDirectory(0);
    njets_ttb = (TH1F*) mue_file->GetObjectChecked("njets_ttb", "TH1F");
    njets_ttb->SetDirectory(0);
    njets_wpj = (TH1F*) mue_file->GetObjectChecked("njets_wpj", "TH1F");
    njets_wpj->SetDirectory(0);
    njets_data = (TH1F*) mue_file->GetObjectChecked("njets_data", "TH1F");
    njets_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(njets_u50);
    bkg.push_back(njets_o50);
    bkg.push_back(njets_ttb);
    bkg.push_back(njets_wpj);

    dataMCplotMaker(njets_data, bkg, titles, "njets (muon-electron)", "p_{T}>40", "--outputName mue_njets.pdf --xAxisLabel njets --lumi 21.3 --legendUp -0.03 --legendRight -0.05 --nDivisions 10 --noXaxisUnit");

    // nbtags mue

    nbtags_u50 = (TH1F*) mue_file->GetObjectChecked("nbtags_u50", "TH1F");
    nbtags_u50->SetDirectory(0);
    nbtags_o50 = (TH1F*) mue_file->GetObjectChecked("nbtags_o50", "TH1F");
    nbtags_o50->SetDirectory(0);
    nbtags_ttb = (TH1F*) mue_file->GetObjectChecked("nbtags_ttb", "TH1F");
    nbtags_ttb->SetDirectory(0);
    nbtags_wpj = (TH1F*) mue_file->GetObjectChecked("nbtags_wpj", "TH1F");
    nbtags_wpj->SetDirectory(0);
    nbtags_data = (TH1F*) mue_file->GetObjectChecked("nbtags_data", "TH1F");
    nbtags_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(nbtags_u50);
    bkg.push_back(nbtags_o50);
    bkg.push_back(nbtags_ttb);
    bkg.push_back(nbtags_wpj);

    dataMCplotMaker(nbtags_data, bkg, titles, "nbtags (muon-electron)", "p_{T}>40", "--outputName mue_nbtags.pdf --xAxisLabel nbtags --lumi 21.3 --legendUp -0.00 --legendRight -0.05  --nDivisions 5 --noXaxisUnit");


    // jetpt mue

    jetpt_u50 = (TH1F*) mue_file->GetObjectChecked("jetpt_u50", "TH1F");
    jetpt_u50->SetDirectory(0);
    jetpt_o50 = (TH1F*) mue_file->GetObjectChecked("jetpt_o50", "TH1F");
    jetpt_o50->SetDirectory(0);
    jetpt_ttb = (TH1F*) mue_file->GetObjectChecked("jetpt_ttb", "TH1F");
    jetpt_ttb->SetDirectory(0);
    jetpt_wpj = (TH1F*) mue_file->GetObjectChecked("jetpt_wpj", "TH1F");
    jetpt_wpj->SetDirectory(0);
    jetpt_data = (TH1F*) mue_file->GetObjectChecked("jetpt_data", "TH1F");
    jetpt_data->SetDirectory(0);

    jetpt_u50->Rebin(2);
    jetpt_o50->Rebin(2);
    jetpt_ttb->Rebin(2);
    jetpt_wpj->Rebin(2);
    jetpt_data->Rebin(2);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(jetpt_u50);
    bkg.push_back(jetpt_o50);
    bkg.push_back(jetpt_ttb);
    bkg.push_back(jetpt_wpj);

    dataMCplotMaker(jetpt_data, bkg, titles, "leading jet p_{T} (muon-electron)", "", "--outputName mue_jetpt.pdf --xAxisLabel p_{T} --lumi 21.3 --legendUp -0.00 --legendRight -0.05 ");

    // ht mue

    ht_u50 = (TH1F*) mue_file->GetObjectChecked("ht_u50", "TH1F");
    ht_u50->SetDirectory(0);
    ht_o50 = (TH1F*) mue_file->GetObjectChecked("ht_o50", "TH1F");
    ht_o50->SetDirectory(0);
    ht_ttb = (TH1F*) mue_file->GetObjectChecked("ht_ttb", "TH1F");
    ht_ttb->SetDirectory(0);
    ht_wpj = (TH1F*) mue_file->GetObjectChecked("ht_wpj", "TH1F");
    ht_wpj->SetDirectory(0);
    ht_data = (TH1F*) mue_file->GetObjectChecked("ht_data", "TH1F");
    ht_data->SetDirectory(0);

    bkg.pop_back(); bkg.pop_back(); bkg.pop_back(); bkg.pop_back();
    bkg.push_back(ht_u50);
    bkg.push_back(ht_o50);
    bkg.push_back(ht_ttb);
    bkg.push_back(ht_wpj);

    dataMCplotMaker(ht_data, bkg, titles, "H_{T} (muon-electron)", "jet p_{T}>40", "--outputName mue_ht.pdf --xAxisLabel H_{T} --lumi 21.3 --legendUp -0.0w --legendRight -0.05");

 
}
