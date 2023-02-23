// listType.cpp				S.W. Smith

// For priorityQueue version 2 (current assignment), use single pointers, please.
// We will port it to double pointers for version 3.

#ifndef LISTTYPE_FLAG
#define LISTTYPE_FLAG
#include <iostream>
using namespace std;

template <class elementType>
class listType
{
	private:
		// the definition of the struct nodeType is private
		struct nodeType
		{
			elementType payLoad;
			int priority;
			nodeType* next;

			nodeType()
			{
				next=NULL;
				priority = 0;

				return;
			}
		};

		nodeType *root = NULL;
		nodeType **envPtr; // double Pointer!!!  (This is new.)

		bool isEmpty() {
			return root == NULL;
		}
		//**************************************
		// wrapper method for create()

		void altCreate(nodeType *p) // version with the recursion at end of the logic.
		{
			if( p )
			{
				nodeType *q;
				q=p->next; // maybe q is NULL, maybe not.

				p->next=NULL;
				delete p;
				altCreate( q );
			}

			return;
		}

		//***********************************
		// wrapper method for print()
		void altPrint(nodeType *p)
		{
			if(p)
			{
				cout<<p->payLoad << "       " << p->priority << '\n'; 
				altPrint(p->next);
			}

			return;
		}
		//************************************
	public:
		listType()
		{
			root=NULL;
			envPtr=NULL;

			return;
		} // constructor.

		//******************************

		~listType()
		{
			altCreate(root); // this deletes an existing list

			return;
		} // destructor.

		//******************************

		void create()
		{
			altCreate(root);
			root=NULL;

			return;
		}

		//******************************

		bool isRoom()
		{
			// There is no standard way to do this with 100% certainty.
			// Here is one approach:

			nodeType *p;
			p=new nodeType;
			if( p ) // allocation failure returns NULL pointer
			{
				delete p;
				return true;
			}
			else return false;

		}

		//******************************

		void enqueue(elementType &e)
		{
			nodeType *p;
			p = new nodeType;
			p->payLoad = e;
			if (isThere(e))
			{
				// Set p to eqaul envPtr values
				p->payLoad = (*envPtr)->payLoad;
				p->priority = (*envPtr)->priority;
				// remove
				remove(e);
				// increment
				++p->priority;
				// isThere(e) to set envPtr correctly
			}
			isThereSorted(e, p->priority);
			put(p->payLoad, p->priority);
		}

		//****************************************

		elementType dequeue()
		{
			nodeType *temp;
			if(!isEmpty()) {
				temp = root;
				root = root->next;
			}

			return temp->payLoad;
		}

		//****************************************
		bool isThere(elementType &e) // This method has significant changes
		{
			envPtr=&root;
			
			while( *envPtr  &&   (*envPtr)->payLoad != e) {
				envPtr=&(*envPtr)->next;
			}
			return *envPtr && (*envPtr)->payLoad == e;
		}
		bool isThereSorted(elementType &e, int &f) // This method has significant changes
		{
			envPtr=&root;
			while( *envPtr  &&   (*envPtr)->priority > f) {
				envPtr=&(*envPtr)->next;
			}
			if(*envPtr && (*envPtr)->priority == f && (*envPtr)->next != NULL) {
				//nodeType *temp; temp = (*envPtr)->next;
				while((*envPtr)->payLoad > e && (*envPtr)->next != NULL) {
					envPtr=&(*envPtr)->next;
				}
			}
			return *envPtr && (*envPtr)->payLoad == e;
		}

/*
		// This is analogous to:
			nodeType *p=root;

			while( p && p->payload<e )
				p=p->next;

			return p && p->payload == e;

		// except this logic leaves envPtr set to the list pointer where it
		// either found it or where it goes.
*/

		//******************************

		void put(elementType &e, int &f)
		{
			// I should check isRoom() here.  Not sure what I'd do
			// if it failed to allocate.  I suppose ask the user?

			// inserting a node into a linked list:
			nodeType *p;
			p=*envPtr;
			*envPtr=new nodeType;
			(*envPtr)->payLoad=e;
			(*envPtr)->priority=f;
			(*envPtr)->next=p;
			
		}


		//******************************

		void remove(elementType &e)
		{
			if(isThere(e)) {
				nodeType *p;
				p=*envPtr;
				*envPtr = (*envPtr)->next;

				p->next=NULL;
				delete p;
			}
		}

		//******************************

		void print() // for diagnostics only
		{
			cout << "  Payload\tPriority" << endl;
			cout<<"*********************\n";
			
			altPrint(root);

			cout<<"*********************\n";
			return;
		}


};
#endif

