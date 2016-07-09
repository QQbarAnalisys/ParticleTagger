#include "ParticleTagger.hh"

// ----- include for verbosity dependent logging ---------
//#include "marlin/VerbosityLevels.h"
//#include "marlin/StringParameters.h"
//#define SLM streamlog_out(MESSAGE)


//using namespace std;
//using namespace lcio ;
//using namespace marlin ;
using std::vector;
using std::string;
using EVENT::MCParticle;
using TTbarAnalysis::MathOperator;
using EVENT::ReconstructedParticle;
using IMPL::ReconstructedParticleImpl;
using UTIL::LCRelationNavigator;
using IMPL::TrackImpl;
using EVENT::Track;
using EVENT::Vertex;
using IMPL::TrackStateImpl;
using EVENT::Track;
using EVENT::LCCollection;
using IMPL::LCRelationImpl;
ParticleTagger aParticleTagger ;

ParticleTagger::ParticleTagger() : Processor("ParticleTagger") {
  
  // modify processor description
	_description = "" ;

	// input collections
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"PFOCollection",
			"Input track collection to convert",
			_inputPFOCollectionName,
			std::string("PandoraPFOs") );
	registerInputCollection( LCIO::TRACK,
			"TrackCollection",
			"Input Track collection to convert",
			_inputTrackCollectionName,
			std::string("MarlinTrkTracks") );
	registerOutputCollection( LCIO::LCRELATION,
			"TrackRelCollection",
			"Input track rel collection",
			_inputTrackRelCollectionName,
			std::string("MarlinTrkTracksMCTruthLink") );
	registerOutputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"OutPFOCollection",
			"Input track collection to convert",
			_outputPFOCollectionName,
			std::string("PandoraPFOs_modified") );
	registerOutputCollection( LCIO::TRACK,
			"OutTrackCollection",
			"Input Track collection to convert",
			_outputTrackCollectionName,
			std::string("MarlinTrkTracks_modified") );
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"InputExcludePFOCollection",
			"Input PFO collection to convert",
			_inputExcludeCollectionName,
			std::string("SelectedLepton") );

	// output collection
	registerOutputCollection( LCIO::LCRELATION,
			"OutputRelCollection",
			"Ouptut rel collection",
			_outputRelCollectionName,
			std::string("FinalJets_newrel") );
}

ParticleTagger::~ParticleTagger() {}

