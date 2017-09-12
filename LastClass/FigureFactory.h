//FigureFactory.h

#ifndef _FIGUREFACTORY_H
#define _FIGUREFACTORY_H

#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include <string>

typedef unsigned long int ULong;
typedef signed long int Long;

using namespace std;
class TextComponent;
class Figure;
class FigureFactory {
public:
	FigureFactory();
	~FigureFactory();

	TextComponent* CreateRow(Long x, Long y, Long rowHieght, string stringCharacter);
	
	virtual TextComponent* CreateSingleCharacter(char singleByteCharacter) const {
		return new SingleByteCharacter(singleByteCharacter);
	}
	virtual TextComponent* CreateDoubleCharacter(char(*doubleByteCharacter)) const {
		return new DoubleByteCharacter(doubleByteCharacter);
	}
};

#endif // !_FIGUREFACTORY_H