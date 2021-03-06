#include <iostream>
#include <vector>
#include <string>


class square {
private:
    int x = 0;
    int y = 0;
    char pawn = ' ';

public:

    square()
    {
    }
    square(int inputX, int inputY)
    {
        x = inputX;
        y = inputY;

        if ((x + y) % 2 == 0)
        {
            if (y < 3)
            {
                pawn = 'W';
            }
            else if (y > 4)
            {
                pawn = 'B';
            }
        }
        else
        {
            pawn = ' ';
        }
    }

    void printDebug()
    {
        std::cout << " " << pawn << " ";
    }

    char getPawn()
    {
        return pawn;
    }
    void destroyPawn()
    {
        pawn = ' ';
    }
};

void start();
void switchPlayer(char& player, bool& anotherTarget, bool& selectSet, bool& targetSet);
void refreshBoard(square field[8][8], char currentPlayer);
void anotherMove(int& selectX, int& selectY, int& targetX, int& targetY);

int main()
{
    start();
    system("pause>0");
}

void start()
{
    square field[8][8];

    char currentPlayer = 'W';

    bool anotherTarget = false;

    std::string select, target;
    int selectX, selectY, targetX, targetY;
    bool selectSet = false;
    bool targetSet = false;

    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            field[x][y] = square(x, y);
        }
    }

    do
    {
        refreshBoard(field, currentPlayer);

        //////////////select
        do
        {
            if (selectSet == false)
            {
                std::cout << "\nSelect pawn: ";
                getline(std::cin, select);
                select[0] = tolower(select[0]);

                if ((select[1] > '0' && select[1] <= '8') && (select[0] >= 'a' && select[0] <= 'h'))
                {
                    selectX = select[0] - 96 - 1;
                    selectY = select[1] - 48 - 1;

                    if (field[selectX][selectY].getPawn() == currentPlayer)
                    {
                        selectSet = true;
                        break;
                    }
                    else
                    {
                        std::cout << "No " << currentPlayer << " pawns in this area.\n";
                        field[selectX][selectY].printDebug();
                    }
                }
                else
                {
                    std::cout << "Invalid input.\n";
                }
            }
            else
            {
                break;
            }
        } while (true);

        //////////////target
        do
        {
            std::cout << "\nSelect target: ";
            getline(std::cin, target);
            if ((target[1] > '0' && target[1] <= '8') && (target[0] >= 'a' && target[0] <= 'h'))//validates input
            {
                std::cout << "Valid\n";
                targetX = target[0] - 96 - 1;
                targetY = target[1] - 48 - 1;

                if ((targetX + targetY) % 2 == 0 && field[targetX][targetY].getPawn() == ' ')////check if trying to move on correct field and if its empty
                {
                    if ((targetX - selectX == 1 || targetX - selectX == -1) && (targetY - selectY == 1 || targetY - selectY == -1))//check if trying to move once
                    {
                        std::swap(field[selectX][selectY], field[targetX][targetY]);
                        targetSet = true;
                        break;
                    }
                    else if ((targetX - selectX == 2 || targetX - selectX == -2) && (targetY - selectY == 2 || targetY - selectY == -2))//check if trying to move twice
                    {
                        if (field[(selectX + targetX) / 2][(selectY + targetY) / 2].getPawn() != ' ' && field[(selectX + targetX) / 2][(selectY + targetY) / 2].getPawn() != currentPlayer)//check if there is pawn to destroy
                        {
                            field[(selectX + targetX) / 2][(selectY + targetY) / 2].destroyPawn();
                            std::swap(field[selectX][selectY], field[targetX][targetY]);
                            targetSet = true;

                            if ((targetX + 2 < 8 && targetY + 2 < 8) && field[targetX + 1][targetY + 1].getPawn() != ' ' && field[targetX + 1][targetY + 1].getPawn() != currentPlayer)
                            {
                                if (field[targetX + 2][targetY + 2].getPawn() == ' ')
                                {
                                    anotherTarget = true;
                                    anotherMove(selectX, selectY, targetX, targetY);
                                    refreshBoard(field, currentPlayer);
                                    break;
                                }
                            }
                            if ((targetX - 2 >= 0 && targetY - 2 >= 0) && field[targetX - 1][targetY - 1].getPawn() != ' ' && field[targetX - 1][targetY - 1].getPawn() != currentPlayer)
                            {
                                if (field[targetX - 2][targetY - 2].getPawn() == ' ')
                                {
                                    anotherTarget = true;
                                    anotherMove(selectX, selectY, targetX, targetY);
                                    refreshBoard(field, currentPlayer);
                                    break;
                                }
                            }
                            if ((targetX - 2 >= 0 && targetY + 2 < 8) && field[targetX - 1][targetY + 1].getPawn() != ' ' && field[targetX - 1][targetY + 1].getPawn() != currentPlayer)
                            {
                                if (field[targetX - 2][targetY + 2].getPawn() == ' ')
                                {
                                    anotherTarget = true;
                                    anotherMove(selectX, selectY, targetX, targetY);
                                    refreshBoard(field, currentPlayer);
                                    break;
                                }
                            }
                            if ((targetX + 2 < 8 && targetY - 2 >= 0) && field[targetX + 1][targetY - 1].getPawn() != ' ' && field[targetX + 1][targetY - 1].getPawn() != currentPlayer)
                            {
                                if (field[targetX + 2][targetY - 2].getPawn() == ' ')
                                {
                                    anotherTarget = true;
                                    anotherMove(selectX, selectY, targetX, targetY);
                                    refreshBoard(field, currentPlayer);
                                    break;
                                }
                            }
                            break;
                        }
                        else
                        {
                            std::cout << "Invalid move.\n";
                        }
                    }
                    else
                    {
                        std::cout << "Invalid move.\n";
                    }
                }
                else
                {
                    std::cout << "Invalid move.\n";
                }
            }
            else
            {
                std::cout << "Invalid input.\n";
            }
        } while (true);
        switchPlayer(currentPlayer, anotherTarget, selectSet, targetSet);
    } while (true);
}

