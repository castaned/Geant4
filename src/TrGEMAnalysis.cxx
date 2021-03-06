#include "TrGEMAnalysis.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4Run.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4String.hh"

#include <TROOT.h>
#include <TFile.h>
#include <TH1D.h>
#include <TNtuple.h>

TrGEMAnalysis* TrGEMAnalysis::singleton = 0 ;

TrGEMAnalysis* TrGEMAnalysis::GetInstance() {
  if ( singleton == 0 ) {
    static TrGEMAnalysis analysis;
    singleton = &analysis;
  }
  return singleton;
}

TrGEMAnalysis::~TrGEMAnalysis() 
{}

TrGEMAnalysis::TrGEMAnalysis() 
{
  m_ROOT_file = 0;
}

void TrGEMAnalysis::PrepareNewEvent(const G4Event* /*anEvent*/)
{
  //Reset variables relative to this event
  isNewEvent = true ;
  //   thisEventTotEM = 0;
  //  thisEventCentralEM = 0;
  //  thisEventSecondaries = 0;
  
  
  Event = 0;
  EDepI = -10000;
  Trajnum = -10000;
  TrajPoint = -10000;
  nSteps = 0;
  ETotstep = 0.;
  deltaETotstep = 0.;
   
   
  Trjen= -10000.;

  for(G4int k=0;k<200;k++){

    Trjposx[k] = -10000.;
    Trjposy[k] = -10000.;
    Trjposz[k] = -10000.;

    Trjposx_perstep[k] = -10000.;
    Trjposy_perstep[k] = -10000.;
    Trjposz_perstep[k] = -10000.;

    SLength_perstep[k] = -10000.;
    Nclust_perstep[k] = 0;
    Nclust2_perstep[k] = 0;
    ETot_perstep[k] = -10000.;
    VolumeName_perstep[k]= -10000.;
    EDelta_perstep[k] = -10000.;
    EDepI_perstep[k] = -10000.;
    EDepSec_perstep[k] = -10000.;
    EDepImSec_perstep[k] = -10000.;
    EDepImu_perstep[k] = -10000.;
    pdgIDstep[k] = -10000;
    parentIDstep[k] = -10000.;
    genZstep[k] = -10000.;
     
    nSec[k] = 0;
    nIonAlStep[k] = 0;

    for(G4int l=0;l<200;l++){
      posIAlStepx[k][l] = -10000;
      posIAlStepy[k][l] = -10000;
      posIAlStepz[k][l] = -10000;
      
      //      posIAlStepx[k] = -10000.;
      //      posIAlStepy[k] = -10000.;
      //      posIAlStepz[k] = -10000.;
    }
    
  }
 
  //  elexevt = 0 ;
  //  posxevt = 0 ;
  //  gammaxevt = 0 ;
  //  secoxevt = 0 ;
   
  // for(G4int t=0;t<9;t++){
  
  //     driftEdep[t] = 0. ;
  //     driftEdepI[t] = 0. ;
 
  //     transferEdep[t] = 0. ;
  //     transferEdepI[t] = 0. ;
      
  //     transfer2Edep[t]  = 0. ;
  //     transfer2EdepI[t]  = 0. ;

  //     inductionEdep[t]  = 0. ;
  //     inductionEdepI[t]  = 0. ;

  //     driftEdep_B[t]  = 0. ;
  //     driftEdepI_B[t]  = 0. ;

  //     transferEdep_B[t]  = 0. ;
  //     transferEdepI_B[t]  = 0. ;

  //     transfer2Edep_B[t]  = 0. ;
  //     transfer2EdepI_B[t]  = 0. ;

  //     inductionEdep_B[t]  = 0. ;
  //     inductionEdepI_B[t]  = 0. ;
 
  //  }
  //  eleGap=0;
  //  chargeGap=0;
  //  eleGap_B=0;
  //  chargeGap_B=0;
  //  primaryEne=0.;
  //  zInteraction=0.;
 
  //  gapTrackPart.clear();
  //  gapTrackGenProcess.clear();
  //  gapTrackVolume.clear();
  //  gapTrackGenZ.clear();
  //  gapTrackGap.clear();
  //  gapTrackEne.clear();

  //  postTrackPart.clear();
  //  postTrackEne.clear();
   
  //  pdgCode.clear();
  //  kineticEnergy.clear();
  //  positionX.clear();
  //  positionY.clear();
  //  positionZ.clear();
  //  momentumX.clear();
  //  momentumY.clear();
  //  momentumZ.clear();
 
}

