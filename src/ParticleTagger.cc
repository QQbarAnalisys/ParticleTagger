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
	registerProcessorParameter( "ROOTFileName",
			"Output ROOT File Name",
			_hfilename,
			string("pid.root") );
	a=0.019;
	registerProcessorParameter( "slope_kaon_selection",
			"Slope of the line for kaon selection: dEdx=b+slope log(p)",
			a,
			a);
	b1=0.1115;
	registerProcessorParameter( "upper_limit_kaon_selection",
			"Upper limit of the area in which kaons are selected",
			b1,
			b1);
	b2=0.096;
	registerProcessorParameter( "lower_limit_kaon_selection",
			"Lower limit of the area in which kaons are selected",
			b2,
			b2);
	bfield=3.5;
	registerProcessorParameter( "Bfield",
			"B field of ILD, in T",
			bfield,
			bfield);
	registerProcessorParameter( "NewPID",
			"New kaon PID tagger",
			algorithmName,
			string("KaonTagger") );
	registerInputCollection( LCIO::RECONSTRUCTEDPARTICLE,
			"PFOCollection",
			"Input track collection to convert",
			_inputPFOCollectionName,
			std::string("PandoraPFOs") );
	registerInputCollection( LCIO::LCRELATION,
			"TrackRelCollection",
			"Input track rel collection",
			_inputTrackRelCollectionName,
			std::string("MarlinTrkTracksMCTruthLink") );

}

ParticleTagger::~ParticleTagger() {}

