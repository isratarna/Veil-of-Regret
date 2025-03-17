#pragma once
#include "Pos.h"
#include "Dim.h"
#include "iGraphics.h"
#include <vector>
#include <string>


class PlayerProjectile {
public:
	Pos position;
	Dim dimension;
	float velocityX;
	float velocityY;
	mutable bool isActive;
	int sprite;

	PlayerProjectile(Pos pos, Dim dim, float velX, float velY)
		: position(pos), dimension(dim), velocityX(velX), velocityY(velY), isActive(true)
	{
		sprite = iLoadImage("Images/player/Attack/projectile.png");
	}

	void update(double deltaTime) {
		if (!isActive) return;

		position.setX(position.getX() + velocityX * deltaTime);
		position.setY(position.getY() + velocityY * deltaTime);

		// Deactivate the projectile if it goes off-screen
		if (position.getX() < 0 || position.getX() > 1920 || position.getY() < 0 || position.getY() > 1080) {
			isActive = false;
		}
	}

	void render() {
		if (!isActive) return;
		iShowImage(position.getX(), position.getY(), dimension.width, dimension.height, sprite);
	}
};
class Player
{
public:
	int HP = 100;
	Pos pos;
	Dim dim;
	std::vector<int> idleSprites;
	std::vector<int> walkSprites;
	std::vector<int> attackSprites;
	unsigned int walkIndex = 0;
	unsigned int idleIndex = 0;
	unsigned int attackIndex = 0;
	int attackSize;
	int walkSize;
	int idleSize;
	std::vector<PlayerProjectile> projectiles;
	const float gravity = -30.f;
	const float jumpStrength = 50.0f;
	const float jumpMoveSpeed = 25.0f;
	int movespeed = 5;
	bool isJumping = false;
	float jumpVelocity = 0.0f;
	float attackTimer = 0.0f;
	float attackCooldown;
	bool shouldHealthbarRender = true;
	bool isIdle;
	bool isDead=false;
	int groundLevel = 42 - 16;
	bool isMoving;
	bool isAttacking;
	int lostImage;
	bool facingRight = true;
	bool isRanged = false;
	int damage;
	int deathSprite;
	int lostSprite;

