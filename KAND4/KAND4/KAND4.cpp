#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;
int main()
{
	char memory[256] = {};
	char registers[16] = {};
	char* pc(nullptr);
	pc = memory;
	char flags = 0b00000010;
	ifstream filebin("decryptor.bin", ios::in | ios::binary);
	memory[255] = 0;
	while (!filebin.eof())
	{
		filebin.get(memory[memory[255]]);
		memory[255]++;
	}
	filebin.close();

	ifstream filetxt("q1_encr.txt");
	while (*pc != 0x0B)
	{
		if (*pc == 0x01)
		{
			registers[*(pc + 1) & 0b00001111]++;
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		else if (*pc == 0x02)
		{
			registers[*(pc + 1) & 0b00001111]--;
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		else if (*pc == 0x03)
		{
			registers[*(pc + 1) & 0b00001111] = registers[(*(pc + 1) & 0b11110000) >> 4];
			pc += 2;
		}
		else if (*pc == 0x04)
		{
			registers[0] = *(pc + 1);
			pc += 2;
		}
		else if (*pc == 0x05)
		{
			registers[*(pc + 1) & 0b00001111] = registers[*(pc + 1) & 0b00001111] << 1;
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		else if (*pc == 0x06)
		{
			registers[*(pc + 1) & 0b00001111]=registers[*(pc + 1) & 0b00001111] >> 1;
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		else if (*pc == 0x0C)
		{
			registers[*(pc + 1) & 0b00001111] += registers[(*(pc + 1) & 0b11110000) >> 4];
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		if (*pc == 0x07)
		{
			pc += *(pc + 1);
		}
		else if (*pc == 0x08 && (flags & 0b00001000) >> 3 == 1)
		{
			pc += *(pc + 1);
		}
		else if (*pc == 0x08 && (flags & 0b00001000) >> 3 == 0)
		{
			pc += 2;
		}
		else if (*pc == 0x09 && (flags & 0b00001000) == 0)
		{
			pc += *(pc + 1);
		}
		else if (*pc == 0x09 && (flags & 0b00001000) >> 3 == 1)
		{
			pc += 2;
		}
		else if (*pc == 0x0A && (flags & 0b00010000) >> 4 == 1)
		{
			pc += *(pc + 1);
		}
		else if (*pc == 0x0A && (flags & 0b00010000) >> 4 == 0)
		{
			pc += 2;
		}
		else if (*pc == 0x0B)
		{
			break;
		}
		else if (*pc == 0x0D)
		{
			registers[*(pc + 1) & 0b00001111] -= registers[(*(pc + 1) & 0b11110000) >> 4];
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		else if (*pc == 0x0E)
		{
			registers[*(pc + 1) & 0b00001111] = registers[*(pc + 1) & 0b00001111] ^ registers[(*(pc + 1) & 0b11110000) >> 4];
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		else if (*pc == 0x0F)
		{
			registers[*(pc + 1) & 0b00001111] = registers[*(pc + 1) & 0b00001111] | registers[(*(pc + 1) & 0b11110000) >> 4];
			if (registers[(*pc + 1) & 0b00001111] == 0 && (flags & 0b00001000) == 0)
			{
				flags = flags ^ 0b00001000;
			}
			else if (registers[*(pc + 1) & 0b00001111] != 0 && (flags & 0b00001000) >> 3 == 1)
			{
				flags = flags ^ 0b00001000;
			}
			pc += 2;
		}
		else if (*pc == 0x10)
		{
			filetxt.get(registers[*(pc + 1) & 0b00001111]);
			if (filetxt.eof() && (flags & 0b00010000) == 0)
			{
				flags = flags ^ 0b00010000;
			}
			pc += 2;
		}
		else if (*pc == 0x11)
		{
			printf("%c", registers[*(pc + 1) & 0b00001111]);
			pc += 2;
		}
	}
	filetxt.close();
}