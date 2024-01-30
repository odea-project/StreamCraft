#ifndef TESTS_HPP
#define TESTS_HPP

#include "sclib.hpp"
// #include "MSToolkitTypes.h"
// #include "MSReader.h"
// #include "MSObject.h"
// #include "Spectrum.h"
// using namespace MSToolkit;

namespace tests {

  void test_writing_mzml(const std::string& file) {









    // const char* fl = file.c_str();
    // pugi::xml_document doc;
    // pugi::xml_parse_result result = doc.load_file(fl);
    // std::cout << "Load result: " << result.description() << ", mesh name: " << doc.child("mesh").attribute("name").value() << std::endl;

    sc::mzml::MZML mzml(file);

    mzml.print_spectra_binary_metadata();

    std::vector<int> indices = {0, 1};
    std::vector<std::vector<std::vector<double>>> spectra_tensor = mzml.get_spectra(indices);

    // TODO add get_spectra_names and get_spectra_units

    std::cout << "N. spectra: " << spectra_tensor.size() << std::endl;
    std::cout << "N. spectra arrays: " << spectra_tensor[0].size() << std::endl;
    std::cout << "N. traces in 1st spectrum: " << spectra_tensor[0][0].size() << std::endl;
    // std::cout << "m/z vals: ";
    // for (const double& mz : spectra_tensor[0][0]) std::cout << mz << "; ";
    // std::cout << std::endl;

    const pugi::xml_node& root = mzml.get_root();

    std::string search_run = "//run";

    const pugi::xpath_node& xps_run = root.select_node(search_run.c_str());

    const pugi::xml_node& spec_list = xps_run.node().child("spectrumList");

    int number_spectra = spec_list.attribute("count").as_int();

    std::cout << "N. total spectra: " << number_spectra << std::endl;

    std::vector<pugi::xml_node> spectra_nodes;

    for (pugi::xml_node child = spec_list.first_child(); child; child = child.next_sibling()) {
      spectra_nodes.push_back(child);
    }

    for (int i : indices) {

      pugi::xml_node node = spectra_nodes[i];
      pugi::xml_node binary_list = node.child("binaryDataArrayList");

      if (binary_list) {
        pugi::xml_attribute count = binary_list.attribute("count");
        count.set_value(3);
      }

      pugi::xml_node new_bin = binary_list.append_child("binaryDataArray");

      new_bin.append_attribute("encodedLength") = 100;

      pugi::xml_node param = new_bin.append_child("cvParam");
      param.append_attribute("cvRef") = "MS";
      param.append_attribute("accession") = "MS:1000523";
      param.append_attribute("name") = "64-bit float";
      param.append_attribute("value") = "";

      param = new_bin.append_child("cvParam");
      param.append_attribute("cvRef") = "MS";
      param.append_attribute("accession") = "MS:1000574";
      param.append_attribute("name") = "zlib compression";
      param.append_attribute("value") = "";

      param = new_bin.append_child("cvParam");
      param.append_attribute("cvRef") = "MS";
      param.append_attribute("accession") = "MS:1000XXX";
      param.append_attribute("name") = "array name";
      param.append_attribute("value") = "";
      param.append_attribute("unitCvRef") = "MS";
      param.append_attribute("unitAccession") = "MS:10000XX";
      param.append_attribute("unitName") = "unit name";

    }

    const pugi::xml_document& doc = mzml.get_document();

    std::cout << "Saving result: " << doc.save_file("example_modified_test.xml") << std::endl;

    // add two additional binary sets to the binaryDataArrayList of spectra in the indices

















  };










  // void test_integration_mstoolkit(const std::string& file) {

  // MSReader r;
  //   Spectrum s;
  //   // int j;

  //   r.addFilter(MS1);
  //   r.addFilter(MS2);
  //   r.addFilter(MSX);
  //   r.addFilter(SRM);

  //   char nativeID[256];
  //   r.readFile(file.c_str(), s, 900503);
  //   if(s.getScanNumber()==0) exit(-1);

  //   char szNativeID[128];
  //   if (s.getNativeID(szNativeID, 128))
  //       printf("success:  scan %d  nativeID: %s\n", s.getScanNumber(), szNativeID);
  //   else
  //       printf("failure:  scan %d\n", s.getScanNumber());

  //   printf("size: %d\n", s.sizeMZ());

  //   s.getNativeID(nativeID, 256);
  //   printf("%s\n",nativeID);
  //   // printf("S\t%d\t%d",s.getScanNumber(),s.getScanNumber());
  //   // for(j=0;j<s.sizeMZ();j++){
  //   // 	printf("\t%.*lf",4,s.getMZ(j));
  //   // }
  //   // printf("\n");
  //   // if(s.getRTime()>0) printf("I\tRTime\t%.*f\n",4,s.getRTime());
  //   // //printf("I\tConvA\t%.6lf\n",s.getConversionA());
  //   // //printf("I\tConvB\t%.6lf\n",s.getConversionB());
  //   // //printf("I\tConvC\t%.6lf\n",s.getConversionC());
  //   // //printf("I\tConvD\t%.6lf\n",s.getConversionD());
  //   // //printf("I\tConvE\t%.6lf\n",s.getConversionE());
  //   // //printf("I\tConvI\t%.6lf\n",s.getConversionI());
  //   // for(j=0;j<s.sizeZ();j++){
  //   // 	printf("Z\t%d\t%.*f\n",s.atZ(j).z,6,s.atZ(j).mh);
  //   // }

