#pragma once
#include "Singleton.h"

class Scene;

enum class SceneIds
{
<<<<<<< HEAD
	None = -1, SceneDev1, SceneDev2, Count,
=======
	None = -1, SceneTitle, SceneIntro, SceneMapTool, SceneDev1, SceneDev2, Count,
>>>>>>> Develop
};

class SceneMgr : public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>;

protected:
	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::SceneTitle;
	SceneIds currentScene = startScene;
	SceneIds nextScene = SceneIds::None;
	bool isDeveloperMode = false;

	SceneMgr() = default;
	virtual ~SceneMgr();

public:
	void Init();
	void Release();

	void ChangeScene(SceneIds id);

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	bool GetDeveloperMode() { return isDeveloperMode; }

	bool Update(float dt);
	void LateUpdate(float dt);
	void FixedUpdate(float dt);
	void Draw(sf::RenderWindow& window);

	SceneMgr(const SceneMgr&) = delete;
	SceneMgr(SceneMgr&&) = delete;
	SceneMgr& operator=(const SceneMgr&) = delete;
	SceneMgr& operator=(SceneMgr&&) = delete;
};

#define SCENE_MGR (SceneMgr::Instance())