
#define STREAMCRAFT_HEADER_ONLY
#include "StreamCraft_lib.hpp"
#include "../tests/StreamCraft_tests.hpp"

// Workaround if M_2_SQRTPI is not recognized
#ifndef M_2_SQRTPI
#define M_2_SQRTPI 1.12837916709551257390
#endif

// #include "external/qAlgorithms/include/qalgorithms_utils.h"
// #include "external/qAlgorithms/include/qalgorithms_matrix.h"
// #include "external/qAlgorithms/include/qalgorithms.h"

// #include "external/qAlgorithms/src/qalgorithms_matrix.cpp"
// #include "external/qAlgorithms/src/qalgorithms_utils.cpp"
// #include "external/qAlgorithms/src/qalgorithms.cpp"

int main() {

  // In the repository
  std::string file1 = "./excluded/example.mzML";
  std::string file2 = "./excluded/example.animl";
  std::string file3 = "./excluded/basic.xml";
  std::string file4 = "./excluded/mrm_pos.mzML";
  std::string file5 = "./excluded/mrm_neg.mzML";
  std::string file6 = "./excluded/example_strict.animl";
  std::string file7 = "./excluded/example.mzXML";
  std::string file8 = "./excluded/example_profile.mzML";
  std::string file9 = "./excluded/example_modified.mzML";

  // In the local laptop
  std::string file10 = "C:/Users/apoli/Documents/example_ms_files/tof_25000_mix1-r001.mzML";
  std::string file11 = "C:/Users/apoli/Documents/iSoft/BSA_products/BSA_7AqYf_1.mzML";

  // With IM data (large)
  std::string file12 = "D:/NTS/Project_240124_PFAS_Zweigle/mzml/05_PFAS_MIX_100_FS-r001.mzML";

  // With IM data (rick)
  std::string file13 = "./excluded/example_timsTOF_rick.mzML";
  std::string file14 = "C:/Users/apoli/Documents/example_ms_files/example_data.mzML/BRAVE_SC_QC_M_103_POS_20V_06Sep19_Fiji_ZIC-19-06-01.mzML";
  
  // waters files DIA
  std::string file16 = "C:/Users/apoli/Documents/example_ms_files/tisler/201026_targetScreening_effluent_POS_QC3.mzML";

  // test_extract_ms_analysis(file13, 10);

  // std::unique_ptr<sc::MS_READER> ms_reader = sc::create_ms_reader(file1);

  // sc::MZML ana(file14);
  // int number_of_spectra = ana.get_number_spectra();
  // std::cout << "Number of spectra: " << number_of_spectra << std::endl;
  
  // int idx = 2;

  // std::vector<int> indices = {idx};
  // sc::MS_SPECTRA_HEADERS hd = ana.get_spectra_headers(indices);
  // std::cout << "Index: " << hd.index[0] << std::endl;
  // std::cout << "Scan: " << hd.scan[0] << std::endl;
  // std::cout << "RT: " << hd.rt[0] << std::endl;
  // std::cout << "Polarity: " << hd.polarity[0] << std::endl;
  // std::cout << "Level: " << hd.level[0] << std::endl;
  // std::cout << "Mode: " << hd.mode[0] << std::endl;
  // std::cout << "Low mz: " << hd.lowmz[0] << std::endl;
  // std::cout << "High mz: " << hd.highmz[0] << std::endl;
  // std::cout << "Bp mz: " << hd.bpmz[0] << std::endl;
  // std::cout << "Bp int: " << hd.bpint[0] << std::endl;
  // std::cout << "Tic: " << hd.tic[0] << std::endl;
  // std::cout << "Configuration: " << hd.configuration[0] << std::endl;
  // std::cout << "Mobility: " << hd.mobility[0] << std::endl;
  // std::cout << "Window mz: " << hd.window_mz[0] << std::endl;
  // std::cout << "Window mz low: " << hd.window_mzlow[0] << std::endl;
  // std::cout << "Window mz high: " << hd.window_mzhigh[0] << std::endl;
  // std::cout << "Precursor mz: " << hd.precursor_mz[0] << std::endl;
  // std::cout << "Precursor intensity: " << hd.precursor_intensity[0] << std::endl;
  // std::cout << "Precursor charge: " << hd.precursor_charge[0] << std::endl;
  // std::cout << "Activation CE: " << hd.activation_ce[0] << std::endl;
  // int bin_arrays = ana.get_number_spectra_binary_arrays();
  // std::cout << "Number of binary arrays: " << bin_arrays << std::endl;

  // std::vector<sc::mzml::MZML_BINARY_METADATA> bin_mtd = ana.get_spectra_binary_metadata();
  // sc::MS_SPECTRUM spectra = ana.get_spectrum(idx);
  // std::cout << std::endl;
  // std::cout << "Index: " << spectra.index << std::endl;
  // std::cout << "Binary data: " << std::endl;
  // for (size_t i = 0; i < bin_mtd.size(); i++) {
  //   std::cout << bin_mtd[i].data_name << " / ";
  // }
  // std::cout << std::endl;
  // for (int i = 0; i < 11; i++) {
  //   for (size_t j = 0; j < spectra.binary_data.size(); j++) {
  //     std::cout << spectra.binary_data[j][i] << " / ";
  //   }
  //   std::cout << std::endl;
  // }



  

  

  // sc::MS_ANALYSIS ana(file1);
  // sc::MS_SPECTRUM sp = ana.get_spectrum(10);
  // std::cout << "Scan: " << sp.index << std::endl;
  // std::cout << "RT: " << sp.rt << std::endl;
  // std::cout << "Polarity: " << sp.polarity << std::endl;
  // std::cout << "Level: " << sp.level << std::endl;
  // std::cout << "Mode: " << sp.mode << std::endl;
  // std::cout << "MZ: " << sp.binary_data[0].size() << std::endl;
  // std::cout << "Intensity: " << sp.binary_data[1].size() << std::endl;
  // std::cout << "Drift: " << sp.drift << std::endl;
  // std::cout << "Window mz: " << sp.window_mz << std::endl;
  // std::cout << "Window high: " << sp.window_mzhigh << std::endl;
  // std::cout << "Collision energy: " << sp.activation_ce << std::endl;

  // auto start = std::chrono::high_resolution_clock::now();

  // sc::MZML ana(file12);
  // auto stop = std::chrono::high_resolution_clock::now();
  // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  // std::cout << "Opening file: " << duration.count() / 1000 << " seconds" << std::endl;

  // start = std::chrono::high_resolution_clock::now();

  // sc::MS_SPECTRA_HEADERS hd = ana.get_spectra_headers();

  // stop = std::chrono::high_resolution_clock::now();
  // duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  // std::cout << "Extract headers: " << duration.count() / 1000 << " seconds" << std::endl;

  // start = std::chrono::high_resolution_clock::now();

  // std::vector<std::vector<std::vector<double>>> sp = ana.get_spectra();

  // stop = std::chrono::high_resolution_clock::now();
  // duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  // std::cout << "Extract spectra: " << duration.count() / 1000 << " seconds" << std::endl;

  // start = std::chrono::high_resolution_clock::now();

  // sp.clear();
  // sp.shrink_to_fit();

  // stop = std::chrono::high_resolution_clock::now();
  // duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  // std::cout << "Destroy spectra: " << duration.count() / 1000 << " seconds" << std::endl;

  // std::vector<int> idx = {10};

  // std::vector<std::vector<std::vector<double>>> sp = ana.get_spectra(idx);

  // sc::MZML ana = file1;

  // std::unique_ptr<sc::VIRTUAL_MS_SPECTRUM> sp = ana.get_spectrum(100);

  // int idx = sp->extract_scan_rt();
  // std::cout << "Index: " << idx << std::endl;

  // auto start = std::chrono::high_resolution_clock::now();

  // const sc::MS_SPECTRA_HEADERS hd = ana.get_spectra_headers();
  
  // auto stop = std::chrono::high_resolution_clock::now();
  // auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
  // std::cout << "Time taken by function: " << duration.count() << " milliseconds" << std::endl;

  // auto start2 = std::chrono::high_resolution_clock::now();

  // const std::vector<std::vector<std::vector<double>>> sp = ana.get_spectra();
  
  // auto stop2 = std::chrono::high_resolution_clock::now();
  // auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(stop2 - start2);
  // std::cout << "Time taken by function: " << duration2.count() << " milliseconds" << std::endl;

  // sc::MZXML_SPECTRUM sp = ana.get_spectrum(0);
  // std::cout << "Scan: " << sp.extract_scan_rt() << std::endl;

  // sc::test_extract_spectra_mzxml(file8);

  sc::MS_TARGETS targets;
  targets.resize_all(3);
  targets.index = {0, 1, 2};
  targets.id = {"Metoprolol", "Diclofenac", "Diuron"};
  targets.level = {2, 2, 2};
  targets.polarity = {1, 1, 1};
  targets.precursor = {true, true, true}; // for DIA set precursor to false, keeping level to 2
  targets.mzmin = {268.1854,  296.0181, 233.0197};
  targets.mzmax = {268.1961,  296.0299, 233.0290};
  targets.rtmin = {905, 1245, 1150};
  targets.rtmax = {925, 1265, 1170};
  targets.mobilitymin = {0, 0, 0};
  targets.mobilitymax = {0, 0, 0};

  sc::MS_ANALYSIS ana(file7);

  sc::MS_TARGETS_SPECTRA res = ana.get_spectra_targets(targets);

  for (size_t i = 0; i < res.id.size(); i++) {
    std::cout << res.id[i] << " "
    << " " << res.level[i] << " "
    << res.polarity[i] << " "
    << res.pre_mz[i] << " "
    << res.pre_mzlow[i] << " "
    << res.pre_mzhigh[i] << " " 
    << res.rt[i] << " " 
    << res.mobility[i] << " " 
    << res.mz[i] << " " 
    << res.intensity[i] << std::endl;
  }

  // sc::MS_TARGETS targetsdda;
  //   targetsdda.resize_all(3);
  //   targetsdda.index = {0, 1, 2};
  //   targetsdda.id = {"Metoprolol", "Diclofenac", "Diuron"};
  //   targetsdda.level = {2, 2, 2};
  //   targetsdda.mzmin = {268.1854,  296.0181, 233.0197};
  //   targetsdda.mzmax = {268.1961,  296.0299, 233.0290};
  //   targetsdda.rtmin = {905, 1245, 1150};
  //   targetsdda.rtmax = {925, 1265, 1170};
  //   targetsdda.driftmin = {0, 0, 0};
  //   targetsdda.driftmax = {0, 0, 0};

  // std::vector<std::vector<std::vector<double>>> res2 = ana.get_spectra_dda_targets(targetsdda);

  // for (size_t i = 0; i < res.size(); i++) {
  //   std::cout << "Target: " << targetsdda.id[i] << std::endl;
  //   for (size_t j = 0; j < res[i][0].size(); j++) {
  //     std::cout << res2[i][0][j] << " " << res2[i][1][j] << " " << res2[i][2][j] << " " << res2[i][3][j] << " " << res2[i][4][j] << " " << res2[i][5][j] << std::endl;
  //   }
  // }


  

  





  // sc::MZXML z(file7);
  // std::vector<int> idx(10);
  // std::iota(idx.begin(), idx.end(), 0);
  // // z.print();
  // // z.print_binary_metadata();
  // sc::MS_SPECTRA_HEADERS hd = z.get_spectra_headers(idx);
  // // show all rt values in console
  // for (size_t i = 0; i < hd.index.size(); i++) {
  //   std::cout << hd.rt[i] << std::endl;
  // }
  // std::vector<std::vector<std::vector<double>>> spectra = z.get_spectra(idx);
  // // show all rt values in console
  // for (size_t i = 0; i < spectra[0][0].size(); i++) {
  //   std::cout << spectra[0][1][i] << " ";
  // }
  // std::cout << std::endl;


  // mzml::MZML z(file2);

  // std::vector<int> idx(10);
  // std::iota(idx.begin(), idx.end(), 0);

  // std::vector<double> rt = z.get_spectra_collision_energy(idx);

  // // show all rt values in console
  // for (size_t i = 0; i < rt.size(); i++) {
  //   std::cout << rt[i] << std::endl;
  // }


  // sc::MZML z(file9);

  // std::vector<int> idx(10);
  // std::iota(idx.begin(), idx.end(), 0);

  // std::vector<std::vector<std::vector<double>>> spectra;
  // // spectra list
  //     // spectrum
  //       // m/z, intensity, ...
  // spectra = z.get_spectra();
  
  // std::cout << "Number of extracted spectra: " << spectra.size() << std::endl;

  // // Add two extra binnary arays to each spectrum
  // int number_traces = 0;
  // for (size_t i = 0; i < spectra.size(); i++) {
  //   for (size_t j = 0; j < spectra[i].size(); j++) {
  //     spectra[i][j].resize(10);
  //   }
  //   number_traces = number_traces + spectra[i][0].size();
  //   spectra[i].push_back(spectra[i][0]);
  //   spectra[i].push_back(spectra[i][0]);
  // }

  // std::cout << "Number of traces: " << number_traces << std::endl;
  // std::cout << "Number of traces in 1st spectrum: " << spectra[0][0].size() << std::endl;
  // std::cout << "Number of binary entries: " << spectra[0].size() << std::endl;

  // std::vector<std::string> bin_names = {"mz", "intensity", "x1", "x2"};

  // z.write_spectra(spectra, bin_names, sc::MS_SPECTRA_MODE::CENTROID, true, true, "_cent");

  // std::cout << std::endl;

  // q::Matrix xyData(number_traces, 3);
  
  // int offset = 0;
  
  // for (size_t i = 0; i < spectra.size(); i++) {
  //   const int& scan = headers.spec_index[i];
  //   const std::vector<std::vector<double>>& sp = spectra[i];

  //   for (size_t j = 0; j < sp[0].size(); j++) {
  //     xyData(offset, 0) = sp[0][j]; // m/z
  //     xyData(offset, 1) = sp[1][j]; // intensity
  //     xyData(offset, 2) = scan; // index
  //     offset = offset + 1;
  //   }
  // }

  // std::cout << "1st mz: " << xyData(0, 0) << std::endl;
  // std::cout << "1st intensity: " << xyData(0, 1) << std::endl;
  // std::cout << "1st scan: " << xyData(0, 2) << std::endl;

  // q::tValues tVal;

  // int maxScale = 5;

  // int mode = 2;
  
  // q::Peakmodel model(maxScale);
  
  // switch (mode) {
  //   case 0:
  //     model.setMode(q::Mode::DEBUGGING);
  //     break;
      
  //   case 2:
  //     model.setMode(q::Mode::PROGRESS);
  //     break;
      
  //   default:
  //     break;
  // }
  
  // model.loadTValues(tVal);
  
  // model.addMultipleMeasurements(xyData);

  // model.findPeaks();

  // std::vector<double> cent_scan = model.getPeakProperties(q::Peakproperties::SMPLID);
  // std::vector<double> cent_mz = model.getPeakProperties(q::Peakproperties::POSITION);
  // std::vector<double> cent_intensity = model.getPeakProperties(q::Peakproperties::HEIGHT);

  // std::cout << "Number of traces after: " << cent_mz.size() << std::endl;
  // std::cout << "1st mz after: " << cent_mz[0] << std::endl;
  // std::cout << "1st intensity after: " << cent_intensity[0] << std::endl;

  // std::cout << "Var Check " << std::endl;
  // for (size_t i = 0; i < cent_scan.size(); i++) {
  //   std::cout << cent_scan[i] << " ";
  // }
  // std::cout << std::endl;



  // list_out["mz"] = model.getPeakProperties(q::Peakproperties::POSITION);
  // list_out["intensity"] = model.getPeakProperties(q::Peakproperties::HEIGHT);
  // list_out["area"] = model.getPeakProperties(q::Peakproperties::AREA);
  // list_out["DQS"] = model.getPeakProperties(q::Peakproperties::DQS);

  // std::vector<std::vector<double>> spectra2D(3);
  // spectra2D[0].resize(number_traces);
  // spectra2D[1].resize(number_traces);
  // spectra2D[2].resize(number_traces);

  // for (size_t i = 0; i < spectra.size(); i++) {
  //   int scan = headers.spec_scan[i];
  //   const std::vector<std::vector<double>>& sp = spectra[i];
  //   const std::vector<double>& mz = sp[0];
  //   const std::vector<double>& intensity = sp[1];

  //   for (size_t j = 0; j < mz.size(); j++) {
  //     spectra2D[0].push_back(scan);
  //     spectra2D[1].push_back(mz[j]);
  //     spectra2D[2].push_back(intensity[j]);
  //   }
  // }

  // std::cout << "Number of traces: " << spectra2D[0].size() << std::endl;


  // std::vector<std::vector<double>> matrix;

  // q::Matrix xyData(matrix.size(), 3);

  // tests::test_writing_mzml(file9);

  // tests::test_integration_mstoolkit(file2);

  // tests::test_reading_generic_xml(file4);

  // // Pre conversion of a float vector to double for returning the same as input
  // std::vector<float> inputFloat = {10, 13.4, 15.6, 1000.5};
  // std::vector<double> inputDouble(inputFloat.size());
  // for (size_t i = 0; i < inputFloat.size(); i++) inputDouble[i] = static_cast<double>(inputFloat[i]);
  // utils::test_encoding_decoding_little_endian(inputDouble, 4);
  // std::vector<double> input = {10, 13.4, 15.6, 1000.5};
  // utils::test_encoding_decoding_little_endian(input, 8);

  // // Pre conversion of a float vector to double for returning the same as input
  // std::vector<float> inputFloat = {10, 13.4, 15.6, 1000.5};
  // std::vector<double> inputDouble(inputFloat.size());
  // for (size_t i = 0; i < inputFloat.size(); i++) inputDouble[i] = static_cast<double>(inputFloat[i]);
  // utils::test_encoding_decoding_big_endian(inputDouble, 4);
  // std::vector<double> input = {10, 13.4, 15.6, 1000.5};
  // utils::test_encoding_decoding_big_endian(input, 8);

  // mzml::test_extract_spectra_mzml(file2);

  // mzml::test_extract_chromatograms_mzml(file5);

  // tests::test_reading_animl(file7);

   // omp_set_num_threads(4);

  // int *arr = new int[ARRAY_SIZE];
  // std::fill_n(arr, ARRAY_SIZE, ARRAY_VALUE);

  // #pragma omp parallel for
  // for(int i = 0; i < ARRAY_SIZE; i++)
  // {
  //     arr[i] = arr[i] / arr[i] + arr[i] / 5 - 14;
  // }


  return 0;
}
