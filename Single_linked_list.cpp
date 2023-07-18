#include <iostream>
#include <cassert>
#include <climits>

#include <vector>		// for debug
#include <algorithm>
#include <sstream>
using namespace std;

struct Node
{
    int data=0;
    Node*next=nullptr;

    Node(int data) :data(data){};
};

class LinkedList
{
private:
   Node *head { };
   Node *tail{ };
   int length=0;
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

Node* get_head(){return head;}
Node* get_tail(){return tail;}

/*Debug section */
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
			assert(!tail->next);
		}
		int len = 0;
		for (Node* cur = head; cur; cur = cur->next, len++)
			assert(len < 10000);	// Consider infinite cycle?
		assert(length == len);
		//assert(length == (int)debug_data.size());
	}
    /////////////////////////////////////////////////////
    
   void print ()
   {
    Node * tempHead=head;
    while (tempHead !=nullptr)
    {
        cout<<tempHead->data<<" ";
        tempHead=tempHead->next;
    }
    
   }

   void print2 ()
   {
    for ( Node *tempHead = head; tempHead;tempHead=tempHead->next )
    {
          cout<<tempHead->data<<" ";
    }
    

   }
   //////////////////////////////////////////////////////

   void delete_node(Node* node) {
		debug_remove_node(node);
		--length;
		delete node;
	}

	void add_node(Node* node) {
		debug_add_node(node);
		++length;

	}

    

////////////////////////////////////////////////////////////

   void insert_end(int value)
   {
    Node*insertedValue=new Node (value);
    if (!head)
    {
        head=tail=insertedValue;
        length++;
    }

    else
    {
        tail->next=insertedValue;
        tail=insertedValue;
        length++;
    }

     debug_verify_data_integrity();
   }

   void insert_front (int value)
   {
    Node *insertedValue=new Node(value);
    if(!head)
    {
        head=tail=insertedValue;
        length++;
    }
    else 
    {
        Node*old_head=head;
        head=insertedValue;
        head->next=old_head;
        length++;
    }
     debug_verify_data_integrity();
   }

   ///////////////////////////////////////////////////////

   void delete_front()
   {
    assert(length);
    Node*old_Head=head;
    head=head->next;
    delete_node(old_Head);
    if(length<=1)
    tail==head;
    
   }

   void delete_back()
   {
    assert(length);
    if(length==1)
    head=tail=nullptr;

    Node*old_tail=tail;
    Node*prv=get_nth(length-1);
    
    tail=prv;
    tail->next=nullptr;
     delete_node(old_tail);
    debug_verify_data_integrity();
   }



  /*Delete nth node
  *Example: {1,3,4,5}
  * (index start from 1 not zero)
  * assume index=3
  * new linked list={1,3,5}
  */
  void delet_nth(int index)
  {
     assert(length);
     Node*nth_node=get_nth(index);
     if(index<1||index>length)
     {
        cout<<"out of range!!";
        return;
     }
     
    if(length==1)
    {
        head=tail=nullptr;
        return;
    }
    
     if(nth_node==head)
     {
        delete_front();
        return;
     }
    
    if(nth_node==tail)
       {
        delete_back();
        return;
     }

    
    Node*prv=get_nth(index-1);
    Node*next=get_nth(index+1);
   
    prv->next=next;
    delete_node(nth_node);

   debug_verify_data_integrity();
        
  }



    /*Delete the next node of sepcific node*/
void delete_next_node(Node* node) {
        // Delete the next of the current node
        // Handle if next is tail case
        assert(node);

        Node* to_delete = node->next;
        bool is_tail = to_delete == tail;

        // node->next in middle to delete
        node->next = node->next->next;

        delete_node(to_delete);
        if (is_tail)
            tail = node;
    }



    /*Given a list, delete the first node with the given key value
   *E.g. {1, 2, 3, 4, 2, 6}, key = 2 ⇒ {1, 3, 4, 2, 6}
   */
    void delete_node_with_key(int value)
    {
        Node*cur=head;
        int count;
        for (count=1; cur; cur=cur->next,count++)
        {
            if(cur->data ==value)
            break;
        }
       if(count<=length)
        delet_nth(count);

        else
        cout<<"This value doesn't exsist\n ";

    }



   /*Given a list, delete all nodes at even positions (2, 4, 6, etc)
   *E.g. {1, 2, 3, 4, 10} ⇒ {1, 3, 10}
   */

    void delete_even_positions() {	
		if (length <= 1)
			return;
		// maintain previous and delete its next (even order)
		for(Node *cur = head->next, *prv = head;cur;) {
			delete_next_node(prv);	// prev is odd, prev-next is even
			if (!prv->next)	// tail
				break;
			cur = prv->next->next;
			prv = prv->next;
		}
		debug_verify_data_integrity();
	}


 
    /*Given list of numbers (not sorted), for any repeated number, remove all 
    except the first
    * 1, 2, 1, 3, 2, 4, 3, 5, 2 ⇒ 1, 2, 3, 4, 5
    */
    void delete_duplicate()
   {

    for(Node*value=head;value;value=value->next)
    {
        for(Node*value2=value->next,*prv=value;value2;)
        {
            if(value->data==value2->data)
            {
               delete_next_node(prv);
               value2=prv->next;


            }
            else
            {
            prv=value2;
            value2=value2->next;
            }
        }
        
    }
   }



    /*Given list of numbers (not sorted), and a key: remove the last occurrence for 
    this key
    * Example : 1, 2, 3 - key = 1 ⇒ 2, 3
    */
   	void delete_last_occurrence(int target) {		
		if (!length)
			return;

		Node* delete_my_next_node = nullptr;
		bool is_found = false;

		// Find the last one and remove it

		for (Node *cur = head, *prv = nullptr; cur; prv = cur, cur = cur->next) {
			if (cur->data == target)
				is_found = true, delete_my_next_node = prv;
		}
		if (is_found) {
			if (delete_my_next_node)
				delete_next_node(delete_my_next_node);
			else
				// if prv is null, then found at head
				delete_front();
		}
		debug_verify_data_integrity();
	}



    //////////////////////////////////////////////////////
  
   /*Get the nth item of linked list */
   Node*  get_nth (int n)
   {
    int count=0;
    for(Node*cur=head;cur;cur=cur->next)
     if(++count==n)
     return cur;

    return nullptr; 
   }

   Node* get_nth_back(int n)
   {
    int count=0;
    for(Node*cur=head;cur;cur=cur->next)
     if(++count==1+(length-n))
     return cur;

    return nullptr; 
   }

   
