#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>
#include <cstdint>
#include <thread>

#define print(x) std::cout << x
#define println(x) std::cout << x << std::endl

// ================= CONSOLE UTILS =================
void setcolor(uint8_t c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void resetcolor()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// FIX 1: ripristinata wait(ms) con sleep corretto
void wait(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void clearScreen()
{
    system("cls");
}

// ================= GAME UTILS =================
std::string ToString(int c)
{
    switch (c)
    {
    case 1: return "Rock";
    case 2: return "Paper";
    case 3: return "Scissors";
    default: return "Error";
    }
}

int result(int p, int c)
{
    if (p == c) return 0;

    if ((p == 1 && c == 3) ||
        (p == 2 && c == 1) ||
        (p == 3 && c == 2))
        return 1;

    return -1;
}

// ================= INPUT =================
int getKeyPress()
{
    while (true)
    {
        if (GetAsyncKeyState(VK_UP) & 1)     return -1;
        if (GetAsyncKeyState(VK_DOWN) & 1)   return 1;
        if (GetAsyncKeyState(VK_RETURN) & 1) return 0;
        Sleep(10);
    }
}

// ================= PAUSE =================
void pressToContinue()
{
    setcolor(14);
    println("\nWAIT 5 SECONDS TO CONTINUE");
    resetcolor();

    // Svuota il '\n' lasciato da std::cin >> p
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Sleep(5000);
}

// FIX 2: helper che aspetta INVIO tramite polling (senza toccare cin)
void waitForEnter()
{
    Sleep(150);
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN) & 1)
            break;
        Sleep(10);
    }
}

// ================= TITLE =================
void titleScreen()
{
    clearScreen();

    setcolor(11);
    println("======================================");
    println(" ROCK PAPER SCISSORS ARCADE EDITION  ");
    println("======================================");
    resetcolor();

    println("\nBooting...");
    wait(500);
    println("Loading...");
    wait(500);
    println("Ready!");

    println("\nPress ENTER...");
    waitForEnter();
}

// ================= MENU =================
int menuSelector()
{
    int selected = 0;
    const char* items[] = { "START GAME", "RULES", "EXIT" };

    while (true)
    {
        clearScreen();

        setcolor(11);
        println("======= MAIN MENU =======");
        resetcolor();

        for (int i = 0; i < 3; i++)
        {
            if (i == selected)
            {
                setcolor(10);
                print(" > ");
                println(items[i]);
                resetcolor();
            }
            else
            {
                print("   ");
                println(items[i]);
            }
        }

        setcolor(11);
        println("=========================");
        resetcolor();

        int input = getKeyPress();

        if (input == -1)
        {
            selected--;
            if (selected < 0) selected = 2;
        }
        else if (input == 1)
        {
            selected++;
            if (selected > 2) selected = 0;
        }
        else if (input == 0)
        {
            return selected;
        }
    }
}

// ================= CPU =================
int cpuMove()
{
    return rand() % 3 + 1;
}

// ================= GAME OVER =================
void gameOverScreen(int p, int c)
{
    std::string msg = (p > c) ? "YOU WIN!" : (p < c ? "YOU LOSE!" : "DRAW!");

    for (int i = 0; i < 3; i++)
    {
        clearScreen();

        setcolor(11);
        println("======================");
        println("      GAME OVER       ");
        println("======================");
        resetcolor();

        if (i % 2 == 0) setcolor(10);
        else setcolor(12);

        println(msg);
        resetcolor();

        println("\nFinal Score  -  YOU: " << p << "  CPU: " << c);

        wait(300);
    }

    println("\nPress ENTER to return to menu...");
    waitForEnter();
}

// ================= GAME =================
void playGame()
{
    int rounds;
    int scoreP = 0, scoreC = 0;

    clearScreen();
    print("How many rounds? ");
    std::cin >> rounds;

    if (rounds < 1)
    {
        println("Invalid number of rounds.");
        wait(1000);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    for (int i = 1; i <= rounds; i++)
    {
        clearScreen();

        setcolor(11);
        println("ROUND " << i << " / " << rounds);
        resetcolor();

        println("");
        println("1  Rock");
        println("2  Paper");
        println("3  Scissors");
        println("");

        int p;
        print("Choose: ");
        std::cin >> p;

        if (p < 1 || p > 3)
        {
            setcolor(12);
            println("Invalid input. Try again.");
            resetcolor();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            wait(800);
            i--;
            continue;
        }

        int c = cpuMove();

        println("");

        setcolor(14);
        println("You: " << ToString(p));
        println("CPU: " << ToString(c));
        resetcolor();

        int r = result(p, c);

        println("");
        if (r == 1)
        {
            scoreP++;
            setcolor(10);
            println(">> You win this round!");
        }
        else if (r == -1)
        {
            scoreC++;
            setcolor(12);
            println(">> CPU wins this round!");
        }
        else
        {
            setcolor(14);
            println(">> Draw!");
        }
        resetcolor();

        println("");
        setcolor(11);
        println("Score  -  YOU: " << scoreP << "  CPU: " << scoreC);
        resetcolor();

        pressToContinue();
    }

    gameOverScreen(scoreP, scoreC);
}

// ================= RULES =================
void showRules()
{
    clearScreen();

    setcolor(11);
    println("============ RULES ============");
    resetcolor();

    println("");
    println("  Rock     beats  Scissors");
    println("  Scissors beats  Paper");
    println("  Paper    beats  Rock");
    println("");
    println("Play a set number of rounds.");
    println("Most round wins takes the match!");
    println("");

    setcolor(11);
    println("===============================");
    resetcolor();

    println("\nPress ENTER to go back...");
    waitForEnter();
}

// ================= MAIN =================
int main()
{
    srand(static_cast<unsigned int>(time(0)));

    titleScreen();

    while (true)
    {
        int choice = menuSelector();

        if (choice == 0)
        {
            playGame();
        }
        else if (choice == 1)
        {
            showRules();
        }
        else
        {
            clearScreen();
            setcolor(11);
            println("Thanks for playing. Goodbye!");
            resetcolor();
            wait(800);
            break;
        }
    }

    return 0;
}