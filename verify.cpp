#include "verify.h"

#if WIN32
VERIFY_API char* Add()
{
	string temp = "string dll test for C Sharp.";
	char* codeer = new char[temp.length() + 1];

	for (size_t i = 0; i <= temp.length(); ++i)
	{
		if (i == temp.length())
		{
			codeer[i] = '\0';
			break;
		}

		codeer[i] = temp[i];
	}
	return codeer;
}

VERIFY_API bool VerifyActivationCode(const char* activation, const char* serial)
{
	string encryption_code = Encryption_HMAC_SHA256(serial);
	if (encryption_code == activation)
	{
		Write_Regedit(HKEY_CURRENT_USER, encryption_code.c_str(), "code");
		return true;
	}
    return false;
}

VERIFY_API bool VerifyIsTheDevAct(const char* serial)
{
    return Red_Regedit("code") == Encryption_HMAC_SHA256(serial);
}

// hmac_sha256 ¼ÓÃÜ
string Encryption_HMAC_SHA256(const char* serial)
{
	string m_Serial = serial;
	std::string key = "secretxxxxxx2df8976eenxxxxxx";

	string str_data = "X1" + m_Serial + "x2";
	std::stringstream ss_result;

	// Allocate memory for the HMAC
	std::vector<uint8_t> out(SHA256_HASH_SIZE);

	// Call hmac-sha256 function
	hmac_sha256(key.data(), key.size(), str_data.data(), str_data.size(),
		out.data(), out.size());

	// Convert `out` to string with std::hex
	for (uint8_t x : out) {
		ss_result << std::hex << std::setfill('0') << std::setw(2) << (int)x;
	}

	// Print out the result
	//std::cout << "Message: " << str_data << std::endl;
	//std::cout << "Key: " << key << std::endl;
	//std::cout << "HMAC: " << ss_result.str() << std::endl;
	return ss_result.str();
}

//Ð´×¢²á±í
BOOL Write_Regedit(HKEY Reg_Root, const char* lpszFileName, const char* lpszValueName)
{
	HKEY hKey;
	if (ERROR_SUCCESS != RegOpenKeyEx(Reg_Root, Reg_Path, 0, KEY_WRITE, &hKey))
	{
		::RegCreateKeyA(HKEY_CURRENT_USER, Reg_Path, &hKey); //Create Regedit
		//return FALSE;
	}
	if (ERROR_SUCCESS != RegSetValueEx(hKey, lpszValueName, 0, REG_SZ, (BYTE*)lpszFileName, (1 + ::lstrlen(lpszFileName))))
	{
		RegCloseKey(hKey);
		return FALSE;
	}
	RegCloseKey(hKey);
	return TRUE;
}

//¶Á×¢²á±í
std::string Red_Regedit(const std::string& key) {
	HKEY hkey = nullptr;
	LSTATUS res = ::RegOpenKeyExA(HKEY_CURRENT_USER, Reg_Path, 0, KEY_READ, &hkey);
	if (res != ERROR_SUCCESS) {
		return "";
	}
	std::shared_ptr<void> close_key(nullptr, [&](void*) {
		if (hkey != nullptr) {
			::RegCloseKey(hkey);
			hkey = nullptr;
		}
		});
	DWORD type = REG_SZ;
	DWORD size = 0;
	res = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, nullptr, &size);
	if (res != ERROR_SUCCESS || size <= 0) {
		return "";
	}
	std::vector<BYTE> value_data(size);
	res = ::RegQueryValueExA(hkey, key.c_str(), 0, &type, value_data.data(), &size);
	if (res != ERROR_SUCCESS) {
		return "";
	}
	return std::string(value_data.begin(), value_data.end() - 1); // È¥µôÄ©Î² '\0'
}

#endif
