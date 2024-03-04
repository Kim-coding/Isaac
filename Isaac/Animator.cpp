#include "pch.h"
#include "Animator.h"

Animator::Animator()
{
}

Animator::~Animator()
{
}

void Animator::AddClip(const AnimationClip& clip)
{
	//중복 허용 x, 키 검사를 하고 넣기
	if (clips.find(clip.id) == clips.end())         //중복 검사 필수
	{
		//clips.insert({ clip.id, clip });          //아래와 동일
		clips[clip.id] = clip;            
	}
}

void Animator::Update(float dt)
{
	if (!isPlaying)
		return;

	accumTime += dt * speed;
	if (accumTime < clipDuration)
		return;

	accumTime = 0.f;
	currentFrame += addFrame;

	if (currentFrame == totalFrame)
	{
		if (!queue.empty())
		{
			std::string id = queue.front();
			queue.pop();                             //반환형이 없음
			Play(id, false);
			return;
		}


		switch (currentClip->looptype)
		{
		case AnimationLoopTime::Single:              //싱글이면 마지막 프레임 유지
			currentFrame = totalFrame - 1;
			break;
		case AnimationLoopTime::Loop:                //루프이면 첫 번째 프레임으로 이동
			currentFrame = 0;
			break;
		case AnimationLoopTime::Pingpong:
			if (addFrame > 0)
			{
				currentFrame = totalFrame - 2;       //1 프레임인 경우 오류 처리
				
				addFrame = -1;
				totalFrame = -1;
			}
			else
			{
				currentFrame = 1;
				addFrame = 1;
				totalFrame = currentClip->frames.size();
			}
		}
	}

	SetFrame(currentClip->frames[currentFrame]);
}

void Animator::Play(const std::string& clipId, bool clearQueue) //첫번째 프레임 상태로 설정, 맴버변수의 값을 세팅
{
	addFrame = 1;
	if (clearQueue)
	{
		while (!queue.empty())
		{
			queue.pop();
		}
	}

	isPlaying = true;      
	accumTime = 0.f;                                 

	currentClip = &clips[clipId];
	currentFrame = 0;
	totalFrame = currentClip->GetTotalFrame();
	clipDuration = 1.f / currentClip->fps;               //한 프레임당 시간
	SetFrame(currentClip->frames[currentFrame]);         //첫 번째 프레임으로 설정
}

void Animator::PlayQueue(const std::string& clipId)
{
	queue.push(clipId);
}

void Animator::Stop()
{
	isPlaying = false;
}

void Animator::SetFrame(const AnimationFrame& frame)
{
	//애니매이션에 들어가 있는 정보를 
	target->setTexture(frame.GetTexture());
	target->setTextureRect(frame.texCoord);
}
