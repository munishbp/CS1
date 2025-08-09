/*COP 3502C Assignment 2
This program is written by: Munish Persaud*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 12

typedef struct customer{
  char name[16];
  int numSmoothie; 
  int lineNum; 
  int timeEnter;
}customer; 

typedef struct node{
  customer* data;
  struct node* next;
}node;

typedef struct queue{
  node* front;//front of queue is also head of linked list
  node* back;
}queue;

queue* init(int array[])//makes from and rear pointers of the queue NULL
{
  queue* queue=malloc(SIZE*sizeof(queue)); 
  queue->front==NULL; 
  queue->back==NULL;

  return queue; 
}

node* EnQueue(customer *ptr, int i,queue*queue, int array[])//creates new node, then adds to tail by making the previous node point to temp and temp->next point to NULL
{
  node* newNode=malloc(sizeof(node)); 
  newNode->data=ptr; 
  newNode->next=NULL; 
  if(queue->front==NULL)
  {
    queue->front=newNode; 
    queue->back=newNode->next; 
  }
  else
  {
    queue->back->next=newNode; 
    queue->back++; 
  }

  return newNode; 
}

node* DeQueue(queue*queue,int array[])//removes node from the head 
{
  node*temp=queue->front; 
  if (queue->front==NULL)
  {
    //put something here 
  }
  else
  {
    queue->front=queue->front->next; 
    queue->back=queue->back->next; 
  }
  free(temp); 
}

queue* Empty(struct queue*array[],int i)//checks the queue to see if its empty. Returns 1 if empty, 0 if not. 
{
  if (array[i]->front!=NULL)
  {
    return 1; 
  }
  else
  {
    return 0; 
  }
}

queue* Peek(struct queue* queue,int array[])//looks at front of line without removing
{
  if (Empty==0)
  {
    return queue->front->data; 
  }
  else return 1; 
}


customer* createCustomer(queue*queue, int n)//creates customer by using struct
{
  customer* newCustomer = (customer*)malloc(sizeof(customer)*n);
  struct queue*lines[SIZE];
  for(int i=0; i<SIZE;i++){
    init(lines[i]); 
  }

  for(int i=0; i<n; i++)
  { 
    scanf("%d",&newCustomer[i].timeEnter);//why ampersand?
    scanf("%d",&newCustomer[i].lineNum);
    scanf("%s",newCustomer[i].name);//why no amerpersand?
    scanf("%d",&newCustomer[i].numSmoothie);
    lines[newCustomer[i].lineNum-1]=EnQueue(newCustomer, i,queue, lines[SIZE]);
  }
  return newCustomer; 
  return lines; 
}

queue* checkoutCustomer(queue* array[])//start from scratch logic is wrong
//if curTime is less than 100, pick first customer
//update curTime with first customer
//check if time is less than 100 and then take lowest value from front pointer for the queues
//once time is at or greater than 100 you process by the lowest number of smoothies
//to tranverse the array, take index 0 as lowest, if next index is lower it becomes the new lowest
//do this till end of array and print the details of the array index's queue front then dequeue and restart
{
  int curTime=0; 
  int correctIndex=0; 
  if(curTime=0){}

  if(curTime<100){
    int compareArray[SIZE];
    for(int i=0; i<SIZE;i++){
        if(Empty(array[i],i)!=1){
          compareArray[i]+=array[i]->front->data->timeEnter; 
        }
        else if(Empty(array[i], i)==1){
          compareArray[i]+=999999;
        }
    }

    for(int i=0; i<SIZE-1;i++){
      int lowestTime=compareArray[0];
      if(compareArray[i+1]<lowestTime){
        lowestTime=compareArray[i+1];
      }
           
      else if(compareArray[i+1]=lowestTime){
        lowestTime=lowestTime; 
      }
  
      else if(compareArray[i+1]>lowestTime){
        lowestTime=lowestTime;
      }
      correctIndex=i+1;
      curTime+=(lowestTime+30+(array[correctIndex]->front->data->numSmoothie*5));
      printf("At time %d, %s left the counter from line %d.",curTime,array[correctIndex]->front->data->name,array[correctIndex]->front->data->lineNum);
      Dequeue(array[correctIndex]->front); 
    }
  }
}
 

int main(void) {
  queue*queue; 
  customer*customerptr; 
  int testcases=0; 
  scanf("%d",&testcases); 
  for (int i=0; i<testcases; i++){
    printf("test cases worked");
    int customerNum; 
    scanf("%d",&customerNum);
    customer* createCustomer(queue, customerNum); 
  }
}