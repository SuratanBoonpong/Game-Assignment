#include "Player.h"
//for variables
void Player::initVariables()
{
	this->animState = PlAYER_ANIMATION_STATES::IDLE; //direct status

	//attacking 
	this->attackcooldownmax_top = 30.f;
	this->attackcooldown_top = this->attackcooldownmax_top;
	this->attackcooldownmax_left = 30.f;
	this->attackcooldown_left = this->attackcooldownmax_left;
	this->attackcooldownmax_down = 30.f;
	this->attackcooldown_down = this->attackcooldownmax_down;
	this->attackcooldownmax_right = 30.f;
	this->attackcooldown_right = this->attackcooldownmax_right;

	//player hp
	this->hpMax = 100;
	this->hp = this->hpMax;

	//random spawn
	this->RandomX = rand() % 1012;
	this->RandomY = rand() % 625;
}

//include picture from files
void Player::initTexture()
{
	this->playertexture.loadFromFile("Sprite/Player.png");
}

//settings sprites of player
void Player::initSprite()
{
	this->playersprite.setTexture(this->playertexture);
	this->currentFrame = sf::IntRect(0, 0, 68,95 );
	this->playersprite.setTextureRect(sf::IntRect(this->currentFrame));
	this->playersprite.setScale(1.f, 1.f);
	this->playerposition = sf::Vector2f(RandomX, RandomY);
	this->playersprite.setPosition(sf::Vector2f(this->playerposition));
}

//include spawn point pics from files
void Player::initspawntexture()
{
	this->spawnpointtexture.loadFromFile("Sprite/Summoning ring.png");
}

//settings sprites of spawnpoint 
void Player::initspawnsprite()
{
	this->spawnpointsprite.setTexture(this->spawnpointtexture);
	this->spawnpointsprite.setTextureRect(sf::IntRect(0, 0, 68, 68));
	this->spawnpointsprite.setScale(1.f, 1.f);
	this->spawnpointsprite.setPosition(sf::Vector2f(RandomX, RandomY+27));
}

//settings animation timer 
void Player::initAnimations()
{
	this->animatetimer.restart();
}

//all funtion about player
Player::Player()
{	
	//variables
	this->initVariables();
	
	//spawnpoint sprite and texture
	this->initspawntexture();
	this->initspawnsprite();

	//player sprite and texture
	this->initTexture();
	this->initSprite();

	//player animations
	this->initAnimations();
}

Player::~Player()
{
}

//get position player
const sf::Vector2f& Player::getPos() const
{
	return this->playersprite.getPosition();
}

//get colision player
const sf::FloatRect Player::getBounds() const
{
	return this->playersprite.getGlobalBounds();
}

//get HP of player
const int& Player::getHp() const
{
	return this->hp;
}

//get HPMax of player
const int& Player::getHpMax() const
{
	return this->hpMax;
}

//setting player HP
void Player::setHp(const int hp)
{
	this->hp = hp;
}

//lose Hp function
void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}

void Player::doubattack(const int check)
{
	if (check == 1) {
		this->attackcooldownmax_top = 15.f;
		this->attackcooldownmax_down = 15.f;
		this->attackcooldownmax_left = 15.f;
		this->attackcooldownmax_right = 15.f;
	}
	else {
		this->attackcooldownmax_top = 30.f;
		this->attackcooldownmax_down = 30.f;
		this->attackcooldownmax_left = 30.f;
		this->attackcooldownmax_right = 30.f;
	}
}

//Movement functions
void Player::updatemovement()
{
	this->animState = PlAYER_ANIMATION_STATES::IDLE; //not walk
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (this->playerposition.y <= 625.f) {
			this->playersprite.move(0.f, 2.f);
			this->playerposition.y += 2.f;
		}
		this->animState = PlAYER_ANIMATION_STATES::MOVING_DOWN; //go down
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (this->playerposition.x >= 0.f) {
			this->playersprite.move(-2.f, 0.f);
			this->playerposition.x -= 2.f;
		}
		this->animState = PlAYER_ANIMATION_STATES::MOVING_LEFT; //go left
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (this->playerposition.x <= 1012.f) {
			this->playersprite.move(2.f, 0.f);
			this->playerposition.x += 2.f;
		}
		this->animState = PlAYER_ANIMATION_STATES::MOVING_RIGHT; //go right
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (this->playerposition.y >= 0.f) {
			this->playersprite.move(0.f, -2.f);
			this->playerposition.y -= 2.f;
		}
		this->animState = PlAYER_ANIMATION_STATES::MOVING_TOP; //go top
	}
}

//function for play next sprite
void Player::updateAnimations()
{
	if (this->animState == PlAYER_ANIMATION_STATES::IDLE) {}
	else if (this->animState == PlAYER_ANIMATION_STATES::MOVING_DOWN) {
		if (this->animatetimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 68.f;
			if (this->currentFrame.left >= 137.f) {
				this->currentFrame.left = 0;
			}
			this->animatetimer.restart();
			this->playersprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PlAYER_ANIMATION_STATES::MOVING_LEFT) {
		if (this->animatetimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 95.f;
			this->currentFrame.left += 68.f;
			if (this->currentFrame.left >= 137.f) {
				this->currentFrame.left = 0;
			}
			this->animatetimer.restart();
			this->playersprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PlAYER_ANIMATION_STATES::MOVING_RIGHT) {
		if (this->animatetimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 190.f;
			this->currentFrame.left += 68.f;
			if (this->currentFrame.left >= 137.f) {
				this->currentFrame.left = 0;
			}
			this->animatetimer.restart();
			this->playersprite.setTextureRect(this->currentFrame);
		}
	}
	else if (this->animState == PlAYER_ANIMATION_STATES::MOVING_TOP) {
		if (this->animatetimer.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 285.f;
			this->currentFrame.left += 68.f;
			if (this->currentFrame.left >= 137.f) {
				this->currentFrame.left = 0;
			}
			this->animatetimer.restart();
			this->playersprite.setTextureRect(this->currentFrame);
		}
	}
}

//check can attack functions
const bool Player::canAttack_top()
{
	if (this->attackcooldown_top >= this->attackcooldownmax_top) {
		this->attackcooldown_top = 0.f;
		return true;
	}
	return false;
}
const bool Player::canAttack_left()
{
	if (this->attackcooldown_left >= this->attackcooldownmax_left) {
		this->attackcooldown_left = 0.f;
		return true;
	}
	return false;
}
const bool Player::canAttack_right()
{
	if (this->attackcooldown_right >= this->attackcooldownmax_right) {
		this->attackcooldown_right = 0.f;
		return true;
	}
	return false;
}
const bool Player::canAttack_down()
{
	if (this->attackcooldown_down >= this->attackcooldownmax_down) {
		this->attackcooldown_down = 0.f;
		return true;
	}
	return false;
}

//update attack functions
void Player::updateAttack()
{
	if(this->attackcooldown_top<this->attackcooldownmax_top)
		this->attackcooldown_top += 0.5f;
	if (this->attackcooldown_left < this->attackcooldownmax_left)
		this->attackcooldown_left += 0.5f;
	if (this->attackcooldown_right < this->attackcooldownmax_right)
		this->attackcooldown_right += 0.5f;
	if (this->attackcooldown_down < this->attackcooldownmax_down)
		this->attackcooldown_down += 0.5f;
}

//player update
void Player::updated()
{
	this->updatemovement();
	this->updateAnimations();
	this->updateAttack();
}

//player render
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->spawnpointsprite);
	target.draw(this->playersprite);
}
