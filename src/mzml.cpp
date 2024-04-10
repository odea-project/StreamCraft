#include "mzml.hpp"
#include <omp.h>
#include <filesystem>
#include <cstring>
#include <algorithm>

mzml::SPECTRA_HEADERS mzml::MZML::extract_spectra_headers(const std::vector<int>& idxs) {

  std::string search_run = "//run";

  pugi::xpath_node xps_run = root.select_node(search_run.c_str());

  pugi::xml_node spec_list = xps_run.node().child("spectrumList");

  SPECTRA_HEADERS headers;

  int number_spectra = idxs.size();

  if (number_spectra == 0) {
    std::cerr << "Warning: No indices given!" << std::endl;
    return headers;
  }

  if (spec_list) {

    std::vector<pugi::xml_node> spectra;

    for (pugi::xml_node child = spec_list.first_child(); child; child = child.next_sibling()) {
      spectra.push_back(child);
    }

    headers.spec_index.resize(number_spectra);
    headers.spec_id.resize(number_spectra);
    headers.spec_scan.resize(number_spectra);
    headers.spec_array_length.resize(number_spectra);
    headers.spec_level.resize(number_spectra);
    headers.spec_mode.resize(number_spectra);
    headers.spec_polarity.resize(number_spectra);
    headers.spec_lowmz.resize(number_spectra);
    headers.spec_highmz.resize(number_spectra);
    headers.spec_bpmz.resize(number_spectra);
    headers.spec_bpint.resize(number_spectra);
    headers.spec_tic.resize(number_spectra);
    headers.spec_title.resize(number_spectra);
    headers.scan_rt.resize(number_spectra);
    headers.scan_drift.resize(number_spectra);
    headers.scan_filter_string.resize(number_spectra);
    headers.scan_config.resize(number_spectra);
    headers.scan_injection_ion_time.resize(number_spectra);
    headers.precursor_scan.resize(number_spectra);
    headers.window_mz.resize(number_spectra);
    headers.window_mzlow.resize(number_spectra);
    headers.window_mzhigh.resize(number_spectra);
    headers.ion_mz.resize(number_spectra);
    headers.ion_intensity.resize(number_spectra);
    headers.ion_charge.resize(number_spectra);
    headers.activation_type.resize(number_spectra);
    headers.activation_ce.resize(number_spectra);

    // #pragma omp parallel for
    for (int i = 0; i < number_spectra; i++) {

      const int& index = idxs[i];

      const pugi::xml_node& spec = spectra[index];

      headers.spec_index[i] = spec.attribute("index").as_int();

      std::string spec_id = spec.attribute("id").as_string();

      headers.spec_id[i] = spec_id;

      std::size_t poslastEqual = spec_id.rfind('=');

      headers.spec_scan[i] = std::stoi(spec_id.substr(poslastEqual + 1));

      headers.spec_array_length[i] = spec.attribute("defaultArrayLength").as_int();

      pugi::xml_node level_node = spec.find_child_by_attribute("cvParam", "name", "ms level");
      headers.spec_level[i] = level_node.attribute("value").as_int();

      pugi::xml_node centroid_node = spec.find_child_by_attribute("cvParam", "accession", "MS:1000127");
      pugi::xml_node profile_node = spec.find_child_by_attribute("cvParam", "accession", "MS:1000128");

      if (centroid_node) {
        headers.spec_mode[i] = "centroid";
      } else if (profile_node) {
        headers.spec_mode[i] = "profile";
      } else {
        headers.spec_mode[i] = "";
      }

      pugi::xml_node pol_pos_node = spec.find_child_by_attribute("cvParam", "accession", "MS:1000130");
      pugi::xml_node pol_neg_node = spec.find_child_by_attribute("cvParam", "accession", "MS:1000129");

      if (pol_pos_node) {
        headers.spec_polarity[i] = "positive";
      } else if (pol_neg_node) {
        headers.spec_polarity[i] = "negative";
      } else {
        headers.spec_polarity[i] = "";
      }

      pugi::xml_node lowmz_node = spec.find_child_by_attribute("cvParam", "name", "lowest observed m/z");
      headers.spec_lowmz[i] = lowmz_node.attribute("value").as_double();

      pugi::xml_node highmz_node = spec.find_child_by_attribute("cvParam", "name", "highest observed m/z");
      headers.spec_highmz[i] = highmz_node.attribute("value").as_double();

      pugi::xml_node bpmz_node = spec.find_child_by_attribute("cvParam", "name", "base peak m/z");
      headers.spec_bpmz[i] = bpmz_node.attribute("value").as_double();

      pugi::xml_node bpint_node = spec.find_child_by_attribute("cvParam", "name", "base peak intensity");
      headers.spec_bpint[i] = bpint_node.attribute("value").as_double();

      pugi::xml_node tic_node = spec.find_child_by_attribute("cvParam", "name", "total ion current");
      headers.spec_tic[i] = tic_node.attribute("value").as_double();

      pugi::xml_node title_node = spec.find_child_by_attribute("cvParam", "name", "spectrum title");
      headers.spec_title[i] = title_node.attribute("value").as_string();

      pugi::xml_node node_scan = spec.child("scanList").child("scan");

      pugi::xml_node rt_node = node_scan.find_child_by_attribute("cvParam", "name", "scan start time");
      std::string rt_unit = rt_node.attribute("unitName").as_string();
      double rt_val = rt_node.attribute("value").as_double();
      if (rt_unit == "minute") rt_val = rt_val * 60;
      headers.scan_rt[i] = rt_val;

      pugi::xml_node drift_node = node_scan.find_child_by_attribute("cvParam", "name", "ion mobility drift time");
      headers.scan_drift[i] = drift_node.attribute("value").as_double();

      pugi::xml_node filter_string_node = node_scan.find_child_by_attribute("cvParam", "name", "filter string");
      headers.scan_filter_string[i] = filter_string_node.attribute("value").as_string();

      pugi::xml_node config_node = node_scan.find_child_by_attribute("cvParam", "name", "preset scan configuration");
      headers.scan_config[i] = config_node.attribute("value").as_int();

      pugi::xml_node iit_node = node_scan.find_child_by_attribute("cvParam", "name", "ion injection time");
      headers.scan_injection_ion_time[i] = iit_node.attribute("value").as_double();

      pugi::xml_node precursor = spec.child("precursorList").child("precursor");

      if (precursor) {

        std::string pre_scan_str = precursor.attribute("spectrumRef").as_string();

        if (pre_scan_str != "") {
          std::size_t poslastEqual = pre_scan_str.rfind('=');
          int pre_scan_n = std::stoi(pre_scan_str.substr(poslastEqual + 1));
          headers.precursor_scan[i] = pre_scan_n;
        }

        pugi::xml_node isolation = precursor.child("isolationWindow");

        pugi::xml_node window_mz_node = isolation.find_child_by_attribute("cvParam", "name", "isolation window target m/z");
        headers.window_mz[i] = window_mz_node.attribute("value").as_double();

        pugi::xml_node window_mzlow_node = isolation.find_child_by_attribute("cvParam", "name", "isolation window lower offset");
        headers.window_mzlow[i] = window_mzlow_node.attribute("value").as_double();

        pugi::xml_node window_mzhigh_node = isolation.find_child_by_attribute("cvParam", "name", "isolation window upper offset");
        headers.window_mzhigh[i] = window_mzhigh_node.attribute("value").as_double();

        pugi::xml_node slected_ion = precursor.child("selectedIonList").first_child();

        if (slected_ion) {

          pugi::xml_node ion_mz_node = slected_ion.find_child_by_attribute("cvParam", "name", "selected ion m/z");
          headers.ion_mz[i] = ion_mz_node.attribute("value").as_double();

          pugi::xml_node ion_intensity_node = slected_ion.find_child_by_attribute("cvParam", "name", "peak intensity");
          headers.ion_intensity[i] = ion_intensity_node.attribute("value").as_double();

          pugi::xml_node ion_charge_node = slected_ion.find_child_by_attribute("cvParam", "name", "charge state");
          headers.ion_charge[i] = ion_charge_node.attribute("value").as_int();

        }

        pugi::xml_node activation = precursor.child("activation");

        if (activation) {

          pugi::xml_node activation_type_node = activation.first_child();
          headers.activation_type[i] = activation_type_node.name();

          pugi::xml_node activation_ce_node = activation.find_child_by_attribute("cvParam", "name", "collision energy");
          headers.activation_ce[i] = activation_ce_node.attribute("value").as_double();

        }
      }
    } // end of i loop

  } else {
    std::cerr << "Warning: Spectra list not found in the mzML file!" << std::endl;
  }

  return headers;
}

