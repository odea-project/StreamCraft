#ifndef STREAMCRAFT_LIB_HPP
#define STREAMCRAFT_LIB_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <memory>
#include "pugixml.hpp"
#include "StreamCraft_utils.hpp"
#include "StreamCraft_mzml.hpp"
#include "StreamCraft_mzxml.hpp"

namespace sc
{

  std::unique_ptr<MS_READER> create_ms_reader(const std::string &file);

  class MS_ANALYSIS
  {

  private:
    const std::vector<std::string> possible_formats = {"mzML", "mzXML", "animl"};

  public:
    std::string file_path;

    std::string file_dir;

    std::string file_name;

    std::string file_extension;

    std::string format;

    int format_case;

    std::unique_ptr<MS_READER> ms;

    MS_ANALYSIS(const std::string &file);

    int get_number_spectra() { return ms->get_number_spectra(); }
    int get_number_chromatograms() { return ms->get_number_chromatograms(); }
    int get_number_spectra_binary_arrays() { return ms->get_number_spectra_binary_arrays(); }
    std::string get_format() { return ms->get_format(); }
    std::string get_type() { return ms->get_type(); }
    std::string get_time_stamp() { return ms->get_time_stamp(); }

    std::vector<int> get_polarity() { return ms->get_polarity(); }
    std::vector<int> get_mode() { return ms->get_mode(); }
    std::vector<int> get_level() { return ms->get_level(); }
    std::vector<int> get_configuration() { return ms->get_configuration(); }
    float get_min_mz() { return ms->get_min_mz(); }
    float get_max_mz() { return ms->get_max_mz(); }
    float get_start_rt() { return ms->get_start_rt(); }
    float get_end_rt() { return ms->get_end_rt(); }
    bool has_ion_mobility() { return ms->has_ion_mobility(); }
    MS_SUMMARY get_summary() { return ms->get_summary(); }

    std::vector<int> get_spectra_index(std::vector<int> indices = {}) { return ms->get_spectra_index(indices); }
    std::vector<int> get_spectra_scan_number(std::vector<int> indices = {}) { return ms->get_spectra_scan_number(indices); }
    std::vector<int> get_spectra_array_length(std::vector<int> indices = {}) { return ms->get_spectra_array_length(indices); }
    std::vector<int> get_spectra_level(std::vector<int> indices = {}) { return ms->get_spectra_level(indices); }
    std::vector<int> get_spectra_mode(std::vector<int> indices = {}) { return ms->get_spectra_mode(indices); }
    std::vector<int> get_spectra_polarity(std::vector<int> indices = {}) { return ms->get_spectra_polarity(indices); }
    std::vector<float> get_spectra_lowmz(std::vector<int> indices = {}) { return ms->get_spectra_lowmz(indices); }
    std::vector<float> get_spectra_highmz(std::vector<int> indices = {}) { return ms->get_spectra_highmz(indices); }
    std::vector<float> get_spectra_bpmz(std::vector<int> indices = {}) { return ms->get_spectra_bpmz(indices); }
    std::vector<float> get_spectra_bpint(std::vector<int> indices = {}) { return ms->get_spectra_bpint(indices); }
    std::vector<float> get_spectra_tic(std::vector<int> indices = {}) { return ms->get_spectra_tic(indices); }
    std::vector<int> get_spectra_configuration(std::vector<int> indices = {}) { return ms->get_spectra_configuration(indices); }
    std::vector<float> get_spectra_rt(std::vector<int> indices = {}) { return ms->get_spectra_rt(indices); }
    std::vector<float> get_spectra_drift(std::vector<int> indices = {}) { return ms->get_spectra_mobility(indices); }
    std::vector<int> get_spectra_precursor_scan(std::vector<int> indices = {}) { return ms->get_spectra_precursor_scan(indices); }
    std::vector<float> get_spectra_precursor_mz(std::vector<int> indices = {}) { return ms->get_spectra_precursor_mz(indices); }
    std::vector<float> get_spectra_precursor_window_mz(std::vector<int> indices = {}) { return ms->get_spectra_precursor_window_mz(indices); }
    std::vector<float> get_spectra_precursor_window_mzlow(std::vector<int> indices = {}) { return ms->get_spectra_precursor_window_mzlow(indices); }
    std::vector<float> get_spectra_precursor_window_mzhigh(std::vector<int> indices = {}) { return ms->get_spectra_precursor_window_mzhigh(indices); }
    std::vector<float> get_spectra_collision_energy(std::vector<int> indices = {}) { return ms->get_spectra_collision_energy(indices); }
    MS_SPECTRA_HEADERS get_spectra_headers(std::vector<int> indices = {}) { return ms->get_spectra_headers(indices); }
    MS_CHROMATOGRAMS_HEADERS get_chromatograms_headers(std::vector<int> indices = {}) { return ms->get_chromatograms_headers(indices); }
    std::vector<std::vector<std::vector<float>>> get_spectra(std::vector<int> indices = {}) { return ms->get_spectra(indices); }
    std::vector<std::vector<std::vector<float>>> get_chromatograms(std::vector<int> indices = {}) { return ms->get_chromatograms(indices); }
    std::vector<std::vector<std::string>> get_software() { return ms->get_software(); }
    std::vector<std::vector<std::string>> get_hardware() { return ms->get_hardware(); }
    MS_SPECTRUM get_spectrum(const int &index) { return ms->get_spectrum(index); }
    MS_TARGETS_SPECTRA get_spectra_targets(const MS_TARGETS &targets, const sc::MS_SPECTRA_HEADERS &hd, const float &minIntLv1, const float &minIntLv2);
  };

}; // namespace sc

#endif // SCLIB_HPP
