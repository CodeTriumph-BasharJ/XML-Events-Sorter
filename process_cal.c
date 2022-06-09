/*
Author: Bashar Jirjees
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

#define MAX_NUMBERofLINES 1200
#define MAX_CHARinLINE 400
#define MAX_EVENTS 1200
#define MAX_CHARinDATE 20

/*Defining functions prototypes that are defined explicitly after the main 
function. */
static FILE* FileCheck(char []);
static void readFileandFullDisplay (char [],char [], char []);
static int NumberofLines(char *[]);
static void displayDescription (char *);
static void displayLocation (char *);
static void displayTimeZone (char *);
static void displayDay (char *);
static void displayMonth (char *);
static void displayYear (char *);
static void displayWeek (char *);
static void displayStart (char *);
static void displayEnd (char *);
static void displayDashes ();
static int compare (const void *, const void *);
static void adjustStartDate(char [], char[], char[]);
static void adjustEndDate(char [], char[], char[]);
static void StrLen_Month(long int);
static void Strlen_DayinWeek(long int);
static void Strlen_DayNumbered(long int);
static void Strlen_Year(long int);

static int LinesNumberofDailyEvents(char* [] ,char*[], 
char[MAX_EVENTS][MAX_CHARinDATE], char[MAX_EVENTS][MAX_CHARinDATE]);

static void DataOutput(char* [] ,char*[], char[MAX_EVENTS][MAX_CHARinDATE],
char[MAX_EVENTS][MAX_CHARinDATE]);

static void fullSortDisplay (char *[], char [], char []);
long int Strlen_M_Y_DW_D = 0;


// main function to adjust the passed command line argumets and calls necessary methods.
int main (int argc, char *argv[])
{
 
 char filename[100] = {};  
 char startdate[100] = {}; 
 char enddate[100] = {};  
 strcpy(filename,argv[3] + 7); 
 strcpy(enddate,argv[2] + 10); 
 strcpy(startdate,argv[1] + 12); 


  
  readFileandFullDisplay (filename, startdate, enddate);
  exit (0);
}

//Function to operate the file and check its existence.
static FILE* FileCheck(char filename[])
{
      
  FILE *file;
  file = fopen (filename, "r");	
  if(file == NULL)
  {
    perror("FILE IS EMPTY OR NON-EXISTENT");
    exit(0);
  }
  
  return file;
}

