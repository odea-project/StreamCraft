#define STREAMCRAFT_HEADER_ONLY
#include "StreamCraft_lib.hpp"

void test_encoding_decoding_little_endian(const std::vector<double>& input, const int& precision) {
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Encoding and Decoding Little Endian (" << precision * 8 << "-bit) Test" << std::endl;
  std::cout << std::endl;
  std::cout << "Input vector: ";
  for (double i : input) std::cout << i << " ";
  std::cout << std::endl;
  std::string result = sc::encode_little_endian(input, precision);
  std::cout << "Encoded: " << result << std::endl;
  result = sc::compress_zlib(result);
  std::cout << "Compressed: " << "Not printed!" << std::endl;
  result = sc::encode_base64(result);
  std::cout << "Encoded_base64: " << result << std::endl;
  std::cout << std::endl;
  result = sc::decode_base64(result);
  std::cout << "Decoded_base64: " << "Not printed!" << std::endl;
  result = sc::decompress_zlib(result);
  std::cout << "Decompressed: " << result << std::endl;
  std::vector<double> result_back = sc::decode_little_endian(result, precision);
  std::cout << "Decoded: ";
  for (double i : result_back) std::cout << i << " ";
  std::cout << std::endl;
  bool check = input == result_back;
  std::cout << std::endl;
  std::cout << "When 1 the result is equal to input: " << check << std::endl;
  std::cout << std::endl;
};

void test_encoding_decoding_big_endian(const std::vector<double>& input, const int& precision) {
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Encoding and Decoding Big Endian (" << precision * 8 << "-bit) Test" << std::endl;
  std::cout << std::endl;
  std::cout << "Input vector: ";
  for (double i : input) std::cout << i << " ";
  std::cout << std::endl;
  std::string result = sc::encode_big_endian(input, precision);
  std::cout << "Encoded: " << result << std::endl;
  result = sc::compress_zlib(result);
  std::cout << "Compressed: " << "Not printed!" << std::endl;
  result = sc::encode_base64(result);
  std::cout << "Encoded_base64: " << result << std::endl;
  std::cout << std::endl;
  result = sc::decode_base64(result);
  std::cout << "Decoded_base64: " << "Not printed!" << std::endl;
  result = sc::decompress_zlib(result);
  std::cout << "Decompressed: " << result << std::endl;
  std::vector<double> result_back = sc::decode_big_endian(result, precision);
  std::cout << "Decoded: ";
  for (double i : result_back) std::cout << i << " ";
  std::cout << std::endl;
  bool check = input == result_back;
  std::cout << std::endl;
  std::cout << "When 1 the result is equal to input: " << check << std::endl;
  std::cout << std::endl;
};

void test_extract_spectra_mzml(const std::string& file) {
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Test Extract Spectra mzML file:" << std::endl;
  std::cout << std::endl;
  sc::MZML mzml(file);
  std::cout << "Root name: " << mzml.name << std::endl;
  std::cout << "Number of spectra: " << mzml.get_number_spectra() << std::endl;
  sc::MS_SPECTRA_HEADERS hd;
  hd = mzml.get_spectra_headers();
  int number = hd.index.size();
  std::cout << "Size of vector in headers struct: " << number << std::endl;
  std::cout << "Retention time of 10th spectrum: " << hd.rt[10] << std::endl;
  std::cout << "Number of binary arrays: " << mzml.get_number_spectra_binary_arrays() << std::endl;
  std::vector<std::vector<std::vector<double>>> spectra;
  std::vector<int> indices = {10, 15};
  spectra = mzml.get_spectra(indices);
  std::cout << "Number of extracted spectra: " << spectra.size() << std::endl;
  std::cout << "Number of traces in the first extracted spectrum: " << spectra[0][0].size() << std::endl;
  std::cout << std::endl;
};

void test_extract_chromatograms_mzml(const std::string& file) {
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Test Chromatograms mzML file:" << std::endl;
  std::cout << std::endl;
  sc::MZML mzml(file);
  std::cout << "Root name: " << mzml.name << std::endl;
  std::cout << "Number of chromatograms: " << mzml.get_number_chromatograms() << std::endl;
  sc::MS_CHROMATOGRAMS_HEADERS ch;
  ch = mzml.get_chromatograms_headers();
  int number_chroms = ch.index.size();
  std::cout << "Size of vector in headers chroms struct: " << number_chroms << std::endl;
  std::cout << "Polarity of 5th chrom: " << ch.polarity[5] << std::endl;
  std::vector<std::vector<std::vector<double>>> chroms;
  std::vector<int> indices = {1, 5, 6};
  chroms = mzml.get_chromatograms(indices);
  std::cout << "Number of extracted chroms: " << chroms.size() << std::endl;
  std::cout << "Number of variables in 1st chromatogram: " << chroms[0].size() << std::endl;
  std::cout << "Number of variables in 6th chromatogram: " << chroms[2].size() << std::endl;
  std::cout << "Number of traces in the first extracted chrom: " << chroms[0][0].size() << std::endl;
  std::cout << std::endl;
};

void test_extract_spectra_mzxml(const std::string& file) {
  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "Test Extract Spectra mzXML file:" << std::endl;
  std::cout << std::endl;
  sc::MZXML mzxml(file);
  std::cout << "Root name: " << mzxml.name << std::endl;
  std::cout << "Number of spectra: " << mzxml.get_number_spectra() << std::endl;
  sc::MS_SPECTRA_HEADERS hd;
  hd = mzxml.get_spectra_headers();
  int number = hd.index.size();
  std::cout << "Size of vector in headers struct: " << number << std::endl;
  std::cout << "Retention time of 10th spectrum: " << hd.rt[10] << std::endl;
  std::cout << "Number of binary arrays: " << mzxml.get_number_spectra_binary_arrays() << std::endl;
  std::vector<std::vector<std::vector<double>>> spectra;
  std::vector<int> indices = {10, 15};
  spectra = mzxml.get_spectra(indices);
  std::cout << "Number of extracted spectra: " << spectra.size() << std::endl;
  std::cout << "Number of traces in the first extracted spectrum: " << spectra[0][0].size() << std::endl;
  std::cout << std::endl;
};
