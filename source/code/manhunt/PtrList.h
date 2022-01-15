#pragma once
#include "core.h"
// todo

template <typename T>
struct CPtrListNode {
	int index;
	T* ptr;
	T* next;
};

template <typename T>
class CPtrList
{
public:
	CPtrListNode<T>* head;

	void Add(CPtrListNode<T>* ptr);
	void Remove(CPtrListNode<T>* ptr);
};

template<typename T>
inline void CPtrList<T>::Add(CPtrListNode<T>* ptr)
{
	CallMethod<0x43B510, CPtrList<T>*, CPtrListNode<T>*>(this, ptr);
}

template<typename T>
inline void CPtrList<T>::Remove(CPtrListNode<T>* ptr)
{
	CallMethod<0x59BA40, CPtrList<T>*, CPtrListNode<T>*>(this, ptr);
}
