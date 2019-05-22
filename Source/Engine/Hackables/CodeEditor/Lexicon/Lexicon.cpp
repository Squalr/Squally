#include "Lexicon.h"

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPages.h"

using namespace cocos2d;

Lexicon* Lexicon::create()
{
	Lexicon* instance = new Lexicon();

	instance->autorelease();

	return instance;
}

Lexicon::Lexicon()
{
	this->pages = std::vector<LexiconPage*>();

	this->pages.push_back(NopPage::create());

	for (auto it = this->pages.begin(); it != this->pages.end(); it++)
	{
		this->addChild(*it);
	}
}

Lexicon::~Lexicon()
{
}