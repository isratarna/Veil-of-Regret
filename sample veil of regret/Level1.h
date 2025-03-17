#pragma once
#include <utility>
#include <vector>

#include "Animation.h"
#include "Player.h"

class Level1
{
public:
	virtual ~Level1() = default;
	std::vector<int> levelImages;
	int levelImageIndex = 0;
	std::string ans;
	bool  hasPassed = false;
	int mapSprite;
	int backgroundX = 0;
	const int speed = 10;
	int noOfTries = 0;
	bool gameOverMusicPlaying = false;
	bool gameOver = false;
	bool initLevel = false;
	int gameOverSprite;
	int wonLevel;
	bool lvl2Active = false;

	Level1(std::vector<int> levelImages) : levelImages(std::move(levelImages))
	{
		gameOverSprite = iLoadImage("Images/gameOver.png");
		mapSprite = iLoadImage("Images/level1/gameplay.jpg");
		wonLevel = iLoadImage("Images/level1/win.png");
	}
	void takeKeyInput(unsigned char key)
	{
		if (!gameOver && !hasPassed && ans.size() < 6)  // Prevent input if already passed or game over
		{
			ans += key;
			std::cout << "Key Pressed: " << key << ", Current Answer: " << ans << std::endl;
		}
	}
	void resetLevel()
	{
		levelImageIndex = 0;
		ans.clear();
		hasPassed = false;
		backgroundX = 0;
		noOfTries = 0;
		gameOverMusicPlaying = false;
		gameOver = false;
		initLevel = false;
	}

	virtual void update(Player& player)
	{
		if (initLevel)
		{
			if (player.isMoving && player.facingRight)
			{
				backgroundX -= speed;
				if (backgroundX <= -800) backgroundX = 0;
			}
		}
		if (!gameOver && !hasPassed)  // Only process if game is not over and the answer is not correct
		{
			if (ans == "140903")  // Correct answer given
			{
				hasPassed = true;
				if (levelImages.size() > 1)
				{
					levelImageIndex++;
				}
			}
			else if (ans.size() > 5)  // Incorrect input after 6 characters
			{
				ans = "";   // Reset the answer
				noOfTries++;

				if (noOfTries > 2)  // Check if max attempts exceeded
				{
					gameOver = true;
				}
			}
		}
	}
	void render()
	{
		if (!gameOver && !initLevel)
		{
			iShowImage(0, 0, 800, 600, levelImages[levelImageIndex]);
			iSetColor(200, 154, 109);
			if (!hasPassed)
				iText(356, 293, const_cast<char*>(ans.c_str()), GLUT_BITMAP_HELVETICA_18);
		}
		if (!gameOver && initLevel)
		{
			iShowImage(backgroundX, 0, 800, 600, mapSprite);
			iShowImage(backgroundX + 800, 0, 800, 600, mapSprite);
			//player enemy render logic
		}
		else if (gameOver)
		{
			iShowImage(0, 0, 800, 600, gameOverSprite);
			if (!gameOverMusicPlaying)
			{
				PlaySound(NULL, NULL, 0);
				PlaySound("Audio/gameOverMusic", NULL, SND_FILENAME | SND_ASYNC);
				gameOverMusicPlaying = true;
			}
		}
	}
};

class Level1End
{
public:
	std::vector<int> levelImages;
	int levelImageIndex = 0;
	int mapSprite;
	int backgroundX = 0;
	const int speed = 10;
	bool initLevel = false;

	Level1End(std::vector<int> images) : levelImages(std::move(images))
	{
		mapSprite = iLoadImage("Images/level2/gameplay.jpg");
	}

	void update(Player& player)
	{
		if (initLevel && player.isMoving && player.facingRight)
		{
			backgroundX -= speed;
			if (backgroundX <= -800) backgroundX = 0;
		}
	}

	void render()
	{
		if (!initLevel)
		{
			iShowImage(0, 0, 800, 600, levelImages[levelImageIndex]);
		}
		else
		{
			iShowImage(backgroundX, 0, 800, 600, mapSprite);
			iShowImage(backgroundX + 800, 0, 800, 600, mapSprite);
		}
	}
	void resetLevel() {
		levelImageIndex = 0;
		backgroundX = 0;
		initLevel = false;
	}
	void advanceImage()
	{
		if (levelImageIndex + 1 < levelImages.size())
		{
			levelImageIndex++;
		}
	}
};
class Level2
{
public:
	std::vector<int> levelImages;
	int levelImageIndex = 0;
	int mapSprite;
	int backgroundX = 0;
	int puzzleImage;
	int wonSprite;
	bool guiltShame = false;
	bool forgiveEscape = false;
	bool memoryTruth = false;
	bool puzzleCompleted = false;
	const int speed = 10;
	std::string choice1;
	std::string choice2;
	bool initLevel = false;