void TrGEMAnalysis::PrepareNewRun(const G4Run* /*aRun*/)
{

  eventCounter = 0 ;
  //Reset variables relative to the run
  // thisRunTotEM  = 0;
  // thisRunTotEM2 = 0;
  // thisRunCentralEM  = 0;
  // thisRunCentralEM2 = 0;
  // n_gamma = 0;
  // n_electron = 0;
  // n_positron = 0;

  
  // pgapTrackPart= &gapTrackPart;
  // pgapTrackGenProcess= &gapTrackGenProcess;
  // pgapTrackVolume= &gapTrackVolume;
  // pgapTrackGenZ= &gapTrackGenZ;
  // pgapTrackGap= &gapTrackGap;
  // pgapTrackEne= &gapTrackEne;
  
  // ppostTrackPart = &postTrackPart;
  // ppostTrackEne = &postTrackEne;
  
  // ppdgCode = &pdgCode;
  // pkineticEnergy = &kineticEnergy;
  // ppositionX = &positionX;
  // ppositionY = &positionY;
  // ppositionZ = &positionZ;
  // pmomentumX =  &momentumX;
  // pmomentumY =  &momentumY;
  // pmomentumZ =  &momentumZ;

  
  // create ROOT file
  m_ROOT_file = new TFile("task3.root","RECREATE");
  if(m_ROOT_file) 
    G4cout << "ROOT file task3.root is created " << G4endl;
  else {
    //G4Exception("ROOT file task3.root has not been created!");
    G4cerr << "ROOT file task3.root has not been created!" << G4endl;
  }
m_ROOT_file = new TFile("task3.root","RECREATE");
  if(m_ROOT_file) 
    G4cout << "ASCII file is created " << G4endl;
  else {
    //G4Exception("ROOT file task3.root has not been created!");
    G4cerr << "ASCII file has not been created!" << G4endl;
  }
  // create histograms
  //  m_ROOT_histo0 = new TH1D("etot","Total energy deposit normalized to beam energy",100,0,1);
  //  m_ROOT_histo1 = new TH1D("e0","Energy deposit in central crystal normalized to beam energy",100,0,1);
  //  m_ROOT_histo2 = new TH1D("ez","Energy profile along the GEM (mm)",100,0,20);
  //  m_ROOT_histo3 = new TH1D("egap","Energy profile vs. GasGap",5,0,5);
  // //ntuple = new TNtuple("gasgap1","secondaries in gas gap 1","gapGamma:gapElectron:gapPositron") ;

  // create tree and branch(es)
  t = new TTree("MyRun","Run with awesome data") ;
  t->Branch("Event",&Event,"Event/I");
  
  t->Branch("primaryEn",&primaryEn,"primaryEn/D");
  t->Branch("primarypos_x",&primarypos_x,"primarypos_x/D");
  t->Branch("primarypos_y",&primarypos_y,"primarypos_y/D");
  t->Branch("primarypos_z",&primarypos_z,"primarypos_z/D");
   
  t->Branch("EDepI",&EDepI,"EDepI/D");
  t->Branch("ETotstep",&ETotstep,"ETotstep/D");
  t->Branch("deltaETotstep",&deltaETotstep,"deltaETotstep/D");
  t->Branch("Trajnum",&Trajnum,"Trajnum/I");
  t->Branch("TrajPoint",&TrajPoint,"TrajPoint/I");
  t->Branch("nSteps",&nSteps,"nSteps/I");
  t->Branch("nSec",&nSec,"nSec[nSteps]/I");

  t->Branch("nIonAlStep",&nIonAlStep,"nIonAlStep[nSteps]/I");
  
  t->Branch("Trjposx",&Trjposx,"Trjposx[20]/D");
  t->Branch("Trjposy",&Trjposy,"Trjposy[20]/D");
  t->Branch("Trjposz",&Trjposz,"Trjposz[20]/D");

  t->Branch("Trjposx_perstep",&Trjposx_perstep,"Trjposx_perstep[nSteps]/D");
  t->Branch("Trjposy_perstep",&Trjposy_perstep,"Trjposy_perstep[nSteps]/D");
  t->Branch("Trjposz_perstep",&Trjposz_perstep,"Trjposz_perstep[nSteps]/D");

  t->Branch("posIAlStepx",&posIAlStepx,"posIAlStepx[200][200]/D");
  t->Branch("posIAlStepy",&posIAlStepy,"posIAlStepy[200][200]/D");
  t->Branch("posIAlStepz",&posIAlStepz,"posIAlStepz[200][200]/D");

//   t->Branch("posIAlStepx",&posIAlStepx,"posIAlStepx[nIonAlStep]/D");
//   t->Branch("posIAlStepy",&posIAlStepy,"posIAlStepy[nIonAlStep]/D");
//   t->Branch("posIAlStepz",&posIAlStepz,"posIAlStepz[nIonAlStep]/D");

  // t->Branch("Stepno",&Stepno,"Nclust_perstep
  
  t->Branch("SLength_perstep",&SLength_perstep,"SLength_perstep[nSteps]/D");
  t->Branch("ETot_perstep",&ETot_perstep,"ETot_perstep[nSteps]/D");
  t->Branch("VolumeName_perstep",&VolumeName_perstep,"VolumeName_perstep[nSteps]/D");
  t->Branch("Nclust_perstep",&Nclust_perstep,"Nclust_perstep[nSteps]/I");  
  t->Branch("Nclust2_perstep",&Nclust2_perstep,"Nclust2_perstep[nSteps]/I");
  t->Branch("EDelta_perstep",&EDelta_perstep,"EDelta_perstep[nSteps]/D");
  t->Branch("EDepI_perstep",&EDepI_perstep,"EDepI_perstep[nSteps]/D");
  t->Branch("EDepSec_perstep",&EDepSec_perstep,"EDepSec_perstep[nSteps]/D");
  t->Branch("EDepImSec_perstep",&EDepImSec_perstep,"EDepImSec_perstep[nSteps]/D");
  t->Branch("EDepImu_perstep",&EDepImu_perstep,"EDepImu_perstep[nSteps]/D");
  t->Branch("pdgIDstep",&pdgIDstep,"pdgIDstep[nSteps]/I");
  t->Branch("parentIDstep",&parentIDstep,"parentIDstep[nSteps]/I");
  t->Branch("genZstep",&genZstep,"genZstep[nSteps]/D");

  //   t->Branch("Trjen",&Trjen,"Trjen/D");
  //   t->Branch("elexevt",&elexevt,"elexevt/I") ;
  //   t->Branch("posxevt",&posxevt,"posxevt/I") ;
  //   t->Branch("gammaxevt",&gammaxevt,"gammaxevt/I") ;
  //   t->Branch("secoxevt",&secoxevt,"secoxevt/I") ;
 
  //   t->Branch("driftEdep",driftEdep,"driftEdep[9]/D") ;
  //   t->Branch("driftEdepI",driftEdepI,"driftEdepI[9]/D") ;
  //   t->Branch("transferEdep",transferEdep, "transferEdep[9]/D") ;
  //   t->Branch("transferEdepI",transferEdepI, "transferEdepI[9]/D") ;
  //   t->Branch("transfer2Edep",transfer2Edep, "transfer2Edep[9]/D") ;
  //   t->Branch("transfer2EdepI",transfer2EdepI, "transfer2EdepI[9]/D") ;
  //   t->Branch("inductionEdep",inductionEdep, "inductionEdep[9]/D") ;
  //   t->Branch("inductionEdepI",inductionEdepI, "inductionEdepI[9]/D") ;
  //   t->Branch("driftEdep_B",driftEdep_B,"driftEdep_B[9]/D") ;
  //   t->Branch("driftEdepI_B",driftEdepI_B,"driftEdepI_B[9]/D") ;
  //   t->Branch("transferEdep_B",transferEdep_B, "transferEdep_B[9]/D") ;
  //   t->Branch("transferEdepI_B",transferEdepI_B, "transferEdepI_B[9]/D") ;
  //   t->Branch("transfer2Edep_B",transfer2Edep_B, "transfer2Edep_B[9]/D") ;
  //   t->Branch("transfer2EdepI_B",transfer2EdepI_B, "transfer2EdepI_B[9]/D") ;
  //   t->Branch("inductionEdep_B",inductionEdep_B, "inductionEdep_B[9]/D") ;
  //   t->Branch("inductionEdepI_B",inductionEdepI_B, "inductionEdepI_B[9]/D") ;


  //   t->Branch("neutronSensitivity",&neutronSensitivity, "neutronSensitivity/O") ;
  //   t->Branch("eleGap",&eleGap, "eleGap/O") ;
  //   t->Branch("eleGap_B",&eleGap_B, "eleGap_B/O") ;
  //   t->Branch("chargeGap",&chargeGap, "chargeGap/O") ;
  //   t->Branch("chargeGap_B",&chargeGap_B, "chargeGap_B/O") ;
  //   t->Branch("primaryEne",&primaryEne, "primaryEne/D") ;
  //   t->Branch("zInteraction",&zInteraction, "zInteraction/D") ;
  
  //   t->Branch("gapTrackPart",&pgapTrackPart);
  //   t->Branch("gapTrackGenProcess",&pgapTrackGenProcess);
  //   t->Branch("gapTrackVolume",&pgapTrackVolume);
  //   t->Branch("gapTrackGenZ",&pgapTrackGenZ);
  //   t->Branch("gapTrackGap",&pgapTrackGap);
  //   t->Branch("gapTrackEne",&pgapTrackEne);
  
  //   t->Branch("postTrackPart",&ppostTrackPart);
  //   t->Branch("postTrackEne",&ppostTrackEne);
   

  //   g = new TTree("Garfield","Interesting variables for Garfield") ;
  // //  g->Branch("globalTime",&globalTime,"globalTime/D") ;
  //   g->Branch("pdgCode",&pdgCode) ;
  //   g->Branch("kineticEnergy",&kineticEnergy) ;
  //   g->Branch("positionX",&positionX) ;
  //   g->Branch("positionY",&positionY) ;
  //   g->Branch("positionZ",&positionZ) ;
  //   g->Branch("momentumX",&momentumX) ;
  //   g->Branch("momentumY",&momentumY) ;
  //   g->Branch("momentumZ",&momentumZ) ;
  //  // g->Branch("momentumDirectionX",&momentumDirectionX,"momentumDirectionX/D") ;
  //   //g->Branch("momentumDirectionY",&momentumDirectionY,"momentumDirectionY/D") ;
  //  // g->Branch("momentumDirectionZ",&momentumDirectionZ,"momentumDirectionZ/D") ;

   
}

