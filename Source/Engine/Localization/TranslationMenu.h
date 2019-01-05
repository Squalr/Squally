#pragma once

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/GlobalNode.h"

namespace cocos2d
{
	class DrawNode;
	class Event;
	class Sprite;

	namespace ui
	{
		class UICCTextField;
	}
}

class LocalizedLabel;
class TextMenuSprite;
class TextWindow;

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
	void onTranslationMenuOpen(LocalizationEvents::TranslationBeginEditArgs* args);
	void onCancelClick();
	void onSubmitClick();

	cocos2d::Node* previousFocus;
	cocos2d::Sprite* menuBackground;
	LocalizedLabel* title;
	LocalizedLabel* englishTitle;
	LocalizedLabel* englishTranslation;
	LocalizedLabel* nativeTitle;
	LocalizedLabel* oldTranslation;
	LocalizedLabel* newTranslationTitle;
	cocos2d::ui::UICCTextField* newTranslation;
	TextMenuSprite* cancelButton;
	TextMenuSprite* submitButton;
	LocalizedString* editTarget;

	static TranslationMenu* instance;
	static const cocos2d::Size InputSize;
};
