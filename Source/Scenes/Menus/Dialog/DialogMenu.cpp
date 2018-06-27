#include "DialogMenu.h"

DialogMenu * DialogMenu::loadDialogFromFile(std::string filePath)
{
	return DialogMenu::loadDialogFromJson(FileUtils::getInstance()->getStringFromFile(filePath.c_str()));
}

DialogMenu * DialogMenu::loadDialogFromJson(std::string json)
{
	Document document = Document();
	document.Parse<0>(json.c_str());

	std::string dialogText = document.HasMember("Dialog") ? document["Dialog"].GetString() : "";
	TextMood textMood = document.HasMember("TextMood") ? DialogMenu::stringToTextMood(document["TextMood"].GetString()) : TextMood::Normal;
	Speaker speaker = document.HasMember("Speaker") ? DialogMenu::stringToSpeaker(document["Speaker"].GetString()) : Speaker::NoSpeaker;
	Portrait portraitLeft = document.HasMember("PortraitLeft") ? DialogMenu::stringToPortrait(document["PortraitLeft"].GetString()) : Portrait::NoPortrait;
	Portrait portraitRight = document.HasMember("PortraitRight") ? DialogMenu::stringToPortrait(document["PortraitRight"].GetString()) : Portrait::NoPortrait;

	std::queue<std::pair<std::string, DialogMenu*>>* children = new std::queue<std::pair<std::string, DialogMenu*>>();

	if (document.HasMember("Choices"))
	{
		GenericArray<false, rapidjson::Value::ValueType> choicesArray = document["Choices"].GetArray();

		// Iterate through choices
		for (rapidjson::Value::ConstValueIterator choiceIterator = choicesArray.Begin(); choiceIterator != choicesArray.End(); ++choiceIterator)
		{
			// Parse the choice object
			for (auto member = choiceIterator->MemberBegin(); member != choiceIterator->MemberEnd(); ++member)
			{
				auto choice = member->name.GetString();
				auto dialogObject = member->value.GetObjectW();

				rapidjson::StringBuffer stringBuffer;
				rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
				member->value.Accept(writer);
				std::string childString = stringBuffer.GetString();

				DialogMenu* child = DialogMenu::loadDialogFromJson(childString);
				children->push(std::pair<std::string, DialogMenu*>(choice, child));
			}
		}
	}

	DialogMenu* dialog = DialogMenu::create(portraitLeft, portraitRight, speaker, textMood, dialogText, children);

	return dialog;
}

DialogMenu* DialogMenu::create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::queue<std::pair<std::string, DialogMenu*>>* children)
{
	DialogMenu* dialogMenu = new DialogMenu(portraitLeft, portraitRight, speaker, textMood, text, children);

	dialogMenu->autorelease();

	return dialogMenu;
}

