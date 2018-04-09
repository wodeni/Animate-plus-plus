#include "../include/rapidxml-1.13/rapidxml_utils.hpp"
#include <iostream>
#include <string>
#include <sstream>

using namespace rapidxml;
using namespace std;

int main() {
	file<> xml_file("sample.xml");
	xml_document<> doc;
	doc.parse<0>(xml_file.data());
	cout << doc.first_node()->name() << "\n";

	// loop through all nodes
	xml_node<> *head = doc.first_node();
	for(xml_node<> *pNode=head->first_node(); pNode; pNode=pNode->next_sibling()){
		cout << pNode->name() << "\n";
		for(xml_attribute<> *pAttr=pNode->first_attribute(); pAttr; pAttr=pAttr->next_attribute()){
			cout << pAttr->name() << " " << pAttr->value() << "\n";
		}
		cout << "\n";
	}
}
