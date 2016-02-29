# MySecrect

一个简单、安全、跨平台的加解密工具

### [Releases](https://github.com/DD-L/MySecrect/releases)

* [v0.0.2-alpha](https://github.com/DD-L/MySecrect/releases/tag/v0.0.2-alpha)
	
	1. 新特性

		* 从 [v0.0.2-alpha](https://github.com/DD-L/MySecrect/releases/tag/v0.0.2-alpha) 开始，MySecret 支持易用的图形用户界面. 
		* MySecret 成为“混合式 `Hybrid` 应用程序”, 采用 C++/JavaScript/HTML/CSS 编写. 
		* 多平台支持：Android, Windows, Linux, Cygwin.

			|  GUI  |  CLI  |
			|:-----:|:-----:|
			|Android| Linux |
			|Windows| Cygwin|
			| Linux Desktop |
		
		* 不再对 "Secret Key" 做 首尾空白字符 剔除处理 `trim()`.

	2. 二进制程序
		
		2.1 GUI

		* Android
			* x86  【暂未提供】
			* armv5 【暂未提供】
			* [armeabi-v7](https://github.com/DD-L/MySecrect/releases/download/v0.0.2-alpha/build-MySecret-Android_for_armeabi_v7a_GCC_4_9_Qt_5_5_1.zip) （apk 11.8MB）
		* Windows
			* msvc  【暂未提供】
			* msvc  静态编译版本 【暂未提供】
			* [MinGW-4.9.2-32bit](https://github.com/DD-L/MySecrect/releases/download/v0.0.2-alpha/build-MySecret-Desktop_Qt_5_5_1_MinGW_4.9.2_32bit.7z) （*1.48MB 的* `MySecret.exe` + *90MB 的 Qt 环境依赖库*: `Qt 5.5 & MinGW 4.9.2-32bit DLL's`, 压缩后共 24.5MB）
			* MinGW-4.9.2-32bit 静态编译版本 【暂不提供】
		* Linux Desktop Environment【暂不提供】

		2.2 CLI 
		
		* Linux 【暂未提供】
		* Cygwin 【暂未提供】
			
	3. 一些截图: [Screenshots](./doc/v0.0.2-alpha/screenshots.md).

	4. Known Issues.

		此版本问题较多: [Issues](https://github.com/DD-L/MySecrect/issues)
		* ...
		* ...

	5. [TODO](./TODO)

* [v0.0.1](https://github.com/DD-L/lproxy/tree/master/src/core/crypto/test/easteregg)

	命令行界面的 MySecret。此版本与 v0.0.2-alpha CLI 相差无几。
	
	```
	$ ./mysecret.exe --help

	'mysecret' will auto-load the './key' file from the current
	working path, then complete the encryption and decryption
	tasks with the key...
	
	Usage:
	  ./mysecret [option, ..] [ file | text ]
	  e.g.
	    ./mysecret -e -f plain_file_name
	    ./mysecret -d -f cipher_file_name
	    ./mysecret -e -s plain_text
	    ./mysecret -d -s cipher_text
	    ./mysecret -h
	    ./mysecret -v
	option:
	  -h, --help           Show this message.
	  -v, --version        Show version.
	  -e, --encrypt        Encode.
	  -d, --decrypt        Decode.
	  -f, --file           File.
	  -s, --string         String.

	```

### How to contribute

为 `MySecret` 贡献 Issues 和 代码。 see [here](./doc/how2contribute.md)

### Build

##### Get Code
	
	$ git clone -b develop https://github.com/DD-L/MySecrect
	$ cd MySecrect
	$ git submodule init
	$ git submodule update

或见 [How to contribute](./doc/how2contribute.md) 为 `MySecret`贡献代码部分。

##### Build GUI 

1. 编译 lproxy/contrib/cryptopp 静态库 `libcryptopp.a`. 

	如果想自己编译 libcryptopp.a , 可以参照以下步骤（以下编译均在 Windows 系统下完成）：

	1.1 编译 Desktop Qt 5.5.1 MinGW 32bit 版本的 cryptopp 静态库 `libcryptopp.a`

		要求： 
		* Desktop Qt 5.5.1 MinGW 32bit
		
		进入 Qt 5.5 for Desktop (MinGW 4.9.2 32 bit) 命令行界面执行：

		> cd /D path\to\MySecret\..\MySecret\lproxy\contrib\cryptopp
		> mingw32-make.exe

		将生成的 path\to\MySecret\..\MySecret\lproxy\contrib\cryptopp\cryptopp\libcryptopp.a
		拷贝到 path\to\MySecret\..\MySecret\libs\MinGW32bit 目录下
		完整名为 path\to\MySecret\..\MySecret\libs\MinGW32bit\libcryptopp.a
		
		
	1.2 Android for armeabi-v7a (GCC 4.9. Qt 5.5.1) on Windows 版本的 cryptopp 静态库 `libcryptopp.a`

		要求：
		* Cygwin
		* Android NDK for windows

		进入 Cygwin 环境，在 Cygwin 命令行界面执行
		
		$ cd "path\to\MySecret\..\MySecret\lproxy\contrib\cryptopp"
		$ cat readme.txt
		# 参照 readme.txt 的描述，在 Cygwin 环境下编译 libcryptopp.a
		# 例如
		$ #tar xvfJ ./cryptopp.bak.tar.xz; mv cryptopp.bak cryptopp
		$ git clone https://github.com/DD-L/cryptopp # 推荐
		$ export ANDROID_NDK_ROOT=/d/Qt/android/android-ndk-r10e
        $ . ./setenv-android.sh armeabi-v7a gnu-static # 忽略提示的ERROR
        $ export ANDROID_NDK_ROOT=/cygdrive/d/Qt/android/android-ndk-r10e
        $ . ./setenv-android.sh armeabi-v7a gnu-static # 忽略提示的ERROR
        $ export ANDROID_NDK_ROOT="D:/Qt/android/android-ndk-r10e"
        $ . ./setenv-android.sh armeabi-v7a gnu-static 
        $ cd cryptopp
        $ mv GNUmakefile-cross GNUmakefile-cross.old
        $ cp ../GNUmakefile-cross ./GNUmakefile-cross
        $ #make -f GNUmakefile-cross static dynamic cryptest.exe
        $ make -f GNUmakefile-cross static
        $ mv GNUmakefile-cross.old GNUmakefile-cross

		#如果以上 setenv-android.sh 程序 3 次都未能成功运行，请检查 .sh 文件的编码。
		#如果是编码或行尾换行符问题：
		#可以使用 dos2unix 转换；
		#也可以在 使用 git clone、 pull、submodule update 等下载代码文件之前，
		#设置 git config --global core.autocrlf false ，从而避免 git 自动转换行尾换行符。

		将生成的 path\to\MySecret\..\MySecret\lproxy\contrib\cryptopp\cryptopp\libcryptopp.a
		拷贝到 path\to\MySecret\..\MySecret\libs\Androidarmeabiv7a\ 目录下， 
		完整名为 path\to\MySecret\..\MySecret\libs\Androidarmeabiv7a\libcryptopp.a
		

2. 修改 project 文件 `MySecret.pro` 中的变量:

	* INCLUDEPATH
	* LIBS

3. 工程导入 `lproxy/src/core/crypto/*.h` 和 `lproxy/src/core/crypto/*.cpp` (此步骤已经在 MySecret.pro 中配置过了，不必重复配置，可忽略)

4. 工程导入 资源文件 `GUI/qml.qrc`
5. 构建项目

##### Build CLI

	$ cd /path/to/MySecret/CLI
	$ make


### [LICENSE](./LICENSE) 

	
	