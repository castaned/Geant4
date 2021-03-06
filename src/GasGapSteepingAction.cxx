//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#include "GasGapSteppingAction.hh"
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

GasGapSteppingAction::GasGapSteppingAction()
{;}

GasGapSteppingAction::~GasGapSteppingAction()
{;}

void GasGapSteppingAction::UserSteppingAction(const G4Step * theStep)
{

  G4cout<<" Entering the SteppingAction    "<<G4endl;
  
  G4Track * theTrack = theStep->GetTrack();
  
  // check if it is alive
  if(theTrack->GetTrackStatus()!=fAlive) { return; }

  // // check if it is primary
  // if(theTrack->GetParentID()!=0) { return; }
  
  // // check if it is NOT muon
  // G4ParticleDefinition * particleType = theTrack->GetDefinition();
  // if((particleType==G4MuonPlus::MuonPlusDefinition())
  //    ||(particleType==G4MuonMinus::MuonMinusDefinition()))
  //   { return; }
  
  // check if it is entering to the GasGap volume
  // G4StepPoint * thePrePoint = theStep->GetPreStepPoint();
  // G4VPhysicalVolume * thePrePV = thePrePoint->GetPhysicalVolume();
  // G4String thePrePVname = thePrePV->GetName();
  // //  if(thePrePVname(0,6)=="GasGap") {G4cout<<"Entering the volume  "<<G4endl; return; }
  // G4cout<<" PrePVname   "<<thePrePVname<<G4endl;
  // //  if(thePrePVname=="GasGap") {G4cout<<"   Entering the volume  "<<G4endl; return; }
  // G4StepPoint * thePostPoint = theStep->GetPostStepPoint();
  // G4VPhysicalVolume * thePostPV = thePostPoint->GetPhysicalVolume(); 
  // G4String thePostPVname = thePostPV->GetName();
  // G4cout<<" PostPVname   "<<thePostPVname<<G4endl;
  //  if(thePostPVname(0,6)!="GasGap") {G4cout<<" Exit the Volume  "<<G4endl; return; }
  //  if(thePostPVname(0,6)!="GasGap") {G4cout<<"Entering the volume  "<<G4endl; return; }
  
  //then suspend the track
  theTrack->SetTrackStatus(fSuspend);
}