	Player(const Pos& pos, const Dim& dim,int damage,float attackCooldown,int attackSize ,int walkSize, int idleSize)
		: pos(pos),
		  dim(dim),
		  isIdle(true), isMoving(false), isAttacking(false), damage(damage), attackCooldown(attackCooldown), attackSize(attackSize), walkSize(walkSize), idleSize(idleSize)
	{
		std::string path;
		walkSprites.reserve(walkSize);
		for (int i = 0; i < walkSize; i++)
		{
			path = "Images/player/runright" + std::to_string(i+1) + ".png";
			walkSprites.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		idleSprites.reserve(idleSize);
		for (int i = 0; i < idleSize; i++)
		{
			path = "Images/player/Stand/idle (" + std::to_string(i + 1) + ").png";
			idleSprites.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		attackSprites.reserve(attackSize);
		for (int i = 0; i < attackSize; i++)
		{
			path = "images/player/attack/" + std::to_string(i + 1) + ".png";
			attackSprites.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		deathSprite = iLoadImage("Images/Player/death/death.png");
		lostSprite = iLoadImage("Images/player/death/lose.png");
	}
	bool isColliding(const Player& other) const
	{
		return (pos.x < other.pos.x + other.dim.width &&
			pos.x + dim.width > other.pos.x &&
			pos.y < other.pos.y + other.dim.height &&
			pos.y + dim.height > other.pos.y);
	}
	void loadNewAttackSprites()
	{
		std::string path;
		std::vector<int> vec;
		for (int i = 0; i < attackSize; i++)
		{
			path = "images/player/attack/Attack (" + std::to_string(i + 1) + ").png";
			vec.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
		}
		attackSprites = vec;
	}

	void loadGunSprites()
	{
		char c[50];
		std::vector<int> vec;
		for (int i = 0; i < 6; i++)
		{
			sprintf_s(c, sizeof(c), "images/player/attack/gun%d.png", i);
			vec.emplace_back(iLoadImage(c));
		}
		attackSprites = vec;
	}
	void loadChainsawSprites()
	{
		char c[50];
		std::vector<int> vec;
		for (int i = 0; i < 6; i++)
		{
			sprintf_s(c, sizeof(c), "images/player/attack/cAttack%d.png", i);
			vec.emplace_back(iLoadImage(c));
		}
		attackSprites = vec;
	}

	void updateProjectiles(double deltaTime)
	{
		for (auto& proj : projectiles) {
			proj.update(deltaTime);
		}
	}

	virtual void update(float dT)
	{
		if (isDead) return;

		if (isMoving)
		{
			walkIndex = (walkIndex + 1) % walkSprites.size();
		}

		if (isAttacking)
		{
			attackTimer += dT;
			if (attackTimer >= attackCooldown)
			{
				isAttacking = false;
				isIdle = true;
				attackTimer = 0.0f;
			}
			else
			{
				attackIndex = (attackIndex + 1) % attackSprites.size();
			}
		}

		if (isJumping)
		{
			pos.y += jumpVelocity;
			jumpVelocity += gravity;

			if (isMoving)
			{
				float newX = pos.x + (facingRight ? jumpMoveSpeed : -jumpMoveSpeed);
				if (newX + 50 >= 0 && newX - 50 <= 800 - dim.width)
				{
					pos.x = newX;
				}
			}

			// **Fix: Check if the player has hit the ground**
			if (pos.y <= groundLevel)
			{
				pos.y = groundLevel;
				isJumping = false;
				jumpVelocity = 0.0f;
			}
		}

		if (isIdle)
		{
			idleIndex = (idleIndex + 1) % idleSprites.size();
		}

		if (HP <= 0)
		{
			HP = 0;
			isDead = true;
		}

		updateProjectiles(dT);
	}
	void jump()
	{
		if (!isJumping)
		{
			isJumping = true;
			jumpVelocity = jumpStrength;
		}
	}

	virtual void reset() {
		this->pos = Pos(200, 42 - 16);
		this->dim = Dim(128, 128);
		this->HP = 100;
		this->isDead = false;
		this->shouldHealthbarRender = true;
		this->isIdle = true;
		this->isMoving = false;
		this->isAttacking = false;
		this->attackTimer = 0.0f;  // Reset attack cooldown
	}

	virtual void render()
	{
		if (isDead)
		{
			// Render the death sprite
			iShowImage(0, 0, 800, 600, lostSprite);
			iShowImage(pos.x, pos.y, dim.width, dim.height, deathSprite);
			return;  // Skip the rest of the rendering since the player is dead
		}
		int spriteToRender = 0;
		//healthbar
		if (shouldHealthbarRender)
		{
			iSetColor(0, 255, 0);
			iFilledRectangle(pos.x, pos.y + dim.height + 20, 1 * HP, 10);
		}
		if (isIdle)
		{
			spriteToRender = idleSprites[idleIndex];
		}
		else if (isMoving)
		{
			spriteToRender = walkSprites[walkIndex];
		}
		else if (isAttacking)
		{
			spriteToRender = attackSprites[attackIndex];
		}

		// Flip sprite if facing left
		if (facingRight)
			iShowImage(pos.x, pos.y, dim.width, dim.height, spriteToRender);
		else
			iShowImage(pos.x + dim.width, pos.y, -dim.width, dim.height, spriteToRender);
		for (auto& proj : projectiles)
			proj.render();
	}

	void takeDamage(int damageAmount)
	{
		if (!isDead)
		{
			HP -= damageAmount;
			if (HP <= 0)
			{
				HP = 0;
				isDead = true;
			}
		}
	}

	void rangedAttack()
	{
		if (isDead) return;
		if (!isAttacking)
		{
			float projVelX = facingRight ? 10.0f : -10.0f;
			isAttacking = true;
			isIdle = false;
			isMoving = false;
			attackIndex = 0;
			attackTimer = 0.0f;
			projectiles.emplace_back(Pos(pos.x + dim.width, pos.y + dim.height / 2 - 30), Dim(32, 32), projVelX, 0);
			/*
			 int projectiles[50];
			 projectiles[0] = new Projectile(
			 */
		}
	}
	
	virtual void attack(Player& target)
	{
		if (isDead) return;
		if (!isAttacking) // Attack only if not already attacking and the target is within range
		{
			isAttacking = true;
			isIdle = false;
			isMoving = false;
			attackIndex = 0;  // Reset attack animation
			attackTimer = 0.0f;  // Reset timer for cooldown

			// Deal damage to the target
			if (isColliding(target))
			{
				std::cout << "Collision detected! Applying damage." << std::endl;
				target.takeDamage(damage);
			}
		}
	}
	void moveRight()
	{
		if (isDead) return;
		if (pos.x + dim.width < 800 + 50)
		{
			pos.x += movespeed;  // Move right by 5 pixels per frame (adjust as needed)
			isMoving = true;
			isIdle = false;
			facingRight = true;
			isAttacking = false;
		}
	}
	void moveLeft()
	{
		if (isDead) return;
		if (pos.x > 0 - 50)
		{
			pos.x -= movespeed;  // Move left by 5 pixels per frame
			isMoving = true;
			isIdle = false;
			facingRight = false;
			isAttacking = false;
		}
	}
	void stopMoving()
	{
		isMoving = false;
		isIdle = true;
	}

virtual	~Player() = default;
};

