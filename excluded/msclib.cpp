#include <iostream>
#include <string>
#include <cstring>
#include "msclib.h"

void msc::hello() {
  std::cout << std::endl;
  std::cout << "Welcome to msclib!" << std::endl;
}

void msc::XML::load_file(const std::string& file) {
  path = file.c_str();
  
  loading_result = doc.load_file(path, pugi::parse_default | pugi::parse_declaration | pugi::parse_pi);

  if (loading_result) {
    root = doc.document_element();

    if (!root) {
      std::cout << std::endl;
      std::cout << "Root node is empty!" << std::endl;

    } else {
      format = root.name();

      if ("indexedmzML" == format) {
        format = "mzML";
      }

      std::cout << std::endl;
      std::cout << "Opened " << format << " file!" << std::endl;
    }

  } else {
    std::cout << std::endl;
    std::cout << "XML file could not be opened! " << loading_result.description() << std::endl;
  }
}

bool msc::XML::valid_format() {
  bool valid = false;

  if (format == "mzML" || format == "mzXML") {
    valid = true;
  }

  return valid;
}

pugi::xml_node msc::get_main_node(const pugi::xml_node& root) {
  const char* root_name = root.name();
  pugi::xml_node main_node;

  if (strcmp("indexedmzML", root_name) == 0) {
    main_node = root.child("mzML");

  } else if (strcmp("mzXML", root_name) == 0) {
    main_node = root;

  } else {
    std::cout << std::endl;
    std::cout << "The file must be a valid mzML or mzXML format!" << std::endl;
  }

  return main_node;
}

