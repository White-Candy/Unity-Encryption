### Instruction
*本工具使用 [hmac_sha256 x64位](https://github.com/h5p9sl/hmac_sha256) 作为加密算法。*  
本工具使用方法是编译成DLL文件，载入UnityEditor中使用。  
```
———————————————————————————————————————————————
|      开发版本IDE     |  Visual Studio 2022  | 
———————————————————————————————————————————————
|     WindowsSDK版本   |        10.0          |  
———————————————————————————————————————————————
|      C++语言版本     |      ISO C++ 14      | 
———————————————————————————————————————————————
```

### Interface
```  
verify.h
—————————————————————————————————————————————————————————
|      FUNC: char* Add    | 用于测试Unity 与 DLL 接口测试|
—————————————————————————————————————————————————————————
|         RETURN          | string dll test for C Sharp.|
—————————————————————————————————————————————————————————

————————————————————————————————————————————————————————————————
| FUNC: bool VerifyActivationCode   |     检查激活码是否正确    |
————————————————————————————————————————————————————————————————
|       PARAM: char* activation     |         激活码           | 
————————————————————————————————————————————————————————————————
|       PARAM: char* serial         |      Unity硬件序列码     |
————————————————————————————————————————————————————————————————
|            RETURN                 | 相同返回TRUE，否则FALSE值 |
————————————————————————————————————————————————————————————————

————————————————————————————————————————————————————————————————
| FUNC: bool VerifyIsTheDevAct      |    检查本机是否已经激活   |
————————————————————————————————————————————————————————————————
|       PARAM: char* serial         |      Unity硬件序列码     |
————————————————————————————————————————————————————————————————
|            RETURN                 | 激活返回TRUE，否则FALSE值 |
————————————————————————————————————————————————————————————————

```

### Use
克隆该仓库:
```
git@github.com:White-Candy/Unity-Encryption.git
```  
导入VS2022中，'配置类型' 为DLL动态库，点击'生成' DLL文件。  

### Example
*生成的DLL文件导入Unity 'Asset/Plugins' 下使用。*  
```C#
[DllImport("Encryption")]
private static extern IntPtr Add();

[DllImport("Encryption")]
private static extern bool VerifyActivationCode(string activation, string serial);

[DllImport("Encryption")]
private static extern bool VerifyIsTheDevAct(string serial);
```
