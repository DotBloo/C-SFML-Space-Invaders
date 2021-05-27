#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include"entity.h"
#include<iostream>
#include"laser.h"
#include<fstream>
bool collision(sf::Vector2f a, sf::Vector2f b, int type)
{
    if(type==1)//1 for player
    {
        if(((a.x+35>b.x)&&(a.x+35<b.x+70)&&(a.y<b.y+70)&&(a.y>b.y))||((a.x>b.x)&&(a.x<b.x+70)&&(a.y+60<b.y+70)&&(a.y+60>b.y))||((a.x+70>b.x)&&(a.x=70<b.x+70)&&(a.y+60<b.y+70)&&(a.y+60>b.y)))
            return true;
        else return false;
    }
    if(type==2)//2 for lasers
    {
        if((a.x+35>b.x)&&(a.x+35<b.x+70)&&(a.y<b.y+70)&&(a.y>b.y))
            return true;
        else return false;
    }

}
int main()
{
    int i,j, wincount, playerNum=0;
    ofstream score;
    char scorePrint;
    score.open("score.txt", ios::app);
    int scoreIndex;
    ifstream scoreP;
    Laser lasers;
    int key1=0;
    scoreIndex=score.tellp();
    score<<"----------SESSION------------\n\n";
    unsigned int count=0;
    playerClass player1("Data/Sprites/Spaceship1.png",(1400/2)-35,600, false); //passing sprite and spawn values to player
    sf::RenderWindow window(sf::VideoMode(1400, 700), "Saiku");
    gameWorld gameworld;
    gameworld.setUpInitialState(); //initial state
    window.setFramerateLimit(60);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type==sf::Event::Closed)
                window.close();
        }
        if(key1==0)
                    gameworld.startMusic.play();
        key1++;
        window.clear();
         if(!gameworld.gameStart) //startup screen
        {

                window.draw(gameworld.logoSprite);
                window.display();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) //exit out of logo screen, stop logo music, start game music
                {
                    playerNum++;
                    gameworld.gameStart=true; //start of game set to true
                    gameworld.startMusic.stop();
                    gameworld.gameMusic.play();
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                {
                    system("CLS");
                    score.close();
                    scoreP.open("score.txt", ios::in);
                    scoreP.seekg(scoreIndex);
                    while(!scoreP.eof())
                    {
                        scoreP>>noskipws>>scorePrint;
                        std::cout<<scorePrint;
                    }

                    scoreP.close();
                    score.open("score.txt", ios::app);
                }
        }
        else{
            if(!player1.dead)  //if player not dead
            {

                if(!gameworld.win){
                    if(key1%20==0)
                        gameworld.updateEnemy();
                    player1.updatePos();
                    gameworld.backgroundSprite.move(sf::Vector2f(0,1)); //moving the background
                    window.draw(gameworld.backgroundSprite);
                    window.draw(player1.sprite);
                    if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)||sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)||sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))&&key1%6==5) //key1 limits one fire per 5 frames, me being indecisive about firing switch
                    {
                        lasers.Insert(sf::Vector2f(player1.pos.x+35/2,player1.pos.y)); //inserts a new node in linked list with data member of node being position of center of the  in Vector2f type
                        gameworld.laserFire.play(); //sound of laser being fire played
                    }
                //queue test
                    lasers.temp = lasers.front; //queued linked list stuffs. my brain died doing this
                    while (lasers.temp != NULL) {
                        gameworld.laserSprite.setPosition(lasers.temp->data);
                        window.draw(gameworld.laserSprite);
                        lasers.temp->data.y+=-5;
                        if(lasers.temp->data.y<=0) //deletes member if position is lesser than y==0, being top of the window (it will be above the window.)
                            lasers.Delete();
                        lasers.temp = lasers.temp->next;

                        }
                    lasers.temp = lasers.front;
                    while (lasers.temp != NULL) { //same loop as above but this is for collision detection between each laser and each alien;

                        for(int i=1;i<gameworld.m;i++)
                        {
                            for(int j=0;j<(gameworld.n);j++)
                            {
                                if(lasers.temp!=NULL)
                                {
                                    if ((collision(sf::Vector2f(lasers.temp->data.x, lasers.temp->data.y), gameworld.alienPos[i][j], 2)))
                                        {
                                            lasers.Delete();
                                            gameworld.HP[i][j]+=-50; //if collision detected, HP of the alien is reduced by 50
                                            if(gameworld.HP[i][j]<=0) //hp below 0 (d e d)>
                                            {
                                                gameworld.alienDead.play();
                                                gameworld.alienPos[i][j].x=-140; //if alien is dead, i set their x coord to -140. using this to detect dead aliens.|| if any bugs in drawing, they draw off the window
                                            }
                                        }
                                }
                            }
                        }
                        lasers.temp = lasers.temp->next;
                    }
                //drawing aliens
                    for( i=1;i<gameworld.m;i++)
                    {
                        for( j=0;j<gameworld.n;j++)
                        {
                            if (((collision(player1.pos, gameworld.alienPos[i][j], 1)||(gameworld.alienPos[i][j].y+70>=700)))&&gameworld.alienPos[i][j].x!=-140)
                                {
                                    player1.dead=true;
                                    gameworld.win=false;
                                    score<<"Player "<<playerNum<<" scored  "<<wincount<<std::endl;
                                    break;
                                }
                            if(gameworld.alienPos[i][j].x!=-140){
                                count++;
                                if(i%2||j%2!=0){ //some random logic to make a pattern with two different alien sprites
                                        gameworld.alienSprite.setPosition(gameworld.alienPos[i][j]);
                                        window.draw(gameworld.alienSprite);
                                    }
                                else{
                                        gameworld.alienSprite2.setPosition(gameworld.alienPos[i][j]);
                                        window.draw(gameworld.alienSprite2);
                                    }
                            }
                        }
                    }
                    wincount=27-count;
                    if(count==0){ //count= number of aliens alive. if 0, game won.
                        gameworld.win=true;
                        if(gameworld.win)
                            key1=1;
                    }
                    else
                        count=0;
            } //if player has won true
            else{
                    gameworld.gameMusic.stop();//stopping game music
                    if(key1<280)
                    {   if(key1==4)
                        {
                            gameworld.cheering.play();
                            score<<"Player "<<playerNum<<" won the game!\n";
                        }
                        window.draw(gameworld.youWinSprite); //drawing Winning sprite on screen

                        if(key1==150)
                            gameworld.cheering.stop();
                        else if(key1==200)
                            gameworld.bossMusic.play();
                    }
                    else if(key1<500)
                    {
                        //let's skip over this part unless i have already executed the game
                        window.draw(gameworld.orDidYouSprite);
                    }
                    else
                    {
                        if(key1==500)   //A little something something.
                            gameworld.initaliseEasterEgg();
                        window.draw(gameworld.easterEggSprite);
                        player1.sprite.setPosition(sf::Vector2f(700-35,100));
                        player1.updatePos();
                        window.draw(player1.sprite);
                        gameworld.easterEggSprite.move(sf::Vector2f(0, 1));
                        if(gameworld.easterEggSprite.getPosition().y+700>700+35||key1==1235)
                        {
                                player1.dead=true;
                                key1=1;
                        }
                    }
            }
        }
        else{ //this is the whole condition for dead player
                if(!gameworld.win){ // dead and lost
                    gameworld.gameMusic.stop();
                    window.draw(gameworld.deathSprite); //dead screen
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){ //pressing Enter to reset game
                        gameworld.setUpInitialState();
                        player1.pos=gameworld.playerPos;
                        player1.dead=false;
                        gameworld.startMusic.play();
                        lasers.DeleteAll();
                    }
                }
                else{//dead and won
                    gameworld.bossMusic.stop();
                    if(key1==2)
                        gameworld.easterEggCredit.play();
                    window.draw(gameworld.directedBySprite);
                    gameworld.directedBySprite.move(sf::Vector2f(0,-2));
                    if(gameworld.directedBySprite.getPosition().y<-10000||sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
                    {
                        lasers.DeleteAll();
                        gameworld.easterEggCredit.stop(); //lul easter egg it seems it wasnt even one
                        gameworld.setUpInitialState();
                        player1.pos=gameworld.playerPos;
                        player1.dead=false;
                        gameworld.startMusic.play();
                    }

                }
                key1++;
            }

        window.display(); //displaying everything that is drawn

        if(key1>5000000)
            key1=6; //making sure key going above int limit doesn't cause any problems
        }
        if(gameworld.backgroundSprite.getPosition().y==0)
            gameworld.backgroundSprite.setPosition(sf::Vector2f(0,-14000+700)); //resetting background to initial state if the reel ends
    }
}
