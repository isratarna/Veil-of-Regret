#include "Animation.h"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Enemy.h"
#include "Menu.h"
#include "Scene.h"
#include "level1.h"
#include "Player.h"
bool guiltSpawned;
int frame = 0;
bool onFirstWinLastFrame = false;
bool guiltContinue = false;
bool continueToMenu = false;
bool lv1Active = false;
bool paranoiaKilled;
bool regretSpawned = false;
bool regretKilled = false;
bool lvl2Active = false;
bool lvl3Active = false;
bool lvl2AnimActive = false;
bool lvl2CatSegment = false;
bool menuMusicPlaying = false;
int narrativeIndex = 0;
std::vector<std::unique_ptr<Animation>> animations;  // Animation vector
std::unique_ptr<Menu> menu;
std::vector<int> levelImages;
std::vector<int> level1EndImages;
std::shared_ptr<Level2End> lvl2Won;
std::shared_ptr<Level3> lvl3;
Animation* victoryLvl1;
size_t currentAnimationIndex = 0;  // Track the current animation index
int animationTimerID = -1;  // Global variable to store timer ID
Scene* scene1; // stating level 1
Level1* level1;
Level1End* level1End;
bool paranoiaSpawned;
std::unique_ptr<Level2> lvl2;
std::unique_ptr<Player> player;
bool lvl3AnimActive = false;
std::shared_ptr<Enemy> guilt;
std::shared_ptr<Enemy> guilt2;
std::shared_ptr<Enemy> guilt3;
std::shared_ptr<Enemy> paranoia;
std::shared_ptr<Enemy> paranoia2;
std::shared_ptr<Enemy> paranoia3;
std::shared_ptr<Enemy> paranoia4;
std::shared_ptr<Enemy> paranoia5;
std::shared_ptr<Enemy> paranoia6;
std::shared_ptr<Enemy> fireworm;
std::shared_ptr<Enemy> fireworm2;
std::shared_ptr<Enemy> fireworm3;
std::shared_ptr<Enemy> regret;
void startAnimationTimer();
std::shared_ptr<Enemy> fear;
std::shared_ptr<Enemy> reaper;
std::shared_ptr<Enemy> reaper2;
std::vector<std::shared_ptr<Enemy>> lvl3Enemies;
bool lvl1End = false;
bool lvl2End = false;
bool lvl2Victory = false;
bool fearKilled = false;
bool guiltKilled = false;
bool anim1placed = false;
bool lvl1Won;
bool lvl2AnimComplete = false;
bool playedVictory = false;
bool resetVicAnim = false;
bool playLevel1EndAnimation = false;
bool lvl3AnimComplete = false;
bool gameEnd = false;
bool level2AnimationFinished = false;
bool showLastNarrativeLvl2 = false;
int lastImage;
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::Idraw Here::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::://
void returnToChapterSelect() {
	// Reset variables to their initial states
	lv1Active = false;
	lvl1End = false;
	lvl1Won = false;
	fearKilled = false;
	gameEnd = false;
	lvl3AnimActive = false;
	lvl3AnimComplete = false;
	guiltKilled = false;
	lvl1Won = false;
	playLevel1EndAnimation = false;
	level2AnimationFinished = false;
	lvl2AnimComplete = false;
	lvl2AnimActive = false;
	lvl2CatSegment = false;
	player->isRanged = false;
	lvl3Active = false;
	lvl2Active = false;
	lvl2Victory = false;
	guiltSpawned = false;
	paranoiaSpawned = false;
	paranoiaKilled = false;
	playedVictory = false;
	resetVicAnim = false;
	showLastNarrativeLvl2 = false;
	regretSpawned = false;
	// Reset menu state
	menu->play_clicked = true;
	menu->chapterChoice = 0;
	menu->choice = 0;

	// Reset level states
	scene1->setContinueStatus(false);
	if (level1)
		level1->resetLevel();
	if (lvl2)
		lvl2->resetLevel();
	if (lvl3)
		lvl3->reset();
	// Reset player and enemy
	player->reset();  // Add reset function to Player class
	if (fear){
		fear->reset(Pos(600, 1), 100);
	}
	if (guilt) {
		guilt->reset(Pos(600, 26), 150);
	}
	if (guilt2) {
		guilt2->reset(Pos(600, 26), 150);
	}
	if (guilt3) {
		guilt3->reset(Pos(600, 26), 150);
	}
	if (lvl2Won)
		lvl2Won->resetLevel();
	if (level1End) level1End->resetLevel();
	guiltContinue = false;
}


