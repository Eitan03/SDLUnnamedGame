#pragma once
class subject;

class observer {
public:
	virtual void update() = 0;
	void setSubject(subject* sbj) { _subject = sbj; }
protected:
	subject* _subject;
};



