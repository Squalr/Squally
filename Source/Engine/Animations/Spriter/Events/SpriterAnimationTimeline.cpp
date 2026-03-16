#include "SpriterAnimationTimeline.h"

#include "2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventAnimation.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventMainline.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationParser.h"
#include "Engine/GlobalDirector.h"

using namespace cocos2d;

std::map<std::string, SpriterAnimationTimeline*> SpriterAnimationTimeline::TimelineCache = std::map<std::string, SpriterAnimationTimeline*>();

SpriterAnimationTimeline* SpriterAnimationTimeline::getInstance(const std::string& animationResource)
{
	if (SpriterAnimationTimeline::TimelineCache.find(animationResource) == SpriterAnimationTimeline::TimelineCache.end())
	{
		SpriterAnimationTimeline* timeline = new SpriterAnimationTimeline(animationResource);

		timeline->autorelease();

		SpriterAnimationTimeline::TimelineCache[animationResource] = timeline;
		GlobalDirector::getInstance()->RegisterGlobalNode(timeline);
	}

	return SpriterAnimationTimeline::TimelineCache[animationResource];
}

SpriterAnimationTimeline::SpriterAnimationTimeline(const std::string& animationResource)
{
	this->buildTimelines(SpriterAnimationParser::Parse(animationResource));
}

void SpriterAnimationTimeline::onEnter()
{
	// Optimization
	if (!this->onEnterRunOnce)
	{
		super::onEnter();

		this->onEnterRunOnce = true;
	}

	this->scheduleUpdate();
}

void SpriterAnimationTimeline::update(float dt)
{
	super::update(dt);

	for (SpriterAnimationNode* animationNode : this->registeredAnimationNodes)
	{
		const std::string& entityName = animationNode->getCurrentEntityName();
		const std::string& animationName = animationNode->getCurrentAnimation();

		if (this->mainlineEvents.find(entityName) == this->mainlineEvents.end() || this->mainlineEvents[entityName].find(animationName) == this->mainlineEvents[entityName].end())
		{
			continue;
		}
		
		// Advance animation time on the registered node
		animationNode->advanceTimelineTime(dt, this->mainlineEvents[entityName][animationName].back()->getEndTime());

		// Process all mainline events (hierarchy, z-sorting, global interpolation type)
		for (SpriterAnimationTimelineEventMainline* mainlineEvent : this->mainlineEvents[entityName][animationName])
		{
			mainlineEvent->advance(animationNode);
		}

		// Process all animation events (position, scale, rotation, local interpolation type)
		for (SpriterAnimationTimelineEventAnimation* animationEvent : this->animationEvents[entityName][animationName])
		{
			if (animationEvent->canAdvance())
			{
				animationEvent->advance(animationNode);
			}
		}

		animationNode->dispatchAnimationComplete();
	}
}

void SpriterAnimationTimeline::registerAnimationNode(SpriterAnimationNode* animationNode)
{
	this->registeredAnimationNodes.insert(animationNode);
}

void SpriterAnimationTimeline::unregisterAnimationNode(SpriterAnimationNode* animationNode)
{
	this->registeredAnimationNodes.erase(animationNode);
}

void SpriterAnimationTimeline::applyCurrentAnimationState(SpriterAnimationNode* animationNode)
{
	if (animationNode == nullptr)
	{
		return;
	}

	const std::string& entityName = animationNode->getCurrentEntityName();
	const std::string& animationName = animationNode->getCurrentAnimation();

	if (this->mainlineEvents.find(entityName) == this->mainlineEvents.end() || this->mainlineEvents[entityName].find(animationName) == this->mainlineEvents[entityName].end())
	{
		return;
	}

	const float currentTime = animationNode->getTimelineTime();

	for (SpriterAnimationTimelineEventMainline* mainlineEvent : this->mainlineEvents[entityName][animationName])
	{
		if (mainlineEvent->getKeyTime() <= currentTime && currentTime < mainlineEvent->getEndTime())
		{
			mainlineEvent->fire(animationNode);
			break;
		}
	}

	for (SpriterAnimationTimelineEventAnimation* animationEvent : this->animationEvents[entityName][animationName])
	{
		if (animationEvent->getKeyTime() <= currentTime && currentTime < animationEvent->getEndTime())
		{
			animationEvent->applyCurrentState(animationNode);
		}
	}
}