	Level2(std::vector<int> images) : levelImages(std::move(images))
	{
		mapSprite = iLoadImage("Images/lvl2/gameplay.jpg");
		puzzleImage = iLoadImage("Images/lvl2/puzzle.png");
		wonSprite = iLoadImage("Images/lvl2/wonSprite.png");
	}
	void puzzleLogic(int mx, int my)
	{
		if (levelImageIndex == 1)
		{
			// Select for guilt & shame (if not solved)
			if (!guiltShame)
			{
				if (mx > 140 && my > 368 && mx < 359 && my < 443 && choice1.empty()) choice1 = "guilt";
				else if (mx > 491 && my > 246 && mx < 708 && my < 316 && choice2.empty()) choice2 = "shame";
			}

			// Select for forgive & escape (if not solved)
			if (!forgiveEscape)
			{
				if (mx > 134 && my > 245 && mx < 357 && my < 317 && choice1.empty()) choice1 = "forgive";
				else if (mx > 489 && my > 117 && mx < 693 && my < 190 && choice2.empty()) choice2 = "escape";
			}

			// Select for truth & memory (if not solved)
			if (!memoryTruth)
			{
				if (mx > 146 && my > 117 && mx < 361 && my < 190 && choice1.empty()) choice1 = "truth";
				else if (mx > 492 && my > 373 && mx < 709 && my < 443 && choice2.empty()) choice2 = "memory";
			}
		}
	}
	void resetLevel()
	{
		levelImageIndex = 0;
		backgroundX = 0;
		guiltShame = false;
		forgiveEscape = false;
		memoryTruth = false;
		puzzleCompleted = false;
		choice1.clear();
		choice2.clear();
		initLevel = false;
	}
	void update(Player& player)
	{
		if (initLevel && player.isMoving && player.facingRight)
		{
			backgroundX -= speed;
			if (backgroundX <= -800) backgroundX = 0;
		}

		// Only check if both choices are filled
		if (!puzzleCompleted)
		{
			if (!choice1.empty() && !choice2.empty())
			{
				// Check for Guilt & Shame
				if (!guiltShame &&
					((choice1 == "guilt" && choice2 == "shame") || (choice1 == "shame" && choice2 == "guilt")))
				{
					guiltShame = true;
					std::cout << "Guilt & Shame solved!\n";
				}

				// Check for Forgive & Escape
				else if (!forgiveEscape &&
					((choice1 == "forgive" && choice2 == "escape") || (choice1 == "escape" && choice2 == "forgive")))
				{
					forgiveEscape = true;
					std::cout << "Forgive & Escape solved!\n";
				}

				// Check for Truth & Memory
				else if (!memoryTruth &&
					((choice1 == "truth" && choice2 == "memory") || (choice1 == "memory" && choice2 == "truth")))
				{
					memoryTruth = true;
					std::cout << "Memory & Truth solved!\n";
				}

				// Clear choices only after checking
				choice1.clear();
				choice2.clear();
			}
		}

		// Final puzzle check
		if (guiltShame && forgiveEscape && memoryTruth)
		{
			puzzleCompleted = true;
		}
	}

	void render()
	{
		if (!initLevel)
		{
			iShowImage(0, 0, 800, 600, levelImages[levelImageIndex]);
		}
		else if (initLevel)
		{
			iShowImage(backgroundX, 0, 800, 600, mapSprite);
			iShowImage(backgroundX + 800, 0, 800, 600, mapSprite);
		}
		if (levelImageIndex == 1 && !initLevel)
		{
			if (!puzzleCompleted)
			{
				if (guiltShame)
				{
					iSetColor(0, 0, 0);
					iFilledRectangle(140, 368, 220, 73);
					iFilledRectangle(492, 245, 220, 73);
				}
				if (forgiveEscape)
				{
					iSetColor(0, 0, 0);
					iFilledRectangle(140, 245, 220, 73);
					iFilledRectangle(489, 117, 220, 73);
				}
				if (memoryTruth)
				{
					iSetColor(0, 0, 0);
					iFilledRectangle(491, 368, 220, 73);
					iFilledRectangle(146, 117, 220, 73);
				}
				iSetColor(255, 255, 255);
				iText(172, 50, const_cast<char*>(choice1.c_str()), GLUT_BITMAP_HELVETICA_18);
				iText(490, 50, const_cast<char*>(choice2.c_str()), GLUT_BITMAP_HELVETICA_18);
			}
			else if (puzzleCompleted)
			{
				iShowImage(0, 0, 800, 600, wonSprite);
			}
		}
	}

