#include <iostream>
#include <vector>
using namespace std;
struct Play
{
    char board[9] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
    const char mePlayer = 'o';
    const char aiPlayer = 'x';
} play;
class Move
{
public:
    int index;
    double score;
};
// победные комбинации с учётом индексов
bool winning(char board[], char player) {
    if (
        (board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player) ||
        (board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player) ||
        (board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player)
        ) {
        return true;
    }
    else {
        return false;
    }
}
vector<int> emptyIndices(char newBoard[])
{
    vector <int> s;
    for (int i{}; i < 9; i++)
        if ((newBoard[i] != 'o') && (newBoard[i] != 'x'))
            s.push_back(i);
    return s;
}
Move minimax(char newBoard[], char player, int depth=0) 
{
    vector<int> availSpots = emptyIndices(newBoard);
    if (winning(newBoard,play.mePlayer)) 
    {
        Move m = { -2,-10-depth};//выиграл человек
        return m;
    }
    else if (winning(newBoard, play.aiPlayer)) 
    {
        Move m = { -3,10-depth };//выиграл компьютер
        return m;
    }
    if (availSpots.size() == 0) 
    {
        Move m = { -1,0 };//ничья
        return m;
    }
    vector <Move> moves;
    for (int i = 0; i < availSpots.size(); i++)
    {
        Move move = {};
        move.index = availSpots[i];
        newBoard[availSpots[i]] = player;
        if (player == play.aiPlayer) {
            auto result = minimax(newBoard, play.mePlayer, depth=depth+1);
            move.score = result.score;
        }
        else {
            auto result = minimax(newBoard, play.aiPlayer, depth = depth + 1);
            move.score = result.score;
        }
        newBoard[availSpots[i]] = move.index;
        moves.push_back(move);
    }
    // if it is the computer's turn loop over the moves and choose the move with the highest score
    int bestMove;
    if (player == play.aiPlayer) 
    {
        auto bestScore = -10000;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score > bestScore) {
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    }
    else
    {
        auto bestScore = 10000;
        for (int i = 0; i < moves.size(); i++) {
            if (moves[i].score < bestScore) {
                bestScore = moves[i].score;
                bestMove = i;
            }
        }
    }
    return moves[bestMove];
}
bool checkField(int index)
{
    if ((play.board[index] == 'x')||(play.board[index] == 'o')) return false;
    return true;
}
void drawBoard()
{
    cout << endl;
    cout << "  " << play.board[0] << "  " << play.board[1] << "  " << play.board[2] << endl;
    cout << "  " << play.board[3] << "  " << play.board[4] << "  " << play.board[5] << endl;
    cout << "  " << play.board[6] << "  " << play.board[7] << "  " << play.board[8] << endl;

}

int main()
{
    while (true)
    {
        char board0[9] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
        for (int i{}; i < 9; i++)
            play.board[i] = board0[i];
        int order;
        cout << "Play first or second? \n" << "1-firsct \n" << "2-second \n";
        cin >> order;
        while ((order != 1) && (order != 2))
        {
            cout << " Enter 1 or 2!";
            cin >> order;
            continue;
        }
        drawBoard();

        vector<int> availSpots;
        bool flag = true;
        int meMotion;
        while (flag)
        {
            if (order == 1)
            {

                bool flag1 = true;
                while (flag1)
                {
                    cin >> meMotion;
                    if ((meMotion > 8) && (meMotion < 0))
                    {
                        cout << "Incorrect index field! Enter another";
                        continue;
                    }
                    if (!checkField(meMotion))
                    {
                        cout << "This field is occupied! Enter another";
                        continue;
                    }
                    flag1 = false;
                }
                play.board[meMotion] = play.mePlayer;
                availSpots = emptyIndices(play.board);
                if (winning(play.board, play.mePlayer))
                {
                    cout << "U won!" << endl;
                    break;
                }
                if (availSpots.size() == 0)
                {
                    cout << "Game of draw!" << endl;
                    break;
                }
                //ответ компьютера:
                char newBoard[9] = {};
                for (int i{}; i < 9; i++)
                    newBoard[i] = play.board[i];
                auto result = minimax(newBoard, play.aiPlayer);
                if (result.index == -1)
                {
                    cout << "Game of draw!" << endl;
                    break;
                }
                if (result.index == -2)
                {
                    cout << "U won!" << endl;
                    break;
                }
                if (result.index == -3)
                {
                    cout << "U lose:(" << endl;
                    break;
                }
                play.board[result.index] = play.aiPlayer;
                drawBoard();

                availSpots = emptyIndices(play.board);
                if (winning(play.board, play.aiPlayer))
                {
                    cout << "U lose:(" << endl;
                    break;
                }
                if (availSpots.size() == 0)
                {
                    cout << "Game of draw!" << endl;
                    break;
                }

            }
            else
            {
                char newBoard[9] = {};
                for (int i{}; i < 9; i++)
                    newBoard[i] = play.board[i];
                auto result = minimax(newBoard, play.aiPlayer);
                if (result.index == -1)
                {
                    cout << "Game of draw!" << endl;
                    break;
                }
                if (result.index == -2)
                {
                    cout << "U won!" << endl;
                    break;
                }
                if (result.index == -3)
                {
                    cout << "U lose:(" << endl;
                    break;
                }
                play.board[result.index] = play.aiPlayer;
                drawBoard();
                availSpots = emptyIndices(play.board);
                if (winning(play.board, play.aiPlayer))
                {
                    cout << "U lose:(" << endl;
                    break;
                }
                if (availSpots.size() == 0)
                {
                    cout << "Game of draw!" << endl;
                    break;
                }
                bool flag1 = true;
                while (flag1)
                {
                    cin >> meMotion;
                    if ((meMotion > 8) && (meMotion < 0))
                    {
                        cout << "Incorrect index field! Enter another";
                        continue;
                    }
                    if (!checkField(meMotion))
                    {
                        cout << "This field is occupied! Enter another";
                        continue;
                    }
                    flag1 = false;
                }
                play.board[meMotion] = play.mePlayer;

                availSpots = emptyIndices(play.board);
                if (winning(play.board, play.mePlayer))
                {
                    cout << "U won!" << endl;
                    break;
                }
                if (availSpots.size() == 0)
                {
                    cout << "Game of draw!" << endl;
                    break;
                }
            }

        }
        cout << "Shall we play again? \n" << "1-Yes \n" << "2-No \n";
        cin >> order;
        if (order == 2)
        {
            break;
        }

    }

    return 0;
}


