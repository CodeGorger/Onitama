#ifndef _MOVEVALIDATOR_H_
#define _MOVEVALIDATOR_H_

#include <string>
#include <vector>
#include "../OnitamaEngine/OnitamaEngine.h"

class MoveValidator
{
public:
	MoveValidator(
		bool inRedStarts,
		MoveInformation inMove,
        OnitamaEngine inEngine);
	bool ValidateMove();
    std::string GetStatus();

private:
	bool _redStarts;
	MoveInformation _move;
    OnitamaEngine _engine;
    std::string _moveValidatorStatus;


    // _isOnBoard will take inPoint and return
    // true: if it is within the measurements of the board
    bool _isOnBoard(Point2D inPoint);

    // _hasOwnPieceAtLocation will check _currentBoardState
    // for a figure of type red (or blue, depending on inIsPlayerRed)
    bool _hasOwnPieceAtLocation(
        bool inIsPlayerRed,
        Point2D inPoint);

    // _checkIfCardExists will return 
    // true: if _allCards has a card called inCardName
    // false: if _allCards does not have a card called inCardName
    bool _checkIfCardExists(std::string inCardName);

    // _endpointIsInEndPositionOptions will consider all calculated
    // endpoint options and if one is equal to inFigureEndPosition
    // it will return true
    bool _endpointIsInEndPositionOptions(
        std::vector<Point2D> inEndPositionOptions,
        Point2D inFigureEndPosition);

    // _checkIfPlayerOwnsCard will return 
    // true: if inCardName is in _currentCardsRed
    //       (or _currentCardsBlue, depending on inIsPlayerRed)
    bool _checkIfPlayerOwnsCard(
        bool inIsPlayerRed,
        std::string inCardName);

    // _cardHasEndpositionAsOption will get the card, take all jumpoptions
    // calculate the endpoints and 
    bool _cardHasEndpositionAsOption(
        bool inIsPlayerRed,
        MoveInformation inMove);

    Card _getCard(std::string inCardName);

    // _calculateJumpEndOptions will take each inJumpOptions entry
    // add inFigureStartPosition onto them and give them back.
    // These will basically reflect all points a figure can jump
    // to with a card.
    std::vector<Point2D> _calculateJumpEndOptions(
        Point2D inFigureStartPosition,
        std::vector<Point2D> inJumpOptions);

};

#endif