void ParticleTagger::init() 
{ 
	// usually a good idea to
	string _hfilename = "pid.root";
	_hfile = new TFile( _hfilename.c_str(), "RECREATE", _hfilename.c_str() ) ;
	_hTree = new TTree( "Stats", "My vertex tree!" );
	_hTree->Branch("nParticles", &_nParticles, "nParticles/I");

	_hTree->Branch("tpcHits", _tpcHits, "tpcHits[nParticles]/I");
	_hTree->Branch("costheta", _costheta, "costheta[nParticles]/F");
	_hTree->Branch("momentum", _momentum, "momentum[nParticles]/F");
	_hTree->Branch("type", _type, "type[nParticles]/I");
	_hTree->Branch("tagType", _tagType, "tagType[nParticles]/I");
	_hTree->Branch("trueType", _trueType, "trueType[nParticles]/I");
	_hTree->Branch("dEdx", _dEdx, "dEdx[nParticles]/F");
	a = 1.9e-08;
	//b1 = 1.2e-07;
	//b2 = 1.02e-07;
	b1 = 1.25e-07;
	b2 = 1.07e-07;
	printParameters() ;
	algorithmName = "HadronTagger";

}
MCParticle * ParticleTagger::GetMCParticleTrackRel(Track * reco, LCCollection * trackrel)
{
	LCRelationNavigator navigator(trackrel);
	MCParticle * mcparticle = NULL;
	/*if (std::abs(secondary->getCharge()) < 0.1)
	{
		return mcparticle;
	}
	Track * reco = secondary->getTracks()[0];*/
	const vector< LCObject * > obj = navigator.getRelatedToObjects(reco);
	const vector< float > weights = navigator.getRelatedToWeights(reco);
	if (obj.size() < 1) 
	{
		std::cout << "ERROR: no Track truthlink for particle either\n";
		return mcparticle;
	}
	float maxweight = 0.7;
	for (unsigned int i = 0; i < obj.size(); i++) 
	{
		MCParticle * candidate = dynamic_cast< MCParticle * >(obj[i]);
		if (std::abs(candidate->getCharge()) < 0.09) 
		{
			std::cout << "WARNING: neutral truthlink for particle\n";
			continue;
		}
		if (weights[i] > maxweight) 
		{
			maxweight = weights[i];
			mcparticle = candidate;
		}
	}
	return mcparticle;

}
ReconstructedParticle * ParticleTagger::ReconstructParticle(Track *  track)
{
	float Bz = 3.5;
	float a = 3.0e-4;
	float omega = track->getOmega();
	float tanl = track->getTanLambda();
	float phi = track->getPhi();
	float pt = a * std::abs(Bz / omega);
	//float p = pt * std::sqrt(1 + tanl * tanl);
	
	double momentum[3];
	momentum[0] = pt * std::cos(phi);
	momentum[1] = pt * std::sin(phi);
	momentum[2] = pt * tanl;

	float charge = Bz / omega / std::abs(Bz / omega);
	ReconstructedParticleImpl * result = new ReconstructedParticleImpl();
	result->setCharge(charge);
	result->setMomentum(momentum);
	result->addTrack(track);
	return result;
}
void ParticleTagger::PrintParticle(ReconstructedParticle * particle)
{
	if (!particle) 
	{
		return;
	}
	std::cout << std::fixed << std::setw( 6 ) << std::setprecision( 3 ) << std::setfill( ' ' );
	int id = 0;
	if (particle->getParticleIDUsed()) 
	{
		std::cout << "Type " << particle->getParticleIDUsed()->getType() << '\n';
		id = particle->getParticleIDs()[0]->getPDG(); 
	}
	float dedx = 0.;
	if (particle->getCharge() != 0) 
	{
		dedx = particle->getTracks()[0]->getdEdx() * 1e7;
	}
	std::cout<<"|"<<std::abs(particle->getType())<<"\t\t|"<<(int)particle->getCharge()<<"\t\t|"<< dedx  <<"\t\t|"<<MathOperator::getModule(particle->getMomentum()) <<"\t\t|\n";

}
void ParticleTagger::PrintParticle(MCParticle * particle)
{
	if (!particle) 
	{
		return;
	}
	streamlog_out(MESSAGE)  << std::fixed << std::setw( 6 ) << std::setprecision( 3 ) << std::setfill( ' ' );
	//streamlog_out(MESSAGE) <<"|"<<particle->getPDG() <<"\t|"<<particle->getMass()<<"\t|"<<particle->getCharge()  <<"\t|"<<particle->getEnergy()<<"\t|"<<particle->getVertex()[0]<<"\t|"<<particle->getVertex()[1]<<"\t\t|"<<particle->getVertex()[2] <<"\t|\n";
	streamlog_out(MESSAGE) <<"|"<<particle->getPDG() <<"\t|"<<particle->getMass()<<"\t|"<<(int)particle->getCharge() <<"\t|"<< MathOperator::getModule(particle->getVertex()) <<"\t|"<<particle->getEnergy() <<"\t|\n";

}
bool ParticleTagger::checkParticle(ReconstructedParticle * particle, int pdg)
{
	float p  = MathOperator::getModule(particle->getMomentum());
	vector<float> direction = MathOperator::getDirection(particle->getMomentum());
	float angle = std::abs(MathOperator::getAngles(direction)[1]);
	float pi = 3.1415;
	if (angle > pi / 2) 
	{
		angle = pi - angle;
	}
	std::cout << "Angle: " << std::pow(angle,0.15) << "\n";
	float dedx =  particle->getTracks()[0]->getdEdx()* std::abs(std::pow(angle,0.15));
	int tpchits = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
	float pcut = 2.;
	if (pdg == 321) 
	{
		return //(std::abs(particle->getType()) > 13 && // NOT LEPTON
		tpchits > 60 &&
		p > pcut &&
		//p < 30.  &&
		dedx > 0 && 
		dedx < a*std::log(p) + b1 &&
		dedx > a*std::log(p) + b2;
	}
	if (pdg == 2212) 
	{
		return //(std::abs(particle->getType()) > 13 && // NOT LEPTON
		tpchits > 60 &&
		p > pcut &&
		//p < 30.  &&
		dedx > 0 && 
		dedx < a*std::log(p) + b2;
	}
	return false;
}
void  ParticleTagger::TagParticle(ReconstructedParticle * particle, PIDHandler & pidh)
{
	float p  = MathOperator::getModule(particle->getMomentum());

	vector<float> direction = MathOperator::getDirection(particle->getMomentum());
	float angle = (MathOperator::getAngles(direction)[1]);
	float pi = 3.1415;
	if (angle > pi / 2) 
	{
		angle = pi- angle;
	}
	float dedx =  particle->getTracks()[0]->getdEdx() * std::pow(angle,0.15);
	_momentum[_nParticles] = p;
	_type[_nParticles] = particle->getType();
	_tpcHits[_nParticles] = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
	_dEdx[_nParticles] = dedx;
	_costheta[_nParticles] = std::cos(angle);
	bool tagged = false;
	vector<float> parameters;
	if (checkParticle(particle,321))
	{
		_tagType[_nParticles]  = 321;
		tagged = true;
	}
	if (checkParticle(particle,2212))
	{
		_tagType[_nParticles]  = 2212;
		tagged = true;
	}
	if (!tagged) 
	{
		_tagType[_nParticles]  = 211;
	}
	pidh.setParticleID(particle, _tagType[_nParticles], _tagType[_nParticles], 1.0, _algorithmID, parameters);
}



