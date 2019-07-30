#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    return (char)(32 + rand() % (( 126 + 1 ) - 32));
}

void inputString(char string[])
{
    int length = (rand() % 6) + 3; //string between 3-8 characters long

    for(int i = 0; i < length; i++){
      string[i] = inputChar();
    }
    string[length] = '\0'; //add a null terminator
}

void testme()
{
  int tcCount = 0;
  char string[10];
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    memset(string, '0', 10);
    inputString(string);
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, string, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (string[0] == 'r' && string[1] == 'e'
       && string[2] == 's' && string[3] == 'e'
       && string[4] == 't' && string[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
