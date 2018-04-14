//
// Created by jeremy on 12/12/15.
//
#include "2d/CCSprite.h"
#include <sstream>

#include "CCAnimationNode.h"
#include "CCObjectFactory.h"

NS_CC_BEGIN

    enum CommandType {PlayOnce, PlayRepeat};

    struct EntityCommand {
        EntityCommand(CommandType type, SpriterEngine::EntityInstance* entity, EntityEvent onComplete)
                : type(type), entity(entity), onComplete(onComplete) {}
        CommandType type;
        std::unique_ptr<SpriterEngine::EntityInstance> entity;
        EntityEvent onComplete;
    };

    void doNothing(SpriterEngine::EntityInstance*) {}

    class AnimationNode::impl {
    public:
        impl(cocos2d::Node* parent, SpriteLoader loader, const std::string& scmlFile)
                : files(new CCFileFactory(parent,loader))
                , model(scmlFile, files, new CCObjectFactory(parent)) {}

        ~impl() {}

        void update(float dt)
        {
            files->resetSprites();
            auto removed =
                    std::remove_if(entities.begin(), entities.end(),
                                   [dt](const EntityCommand& cmd){
                                       auto pre_ratio = cmd.entity->getTimeRatio();
                                       cmd.entity->setTimeElapsed(dt * 1000.0f);
                                       if (cmd.type == PlayOnce
                                           && (pre_ratio > .99f
                                              || pre_ratio > cmd.entity->getTimeRatio())) {
                                           cmd.onComplete(cmd.entity.get());
                                           return true;
                                       }
                                       cmd.entity->playAllTriggers();
                                       cmd.entity->render();
                                       return false;
                                   });
            entities.erase(removed, entities.end());
        }

        SpriterEngine::EntityInstance* createEntity(const std::string &name
                                        ,CommandType type
                                        ,EntityEvent onComplete)
        {
            SpriterEngine::EntityInstance* entity = model.getNewEntityInstance(name);
            entities.emplace_back(type, entity, onComplete);
            return entity;
        }

        void deleteEntity(SpriterEngine::EntityInstance*& remove)
        {
            auto removed = std::remove_if(entities.begin(), entities.end(),
                                          [=](const EntityCommand& cmd){
                                              return cmd.entity.get() == remove;
                                          });
            entities.erase(removed, entities.end());
            remove = nullptr;
        }

		void updateFlipped(bool isFlippedX, bool isFlippedY)
		{
			for (auto it = this->entities.begin(); it != this->entities.end(); *it++)
			{
				it->entity->setScale(SpriterEngine::point(isFlippedX ? -1.0f : 1.0f, isFlippedY ? -1.0f : 1.0f));
			}
		}


    private:
		std::vector<EntityCommand> entities;
        CCFileFactory* files;
        SpriterEngine::SpriterModel model;
    };

    SpriterEngine::EntityInstance *createEntity(const std::string &name, CommandType type);


    AnimationNode::AnimationNode(const std::string& scmlFile, SpriteLoader loader)
            : self(new impl(this, loader, scmlFile)) {
		this->isFlippedX = false;
		this->isFlippedY = false;
	}

    AnimationNode::~AnimationNode() {}

    void AnimationNode::update(float dt)
    {
        self->update(dt);
    }

	void AnimationNode::setFlippedX(bool flippedX)
	{
		this->isFlippedX = flippedX;
		this->self->updateFlipped(this->isFlippedX, this->isFlippedY);
	}

	void AnimationNode::setFlippedY(bool flippedY)
	{
		this->isFlippedY = flippedY;
		this->self->updateFlipped(this->isFlippedX, this->isFlippedY);
	}

    SpriterEngine::EntityInstance* AnimationNode::playOnce(const std::string &name)
    {
		SpriterEngine::EntityInstance* instance = self->createEntity(name, PlayOnce, doNothing);

		this->self->updateFlipped(this->isFlippedX, this->isFlippedY);

		return instance;
    }

    SpriterEngine::EntityInstance* AnimationNode::playOnce(const std::string &name
                                               ,EntityEvent onComplete)
    {
		SpriterEngine::EntityInstance* instance = self->createEntity(name, PlayOnce, onComplete);

		this->self->updateFlipped(this->isFlippedX, this->isFlippedY);

		return instance;
    }

    SpriterEngine::EntityInstance *AnimationNode::play(const std::string &name) {
		SpriterEngine::EntityInstance* instance = self->createEntity(name, PlayRepeat, doNothing);

		this->self->updateFlipped(this->isFlippedX, this->isFlippedY);

		return instance;
    }

    AnimationNode* AnimationNode::create(const std::string& scmlFile, SpriteLoader loader)
    {
        AnimationNode* ret = new (std::nothrow) AnimationNode(scmlFile, loader);
        if (ret && ret->init())
        {
            ret->autorelease();
        }
        else
        {
            CC_SAFE_DELETE(ret);
        }
        return ret;
    }

    SpriteLoader AnimationNode::fileLoader()
    {
        return [](const std::string& name) { return cocos2d::Sprite::create(name);};
    }

    std::vector<std::string> split(const std::string& s, char delim)
    {
        std::stringstream ss(s);
        std::string item;
        std::vector<std::string> elems;
        while (std::getline(ss, item, delim)) {
            elems.push_back(item);
        }
        return elems;
    }

    SpriteLoader AnimationNode::cacheLoader()
    {
        return [](const std::string& name) {
            auto fullpath = split(name, '/');
            return cocos2d::Sprite::createWithSpriteFrameName(fullpath.back());
        };
    }

    void AnimationNode::onEnter()
    {
		cocos2d::Node::onEnter();
        this->scheduleUpdate();
    }

    void AnimationNode::onExit()
    {
        cocos2d::Node::onExit();
        this->unscheduleUpdate();
    }

    void AnimationNode::deleteEntity(SpriterEngine::EntityInstance*& remove)
    {
        self->deleteEntity(remove);
    }

NS_CC_END