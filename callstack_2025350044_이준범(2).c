/*  call_stack

    ���� �ý��ۿ����� ������ �޸𸮿� ���������, �� ���������� `int` �迭�� �̿��Ͽ� �޸𸮸� �����մϴ�.
    ������ SFP�� Return Address�� ���� ���� �޸� �ּҰ� ��������, �̹� ���������� -1�� ��ü�մϴ�.

    int call_stack[]      : ���� ������(`int ��`) �Ǵ� `-1` (��Ÿ������ ���п�)�� �����ϴ� int �迭
    char stack_info[][]   : call_stack[]�� ���� ��ġ(index)�� ���� ������ �����ϴ� ���ڿ� �迭

    ==========================call_stack ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���   : int �� �״��
    Saved Frame Pointer �� push�� ���  : call_stack������ index
    ��ȯ �ּҰ��� push�� ���       : -1
    =======================================================================


    ==========================stack_info ���� ��Ģ==========================
    �Ű� ���� / ���� ������ push�� ���        : ������ ���� ����
    Saved Frame Pointer �� push�� ���  : � �Լ��� SFP����
    ��ȯ �ּҰ��� push�� ���                 : "Return Address"
    ========================================================================
*/
#include <stdio.h>
#define STACK_SIZE 50 // �ִ� ���� ũ��

int     call_stack[STACK_SIZE];         // Call Stack�� �����ϴ� �迭
char    stack_info[STACK_SIZE][20];     // Call Stack ��ҿ� ���� ������ �����ϴ� �迭

/*  SP (Stack Pointer), FP (Frame Pointer)

    SP�� ���� ������ �ֻ�� �ε����� ����ŵ�ϴ�.
    ������ ������� �� SP = -1, �ϳ��� ���̸� `call_stack[0]` -> SP = 0, `call_stack[1]` -> SP = 1, ...

    FP�� ���� �Լ��� ���� ������ �������Դϴ�.
    ���� ���� �Լ� ���� �������� sfp�� ����ŵ�ϴ�.
*/
int SP = -1;
int FP = -1;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

void push(int num1, char str1[20])
{
    SP++;
    if (num1 != -2) {
        call_stack[SP] = num1;
        strcpy(stack_info[SP], str1);
    }
    else {
        call_stack[SP] = SP;
        strcpy(stack_info[SP], str1);
        FP = SP;
    }
}

void pop(void) {

     strcpy(stack_info[SP], "\0");
     SP--;
}


/*
    ���� call_stack ��ü�� ����մϴ�.
    �ش� �Լ��� ��� ������� �������� ���� �ϼ����� ���� �����Դϴ�.
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
            printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
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


//func ���δ� �����Ӱ� �߰��ص� ��������, �Ʒ��� ������ �ٲ����� ������
void func1(int arg1, int arg2, int arg3)
{
    int var_1 = 100;

    push(3, "arg3");
    push(2, "arg2");
    push(1, "arg1");

    push(-1, "Return Address");

    push(-2, "func1 SFP");

    push(100, "var_1");

    // func1�� ���� ������ ���� (�Լ� ���ѷα� + push)

    print_stack();
    func2(11, 13);

    // func2�� ���� ������ ���� (�Լ� ���ʷα� + pop)

    pop();
    pop();
    pop();
    pop();
    pop();
    FP = 4;

    print_stack();
}


void func2(int arg1, int arg2)
{
    int var_2 = 200;

    push(13, "arg2");
    push(11, "arg1");

    push(-1, "Return Address");

    push(-2, "func2 SFP");

    push(200, "var_2");

    // func2�� ���� ������ ���� (�Լ� ���ѷα� + push)

    print_stack();
    func3(77);

    // func3�� ���� ������ ���� (�Լ� ���ʷα� + pop)

    pop();
    pop();
    pop();
    pop();
    pop();
    FP = 9;

    print_stack();
}


void func3(int arg1)
{
    int var_3 = 300;
    int var_4 = 400;

    push(77, "arg1");

    push(-1, "Return Address");

    push(-2, "func3 SFP");

    push(300, "var_3");
    push(400, "var_4");

    // func3�� ���� ������ ���� (�Լ� ���ѷα� + push)
    print_stack();
}


//main �Լ��� ���õ� stack frame�� �������� �ʾƵ� �˴ϴ�.
int main()
{
    func1(1, 2, 3);

    // func1�� ���� ������ ���� (�Լ� ���ʷα� + pop)

    pop();
    pop();
    pop();
    pop();
    pop();
    pop();

    print_stack();
    return 0;
}