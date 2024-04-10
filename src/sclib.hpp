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

  class MassSpecAnalysis {

    private:

      std::vector<std::string> possible_formats = {
        "mzML", "mzXML", "animl"
      };

    public:
      
      std::string file_path;

      std::string file_dir;

      std::string file_name;

      std::string file_extension;

      MassSpecAnalysis(const std::string& file) {
        file_path = file;
        file_dir = file.substr(0, file.find_last_of("/\\") + 1);
        file_name = file.substr(file.find_last_of("/\\") + 1);
        file_extension = file_name.substr(file_name.find_last_of(".") + 1);
        file_name = file_name.substr(0, file_name.find_last_of("."));
      }
  };

  

  // class XML {

  //   private:

  //   public:

  //     std::string file_path;

  //     pugi::xml_document doc;

  //     pugi::xml_node root;

  //     pugi::xml_parse_result loading_result;

  //     std::string name;

  //     XML(const std::string& file) {

  //       file_path = file;

  //       const char* path = file.c_str();

  //       loading_result = doc.load_file(path, pugi::parse_default | pugi::parse_declaration | pugi::parse_pi);

  //       if (loading_result) {
  //         root = doc.document_element();

  //         if (!root) {
  //           std::cout << std::endl;
  //           std::cout << "Root node is empty!" << std::endl;

  //         } else {
  //           name = root.name();
  //         }

  //       } else {
  //         std::cout << std::endl;
  //         std::cout << "XML file could not be opened! " << std::endl << loading_result.description() << std::endl;
  //       }
  //     };
  // };

}; // namespace sc

#endif // SCLIB_HPP

#if defined(SC_HEADER_ONLY) && !defined(SC_SOURCE)
#	define SC_SOURCE "sclib.cpp"
#	include SC_SOURCE
#endif
