#include<stdio.h>
#include<string.h>

void expand(char *s1,char *s2);

int main(void)
{
    char *s[] = {  "1-9-1","5-5","a-z-", "z-a-", "-1-6-",
                  "a-ee-a", "a-R-L", NULL };
    char result[100] ;
    int i = 0;

    while(s[i]){
        expand(result,s[i]);
        printf("original string is %s \n",s[i]);
        printf("expanded string is %s \n",result);
        ++i;
    }
    return (0);
}

void expand(char *s1,char *s2){
 
 char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 char lower[] = "abcdefghijklmnopqrstuvwxyz";
 char digit[] = "0123456789" ;

 char * start,*end,*p;

 int i,j;
 i = j = 0;
 while(s2[i])
    {
        switch(s2[i]){
            case '-' :
                   if(i == 0 || s2[i + 1 ] == '\0'){
                    s1[j++] = '-';
                    ++i;
                    break;
                   }
                   else {
                    if((start = strchr(upper,s2[i-1]))&&(end = strchr(upper,s2[i+1])));
                    else if((start = strchr(lower,s2[i - 1])) && (end = strchr(lower,s2[i +1])));
                    else if((start = strchr(digit,s2[i - 1]))&&(end = strchr(digit,s2[i + 1])));
                    else {
                        fprintf(stderr,"mismatched %c-%c \n",s2[i -1],s2[i+1]);
                        s1[j++] = s2 [i - 1];
                        s1[j++] = s2[i++];
                        break;
                    }

                   p = start ;
                   while(p != end){
                    s1[j++] = *p ;
                    if(end > start)
                        ++p;
                    else
                        --p ;
                   }
                   s1[j++] = *p ;
                   i+=2 ;
                   }
                   break;
            default :
                if(s2[i+1]=='-' && s2[i+2] != '\0')
                {
                    ++i;
                }
                else
                {
                  s1[j++] = s2[i++];
                }
                break;
        }
       
    }
   s1[j] = s2[i];
 
}