mzml::BINARY_METADATA mzml::MZML::extract_binary_metadata(const pugi::xml_node& bin) {

  BINARY_METADATA mtd;

  pugi::xml_node node_integer_32 = bin.find_child_by_attribute("cvParam", "accession", "MS:1000519");

  pugi::xml_node node_float_32 = bin.find_child_by_attribute("cvParam", "accession", "MS:1000521");

  pugi::xml_node node_integer_64 = bin.find_child_by_attribute("cvParam", "accession", "MS:1000522");

  pugi::xml_node node_float_64 = bin.find_child_by_attribute("cvParam", "accession", "MS:1000523");

  if (node_float_64) {
    mtd.precision_name = node_float_64.attribute("name").as_string();
    mtd.precision_accession = node_float_64.attribute("accession").as_string();
    mtd.precision_type = "float";
    mtd.precision_int = 64;

  } else if (node_float_32) {
    mtd.precision_name = node_float_32.attribute("name").as_string();
    mtd.precision_accession = node_float_32.attribute("accession").as_string();
    mtd.precision_type = "float";
    mtd.precision_int = 32;

  } else if (node_integer_64){
    mtd.precision_name = node_integer_64.attribute("name").as_string();
    mtd.precision_accession = node_integer_64.attribute("accession").as_string();
    mtd.precision_type = "integer";
    mtd.precision_int = 64;

  } else if (node_integer_32){
    mtd.precision_name = node_integer_32.attribute("name").as_string();
    mtd.precision_accession = node_integer_32.attribute("accession").as_string();
    mtd.precision_type = "integer";
    mtd.precision_int = 32;

  } else {
    throw("Encoding precision with accession MS:1000521, MS:1000522 or MS:1000523 not found!");
  }

  pugi::xml_node node_comp = bin.find_child_by_attribute("cvParam", "accession", "MS:1000574");

  if (node_comp) {
    mtd.compression = node_comp.attribute("name").as_string();

    if (mtd.compression == "zlib" || mtd.compression == "zlib compression") {
      mtd.compressed = true;

    } else {
      mtd.compressed = false;
    }
  }

  bool has_bin_data_type = false;

  for (size_t i = 0; 1 < possible_accessions_binary_data.size(); ++i) {
    pugi::xml_node node_data_type = bin.find_child_by_attribute("cvParam", "accession", possible_accessions_binary_data[i].c_str());

    if (node_data_type) {

      has_bin_data_type = true;

      mtd.data_name = node_data_type.attribute("name").as_string();

      mtd.data_accession = node_data_type.attribute("accession").as_string();

      mtd.data_value = node_data_type.attribute("value").as_string();

      mtd.data_unit = node_data_type.attribute("unitName").as_string();

      mtd.data_name_short = possible_short_name_binary_data[i];

      break;
    }
  }

  if (!has_bin_data_type) {
    throw("Encoded data type could not be found matching the mzML official vocabolary!");
  }

  if (mtd.data_name_short == "other") {
    mtd.data_name_short = mtd.data_value;
  }

  return mtd;
}

