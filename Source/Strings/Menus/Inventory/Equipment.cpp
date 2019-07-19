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
		return "المخزون";
	}

	std::string Menus_Inventory_Equipment::getStringBg()
	{
		return "Складова наличност";
	}

	std::string Menus_Inventory_Equipment::getStringCs()
	{
		return "Inventář";
	}

	std::string Menus_Inventory_Equipment::getStringDa()
	{
		return "Beholdning";
	}

	std::string Menus_Inventory_Equipment::getStringDe()
	{
		return "Inventar";
	}

	std::string Menus_Inventory_Equipment::getStringEl()
	{
		return "Καταγραφή εμπορευμάτων";
	}

	std::string Menus_Inventory_Equipment::getStringEn()
	{
		return "Inventory";
	}

	std::string Menus_Inventory_Equipment::getStringEs()
	{
		return "Inventario";
	}

	std::string Menus_Inventory_Equipment::getStringEs419()
	{
		return "Inventario";
	}

	std::string Menus_Inventory_Equipment::getStringFi()
	{
		return "inventaario";
	}

	std::string Menus_Inventory_Equipment::getStringFr()
	{
		return "Inventaire";
	}

	std::string Menus_Inventory_Equipment::getStringHu()
	{
		return "Leltár";
	}

	std::string Menus_Inventory_Equipment::getStringIt()
	{
		return "Inventario";
	}

	std::string Menus_Inventory_Equipment::getStringJa()
	{
		return "在庫";
	}

	std::string Menus_Inventory_Equipment::getStringKo()
	{
		return "목록";
	}

	std::string Menus_Inventory_Equipment::getStringNl()
	{
		return "Inventaris";
	}

	std::string Menus_Inventory_Equipment::getStringNo()
	{
		return "Inventar";
	}

	std::string Menus_Inventory_Equipment::getStringPl()
	{
		return "Inwentarz";
	}

	std::string Menus_Inventory_Equipment::getStringPt()
	{
		return "Inventário";
	}

	std::string Menus_Inventory_Equipment::getStringPtBr()
	{
		return "Inventário";
	}

	std::string Menus_Inventory_Equipment::getStringRo()
	{
		return "Inventar";
	}

	std::string Menus_Inventory_Equipment::getStringRu()
	{
		return "инвентарь";
	}

	std::string Menus_Inventory_Equipment::getStringSv()
	{
		return "Lager";
	}

	std::string Menus_Inventory_Equipment::getStringTh()
	{
		return "สินค้าคงคลัง";
	}

	std::string Menus_Inventory_Equipment::getStringTr()
	{
		return "Envanter";
	}

	std::string Menus_Inventory_Equipment::getStringUk()
	{
		return "Інвентаризація";
	}

	std::string Menus_Inventory_Equipment::getStringVi()
	{
		return "Hàng tồn kho";
	}

	std::string Menus_Inventory_Equipment::getStringZhCn()
	{
		return "库存";
	}

	std::string Menus_Inventory_Equipment::getStringZhTw()
	{
		return "庫存";
	}
}
