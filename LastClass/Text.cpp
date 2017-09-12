//Text.cpp 
#include "Text.h"

Text::Text(Long capacity) : TextComposite(capacity) {
	this->capacity = capacity;
	this->length = 0;
}
Text::~Text() {
}

Text::Text(const Text& source) {
	this->textComponents = source.textComponents;

	Long i = 0;
	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Text&>(source)).textComponents[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

Long Text::Add(Row *row) {
	Long index;

	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, row->Clone());
	}
	else {
		index = this->textComponents.AppendFromRear(row->Clone());
		this->capacity++;
	}
	this->length++;
	return index;
}

Long Text::Add(TextComponent *textComponent) {
	Long index;

	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, textComponent);
	}
	else {
		index = this->textComponents.AppendFromRear(textComponent);
		this->capacity++;
	}
	this->length++;
	return index;
}
///////////////////////////////////////////////////////////////////////////////
Long Text::Modify(Long index, Long x, Long y, TextComponent *textComponent) {
	Row *row = new Row(x, y, 128);

	if (this->length < this->capacity) {
		index = this->textComponents.Store(this->length, textComponent);
	}
	else {
		index = this->textComponents.AppendFromRear(textComponent);
		this->capacity++;
	}
	this->length++;
	return index;
}

void Text::Find(Long x, Long y, Long height, Row**(*indexes), Long *count) {
	if (*indexes != 0) {
		delete *indexes;
		*indexes = 0;
	}
	*indexes = new Row*[128];
	Long i = 0;
	Long j = 0;
	while (i < this->GetLength()) {
		if (this->GetAt(i)->GetX() == x && this->GetAt(i)->GetY() >= y && this->GetAt(i)->GetY() <= y + height) {
			(*indexes)[j] = (Row*)(this->GetAt(i)->Clone());
			j++;
			*count += 1;
		}
		i++;
	}



	/*SmartPointer<TextComponent*> iterator(this->CreateIterator());
	if (*indexes != 0) {
	delete *indexes;
	*indexes = 0;
	}
	*indexes = new Row*[128];
	Long i = 0;
	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
	if (((Row*)iterator->Current())->GetX() == x && ((Row*)iterator->Current())->GetY() >= y && ((Row*)iterator->Current())->GetY() <= y + height) {
	(*indexes)[i] = (Row*)iterator->Current();
	i++;
	}
	}
	*count = i;*/
}

Long Text::Remove(Long index) {
	index=this->textComponents.Delete(index);
	this->length--;
	this->capacity--;
	return index;
}


Row* Text::GetAt(Long index) {
	return dynamic_cast<Row*>(this->textComponents[index]);
}

TextComponent* Text::Clone() const {
	return new Text(*this);
}

#include <iostream>
using namespace std;

void Text::PrintRow(SmartPointer<TextComponent*>& index) {
	Long i;
	for (index->First(); !index->IsDone(); index->Next()) {
		cout << "PrintRow Ȯ��" << endl;
	}
}

void Text::Accept(Visitor& visitor, CDC* cPaintDc) {
	cout << "Text Accept" << endl;
	SmartPointer<TextComponent*> smartPointer(this->CreateIterator());
	for (smartPointer->First(); !smartPointer->IsDone(); smartPointer->Next()) {
		static_cast<Row*>(smartPointer->Current())->Accept(visitor, cPaintDc);
	}
}

Long Text::InsertRow(Long formX, Long formY, Long rowHeight, Long index) {
	Row *row = new Row(formX, formY - 28 + (index + 1) * rowHeight, rowHeight);
	index = this->textComponents.Insert(index + 1, row->Clone());
	this->capacity++;
	this->length++;

	return index;
}

Row* Text::operator [] (Long index) {
	return dynamic_cast<Row*>(this->textComponents[index]);
}

