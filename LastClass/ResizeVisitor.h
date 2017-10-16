//ResizeVisitor.h

#ifndef _RESIZEVISITOR_H
#define _RESIZEVISITOR_H

#include "Visitor.h" 

class ResizeVisitor : public Visitor {
public:
	ResizeVisitor(Long previousZoomRate, Long nextZoomRate);
	~ResizeVisitor();
	void Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY);
	void Visit(Class *object, CDC* pDC);
	void Visit(MemoBox* memoBox, CDC* pDC);
	void Visit(Selection *selection, CDC *pDC);

	void Visit(Template *object, CDC *pDC);
	void Visit(ClassName* className, CDC* pDC);
	void Visit(Attribute* attribute, CDC* pDC);
	void Visit(Method* method, CDC* pDC);
	void Visit(Reception* reception, CDC* pDC);
	void Visit(Line *line, CDC* pDC);

	void Visit(Generalization *generalization, CDC* pDC); //�Ϲ�ȭ
	void Visit(Realization * realization, CDC* pDC);		//��üȭ
	void Visit(Dependency *dependency, CDC* pDC);		//����
	void Visit(Association *association, CDC* pDC);		//����ȭ
	void Visit(DirectedAssociation *directedAssociation, CDC* pDC);		//��������
	void Visit(Aggregation *aggregation, CDC* pDC);		//����
	void Visit(Aggregations *aggregations, CDC* pDC);		//���տ���
	void Visit(Composition *composition, CDC* pDC);		//�ռ�
	void Visit(Compositions *compositions, CDC* pDC);		//���տ���
	void Visit(MemoLine* memobox, CDC *pDC); //�޸�
	void Visit(SelfGeneralization *selfGeneralization, CDC *pDC);
	void Visit(SelfAggregation *selfAggregation, CDC *pDC);
	void Visit(SelfDependency *selfdependency, CDC *pDC);
	void Visit(SelfAssociation *selfAssociation, CDC *pDC);
	void Visit(SelfAggregations *selfAggregations, CDC *pDC);
	void Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *pDC);
	void Visit(SelfComposition *selfComposition, CDC *pDC);
	void Visit(SelfCompositions *selfCompositions, CDC *pDC);

	void Visit(SelfRelation *selfRelation, CDC *pDC);
	void Visit(Relation *relation, CDC *pDC);

	void Visit(Text* text, CDC* pDC);


	void Visit(Diagram *diagram, Long zoomRate);
	void Visit(Class *object, Long zoomRate);
	void Visit(Relation *relation, Long zoomRate);
	void Visit(MemoBox *memoBox, Long zoomRate);
	void Visit(Line *line, Long zoomRate);
	void Visit(SelfRelation *selfRelation, Long zoomRate);
	void Visit(ClassName *className, Long zoomRate);
	void Visit(Attribute *attribute, Long zoomRate);
	void Visit(Method *method, Long zoomRate);
	void Visit(Reception *reception, Long zoomRate);
	void Visit(Template *object, Long zoomRate);

	//�������� �ؽ�Ʈ
	void Visit(Text *text, Long zoomRate);
private:
	Long previousZoomRate;
	Long nextZoomRate;
};

#endif // _RESIZEVISITOR_H