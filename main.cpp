#ifndef MAIN_CPP
#include "ScreenGen.h"
#include "player.h"
#include "invader.h"
#include "bullet.h"
#include "barrier.h"
#include "gameEngine.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <chrono>
#define MAIN_CPP

using namespace std;

using namespace std::chrono;

typedef void * (*THREADFUNCPTR)(void *);

gameEngine gameMechanics;

sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders");

ScreenGen myGame(window);

bool input[8]; //LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, SPACE = 4, ENTER = 5, P = 6, ESC = 7 

void* draw_the_game(void *){
    
    myGame.drawGameWithEngine(window,gameMechanics); 
    
    return NULL;
    
}

void* readInput(void *){
    
for(int i = 0; i < 8; i++){
    
    input[i] = false;
    
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
             input[7] = true;
}    

if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) ){//&& this->gamer->getLives() > 0 ){
             input[6] = true;
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
             input[0] = true;
}

else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
             input[1] = true;
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
             input[4] = true;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
             input[2] = true;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
             input[3] = true;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
             input[5] = true;
}

return NULL;

}

int main()
{   
    
    cout << "Generating Screen\n";
    //sf::RenderWindow window(sf::VideoMode(800, 600), "Enschede Invaders");  //For now , this have to be generate a 800x600, there is no automated way to re-scale screen  
    //ScreenGen myGame(window);
    cout << "Loading Game...\n";
    //gameEngine gameMechanics;
    //cout << gameEngine->getInvaders().size();        
    myGame.splashScreen(window);//Create a initial screen before the game    
    //A menu to make the game more presentable, it
    
    
    pthread_t check_input;
    pthread_t run_game;
    pthread_t draw_game;
    
    bool B_1 = false;
    bool B_2 = true;
    bool B_3 = true;

    while (window.isOpen())
    {     
        if(gameMechanics.exitGame()){
            window.close();
            return 0;        
    }
    
    sf::Event event;    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
    
    if(B_2 && B_3){
        B_2 = false;
        B_3 = false;
        
        //cout << "joe" << "\n";
        
        pthread_create(&run_game, NULL, (THREADFUNCPTR) &gameEngine::runGame, &gameMechanics); 
        pthread_join(run_game, NULL);
        B_1 = true;
    }
    
    if(B_1){
        //cout << "poep" << "\n";
        B_1 = false;
        pthread_create(&check_input, NULL, readInput, NULL);
        //cout << "neen" << "\n";
        pthread_join(check_input, NULL);
        //cout << "pies" << "\n";
        //myGame.drawGameWithEngine(window,gameMechanics); 
        //draw_the_game(NULL);
        //cout << "troep" << "\n";
        pthread_create(&draw_game, NULL, draw_the_game, NULL);

        //pthread_join(check_input, NULL);
        
        pthread_join(draw_game, NULL);
        //pthread_join(check_input, NULL);
        
        B_2 = true;
        B_3 = true;
    }
    
    //pthread_create(&check_input, NULL, (THREADFUNCPTR) &gameEngine::runGame, &gameMechanics); 
    
    //pthread_join(check_input, NULL);


    
    //gameMechanics.runGame();
    
    //myGame.drawGameWithEngine(window,gameMechanics); 
    
    //auto start = high_resolution_clock::now();
       
    //auto stop = high_resolution_clock::now();
    //auto duration = duration_cast<microseconds> (stop - start);
    //cout << duration.count() << endl;

    //sf::sleep(sf::milliseconds(100));
  
}    
    return 0;
}



#endif
