/* 
    Mateusz Suszek
    324132
    LJE
*/

#include <iostream>
#include <queue>

int n,m, flags;
char board[2001][2001];
int flag[2001][2001];

struct Tile {
    int x,y;
};

struct Tile makeTile(int x, int y) {
    struct Tile tile;
    tile.x = x;
    tile.y = y;
    return tile;
}

int tileInside(Tile tile) {
    return (tile.x >= 0 && tile.x <= (n-1) && tile.y >= 0 && tile.y <= (m-1));
}

int tileVisited(Tile tile) {
    return (flag[tile.x][tile.y] != 0);
}

void tileMarkVisited(Tile tile, int flagNum) {
    flag[tile.x][tile.y] = flagNum;
}


void printBoard() {

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void printFlags() {

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%d ", flag[i][j]);
        }
        printf("\n");
    }
}

int main() {

    scanf("%d %d", &n, &m);

    for(int i = 0; i < n; i++) {
        getchar();
        scanf("%s", board[i]);
    }

    std::queue<Tile> queue;

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < m; j++) {

            while(!queue.empty()) {

                Tile currentTile = queue.front();
                queue.pop();
                int x = currentTile.x;
                int y = currentTile.y;
                int currentFlag = flag[x][y];
                char letter = board[x][y];

                Tile upTile = makeTile(x-1, y);
                Tile rightTile = makeTile(x, y+1);
                Tile downTile = makeTile(x+1, y);
                Tile leftTile = makeTile(x, y-1);

                if(tileInside(upTile) & !tileVisited(upTile) & (letter == 'C' || letter == 'D' || letter == 'F')) {
                    char upLetter = board[x-1][y];
                    if((upLetter == 'B' || upLetter == 'E' || upLetter == 'F') && upLetter != 'A') {
                        tileMarkVisited(upTile, currentFlag);
                        queue.push(upTile); 
                    }
                }

                if(tileInside(rightTile) & !tileVisited(rightTile) & (letter == 'D' || letter == 'E' || letter == 'F')) {
                    char rightLetter = board[x][y+1];
                    if((rightLetter == 'B' || rightLetter == 'C' || rightLetter == 'F') && rightLetter != 'A') {
                        tileMarkVisited(rightTile, currentFlag);
                        queue.push(rightTile); 
                    }
                    
                }

                if(tileInside(downTile) & !tileVisited(downTile) & (letter == 'B' || letter == 'E' || letter == 'F')) {
                    char downLetter = board[x+1][y];
                    if((downLetter == 'C' || downLetter == 'D' || downLetter == 'F') && downLetter != 'A') {
                        tileMarkVisited(downTile, currentFlag);
                        queue.push(downTile);
                    }
                    
                }

                if(tileInside(leftTile) & !tileVisited(leftTile) & (letter == 'B' || letter == 'C' || letter == 'F')) {
                    char leftLetter = board[x][y-1];
                    if((leftLetter == 'D' || leftLetter == 'E' || leftLetter == 'F') && leftLetter != 'A') {
                        tileMarkVisited(leftTile, currentFlag);
                        queue.push(leftTile);  
                    }
                    
                }
                
            }

            Tile currentTile = makeTile(i, j);

            if(!tileVisited(currentTile) && board[i][j] != 'A') {
                flags++;
                tileMarkVisited(currentTile, flags);
                queue.push(currentTile);
            }
        }
    }

    printf("%d\n", flags);

    return 0;
}