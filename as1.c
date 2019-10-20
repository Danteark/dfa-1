#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLEN 20

/*Given struct represents a node in Deterministic Finite Automata(DFA) 
  start variable is '1' if the node is start state in the DFA and '0' otherwise
  final variable is '1' if the node is final state in the DFA and '0' otherwise
  struct Node_tag *a is a pointer to the next node. It represents the transition we are supposed to take when we encounter 'a'
  struct Node_tag *b is a pointer to the next node. It represents the transition we are supposed to take when we encounter 'b'
  struct Node_tag *c is a pointer to the next node. It represents the transition we are supposed to take when we encounter 'c'
*/
typedef struct Node_tag{
  int start;
  int final;
  struct Node_tag *a;
  struct Node_tag *b;
  struct Node_tag *c;
 }Node;


// making DFA connections with all transitions. 
Node *makeConnections1(Node *start)
 {
    Node *st = start;
    Node *a = (Node *)malloc(sizeof(Node));
    Node *b = (Node *)malloc(sizeof(Node));
    Node *c = (Node *)malloc(sizeof(Node));
    Node *aa = (Node *)malloc(sizeof(Node));
    Node *bb = (Node *)malloc(sizeof(Node));
    Node *cc = (Node *)malloc(sizeof(Node));
    Node *qd = (Node *)malloc(sizeof(Node));
    
    st->a = a;
    st->b = b;
    st->c = c;

              
    a->start = 0;
    a->final = 0;
    a->a = aa;
    a->b = qd;
    a->c = qd;

    b->start = 0;
    b->final = 0;
    b->a = qd;
    b->b = bb;
    b->c =qd;

    c->start = 0;
    c->final = 0;
    c->a = qd;
    c->b =qd;
    c->c = cc;

    aa->start = 0;
    aa->final = 1;
    aa->a = a;
    aa->b = b;
    aa->c = c;

    bb->start = 0;
    bb->final = 1;
    bb->a = a;
    bb->b = b;
    bb->c = c;

    cc->start = 0;
    cc->final = 1;
    cc->a = a;
    cc->b = b;
    cc->c = c;

    qd->start = 0;
    qd->final = 0;
    qd->a = qd;
    qd->b = qd;
    qd->c = qd;

  return st;

 }
  //function to check is the given string[] is accepted by the DFA or not
  // returns 1 if DFA accepts string[] and 0 otherwise
  int Check1( char string[] , Node *start )
  {
	char str_dup[MAXLEN];
	strcpy(str_dup , string);
	int i =0;
	Node *state = start;

	while(str_dup[i] != '\0' )
		{
			switch( str_dup[i] )
				{
					case 'a' : state = state->a;
							break;
					case 'b' : state = state->b;
							break;
					case 'c' : state = state->c;
							break;
					default : return 0;
				}
                       i++;
		}

	if(state->final == 0)
             return 0;
         else 
              return 1;
         
  }
 //input is taken through in1.txt and output is stored in out1.txt
//sample input file is in the repository
 void main()
 {
    FILE *fpw,*fpr;
    char str[MAXLEN] = "NULL";
    char endchar[4] = "end";
     int chk =0;
     int flag =1;
    Node *st = (Node *)malloc(sizeof(Node));
    fpw = fopen("/home/aman/Desktop/out1.txt" , "a");
    fpr = fopen("/home/aman/Desktop/in1.txt","r");
    	st->start = 1;
    	st->final = 1;
    	
    st = makeConnections1(st);
   
    if(fpr==NULL){
        printf("\nUnable to open file\n");
        }
    else
       {
           while(flag != 0)
                   {       str[0] = '\0';
                            fscanf(fpr , "%s" ,str );
			 if(strcmp(str,endchar) ==0)
                              {
                                   flag = 0;
                              }

			chk = Check1(str,st);
         		if(chk == 1 && flag == 1)
              			fprintf(fpw ,"\nacceptable string\n");
         		else if(chk ==0 && flag ==1)
             			fprintf(fpw,"\nUnacceptable string\n");
                     }
       }
          
      fclose(fpw);
      fclose(fpr);

 }
