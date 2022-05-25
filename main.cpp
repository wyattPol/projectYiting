#include <iostream>
#include<SFML/Graphics.hpp>
#include<time.h>
#include<vector>
#include<algorithm>
using namespace sf;
using namespace std;
/*
class Dragon:public AnimatedAssets{
public:
    Texture *Tex;
    Sprite dragonshape;
    Dragon(Texture *Tex):AnimatedAssets(){
        this->Tex=Tex;
        this->dragonshape.setTexture(*Tex);
        this->dragonshape.setScale(0.1,0.1);
        this->dragonshape.setPosition(100,300);
    }
    void SingleAnimation(){
        double speed=0;
        double gra=150;
        dragonshape.move(0,speed*gra);

    }

};*/
class AnimatedAssets{
public:
    Texture *Tex;
    AnimatedAssets(){
        this->Tex=Tex;
    }
};
class Explosion:public AnimatedAssets{
public:
    Explosion(Texture *Tex):AnimatedAssets(){
    this->Tex=Tex;
    this->exploshape.setTexture(*Tex);
    this->exploshape.setScale(0.5,0.5);
    this->exploshape.setPosition(-300,-300);
    }
    Texture *Tex;
    Sprite exploshape;

};
class Bullet:public AnimatedAssets{
public:
    Sprite bulletshape;
    Texture *bulletTex;
    Bullet(Texture *bulletTex):AnimatedAssets(){
        this->bulletTex=bulletTex;
        this->bulletshape.setTexture(*bulletTex);
        this->bulletshape.setScale(0.1,0.1);
        this->bulletshape.setPosition(rand()%1550+50,0);
    }
};
class ColorEnemy:public AnimatedAssets{
public:
    Sprite enemyshape;
    Texture *colortex;
    ColorEnemy(Texture *colortex):AnimatedAssets(){
        this->colortex=colortex;
        this->enemyshape.setTexture(*colortex);
        this->enemyshape.setScale(0.13,0.13);
        this->enemyshape.setPosition(1600,rand()%870+60);
    }
    void moveopposite(){
        enemyshape.move(0,0);
        enemyshape.move(5,-5);
    }

};

class Player{
public:
    Sprite stardog;
    Texture *starTex;
    Player(Texture *starTex){
        this->starTex=starTex;
        this->stardog.setTexture(*starTex);
        this->stardog.setScale(0.12,0.12);
        this->stardog.setPosition(25,900);

    }
   /* void settarget(){
        stardog.move(10,20);
    }*/ //移动到指定点的函数
};
class BlueEnemy:public AnimatedAssets{
public:
    Sprite enemyshape;
    Texture *bluetex;
    BlueEnemy(Texture *bluetex):AnimatedAssets(){
        this->bluetex=bluetex;
        this->enemyshape.setTexture(*bluetex);
        this->enemyshape.setScale(0.11,0.11);
        this->enemyshape.setPosition(1600,rand()%870+60);
    }
    void moveopposite(){
        enemyshape.move(0,0);
        enemyshape.move(5,-5);

    }

};

