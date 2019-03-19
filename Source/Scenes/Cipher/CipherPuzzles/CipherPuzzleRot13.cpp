#include "CipherPuzzleRot13.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

const std::string CipherPuzzleRot13::MapKeyRot13 = "rot13";

CipherPuzzleRot13* CipherPuzzleRot13::create()
{
	CipherPuzzleRot13* instance = new CipherPuzzleRot13();

	instance->autorelease();

	return instance;
}

CipherPuzzleRot13::CipherPuzzleRot13() : super(std::map<std::string, std::string>({
	 { "yvsr", "life" },
	 { "ybir", "love" },
	 { "JnK", "WaX" },
	 { "gjb", "two" },
	 { "ELR", "RYE" },
	 { "cyf", "pls" },
	 { "ZNQ", "MAD" },
	 { "bXnL", "oKaY" },
}))
{
}

CipherPuzzleRot13::~CipherPuzzleRot13()
{
}
