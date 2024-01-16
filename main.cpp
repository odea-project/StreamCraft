#include "sclib.hpp"
#include "tests.hpp"

int main() {

  std::string file1 = "/home/cunha/Documents/example_ms_files/tof_25000_mix1-r001.mzML";
  std::string file2 = "./excluded/example.mzML";
  std::string file3 = "./excluded/example.animl";
  std::string file4 = "./excluded/basic.xml";
  std::string file5 = "./excluded/mrm_pos.mzML";
  std::string file6 = "./excluded/mrm_neg.mzML";
  std::string file7 = "./excluded/example_strict.animl";
  std::string file8 = "./excluded/example.mzXML";
  std::string file9 = "./excluded/example_modified.mzML";

  sc::hello();
  std::cout << std::endl;


  tests::test_writing_mzml(file9);

  // tests::test_integration_mstoolkit(file2);

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

  // tests::test_reading_animl(file7);




  return 0;
}
