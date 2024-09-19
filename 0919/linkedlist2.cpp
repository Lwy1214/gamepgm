#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// 스택 노드를 정의
struct stack_node {
    char data;
    struct stack_node *link;
};

// 전역 스택 포인터 선언
struct stack_node *top = NULL;

void push(char data);
char pop(void);

int main(void)
{
    int count = 0;
    char key;
    
    do {
        count++;
        printf("%2d 번 문자입력 >", count);
        key = getch();  // getchar()로 대체 가능
        push(key);
        printf("%c \n", key);
    } while (key != 27);  // ASCII code 27은 ESC키
    
    printf("\n\n");
    printf("데이터 pop 과정 \n\n");
    
    while (top != NULL) {
        key = pop();
        printf("%c ", key);
    }
    
    printf("\n");
    return 0;
}

// 스택에 데이터를 삽입하는 함수
void push(char data)
{
    struct stack_node *new_node;
    new_node = (struct stack_node*)malloc(sizeof(struct stack_node));
    
    new_node->data = data;
    new_node->link = top;
    top = new_node;
}

// 스택에서 데이터를 제거하는 함수
char pop(void)
{
    struct stack_node *temp;
    char data;
    
    
    data = top->data;
    temp = top;
    top = top->link;
    free(temp);
    
    return data;
}