  //   // for(j=0;j<s.size();j++){
  //   // 	printf("%.4f %.4f\n",s.at(j).mz,s.at(j).intensity);
  //   // }

  //   int lastScan =  r.getLastScan();
  //   std::cout << "Last Scan: " << lastScan << std::endl;

  //   int len = s.size();
  //   double val = s[0].mz;

  //   s.printMe();

  //   Peak_T pk1 = s[0];

  //   std::cout << pk1.mz << " - " << pk1.intensity << std::endl;

  //   std::cout << len << std::endl;

  //   std::cout << val << std::endl;

  // };



  /*!
  * Tests reading an AnIML.
  */
  void test_reading_animl(const std::string& file) {

    sc::animl::ANIML animl_file(file);
    std::cout << animl_file.get_name() << std::endl;
    std::cout << std::endl;
    std::cout << "Number of samples: " << animl_file.get_number_samples() << std::endl;
    std::cout << std::endl;
    std::vector<int> indices = {1, 2};
    std::vector<sc::animl::SAMPLE> samples = animl_file.get_samples(indices, {}, {});
    std::cout << "Get samples by indices:" << std::endl;
    std::cout << "Names: ";
    for (const sc::animl::SAMPLE& sp : samples) std::cout << sp.name << "; ";
    std::cout << std::endl;
    std::cout << "SampleID: ";
    for (const sc::animl::SAMPLE& sp : samples) std::cout << sp.sampleID << "; ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::vector<std::string> names = {"Mobile Phase", "Test Sample"};
    std::vector<sc::animl::SAMPLE> samples2 = animl_file.get_samples({}, names, {});
    std::cout << "Get samples by name:" << std::endl;
    std::cout << "Names: ";
    for (const sc::animl::SAMPLE& sp : samples2) std::cout << sp.name << "; ";
    std::cout << std::endl;
    std::cout << "SampleID: ";
    for (const sc::animl::SAMPLE& sp : samples2) std::cout << sp.sampleID << "; ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::vector<std::string> sampleIDs = {"s1", "s3"};
    std::vector<sc::animl::SAMPLE> samples3 = animl_file.get_samples({}, {}, sampleIDs);
    std::cout << "Get samples by sampleID:" << std::endl;
    std::cout << "Names: ";
    for (const sc::animl::SAMPLE& sp : samples3) std::cout << sp.name << "; ";
    std::cout << std::endl;
    std::cout << "SampleID: ";
    for (const sc::animl::SAMPLE& sp : samples3) std::cout << sp.sampleID << "; ";
    std::cout << std::endl;
    std::cout << std::endl;


    std::cout << "Number of experiments: " << animl_file.get_number_experiment_steps() << std::endl;
    std::cout << std::endl;
    std::vector<int> indices2 = {0};
    std::vector<sc::animl::EXPSTEP> exps = animl_file.get_experiment_steps(indices2, {}, {}, {});
    std::cout << "Get experiments by indices:" << std::endl;
    std::cout << "Names: ";
    for (const sc::animl::EXPSTEP& ex : exps) std::cout << ex.name << "; ";
    std::cout << std::endl;
    std::cout << "Technique: ";
    for (const sc::animl::EXPSTEP& ex : exps) std::cout << ex.technique_name << "; ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::vector<std::string> names2 = {"Q1"};
    std::vector<sc::animl::EXPSTEP> exps2 = animl_file.get_experiment_steps({}, names2 ,{}, {});
    std::cout << "Get experiments by names:" << std::endl;
    std::cout << "Names: ";
    for (const sc::animl::EXPSTEP& ex : exps2) std::cout << ex.name << "; ";
    std::cout << std::endl;
    std::cout << "Technique: ";
    for (const sc::animl::EXPSTEP& ex : exps2) std::cout << ex.technique_name << "; ";
    std::cout << std::endl;
    std::cout << std::endl;
    std::vector<std::string> tech = {"Chromatography"};
    std::vector<sc::animl::EXPSTEP> exps3 = animl_file.get_experiment_steps({},{}, tech, {});
    std::cout << "Get experiments by technique:" << std::endl;
    std::cout << "Names: ";
    for (const sc::animl::EXPSTEP& ex : exps3) std::cout << ex.name << "; ";
    std::cout << std::endl;
    std::cout << "Technique: ";
    for (const sc::animl::EXPSTEP& ex : exps3) std::cout << ex.technique_name << "; ";
    std::cout << std::endl;
    std::cout << "Technique URI: ";
    for (const sc::animl::EXPSTEP& ex : exps3) std::cout << ex.technique_uri << "; ";
    std::cout << std::endl;
    std::cout << std::endl;
    sc::animl::EXPSTEP exp3 = exps3[0];
    std::cout << "Experiment (first): " << exp3.name << std::endl;
    std::cout << std::endl;
    std::cout << "Number of results: " << exp3.ResultSet.size() << std::endl;
    std::cout << std::endl;
    sc::animl::RESULT expRes = exp3.ResultSet[0];
    std::cout << "Result (first): " << expRes.name << std::endl;
    std::cout << "Number of series: " << expRes.SeriesSet.size() << std::endl;
    sc::animl::SERIES expSeries = expRes.SeriesSet[0];
    std::cout << "Name of series (first): " << expSeries.name << std::endl;
    std::cout << "Name of series value type (first): " << expSeries.ValueSetName << std::endl;
    std::cout << "Series values (first): ";
    for (const double& val : expSeries.EncodedValueSet) std::cout << val << "; ";
    std::cout << std::endl;
    std::cout << "Number of experiments: " << expRes.ExpStepSet.size() << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // using MyVariableType = decltype(expRes);
    // std::cout << "Type of myVariable: " << typeid(expRes).name() << std::endl;

    // if (typeid(expRes) == typeid(sc::animl::RESULT)) {
    //   std::cout << "myObject is of type X." << std::endl;
    // } else {
    //     std::cout << "myObject is not of type X." << std::endl;
    // }

  };



