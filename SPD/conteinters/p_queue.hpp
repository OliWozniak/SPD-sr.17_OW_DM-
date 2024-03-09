#ifndef PQUEUE_H
#define PQUEUE_H

template <typename tType>
class P_Queue;

template <typename tType>
class P_Node{
    private:
    tType data;
    uint priority;
    P_Node<tType>* next;
    P_Node<tType>* prev;
    friend class P_Queue<tType>;
    public: 

    P_Node(tType value, uint n){
    this->data=value; 
    this->priority=n; 
    this->next=NULL; 
    this->prev=NULL;
    }

    ~P_Node(){}

    tType getData() const{return this->data;}
    uint getPriority() const{return this->priority;}
    P_Node* getNext() const{return this->next;}
    P_Node* getPrev() const{return this->prev;}
    void setData(tType newData){this->data=newData;}
    void setNext(P_Node<tType>* nextNode){this->next=nextNode;}
    void setPrev(P_Node<tType>* prevNode){this->prev=prevNode;}
};

template <typename tType>
class P_Queue{
    private:
        P_Node<tType>* min;
        P_Node<tType>* last;
    public:
        P_Queue(){min=NULL;last=NULL;}
        ~P_Queue(){}

        bool isEmpty() const{
            if(min==NULL){return true;} return false;
        }

        void addNode(const tType& value,const uint& p){
            P_Node<tType> *added=new P_Node<tType>(value,p);
            if((this->last==NULL)&&(this->min==NULL)){
                this->min=added;
                this->last=added;
            } else
            {
                P_Node<tType>* temp1 = this->last;
                while((temp1->getPrev()!=NULL)&&(temp1->getPriority()>p)){
                    temp1=temp1->getPrev();
                }

                if ((temp1->getPrev()==NULL)&&(temp1->getPriority()>p)){
                    this->min=added;
                    temp1->setPrev(added);
                    added->setNext(temp1);
                    added->setPrev(NULL);
                } else if(temp1->getNext()==NULL) {
                    this->last=added;
                    temp1->setNext(added);
                    added->setPrev(temp1);
                    added->setNext(NULL);
                } else {
                    added->setPrev(temp1);
                    added->setNext(temp1->getNext());
                    temp1->setNext(added);
                    temp1=added->getNext();
                    temp1->setPrev(added);
                }
            }
        }

        tType peakMin() const{
            if(this->isEmpty()){throw std::range_error("Brak elementów");}
            return min->getData();
        }

        tType removeMin(){
            if(this->isEmpty()){throw std::range_error("Brak elementów");}
            tType temp;
            temp=min->getData();
            if(min->getNext()==NULL){
                this->min=NULL;
                this->last=NULL;
            }else{
                min=min->getNext();
                min->setPrev(NULL);
            }
            return temp;
        }

        uint size() const{
            P_Node<tType>* temp1=min;
            int val=0;
            while(temp1!=NULL){
                val++;
                temp1=temp1->getNext(); 
            }
            return val;
        }

        void clear(){
            this->min=NULL;
            this->last=NULL;
        }

};

#endif