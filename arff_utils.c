#include <stdio.h>
#include <string.h>

#define MAXLINE 8192

void process_quoted_attribute(char *line);
void process_unquoted_attribute(char *line);


/****************************************
 * http://weka.wikispaces.com/ARFF+%28book+version%29
 *
 *
 */

/* We use fscanf, from stdio.h, which is formatted data input.
 * Page 162 of Advanced Programming in the UNIX Environment, 3rd.
 * Any line that begins with % is a comment.
 * The @relation, @attribute, and @data are case insensitive.
 *
 * ARFF Header Section * Example Attribute Line: 
 * @attribute NumberOfAdults {0,1,2,'3 or more'}
 *
 * ARFF Data Section
 *
 */

int main()
{
   char line[MAXLINE];
   memset(line, 0, sizeof(line));
   FILE *fp;
   int count = 0;
   
   if ((fp = fopen("/home/krw/data/training_subsetD.arff", "r")) == NULL)
   {
      printf("error opening file!\n");
      return 1;
   }
   else
   {
      /* While there are lines in the file. */
      while (fgets(line, MAXLINE, fp) != NULL)
      {
         /* If line is an attribute. */
         if ( strncmp("@attribute", line, 10) == 0 )
         {
            /* Process quoted attribute. */
            if ( line[11] == '\'' )
            {
               printf("QUOTED!\n");
               process_quoted_attribute(line);
            }
            /* Process unquoted attribute. */
            else
            {
               printf("UNQUOTED!\n");
               process_unquoted_attribute(line);
            }
         }
         /* Else if has more than 20 chars, then data line. */
         else if ( strlen(line) > 20 )
         {
            count++;
         }
      }

      printf("data lines: %d\n", count);
      
/*
      while (( c = getc(fp)) != EOF && i < MAXLINE)
      {
         line[i] = c;
         i++;
         if ( c == '\n' )
         {
            if ( strncmp(attr_str, line, 10) == 0 )
            {
               printf("\n\nFOUND ATTRIBUTE!\n");
               printf("%s", line);
            }

            i = 0;
            memset(line, 0, sizeof(line));
         }
      }
*/

      fclose(fp);
   }

   return 0;
}

void process_unquoted_attribute(char *line)
{
   char *str1;
   char *tok;
   str1 = strstr(line, "{");
   char *tokens[100] = {'\0'};
   int counter = 0;
   
   printf("LINE: %s\n\n", line);
   printf("STR1: %s\n\n", str1);

   tok = strtok(str1, ",");
   tok += 1; /* move 1 ahead to move passed the { char */
   tokens[counter++] = tok;
   while ( (tok = strtok(NULL, ",")) )
   {
      char *tmp;
      tmp = tok;

      /* walk through to find last } and change to 0. */
      while ( *tmp != '\n')
         tmp += 1;
      tmp = tmp - 1;
      *tmp = 0;

      tokens[counter++] = tok;
   }
   printf("\n\nhere they are\n\n");
   int i = 0;
   for ( i = 0; i < 10; i++ )
   {
      if ( tokens[i] != '\0' )
         printf("tokens[%d] = %s\n", i, tokens[i]);
      else
         break;
   }
   printf("\n\n\n");
}

void process_quoted_attribute(char *line)
{
   printf("%s", line);
}
