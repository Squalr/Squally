#pragma once
#include <set>
#include <string>
#include <vector>

#include "cocos/base/ccTypes.h"

#include "Engine/SmartNode.h"

class LexiconPage;

class Lexicon : public SmartNode
{
public:
	static Lexicon* create();

private:
	typedef SmartNode super;
	Lexicon();
	~Lexicon();

	std::vector<LexiconPage*> pages;
};