void ParticleTagger::processRunHeader( LCRunHeader* run) 
{ 
} 


void ParticleTagger::processEvent( LCEvent * evt ) 
{
	std::cout << "*********************Event*" << _nEvt++ << "************************\n";
	std::cout<<"|"<<"Type"<<"\t\t|"<<"Charge"<<"\t\t|"<< "dEdx"  <<"\t\t|"<<"P" <<"\t\t|\n";
	LCCollection * pfoCol = evt->getCollection( _inputPFOCollectionName );
	//LCCollection * trackCol = evt->getCollection( _inputTrackCollectionName );
	LCCollection * trackRelCol = evt->getCollection( _inputTrackRelCollectionName );
	PIDHandler pidh(pfoCol); 
	_algorithmID = pidh.addAlgorithm(algorithmName, _parameterNames);
	int total = pfoCol->getNumberOfElements();
	_nParticles = 0;
	for (int i = 0; i < total; i++) 
	{
		//Track * track = static_cast< Track * > (trackCol->getElementAt(i));
		//ReconstructedParticle * recoparticle =  ReconstructParticle(track);
		ReconstructedParticle * recoparticle =  static_cast< ReconstructedParticle * > (pfoCol->getElementAt(i));
		if (abs(recoparticle->getCharge()) < 0.5 || MathOperator::getModule(recoparticle->getMomentum()) < 0.05) 
		{
			continue;
		}
		Track * track = recoparticle->getTracks()[0];
		TagParticle(recoparticle, pidh);
		//PrintParticle(recoparticle);
		MCParticle * genparticle = GetMCParticleTrackRel(track, trackRelCol);
		_trueType[_nParticles]  =(genparticle)? std::abs(genparticle->getPDG()):0;
		_nParticles++;
	}
	_hTree->Fill();
	ClearVariables();
}

void ParticleTagger::check( LCEvent * evt ) { 
  // nothing to check here - could be used to fill checkplots in reconstruction processor
}
void ParticleTagger::ClearVariables()
{
	for (int i = 0; i < MAXV; i++) 
	{
		
	}

}
int ParticleTagger::getVertexType(EVENT::ReconstructedParticle * particle)
{
	Vertex * vertex = particle->getStartVertex();
	int result = 0;
	if (vertex) 
	{
		if (vertex->isPrimary()) 
		{
			result = 1;
		}
		else 
		{
			result = 2;
		}
	}
	return result;
}
float ParticleTagger::GetOffsetErrorSimple(EVENT::ReconstructedParticle * particle)
{
	if (!particle || particle->getTracks().size() < 0) 
	{
		return -1;
	}
	Track * track = particle->getTracks()[0];
	const vector<float> covMatrix = track->getCovMatrix();
	float d0 = particle->getTracks()[0]->getD0();
	float z0 = particle->getTracks()[0]->getZ0();
	float offset = std::sqrt(d0*d0 + z0*z0);
	float error = std::sqrt( d0*d0/offset/offset * covMatrix[0] + z0*z0/offset/offset * covMatrix[9] + 2*d0*z0/offset/offset * covMatrix[6] );
	return error;
	//return  covMatrix[0] +  covMatrix[9];

}	


void ParticleTagger::end()
{
	_hfile->cd();
	_hfile->Write();
	_hfile->Close();
}
