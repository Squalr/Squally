////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "Resume.h"

namespace Strings
{
	Menus_Resume* Menus_Resume::create()
	{
		Menus_Resume* instance = new Menus_Resume();

		instance->autorelease();

		return instance;
	}
	
	LocalizedString* Menus_Resume::clone()
	{
		LocalizedString* clonedString = Menus_Resume::create();
		
		this->copyAttributesTo(clonedString);
		
		return clonedString;
	}

	Menus_Resume::Menus_Resume() : LocalizedString()
	{
	}

	Menus_Resume::~Menus_Resume()
	{
	}

	std::string Menus_Resume::getStringIdentifier()
	{
		return "Menus_Resume";
	}

	std::string Menus_Resume::getStringAr()
	{
		return "استئنف";
	}

	std::string Menus_Resume::getStringBg()
	{
		return "Продължи";
	}

	std::string Menus_Resume::getStringCs()
	{
		return "pokračovat ve hře";
	}

	std::string Menus_Resume::getStringDa()
	{
		return "Genoptag";
	}

	std::string Menus_Resume::getStringDe()
	{
		return "Fortsetzen";
	}

	std::string Menus_Resume::getStringEl()
	{
		return "συνέχιση παιχνιδιού";
	}

	std::string Menus_Resume::getStringEn()
	{
		return "Resume";
	}

	std::string Menus_Resume::getStringEs()
	{
		return "Reanudar";
	}

	std::string Menus_Resume::getStringEs419()
	{
		return "Reanudar";
	}

	std::string Menus_Resume::getStringFi()
	{
		return "Jatkaa";
	}

	std::string Menus_Resume::getStringFr()
	{
		return "Reprendre";
	}

	std::string Menus_Resume::getStringHu()
	{
		return "Visszanyer";
	}

	std::string Menus_Resume::getStringIt()
	{
		return "Riprendere";
	}

	std::string Menus_Resume::getStringJa()
	{
		return "ゲームを再開";
	}

	std::string Menus_Resume::getStringKo()
	{
		return "게임을 계속하다";
	}

	std::string Menus_Resume::getStringNl()
	{
		return "Hervatten";
	}

	std::string Menus_Resume::getStringNo()
	{
		return "Fortsett";
	}

	std::string Menus_Resume::getStringPl()
	{
		return "Kontynuuj grę";
	}

	std::string Menus_Resume::getStringPt()
	{
		return "Retomar o jogo";
	}

	std::string Menus_Resume::getStringPtBr()
	{
		return "Retomar o jogo";
	}

	std::string Menus_Resume::getStringRo()
	{
		return "Relua jocul";
	}

	std::string Menus_Resume::getStringRu()
	{
		return "продолжить игру";
	}

	std::string Menus_Resume::getStringSv()
	{
		return "återupptag spelet";
	}

	std::string Menus_Resume::getStringTh()
	{
		return "กลับสู่เกม";
	}

	std::string Menus_Resume::getStringTr()
	{
		return "oyuna devam et";
	}

	std::string Menus_Resume::getStringUk()
	{
		return "відновити гру";
	}

	std::string Menus_Resume::getStringVi()
	{
		return "tiếp tục trò chơi";
	}

	std::string Menus_Resume::getStringZhCn()
	{
		return "游戏继续";
	}

	std::string Menus_Resume::getStringZhTw()
	{
		return "遊戲繼續";
	}
}
