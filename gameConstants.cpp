#include <iostream>
#include <ncurses.h>
#include <cstdlib>
using namespace std;

class snakeGame
{
private:
    bool game_running;
    const int width = 20;
    const int height = 20;
    int x, y, fruitX, fruitY, score;

    int tailX[100], tailY[100];
    int nTail = 0;

    enum eDirection
    {
        // enum is a user-defined data type that consists of a set of named constant values.
        // enums are used to define a set of possible values for a variable, making the code more readable and expressive
        STOP = 0,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    eDirection dir;

public:
    void setup()
    {
        initscr();
        clear();
        noecho();
        cbreak();
        curs_set(0);

        game_running = false;
        dir = STOP;
        x = width / 2; // head starts at the middle of the board
        y = height / 2;

        fruitX = (rand() % width + 1); // fruit must be located randomly on the map
        fruitY = (rand() % height + 1);

        score = 0;
    }

    void draw()
    {
        clear(); // from ncurses
        for (int i = 0; i < width + 2; i++)
            mvprintw(0, i, "#"); // must enter y value first followed by x value followed by desired item to be printed
        // cout << endl;

        for (int i = 0; i < height + 2; i++)
        {
            for (int j = 0; j < width + 2; j++)
            {
                // boundaries:
                if (i == 0 || i == 21)
                    mvprintw(i, j, "#");
                else if (j == 0 || j == 21)
                    mvprintw(i, j, "#");
                else if (i == y && j == x)
                {
                    mvprintw(i, j, "O");
                }
                else if (i == fruitY && j == fruitX)
                {
                    mvprintw(i, j, "@");
                }
                else
                {
                    for (int k = 0; k < nTail; k++)
                    {
                        if (tailX[k] == j && tailY[k] == i)
                        {
                            mvprintw(i, j, "()");
                        }
                    }
                }
            }
            cout << endl;
        }
        mvprintw(23, 0, "Score %d", score);

        cout << endl;
        refresh();
    }

    void input()
    {
        keypad(stdscr, TRUE);     // prepares computer for any input
        halfdelay(1);             // determines speed of game (don't have to keep pressing key to move)
        int move_input = getch(); // gets char
        if (nTail >= 0)
        {
            // player should not be able to move backwards
            // need to keep track of moves made or condition check where the tail is in relation to the head
        }

        switch (move_input)
        {
        case 'w':
            dir = UP;
            break;
        case KEY_UP:
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case KEY_LEFT:
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        case 'x':
            game_running = true;
            break;
        }
    }

    void Logic()
    {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;

        for (int i = 1; i < nTail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];

            tailX[i] = prevX;
            tailY[i] = prevY;

            prevX = prev2X;
            prevY = prev2Y;
        }

        switch (dir)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }

        // snake hits border:
        if (x > width || x < 1 || y < 1 || y > height)
        {
            game_running = true;
        }

        // snake eats fruit:
        if (x == fruitX && y == fruitY)
        {
            score++;
            fruitX = (rand() % width + 1); // fruit position changes
            fruitY = (rand() % height + 1);
            nTail++;
        }

        // snake hits  tail
        for (int i = 0; i < nTail; i++)
        {
            // runs through all the tail segments and checks if the head coordinates equal any segment
            if (tailX[i] == x && tailY[i] == y)
            {
                game_running = true;
            }
        }
    }

    bool getGameStatus()
    {
        return game_running;
    }

    void setGameStatus(bool status)
    {
        game_running = status;
    }
};