class Wall{
public:
    Sprite wallshape;
    Texture *wallTex;
    Wall(Texture *wallTex){
        this->wallTex=wallTex;
        this->wallTex->setRepeated(true);
        this->wallshape.setTexture(*wallTex);
        this->wallshape.setScale(0.5,0.5);
        this->wallshape.setTextureRect(sf::IntRect(150, 100, 150, rand()%21+300));
        this->wallshape.rotate(90);
        this->wallshape.setPosition(rand()%1300+300,rand()%900+100);
    }
};
void moveInDirection(Sprite &player,const sf::Time &elapsed, const sf::Keyboard::Key key)
{
    double speed_x=400;
    double speed_y=400;
    if(player.getGlobalBounds().left>=0 &&key==Keyboard::A)
      {

      player.move(-speed_x*elapsed.asSeconds(), 0);
      }
    if(player.getGlobalBounds().left+player.getGlobalBounds().width<1850&&key==Keyboard::D)
      {

      player.move(speed_x*elapsed.asSeconds(),0);
      }
    if(player.getGlobalBounds().top>=0&&key==Keyboard::W)
      {

       player.move(0,-speed_y*elapsed.asSeconds());
      }
    if(player.getGlobalBounds().top+player.getGlobalBounds().height<1000&&key==Keyboard::S)
      {

       player.move(0,speed_y*elapsed.asSeconds());
      }
}
int main()
{
   Clock clock;
   RenderWindow window(VideoMode(1600,1080),"DOG ROAD KILLER");
   window.setFramerateLimit(60);
           srand(time(NULL));
           sf::Time elapsed=clock.restart();
   //UI Init
   int level=0;
   int life=3;
   Font font,gamefont;
   font.loadFromFile("IMMORTAL.ttf");
   gamefont.loadFromFile("BebasNeue-Regular.ttf");
   Text scores,gameover,lifes,easy,hard;
   scores.setCharacterSize(40);
   scores.setFont(font);
   scores.setFillColor(Color::White);
   scores.setPosition(30,30);
   gameover.setFont(gamefont);
   gameover.setCharacterSize(300);
   gameover.setFillColor(Color::Red);
   gameover.setPosition(400,300);
   gameover.setString("GAME OVER");
   lifes.setCharacterSize(40);
   lifes.setFont(font);
   lifes.setFillColor(Color::White);
   lifes.setPosition(30,70);
   easy.setFont(gamefont);
   easy.setCharacterSize(300);
   easy.setFillColor(Color::Red);
   easy.setPosition(500,200);
   easy.setString("E A S Y");
   hard.setFont(gamefont);
   hard.setCharacterSize(300);
   hard.setFillColor(Color::Red);
   hard.setPosition(500,600);
   hard.setString("H A R D");
   //Init Background
   int score=100;
   Sprite background;
   Texture backTex;
   backTex.loadFromFile("road.png");
   background.setScale(float(window.getSize().x)/float(backTex.getSize().x),
                   float(window.getSize().y)/float(backTex.getSize().y));
   background.setTexture(backTex);
   //Init explosion
   Texture exploTex;
   exploTex.loadFromFile("explosion.png");

   Explosion explosion(&exploTex);
   //Init bullet
   Texture bullTex;
   bullTex.loadFromFile("bullet.png");
   vector<Bullet> bullets;
   //Init Player
   int speedmoveback=400;
   Texture starTex;
   starTex.loadFromFile("stardog.png");
   Player player(&starTex);
   //Init Wall
   Texture wallTex;
   wallTex.loadFromFile("wall.png");
   vector<Wall> walls;
   for(int j=0;j<5;j++){
      walls.push_back(Wall(&wallTex));
    }
   //Init BlueEnemy
   int enemySpawnTimer=0;
   int colorSpawnTimer=0;
   Texture bluetex;
   bluetex.loadFromFile("blue.png");
   vector<BlueEnemy> bluenemies;
   bluenemies.push_back(BlueEnemy(&bluetex));
   //Init ColorEnemy
   Texture colortex;
   colortex.loadFromFile("color.png");
   vector<ColorEnemy> colorenemies;
   colorenemies.push_back(ColorEnemy(&colortex));
 while (window.isOpen()){
     Event event;
     while(window.pollEvent((event)))
    {
     if(event.type==Event::Closed)
        window.close();
     if(event.KeyPressed && event.key.code==Keyboard::Escape)
        window.close();
   //Set Levels
     if(event.type==Event::MouseButtonPressed){
         if(Mouse::isButtonPressed(Mouse::Left)) {

             if(Mouse::getPosition().y<=600){
                 level=1;
             }
             else{
                 level=2;
            }

         }
     }
     //Player Move
     if(event.type==sf::Event::KeyPressed && life!=0)
        {
         const sf::Keyboard::Key key =event.key.code;
         moveInDirection(player.stardog,elapsed,key);
         for(size_t i=0;i<walls.size();i++)
          {
             if(player.stardog.getGlobalBounds().intersects(walls[i].wallshape.getGlobalBounds()) && level==2)
             {
                 if(key==Keyboard::A)
                     player.stardog.move(speedmoveback*elapsed.asSeconds(),0);
                  else if(key==Keyboard::D)
                     player.stardog.move(-speedmoveback*elapsed.asSeconds(),0);
                  else if(key==Keyboard::W)
                     player.stardog.move(0,speedmoveback*elapsed.asSeconds());
                  else if(key==Keyboard::S)
                     player.stardog.move(0,-speedmoveback*elapsed.asSeconds());
              }
           }
         }
     }

   if(life>0)
 { //EnemiesMove
     if(enemySpawnTimer<80)
         enemySpawnTimer++;
     if(enemySpawnTimer>=80)
      {
         bluenemies.push_back(BlueEnemy(&bluetex));
         bullets.push_back(Bullet(&bullTex));
         enemySpawnTimer=0;
      }
    for(size_t i=0;i<bluenemies.size();i++)//wall and bluenemy collision detect
    {
     bluenemies[i].enemyshape.move(-3,0);
     for(size_t j=0;j<walls.size();j++)
     {
         if(bluenemies[i].enemyshape.getGlobalBounds().intersects(walls[j].wallshape.getGlobalBounds()) && level==2)
             bluenemies[i].moveopposite();
     }
        //player and bluenemy collision detect
     if(bluenemies[i].enemyshape.getPosition().x<= 0-bluenemies[i].enemyshape.getGlobalBounds().width)
         bluenemies.erase(bluenemies.begin()+i);
     if(bluenemies[i].enemyshape.getGlobalBounds().intersects(player.stardog.getGlobalBounds()))
       {  score=score-10;
         bluenemies.erase(bluenemies.begin()+i);}
    }
  //BulletMove
    for(size_t i=0;i<bullets.size();i++)
    {
        bullets[i].bulletshape.move(0,8);
        if(bullets[i].bulletshape.getGlobalBounds().intersects(player.stardog.getGlobalBounds()))
         {
            bullets.erase(bullets.begin()+i);
            life--;
        }
    }
  //ColorEnemies
    if(colorSpawnTimer<200)
        colorSpawnTimer++;
    if( colorSpawnTimer>=200)
     {
        colorenemies.push_back(ColorEnemy(&colortex));
        colorSpawnTimer=0;
     }
  //Collision Detect
    //wall and bluenemy collision detect
    for(size_t i=0;i<colorenemies.size();i++)//wall and bluenemy collision detect
    {
     colorenemies[i].enemyshape.move(-3,0);
     for(size_t j=0;j<walls.size();j++)
     {
         if(colorenemies[i].enemyshape.getGlobalBounds().intersects(walls[j].wallshape.getGlobalBounds()) && level==2)
             colorenemies[i].moveopposite();
     }
    }
     //player and colorenemy collision detect
   for(size_t i=0;i<colorenemies.size();i++)//player and colorenemy collision detect
   {
    colorenemies[i].enemyshape.move(-2,0);
    if(colorenemies[i].enemyshape.getPosition().x<= 0-colorenemies[i].enemyshape.getGlobalBounds().width)
        colorenemies.erase(colorenemies.begin()+i);
    if(colorenemies[i].enemyshape.getGlobalBounds().intersects(player.stardog.getGlobalBounds()))
    {
        colorenemies.erase(colorenemies.begin()+i);
        score+=40;
        explosion.exploshape.setPosition(player.stardog.getPosition().x,player.stardog.getPosition().y);
        break;
    }

   }
  //PlayerMove

}

  //UI Update
   scores.setString("SCORE: "+to_string(score));
   lifes.setString("Lifes: "+to_string(life));
  //Draw
   window.clear();
   window.draw(background);
if(level==0){
   window.draw(easy);
   window.draw(hard);}
if(level==2){
    for(size_t i=0;i<walls.size();i++)
    {
        window.draw(walls[i].wallshape);
    }
}
if(level==1 || level==2){
   for(size_t i=0;i<bluenemies.size();i++)
   {
    window.draw(bluenemies[i].enemyshape);

    }
   for(size_t i=0;i<colorenemies.size();i++)
   {
    window.draw(colorenemies[i].enemyshape);

    }

   for(size_t i=0;i<bullets.size();i++)
   {
       window.draw(bullets[i].bulletshape);
   }
   window.draw(explosion.exploshape);
   window.draw(player.stardog);
   window.draw(scores);
   window.draw(lifes);
   if(life==0){
       window.draw(gameover);
   }
}
   window.display();
   }
    return 0;
}
