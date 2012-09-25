#ifndef _TPOINTER_H_
#define _TPOINTER_H_

template <class T> class TPointer {
private:
	Pointer(T* Object = 0);
	Pointer(const Pointer& from);
	~Pointer();

	operator T*() const;
	T& operator*() const;
	T* operator->() const;

	TPointer& operator=(T* object);
	TPointer& operator=(const TPointer& reference);
	bool operator==(T* object) const;
	bool operator!=(T* object) const;
	bool operator==(const TPointer& reference) const;
	bool operator!=(const TPointer& reference) const;
public:

private:

};

#endif