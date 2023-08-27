#include <iostream>
#include <deque>
#include <array>
#include <algorithm>

class Snake{
    public:
        int apple[2];
        int snakeDirection[2] = {1,0};
        std::deque<std::array<int,2>> snakeBodies;
        const int WIDTH;
        const int HEIGHT;
        Snake(int length, int w, int h) : WIDTH(w), HEIGHT(h) {
            const int HEAD_Y = w/2;
            const int HEAD_X = h/2;
            for(int i = 0; i < length; i++){
                int currentX = HEAD_X-i;
                std::array<int, 2> cord = {currentX, HEAD_Y};
                snakeBodies.push_back(cord);
            }

            apple[0]=10;
            apple[1]=10;
        }


        std::array<int,2> getNextCord(){
            std::array<int,2> headCords = snakeBodies.front();
            std::array<int,2> nextCords = {headCords[0]+snakeDirection[0], headCords[1]+snakeDirection[1]};
            return nextCords;
        }

        bool checkCollision(){
            std::array<int,2> nextCords = getNextCord();
            bool insideX = nextCords[0]<WIDTH && nextCords[0]>=0;
            bool insideY = nextCords[1]<HEIGHT && nextCords[1]>=0;
            bool insideSnake = std::find(snakeBodies.begin(), snakeBodies.end(), nextCords) != snakeBodies.end();
            if(insideX&&insideY&&!insideSnake){
                return false;
            }
            return true;
        }

        bool appleInFront(){
            std::array<int,2> nextCords = getNextCord();
            if(nextCords[0] == apple[0] && nextCords[1]==apple[1]){
                return true;
            }
            return false;
        }

        void moveSnake(){
            if(checkCollision()){
                return;
            }
            std::array<int,2> nextCords = getNextCord();
            if(!appleInFront()){
                snakeBodies.push_front(nextCords);
                snakeBodies.pop_back();
                return;
            }
            snakeBodies.push_front(nextCords);
            apple[0]=rand()%(WIDTH);
            apple[1]=rand()%(HEIGHT);
        }
};

int main(){
    bool gameRunning = true;
    const int WIDTH = 16;
    const int HEIGHT = 16;
    Snake game(3, WIDTH, HEIGHT);

    while(gameRunning){

        char board[WIDTH][HEIGHT] = {' '};
        board[game.apple[0]][game.apple[1]]='A';
        for(int i = 0; i < game.snakeBodies.size(); i++){
            board[game.snakeBodies[i][0]][game.snakeBodies[i][1]]='S';
        }
        board[game.snakeBodies.front()[0]][game.snakeBodies.front()[1]]='H';

        for(int y = HEIGHT-1; y>=0; y--){
            for(int x = 0; x<WIDTH; x++){
                std::cout << board[x][y] << " ";
            }
            std::cout << std::endl;
        }

        std::string dir;
        std::cout << "Next move (up-down-right-left): " << std::endl;
        std::cin >> dir;
        if(dir== "left"){
            game.snakeDirection[0]=-1;
            game.snakeDirection[1]=0;  
        } else if(dir=="right"){
            game.snakeDirection[0]=1;
            game.snakeDirection[1]=0;
        } else if(dir=="up"){
            game.snakeDirection[0]=0;
            game.snakeDirection[1]=1;
        } else {
            game.snakeDirection[0]=0;
            game.snakeDirection[1]=-1;
        }
        gameRunning=!game.checkCollision();
        game.moveSnake();
        system("cls");
    }

    return 0;
}