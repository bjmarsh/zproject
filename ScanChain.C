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
#include "/home/users/bmarsh/CORE/VertexSelections.h"

// Tools
#include "/home/users/bmarsh/Tools/goodrun.h"

//nice plots
#include "/home/users/bmarsh/Software/dataMCplotMaker/dataMCplotMaker.h"


#define DOUBLE_MU 0
#define DOUBLE_E 1
#define MU_E 2


using namespace std;
using namespace tas;

int getFileType(const char* fname){
    // 0 = drell-yan mLL<50, 1 = drell-yan mLL>50, 2 = ttbar, 3 = WJets, 4 = data

    int filetype = -1;

    if (strstr(fname, "DYJets") != NULL && strstr(fname, "M-10") != NULL)
        filetype = 0;
    else if (strstr(fname, "DYJets") != NULL && strstr(fname, "M-50") != NULL)
        filetype = 1;
    else if (strstr(fname, "TTJets") != NULL)
        filetype = 2;
    else if (strstr(fname, "WJets") != NULL)
        filetype = 3;
    else if (strstr(fname, "DoubleMuon") != NULL || strstr(fname, "DoubleEG") != NULL || strstr(fname, "MuonEG") != NULL)
        filetype = 4;

    if(filetype == -1){
        cout << "ERROR: unrecognized data file " << fname << endl;
        return 0;
    }

    return filetype;
    
}

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1) {

    /* define the mode that you want to run */
    const char doWhat = DOUBLE_MU;

    // Benchmark
    TBenchmark *bmark = new TBenchmark();
    bmark->Start("benchmark");

    TCanvas *c = new TCanvas("c","",800,600);
    c->cd();

    TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

    const char *json_file;
    if(doWhat == DOUBLE_MU)
        json_file = "/home/users/bmarsh/analysis/zproject/json_golden/golden_json_mumu_snt.txt";
    if(doWhat == DOUBLE_E)
        json_file = "/home/users/bmarsh/analysis/zproject/json_golden/golden_json_ee_snt.txt";
    if(doWhat == MU_E)
        json_file = "/home/users/bmarsh/analysis/zproject/json_golden/golden_json_mue_snt.txt";
    set_goodrun_file(json_file);

    // double muon
    TH1F *mLL_mumu_o50 = new TH1F("mLL_mumu_o50", "", 100,0,150);
    mLL_mumu_o50->SetDirectory(rootdir);
    TH1F *mLL_mumu_u50 = new TH1F("mLL_mumu_u50", "", 100,0,150);
    mLL_mumu_u50->SetDirectory(rootdir);
    TH1F *mLL_mumu_ttb = new TH1F("mLL_mumu_ttb", "", 100,0,150);
    mLL_mumu_ttb->SetDirectory(rootdir);
    TH1F *mLL_mumu_wpj = new TH1F("mLL_mumu_wpj", "", 100,0,150);
    mLL_mumu_wpj->SetDirectory(rootdir);
    TH1F *mLL_mumu_data = new TH1F("mLL_mumu_data", "", 100,0,150);
    mLL_mumu_data->SetDirectory(rootdir);

    // double electron
    TH1F *mLL_ee_o50 = new TH1F("mLL_ee_o50", "", 100,0,150);
    mLL_ee_o50->SetDirectory(rootdir);
    TH1F *mLL_ee_u50 = new TH1F("mLL_ee_u50", "", 100,0,150);
    mLL_ee_u50->SetDirectory(rootdir);
    TH1F *mLL_ee_ttb = new TH1F("mLL_ee_ttb", "", 100,0,150);
    mLL_ee_ttb->SetDirectory(rootdir);
    TH1F *mLL_ee_wpj = new TH1F("mLL_ee_wpj", "", 100,0,150);
    mLL_ee_wpj->SetDirectory(rootdir);
    TH1F *mLL_ee_data = new TH1F("mLL_ee_data", "", 100,0,150);
    mLL_ee_data->SetDirectory(rootdir);

    // muon-electron
    TH1F *mLL_mue_o50 = new TH1F("mLL_mue_o50", "", 50,0,250);
    mLL_mue_o50->SetDirectory(rootdir);
    TH1F *mLL_mue_u50 = new TH1F("mLL_mue_u50", "", 50,0,250);
    mLL_mue_u50->SetDirectory(rootdir);
    TH1F *mLL_mue_ttb = new TH1F("mLL_mue_ttb", "", 50,0,250);
    mLL_mue_ttb->SetDirectory(rootdir);
    TH1F *mLL_mue_wpj = new TH1F("mLL_mue_wpj", "", 50,0,250);
    mLL_mue_wpj->SetDirectory(rootdir);
    TH1F *mLL_mue_data = new TH1F("mLL_mue_data", "", 50,0,250);
    mLL_mue_data->SetDirectory(rootdir);

    // find the J/Psi
    TH1F *mLL_jpsi_o50 = new TH1F("mLL_jpsi_o50", "", 120,0,12);
    mLL_jpsi_o50->SetDirectory(rootdir);
    TH1F *mLL_jpsi_u50 = new TH1F("mLL_jpsi_u50", "", 120,0,12);
    mLL_jpsi_u50->SetDirectory(rootdir);
    TH1F *mLL_jpsi_ttb = new TH1F("mLL_jpsi_ttb", "", 120,0,12);
    mLL_jpsi_ttb->SetDirectory(rootdir);
    TH1F *mLL_jpsi_wpj = new TH1F("mLL_jpsi_wpj", "", 120,0,12);
    mLL_jpsi_wpj->SetDirectory(rootdir);
    TH1F *mLL_jpsi_data = new TH1F("mLL_jpsi_data", "", 120,0,12);
    mLL_jpsi_data->SetDirectory(rootdir);

    // find the upsilon
    TH1F *mLL_ups_data = new TH1F("mLL_ups_data", "", 80,8,12);
    mLL_ups_data->SetDirectory(rootdir);
 
    // pfmet
    TH1F *pfmet_o50 = new TH1F("pfmet_o50", "", 100,0,150);
    pfmet_o50->SetDirectory(rootdir);
    TH1F *pfmet_u50 = new TH1F("pfmet_u50", "", 100,0,150);
    pfmet_u50->SetDirectory(rootdir);
    TH1F *pfmet_ttb = new TH1F("pfmet_ttb", "", 100,0,150);
    pfmet_ttb->SetDirectory(rootdir);
    TH1F *pfmet_wpj = new TH1F("pfmet_wpj", "", 100,0,150);
    pfmet_wpj->SetDirectory(rootdir);
    TH1F *pfmet_data = new TH1F("pfmet_data", "", 100,0,150);
    pfmet_data->SetDirectory(rootdir);

    // njets
    TH1F *njets_o50 = new TH1F("njets_o50", "", 10,-0.5,9.5);
    njets_o50->SetDirectory(rootdir);
    TH1F *njets_u50 = new TH1F("njets_u50", "", 10,-0.5,9.5);
    njets_u50->SetDirectory(rootdir);
    TH1F *njets_ttb = new TH1F("njets_ttb", "", 10,-0.5,9.5);
    njets_ttb->SetDirectory(rootdir);
    TH1F *njets_wpj = new TH1F("njets_wpj", "", 10,-0.5,9.5);
    njets_wpj->SetDirectory(rootdir);
    TH1F *njets_data = new TH1F("njets_data", "", 10,-0.5,9.5);
    njets_data->SetDirectory(rootdir);

    // nbtags
    TH1F *nbtags_o50 = new TH1F("nbtags_o50", "", 5,-0.5,4.5);
    nbtags_o50->SetDirectory(rootdir);
    TH1F *nbtags_u50 = new TH1F("nbtags_u50", "", 5,-0.5,4.5);
    nbtags_u50->SetDirectory(rootdir);
    TH1F *nbtags_ttb = new TH1F("nbtags_ttb", "", 5,-0.5,4.5);
    nbtags_ttb->SetDirectory(rootdir);
    TH1F *nbtags_wpj = new TH1F("nbtags_wpj", "", 5,-0.5,4.5);
    nbtags_wpj->SetDirectory(rootdir);
    TH1F *nbtags_data = new TH1F("nbtags_data", "", 5,-0.5,4.5);
    nbtags_data->SetDirectory(rootdir);

    // leading jet pt
    TH1F *jetpt_o50 = new TH1F("jetpt_o50", "", 80,0,200);
    jetpt_o50->SetDirectory(rootdir);
    TH1F *jetpt_u50 = new TH1F("jetpt_u50", "", 80,0,200);
    jetpt_u50->SetDirectory(rootdir);
    TH1F *jetpt_ttb = new TH1F("jetpt_ttb", "", 80,0,200);
    jetpt_ttb->SetDirectory(rootdir);
    TH1F *jetpt_wpj = new TH1F("jetpt_wpj", "", 80,0,200);
    jetpt_wpj->SetDirectory(rootdir);
    TH1F *jetpt_data = new TH1F("jetpt_data", "", 80,0,200);
    jetpt_data->SetDirectory(rootdir);

    // h_t
    TH1F *ht_o50 = new TH1F("ht_o50", "", 100,40,340);
    ht_o50->SetDirectory(rootdir);
    TH1F *ht_u50 = new TH1F("ht_u50", "", 100,40,340);
    ht_u50->SetDirectory(rootdir);
    TH1F *ht_ttb = new TH1F("ht_ttb", "", 100,40,340);
    ht_ttb->SetDirectory(rootdir);
    TH1F *ht_wpj = new TH1F("ht_wpj", "", 100,40,340);
    ht_wpj->SetDirectory(rootdir);
    TH1F *ht_data = new TH1F("ht_data", "", 100,40,340);
    ht_data->SetDirectory(rootdir);

    // nvertices
    TH1F *nvertices_o50 = new TH1F("nvertices_o50", "", 31,-0.5,30.5);
    nvertices_o50->SetDirectory(rootdir);
    TH1F *nvertices_u50 = new TH1F("nvertices_u50", "", 31,-0.5,30.5);
    nvertices_u50->SetDirectory(rootdir);
    TH1F *nvertices_ttb = new TH1F("nvertices_ttb", "", 31,-0.5,30.5);
    nvertices_ttb->SetDirectory(rootdir);
    TH1F *nvertices_wpj = new TH1F("nvertices_wpj", "", 31,-0.5,30.5);
    nvertices_wpj->SetDirectory(rootdir);
    TH1F *nvertices_data = new TH1F("nvertices_data", "", 31,-0.5,30.5);
    nvertices_data->SetDirectory(rootdir);

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
    int totalWPJevents = 24089991;

    // get the number of events in each category (U50/O50/TTB) (for proper scaling)
    int loadedU50events = 0;
    int loadedO50events = 0;
    int loadedTTBevents = 0;
    int loadedWPJevents = 0;
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
        }else if(fileType==3){
            loadedWPJevents += tree->GetEntries();
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
            double lumMuMu = 0.021282, lumEE = 0.021282, lumMuE = 0.021282;
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
            if(fileType==3){
                scaleMuMu = evt_scale1fb()*lumMuMu*totalWPJevents/loadedWPJevents;
                scaleEE = evt_scale1fb()*lumEE*totalWPJevents/loadedWPJevents;
                scaleMuE = evt_scale1fb()*lumMuE*totalWPJevents/loadedWPJevents;
            }
    
            // Progress
            CMS3::progress( nEventsTotal, nEventsChain );            

            /******** Analysis Code *********/

            // make sure it is a good run
            if(fileType==4 && evt_isRealData() && !goodrun(evt_run(), evt_lumiBlock()))
                continue;

            int besthyp = -1;
            
            //dimuon events
            if(doWhat == DOUBLE_MU && passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ")){
                int nhyp = hyp_p4().size();
                besthyp = -1;
                double bestpT = 0;
                for(int i = 0; i < nhyp; i++){
                    if(abs(hyp_ll_id()[i])!=13 || abs(hyp_lt_id()[i])!=13)
                        continue;
                    
                    double pT1 = fmin(hyp_ll_p4()[i].Pt(),hyp_lt_p4()[i].Pt());
                    double pT2 = fmax(hyp_ll_p4()[i].Pt(),hyp_lt_p4()[i].Pt());
                    // momentum cut
                    if(pT1<10 || pT2<20)
                        continue;
                    
                    // opposite sign
                    if(hyp_ll_charge()[i] + hyp_lt_charge()[i] != 0)
                        continue;
                    
                    if(!muonID(hyp_ll_index()[i], STOP_medium_v2) || !muonID(hyp_lt_index()[i], STOP_medium_v2))
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
                    }else if(fileType==2){
                        mLL_mumu_ttb->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                        mLL_jpsi_ttb->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                    }else if(fileType==3){
                        mLL_mumu_wpj->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                        mLL_jpsi_wpj->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuMu);
                    }else if(fileType==4){
                        mLL_mumu_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                        mLL_jpsi_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                        mLL_ups_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);                        
                    }
                }

            }

            //double electron events
            if(doWhat == DOUBLE_E && passHLTTriggerPattern("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ")){
                int nhyp = hyp_p4().size();
                besthyp = -1;
                double bestpT = 0;
                for(int i = 0; i < nhyp; i++){
                    if(abs(hyp_ll_id()[i])!=11 || abs(hyp_lt_id()[i])!=11)
                        continue;
                    
                    double pT1 = fmin(hyp_ll_p4()[i].Pt(),hyp_lt_p4()[i].Pt());
                    double pT2 = fmax(hyp_ll_p4()[i].Pt(),hyp_lt_p4()[i].Pt());
                    // momentum cut
                    if(pT1<30 || pT2<20)
                        continue;
                    
                    // opposite sign
                    if(hyp_ll_charge()[i] + hyp_lt_charge()[i] != 0)
                        continue;
                    
                    if(!electronID(hyp_ll_index()[i], STOP_medium_v2) || !electronID(hyp_lt_index()[i], STOP_medium_v2))
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
                    else if(fileType==2)
                        mLL_ee_ttb->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleEE);
                    else if(fileType==3)
                        mLL_ee_wpj->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleEE);
                    else if(fileType==4)
                        mLL_ee_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                }
            }

            double pTeCut = 0;
            double pTmuCut = 0;
            //muon-electron events
            if(doWhat == MU_E && passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL")){
                pTeCut = 20;
                pTmuCut = 20;
            }
            if(doWhat == MU_E && passHLTTriggerPattern("HLT_Mu8_TrkIsoVVL_Ele17_CaloIdL_TrackIdL_IsoVL")){
                pTeCut = 25;
                pTmuCut = 10;
            }
            if(doWhat == MU_E && pTeCut>0){
                int nhyp = hyp_p4().size();
                besthyp = -1;
                double bestpT = 0;
                bool llIsMuon = false;
                for(int i = 0; i < nhyp; i++){
                    if(abs(hyp_ll_id()[i])==11 && abs(hyp_lt_id()[i])==13)
                        llIsMuon = false;
                    else if(abs(hyp_ll_id()[i])==13 && abs(hyp_lt_id()[i])==11)
                        llIsMuon = true;
                    else
                        continue;
                    
                    double pTmu = llIsMuon ? hyp_ll_p4()[i].Pt() : hyp_lt_p4()[i].Pt();
                    double pTe  = llIsMuon ? hyp_lt_p4()[i].Pt() : hyp_ll_p4()[i].Pt();
                    // momentum cut
                    if(pTmu<pTmuCut || pTe<pTeCut)
                        continue;
                    
                    // opposite sign
                    if(hyp_ll_charge()[i] + hyp_lt_charge()[i] != 0)
                        continue;
                    
                    if(llIsMuon && (!muonID(hyp_ll_index()[i], STOP_medium_v2) || !electronID(hyp_lt_index()[i], STOP_medium_v2)))
                        continue;
                    if(!llIsMuon && (!electronID(hyp_ll_index()[i], STOP_medium_v2) || !muonID(hyp_lt_index()[i], STOP_medium_v2)))
                        continue;

                    
                    double totalpT = hyp_ll_p4()[i].Pt() + hyp_lt_p4()[i].Pt();
                    if(totalpT > bestpT){
                        bestpT = totalpT;
                        besthyp = i;
                    }
                }
                if(besthyp > -1){
                    if(fileType==1)
                        mLL_mue_o50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuE);
                    else if(fileType==0)
                        mLL_mue_u50->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuE);
                    else if(fileType==2)
                        mLL_mue_ttb->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuE);
                    else if(fileType==3)
                        mLL_mue_wpj->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), scaleMuE);
                    else if(fileType==4)
                        mLL_mue_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                }
            }
            
            if(besthyp==-1)
                continue;


            double scale;
            if(doWhat == DOUBLE_MU)
                scale = scaleMuMu;
            if(doWhat == DOUBLE_E)
                scale = scaleEE;
            if(doWhat == MU_E)
                scale = scaleMuE;

            if(fileType==0)
                pfmet_u50->Fill(evt_pfmet(),scale);
            else if(fileType==1)
                pfmet_o50->Fill(evt_pfmet(),scale);
            else if(fileType==2)
                pfmet_ttb->Fill(evt_pfmet(),scale);
            else if(fileType==3)
                pfmet_wpj->Fill(evt_pfmet(),scale);
            else if(fileType==4)
                pfmet_data->Fill(evt_pfmet(),1);


            int ntotalvertices = vtxs_position().size();
            int ngoodvertices = 0;
            for(int i=0; i<ntotalvertices; i++){
                if(isGoodVertex(i))
                    ngoodvertices++;
            }

            if(fileType==0)
                nvertices_u50->Fill(ngoodvertices,scale);
            else if(fileType==1)
                nvertices_o50->Fill(ngoodvertices,scale);
            else if(fileType==2)
                nvertices_ttb->Fill(ngoodvertices,scale);
            else if(fileType==3)
                nvertices_wpj->Fill(ngoodvertices,scale);
            else if(fileType==4)
                nvertices_data->Fill(ngoodvertices,1);
            

            int njetstotal = pfjets_p4().size();
            int ngoodjets = 0;
            int nbtags = 0;
            double h_t = 0;
            double maxjetpt = 0;

            for(int i =0; i<njetstotal; i++){

                // reject jet if it is too close to one of the Z leptons
                double jetEta = pfjets_p4()[i].Eta();
                double jetPhi = pfjets_p4()[i].Phi();
                double l1Eta = hyp_ll_p4()[besthyp].Eta();
                double l2Eta = hyp_lt_p4()[besthyp].Eta();
                double l1Phi = hyp_ll_p4()[besthyp].Phi();
                double l2Phi = hyp_lt_p4()[besthyp].Phi();
                double dR1 = sqrt((jetEta-l1Eta)*(jetEta-l1Eta)+(jetPhi-l1Phi)*(jetPhi-l1Phi));
                double dR2 = sqrt((jetEta-l2Eta)*(jetEta-l2Eta)+(jetPhi-l2Phi)*(jetPhi-l2Phi));
                if(dR1 < 0.4 || dR2 < 0.4)
                    continue;                

                if(fabs(jetEta)>2.4)
                    continue;

                bool isBtag = (pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag()[i] > 0.814);                

                if(pfjets_p4()[i].Pt() > maxjetpt)
                    maxjetpt = pfjets_p4()[i].Pt();

                if(pfjets_p4()[i].Pt() >= 40){
                    if(fabs(pfjets_p4()[i].Eta())<2.4){
                        ngoodjets++;
                    }
                    h_t += pfjets_p4()[i].Pt();
                    if(isBtag)
                        nbtags++;
                }
            }

            if(fileType==0){
                njets_u50->Fill(ngoodjets, scale);
                nbtags_u50->Fill(nbtags, scale);
                if(maxjetpt>0)
                    jetpt_u50->Fill(maxjetpt, scale);
                if(ngoodjets > 0)
                    ht_u50->Fill(h_t, scale);
            }else if(fileType==1){
                njets_o50->Fill(ngoodjets, scale);
                nbtags_o50->Fill(nbtags, scale);
                if(maxjetpt>0)
                    jetpt_o50->Fill(maxjetpt, scale);
                if(ngoodjets > 0)
                    ht_o50->Fill(h_t, scale);
            }else if(fileType==2){
                njets_ttb->Fill(ngoodjets, scale);
                nbtags_ttb->Fill(nbtags, scale);
                if(maxjetpt>0)
                    jetpt_ttb->Fill(maxjetpt, scale);
                if(ngoodjets > 0)
                    ht_ttb->Fill(h_t, scale);
            }else if(fileType==3){
                njets_wpj->Fill(ngoodjets, scale);
                nbtags_wpj->Fill(nbtags, scale);
                if(maxjetpt>0)
                    jetpt_wpj->Fill(maxjetpt, scale);
                if(ngoodjets > 0)
                    ht_wpj->Fill(h_t, scale);
            }else if(fileType==4){
                njets_data->Fill(ngoodjets, 1);
                nbtags_data->Fill(nbtags, 1);
                if(maxjetpt>0)
                    jetpt_data->Fill(maxjetpt, 1);
                if(ngoodjets > 0)
                    ht_data->Fill(h_t, 1);
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
 

    if(doWhat == DOUBLE_MU){
        TFile histos ("mLL_mumu_histos.root", "RECREATE");
        mLL_mumu_u50->Write();
        mLL_mumu_o50->Write();
        mLL_mumu_ttb->Write();
        mLL_mumu_wpj->Write();
        mLL_mumu_data->Write();
        mLL_jpsi_u50->Write();
        mLL_jpsi_o50->Write();
        mLL_jpsi_ttb->Write();
        mLL_jpsi_wpj->Write();
        mLL_jpsi_data->Write();
        mLL_ups_data->Write();
        pfmet_u50->Write();
        pfmet_o50->Write();
        pfmet_ttb->Write();
        pfmet_wpj->Write();
        pfmet_data->Write();
        njets_u50->Write();
        njets_o50->Write();
        njets_ttb->Write();
        njets_wpj->Write();
        njets_data->Write();
        nbtags_u50->Write();
        nbtags_o50->Write();
        nbtags_ttb->Write();
        nbtags_wpj->Write();
        nbtags_data->Write();
        jetpt_u50->Write();
        jetpt_o50->Write();
        jetpt_ttb->Write();
        jetpt_wpj->Write();
        jetpt_data->Write();
        ht_u50->Write();
        ht_o50->Write();
        ht_ttb->Write();
        ht_wpj->Write();
        ht_data->Write();
        nvertices_u50->Write();
        nvertices_o50->Write();
        nvertices_ttb->Write();
        nvertices_wpj->Write();
        nvertices_data->Write();
        histos.Close();
    }
    if(doWhat == DOUBLE_E){
        TFile histos ("mLL_ee_histos.root", "RECREATE");
        mLL_ee_u50->Write();
        mLL_ee_o50->Write();
        mLL_ee_ttb->Write();
        mLL_ee_wpj->Write();
        mLL_ee_data->Write();
        pfmet_u50->Write();
        pfmet_o50->Write();
        pfmet_ttb->Write();
        pfmet_wpj->Write();
        pfmet_data->Write();
        njets_u50->Write();
        njets_o50->Write();
        njets_ttb->Write();
        njets_wpj->Write();
        njets_data->Write();
        nbtags_u50->Write();
        nbtags_o50->Write();
        nbtags_ttb->Write();
        nbtags_wpj->Write();
        nbtags_data->Write();
        jetpt_u50->Write();
        jetpt_o50->Write();
        jetpt_ttb->Write();
        jetpt_wpj->Write();
        jetpt_data->Write();
        ht_u50->Write();
        ht_o50->Write();
        ht_ttb->Write();
        ht_wpj->Write();
        ht_data->Write();
        nvertices_u50->Write();
        nvertices_o50->Write();
        nvertices_ttb->Write();
        nvertices_wpj->Write();
        nvertices_data->Write();
        histos.Close();
    }
    if(doWhat == MU_E){
        TFile histos ("mLL_mue_histos.root", "RECREATE");
        mLL_mue_u50->Write();
        mLL_mue_o50->Write();
        mLL_mue_ttb->Write();
        mLL_mue_wpj->Write();
        mLL_mue_data->Write();
        pfmet_u50->Write();
        pfmet_o50->Write();
        pfmet_ttb->Write();
        pfmet_wpj->Write();
        pfmet_data->Write();
        njets_u50->Write();
        njets_o50->Write();
        njets_ttb->Write();
        njets_wpj->Write();
        njets_data->Write();
        nbtags_u50->Write();
        nbtags_o50->Write();
        nbtags_ttb->Write();
        nbtags_wpj->Write();
        nbtags_data->Write();
        jetpt_u50->Write();
        jetpt_o50->Write();
        jetpt_ttb->Write();
        jetpt_wpj->Write();
        jetpt_data->Write();
        ht_u50->Write();
        ht_o50->Write();
        ht_ttb->Write();
        ht_wpj->Write();
        ht_data->Write();
        histos.Close();
    }

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
