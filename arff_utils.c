#include <stdio.h>

#define MAXLINE 5000

int main()
{
   char line[MAXLINE];
   FILE *fp;
   int c;
   int i;

   i = 0;

   if ((fp = fopen("data/hello", "r")) == NULL)
   {
      printf("error opening file!\n");
      return 1;
   }
   else
   {
      while (( c = getc(fp)) != EOF && i < MAXLINE)
      {
         line[i] = c;
         i++;
      }
      printf("here is a line...\n%s", line);
      printf("\n\n");
      fclose(fp);
   }

   return 0;
}
