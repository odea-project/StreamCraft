#if !defined(MSCLIB_H)
#define MSCLIB_H

#include <iostream>

#define PUGIXML_HEADER_ONLY
#include "pugixml.hpp"

namespace msc {

  void hello();

  class XML {
    private:

    public:
      const char* path;
      
      pugi::xml_document doc;
      
      pugi::xml_node root;
      
      pugi::xml_parse_result loading_result;

      std::string format;

      void load_file(const std::string& file);

      bool valid_format();
  };



  class mzML {
    private:
      pugi::xml_document doc;
      
      pugi::xml_node main;

    public:
      mzML(const XML& value) {
        if (value.format == "mzML") {
          main = value.root.child("mzML");
        }
      }

      std::string node_name() {
        return main.name();
      };
      
  };

  pugi::xml_node get_main_node(const pugi::xml_node& root);



}

#endif // MSCLIB_H
