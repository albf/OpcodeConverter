//Tic-tac-toe playing AI. Exhaustive tree-search. WTFPL
//Matthew Steel 2009, www.www.repsilat.com

#include <stdio.h>

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3]; // = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    wins[0][0] = 0; wins[0][1] = 1; wins[0][2] = 2;
    wins[1][0] = 3; wins[1][1] = 4; wins[1][2] = 5;
    wins[2][0] = 6; wins[2][1] = 7; wins[2][2] = 8;
    wins[3][0] = 0; wins[3][1] = 3; wins[3][2] = 6;
    wins[4][0] = 1; wins[4][1] = 4; wins[4][2] = 7;
    wins[5][0] = 2; wins[5][1] = 5; wins[5][2] = 8;
    wins[6][0] = 0; wins[6][1] = 4; wins[6][2] = 8;
    wins[7][0] = 2; wins[7][1] = 4; wins[7][2] = 6;
    
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
}

/*void playerMove(int board[9]) {
    int move = 0;
    do {
        printf("\nInput move ([0..8]): ");
        scanf("%d", &move);
        printf("\n");
    } while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = -1;
}*/

int main() {
    int board[9];
    //computer squares are 1, player squares are -1.
    
    board[0] = 1;board[3] = 0;board[6] = 0;
    board[1] = 0;board[4] = -1;board[7] = 1;
    board[2] = 0;board[5] = 0;board[8] = 0;
    computerMove(board);
    
    return board[4];
}