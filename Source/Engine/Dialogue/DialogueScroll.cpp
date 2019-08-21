#include "DialogueScroll.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/DialogueEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/FX/TypeWriterEffect.h"

#include "Strings/Common/Empty.h"

using namespace cocos2d;

const Color4F DialogueScroll::PanelColor = Color4F(Color4B(189, 215, 221, 196));
const Color4F DialogueScroll::PanelEdgeColor = Color4F(Color4B(47, 71, 78, 196));
const Color4B DialogueScroll::PanelTextColor = Color4B(47, 71, 78, 255);
const float DialogueScroll::PanelBorderSize = 3.0f;

DialogueScroll* DialogueScroll::create()
{
	DialogueScroll* instance = new DialogueScroll();

	instance->autorelease();

	return instance;
}

DialogueScroll::DialogueScroll()
{
	this->panel = DrawNode::create(3.0f);
	this->text = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Common_Empty::create());

	this->text->setTextColor(DialogueScroll::PanelTextColor);

	this->panel->setOpacity(0);
	this->text->setOpacity(0);

	this->addChild(this->panel);
	this->addChild(this->text);
}

DialogueScroll::~DialogueScroll()
{
}

void DialogueScroll::initializePositions()
{
	super::initializePositions();
}

void DialogueScroll::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(DialogueEvents::EventDialogueOpen, [=](EventCustom* eventCustom)
	{
		DialogueEvents::DialogueOpenArgs* args = static_cast<DialogueEvents::DialogueOpenArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->runDialogue(args->dialogue);
		}
	}));
}

void DialogueScroll::runDialogue(LocalizedString* localizedString)
{
	const Size padding = Size(16.0f, 16.0f);
	const float centerAutoOffset = 256.0f;
	const Size triangleSize = Size(16.0f, 32.0f);

	this->panel->runAction(FadeTo::create(0.5f, 255));
	this->text->runAction(FadeTo::create(0.5f, 255));

	this->text->setLocalizedString(localizedString);
	this->text->setDimensions(1280.0f, 0.0f);
	this->text->setAnchorPoint(Vec2(0.5f, 0.0f));

	TypeWriterEffect::runTypeWriterEffect(this->text);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size dialogueSize = Size(visibleSize.width - 64.0f, 320.0f);
	Vec2 halfSize = Vec2(dialogueSize.width / 2.0f, dialogueSize.height / 2.0f);
	
	this->panel->clear();
	this->panel->drawSolidRect(-halfSize, halfSize, DialogueScroll::PanelColor);
	this->panel->drawRect(-halfSize, halfSize, DialogueScroll::PanelEdgeColor);
}

void DialogueScroll::hideDialogue()
{
	this->panel->runAction(FadeTo::create(0.5f, 0));
	this->text->runAction(FadeTo::create(0.5f, 0));
}
