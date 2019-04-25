#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuVoidStar : public CipherPuzzleSelectMenuBase
{
public:
	static void registerGlobalScene();

protected:
	CipherPuzzleMenuVoidStar();
	~CipherPuzzleMenuVoidStar();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuVoidStar* instance;
};