Text& Text::operator = (const Text& source) {
	Long i = 0;
	this->textComponents = source.textComponents;

	while (i < source.length) {
		this->textComponents.Modify(i, (const_cast<Text&>(source)).textComponents.GetAt(i)->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}


//#include <iostream>
//using namespace std;
//
//#include "SingleByteCharacter.h"
//#include "DoubleByteCharacter.h"
//#include "Character.h"
//#include "WritingVisitor.h"
//
//#include <iostream>
//
//#include <string>
//
//using namespace std;
//
//int main(int argc, char* argv[]) {
//	Text object1(100); //����Ʈ������ Ȯ��
//	cout << object1.GetCapacity() << " " << object1.GetLength() << endl;
//
//	Text object2(object1); // ��������� Ȯ��
//	cout << object2.GetCapacity() << " " << object2.GetLength() << endl;
//
//	SingleByteCharacter singleByte('A');
//	
//	Row rowObject1(100);
//	Row rowObject2;
//	Row rowObject3;
//
//	DoubleByteCharacter doubleByte("��"); // 1
//	rowObject1.Add(doubleByte.Clone());
//	DoubleByteCharacter doubleByte2("��"); // 1
//	rowObject1.Add(doubleByte2.Clone());
//	DoubleByteCharacter doubleByte3("��"); // 2
//	rowObject2.Add(doubleByte3.Clone());
//	DoubleByteCharacter doubleByte4("��"); // 2
//	rowObject2.Add(doubleByte4.Clone());
//	DoubleByteCharacter doubleByte5(" !"); // 3
//	rowObject3.Add(doubleByte5.Clone());
//	SingleByteCharacter singleByte1('C'); // 3
//	rowObject3.Add(singleByte1.Clone());
//	SingleByteCharacter singleByte2('A'); // 3
//	rowObject3.Add(singleByte2.Clone());
//	SingleByteCharacter singleByte3('E'); // 2
//	rowObject2.Add(singleByte3.Clone());
//	SingleByteCharacter singleByte4('C'); // 1
//	rowObject1.Add(singleByte4.Clone());
//
//	object1.Add(rowObject1.Clone());
//	object1.Add(rowObject2.Clone());
//	object1.Add(rowObject3.Clone());
//
//	string testString;
//	Long i = 0;
//
//	while (i < object1.GetAt(0)->GetLength()) {
//
//		char testDouble[3] = { static_cast<DoubleByteCharacter*>(object1.GetAt(0)->GetAt(i))->GetCharacters()[0],
//								static_cast<DoubleByteCharacter*>(object1.GetAt(0)->GetAt(i))->GetCharacters()[1], '\0' };
//		testString = testDouble;
//		cout << testDouble;
//		i++;
//	}
//	
//	cout << endl << endl << "�����ϰ� ��±��� Ȯ��" << endl << endl;
//
//	SmartPointer<TextComponent*> testIterator = object1.CreateIterator();
//	object1.PrintRow(testIterator);
//
//	SmartPointer<TextComponent*> testIterator2 = object1.GetAt(0)->CreateIterator();
//	object1.GetAt(0)->PrintCharacter(testIterator2);
//	
//	cout << endl << endl << "Iterator SmartPointer ���� Ȯ��" << endl << endl;
//	
//	WritingVisitor testWritingVisitor;
//
//	if (dynamic_cast<SingleByteCharacter*>(object1.GetAt(0)->GetAt(0))) {
//		static_cast<SingleByteCharacter*>(object1.GetAt(0)->GetAt(0))->Accept(testWritingVisitor);
//	}
//	else if (dynamic_cast<DoubleByteCharacter*>(object1.GetAt(0)->GetAt(0))) {
//		static_cast<DoubleByteCharacter*>(object1.GetAt(0)->GetAt(0))->Accept(testWritingVisitor);
//	}
//
//	object1.GetAt(0)->Accept(testWritingVisitor);
//	cout << endl;
//	object1.Accept(testWritingVisitor);
//
//
//
//	return 0;
//}