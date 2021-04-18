#ifndef _MOVEINFORMATION_H_
#define _MOVEINFORMATION_H_

#include <string>
#include "Point2D.h"

class MoveInformation
{
private:
    std::string _cardName;
    Point2D _figureStartPosition;
    Point2D _figureEndPosition;
    bool _isInitialized;
public:
    MoveInformation(
        std::string inCardName, 
        Point2D inFigureStartPosition, 
        Point2D inFigureEndPosition)
    : _cardName(inCardName)
        , _figureStartPosition(inFigureStartPosition)
        , _figureEndPosition(inFigureEndPosition)
        , _isInitialized(true)
    {}

    MoveInformation()
        : _cardName("")
        , _figureStartPosition(Point2D(0,0))
        , _figureEndPosition(Point2D(0, 0))
        , _isInitialized(false)
    {}

    // Will return if it was successful
    // inTcpMove e.g. "TIGER;A1A3"
    bool ParseMove(std::string inTcpMove);

    Point2D GetFigureStartPosition() { return _figureStartPosition; }
    Point2D GetFigureEndPosition() { return _figureEndPosition; }
    std::string GetCardName() { return _cardName; }

};


#endif