void TrGEMAnalysis::EndOfEvent(const G4Event* anEvent)
{
  //Accumulate over the run
  //  thisRunTotEM += thisEventTotEM;

  //Uncomment these lines for more verbosity:
  G4cout<<"Event ID: "<< anEvent->GetEventID() <<G4endl;
  G4cout<<" ===================" <<G4endl;
  //<<G4BestUnit(thisEventTotEM,"Energy")<<" Secondaries: "<<thisEventSecondaries<<G4endl;
  //G4cout<<G4BestUnit(thisEventCentralEM,"Energy")<<G4endl;

  //save information to ROOT
  //m_ROOT_histo0->Fill(thisEventTotEM/beamEnergy, 1.0);
  //ntuple->Fill(double(n_gapGamma[0]),double(n_gapElectron[0]),double(n_gapPositron[0])) ;

  Event = anEvent->GetEventID();
  
  t->Fill() ; 
  //   g->Fill() ;
  
}

void TrGEMAnalysis::EndOfRun(const G4Run* aRun)
{

  //Some print outs
  G4int numEvents = aRun->GetNumberOfEvent();
  if(numEvents == 0) { return; }

  //G4double norm = numEvents*beamEnergy;
  // G4cout << "================="<<G4endl;
  // G4cout << "Summary for run: " << aRun->GetRunID() << G4endl ;
  // G4cout << "  Beam of " << beamParticle->GetParticleName() 
  //    << " kinetic energy: "<< G4BestUnit(beamEnergy,"Energy") << G4endl ;
  // G4cout << "  Event processed:         " << numEvents << G4endl ;
  // G4cout << "  Average number of gamma: "<<(G4double)n_gamma/(G4double)numEvents<<G4endl ;
  // G4cout << "  Average number of e-   : "<<(G4double)n_electron/(G4double)numEvents<<G4endl ;
  // G4cout << "  Average number of e+   : "<<(G4double)n_positron/(G4double)numEvents<<G4endl ;
  // for(G4int i = 0; i < 4; i++) {
  //    G4cout << "Gap number " << i + 1 << G4endl ;
  //    G4cout << "  Average number of gamma: " << (G4double)n_gapGamma[i]/(G4double)numEvents << G4endl ;
  //    G4cout << "  Average number of e-   : " << (G4double)n_gapElectron[i]/(G4double)numEvents << G4endl ;
  //    G4cout << "  Average number of e+   : " << (G4double)n_gapPositron[i]/(G4double)numEvents << G4endl ;
  //    G4cout << "  - - - - - - - - - - " << G4endl ;
  // }
  // G4cout << "  Average energy deposition in TrGEM: "
  //    << G4BestUnit(thisRunTotEM/(G4double)numEvents,"Energy") << G4endl ;

  // Writing and closing the ROOT file
  m_ROOT_file->cd() ;
  t->Write() ;
  //   g->Write() ;
  G4cout << "ROOT: files writing..." << G4endl;
  m_ROOT_file->Write();
  G4cout << "ROOT: files closing..." << G4endl;
  m_ROOT_file->Close();
  delete m_ROOT_file;

}

