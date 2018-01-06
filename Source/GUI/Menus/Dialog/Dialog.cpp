#include "Dialog.h"

Dialog * Dialog::loadDialogFromFile(std::string filePath)
{
	return Dialog::loadDialogFromJson(FileUtils::getInstance()->getStringFromFile(filePath.c_str()));
}

Dialog * Dialog::loadDialogFromJson(std::string json)
{
	Document document = Document();
	document.Parse<0>(json.c_str());

	std::string dialogText = document.HasMember("Dialog") ? document["Dialog"].GetString() : "";
	TextMood textMood = document.HasMember("TextMood") ? Dialog::stringToTextMood(document["TextMood"].GetString()) : TextMood::Normal;
	Speaker speaker = document.HasMember("Speaker") ? Dialog::stringToSpeaker(document["Speaker"].GetString()) : Speaker::NoSpeaker;
	Portrait portraitLeft = document.HasMember("PortraitLeft") ? Dialog::stringToPortrait(document["PortraitLeft"].GetString()) : Portrait::NoPortrait;
	Portrait portraitRight = document.HasMember("PortraitRight") ? Dialog::stringToPortrait(document["PortraitRight"].GetString()) : Portrait::NoPortrait;

	std::map<std::string, Dialog*>* children = new std::map<std::string, Dialog*>();

	if (document.HasMember("Children"))
	{
		GenericArray<false, rapidjson::Value::ValueType> childrenArr = document["Children"].GetArray();
		int index = 0;

		for (rapidjson::Value::ConstValueIterator iterator = childrenArr.Begin(); iterator != childrenArr.End(); ++iterator)
		{
			rapidjson::StringBuffer stringBuffer;
			rapidjson::Writer<rapidjson::StringBuffer> writer(stringBuffer);
			document["Children"][index].Accept(writer);

			Dialog* child = Dialog::loadDialogFromJson(stringBuffer.GetString());
			children->insert_or_assign(child->dialogChoice, child);
			index++;
		}
	}

	Dialog* dialog = Dialog::create(portraitLeft, portraitRight, speaker, textMood, dialogText, children);
	dialog->dialogChoice = document["Choice"].GetString();

	return dialog;
}

Dialog* Dialog::create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::map<std::string, Dialog*>* children)
{
	Dialog* dialog = new Dialog(portraitLeft, portraitRight, speaker, textMood, text, children);

	dialog->autorelease();

	return dialog;
}

Dialog::Dialog(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text, std::map<std::string, Dialog*>* children)
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

	this->spriteLeftClip = ClippingNode::create(stencilLeft);
	this->spriteRightClip = ClippingNode::create(stencilRight);

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

	this->dialogChildren = new std::map<MenuLabel*, Dialog*>();

	for (auto iterator = children->begin(); iterator != children->end(); ++iterator)
	{
		MenuLabel* label = MenuLabel::create(iterator->first, Resources::Fonts_Montserrat_Medium, 24);
		label->setCallback(CC_CALLBACK_1(Dialog::onChooseDialog, this));

		this->dialogChildren->insert_or_assign(label, iterator->second);
	}

	delete(children);

	this->initializePositions();

	this->spriteLeftClip->addChild(this->spriteLeft);
	this->spriteRightClip->addChild(this->spriteRight);
	this->addChild(this->spriteLeftClip);
	this->addChild(this->spriteRightClip);
	this->addChild(this->dialogText);

	for (auto iterator = this->dialogChildren->begin(); iterator != this->dialogChildren->end(); ++iterator)
	{
		this->addChild(iterator->first);
	}
}

Dialog::~Dialog()
{
	delete(this->dialogChildren);
}

void Dialog::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->spriteLeftClip->setPosition(Vec2(-732.0f, 16.0f));
	this->spriteRightClip->setPosition(Vec2(+732.0f, 16.0f));
	this->dialogText->setPosition(Vec2(0.0f, -16.0f));

	int index = 0;
	int count = (int)this->dialogChildren->size();

	for (auto iterator = this->dialogChildren->begin(); iterator != this->dialogChildren->end(); ++iterator)
	{
		Vec2 pos = Vec2(0.0f, 0.0f);

		switch (count)
		{
		case 1:
			switch (index)
			{
			case 0:
				pos.y -= 64.0f;
				break;
			}
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
		default:
			break;
		}

		iterator->first->setPosition(pos);
		index++;
	}
}

void Dialog::onChooseDialog(MenuLabel* dialogMenu)
{

}

Node* Dialog::getPortraitNode(Portrait portrait, bool isRight)
{
	switch (portrait)
	{
	case Portrait::Player:
	{
		Node * node = Node::create();
		FloatingSprite * sprite = FloatingSprite::create(Resources::Menus_DialogMenu_PlayerPortrait, Vec2(2.0f, -24.0f), Vec2(6.25f, 6.25f));
		sprite->setFlippedX(isRight);

		ParticleSystem* starParticles = ParticleSystemQuad::create(Resources::Particles_ColorfulStars);

		node->addChild(starParticles);
		node->addChild(sprite);

		return node;
	}
	case Portrait::AI:
	{
		Node * node = Node::create();
		FloatingSprite * sprite = FloatingSprite::create(Resources::Menus_DialogMenu_AI, Vec2(2.0f, -24.0f), Vec2(6.25f, 6.25f));
		sprite->setFlippedX(isRight);

		ParticleSystem* netherParticles = ParticleSystemQuad::create(Resources::Particles_BlueNether);
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

		node->addChild(netherParticles);
		node->addChild(sparkParticlesBack);
		node->addChild(sprite);
		node->addChild(sparkParticles);

		return node;
	}
	case Portrait::NoPortrait:
	default:
	{
		return Sprite::create();
	}
	}
}

Dialog::Portrait Dialog::stringToPortrait(std::string portraitNameString)
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

Dialog::Speaker Dialog::stringToSpeaker(std::string speakerString)
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

Dialog::TextMood Dialog::stringToTextMood(std::string textMoodString)
{
	return TextMood::Normal;
}
