#include "CipherPuzzleAtbash.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Scenes/Cipher/CipherState.h"

using namespace cocos2d;

const std::string CipherPuzzleAtbash::MapKeyAtbash = "atbash";

CipherPuzzleAtbash* CipherPuzzleAtbash::create()
{
	CipherPuzzleAtbash* instance = new CipherPuzzleAtbash();

	instance->autorelease();

	return instance;
}

CipherPuzzleAtbash::CipherPuzzleAtbash() : super(std::map<std::string, std::string>({
	 { "hzw", "sad" },
	 { "trm", "gin" },
	 { "YRIW", "BIRD" },
	 { "zix", "arc" },
	 { "SVM", "HEN" },
	 { "xork", "clip" },
	 { "grvi", "TiEr" },
}))
{
}

CipherPuzzleAtbash::~CipherPuzzleAtbash()
{
}