// void TrGEMAnalysis::AddSecondary(const G4ParticleDefinition* part)
// {
//    if(part == G4Gamma::Gamma())            { ++n_gamma; }
//    else if(part == G4Electron::Electron()) { ++n_electron; }  
//    else if(part == G4Positron::Positron()) { ++n_positron; }
// }


// void TrGEMAnalysis::AddGapSecondary(const G4ParticleDefinition* part, G4int gapNum)
// {
//    gapNum-- ;
//    if(part == G4Gamma::Gamma())            { ++n_gapGamma[gapNum]; }
//    else if(part == G4Electron::Electron()) { ++n_gapElectron[gapNum]; }  
//    else if(part == G4Positron::Positron()) { ++n_gapPositron[gapNum]; }
// }

// void TrGEMAnalysis::AddEDep(G4double edep, G4double z)
// {
//   //  thisEventTotEM += edep;
//   //  m_ROOT_histo2->Fill(z, edep);
// }

void TrGEMAnalysis::AddEDepI(G4double edepIon)
{
  EDepI = edepIon;
}

void TrGEMAnalysis::AddPrimEn(G4double primen)
{
  primaryEn = primen;
}


void TrGEMAnalysis::AddPrimPos(G4double primx,G4double primy, G4double primz)
{
  primarypos_x = primx;
  primarypos_y = primy;
  primarypos_z = primz;
  
}

