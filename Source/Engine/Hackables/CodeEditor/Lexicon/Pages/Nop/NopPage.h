#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

class NopPage : public LexiconPage
{
public:
	static NopPage* create();
	
private:
	typedef LexiconPage super;
	NopPage();
	~NopPage();
};
