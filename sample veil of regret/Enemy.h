#pragma once
#include <utility>
#include "Player.h"

class Enemy : public Player
{
public:
	std::vector<int> deathSprites; // Death animation frames
	unsigned int deathIndex = 0;
	std::string name;
	int deathSize;
	int damageIndex = 5;
	int deathTimer = 0;
	int offsetX = 40;
	bool moveApplied = false;
	int leftX = 40;
	int rotation = 0;
	float attackCooldownTimer = 0.0f;  // Tracks the cooldown period after attack
	const float attackCooldownDuration = 2.0f;  // 2-second cooldown duration
	Player* targetPlayer = nullptr;
	Enemy(const Pos& _pos, const Dim& _dim, const int damage, float attack_cooldown, int movespeed,
		std::vector<int> walk, std::vector<int> idle, std::vector<int> attack,
		std::vector<int> death, int walkS, int idleS, int attackS,int deathS, std::string name = "")
		: Player(_pos, _dim, damage, attack_cooldown, attackS, walkS, idleS),
		deathSprites(std::move(death))
	{
		facingRight = false;
		isIdle = true;
		isMoving = false;
		this->name = name;
		walkSprites = std::move(walk);
		idleSprites = std::move(idle);
		attackSprites = std::move(attack);
		deathSize = deathS;
		this->movespeed = movespeed;
	}

	void updateAI(Player& plr)
	{
		if (isDead) return; // Stop updating if dead

		moveTowardsPlayer(plr);

		// If close enough, start attacking
		if (!isAttacking && isNearPlayer(plr))
		{
			stopMoving();
			attack(plr);
			isAttacking = true; // Ensure this flag is set to true
		}
	}
	void checkCollision(std::vector<PlayerProjectile>& projectiles)
	{
		if (isDead) return;

		for (auto& projectile : projectiles)
		{
			if (projectile.isActive &&
				pos.x < projectile.position.getX() + projectile.dimension.width &&
				pos.x + dim.width > projectile.position.getX() &&
				pos.y < projectile.position.getY() + projectile.dimension.height &&
				pos.y + dim.height > projectile.position.getY())
			{
				projectile.isActive = false;
				takeDamage(10);
			}
		}
	}
	void moveTowardsPlayer(Player& plr)
	{
		if (isDead) return; // Dead enemy should not move

		int enemyX = pos.x;   // Enemy's x position
		int playerX = plr.pos.x;  // Player's x position

		if (isNearPlayer(plr))
		{
			stopMoving();
			return;
		}

		if (enemyX < playerX) // Player is to the right
		{
			if (!facingRight) facingRight = true; // Correct facing direction
			moveRight();
		}
		else if (enemyX > playerX) // Player is to the left
		{
			if (facingRight) facingRight = false; // Correct facing direction
			moveLeft();
		}
	}


