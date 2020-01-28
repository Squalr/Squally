#include "TypeWriterEffect.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/StrUtils.h"

const float TypeWriterEffect::DefaultDelayPerLetter = 0.025f;

using namespace cocos2d;

void TypeWriterEffect::runTypeWriterEffect(LocalizedLabel* label, std::function<void()> onEffectFinishedCallback, float delayPerLetter)
{
	if (label == nullptr || label->localizedString == nullptr)
	{
		if (onEffectFinishedCallback != nullptr)
		{
			onEffectFinishedCallback();
		}
		
		return;
	}

	int max = label->getStringLength();

	// We have to add events the old way -- LocalizedLabels inherit from a cocos label, not a SmartNode
	label->getEventDispatcher()->addCustomEventListener(LocalizationEvents::BeforeLocaleChangeEvent, [=](EventCustom* args)
	{
		if (label == nullptr)
		{
			return;
		}

		for (int i = 0; i < max; i++)
		{
			Sprite* letter = label->getLetter(i);

			if (letter != nullptr)
			{
				letter->stopAllActions();
				letter->setTextureAtlas(nullptr);
			}
		}

		label->_contentDirty = true;
		label->_letters.clear();
	});

	int strLen = StrUtils::unicodeStrLen(label->localizedString->getString());
	int strLenEn = StrUtils::unicodeStrLen(label->localizedString->getStringByLanguage(LanguageType::ENGLISH));

	// I don't know how fast characters should appear in other locales -- just normalize them to the speed of english
	delayPerLetter = (strLen <= 0) ? delayPerLetter : (delayPerLetter * ((float)strLenEn / (float)strLen));

	for (int i = 0; i < max; i++)
	{
		if (label->getLetter(i) != nullptr)
		{
			label->getLetter(i)->setOpacity(0);
			label->getLetter(i)->runAction(Sequence::create(
				DelayTime::create((float)i * delayPerLetter),
				FadeTo::create(0.1f, 255),
				nullptr
			));
		}
	}

	if (onEffectFinishedCallback != nullptr)
	{
		label->runAction(Sequence::create(
			DelayTime::create((float)max * delayPerLetter),
			CallFunc::create([=]()
			{
				onEffectFinishedCallback();
			}),
			nullptr
		));
	}
}

void TypeWriterEffect::cancelEffect(LocalizedLabel* label)
{
	if (label == nullptr || label->localizedString == nullptr)
	{
		return;
	}

	int max = label->getStringLength();

	for (int i = 0; i < max; i++)
	{
		if (label->getLetter(i) != nullptr)
		{
			label->getLetter(i)->stopAllActions();
		}
	}
	
	label->removeLetters();
}
