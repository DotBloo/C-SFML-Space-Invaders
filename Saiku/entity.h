#ifndef ENTITY_H_INCLUDED
#define ENTITY_H_INCLUDED
#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>

class gameWorld{
private:
    unsigned long long int key=0;
    //textures, sprites and sound buffers
    sf::Texture winTexture;
    sf::Texture laserTexture;
    sf::Texture death;
    sf::Texture alienTexture;
    sf::Texture alienTexture2;
    sf::Texture logoTexture;
    sf::Texture backgroundTexture;
    sf::Texture easterEgg;
    sf::Texture orDidyouTexture;
    sf::Texture directedTexture;
    public:
    sf::SoundBuffer gameMusicBuff;
    sf::Sound gameMusic;
    sf::SoundBuffer laserFireBuff;
    sf::Sound laserFire;
    sf::SoundBuffer startMusicBuff;
    sf::SoundBuffer bossMusicBuff;
    sf::SoundBuffer cheeringBuff;
    sf::Sound bossMusic;
    sf::Music startMusic;
    sf::Sound easterEggCredit;
    sf::SoundBuffer easterEggCreditBuff;
    sf::SoundBuffer alienDeadBuffer;
    sf::Sound alienDead;
    sf::Sound cheering;
    sf::Sprite directedBySprite;
    sf::Sprite youWinSprite;
    sf::Sprite orDidYouSprite;
    sf::Sprite easterEggSprite;
    sf::Sprite alienSprite;
    sf::Sprite alienSprite2;
    sf::Sprite laserSprite;
    sf::Sprite deathSprite;
    sf::Sprite logoSprite;
    sf::Sprite backgroundSprite;
    //textures, sprites and sound, buffers

    sf::Vector2f alienPos[10][5]; //alien position stored in array of vector2fs
    int HP[10][5]; //HP stored same way
    sf::Vector2f playerPos;
    int m, n;
    bool gameStart=false;
    bool win=false;
    gameWorld(){ //initializes all buffers, textures and sounds
        alienDead.setVolume(20);
        cheeringBuff.loadFromFile("Data/Sounds/cheer.wav");
            cheering.setBuffer(cheeringBuff);
            cheering.setVolume(20);
            cheering.setLoop(false);
        easterEggCreditBuff.loadFromFile("Data/Sounds/EasterEgg2.flac");
            easterEggCredit.setBuffer(easterEggCreditBuff);
        directedTexture.loadFromFile("Data/Sprites/Directed.png");
            directedBySprite.setTexture(directedTexture);
        winTexture.loadFromFile("Data/Sprites/win.png");
            youWinSprite.setTexture(winTexture);
        orDidyouTexture.loadFromFile("Data/Sprites/or.png");
            orDidYouSprite.setTexture(orDidyouTexture);
        bossMusicBuff.loadFromFile("Data/Sounds/EasterEgg1.flac");
            bossMusic.setBuffer(bossMusicBuff);
            bossMusic.setVolume(40);
        easterEgg.loadFromFile("Data/Sprites/EasterEgg.png");
            easterEggSprite.setTexture(easterEgg);
        laserFireBuff.loadFromFile("Data/Sounds/blaster-firing.wav");
            laserFire.setBuffer(laserFireBuff);
            laserFire.setVolume(20);
        laserTexture.loadFromFile("Data/Sprites/laser.png");
            laserSprite.setTexture(laserTexture);
        alienDeadBuffer.loadFromFile("Data/Sounds/R2D2-do.wav");
            alienDead.setBuffer(alienDeadBuffer);
        alienTexture.loadFromFile("Data/Sprites/alien1.png");
            alienSprite.setTexture(alienTexture);
        alienTexture2.loadFromFile("Data/Sprites/alien2.png");
            alienSprite2.setTexture(alienTexture2);
        gameMusicBuff.loadFromFile("Data/Sounds/Game.wav");
            gameMusic.setVolume(20);
            gameMusic.setBuffer(gameMusicBuff);
            gameMusic.setLoop(true);
        startMusic.openFromFile("Data/Sounds/Start.wav");
            startMusic.setVolume(20);
            startMusic.setLoop(true);
        backgroundTexture.loadFromFile("Data/Sprites/stars.png");
            backgroundSprite.setTexture(backgroundTexture);
        logoTexture.loadFromFile("Data/Sprites/logo1.png");
            logoSprite.setTexture(logoTexture);
        death.loadFromFile("Data/Sprites/DEATHISTHEONLYANSWER.png");
            deathSprite.setTexture(death);
    }
    void setUpInitialState(){  //initial state of the game
        setUpEnemyPos(1);

        gameStart=false;playerPos=sf::Vector2f((1400/2 )-35, 700-70);
        backgroundSprite.setPosition(sf::Vector2f(0,-14000+700));
        win=false;
        cheering.setPlayingOffset(sf::seconds(3));
    }
    void setUpEnemyPos(int level){ //enemy position setting
        int i, j, x;
        if(level==1)
        {
            for(i=1;i<10;i++)
            {
                x=140*i;
                for(j=0;j<3;j++)
                {
                    alienPos[i][j].y=140*j;
                    if(i%2)
                        alienPos[i][j].y+=70;
                    alienPos[i][j].x=x;
                    HP[i][j]=500;
                }
            }
            m=10, n=3;
        }
        else if(level==2) //a level 2 that will never be used because i am lazy
        {
            for(i=1;i<10;i++)
            {
                x=140*i;
                for(j=0;j<5;j++)
                {
                    alienPos[i][j].y=70*j;
                    alienPos[i][j].x=x;
                    HP[i][j]=500;
                }
            }
            m=10;
            n=5;
        }
    }
    void updateEnemy() //moving enemy left and right to make them move and not seem dead because i am too lazy to make animation sprites
    {
        int i, j;
        for(i=1;i<m;i++)
        {
            for(j=0;j<n;j++)
            {
                if(alienPos[i][j].x!=-140)
                {
                    if(key%2){
                        alienPos[i][j].x+=20;
                    }
                    else
                    {
                        alienPos[i][j].x+=-20;
                    }
                    alienPos[i][j].y+=4;
                }
            }
        }
        key++;
    }
    void initaliseEasterEgg() // aw shit here we go again
    {
        easterEggSprite.setPosition(sf::Vector2f(35, -700));
    }
};
class playerClass{ //stores player stuff like if player dead or not, position and controls player movement;
public:
    bool dead;
    sf::Vector2f pos;
    sf::Texture texture;
    sf::Sprite sprite;
    playerClass(std::string textureName, float x, float y, bool death){
        if(!setUpSprite(textureName))
            return;
        pos=sf::Vector2f(x,y);
        sprite.setPosition(pos);
        dead=death;
    }
    bool setUpSprite(std::string textureName){
        if(!texture.loadFromFile(textureName))
            return false;
        texture.setSmooth(true);
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(0,0,70,70));
        return true;
    }
    void updatePos() //detecting key and changing position of player accordingly.
    {
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))&&pos.x>0)
            pos.x+=-5;
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D))&&pos.x<1400-70)
            pos.x+=5;
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)||sf::Keyboard::isKeyPressed(sf::Keyboard::W))&&pos.y>0)
            pos.y+=-5;
        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)||sf::Keyboard::isKeyPressed(sf::Keyboard::S))&&pos.y<700-70)
            pos.y+=5;
        sprite.setPosition(pos);

    }
};
#endif
