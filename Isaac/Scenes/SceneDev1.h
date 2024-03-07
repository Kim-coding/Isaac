#pragma once

class SpriteGo;

class SceneDev1 : public Scene
{
	std::map<int, sf::Vector2f> doorPosition;

protected:
	SpriteGo* spriteGoBackground;
	SpriteGo* spriteGoBackgroundfloor;
	SpriteGo* regularRoom;
	SpriteGo* regularRoomfloor;
	SpriteGo* door;


	std::vector<SpriteGo> floor;
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
};

