#ifndef DLIST_H
#define DLIST_H

template <typename tType>
class DList;

template <typename tType>
class DNode{
    private:
    tType data;
    uint number;
    DNode<tType>* next;
    DNode<tType>* prev;
    friend class DList<tType>;
    public: 
    DNode(){this->next=NULL; this->number=0;}
    DNode(tType value){this->data=value; this->number=0; this->next=NULL;}
    DNode(tType value, uint n){this->data=value; this->number=n; this->next=NULL;}
    ~DNode(){}
    tType getData() const{return this->data;}
    uint getNumber() const{return this->number;}
    DNode* getNext() {return this->next;}
    DNode* getPrev() {return this->prev;}
    void setData(tType newData){data=newData;}
    void setNext(DNode<tType>* nextNode){next=nextNode;}
    void setPrev(DNode<tType>* prevNode){prev=prevNode;}
};

template <typename tType>
class DList{
    private:
        DNode<tType>* head;
        DNode<tType>* tail;
    public:
        DList(){head=NULL;tail=NULL;}
        ~DList(){}

        bool empty() const{
            if(head==NULL){return true;} return false;
        }

        void addFront(const tType& value){
            DNode<tType> *front=new DNode<tType>(value);
            if(this->empty()){
                tail=front;
                front->setNext(NULL);
            }else{
                head->setPrev(front);
                front->setNext(head);
            }
            front->setPrev(NULL);
            head=front;
        }

        void addBack(const tType& value){
            DNode<tType> *back=new DNode<tType>(value);
            if(this->empty()){
                head=back;
                back->setPrev(NULL);
            }else{
                tail->setNext(back);
                back->setPrev(tail);
            }
            back->setNext(NULL);
            tail=back;
        }
        
        void addAfter(const tType& value, uint n){
            if(n==0){
                this->addFront(value);
            }
            else{
                DNode<tType>* after=new DNode<tType>(value);
                DNode<tType>* temp1=head;
                uint i=1;
                while((temp1!=NULL)&&(i<n)){
                    ++i;
                    temp1=temp1->getNext(); 
                }
                if(temp1==NULL){
                    throw std::range_error("Wykroczono poza zakres");
                }
                else if(temp1->getNext()!=NULL){
                    after->setPrev(temp1);
                    after->setNext(temp1->getNext());
                    temp1->setNext(after);
                }
                else if(i==n){
                    after->setPrev(temp1);
                    after->setNext(NULL);
                    temp1->setNext(after);
                }
                else{throw std::range_error("Wykroczono poza zakres");}

            }
        }

        void addBefore(const tType& value, uint n){
            if(n==0){
                throw std::range_error("Wykroczono poza zakres");
            }
            else if(n==1){
                this->addFront(value);
            }
            else{
                
                DNode<tType>* temp1=head;
                uint i=1;
                while((temp1!=NULL)&&(i<n)){
                    ++i;
                    temp1=temp1->getNext(); 
                }
                if(temp1!=NULL){
                    DNode<tType>* before=new DNode<tType>(value);
                    before->setNext(temp1);
                    before->setPrev(temp1->getPrev());
                    temp1->setPrev(before);
                }
                else if(i==n){
                    this->addBack(value);
                }
                else{throw std::range_error("Wykroczono poza zakres");}

            }
        }

        tType first() const{
            if(this->empty()){throw std::range_error("Brak elementów");}
            return head->getData();
        }

        tType last() const{
            if(this->empty()){throw std::range_error("Brak elementów");}
            return tail->getData();
        }

        void removeFront(){
            if(this->empty()){throw std::range_error("Brak elementów");}
            std::cout << "Wartość usunięta   " << head->getData() << std::endl;
            if(head->getNext()!=NULL){
            head=head->getNext();
            head->setPrev(NULL);
            }else{
                tail=NULL;
                head=NULL;
            }
            
        }

        void removeBack(){
            if(this->empty()){throw std::range_error("Brak elementów");}
            std::cout << "Wartość usunięta   " << tail->getData() << std::endl;
            if(tail->getPrev()!=NULL){
            tail=tail->getPrev();
            tail->setNext(NULL);
            }else{
                head=NULL;
                tail=NULL;
            }
            
        }

        
        void removeNode(const uint& n){
            if(n<1){throw std::range_error("Można usunąć elementy od 1");}
            DNode<tType>* temp1=head;
            uint i=1;
            while((temp1!=NULL)&&(i<n)){
                ++i;
                temp1=temp1->getNext(); 
            }
            if((temp1!=NULL)){
                if(temp1->getNext()==NULL){
                    tail=temp1->getPrev();
                    std::cout << "Usunięto element: " << temp1->getData() << std::endl;
                    tail->setNext(NULL);
                }else if(temp1->getPrev()==NULL){
                    head=temp1->getNext();
                    std::cout << "Usunięto element: " << temp1->getData() << std::endl;
                    head->setPrev(NULL);
                }else{
                    DNode<tType>* temp2=temp1->getPrev();
                    temp2->setNext(temp1->getNext());
                    std::cout << "Usunięto element: " << temp1->getData() << std::endl;
                    temp1=temp1->getNext();
                    temp1->setPrev(temp2);
                }
            }
            else{throw std::range_error("Wykroczono poza zakres");}
        }

        int nodeNumber() const{
            DNode<tType>* temp1=head;
            int val=0;
            while(temp1!=NULL){
                val++;
                temp1=temp1->getNext(); 
            }
            return val;
        }

        void printData() const{
            DNode<tType>* temp1=head;
            if(this->empty()){std::cout << "No Data" << std::endl;}
            else{
                std::cout << "Dane:" << std::endl;
                while(temp1!=NULL){
                    std::cout << temp1->getData() << "\t";
                    temp1=temp1->getNext();
                }
                std::cout << std::endl;
            }
        }

        std::string toString() const{
            DNode<tType>* temp1=head;
            std::string text;
            if(this->empty()){throw std::range_error("Brak elementów");}
            else{
                while(temp1!=NULL){
                    text+=temp1->getData();
                    temp1=temp1->getNext();
                }
            }
            return text;
        }

};


#endif