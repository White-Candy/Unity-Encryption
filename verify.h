/*
 * @Author: ShiyiTang
 * @Date: 2024-04-22 11:20:34
 * @FilePath:
 * @Description: verify interface
 */
#pragma once

#ifndef WIN32
#define WIN32 1
#endif // !WIN32

#if WIN32
#define VERIFY_API extern "C" __declspec(dllexport)
#define SHA256_HASH_SIZE 32
#define Reg_Path "Software\\hardware"

#include <cassert>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <Windows.h>

#include "hmac_sha256.h"

using namespace std;

extern string m_Serial;
extern string key;

BOOL Write_Regedit(HKEY Reg_Root, const char* lpszFileName, const char* lpszValueName); //Ð´×¢²á±í
string Red_Regedit(const std::string& key); //¶Á×¢²á±í
string Encryption_HMAC_SHA256(const char* serial);

VERIFY_API char* Add();
VERIFY_API bool VerifyActivationCode(const char* activation = "", const char* serial = "");
VERIFY_API bool VerifyIsTheDevAct(const char* device);

#endif