	bool isNearPlayer(Player& plr)
	{
		if (!facingRight)
			return std::abs(pos.x - plr.pos.x) <= offsetX;
		if (facingRight)
			return std::abs(pos.x - plr.pos.x) <= leftX;
	}
	void multiAttack()
	{
		if (rotation == 0 && !moveApplied)
		{
			std::vector<int> v;
			v.reserve(10);
			for (int i = 0; i < 10; i++)
			{
				std::string path = "Images/regret/Rattack" + std::to_string(i) + ".png";
				v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
			}
			attackSprites = v;
			attackSize = 10;
			moveApplied = true;
			rotation = 1;
		}
		else if (rotation == 1 && !moveApplied)
		{
			std::vector<int> v;
			v.reserve(10);
			for (int i = 0; i < 9; i++)
			{
				std::string path = "Images/regret/R2attack (" + std::to_string(i+1) + ").png";
				v.emplace_back(iLoadImage(const_cast<char*>(path.c_str())));
			}
			attackSprites = v;
			moveApplied = true;
			attackSize = 9;
			rotation = 0;
		}
	}
	void reset(const Pos& startPos, int startHP)
	{
		pos = startPos;     // Reset position
		HP = startHP;       // Reset health
		isDead = false;     // Revive enemy
		isIdle = true;
		isMoving = false;
		isAttacking = false;

		deathIndex = 0;     // Reset death animation
		attackIndex = 0;    // Reset attack animation
		walkIndex = 0;      // Reset walking animation
		deathTimer = 0;
		idleIndex = 0;      // Reset idle animation

		attackTimer = 0.0f;
		attackCooldownTimer = 0.0f;

		targetPlayer = nullptr; // Clear target

		facingRight = false; // Reset facing direction
	}
	void update(float dT,Player& player)
	{
		if (HP <= 0 && !isDead)
		{
			die();
		}

		if (isDead)
		{
			if (deathIndex < deathSprites.size() - 1)
			{
				deathIndex++;
				deathTimer += 2;
				std::cout << "Death animation frame: " << deathIndex << std::endl;
			}
			return;
		}

		// Handle attack cooldown logic
		if (attackCooldownTimer > 0.0f)
		{
			attackCooldownTimer -= dT; // Countdown the cooldown timer
			if (attackCooldownTimer <= 0.0f)
			{
				attackCooldownTimer = 0.0f; // Reset to prevent negative values
				isIdle = true;  // Set back to idle after cooldown
			}
			return; // Exit early to prevent attacking during cooldown
		}

		// Handle attack logic
		if (isAttacking)
		{
			if (attackIndex == damageIndex && isColliding(player))
			{
				std::cout << "Enemy is attacking! Aralyn HP: " << targetPlayer->HP << ", Fear HP: " << this->HP << std::endl;
				player.takeDamage(damage);
			}

			// Update attack animation
			attackIndex = (attackIndex + 1) % attackSprites.size();

			// End attack cycle and start cooldown
			attackTimer += dT;
			if (attackTimer >= attackCooldown)
			{
				isAttacking = false;
				isIdle = true;
				attackTimer = 0.0f;  // Reset attack timer
				attackCooldownTimer = attackCooldownDuration; // Start cooldown timer
			}
		}
		else
		{
			Player::update(dT); // Continue normal updates if not attacking
		}
	}

	void attack(Player& target) override
	{
		if (isDead) return;
		if (!isAttacking && attackCooldownTimer <= 0.0f)  // Only attack if cooldown is over
		{
			isAttacking = true;
			isIdle = false;
			isMoving = false;
			attackIndex = 0;
			attackTimer = 0.0f;
			targetPlayer = &target;
		}
		if (name == "regret")
		{
			moveApplied = false;
			multiAttack();
		}
	}

	void render() override
	{
		if (isDead)
		{
			iShowImage(pos.x, pos.y, dim.width, dim.height, deathSprites[deathIndex]);
			return;
		}

		// Handle attack animation
		iSetColor(255, 0, 0);
		iFilledRectangle(pos.x, pos.y + dim.height + 20, 1 * HP, 10);
		if (isAttacking)
		{
			// Check the facing direction and flip the sprite accordingly
			if (facingRight)
			{
				iShowImage(pos.x, pos.y, dim.width, dim.height, attackSprites[attackIndex]);
			}
			else
			{
				iShowImage(pos.x + dim.width, pos.y, -dim.width, dim.height, attackSprites[attackIndex]);  // Flip horizontally
			}
		}
		// Handle walking animation
		else if (isMoving)
		{
			// Check the facing direction and flip the sprite accordingly
			if (facingRight)
			{
				iShowImage(pos.x, pos.y, dim.width, dim.height, walkSprites[walkIndex]);
			}
			else
			{
				iShowImage(pos.x + dim.width, pos.y, -dim.width, dim.height, walkSprites[walkIndex]);  // Flip horizontally
			}
		}
		// Handle idle animation
		else
		{
			// Check the facing direction and flip the sprite accordingly
			if (facingRight)
			{
				iShowImage(pos.x, pos.y, dim.width, dim.height, idleSprites[idleIndex]);
			}
			else
			{
				iShowImage(pos.x + dim.width, pos.y, -dim.width, dim.height, idleSprites[idleIndex]);  // Flip horizontally
			}
		}
	}

	void die()
	{
		if (!isDead)
		{
			isDead = true;
			deathIndex = 0; // Start death animation
		}
	}

	~Enemy() override = default;
};

