//Aggregation.cpp
//����

#include "Aggregation.h"
#include "RollNameBox.h"

Aggregation::Aggregation(Long capacity):Relation(capacity) {
}

Aggregation::Aggregation(Long x, Long y, Long width, Long height) : Relation(x, y, width, height) {
	CPoint startPoint{ x, y };
	CPoint endPoint{ x + width, y + height };
	RollNameBox *boxPoint = RollNameBox::Instance();
	this->rollNamePoints->Modify(0, boxPoint->GetFirstRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(1, boxPoint->GetSecondRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(2, boxPoint->GetThirdRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(3, boxPoint->GetFourthRollNamePoint(startPoint, endPoint));
	this->rollNamePoints->Modify(4, boxPoint->GetFifthRollNamePoint(startPoint, endPoint));
}

Aggregation::~Aggregation() {

}

Aggregation::Aggregation(const Aggregation& source):Relation(source){
}

Aggregation& Aggregation::operator=(const Aggregation& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	return *this;
}

void Aggregation::Accept(Visitor& visitor, CDC *cPaintDc) {
	visitor.Visit(this,cPaintDc);//, cPaintDc);
}

Figure* Aggregation::Clone() const {
	return new Aggregation(*this);
}