	void advanceImage()
	{
		if (levelImageIndex + 1 < levelImages.size())
		{
			levelImageIndex++;
		}
	}
};
class Cat
{
public:
	Pos pos{ 900, 26 };
	Dim dim{ 64, 64 };
	std::vector<int> idleSprites;
	std::vector<int> moveSprites;
	int idleSize = 6;
	int moveIndex = 0;
	int idleIndex = 0;
	int moveSize = 6;
	int segment1Text;
	int segment2Text;
	int acceptImage;
	int rejectImage;
	bool isNearPlayer = false;
	bool facingRight = false;
	bool moving = false;
	bool idle = true;
	bool hasMovedOut = false;
	bool middleOfTheScreen = false;
	bool accepted = false;
	bool rejected = false;
	bool reachedPlayer = false;
	Cat()
	{
		std::string str;
		for (int i = 0; i < moveSize; i++)
		{
			str = "Images/cat/Idle" + std::to_string(i) + ".png";
			idleSprites.emplace_back(iLoadImage(const_cast<char*>(str.c_str())));
		}
		for (int i = 0; i < moveSize; i++)
		{
			str = "Images/cat/Move" + std::to_string(i) + ".png";
			moveSprites.emplace_back(iLoadImage(const_cast<char*>(str.c_str())));
		}
		segment1Text = iLoadImage("Images/cat/catSegment1.png");
		segment2Text = iLoadImage("Images/cat/catSegment2.png");
		acceptImage = iLoadImage("Images/cat/acceptImage.png");
		rejectImage = iLoadImage("Images/cat/rejectImage.png");
	}
	void Cat::reset() {
		pos = { 900, 26 };
		isNearPlayer = false;
		facingRight = false;
		moving = false;
		idle = true;
		hasMovedOut = false;
		middleOfTheScreen = false;
		accepted = false;
		rejected = false;
		reachedPlayer = false;
		idleIndex = 0;
		moveIndex = 0;
	}

	void moveLeft()
	{
		pos.x -= 10;
		facingRight = false;
		moving = true;
		idle = false;
	}
	void moveRight()
	{
		pos.x += 10;
		moving = true;
		facingRight = true;
		idle = false;
	}
	void moveLogic(Player player)
	{
		if (pos.x > 800 / 2 && !middleOfTheScreen)
		{
			moveLeft();
		}
		else if (pos.x == 800 / 2)
		{
			idle = true;
			moving = false;
			middleOfTheScreen = true;
		}

		if (middleOfTheScreen)
		{
			if (accepted)
			{
				if (std::abs(player.pos.x - pos.x) > 60) moveLeft();
				else {
					reachedPlayer = true;
					idle = true;
					moving = false;
				}
			}
			else if (rejected)
			{
				if (pos.x < 850) moveRight();
				else
				{
					hasMovedOut = true;
				}
			}
		}
	}
	bool Cat::outOfScreen()
	{
		return pos.x > 800;
	}
	
	void update()
	{
		if (moving)
		{
			moveIndex = (moveIndex + 1) % moveSize;
			std::cout << "Move Index: " << moveIndex << std::endl;
		}
		if (idle)
		{
			idleIndex = (idleIndex + 1) % idleSize;
			std::cout << "Idle Index: " << idleIndex << std::endl;
		}
	}

