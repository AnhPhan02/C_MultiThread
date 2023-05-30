#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<Windows.h>
#include<string.h>

/***
* By AnhPhan02
* Description: this is MultiThread code
* creat Thread of function by CreateThread
* then CreatePipe to witer form main to function to read data
* Ex: in main function we write data by variable sensor then using another function to read
*The purpose todo it main function and another function will run parallel
**/
int sensor = 0;
HANDLE read_pipe = 0;
HANDLE write_pipe = 0;

DWORD WINAPI function(LPVOID lpThreadParameter)
{
	int read_data = 0;
	DWORD Data_available = 0;
	while (1) {
		PeekNamedPipe(
		read_pipe,
			NULL,0,NULL,&Data_available,NULL);

		ReadFile(read_pipe,
			&read_data,
			sizeof(read_data),
			NULL,NULL);

		printf("Function: sensor %d  available\r\n",read_data);
		printf("Function: data %d byte available\r\n", Data_available); // đọc dữ liệu đã được ghi trong pipe
		Sleep(1500);
	}
}

void main() {
	
	HANDLE thread_a = CreateThread(NULL,
						1024,
						function,
						NULL, CREATE_SUSPENDED,NULL);
	ResumeThread(thread_a);

	CreatePipe(&read_pipe,
		&write_pipe,
		NULL,
		1024);
	while (1) {
		sensor++;

		WriteFile(
			write_pipe,
			&sensor,
			sizeof(sensor),
			NULL,NULL);

		printf("Main is running\r\n");

		Sleep(1000);
	}

}