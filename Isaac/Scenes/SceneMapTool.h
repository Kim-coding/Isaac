#pragma once
#include "Scene.h"
#include "TextGo.h"
#include "MapInfo.h"

class SpriteGo;

class SceneMapTool : public Scene
{
protected:
	SpriteGo* backGround;
	SpriteGo* buttonFloor;
	SpriteGo* buttonRoom;
	SpriteGo* buttonSave;
	SpriteGo* buttonObj;
	TextGo FloorButtonText;
	TextGo RoomButtonText;
	TextGo SaveButtonText;
	TextGo ObjButtonText;

	SpriteGo* rock;
	MapInfo mapInfo;

	sf::Texture imageTexture;
	sf::Texture imageRoom;
	sf::Sprite spriteFloor;
	sf::Sprite spriteRoom;


	bool isDragging = false;
public:
	SceneMapTool(SceneIds id);
	~SceneMapTool() override;

	void Init();
	void Release();

	std::wstring SelectFloor();
	std::wstring SelectRoom();

	void Enter();
	void Exit();

	void Update(float dt);

	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	void SaveMapCSV();
	std::string ToRelativePath(const std::string& originalPath, const std::string& basePath);

};