void SpriterAnimationTimeline::buildTimelines(const SpriterData& spriterData)
{
	std::vector<SpriterAnimationTimelineEventMainline*> allMainlines = std::vector<SpriterAnimationTimelineEventMainline*>();

	for (const SpriterEntity& entity : spriterData.entities)
	{
		for (const SpriterAnimation& animation : entity.animations)
		{
			std::map<int, const SpriterTimeline*> timelinesById = std::map<int, const SpriterTimeline*>();
			std::map<int, std::map<int, const SpriterTimelineKey*>> timelineKeysById = std::map<int, std::map<int, const SpriterTimelineKey*>>();
			std::map<std::string, std::vector<SpriterAnimationTimelineEventAnimation*>> animationEventsByPartName = std::map<std::string, std::vector<SpriterAnimationTimelineEventAnimation*>>();

			for (const SpriterTimeline& timeline : animation.timelines)
			{
				timelinesById[timeline.id] = &timeline;

				for (const SpriterTimelineKey& timelineKey : timeline.keys)
				{
					timelineKeysById[timeline.id][timelineKey.id] = &timelineKey;
				}
			}

			// Parse mainline (each key is a unique event)
			for (int index = 0; index < int(animation.mainline.keys.size()); index++)
			{
				const SpriterMainlineKey& mainlineKey = animation.mainline.keys[index];

				float endTime = index + 1 < int(animation.mainline.keys.size()) ? animation.mainline.keys[index + 1].time : animation.length;
				SpriterAnimationTimelineEventMainline* mainlineEvent = SpriterAnimationTimelineEventMainline::create(this, endTime, animation, mainlineKey);

				this->mainlineEvents[entity.name][animation.name].push_back(mainlineEvent);
				
				allMainlines.push_back(mainlineEvent);
				this->addChild(mainlineEvent);

				auto registerSegmentAnimation = [&](int timelineId, int keyId)
				{
					const auto timelineIt = timelinesById.find(timelineId);
					const auto keyTimelineIt = timelineKeysById.find(timelineId);

					if (timelineIt == timelinesById.end() || keyTimelineIt == timelineKeysById.end())
					{
						return;
					}

					const auto keyIt = keyTimelineIt->second.find(keyId);

					if (keyIt == keyTimelineIt->second.end() || keyIt->second == nullptr)
					{
						return;
					}

					const SpriterTimeline& timeline = *timelineIt->second;
					const SpriterTimelineKey& timelineKey = *keyIt->second;
					SpriterAnimationTimelineEventAnimation* animationEvent = SpriterAnimationTimelineEventAnimation::create(this, float(mainlineKey.time), endTime, timeline, timelineKey);

					mainlineEvent->registerAnimation(animationEvent);
					animationEventsByPartName[timeline.name].push_back(animationEvent);
					this->animationEvents[entity.name][animation.name].push_back(animationEvent);
					this->addChild(animationEvent);
				};

				for (const SpriterBoneRef& boneRef : mainlineKey.boneRefs)
				{
					registerSegmentAnimation(boneRef.timeline, boneRef.key);
				}

				for (const SpriterObjectRef& objectRef : mainlineKey.objectRefs)
				{
					registerSegmentAnimation(objectRef.timeline, objectRef.key);
				}
			}

			for (auto& partEventsEntry : animationEventsByPartName)
			{
				std::vector<SpriterAnimationTimelineEventAnimation*>& partEvents = partEventsEntry.second;
				const float animationLength = animation.length / 1000.0f;

				for (int index = 0; index < int(partEvents.size()); index++)
				{
					SpriterAnimationTimelineEventAnimation* currentEvent = partEvents[index];
					SpriterAnimationTimelineEventAnimation* nextEvent = currentEvent;
					float sampleStartTime = currentEvent->getTimelineKeyTime();
					float sampleEndTime = sampleStartTime;
					bool sampleTimeWraps = false;

					if (!partEvents.empty())
					{
						for (int offset = 1; offset < int(partEvents.size()); offset++)
						{
							SpriterAnimationTimelineEventAnimation* candidateEvent = partEvents[(index + offset) % partEvents.size()];

							if (candidateEvent->getTimelineKeyId() == currentEvent->getTimelineKeyId())
							{
								continue;
							}

							nextEvent = candidateEvent;
							sampleEndTime = candidateEvent->getTimelineKeyTime();

							if (animation.isLooping && sampleEndTime <= sampleStartTime)
							{
								sampleEndTime += animationLength;
								sampleTimeWraps = true;
							}

							break;
						}

						if (nextEvent == currentEvent && animationLength > 0.0f)
						{
							sampleEndTime = animation.isLooping
								? sampleStartTime + animationLength
								: std::max(animationLength, sampleStartTime);
						}
					}

					currentEvent->setNext(nextEvent);
					currentEvent->setSamplingWindow(sampleStartTime, sampleEndTime, animationLength, sampleTimeWraps);
				}
			}
		}
	}

	for (SpriterAnimationTimelineEventMainline* next : allMainlines)
	{
		next->buildAnimationHeirarchy();
	}

	for (SpriterAnimationTimelineEventMainline* next : allMainlines)
	{
		next->buildDeltas();
	}
}

