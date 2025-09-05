// Program to find the longest word in the string

#include<stdio.h>
#include<string.h>

int main()
{
    char str[100];
    scanf("%[^\n]",str);
    char curr[100], longest[100];
    int clen =0, llen=0, i=0;

    while(str[i] !='\0')
    {
        if((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        {
            curr[clen++] = str[i];
        }
        else
        {
            if(clen > 0)
            {
                curr[clen] = '\0';
                if(clen > llen)
                {
                    llen = clen;
                    for(int j=0;j<=clen;j++)
                    {
                        longest[j] = curr[j];
                    }
                }
                clen =0;
            }
            
        }

        i++;
    }

    //  for last word to terminate normally 
    if(clen > 0)
    {
        curr[clen] = '\0';
        if(clen > llen)
        {
            llen = clen;
            for(int j=0;j<=clen;j++)
            {
                longest[j] = curr[j];
            }
        }
    }

    printf("The longest word in %s is %s\n",str,longest);

    return 0;
}