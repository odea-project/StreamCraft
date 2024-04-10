#ifndef MZML_HPP
#define MZML_HPP

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

#define PUGIXML_HEADER_ONLY
#include "../external/pugixml-1.14/src/pugixml.hpp"

#define UTILS_HEADER_ONLY
#include "utils.hpp"

namespace mzml {

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

  class MZML {

    private:

      std::string file_path;

      std::string file_dir;

      std::string file_name;

      std::string file_extension;

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

      SPECTRA_HEADERS first_spectra_headers;

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

        file_dir = file.substr(0, file.find_last_of("/\\") + 1);

        file_name = file.substr(file.find_last_of("/\\") + 1);
        
        file_extension = file_name.substr(file_name.find_last_of(".") + 1);
        
        file_name = file_name.substr(0, file_name.find_last_of("."));

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

        std::vector<int> sp0 = {0};

        first_spectra_headers = extract_spectra_headers(sp0);

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

      void print() {
        std::cout << name << std::endl;
        std::cout << std::endl;
        std::cout << " File:                      " << file_path << std::endl;
        std::cout << std::endl;
        std::cout << " Number of spectra:         " << number_spectra << std::endl;
        std::cout << " Spectra mode (first):      " << first_spectra_headers.spec_mode[0] << std::endl;
        std::cout << " Number of binnary arrays:  " << number_spectra_binary_arrays << std::endl;
        std::cout << " Name of binary arrays:     ";
        if (number_spectra_binary_arrays > 0) {
          for (int i = 0; i < number_spectra_binary_arrays; ++i) {
            std::cout << spectra_binary_metadata[i].data_name_short;
            if (i < (number_spectra_binary_arrays -1)) {
              std::cout << ", ";
            }
          }
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << " Number of chromatograms:   " << number_chromatograms << std::endl;
        std::cout << std::endl;
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

      void write_spectra(
        std::vector<std::vector<std::vector<double>>> spectra = {},
        std::vector<std::string> names = {},
        std::string mode = "centroid",
        bool compress = true,
        bool save = false,
        std::string save_suf = "_cent"
      );

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

    void test_extract_spectra_mzml(const std::string& file) {
      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "Test Extract Spectra mzML file:" << std::endl;
      std::cout << std::endl;

      mzml::MZML mzml(file);

      std::cout << "Root name: " << mzml.get_root_name() << std::endl;

      std::cout << "Number of spectra: " << mzml.get_number_spectra() << std::endl;

      mzml::SPECTRA_HEADERS hd;

      hd = mzml.get_spectra_headers();

      int number = hd.spec_index.size();

      std::cout << "Size of vector in headers struct: " << number << std::endl;

      std::cout << "Retention time of 10th spectrum: " << hd.scan_rt[10] << std::endl;

      std::cout << "Number of binary arrays: " << mzml.get_number_spectra_binary_arrays() << std::endl;

      std::vector<mzml::BINARY_METADATA> mtd = mzml.get_spectra_binary_metadata();

      std::cout << "Name of first binary array: " << mtd[1].data_name << std::endl;

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

      mzml::MZML mzml(file);

      std::cout << "Root name: " << mzml.get_root_name() << std::endl;

      std::cout << "Number of chromatograms: " << mzml.get_number_chromatograms() << std::endl;

      mzml::CHROMATOGRAMS_HEADERS ch;

      ch = mzml.get_chromatograms_headers();

      int number_chroms = ch.chrom_index.size();

      std::cout << "Size of vector in headers chroms struct: " << number_chroms << std::endl;

      std::cout << "Polarity of 5th chrom: " << ch.chrom_polarity[5] << std::endl;

      std::vector<std::vector<std::vector<double>>> chroms;

      std::vector<int> indices = {1, 5, 6};

      chroms = mzml.get_chromatograms(indices);

      std::cout << "Number of extracted chroms: " << chroms.size() << std::endl;

      std::cout << "Number of variables in 1st chromatogram: " << chroms[0].size() << std::endl;

      std::cout << "Number of variables in 6th chromatogram: " << chroms[2].size() << std::endl;

      std::cout << "Number of traces in the first extracted chrom: " << chroms[0][0].size() << std::endl;

      std::cout << std::endl;
    };

  }; // namespace mzml

#endif // MZML_HPP

#if defined(MZML_HEADER_ONLY) && !defined(MZML_SOURCE)
#	define MZML_SOURCE "mzml.cpp"
#	include MZML_SOURCE
#endif
