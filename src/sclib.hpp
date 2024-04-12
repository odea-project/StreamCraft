#ifndef SCLIB_HPP
#define SCLIB_HPP

#include <vector>
#include <string>

#define PUGIXML_HEADER_ONLY
#include "../external/pugixml-1.14/src/pugixml.hpp"

#define UTILS_HEADER_ONLY
#include "utils.hpp"

#define MZML_HEADER_ONLY
#include "mzml.hpp"

namespace sc {

  void welcome();

  class VirtualMassSpecFile {
    public:
      virtual ~VirtualMassSpecFile() = default;

      virtual int get_number_spectra() = 0;
      virtual int get_number_chromatograms() = 0;
      virtual int get_number_spectra_binary_arrays() = 0;
      virtual utils::MS_SPECTRA_HEADERS get_first_spectra_headers() = 0;
      virtual utils::MS_SPECTRA_HEADERS get_spectra_headers() = 0;
      // virtual utils::MS_CHROMATOGRAMS_HEADERS get_chromatograms_headers() = 0;
      // virtual std::vector<std::vector<std::vector<double>>> get_spectra() = 0;
      // virtual std::vector<std::vector<std::vector<double>>> get_chromatograms() = 0;
      // virtual std::vector<int> get_spectra_index() = 0;
      // virtual std::vector<int> get_spectra_scan_number() = 0;
      // virtual std::vector<int> get_spectra_array_length() = 0;
      // virtual std::vector<int> get_spectra_level() = 0;
      // virtual std::vector<std::string> get_spectra_mode() = 0;
      // virtual std::vector<std::string> get_spectra_polarity() = 0;
      // virtual std::vector<double> get_spectra_lowmz() = 0;
      // virtual std::vector<double> get_spectra_highmz() = 0;
      // virtual std::vector<double> get_spectra_bpmz() = 0;
      // virtual std::vector<double> get_spectra_bpint() = 0;
      // virtual std::vector<double> get_spectra_tic() = 0;
      // virtual std::vector<double> get_spectra_rt() = 0;
      // virtual std::vector<double> get_spectra_drift() = 0;
      // virtual std::vector<int> get_spectra_precursor_scan() = 0;
      // virtual std::vector<double> get_spectra_precursor_mz() = 0;
      // virtual std::vector<double> get_spectra_precursor_window_mz() = 0;
      // virtual std::vector<double> get_spectra_precursor_window_mzlow() = 0;
      // virtual std::vector<double> get_spectra_precursor_window_mzhigh() = 0;
      // virtual std::vector<double> get_spectra_collision_energy() = 0;  
  };

  template <typename T>
  class MassSpecFile  : public VirtualMassSpecFile {
    public:
      MassSpecFile(const std::string& file) : ms(file) {}

      int get_number_spectra() override { return ms.number_spectra; }

      int get_number_chromatograms() override { return ms.number_chromatograms; }

      int get_number_spectra_binary_arrays() { return ms.number_spectra_binary_arrays; }

      utils::MS_SPECTRA_HEADERS get_first_spectra_headers() override { return ms.first_spectra_headers; }

      utils::MS_SPECTRA_HEADERS get_spectra_headers() override { return ms.get_spectra_headers(); }

      T& open() { return ms; };

    private:
      T ms;
  };

  class MassSpecAnalysis {

    private:
    
      std::vector<std::string> possible_formats = { "mzML", "mzXML", "animl" };

    public:

      std::string file_path;

      std::string file_dir;

      std::string file_name;

      std::string file_extension;

      int format_case;

      std::unique_ptr<VirtualMassSpecFile> ms;

      int number_spectra;

      int number_chromatograms;

      int number_spectra_binary_arrays;

      utils::MS_SPECTRA_HEADERS first_spectra_headers;

      MassSpecAnalysis(const std::string& file);

      void print();
  };

}; // namespace sc

#endif // SCLIB_HPP

#if defined(SC_HEADER_ONLY) && !defined(SC_SOURCE)
#	define SC_SOURCE "sclib.cpp"
#	include SC_SOURCE
#endif
