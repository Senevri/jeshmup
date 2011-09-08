#include "XmlReader.h"
#define TIXML_USE_TICPP

void XmlReader::parse(ticpp::Node *n){
	if (NULL == n) return;

	try {
		ticpp::Element * el = n->ToElement();
		std::string strName;
		std::string strValue;
		std::string strText;
		std::cout << std::endl << "Element:" << std::endl;
		el->GetValue(&strName);
		std::cout << strName << std::endl;
		std::cout << "-------------" << std::endl;
		ticpp::Iterator< ticpp::Attribute > attribute;
		//ticpp::Attribute * attribute = el->FirstAttribute();
		for(attribute = attribute.begin(el); attribute != attribute.end();
				attribute++){
			attribute->GetName(&strName);
			attribute->GetValue(&strValue);
			std::cout << strName << ": " << strValue << std::endl;
		}
		//std::cout << std::endl;
		strText = el->GetText(false);
		if(strText.length() > 0 ) std::cout << "Text:" << strText << std::endl;
	} catch (ticpp::Exception &e) {
		//had no further children
		std::cout <<"alt xmlerr " << e.what() <<std::endl;
	}
	parse (n->FirstChild(false));
	parse (n->NextSibling(false));

}

void XmlReader::load(const char * pcFilename){
	ticpp::Document doc(pcFilename);
	doc.LoadFile();
	parse(doc.FirstChild("level"));

}
