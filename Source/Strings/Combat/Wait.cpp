////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Wait.h"

namespace Strings
{
	Combat_Wait* Combat_Wait::create()
	{
		Combat_Wait* instance = new Combat_Wait();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Combat_Wait::clone()
	{
		LocalizedString* clonedString = Combat_Wait::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Combat_Wait::Combat_Wait() : LocalizedString()
	{
	}

	Combat_Wait::~Combat_Wait()
	{
	}

	std::string Combat_Wait::getStringIdentifier()
	{
		return "Combat_Wait";
	}

	std::string Combat_Wait::getStringAr()
	{
		return "انتظر";
	}

	std::string Combat_Wait::getStringBg()
	{
		return "изчакайте";
	}

	std::string Combat_Wait::getStringCs()
	{
		return "Počkejte";
	}

	std::string Combat_Wait::getStringDa()
	{
		return "Vente";
	}

	std::string Combat_Wait::getStringDe()
	{
		return "Warten";
	}

	std::string Combat_Wait::getStringEl()
	{
		return "Περιμένετε";
	}

	std::string Combat_Wait::getStringEn()
	{
		return "WAIT";
	}

	std::string Combat_Wait::getStringEs()
	{
		return "Espere";
	}

	std::string Combat_Wait::getStringEs419()
	{
		return "Espere";
	}

	std::string Combat_Wait::getStringFi()
	{
		return "Odota";
	}

	std::string Combat_Wait::getStringFr()
	{
		return "Attendre";
	}

	std::string Combat_Wait::getStringHu()
	{
		return "Várjon";
	}

	std::string Combat_Wait::getStringIt()
	{
		return "Aspettare";
	}

	std::string Combat_Wait::getStringJa()
	{
		return "待つ";
	}

	std::string Combat_Wait::getStringKo()
	{
		return "기다림";
	}

	std::string Combat_Wait::getStringNl()
	{
		return "Wacht";
	}

	std::string Combat_Wait::getStringNo()
	{
		return "Vente";
	}

	std::string Combat_Wait::getStringPl()
	{
		return "Czekać";
	}

	std::string Combat_Wait::getStringPt()
	{
		return "Esperar";
	}

	std::string Combat_Wait::getStringPtBr()
	{
		return "Esperar";
	}

	std::string Combat_Wait::getStringRo()
	{
		return "Aștepta";
	}

	std::string Combat_Wait::getStringRu()
	{
		return "Подождите";
	}

	std::string Combat_Wait::getStringSv()
	{
		return "Vänta";
	}

	std::string Combat_Wait::getStringTh()
	{
		return "รอ";
	}

	std::string Combat_Wait::getStringTr()
	{
		return "Bekleyin";
	}

	std::string Combat_Wait::getStringUk()
	{
		return "Зачекайте";
	}

	std::string Combat_Wait::getStringVi()
	{
		return "Chờ đợi";
	}

	std::string Combat_Wait::getStringZhCn()
	{
		return "等待";
	}

	std::string Combat_Wait::getStringZhTw()
	{
		return "等待";
	}
}
