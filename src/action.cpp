#ifndef ACTION_CPP
#define ACTION_CPP

// action functions

bool isEnabled(action_code code, const game &g)
{
    switch (code)
    {
    case EXIT:
        return true;
    case NEW:
        return g.numGuesses != 0 || !g.hidden || g.endTime != 0;
    case TRY:
        return !g.rightGuess && g.hidden && g.numGuesses < MAX_GUESSES && g.endTime == 0;
    case SHOW:
        return g.hidden && !g.rightGuess;
    case NONE:
        return true;
    default:
        return false;
    }
}

void processUserCommand(action c, game &g, configuration &config)
{
    if (DEBUG)
    {
        cout << "processing action " << c.code << " with param " << c.param << ": enabled " << isEnabled(c.code, g) << endl;
    }
    if (isEnabled(c.code, g))
    {
        switch (c.code)
        {
        case EXIT:
            break;
        case NEW:
            g = newGame(config);
            break;
        case TRY:
            checkGuess(g, c.param); // ignore result
            break;
        case SHOW:
            getSecret(g); // ignore result
            break;
        case NONE:
            break;
            default:
            cout << "Should never be here !!!! " << endl;
        }
    }
    else
    {
        statusMsg("command not available");
    }
}

#endif