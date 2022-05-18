
#include <stdio.h>
#include <ctype.h>  // for tolower
#include <string.h>
#include <stdlib.h>

#define SIZE 30
#define fieldLength 200

#define optimalH 120
#define optimalL 80
 

struct db_type
{
   char name[fieldLength];
   
   int age;

   float high;
   float low;
   float risk;
};

 
char prompt_menu(void);
void enterNew(struct db_type * pArr[]);  
void init_list(struct db_type * pArr[]); 
void displayDB(struct db_type * pArr[]);   
void sort(struct db_type * pArr[]);
void swap(struct db_type * pArr[]); 
void removeRecord(struct db_type * pArr[]);
void clearDB(struct db_type * pArr[]);



int main(int argc, char *argv[])
{
    
    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL
    
    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;
        
         case 's': sort(db_pArr); break;
	   
         case 'c': clearDB(db_pArr); break;  
        
         case 'p': swap(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;
         
         case 'q': exit(1); // terminate the whole program
       }
	
     }
     return 0;
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("Swa(p) records\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay db\t|\n");
  
   // printf("|    %-20s","(L)oad disk");
   // printf("%-20s","(W)rite disk");
   // printf("(E)mpty disk\t|\n");
  
   
    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");
  
    fgets(s,50, stdin); // \n added
    //scanf("%s", s);  
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s))) 
       return tolower(*s); // s[0], return the first character of s  
    //else
    printf("not a valid input!\n");
	 
 }
}


void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  { 
     pArr[t]= NULL;
  }
}

void clearDB(struct db_type * pArr[]){
   char c3[3];
   printf("are you sure to clear db? (y) or (n)? ");
    
   fgets(c3,3,stdin);
   
   // complete the function by calling init_list();
   //if user inputted y then only database will be cleared
   if(strcmp(c3,"y\n")==0){
    init_list(pArr);
   }
}

//item variable is globaly declared so that it can be used in display function
int item = 0;

/* input items into the db */
void enterNew(struct db_type * pArr[SIZE]){
  char new[fieldLength];

  //creating array using dynamic memory allocation
  pArr[item] = malloc(sizeof(struct db_type));
  printf("name: ");
  if(fgets(new,fieldLength,stdin) != NULL){
  strcpy((*pArr[item]).name,new); //string copied to pArr
  }
  else exit(0);
  printf("age: ");
  if(fgets(new,fieldLength,stdin) == NULL)
  exit(0);
  (*pArr[item]).age = atoi(new); //atoi converts string type arguement into int
  printf("high bp: ");
  if(fgets(new,fieldLength,stdin) == NULL)
  exit(0);
  (*pArr[item]).high = atof(new); //atof converts string type arguement into float
  printf("low bp: ");
  if(fgets(new,fieldLength,stdin) == NULL)
  exit(0);
  (*pArr[item]).low = atof(new);

  //Declaring variables for high bp and low bp to compare further
  float hBP = (*pArr[item]).high;
  float lBP = (*pArr[item]).low;

  if(hBP <= optimalH && lBP <= optimalL){
    (*pArr[item]).risk = 0;
  }
  else if((hBP <= 130 && lBP <= optimalL) || (hBP <= optimalH && lBP <= 90)){
    (*pArr[item]).risk = 1;
  }
  else if(hBP <= 130 && lBP <= 90){
    (*pArr[item]).risk = 2;
  }
  else if((hBP <= 140 && lBP <= optimalL) || (hBP <= optimalH && lBP <= 100)){
    (*pArr[item]).risk = 3;
  }
  else if(hBP <= 140 && lBP <= 100){
    (*pArr[item]).risk = 4;
  }
  else 
  (*pArr[item]).risk = 5;

  //Age above 50 case:
  if((*pArr[item]).age > 50 && !(hBP <= optimalH && lBP <= optimalL)){
    (*pArr[item]).risk = (*pArr[item]).risk + 0.5;
  }

  item++;
}


/* remove an existing item from the db */
void removeRecord (struct db_type * pArr[])	{
  
}

/* display all records. Generate output with the same formaing as the sample output 
 use \t to align well
*/
void displayDB(struct db_type * pArr[]){
  
  printf("===============================\n\n");
  int x = 0;
  while(x < item){ //loop will run till last element
    printf("name: \t%s",(*pArr[x]).name);
    printf("age: \t%d\n",(*pArr[x]).age);
    printf("bp: \t%.2f %.2f\n", (*pArr[x]).high, (*pArr[x]).low);
    printf("risk: \t%.1f\n\n",(*pArr[x]).risk);
    x++;
  }
  printf("========== %d records ==========\n",item);
 
}

/* swap the adjacent records */
void swap(struct db_type * pArr[]){
  int x = 0;
  while(pArr[x+1]!=NULL){ //while loop will run till the last element of pArr be NULL
    struct db_type* tmp = malloc(sizeof(struct db_type)); //Memory allocation to store the swaped array temporarily
    tmp = pArr[x];
    pArr[x] = pArr[x+1];
    pArr[x+1] = tmp;
    x = x+2; //We are swaping 2 members at a time so x will be incremented by 2 so that next two element can be swaped.
  }
} 

 
// sort the record, either by name or risk factor, prompt use for choice
void sort(struct db_type * pArr[])
{
 
}

