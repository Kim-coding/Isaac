#pragma once

class SpriteGo;
class PlayerIsaac;
class Charger;

class SceneDev1 : public Scene
{
	std::map<int, sf::Vector2f> doorPosition;
	std::map<int, sf::Vector2f> nextDoorPosition;
	std::map<int, sf::Vector2f> Room;
public:

	enum class Status
	{
		Awake,
		Game,
		NextRoom,
		Pause
	};
protected:
	Status currStatus = Status::Awake;

	SpriteGo* spriteGoBackground;
	SpriteGo* spriteGoBackgroundfloor;
	SpriteGo* regularRoom;
	SpriteGo* regularRoomfloor;

	SpriteGo* door;

	SpriteGo* currentFloor;

	PlayerIsaac* player;
	Charger* charger;

	std::vector<SpriteGo*> doors;
	std::list<GameObject*> monsterList;

public:
	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	const std::list<GameObject*>& GetMonsterList() const { return monsterList; }

	bool IsInMap(const sf::Vector2f& point);
	sf::Vector2f ClampByMap(const sf::Vector2f point);

	bool crashDoor(const sf::Vector2f point);
	//void MoveToNextRoom(size_t doorIndex);
	void nextRoom();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateNextRome(float dt);
	void UpdatePause(float dt);

	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status newStatus);
	Status GetStatus() { return currStatus; }

};

