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

    // Benchmark
    TBenchmark *bmark = new TBenchmark();
    bmark->Start("benchmark");

    TCanvas *c = new TCanvas("c","",800,600);
    c->cd();

    TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

    bool doElectrons = true;
    bool doMuons = false;

    const char *json_file;
    if(doMuons)
        json_file = "json_DCSONLY_Run2015B_mumu_snt.txt";
    if(doElectrons)
        json_file = "json_DCSONLY_Run2015B_ee_snt.txt";
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
            double lumMuMu = 0.023146, lumEE = 0.023293, lumMuE = 0.009169;
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
            if(doMuons && passHLTTriggerPattern("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ")){
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
            if(doElectrons && passHLTTriggerPattern("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ")){
                int nhyp = hyp_p4().size();
                besthyp = -1;
                double bestpT = 0;
                for(int i = 0; i < nhyp; i++){
                    if(abs(hyp_ll_id()[i])!=11 || abs(hyp_lt_id()[i])!=11)
                        continue;
                    
                    double pT1 = fmin(hyp_ll_p4()[i].Pt(),hyp_lt_p4()[i].Pt());
                    double pT2 = fmax(hyp_ll_p4()[i].Pt(),hyp_lt_p4()[i].Pt());
                    // momentum cut
                    if(pT1<20 || pT2<30)
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
                        mLL_ee_wpj->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                    else if(fileType==4)
                        mLL_ee_data->Fill((hyp_ll_p4()[besthyp]+hyp_lt_p4()[besthyp]).M(), 1);
                }
            }
            
            if(besthyp==-1)
                continue;

            double scale;
            if(doMuons)
                scale = scaleMuMu;
            if(doElectrons)
                scale = scaleEE;

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


            int njetstotal = pfjets_p4().size();
            int ngoodjets = 0;
            int nbtags = 0;
            double h_t = 0;

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

                bool isBtag = (pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag()[i] > 0.814);                

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
            }else if(fileType==1){
                njets_o50->Fill(ngoodjets, scale);
                nbtags_o50->Fill(nbtags, scale);
            }else if(fileType==2){
                njets_ttb->Fill(ngoodjets, scale);
                nbtags_ttb->Fill(nbtags, scale);
            }else if(fileType==3){
                njets_wpj->Fill(ngoodjets, scale);
                nbtags_wpj->Fill(nbtags, scale);
            }else if(fileType==4){
                njets_data->Fill(ngoodjets, 1);
                nbtags_data->Fill(nbtags, 1);
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
 

    if(doMuons){
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
        histos.Close();
    }
    if(doElectrons){
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
