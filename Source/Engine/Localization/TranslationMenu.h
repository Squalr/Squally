#pragma once

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/GlobalHud.h"

namespace cocos2d
{
	class DrawNode;
	class Event;
	class LayerColor;
	class Sprite;

	namespace ui
	{
		class UICCTextField;
	}
}

class LocalizedLabel;
class ClickableTextNode;
class TextWindow;

class TranslationMenu : public GlobalHud
{
public:
	static void registerGlobalNode();
private:
	typedef GlobalHud super;
	TranslationMenu();
	virtual ~TranslationMenu();

	static TranslationMenu* getInstance();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onTranslationMenuOpen(LocalizationEvents::TranslationBeginEditArgs* args);
	void onCancelClick();
	void onSubmitClick();

	cocos2d::Node* previousFocus;
	cocos2d::LayerColor* background;
	cocos2d::Sprite* menuBackground;
	LocalizedLabel* title;
	LocalizedLabel* englishTitle;
	LocalizedLabel* englishTranslation;
	LocalizedLabel* nativeTitle;
	LocalizedLabel* oldTranslation;
	LocalizedLabel* newTranslationTitle;
	cocos2d::ui::UICCTextField* newTranslation;
	ClickableTextNode* cancelButton;
	ClickableTextNode* submitButton;
	LocalizedString* editTarget;

	static TranslationMenu* instance;
	static const cocos2d::Size PreviousTranslationSize;
	static const cocos2d::Size InputSize;
};
