#ifndef GAME_CPP
#define GAME_CPP

// game functions

game newGame(const configuration &c)
{
    game g;
    g.secret = '0' + rand() % ('9' - '0' + 1);
    if (DEBUG)
    {
        cout << "new game " << g.secret << endl;
    }
    gameStarted(g); // notify UI
    return g;
}

guess getSecret(game &g)
{
    g.hidden = false;
    secretShown(g); // notify UI
    gameEnded(g);   // notify UI
    return g.secret;
}

bool checkGuess(game &g, guess tentativo)
{
    bool result = false;
    if (isEnabled(TRY, g))
    {
        g.guesses[g.numGuesses] = tentativo;
        g.numGuesses++;
        result = g.rightGuess = tentativo == g.secret;
        guessChecked(g); // notify UI
        if (g.rightGuess || g.numGuesses == MAX_GUESSES)
        {
            gameEnded(g); // notify UI
        }
    }
    return result;
}

#endif