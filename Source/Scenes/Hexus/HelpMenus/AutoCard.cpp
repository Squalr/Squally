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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary0), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal0), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex0), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary1), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal1), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex1), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary2), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal2), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex2), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary3), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal3), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex3), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary4), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal4), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex4), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary5), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal5), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex5), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary6), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal6), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex6), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary7), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal7), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex7), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary8), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal8), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex8), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary9), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal9), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex9), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary10), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal10), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex10), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary11), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal11), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex11), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary12), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal12), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex12), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary13), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal13), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex13), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary14), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal14), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex14), true, false);
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
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Binary15), true, false);
                    break;
                }
                case DisplayType::Decimal:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Decimal15), true, false);
                    break;
                }
                case DisplayType::Hex:
                {
                    this->activeCard = Card::create(Card::CardStyle::Earth, CardList::getInstance()->cardListByName.at(CardKeys::Hex15), true, false);
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
