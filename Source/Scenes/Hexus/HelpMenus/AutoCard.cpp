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
    this->activeCard = nullptr;
    this->cardScale = Card::cardScale;
    this->displayType = DisplayType::Binary;

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
    this->currentAttack = (this->currentAttack + 1) % 15;

    this->updateToggle();
}

void AutoCard::decrementAttack()
{
    this->currentAttack = (this->currentAttack - 1) % 15;

    this->updateToggle();
}

void AutoCard::updateToggle()
{
    if (this->activeCard != nullptr)
    {
        this->cardNode->removeChild(this->activeCard);
    }

    switch(this->currentAttack)
    {
        default:
        case 0:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary0));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal0));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex0));
                    break;
                }
            }

            break;
        }
        case 1:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary1));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal1));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex1));
                    break;
                }
            }

            break;
        }
        case 2:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary2));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal2));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex2));
                    break;
                }
            }
            
            break;
        }
        case 3:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary3));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal3));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex3));
                    break;
                }
            }
            
            break;
        }
        case 4:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary4));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal4));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex4));
                    break;
                }
            }
            
            break;
        }
        case 5:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary5));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal5));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex5));
                    break;
                }
            }
            
            break;
        }
        case 6:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary6));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal6));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex6));
                    break;
                }
            }
            
            break;
        }
        case 7:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary7));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal7));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex7));
                    break;
                }
            }
            
            break;
        }
        case 8:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary8));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal8));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex8));
                    break;
                }
            }
            
            break;
        }
        case 9:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary9));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal9));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex9));
                    break;
                }
            }
            
            break;
        }
        case 10:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary10));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal10));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex10));
                    break;
                }
            }
            
            break;
        }
        case 11:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary11));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal11));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex11));
                    break;
                }
            }
            
            break;
        }
        case 12:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary12));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal12));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex12));
                    break;
                }
            }
            
            break;
        }
        case 13:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary13));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal13));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex13));
                    break;
                }
            }
            
            break;
        }
        case 14:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary14));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal14));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex14));
                    break;
                }
            }
            
            break;
        }
        case 15:
        {
            switch(this->displayType)
            {
                default:
                case DisplayType::Binary:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary15));
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal15));
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex15));
                    break;
                }
            }
            
            break;
        }
    }

    this->activeCard->setScale(this->cardScale);
    this->activeCard->reveal();
    this->activeCard->disableInteraction();

    this->cardNode->addChild(this->activeCard);
}
