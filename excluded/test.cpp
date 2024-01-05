
#include "pugixml.hpp"
#include <iostream>
#include <string>

// Function to search for the XML file
std::string findXmlFile() {
    std::string filename = "/home/cunha/Documents/github/adrw/ms_simple.animl";
    // std::cout << "Enter the XML file name: ";
    // std::cin >> filename;
    return filename;
}

int main() {
    // Find the XML file
    std::string xmlFilename = findXmlFile();

    // Load the XML file
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(xmlFilename.c_str());

    // Check if the XML file is loaded successfully
    if (!result) {
        std::cerr << "Error loading XML file: " << result.description() << std::endl;
        return 1;
    }

    // Accessing XML content
    pugi::xml_node root = doc.first_child();
    if (root) {
        // Print content to the console
        std::cout << "Root node name: " << root.name() << std::endl;

        // Access other nodes and attributes as needed
        // Example: pugi::xml_node childNode = root.child("childNode");
        //          std::cout << "Child node value: " << childNode.text().get() << std::endl;
    } else {
        std::cerr << "Root node not found in XML file." << std::endl;
        return 1;
    }

    return 0;
}