	void render()
	{
		if (!middleOfTheScreen) iShowImage(0, 0, 800, 600, segment1Text);
		else if (middleOfTheScreen && !accepted && !rejected)
		{
			iShowImage(0, 0, 800, 600, segment2Text);
			iSetColor(255, 255, 255);
			iText(200, 100, "Press PageDown to accept, PageUp to reject.", GLUT_BITMAP_HELVETICA_18);
		}
		else if (middleOfTheScreen && accepted && reachedPlayer)
		{
			iShowImage(0, 0, 800, 600, acceptImage);
		}
		else if (middleOfTheScreen && rejected && pos.x > 800)
		{
			iShowImage(0, 0, 800, 600, rejectImage);
		}

		int currentSprite;
		if (moving)
		{
			currentSprite = moveSprites[moveIndex];
		}
		else if (idle)
		{
			currentSprite = idleSprites[idleIndex];
		}
		if (facingRight)
		{
			iShowImage(pos.x, pos.y, dim.width, dim.height, currentSprite);
		}
		else
		{
			iShowImage(pos.x + dim.width, pos.y, -dim.width, dim.height, currentSprite);
		}
	}
	
};
class Level2End
{
public:
	int mapSprite;
	std::shared_ptr<Cat> cat;
	bool catSpawned = false;
	int backgroundX = 0;
	const int speed = 10;
	bool initLevel = false;
	int victoryImg;
	int lvl2LastNarrative;

	Level2End()
	{
		cat = std::make_shared<Cat>();
		mapSprite = iLoadImage("Images/lvl2/gameplay.jpg");
		victoryImg = iLoadImage("Images/lvl2/anim/last.png");
		lvl2LastNarrative = iLoadImage("Images/lvl2/narrative2.png");
	}

	void update()
	{
		if (catSpawned) {
			cat->update();
		}
	}

	void render()
	{

		iShowImage(backgroundX, 0, 800, 600, mapSprite);
		iShowImage(backgroundX + 800, 0, 800, 600, mapSprite);
		if (catSpawned)
			cat->render();
	}
	void Level2End::resetLevel() {
		backgroundX = 0;
		catSpawned = false;
		initLevel = false;
		if (cat) {
			cat->reset();
		}
	}
};
class Level3
{
public:
	std::vector<int> levelImages;
	int levelImageIndex = 0;
	bool hasPassed = false;
	int mapSprite;
	int backgroundX = 0;
	const int speed = 10;
	bool failed = false;
	bool gameOver = false;
	bool initLevel = false;
	bool initPuzzle = false;
	int puzzleWon;
	int gameOverSprite;
	float regretTimer=0.0;
	int choice;
	int wonLevel;
	std::vector<int> puzzleImages;
	int lastImage;
	int introImage;
	bool lvl3Active = false;
	int puzzleIndex = 0;
	bool puzzleCompleted = false;

	Level3()
	{
		introImage = iLoadImage("Images/level3/narrative1.png");
		puzzleImages.emplace_back(iLoadImage("Images/level3/puzzle1.png"));
		puzzleImages.emplace_back(iLoadImage("Images/level3/puzzle2.png"));
		puzzleImages.emplace_back(iLoadImage("Images/level3/puzzle3.png"));
		mapSprite = iLoadImage("Images/level3/map.png");
		lastImage = iLoadImage("Images/level3/anim/last.png");
		puzzleWon = iLoadImage("Images/level3/puzzle_win.png");
	}
	void updateChoice(unsigned char key)
	{
		choice = key;
		if (initPuzzle && !initLevel)
		{
			if (puzzleIndex == 0 && choice == '2')
			{
				puzzleIndex++;
			}
			else if (puzzleIndex == 1 && choice == '1')
			{
				puzzleIndex++;
			}
			else if (puzzleIndex == 2 && choice == '3')
			{
				puzzleCompleted = true;
			}
			else failed = true;
		}
	}
	void reset()
	{
		levelImageIndex = 0;
		hasPassed = false;
		backgroundX = 0;
		failed = false;
		gameOver = false;
		initLevel = false;
		initPuzzle = false;
		lvl3Active = false;
		puzzleIndex = 0;
		puzzleCompleted = false;
	}
	void render()
	{
		if (failed)
		{

			return;
		}
		if (!initPuzzle && !puzzleCompleted)
		iShowImage(0, 0, 800, 600, introImage);
		else if (initPuzzle && !puzzleCompleted)
		{
			if (puzzleIndex < puzzleImages.size())
			iShowImage(0, 0, 800, 600, puzzleImages[puzzleIndex]);
		}
		if (puzzleCompleted && !initLevel)
		{
			iShowImage(0, 0, 800, 600, puzzleWon);
		}
		if (puzzleCompleted && initLevel)
		{
			iShowImage(0, 0, 800, 600, mapSprite);
		}
	}
};