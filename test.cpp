#define STREAMCRAFT_HEADER_ONLY
#include "StreamCraft_lib.hpp"
#include "../tests/StreamCraft_tests.hpp"

int main() {

  std::vector<float> input = {10, 13.4, 15.6, 1000.5};
  test_encoding_decoding_little_endian(input, 4);
  test_encoding_decoding_little_endian(input, 8);
  test_encoding_decoding_big_endian(input, 4);
  test_encoding_decoding_big_endian(input, 8);

  std::string file1 = "./excluded/example.mzML";
  test_extract_spectra_mzml(file1);
  std::string file4 = "./excluded/mrm_pos.mzML";
  test_extract_chromatograms_mzml(file4);
  std::string file7 = "./excluded/example.mzXML";
  test_extract_spectra_mzxml(file7);
  std::string file8 = "./excluded/example_profile.mzML";
  test_extract_ms_analysis(file8, 4);

  return 0;
}
