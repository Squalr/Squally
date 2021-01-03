#include "SpriterAnimationTimeline.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventAnimation.h"
#include "Engine/Animations/Spriter/Events/SpriterAnimationTimelineEventMainline.h"
#include "Engine/Animations/Spriter/SpriterAnimationNode.h"
#include "Engine/Animations/Spriter/SpriterAnimationParser.h"
#include "Engine/GlobalDirector.h"

using namespace cocos2d;

std::map<std::string, SpriterAnimationTimeline*> SpriterAnimationTimeline::TimelineCache = std::map<std::string, SpriterAnimationTimeline*>();

SpriterAnimationTimeline* SpriterAnimationTimeline::getInstance(const std::string& animationResource)
{
	if (!SpriterAnimationTimeline::TimelineCache.contains(animationResource))
	{
		SpriterAnimationTimeline* timeline = new SpriterAnimationTimeline(animationResource);

		timeline->autorelease();

		SpriterAnimationTimeline::TimelineCache[animationResource] = timeline;
		GlobalDirector::getInstance()->registerGlobalNode(timeline);
	}

	return SpriterAnimationTimeline::TimelineCache[animationResource];
}

SpriterAnimationTimeline::SpriterAnimationTimeline(const std::string& animationResource)
{
	this->mainlineEvents = std::map<std::string, std::map<std::string, std::vector<SpriterAnimationTimelineEventMainline*>>>();
	this->animationEvents = std::map<std::string, std::map<std::string, std::vector<SpriterAnimationTimelineEventAnimation*>>>();
	this->registeredAnimationNodes = std::set<SpriterAnimationNode*>();
	this->onEnterRunOnce = false;
	
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

		if (!this->mainlineEvents.contains(entityName) || !this->mainlineEvents[entityName].contains(animationName))
		{
			continue;
		}
		
		// Advance animation time on the registered node
		animationNode->advanceTimelineTime(dt, this->mainlineEvents[entityName][animationName].back()->getEndTime());

		// Process all mainline events (heirarchy, z-sorting, global interpolation type)
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

void SpriterAnimationTimeline::buildTimelines(const SpriterData& spriterData)
{
	std::vector<SpriterAnimationTimelineEventMainline*> allMainlines = std::vector<SpriterAnimationTimelineEventMainline*>();

	for (const SpriterEntity& entity : spriterData.entities)
	{
		for (const SpriterAnimation& animation : entity.animations)
		{
			// There exists a 'key' property on bone/obj refs that maps to a timeline key at a given time.
			// Painfully, there can be extraneous info in the timeilne that we need to ignore if it references a value that does not exist in this set.
			// Joint key of key << 48 | timeline id << 32 | timeline time. We can get away with hashing 3 ints this way because key/timeline ID will always be small ints.
			std::set<uint64_t> mainlineTimelineRefKeys = std::set<uint64_t>();
			std::map<int, SpriterAnimationTimelineEventMainline*> mainlinesByTime = std::map<int, SpriterAnimationTimelineEventMainline*>();

			// Parse mainline (each key is a unique event)
			for (int index = 0; index < int(animation.mainline.keys.size()); index++)
			{
				const SpriterMainlineKey& mainlineKey = animation.mainline.keys[index];

				float endTime = index + 1 < int(animation.mainline.keys.size()) ? animation.mainline.keys[index + 1].time : animation.length;
				SpriterAnimationTimelineEventMainline* mainlineEvent = SpriterAnimationTimelineEventMainline::create(this, endTime, animation, mainlineKey);

				this->mainlineEvents[entity.name][animation.name].push_back(mainlineEvent);

				for (const auto& boneRef : mainlineKey.boneRefs)
				{
					mainlineTimelineRefKeys.insert(uint64_t(boneRef.key) << 48 | uint64_t(boneRef.timeline) << 32 | uint64_t(mainlineKey.time));
				}

				for (const auto& objectRef : mainlineKey.objectRefs)
				{
					mainlineTimelineRefKeys.insert(uint64_t(objectRef.key) << 48 | uint64_t(objectRef.timeline) << 32 | uint64_t(mainlineKey.time));
				}

				mainlinesByTime[mainlineKey.time] = mainlineEvent;
				
				allMainlines.push_back(mainlineEvent);
				this->addChild(mainlineEvent);
			}
			
			// Parse animations
			for (const auto& timeline : animation.timelines)
			{
				// Filter out extraneous timeline information that references non-existent keys.
				std::vector<SpriterTimelineKey> filteredKeys = std::vector<SpriterTimelineKey>();
				std::set<int> filteredKeyTimes = std::set<int>();

				std::copy_if(timeline.keys.begin(), timeline.keys.end(), std::back_inserter(filteredKeys), [&](const SpriterTimelineKey& key)
				{
					return mainlineTimelineRefKeys.contains(uint64_t(key.id) << 48 | uint64_t(timeline.id) << 32 | uint64_t(key.time));
				});

				// Sort by time ascending
				std::stable_sort(filteredKeys.begin(), filteredKeys.end(),  [](const SpriterTimelineKey& a, const SpriterTimelineKey& b) -> bool
				{ 
					return a.time < b.time; 
				});

				for (const SpriterTimelineKey& next : filteredKeys)
				{
					filteredKeyTimes.insert(next.time);
				}

				// Fill in missing times. Our particular implementation expects an event for each object at each frame.
				for (const auto& [time, value] : mainlinesByTime)
				{
					if (!filteredKeyTimes.contains(time))
					{
						for (int index = int(filteredKeys.size() - 1); index >= 0; index--)
						{
							if (filteredKeys[index].time < time)
							{
								filteredKeys.push_back(filteredKeys[index]);
								filteredKeys.back().time = time;
								break;
							}
						}
					}
				}

				// Resort
				std::stable_sort(filteredKeys.begin(), filteredKeys.end(),  [](const SpriterTimelineKey& a, const SpriterTimelineKey& b) -> bool
				{ 
					return a.time < b.time; 
				});

				std::vector<SpriterAnimationTimelineEventAnimation*> eventsToAdd = std::vector<SpriterAnimationTimelineEventAnimation*>(filteredKeys.size());
				
				// Parse animation keys (each key is a unique event)
				for (int index = 0; index < int(filteredKeys.size()); index++)
				{
					const SpriterTimelineKey& timelineKey = filteredKeys[index];
					float endTime = index + 1 < int(filteredKeys.size()) ? filteredKeys[index + 1].time : animation.length;
					SpriterAnimationTimelineEventAnimation* animationTimeline = SpriterAnimationTimelineEventAnimation::create(this, endTime, timeline, timelineKey);

					if (mainlinesByTime.contains(timelineKey.time))
					{
						mainlinesByTime[timelineKey.time]->registerAnimation(animationTimeline);
					}

					eventsToAdd[index] = animationTimeline;

					this->addChild(animationTimeline);
				}

				// Set up 'next' targets for added animation events
				for (int index = 0; index < int(eventsToAdd.size()); index++)
				{
					int nextIndex = index + 1 < int(eventsToAdd.size()) ? index + 1 : 0;
					eventsToAdd[index]->setNext(eventsToAdd[nextIndex]);

					this->animationEvents[entity.name][animation.name].push_back(eventsToAdd[index]);
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