  /*!
  * Tests reading a generic XML file.
  */
  void test_reading_generic_xml(const std::string& file) {

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Reading Generic XML" << std::endl;
    std::cout << std::endl;

    sc::XML xml(file);
    std::cout << xml.file_path << std::endl;
    std::cout << xml.name << std::endl;
    std::cout << std::endl;
  }



  /*!
  * Tests litle endian encoding and deconding based on an input vector of doubles and a precision integer.
  */
  void test_encoding_decoding_little_endian(const std::vector<double>& input, const int& precision) {

      std::cout << std::endl;
      std::cout << std::endl;
      std::cout << "Encoding and Decoding Little Endian (" << precision * 8 << "-bit) Test" << std::endl;
      std::cout << std::endl;

      std::cout << "Input vector: ";
      for (double i : input) std::cout << i << " ";
      std::cout << std::endl;
      std::string result = sc::utils::encode_little_endian(input, precision);
      std::cout << "Encoded: " << result << std::endl;
      result = sc::utils::compress_zlib(result);
      std::cout << "Compressed: " << "Not printed!" << std::endl;
      result = sc::utils::encode_base64(result);
      std::cout << "Encoded_base64: " << result << std::endl;

      std::cout << std::endl;
      result = sc::utils::decode_base64(result);
      std::cout << "Decoded_base64: " << "Not printed!" << std::endl;
      result = sc::utils::decompress_zlib(result);
      std::cout << "Decompressed: " << result << std::endl;
      std::vector<double> result_back = sc::utils::decode_little_endian(result, precision);
      std::cout << "Decoded: ";
      for (double i : result_back) std::cout << i << " ";
      std::cout << std::endl;
      bool check = input == result_back;

      std::cout << std::endl;
      std::cout << "When 1 the result is equal to input: " << check << std::endl;
      std::cout << std::endl;
    };

  /*!
  * Tests extracting spectra from mzML.
  */
  void test_extract_spectra_mzml(const std::string& file) {

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Extract Spectra mzML file:" << std::endl;
    std::cout << std::endl;

    sc::MZML mzml(file);

    std::cout << "Root name: " << mzml.get_root_name() << std::endl;

    std::cout << "Number of spectra: " << mzml.get_number_spectra() << std::endl;

    sc::mzml::SPECTRA_HEADERS hd;

    hd = mzml.get_spectra_headers();

    int number = hd.spec_index.size();

    std::cout << "Size of vector in headers struct: " << number << std::endl;

    std::cout << "Retention time of 10th spectrum: " << hd.scan_rt[10] << std::endl;

    std::cout << "Number of binary arrays: " << mzml.get_number_spectra_binary_arrays() << std::endl;

    std::vector<sc::mzml::BINARY_METADATA> mtd = mzml.get_spectra_binary_metadata();

    std::cout << "Name of first binary array: " << mtd[1].data_name << std::endl;

    std::vector<std::vector<std::vector<double>>> spectra;

    std::vector<int> indices = {10, 15};

    spectra = mzml.get_spectra(indices);

    std::cout << "Number of extracted spectra: " << spectra.size() << std::endl;

    std::cout << "Number of traces in the first extracted spectrum: " << spectra[0][0].size() << std::endl;

    std::cout << std::endl;
    };

    /*!
  * Tests extracting chromatograms from mzML.
  */
  void test_extract_chromatograms_mzml(const std::string& file) {

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Test Chromatograms mzML file:" << std::endl;
    std::cout << std::endl;

    sc::mzml::MZML mzml(file);

    std::cout << "Root name: " << mzml.get_root_name() << std::endl;

    std::cout << "Number of chromatograms: " << mzml.get_number_chromatograms() << std::endl;

    sc::mzml::CHROMATOGRAMS_HEADERS ch;

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

};

#endif // TESTS_HPP