//Function to read the xml file data, parsing and ouputting them.
static void readFileandFullDisplay (char filename[],char startdate[], char enddate[])
{

  int ind1 = 0;
  int ind2 = 0;	
  char apr[MAX_NUMBERofLINES][MAX_CHARinLINE];	
  char *ptr[MAX_CHARinLINE] = { }; 
  int counter = 0; 
  FILE *file = FileCheck(filename); 

  char *temp = NULL;  
  
 
  while (fgets (apr[ind1], sizeof apr[ind1], file) != NULL)	

    {
	  
      //Reading and adjusting description line data.
      if (counter == 2)
	{
	  temp = apr[ind1] + 21;
	  temp[strlen (temp) - 16] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjusitng timezone line data.
      if (counter == 3)
	{
	  temp = apr[ind1] + 18;
	  temp[strlen (temp) - 13] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjusting location line data.
      if (counter == 4)
	{
	  temp = apr[ind1] + 18;
	  temp[strlen (temp) - 13] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjusting day line data.
      if (counter == 5)
	{
	  temp = apr[ind1] + 13;
	  temp[strlen (temp) - 8] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjusting month line data.
      if (counter == 6)
	{
	  temp = apr[ind1] + 15;
	  temp[strlen (temp) - 10] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjsuting year line data.
      if (counter == 7)
	{
	  temp = apr[ind1] + 14;
	  temp[strlen (temp) - 9] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjusting weekday line data.
      if (counter == 8)
	{	
	  temp = apr[ind1] + 15;
	  temp[strlen (temp) - 10] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjusting start-time line data.
      if (counter == 9)
	{
	  temp = apr[ind1] + 15;
	  temp[strlen (temp) - 10] = '\0';
	  ptr[ind2++] = temp;
	}
	  
      //Reading and adjusting end-time line data.
      if (counter == 10)
	{
	  temp = apr[ind1] + 13;
	  temp[strlen (temp) - 8] = '\0';
	  ptr[ind2++] = temp;
	  counter = -1;	
	}
      ++counter; 
      ++ind1;
    }
   
  
    fclose (file); 
    fullSortDisplay (ptr, startdate, enddate);
}


/* Function to count the number of lines in the file without the 2 tags between
 * each event or at the beginning or end of the file.
 */
static int NumberofLines(char *arr[]){
    
    int ind_counter = 0;
    while(arr[ind_counter] != NULL){
    ++ind_counter;
    }
    return ind_counter;
}

//Function to display descriptions.
static void
displayDescription (char *des)
{
  printf ("%s ", des);
}

//Function to display locations.
static void
displayLocation (char *loc)
{
  printf ("{{%s}}", loc);
}

//Function to display timezones.
static void
displayTimeZone (char *timz)
{
  printf (" | %s", timz);
}

//Function to display day number in each month.
static void
displayDayNumbered (char *day)
{
  long int Len = 0;
  Len = strlen(day) + 2; //Storing the length of event's weekday name.
  Strlen_DayNumbered(Len);
  printf ("%s, ", day);
}

//Function to display month.
static void
displayMonth (char *monthNum)
{
  char temp [20] = {};
  long int Len = 0;
  char *months[12] = {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December" };

  Len = strlen(months[atoi(monthNum) - 1]) + 1; /* Storing the length of the event's 
  					           month. */
  StrLen_Month(Len);
  printf ("%s ", months[atoi(monthNum) - 1]);
}

//Function to display year.
static void
displayYear (char *year)
{
  long int Len = 0;
  Len = strlen(year) + 1; //Storing the length of the event's year.
  Strlen_Year(Len);
  printf ("%s ", year);
}

//Function to display weekday.
static void
displayDayinWeek (char *Dweek)
{
  long int Len = 0;
  Len = strlen(Dweek) + 2; //Storing the length of the weekday.
  Strlen_DayinWeek(Len);
  printf ("(%s)", Dweek);
}

//Function to display start-time in 12-hour format.
static void
displayStart (char *start)
{
  if (strtol (start, NULL, 10) == 0)
    {
      printf ("%li%s AM to", strtol (start, NULL, 10) + 12, start + 2);
    }
  else if (strtol (start, NULL, 10) > 12 && strtol (start, NULL, 10) < 22)
    {
      printf ("0%li%s PM to", strtol (start, NULL, 10) - 12, start + 2);
    }
  else if (strtol (start, NULL, 10) >= 22 && strtol (start, NULL, 10) < 24)
    {
      printf ("%li%s PM to", strtol (start, NULL, 10) - 12, start + 2);
    }
  else if (strtol (start, NULL, 10) == 12)
    {
      printf ("%li%s AM to", strtol (start, NULL, 10), start + 2);
    }
  else if (strtol (start, NULL, 10) < 10)
    {
      printf ("0%li%s AM to", strtol (start, NULL, 10), start + 2);
    }
  else if (strtol (start, NULL, 10) >= 10 && strtol (start, NULL, 10) < 13)
    {
      printf ("%li%s AM to", strtol (start, NULL, 10), start + 2);
    }
}

//Function to display end-time in 12-hour format.
static void
displayEnd (char *end)
{
  if (strtol (end, NULL, 10) == 0)
    {
      printf (" %li%s AM: ", strtol (end, NULL, 10) + 12, end + 2);
    }
  else if (strtol (end, NULL, 10) > 12 && strtol (end, NULL, 10) < 22)
    {
      printf (" 0%li%s PM: ", strtol (end, NULL, 10) - 12, end + 2);
    }
  else if (strtol (end, NULL, 10) >= 22 && strtol (end, NULL, 10) < 24)
    {
      printf (" %li%s PM: ", strtol (end, NULL, 10) - 12, end + 2);
    }
  else if (strtol (end, NULL, 10) == 12)
    {
      printf (" %li%s PM: ", strtol (end, NULL, 10), end + 2);
    }
  else if (strtol (end, NULL, 10) < 10)
    {
      printf (" 0%li%s AM: ", strtol (end, NULL, 10), end + 2);
    }
  else if (strtol (end, NULL, 10) >= 10 && strtol (end, NULL, 10) < 13)
    {
      printf (" %li%s AM: ", strtol (end, NULL, 10), end + 2);
    }
}

//Function to store the event's month length of chars.
static void StrLen_Month(long int mo){
    Strlen_M_Y_DW_D += mo;
}

//Function to store the event's weekday length of chars.
static void Strlen_DayinWeek(long int dw){
    Strlen_M_Y_DW_D += dw;
}

//Function to store the event's month's day length of integers.
static void Strlen_DayNumbered(long int dn){
    Strlen_M_Y_DW_D += dn;
}

//Function to store the length of the event's year in integers.
static void Strlen_Year(long int ye){
    Strlen_M_Y_DW_D += ye;
}

//Function to display dashes.
static void displayDashes ()
{
  printf("\n");
  for(long int i = 0; i < Strlen_M_Y_DW_D; ++i)
  {
    printf ("-");
  }
  printf("\n");
  
  Strlen_M_Y_DW_D = 0; /* Resetting the length to zero for storing next event
                          date length. */
}


//Function to comapre to charcters and return which on is bigger than the other.
static int
compare (const void *str1, const void *str2)
{
  const char *str1_2 = *(const char **) str1;
  const char *str2_2 = *(const char **) str2;
  return strcmp (str1_2, str2_2);
}

//Function to store the given start date day and month values.
static void adjustStartDate(char startdate[], char daySt[], char monthSt[]) {

int ind = 0, ind2 = 0; 
int counter = 0; 


for(int i = 0; i < strlen(startdate); ++i){
   if(startdate[i] == '/') {
   ind = i + 1;
   ++counter;
}
   if(counter == 1 && startdate[ind] != '/'){
     monthSt[ind2] = startdate[ind];
     ++ind;
     ++ind2;
}	
}
--ind;
ind2 = 0;
counter = 0;
int ind3 = 0; 


for(int j = ind; j < (strlen(startdate)); ++j){
   if(startdate[j] == '/'){
      ind3 = j + 1;
      ++counter;
  }
   if(counter > 0){
   daySt[ind2] = startdate[ind3];
   ++ind2;
   ++ind3;
  }   
 }
}

//Function to store the needed end date day and month.
static void adjustEndDate(char enddate[], char dayEn[], char monthEn[]){

int ind = 0, ind2 = 0; 
int counter = 0; 


for(int i = 0; i < strlen(enddate); ++i){
   if(enddate[i] == '/') {
    ind = i + 1;
    ++counter;
 } 
   if(counter == 1 && enddate[ind] != '/'){
    monthEn[ind2] = enddate[ind];
    ++ind;
    ++ind2;
 }
}

--ind;
ind2 = 0;
counter = 0;
int ind3 = 0;// Array index.


for (int j = ind; j < (strlen(enddate)); ++j){
   if(enddate[j] == '/'){
      ind3 = j + 1;
      ++counter;
}
   if(counter > 0){
     dayEn[ind2] = enddate[ind3];
     ++ind2;
     ++ind3;
  }
 }
}

//Function to display the desired output.
static void DataOutput(char *Combined_Sorted_Month_Day[],char* arr[],
char tempArr2 [MAX_EVENTS][MAX_CHARinDATE],
char tempArr3[MAX_EVENTS][MAX_CHARinDATE]){
 
  /** 
   *Storing incorrect extra data in the last slots for month and day in the 
   *agray of events to avoid logical errors when reading the data for the latest
   *egents in the file that might get skipped while reading. 
   */
  arr[NumberofLines(arr) + 4] = "13";
  arr [NumberofLines(arr) + 3] = "32";
  
  int ind3 = 4;	
  int ind2 = 0;	    
  int counter = 0; 
  int counter2 = 0; 
  
  int counter3 = 0; 
 
      while(Combined_Sorted_Month_Day[ind2] != NULL && arr[ind3] != NULL)

    {   
        while ((atoi(Combined_Sorted_Month_Day[ind2]) == atoi(arr[ind3])) &&
	(atoi(tempArr2[ind2]) == atoi(arr[ind3 - 1]))
	&& (atoi(tempArr3[ind2]) != atoi(tempArr3[ind2 + 1])))

	{

     if (counter == 0)
	    {
	      if(counter2 > 0) printf ("\n");
	      displayMonth (arr[ind3]);
	      displayDayNumbered (arr[ind3 - 1]);
	      displayYear (arr[ind3 + 1]);
	      displayDayinWeek (arr[ind3 + 2]);
	      displayDashes ();
	      ++counter;
	      ++counter2;
	    }
	      displayStart (arr[ind3 + 3]);
	      displayEnd (arr[ind3 + 4]);;
	      displayDescription (arr[ind3 - 4]);
	      displayLocation (arr[ind3 - 2]);
	      displayTimeZone (arr[ind3 - 3]);
	      ++counter3;

          if(counter3 != LinesNumberofDailyEvents(Combined_Sorted_Month_Day,
          arr, tempArr2,tempArr3)) printf("\n");

	  if (arr[ind3] != NULL)
	  ind3 += 9; 
	  
	  if (arr[ind3] == NULL)
	    {
	      break;  
	    }
	}

     if(arr[ind3] != NULL)
          ind3 += 9;  
        
      if (arr[ind3 + 9] == NULL)
	{
	      ind3 = 4;
	      ++ind2;
	      counter = 0;
	}
    }
}

//Function to count the total number of events with each day.
static int LinesNumberofDailyEvents(char *Combined_Sorted_Month_Day[],char* arr[],
char tempArr2[MAX_EVENTS][MAX_CHARinDATE],
char tempArr3[MAX_EVENTS][MAX_CHARinDATE]){
    
 
  arr[NumberofLines(arr) + 4] = "13";
  arr [NumberofLines(arr) + 3] = "32";
  
  int ind3 = 4;	
  int ind2 = 0;	
  int counter = 0; 
  int counter2 = 0; 
  int counter3 = 0; 

      while (Combined_Sorted_Month_Day[ind2] != NULL && arr[ind3] != NULL)

    {
    
      while ((atoi(Combined_Sorted_Month_Day[ind2]) == atoi(arr[ind3])) &&
	        (atoi(tempArr2[ind2]) == atoi(arr[ind3 - 1]))
	        && (atoi(tempArr3[ind2]) != atoi(tempArr3[ind2 + 1])))
	{
	 
     if (counter == 0)
	    {
	       ++counter;
	      
	    }
	       ++counter3;
      

	  if (arr[ind3] != NULL)
	  ind3 += 9; 
	  
	  if (arr[ind3] == NULL)
	    {
	      break;
	    }
	}
	  if(arr[ind3] != NULL)
      ind3 += 9;  
        
      if (arr[ind3 + 9] == NULL)
	{
	      ind3 = 4;
	      ++ind2;
	      counter = 0;
	}
  }
  return counter3; 
}

//Function to sort display functions in the needed format.
static void fullSortDisplay (char *arr[], char startdate[], char enddate[])
{
  int ind1 = 0, ind2 = 0, ind3 = 0, ind4 = 0; 
  char *day[MAX_EVENTS];     
  char *month[MAX_EVENTS];  
  int counter = 0;	
  char Non_Sorted_Month_Day[MAX_CHARinDATE]; 
  
  char *Combined_Sorted_Month_Day[MAX_EVENTS];	
  
  char *Sorted_Month[MAX_EVENTS]; 
  
  char tempArr[MAX_EVENTS][MAX_CHARinLINE];  
  
  char tempArr2[MAX_EVENTS][MAX_CHARinDATE]; 
  
  char tempArr3[MAX_EVENTS][MAX_CHARinDATE]; 

  char tempLast_Event[MAX_CHARinDATE][MAX_CHARinDATE]; 

char daySt[100] ={};
char monthSt[100] = {};
char dayEn[100] = {}; 
char monthEn[100] = {}; 

adjustStartDate(startdate, daySt, monthSt); 
adjustEndDate(enddate, dayEn, monthEn); 
ind1= ind2 =0;

  
  while (arr[ind1] != NULL)

  {   
     if (atoi(arr[ind1 + 4]) == atoi(monthSt) &&  atoi(arr[ind2 + 3]) >= atoi(daySt)){
     	
	month[ind3++] = arr[ind1 + 4];
      	day[ind4++] = arr[ind2 + 3];

     } else if (atoi(arr[ind1 + 4]) == atoi(monthEn) && atoi(arr[ind2 + 3]) <= atoi(dayEn)){
	
	month[ind3++] = arr[ind1 + 4];
        day[ind4++] = arr[ind2 + 3];

     } else if(atoi(arr[ind1 + 4]) > atoi(monthSt) && atoi(arr[ind1 + 4]) < atoi(monthEn)){
	
	month[ind3++] = arr[ind1 + 4];
        day[ind4++] = arr[ind2 + 3];	

     }	     
         ind1 += 9;
         ind2 += 9;
  }

  
  if(month[0] == NULL || day[0] == NULL) 
     
     exit(0); 


  ind1 = 0; 

  while (day[ind1] != NULL && month[ind1] != NULL)
    {
     sprintf (Non_Sorted_Month_Day, "%s%s", month[ind1], day[ind1]);
     strcpy (tempArr[ind1], Non_Sorted_Month_Day);
     Combined_Sorted_Month_Day[ind1] = tempArr[ind1];
     
     if (day[ind1 + 1] == NULL && month[ind1 + 1] == NULL)
     
          
         strcpy (tempLast_Event[0], tempArr[ind1]);
 
     ++ind1;
    }


  qsort (Combined_Sorted_Month_Day, ind1, sizeof (char *), compare);

  ind1 = 0;	//Setting array index to zero.


  while (Combined_Sorted_Month_Day[ind1] != NULL)
    {

      strcpy (tempArr2[ind1], Combined_Sorted_Month_Day[ind1] + 2 );     
      ++ind1;
    }

  ind1 = 0;


  while (Combined_Sorted_Month_Day[ind1] != NULL)
    {
      strcpy (tempArr3[ind1], Combined_Sorted_Month_Day[ind1]);    
      ++ind1;
    }
   
  ind1 = 0 ;  

  
  while (Combined_Sorted_Month_Day[ind1] != NULL)
    {
        

    Combined_Sorted_Month_Day[ind1][strlen (Combined_Sorted_Month_Day[ind1])
    - 2] = '\0'; 
    ++ind1;

    }

   
    LinesNumberofDailyEvents(Combined_Sorted_Month_Day,arr,tempArr2,tempArr3);
    
    DataOutput(Combined_Sorted_Month_Day,arr,tempArr2,tempArr3);

}

