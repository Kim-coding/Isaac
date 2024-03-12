#include "pch.h"
#include "SceneTest.h"
#include "SceneMapTool.h"

SceneTest::SceneTest(SceneIds id)
	:Scene(id)
{
}

SceneTest::~SceneTest()
{
}

void SceneTest::Init()
{
}

void SceneTest::Release()
{
	Scene::Release();
}

void SceneTest::Enter()
{
	Scene::Enter();
}

void SceneTest::Exit()
{
	Scene::Exit();
}

void SceneTest::Update(float dt)
{
	Scene::Update(dt);

}

void SceneTest::LateUpdate(float dt)
{
	Scene::LateUpdate(dt);
}

void SceneTest::FixedUpdate(float dt)
{
	Scene::FixedUpdate(dt);
}

void SceneTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
