////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Equipment.h"

namespace Strings
{
	Menus_Inventory_Equipment* Menus_Inventory_Equipment::create()
	{
		Menus_Inventory_Equipment* instance = new Menus_Inventory_Equipment();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Menus_Inventory_Equipment::clone()
	{
		LocalizedString* clonedString = Menus_Inventory_Equipment::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Menus_Inventory_Equipment::Menus_Inventory_Equipment() : LocalizedString()
	{
	}

	Menus_Inventory_Equipment::~Menus_Inventory_Equipment()
	{
	}

	std::string Menus_Inventory_Equipment::getStringIdentifier()
	{
		return "Menus_Inventory_Equipment";
	}

	std::string Menus_Inventory_Equipment::getStringAr()
	{
		return "الرجعية";
	}

	std::string Menus_Inventory_Equipment::getStringBg()
	{
		return "оборудване";
	}

	std::string Menus_Inventory_Equipment::getStringCs()
	{
		return "Zařízení";
	}

	std::string Menus_Inventory_Equipment::getStringDa()
	{
		return "Udstyr";
	}

	std::string Menus_Inventory_Equipment::getStringDe()
	{
		return "Ausrüstung";
	}

	std::string Menus_Inventory_Equipment::getStringEl()
	{
		return "Εξοπλισμός";
	}

	std::string Menus_Inventory_Equipment::getStringEn()
	{
		return "Equipment";
	}

	std::string Menus_Inventory_Equipment::getStringEs()
	{
		return "Equipo";
	}

	std::string Menus_Inventory_Equipment::getStringEs419()
	{
		return "Equipo";
	}

	std::string Menus_Inventory_Equipment::getStringFi()
	{
		return "Laitteet";
	}

	std::string Menus_Inventory_Equipment::getStringFr()
	{
		return "Équipement";
	}

	std::string Menus_Inventory_Equipment::getStringHu()
	{
		return "Felszerelés";
	}

	std::string Menus_Inventory_Equipment::getStringIt()
	{
		return "attrezzatura";
	}

	std::string Menus_Inventory_Equipment::getStringJa()
	{
		return "装置";
	}

	std::string Menus_Inventory_Equipment::getStringKo()
	{
		return "장비";
	}

	std::string Menus_Inventory_Equipment::getStringNl()
	{
		return "uitrusting";
	}

	std::string Menus_Inventory_Equipment::getStringNo()
	{
		return "Utstyr";
	}

	std::string Menus_Inventory_Equipment::getStringPl()
	{
		return "Sprzęt";
	}

	std::string Menus_Inventory_Equipment::getStringPt()
	{
		return "Equipamento";
	}

	std::string Menus_Inventory_Equipment::getStringPtBr()
	{
		return "Equipamento";
	}

	std::string Menus_Inventory_Equipment::getStringRo()
	{
		return "echipament";
	}

	std::string Menus_Inventory_Equipment::getStringRu()
	{
		return "Оборудование";
	}

	std::string Menus_Inventory_Equipment::getStringSv()
	{
		return "Utrustning";
	}

	std::string Menus_Inventory_Equipment::getStringTh()
	{
		return "อุปกรณ์";
	}

	std::string Menus_Inventory_Equipment::getStringTr()
	{
		return "ekipman";
	}

	std::string Menus_Inventory_Equipment::getStringUk()
	{
		return "Обладнання";
	}

	std::string Menus_Inventory_Equipment::getStringVi()
	{
		return "Trang thiết bị";
	}

	std::string Menus_Inventory_Equipment::getStringZhCn()
	{
		return "设备";
	}

	std::string Menus_Inventory_Equipment::getStringZhTw()
	{
		return "設備";
	}
}
