#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuVoidStar : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuVoidStar* getInstance();

protected:
	CipherPuzzleMenuVoidStar();
	~CipherPuzzleMenuVoidStar();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuVoidStar* instance;
};