void switchPlayer(char& player, bool& anotherTarget, bool& selectSet, bool& targetSet)
{
    if (anotherTarget == true)
    {
        std::cout << "\nAnother attack? (y/n): ";
        char yn;
        std::cin >> yn;
        std::cin.clear();
        std::cin.ignore();
        switch (tolower(yn))
        {
            case 'y':
                anotherTarget = false;
                targetSet = false;
                return;
            default:
                anotherTarget = false;
                break;
        }
    }

    switch (player)
    {
        case 'W':
            player = 'B';
            break;
        case 'B':
            player = 'W';
            break;
        default:
            exit(2);
    }

    targetSet = false;
    selectSet = false;
}

void refreshBoard(square field[8][8], char currentPlayer)
{
    system("cls");

    for (int height = 8 * 4; height >= 0; height--)
    {
        if (height % 4 == 0)
        {
            for (int width = 0; width <= 8 * 4; width++)
            {
                if (width % 4 == 2 && height == 0)
                {
                    std::cout << " " << (char)((width / 4) + 97) << " ";
                }
                else if (width % 4 == 0)
                {
                    std::cout << "|";
                }
                else
                {
                    std::cout << "---";
                }
            }
        }
        else if (height % 4 == 2)
        {
            for (int width = 0; width <= 8 * 4; width++)
            {
                if (width == 0)
                {
                    std::cout << (height / 4) + 1;
                }
                else if (width % 4 == 2)
                {
                    field[width / 4][height / 4].printDebug();
                }
                else if (width % 4 == 0)
                {
                    std::cout << "|";
                }
                else
                {
                    std::cout << "   ";
                }
            }
        }
        else
        {
            for (int width = 0; width <= 8 * 4; width++)
            {
                if (width % 4 == 0)
                {
                    std::cout << "|";
                }
                else
                {
                    std::cout << "   ";
                }
            }
        }

        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "\nCurrent player: " << currentPlayer << "\n";
}

void anotherMove(int& selectX, int& selectY, int& targetX, int& targetY)
{
    selectX = targetX;
    selectY = targetY;
}
