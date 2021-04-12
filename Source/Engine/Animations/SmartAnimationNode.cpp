#include "SmartAnimationNode.h"

#include <spriter2dx/AnimationNode.h>

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"

using namespace cocos2d;
using namespace Spriter2dX;

const std::string SmartAnimationNode::DefaultAnimationEntityName = "Entity";
const std::string SmartAnimationNode::DefaultAnimationName = "Idle";

SmartAnimationNode* SmartAnimationNode::create(std::string animationResource)
{
	return SmartAnimationNode::create(animationResource, SmartAnimationNode::DefaultAnimationEntityName);
}

SmartAnimationNode* SmartAnimationNode::create(std::string animationResource, std::string entityName)
{
	SmartAnimationNode* instance = new SmartAnimationNode(animationResource, entityName);

	instance->autorelease();

	return instance;
}

SmartAnimationNode::SmartAnimationNode(std::string animationResource, std::string entityName)
{
	this->animationResource = animationResource;
	this->entityName = entityName;
	this->animationNode = AnimationNode::create(animationResource);
	this->entity = this->animationNode->play(entityName);
	this->animationParts = std::map<std::string, AnimationPart*>();
	this->initialized = false;
	this->currentAnimation = "";
	this->currentAnimationPriority = -1.0f;
	this->spriterAnimation = nullptr; // SpriterAnimationNode::create(animationResource);

	/*
	I really want the new implementation of spriter to work, because it will cut load times down by 15%, and reduce ~4-5% of update cycle time consumption.
	Also, and more importantly, I should be able to get animation blending to work if I implement spriter myself.

	Two general strategies exist:
	- Full heirarchy, where bones and sprites have a full parent stack up to the root bone.
		- Tragically, cocos2d-x does not allow for cascading scales and rotations simultaneously. This results in skewing due to their matrix math.
		- This strategy relies on global Z sorting working, which we disabled at one point. Supporting it is a huge performance hit.
			- There may be hacky fixes like bone duplication or some sort of draw redirect magic (UIBoundNodes are the closest concept I know of)
	- No heirarchy, cascading all bone positioning down to the sprites at each time frame. This runs into the problem of interrupting timeline sampling,
		as it would require a "key" at each time. If we enforce linear sampling as the only supported sampling, this is probably fine.

	Cascading has the benefit of requiring more up front computation, and less runtime strain. We can also cache these computations, meaning subsequent
	loads will be significantly faster. We would only need timeline events for sprites themselves! We could eliminate all bone timeline events.
	At least in theory.

	The correct answer is likely a mix of these, which is what my current implementation does. The current implementation builds a full heirarchy of bones,
	but does it out of the timeline objects themselves. It even positions the timelines despite the fact that they are not renderable.
	By doing this, we can query their "world position/scale/rotation/etc" -- ie their cascaded state. Then we simply apply these to the sprites at each time frame.

	Or at least that was the hope. It turns out not every sprite has a frame at the same time as the mainline event that is firing.
	Cascading logic gets fucked here

	BRAIN DUMP FOR WHEN I REVISIT IMPLEMENTING HIGHER EFFICIENCY SPRITER CODE:
	- Cascading is the source of all of my problems.
	- The existing method of cascading position and scale is broken.
	- Our mainline implementation expects corresponding animation events for it's time. But these dont exist.
	- This means bones keyed at various times eventually cascade down and then fail to apply their "danging scales" due to a missing anim key at that time.
	- If we try to duplicate keys and shove them in ex post facto, it ruins their time sampling.

	OPTION 1) Dangling cascades
	- Use a heirarchy, but cascade scales (and modified positions as a result of these scales)
	- Some of these scales will "dangle", as is our current problem.
	- Attempt to "reach up" and find these dangling scales when setting the position of a sprite.

	This might be complete garbage though, as these dangling scales may be several parents up the chain. Expensive.

	OPTION 2) COCOS FIX (Would be a heirarchy solution though)
	- Figure out how to allow rotations and scales to exist simultaneously in the heirarchy. This would mean we could avoid the cascade problem.
	    - Check if the rotation/scale bug exists in modern cocos. If it does, it's not my fault and I can ask for help fixing it.
	    - Another possibility is to apply scales based on the full rotation stack. something something cosine sine something something.
	- Less painfully but less optimally, we could redo cocos code to pass along scales differently. Some sort of child dirty recursive strategy.
	- Do not apply the scales to the matrix until we reach a sprite or other UI based node.
	- This may run into the issue of needing to then solve the Z sorting issue if we allow for bones to exist in the heirarchy with scale
	- Either way, this would solve all positioning errors. Cascading is no longer required, and those problems go away.

	Assessment: Option 2 seems best. It is the most clear path to getting this working, without rewriting much of my code.
	Will have to walk back the git history and ensure that we are reparenting sprites, and we will need to disable the cascading code.
	The problems are very clear and solveable.
	1) Solve the scale/rotation duality bug (super frustrating)
	2) Switch back to a heirarchical spriter model.
	3) Solve the Z sorting bug
	*/

	// animationNode->setPosition(Vec2(256.0f, -0.0f));

	this->addChild(this->animationNode);
	// this->addChild(this->spriterAnimation);
}

