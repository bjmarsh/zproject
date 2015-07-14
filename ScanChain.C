// Usage:
// > root -b doAll.C

// C++
#include <iostream>
#include <vector>

// ROOT
#include "TBenchmark.h"
#include "TChain.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTreeCache.h"
#include "TCanvas.h"

// CORE
#include "/home/users/bmarsh/CORE/CMS3.h"
#include "/home/users/bmarsh/CORE/ElectronSelections.h"
#include "/home/users/bmarsh/CORE/MuonSelections.h"
#include "/home/users/bmarsh/CORE/JetSelections.h"
#include "/home/users/bmarsh/CORE/TriggerSelections.h"

// Tools
#include "/home/users/bmarsh/Tools/goodrun.h"

//nice plots
#include "/home/users/bmarsh/Software/dataMCplotMaker/dataMCplotMaker.h"

using namespace std;
using namespace tas;

int getFileType(const char* fname){
    // 0 = drell-yan mLL<50, 1 = drell-yan mLL>50, 2 = ttbar, 3 = data

    int filetype = -1;

    if (strstr(fname, "DYJets") != NULL && strstr(fname, "M-10") != NULL)
        filetype = 0;
    else if (strstr(fname, "DYJets") != NULL && strstr(fname, "M-50") != NULL)
        filetype = 1;
    else if (strstr(fname, "TTJets") != NULL)
        filetype = 2;
    else if (strstr(fname, "DoubleMuon") != NULL || strstr(fname, "DoubleEG") != NULL || strstr(fname, "MuonEG") != NULL)
        filetype = 3;

    if(filetype == -1){
        cout << "ERROR: unrecognized data file " << fname << endl;
        return 0;
    }

    return filetype;
    
}

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1) {

    // Benchmark
    TBenchmark *bmark = new TBenchmark();
    bmark->Start("benchmark");

    TCanvas *c = new TCanvas("c","",800,600);
    c->cd();

    const char *json_file = "json_DCSONLY_Run2015B_snt.txt";
    set_goodrun_file(json_file);

    TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

    // double muon
    TH1F *mLL_mumu_o50 = new TH1F("mLL_mumu_o50", "", 50,0,150);
    mLL_mumu_o50->SetDirectory(rootdir);
    TH1F *mLL_mumu_u50 = new TH1F("mLL_mumu_u50", "", 50,0,150);
    mLL_mumu_u50->SetDirectory(rootdir);
    TH1F *mLL_mumu_data = new TH1F("mLL_mumu_data", "", 50,0,150);
    mLL_mumu_data->SetDirectory(rootdir);

    // double electron
    TH1F *mLL_ee_o50 = new TH1F("mLL_ee_o50", "", 50,0,150);
    mLL_ee_o50->SetDirectory(rootdir);
    TH1F *mLL_ee_u50 = new TH1F("mLL_ee_u50", "", 50,0,150);
    mLL_ee_u50->SetDirectory(rootdir);
    TH1F *mLL_ee_data = new TH1F("mLL_ee_data", "", 50,0,150);
    mLL_ee_data->SetDirectory(rootdir);

    // find the J/Psi
    TH1F *mLL_jpsi_o50 = new TH1F("mLL_jpsi_o50", "", 120,0,12);
    mLL_jpsi_o50->SetDirectory(rootdir);
    TH1F *mLL_jpsi_u50 = new TH1F("mLL_jpsi_u50", "", 120,0,12);
    mLL_jpsi_u50->SetDirectory(rootdir);
    TH1F *mLL_jpsi_data = new TH1F("mLL_jpsi_data", "", 120,0,12);
    mLL_jpsi_data->SetDirectory(rootdir);

    // Loop over events to Analyze
    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();
    if( nEvents >= 0 ) nEventsChain = nEvents;
    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    // total events in each sample
    int totalO50events = 19925500;
    int totalU50events = 14820919;
    int totalTTBevents = 4992231;

    // get the number of events in each category (U50/O50/TTB) (for proper scaling)
    int loadedU50events = 0;
    int loadedO50events = 0;
    int loadedTTBevents = 0;
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");

        int fileType = getFileType(currentFile->GetTitle());

        cout << currentFile->GetTitle() << " " << fileType << endl;

        if(fileType==0){
            loadedU50events += tree->GetEntries();
        }else if(fileType==1){
            loadedO50events += tree->GetEntries();
        }else if(fileType==2){
            loadedTTBevents += tree->GetEntries();
        }
    }

    fileIter.Reset();
    int fileCounter = -1;

    // File Loop
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        fileCounter++;

        int fileType = getFileType(currentFile->GetTitle());

        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        if(fast) TTreeCache::SetLearnEntries(10);
        if(fast) tree->SetCacheSize(128*1024*1024);
        cms3.Init(tree);

        // Loop over Events in current file
        if( nEventsTotal >= nEventsChain ) continue;
        unsigned int nEventsTree = tree->GetEntriesFast();
        for( unsigned int event = 0; event < nEventsTree; ++event) {
    
            // Get Event Content
            if( nEventsTotal >= nEventsChain ) continue;
            if(fast) tree->LoadTree(event);
            cms3.GetEntry(event);
            ++nEventsTotal;

            // get the proper scale factors
            double scaleMuMu = 1, scaleEE = 1, scaleMuE = 1;
            double lumMuMu = 0.009169, lumEE = 0.007564, lumMuE = 0.009169;
            if(fileType==0){
                scaleMuMu = evt_scale1fb()*lumMuMu*totalU50events/loadedU50events;
                scaleEE = evt_scale1fb()*lumEE*totalU50events/loadedU50events;
                scaleMuE = evt_scale1fb()*lumMuE*totalU50events/loadedU50events;
            }
            if(fileType==1){
                scaleMuMu = evt_scale1fb()*lumMuMu*totalO50events/loadedO50events;
                scaleEE = evt_scale1fb()*lumEE*totalO50events/loadedO50events;
                scaleMuE = evt_scale1fb()*lumMuE*totalO50events/loadedO50events;
            }
            if(fileType==2){
                scaleMuMu = evt_scale1fb()*lumMuMu*totalTTBevents/loadedTTBevents;
                scaleEE = evt_scale1fb()*lumEE*totalTTBevents/loadedTTBevents;
                scaleMuE = evt_scale1fb()*lumMuE*totalTTBevents/loadedTTBevents;
            }
    
            // Progress
            CMS3::progress( nEventsTotal, nEventsChain );            

            /******** Analysis Code *********/

            if(fileType==3 && evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()))
                continue;
            
            //dimuon events
            if(passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ")){
                int nhyp = hyp_p4().size();
                int besthyp = -1;
                double bestpT = 0;
                for(int i = 0; i < nhyp; i++){
                    if(abs(hyp_ll_id()[i])!=13 || abs(hyp_lt_id()[i])!=13)
                        continue;
                    
                    // momentum cut
                    if(hyp_ll_p4()[i].Pt()<20 || hyp_lt_p4()[i].Pt()<20)
                        continue;
                    
                    // opposite sign
                    if(hyp_ll_charge()[i] + hyp_lt_charge()[i] != 0)
                        continue;
                    
                    if(!isLooseMuonPOG(hyp_ll_index()[i]) || !isLooseMuonPOG(hyp_lt_index()[i]))
                        continue;
                    
                    double totalpT = hyp_ll_p4()[i].Pt() + hyp_lt_p4()[i].Pt();
                    if(totalpT > bestpT){
                        bestpT = totalpT;
                        besthyp = i;
                    }
                }
                if(besthyp > -1){
                    if(fileType==1){
                        mLL_mumu_o50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                        mLL_jpsi_o50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                    }else if(fileType==0){
                        mLL_mumu_u50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                        mLL_jpsi_u50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                    }else if(fileType==3){
                        mLL_mumu_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                        mLL_jpsi_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                    }
                }
            }

            //double electron events
            if(false && passHLTTriggerPattern("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ")){
                int nhyp = hyp_p4().size();
                int besthyp = -1;
                double bestpT = 0;
                for(int i = 0; i < nhyp; i++){
                    if(abs(hyp_ll_id()[i])!=11 || abs(hyp_lt_id()[i])!=11)
                        continue;
                    
                    // momentum cut
                    if(hyp_ll_p4()[i].Pt()<30 || hyp_lt_p4()[i].Pt()<30)
                        continue;
                    
                    // opposite sign
                    if(hyp_ll_charge()[i] + hyp_lt_charge()[i] != 0)
                        continue;
                    
                    if(!isVetoElectronPOG(hyp_ll_index()[i]) || !isVetoElectronPOG(hyp_lt_index()[i]))
                        continue;
                    
                    double totalpT = hyp_ll_p4()[i].Pt() + hyp_lt_p4()[i].Pt();
                    if(totalpT > bestpT){
                        bestpT = totalpT;
                        besthyp = i;
                    }
                }
                if(besthyp > -1){
                    if(fileType==1)
                        mLL_ee_o50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleEE);
                    else if(fileType==0)
                        mLL_ee_u50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleEE);
                    else if(fileType==3)
                        mLL_ee_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                }
            }

        }
  
        // Clean Up
        delete tree;
        file->Close();
        delete file;
    }
    if ( nEventsChain != nEventsTotal ) {
        cout << Form( "ERROR: number of events from files (%d) is not equal to total number of events (%d)", nEventsChain, nEventsTotal ) << endl;
    }
  

    vector<TH1F*> bkg;
    vector<string> str;

    // double muon
    bkg.push_back(mLL_mumu_o50);
    bkg.push_back(mLL_mumu_u50);
    str.push_back("DY (m_{LL}>50)");
    str.push_back("DY (m_{LL}<50)");
    dataMCplotMaker(mLL_mumu_data, bkg, str, "Dimuon Invariant Mass", "pT>20", "--outputName mLL_mumu.pdf --xAxisLabel M\\mu\\mu --isLinear --lumi 9.2" );

    // double electron
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_ee_o50);
    bkg.push_back(mLL_ee_u50);
    dataMCplotMaker(mLL_ee_data, bkg, str, "ee Invariant Mass", "pT>30", "--outputName mLL_ee.pdf --xAxisLabel M_{ee} --isLinear --lumi 7.6 --legendTextSize .025" );

    // j/psi
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_jpsi_o50);
    bkg.push_back(mLL_jpsi_u50);
    dataMCplotMaker(mLL_jpsi_data, bkg, str, "\\mu\\mu Invariant Mass", "pT>20", "--outputName mLL_jpsi.pdf --xAxisLabel M\\mu\\mu --isLinear --lumi 9.2 --noOverflow --noDataMC" );

    // Example Histograms
    //samplehisto->Draw();
    //c->Print("samplehisto.pdf");

    // return
    bmark->Stop("benchmark");
    cout << endl;
    cout << nEventsTotal << " Events Processed" << endl;
    cout << "------------------------------" << endl;
    cout << "CPU  Time:	" << Form( "%.01f", bmark->GetCpuTime("benchmark")  ) << endl;
    cout << "Real Time:	" << Form( "%.01f", bmark->GetRealTime("benchmark") ) << endl;
    cout << endl;
    delete bmark;
    return 0;
}
