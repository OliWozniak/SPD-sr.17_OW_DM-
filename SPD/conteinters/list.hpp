#ifndef LIST_H
#define LIST_H

template <typename tType>
class SList;

template <typename tType>
class SNode{
    private:
    tType data;
    uint number;
    SNode<tType>* next;
    friend class SList<tType>;
    public: 
    SNode(){this->next=NULL; this->number=0;}
    SNode(tType value){this->data=value; this->number=0; this->next=NULL;}
    SNode(tType value, uint n){this->data=value; this->number=n; this->next=NULL;}
    tType getData() const{return this->data;}
    uint getNumber() const{return this->number;}
    SNode* getNext() {return this->next;}
    void setData(tType newData){data=newData;}
    void setNext(SNode<tType>* nextNode){next=nextNode;}
};

template <typename tType>
class SList{
    private:
        SNode<tType>* head;
    public:
        SList(){head=NULL;}
        ~SList(){}

        bool empty() const{
            if(head==NULL){return true;} return false;
        }

        void addFront(const tType& value){
            SNode<tType> *front=new SNode<tType>(value);
            if(this->empty()){
                front->setNext(NULL);
            }
            else{
                front->setNext(head);
            }
            head=front;
        }

        void addBack(const tType& value){
            SNode<tType> *back=new SNode<tType>(value);
            SNode<tType>* temp1=head;
            if(head==NULL){
                head=back;
            }else{
                while(temp1->getNext()!=NULL){
                    temp1=temp1->getNext(); 
                }
                temp1->setNext(back);
            }
            back->setNext(NULL);
            
        }

        tType first() const{
            if(this->empty()){throw std::range_error("Brak elementów");}
            return head->getData();
        }

        tType last() const{
            if(this->empty()){throw std::range_error("Brak elementów");}
            SNode<tType>* temp1=head;
            while(temp1->getNext()!=NULL){
                    temp1=temp1->getNext(); 
            }
            return temp1->getData();
        }

        void removeFront(){
            if(this->empty()){throw std::range_error("Brak elementów");}
            std::cout << "Wartość usunięta   " << head->getData() << std::endl;
            head=head->getNext();
        }

        int nodeNumber() const{
            SNode<tType>* temp1=head;
            int val=0;
            while(temp1!=NULL){
                val++;
                temp1=temp1->getNext(); 
            }
            return val;
        }

        void printData() const{
            SNode<tType>* temp1=head;
            if(this->empty()){std::cout << "No Data" << std::endl;}
            else{
                std::cout << "Dane:" << std::endl;
                while(temp1!=NULL){
                    std::cout << temp1->getData();
                    temp1=temp1->getNext();
                }
                std::cout << std::endl;
            }
        }

        std::string toString() const{
            SNode<tType>* temp1=head;
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