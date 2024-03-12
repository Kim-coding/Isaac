#pragma once
struct MapObjectInfo
{
	std::string objectType;
	std::string TexId;
	sf::Vector2f position;
	std::string name;
};

struct MonsterInfo
{
	std::string monsterType;
	std::string TexId;
	sf::Vector2f position;
	std::string name;
};

struct MapInfo
{
	std::string roomTexId;
	std::string roomFloorTexId;
	std::vector<MapObjectInfo> objectList;
	std::vector<MonsterInfo> monsterList;

	void LoadFromFile(std::string path);


};

