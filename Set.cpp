#include "Set.h"
#include "SetITerator.h"
#include <cmath>

Set::Set() {
    this->m=13;
    this->nrElems=0;
    this->HashTable=new Node*[this->m];
    for(int i=0;i<this->m;i++)
        this->HashTable[i]= nullptr;
}

//best 0(1) worst 0(n) avg 0(1)
bool Set::add(TElem elem) {
    if(this->nrElems/ this->m==2) resize();
	if(!search(elem)){
        int pos= hash(elem);

        if(this->HashTable[pos]== nullptr){
            this->HashTable[pos]= new Node;
            this->HashTable[pos]->info=elem;
            this->HashTable[pos]->next= nullptr;
        }else{
            Node* aux=new Node;
            aux->info=elem;
            aux->next= this->HashTable[pos]->next;
            this->HashTable[pos]->next=aux;
        }

        this->nrElems++;
        return true;
    }
	return false;
}

//best 0(1) worst 0(n) avg 0(1)
bool Set::remove(TElem elem) {
	if(search(elem)){
        int pos= hash(elem);
        if(this->HashTable[pos]->info==elem)
            this->HashTable[pos]= this->HashTable[pos]->next;
        else{
            Node* current=this->HashTable[hash(elem)];
            Node* prev = nullptr;
            while (current != nullptr) {
                if(current->info==elem) {
                    prev->next = current->next;
                    delete current;
                    this->nrElems--;
                    return true;
                }
                prev=current;
                current=current->next;
            }
                return false;
        }

        this->nrElems--;
        return true;
    }
	return false;
}

//best 0(1) worst 0(n) avg 0(1)
bool Set::search(TElem elem) const {
    if(this->HashTable[hash(elem)]== nullptr)
        return false;
    else {
        Node* current=this->HashTable[hash(elem)];
        while (current != nullptr) {
            if (current->info == elem) {
                return true;
            } else {
                current = current->next;
            }
        }
    }
	return false;
}

//best 0(1) worst 0(1) avg 0(1)
int Set::size() const {
    return this->nrElems;
}

//best 0(1) worst 0(1) avg 0(1)
bool Set::isEmpty() const {
    if(this->nrElems==0)
        return true;
    return false;
}

//best 0(n) worst 0(n) avg 0(n)
Set::~Set() {
    for(int i=0;i<m;i++){
        if(this->HashTable[i]!= nullptr) {
            Node *aux = this->HashTable[i]->next;
            Node *prev = this->HashTable[i];
            while (aux != nullptr) {
                delete prev;
                prev = aux;
                aux = aux->next;
            }
            delete prev;
        }
    }
    delete[] this->HashTable;

}


SetIterator Set::iterator() const {
	return SetIterator(*this);
}

//best 0(1) worst 0(1) avg 0(1)
int Set::hash(TElem e) const {
    return abs(e%this->m);
}

//best 0(n) worst 0(n) avg 0(n)
void Set::resize() {
    TElem arr[nrElems];
    int index = 0;
    for(int i=0;i<m;i++){
        if(this->HashTable[i]!= nullptr){
            Node* current=this->HashTable[i];
            while (current != nullptr) {
                arr[index]=current->info;
                index++;
                current=current->next;
            }
        }
    }

    for(int i=0;i<m;i++){
        if(this->HashTable[i]!= nullptr) {
            Node *aux = this->HashTable[i]->next;
            Node *prev = this->HashTable[i];
            while (aux != nullptr) {
                delete prev;
                prev = aux;
                aux = aux->next;
            }
            delete prev;
        }
    }
    delete[] this->HashTable;

    this->m*=2;
    this->HashTable=new Node*[this->m];
    int old = nrElems;
    this->nrElems = 0;
    for(int i=0;i<this->m;i++)
        this->HashTable[i]= nullptr;

    for(int i=0;i<old;i++){
        add(arr[i]);
    }

}

//best 0(n) worst 0(n) avg 0(n)
Set Set::join(Set s1, Set s2) {
    Set *s3=new Set;
    s3->m=s1.m+s2.m;
    s3->nrElems=s1.nrElems+s2.nrElems;
    s3->HashTable=new Node*[s3->m];

    TElem arr[s3->nrElems];
    int index = 0;
    for(int i=0;i<s1.m;i++){
        if(s1.HashTable[i]!= nullptr){
            Node* current=s1.HashTable[i];
            while (current != nullptr) {
                arr[index]=current->info;
                index++;
                current=current->next;
            }
        }
    }
    for(int i=0;i<s2.m;i++){
        if(s2.HashTable[i]!= nullptr){
            Node* current=s2.HashTable[i];
            while (current != nullptr) {
                arr[index]=current->info;
                index++;
                current=current->next;
            }
        }
    }
    for(int i=0;i<index;i++) {
        int pos = hash(arr[i]);

        if (s3->HashTable[pos] == nullptr) {
            s3->HashTable[pos] = new Node;
            s3->HashTable[pos]->info = arr[i];
            s3->HashTable[pos]->next = nullptr;
        } else {
            Node *aux = new Node;
            aux->info = arr[i];
            aux->next = s3->HashTable[pos]->next;
            s3->HashTable[pos]->next = aux;
        }
    }

    return *s3;
}