void mzml::MZML::extract_spectra_binary_metadata(const pugi::xml_node& first_node) {

  pugi::xml_node binary_list = first_node.child("binaryDataArrayList");

  int counter = 0;

  for (const pugi::xml_node& bin: binary_list.children("binaryDataArray")) {

    BINARY_METADATA mtd = extract_binary_metadata(bin);

    if (mtd.data_name_short == "") {
      mtd.data_name_short = "val_" + std::to_string(counter);
    }

    mtd.index = counter;

    spectra_binary_metadata.push_back(mtd);

    counter++;
  }

  number_spectra_binary_arrays = counter;
}

std::vector<std::vector<double>> mzml::MZML::extract_spectrum(const pugi::xml_node& spectrum_node) {

  std::vector<std::vector<double>> spectrum;

  int number_traces = spectrum_node.attribute("defaultArrayLength").as_int();

  pugi::xml_node node_binary_list = spectrum_node.child("binaryDataArrayList");

  int number_bins = node_binary_list.attribute("count").as_int();

  if (number_spectra_binary_arrays != number_bins) {
    throw("Binary array length does not match binary array length of first spectrum!");
  }

  spectrum.resize(number_bins);

  int counter = 0;

  for (auto i = node_binary_list.children("binaryDataArray").begin(); i != node_binary_list.children("binaryDataArray").end(); ++i) {

    const pugi::xml_node& bin = *i;

    pugi::xml_node node_binary = bin.child("binary");

    std::string encoded_string = node_binary.child_value();

    std::string decoded_string = utils::decode_base64(encoded_string);

    if (spectra_binary_metadata[counter].compressed) {
      decoded_string = utils::decompress_zlib(decoded_string);
    }

    spectrum[counter] = utils::decode_little_endian(decoded_string, spectra_binary_metadata[counter].precision_int / 8);

    int bin_array_size = spectrum[counter].size();

    if (bin_array_size != number_traces) {
      throw("Number of traces in binary array does not match the value of the spectrum header!");
    }

    if (spectra_binary_metadata[counter].data_name_short == "time") {
      pugi::xml_node node_unit = bin.find_child_by_attribute("cvParam", "unitCvRef", "UO");
      std::string unit = node_unit.attribute("unitName").as_string();

      if (unit == "minute") {
        for (double &j : spectrum[counter]) {
          j *= 60;
        }
      }
    }

    counter++;
  }

  return spectrum;
}