SmartAnimationNode::~SmartAnimationNode()
{
}

SmartAnimationNode* SmartAnimationNode::clone()
{
	return SmartAnimationNode::create(this->animationResource, this->entityName);
}

void SmartAnimationNode::playAnimation(AnimationPlayMode animationPlayMode, AnimParams animParams, std::function<void()> callback)
{
	this->playAnimation(SmartAnimationNode::DefaultAnimationName, animationPlayMode, animParams, callback);
}

void SmartAnimationNode::playAnimation(std::string animationName, AnimationPlayMode animationPlayMode, AnimParams animParams, std::function<void()> callback)
{
	if (animParams.priority <= this->currentAnimationPriority && !animParams.cancelAnim)
	{
		return;
	}

	this->currentAnimationPriority = animParams.priority;

	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->playAnimation(animationName);
	}

	if (this->entity == nullptr)
	{
		return;
	}
	
	if (this->entity->hasAnimation(animationName))
	{
		if (!this->initialized || animParams.cancelAnim || this->entity->currentAnimationName() != animationName)
		{
			this->initialized = true;
			this->entity->setCurrentTime(0.0f);
			this->entity->setCurrentAnimation(animationName, animParams.blendTime);
			this->currentAnimation = animationName;
		}

		switch (animationPlayMode)
		{
			case AnimationPlayMode::ReturnToIdle:
			{
				this->entity->setAnimationCompleteCallback([=]()
				{
					this->clearAnimationPriority();

					this->playAnimation(AnimationPlayMode::ReturnToIdle);
				});

				break;
			}
			case AnimationPlayMode::PauseOnAnimationComplete:
			{
				this->entity->setAnimationCompleteCallback([=]()
				{
					this->entity->pausePlayback();
				});

				break;
			}
			case AnimationPlayMode::Callback:
			{
				this->entity->setAnimationCompleteCallback([=]()
				{
					if (callback != nullptr)
					{
						callback();
					}
				});
				break;
			}
			default:
			case AnimationPlayMode::Repeat:
			{
				this->entity->setAnimationCompleteCallback([=]()
				{
					float priority = this->currentAnimationPriority;
					this->initialized = false;
					this->clearAnimationPriority();

					this->playAnimation(this->getCurrentAnimation(), AnimationPlayMode::Repeat, priority);
				});
				break;
			}
		}
	}
}

void SmartAnimationNode::clearAnimationPriority()
{
	this->currentAnimationPriority = -1.0f;
}

AnimationPart* SmartAnimationNode::getAnimationPart(std::string partName)
{
	if (this->entity == nullptr)
	{
		return nullptr;
	}

	if (this->animationParts.contains(partName))
	{
		return this->animationParts[partName];
	}

	AnimationPart* animationPart = AnimationPart::create(this->entity, partName);

	this->animationParts[partName] = animationPart;

	this->addChild(animationPart);

	return animationPart;
}

void SmartAnimationNode::restoreAnimationPart(std::string partName)
{
	if (this->entity == nullptr)
	{
		return;
	}
	
	auto animVariable = this->entity->getObjectInstance(partName);

	if (animVariable != nullptr)
	{
		animVariable->toggleTimelineCanUpdate(true);
	}
}

void SmartAnimationNode::setFlippedX(bool flippedX)
{
	if (this->spriterAnimation != nullptr)
	{
		this->spriterAnimation->setFlippedX(flippedX);
	}

	if (this->animationNode == nullptr)
	{
		return;
	}

	this->animationNode->setFlippedX(flippedX);
}

void SmartAnimationNode::setFlippedY(bool flippedY)
{
	if (this->animationNode == nullptr)
	{
		return;
	}
	
	this->animationNode->setFlippedY(flippedY);
}

bool SmartAnimationNode::getFlippedX()
{
	if (this->animationNode == nullptr)
	{
		return false;
	}
	
	return this->animationNode->getFlippedX();
}

bool SmartAnimationNode::getFlippedY()
{
	if (this->animationNode == nullptr)
	{
		return false;
	}
	
	return this->animationNode->getFlippedY();
}

std::string SmartAnimationNode::getCurrentAnimation()
{
	return this->currentAnimation;
}

std::string SmartAnimationNode::getAnimationResource()
{
	return this->animationResource;
}

void SmartAnimationNode::disableRender()
{
	if (this->animationNode == nullptr)
	{
		return;
	}

	this->animationNode->disableRender();
}

void SmartAnimationNode::enableRender()
{
	if (this->animationNode == nullptr)
	{
		return;
	}
	
	this->animationNode->enableRender();
}
