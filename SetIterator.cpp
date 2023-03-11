#include <exception>
#include "SetIterator.h"
#include "Set.h"


SetIterator::SetIterator(const Set& m) : set(m) {
    current_pos=set.m;
    current_elem= nullptr;
    for(int i=0;i<set.m;i++){
        if(set.HashTable[i]!= nullptr) {
            current_pos = i;
            this->current_elem=set.HashTable[this->current_pos];
            break;
        }
    }
}

//best 0(1) worst 0(n) avg O(n)
void SetIterator::first() {
    current_pos=set.m;
    current_elem= nullptr;
    for(int i=0;i<set.m;i++){
        if(set.HashTable[i]!= nullptr) {
            current_pos = i;
            this->current_elem=set.HashTable[this->current_pos];
            break;
        }
    }
}

//best 0(1) worst 0(n) avg O(n)
void SetIterator::next() {
    if (valid()) {
        current_elem = current_elem->next;
        if (current_elem == nullptr) {
            do {
                current_pos++;
            } while (set.HashTable[current_pos]== nullptr);
            current_elem = set.HashTable[current_pos];
        }
    } else

        throw exception();

}

//best 0(1) worst 0(1) avg 0(1)
TElem SetIterator::getCurrent() {
	if(valid())
        return this->current_elem->info;
    else
        throw exception();
}

//best 0(1) worst 0(1) avg 0(1)
bool SetIterator::valid() const {
	if(this->current_pos<set.m && this->current_elem!= nullptr)
        return true;
	return false;
}



