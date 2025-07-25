#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "Settings.h"
#include "Detector.h"

bool AraUtilExists = false;

#ifdef ARA_UTIL_EXISTS
#include "AraRootVersion.h"
#endif

ClassImp(Settings);

using namespace std;

Settings::Settings() {
    Initialize();
//    ReadFile();

}

Settings::~Settings() {
    //default destructor
}


void Settings::Initialize() {


// below : values from icemc Settings class
  NDISCONES_PASS=3;

  DEBUG=false;                   // debugging option
 outputdir="outputs"; // directory where outputs go
 FREQ_LOW_SEAVEYS=200.E6;
 FREQ_HIGH_SEAVEYS=1200.E6;
 BW_SEAVEYS=FREQ_HIGH_SEAVEYS-FREQ_LOW_SEAVEYS;
 SIGMAPARAM=1;  // Connolly et al. 2011 default cross section parametrization
 SIGMA_FACTOR=1.;   // default sigma factor : 1
 YPARAM=1;  // 1: Connolly et al. 2011 default y parametrization, 2: Set ELAST_Y yourself
 ELAST_Y = 0.0;
 UNBIASED_SELECTION=1.; // (0) pick neutrino interaction in the ice and neutrino from any direction or (1) choose neutrino interaction point in the horizon on the balloon in the ice and neutrino direction on the cerenkov cone

 SIGMA_SELECT=0; // when in SIGMAPARAM=1 case, 0 : (default) use mean value, 1 : use upper bound, 2 : use lower bound

 HPOL_GAIN_FILE=string(getenv("ARA_SIM_DIR"))+"/data/antennas/realizedGain/ARA_dipoletest1_output.txt"; // Default to original Ara Data
 VTOP_GAIN_FILE=string(getenv("ARA_SIM_DIR"))+"/data/antennas/realizedGain/ARA_bicone6in_output.txt"; // Default to original Ara Data
 VPOL_GAIN_FILE=string(getenv("ARA_SIM_DIR"))+"/data/antennas/realizedGain/ARA_bicone6in_output.txt"; // Default to original Ara Data

// end of values from icemc

 ARASIM_VERSION_MAJOR = ARASIM_MAJOR;
 ARASIM_VERSION_MINOR = ARASIM_MINOR;
 ARASIM_VERSION_SUBMINOR = ARASIM_SUBMINOR;
 ARASIM_VERSION = (double)ARASIM_VERSION_MAJOR + (double)ARASIM_VERSION_MINOR * 0.001 + (double)ARASIM_VERSION_SUBMINOR * 0.000001;
 
 // assign the default git hash
 std::strncpy(COMMIT_HASH, "UNDEFINED_COMMIT_HASH_OR_NOT_SET", sizeof(COMMIT_HASH));
 COMMIT_HASH[sizeof(COMMIT_HASH) - 1] = '\0';  // Ensure null-termination

 ARAROOT_VERSION = 0.;

 ARAUTIL_EXISTS = false;
#ifdef ARA_UTIL_EXISTS
 ARAUTIL_EXISTS = true;
 ARAROOT_VERSION = (double)ARA_ROOT_MAJOR + (double)ARA_ROOT_MINOR * 0.01;
#endif
 

  NNU=100;

  // NEED TO FIGURE OUT A GOOD WAY TO READ THIS IN AND STORE THEM.
  // INPUT FILE AGAIN?  SOMETHING ELSE?
  //These were moved here from IceModel under the new compilation scheme
  ICE_MODEL=0; //Select ice model to be used.  0 = Crust 2.0 , 1 = BEDMAP.
  NOFZ=1; // 1=depth dependent index of refraction,0=off
  BIREFRINGENCE=0; // To activate birefringence. Default 0 means no birefringence
  BIAXIAL=1; //Type of birefringence: 1 = biaxial, 0 = uniaxial 
  CONSTANTCRUST=0; // set crust density and thickness to constant values.
  CONSTANTICETHICKNESS=0; // set ice thickness to constant value
  FIXEDELEVATION=0; // fix the elevation to the thickness of ice.
  MOOREBAY=0; //1=use Moore's Bay measured ice field attenuation length for the west land, otherwise use South Pole data
  USE_ARA_ICEATTENU=1; // use ARA measured ice attenuation value
  
  EXPONENT=19.; // 10^19 eV neutrinos only

  EXPONENT_MIN = 16.; // minimum log10(eV) of Neutrino energy spectrum, if user use continuous energy spectrum for simulating Neutrino 

  EXPONENT_MAX = 22.; // maximum log10(eV) of Neutrino energy spectrum, if user use continuous energy spectrum for simulating Neutrino

  DETECTOR=1;   //ARA layout with small number of stations

  DETECTOR_STATION=-1; // initiate this to negative -1, so it does nothing by default
  DETECTOR_STATION_ARAROOT=-1; // initiate this to negative -1, so it does nothing by default
  DETECTOR_STATION_LIVETIME_CONFIG=-1; // intiative this to negative -1, so it does nothing by default
  DETECTOR_YEAR=2011;

  INTERACTION_MODE=1;   //PickNear mode (0: Aeff mode using sphere surface around station, 1: Veff mode using cylinder volume around station)

  POSNU_RADIUS=3000;    //radius for PickNear method

  WHICHPARAMETERIZATION=0;  //

  SIMULATION_MODE=1;    // default time domain simulation

  USE_PARAM_RE_TTERM_TABLE=1; // default: use the interpolation table to get Param_RE_TTerm

  EVENT_TYPE=0;         // default neutrino only events

  WAVE_TYPE=0;          // default wave type : plane wave (inside the ice)

  LPM=1;                //default : enable LPM effect

  SECONDARIES=1;        //default : enable secondary interactions

  TAUDECAY=1;           //default : let taudecay as secondary interactions

  TIMESTEP=(0.625)*1.E-9;  // default, in sec (old default: 0.5E-9, new default 0.625E-9

  PHASE=90.;            // default : 90 deg phase (it means all imaginary values)

  NFOUR=2048;           // default : 2048
    
  NOISE=0;              // degault : 0, flat thermal noise, 1 : for TestBed (DETECTOR=3), use Rayleigh distribution fitted for borehole channels

  ATMOSPHERE=1;         // default : 1, include atmosphere

  TRIG_SCAN_MODE=0;	// default 0 (old mode) 1: new mode (faster) 2: scan all Pthresh values 3: scan also all N out of 8 
  
  POWERTHRESHOLD=-6.06; // old default : -6.15, new default: -6.06

  MAXT_DIODE=70.E-9;    // default : 70 ns

  IDELAYBEFOREPEAK_DIODE=(int)(13.E-9 / TIMESTEP);    // default : 13.e-9/TIMESTEP = 33

  IWINDOW_DIODE=(int)(4.E-9 / TIMESTEP);           // default : 4.e-9 / TIMESTEP = 10

  DATA_BIN_SIZE=16384;   // default : 16384

  NOISE_TEMP=325.;      // default : 325 K

  TRIG_ANALYSIS_MODE=0;    // default : 0, signal + noise

  TRIG_TIMEOUT=1.E-6;       // default : 1us

  TRIG_WINDOW=1.7E-7;       // old default : 110 ns, new default: 170 ns

  NOISE_EVENTS=16;        // default : 16 events

  DATA_SAVE_MODE=0;         // default : 0 (full mode)

  N_TRIG=3;                 // default : 3 (3 out of all channels in a station)

  RANDOM_MODE=1;            // default : 1 (seed is unique in time/space)

  SEED=1; // default: 1, only applies if RANDOM_MODE=0, provides base seed value and run number taken from arguments is added to this value in order to submit multiple repeatable runs instead of only one single long repeatable run
    
  BORE_HOLE_ANTENNA_LAYOUT=0;   // default : 0 (VHVH)

  DATA_LIKE_OUTPUT=1; //default : 0 (doesn't write out data-like events)
    
  RAYSOL_RANGE=5000; // default : 5000 m

  PICK_POSNU_DEPTH=0;     //default : 0 pick posnu depth from 0 to ice depth

  MAX_POSNU_DEPTH=0.;     // default : 0m depth max

  NNU_THIS_THETA=0;         // default 0: nnu angle pure random, 1: set a specific theta

  NNU_THETA=0.785;          // default : nnu theta : 45 deg

  NNU_D_THETA=0.0873;       // default : nnu d_theta : 5 deg

  NNU_THIS_PHI=0;//default 0: random phi, 1: a specific phi

  NNU_PHI=0.785;// default : nnu phi : 45 deg

  NNU_D_PHI=0.0873;// default : nnu_d_phi : 5 deg

  Z_THIS_TOLERANCE=1; // 0 : use default 'requiredAccuracy' metod for ray tracing, 1 (default) : change 'requiredAccuracy' parameter by Z_TOLERANCE

  Z_TOLERANCE=0.2; // 0.2 : (default)   
 
  CALPULSER_ON=0; // default : calpulsers off
  
  TESTBED_ON=0; // default : 0 stations[0] is ARA1 not Testbed
  
  READGEOM=0; // default : 0 : use idealized geometry and do not read in from sqlite database
  
  V_MIMIC_MODE = 0; // default : 0 - write out all chs where global triggered bin is center of the window
                      // 1 - same as above 0 mode but apply TestBed ch delay - average BH ch delay
                      // 2 - same as above 0 mode but apply TestBed ch delay - average BH ch delay + additional delay to match with actual TestBed data waveforms
  
  USE_INSTALLED_TRIGGER_SETTINGS = 0; // default : 0 - use idealized settings for the trigger
  
  NUM_INSTALLED_STATIONS = 6;

  CALPUL_OFFCONE_ANGLE = 35.;

  CALPUL_AMP = 100.;

  TRIG_ONLY_BH_ON = 0;    // default trigger will occur with all chs (1 will do trigger analysis with BH chs only)

  TRIG_THRES_MODE = 0;    // default trigger threshold (0) will use 1 as offset (so no offset), (1) will use data/threshold_offset.csv as threshold off set factor

  NOISE_CHANNEL_MODE = 0;    //default noise temp setting (just same temp for all chs), 1 : all chs have different systemp, 2 : only first 8 chs have different systemp

  USE_TESTBED_RFCM_ON = 0;    // use RFCM measurement for testbed or not

  RFCM_OFFSET = 80.;  // if above USE_TESTBED_RFCM_ON = 1, we need RFCM attenuator factor cancel

  CONST_MEANDIODE = -6.5e-15; // just from one run

  CONST_RMSDIODE = 1.346e-13; // also from one run

  USE_MANUAL_GAINOFFSET = 0; //if use gain offset file to read values or just use constant gain offset from setup file (default 0 : use file)
          
  MANUAL_GAINOFFSET_VALUE = 1.; // gain offset value

  NOISE_WAVEFORM_GENERATE_MODE = 0; // mode 0 (default) will generate noise waveforms newly for each events. other values will use first generated noise waveforms for later events (huge mem usage)

  USE_CH_GAINOFFSET = 0; // if use gain offset for different channels. (default 0 : not using gain offset). mode 1 is only availbale for installed TestBed so far.

  // removed GETCHORD_MODE. This parameter is merged into INTERACTION_MODE
  //GETCHORD_MODE = 0; // which Getchord function to use. default 0 : old Getchord function (not correct tau weight, weight don't have ice inside interaction probability in it). 1 : new Getchord from icemc. This has new tau weight calculation and ice interaction probability applied to weight factor.

  taumodes = 0; // no tau created in the rock

  BH_ANT_SEP_DIST_ON = 1; // 0 : use constant borehole antenna distance. default 1 : use separate antenna distance. use z_btw01, z_btw12, ... in ARA_N_info.txt or ARA37_info.txt

  TRIG_MODE = 1; // default 1 : if any antennas got passed N_TRIG or more, global trig. 1 : either Vpol or Hpol antennas got passed N_TRIG_V or N_TRIG_H respectively, global trig.

  N_TRIG_V=3;                 // default : 3 (3 out of Vpolchannels in a station)

  N_TRIG_H=3;                 // default : 3 (3 out of Hpol channels in a station)

  FILL_TREE_MODE = 0; // default 0 : fill tree for all events, 1 : fill tree only usable posnu events, 2 : fill tree only trigger passed events

  ONLY_PASSED_EVENTS = 0;
  NNU_PASSED = 0;

  //Defining source for INTERACTION_MODE == 5.
  SOURCE_LATITUDE = -89.97953; //Latitude of SpiceCore (from 2023 survey data)

  SOURCE_LONGITUDE = -100.78595; //Longitude of SpiceCore (from 2023 survey data)

  SOURCE_DEPTH = -1000.0; //Default depth of 1000 meters below ice surface.    


  SHOWER_MODE = 2; // EM (0) or HAD (1) shower in t-domain signal. or either one which is bigger (3) or both EM and HAD (2)  default : 2, both EM and HAD showers

  SHOWER_STEP = 0.001; // step size in generating shower profile. default 0.001 m

  SHOWER_PARAM_MODEL = 0; // choose shower profile parameters (by Jaime fit = 0, or Carl's fit = 1). default = 0

  OFFCONE_LIMIT = 10.; // offcone angle (deg) limit to calculate time domain signal. Increasing this value will result in drametically increase computation time

  ALL_ANT_V_ON = 0; // use Vpol antenna gain for both Vpol and Hpol = 1, use Hpol gain for Hpol model = 0

  PHASE_SKIP_MODE = 0; // skip applying phase in t-domain mode (SIMULATION_MODE = 1). default 0 : don't skip (apply all phase), 1 : only upto Askaryan radiation, 2 : only upto antenna



  DEBUG_MODE_ON = 0; // 0 : off (do as usual), 1 : on (skip most of intensive computational process which don't have random generations)

  DEBUG_SKIP_EVT = 0; // when DEBUG_MODE_ON = 1, skip upto this number and then do as DEBUG_MODE_ON = 0


  V_SATURATION = 1.; // saturated voltage +-V_SATURATION

  ADDITIONAL_DEPTH_ON = 0; // whether add more depth to each antenas

  ADDITIONAL_DEPTH = 100.; // default additional depth value



  TRIG_ONLY_LOW_CH_ON = 0;    // default trigger will occur with all chs (1 will do trigger analysis with lower 8 chs; bottom 4 Vpol & bottom 4 Hpols)


  ACCUM_TRIG_SEARCH_BINS_STATION0 = 0.; // not actually setting value but gives us how much trigger searched bins there were in the run for station0

  NU_NUBAR_SELECT_MODE = 3; // default : 3 = random nu_nubar based on arXiv:1108.3163, section 3, 0 = just nu, 1 = just nubar 


  SELECT_FLAVOR = 0; // default : 0 = randomly 1:1:1 ratio, 1 : el. 2 : mu, 3 : tau
  SELECT_CURRENT = 2; // default: 2:random, 0:nc, 1:cc

  OUTPUT_TDR_GRAPH = 0;// saves a few example graphs of the tunnel diode response for a triggered event


  AVZ_NORM_FACTOR_MODE = 1; // default : 1 : don't apply sqrt(2) (actually applied but cancel that) as realft assume Hn as double-sided spectrum (invFFT normalization factor 2/N) and also remove dF binning factor in MakeArraysforFFT function, 0 : use normalization factors like in old version

  number_of_stations = 1;

  RAY_TRACE_ICE_MODEL_PARAMS=0; // Default: South Pole values fitted from RICE data

  WAVEFORM_LENGTH = 64/2*20; // Default: 64 digitization samples per block / 2 samples per waveform value * 20 blocks (value used for 2013-2016)
  
  WAVEFORM_CENTER = 0; // Default: 0, no offset in waveform centering

  DEADTIME = 1.E-3; // Default: 1 millisecond (for ARA stations; see https://aradocs.wipac.wisc.edu/cgi-bin/DocDB/ShowDocument?docid=2116)
                    // Deadtime for PA should be 0.1 ms (based on 0.12% livetime loss in PA search arXiv:2202.07080)
  
  POSNU_R = 1000.;
  POSNU_THETA=-3.1415926535/4.;
  POSNU_PHI=0.;

  ARBITRARY_EVENT_ATTENUATION = 1.0;
  PICK_ABOVE_HEIGHT = 3000;

  EVENT_GENERATION_MODE = 0;//default: 0: not event mode, 1: event mode
  //    EVENT_NUM = 10;//read in event number in EVENT_GENERATION_MODE=1, no more than 100 events
  ANTENNA_MODE=0; //default: 0 - old antenna model information
  IMPEDANCE_RX_VPOL=0;
  IMPEDANCE_RX_VPOL_TOP=0;
  IMPEDANCE_RX_HPOL=0;
  IMPEDANCE_TX=0;
  APPLY_NOISE_FIGURE=0; // default: 0 - don't use new noise figure information

  CUSTOM_ELECTRONICS=0; //default: 0 -- don't use custom electronics, load regular "ARA_Electronics_TotalGain_TwoFilter.csv"

  ELECTRONICS_ANTENNA_CONSISTENCY = 1; // default: 1 -- ensure antenna gain used to calculate electronics gain is consistent
                                       //               with that used in this simulation  
                                       // This setting is only used if DETECTOR > 3 && NOISE == 1 && CUSTOM_ELECTRONICS == 0
 
  CLOCK_ANGLE=0; //Default: 0 -- Angle of polarization "on the clock".  Angle of zero is pure thetaPol, whereas 90º is pure phiPol.




    /*
//arrays for saving read in event features in EVENT_GENERATION_MODE=1
    EVID[100] = {0};
    NUFLAVORINT[100] = {0};
    NUBAR[100] = {0};
    PNU[100] = {0};
    CURRENTINT[100] = {0};
    IND_POSNU_R[100] = {0};
    IND_POSNU_THETA[100] = {0};
    IND_POSNU_PHI[100] = {0};
    IND_NNU_THETA[100] = {0};
    IND_NNU_PHI[100] = {0};
    */
}

