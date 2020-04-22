#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Buff;
class PlatformerEntity;

class EntityBuffBehavior : public AttachedBehavior
{
public:
	static EntityBuffBehavior* create(GameObject* owner);

	template <class T>
	T* getBuff()
	{
		for (auto next : buffs)
		{
			if (dynamic_cast<T*>(next) != nullptr)
			{
				return dynamic_cast<T*>(next);
			}
		}

		return nullptr;
	}

	template <class T>
	void getBuff(std::function<void(T*)> onFound)
	{
		T* buff = this->getBuff<T>();

		if (buff != nullptr)
		{
			onFound(buff);
		}
	}

	void applyBuff(Buff* buff);
	void removeBuff(Buff* buff);
	void removeBuffsById(std::string buffId);
	void removeAllBuffs();

	static const std::string MapKey;

protected:
	EntityBuffBehavior(GameObject* owner);
	virtual ~EntityBuffBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void repositionBuffIcons();

	cocos2d::Node* buffNode;
	
	PlatformerEntity* entity;

	std::vector<Buff*> buffs;
};
