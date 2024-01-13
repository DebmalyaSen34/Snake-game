#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

const int width = 80;
const int height = 20;

int x, y;

int fruit_x, fruit_y;

int player_score;

int snake_tail_x[100], snake_tail_y[100];

int snake_length;

enum snake_direction{
    STOP = 0,
    LEFT, RIGHT, UP, DOWN
};

snake_direction s_direction;

bool is_Game_over;

void Game_init(){
    is_Game_over = false;
    s_direction = STOP;
    x = width/2;
    y = height/2;
    fruit_x = rand() % width;
    fruit_y = rand() % height;
    player_score = 0;
}

void Game_board(string player){
    system("cls");

    for(int i=0; i<width+2; i++){
        cout<<"-";
    }
    cout<<endl;

    for(int i=0; i<height; i++){
        for(int j=0; j<=width; j++){
            if(j==0 or j==width){
                cout<<"|";
            }
            if(i==y and j==x){
                cout<<"O";
            }else if(i==fruit_y and j==fruit_x){
                cout<<"#";
            }else{
                bool pr_tail = false;
                for(int k=0; k<snake_length; k++){
                    if(snake_tail_x[k]==j and snake_tail_y[k]==i){
                        cout<<"o";
                        pr_tail = true;
                    }
                }
                if(!pr_tail){
                    cout<<" ";
                }
            }
        }
        cout<<endl;
    }
    for(int i=0; i<width+2; i++){
        cout<<"-";
    }
    cout<<endl;

    cout<<player<<"'s score is: "<<player_score<<endl;
}

void game_update(){
    int prev_x = snake_tail_x[0];
    int prev_y = snake_tail_y[0];
    int prev_2x, prev_2y;
    snake_tail_x[0] = x;
    snake_tail_y[0] = y;

    for(int i=0; i<snake_length; i++){
        prev_2x = snake_tail_x[i];
        prev_2y = snake_tail_y[i];
        snake_tail_x[i] = prev_x;
        snake_tail_y[i] = prev_y;
        prev_x = prev_2x;
        prev_y = prev_2y;
    }

    switch(s_direction){
        case LEFT:
        {
            x--;
            break;
        }
        case RIGHT:
        {
            x++;
            break;
        }
        case UP:
        {
            y--;
            break;
        }
        case DOWN:
        {
            y++;
            break;
        }
    }

    if(x>=width or x<0 or y>=height or y<0){
        is_Game_over = true;
    }
    for(int i=0; i<snake_length; i++){
        if(snake_tail_x[i]==x and snake_tail_y[i]==y){
            is_Game_over = true;
        }
    }

    if(x==fruit_x and y==fruit_y){
        player_score+=10;
        fruit_x = rand() % width;
        fruit_y = rand() % height;
        snake_length++;
    }
}

int difficulty(){
    int dfc, choice;
    cout<<"Set difficulty: "<<endl;
    cout<<"1. Easy\n2. Medium\n3. Hard"<<endl;
    cout<<"(If not chosen then medium difficulty will be chosen as default)"<<endl;
    cout<<"Chose difficulty: "<<endl;
    cin>>choice;
    switch(choice){
        case '1':
        {
            dfc = 50;
            break;
        }
        case '2':
        {
            dfc = 100;
            break;
        }
        case '3':
        {
            dfc = 150;
            break;
        }
        default: 
        {
            dfc = 100;
        }
    }
    return dfc;
}

void user_input(){
    if(_kbhit()){
        // _kbhit() function checks the console for a recent keystroke.
        // If the function returns a nonzero value, a keystroke is waiting in the buffer.
        // The program can then call _getch() or _getche() to get the keystroke.
        switch(_getch()){
            case 'a':
            {
                s_direction = LEFT;
                break;
            }
            case 'd':
            {
                s_direction = RIGHT;
                break;
            }
            case 'w':
            {
                s_direction = UP;
                break;
            }
            case 's':
            {
                s_direction = DOWN;
                break;
            }
            case 'x':
            {
                is_Game_over = true;
                break;
            }
        }
    }
}

int main(){
    string player;
    cout<<"Enter your name: "<<endl;
    getline(cin, player);
    int dfc = difficulty();
    Game_init();

    while(!is_Game_over){
        Game_board(player);
        user_input();
        game_update();
        // According to difficulty the sleep value is initialized
        Sleep(dfc);
    }
    return 0;
}