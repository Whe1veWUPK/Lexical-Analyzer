#include<stdio.h>
typedef struct{
    double x;
    double y;
} Dot;
void printHelloWorld(){
    printf("HelloWorld");
    return;
}
int main(){
    int a = 2;
    double b = 3.55;
    char c = '2';
    const char *d = "Compile";
    switch(a){
        case 1:
            a=a+1;
            break;
        case 2;
            break;
    }
    while(a>=2){
        a=a-1;
    }
    if(a>2){
        printf("a>2");
    }
    else if(a>=1){
        printf("a>=1");
    }
    else{
        print("OtherCases");
    }
    return 0;
}