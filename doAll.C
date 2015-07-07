{
    gSystem->Load("/home/users/bmarsh/CORE/CMS3_CORE.so");
    gROOT->ProcessLine(".L /home/users/bmarsh/Software/dataMCplotMaker/dataMCplotMaker.cc++");
    gROOT->ProcessLine(".L ScanChain.C++");
    

    TChain *ch = new TChain("Events"); 
    // ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/merged_ntuple_100.root");
    // ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/merged_ntuple_101.root");
    // ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/merged_ntuple_102.root");
    // ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/merged_ntuple_100.root");
    // ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/merged_ntuple_101.root");
    // ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/merged_ntuple_102.root");

    ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/V07-04-03/*10*.root");
    ch->Add("/hadoop/cms/store/group/snt/run2_50ns/DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8_RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/V07-04-03/*10*.root");
    
    // phys14 stuff
    //ch->Add("/hadoop/cms/store/group/snt/phys14/DYJetsToLL_M-50_13TeV-madgraph-pythia8_Phys14DR-PU20bx25_PHYS14_25_V1-v1/V07-02-08/merged_ntuple_10.root");
    ScanChain(ch); 
}
