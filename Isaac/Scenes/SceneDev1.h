#pragma once
#include "MapInfo.h"

class SpriteGo;
class PlayerIsaac;
class UiHud;


class SceneDev1 : public Scene
{
	std::map<int, sf::Vector2f> doorPosition;
	std::map<int, sf::Vector2f> nextDoorPosition;
	std::map<int, sf::Vector2f> Room;
public:
	enum class Status
	{
		Game,
		GameOver,
		Pause
	};

protected:
	MapInfo mapinfo;

	Status currStatus = Status::Game;

	SpriteGo* spriteGoBackgroundfloor;
	SpriteGo* regularRoom;
	SpriteGo* regularRoomfloor;
	SpriteGo* rock;
	UiHud* uiHud = nullptr;

	SpriteGo* door;

	SpriteGo* currentFloor;

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

	UiHud* GetHud() const { return uiHud; }

	void Update(float dt) override;
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status newStatus);
	Status GetStatus() { return currStatus; }
};