void ParticleTagger::init() 
{ 

	_hfile = new TFile( _hfilename.c_str(), "RECREATE", _hfilename.c_str() ) ;
	_hTree = new TTree( "Stats", "My PID Tree" );
	_hTree->Branch("nParticles", &_nParticles, "nParticles/I");

	_hTree->Branch("tpcHits", _tpcHits, "tpcHits[nParticles]/I");
	_hTree->Branch("costheta", _costheta, "costheta[nParticles]/F");
	_hTree->Branch("theta", _theta, "theta[nParticles]/F");
	_hTree->Branch("momentum", _momentum, "momentum[nParticles]/F");
	_hTree->Branch("type", _type, "type[nParticles]/I");
	_hTree->Branch("tagType", _tagType, "tagType[nParticles]/I");
	_hTree->Branch("type_algo0", _type_algo0, "type_algo0[nParticles]/I");
	_hTree->Branch("type_algo1", _type_algo1, "type_algo1[nParticles]/I");
	_hTree->Branch("type_algo2", _type_algo2, "type_algo2[nParticles]/I");
	_hTree->Branch("type_algo3", _type_algo3, "type_algo3[nParticles]/I");
	_hTree->Branch("type_algo4", _type_algo4, "type_algo4[nParticles]/I");

	_hTree->Branch("likelihood_algo0", _likelihood_algo0, "likelihood_algo0[nParticles]/F");
	_hTree->Branch("likelihood_algo1", _likelihood_algo1, "likelihood_algo1[nParticles]/F");
	_hTree->Branch("likelihood_algo2", _likelihood_algo2, "likelihood_algo2[nParticles]/F");
	_hTree->Branch("likelihood_algo3", _likelihood_algo3, "likelihood_algo3[nParticles]/F");
	_hTree->Branch("likelihood_algo4", _likelihood_algo4, "likelihood_algo4[nParticles]/F");

	_hTree->Branch("vtxType", _vtxType, "vtxType[nParticles]/I");
	_hTree->Branch("trueType", _trueType, "trueType[nParticles]/I");
	_hTree->Branch("dEdx", _dEdx, "dEdx[nParticles]/F");

	//sviatoslav params
	//	a = 1.9e-08;
	////b1 = 1.2e-07;
	////b2 = 1.02e-07;
	//	b1 = 1.25e-07;
	//	b2 = 1.07e-07;

	printParameters() ;

}
MCParticle * ParticleTagger::GetMCParticleTrackRel(Track * reco, LCCollection * trackrel)
{
	LCRelationNavigator navigator(trackrel);
	MCParticle * mcparticle = NULL;

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
	float Bz = bfield;
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

	streamlog_out(DEBUG)  << "*********************Event*" << _nEvt++ << "************************\n";                                       
	streamlog_out(DEBUG) <<"|"<<"Type"<<"\t\t|"<<"Charge"<<"\t\t|"<< "dEdx"  <<"\t\t|"<<"P" <<"\t\t|\n";
	if (!particle) 
	{
		return;
	}
	streamlog_out(DEBUG) << std::fixed << std::setw( 6 ) << std::setprecision( 3 ) << std::setfill( ' ' );
	int id = 0;
	if (particle->getParticleIDUsed()) 
	{
		std::cout << "Type " << particle->getParticleIDUsed()->getType() << '\n';
		id = particle->getParticleIDs()[0]->getPDG(); 
	}
	float dedx = 0.;
	if (particle->getCharge() != 0) 
	{
		dedx = particle->getTracks()[0]->getdEdx() * 1e6;
	}
	streamlog_out(DEBUG) <<"|"<<std::abs(particle->getType())<<"\t\t|"<<(int)particle->getCharge()<<"\t\t|"<< dedx  <<"\t\t|"<<MathOperator::getModule(particle->getMomentum()) <<"\t\t|\n";

}
void ParticleTagger::PrintParticle(MCParticle * particle)
{
	if (!particle) 
	{
		return;
	}
	streamlog_out(DEBUG)  << std::fixed << std::setw( 6 ) << std::setprecision( 3 ) << std::setfill( ' ' );
	streamlog_out(DEBUG) <<"|"<<particle->getPDG() <<"\t|"<<particle->getMass()<<"\t|"<<(int)particle->getCharge() <<"\t|"<< MathOperator::getModule(particle->getVertex()) <<"\t|"<<particle->getEnergy() <<"\t|\n";

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
	//std::cout << "Angle: " << std::pow(angle,0.15) << "\n";
	float dedx =  particle->getTracks()[0]->getdEdx()*1e6;//*std::abs(std::pow(angle,0.15));
	int tpchits = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
	float pcut = 2.;
	if (pdg == 211) 
	{
		return //(std::abs(particle->getType()) > 13 && // NOT LEPTON
			//tpchits > 60 &&
			//p > pcut &&
			//p < 30.  &&
			dedx > 0 && 
			dedx > a*std::log(p) + b1;
	}
	if (pdg == 321) 
	{
		return //(std::abs(particle->getType()) > 13 && // NOT LEPTON
			//tpchits > 60 &&
			//p > pcut &&
			//p < 30.  &&
			dedx > 0 && 
			dedx < a*std::log(p) + b1 &&
			dedx > a*std::log(p) + b2;
	}
	if (pdg == 2212) 
	{
		return //(std::abs(particle->getType()) > 13 && // NOT LEPTON
			//tpchits > 60 &&
			//p > pcut &&
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
	//	float dedx_corrected =  particle->getTracks()[0]->getdEdx() * std::pow(angle,0.15);
	float dedx =  particle->getTracks()[0]->getdEdx();
	_momentum[_nParticles] = p;
	_type[_nParticles] = particle->getType();
	_tpcHits[_nParticles] = particle->getTracks()[0]->getSubdetectorHitNumbers()[6];
	_dEdx[_nParticles] = dedx;
	_costheta[_nParticles] = std::cos(angle);
	_theta[_nParticles] = angle;


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
	if (checkParticle(particle,211))
	{
		_tagType[_nParticles]  = 211;
		tagged = true;
	}
	if (!tagged) 
	{
		_tagType[_nParticles]  = 0;
	}
	pidh.setParticleID(particle, _tagType[_nParticles], _tagType[_nParticles], 1.0, _algorithmID, parameters);

	_type_algo4[_nParticles]=_tagType[_nParticles];
	_likelihood_algo4[_nParticles]=1.0;


}



void ParticleTagger::processRunHeader( LCRunHeader* run) 
{ 
} 


void ParticleTagger::processEvent( LCEvent * evt ) 
{

	ClearVariables();                                                                                                                                                            
	LCCollection * pfoCol = evt->getCollection( _inputPFOCollectionName );
	LCCollection * trackRelCol = evt->getCollection( _inputTrackRelCollectionName );
	PIDHandler pidh(pfoCol); 
	_algorithmID = pidh.addAlgorithm(algorithmName, _parameterNames);
	TString myAlgorithmName[4];
	myAlgorithmName[0]="LikelihoodPID";
	myAlgorithmName[1]="LowMomMuID";
	myAlgorithmName[2]="BasicVariablePID";
	myAlgorithmName[3]="dEdxPID";

	int total = pfoCol->getNumberOfElements();
	_nParticles = 0;
	for (int i = 0; i < total; i++) 
	{
		ReconstructedParticle * recoparticle =  static_cast< ReconstructedParticle * > (pfoCol->getElementAt(i));
		if (abs(recoparticle->getCharge()) < 0.5 || MathOperator::getModule(recoparticle->getMomentum()) < 0.05) 
		{
			continue;
		}
		Track * track = recoparticle->getTracks()[0];
		//tag particle using provided algorithms
		for(int j=0; j<4;j++) {                                                                                                                     
			int pid = pidh.getAlgorithmID(myAlgorithmName[j].Data());
			int pdg = pidh.getParticleID(recoparticle, pid).getPDG();
			double likelihood=pidh.getParticleID(recoparticle, pid).getLikelihood();

			if(j==0) {
				_type_algo0[_nParticles]=pdg;
				_likelihood_algo0[_nParticles]=likelihood;
			}
			if(j==1) {
				_type_algo1[_nParticles]=pdg;
				_likelihood_algo1[_nParticles]=likelihood;
			}
			if(j==2) {
				_type_algo2[_nParticles]=pdg;
				_likelihood_algo2[_nParticles]=likelihood;
			}
			if(j==3) {
				_type_algo3[_nParticles]=pdg;
				_likelihood_algo3[_nParticles]=likelihood;
			}		  
		}
		TagParticle(recoparticle, pidh);
		PrintParticle(recoparticle);
		MCParticle * genparticle = GetMCParticleTrackRel(track, trackRelCol);
		_trueType[_nParticles]  =(genparticle)? std::abs(genparticle->getPDG()):0;
		_vtxType[_nParticles] = getVertexType(recoparticle);
		_nParticles++;
	}
	_hTree->Fill();
	//  ClearVariables();
}

void ParticleTagger::check( LCEvent * evt ) { 
	// nothing to check here - could be used to fill checkplots in reconstruction processor
}
void ParticleTagger::ClearVariables()
{
	for (int i = 0; i < MAXV; i++) 
	{
		_nParticles=0;
		_dEdx[i]=0;  
		_dEdx_corrected[i]=0;   
		_momentum[i]=0;   
		_vtxHits[i]=0;   
		_tpcHits[i]=0;  
		_ftdHits[i]=0; 
		_vtxType[i]=0; 
		_type[i]=0; 
		_tagType[i]=0;  
		_trueType[i]=0;
		_type_algo0[i]=0; 
		_type_algo1[i]=0; 
		_type_algo2[i]=0;  
		_type_algo3[i]=0; 
		_type_algo4[i]=0;
		_likelihood_algo0[i]=0;
		_likelihood_algo1[i]=0; 
		_likelihood_algo2[i]=0;
		_likelihood_algo3[i]=0;
		_likelihood_algo4[i]=0;
		_costheta[i]=0;
		_theta[i]=0;
		_chi2[i]=0;

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
