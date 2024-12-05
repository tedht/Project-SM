#pragma once

class Player;
class PlayerState;

/* ********************* */
/* PLAYER STATE HANDLERS */
/* ********************* */
class PlayerStateHandler
{
protected:
	Player* player;
	int frameSpeed;
	int rows;
	int cols;

	float frameWidth;
	float frameHeight;

	float frameX;
	float frameY;
	int   maxFrameX;
	int   maxFrameY;
    int   framesCounter;

	PlayerState *currentState;
public:
	PlayerStateHandler(Player *player);

	void Init();
	void HandleInput(Player* player);
	void Update();

	void setState(PlayerState& newState);
	void setFrameY(int frameY);
	void setFrameSpeed(int frameSpeed);

	PlayerState* getState();

	virtual Rectangle getSrc() = 0;
	virtual Rectangle getDest(Vector2 position) = 0;
	
	std::string getName();
	virtual ~PlayerStateHandler() = default;
};

class MovementStateHandler: public PlayerStateHandler
{
	public:
		MovementStateHandler(Player *player);

		Rectangle getSrc();
		Rectangle getDest(Vector2 position);
};

class FiringStateHandler: public PlayerStateHandler
{
	public:
		FiringStateHandler(Player *player);

		Rectangle getSrc();
		Rectangle getDest(Vector2 position);
};

/* ************* */
/* PLAYER STATES */
/* ************* */
class PlayerState
{
protected: 
	PlayerState();
public:
	virtual void enter      (PlayerStateHandler* psh, Player* player) = 0;
	virtual void exit       (PlayerStateHandler* psh, Player* player) = 0;
	virtual void HandleInput(PlayerStateHandler* psh) = 0;

	virtual std::string getName() = 0;
	virtual ~PlayerState() = default;
};

/* MOVEMENT STATES */
// Idle
class Idle : public PlayerState
{
public:
	void enter (PlayerStateHandler* psh, Player* player);
	void exit  (PlayerStateHandler* psh, Player* player);
	void HandleInput(PlayerStateHandler* psh);

	std::string getName();
	static PlayerState& getInstance();
private:
	Idle();
	Idle(const Idle& other);
};

// Focus
class Focus : public PlayerState
{
public:
	void enter (PlayerStateHandler* psh, Player* player);
	void exit  (PlayerStateHandler* psh, Player* player);
	void HandleInput(PlayerStateHandler* psh);

	std::string getName();
	static PlayerState& getInstance();

private:
	Focus();
	Focus(const Focus& other);
};

// Moving
class Moving : public PlayerState
{
public:
	void enter (PlayerStateHandler* psh, Player* player);
	void exit  (PlayerStateHandler* psh, Player* player);
	void HandleInput(PlayerStateHandler* psh);

	std::string getName();
	static PlayerState& getInstance();

private:
	Moving();
	Moving(const Moving& other);
};

/* FIRING STATES*/

// Standby
class Standby : public PlayerState
{
public:
	void enter (PlayerStateHandler* psh, Player* player);
	void exit  (PlayerStateHandler* psh, Player* player);
	void HandleInput(PlayerStateHandler* psh);

	std::string getName();
	static PlayerState& getInstance();

private:
	Standby();
	Standby(const Standby& other);
};

// Firing
class Firing : public PlayerState
{
public:
	void enter (PlayerStateHandler* psh, Player* player);
	void exit  (PlayerStateHandler* psh, Player* player);
	void HandleInput(PlayerStateHandler* psh);

	std::string getName();
	static PlayerState& getInstance();
private:
	Firing();
	Firing(const Firing& other);
};