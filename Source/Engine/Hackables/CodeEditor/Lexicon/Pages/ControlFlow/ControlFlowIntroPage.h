#pragma once

#include "Engine/Hackables/CodeEditor/Lexicon/Pages/LexiconPage.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class ControlFlowIntroPage : public LexiconPage
{
public:
	static ControlFlowIntroPage* create();

	static const std::string KeyControlFlowIntroPage;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	
private:
	typedef LexiconPage super;
	ControlFlowIntroPage();
	~ControlFlowIntroPage();

	cocos2d::Sprite* hourglassSprite;
	cocos2d::Sprite* chapterSprite;
	LocalizedLabel* introText;
	LocalizedLabel* titleLabel;
};
