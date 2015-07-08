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


//nice plots
#include "/home/users/bmarsh/Software/dataMCplotMaker/dataMCplotMaker.h"

using namespace std;
using namespace tas;

int ScanChain( TChain* chain, bool fast = true, int nEvents = -1) {

    // Benchmark
    TBenchmark *bmark = new TBenchmark();
    bmark->Start("benchmark");

    TCanvas *c = new TCanvas("c","",800,600);
    c->cd();

    TDirectory *rootdir = gDirectory->GetDirectory("Rint:");

    // mLL, genps
    TH1F *mLL_genps_o50 = new TH1F("mLL_genps_o50", "", 300,0,150);
    mLL_genps_o50->SetDirectory(rootdir);
    TH1F *mLL_genps_u50 = new TH1F("mLL_genps_u50", "", 300,0,150);
    mLL_genps_u50->SetDirectory(rootdir);

    // mLL, genps, noscale
    TH1F *mLL_genps_noscale_o50 = new TH1F("mLL_genps_noscale_o50", "", 300,0,150);
    mLL_genps_noscale_o50->SetDirectory(rootdir);
    TH1F *mLL_genps_noscale_u50 = new TH1F("mLL_genps_noscale_u50", "", 300,0,150);
    mLL_genps_noscale_u50->SetDirectory(rootdir);

    // mLL, reco, all hyps
    TH1F *mLL_reco_all_o50 = new TH1F("mLL_reco_all_o50", "", 300,0,150);
    mLL_reco_all_o50->SetDirectory(rootdir);
    TH1F *mLL_reco_all_u50 = new TH1F("mLL_reco_all_u50", "", 300,0,150);
    mLL_reco_all_u50->SetDirectory(rootdir);

    // mLL, reco, best hyp
    TH1F *mLL_reco_best_o50 = new TH1F("mLL_reco_best_o50", "", 300,0,150);
    mLL_reco_best_o50->SetDirectory(rootdir);
    TH1F *mLL_reco_best_u50 = new TH1F("mLL_reco_best_u50", "", 300,0,150);
    mLL_reco_best_u50->SetDirectory(rootdir);

    // mLL, reco, pT>20
    TH1F *mLL_reco_pT20_o50 = new TH1F("mLL_reco_pT20_o50", "", 300,0,150);
    mLL_reco_pT20_o50->SetDirectory(rootdir);
    TH1F *mLL_reco_pT20_u50 = new TH1F("mLL_reco_pT20_u50", "", 300,0,150);
    mLL_reco_pT20_u50->SetDirectory(rootdir);

    // mLL, reco, pT>20, OS
    TH1F *mLL_reco_pT20_OS_o50 = new TH1F("mLL_reco_pT20_OS_o50", "", 300,0,150);
    mLL_reco_pT20_OS_o50->SetDirectory(rootdir);
    TH1F *mLL_reco_pT20_OS_u50 = new TH1F("mLL_reco_pT20_OS_u50", "", 300,0,150);
    mLL_reco_pT20_OS_u50->SetDirectory(rootdir);

    // mLL, reco, pT>20, besthyp
    TH1F *mLL_reco_pT20_OS_best_o50 = new TH1F("mLL_reco_pT20_OS_best_o50", "", 300,0,150);
    mLL_reco_pT20_OS_best_o50->SetDirectory(rootdir);
    TH1F *mLL_reco_pT20_OS_best_u50 = new TH1F("mLL_reco_pT20_OS_best_u50", "", 300,0,150);
    mLL_reco_pT20_OS_best_u50->SetDirectory(rootdir);

    // pfmet
    TH1F *pfmet_o50 = new TH1F("pfmet_o50", "", 200,0,150);
    pfmet_o50->SetDirectory(rootdir);
    TH1F *pfmet_u50 = new TH1F("pfmet_u50", "", 200,0,150);
    pfmet_u50->SetDirectory(rootdir);

    // njets
    TH1F *njets_o50 = new TH1F("njets_o50", "", 10,-0.5,9.5);
    njets_o50->SetDirectory(rootdir);
    TH1F *njets_u50 = new TH1F("njets_u50", "", 10,-0.5,9.5);
    njets_u50->SetDirectory(rootdir);

    // njets_jetid
    TH1F *njets_jetid_o50 = new TH1F("njets_jetid_o50", "", 10,-0.5,9.5);
    njets_jetid_o50->SetDirectory(rootdir);
    TH1F *njets_jetid_u50 = new TH1F("njets_jetid_u50", "", 10,-0.5,9.5);
    njets_jetid_u50->SetDirectory(rootdir);

    // H_T (scalar sum jet momenta)
    TH1F *ht_o50 = new TH1F("ht_o50", "", 200,0,300);
    ht_o50->SetDirectory(rootdir);
    TH1F *ht_u50 = new TH1F("ht_u50", "", 200,0,300);
    ht_u50->SetDirectory(rootdir);

    // jet pT
    TH1F *jetpt_o50 = new TH1F("jetpt_o50", "", 200,0,300);
    jetpt_o50->SetDirectory(rootdir);
    TH1F *jetpt_u50 = new TH1F("jetpt_u50", "", 200,0,300);
    jetpt_u50->SetDirectory(rootdir);

    // lep pT
    TH1F *leppt_o50 = new TH1F("leppt_o50", "", 300,0,200);
    leppt_o50->SetDirectory(rootdir);
    TH1F *leppt_u50 = new TH1F("leppt_u50", "", 300,0,200);
    leppt_u50->SetDirectory(rootdir);

    // lep eta
    TH1F *lep_eta_o50 = new TH1F("lep_eta_o50", "", 150,-3,3);
    lep_eta_o50->SetDirectory(rootdir);
    TH1F *lep_eta_u50 = new TH1F("lep_eta_u50", "", 150,-3,3);
    lep_eta_u50->SetDirectory(rootdir);

    // lep phi
    TH1F *lep_phi_o50 = new TH1F("lep_phi_o50", "", 150,-3.4,3.4);
    lep_phi_o50->SetDirectory(rootdir);
    TH1F *lep_phi_u50 = new TH1F("lep_phi_u50", "", 150,-3.4,3.4);
    lep_phi_u50->SetDirectory(rootdir);

    // nBtags
    TH1F *nbtags_o50 = new TH1F("nbtags_o50", "", 4,-0.5,3.5);
    nbtags_o50->SetDirectory(rootdir);
    TH1F *nbtags_u50 = new TH1F("nbtags_u50", "", 4,-0.5,3.5);
    nbtags_u50->SetDirectory(rootdir);

    // bjetpT
    TH1F *bjetpt_o50 = new TH1F("bjetpt_o50", "", 200,0,100);
    bjetpt_o50->SetDirectory(rootdir);
    TH1F *bjetpt_u50 = new TH1F("bjetpt_u50", "", 200,0,100);
    bjetpt_u50->SetDirectory(rootdir);
  

    // Loop over events to Analyze
    unsigned int nEventsTotal = 0;
    unsigned int nEventsChain = chain->GetEntries();
    if( nEvents >= 0 ) nEventsChain = nEvents;
    TObjArray *listOfFiles = chain->GetListOfFiles();
    TIter fileIter(listOfFiles);
    TFile *currentFile = 0;

    // get the number of events in each category (U50/O50)
    int loadedU50events = 0;
    int loadedO50events = 0;
    int nFilesOver50 = 0;
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        bool isO50 = (strstr(currentFile->GetTitle(), "M-10") == NULL);  

        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        if(isO50){
            loadedO50events += tree->GetEntries();
            nFilesOver50++;
        }else{
            loadedU50events += tree->GetEntries();
        }
    }

    cout << "Number of O50 files: " << nFilesOver50 << "\nNumber of U50 files: " << chain->GetNtrees() - nFilesOver50 << endl;

    fileIter.Reset();
    int fileCounter = -1;

    // File Loop
    while ( (currentFile = (TFile*)fileIter.Next()) ) {

        fileCounter++;
        int isU50 = (fileCounter >= nFilesOver50);

        // Get File Content
        TFile *file = new TFile( currentFile->GetTitle() );
        TTree *tree = (TTree*)file->Get("Events");
        if(fast) TTreeCache::SetLearnEntries(10);
        if(fast) tree->SetCacheSize(128*1024*1024);
        cms3.Init(tree);
    
        // total events in each sample
        int totalO50events = 19925500;
        int totalU50events = 14820919;

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
            double scale;
            if(!isU50)
                scale = evt_scale1fb()*10*totalO50events/loadedO50events;
            if(isU50)
                scale = evt_scale1fb()*10*totalU50events/loadedU50events;
    
            // Progress
            CMS3::progress( nEventsTotal, nEventsChain );            

            /******** Analysis Code *********/

            // lep pT, eta, phi. these come first b/c they do not have any cuts

            int nElecTotal = els_p4().size();
            int nMuonTotal = mus_p4().size();
            for(int i=0; i<nElecTotal; i++){
                if(!isU50){
                    leppt_o50->Fill(els_p4()[i].Pt(), scale);
                }else{
                    leppt_u50->Fill(els_p4()[i].Pt(), scale);
                }
                                
                if(els_p4()[i].Pt() < 20)
                    continue;

                if(!isU50){
                    lep_eta_o50->Fill(els_p4()[i].Eta(), scale);
                    lep_phi_o50->Fill(els_p4()[i].Phi(), scale);
                }else{
                    lep_eta_u50->Fill(els_p4()[i].Eta(), scale);
                    lep_phi_u50->Fill(els_p4()[i].Phi(), scale);
                }                               
            }
            for(int i=0; i<nMuonTotal; i++){
                
                if(!isU50){
                    leppt_o50->Fill(mus_p4()[i].Pt(), scale);
                }else{
                    leppt_u50->Fill(mus_p4()[i].Pt(), scale);
                }
                
                if(mus_p4()[i].Pt() < 20)
                    continue;

                if(!isU50){
                    lep_eta_o50->Fill(mus_p4()[i].Eta(), scale);
                    lep_phi_o50->Fill(mus_p4()[i].Phi(), scale);
                }else{
                    lep_eta_u50->Fill(mus_p4()[i].Eta(), scale);
                    lep_phi_u50->Fill(mus_p4()[i].Phi(), scale);
                }                               

            }

            // dilepton invariant mass

            // genps
            vector<int> good;
            int ngen = genps_id().size();
            for(int i=0; i<ngen; i++){
                int pid = abs(genps_id()[i]);
                if((pid==11 || pid==13) && genps_status()[i]==23){
                    good.push_back(i);
                }
            }

            for(unsigned int i=0; i<good.size(); i++){
                for(unsigned int j=i+1; j<good.size(); j++){
                    double mass = (genps_p4()[good[i]]+genps_p4()[good[j]]).M();
                    if(!isU50){
                        mLL_genps_o50->Fill(mass, scale);
                        mLL_genps_noscale_o50->Fill(mass, 1);                        
                    }else{
                        mLL_genps_u50->Fill(mass, scale);
                        mLL_genps_noscale_u50->Fill(mass, 1);
                    }
                }
            }

            // reco (hypotheses)
            int nhyp = hyp_p4().size();
            int besthyp_nocuts = -1;
            double bestpT_nocuts = 0;
            int besthyp_cuts = -1;
            double bestpT_cuts = 0;
            for(int i = 0; i < nhyp; i++){
                if(!isU50)
                    mLL_reco_all_o50->Fill((hyp_ll_p4()[i]+hyp_lt_p4()[i]).M(), scale);
                else
                    mLL_reco_all_u50->Fill((hyp_ll_p4()[i]+hyp_lt_p4()[i]).M(), scale);
               
                double totalpT = hyp_ll_p4()[i].Pt() + hyp_lt_p4()[i].Pt();
                if(totalpT > bestpT_nocuts){
                    bestpT_nocuts = totalpT;
                    besthyp_nocuts = i;
                }

                // momentum cut
                if(hyp_ll_p4()[i].Pt()<20 || hyp_lt_p4()[i].Pt()<20)
                    continue;
                
                if(!isU50)
                    mLL_reco_pT20_o50->Fill((hyp_ll_p4()[i]+hyp_lt_p4()[i]).M(), scale);
                else
                    mLL_reco_pT20_u50->Fill((hyp_ll_p4()[i]+hyp_lt_p4()[i]).M(), scale);
                
                // opposite sign
                if(hyp_ll_charge()[i] + hyp_lt_charge()[i] != 0)
                    continue;
                
                if(!isU50)
                    mLL_reco_pT20_OS_o50->Fill((hyp_ll_p4()[i]+hyp_lt_p4()[i]).M(), scale);
                else
                    mLL_reco_pT20_OS_u50->Fill((hyp_ll_p4()[i]+hyp_lt_p4()[i]).M(), scale);               

                
                if(abs(hyp_ll_id()[i])==11 && !isVetoElectronPOG(hyp_ll_index()[i]))
                    continue;
                if(abs(hyp_lt_id()[i])==11 && !isVetoElectronPOG(hyp_lt_index()[i]))
                    continue;
                if(abs(hyp_ll_id()[i])==13 && !isLooseMuonPOG(hyp_ll_index()[i]))
                    continue;
                if(abs(hyp_lt_id()[i])==13 && !isLooseMuonPOG(hyp_lt_index()[i]))
                    continue;

                if(totalpT > bestpT_cuts){
                    bestpT_cuts = totalpT;
                    besthyp_cuts = i;
                }
            }
            if(besthyp_cuts > -1){
                if(!isU50)
                    mLL_reco_pT20_OS_best_o50->Fill((hyp_ll_p4()[besthyp_cuts]+hyp_lt_p4()[besthyp_cuts]).M(), scale);
                else
                    mLL_reco_pT20_OS_best_u50->Fill((hyp_ll_p4()[besthyp_cuts]+hyp_lt_p4()[besthyp_cuts]).M(), scale);
            } 
            if(besthyp_nocuts > -1){
                if(!isU50)
                    mLL_reco_best_o50->Fill((hyp_ll_p4()[besthyp_nocuts]+hyp_lt_p4()[besthyp_nocuts]).M(), scale);
                else
                    mLL_reco_best_u50->Fill((hyp_ll_p4()[besthyp_nocuts]+hyp_lt_p4()[besthyp_nocuts]).M(), scale);
            } 

            // no good Z-candidate pair of leptons was found
            if(besthyp_cuts == -1)
                continue;

            // pfmet

            if(!isU50)
                pfmet_o50->Fill(evt_pfmet(),scale);
            else
                pfmet_u50->Fill(evt_pfmet(),scale);

            // njets, H_T, jet pT, nbtags, bjetpT

            int njetstotal = pfjets_p4().size();
            int ngoodjets = 0;
            int ngoodidjets = 0;
            int nbtags = 0;
            double h_t = 0;

            for(int i =0; i<njetstotal; i++){

                // reject jet if it is too close to one of the Z leptons
                double jetEta = pfjets_p4()[i].Eta();
                double jetPhi = pfjets_p4()[i].Phi();
                double l1Eta = hyp_ll_p4()[besthyp_cuts].Eta();
                double l2Eta = hyp_lt_p4()[besthyp_cuts].Eta();
                double l1Phi = hyp_ll_p4()[besthyp_cuts].Phi();
                double l2Phi = hyp_lt_p4()[besthyp_cuts].Phi();
                double dR1 = sqrt((jetEta-l1Eta)*(jetEta-l1Eta)+(jetPhi-l1Phi)*(jetPhi-l1Phi));
                double dR2 = sqrt((jetEta-l2Eta)*(jetEta-l2Eta)+(jetPhi-l2Phi)*(jetPhi-l2Phi));
                if(dR1 < 0.4 || dR2 < 0.4)
                    continue;                

                bool isBtag = (pfjets_pfCombinedInclusiveSecondaryVertexV2BJetTag()[i] > 0.814);                

                if(pfjets_p4()[i].Pt() >= 40){
                    if(fabs(pfjets_p4()[i].Eta())<2.4){
                        ngoodjets++;
                        if(isLoosePFJet(i))
                            ngoodidjets++;
                    }
                    h_t += pfjets_p4()[i].Pt();
                    if(isBtag)
                        nbtags++;
                }
                if(!isU50){
                    jetpt_o50->Fill(pfjets_p4()[i].Pt(), scale);
                    if(isBtag)
                        bjetpt_o50->Fill(pfjets_p4()[i].Pt(), scale);                        
                }else{
                    jetpt_u50->Fill(pfjets_p4()[i].Pt(), scale);
                    if(isBtag)
                        bjetpt_u50->Fill(pfjets_p4()[i].Pt(), scale);                        
                }
            }

            if(!isU50){
                njets_o50->Fill(ngoodjets,scale);                
                njets_jetid_o50->Fill(ngoodidjets,scale);                
                nbtags_o50->Fill(nbtags,scale);                
                if(ngoodjets > 0)
                    ht_o50->Fill(h_t,scale);
            }else{
                njets_u50->Fill(ngoodjets,scale);
                njets_jetid_u50->Fill(ngoodidjets,scale);
                nbtags_u50->Fill(nbtags,scale);
                if(ngoodjets > 0)
                    ht_u50->Fill(h_t,scale);
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
  

    // mLL_genps
    std::vector<TH1F*> bkg;
    bkg.push_back(mLL_genps_o50);
    bkg.push_back(mLL_genps_u50);
    std::vector<string> str;
    str.push_back("DY (m_{LL}>50)");
    str.push_back("DY (m_{LL}<50)");
    TH1F *null = new TH1F("","",1,0,1);
    dataMCplotMaker(null, bkg, str, "Dilepton Invariant Mass", "gen leptons", "--outputName mLL_genps.pdf --xAxisLabel M_{LL}  --setMinimum 1000" );

    // mLL_genps_noscale
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_genps_noscale_o50);
    bkg.push_back(mLL_genps_noscale_u50);
    dataMCplotMaker(null, bkg, str, "Dilepton Invariant Mass", "gen leptons, no scaling", "--outputName mLL_genps_noscale.pdf --xAxisLabel M_{LL} --setMinimum 10" );

    // mLL_reco_all
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_reco_all_o50);
    bkg.push_back(mLL_reco_all_u50);
    dataMCplotMaker(null, bkg, str, "Dilepton Invariant Mass", "reco, all hypotheses", "--outputName mLL_reco_all.pdf --xAxisLabel M_{LL} --isLinear" );

    // mLL_reco_best
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_reco_best_o50);
    bkg.push_back(mLL_reco_best_u50);
    dataMCplotMaker(null, bkg, str, "Dilepton Invariant Mass", "reco, best hypothesis", "--outputName mLL_reco_best.pdf --xAxisLabel M_{LL} --isLinear" );

    // mLL_reco_pT20
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_reco_pT20_o50);
    bkg.push_back(mLL_reco_pT20_u50);
    dataMCplotMaker(null, bkg, str, "Dilepton Invariant Mass", "reco, pT>20", "--outputName mLL_reco_pT20.pdf --xAxisLabel M_{LL} --isLinear" );

    // mLL_reco_pT20_OS
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_reco_pT20_OS_o50);
    bkg.push_back(mLL_reco_pT20_OS_u50);
    dataMCplotMaker(null, bkg, str, "Dilepton Invariant Mass", "reco, pT>20, OS", "--outputName mLL_reco_pT20_OS.pdf --xAxisLabel M_{LL} --isLinear" );

    // mLL_reco_pT20_OS_best
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(mLL_reco_pT20_OS_best_o50);
    bkg.push_back(mLL_reco_pT20_OS_best_u50);
    dataMCplotMaker(null, bkg, str, "Dilepton Invariant Mass", "reco, pT>20, OS, best hyp", "--outputName mLL_reco_pT20_OS_best.pdf --xAxisLabel M_{LL} --isLinear" );

    // pfmet
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(pfmet_o50);
    bkg.push_back(pfmet_u50);
    dataMCplotMaker(null, bkg, str, "pfmet", "", "--outputName pfmet.pdf --xAxisLabel MET --isLinear" );
 
    // njets
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(njets_o50);
    bkg.push_back(njets_u50);
    dataMCplotMaker(null, bkg, str, "njets", "pT>40, |eta|<2.4", "--outputName njets.pdf --xAxisLabel Njets --noXaxisUnit --setMinimum 100 --noDivisionLabel --nDivisions 10" );

    // njets_jetid
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(njets_jetid_o50);
    bkg.push_back(njets_jetid_u50);
    dataMCplotMaker(null, bkg, str, "njets", "pT>40, |eta|<2.4, jet id", "--outputName njets_jetid.pdf --xAxisLabel Njets --noXaxisUnit --setMinimum 100 --noDivisionLabel --nDivisions 10" );

    // H_T
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(ht_o50);
    bkg.push_back(ht_u50);
    dataMCplotMaker(null, bkg, str, "H_T", "jet pT>40", "--outputName H_T.pdf --xAxisLabel H_{T} --isLinear" );

    // jet pT
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(jetpt_o50);
    bkg.push_back(jetpt_u50);
    dataMCplotMaker(null, bkg, str, "jet pT", "", "--outputName jetpT.pdf --xAxisLabel p_{T} --setMinimum 1000" );

    // lep pT
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(leppt_o50);
    bkg.push_back(leppt_u50);
    dataMCplotMaker(null, bkg, str, "lepton pT", "", "--outputName leppT.pdf --xAxisLabel p_{T} --setMinimum 1000" );

    // lep eta
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(lep_eta_o50);
    bkg.push_back(lep_eta_u50);
    dataMCplotMaker(null, bkg, str, "lepton eta", "pT>20", "--outputName lep_eta.pdf --xAxisLabel eta --noXaxisUnit --isLinear --noDivisionLabel" );

    // lep phi
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(lep_phi_o50);
    bkg.push_back(lep_phi_u50);
    dataMCplotMaker(null, bkg, str, "lepton phi", "pT>20", "--outputName lep_phi.pdf --xAxisLabel phi --noXaxisUnit --isLinear --noDivisionLabel" );

    // nbtags
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(nbtags_o50);
    bkg.push_back(nbtags_u50);
    dataMCplotMaker(null, bkg, str, "nBtags", "pT>40", "--outputName nBtags.pdf --xAxisLabel nBtags --noXaxisUnit --setMinimum 10000 --noDivisionLabel --nDivisions 4" );

    // bjetpT
    bkg.pop_back(); bkg.pop_back();
    bkg.push_back(bjetpt_o50);
    bkg.push_back(bjetpt_u50);
    dataMCplotMaker(null, bkg, str, "b-jet pT", "", "--outputName bjetpT.pdf --xAxisLabel p_{T} --setMinimum 1000" );
 

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
