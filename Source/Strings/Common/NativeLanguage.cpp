////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "NativeLanguage.h"

namespace Strings
{
	Common_NativeLanguage* Common_NativeLanguage::create()
	{
		Common_NativeLanguage* instance = new Common_NativeLanguage();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Common_NativeLanguage::clone()
	{
		LocalizedString* clonedString = Common_NativeLanguage::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Common_NativeLanguage::Common_NativeLanguage() : LocalizedString()
	{
	}

	Common_NativeLanguage::~Common_NativeLanguage()
	{
	}

	std::string Common_NativeLanguage::getStringIdentifier()
	{
		return "Common_NativeLanguage";
	}

	std::string Common_NativeLanguage::getStringAr()
	{
		return "عربى";
	}

	std::string Common_NativeLanguage::getStringBg()
	{
		return "български";
	}

	std::string Common_NativeLanguage::getStringCs()
	{
		return "Čeština";
	}

	std::string Common_NativeLanguage::getStringDa()
	{
		return "Dansk";
	}

	std::string Common_NativeLanguage::getStringDe()
	{
		return "Deutsch";
	}

	std::string Common_NativeLanguage::getStringEl()
	{
		return "Ελληνικά";
	}

	std::string Common_NativeLanguage::getStringEn()
	{
		return "English";
	}

	std::string Common_NativeLanguage::getStringEs()
	{
		return "Español";
	}

	std::string Common_NativeLanguage::getStringEs419()
	{
		return "Español";
	}

	std::string Common_NativeLanguage::getStringFi()
	{
		return "Suomalainen";
	}

	std::string Common_NativeLanguage::getStringFr()
	{
		return "Français";
	}

	std::string Common_NativeLanguage::getStringHu()
	{
		return "Magyar";
	}

	std::string Common_NativeLanguage::getStringIt()
	{
		return "Italiana";
	}

	std::string Common_NativeLanguage::getStringJa()
	{
		return "日本人";
	}

	std::string Common_NativeLanguage::getStringKo()
	{
		return "한국어";
	}

	std::string Common_NativeLanguage::getStringNl()
	{
		return "Nederlands";
	}

	std::string Common_NativeLanguage::getStringNo()
	{
		return "Norsk";
	}

	std::string Common_NativeLanguage::getStringPl()
	{
		return "Polski";
	}

	std::string Common_NativeLanguage::getStringPt()
	{
		return "Português";
	}

	std::string Common_NativeLanguage::getStringPtBr()
	{
		return "Português (BR)";
	}

	std::string Common_NativeLanguage::getStringRo()
	{
		return "Română";
	}

	std::string Common_NativeLanguage::getStringRu()
	{
		return "Русский";
	}

	std::string Common_NativeLanguage::getStringSv()
	{
		return "Svenska";
	}

	std::string Common_NativeLanguage::getStringTh()
	{
		return "ไทย";
	}

	std::string Common_NativeLanguage::getStringTr()
	{
		return "Türk";
	}

	std::string Common_NativeLanguage::getStringUk()
	{
		return "Українська";
	}

	std::string Common_NativeLanguage::getStringVi()
	{
		return "Tiếng Việt";
	}

	std::string Common_NativeLanguage::getStringZhCn()
	{
		return "中文(简体)";
	}

	std::string Common_NativeLanguage::getStringZhTw()
	{
		return "中文(台灣)";
	}
}
