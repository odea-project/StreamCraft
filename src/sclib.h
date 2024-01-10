#ifndef SCLIB_H
#define SCLIB_H

#include <iostream>
#include <vector>
#include <string>
#include <numeric>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <zlib.h>

#define PUGIXML_HEADER_ONLY
#include "pugixml-1.14/src/pugixml.hpp"

/// @brief Assets to read and write XML based analytical files
namespace sc {

  void hello();

  inline namespace utils {

    std::string encode_little_endian(const std::vector<double>& input, const int& precision);

    std::vector<double> decode_little_endian(const std::string& str, const int& precision);

    // std::string encode_big_endian(const std::vector<double>& input);

    // std::vector<double> decode_big_endian(const std::string& str, const int& precision);

    std::string compress_zlib(const std::string& str);

    std::string decompress_zlib(const std::string& compressed_string);

    std::string encode_base64(const std::string& str);

    std::string decode_base64(const std::string& encoded_string);

  } // namespace utils



  /// @brief Class representing a generic XML file.
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



  inline namespace mzml {

    struct SPECTRA_HEADERS {
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

    struct BINARY_METADATA {
      int index;
      int precision;
      std::string compression;
      std::string type;
      std::string name;
    };

    struct CHROMATOGRAMS_HEADERS {
      std::vector<int> chrom_index;
      std::vector<std::string> chrom_id;
      std::vector<int> chrom_array_length;
      std::vector<std::string> chrom_polarity;
      std::vector<double> precursor_mz;
      std::vector<std::string> activation_type;
      std::vector<double> activation_ce;
      std::vector<double> product_mz;
    };



    /// @brief Class representing an mzML file.
    class MZML {

      private:

        std::string file_path;

        pugi::xml_document doc;

        pugi::xml_parse_result loading_result;

        pugi::xml_node root;

        std::string format;

        std::string name;

        int number_spectra;

        SPECTRA_HEADERS spectra_headers;

        SPECTRA_HEADERS extract_spectra_headers(const std::vector<int>& idxs);

        int spectra_binary_arrays_number;

        std::vector<BINARY_METADATA> spectra_binary_metadata;

        BINARY_METADATA extract_binary_metadata(const pugi::xml_node& bin);

        void get_spectra_binary_metadata(const pugi::xml_node& first_node);

        std::vector<std::vector<double>> extract_spectrum(const pugi::xml_node& spectrum_node);

        std::vector<std::vector<std::vector<double>>> extract_spectra(const std::vector<int>& idxs);

        CHROMATOGRAMS_HEADERS extract_chrom_headers(const std::vector<int>& idxs);

        std::vector<std::vector<double>> extract_chromatogram(const pugi::xml_node& chrom_node);

        std::vector<std::vector<std::vector<double>>> extract_chromatograms(const std::vector<int>& idxs);

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
            get_spectra_binary_metadata(spec_list.first_child());
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

        std::vector<BINARY_METADATA> get_spectra_binary_metadata() {
          return spectra_binary_metadata;
        };

        void load_headers() {

          if (number_spectra == 0) {
            std::cerr << "Warning: There are no spectra in the mzML file!" << std::endl;

          } else {
            std::vector<int> all_indices(number_spectra);
            std::iota(all_indices.begin(), all_indices.end(), 0);
            spectra_headers = extract_spectra_headers(all_indices); //root,
          }

        };

        SPECTRA_HEADERS get_spectra_headers(const std::vector<int>& indices = {}) {

          SPECTRA_HEADERS hd;

          if (number_spectra == 0) {
            std::cerr << "Warning: There are no spectra in the mzML file!" << std::endl;

          } else {

            if (indices.size() == 0) {
              std::vector<int> all_indices(number_spectra);
              std::iota(all_indices.begin(), all_indices.end(), 0);
              hd = extract_spectra_headers(all_indices);

            } else {
              hd = extract_spectra_headers(indices);
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
              sp = extract_spectra(all_indices);

            } else {
              sp = extract_spectra(indices);
            }
          }

          return sp;

        };

        CHROMATOGRAMS_HEADERS get_chromatograms_headers(const std::vector<int>& indices = {}) {

          CHROMATOGRAMS_HEADERS ch;

          if (number_chromatograms == 0) {
            std::cerr << "Warning: There are no chromatograms in the mzML file!" << std::endl;

          } else {

            if (indices.size() == 0) {
              std::vector<int> all_indices(number_chromatograms);
              std::iota(all_indices.begin(), all_indices.end(), 0);
              ch = extract_chrom_headers(all_indices);

            } else {
              ch = extract_chrom_headers(indices);
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
              chr = extract_chromatograms(all_indices);

            } else {
              chr = extract_chromatograms(indices);
            }
          }

          return chr;

        };
    };
  } // namespace mzml


  inline namespace animl {

    // Forward declaration of EXPSTEP
    class EXPSTEP;
    class RESULT;
    class SERIES;

    int extract_set_size(const pugi::xml_node& node, const std::string& name);

    std::vector<EXPSTEP> extract_experiment_step_by_indices(const pugi::xml_node& node, const std::vector<int>& idxs);

    std::vector<EXPSTEP> extract_experiment_step_by_attr(const pugi::xml_node& node, const std::string& attr, const std::vector<std::string>& names);

    std::vector<EXPSTEP> extract_experiment_step_by_child_attr(const pugi::xml_node& node, const std::string& child_name, const std::string& attr, const std::vector<std::string>& names);

    class TAG {
      public:
        std::string name;
        std::string value;
    };



    class UNIT {
      public:
        std::string label;
        std::string quantity;
        double factor;
        double exponent;
    };



    class SAMPLE {
      public:
        std::string name;
        std::string sampleID;
        std::vector<TAG> TagSet;
    };



    class PARAMETER {
      public:
        std::string name;
        std::string id;
        std::string type;
        unsigned value;
        UNIT value_unit;
    };



    class SERIES {
      public:
        std::string name;
        // std::string dependency;
        // std::string seriesID;
        // std::string type;
        // std::vector<unsigned> ValueSet;
        // UNIT valueUnit;
        void extract(const pugi::xml_node& node);
    };



    class CATEGORY {
      public:
        std::vector<PARAMETER> ParameterSet;
        std::vector<SERIES> SeriesSet;
        std::vector<CATEGORY> CategorySet;
    };



    class RESULT {
      public:
        std::string name;
        std::vector<SERIES> SeriesSet;
        std::vector<EXPSTEP> ExpStepSet;
        void extract(const pugi::xml_node& node);
    };



    class EXPSTEP {
      public:
        std::string name;
        std::string expID;
        std::string technique_name;
        std::string technique_uri;
        std::vector<TAG> TagSet;
        std::vector<RESULT> ResultSet;
        void extract(const pugi::xml_node& node);
    };



    /// @brief Class representing an AnIMl file.
    class ANIML {

      private:

        std::string file_path;

        pugi::xml_document doc;

        pugi::xml_parse_result loading_result;

        pugi::xml_node root;

        std::string format;

        std::string name;

        std::vector<SAMPLE> extract_samples_by_indices(const std::vector<int>& idxs);

        std::vector<SAMPLE> extract_samples_by_attr(const std::string& attr, const std::vector<std::string>& names);

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

        int get_number_samples() {
          return extract_set_size(root, "SampleSet");
        };

        int get_number_experiment_steps() {
          return extract_set_size(root, "ExperimentStepSet");
        };

        std::vector<SAMPLE> get_samples(const std::vector<int>& indices = {},
                                              const std::vector<std::string>& names = {},
                                              const std::vector<std::string>& sampleID = {}) {

          std::vector<sc::SAMPLE> samples;

          int number_samples = get_number_samples();

          if (number_samples == 0) {
            std::cerr << "Warning: No samples to return!" << std::endl;
            return samples;
          }

          if (indices.size() != 0) {
            samples = extract_samples_by_indices(indices);

          } else if (names.size() != 0) {
            samples = extract_samples_by_attr("name", names);

          } else if (sampleID.size() != 0) {
            samples = extract_samples_by_attr("sampleID", sampleID);

          } else {
            std::vector<int> idxs(number_samples);
            std::iota(idxs.begin(), idxs.end(), 0);
            samples = extract_samples_by_indices(idxs);
          }

          return samples;
        };

        std::vector<EXPSTEP> get_experiment_steps(const std::vector<int>& indices = {},
                                                  const std::vector<std::string>& names = {},
                                                  const std::vector<std::string>& techniques = {},
                                                  const std::vector<std::string>& experimentStepIDs = {}) {

          std::vector<EXPSTEP> exps;

          int number_exps = get_number_experiment_steps();

          if (number_exps == 0) {
            std::cerr << "Warning: No samples to return!" << std::endl;
            return exps;
          }

          if (indices.size() != 0) {
            exps = extract_experiment_step_by_indices(root, indices);

          } else if (names.size() != 0) {
            exps = extract_experiment_step_by_attr(root, "name", names);

          } else if (techniques.size() != 0) {
            exps = extract_experiment_step_by_child_attr(root, "Technique", "name", techniques);


          } else if (experimentStepIDs.size() != 0) {
            exps = extract_experiment_step_by_attr(root, "experimentStepID", experimentStepIDs);

          } else {
            std::vector<int> idxs(number_exps);
            std::iota(idxs.begin(), idxs.end(), 0);
            exps = extract_experiment_step_by_indices(root, idxs);
          }

          return exps;
        };
    };

  } // animl

} // namespace sc

/// @brief Test functions for the StreamCraft
namespace tests {

  void test_reading_generic_xml(const std::string& file);

  void test_encoding_decoding_little_endian(const std::vector<double>& input, const int& precision);

  void test_extract_spectra_mzml(const std::string& file);

  void test_extract_chromatograms_mzml(const std::string& file);

} // namespace tests

#endif