std::vector<std::vector<std::vector<double>>> mzml::MZML::extract_spectra(const std::vector<int>& idxs) {

  std::string search_run = "//run";

  pugi::xpath_node xps_run = root.select_node(search_run.c_str());

  pugi::xml_node spec_list = xps_run.node().child("spectrumList");

  std::vector<std::vector<std::vector<double>>> sp;

  int number_spectra_to_extract = idxs.size();

  if (number_spectra_to_extract == 0) {
    std::cerr << "Warning: No indices given!" << std::endl;
    return sp;
  }

  if (spec_list) {

    sp.resize(number_spectra_to_extract);

    std::vector<pugi::xml_node> spectra;

    for (pugi::xml_node child = spec_list.first_child(); child; child = child.next_sibling()) {
      spectra.push_back(child);
    }

    // #pragma omp parallel for
    for (int i = 0; i < number_spectra_to_extract; i++) {

      const int& index = idxs[i];

      const pugi::xml_node& spectrum_node = spectra[index];

      sp[i] = extract_spectrum(spectrum_node);
    }
  }

  return sp;
}

mzml::CHROMATOGRAMS_HEADERS mzml::MZML::extract_chrom_headers(const std::vector<int>& idxs) {

  std::string search_run = "//run";

  pugi::xpath_node xps_run = root.select_node(search_run.c_str());

  pugi::xml_node chrom_list = xps_run.node().child("chromatogramList");

  CHROMATOGRAMS_HEADERS headers;

  int number_chroms = idxs.size();

  if (number_chroms == 0) {
    std::cerr << "Warning: No indices given!" << std::endl;
    return headers;
  }

  if (chrom_list) {

    std::vector<pugi::xml_node> chroms;

    for (pugi::xml_node child = chrom_list.first_child(); child; child = child.next_sibling()) {
      chroms.push_back(child);
    }

    if (chroms.size() == 0) {
      std::cerr << "No chromatograms found!" << std::endl;
      return headers;
    }

    headers.chrom_index.resize(number_chroms);
    headers.chrom_id.resize(number_chroms);
    headers.chrom_array_length.resize(number_chroms);
    headers.chrom_polarity.resize(number_chroms);
    headers.precursor_mz.resize(number_chroms);
    headers.activation_type.resize(number_chroms);
    headers.activation_ce.resize(number_chroms);
    headers.product_mz.resize(number_chroms);

    for (int i = 0; i < number_chroms; i++) {

      const int& index = idxs[i];

      const pugi::xml_node& chrom = chroms[index];

      headers.chrom_id[i] = chrom.attribute("index").as_int();

      std::string id = chrom.attribute("id").as_string();

      headers.chrom_id[i] = id;

      headers.chrom_array_length[i] = chrom.attribute("defaultArrayLength").as_int();

      pugi::xml_node pol_pos_node = chrom.find_child_by_attribute("cvParam", "accession", "MS:1000130");
      pugi::xml_node pol_neg_node = chrom.find_child_by_attribute("cvParam", "accession", "MS:1000129");

      if (pol_pos_node) {
        headers.chrom_polarity[i] = "positive";

      } else if (pol_neg_node) {
        headers.chrom_polarity[i] = "negative";
      } else {
        headers.chrom_polarity[i] = "";
      }

      pugi::xml_node precursor = chrom.child("precursor");

      if (precursor != NULL) {

        pugi::xml_node isolation = precursor.child("isolationWindow");

        pugi::xml_node pre_mz_node = isolation.find_child_by_attribute("cvParam", "name", "isolation window target m/z");

        headers.precursor_mz[i] = pre_mz_node.attribute("value").as_double();

        pugi::xml_node activation = precursor.child("activation");

        if (activation) {

          pugi::xml_node activation_type_node = activation.first_child();
          headers.activation_type[i] = activation_type_node.name();

          pugi::xml_node activation_ce_node = activation.find_child_by_attribute("cvParam", "name", "collision energy");
          headers.activation_ce[i] = activation_ce_node.attribute("value").as_double();

        }
      }

      pugi::xml_node product = chrom.child("product");

      if (product) {

        pugi::xml_node isolation = product.child("isolationWindow");

        pugi::xml_node pro_mz_node = isolation.find_child_by_attribute("cvParam", "name", "isolation window target m/z");
        headers.product_mz[i] = pro_mz_node.attribute("value").as_double();

      }
    } // end of i loop

  } else {
    std::cerr << "Warning: Chromatogram list not found in the mzML file!" << std::endl;
  }

  return headers;
}

