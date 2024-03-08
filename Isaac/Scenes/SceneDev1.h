#pragma once

class SpriteGo;
class PlayerIsaac;

class SceneDev1 : public Scene
{
	std::map<int, sf::Vector2f> doorPosition;
	std::map<int, sf::Vector2f> nextDoorPosition;
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

	std::vector<SpriteGo*> doors;
public:
	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	bool IsInMap(const sf::Vector2f& point);
	sf::Vector2f ClampByMap(const sf::Vector2f point);

	bool crashDoor(const sf::Vector2f point);
	void nextRoom();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdatePause(float dt);

	void Draw(sf::RenderWindow& window) override;

	void SetStatus(Status newStatus);
	Status GetStatus() { return currStatus; }

};

