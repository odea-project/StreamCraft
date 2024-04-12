#include "sclib.hpp"
#include <iostream>

void sc::welcome() {
  std::cout << std::endl;
  // make a welcome message with Stream in dark blue and Craft is red but glue the words together as StreamCraft
  std::cout << "  \033[1;34mStream\033[0m\033[1;31mCraft\033[0m" << std::endl;
  std::cout << std::endl;
};

sc::MassSpecAnalysis::MassSpecAnalysis(const std::string& file) {
  file_path = file;
  
  file_dir = file.substr(0, file.find_last_of("/\\") + 1);
  if (file_dir.back() == '/') file_dir.pop_back();

  file_name = file.substr(file.find_last_of("/\\") + 1);
  
  file_extension = file_name.substr(file_name.find_last_of(".") + 1);
  
  file_name = file_name.substr(0, file_name.find_last_of("."));

  if (std::find(possible_formats.begin(), possible_formats.end(), file_extension) == possible_formats.end()) {
    std::cerr << "Invalid file extension for MassSpecAnalysis!" << std::endl;
  }

  format_case = std::distance(possible_formats.begin(), std::find(possible_formats.begin(), possible_formats.end(), file_extension));

  switch (format_case) {

    case 0: {
      ms = std::make_unique<MassSpecFile<mzml::MZML>>(file);
      break;
    }

    case 1: {
      ms = std::make_unique<MassSpecFile<mzxml::MZXML>>(file);
      break;
    }
    
    default:
      break;
  }

  number_spectra = ms->get_number_spectra();
  number_chromatograms = ms->get_number_chromatograms();
  number_spectra_binary_arrays = ms->get_number_spectra_binary_arrays();
  first_spectra_headers = ms->get_first_spectra_headers();
};

void sc::MassSpecAnalysis::print() {
  std::cout << "MassSpecAnalysis (" << possible_formats[format_case] << ")" << std::endl;
  std::cout << "  File:                      " << file_path << std::endl;
  std::cout << "  Number of spectra:         " << number_spectra << std::endl;
  std::cout << "  Spectra mode (first):      " << first_spectra_headers.mode[0] << std::endl;
  std::cout << "  Number of binnary arrays:  " << number_spectra_binary_arrays << std::endl;
  std::cout << "  Number of chromatograms:   " << number_chromatograms << std::endl;
  std::cout << std::endl;
};
