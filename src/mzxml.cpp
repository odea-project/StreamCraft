#include "mzxml.hpp"
#include <omp.h>
#include <filesystem>
#include <cstring>
#include <algorithm>

mzxml::MZXML::MZXML(const std::string& file) {

  file_path = file;

  file_dir = file.substr(0, file.find_last_of("/\\") + 1);

  if (file_dir.back() == '/') file_dir.pop_back();

  file_name = file.substr(file.find_last_of("/\\") + 1);
  
  file_extension = file_name.substr(file_name.find_last_of(".") + 1);
  
  file_name = file_name.substr(0, file_name.find_last_of("."));

  const char* path = file.c_str();

  loading_result = doc.load_file(path, pugi::parse_default | pugi::parse_declaration | pugi::parse_pi);

  if (loading_result) {
    root = doc.document_element();

    if (!root) {
      std::cerr << "Root element is empty!" << std::endl;

    } else {
      format = root.name();

      if ("mzXML" == format) {
        format = "mzXML";

      } else {
        std::cerr << "Root element must be mzXML!" << std::endl;
      }
    }

  } else {
    std::cerr << "mzXML file could not be opened!" << std::endl << loading_result.description() << std::endl;
  }

  name = root.name();

  pugi::xml_node msrun = root.child("msRun");

  std::vector<int> sp0 = {0};

  number_spectra = msrun.attribute("scanCount").as_int();

  pugi::xml_node first_node = msrun.child("scan");

  if (number_spectra > 0) {
    if (first_node) extract_binary_metadata(first_node);
  }
};

void mzxml::MZXML::extract_binary_metadata(const pugi::xml_node& first_node) {

  binary_metadata.precision = first_node.child("peaks").attribute("precision").as_int();

  std::string compression = first_node.child("peaks").attribute("compressionType").as_string();

  binary_metadata.compression = compression;

  if (compression == "zlib" || compression == "zlib compression") {
    binary_metadata.compressed = true;

  } else {
    binary_metadata.compressed = false;
  }

  std::string byte_order = first_node.child("peaks").attribute("byteOrder").as_string();

  if (byte_order == "network") {
    binary_metadata.byte_order = "big_endian";

  } else {
    binary_metadata.byte_order = "little_endian";
  }
};

void mzxml::MZXML::print() {
  std::cout << name << std::endl;
  std::cout << std::endl;
  std::cout << " File:                      " << file_path << std::endl;
  std::cout << std::endl;
  std::cout << " Number of spectra:         " << number_spectra << std::endl;
  // std::cout << " Spectra mode (first):      " << first_spectra_headers.spec_mode[0] << std::endl;
  std::cout << std::endl;
};

std::vector<pugi::xml_node> mzxml::MZXML::link_vector_spectra_nodes() {

  std::vector<pugi::xml_node> spectra;

  pugi::xml_node msrun = root.child("msRun");

  if (msrun) {
    for (pugi::xml_node child = msrun.child("scan"); child; child = child.next_sibling()) {
      spectra.push_back(child);
    }

  } else {
    std::cerr << "msRun not found in the mzXML file!" << std::endl;
  }
  
  return spectra;
};

int mzxml::MZXML::extract_spec_index(const pugi::xml_node& spec) {
  return spec.attribute("num").as_int();
};

std::string mzxml::MZXML::extract_spec_id(const pugi::xml_node& spec) {
  return spec.attribute("num").as_string();
};

int mzxml::MZXML::extract_spec_scan(const pugi::xml_node& spec) {
  return spec.attribute("num").as_int();
};

