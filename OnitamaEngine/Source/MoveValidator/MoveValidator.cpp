#include "MoveValidator.h"
#include "../MoveInformation/MoveInformation.h"


MoveValidator::MoveValidator(
    bool inRedStarts,
    MoveInformation inMove,
    OnitamaEngine inEngine)
    : _redStarts(inRedStarts)
    , _move(inMove)
    , _engine(inEngine)
{    
}


bool MoveValidator::ValidateMove()
{
    std::string cardName = _move.GetCardName();
    Point2D figureStartPosition = _move.GetFigureStartPosition();
    Point2D figureEndPosition = _move.GetFigureEndPosition();

    if (!_isOnBoard(figureStartPosition))
    {
        _moveValidatorStatus = "The start point isn't on the game board (";
        _moveValidatorStatus += figureStartPosition.ToChessString() + ").";
        return false;
    }
    if (!_hasOwnPieceAtLocation(_redStarts, figureStartPosition))
    {
        _moveValidatorStatus = "No piece of player ";
        _moveValidatorStatus += ((_redStarts) ? "red" : "blue");
        _moveValidatorStatus += " found at start point (";
        _moveValidatorStatus += figureStartPosition.ToChessString() + ").";
        return false;
    }
    if (!_checkIfCardExists(cardName))
    {
        _moveValidatorStatus = "The cardname ";
        _moveValidatorStatus += cardName;
        _moveValidatorStatus += " wasn't found at all.";
        return false;
    }
    if (!_checkIfPlayerOwnsCard(_redStarts, cardName))
    {
        _moveValidatorStatus = "The player ";
        _moveValidatorStatus += ((_redStarts) ? "red" : "blue");
        _moveValidatorStatus += " doesn't have the card ";
        _moveValidatorStatus += cardName;
        _moveValidatorStatus += ".";
        return false;
    }
    if (!_isOnBoard(figureEndPosition))
    {
        _moveValidatorStatus = "The end point isn't on the board (";
        _moveValidatorStatus += figureEndPosition.ToChessString() + ").";
        return false;
    }
    if (_hasOwnPieceAtLocation(_redStarts, figureEndPosition))
    {
        _moveValidatorStatus = "The end point is already occupied by a piece of player(";
        _moveValidatorStatus += ((_redStarts) ? "red" : "blue");
        _moveValidatorStatus += ".";
        return false;
    }
    if (_cardHasEndpositionAsOption(
        _redStarts, _move))
    {
        _moveValidatorStatus = "The choosen card (" + cardName;
        _moveValidatorStatus += ") doesn't allow a jump from ";
        _moveValidatorStatus += figureStartPosition.ToChessString() + " to ";
        _moveValidatorStatus += figureEndPosition.ToChessString() + ".";
        return false;
    }
    return true;
}

std::string MoveValidator::GetStatus()
{
    return _moveValidatorStatus;
}


bool MoveValidator::_isOnBoard(Point2D inPoint)
{
    if (inPoint.GetX() < 0 ||
        inPoint.GetX() > _engine.GetBoardSize() - 1 ||
        inPoint.GetY() < 0 ||
        inPoint.GetY() > _engine.GetBoardSize() - 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}


bool MoveValidator::_hasOwnPieceAtLocation(
    bool inIsPlayerRed,
    Point2D inPoint)
{
    char pieceOnPoint = _engine.GetCurrentBoardState()[inPoint.GetY()][inPoint.GetX()];
    char ownDisciple;
    char ownMaster;
    if (inIsPlayerRed)
    {
        ownDisciple = _engine.GetRedDisciple();
        ownMaster = _engine.GetRedMaster();
    }
    else
    {
        ownDisciple = _engine.GetBlueDisciple();
        ownMaster = _engine.GetBlueMaster();
    }
    if (pieceOnPoint != ownDisciple && pieceOnPoint != ownMaster)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool MoveValidator::_checkIfCardExists(std::string inCardName)
{
    for (
        unsigned int i = 0; 
        i < _engine.GetAllCards().size(); 
        i++)
    {
        if (_engine.GetAllCards()[i].GetName() == inCardName)
        {
            return true;
        }
    }
    return false;
}

bool MoveValidator::_endpointIsInEndPositionOptions(
    std::vector<Point2D> inEndPositionOptions,
    Point2D inFigureEndPosition)
{
    for (unsigned int i = 0; i < inEndPositionOptions.size(); i++)
    {
        if (inFigureEndPosition == inEndPositionOptions[i])
        {
            return true;
        }
    }
    return false;
}

bool MoveValidator::_checkIfPlayerOwnsCard(
    bool inIsPlayerRed,
    std::string inCardName)
{
    std::vector<Card> playersCards;
    if (inIsPlayerRed)
    {
        playersCards = _engine.GetCurrentCardsRed();
    }
    else
    {
        playersCards = _engine.GetCurrentCardsBlue();
    }

    for (unsigned int i = 0; i < playersCards.size(); i++)
    {
        if (playersCards[i].GetName() == inCardName)
        {
            return true;
        }
    }
    return false;
}


bool MoveValidator::_cardHasEndpositionAsOption(
    bool inIsPlayerRed,
    MoveInformation inMove)
{
    Card usedCard = _getCard(inMove.GetCardName());
    std::vector<Point2D> jumpOptions =
        usedCard.GetJumpOptions(inIsPlayerRed);
    std::vector<Point2D> endPositionOptions =
        _calculateJumpEndOptions(
            inMove.GetFigureStartPosition(),
            jumpOptions);

    return _endpointIsInEndPositionOptions(
        endPositionOptions,
        inMove.GetFigureEndPosition());
}

Card MoveValidator::_getCard(std::string inCardName)
{
    for (unsigned int i = 0; i < _engine.GetAllCards().size(); i++)
    {
        if (_engine.GetAllCards()[i].GetName() == inCardName)
        {
            return _engine.GetAllCards()[i];
        }
    }
    return Card("HÄBÄDÄBÄDÄH!", true);
}

std::vector<Point2D> MoveValidator::_calculateJumpEndOptions(
    Point2D inFigureStartPosition,
    std::vector<Point2D> inJumpOptions)
{
    std::vector<Point2D> ret = std::vector<Point2D>();
    for (unsigned int i = 0; i < inJumpOptions.size(); i++)
    {
        ret.push_back(inFigureStartPosition + inJumpOptions[i]);
    }
    return ret;
}

