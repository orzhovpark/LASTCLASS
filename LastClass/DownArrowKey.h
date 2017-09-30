//DownArrowKey.h

#ifndef _DOWNARROWKEY_H
#define _DOWNARROWKEY_H

#include "KeyAction.h"

class TextEdit;
class ClassDiagramForm;
class DownArrowKey : public KeyAction {
public:
	DownArrowKey();
	DownArrowKey(const DownArrowKey& source);
	virtual ~DownArrowKey();

	void KeyPress(TextEdit *textEdit);
	void KeyPress(ClassDiagramForm *classDiagramForm);
};

#endif // _DOWNARROWKEY_H