#include "Dialog.h"

Dialog * Dialog::loadDialogFromFile(std::string filePath)
{
	return Dialog::loadDialogFromJson(FileUtils::getInstance()->getStringFromFile(filePath.c_str()));
}

Dialog * Dialog::loadDialogFromJson(std::string json)
{
	Document document = Document();
	document.Parse<0>(json.c_str());

	std::string dialogText = document["Dialog"].GetString();
	TextMood textMood = Dialog::stringToTextMood(document["TextMood"].GetString());
	Speaker speaker = Dialog::stringToSpeaker(document["Speaker"].GetString());
	Portrait portraitLeft = Dialog::stringToPortrait(document["SpeakerLeft"].GetString());
	Portrait portraitRight = Dialog::stringToPortrait(document["SpeakerRight"].GetString());
	GenericArray<false, rapidjson::Value::ValueType> children = document["Children"].GetArray();

	Dialog* dialog = Dialog::create(portraitLeft, portraitRight, speaker, textMood, dialogText);
	dialog->dialogChoice = document["Choice"].GetString();

	for (rapidjson::Value::ConstValueIterator iterator = children.Begin(); iterator != children.End(); ++iterator)
	{
		Dialog* child = Dialog::loadDialogFromJson(iterator->GetString());
		dialog->children->insert_or_assign(child->dialogChoice, child);
	}

	return dialog;
}

Dialog* Dialog::create(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text)
{
	Dialog* dialog = new Dialog(portraitLeft, portraitRight, speaker, textMood, text);

	dialog->autorelease();

	return dialog;
}

Dialog::Dialog(Portrait portraitLeft, Portrait portraitRight, Speaker speaker, TextMood textMood, std::string text)
{
	this->children = new std::map<std::string, Dialog*>();
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

	this->initializePositions();

	this->spriteLeftClip->addChild(this->spriteLeft);
	this->spriteRightClip->addChild(this->spriteRight);
	this->addChild(this->spriteLeftClip);
	this->addChild(this->spriteRightClip);
	this->addChild(this->dialogText);
}

Dialog::~Dialog()
{
	delete(this->children);
}

void Dialog::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->spriteLeftClip->setPosition(Vec2(visibleSize.width / 2 - 732, 16));
	this->spriteRightClip->setPosition(Vec2(visibleSize.width / 2 + 732, 16));
	this->dialogText->setPosition(Vec2(visibleSize.width / 2, -16));
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
