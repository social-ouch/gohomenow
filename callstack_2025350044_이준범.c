
/*  call_stack
    
    실제 시스템에서는 스택이 메모리에 저장되지만, 본 과제에서는 `int` 배열을 이용하여 메모리를 구현합니다.
    원래는 SFP와 Return Address에 실제 가상 메모리 주소가 들어가겠지만, 이번 과제에서는 -1로 대체합니다.
    
    int call_stack[]      : 실제 데이터(`int 값`) 또는 `-1` (메타데이터 구분용)을 저장하는 int 배열 
    char stack_info[][]   : call_stack[]과 같은 위치(index)에 대한 설명을 저장하는 문자열 배열

    ==========================call_stack 저장 규칙==========================
    매개 변수 / 지역 변수를 push할 경우   : int 값 그대로
    Saved Frame Pointer 를 push할 경우  : call_stack에서의 index
    반환 주소값을 push할 경우       : -1
    =======================================================================
    

    ==========================stack_info 저장 규칙==========================
    매개 변수 / 지역 변수를 push할 경우        : 변수에 대한 설명
    Saved Frame Pointer 를 push할 경우  : 어떤 함수의 SFP인지
    반환 주소값을 push할 경우                 : "Return Address"
    ========================================================================
*/
#include <stdio.h>
#define STACK_SIZE 50 // 최대 스택 크기

int     call_stack[STACK_SIZE];         // Call Stack을 저장하는 배열
char    stack_info[STACK_SIZE][20];     // Call Stack 요소에 대한 설명을 저장하는 배열

/*  SP (Stack Pointer), FP (Frame Pointer)

    SP는 현재 스택의 최상단 인덱스를 가리킵니다.
    스택이 비어있을 때 SP = -1, 하나가 쌓이면 `call_stack[0]` -> SP = 0, `call_stack[1]` -> SP = 1, ...

    FP는 현재 함수의 스택 프레임 포인터입니다.
    실행 중인 함수 스택 프레임의 sfp를 가리킵니다.
*/
int SP = -1; 
int FP = -1;
int SFP1, SFP2, SFP3;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);


/*  
    현재 call_stack 전체를 출력합니다.
    해당 함수의 출력 결과들을 바탕으로 구현 완성도를 평가할 예정입니다.
*/
void print_stack()
{
    if (SP == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");
    
    for (int i = SP; i >= 0; i--)
    {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i ,stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== [esp]\n");
        else if (i == FP)
            printf("    <=== [ebp]\n");
        else
            printf("\n");
    }
    printf("================================\n\n");
}


//func 내부는 자유롭게 추가해도 괜찮으나, 아래의 구조를 바꾸지는 마세요
void func1(int arg1, int arg2, int arg3)
{
    int var_1 = 100;

    SP++;
    call_stack[SP] = arg3;
    strcpy(stack_info[SP], "arg3");

    SP++;
    call_stack[SP] = arg2;
    strcpy(stack_info[SP], "arg2");

    SP++;
    call_stack[SP] = arg1;
    strcpy(stack_info[SP], "arg1");

    SP++;
    call_stack[SP] = -1;
    strcpy(stack_info[SP], "Return Address");

    SP++;
    call_stack[SP] = SP;
    strcpy(stack_info[SP], "func1 SFP");
    FP = SP;
    SFP1 = SP;

    SP++;
    call_stack[SP] = var_1;
    strcpy(stack_info[SP], "var_1");


    // func1의 스택 프레임 형성 (함수 프롤로그 + push)
    print_stack();
    func2(11, 13);
    // func2의 스택 프레임 제거 (함수 에필로그 + pop)


    FP = SFP1;
    SP--;
    SP--;
    SP--;
    SP--;
    SP--;
    print_stack();
}


void func2(int arg1, int arg2)
{
    int var_2 = 200;

    SP++;
    call_stack[SP] = arg2;
    strcpy(stack_info[SP], "arg2");

    SP++;
    call_stack[SP] = arg1;
    strcpy(stack_info[SP], "arg1");

    SP++;
    call_stack[SP] = -1;
    strcpy(stack_info[SP], "Return Address");

    SP++;
    call_stack[SP] = SP;
    strcpy(stack_info[SP], "func2 SFP");
    FP = SP;
    SFP2 = SP;

    SP++;
    call_stack[SP] = var_2;
    strcpy(stack_info[SP], "var_2");

    // func2의 스택 프레임 형성 (함수 프롤로그 + push)


    print_stack();
    func3(77);

    // func3의 스택 프레임 제거 (함수 에필로그 + pop)

    FP = SFP2;
    SP--;
    SP--;
    SP--;
    SP--;
    SP--;

    print_stack();
}


void func3(int arg1)
{
    int var_3 = 300;
    int var_4 = 400;

    SP++;
    call_stack[SP] = arg1;
    strcpy(stack_info[SP], "arg1");

    SP++;
    call_stack[SP] = -1;
    strcpy(stack_info[SP], "Return Address");

    SP++;
    call_stack[SP] = SP;
    strcpy(stack_info[SP], "func3 SFP");
    FP = SP;
    SFP3 = SP;


    SP++;
    call_stack[SP] = var_3;
    strcpy(stack_info[SP], "var_3");

    SP++;
    call_stack[SP] = var_4;
    strcpy(stack_info[SP], "var_4");
    

    // func3의 스택 프레임 형성 (함수 프롤로그 + push)
    print_stack();
}


//main 함수에 관련된 stack frame은 구현하지 않아도 됩니다.
int main()
{
    func1(1, 2, 3);
    // func1의 스택 프레임 제거 (함수 에필로그 + pop)

    SP--;
    SP--;
    SP--;
    SP--;
    SP--;
    SP--;

    print_stack();


    return 0;
}