void iDraw()
{
	iClear();

	if (!animations.empty()) {
		animations[currentAnimationIndex]->start();
		animations[currentAnimationIndex]->render(0, 0, 800, 600);

		if (animations[currentAnimationIndex]->hasFinished()) {
			if (!animations[currentAnimationIndex]->isLastFrameRendered()) {
				return;  // Don't advance yet
			}
			if (currentAnimationIndex + 1 < animations.size()) {
				currentAnimationIndex++;
				animations[currentAnimationIndex]->reset();
				startAnimationTimer();
			}
			else {
				onFirstWinLastFrame = true;
			}
		}
	}

	if (onFirstWinLastFrame && continueToMenu) {
		if (!menuMusicPlaying) {  // Play only if not already playing
			PlaySound(NULL, NULL, 0);  // Stop previous music
			PlaySound("Audio/menuMusic.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
			menuMusicPlaying = true;
		}
		menu->render();
	}
	if (lv1Active && !scene1->getContinueStatus()) {
		scene1->render(narrativeIndex);
	}
	else if (lv1Active && scene1->getContinueStatus()) {
		if (!lvl1Won)
		{
			level1->render();
			if (level1->hasPassed && level1->initLevel)
			{
				if (!lvl1End)
				{
					player->render();
					fear->render();
					reaper->render();
					reaper2->render();
				}
				else if (lvl1End)
				{
					iShowImage(0, 0, 800, 600, level1->wonLevel);
				}
			}
		}
		if (lvl1Won)
		{
			if (!anim1placed)
			{
				animations.emplace_back(std::make_unique<Animation>(
					"Images/lvl2", "memory", 80, false, 70, "Audio/firstWindowMusic.wav", false));
				anim1placed = true;
			}
			if (!playLevel1EndAnimation)
			{
				level1End->render();  // Normal level 1End rendering
			}

			if (!animations.empty() && playLevel1EndAnimation)
			{
				animations[currentAnimationIndex]->render(0, 0, 800, 600);

				if (animations[currentAnimationIndex]->hasFinished())
				{
					if (!animations[currentAnimationIndex]->isLastFrameRendered())
						return;  // Wait for the final frame

					if (currentAnimationIndex + 1 < animations.size())
					{
						currentAnimationIndex++;
						animations[currentAnimationIndex]->reset();
						startAnimationTimer();
					}
					else
					{
						playLevel1EndAnimation = false; // Stop after animation finishes
					}
				}
			}
		}
	}
	if (lvl2Active)
	{
		lvl2->render();
		if (lvl2->initLevel)
		{
			player->render();
			if (guilt && guiltSpawned)
			{
				guilt->render();
			}
			if (guilt2 && guiltSpawned)
			{
				guilt2->render();
			}
			if (guilt3 && guiltSpawned)
			{
				guilt3->render();
			}
			if (guiltKilled && guilt->deathIndex == guilt->deathSize - 1 && lvl2Won && guiltContinue)
			{
				lvl2Won->render();
				lvl2Won->cat->render();
				if (player->shouldHealthbarRender) player->shouldHealthbarRender = false;
				player->render();
			}
			if (lvl2AnimActive)
			{
				animations[currentAnimationIndex]->render(0, 0, 800, 600);
				if (animations[currentAnimationIndex]->hasFinished())
				{
					if (!animations[currentAnimationIndex]->isLastFrameRendered())
						return;  // Wait for the final frame

					if (currentAnimationIndex + 1 < animations.size())
					{
						currentAnimationIndex++;
						animations[currentAnimationIndex]->reset();
						startAnimationTimer();
					}
					else
					{
						lvl2AnimActive = false; // Stop after animation finishes
						lvl2AnimComplete = true;
					}

				}
			}
			if (lvl2AnimComplete && !lvl2AnimActive)
			{
				lvl2Victory = true;
				iShowImage(0, 0, 800, 600, lvl2Won->victoryImg);
			}
			if (lvl2Victory && showLastNarrativeLvl2)
			{
				iShowImage(0, 0, 800, 600, lvl2Won->lvl2LastNarrative);
			}
		}
	}
	if (lvl3Active)
	{
		lvl3->render();
		std::cout << "Anim : " << lvl3AnimActive << " & gameEnd : " << gameEnd << "& complete : " << lvl3AnimComplete << "\n";
		if (lvl3->puzzleCompleted && lvl3->initLevel && !lvl3AnimComplete)
		{
			if (paranoia) paranoia->render();
			if (paranoia2) paranoia2->render();
			if (paranoia3) paranoia3->render();
			if (paranoia4) paranoia4->render();
			if (paranoia5) paranoia5->render();
			if (paranoia6) paranoia6->render();
			if (fireworm) fireworm->render();
			if (fireworm2) fireworm2->render();
			if (fireworm3) fireworm3->render();
			player->render();
		}
		if (regretSpawned)
		{
			if (lvl3->regretTimer <= 20.f)
			{
				lvl3->regretTimer += 1.f;
				iSetColor(255, 0, 0);
				iText(400, 300, "Regret sets in...", GLUT_BITMAP_HELVETICA_18);
			}
			if (regret && !lvl3AnimComplete)
				regret->render();
		}
		if (regret && regret->isDead && lvl3AnimActive)
		{
			animations[currentAnimationIndex]->render(0, 0, 800, 600);
			if (animations[currentAnimationIndex]->hasFinished())
			{
				if (!animations[currentAnimationIndex]->isLastFrameRendered())
					return;  // Wait for the final frame

				if (currentAnimationIndex + 1 < animations.size())
				{
					currentAnimationIndex++;
					animations[currentAnimationIndex]->reset();
					startAnimationTimer();
				}
				else
				{
					lvl3AnimActive = false; // Stop after animation finishes
					lvl3AnimComplete = true;
					gameEnd = true;
					std::cout << "Anim completed\n";
				}

			}
		}
		if (!lvl3AnimActive && lvl3AnimComplete)
		{
			iShowImage(0, 0, 800, 600, lastImage);
			std::cout << "Rendering last image\n";
		}
	}
}
void updateFrame() {
	if (!animations.empty()) {
		animations[currentAnimationIndex]->updateFrame();
	}
}


/*function iMouseMove() is called when the user presses and drags the mouse.
(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	std::cout << mx << ", " << my << std::endl;
}

//*******************************************************************ipassiveMouse***********************************************************************//
void iPassiveMouseMove(int mx, int my)
{
	menu->update(mx, my);
}

void iMouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if (menu->getChoice() == 1)
		{
			menu->play_clicked = true;
			std::cout << "Play click status : " << menu->play_clicked << "\n";
		}
		if (menu->getChoice() == 2)
		{
			menu->inst_clicked = true;
		}
		else if (menu->getChoice() == 3)
		{
			menu->credits_clicked = true;
		}
		else if (menu->getChoice() == 4) exit(0);
		else if (menu->play_clicked)
		{
			if (menu->getLevelChoice() == 1 && !lvl2Active)
			{
				lv1Active = true;
				player->lostSprite = iLoadImage("Images/player/death/lose.png");
			}
			else if (menu->getLevelChoice() == 2 && !lv1Active)
			{
				lvl2Active = true;
				player->loadNewAttackSprites();
				player->lostSprite = iLoadImage("Images/lvl2/gameOver.png");
			}
			else if (menu->getLevelChoice() == 3 && !lvl2Active && !lv1Active)
			{
				lvl3Active = true;
				player->lostSprite = iLoadImage("Images/level3/gameOver.png");
			}
			else if (menu->getLevelChoice() == 4)
			{
				menu->play_clicked = false;
				menu->credits_clicked = false;
			}
		}
		if (lvl2 && lvl2->levelImageIndex == 1)
		{
			lvl2->puzzleLogic(mx, my);
		}
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {}
}
/*
function iKeyboard() is called whenever the user hits a key in keyboard.
key- holds the ASCII value of the key pressed.
*/
bool enterPressed = false;
bool attackPressed = false;

