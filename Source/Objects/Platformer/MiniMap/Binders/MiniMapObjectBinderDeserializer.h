#pragma once

#include <functional>
#include <map>

class GameObject;
class MiniMapObjectBinder;

class MiniMapObjectBinderDeserializer
{
public:
	static MiniMapObjectBinder* Deserialize(std::string objectName);

protected:

private:
	static void InitializeBindingTable();

	static std::map<std::string, std::function<MiniMapObjectBinder*()>> BindingTable;
};
