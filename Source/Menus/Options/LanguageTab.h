#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
	class Sprite;
	class Label;
}

class LocalizedString;
class TextMenuSprite;

class LanguageTab : public SmartNode
{
public:
	static LanguageTab* create();

protected:
	LanguageTab();
	~LanguageTab();

private:
	typedef SmartNode super;

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;
	TextMenuSprite* constructLanguageButton(LocalizedString* string);

	std::vector<TextMenuSprite*> languageButtons;
};