DialogMenu::DialogMenu(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::queue<std::pair<std::string, DialogMenu*>>* children)
{
	this->spriteLeft = this->getPortraitNode(portraitLeft, false);
	this->spriteRight = this->getPortraitNode(portraitRight, true);

	this->dialogText = Label::create(text, Resources::Fonts_Montserrat_Medium, 24);
	this->dialogText->enableWrap(true);
	this->dialogText->setDimensions(1024.0f, 224.0f);

	DrawNode* stencilLeft = DrawNode::create();
	DrawNode* stencilRight = DrawNode::create();
	stencilLeft->drawSolidCircle(Vec2(12.0f, 0.0f), 256.0f / 2.0f, 0.0f, 48.0f, Color4F::GREEN);
	stencilRight->drawSolidCircle(Vec2(-12.0f, 0.0f), 256.0f / 2.0f, 0.0f, 48.0f, Color4F::GREEN);

	// Enable to debug clipping:
	// this->addChild(stencilLeft);
	// this->addChild(stencilRight);

	this->dialogMenu = Sprite::create(Resources::Menus_DialogMenu_DialogBox);
	this->spriteLeftClip = ClippingNode::create(stencilLeft);
	this->spriteRightClip = ClippingNode::create(stencilRight);
	this->frameLeft = Sprite::create(Resources::Menus_DialogMenu_DialogFrameLeft);
	this->frameRight = Sprite::create(Resources::Menus_DialogMenu_DialogFrameRight);

	switch (speaker)
	{
	case Speaker::NoSpeaker:
		this->dialogText->setAlignment(TextHAlignment::CENTER);
		break;
	case Speaker::Left:
		this->dialogText->setAlignment(TextHAlignment::LEFT);
		break;
	case Speaker::Right:
		this->dialogText->setAlignment(TextHAlignment::RIGHT);
		break;
	}

	switch (textMood)
	{
	case TextMood::Normal:
		this->dialogText->setColor(Color3B::WHITE);
		break;
	case TextMood::Calm:
		this->dialogText->setColor(Color3B(0x91, 0xb6, 0xd8));
		break;
	case TextMood::Angry:
		this->dialogText->setColor(Color3B(0xcd, 0x4f, 0x39));
		break;
	}

	this->dialogChildren = new std::vector<std::pair<MenuLabel*, DialogMenu*>>();

	while (children->size() > 0)
	{
		std::pair<std::string, DialogMenu*> choiceDialogPair = children->front();
		children->pop();

		std::string choice = choiceDialogPair.first;
		DialogMenu* dialogMenu = choiceDialogPair.second;

		MenuLabel* label = MenuLabel::create(choice, Resources::Fonts_Montserrat_Medium, 24);
		label->setColor(Color4B::YELLOW);
		label->setHoverColor(Color4B(0x6c, 0xa5, 0xad, 0xff));
		label->setGlowColor(Color4B::WHITE);
		label->setCallback(CC_CALLBACK_1(DialogMenu::onChooseDialog, this));

		this->dialogChildren->push_back(std::pair<MenuLabel*, DialogMenu*>(label, dialogMenu));
		dialogMenu->retain();
	}

	delete(children);

	this->initializePositions();

	this->addChild(this->dialogMenu);
	this->spriteLeftClip->addChild(this->spriteLeft);
	this->spriteRightClip->addChild(this->spriteRight);
	this->addChild(this->spriteLeftClip);
	this->addChild(this->spriteRightClip);
	this->addChild(this->frameLeft);
	this->addChild(this->frameRight);
	this->addChild(this->dialogText);

	for (auto iterator = this->dialogChildren->begin(); iterator != this->dialogChildren->end(); ++iterator)
	{
		MenuLabel* label = (*iterator).first;

		this->addChild(label);
	}
}

DialogMenu::~DialogMenu()
{
	delete(this->dialogChildren);
}

