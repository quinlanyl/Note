void Parse(const int argc, char** argv);
{
   /* argc是命令行总的参数个数  
   argv[]是argc个参数，其中第0个参数是程序的全名，以后的参数  
   命令行后面跟的用户输入的参数，比如：  
   int   main(int   argc,   char*   argv[])  
   {  
   int   i;  
   for   (i   =   0;   i<argc;   i++)  
   cout<<argv[i]<<endl;  
   cin>>i;  
   return   0;  
   }  
   执行时敲入  
   F:\MYDOCU~1\TEMPCODE\D1\DEBUG\D1.EXE   aaaa   bbb   ccc   ddd  
   输出如下：  
   F:\MYDOCU~1\TEMPCODE\D1\DEBUG\D1.EXE  
   aaaa  
   bbb  
   ccc  
   ddd  
--------------------------------------------------------------------
char   *argv[]是一个字符数组,其大小是int   argc,主要用于命令行参数   argv[]   参数，数组里每个元素代表一个参数;
比如你输入  
   test   a.c   b.c   t.c  
   则  
   argc   =   4  
    
   argv[0]   =   "test"  
   argv[1]   =   "a.c"  
   argv[2]   =   "b.c"  
   argv[3]   =   "t.c"
--------------------------------------------------------------------------------------------  
argc记录了用户在运行程序的命令行中输入的参数的个数。  
arg[]指向的数组中至少有一个字符指针，即arg[0].他通常指向程序中的可执行文件的文件名。在有些版本的编译器中还包括程序
文件所在的路径。
-------------------------------------------------------------------------
在调用一个可执行程序时，某些情况下需要向程序传递参数。如我们可以在控制台中键入notepad.exe，
回车后将执行记事本程序。如果我们希望在打开notepad时同时打开一个文本文件，可以在notepad.exe  
后面跟上文件的路径和名字，如notepad.exe   example.txt（文件在当前路径）。  
    
   那么程序中如何能得到这些输入参数呢？这个工作是编译器帮我们完成的，编译器将输入参数的信息
放入main函数的参数列表中。  
    
   main函数的参数列表保存了输入参数的信息，第一个参数argc记录了输入参数的个数，  
   第二个参数是字符串数组的，字符串数组的每个单元是char*类型的，指向一个c风格字符串。  
   以notepad.exe   example.txt为例  
   argc是2，就是说argv数组中有两个有效单元  
   第一单元指向的字符串是"notepad.exe"  
   第二单元指向的字符串是"example.txt"  
    
   argv数组中的第一个单元指向的字符串总是可执行程序的名字，以后的单元指向的字符串依次是程序调用时的参数。  
    
   这个赋值过程是编译器完成的，我们只需要读出数据就可以了。 */
}

desc_->add_options()(name.c_str(),
                       boost::program_options::value<T>(option)->required(),
                       help_text.c_str());
 {
	 int opt;
/* 类 options_description 是存储选项详细信息的类 */
      options_description parser("name_your_like");
/*add_option() 支持() 操作. 多次调用add_options() 的效果等同于将所有的选项使用() 并列声明*/
      parser.add_options()
         /*无参数的选项格式 : "命令名" , "命令说明" */
         ("help", "produce help message")
         /* 有参数的选项格式 : 
          "命令名" , "参数说明" , "命令说明" */ 
         ("set-float" ,value<float>(), "set a float parameter")
         /* 参数对应已有数据(特定地址) , 并且有初始值 : */ 
         ("optimization", value<int>(&opt)->default_value(10), 
             "optimization level")
         /* 支持短选项 ( --include-path 和 -I 等效 ) ,
            多次调用存在依次vector中 */
         ("include-path,I", value< vector<string> >(), 
             "include path")
 }	
 #include "endian.h"
 {
	 reverse的用法
	 {

		 int main()
		{
			
			std::vector<int> myvector;
			for (int i = 1; i<10; ++i) myvector.push_back(i);   // 1 2 3 4 5 6 7 8 9  

																//std::reverse(myvector.begin(), myvector.end());    // 9 8 7 6 5 4 3 2 1  
			std::reverse(myvector.begin(), myvector.begin() + 5);    // 5 4 3 2 1 6 7 8 9  
																	  //前五个反过来
																	 // print out content:  
			std::cout << "myvector contains:";
			for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
				std::cout << ' ' << *it;
			std::cout << '\n';

			std::string str{ "abcdef" };
			std::reverse(str.begin(), str.end());
			fprintf(stderr, "str: %s\n", str.c_str());
			system("pause");
			/*
			40myvector contains: 5 4 3 2 1 6 7 8 9
			str: fedcba
	*/
		}
	 }
	 // Check the order in which bytes are stored in computer memory.
	bool IsLittleEndian();
	bool IsBigEndian();
	{
	1． Little-endian：将低序字节存储在起始地址（低位编址）
	2． Big-endian：将高序字节存储在起始地址（高位编址）
	  一、大端和小端的问题

	对于整型、长整型等数据类型，Big endian 认为第一个字节是最高位字节（按照从低地址到高地址的顺序存放数据的高位字节到低位字节）；而 Little endian 则相反，它认为第一个字节是最低位字节（按照从低地址到高地址的顺序存放据的低位字节到高位字节）。

	例如，假设从内存地址 0x0000 开始有以下数据：  
	0x0000         0x0001       0x0002       0x0003  
	0x12            0x34           0xab           0xcd 
	如果我们去读取一个地址为 0x0000 的四个字节变量，若字节序为big-endian，则读出结果为0x1234abcd；若字节序为little-endian，则读出结果为0xcdab3412。

	如果我们将0x1234abcd 写入到以 0x0000 开始的内存中，则Little endian 和 Big endian 模式的存放结果如下：  
	地址           0x0000         0x0001        0x0002          0x0003 
	big-endian   0x12           0x34            0xab            0xcd  
	little-endian  0xcd           0xab            0x34            0x12

	一般来说，x86 系列 CPU 都是 little-endian 的字节序，PowerPC 通常是 big-endian，网络字节顺序也是 big-endian还有的CPU 能通过跳线来设置 CPU 工作于 Little endian 还是 Big endian 模式。

	对于0x12345678的存储：

	小端模式：（从低字节到高字节）
	地位地址 0x78 0x56 0x34 0x12 高位地址

	大端模式：（从高字节到低字节）
	地位地址 0x12 0x34 0x56 0x78 高位地址
	}
	T LittleEndianToNative(const T x);//先判断那种类型，再反转
	template <typename T>
	T BigEndianToNative(const T x);
	template <typename T>
	T NativeToLittleEndian(const T x);
	template <typename T>
	T NativeToBigEndian(const T x);
	T ReadBinaryLittleEndian(std::istream* stream) 
	{
	  T data_little_endian;
	  //将stream中的内容写到data_little_endian ，只写sizeof（T）个字节
	  stream->read(reinterpret_cast<char*>(&data_little_endian), sizeof(T));
	  return LittleEndianToNative(data_little_endian);
	} 
	template <typename T>
	void WriteBinaryLittleEndian(std::ostream* stream, const T& data) 
	{
	  const T data_little_endian = NativeToLittleEndian(data);
	  //与上述相反，
	  stream->write(reinterpret_cast<const char*>(&data_little_endian), sizeof(T));
	}
	//重载
	void WriteBinaryLittleEndian(std::ostream* stream, const std::vector<T>& data)
	 {//容器遍历
	  for (const auto& elem : data) {
		WriteBinaryLittleEndian<T>(stream, elem);
	  }
	}
 }