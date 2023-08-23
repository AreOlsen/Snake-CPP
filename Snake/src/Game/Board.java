import Game.Apple;

package Game;

public class Board {
    public int width;
    public int height;

    public int remainingApples;
    Block[][] boardBlocks;
    public Board(int x, int y, int appleAmount){
        this.width=x;
        this.height=y;
        boardBlocks = new Block[x][y];


        for(int i = 0; i < appleAmount; i++){
            int randomX = (int)Math.floor(Math.random()*x);
            int randomY = (int)Math.floor(Math.random()*y);
            
            while (alreadyApple) {
                randomX = (int)Math.floor(Math.random()*x);
                randomY = (int)Math.floor(Math.random()*y);
            }
            boardBlocks[randomX][randomY] = new Apple(x,y);
        }
    }
}
