#include "sclib.h"

// #include "MSToolkitTypes.h"
// #include "MSReader.h"
// #include "MSObject.h"
// #include "Spectrum.h"
// using namespace std;
// using namespace MSToolkit;

int main() {

  std::string file1 = "/home/cunha/Documents/example_ms_files/tof_25000_mix1-r001.mzML";
  std::string file2 = "./excluded/example.mzML";
  std::string file3 = "./excluded/example.animl";
  std::string file4 = "./excluded/basic.xml";
  std::string file5 = "./excluded/mrm_pos.mzML";
  std::string file6 = "./excluded/mrm_neg.mzML";
  std::string file7 = "./excluded/example_strict.animl";

  sc::hello();
  std::cout << std::endl;

  // tests::test_reading_generic_xml(file4);

  // Pre conversion of a float vector to double for returning the same as input
  // std::vector<float> inputFloat = {10, 13.4, 15.6, 1000.5};
  // std::vector<double> inputDouble(inputFloat.size());
  // for (size_t i = 0; i < inputFloat.size(); i++) {
  //   inputDouble[i] = static_cast<double>(inputFloat[i]);
  // }

  // tests::test_encoding_decoding_little_endian(inputDouble, 4);


  // std::vector<double> input = {10, 13.4, 15.6, 1000.5};
  // tests::test_encoding_decoding_little_endian(input, 8);

  // tests::test_extract_spectra_mzml(file2);

  // tests::test_extract_chromatograms_mzml(file5);

  sc::animl::ANIML animl_file(file7);
  std::cout << animl_file.get_name() << std::endl;
  std::cout << std::endl;
  std::cout << "Number of samples: " << animl_file.get_number_samples() << std::endl;
  std::cout << std::endl;
  std::vector<int> indices = {1, 2};
  std::vector<sc::animl::SAMPLE> samples = animl_file.get_samples(indices, {}, {});
  std::cout << "Get samples by indices:" << std::endl;
  std::cout << "Names: ";
  for (const sc::animl::SAMPLE& sp : samples) std::cout << sp.name << "; ";
  std::cout << std::endl;
  std::cout << "SampleID: ";
  for (const sc::animl::SAMPLE& sp : samples) std::cout << sp.sampleID << "; ";
  std::cout << std::endl;
  std::cout << std::endl;
  std::vector<std::string> names = {"Mobile Phase", "Test Sample"};
  std::vector<sc::animl::SAMPLE> samples2 = animl_file.get_samples({}, names, {});
  std::cout << "Get samples by name:" << std::endl;
  std::cout << "Names: ";
  for (const sc::animl::SAMPLE& sp : samples2) std::cout << sp.name << "; ";
  std::cout << std::endl;
  std::cout << "SampleID: ";
  for (const sc::animl::SAMPLE& sp : samples2) std::cout << sp.sampleID << "; ";
  std::cout << std::endl;
  std::cout << std::endl;
  std::vector<std::string> sampleIDs = {"s1", "s3"};
  std::vector<sc::animl::SAMPLE> samples3 = animl_file.get_samples({}, {}, sampleIDs);
  std::cout << "Get samples by sampleID:" << std::endl;
  std::cout << "Names: ";
  for (const sc::animl::SAMPLE& sp : samples3) std::cout << sp.name << "; ";
  std::cout << std::endl;
  std::cout << "SampleID: ";
  for (const sc::animl::SAMPLE& sp : samples3) std::cout << sp.sampleID << "; ";
  std::cout << std::endl;
  std::cout << std::endl;


  std::cout << "Number of experiments: " << animl_file.get_number_experiment_steps() << std::endl;
  std::cout << std::endl;
  std::vector<int> indices2 = {0};
  std::vector<sc::animl::EXPSTEP> exps = animl_file.get_experiment_steps(indices2, {}, {}, {});
  std::cout << "Get experiments by indices:" << std::endl;
  std::cout << "Names: ";
  for (const sc::animl::EXPSTEP& ex : exps) std::cout << ex.name << "; ";
  std::cout << std::endl;
  std::cout << "Technique: ";
  for (const sc::animl::EXPSTEP& ex : exps) std::cout << ex.technique_name << "; ";
  std::cout << std::endl;
  std::cout << std::endl;
  std::vector<std::string> names2 = {"Q1"};
  std::vector<sc::animl::EXPSTEP> exps2 = animl_file.get_experiment_steps({}, names2 ,{}, {});
  std::cout << "Get experiments by names:" << std::endl;
  std::cout << "Names: ";
  for (const sc::animl::EXPSTEP& ex : exps2) std::cout << ex.name << "; ";
  std::cout << std::endl;
  std::cout << "Technique: ";
  for (const sc::animl::EXPSTEP& ex : exps2) std::cout << ex.technique_name << "; ";
  std::cout << std::endl;
  std::cout << std::endl;
  std::vector<std::string> tech = {"Chromatography"};
  std::vector<sc::animl::EXPSTEP> exps3 = animl_file.get_experiment_steps({},{}, tech, {});
  std::cout << "Get experiments by technique:" << std::endl;
  std::cout << "Names: ";
  for (const sc::animl::EXPSTEP& ex : exps3) std::cout << ex.name << "; ";
  std::cout << std::endl;
  std::cout << "Technique: ";
  for (const sc::animl::EXPSTEP& ex : exps3) std::cout << ex.technique_name << "; ";
  std::cout << std::endl;
  std::cout << "Technique URI: ";
  for (const sc::animl::EXPSTEP& ex : exps3) std::cout << ex.technique_uri << "; ";
  std::cout << std::endl;
  std::cout << std::endl;
  sc::animl::EXPSTEP exp3 = exps3[0];
  std::cout << "Experiment (first): " << exp3.name << std::endl;
  std::cout << std::endl;
  std::cout << "Number of results: " << exp3.ResultSet.size() << std::endl;
  std::cout << std::endl;
  sc::animl::RESULT expRes = exp3.ResultSet[0];
  std::cout << "Result (first): " << expRes.name << std::endl;
  std::cout << "Number of series: " << expRes.SeriesSet.size() << std::endl;
  std::cout << "Number of experiments: " << expRes.ExpStepSet.size() << std::endl;
  std::cout << std::endl;


  return 0;
}
