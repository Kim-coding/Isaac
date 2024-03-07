#pragma once

class SpriteGo;
class PlayerIsaac;

class SceneDev1 : public Scene
{
	std::map<int, sf::Vector2f> doorPosition;

public:
	enum class MapObject
	{
		empty,
		wall,
	};
protected:
	SpriteGo* spriteGoBackground;
	SpriteGo* spriteGoBackgroundfloor;
	SpriteGo* regularRoom;
	SpriteGo* regularRoomfloor;
	SpriteGo* door;

	SpriteGo* currentFloor;

	PlayerIsaac* player;

	std::vector<SpriteGo> floor;
	std::vector<SpriteGo*> doors;



	int col = 13;
	int row = 9;
	float size = 72.f;

	float offsetX = 30.f;
	float offsetY = 40.f;
	sf::VertexArray grid;
	std::vector<MapObject> mapObj;
	std::vector<std::string> mapLayout =
	{
		"WWWWWEEWWWWW",
		"WWWWWEEWWWWW",
		"WWEEEEEEEEWW",
		"WWEEEEEEEEWW",
		"EEEEEEEEEEEE",
		"WWEEEEEEEEWW",
		"WWEEEEEEEEWW",
		"WWWWWEEWWWWW",
		"WWWWWEEWWWWW",
	};
public:
	SceneDev1(SceneIds id);
	virtual ~SceneDev1();

	void SetGrid();

	bool IsInMap(const sf::Vector2f& point);
	sf::Vector2f ClampByMap(const sf::Vector2f point);

	bool crashDoor(const sf::Vector2f point);
	void nextRoom();

	void Init() override;
	void Release() override;

	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void SetMap();

	void Draw(sf::RenderWindow& window) override;
	bool CheckInteraction(int index, sf::Keyboard::Key key); //인덱스 번호를 받아서 오브젝트 상호작용 작동

};

