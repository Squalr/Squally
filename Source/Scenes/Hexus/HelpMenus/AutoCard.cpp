#include "AutoCard.h"

#include "Engine/Utils/MathUtils.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

using namespace cocos2d;

AutoCard* AutoCard::create(int defaultAttack)
{
    AutoCard* instance = new AutoCard(defaultAttack);

    instance->autorelease();

    return instance;
}

AutoCard::AutoCard(int defaultAttack)
{
    this->currentAttack = defaultAttack;
    this->cardNode = Node::create();
	this->binaryCardMap = std::map<int, Card*>();
	this->decimalCardMap = std::map<int, Card*>();
	this->hexCardMap = std::map<int, Card*>();
	this->binaryCardFactory = std::map<int, std::function<Card*()>>();
	this->decimalCardFactory = std::map<int, std::function<Card*()>>();
	this->hexCardFactory = std::map<int, std::function<Card*()>>();
    this->activeCard = nullptr;
    this->cardScale = Card::cardScale;
    this->displayType = DisplayType::Binary;

    for (auto it = CardList::getInstance()->cardListByName.begin(); it != CardList::getInstance()->cardListByName.end(); it++)
    {
        CardData* cardData = (*it).second;
        
        switch(cardData->getCardType())
        {
            case CardData::CardType::Binary:
            {
                this->binaryCardFactory[cardData->getAttack()] = [=](){ return Card::create(Card::CardStyle::Earth, cardData, true, false); };
                break;
            }
            case CardData::CardType::Decimal:
            {
                this->decimalCardFactory[cardData->getAttack()] = [=](){ return Card::create(Card::CardStyle::Earth, cardData, true, false); };
                break;
            }
            case CardData::CardType::Hexidecimal:
            {
                this->hexCardFactory[cardData->getAttack()] = [=](){ return Card::create(Card::CardStyle::Earth, cardData, true, false); };
                break;
            }
            default:
            {
                continue;
            }
        }
    }

    this->addChild(this->cardNode);
}

AutoCard::~AutoCard()
{
}

void AutoCard::onEnter()
{
    super::onEnter();

    this->updateToggle();
}

int AutoCard::getAttack()
{
    return this->currentAttack;
}

void AutoCard::setDisplayType(DisplayType displayType)
{
    this->displayType = displayType;

    this->updateToggle();
}

AutoCard::DisplayType AutoCard::getDisplayType()
{
    return this->displayType;
}

void AutoCard::setCardScale(float cardScale)
{
    this->cardScale = cardScale;
}

void AutoCard::setAttack(int attack)
{
    this->currentAttack = MathUtils::clamp(attack, 0, 15);

    this->updateToggle();
}

void AutoCard::incrementAttack()
{
    this->currentAttack = MathUtils::wrappingNormalize(this->currentAttack + 1, 0, 15);

    this->updateToggle();
}

void AutoCard::decrementAttack()
{
    this->currentAttack = MathUtils::wrappingNormalize(this->currentAttack - 1, 0, 15);

    this->updateToggle();
}

void AutoCard::updateToggle()
{
    if (this->activeCard != nullptr)
    {
        this->activeCard->setVisible(false);
    }
    
    switch (this->displayType)
    {
        default:
        case DisplayType::Binary:
        {
            if (this->binaryCardMap.find(this->currentAttack) != this->binaryCardMap.end())
            {
                this->activeCard = this->binaryCardMap[this->currentAttack];
            }
            else
            {
                this->activeCard = this->binaryCardFactory[this->currentAttack]();
                this->binaryCardMap[this->currentAttack] = this->activeCard;
                this->cardNode->addChild(this->activeCard);
            }
            break;
        }
        case DisplayType::Decimal:
        {
            if (this->decimalCardMap.find(this->currentAttack) != this->decimalCardMap.end())
            {
                this->activeCard = this->decimalCardMap[this->currentAttack];
            }
            else
            {
                this->activeCard = this->decimalCardFactory[this->currentAttack]();
                this->decimalCardMap[this->currentAttack] = this->activeCard;
                this->cardNode->addChild(this->activeCard);
            }
            break;
        }
        case DisplayType::Hex:
        {
            if (this->hexCardMap.find(this->currentAttack) != this->hexCardMap.end())
            {
                this->activeCard = this->hexCardMap[this->currentAttack];
            }
            else
            {
                this->activeCard = this->hexCardFactory[this->currentAttack]();
                this->hexCardMap[this->currentAttack] = this->activeCard;
                this->cardNode->addChild(this->activeCard);
            }
            break;
        }
    }

    this->activeCard->setVisible(true);
    this->activeCard->setScale(this->cardScale);
    this->activeCard->reveal();
    this->activeCard->disableInteraction();
}