mzxml::SPECTRA_HEADERS mzxml::MZXML::extract_spectra_headers(const std::vector<int>& idxs) {

  SPECTRA_HEADERS headers;

  std::vector<pugi::xml_node> spectra_nodes = link_vector_spectra_nodes();

  int n = idxs.size();

  if (n == 0) {
    std::cerr << "No indices given!" << std::endl;
    return headers;
  }

  if (spectra_nodes.size() == 0) {
    std::cerr << "No spectra found!" << std::endl;
    return headers;
  }

  headers.spec_index.resize(n);
  headers.spec_id.resize(n);
  headers.spec_scan.resize(n);
  headers.spec_array_length.resize(n);
  headers.spec_level.resize(n);
  headers.spec_mode.resize(n);
  headers.spec_polarity.resize(n);
  headers.spec_lowmz.resize(n);
  headers.spec_highmz.resize(n);
  headers.spec_bpmz.resize(n);
  headers.spec_bpint.resize(n);
  headers.spec_tic.resize(n);
  headers.spec_title.resize(n);
  headers.scan_rt.resize(n);
  headers.scan_drift.resize(n);
  headers.scan_filter_string.resize(n);
  headers.scan_config.resize(n);
  headers.scan_injection_ion_time.resize(n);
  headers.precursor_scan.resize(n);
  headers.window_mz.resize(n);
  headers.window_mzlow.resize(n);
  headers.window_mzhigh.resize(n);
  headers.ion_mz.resize(n);
  headers.ion_intensity.resize(n);
  headers.ion_charge.resize(n);
  headers.activation_type.resize(n);
  headers.activation_ce.resize(n);

  // #pragma omp parallel for
  for (int i = 0; i < n; i++) {

    const int& index = idxs[i];

    const pugi::xml_node& spec = spectra_nodes[index];

    headers.spec_index[i] = extract_spec_index(spec);

    headers.spec_id[i] = extract_spec_id(spec);

    headers.spec_scan[i] = extract_spec_scan(spec);

    // headers.spec_array_length[i] = extract_spec_array_length(spec);

    // headers.spec_level[i] = extract_spec_level(spec);

    // headers.spec_mode[i] = extract_spec_mode(spec);

    // headers.spec_polarity[i] = extract_spec_polarity(spec);

    // headers.spec_lowmz[i] = extract_spec_lowmz(spec);

    // headers.spec_highmz[i] = extract_spec_highmz(spec);

    // headers.spec_bpmz[i] = extract_spec_bpmz(spec);

    // headers.spec_bpint[i] = extract_spec_bpint(spec);

    // headers.spec_tic[i] = extract_spec_tic(spec);

    // headers.spec_title[i] = extract_spec_title(spec);

    // headers.scan_rt[i] = extract_scan_rt(spec);

    // headers.scan_drift[i] = extract_scan_drift(spec);

    // headers.scan_filter_string[i] = extract_scan_filter_string(spec);

    // headers.scan_config[i] = extract_scan_config(spec);

    // headers.scan_injection_ion_time[i] = extract_scan_injection_ion_time(spec);

    // pugi::xml_node precursor = spec.child("precursorList").child("precursor");

    // if (precursor) {

    //   headers.precursor_scan[i] = extract_precursor_scan(spec);

    //   headers.window_mz[i] = extract_window_mz(spec);

    //   headers.window_mzlow[i] = extract_window_mzlow(spec);

    //   headers.window_mzhigh[i] = extract_window_mzhigh(spec);

    //   pugi::xml_node slected_ion = precursor.child("selectedIonList").first_child();

    //   if (slected_ion) {

    //     headers.ion_mz[i] = extract_ion_mz(spec);

    //     headers.ion_intensity[i] = extract_ion_intensity(spec);

    //     headers.ion_charge[i] = extract_ion_charge(spec);

    //   }

    //   pugi::xml_node activation = precursor.child("activation");

    //   if (activation) {

    //     headers.activation_type[i] = extract_activation_type(spec);

    //     headers.activation_ce[i] = extract_activation_ce(spec);

    //   }
    // }
  } // end of i loop

  return headers;
}

mzxml::SPECTRA_HEADERS mzxml::MZXML::get_spectra_headers(std::vector<int> indices) {

  SPECTRA_HEADERS hd;

  if (number_spectra == 0) {
    std::cerr << "There are no spectra in the mzXML file!" << std::endl;
    return hd;
  } 

  if (indices.size() == 0) {
    indices.resize(number_spectra);
    std::iota(indices.begin(), indices.end(), 0);
  }

  hd = extract_spectra_headers(indices);
  
  return hd;
};