void iKeyboard(unsigned char key)
{
	if (lv1Active && scene1->getContinueStatus())
	{
		if (key >= '0' && key <= '9')  // Only accept numeric keys
		{
			level1->takeKeyInput(key);
		}

		else if (key == 8)
		{
			if (!level1->ans.empty())
				level1->ans.pop_back();
		}
	}
	if (!enterPressed)
	{
		if (key == '\r')
		{
			if (lv1Active && !scene1->getContinueStatus())
			{
				scene1->setContinueStatus(true);
			}
			if (level1->hasPassed && !level1->initLevel)
			{
				PlaySound(NULL, NULL, 0);
				level1->initLevel = true;
			}
			if (fear->isDead && reaper->isDead && reaper2->isDead && lvl1End && !lvl1Won)
			{
				lvl1Won = true;
			}
			if (lvl1Won && !playLevel1EndAnimation && animations.size() < 3) // Prevent duplicates
			{
				playLevel1EndAnimation = true;
				startAnimationTimer();
			}
			if (guilt && guilt->isDead && guilt2->isDead && guilt3->isDead && guilt->deathIndex == guilt->deathSize - 1 && !guiltContinue)
			{
				player->pos.x = 200;
				guiltContinue = true;
			}
			enterPressed = true;
			if (lvl2Active)
			{
				lvl2->advanceImage();
				if (lvl2->puzzleCompleted && !lvl2->initLevel)
				{
					lvl2->initLevel = true;
				}
				if (guiltContinue && lvl2Won->cat->accepted && lvl2Won->cat->reachedPlayer && !lvl2AnimActive)
				{
					lvl2AnimActive = true;
					animations.emplace_back(std::make_unique<Animation>("Images/lvl2/anim", "memory", 104,
						false, 100, "Audio/firstWindowMusic.wav", false));
					startAnimationTimer();
				}
				else if (guiltContinue && lvl2Won->cat->rejected && lvl2Won->cat->outOfScreen() && !lvl2AnimActive)
				{
					lvl2AnimActive = true;
					animations.emplace_back(std::make_unique<Animation>("Images/lvl2/anim", "memory", 104,
						false, 100, "Audio/firstWindowMusic.wav", false));
					startAnimationTimer();
				}
			}
			if (lvl3Active)
			{
				if (lvl3->initPuzzle == false) lvl3->initPuzzle = true;
				if (lvl3->puzzleCompleted) lvl3->initLevel = true;
				if (regret && regret->isDead && !lvl3AnimActive)
				{
					lvl3AnimActive = true;
					animations.emplace_back(std::make_unique<Animation>("Images/level3/anim", "memoriezzz", 95, false,
						100, "Audio/firstWindowMusic.wav", false));
					startAnimationTimer();
				}
			}
			if (gameEnd)
			{
				returnToChapterSelect();
			}
		}
	}
	if (key >= '1' && key <= '3')
	{
		if (lvl3->initPuzzle)
		{
			lvl3->updateChoice(key);
		}
	}
	if (key == ' ')
	{
		level1End->advanceImage();
		if (guiltKilled && guilt->deathIndex == guilt->deathSize - 1 && !lvl2End)
		{
			lvl2End = true;
		}
		if (lvl2Victory)
		{
			showLastNarrativeLvl2 = true;
		}
	}
	if (key == 27)
	{
		if (level1End->levelImageIndex >= level1End->levelImages.size() - 1)
		{
			returnToChapterSelect();
		}
		if (showLastNarrativeLvl2)
		{
			returnToChapterSelect();
		}
		if (player->isDead)
		{
			returnToChapterSelect();
		}
	}
	if (lvl3Active)
	{
		if (key == '1')
		{
			player->loadChainsawSprites();
			player->damage = 13;
			player->isRanged = false;
		}
		if (key == '2')
		{
			player->loadGunSprites();
			player->isRanged = true;
		}
	}
}
std::vector<std::shared_ptr<Enemy>> fears;
std::vector<std::shared_ptr<Enemy>> guilts;
std::vector<std::shared_ptr<Enemy>> paranoias;
/*
function iSpecialKeyboard() is called whenver user hits special keys like-
function keys, home, end, pg up, pg down, arraows etc.
*/
void iSpecialKeyboard(unsigned char key)
{
	if (key)
	{
		if (fear->isDead &&  reaper->isDead && reaper2->isDead && !lvl1End)
		{
			lvl1End = true;
		}
	}
	if (key == GLUT_KEY_UP)
	{
		player->jump();
	}
	if (key == GLUT_KEY_HOME)
	{
		if (onFirstWinLastFrame && !continueToMenu)
		{
			continueToMenu = true;
		}
	}
	if (level1->hasPassed && level1->initLevel)
	{
		if (key == GLUT_KEY_RIGHT)  player->moveRight();
		if (key == GLUT_KEY_LEFT)  player->moveLeft();
		if (key == GLUT_KEY_END)
		{
			for (auto& f : fears)
			{
				player->attack(*f);
				if (player->isColliding(*f) && player->attackIndex == 3)
				{
					f->takeDamage(player->damage);
				}
			}
		}
	}

	if (lvl2->initLevel && lvl2->puzzleCompleted)
	{
		if (key == GLUT_KEY_RIGHT) if (!lvl2CatSegment)player->moveRight();
		if (key == GLUT_KEY_LEFT)if (!lvl2CatSegment) player->moveLeft();
		if (key == GLUT_KEY_END)
		{
			for (auto& f : guilts)
			{
				player->attack(*f);
				if (player->isColliding(*f) && player->attackIndex == 3)
				{
					f->takeDamage(player->damage);
				}
			}
		}
		if (lvl2CatSegment)
		{
			if (key == GLUT_KEY_PAGE_DOWN && (!lvl2Won->cat->accepted && !lvl2Won->cat->rejected)) lvl2Won->cat->accepted = true;
			if (key == GLUT_KEY_PAGE_UP && (!lvl2Won->cat->accepted && !lvl2Won->cat->rejected)) lvl2Won->cat->rejected = true;
		}
	}
	if (lvl3->initLevel)
	{
		if (key == GLUT_KEY_RIGHT) player->moveRight();
		if (key == GLUT_KEY_LEFT) player->moveLeft();
		if (key == GLUT_KEY_END && !player->isRanged)
		{
			for (auto& f : paranoias)
			{
				player->attack(*f);
				if (player->isColliding(*f) && player->attackIndex == 3)
				{
					f->takeDamage(player->damage);
				}
			}
			if (regretSpawned)
			{
				player->attack(*regret);
				if (player->isColliding(*regret) && player->attackIndex == 3)
				{
					regret->takeDamage(player->damage);
				}
			}
		}
		else if (key == GLUT_KEY_END && player->isRanged)
		{
			player->rangedAttack();
		}
	}
}
void keyUp(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT || key == GLUT_KEY_LEFT)
	{
		player->stopMoving();
	}
	if (key == GLUT_KEY_END)
	{
	}
}

