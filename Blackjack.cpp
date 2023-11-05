#include <iostream>
#include <cstdlib>

using namespace std;

/* All Prototypes */
void shuffle(int cards[]);
void outputCard(int id);
int cardValue(int id);
void outputHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);
void playGame(int cards[]);

const int NUM_CARDS = 52;
const int BLACKJACK = 21;
const int DEALER_MIN = 17;

const char suit[4] = { 'H', 'S', 'D', 'C' };
const char *type[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A" };
const int value[13] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11 };


// Function to display a card's type and suit
void outputCard(int id) {
    cout << type[id % 13] << "-" << suit[id / 13] << " ";
}


// Function to return the point value of a card
int cardValue(int id) {
    return value[id % 13];
}


// Function to shuffle the deck using the Fisher-Yates algorithm
void shuffle(int cards[]) {
    
    for (int i = 0; i < NUM_CARDS; i++) {
        cards[i] = i;
    }
    
    for (int i = NUM_CARDS - 1; i >= 1; i--) {
        int j = rand() % (i + 1);
        swap(cards[i], cards[j]);
    }
}


// Function to output all cards in a hand
void outputHand(int hand[], int numCards) {
    for (int i = 0; i < numCards; i++) {
        outputCard(hand[i]);
    }
    cout << endl;
}


// Function to calculate the best score for a hand
// It considers an Ace as 11 points unless it causes the player to bust
int getBestScore(int hand[], int numCards) {
    
    int totalScore = 0;
    int numAces = 0;
    for (int i = 0; i < numCards; i++) {
        totalScore += cardValue(hand[i]);
        if (cardValue(hand[i]) == 11) {
            numAces++;
        }
    }
    while ((totalScore > BLACKJACK) && (numAces > 0)) {
        totalScore -= 10;
        numAces--;
    }
    return totalScore;
}


// This function has the game's Main logic
void playGame(int cards[]) {
    
    int cardIdx = 0;
    int playerHand[9];
    int dealerHand[9];
    int playerNumCards = 2;
    int numDealerCards = 2;
    
    // deal cards to player and dealer
    for (int i = 0; i < 2; i++) {
        playerHand[i] = cards[cardIdx++];
        dealerHand[i] = cards[cardIdx++];
    }
    
    // Display initial cards
    cout << "Dealer: ";
    outputCard(dealerHand[1]);
    
    cout << "Player: ";
    outputHand(playerHand, playerNumCards);

    // Player's turn to hit or stay
    char action;
    int playerScore = getBestScore(playerHand, playerNumCards);
    while (playerScore < BLACKJACK) {
        cout << "Type 'h' to hit and 's' to stay:" << endl;
        cin >> action;
        if (action == 'h') {
            playerHand[playerNumCards++] = cards[cardIdx++];
            outputHand(playerHand, playerNumCards);
            playerScore = getBestScore(playerHand, playerNumCards);
        } else {
            break;
        }
    }

    // Dealer's turn
    int dealerScore = getBestScore(dealerHand, numDealerCards);
    while (dealerScore < DEALER_MIN) {
        dealerHand[numDealerCards++] = cards[cardIdx++];
        dealerScore = getBestScore(dealerHand, numDealerCards);
    }

    // Determine and display the winner
    if (playerScore > BLACKJACK) {
        cout << "Player busts" << endl;
    } else if (dealerScore > BLACKJACK || playerScore > dealerScore) {
        cout << "Win " << playerScore << " " << dealerScore << endl;
    } else if (dealerScore == playerScore) {
        cout << "Tie " << playerScore << " " << dealerScore << endl;
    } else {
        cout << "Lose " << playerScore << " " << dealerScore << endl;
    }
}

int main(int argc, char *argv[]) {
    
    // Ensures the user has provided a seed value
    if (argc < 2) {
        cout << "Please provide a seed value" << endl;
        return 1;
    }
    
    int seed = atoi(argv[1]);
    srand(seed);

    int cards[NUM_CARDS];
    char playAgain;
    
    do {
        shuffle(cards);
        playGame(cards);
        cout << "another round? [y/n]" << endl;
        cin >> playAgain;
    } while (playAgain == 'y');
    return 0;
}
