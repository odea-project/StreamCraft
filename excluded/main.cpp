#include <iostream>
#include <string>
#include "msclib.h"

// #define _LARGEFILE_SOURCE
// #define _NOSQLITE
// #define _FILE_OFFSET_BITS 64
// #include "MSReader.h"

int main() {

  std::string file = "C:/Users/Ricardo Cunha/Documents/example_ms_files/tof_25000_mix1-r001.mzML";
  // std::string file = "./output.xml";


  std::cout << std::endl;
  std::cout << file << std::endl;
  std::cout << std::endl;

  msc::hello();
  std::cout << std::endl;

  std::cout << "Loading a generic XML DOC..." << std::endl;
  msc::XML Doc;
  Doc.load_file(file);
  std::cout << Doc.path << std::endl;
  std::cout << Doc.format << std::endl;
  std::cout << Doc.valid_format() << std::endl;
  std::cout << std::endl;

  std::cout << "Loading a mzML based on DOC..." << std::endl;
  msc::mzML mzml(Doc);
  std::cout << mzml.node_name() << std::endl;
  std::cout << std::endl;

  const char* cfile = file.c_str();

  return 0;
}
