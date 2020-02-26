// OS-Laba1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <windows.h>
#include <iostream>
using namespace std;

void execF();
void execS();
void execT(char str[]);
char* substr(char str[]);

const char wordStr[] = { "C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.EXE" };
const char exelStr[] = { "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE" };

int main()
{
	setlocale(LC_ALL, "Russian");

	char str[100];
	do {
		cout << "Введите команду: ";
		cin.getline(str, 100);

		if (!strcmp(str, "run word")) {
			execF();
		}
		else if (!strcmp(str, "run exel")) {
			execS();
		}
		else if (!strcmp(substr(str), "open")) {
			cout << (str + 5) << endl;
			execT(str);
		}
		else if (!strcmp(str, "exit")) {
			ExitProcess(NO_ERROR);
		}
		else {
			cout << "Команда не найдена!" << endl;
		}
	} while (true);
}

void execF() {
	switch (WinExec(wordStr, SW_SHOW))
	{
	case 0:
		cout << "ERROR: Системе не хватает памяти или ресурсов." << endl;
		break;
	case ERROR_BAD_FORMAT:
		cout << "ERROR: Исполняемый файл невалидный." << endl;
		break;
	case ERROR_PATH_NOT_FOUND:
		cout << "ERROR: Заданный путь не найден." << endl;
		break;
	case ERROR_FILE_NOT_FOUND:
		cout << "ERROR: Заданный файл не найден." << endl;
		break;
	}
}
void execS() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	if (!CreateProcess(exelStr, NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi)) {
		cout << "ERROR: Ошибка запуска процесса." << endl;
	}
	else {
		cout << "ID процесса: " << pi.dwProcessId << endl;
		SetPriorityClass(pi.hProcess, ABOVE_NORMAL_PRIORITY_CLASS);
		cout << "Версии для котрого предполагается исп.: " << GetProcessVersion(pi.dwProcessId) << endl;
		FILETIME time[4];
		SYSTEMTIME systime;
		GetProcessTimes(pi.hProcess, &time[0], &time[1], &time[2], &time[3]);
		FileTimeToSystemTime(&time[0], &systime);
		cout << "Время запуска: " << systime.wHour << ":" << systime.wMinute << ":" << systime.wSecond << endl;
	}
}
void execT(char str[]) {
	switch ((int)ShellExecute(NULL, "open", (str + 5), NULL, NULL, SW_SHOWNORMAL))
	{
	case ERROR_FILE_NOT_FOUND:
		cout << "ERROR: Файл не найден!" << endl;
		break;
	case ERROR_PATH_NOT_FOUND:
		cout << "ERROR: Путь не найден!" << endl;
		break;
	case ERROR_BAD_FORMAT:
		cout << "ERROR: Ошибка в исполняющемся файле." << endl;
		break;
	}
}
char* substr(char str[]) {
	char str2[5];
	for (int i = 0; i < 4; i++) {
		str2[i] = str[i];
	}
	str2[4] = '\0';
	return str2;
}
