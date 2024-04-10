#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <string>
#include <vector>

namespace utils {

  std::string encode_little_endian(const std::vector<double>& input, const int& precision);

  std::vector<double> decode_little_endian(const std::string& str, const int& precision);

  std::string compress_zlib(const std::string& str);

  std::string decompress_zlib(const std::string& compressed_string);

  std::string encode_base64(const std::string& str);

  std::string decode_base64(const std::string& encoded_string);

  void test_encoding_decoding_little_endian(const std::vector<double>& input, const int& precision) {

      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "Encoding and Decoding Little Endian (" << precision * 8 << "-bit) Test" << std::endl;
      std::cout << std::endl;

      std::cout << "Input vector: ";
      for (double i : input) std::cout << i << " ";
      std::cout << std::endl;
      std::string result = encode_little_endian(input, precision);
      std::cout << "Encoded: " << result << std::endl;
      result = compress_zlib(result);
      std::cout << "Compressed: " << "Not printed!" << std::endl;
      result = encode_base64(result);
      std::cout << "Encoded_base64: " << result << std::endl;

      std::cout << std::endl;
      result = decode_base64(result);
      std::cout << "Decoded_base64: " << "Not printed!" << std::endl;
      result = decompress_zlib(result);
      std::cout << "Decompressed: " << result << std::endl;
      std::vector<double> result_back = decode_little_endian(result, precision);
      std::cout << "Decoded: ";
      for (double i : result_back) std::cout << i << " ";
      std::cout << std::endl;
      bool check = input == result_back;

      std::cout << std::endl;
      std::cout << "When 1 the result is equal to input: " << check << std::endl;
      std::cout << std::endl;
    };

}; // namespace utils

#endif // UTILS_HPP

#if defined(UTILS_HEADER_ONLY) && !defined(UTILS_SOURCE)
#	define UTILS_SOURCE "utils.cpp"
#	include UTILS_SOURCE
#endif