std::vector<std::vector<double>> mzml::MZML::extract_chromatogram(const pugi::xml_node& chrom_node) {

  std::vector<std::vector<double>> chrom;

  int number_traces = chrom_node.attribute("defaultArrayLength").as_int();

  pugi::xml_node node_binary_list = chrom_node.child("binaryDataArrayList");

  int number_bins = node_binary_list.attribute("count").as_int();

  chrom.resize(number_bins);

  int counter = 0;

  for (auto i = node_binary_list.children("binaryDataArray").begin(); i != node_binary_list.children("binaryDataArray").end(); ++i) {

    const pugi::xml_node& bin = *i;

    BINARY_METADATA mtd = extract_binary_metadata(bin);

    pugi::xml_node node_binary = bin.child("binary");

    std::string encoded_string = node_binary.child_value();

    std::string decoded_string = utils::decode_base64(encoded_string);

    if (mtd.compressed) {
      decoded_string = utils::decompress_zlib(decoded_string);
    }

    chrom[counter] = utils::decode_little_endian(decoded_string, mtd.precision_int / 8);

    int bin_array_size = chrom[counter].size();

    if (bin_array_size != number_traces) {
      throw("Number of traces in binary array does not match the value of the chromatogram header!");
    }

    if (mtd.data_name_short == "time") {
      pugi::xml_node node_unit = bin.find_child_by_attribute("cvParam", "unitCvRef", "UO");
      std::string unit = node_unit.attribute("unitName").as_string();

      if (unit == "minute") {
        for (double &j : chrom[counter]) {
          j *= 60;
        }
      }
    }

    counter++;
  }

  if (counter > 0) {
    for (int i = 1; i < counter; i++) {
      if (chrom[0].size() != chrom[i].size()) {
        throw("Number of traces in binary arrays of the chromatogram does not match!");
      }
    }
  }

  return chrom;
}

