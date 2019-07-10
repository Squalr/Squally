#pragma once

#include "Scenes/Cipher/CipherMenu/PuzzleSelect/CipherPuzzleSelectMenuBase.h"

class CipherPuzzleMenuLambdaCrypts : public CipherPuzzleSelectMenuBase
{
public:
	static CipherPuzzleMenuLambdaCrypts* getInstance();

protected:
	CipherPuzzleMenuLambdaCrypts();
	~CipherPuzzleMenuLambdaCrypts();

private:
	typedef CipherPuzzleSelectMenuBase super;

	static std::string ChapterSavekey;
	static CipherPuzzleMenuLambdaCrypts* instance;
};
