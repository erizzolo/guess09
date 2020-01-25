#ifndef GAME_H
#define GAME_H

// The game logic =============================================================
/**
 * Questa sezione definisce la logica del gioco, le operazioni che si possono
 * effettuare ed i dati necessari alla gestione.
 */
// data to be guessed
using guess = char;
// max number of guesses
#define MAX_GUESSES 5 // fair enough!
// game status (with default initialization)
struct game
{
    guess secret;               // il segreto da indovinare
    int numGuesses{0};          // il numero di tentativi effettuati
    guess guesses[MAX_GUESSES]; // i tentativi effettuati
    bool rightGuess{false};     // l'utente ha indovinato
    bool hidden{true};          // segreto nascosto/mostrato all'utente
};
// actions available on the game (known to the application and the user interface)
// game may be NEW (numGuesses == 0 && hidden), RUNNING, OVER (rightGuess || !hidden || numGuesses == MAX_GUESSES)
// get a new game, with default initialization according to configuration
game newGame(const configuration &);
// check if a guess (supposed valid) equals the secret, updating game
// if game is OVER, return false
bool checkGuess(game &, guess);
// get the secret, updating game
guess getSecret(game &);

#endif