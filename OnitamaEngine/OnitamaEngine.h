#ifndef _ONITAMAENGINE_H_
#define _ONITAMAENGINE_H_

#include <vector>
#include "Card.h"
#include <time.h>
#include <cstdlib>
#include "MoveInformation.h"

class OnitamaEngine
{
private:
    static const char _blueDisciple = 'b';
    static const char _blueMaster = 'B';
    static const char _redDisciple = 'r';
    static const char _redMaster = 'R';
    static const int _boardSize = 5;

    // _currentBoardState represents the board as a human would understand it
    // 5 bbBbb
    // 4 .....
    // 3 .....
    // 2 .....
    // 1 rrRrr
    //   ABCDE
    std::vector<std::vector<char>> _currentBoardState;

    // _currentCardsRed is a list of index of
    // the cards that the red player has available
    std::vector<unsigned int> _currentCardsRed;

    // _currentCardsRed is a list of index of
    // the cards that the blue player has available
    std::vector<unsigned int> _currentCardsBlue;

    // _currentCardCenter is the card that lays in the center
    unsigned int _currentCardCenter;

    // _allCards contains all available cards.
    std::vector<Card> _allCards;

    // _engineState will contain a message in case of an event
    std::string _engineState;

    bool _isRedsTurn;

    // _initBoard() will initialize _currentBoardState
    void _initBoard();

    // _initAllCards() will initialize _allCards
    void _initAllCards();

    // _getRandomCards() will return a random subset of 
    // size inAmount from _allCards
    std::vector<Card> _getRandomCards(unsigned int inAmount);

    // _checkIfCardExists will return 
    // true: if _allCards has a card called inCardName
    // false: if _allCards does not have a card called inCardName
    bool _checkIfCardExists(std::string inCardName);

    // _checkIfPlayerOwnsCard will return 
    // true: if inCardName is in _currentCardsRed
    //       (or _currentCardsBlue, depending on inIsPlayerRed)
    bool _checkIfPlayerOwnsCard(
        bool inIsPlayerRed,
        std::string inCardName);

    Card _getCard(std::string inCardName);

    // _calculateJumpEndOptions will take each inJumpOptions entry
    // add inFigureStartPosition onto them and give them back.
    // These will basically reflect all points a figure can jump
    // to with a card.
    std::vector<Point2D> _calculateJumpEndOptions(
        Point2D inFigureStartPosition, 
        std::vector<Point2D> inJumpOptions);

    // _isOnBoard will take inPoint and return
    // true: if it is within the measurements of the board
    bool _isOnBoard(Point2D inPoint);

    // _hasOwnPieceAtLocation will check _currentBoardState
    // for a figure of type red (or blue, depending on inIsPlayerRed)
    bool _hasOwnPieceAtLocation(
        bool inIsPlayerRed, 
        Point2D inPoint);

    // _endpointIsInEndPositionOptions will consider all calculated
    // endpoint options and if one is equal to inFigureEndPosition
    // it will return true
    bool _endpointIsInEndPositionOptions(
        std::vector<Point2D> inEndPositionOptions, 
        Point2D inFigureEndPosition);
    
    // _cardHasEndpositionAsOption will get the card, take all jumpoptions
    // calculate the endpoints and 
    bool _cardHasEndpositionAsOption(
        bool inIsPlayerRed,
        MoveInformation inMove);

public:
    // _validateMove will return true if the given parameter
    // for a move is legal, else false
    // So what happens is:
    // 1. Abort if the start position of the move isn't even on the board
    // 2. Abort if the player doesn't have a figure at the start position
    // 3. Abort if the card doesn't even exist
    // 4. Abort if the player doesn't own such a card
    // 5. Abort if the final position isn't even on the board
    // 6. Abort if the final position is already occupied by an own figure
    // 7. Abort if the card would allow to jump to the given end position
    // All checks passed, seems ok, return true...
    bool ValidateMove(
        bool inIsPlayerRed,
        MoveInformation inMove);

    void ApplyMove(MoveInformation inMove);

    OnitamaEngine();
};

    //void _rejectMove();

    //// Returns 4 x 2D Board [5x5] bool; disciples red, master red, disciples blue, master blue
    //// TODO(Simon) example comment
    //? ? ? GetBordStateDiscrete()

    //// Returns 4 x 2D Board [5x5] bool; all red figures, all blue figures, all disciples, all masters
    //// TODO(Simon): comment showing an example output
    //? ? ? GetBordStateCathegory()

    //// Returns 3 x 12 bool; red cards, blue cards, center card
    //// TODO(Simon): comment showing an example output
    //? ? ? GetCardState()

    //// Returns 2 x 2D jump options [5x5] bool; Card 1 jumping options; Card 2 jumping options; 
    //// TODO(Simon): comment showing an example output
    //? ? ? GetCardsRedCards(bool inMirrored)

    //// Returns 2 x 2D jump options [5x5] bool; Card 1 jumping options; Card 2 jumping options; 
    //// TODO(Simon): comment showing an example output
    //? ? ? GetCardsBlueCards(bool inMirrored)

    ////
    //void ReceiveMove(? ? ? )

#endif