float SpriterAnimationTimeline::sampleMainlineCurve(float timeRatio)
{
	// TODO: Pick correct mainline based current elapsed time, sample that
	return timeRatio; // this->SampleCurve(timeRatio, this->mainlineData.curveType, this->mainlineData.c1, this->mainlineData.c2, this->mainlineData.c3, this->mainlineData.c4);
}

float SpriterAnimationTimeline::sampleCurve(float timeRatio, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
{
	// Polynomial math
	static const auto linear = [](float a, float b, float t) { return ((b - a) * t) + a; };
	static const auto quadratic = [](float a, float b, float c, float t) { return linear(linear(a, b, t), linear(b, c, t), t); };
	static const auto cubic = [](float a, float b, float c, float d, float t) { return linear(quadratic(a, b, c, t), quadratic(b, c, d, t), t); };
	static const auto quartic = [](float a, float b, float c, float d, float e, float t) { return linear(cubic(a, b, c, d, t), cubic(b, c, d, e, t), t); };
	static const auto quintic = [](float a, float b, float c, float d, float e, float f, float t) { return linear(quartic(a, b, c, d, e, t), quartic(b, c, d, e, f, t), t); };

	// Bezier math
	static const auto solveEpsilon = [](float duration) { return 1.0f / (200.0f * duration); };
	static const auto sampleCurve = [](float a, float b, float c, float t) { return ((a * t + b) * t + c) * t; };
	static const auto sampleCurveDerivativeX = [](float ax, float bx, float cx, float t) { return (3.0f * ax * t + 2.0f * bx) * t + cx; };
	static const auto solveCurveX = [](float ax, float bx, float cx, float x, float epsilon)
	{
		float x2;
		float t2 = x;

		// First try a few iterations of Newton's method -- normally very fast.
		for (int i = 0; i < 8; i++)
		{
			x2 = sampleCurve(ax, bx, cx, t2) - x;
			
			if (std::abs(x2) < epsilon)
			{
				return t2;
			}

			float d2 = sampleCurveDerivativeX(ax, bx, cx, t2);

			if (std::abs(d2) < 1e-6f)
			{
				break;
			}

			t2 = t2 - x2 / d2;
		}

		// Fall back to the bisection method for reliability.
		float t0 = 0.0f;
		float t1 = 1.0f;
		t2 = x;

		if (t2 < t0)
		{
			return t0;
		}

		if (t2 > t1)
		{
			return t1;
		}


		while (t0 < t1)
		{
			x2 = sampleCurve(ax, bx, cx, t2);

			if (std::abs(x2 - x) < epsilon)
			{
				return t2;
			}

			if (x > x2)
			{
				t0 = t2;
			}
			else
			{
				t1 = t2;
			}

			t2 = (t1 - t0) * 0.5f + t0;
		}

		return t2; // Failure.
	};
	static const auto solve = [](float ax, float bx, float cx, float ay, float by, float cy, float x, float epsilon) { return sampleCurve(ay, by, cy, solveCurveX(ax, bx, cx, x, epsilon)); };
	static const auto bezier = [](float t, float x1, float y1, float x2, float y2)
	{
		float cx = 3.0f * x1;
		float bx = 3.0f * (x2 - x1) - cx;
		float ax = 1.0f - cx - bx;
		float cy = 3.0f * y1;
		float by = 3.0f * (y2 - y1) - cy;
		float ay = 1.0f - cy - by;

		return solve(ax, bx, cx, ay, by, cy, t, solveEpsilon(1.0f));
	};

	switch(curveType)
	{
		case SpriterCurveType::Instant:
		{
			return timeRatio >= 1.0f ? 1.0f : 0.0f;
		}
		default:
		case SpriterCurveType::Linear:
		{
			return timeRatio;
		}
		case SpriterCurveType::Quadratic:
		{
			return quadratic(0.0f, c1, 1.0f, timeRatio);
		}
		case SpriterCurveType::Cubic:
		{
			return cubic(0.0f, c1, c2, 1.0f, timeRatio);
		}
		case SpriterCurveType::Quartic:
		{
			return quartic(0.0f, c1, c2, c3, 1.0f, timeRatio);
		}
		case SpriterCurveType::Quintic:
		{
			return quintic(0.0f, c1, c2, c3, c4, 1.0f, timeRatio);
		}
		case SpriterCurveType::Bezier:
		{
			return bezier(timeRatio, c1, c2, c3, c4);
		}
	}
}
