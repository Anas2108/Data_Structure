#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node {
	int data { };
	Node* next { };
	Node* prev { };	

	Node(int data) : data(data) {}

	void set(Node* next, Node* prev) {
		this->next = next;
		this->prev = prev;
	}

	~Node() {
		cout << "Destroy value: " << data << " at address " << this << "\n";
	}
};

class DoubleLinkedList 
{
    private:
	Node *head =nullptr;
	Node *tail =nullptr;
	int length = 0;

	// let's maintain how many nodes

	vector<Node*> debug_data;	// add/remove nodes you use

	void debug_add_node(Node* node) {
		debug_data.push_back(node);
	}
	void debug_remove_node(Node* node) {
		auto it = std::find(debug_data.begin(), debug_data.end(), node);
		if (it == debug_data.end())
			cout << "Node does not exist\n";
		else
			debug_data.erase(it);
	}

public:
                    /***** Debug Section  ****/


	void debug_verify_data_integrity() {
		if (length == 0) {
			assert(head == nullptr);
			assert(tail == nullptr);
		} else {
			assert(head != nullptr);
			assert(tail != nullptr);
			if (length == 1)
				assert(head == tail);
			else
				assert(head != tail);
			assert(!head->prev);
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++) {
			if (len == length-1)	// make sure we end at tail
				assert(cur == tail);
		}

		assert(length == len);
		assert(length == (int )debug_data.size());

		len = 0;
		for (Node* cur = tail; cur; cur = cur->prev, len++) {
			if (len == length-1)	// make sure we end at head
				assert(cur == head);
		}
		cout << "\n";
	}
                /***** End of Debug Section  ****/

////////////////////////////////////////////////////////////
 void add_node (Node*node)
 {
    debug_add_node(node);
    length++;
    
 }

 void delete_node (Node*node)
 {
    debug_remove_node(node);
    length--;
    delete node;
 }

//////////////////////////////////////////////////////////////////
 void print ()
   {
    Node * tempHead=head;
    while (tempHead !=nullptr)
    {
        cout<<tempHead->data<<" ";
        tempHead=tempHead->next;
    }
    
   }
//////////////////////////////////////////////////////////////////

    void link (Node*first,Node*second)
    {
        if (first)
        first->next=second;
        if (second)
        second->prev=first;

    };

    void embed_after (Node*before,int value)
    {
        Node*middle=new Node(value);
        add_node(middle);
        Node*after=before->next;
        link (before,middle);
        link (middle,after);
    }

    //////////////////////////////////////////////////////////////////

    void insert_end (int value)
    {
        Node*inserted_value= new Node(value);
        add_node(inserted_value);
        
        if(!head)
        head=tail=inserted_value;
        else
        {
            link(tail,inserted_value);
            tail=inserted_value;
        }
        debug_verify_data_integrity();
    }

    void insert_front (int value)
    {
        Node*inserted_value= new Node(value);
        add_node(inserted_value);
        
        if(!head)
        head=tail=inserted_value;
        else
        {
            link(inserted_value,head);
            head=inserted_value;
        }
        debug_verify_data_integrity();
    }

    void sorted_insert (int value)
    {
        if(!length || value <= head->data)
        insert_front(value);

        else if (tail->data <= value)
        insert_end(value);

        else    
        {
            for (Node*cur=head;cur;cur=cur->next)
            {
                if (value <= cur->data){
                embed_after(cur->prev,value);
                break;
                }
            }
        }

    }

    ////////////////////////////////////////////////////////////////////

    void delete_front ()
    {
        if (!head)
        return;

        Node*cur = head->next;
        delete_node(head);
        head=cur;
        head->prev=nullptr;
        debug_verify_data_integrity();
    }

    void delete_end ()
    {
        if (!head)
        return;

        Node*cur =tail->prev;
        delete_node(tail);
        tail=cur;
        tail->next=nullptr;
        debug_verify_data_integrity();
    }

    Node * delete_and_link (Node *cur)
    {
        Node*before=cur->prev;
        link(cur->prev,cur->next);
        delete_node (cur);
        return before;
    }

    void delete_with_key (int value) 
    {
        if (!head)
        return;
        if (value == head->data)
        delete_front();

        else if (value == tail->data)
        delete_end();

        else 
        {
            for (Node*cur=head ;cur;cur=cur->next)
            {
                if (value == cur->data){
                delete_and_link (cur);
                debug_verify_data_integrity();
                return;
                }
            }
            cout<<"Value not found!";

        }
        debug_verify_data_integrity();
    }

    void  delete_all_nodes_with_key(int value)
    {
       
         if (!head)
        return;

        insert_front(-value);
      
            for (Node *cur = head; cur;) 
            {
			    if (cur->data == value) 
                {
				cur = delete_and_link(cur);
				if(!cur->next)
					tail = cur;
			    }
			    else
				    cur = cur->next;
	    	}
                 delete_front();


    
        debug_verify_data_integrity();
    }

    void delete_even_postions ()
    {
        int counter=1;
        Node*next=nullptr;
        if (!head)
        return;

        if (length<=1)
        {
        return;
        }

        else if(length%2==0)
        delete_end();

         for (Node *cur = head; cur;) 
            {
			    if (counter%2==0) 
                {
                    next=cur->next;
				 delete_and_link(cur);
                 if (next!=nullptr)
                cur=next;
                else 
                tail=cur;	
                counter++;			
			    }
			    else
                {
                    cur = cur->next;
                    counter++;
                }
				    
	    	}
    }

    void delete_odd_positions() 
    {
        if (!head)
        {
            return;
        }

		if (length <= 1)
        {
            delete_front();
        tail=head=nullptr;
			return;
        }
        insert_front(0);
		//cur is always odd and ->next is even
		for(Node *cur = head; cur && cur->next; cur = cur->next) {
			delete_and_link(cur->next);
			if (!cur->next)
				tail = cur;	// in even length, the tail will change
		}
        delete_front();
		debug_verify_data_integrity();
	}

    bool is_palindrome()
    {
        bool flag=true;
        int iteration;

        Node*first=head;
        Node*last=tail;

        if (length%2 == 0)
        iteration=length/2;
        else
        iteration=(length/2)+1;

        while (iteration--)
        {
            if (first->data != last->data)
            {
                flag=false;
                break;
            }  
          
            first=first->next;
            last=last->prev; 
            
        }

        return flag;
        
    }
};


int main ()
{
   DoubleLinkedList list;

   /*Functions Test*/
  
}