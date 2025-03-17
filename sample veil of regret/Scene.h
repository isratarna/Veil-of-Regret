#pragma once
#include "Animation.h"
class Scene
{
private:
	std::vector<int> narrativeSprites;
	int continueSprite;
	bool shall_continue = false;
public:
	Scene(std::vector<int> sprites) : narrativeSprites(std::move(sprites))
	{
		continueSprite = iLoadImage("images/narrative/continue.png");
	}
	void appendNarrative(const std::string& folder)
	{
		narrativeSprites.emplace_back(iLoadImage(const_cast<char*>(folder.c_str())));
	}
	void render(int index)
	{
		iShowImage(0, 0, 800, 600, narrativeSprites[index]);
		iShowImage(400, 50, 266, 21, continueSprite);
	}
	bool getContinueStatus() const
	{
		return shall_continue;
	}
	void setContinueStatus(bool val)
	{
		this->shall_continue = val;
	}
};
