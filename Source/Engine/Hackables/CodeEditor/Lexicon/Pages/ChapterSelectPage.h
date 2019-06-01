#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;

class ChapterSelectPage : public LexiconPage
{
public:
	static ChapterSelectPage* create();

	static const std::string Identifier;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	ChapterSelectPage();
	~ChapterSelectPage();

	cocos2d::Sprite* decorLine;
	LocalizedLabel* chapterSelectLabel;
	ClickableTextNode* dataChapterButton;
	ClickableTextNode* binaryChapterButton;
	ClickableTextNode* controlFlowChapterButton;
	ClickableTextNode* vectorChapterButton;
	ClickableTextNode* floatingPointChapterButton;
	LocalizedLabel* introText;
};
