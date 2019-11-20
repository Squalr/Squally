#include "UIBoundObject.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

UIBoundObject* UIBoundObject::create(cocos2d::Node* referencedObject)
{
    UIBoundObject* instance = new UIBoundObject(referencedObject);

    instance->autorelease();

    return instance;
}

UIBoundObject::UIBoundObject(cocos2d::Node* referencedObject)
{
    this->referencedObject = referencedObject;
    this->originalParent = this->referencedObject == nullptr ? nullptr : this->referencedObject->getParent();
    this->originalCoords = Vec3::ZERO;
    this->originalScale = 1.0f;
    this->realCoords = Vec3::ZERO;
    this->realScale = 1.0f;
    this->eventKey = "";
    this->scheduleTarget = nullptr;
}

UIBoundObject::~UIBoundObject()
{
}

void UIBoundObject::onEnter()
{
    super::onEnter();

    if (this->referencedObject != nullptr && this->referencedObject->getParent() != this)
    {
        Vec3 position = this->referencedObject->getPosition3D();
        
        GameUtils::changeParent(this->referencedObject, this, false);

        this->referencedObject->setPosition3D(position);
    }

    this->scheduleUpdateTask();
}

void UIBoundObject::initializeListeners()
{
    super::initializeListeners();

    this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventReparentBindPrefix + std::to_string((unsigned long long)(this->referencedObject)), [=](EventCustom* eventCustom)
    {
        ObjectEvents::ReparentBindArgs* args = static_cast<ObjectEvents::ReparentBindArgs*>(eventCustom->getUserData());
        
        if (args != nullptr)
        {
            this->originalParent = args->newParent;
            this->scheduleUpdateTask();
        }
    }));

    this->addEventListenerIgnorePause(EventListenerCustom::create(ObjectEvents::EventUnbindObjectPrefix + std::to_string((unsigned long long)(this->referencedObject)), [=](EventCustom* eventCustom)
    {
        ObjectEvents::RelocateObjectArgs* args = static_cast<ObjectEvents::RelocateObjectArgs*>(eventCustom->getUserData());
        
        if (args != nullptr)
        {
            this->removeChild(referencedObject);

            if (this->getParent() != nullptr)
            {
                this->getParent()->removeChild(this);
            }
        }
    }));
}

void UIBoundObject::scheduleUpdateTask()
{
    if (this->scheduleTarget != nullptr && !this->eventKey.empty())
    {
        this->scheduleTarget->unschedule(eventKey);
    }

    static unsigned long long TaskId = 0;
    unsigned long long taskId = TaskId++;
    this->eventKey = "EVENT_UIBOUND_UPDATE_TASK_" + std::to_string(taskId);

   this->scheduleTarget = this->originalParent;

    if (this->scheduleTarget == nullptr)
    {
        this->scheduleTarget = this;
    }

    // Schedule the task on the original parent, that way if the original parent is disposed, update will not be called (avoiding a crash)
    this->scheduleTarget->schedule([=](float dt)
    {
        if (this->referencedObject == nullptr)
        {
            return;
        }

        this->realCoords = UIBoundObject::getRealCoords(this);
        this->realScale = UIBoundObject::getRealScale(this);
    }, 1.0f / 60.0f, this->eventKey);
}

Vec3 UIBoundObject::getRealCoords(UIBoundObject* uiBoundObject)
{
    if (uiBoundObject == nullptr || uiBoundObject->referencedObject == nullptr || uiBoundObject->originalParent == nullptr)
    {
        return Vec3::ZERO;
    }

    Vec3 thisCoords = GameUtils::getWorldCoords3D(uiBoundObject);
    Vec3 originalParentCoords = GameUtils::getWorldCoords3D(uiBoundObject->originalParent);
    Vec3 originalCoords = uiBoundObject->referencedObject->getPosition3D();
    float originalScale = GameUtils::getScale(uiBoundObject->originalParent);
    Vec3 anchorOffset = Vec3(
        0.5f * uiBoundObject->originalParent->getContentSize().width * originalScale,
        0.5f * uiBoundObject->originalParent->getContentSize().height * originalScale,
        0.0f
    );
    Vec3 delta = originalParentCoords - thisCoords + anchorOffset;

    return originalCoords + delta;
}

float UIBoundObject::getRealScale(UIBoundObject* uiBoundObject)
{
    if (uiBoundObject == nullptr || uiBoundObject->referencedObject == nullptr || uiBoundObject->originalParent == nullptr)
    {
        return 1.0f;
    }

    float parentScale = GameUtils::getScale(uiBoundObject->originalParent);

    return parentScale * uiBoundObject->referencedObject->getScale();
}

cocos2d::Node* UIBoundObject::getReferencedObject()
{
    return this->referencedObject;
}

cocos2d::Node* UIBoundObject::getOriginalParent()
{
    return this->originalParent;
}

void UIBoundObject::visit(Renderer *renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    if (this->referencedObject == nullptr)
    {
        return;
    }

    this->originalCoords = this->referencedObject->getPosition3D();
    this->originalScale = this->referencedObject->getScale();
    
    this->referencedObject->setPosition3D(this->realCoords);
    this->referencedObject->setScale(this->realScale);

	super::visit(renderer, parentTransform, parentFlags);

    this->referencedObject->setPosition3D(this->originalCoords);
    this->referencedObject->setScale(this->originalScale);
}