void TrGEMAnalysis::AddSLength_perstep(G4int count, G4double sl)
{
  SLength_perstep[count-1] = sl;
}

void TrGEMAnalysis::AddnSteps()
{
  nSteps++;
}

void TrGEMAnalysis::AddnIonAlStep(G4int count, G4int nias){
  nIonAlStep[count-1] = nias;
}

void TrGEMAnalysis::AddnIonPosXStep(G4int count, G4int nion, G4double posx){
  posIAlStepx[count-1][nion] = posx;
}

void TrGEMAnalysis::AddnIonPosYStep(G4int count, G4int nion, G4double posy){
  posIAlStepy[count-1][nion] = posy;
}

void TrGEMAnalysis::AddnIonPosZStep(G4int count, G4int nion, G4double posz){
  posIAlStepz[count-1][nion] = posz;
}


// void TrGEMAnalysis::AddnIonPosXStep(G4int countion, G4double posx){
//   posIAlStepx[countion] = posx;
// }

// void TrGEMAnalysis::AddnIonPosYStep(G4int countion, G4double posy){
//   posIAlStepy[countion] = posy;
// }

// void TrGEMAnalysis::AddnIonPosZStep(G4int countion, G4double posz){
//   posIAlStepz[countion] = posz;
// }

void TrGEMAnalysis::AddnSec(G4int count, G4int nsec){
  nSec[count-1] = nsec;
}

void TrGEMAnalysis::AddEtotSteps(G4double epstep)
{
  ETotstep += epstep;
}


