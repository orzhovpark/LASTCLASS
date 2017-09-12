//Figure.h

#ifndef _FIGURE_H //���弱��
#define _FIGURE_H

typedef signed long int Long;

class Figure {
public:
	Figure();
	Figure(const Figure& source);
	//virtual Figure& operator = (const Figure& source) = 0;
	virtual ~Figure() = 0;

	virtual Figure* Clone() const = 0;

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
protected:
	Long x;
	Long y;
	Long width;
	Long height;
};

inline Long Figure::GetX() const {
	return this->x;
}
inline Long Figure::GetY() const {
	return this->y;
}
inline Long Figure::GetWidth() const {
	return this->width;
}
inline Long Figure::GetHeight() const {
	return this->height;
}

#endif //_FIGURE_H