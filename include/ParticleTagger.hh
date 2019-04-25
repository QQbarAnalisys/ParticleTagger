#ifndef ParticleTagger_h
#define ParticleTagger_h 1
#include <iomanip>
#include <EVENT/LCRelation.h>
#include "marlin/Processor.h"
#include "MathOperator.hh"
#include <EVENT/LCCollection.h>
#include <EVENT/MCParticle.h>
#include <EVENT/ReconstructedParticle.h>
#include <IMPL/LCCollectionVec.h>
#include <IMPL/TrackImpl.h>
#include <IMPL/TrackStateImpl.h>
#include <EVENT/Track.h>
#include <EVENT/Vertex.h>
#include <IMPL/ReconstructedParticleImpl.h>
#include <IMPL/LCRelationImpl.h>
#include <UTIL/LCRelationNavigator.h>
#include <UTIL/PIDHandler.h>
#include "MathOperator.hh"
#include <cmath>
#include <string>
#include <vector>

#include <TF1.h>
#include <TRandom.h>
#include <TFile.h>
#include <TTree.h>
//#include <TLorentzVector.h>
using namespace marlin ;

/**
 * 
 */

class ParticleTagger : public Processor
{
  
public:
  
  virtual Processor*  newProcessor() { return new ParticleTagger ; }
  
  ParticleTagger() ;
  virtual ~ParticleTagger() ;
  
  /** Called at the begin of the job before anything is read.
   */
  virtual void init() ;
  
  /** Called for every run.
   */
  virtual void processRunHeader( LCRunHeader* run ) ;
  
  /** Called for every event - the working horse.
   */
  virtual void processEvent( LCEvent * evt ) ; 
  
  
  virtual void check( LCEvent * evt ) ; 
  
  std::vector< EVENT::ReconstructedParticle * > * CopyParticles(std::vector< EVENT::ReconstructedParticle * > * pfos, std::vector< EVENT::Track * > * tracks = NULL);
  EVENT::ReconstructedParticle * CopyParticle(EVENT::ReconstructedParticle * initial);
  EVENT::MCParticle * GetMCParticleTrackRel(EVENT::Track * reco, EVENT::LCCollection * trackrel);
  EVENT::ReconstructedParticle * ReconstructParticle(EVENT::Track *  track);
  void PrintParticle(EVENT::ReconstructedParticle * particle);
  void PrintParticle(EVENT::MCParticle * particle);
  void TagParticle(EVENT::ReconstructedParticle * particle, PIDHandler & pidh);
  /** Called after data processing for clean up.
   */
  virtual void end() ;
  
private:
  int getVertexType(EVENT::ReconstructedParticle * particle);
  float GetOffsetErrorSimple(EVENT::ReconstructedParticle * particle);
  void ClearVariables();
  bool checkParticle(EVENT::ReconstructedParticle * particle, int pdg);
  /** Input collection name.
   */
  std::string _inputPFOCollectionName;
  std::string _inputTrackRelCollectionName;
  std::string _hfilename;
  std::string algorithmName;
  float a;
  float b1;
  float b2;
  float bfield;
  float pcut;

  int _algorithmID;

  std::vector<std::string> _parameterNames;
  float _vtxLayerRadius[3];
  float _ftdLayerRadius[2];
  TFile * _hfile;
  TTree * _hTree;
  int _nEvt;

  float * abdd;
  float * abzz;

  static const int MAXV = 200;
  int _nParticles;	
  float _dEdx[MAXV];
  float _dEdx_corrected[MAXV];
  float _momentum[MAXV];
  int _vtxHits[MAXV];
  int _tpcHits[MAXV];
  int _ftdHits[MAXV];
  int _vtxType[MAXV];
  int _type[MAXV];
  int _tagType[MAXV];
  int _trueType[MAXV];
  int _type_algo0[MAXV];
  int _type_algo1[MAXV];
  int _type_algo2[MAXV];
  int _type_algo3[MAXV];
  int _type_algo4[MAXV];

  float _likelihood_algo0[MAXV];
  float _likelihood_algo1[MAXV];
  float _likelihood_algo2[MAXV];
  float _likelihood_algo3[MAXV];
  float _likelihood_algo4[MAXV];
  float _TOFFirstHit[MAXV];
  float _TOFClosestHits[MAXV];
  float _TOFClosestHitsError[MAXV];

  float _costheta[MAXV];
  float _theta[MAXV];

  float _chi2[MAXV];

} ;

#endif



