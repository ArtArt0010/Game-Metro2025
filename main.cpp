#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include"Load_Texture.h"
#include "Player.h"
#include "Automate.h"
#include "Bullet.h"
#include<vector>
#include "Enemy.h"
#include "Spavn.h"
#include "Cartrige.h"
#include "View.h"
#include "LevelLoad.h"
#include <string>
#include<ctime>
#include"Boss.h"
#include"Trains.h"
#include"HelthBar.h"
using namespace std;

int main()
{
    
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    sf::SoundBuffer runBuffer;
    sf::Sound runSound;
    sf::SoundBuffer themBuffer;
    sf::Sound themSound;

    shootSound.setVolume(80);

    if (!shootBuffer.loadFromFile("Sounds/shoot.wav")) {
        std::cerr << "Failed to load shoot.wav" << std::endl;
    }
    if (!runBuffer.loadFromFile("Sounds/Top.wav")) {
        std::cerr << "Failed to load shoot.wav" << std::endl;
    }
    if (!themBuffer.loadFromFile("Sounds/Metro2025_them.wav")) {
        std::cerr << "Failed to load shoot.wav" << std::endl;
    }


    runSound.setBuffer(runBuffer);
    shootSound.setBuffer(shootBuffer);
    themSound.setBuffer(themBuffer);

    sf::Font font;
    font.loadFromFile("Texturs/RodchenkoBTT.ttf");
    srand(time(0));
    sf::Text text("", font, 50);
    sf::Text text2("", font, 30);
    sf::Text Count_Cartrige("", font, 30);
    sf::Text Count_Enemy("", font, 30);


    float timerDead = 5.0;


    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML works!");

    view.reset(sf::FloatRect(0, 0, 1000, 900));

    view.reset(sf::FloatRect(0, 0, 1240, 900));

    LifeBar lifeBarPlayer;

    textures::Level_texture();
    std::vector<sf::Sprite> levelTiles;

    int num_level = 1;
    string name_fail_map = "Levels/level_" + to_string(num_level);
    LevelLoad(name_fail_map + ".txt", textures::level_texture, levelTiles);

    textures::Player_setTextures();
    Player* player = new Player(textures::player_texture, sf::Vector2f(200, 300), 100);
/////////////////////
    textures::Boss_texture();
    Boss* boss = nullptr;
/////////////////////
    textures::Train1_texture();
    vector<Train> trains;
    //Train* train1 = new Train(textures::train1_texture, sf::Vector2f(500, 300));
    spawnTrain(1, 3, trains, textures::train1_texture, 310);

    textures::Automat_texture();
    Automat* automat = new Automat(textures::automat_texture, sf::Vector2f(200, 300), 30);

    textures::Enemy_texture();
   
    vector<Enemy> enemies;
    spawnEnemy(10, 15, enemies, textures::enemy_texture);
    
    textures::Cartrige_texture();
    

    textures::Bullet_texture();

    vector<Bullet> bullets;
    float fireCooldown = 0.f;
    float fireRate = 0.2f;

    vector<Cartriges> cartrige;
    spawnCartriges(2, 6, cartrige, textures::cartrige_texture);

    sf::Clock clock;
    bool Vinner = false;
    
    while (window.isOpen()) {
      
 
        float time = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //train1->Update(time);
        
        player->Update(time);
        //player->colision(train1->getSprite());
        player->restrictions();
        if (player->getState() == State::RUN) {
            if (runSound.getStatus() != sf::Sound::Playing) {
                runSound.play();
            }
        }
        else {
            if (runSound.getStatus() == sf::Sound::Playing) {
                runSound.stop(); // Останавливаем шаги, если игрок не бежит
            }
        }


        lifeBarPlayer.update(player->getHP());

        for (auto& train : trains) {
            train.Update(time);
            player->colision(train.getSprite());
            /*if (boss != nullptr) {
                boss->colision(train.getSprite());
            }*/
        }
        getCameraPosition(player->getPosition());
        automat->Update_weapon(time, player, window);
        
        for (auto& enemy : enemies) {
            sf::Vector2f player_p = player->getPosition();
            enemy.setPlayerPosition(player_p);
            enemy.ataka(time, player);
            enemy.Update(time);
           
           // enemy.colisions(trains);
        }
        //cout << player->count_dead_enemy << " ";
        sf::Vector2f player_p = player->getPosition();
        ///////////////////////
        if (boss != nullptr) {
            boss->setPlayerPosition(player_p);
            boss->ataka(time, player);
            boss->Update(time);
        }
        /////////////////////////////
        fireCooldown -= time;
        if (automat->getState() == State_w::SHOOTING && automat->getCartridges() != 0) {
            if (fireCooldown <= 0.f) {
                bullets.emplace_back(textures::bullet_texture, automat->getPosition(), automat->getDirectionMausse());
                fireCooldown = fireRate;
                automat->setCartriges(automat->getCartridges() - 1);
                shootSound.play();
            }

        }
       
        for (int i = 0; i < cartrige.size(); ) {
            cartrige[i].CartrigeReload(player);
            if (!cartrige[i].flag_crt) {
                cartrige.erase(cartrige.begin() + i);
            }
            else {
                ++i;
            }
        }

       
        for (int i = 0; i < bullets.size(); ) {
            bullets[i].Update(time);

            bool hit = false;
            for (auto& enemy : enemies) {
                if (enemy.isIntersection(bullets[i].getSprite())) {
                    enemy.takeDamage(bullets[i].m_damage);
                    if (enemy.isDead()) {
                        player->count_dead_enemy++;
                    }
                    hit = true;
                    break;
                }
            }

            if (hit || !bullets[i].isAlife()) {
                bullets.erase(bullets.begin() + i);
            }
            else {
                ++i;
            }
        }

        if (boss != nullptr) {
            for (int i = 0; i < bullets.size(); ) {
                bullets[i].Update(time);
                if (boss && boss->isIntersection(bullets[i].getSprite())) {
                    boss->takeDamage(bullets[i].m_damage);
                    bullets.erase(bullets.begin() + i);
                    continue;
                }
                if (!bullets[i].isAlife()) {
                    bullets.erase(bullets.begin() + i);
                }
                else {
                    ++i;
                }
            }
        }
        ///////////обработка уровня
    
        if (player->getPosition().x > 3840 && player->getPosition().x < 3904 &&
            player->getPosition().y > 340 && player->getPosition().y < 416) {

           
            if (num_level == 3) {
                if (boss && boss->isDead()) {
                    
                    num_level++;
                    cartrige.clear();
                    bullets.clear();
                    enemies.clear();
                    trains.clear();

                    LevelLoad("Levels/station.txt", textures::level_texture, levelTiles);
                    sf::Vector2f p(300, 400);
                    player->setPosition(p);
                    player->setLife(1);
                    boss = nullptr;
                    Vinner = true;
                }
       
                else {
                    
                }
            }

    
            else if (num_level < 3) {
                cartrige.clear();
                bullets.clear();
                enemies.clear();
                trains.clear();

                num_level++;

                string name_fail_map = "Levels/level_" + to_string(num_level);
                LevelLoad(name_fail_map + ".txt", textures::level_texture, levelTiles);

                sf::Vector2f p(100, 400);
                player->setPosition(p);

                spawnCartriges(2, 6, cartrige, textures::cartrige_texture);
                spawnTrain(1, 2, trains, textures::train1_texture, 310);

                spawnEnemy(10, 15, enemies, textures::enemy_texture);
            }

         
            if (num_level == 3 && boss == nullptr) {
                boss = new Boss(textures::boss_texture, sf::Vector2f(2000, 200), 200, 10, 250.f, 64, 0.08, 5.f);
                spawnEnemy(15, 20, enemies, textures::enemy_texture);
            }
        }

        if ((player->is_Life() == false) || Vinner == true) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                themSound.stop();
                cartrige.clear();
                bullets.clear();
                enemies.clear();
                trains.clear();
                LevelLoad("Levels/level_1.txt", textures::level_texture, levelTiles);
                sf::Vector2f p(100, 400);
                player->setPosition(p);
                player->setLife(1);
                lifeBarPlayer.update(player->getHP());
                num_level = 1;
                boss = nullptr;
                Vinner = false;
                spawnEnemy(10, 15, enemies, textures::enemy_texture);
                spawnCartriges(4, 6, cartrige, textures::cartrige_texture);
                spawnTrain(1, 2, trains, textures::train1_texture, 310);
               
            }
       }
        
        


        window.setView(view);
        window.clear();

        
        
        for (auto& tile : levelTiles) {
            window.draw(tile);
        }
        
        //window.draw(train1->getSprite());
        for (auto& train : trains) {
            window.draw(train.getSprite());
        }
        

        for (auto & bullet : bullets) {
            window.draw(bullet.getSprite());
        }
        for (auto& crt : cartrige) {
            window.draw(crt.getSprite());
        }
        if (boss != nullptr) {
            window.draw(boss->getSprite());
        }
        window.draw(player->getSprite());
        window.draw(automat->getSprite());
       
        for (auto& enemy : enemies) {
            window.draw(enemy.getSprite());
        }

        if (Vinner == true && player->is_Life()) {
            
            if (themSound.getStatus() != sf::Sound::Playing) {
                themSound.play();
            }
            text.setString("You VVin");
            text2.setString("Enter -> restart");
            Count_Enemy.setString("Enemies killed " + to_string(player->count_dead_enemy));

            text.setFillColor(sf::Color::Red);
            text2.setFillColor(sf::Color::Red);
            Count_Enemy.setFillColor(sf::Color::Yellow);
            text.setCharacterSize(100);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.width / 2, textBounds.height / 2);
            text.setPosition(view.getCenter());
            text2.setPosition(view.getCenter().x, view.getCenter().y + 80);
            Count_Enemy.setPosition(view.getCenter().x, view.getCenter().y + 150);
            window.draw(text);
            window.draw(text2);
            window.draw(Count_Enemy);
        }
        
        if (!player->is_Life()) {
            text.setString("Game Over");
            text2.setString("Enter -> restart");

            text.setFillColor(sf::Color::Red);
            text2.setFillColor(sf::Color::Red);
            text.setCharacterSize(100);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.width / 2, textBounds.height / 2);
            text.setPosition(view.getCenter());
            text2.setPosition(view.getCenter().x, view.getCenter().y + 80);
            window.draw(text);
            window.draw(text2);
        }
        lifeBarPlayer.draw(window);
        Count_Cartrige.setString(to_string(player->count_cartrige));
        sf::Vector2f center = window.getView().getCenter();
        sf::Vector2f size = window.getView().getSize();
        Count_Cartrige.setPosition(center.x - size.x / 2 + 10, center.y - size.y / 2 + 200);
        window.draw(Count_Cartrige);

        window.display();
    }
    
    delete player;
    delete automat;
    delete boss;
    return 0;
}