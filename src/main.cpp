#include <iostream>
#include <string>
#include "sclib.h"
#include "zlib.h"

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

  sc::hello();
  std::cout << std::endl;

  tests::test_reading_generic_xml(file4);

  std::vector<float> inputFloat = {10, 13.4, 15.6, 1000.5};
  std::vector<double> inputDouble(inputFloat.size());
  for (size_t i = 0; i < inputFloat.size(); i++) {
    inputDouble[i] = static_cast<double>(inputFloat[i]);
  }
  tests::test_encoding_decoding_little_endian(inputDouble, 4);


  std::vector<double> input = {10, 13.4, 15.6, 1000.5};
  tests::test_encoding_decoding_little_endian(input, 8);

  tests::test_extract_spectra_mzml(file2);

  tests::test_extract_chromatograms_mzml(file5);


  // std::cout << "Loading an AnIML file!" << std::endl;
  // sc::ANIML animl(file3);
  // std::cout << animl.get_name() << std::endl;
  // std::cout << std::endl;

  return 0;
}
