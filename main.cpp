//
//  main.cpp
//  2048
//
//  Created by abc on 03/07/23.
//

#include <iostream>
#include <algorithm>
 #include <bitset>
 #include <complex>
 #include <deque>
 #include <exception>
 #include <fstream>
 #include <functional>
 #include <iomanip>
 #include <ios>
 #include <iosfwd>
 #include <iostream>
 #include <istream>
 #include <iterator>
 #include <limits>
 #include <list>
 #include <locale>
 #include <map>
 #include <memory>
 #include <new>
 #include <numeric>
 #include <ostream>
 #include <queue>
 #include <set>
 #include <sstream>
 #include <stack>
 #include <stdexcept>
 #include <streambuf>
 #include <string>
 #include <typeinfo>
 #include <utility>
 #include <valarray>
 #include <vector>

 #if __cplusplus >= 201103L
 #include <array>
 #include <atomic>
 #include <chrono>
 #include <condition_variable>
 #include <forward_list>
 #include <future>
 #include <initializer_list>
 #include <mutex>
 #include <random>
 #include <ratio>
 #include <regex>
 #include <scoped_allocator>
 #include <system_error>
 #include <thread>
 #include <tuple>
 #include <typeindex>
 #include <type_traits>
 #include <unordered_map>
 #include <unordered_set>
 #endif



using namespace std;

const int M = (1 << 16) | 1;
const int A = 75;
const int C = 74;
int Xn = 0;

/*
    Return: returns a random (pseudo-random) number
*/
int generateRandomNumber()
{
    Xn = ((A * Xn) + C) % M;
    return Xn;
}



pair<int, pair<int, int>> getRandomEmptyCellAndValue(vector<pair<int, int>> &emptyCells)
{
    int maxsize = (int)emptyCells.size();
    // from all the empty cell choose a cell with index pos .
    int pos = (generateRandomNumber() % (maxsize)) ;

    sort(emptyCells.begin(), emptyCells.end());

  int minval = 1, maxval = 10;
    int value = (generateRandomNumber() % (maxval - minval + 1)) + minval;
// value is between minval and maxval .
    if (value <= 8)
        return make_pair(2, emptyCells[pos]); // empty cell at index pos assigned 2

    return make_pair(4, emptyCells[pos]); // empty cell at index pos assigned 4
}



int board[4][4];
int numEmptyCells;

/*
    Print the current configuration of the board
*/
void printBoard()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                cout << "-";
            else
                cout << board[i][j];
            cout << "\t";
        }
        cout << "\n";
    }
}



void gravity(vector<int> &arr)
{
    int firstEmpty = 0;
    for (int i = 0; i < 4; i++)
    {
        if (arr[i] != 0)
        {
            swap(arr[i], arr[firstEmpty]);
            firstEmpty++;
        }
    }
}


void merge(vector<int> &arr)
{
    for (int i = 1; i < 4; i++)
    {
        if (arr[i] == arr[i - 1] && arr[i] != 0)
        {
            arr[i - 1] = 2 * arr[i - 1];
            arr[i] = 0;
            numEmptyCells++;
        }
    }
}


bool pushToLeft(vector<int> &arr)
{
    vector<int> copyArr(arr);
    gravity(arr);
    merge(arr);
    gravity(arr);
    for (int i = 0; i < 4; i++)
    {
        if (copyArr[i] != arr[i])
            return true;
    }
    return false;
}


bool move(int direction){
    
    bool change = false;
    vector<int> curr;

    // Left
    if (direction == 1){
        for (int i = 0; i < 4; i++)
        {
            // copy the values in a particular direction
            for (int j = 0; j < 4; j++)
                curr.push_back(board[i][j]);

            // push to left and check if anything has changed
            change |= pushToLeft(curr);

            // copy the changed values back to original
            for (int j = 3; j >= 0; j--)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }

        // Down
    else if (direction == 2)
    {
        for (int j = 0; j < 4; j++)
        {

            // copy the values in a particular direction
            for (int i = 3; i >= 0; i--)
                curr.push_back(board[i][j]);

            // push to left and check if anything has changed
            change |= pushToLeft(curr);

            // copy the changed values back to original
            for (int i = 0; i < 4; i++)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }

        // Right
    else if (direction == 3)
    {
        for (int i = 0; i < 4; i++)
        {

            // copy the values in a particular direction
            for (int j = 3; j >= 0; j--)
                curr.push_back(board[i][j]);

            // push to left and check if anything has changed
            change |= pushToLeft(curr);

            // copy the changed values back to original
            for (int j = 0; j < 4; j++)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }

        // Up
    else
    {
        for (int j = 0; j < 4; j++)
        {

            // copy the values in a particular direction
            for (int i = 0; i < 4; i++)
                curr.push_back(board[i][j]);

            // push to left and check if anything has changed
            change |= pushToLeft(curr);

            // copy the changed values back to original
            for (int i = 3; i >= 0; i--)
            {
                board[i][j] = curr.back();
                curr.pop_back();
            }
        }
    }
    return change;
}


void populateRandomCell()
{
    vector<pair<int, int>> emptyCells;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 0)
                emptyCells.push_back({i, j});
        }
    }
    auto valAndCoord = getRandomEmptyCellAndValue(emptyCells);
    int val = valAndCoord.first;
    int x = valAndCoord.second.first, y = valAndCoord.second.second;
    board[x][y] = val;
    numEmptyCells--;
}


int checkGameStatus()
{
    bool moveAvailable = false;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == 2048)
                return 1;
            if (i < 3 && board[i][j] == board[i + 1][j])
                moveAvailable = true;
            if (j < 3 && board[i][j] == board[i][j + 1])
                moveAvailable = true;
        }
    }
    if (numEmptyCells == 0 && (!moveAvailable))
        return 0;
    return 2;
}

/*
    Used to Initialize the Board and other values required by the game
*/
void initialize()
{
    memset(board, 0, sizeof(board));
    numEmptyCells = 16;
    populateRandomCell();
    populateRandomCell();
}

/*
    Runner to run the game
*/
struct Runner
{

    string boardNotChangedMessage = "Invalid Move";
    string gameWonMessage = "Game Over, You Win";
    string gameLostMessage = "Game Over, You Lose";

    Runner(){};

    void play()
    {
        int n; cin >> n;
        initialize();
        printBoard();

        for(int i=0; i<n; i++)
        {
            int moveDir;
            cin >> moveDir;
            bool validMove = move(moveDir);

            if (!validMove)
            {
                cout << boardNotChangedMessage << "\n";
                continue;
            }

            populateRandomCell();
            printBoard();

            int gameStatus = checkGameStatus();

            if (gameStatus == 0)
            {
                cout << gameLostMessage << "\n";
                return;
            }
            else if (gameStatus == 1)
            {
                cout << gameWonMessage << "\n";
                return;
            }
        }
    }
};

int main()
{
    Runner game;
    game.play();

    return 0;
}
