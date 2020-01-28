#ifndef UI_CPP
#define UI_CPP

// UI functions
// functions to paint a window, clear content, ...
using namespace rlutil;
void paint(const window &w)
{
    string top(w.size.horizontal, ' ');
    string left(w.border.horizontal, ' ');
    setColor(w.frame.text);
    setBackgroundColor(w.frame.back);
    for (int row = 0; row < w.size.vertical; ++row)
    {
        locate(w.corner.horizontal, row + w.corner.vertical);
        if (row < w.border.vertical || row + w.border.vertical >= w.size.vertical)
        {
            cout << top;
        }
        else
        {
            cout << left;
            locate(w.corner.horizontal + w.size.horizontal - w.border.horizontal, row + w.corner.vertical);
            cout << left;
        }
    }
    locate(w.corner.horizontal + (w.size.horizontal - string(w.title).length()) / 2, w.corner.vertical);
    cout << w.title;
    clear(w);
}
void clear(const window &w)
{
    string line(w.size.horizontal - 2 * w.border.horizontal, ' ');
    setColor(w.content.text);
    setBackgroundColor(w.content.back);
    for (int row = w.border.vertical; row < w.size.vertical - w.border.vertical; ++row)
    {
        locate(w.corner.horizontal + w.border.horizontal, row + w.corner.vertical);
        cout << line;
    }
    cout.flush();
}
void printText(const window &w, const char msg[], int row /* = 0 */, bool cls /* = true*/)
{
    if (cls)
    {
        clear(w);
    }
    locate(w.corner.horizontal + w.border.horizontal, w.corner.vertical + w.border.vertical + row);
    cout << msg;
    cout.flush();
}

void showWelcomeScreen()
{
    cls();
    paint(mainWindow);
    paint(statusBar);
    printText(mainWindow, "This is the main window", 15);
}
void hideWelcomeScreen()
{
    msleep(500);
    printText(statusBar, "Let's start!!!");
    msleep(500);
    paint(menuBar);
    paint(gameInfo);
    paint(userInput);
}
void updateView(const game &g)
{
    paint(timeElapsed);
    double time = getElapsed(g);
    int minutes = time / 60;
    int seconds = time - minutes * 60;
    int millis = (time - minutes * 60 - seconds) * 1000;
    printText(timeElapsed, "");
    cout << (minutes / 10) << (minutes % 10) << ":";
    cout << (seconds / 10) << (seconds % 10) << ",";
    cout << (millis / 100) << ((millis / 10) % 10) << (millis % 10);
    cout.flush();
    if (UPDATE_VIEW)
    {
        cout << endl; // just to separate
        if (g.rightGuess)
        {
            cout << "You guessed right at " << g.numGuesses << "° guess." << endl;
        }
        else if (g.hidden)
        {
            if (g.numGuesses == 0)
            {
                cout << "You haven't guessed yet: you have " << MAX_GUESSES - g.numGuesses << " guesses available." << endl;
            }
            else
            {
                if (g.numGuesses >= MAX_GUESSES)
                {
                    cout << "You haven't guessed right in the " << MAX_GUESSES << " guesses available." << endl;
                }
                else
                {
                    cout << "You haven't guessed right yet: you still have " << MAX_GUESSES - g.numGuesses << " guesses available." << endl;
                }
                cout << "Here are your previous guesses: ";
                for (int i = 0; i < g.numGuesses; ++i)
                {
                    cout << g.guesses[i] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "You haven't guessed right; as you probably already know, the secret to be guessed was " << g.secret << "." << endl;
        }
    }
}

void showAvailableCommands(const game &g)
{
    for (int a = NONE + 1, row = 0; a < NUM_ACTIONS; a++, row++)
    {
        printText(menuBar, isEnabled((action_code)a, g) ? " " : "[", row, row == 0);
        for (int i = 0; i < NUM_TRANSLATIONS; ++i)
        {
            if (input_action[i].meaning.code == a)
            {
                cout << " " << input_action[i].what;
            }
        }
        cout << ": " << UIcommands[a].description << (isEnabled((action_code)a, g) ? "" : " ]");
    }
    cout.flush();
}

action translateInputToAction(input what)
{
    for (int i = 0; i < NUM_TRANSLATIONS; ++i)
    {
        if (what == input_action[i].what)
        {
            return input_action[i].meaning;
        }
    }
    return {NONE, PARAM_NONE};
}

action getUserCommand(const game &g)
{
    showAvailableCommands(g);
    printText(userInput, inputPrompt);
    input what = nb_getch(); // non blocking
    // translation
    return translateInputToAction(what);
}
void showGuesses(const game &g)
{
    printText(gameInfo, "Remaining guesses: ");
    cout << MAX_GUESSES - g.numGuesses;
    printText(gameInfo, "Previous guesses: ", 1, false);
    for (int i = 0; i < g.numGuesses; ++i)
    {
        cout << g.guesses[i] << " ";
    }
}
void guessChecked(const game &g)
{
    showGuesses(g);
    if (g.rightGuess)
    {
        printText(gameInfo, "You guessed right at ", 2, false);
        cout << g.numGuesses << "° guess (" << g.guesses[g.numGuesses - 1] << ").";
    }
    else
    {
        printText(gameInfo, "Your ", 2, false);
        cout << g.numGuesses << "° guess (" << g.guesses[g.numGuesses - 1] << ") is wrong.";
    }
}
void gameStarted(const game &g)
{
    showGuesses(g);
    cout << "New game!!! You haven't guessed yet.";
}
void gameEnded(const game &g)
{
    statusMsg("Game over!!!");
}
void secretShown(const game &g)
{
    printText(gameInfo, "The secret to be guessed was ", 2, false);
    cout << g.secret << "." << endl;
}
void statusMsg(const char msg[])
{
    printText(statusBar, msg);
}

#endif