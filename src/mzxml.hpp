#ifndef MZXML_HPP
#define MZXML_HPP

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

#define PUGIXML_HEADER_ONLY
#include "../external/pugixml-1.14/src/pugixml.hpp"

#define UTILS_HEADER_ONLY
#include "utils.hpp"

namespace mzxml {

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
      int precision;
      std::string compression;
      bool compressed;
      std::string byte_order;

      void print() {
        std::cout << std::endl;
        std::cout << "Precision:                 " << precision << std::endl;
        std::cout << "Compression:               " << compression << std::endl;
        std::cout << "Byte order:           " << byte_order << std::endl;
        std::cout << std::endl;
      };
  };

  class MZXML {

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

      int number_spectra;

      BINARY_METADATA binary_metadata;

      void extract_binary_metadata(const pugi::xml_node& first_node);

      std::vector<pugi::xml_node> link_vector_spectra_nodes();

      int extract_spec_index(const pugi::xml_node& spec);
      std::string extract_spec_id(const pugi::xml_node& spec);
      int extract_spec_scan(const pugi::xml_node& spec);
      // int extract_spec_array_length(const pugi::xml_node& spec);
      // int extract_spec_level(const pugi::xml_node& spec);
      // std::string extract_spec_mode(const pugi::xml_node& spec);
      // std::string extract_spec_polarity(const pugi::xml_node& spec);
      // double extract_spec_lowmz(const pugi::xml_node& spec);
      // double extract_spec_highmz(const pugi::xml_node& spec);
      // double extract_spec_bpmz(const pugi::xml_node& spec);
      // double extract_spec_bpint(const pugi::xml_node& spec);
      // double extract_spec_tic(const pugi::xml_node& spec);
      // std::string extract_spec_title(const pugi::xml_node& spec);
      // double extract_scan_rt(const pugi::xml_node& spec);
      // double extract_scan_drift(const pugi::xml_node& spec);
      // std::string extract_scan_filter_string(const pugi::xml_node& spec);
      // int extract_scan_config(const pugi::xml_node& spec);
      // double extract_scan_injection_ion_time(const pugi::xml_node& spec);
      // int extract_precursor_scan(const pugi::xml_node& spec);
      // double extract_window_mz(const pugi::xml_node& spec);
      // double extract_window_mzlow(const pugi::xml_node& spec);
      // double extract_window_mzhigh(const pugi::xml_node& spec);
      // double extract_ion_mz(const pugi::xml_node& spec);
      // double extract_ion_intensity(const pugi::xml_node& spec);
      // int extract_ion_charge(const pugi::xml_node& spec);
      // std::string extract_activation_type(const pugi::xml_node& spec);
      // double extract_activation_ce(const pugi::xml_node& spec);

      SPECTRA_HEADERS extract_spectra_headers(const std::vector<int>& idxs);

    public:

      MZXML(const std::string& file);

      const pugi::xml_document& get_document() {return doc;};
      const pugi::xml_node& get_root() {return root;};
      const std::string& get_root_name() {return name;};
      const std::string& get_file_path() {return file_path;};
      const std::string& get_file_dir() {return file_dir;};
      const std::string& get_file_name() {return file_name;};
      const std::string& get_file_extension() {return file_extension;};
      const int& get_number_spectra() {return number_spectra;};

      SPECTRA_HEADERS get_spectra_headers(std::vector<int> indices = {});
      
      void print();
      void print_binary_metadata() {binary_metadata.print();};
    };

    

  }; // namespace mzxml

#endif // MZXML_HPP

#if defined(MZXML_HEADER_ONLY) && !defined(MZXML_SOURCE)
#	define MZXML_SOURCE "mzxml.cpp"
#	include MZXML_SOURCE
#endif