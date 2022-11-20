#pragma once

// WinApi �����ӿ�ũ
#include <Windows.h>

// WinApi img32 ���̺귯��
#pragma comment(lib, "MsImg32.lib")

// FMOD ����
#include "FMOD/inc/fmod.hpp"
#pragma comment(lib, "FMOD/lib/fmod_vc.lib")

using namespace FMOD;

// C++ ǥ�� ���̺귯��
#include <cassert>
#include <chrono>
#include <string>
#include <array>
#include <map>
#include <list>
#include <queue>
#include <unordered_map>

using namespace std;

// Util
#include "SingleTon.h"
#include "Component.h"
#include "Struct.h"
#include "Logger.h"