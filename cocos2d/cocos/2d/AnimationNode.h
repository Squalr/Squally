//
// Created by jeremy on 12/12/15.
//

#ifndef SPRITER2DX_SPRITERNODE_H
#define SPRITER2DX_SPRITERNODE_H

#include <memory>

#include "SpriterPlusPlus/spriterengine/spriterengine.h"
#include "CCFileFactory.h"

#include "2d/CCNode.h"

NS_CC_BEGIN

    typedef std::function<void(SpriterEngine::EntityInstance*)> EntityEvent;

    class AnimationNode : public cocos2d::Node {
    public:
        AnimationNode(const std::string& scmlFile, SpriteLoader loader);
        ~AnimationNode ();
        void update (float dt) override;

        /**
         * Creates and schedules for maintenance a SpriterPlusPlus animation
         * entity. Once the animation completes once it will be deleted, even if it
         * is configured to loop. Use AnimationNode::play for looping animations.
         * @memberof AnimationNode
         * @param name Name of the Spriter Entity in the AnimationNode's model
         * @return a SpriterEngine::EntityInstance which can be manipulated
         * using the SpriterPlusPlus API.
         */
        SpriterEngine::EntityInstance* playOnce(const std::string &name);

        SpriterEngine::EntityInstance* playOnce(const std::string &name, EntityEvent onComplete);

        /**
         * Creates and schedules for maintenance a SpriterPlusPlus animation
         * entity. It will be maintained until deleted using AnimationNode::deleteEntity.
         * Note that the actual behavior depends on the Entity's looping configuration in Spriter;
         * if the animation loops it will play continuously. Otherwise you can use the EntityInstance
         * to resume playback when required.
         * When the animation is no longer needed, it should be cleaned up with AnimationNode::deleteEntity.
         * @memberof AnimationNode
         * @param name Name of the Spriter Entity in the AnimationNode's model
         * @return a SpriterEngine::EntityInstance which can be manipulated
         * using the SpriterPlusPlus API.
         */
        SpriterEngine::EntityInstance* play(const std::string &name);

        /**
         * Remove and destroy the EntityInstance. Takes a reference to an
         * EntityInstance* and will set it to nullptr after removing and deleting it.
         * @memberof AnimationNode
         * @param entity the EntityInstance to delete.
         */
        void deleteEntity(SpriterEngine::EntityInstance*& entity);

        static AnimationNode* create(const std::string& scmlFile, SpriteLoader loader = fileLoader());

        virtual void onEnter() override;
        virtual void onExit() override;

        static SpriteLoader fileLoader();
        static SpriteLoader cacheLoader();
    private:
        class impl;
        std::unique_ptr<impl> self;
    };
	
NS_CC_END


#endif //SPRITERNODE_H