void TrGEMAnalysis::AdddeltaEtotSteps(G4double depstep)
{
  deltaETotstep += depstep;
}

G4int TrGEMAnalysis::GetnStep(){
  return nSteps;
}

void TrGEMAnalysis::AddTrajInf(G4int ntraj){
  Trajnum = ntraj;
}

void TrGEMAnalysis::AddTrajPoint(G4int trajp){
  TrajPoint = trajp;
}

void TrGEMAnalysis::AddTrajPos(G4int count, G4double posx, G4double posy, G4double posz){
  Trjposx[count] = posx;
  Trjposy[count] = posy;
  Trjposz[count] = posz;
}

void TrGEMAnalysis::AddTrajPos_perstep(G4int numstep, G4double posx, G4double posy, G4double posz){
  Trjposx_perstep[numstep-1] = posx;
  Trjposy_perstep[numstep-1] = posy;
  Trjposz_perstep[numstep-1] = posz;
}


void TrGEMAnalysis::AddEDepI_perstep(G4int numstep, G4double edepi){
  EDepI_perstep[numstep-1] = edepi;
}

void TrGEMAnalysis::AddVolumeName_perstep(G4int numstep, G4double volnameID){
  VolumeName_perstep[numstep-1] = volnameID ;
}

void TrGEMAnalysis::AddEDelta_perstep(G4int numstep, G4double edelta){
  EDelta_perstep[numstep-1] = edelta;
}

void TrGEMAnalysis::AddETot_perstep(G4int numstep, G4double etot){
  ETot_perstep[numstep-1] = etot;
}

void TrGEMAnalysis::AddNclust_perstep(G4int numstep, G4int nclust){
  Nclust_perstep[numstep-1] += nclust;
}

void TrGEMAnalysis::AddNclust2_perstep(G4int numstep, G4int nclust2){
  Nclust2_perstep[numstep-1] += nclust2;
}

void TrGEMAnalysis::AddEDepSec_perstep(G4int numstep, G4double edeps){
  EDepSec_perstep[numstep-1] = edeps;
}

void TrGEMAnalysis::AddEDepImSec_perstep(G4int numstep, G4double edepims){
  EDepImSec_perstep[numstep-1] = edepims;
}

void TrGEMAnalysis::AddEDepImu_perstep(G4int numstep, G4double edepimu){
  EDepImu_perstep[numstep-1] = edepimu;
}

void TrGEMAnalysis::AddPDGID(G4int numstep, G4int pdgval)
{
  pdgIDstep[numstep-1] = pdgval;
}


void TrGEMAnalysis::AddParentID(G4int numstep, G4int parentval)
{
  parentIDstep[numstep-1] = parentval;
}

void TrGEMAnalysis::AddgenZ(G4int numstep, G4double genzval)
{
  genZstep[numstep-1] = genzval;
}


// void TrGEMAnalysis::AddTrajEn(G4int count, G4double trjen){
//   Trjen = trjen;
// }

// void TrGEMAnalysis::AddEDepSD(G4double edep, G4int layerIndex)
// {
//    m_ROOT_histo3->Fill(layerIndex, edep);
// }

// void TrGEMAnalysis::SetBeam(const G4ParticleDefinition* part, G4double energy)
// {
//   //   beamParticle = part;
//   //   beamEnergy = energy;
// }

// /*void TrGEMAnalysis::CreateBranch(G4String name, G4int evtNo, G4String type)
//   {
// #ifdef G4ANALYSIS_USE_ROOT
// t->Branch(name, &evtNo, type) ;
// #endif
// }*/

// void TrGEMAnalysis::AddParticlesPerEvent(G4int PDGCode) {
//    secoxevt++ ;
//    if(PDGCode == 11) elexevt++ ;
//    else if(PDGCode == -11) posxevt++ ;
//    else if(PDGCode == 22) gammaxevt++ ;
//    else G4cout << "You must implement a new variable" << G4endl ; 
// }

// void TrGEMAnalysis::SetSensitivity(G4double *someDriftEdep,G4double *someDriftEdepI,
//                                    G4double *someTransferEdep,G4double *someTransferEdepI,
//                                    G4double *someTransfer2Edep,G4double *someTransfer2EdepI,
//                                    G4double *someInductionEdep,G4double *someInductionEdepI,

