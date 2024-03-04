#include "pch.h"
#include "AniTest.h"

AniTest::AniTest(const std::string& name)
	:SpriteGo(name)
{
}

AniTest::~AniTest()
{
}

void AniTest::Init()
{
	SpriteGo::Init();

	animator.SetTarget(&sprite);

	{
		AnimationClip clip;
		clip.id = "Idle";
		clip.fps = 10;
		clip.looptype = AnimationLoopTime::Loop;

		for (int i = 0; i < 8; ++i)
		{
			clip.frames.push_back({ "graphics/sprite_sheet.png", {i*120, 0, 120, 120} });
		}
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Run";
		clip.fps = 10;
		clip.looptype = AnimationLoopTime::Loop;

		for (int i = 0; i < 8; ++i)
		{
			clip.frames.push_back({ "graphics/sprite_sheet.png", {i * 120, 120, 120, 120} });
		}
		clip.frames.push_back({ "graphics/sprite_sheet.png", {0, 240, 120, 120} });
		animator.AddClip(clip);
	}

	{
		AnimationClip clip;
		clip.id = "Jump";
		clip.fps = 10;
		clip.looptype = AnimationLoopTime::Single;

		for (int i = 0; i < 7; ++i)
		{
			clip.frames.push_back({ "graphics/sprite_sheet.png", {i * 120, 360, 120, 120} });
		}
		animator.AddClip(clip);
	}
}

void AniTest::Reset()
{
	//SpriteGo::Reset();
	animator.Play("Idle");
		SetOrigin(Origins::BC);
}

void AniTest::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);


	//direction.x = InputMgr::GetAxis(Axis::Horizontal);
	//direction.y = InputMgr::GetAxis(Axis::Vertical);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal);       // -1 0 1

	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false;
		animator.Play("Jump");
		velocity.y = -300.f;
	}

	velocity.x = h * speed;
	velocity.y += gravity * dt;

	position += velocity * dt;

	if (position.y > 0.f)
	{
		isGrounded = true;
		position.y = 0.f;
		velocity.y = 0.f;
	}

	SetPosition(position);

	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}


	if (animator.GetCurrentCilpId() == "Idle")
	{
		if (h != 0)
		{
			animator.Play("Run");
		}
	}
	else if (animator.GetCurrentCilpId() == "Run")
	{
		if (h == 0)
		{
			animator.Play("Idle");
		}
	}
	else if (animator.GetCurrentCilpId() == "Jump" && isGrounded)
	{
		if (h == 0)
		{
			animator.Play("Idle");
		}
		else
		{
			animator.Play("Run");
		}
	}

	/*sf::Vector2f pos = position + direction * speed * dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		animator.PlayQueue("Run");
		SetFlipX(true);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		animator.PlayQueue("Run");
		SetFlipX(false);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		speed -= 10;
		animator.PlayQueue("Jump");
	}
	
	SetPosition(pos);*/

	//if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	//{
	//	animator.PlayQueue("Idle");     //모든 프레임을 소진 시 까지 재생
	//	//animator.Play("Idle");        //변경 시 바로 종료 후 변경
	//}
	//if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	//{
	//	animator.PlayQueue("Run");
	//}
	//if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	//{
	//	animator.PlayQueue("Jump");
	//}

}
