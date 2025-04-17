#pragma once
class Player;
class PlayerController {
private:
	PlayerController() = default;
    float player_speed = 0.3;
	static PlayerController* controller;
public:
    PlayerController(PlayerController const&) = delete;
    void operator=(PlayerController const&) = delete;
    ~PlayerController();

    static PlayerController* getPlayerController();

    void controllPlayer(Player* player, float time);

};