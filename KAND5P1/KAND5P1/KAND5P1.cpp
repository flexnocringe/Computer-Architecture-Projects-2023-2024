#include<iostream>
#include<string>
using namespace std;
int main(int argc, char* argv[])
{
	char* prd = argv[1];
	int siz = strlen(argv[1]);
	int error = 0;
	unsigned int rez = 0;
	__asm
	{
		push eax
		push ebx
		push ecx
		push esi
		mov esi, prd
		mov ecx, siz
		xor ebx, ebx
		xor eax, eax
		iloop:
		xor edx, edx
		mov ebx, 10
		mul ebx
		mov bl, byte ptr[esi]
		cmp bl, 48
		jl err_not_num
		cmp bl, 57
		jg err_not_num
		sub ebx, 48
		add eax, ebx
		jc err_crr_flg
		inc esi
		dec ecx
		cmp ecx, 0
		je end_loop
		jne iloop
		err_not_num :
		mov error, 1
		jmp end_loop
		err_crr_flg :
		mov error, 2
		jmp end_loop
		end_loop:
		mov rez, eax
		pop eax
		pop ebx
		pop ecx
		pop esi
	};
	if (error == 0)
	{
		cout << rez;
	}
	else if (error == 1)
	{
		cout<<"Error!!! String is not a number.";
	}
	else if (error == 2)
	{
		cout << "Error!!! Number is too big.";
	}
	return 0;
}