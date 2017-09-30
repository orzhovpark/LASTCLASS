#include "MovingObject.h"
#include "Figure.h"
#include "Selection.h"
#include "Finder.h"
#include "Line.h"
#include "SelectionState.h"
#include "Relation.h"
#include "Diagram.h"
MovingObject* MovingObject::instance = 0;

MouseLButtonAction* MovingObject::Instance() {
	if (instance == 0) {
		instance = new MovingObject;
	}
	return instance;
}

void MovingObject::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	if (dynamic_cast<FigureComposite*>(selection->GetAt(0))) {
		MovingVisitor movingVisitor;
		FigureComposite *figures = static_cast<FigureComposite*>(selection->GetAt(0));
		Finder finder;
		Long i = 0; 
		Long j = 0;
		bool ret = false;
		CRect cRect1(figures->GetX()+(currentX-startX), figures->GetY()+(currentY - startY), figures->GetX() + (currentX - startX) + figures->GetWidth(), figures->GetY() + (currentY - startY) + figures->GetHeight());
		while (i < diagram->GetLength() && ret != true) {
			FigureComposite *figureComposite = static_cast<FigureComposite*>(diagram->GetAt(i));
			CRect cRect2(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
			ret = finder.FindRectangleByArea(cRect2, cRect1);
			if (figures == figureComposite) {
				ret = false;
			}
			i++;
		}
		// FigureComposite�� ���輱 �� ��ġ�� �� Remove
		i = 0;
		while (i < figures->GetLength()) {
			if (dynamic_cast<Relation*>(figures->GetAt(i))) {
				Relation *object = static_cast<Relation*>(figures->GetAt(i));
				j = 0;
				while (j < object->GetLength()) {
					CPoint cPoint = object->GetAt(j);
					bool ret1 = finder.FindRectangleByPoint(cRect1, cPoint.x, cPoint.y);
					if (ret1 == true) {
						object->Remove(j);
						j--;
					}
					j++;
				}
			}
			i++;
		}
		if (ret == false) {
			Long distanceX = currentX - startX;
			Long distanceY = currentY - startY;
			selection->Accept(diagram, movingVisitor, distanceX, distanceY);
		}
		this->ChangeState(mouseLButton, SelectionState::Instance());
	}



	this->ChangeState(mouseLButton, SelectionState::Instance());
}
void MovingObject::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
	if (selection->GetLength() == 0) {
		this->ChangeDefault(mouseLButton);
	}
}

void MovingObject::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);


	Long distanceX = currentX - startX;
	Long distanceY = currentY - startY;
	Long i = 0;
	Long j = 0;
	Figure *figure ;

	figure = selection->GetAt(i);
	if (dynamic_cast<FigureComposite*>(figure)) { //Ŭ������ �޸��
												  // �ش� Ŭ������ �޸� �̵�
		cPaintDC->Rectangle(figure->GetX() + distanceX, figure->GetY() + distanceY, figure->GetX() + figure->GetWidth() + distanceX,
			figure->GetY() + figure->GetHeight() + distanceY);
		FigureComposite *figureComposite = static_cast<FigureComposite*>(figure); // ����ȯ

		while (j < figureComposite->GetLength()) { // ����ȯ �Ѱ� �����ϸ� �迭 ��������
			figure = figureComposite->GetAt(j);
			if (dynamic_cast<Line*>(figure)) {
				cPaintDC->MoveTo(figure->GetX() + distanceX, figure->GetY() + distanceY);
				cPaintDC->LineTo(figure->GetX() + figure->GetWidth() + distanceX,
					figure->GetY() + figure->GetHeight() + distanceY);
			}
			j++;
		}
	}


	


	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();

}