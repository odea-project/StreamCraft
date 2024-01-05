#if !defined(SCLIB_H)
#define SCLIB_H
#endif

#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <tuple>

#define PUGIXML_HEADER_ONLY
#include "pugixml-1.14/src/pugixml.hpp"

namespace sc {

  void hello();

  // // Utility Functions // //

  std::string encode_little_endian(const std::vector<double>& input, const int& precision);
  std::vector<double> decode_little_endian(const std::string& str, const int& precision);

  // std::string encode_big_endian(const std::vector<double>& input);
  // std::vector<double> decode_big_endian(const std::string& str, const int& precision);

  std::string compress_zlib(const std::string& str);
  std::string decompress_zlib(const std::string& compressed_string);

  std::string encode_base64(const std::string& str);
  std::string decode_base64(const std::string& encoded_string);



  // // Structs // //

  struct MZML_SPECTRA_HEADERS {
    std::vector<int> spec_index;
    std::vector<std::string> spec_id;
    std::vector<int> spec_scan;
    std::vector<int> spec_array_length;
    std::vector<int> spec_level;
    std::vector<std::string> spec_mode;
    std::vector<std::string> spec_polarity;
    std::vector<double> spec_lowmz;
    std::vector<double> spec_highmz;
    std::vector<double> spec_bpmz;
    std::vector<double> spec_bpint;
    std::vector<double> spec_tic;
    std::vector<std::string> spec_title;
    std::vector<double> scan_rt;
    std::vector<double> scan_drift;
    std::vector<std::string> scan_filter_string;
    std::vector<int> scan_config;
    std::vector<double> scan_injection_ion_time;
    std::vector<int> precursor_scan;
    std::vector<double> window_mz;
    std::vector<double> window_mzlow;
    std::vector<double> window_mzhigh;
    std::vector<double> ion_mz;
    std::vector<double> ion_intensity;
    std::vector<int> ion_charge;
    std::vector<std::string> activation_type;
    std::vector<double> activation_ce;
  };



  struct MZML_BINARY_METADATA {
    int index;
    int precision;
    std::string compression;
    std::string type;
    std::string name;
  };



  struct MZML_CHROMATOGRAMS_HEADERS {
    std::vector<int> chrom_index;
    std::vector<std::string> chrom_id;
    std::vector<int> chrom_array_length;
    std::vector<std::string> chrom_polarity;
    std::vector<double> precursor_mz;
    std::vector<std::string> activation_type;
    std::vector<double> activation_ce;
    std::vector<double> product_mz;
  };



  // // Classes // //

  /**
  *  Class representing a generic XML file.
  */
  class XML {

    private:

    public:

      std::string file_path;

      pugi::xml_document doc;

      pugi::xml_node root;

      pugi::xml_parse_result loading_result;

      std::string name;

      XML(const std::string& file) {

        file_path = file;

        const char* path = file.c_str();

        loading_result = doc.load_file(path, pugi::parse_default | pugi::parse_declaration | pugi::parse_pi);

        if (loading_result) {
          root = doc.document_element();

          if (!root) {
            std::cout << std::endl;
            std::cout << "Root node is empty!" << std::endl;

          } else {
            name = root.name();
          }

        } else {
          std::cout << std::endl;
          std::cout << "XML file could not be opened! " << std::endl << loading_result.description() << std::endl;
        }
      };
  };


  /**
  *  Class representing an mzML file.
  */
  class MZML {

    private:

      std::string file_path;

      pugi::xml_document doc;

      pugi::xml_parse_result loading_result;

      pugi::xml_node root;

      std::string format;

      std::string name;

      int number_spectra;

      MZML_SPECTRA_HEADERS spectra_headers;

      MZML_SPECTRA_HEADERS extract_mzml_spectra_headers(const std::vector<int>& idxs);

      int spectra_binary_arrays_number;

      std::vector<MZML_BINARY_METADATA> spectra_binary_metadata;

      MZML_BINARY_METADATA extract_mzml_binary_metadata(const pugi::xml_node& bin);

      void get_mzml_spectra_binary_metadata(const pugi::xml_node& first_node);

      std::vector<std::vector<double>> extract_mzml_spectrum(const pugi::xml_node& spectrum_node);

      std::vector<std::vector<std::vector<double>>> extract_mzml_spectra(const std::vector<int>& idxs);

      MZML_CHROMATOGRAMS_HEADERS extract_mzml_chrom_headers(const std::vector<int>& idxs);

      std::vector<std::vector<double>> extract_mzml_chromatogram(const pugi::xml_node& chrom_node);

      std::vector<std::vector<std::vector<double>>> extract_mzml_chromatograms(const std::vector<int>& idxs);

      int number_chromatograms;

    public:

