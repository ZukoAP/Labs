#include <stdio.h>
#include <stdlib.h>

int main() {
    int openBracNum, diff,ind;
    scanf("%d", &openBracNum);
    char* bracketsComb = (char*) malloc(2*openBracNum* sizeof(char));
    for(int i=0; i<openBracNum; i++){
        bracketsComb[i] = '(';
        bracketsComb[openBracNum+i] = ')';
    }
    for(int i = 0; i< 2*openBracNum; i++)
        printf("%c", bracketsComb[i]);
    printf("\n");
    while(1){
        ind = 2*openBracNum-1;
        diff = 0;
        while(ind>=0){
            if (bracketsComb[ind] == ')')
                diff -= 1;
            if (bracketsComb[ind] == '(')
                diff += 1;
            if (diff <0 && bracketsComb[ind]=='(')
                break;
            ind -= 1;
        }
        if (ind<0)
            break;
        bracketsComb[ind] = ')';
        for (int i=ind+1;i<2*openBracNum;i++) {
            if (i <= (2 * openBracNum - ind + diff) / 2 + ind)
                bracketsComb[i] = '(';
            else
                bracketsComb[i] = ')';
        }
        //printf("%s\n", bracketsComb);
        for(int i = 0; i< 2*openBracNum; i++)
            printf("%c", bracketsComb[i]);
        printf("\n");
    }

    return 0;
}
