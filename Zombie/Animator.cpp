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
	//�ߺ� ��� x, Ű �˻縦 �ϰ� �ֱ�
	if (clips.find(clip.id) == clips.end())         //�ߺ� �˻� �ʼ�
	{
		//clips.insert({ clip.id, clip });          //�Ʒ��� ����
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
			queue.pop();                             //��ȯ���� ����
			Play(id, false);
			return;
		}


		switch (currentClip->looptype)
		{
		case AnimationLoopTime::Single:              //�̱��̸� ������ ������ ����
			currentFrame = totalFrame - 1;
			break;
		case AnimationLoopTime::Loop:                //�����̸� ù ��° ���������� �̵�
			currentFrame = 0;
			break;
		case AnimationLoopTime::Pingpong:
			if (addFrame > 0)
			{
				currentFrame = totalFrame - 2;       //1 �������� ��� ���� ó��
				
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

void Animator::Play(const std::string& clipId, bool clearQueue) //ù��° ������ ���·� ����, �ɹ������� ���� ����
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
	clipDuration = 1.f / currentClip->fps;               //�� �����Ӵ� �ð�
	SetFrame(currentClip->frames[currentFrame]);         //ù ��° ���������� ����
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
	//�ִϸ��̼ǿ� �� �ִ� ������ 
	target->setTexture(frame.GetTexture());
	target->setTextureRect(frame.texCoord);
}