void Settings::ReadFile(string setupfile) {

  ifstream setFile (setupfile.c_str());
  
  string line, label;

  if ( setFile.is_open() ) {
      while (setFile.good() ) {
          getline (setFile,line);

          if (line[0] != "/"[0]) {
              label = line.substr(0, line.find_first_of("="));
              
              if (label == "NNU") {
                  NNU = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "ICE_MODEL") {
                  ICE_MODEL = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NOFZ") {
                  NOFZ = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
	      else if (label == "BIREFRINGENCE"){
		  BIREFRINGENCE = atof( line.substr(line.find_first_of("=") + 1).c_str() );	
	      }
	      else if (label == "BIAXIAL"){
		  BIAXIAL = atof( line.substr(line.find_first_of("=") + 1).c_str() );	
	      }
              else if (label == "CONSTANTCRUST") {
                  CONSTANTCRUST = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "CONSTANTICETHICKNESS") {
                  CONSTANTICETHICKNESS = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "FIXEDELEVATION") {
                  FIXEDELEVATION = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "MOOREBAY") {
                  MOOREBAY = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "EXPONENT") {
                  EXPONENT = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "EXPONENT_MIN") {
                  EXPONENT_MIN = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "EXPONENT_MAX") {
                  EXPONENT_MAX = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "DETECTOR") {
                  DETECTOR = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "DETECTOR_STATION") {
                  DETECTOR_STATION = atof( line.substr(line.find_first_of("=") + 1).c_str() );
		  DETECTOR_STATION_ARAROOT = DETECTOR_STATION;
		  if (DETECTOR_STATION == 100) {
			DETECTOR_STATION = 1;
			DETECTOR_STATION_ARAROOT = 100;
			}
              }
              else if (label == "DETECTOR_STATION_LIVETIME_CONFIG") {
                  DETECTOR_STATION_LIVETIME_CONFIG = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "DETECTOR_YEAR") {
                  DETECTOR_YEAR = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "INTERACTION_MODE") {
                  INTERACTION_MODE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "POSNU_RADIUS") {
                  POSNU_RADIUS = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "WHICHPARAMETERIZATION") {
                  WHICHPARAMETERIZATION = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SIMULATION_MODE") {
                  SIMULATION_MODE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "USE_PARAM_RE_TTERM_TABLE") {
                  USE_PARAM_RE_TTERM_TABLE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "EVENT_TYPE") {
                  EVENT_TYPE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "WAVE_TYPE") {
                  WAVE_TYPE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "LPM") {
                  LPM = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SECONDARIES") {
                  SECONDARIES = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TAUDECAY") {
                  TAUDECAY = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TIMESTEP") {
                  TIMESTEP = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "PHASE") {
                  PHASE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NFOUR") {
                  NFOUR = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NOISE") {
                  NOISE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "ATMOSPHERE") {
                  ATMOSPHERE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if(label == "TRIG_SCAN_MODE"){
                  TRIG_SCAN_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
              else if (label == "POWERTHRESHOLD") {
                  POWERTHRESHOLD = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "DATA_BIN_SIZE") {
                  DATA_BIN_SIZE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NOISE_TEMP") {
                  NOISE_TEMP = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TRIG_ANALYSIS_MODE") {
                  TRIG_ANALYSIS_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TRIG_TIMEOUT") {
                  TRIG_TIMEOUT = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TRIG_WINDOW") {
                  TRIG_WINDOW = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NOISE_EVENTS") {
                  NOISE_EVENTS = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "DATA_SAVE_MODE") {
                  DATA_SAVE_MODE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "N_TRIG") {
                  N_TRIG = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "RANDOM_MODE") {
                  RANDOM_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SEED") {
                  SEED = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "BORE_HOLE_ANTENNA_LAYOUT") {
                  BORE_HOLE_ANTENNA_LAYOUT = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "RAYSOL_RANGE") {
                  RAYSOL_RANGE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "CALPULSER_ON") {
                  CALPULSER_ON = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TESTBED_ON") {
                  TESTBED_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "READGEOM") {
                  cout << "Read in READGEOM" << endl;
                  READGEOM = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "PICK_POSNU_DEPTH") {
                  PICK_POSNU_DEPTH = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "MAX_POSNU_DEPTH") {
                  MAX_POSNU_DEPTH = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NNU_THIS_THETA") {
                  NNU_THIS_THETA = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NNU_THETA") {
                  NNU_THETA = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NNU_D_THETA") {
                  NNU_D_THETA = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NNU_THIS_PHI") {
                  NNU_THIS_PHI = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NNU_PHI") {
                  NNU_PHI = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NNU_D_PHI") {
                  NNU_D_PHI = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }

              else if (label == "Z_THIS_TOLERANCE") {
                  Z_THIS_TOLERANCE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "Z_TOLERANCE") {
                  Z_TOLERANCE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }

              else if (label == "DATA_LIKE_OUTPUT") {
                  DATA_LIKE_OUTPUT = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "V_MIMIC_MODE") {
                  V_MIMIC_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "USE_INSTALLED_TRIGGER_SETTINGS") {
                  USE_INSTALLED_TRIGGER_SETTINGS = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NUM_INSTALLED_STATIONS") {
                  NUM_INSTALLED_STATIONS = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "CALPUL_OFFCONE_ANGLE") {
                  CALPUL_OFFCONE_ANGLE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "CALPUL_AMP") {
                  CALPUL_AMP = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TRIG_ONLY_BH_ON") {
                  TRIG_ONLY_BH_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "TRIG_THRES_MODE") {
                  TRIG_THRES_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "NOISE_CHANNEL_MODE") {
                  NOISE_CHANNEL_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "CONST_MEANDIODE") {
                  CONST_MEANDIODE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "CONST_RMSDIODE") {
                  CONST_RMSDIODE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "USE_TESTBED_RFCM_ON") {
                  USE_TESTBED_RFCM_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "RFCM_OFFSET") {
                  RFCM_OFFSET = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "USE_MANUAL_GAINOFFSET") {
                  USE_MANUAL_GAINOFFSET = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "MANUAL_GAINOFFSET_VALUE") {
                  MANUAL_GAINOFFSET_VALUE = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NOISE_WAVEFORM_GENERATE_MODE") {
                  NOISE_WAVEFORM_GENERATE_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "USE_CH_GAINOFFSET") {
                  USE_CH_GAINOFFSET = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              //else if (label == "GETCHORD_MODE") {
                  //GETCHORD_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              //}
              else if (label == "taumodes") {
                  taumodes = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "BH_ANT_SEP_DIST_ON") {
                  BH_ANT_SEP_DIST_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TRIG_MODE") {
                  TRIG_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "N_TRIG_V") {
                  N_TRIG_V = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "N_TRIG_H") {
                  N_TRIG_H = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "FILL_TREE_MODE") {
                  FILL_TREE_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "ONLY_PASSED_EVENTS") {
                  ONLY_PASSED_EVENTS = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NNU_PASSED") {
                  NNU_PASSED = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "PICKNEARUNBIASED_R") {
                  PICKNEARUNBIASED_R = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SHOWER_MODE") {
                  SHOWER_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SHOWER_STEP") {
                  SHOWER_STEP = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SHOWER_PARAM_MODEL") {
                  SHOWER_PARAM_MODEL = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "ALL_ANT_V_ON") {
                  ALL_ANT_V_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "PHASE_SKIP_MODE") {
                  PHASE_SKIP_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "DEBUG_MODE_ON") {
                  DEBUG_MODE_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "DEBUG_SKIP_EVT") {
                  DEBUG_SKIP_EVT = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "V_SATURATION") {
                  V_SATURATION = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "OFFCONE_LIMIT") {
                  OFFCONE_LIMIT = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "ADDITIONAL_DEPTH_ON") {
                  ADDITIONAL_DEPTH_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "ADDITIONAL_DEPTH") {
                  ADDITIONAL_DEPTH = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "TRIG_ONLY_LOW_CH_ON") {
                  TRIG_ONLY_LOW_CH_ON = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "USE_ARA_ICEATTENU") {
                  USE_ARA_ICEATTENU = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SIGMA_SELECT") {
                  SIGMA_SELECT = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "SIGMAPARAM") {
                  SIGMAPARAM = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "SIGMA_FACTOR") {
                  SIGMA_FACTOR = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "YPARAM") {
                  YPARAM = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "ELAST_Y") {
                 ELAST_Y = atof( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "NU_NUBAR_SELECT_MODE") {
                  NU_NUBAR_SELECT_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
              else if (label == "SELECT_FLAVOR") {
                  SELECT_FLAVOR = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "SELECT_CURRENT") {
                  SELECT_CURRENT = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }
              else if (label == "OUTPUT_TDR_GRAPH") {
                  OUTPUT_TDR_GRAPH = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }       
              else if (label == "AVZ_NORM_FACTOR_MODE") {
                  AVZ_NORM_FACTOR_MODE = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
              }              
	      else if (label == "number_of_stations") {
		number_of_stations = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "RAY_TRACE_ICE_MODEL_PARAMS") {
		RAY_TRACE_ICE_MODEL_PARAMS = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "WAVEFORM_LENGTH") {
		WAVEFORM_LENGTH = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "WAVEFORM_CENTER") {
		WAVEFORM_CENTER = atoi( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "DEADTIME") {
		    DEADTIME = atof( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "POSNU_R") {
		POSNU_R = atof( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "POSNU_THETA") {
		POSNU_THETA = atof( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "POSNU_PHI") {
		POSNU_PHI = atof( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "ARBITRARY_EVENT_ATTENUATION") {
		ARBITRARY_EVENT_ATTENUATION = atof( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
	      else if (label == "PICK_ABOVE_HEIGHT") {
		PICK_ABOVE_HEIGHT = atof( line.substr(line.find_first_of("=") + 1).c_str() );
	      }
              else if (label == "EVENT_GENERATION_MODE"){
                  EVENT_GENERATION_MODE = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }
	      //              else if (label == "EVENT_NUM"){
	      //                  EVENT_NUM = atoi(line.substr(line.find_first_of("=") + 1).c_str());
	      //              }
              else if (label == "ANTENNA_MODE"){
                  ANTENNA_MODE = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }
              else if (label == "VPOL_GAIN_FILE") {
                  VPOL_GAIN_FILE = ParseFilePath(line);
                  if (VPOL_GAIN_FILE.empty()) {
                      std::cerr << "Warning: could not parse path from line: " << line << std::endl;
                      std::cerr << "Example Input: VPOL_GAIN_FILE=\"path/to/gain/file.txt\"" << std::endl;
                      std::abort();
                  }
              }
              else if (label == "VTOP_GAIN_FILE") {
                  VTOP_GAIN_FILE = ParseFilePath(line);
                  if (VTOP_GAIN_FILE.empty()) {
                      std::cerr << "Warning: could not parse path from line: " << line << std::endl;
                      std::cerr << "Example Input: VTOP_GAIN_FILE=\"path/to/gain/file.txt\"" << std::endl;
                      std::abort();
                  }
              }
              else if (label == "HPOL_GAIN_FILE") {
                  HPOL_GAIN_FILE = ParseFilePath(line);
                  if (HPOL_GAIN_FILE.empty()) {
                      std::cerr << "Warning: could not parse path from line: " << line << std::endl;
                      std::cerr << "Example Input: HPOL_GAIN_FILE=\"path/to/gain/file.txt\"" << std::endl;
                      std::abort();
                  }
              }
              else if (label == "IMPEDANCE_RX_VPOL"){
                  IMPEDANCE_RX_VPOL = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }              
              else if (label == "IMPEDANCE_RX_VPOL_TOP"){
                  IMPEDANCE_RX_VPOL_TOP = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }              
              else if (label == "IMPEDANCE_RX_HPOL"){
                  IMPEDANCE_RX_HPOL = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }              
              else if (label == "IMPEDANCE_TX"){
                  IMPEDANCE_TX = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }              
              else if (label == "APPLY_NOISE_FIGURE"){
                  APPLY_NOISE_FIGURE = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }
              else if (label == "CUSTOM_ELECTRONICS"){
              	   CUSTOM_ELECTRONICS = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }
              else if (label == "ELECTRONICS_ANTENNA_CONSISTENCY"){
              	   ELECTRONICS_ANTENNA_CONSISTENCY = atoi(line.substr(line.find_first_of("=") + 1).c_str());
              }
          else if (label == "CLOCK_ANGLE"){
               CLOCK_ANGLE = atof(line.substr(line.find_first_of("=") + 1).c_str());
          }
          //Adding source easting, northing, and depth for INTERACTION_MODE=5.
          else if (label == "SOURCE_LATITUDE"){
              SOURCE_LATITUDE = atof(line.substr(line.find_first_of("=") + 1).c_str());
          }
          else if (label == "SOURCE_LONGITUDE"){
              SOURCE_LONGITUDE = atof(line.substr(line.find_first_of("=") + 1).c_str());
          }
          else if (label == "SOURCE_DEPTH"){
               SOURCE_DEPTH = atof(line.substr(line.find_first_of("=") + 1).c_str());
          }

          }
      }
      setFile.close();
  }
  else cout<<"Unable to open "<<setupfile<<" file!"<<endl;
  return;
}

void Settings::ReadEvtFile(string evtfile){
    ifstream evtFile(evtfile.c_str());

    std::string line;
    int n = 0;

    if ( evtFile.is_open() ) {
        while (evtFile.good() ) {
            getline(evtFile, line);
            if (line[0] != "/"[0]) {

                std::stringstream iss(line);

                uint64_t EL_evid;
                int EL_nuflavorint, EL_nunubar, EL_current, EL_prim_pid;
                double EL_energy, EL_pos_R, EL_pos_theta, EL_pos_phi, EL_dir_theta, EL_dir_phi;
                double EL_elast_y, EL_weight, EL_prim_energy;
                if(!(iss >> EL_evid >> EL_nuflavorint >> EL_nunubar >> EL_energy >> EL_current 
                         >> EL_pos_R >> EL_pos_theta >> EL_pos_phi >> EL_dir_theta >> EL_dir_phi
                         >> EL_elast_y >> EL_weight >> EL_prim_energy >> EL_prim_pid)){
                    break;
                }

                EVID.push_back(EL_evid);
                NUFLAVORINT.push_back(EL_nuflavorint);
                NUBAR.push_back(EL_nunubar);
                PNU.push_back(EL_energy);
                CURRENTINT.push_back(EL_current);
                IND_POSNU_R.push_back(EL_pos_R);
                IND_POSNU_THETA.push_back(EL_pos_theta);
                IND_POSNU_PHI.push_back(EL_pos_phi);
                IND_NNU_THETA.push_back(EL_dir_theta);
                IND_NNU_PHI.push_back(EL_dir_phi);
                ELAST.push_back(EL_elast_y);
                WEIGHTS.push_back(EL_weight);
                NU_PRIM_ENERGY.push_back(EL_prim_energy);
                NU_PRIM_PID.push_back(EL_prim_pid);

                n++;
            }
        }
        evtFile.close();

        // EVID: Vector storing event IDs (integers) for neutrino interactions.
        // Each element in EVID represents a specific interaction, and repeated event IDs 
        // indicate multiple interactions associated with the same neutrino (stochastic losses, decays, etc).
        
        NNU = 0; //restart neutrino count from zero (default N = 100)

        if (!EVID.empty()) {
            int interactions_per_nnu_cnt = 1;  // Start the counter for interactions per neutrino

            // Iterate through the EVID vector starting from the second element
            for (size_t i = 1; i < EVID.size(); ++i) {
                if (EVID[i] == EVID[i - 1]) {
                    interactions_per_nnu_cnt++;  // Increment the counter when the same event ID repeats
                } else {
                    //New event ID encountered
                    // Store the interactions count for the previous neutrino
                    INT_PER_NNU.push_back(interactions_per_nnu_cnt);
                    // Reset the interaction counter for the new neutrino
                    interactions_per_nnu_cnt = 1;
                    // Increment the number of unique neutrinos
                    NNU++;
                }
            }

            // Store the interaction count for the last neutrino (or if EVID = 1)
            INT_PER_NNU.push_back(interactions_per_nnu_cnt);

            // Increment the neutrino count to account for the last unique neutrino (or if EVID = 1)
            NNU++;
        }
	
    }
    else
        cout << "Unable to open " << evtfile << " file!" << endl;
    return;
}

int Settings::CheckCompatibilitiesDetector(Detector *detector) {

    int num_err = 0;

    // if there's something not going to work, count thoes settings

    if (DETECTOR==1 && READGEOM==1 && detector->params.number_of_stations>1) { // currently only ARA1a one station is possible
        cerr<<"DETECTOR=1, READGEOM=1 is currently only availble with number_of_stations=1 in ARA_N_info.txt file!"<<endl;
        num_err++;
    }

    if (DETECTOR==2 && READGEOM==1) { // currently READGEOM (using actual installed stations info) is not available in DETECTOR=2
        cerr<<"DETECTOR=2 and READGEOM=1 is currently not availble! Only ideal stations are available in DETECTOR=2!"<<endl;
        num_err++;
    }

    // check reasonable number of noise waveforms
    if (NOISE_WAVEFORM_GENERATE_MODE == 0) { // if generating new noise waveforms for every events
        if (NOISE_CHANNEL_MODE == 0) {// share all noise waveforms same with other channels
            //if (NOISE_EVENTS < detector->params.number_of_antennas) { // this is too low number of events!
            if (NOISE_EVENTS < detector->max_number_of_antennas_station) { // this is too low number of events!
                cerr<<"NOISE_EVENTS too less! At least use "<<detector->max_number_of_antennas_station<<"!"<<endl;
                num_err++;
            }
        }
        else if (NOISE_CHANNEL_MODE == 1) {// each chs will have separate noise waveforms
            if (NOISE_EVENTS > 1) { // this case 1 waveform is enough for each channels
                cerr<<"NOISE_EVENTS too many! With NOISE_WAVEFORM_GENERATE_MODE==0 and NOISE_CHANNEL_MODE==1, just use NOISE_EVENTS=1"<<endl;
                num_err++;
            }
        }
    }
    if (NOISE_WAVEFORM_GENERATE_MODE == 1) { // if generating noise waveforms in the begining and keep use them
        if (NOISE_CHANNEL_MODE == 0) {// share all noise waveforms same with other channels
            //if (NOISE_EVENTS < detector->params.number_of_antennas) { // this is too low number of events!
            if (NOISE_EVENTS < detector->max_number_of_antennas_station) { // this is too low number of events!
                cerr<<"NOISE_EVENTS too less! At least use "<<detector->max_number_of_antennas_station<<"!"<<endl;
                num_err++;
            }
        }
    }

    // check if there's enough system temperature values prepared for NOISE_CHANNEL_MODE=1
    if (NOISE_CHANNEL_MODE==1) {// use different system temperature values for different chs
        if (DETECTOR==3 && (detector->params.number_of_antennas > (int)(detector->Temp_TB_ch.size())) ) {
            cout << detector->params.number_of_antennas << " : " <<(int)(detector->Temp_TB_ch.size()) << endl;
            cerr<<"System temperature values are not enough for all channels! Check number of channels you are using and numbers in data/system_temperature.csv"<<endl;
            num_err++;
        }
    }

    // check if the user set a cylinder height but didn't tell AraSim to use it!
    if (MAX_POSNU_DEPTH > 0 && PICK_POSNU_DEPTH != 1) {
        cerr << "Non-zero MAX_POSNU_DEPTH set but PICK_POSNU_DEPTH != 1, so this will be ignored and cylinder height will be ice thickness!" << endl;
        cerr << "Please change settings to either not set MAX_POSNU_DEPTH or set PICK_POSNU_DEPTH to 1." << endl;
        num_err++;
    }

    return num_err;
}

int Settings::CheckCompatibilitiesSettings() {

    int num_err = 0;

    // ensure that NFOUR is a power of 2
    if (NFOUR & (NFOUR-1) != 0) {
        cerr<<"NFOUR is not a power of 2!"<<endl;
        num_err++;
    }

    // ensure that NFOUR is big enough that you don't have problems with FFTs or readout
    if (2*WAVEFORM_LENGTH > NFOUR) {
        cerr<<"NFOUR should be at least twice WAVEFORM_LENGTH to avoid FFT artifacts or problems with readout!"<<endl; 
        num_err++;
    }
 
    // for PA simulations we need to be careful since BINSIZE isnt the usual NFOUR/2 
    // but is hardcoded to 1200/(settings1->TIMESTEP*1.e9), so we need to make sure 
    // NFOUR is at least twice this to avoid FFT issues
    const int PA_INTERNAL_LENGTH = 1200/(TIMESTEP*1.e9);
    if ( DETECTOR==5 && 2*PA_INTERNAL_LENGTH > NFOUR) {
        cerr<<"NFOUR should be at least twice PA_INTERNAL_LENGTH to avoid FFT artifacts or problems with readout!" 
            << " Your PA_INTERNAL_LENGTH = " << PA_INTERNAL_LENGTH <<endl; 
        num_err++;
    }

    // Also ensure that the requested waveform length isn't longer than the internal length
    if ( DETECTOR==5 && PA_INTERNAL_LENGTH < WAVEFORM_LENGTH) {
        cerr<<"WAVEFORM_LENGTH cannot be longer than PA_INTERNAL_LENGTH to avoid problems with readout!"
            << " Your PA_INTERNAL_LENGTH = " << PA_INTERNAL_LENGTH <<endl; 
        num_err++;
    }


    // if BH_ANT_SEP_DIST_ON=1, we can't use READGEOM=1 (actual installed geom)
    if (BH_ANT_SEP_DIST_ON==1 && READGEOM==1) {
        cerr<<"BH_ANT_SEP_DIST_ON=1 is only available in ideal station geom (READGEOM=0)!"<<endl; 
        num_err++;
    }

    // TRIG_MODE=1 (Vpol, Hpol separated) will not work with testbed station mode
    if (TRIG_MODE==1 && DETECTOR==3) {
        cerr<<"TRIG_MODE=1 is not available in TestBed mode (DETECTOR=3)!"<<endl; 
        num_err++;
    }

    if (TRIG_SCAN_MODE==5 && ( DETECTOR!=5 ) ){
        cerr<<"TRIG_SCAN_MODE=5 only compatible for Phased Array (DETECTOR= 5)"<<endl;
        num_err++;
    }

    if ( DETECTOR==5 && TRIG_SCAN_MODE!=5){
        cout<<"Warning: PA trigger only checked on its own if TRIG_SCAN_MODE=5 (for DETECTOR = 5)"<<endl;
        // cerr<<"PA trigger only checked if TRIG_SCAN_MODE=5 (for DETECTOR = 5)"<<endl;
        // num_err++;
    }

    if ( DETECTOR==5 && ( DETECTOR_STATION<1 || DETECTOR_STATION>3 ) ) {
        cerr<<"DETECTOR_STATION must be 1,2,3 for PA Station (DETECTOR = 5) "<<endl;
        num_err++;
    }


    // check modes which will only work for actual installed TestBed case
    if (TRIG_ONLY_BH_ON==1 && DETECTOR!=3) {
        cerr<<"TRIG_ONLY_BH_ON=1 only works with DETECTOR=3!"<<endl;
        num_err++;
    }

    if (NOISE_CHANNEL_MODE==2 && DETECTOR!=3 && TRIG_ONLY_LOW_CH_ON!=1) {
        cerr<<"NOISE_CHANNEL_MODE=2 only works with DETECTOR=3 or TRIG_ONLY_LOW_CH_ON=1"<<endl;
        num_err++;
    }

    if (DETECTOR==3 && READGEOM==0) {
        cerr<<"DETECTOR=3 will always need READGEOM=1"<<endl;
        num_err++;
    }

    if (USE_TESTBED_RFCM_ON==1 && DETECTOR!=3) {
        cerr<<"USE_TESTBED_RFCM_ON=1 only works with DETECTOR=3!"<<endl;
        num_err++;
    }

    if (USE_CH_GAINOFFSET==1 && DETECTOR!=3) {
        cerr<<"USE_CH_GAINOFFSET=1 only works with DETECTOR=3!"<<endl;
        num_err++;
    }

    if (TRIG_THRES_MODE==1 && DETECTOR!=3 && TRIG_ONLY_LOW_CH_ON!=1) {
        cerr<<"TRIG_THRES_MODE=1 only works with DETECTOR=3 or TRIG_ONLY_LOW_CH_ON=1"<<endl;
        num_err++;
    }

    if (TRIG_THRES_MODE==2 && DETECTOR!=3 && TRIG_ONLY_LOW_CH_ON!=1) {
        cerr<<"TRIG_THRES_MODE=2 only works with DETECTOR=3 or TRIG_ONLY_LOW_CH_ON=1"<<endl;
        num_err++;
    }

    if (USE_MANUAL_GAINOFFSET==1 && DETECTOR!=3) {
        cerr<<"USE_MANUAL_GAINOFFSET=1 only works with DETECTOR=3!"<<endl;
        num_err++;
    }

    if (CALPULSER_ON!=0 && DETECTOR!=3) {
        cerr<<"CALPULSER_ON=1 and above only works with DETECTOR=3!"<<endl;
        num_err++;
    }

    if ((V_MIMIC_MODE==1||V_MIMIC_MODE==2) && DETECTOR!=3) {
        cerr<<"V_MIMIC_MODE=1 and 2 only works with DETECTOR=3!"<<endl;
        num_err++;
    }
    
    if (USE_MANUAL_GAINOFFSET==1 && USE_CH_GAINOFFSET==1) {
        cerr<<"Can not use USE_MANUAL_GAINOFFSET=1 and USE_CH_GAINOFFSET=1 same time!"<<endl;
        num_err++;
    }

    if (NOISE==1 && USE_TESTBED_RFCM_ON==1) {
        cerr<<"NOISE=1 only works with USE_TESTBED_RFCM_ON=0!"<<endl;
        num_err++;
    }

    if (NOISE==1 && NOISE_CHANNEL_MODE==0) {
        cerr<<"NOISE=1 don't work with NOISE_CHANNEL_MODE=0!"<<endl;
        num_err++;
    }


    // This is for only ideal stations
    if (TRIG_ONLY_LOW_CH_ON==1 && DETECTOR==3) {
        cerr<<"TRIG_ONLY_LOW_CH_ON=1 doesn't work with DETECTOR=3!"<<endl;
        num_err++;
    }
    if (DATA_LIKE_OUTPUT != 0 && (DETECTOR==0 || DETECTOR==1 || DETECTOR==2)) {
        cerr<<"DATA_LIKE_OUTPUT=1,2 doesn't work with DETECTOR=0,1,2"<<endl;
        cerr<<"DATA_LIKE_OUTPUT controls data-like output into UsefulAtriStationEvent format;" 
            <<" without a real station selected (using DETECTOR==3,4), the mapping to the data-like output will not function correctly"<<endl;
        num_err++;
    }

    if (DATA_LIKE_OUTPUT != 0 && (DETECTOR_STATION>5)) {
        cerr<<"DATA_LIKE_OUTPUT=1,2 doesn't work with DETECTOR_STATION>3"<<endl;
        cerr<<"DATA_LIKE_OUTPUT controls data-like output into UsefulAtriStationEvent format;"
            <<" without a real station selected (using DETECTOR==3,4), the mapping to the data-like output will not function correctly"<<endl;
        num_err++;
    }

    if (DETECTOR == 4 ) {
      if (ARAUTIL_EXISTS == false){
        cerr << "DETECTOR=4 only works with an installation of AraRoot" << endl;
        num_err++;
      } 
      else {
	
        cerr << "DETECTOR is set to 4" << endl; 
        cerr << "Setting READGEOM to 1" << endl;
        READGEOM=1;

        cerr << "Setting number_of_stations to 1" << endl;
        number_of_stations = 1;

        if (DETECTOR_STATION <0 || DETECTOR_STATION >= NUM_INSTALLED_STATIONS){
          cerr << "DETECTOR_STATION is not set to a valid station number" << endl;
          num_err++;
        }
      }
    }

    if ( (int)DETECTOR == 5 ){

	    cerr << "DETECTOR is set to 5" << endl; 

        // Phased Array mode (DETECTOR=5) uses DETECTOR_STATION for DAQ configurations
	    if (DETECTOR_STATION < 1 || DETECTOR_STATION > 3) {
	        cerr << "DETECTOR_STATION is not set to a valid station number" << endl;
	        num_err++;
	    }
    } // end if DETECTOR==5

    //Check that DETECTOR_STATION=0 is only used with DETECTOR=3
    if (DETECTOR_STATION==0 && DETECTOR!=3){
      cerr << " DETECTOR_STATION=0 doesn't work with DETECTOR!=3. If you want to work with TestBed, use DETECTOR=3 & DETECTOR_STATION=0" << endl;
      num_err++;
    }
    if (DETECTOR==0){
      cerr << "DETECTOR=0 is un-used in AraSim."<<endl;
      num_err++;
    }
    if (DETECTOR_STATION>=0 && DETECTOR<3){
      cerr << "DETECTOR_STATION>=0 is only compatible with DETECTOR=3 (Testbed) or DETECTOR=4 (deep stations)"<<endl;
      num_err++;
    }

    // check that USE_PARAM_RE_TTERM_TABLE is only used with SIMULATION_MODE==1
    if (USE_PARAM_RE_TTERM_TABLE==1 && SIMULATION_MODE!=1){
      cerr << "USE_PARAM_RE_TTERM_TABLE=0 doesn't work with SIMULATION_MODE!=1"<<endl;
      num_err++;
    }

   //Compatibilities for birefringence
    if (BIREFRINGENCE==1){
      if(DETECTOR!=4){
        cerr << "BIREFRINGENCE=1 is only supported for individual stations" <<endl;
        num_err++; 
      }	
      if (BIAXIAL<0 || BIAXIAL>1){
        cerr << "BIREFRINGENCE only supports BIAXIAL=0 (uniaxial) or BIAXIAL=1 (biaxial)" << endl;
        num_err++;
      }
      if (RAY_TRACE_ICE_MODEL_PARAMS!=50){
          cerr << "BIREFRINGENCE=1 should only work with RAY_TRACE_ICE_MODEL_PARAMS=50" <<endl;	
          num_err++;
      }
    }
    if (BIREFRINGENCE!=1 && BIREFRINGENCE!=0){
      cerr << "BIREFRINGENCE only takes 0 or 1" << endl;
      num_err++;
    }

    // checking antenna mode 
    if (ANTENNA_MODE != 6) {
        if (!VPOL_GAIN_FILE.empty() || !VTOP_GAIN_FILE.empty() || !HPOL_GAIN_FILE.empty()) {
            std::cerr << "Warning: Custom GAIN_FILE paths provided, "
                    << "but ANTENNA_MODE != 6. These files may be ignored." << std::endl;
            num_err++; 
        }
    }


    return num_err;

}

void Settings::SetGitCommitHash(){
    #ifndef GIT_COMMIT_HASH
    #define GIT_COMMIT_HASH "SETTING_GIT_COMMIT_HASH_FAILED"
    #endif
    std::strncpy(COMMIT_HASH, GIT_COMMIT_HASH, sizeof(COMMIT_HASH));
    COMMIT_HASH[sizeof(COMMIT_HASH) - 1] = '\0';
    std::cout<<"The Git Commit Hash: "<<COMMIT_HASH<<std::endl;
}

std::string Settings::ParseFilePath(const std::string& line) {
    size_t eq_pos = line.find('=');
    if (eq_pos == std::string::npos) {
        return ""; 
    }

    // Search for the first quote after the '='
    size_t quote_start = line.find('"', eq_pos);
    if (quote_start == std::string::npos) {
        return ""; 
    }

    size_t quote_end = line.find('"', quote_start + 1);
    if (quote_end == std::string::npos) {
        return ""; 
    }

    return line.substr(quote_start + 1, quote_end - quote_start - 1);
}