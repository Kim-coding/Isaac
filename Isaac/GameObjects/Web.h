#pragma once
#include "SpriteGo.h"
#include "PlayerIsaac.h"

class SceneDev1;

class Web : public SpriteGo
{
protected:
	PlayerIsaac* player = nullptr;
	SceneDev1* sceneDev1 = nullptr;
	bool isAlive = true;

public:
	Web(const std::string& name);
	~Web() override;

	void Init();
	void Release();
	void Reset();
	void Update(float dt);
};
