#pragma once

enum class AnimationLoopTime
{
	Single,        // 1 2 3 
	Loop,          // 1 2 3 1 2 3
	Pingpong       // 1 2 3 2 1
};

struct AnimationFrame
{
	std::string textureId;
	sf::IntRect texCoord;

	AnimationFrame(const std::string& id, const sf::IntRect& coord)
		: textureId(id), texCoord(coord)
	{

	}

	const sf::Texture& GetTexture() const
	{
		return RES_MGR_TEXTURE.Get(textureId);
	}
};

struct AnimationClip
{
	std::string id;
	std::vector<AnimationFrame> frames;
	AnimationLoopTime looptype = AnimationLoopTime::Single;
	int fps = 30;

	int GetTotalFrame() const
	{
		return frames.size();
	}
};

class Animator
{
protected:
	std::unordered_map<std::string, AnimationClip> clips;   //Ŭ���� ��Ƽ� ���
	float speed = 1.f;

	std::queue<std::string> queue;

	bool isPlaying = false;
	AnimationClip* currentClip = nullptr;   //���� �÷������� �ִϸ��̼�
	int totalFrame = 0;
	int currentFrame = -1;
	int addFrame = 1;
	float clipDuration = 0.f;

	float accumTime = 0.f;

	sf::Sprite* target;

public:
	Animator();
	~Animator();

	void AddClip(const AnimationClip& clip);

	bool IsPlaying() const { return isPlaying; }
	const std::string& GetCurrentCilpId()
	{
		return currentClip->id;
	}
	sf::Sprite* GetTarget() const { return target; }
	void SetTarget(sf::Sprite* t) { target = t; }

	float GetSpeed() const { return speed; }
	void SetSpeed(float s) { speed = s; }

	void Update(float dt);    //���� ����ǰ� �ִ� �ð��� �����ϸ鼭 ������ ����

	void Play(const std::string& clipId, bool clearQueue = true);
	void PlayQueue(const std::string& clipId);
	void Stop();
	void SetFrame(const AnimationFrame& frame);
};