//                                    G4double *someDriftEdep_B,G4double *someDriftEdepI_B,
//                                    G4double *someTransferEdep_B,G4double *someTransferEdepI_B,
//                                    G4double *someTransfer2Edep_B,G4double *someTransfer2EdepI_B,
//                                    G4double *someInductionEdep_B,G4double *someInductionEdepI_B) {

//    for(G4int t=0;t<9;t++){
//       driftEdep[t] = someDriftEdep[t] ;
//       driftEdepI[t] = someDriftEdepI[t] ;
//    }

//    for(G4int t=0;t<9;t++){
//      transferEdep[t] = someTransferEdep[t] ;
//      transferEdepI[t] = someTransferEdepI[t] ;
//    }
 
//     for(G4int t=0;t<9;t++){
//      transfer2Edep[t] = someTransfer2Edep[t] ;
//      transfer2EdepI[t] = someTransfer2EdepI[t] ;
//    }
 
//     for(G4int t=0;t<9;t++){
//      inductionEdep[t] = someInductionEdep[t] ;
//      inductionEdepI[t] = someInductionEdepI[t] ;
//    }
 
//    for(G4int t=0;t<9;t++){
//       driftEdep_B[t] = someDriftEdep_B[t] ;
//       driftEdepI_B[t] = someDriftEdepI_B[t] ;
//    }

//    for(G4int t=0;t<9;t++){
//      transferEdep_B[t] = someTransferEdep_B[t] ;
//      transferEdepI_B[t] = someTransferEdepI_B[t] ;
//    }
 
//     for(G4int t=0;t<9;t++){
//      transfer2Edep_B[t] = someTransfer2Edep_B[t] ;
//      transfer2EdepI_B[t] = someTransfer2EdepI_B[t] ;
//    }
 
//     for(G4int t=0;t<9;t++){
//      inductionEdep_B[t] = someInductionEdep_B[t] ;
//      inductionEdepI_B[t] = someInductionEdepI_B[t] ;
//    }

// }


// void TrGEMAnalysis::SetNeutronSensitivity(G4bool someBool) {

//    neutronSensitivity = someBool ;

// }

// void TrGEMAnalysis::SetEleGap(G4bool elegap, G4bool elegap_B) {

//    eleGap = elegap ;
//    eleGap_B = elegap_B ;

// }
// void TrGEMAnalysis::SetChargeGap(G4bool chargegap,G4bool chargegap_B ) {

//    chargeGap = chargegap ;
//    chargeGap_B = chargegap_B ;

// }

// void TrGEMAnalysis::SavePrimary(G4double primaryene, G4double zinteraction){
  
//    primaryEne = primaryene;
//    zInteraction = zinteraction;
   
// }
 

// void TrGEMAnalysis::SaveGapTrack(G4int gapPart, std::string genprocess, std::string genvolume, G4double genz, std::string volname,  G4double kinene) {
//       gapTrackPart.push_back(gapPart) ;
//       gapTrackGenProcess.push_back(genprocess) ;
//       gapTrackVolume.push_back(genvolume) ;
//       gapTrackGenZ.push_back(genz) ;
//       gapTrackGap.push_back(volname) ;
//       gapTrackEne.push_back(kinene) ;
// }

// void TrGEMAnalysis::SavePostShieldTrack(G4int postPart,  G4double postEne ) {
//       postTrackPart.push_back(postPart) ;
//       postTrackEne.push_back(postEne) ;
// }

// void TrGEMAnalysis::SaveGarfieldQuantities( 
//       G4int aPdgCode,
//       G4double aKineticEnergy,
//       G4double aPositionX, 
//       G4double aPositionY, 
//       G4double aPositionZ,
//       G4double aMomentumX, 
//       G4double aMomentumY, 
//       G4double aMomentumZ) {

//    pdgCode.push_back(aPdgCode) ;
//    kineticEnergy.push_back( aKineticEnergy ) ;
//    positionX.push_back( aPositionX );
//    positionY.push_back( aPositionY );
//    positionZ.push_back( aPositionZ );
//    momentumX.push_back( aMomentumX );
//    momentumY.push_back( aMomentumY );
//    momentumZ.push_back( aMomentumZ );

// } 
