#pragma once

#include "Engine/Components/Component.h"

class Buff;
class PlatformerEntity;

class EntityBuffBehavior : public Component
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

	void sortBuffs();
	std::vector<Buff*> getBuffs();
	void applyBuff(Buff* buff, bool checkAlive = true);
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
	typedef Component super;

	void repositionBuffIcons();

	cocos2d::Node* buffNode;
	
	PlatformerEntity* entity;

	std::vector<Buff*> buffs;
};
