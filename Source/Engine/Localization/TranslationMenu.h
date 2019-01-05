#pragma once

#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class Event;
	class Sprite;
}

class TranslationMenu : public GlobalNode
{
public:
	static void registerGlobalNode();
private:
	typedef GlobalNode super;
	TranslationMenu();
	virtual ~TranslationMenu();

	static TranslationMenu* getInstance();
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* menuBackground;
	static TranslationMenu* instance;
};
