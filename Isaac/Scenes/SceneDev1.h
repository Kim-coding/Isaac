#pragma once

class SpriteGo;
class PlayerIsaac;
class Charger;

class SceneDev1 : public Scene
{
	std::map<int, sf::Vector2f> doorPosition;
	std::map<int, sf::Vector2f> nextDoorPosition;
	std::map<int, sf::Vector2f> Room;
protected:
	SpriteGo* spriteGoBackgroundfloor;
	SpriteGo* regularRoom;
	SpriteGo* regularRoomfloor;

	SpriteGo* door;

	SpriteGo* currentFloor;

	Charger* charger;

	std::vector<SpriteGo*> doors;
	std::vector<SpriteGo*> Rooms;
	std::list<GameObject*> monsterList;

public:
	PlayerIsaac* player;

	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	const std::list<GameObject*>& GetMonsterList() const { return monsterList; }

	bool IsInMap(const sf::Vector2f& point);
	sf::Vector2f ClampByMap(const sf::Vector2f point);

	bool crashDoor(const sf::Vector2f point);
	void nextRoom(const sf::Vector2f point);

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};

