#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <conio.h>
#include <cstring>
#include <Windows.h>
#include <mmsystem.h>
#include "helper.h"
#include "core/user.h"

using namespace std;

#pragma once

#define USER_FILE_PATH "storage/user.dat"
#define HISTORY_FILE_PATH "storage/history.dat"
#define TMP_FILE_PATH "storage/temp.dat"
///////////////////////////
//       Colors
///////////////////////////
#define F_YELLOW "\033[93m"
#define F_GREEN "\033[92m"
#define F_RED "\033[91m"

#define B_MAGENTA "\033[45m"

#define RESET_COLOR "\033[0m"