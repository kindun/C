#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int *init(int n);
void display(int *ans, int n);
void NEW(int *num, int n);
void OLD(int *num, int n);

int main(void)
{
    char buf[1000];
    printf("数列をカンマ区切りで入力してください: \n");
    fgets(buf, sizeof(buf), stdin); 

    int n = 1;
    for (int i = 0; buf[i]; i++) {
        if (buf[i] == ',') n++;
    }

    int *num = init(n); 

    char *token = strtok(buf, ",\n");// "," または"\n"で区切る
    int idx = 0;
    while (token != NULL) {
        num[idx++] = atoi(token);//char型 -> int型 "1" -> 1
        token = strtok(NULL, ",\n");//区切った物を得る
    }


    NEW(num, n);
    OLD(num, n);


    free(num);
    return 0;

}


void NEW(int *num, int n)
{
	int *ans = init(n);
    bool *used = (bool *)calloc(n, sizeof(bool)); 

    for(int i = 0; i < n; i++){
        int a = num[i] % n;

        if(ans[a] == num[i]){
            continue;
        }else if(used[a]) {
            int j = (a + 1) % n;
            while(used[j]){
                j = (j + 1) % n;
            }
            ans[j] = num[i];
            used[j] = true;

        }else{
            ans[a] = num[i];
            used[a] = true;
        }

    }

    printf("NEW :");
    display(ans, n);

    free(ans);
    free(used);
}


void OLD(int *num, int n)
{
    int *ans = init(n);
    int idx = 0;

    for(int i = 0; i < n; i++){
        bool exist = false;
        for(int j = 0; j < idx; j++){
            if(num[i] == ans[j]){
                exist = true;
                break;
            }
        }
        if(!exist){
            ans[idx++] = num[i];
        }
    }

    printf("OLD :");
    display(ans, n);

    free(ans);


}

void display(int *ans, int n)
{
    for(int i = 0; i < n; i++){
        printf("%d ", ans[i]);
    }
    printf("\n");

}


int *init(int n)
{
   return (int *)calloc(n, sizeof(int));

}
