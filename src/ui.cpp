#ifndef UI_CPP
#define UI_CPP

// UI functions
void showWelcomeScreen()
{
    cout << "Welcome to the game!!!" << endl;
}
void hideWelcomeScreen()
{
    cout << "Let's start!!!" << endl;
}
void updateView(const game &g)
{
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
    for (int a = NONE; a < NUM_ACTIONS; a++)
    {
        if (isEnabled((action_code)a, g))
        {
            for (int i = 0; i < NUM_TRANSLATIONS; ++i)
            {
                if (input_action[i].meaning.code == a)
                {
                    cout << " " << input_action[i].what;
                }
            }
            cout << ": " << UIcommands[a].description << endl;
        }
    }
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
    cout << endl; // just to separate
    showAvailableCommands(g);
    cout << inputPrompt;
    input what;
    cin >> what;
    // translation
    return translateInputToAction(what);
}

void guessChecked(const game &g)
{
    if (g.rightGuess)
    {
        cout << "You guessed right at " << g.numGuesses << "° guess (" << g.guesses[g.numGuesses - 1] << ")." << endl;
    }
    else
    {
        cout << "Your " << g.numGuesses << "° guess (" << g.guesses[g.numGuesses - 1] << ") is wrong." << endl;
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
void gameStarted(const game &g)
{
    cout << "New game!!! You haven't guessed yet: you have " << MAX_GUESSES - g.numGuesses << " guesses available." << endl;
}
void gameEnded(const game &g)
{
    cout
        << "Game over!!!" << endl;
}
void secretShown(const game &g)
{
    cout << "The secret to be guessed was " << g.secret << "." << endl;
}

#endif