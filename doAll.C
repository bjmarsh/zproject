{
    gSystem->Load("/home/users/bmarsh/CORE/CMS3_CORE.so");
    gROOT->ProcessLine(".L /home/users/bmarsh/Software/dataMCplotMaker/dataMCplotMaker.cc++");
    gROOT->ProcessLine(".L /home/users/bmarsh/Tools/goodrun.cc++");
    gROOT->ProcessLine(".L ScanChain.C++");
    

    TChain *ch = new TChain("Events"); 

    // drell yan
    ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/*100.root");
    ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/*100.root");

    // ttbar
    ch->Add("/hadoop/cms/store/group/snt/run2_50ns/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/*60.root");

    // WJets
    ch->Add("/hadoop/cms/store/group/snt/run2_50ns/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/*100.root");

    // data
    ch->Add("/hadoop/cms/store/user/mderdzinski/dataTuple/Run2015B_DoubleMuon_MINIAOD_PromptReco-v1/*.root");
    // ch->Add("/hadoop/cms/store/user/cgeorge/dataTuple/Run2015B_DoubleEG_MINIAOD_PromptReco-v1/*.root");
    // ch->Add("/hadoop/cms/store/user/cgeorge/dataTuple/Run2015B_MuonEG_MINIAOD_PromptReco-v1/*.root");
    ScanChain(ch); 
}
