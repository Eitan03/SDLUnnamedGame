#pragma once
class subject;

class observer {
	friend class subject;
public:
	void setSubject(subject* sbj) { _subject = sbj; }
protected:
	virtual void update() = 0;
	subject* _subject;
};



