#ifndef WIZARD_UTILS_STACK_HPP
#define WIZARD_UTILS_STACK_HPP

#include "types.hpp"

#include <cassert>

template<u8 capacity>
struct Stack {
	// Top indice of the stack.
	u8 top = 0;

	// Stack data.
	u8 stack[capacity];
};

template<u8 c>
void InitializeStack(Stack<c> *s) {
	s->top = 0;
}

template<u8 c>
void InvalidateIndex(Stack<c>* s, u8 idx) {
	for(u8 i = idx; i < s->top - 1; i++) {
		s->stack[i] = s->stack[i + 1];
	}
	
	s->top = s->top - 1;
}

template<u8 c>
void Push(Stack<c>* s, u8 v) {
	assert(s->top < s->capacity);
 
	s->stack[s->top++] = v;
}

template<u8 c>
u8 Pop(Stack<c>* s) {
	assert(s->top > 0);

	return s->stack[--s->top];
}


#endif // WIZARD_UTILS_STACK_HPP
