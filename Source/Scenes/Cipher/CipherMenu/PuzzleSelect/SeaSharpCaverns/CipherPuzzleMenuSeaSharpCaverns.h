#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuSeaSharpCaverns : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuSeaSharpCaverns* getInstance();

protected:
	CipherPuzzleMenuSeaSharpCaverns();
	~CipherPuzzleMenuSeaSharpCaverns();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuSeaSharpCaverns* instance;
};
