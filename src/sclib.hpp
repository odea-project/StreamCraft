#ifndef SCLIB_HPP
#define SCLIB_HPP

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <tuple>
#include <numeric>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <zlib.h>
#include <omp.h>

#define PUGIXML_HEADER_ONLY
#include "../external/pugixml-1.14/src/pugixml.hpp"

/// @brief Assets to read and write XML based analytical files
namespace sc {

  void hello();

  inline namespace utils {

    std::string encode_little_endian(const std::vector<double>& input, const int& precision);

    std::vector<double> decode_little_endian(const std::string& str, const int& precision);

    std::string compress_zlib(const std::string& str);

    std::string decompress_zlib(const std::string& compressed_string);

    std::string encode_base64(const std::string& str);

    std::string decode_base64(const std::string& encoded_string);

  }; // namespace utils



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

    class BINARY_METADATA {

      public:
        int index;
        std::string precision_name;
        std::string precision_accession;
        int precision_int;
        std::string precision_type;
        std::string compression;
        bool compressed;
        std::string data_name;
        std::string data_accession;
        std::string data_value;
        std::string data_unit;
        std::string data_name_short;

        void print() {
          std::cout << std::endl;
          std::cout << "Index:                     " << index << std::endl;
          std::cout << "Precision original string: " << precision_name << std::endl;
          std::cout << "Precision accession:       " << precision_accession << std::endl;
          std::cout << "Precision:                 " << precision_int << std::endl;
          std::cout << "Precision type:            " << precision_type << std::endl;
          std::cout << "Compression:               " << compression << std::endl;
          std::cout << "Data name:                 " << data_name << std::endl;
          std::cout << "Data accession:            " << data_accession << std::endl;
          std::cout << "Data value:                " << data_value << std::endl;
          std::cout << "Data unit:                 " << data_unit << std::endl;
          std::cout << "Data short name:           " << data_name_short << std::endl;
          std::cout << std::endl;
        };
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

        std::vector<std::string> possible_accessions_binary_data = {
          "MS:1000514", "MS:1000515", "MS:1000516", "MS:1000517",
          "MS:1000595", "MS:1000617", "MS:1000786", "MS:1000820",
          "MS:1000821", "MS:1000822", "MS:1002478", "MS:1002529",
          "MS:1002530", "MS:1002742", "MS:1002743", "MS:1002744",
          "MS:1002745", "MS:1002893", "MS:1003143", "MS:1003157",
          "MS:1003158"
        };

        std::vector<std::string> possible_short_name_binary_data = {
          "mz", "intensity", "charge", "sn",
          "time", "wavelength", "other", "flowrate",
          "pressure", "temperature", "mean_charge", "resolution",
          "baseline", "noise", "sampled_noise_mz", "sampled_noise_intensity",
          "sampled_noise_baseline", "ion_mobility", "mass", "quadrupole_position_lower_bound_mz",
          "quadrupole_position_upper_bound_mz"
        };

        int number_spectra;

        int number_chromatograms;

        int number_spectra_binary_arrays;

        SPECTRA_HEADERS extract_spectra_headers(const std::vector<int>& idxs);

        std::vector<BINARY_METADATA> spectra_binary_metadata;

        BINARY_METADATA extract_binary_metadata(const pugi::xml_node& bin);

        void extract_spectra_binary_metadata(const pugi::xml_node& first_node);

        std::vector<std::vector<double>> extract_spectrum(const pugi::xml_node& spectrum_node);

        std::vector<std::vector<std::vector<double>>> extract_spectra(const std::vector<int>& idxs);

        CHROMATOGRAMS_HEADERS extract_chrom_headers(const std::vector<int>& idxs);

        std::vector<std::vector<double>> extract_chromatogram(const pugi::xml_node& chrom_node);

        std::vector<std::vector<std::vector<double>>> extract_chromatograms(const std::vector<int>& idxs);

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
            extract_spectra_binary_metadata(spec_list.first_child());
          }

          pugi::xml_node chrom_list = xps_run.node().child("chromatogramList");

          number_chromatograms = chrom_list.attribute("count").as_int();
        }

        const pugi::xml_document& get_document() {
          return doc;
        };

        const pugi::xml_node& get_root() {
          return root;
        };

        const std::string& get_root_name() {
          return name;
        };

        const int& get_number_spectra() {
          return number_spectra;
        };

        const int& get_number_chromatograms() {
          return number_chromatograms;
        };

        const int& get_number_spectra_binary_arrays() {
          return number_spectra_binary_arrays;
        };

        std::vector<BINARY_METADATA> get_spectra_binary_metadata() {
          return spectra_binary_metadata;
        };

        std::vector<std::string> get_spectra_binary_short_names() {
          std::vector<std::string> names(number_spectra_binary_arrays);
          if (number_spectra_binary_arrays > 0) {
            for (int i = 0; i < number_spectra_binary_arrays; ++i) {
              names[i] = spectra_binary_metadata[i].data_name_short;
            }
          }

          return names;
        };

        void print_spectra_binary_metadata() {

          if (number_spectra_binary_arrays > 0) {
            for (int i = 0; i < number_spectra_binary_arrays; ++i) {
              spectra_binary_metadata[i].print();
            }
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
  }; // namespace mzml


  inline namespace animl {

    // Forward declaration of EXPSTEP
    class EXPSTEP;
    class RESULT;
    class SERIES;

    std::tuple<std::string, int> extract_encoding_parameters(const std::string& str);

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
        std::string dependency;
        std::string seriesID;
        std::string seriesType;
        std::string plotScale;
        std::string ValueSetName;
        std::vector<double> EncodedValueSet;
        std::vector<double> AutoIncrementedValueSet;
        std::vector<double> IndividualValueSet;
        UNIT valueUnit;
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
        int SeriesSetLength;
        std::string SeriesSetName;
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



    /// @brief AnIMl file representation.
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

  }; // animl

}; // namespace sc

#endif // SCLIB_HPP
