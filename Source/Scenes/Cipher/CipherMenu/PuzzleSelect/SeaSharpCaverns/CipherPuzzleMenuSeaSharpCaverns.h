#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuSeaSharpCaverns : public CipherPuzzleSelectMenuBase
{
public:
	static void registerGlobalScene();

protected:
	CipherPuzzleMenuSeaSharpCaverns();
	~CipherPuzzleMenuSeaSharpCaverns();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuSeaSharpCaverns* instance;
};
