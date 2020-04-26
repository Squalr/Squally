#include "TypeWriterEffect.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/LocalizationEvents.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Utils/StrUtils.h"

const float TypeWriterEffect::DefaultDelayPerLetter = 0.025f;

using namespace cocos2d;

void TypeWriterEffect::runTypeWriterEffect(SmartNode* host, LocalizedLabel* label, std::function<void()> onEffectFinishedCallback, float delayPerLetter)
{
	if (host == nullptr || label == nullptr || label->localizedString == nullptr)
	{
		if (onEffectFinishedCallback != nullptr)
		{
			onEffectFinishedCallback();
		}
		
		return;
	}

	int max = label->getStringLength();
	int maxRealIndex = 0;

	// LocalizedStrings inherit from cocos labels, thus are not SmartNodes. For this reason, events are registered on a given host.
	host->addEventListenerIgnorePause(EventListenerCustom::create(LocalizationEvents::BeforeLocaleChangeEvent, [=](EventCustom* args)
	{
		if (label == nullptr)
		{
			return;
		}

		for (int index = 0; index < max; index++)
		{
			Sprite* letter = label->getLetter(index);

			if (letter != nullptr)
			{
				letter->stopAllActions();
				letter->setTextureAtlas(nullptr);
			}
		}

		label->_contentDirty = true;
		label->_letters.clear();
	}));

	// ZAC: Unicode string length fucks up with Zalgo text. Not working as intended.
	/*
	int strLen = StrUtils::unicodeStrLen(label->localizedString->getString());
	int strLenEn = StrUtils::unicodeStrLen(label->localizedString->getStringByLanguage(LanguageType::ENGLISH));

	// I don't know how fast characters should appear in other locales -- just normalize them to the speed of english
	// This has the added benefit that if anybody ever speed runs this, they can do it in any language.
	delayPerLetter = (strLen <= 0) ? delayPerLetter : (delayPerLetter * ((float)strLenEn / (float)strLen));
	*/

	for (int index = 0; index < max; index++)
	{
		Sprite* letter = label->getLetter(index);

		if (letter != nullptr)
		{
			int realIndex = letter->getTag();

			maxRealIndex = std::max(maxRealIndex, realIndex);

			letter->setOpacity(0);
			letter->runAction(Sequence::create(
				DelayTime::create((float)realIndex * delayPerLetter),
				FadeTo::create(0.1f, 255),
				nullptr
			));
		}
	}

	if (onEffectFinishedCallback != nullptr)
	{
		label->runAction(Sequence::create(
			DelayTime::create((float)maxRealIndex * delayPerLetter),
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

	for (int index = 0; index < max; index++)
	{
		Sprite* letter = label->getLetter(index);

		if (letter != nullptr)
		{
			letter->stopAllActions();
		}
	}
	
	label->removeLetters();
}