void DialogMenu::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->dialogMenu->setPosition(Vec2(visibleSize.width / 2.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
	this->frameLeft->setPosition(Vec2(visibleSize.width / 2.0f - 744.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
	this->frameRight->setPosition(Vec2(visibleSize.width / 2.0f + 744.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
	this->spriteLeftClip->setPosition(Vec2(visibleSize.width / 2.0f - 744.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
	this->spriteRightClip->setPosition(Vec2(visibleSize.width / 2.0f + 744.0f, this->dialogMenu->getContentSize().height / 2.0f + 16.0f));
	this->dialogText->setPosition(Vec2(visibleSize.width / 2.0f, this->dialogMenu->getContentSize().height / 2.0f - 16.0f));

	int index = 0;
	int count = (int)this->dialogChildren->size();

	for (auto iterator = this->dialogChildren->begin(); iterator != this->dialogChildren->end(); ++iterator)
	{
		Vec2 pos = Vec2(visibleSize.width / 2.0f, this->dialogMenu->getContentSize().height / 2.0f);

		switch (count)
		{
		case 1:
			switch (index)
			{
			case 0:
				pos.y -= 64.0f;
				break;
			}
			break;
		case 2:
			switch (index)
			{
			case 0:
				pos.x -= 256.0f;
				pos.y -= 64.0f;
				break;
			case 1:
				pos.x += 256.0f;
				pos.y -= 64.0f;
				break;
			}
			break;
		case 3:
			switch (index)
			{
			case 0:
				pos.x -= 312.0f;
				pos.y -= 64.0f;
				break;
			case 1:
				pos.y -= 64.0f;
				break;
			case 2:
				pos.x += 312.0f;
				pos.y -= 64.0f;
				break;
			}
			break;
		default:
			break;
		}

		iterator->first->setPosition(pos);
		index++;
	}
}

void DialogMenu::onChooseDialog(MenuLabel* dialogMenu)
{
	for (auto iterator = this->dialogChildren->begin(); iterator != this->dialogChildren->end(); ++iterator)
	{
		auto value = (*iterator);

		if (value.first == dialogMenu)
		{
			// Open the dialog from the selected choice
			DialogEvents::TriggerDialog(DialogEvents::DialogOpenArgs("")); // value.second
			return;
		}
	}
}

Node* DialogMenu::getPortraitNode(Portrait portrait, bool isRight)
{
	switch (portrait)
	{
	case Portrait::Player:
	{
		Node * node = Node::create();
		Sprite* background = Sprite::create(Resources::Menus_DialogMenu_JungleBackground);
		FloatingSprite * sprite = FloatingSprite::create(Resources::Entities_Player_SquallyBase, Vec2(2.0f, -24.0f), Vec2(6.25f, 6.25f));
		sprite->setFlippedX(isRight);

		ParticleSystem* starParticles = ParticleSystemQuad::create(Resources::Particles_ColorfulStars);

		node->addChild(background);
		node->addChild(starParticles);
		node->addChild(sprite);

		return node;
	}
	case Portrait::AI:
	{
		Node * node = Node::create();
		Sprite* background = Sprite::create(Resources::Menus_DialogMenu_ShipBackground);
		FloatingSprite * sprite = FloatingSprite::create(Resources::Menus_DialogMenu_AI, Vec2(2.0f, -24.0f), Vec2(6.25f, 6.25f));
		sprite->setFlippedX(isRight);

		ParticleSystem* staticParticles = ParticleSystemQuad::create(Resources::Particles_Static);
		ParticleSystem* sparkParticles = ParticleSystemQuad::create(Resources::Particles_Spark);
		ParticleSystem* sparkParticlesBack = ParticleSystemQuad::create(Resources::Particles_Spark);

		CallFunc* triggerParticles = CallFunc::create([sprite, sparkParticles]()
		{
			sparkParticles->setSourcePosition(sprite->getPosition() + Vec2(-32.0f, -64.0f));
			sparkParticles->start();
		});

		CallFunc* triggerBackParticles = CallFunc::create([sprite, sparkParticlesBack]()
		{
			sparkParticlesBack->setSourcePosition(sprite->getPosition() + Vec2(20.0f, 72.0f));
			sparkParticlesBack->start();
		});

		sparkParticles->runAction(RepeatForever::create(Sequence::create(triggerParticles, DelayTime::create(7.14f), nullptr)));
		sparkParticlesBack->runAction(RepeatForever::create(Sequence::create(triggerBackParticles, DelayTime::create(5.73f), nullptr)));

		node->addChild(background);
		node->addChild(sparkParticlesBack);
		node->addChild(sprite);
		node->addChild(sparkParticles);
		node->addChild(staticParticles);

		return node;
	}
	case Portrait::NoPortrait:
	default:
	{
		return Sprite::create();
	}
	}
}

DialogMenu::Portrait DialogMenu::stringToPortrait(std::string portraitNameString)
{
	if (portraitNameString == "Player")
	{
		return Portrait::Player;
	}
	else if (portraitNameString == "AI")
	{
		return Portrait::AI;
	}

	return Portrait::NoPortrait;
}

DialogMenu::Speaker DialogMenu::stringToSpeaker(std::string speakerString)
{
	if (speakerString == "Left")
	{
		return Speaker::Left;
	}
	else if (speakerString == "Right")
	{
		return Speaker::Right;
	}

	return Speaker::NoSpeaker;
}

DialogMenu::TextMood DialogMenu::stringToTextMood(std::string textMoodString)
{
	return TextMood::Normal;
}
