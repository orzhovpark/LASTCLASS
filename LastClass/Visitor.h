//Visitor.h

#ifndef _VISITOR_H
#define _VISITOR_H

#include <afxwin.h>

class SingleByteCharacter;
class DoubleByteCharacter;
class Class;
class Line;
class Row;
class Visitor {
public:
	virtual ~Visitor();

	virtual void Visit(Class *object, CDC* cPaintDc) = 0;
	virtual void Visit(Line *line, CDC* cPaintDc) = 0;
	virtual void Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc) = 0;
	virtual void Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) = 0;
	virtual void Visit(Row* row, CDC* cPaintDc) = 0;
protected:
	Visitor();
};

#endif // _VISITOR_H