{
    // compiles a couple root scripts then executes make_plots()

    gROOT->ProcessLine(".L /home/users/bmarsh/Software/dataMCplotMaker/dataMCplotMaker.cc++");
    gROOT->ProcessLine(".L make_plots.C++");

    make_plots();

}