void nkeyUp(unsigned char key, int x, int y)
{
	if (key == '\r')
	{
		enterPressed = false;
	}
}

std::vector<int> loadLevel1Narrative()
{
	std::vector<int> sprites;
	sprites.emplace_back(iLoadImage("Images/narrative/narrative1.png"));
	return sprites;
}
void startAnimationTimer() {
	if (animationTimerID != -1) {
		iPauseTimer(animationTimerID);  // Stop the previous timer
	}
	animationTimerID = iSetTimer(animations[currentAnimationIndex]->getInterval(), updateFrame);
}
bool axeDamageSet = false;

std::vector<int> loadGuiltWalkSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/guilt/walk/walk (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuiltIdleSprites(int idleSize)
{
	std::vector<int> v;
	v.reserve(idleSize);
	for (int i = 0; i < idleSize; i++)
	{
		std::string path = "Images/guilt/idle/idle (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuiltAttackSprites(int attackSize)
{
	std::vector<int> v;
	v.reserve(attackSize);
	for (int i = 0; i < attackSize; i++)
	{
		std::string path = "Images/guilt/attack/attack (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuiltDeathSprites(int deathSize)
{
	std::vector<int> v;
	v.reserve(deathSize);
	for (int i = 0; i < deathSize; i++)
	{
		std::string path = "Images/guilt/death/death (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt2WalkSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/guilt2/walk/walk (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt2IdleSprites(int idleSize)
{
	std::vector<int> v;
	v.reserve(idleSize);
	for (int i = 0; i < idleSize; i++)
	{
		std::string path = "Images/guilt2/idle/idle (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt2AttackSprites(int attackSize)
{
	std::vector<int> v;
	v.reserve(attackSize);
	for (int i = 0; i < attackSize; i++)
	{
		std::string path = "Images/guilt2/attack/attack (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt2DeathSprites(int deathSize)
{
	std::vector<int> v;
	v.reserve(deathSize);
	for (int i = 0; i < deathSize; i++)
	{
		std::string path = "Images/guilt2/death/death (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt3WalkSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/guilt3/walk/walk (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt3IdleSprites(int idleSize)
{
	std::vector<int> v;
	v.reserve(idleSize);
	for (int i = 0; i < idleSize; i++)
	{
		std::string path = "Images/guilt3/idle/idle (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt3AttackSprites(int attackSize)
{
	std::vector<int> v;
	v.reserve(attackSize);
	for (int i = 0; i < attackSize; i++)
	{
		std::string path = "Images/guilt3/attack/attack (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadGuilt3DeathSprites(int deathSize)
{
	std::vector<int> v;
	v.reserve(deathSize);
	for (int i = 0; i < deathSize; i++)
	{
		std::string path = "Images/guilt3/death/death (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadFirewormDeathSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/fireworm/death" + std::to_string(i) + ".png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadFirewormAttackSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/fireworm/attack" + std::to_string(i) + ".png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadFirewormIdleSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/fireworm/Idle (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadFirewormWalkSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/fireworm/walk" + std::to_string(i) + ".png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadParanoiaWalkSprites(int walkS)
{
	std::vector<int> v;
	v.reserve(walkS);
	for (int i = 0; i < walkS; i++)
	{
		std::string path = "Images/paranoia/walk (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadParanoiaDeathSprites(int walkS)
{
	std::vector<int> v;
	v.reserve(walkS);
	for (int i = 0; i < walkS; i++)
	{
		std::string path = "Images/paranoia/death (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}

std::vector<int> loadParanoiaAttackSprites(int walkS)
{
	std::vector<int> v;
	v.reserve(walkS);
	for (int i = 0; i < walkS; i++)
	{
		std::string path = "Images/paranoia/attack (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadParanoiaIdleSprites(int walkS)
{
	std::vector<int> v;
	v.reserve(walkS);
	for (int i = 0; i < walkS; i++)
	{
		std::string path = "Images/paranoia/idle (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadRegretIdleSprites(int S)
{
	std::vector<int> v;
	v.reserve(S);
	for (int i = 0; i < S; i++)
	{
		std::string path = "Images/regret/idle.png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadRegretAttackSprites(int S)
{
	std::vector<int> v;
	v.reserve(S);
	for (int i = 0; i < S; i++)
	{
		std::string path = "Images/regret/Rattack" + std::to_string(i) + ".png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadRegretWalkSprites(int S)
{
	std::vector<int> v;
	v.reserve(S);
	for (int i = 0; i < S; i++)
	{
		std::string path = "Images/regret/Rmove" + std::to_string(i) + ".png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadRegretDeathSprites(int S)
{
	std::vector<int> v;
	v.reserve(S);
	for (int i = 0; i < S; i++)
	{
		std::string path = "Images/regret/death (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
void update()
{
	level1->update(*player);
	if (level1->initLevel && !lvl2Active)
	{
		player->update(10);
	}
	if (lvl1Won)
	{
		level1End->update(*player);
	}
	if (lvl2Active)
	{
		lvl2->update(*player);
		if (lvl2->initLevel)
		{
			player->update(10);
			if (!axeDamageSet) {
				player->damage = 9;
				axeDamageSet = true;
			}
			if (!guiltSpawned)
			{
				guilt = std::make_shared<Enemy>(Pos(600, 26), Dim(128, 128), 15, 150, 8, loadGuiltWalkSprites(7),
					loadGuiltIdleSprites(7), loadGuiltAttackSprites(7), loadGuiltDeathSprites(3), 7, 7, 7, 3);
				guilt2 = std::make_shared<Enemy>(Pos(200, 26), Dim(128, 128), 15, 150, 7, loadGuilt2WalkSprites(13),
					loadGuilt2IdleSprites(7), loadGuilt2AttackSprites(16), loadGuilt2DeathSprites(3), 13, 7, 16, 3);
				guilt3 = std::make_shared<Enemy>(Pos(400, 26), Dim(128, 128), 15, 150, 11, loadGuilt3WalkSprites(13),
					loadGuilt3IdleSprites(5), loadGuilt3AttackSprites(10), loadGuilt3DeathSprites(3), 13, 5, 10, 3);
				guilts.emplace_back(guilt);
				guilts.emplace_back(guilt2);
				guilts.emplace_back(guilt3);
				guiltSpawned = true;
			}
			if (guilt->HP <= 0 && guilt2->HP <= 0 && guilt3->HP <= 0 && !guiltKilled)
			{
				guiltKilled = true;
				lvl2Won = std::make_shared<Level2End>();
				lvl2Won->catSpawned = true;
				lvl2CatSegment = true;
			}
		}
	}
	if (lvl3Active)
	{
		if (lvl3->puzzleCompleted && lvl3->initLevel)
		{
			player->update(15);
			if (!paranoiaSpawned)
			{
				paranoiaSpawned = true;
				player->pos.y = 50;
				player->groundLevel = 50;
				paranoia = std::make_shared<Enemy>(Pos(600, 120), Dim(32, 32), 3, 150, 9, loadParanoiaWalkSprites(4),
					loadParanoiaIdleSprites(4), loadParanoiaAttackSprites(4), loadParanoiaDeathSprites(4), 4, 4, 4, 4);
				paranoia2 = std::make_shared<Enemy>(Pos(100, 90), Dim(32, 32), 3, 150, 11, loadParanoiaWalkSprites(4),
					loadParanoiaIdleSprites(4), loadParanoiaAttackSprites(4), loadParanoiaDeathSprites(4), 4, 4, 4, 4);
				paranoia->damageIndex = 2;
				paranoia2->damageIndex = 2;
				paranoia3 = std::make_shared<Enemy>(Pos(500, 140), Dim(32, 32), 3, 150, 5, loadParanoiaWalkSprites(4),
					loadParanoiaIdleSprites(4), loadParanoiaAttackSprites(4), loadParanoiaDeathSprites(4), 4, 4, 4, 4);
				paranoia4 = std::make_shared<Enemy>(Pos(200, 100), Dim(32, 32), 3, 150, 4, loadParanoiaWalkSprites(4),
					loadParanoiaIdleSprites(4), loadParanoiaAttackSprites(4), loadParanoiaDeathSprites(4), 4, 4, 4, 4);
				paranoia3->damageIndex = 2;
				paranoia4->damageIndex = 2;
				paranoia5 = std::make_shared<Enemy>(Pos(50, 80), Dim(32, 32), 3, 150, 7, loadParanoiaWalkSprites(4),
					loadParanoiaIdleSprites(4), loadParanoiaAttackSprites(4), loadParanoiaDeathSprites(4), 4, 4, 4, 4);
				paranoia6 = std::make_shared<Enemy>(Pos(700, 110), Dim(32, 32), 3, 150, 6, loadParanoiaWalkSprites(4),
					loadParanoiaIdleSprites(4), loadParanoiaAttackSprites(4), loadParanoiaDeathSprites(4), 4, 4, 4, 4);
				fireworm = std::make_shared<Enemy>(Pos(230, 40), Dim(64, 64), 7, 150, 5, loadFirewormWalkSprites(9), loadFirewormIdleSprites(9),
					loadFirewormAttackSprites(16), loadFirewormDeathSprites(8), 9, 9, 16, 8);
				fireworm2 = std::make_shared<Enemy>(Pos(290, 40), Dim(64, 64), 7, 150, 7, loadFirewormWalkSprites(9), loadFirewormIdleSprites(9),
					loadFirewormAttackSprites(16), loadFirewormDeathSprites(8), 9, 9, 16, 8);
				fireworm3 = std::make_shared<Enemy>(Pos(330, 40), Dim(64, 64), 7, 150, 10, loadFirewormWalkSprites(9), loadFirewormIdleSprites(9),
					loadFirewormAttackSprites(16), loadFirewormDeathSprites(8), 9, 9, 16, 8);
				paranoia5->damageIndex = 2;
				paranoia6->damageIndex = 2;
				paranoia->leftX = 1;
				paranoia2->leftX = 1;
				paranoia3->leftX = 1;
				paranoia4->leftX = 1;
				paranoia5->leftX = 1;
				paranoia6->leftX = 1;
				paranoias.emplace_back(paranoia);
				paranoias.emplace_back(paranoia2);
				paranoias.emplace_back(paranoia3);
				paranoias.emplace_back(paranoia4);
				paranoias.emplace_back(paranoia5);
				paranoias.emplace_back(paranoia6);
				paranoias.emplace_back(fireworm);
				paranoias.emplace_back(fireworm2);
				paranoias.emplace_back(fireworm3);
				if (paranoia->isDead && paranoia2->isDead && paranoia3->isDead && paranoia4->isDead && paranoia5->isDead &&
					paranoia6->isDead && fireworm->isDead && fireworm2->isDead && fireworm3->isDead && !paranoiaKilled)
				{
					paranoiaKilled = true;
				}
			}
			if (paranoia->isDead && paranoia2->isDead && paranoia3->isDead && paranoia4->isDead && paranoia5->isDead &&
				paranoia6->isDead && fireworm->isDead && fireworm2->isDead && fireworm3->isDead && !regretSpawned)
			{
				std::cout << "All enemies killed. Spawning Regret." << std::endl;
				regretSpawned = true;
				lvl3->mapSprite = iLoadImage("Images/level3/map2.png");
				regret = std::make_shared<Enemy>(Pos(950, 60), Dim(128, 128), 15, 150, 15, loadRegretWalkSprites(8), loadRegretIdleSprites(1), loadRegretAttackSprites(10), loadRegretDeathSprites(10),
					8, 1, 10, 10, "regret");
			}
			if (!paranoiaKilled)
			{
				for (auto& p : paranoias)
				{
					p->checkCollision(player->projectiles);
				}
			}

			if (regretSpawned && !regret->isDead)
			{
				regret->checkCollision(player->projectiles);
			}
		}
	}
}
void updateEnemy()
{
	if (level1->initLevel)
	{
		if (!lvl1End){
			fear->update(5.f, *player);
			fear->updateAI(*player);
			reaper->update(5.f, *player);
			reaper->updateAI(*player);
			reaper2->update(5.f, *player);
			reaper2->updateAI(*player);
		}
	}
	if (lvl2->initLevel)
	{
		if (guiltSpawned)
		{
			guilt->update(5.f, *player);
			guilt->updateAI(*player);
			guilt2->update(5.f, *player);
			guilt2->updateAI(*player);
			guilt3->update(5.f, *player);
			guilt3->updateAI(*player);
		}
		if (guiltKilled)
		{
			if (lvl2Won && guiltContinue)
				lvl2Won->cat->moveLogic(*player);
			if (guiltContinue)
				lvl2Won->update();
		}
	}
	if (lvl3->initLevel)
	{
		if (paranoiaSpawned)
		{
			paranoia->update(5.f, *player);
			paranoia->updateAI(*player);
			paranoia2->update(5.f, *player);
			paranoia2->updateAI(*player);
			paranoia3->update(5.f, *player);
			paranoia3->updateAI(*player);
			paranoia4->update(5.f, *player);
			paranoia4->updateAI(*player);
			paranoia5->update(5.f, *player);
			paranoia5->updateAI(*player);
			paranoia6->update(5.f, *player);
			paranoia6->updateAI(*player);
			fireworm->update(5.f, *player);
			fireworm->updateAI(*player);
			fireworm2->update(5.f, *player);
			fireworm2->updateAI(*player);
			fireworm3->update(5.f, *player);
			fireworm3->updateAI(*player);
		}
		if (regretSpawned)
		{
			regret->update(5.f, *player);
			regret->updateAI(*player);
		}
	}
}

std::vector<int> loadFearWalkSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/fear/walk/walk (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadFearIdleSprites(int idleSize)
{
	std::vector<int> v;
	v.reserve(idleSize);
	for (int i = 0; i < idleSize; i++)
	{
		std::string path = "Images/fear/idle/idle (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadFearAttackSprites(int attackSize)
{
	std::vector<int> v;
	v.reserve(attackSize);
	for (int i = 0; i < attackSize; i++)
	{
		std::string path = "Images/fear/attack/attack (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadFearDeathSprites(int deathSize)
{
	std::vector<int> v;
	v.reserve(deathSize);
	for (int i = 0; i < deathSize; i++)
	{
		std::string path = "Images/fear/death/death (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadReaperWalkSprites(int walkSize)
{
	std::vector<int> v;
	v.reserve(walkSize);
	for (int i = 0; i < walkSize; i++)
	{
		std::string path = "Images/reaper/walk/walk (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadReaperIdleSprites(int idleSize)
{
	std::vector<int> v;
	v.reserve(idleSize);
	for (int i = 0; i < idleSize; i++)
	{
		std::string path = "Images/reaper/idle/idle.png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadReaperAttackSprites(int attackSize)
{
	std::vector<int> v;
	v.reserve(attackSize);
	for (int i = 0; i < attackSize; i++)
	{
		std::string path = "Images/reaper/attack/attack (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
std::vector<int> loadReaperDeathSprites(int deathSize)
{
	std::vector<int> v;
	v.reserve(deathSize);
	for (int i = 0; i < deathSize; i++)
	{
		std::string path = "Images/reaper/death/death (" + std::to_string(i + 1) + ").png";
		v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
	}
	return v;
}
int main() {
	iInitialize(800, 600, "Veil of Regret");  // Initialize first!
	player = std::make_unique<Player>(Pos(200, 42 - 16), Dim(128, 128), 5, 120, 6, 12, 7);
	fear = std::make_shared<Enemy>(Pos(600, 1), Dim(128, 128), 10, 150, 5, loadFearWalkSprites(16),
		loadFearIdleSprites(16), loadFearAttackSprites(16), loadFearDeathSprites(8),
		16, 16, 16, 8);
	reaper = std::make_shared<Enemy>(Pos(100, 1), Dim(128, 128), 10, 150, 8, loadReaperWalkSprites(4),
		loadReaperIdleSprites(1), loadReaperAttackSprites(6), loadReaperDeathSprites(10),
		4, 1, 6, 10);
	reaper2 = std::make_shared<Enemy>(Pos(700, 1), Dim(128, 128), 10, 150, 6, loadReaperWalkSprites(4),
		loadReaperIdleSprites(1), loadReaperAttackSprites(6), loadReaperDeathSprites(10),
		4, 1, 6, 10);
	fears.emplace_back(fear);
	fears.emplace_back(reaper);
	fears.emplace_back(reaper2);
	animations.emplace_back(std::make_unique<Animation>("Images/clockTicking", "clock", 165, false, 44,
		"Audio/introSound.wav"));
	animations.emplace_back(std::make_unique<Animation>("Images/firstWindow", "window", 25, false, 260,
		"Audio/firstWindowMusic.wav", true));
	scene1 = new Scene(loadLevel1Narrative());
	levelImages.emplace_back(iLoadImage("images/level1/puzzle.png"));
	levelImages.emplace_back(iLoadImage("images/level1/success.png"));
	level1 = new Level1(levelImages);
	level1EndImages.emplace_back(iLoadImage("images/lvl2/begin0.png"));
	level1EndImages.emplace_back(iLoadImage("images/lvl2/begin.png"));
	level1End = new Level1End(level1EndImages);
	std::vector<int> level2Images;
	level2Images.emplace_back(iLoadImage("Images/lvl2/narrative1.png"));
	level2Images.emplace_back(iLoadImage("Images/lvl2/puzzle.png"));
	lastImage = iLoadImage("Images/level3/anim/last.png");
	lvl2 = std::make_unique<Level2>(level2Images);
	lvl3 = std::make_shared<Level3>();
	if (animations.empty()) {
		std::cerr << "Error: Failed to initialize animations" << std::endl;
		return -1;
	}
	glutKeyboardUpFunc(nkeyUp);
	glutSpecialUpFunc(keyUp);
	startAnimationTimer();
	iSetTimer(60, update);
	iSetTimer(100, updateEnemy);
	menu = std::make_unique<Menu>();
	iStart();
	delete scene1;
	delete level1;
	delete level1End;
	delete victoryLvl1;
	return 0;
}