std::vector<std::vector<std::vector<double>>> mzml::MZML::extract_chromatograms(const std::vector<int>& idxs) {

  std::string search_run = "//run";

  pugi::xpath_node xps_run = root.select_node(search_run.c_str());

  pugi::xml_node chrom_list = xps_run.node().child("chromatogramList");

  std::vector<std::vector<std::vector<double>>> chr;

  int number_chroms_to_extract = idxs.size();

  if (number_chroms_to_extract == 0) {
    std::cerr << "Warning: No indices given!" << std::endl;
    return chr;
  }

  if (chrom_list) {

    chr.resize(number_chroms_to_extract);

    std::vector<pugi::xml_node> chromatograms;

    for (pugi::xml_node child = chrom_list.first_child(); child; child = child.next_sibling()) {
      chromatograms.push_back(child);
    }

    for (int i = 0; i < number_chroms_to_extract; i++) {

      const int& index = idxs[i];

      const pugi::xml_node& chrom_node = chromatograms[index];

      chr[i] = extract_chromatogram(chrom_node);
    }
  }

  return chr;
}

void mzml::MZML::write_spectra(std::vector<std::vector<std::vector<double>>> spectra, std::vector<std::string> names, std::string mode, bool compress, bool save, std::string save_suf) {

  if (spectra.size() == 0) {
    std::cerr << "No spectra to write!" << std::endl;
    return;
  }

  if (spectra[0].size() != names.size()) {
    std::cerr << "Number of spectra and names do not match!" << std::endl;
    return;
  }

  std::string search_run = "//run";
  
  pugi::xml_node run_node = root.select_node(search_run.c_str()).node();
  
  pugi::xml_node spec_list_node = run_node.child("spectrumList");

  std::vector<pugi::xml_node> spectra_nodes;

  if (spec_list_node) {

    for (pugi::xml_node child = spec_list_node.first_child(); child; child = child.next_sibling()) {
      spectra_nodes.push_back(child);
    }

    if (spectra_nodes.size() != spectra.size()) {
      std::cerr << "Number of spectra in the file and the number of spectra to write do not match!" << std::endl;
      return;
    }

  } else {
    std::cerr << "Warning: Spectrum list not found in the mzML file!" << std::endl;
    return;
    // spec_list_node = run_node.append_child("spectrumList");
    // spec_list_node.append_attribute("count") = "0";
  }

  int number_spectra = spectra.size();

  std::string number_spectra_str = std::to_string(number_spectra);

  spec_list_node.attribute("count").set_value(number_spectra_str.c_str());

  for (size_t i = 0; i < spectra.size(); i++) {

    pugi::xml_node spec = spectra_nodes[i];

    const std::vector<double>& mz = spectra[i][0];

    const std::vector<double>& intensity = spectra[i][1];

    // if (!spec) spec = spec_list_node.append_child("spectrum");

    spec.attribute("defaultArrayLength").set_value(spectra[i][0].size());

    if (mode == "centroid") {
      pugi::xml_node node_mode = spec.find_child_by_attribute("cvParam", "accession", "MS:1000128");

      if (node_mode) {
        node_mode.attribute("accession").set_value("MS:1000127");
        node_mode.attribute("name").set_value("centroid spectrum");
      }
    }

    pugi::xml_node low_mz_node = spec.find_child_by_attribute("cvParam", "name", "lowest observed m/z");

    double low_mz = *std::min_element(mz.begin(), mz.end());  

    low_mz_node.attribute("value").set_value(low_mz);

    pugi::xml_node high_mz_node = spec.find_child_by_attribute("cvParam", "name", "highest observed m/z");

    double high_mz = *std::max_element(mz.begin(), mz.end());

    high_mz_node.attribute("value").set_value(high_mz);
    
    pugi::xml_node bp_mz_node = spec.find_child_by_attribute("cvParam", "name", "base peak m/z");

    double bp_mz = mz[std::distance(intensity.begin(), std::max_element(intensity.begin(), intensity.end()))];

    bp_mz_node.attribute("value").set_value(bp_mz);

    pugi::xml_node bp_int_node = spec.find_child_by_attribute("cvParam", "name", "base peak intensity");

    double bp_int = *std::max_element(intensity.begin(), intensity.end());

    bp_int_node.attribute("value").set_value(bp_int);

    pugi::xml_node tic_node = spec.find_child_by_attribute("cvParam", "name", "total ion current");

    double tic = std::accumulate(intensity.begin(), intensity.end(), 0.0);

    tic_node.attribute("value").set_value(tic);

    pugi::xml_node bin_array_list = spec.child("binaryDataArrayList");

    bin_array_list.remove_children();

    bin_array_list.attribute("count").set_value(spectra[i].size());

    for (size_t j = 0; j < spectra[i].size(); j++) {

      const std::vector<double>& x = spectra[i][j];

      std::string x_enc = utils::encode_little_endian(x, 8);
      
      if (compress) x_enc = utils::compress_zlib(x_enc);
      
      x_enc = utils::encode_base64(x_enc);

      pugi::xml_node bin_array = bin_array_list.append_child("binaryDataArray");

      bin_array.append_attribute("encodedLength") = x_enc.size();

      pugi::xml_node bin = bin_array.append_child("cvParam");

      bin.append_attribute("cvRef") = "MS";

      bin.append_attribute("accession") = "MS:1000523";

      bin.append_attribute("name") = "64-bit float";

      bin.append_attribute("value") = "";

      bin = bin_array.append_child("cvParam");

      if (compress) {
        bin.append_attribute("cvRef") = "MS";
        bin.append_attribute("accession") = "MS:1000574";
        bin.append_attribute("name") = "zlib compression";
        bin.append_attribute("value") = "";

      } else {
        bin.append_attribute("cvRef") = "MS";
        bin.append_attribute("accession") = "MS:1000576";
        bin.append_attribute("name") = "no compression";
        bin.append_attribute("value") = "";
      }

      bin = bin_array.append_child("cvParam");

      bin.append_attribute("cvRef") = "MS";

      if (j == 0) {
        bin.append_attribute("accession") = "MS:1000514";
        bin.append_attribute("name") = "m/z array";
        bin.append_attribute("value") = "";
        bin.append_attribute("unitCvRef") = "MS";
        bin.append_attribute("unitAccession") = "MS:1000040";
        bin.append_attribute("unitName") = "m/z";

      } else if (j == 1) {
        bin.append_attribute("accession") = "MS:1000515";
        bin.append_attribute("name") = "intensity array";
        bin.append_attribute("value") = "";
        bin.append_attribute("unitCvRef") = "MS";
        bin.append_attribute("unitAccession") = "MS:1000131";
        bin.append_attribute("unitName") = "number of detector counts";

      } else {
        bin.append_attribute("accession") = "MS:1000786";
        bin.append_attribute("name") = "non-standard data array";
        bin.append_attribute("value") = names[j].c_str();
      }

      pugi::xml_node bin_data = bin_array.append_child("binary");

      bin_data.append_child(pugi::node_pcdata).set_value(x_enc.c_str());

    }

  }

  if (std::filesystem::exists("example_modified_test.xml")) std::filesystem::remove("example_modified_test.xml");

  std::cout << "Saving result: " << doc.save_file("example_modified_test.xml") << std::endl;

};