      MZML(const std::string& file) {

        file_path = file;

        const char* path = file.c_str();

        loading_result = doc.load_file(path, pugi::parse_default | pugi::parse_declaration | pugi::parse_pi);

        if (loading_result) {
          root = doc.document_element();

          if (!root) {
            std::cerr << "Warning: Root element is empty!" << std::endl;

          } else {
            format = root.name();

            if ("indexedmzML" == format) {
              format = "mzML";

            } else {
              std::cerr << "Warning: Root element must be indexedmzML!" << std::endl;
            }
          }

        } else {
          std::cerr << "Warning: mzML file could not be opened!" << std::endl << loading_result.description() << std::endl;
        }

        if (format == "mzML") {
          root = root.first_child();
        }

        name = root.name();

        std::string search_run = "//run";

        pugi::xpath_node xps_run = root.select_node(search_run.c_str());

        pugi::xml_node spec_list = xps_run.node().child("spectrumList");

        number_spectra = spec_list.attribute("count").as_int();

        if (number_spectra > 0) {
          get_mzml_spectra_binary_metadata(spec_list.first_child());
        }

        pugi::xml_node chrom_list = xps_run.node().child("chromatogramList");

        number_chromatograms = chrom_list.attribute("count").as_int();
      }

      const std::string& get_name() {
        return name;
      };

      const pugi::xml_node& get_root() {
        return root;
      };

      const int& get_number_spectra() {
        return number_spectra;
      };

      const int& get_number_chromatograms() {
        return number_chromatograms;
      };

      const int& get_spectra_binary_arrays_number() {
        return spectra_binary_arrays_number;
      };

      std::vector<MZML_BINARY_METADATA> get_spectra_binary_metadata() {
        return spectra_binary_metadata;
      };

      void load_headers() {

        if (number_spectra == 0) {
          std::cerr << "Warning: There are no spectra in the mzML file!" << std::endl;

        } else {
          std::vector<int> all_indices(number_spectra);
          std::iota(all_indices.begin(), all_indices.end(), 0);
          spectra_headers = extract_mzml_spectra_headers(all_indices); //root,
        }

      };

      MZML_SPECTRA_HEADERS get_spectra_headers(const std::vector<int>& indices = {}) {

        MZML_SPECTRA_HEADERS hd;

        if (number_spectra == 0) {
          std::cerr << "Warning: There are no spectra in the mzML file!" << std::endl;

        } else {

          if (indices.size() == 0) {
            std::vector<int> all_indices(number_spectra);
            std::iota(all_indices.begin(), all_indices.end(), 0);
            hd = extract_mzml_spectra_headers(all_indices);

          } else {
            hd = extract_mzml_spectra_headers(indices);
          }
        }

        return hd;

      };

      std::vector<std::vector<std::vector<double>>> get_spectra(const std::vector<int>& indices = {}) {

        std::vector<std::vector<std::vector<double>>> sp;

        if (number_spectra == 0) {
          std::cerr << "Warning: There are no spectra in the mzML file!" << std::endl;

        } else {

          if (indices.size() == 0) {
            std::vector<int> all_indices(number_spectra);
            std::iota(all_indices.begin(), all_indices.end(), 0);
            sp = extract_mzml_spectra(all_indices);

          } else {
            sp = extract_mzml_spectra(indices);
          }
        }

        return sp;

      };

      MZML_CHROMATOGRAMS_HEADERS get_chromatograms_headers(const std::vector<int>& indices = {}) {

        MZML_CHROMATOGRAMS_HEADERS ch;

        if (number_chromatograms == 0) {
          std::cerr << "Warning: There are no chromatograms in the mzML file!" << std::endl;

        } else {

          if (indices.size() == 0) {
            std::vector<int> all_indices(number_chromatograms);
            std::iota(all_indices.begin(), all_indices.end(), 0);
            ch = extract_mzml_chrom_headers(all_indices);

          } else {
            ch = extract_mzml_chrom_headers(indices);
          }
        }

        return ch;

      };

      std::vector<std::vector<std::vector<double>>> get_chromatograms(const std::vector<int>& indices = {}) {

        std::vector<std::vector<std::vector<double>>> chr;

        if (number_chromatograms == 0) {
          std::cerr << "Warning: There are no chromatograms in the mzML file!" << std::endl;

        } else {

          if (indices.size() == 0) {
            std::vector<int> all_indices(number_chromatograms);
            std::iota(all_indices.begin(), all_indices.end(), 0);
            chr = extract_mzml_chromatograms(all_indices);

          } else {
            chr = extract_mzml_chromatograms(indices);
          }
        }

        return chr;

      };
  };

  /**
  *  Class representing an AnIMl file.
  */
  class ANIML {

    private:

      std::string file_path;

      pugi::xml_document doc;

      pugi::xml_parse_result loading_result;

      pugi::xml_node root;

      std::string format;

      std::string name;

    public:
      ANIML(const std::string& file) {

        file_path = file;

        const char* path = file.c_str();

        loading_result = doc.load_file(path, pugi::parse_default | pugi::parse_declaration | pugi::parse_pi);

        if (loading_result) {
          root = doc.document_element();

          if (!root) {
            std::cerr << "Warning: Root element is empty!" << std::endl;

          } else {
            format = root.name();

            if ("AnIML" != format) {
              std::cerr << "Warning: Root element must be AnIML!" << std::endl;
            }
          }

        } else {
          std::cerr << "Warning: AnIML file could not be opened!" << std::endl << loading_result.description() << std::endl;
        }

        name = root.name();

      };

      const std::string& get_name() {
        return name;
      };

      const pugi::xml_node& get_root() {
        return root;
      };

  };

}

namespace tests {

  void test_reading_generic_xml(const std::string& file);

  void test_encoding_decoding_little_endian(const std::vector<double>& input, const int& precision);

  void test_extract_spectra_mzml(const std::string& file);

  void test_extract_chromatograms_mzml(const std::string& file);

}
