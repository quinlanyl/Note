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