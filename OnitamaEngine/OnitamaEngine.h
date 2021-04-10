#ifndef _ONITAMAENGINE_H_
#define _ONITAMAENGINE_H_

#include <vector>
#include "Card.h"
#include <time.h>
#include <cstdlib>

class OnitamaEngine
{
private:
    static const char _blueDisciple = 'b';
    static const char _blueMaster = 'B';
    static const char _redDisciple = 'r';
    static const char _redMaster = 'R';
    static const int boardSize = 5;

    // _currentBoardState inited as:
    // 5 bbBbb
    // 4 .....
    // 3 .....
    // 2 .....
    // 1 rrRrr
    //   ABCDE
    std::vector<std::vector<char>> _currentBoardState;
    void _initBoard();

    std::vector<unsigned int> _currentCardsRed;
    std::vector<unsigned int> _currentCardsBlue;
    unsigned int _currentCardCenter;

    std::vector<Card> _allCards;
    std::vector<Card> _getRandomCards(int inAmount);
    bool _validateMove(bool inIsPlayerRed, std::string inCardName, Point2D inFigureStartPosition, Point2D inFigureEndPosition);
    Card _getCard(std::string inCardName);
    bool _checkIfCardExists(std::string inCardName);
    std::vector<Point2D> _calculateJumpEndOptions(Point2D inFigureStartPosition, std::vector<Point2D> jumpOptions);
    bool _isOnBoard(Point2D inPoint);
    bool _hasOwnPiece(bool inIsPlayerRed, Point2D inPoint);
    bool _validateEndPositionOptions(bool inIsRedPlayer, std::vector<Point2D> inEndPositionOptions, Point2D inFigureEndPosition);
public:
    void InitAllCards();
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