//////////////////////////////////////////////

/*find the index of sepcific value*/
   int search (int value)
   {
    int counter=0;
    for(Node *cur=head;cur;cur=cur->next)
    {
        if(cur->data==value)
        return counter;
        counter++;
    }
    return -1;
   }

    /*find the index of sepcific value then shift it one step to left*/

    /*Example {1,2,3,4,5} 
    *value=2
    * new linked list after using it={1,3,2,4,5}
    */
   int search_improved (int value)
   {
    Node* prv=nullptr;
    int counter=0;
    for(Node *cur=head;cur;cur=cur->next)
    {
        if(cur->data==value)
        {
            if(!prv)
            return counter;

            else
            {
                swap (cur->data,prv->data);
                return counter-1;


            }

        }
         counter++;
            prv=cur;
    }
    return -1;
   }

   ////////////////////////////////////////////

   /*Compare two linked list togther */
   bool is_same(const LinkedList&other)
   {
    if(length==other.length)
    {
        for(Node*L1=head,*L2=other.head;L1;L1=L1->next,L2=L2->next)
        {
            if(L1->data!=L2->data)
            return 0;
        }
        return 1;
    }
    return 0;
   }
   ///////////////////////////////////////////  
  
    /*swap each pair*/

    /*Example {1,2,3,4,5} 
    * new linked list after using it={2,1,4,3,5}
    */
	void swap_pairs() {		
		// For each 2 consecutive, swap data and jump cur->next->next
		for (Node* cur = head; cur; cur = cur->next->next) {
			if(cur->next) {
				swap(cur->data, cur->next->data);
				
			}
		}
	}
 /*to swap head with tail not only the value , the whole node*/
    void nodes_swap ()
    {
        tail->next=get_nth(2);
        get_nth(length-1)->next=head;
        head->next=nullptr;
        swap(head,tail);
    }


   ///////////////////////////////////////////

   /*To reverse the Linked list*/
  void reverse()
  {
  
   for (int counter=length;counter>0;counter--)
    {
        if (counter==1)
        get_nth(counter)->next=nullptr;
        else
	    get_nth(counter)->next=get_nth(counter-1);
	}
    swap(head,tail);

    debug_verify_data_integrity();
  }

    /*take number o elements K and rotate them to left*/
    /*Example {1,2,3,4,5} 
    * when k=2
    * new linked list={3,4,5,1,2}
    */
  void left_rotate(int k)
  {
    Node *new_head=head->next;
    for(int i=k;k>0;k--)
    {
        tail->next=head;
        head->next=nullptr;
        tail=head;
        head=new_head;
        new_head=new_head->next;
    }
  }

   ///////////////////////////////////////////
   /*to delete the whole linked list*/
   ~LinkedList()
   {
     while (head)
     {
        Node * cur=head->next;
        delete head;
        head=cur;
     }
     
   }
    
};

//////////////*those fynctions implemented before implement the Linked list class*////////////////

/*Print the nodes using recursive way*/

void print1(Node*head){

if(head ==nullptr)
{
    return ;

}
cout<<head ->data<<" ";

print1(head->next);

}


/*Print the nodes in reverse way*/
void print2(Node*head){

if(head ==nullptr)
{
    return ;

}

print2(head->next);

cout<<head ->data<<" ";

}


/*Print the nodes usuing while loop*/
void print3(Node*head){

while(head !=nullptr)
{
   cout<<head ->data<<" ";

   head=head->next;

}

}

/*find the node of sepecifiv value*/
Node* find (Node *head,int value){

while (head !=nullptr)
{
    if(head->data==value)
    return head;

    head=head->next;
}

return nullptr;


}



int main(){

/*to test the functions of linked list class*/

}
