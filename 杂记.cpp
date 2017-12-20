 使用_CrtSetDbgFlag检测内存泄露
 {
 #define语句将 CRT 堆函数的基版本映射到对应的“Debug”版本。并非绝对需要该语句，但如果没有该语句，内存泄漏转储包含的有用信息将较少。
在添加了上面所示语句之后，可以通过在程序中包括以下语句来转储内存泄漏信息：
_CrtDumpMemoryLeaks()
#define _CRTDBG_MAP_ALLOC  
  
  
#include <stdlib.h>  
#include <crtdbg.h>  
  
  
  
#define new  new(_CLIENT_BLOCK, __FILE__, __LINE__)  
  
  
		int main()  
		{  
		  
			int* leak = new int[10];  
		  
			_CrtDumpMemoryLeaks();  
		  
			system("pause");  
			return 0;  
		  
		}
 } 
qt， connect参数，Qt::DirectConnection，Qt::QueuedConnection
{
	connect用于连接qt的信号和槽，在qt编程过程中不可或缺。它其实有第五个参数，只是一般使用默认值，
	在满足某些特殊需求的时候可能需要手动设置。
Qt::AutoConnection： 默认值，使用这个值则连接类型会在信号发送时决定。如果接收者和发送者在同一个线程，则自动使用Qt::DirectConnection类型。如果接收者和发送者不在一个线程，则自动使用Qt::QueuedConnection类型。
Qt::DirectConnection：槽函数会在信号发送的时候直接被调用，槽函数运行于信号发送者所在线程。效果看上去就像是直接在信号发送位置调用了槽函数。这个在多线程环境下比较危险，可能会造成奔溃。
Qt::QueuedConnection：槽函数在控制回到接收者所在线程的事件循环时被调用，槽函数运行于信号接收者所在线程。发送信号之后，槽函数不会立刻被调用，等到接收者的当前函数执行完，进入事件循环之后，槽函数才会被调用。多线程环境下一般用这个。
Qt::BlockingQueuedConnection：槽函数的调用时机与Qt::QueuedConnection一致，不过发送完信号后发送者所在线程会阻塞，直到槽函数运行完。接收者和发送者绝对不能在一个线程，否则程序会死锁。在多线程间需要同步的场合可能需要这个。
Qt::UniqueConnection：这个flag可以通过按位或（|）与以上四个结合在一起使用。当这个flag设置时，当某个信号和槽已经连接时，再进行重复的连接就会失败。也就是避免了重复连接。
}	
lambda表达式
{
	C++11 的 lambda 表达式规范如下：

		[ capture ] ( params ) mutable exception attribute -> ret { body }	(1)	 
		[ capture ] ( params ) -> ret { body }	(2)	 
		[ capture ] ( params ) { body }	(3)	 
		[ capture ] { body }	(4)	 
其中

(1) 是完整的 lambda 表达式形式，
(2) const 类型的 lambda 表达式，该类型的表达式不能改捕获("capture")列表中的值。
(3)省略了返回值类型的 lambda 表达式，但是该 lambda 表达式的返回类型可以按照下列规则推演出来：
如果 lambda 代码块中包含了 return 语句，则该 lambda 表达式的返回类型由 return 语句的返回类型确定。
如果没有 return 语句，则类似 void f(...) 函数。
省略了参数列表，类似于无参函数 f()。
mutable 修饰符说明 lambda 表达式体内的代码可以修改被捕获的变量，并且可以访问被捕获对象的 non-const 方法。

exception 说明 lambda 表达式是否抛出异常(noexcept)，以及抛出何种异常，类似于void f() throw(X, Y)。

attribute 用来声明属性。

另外，capture 指定了在可见域范围内 lambda 表达式的代码内可见得外部变量的列表，具体解释如下：
捕获列表：lambda表达式的捕获列表精细控制了lambda表达式能够访问的外部变量，以及如何访问这些变量
1).[]不捕获任何变量。

2).[&]捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。

3).[=]捕获外部作用域中所有变量，并作为副本在函数体中使用(按值捕获)。

4).[=,&foo]按值捕获外部作用域中所有变量，并按引用捕获foo变量。

5).[bar]按值捕获bar变量，同时不捕获其他变量。

6).[this]捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。如果已经使用了&或者=，就默认添加此选项。捕获this的目的是可以在lamda中使用当前类的成员函数和成员变量。

/* 
[a,&b] a变量以值的方式呗捕获，b以引用的方式被捕获。
[this] 以值的方式捕获 this 指针。
[&] 以引用的方式捕获所有的外部自动变量。
[=] 以值的方式捕获所有的外部自动变量。
[] 不捕获外部的任何变量。 */
此外，params 指定 lambda 表达式的参数。

一个具体的 C++11 lambda 表达式例子：

		class A  
		{  
		public:  
			int i_ = 0;  
			  
			void func(int x,int y){  
				auto x1 = [] { return i_; };                             //error,没有捕获外部变量  
				auto x2 = [=] { return i_ + x + y; };               //OK  
				auto x3 = [&] { return i_ + x + y; };               //OK  
				auto x4 = [this] { return i_; };                        //OK  
				auto x5 = [this] { return i_ + x + y; };            //error,没有捕获x,y  
				auto x6 = [this, x, y] { return i_ + x + y; };    //OK  
				auto x7 = [this] { return i_++; };                   //OK  
		};  
		  
		int a=0 , b=1;  
		auto f1 = [] { return a; };                            //error,没有捕获外部变量      
		auto f2 = [&] { return a++ };                      //OK  
		auto f3 = [=] { return a; };                         //OK  
		auto f4 = [=] {return a++; };                     //error,a是以复制方式捕获的，无法修改  
		auto f5 = [a] { return a+b; };                     //error,没有捕获变量b  
		auto f6 = [a, &b] { return a + (b++); };      //OK  
		auto f7 = [=, &b] { return a + (b++); };     //OK  
}
}
unique_ptr相关用法
{
	<code class=" hljs cpp">#include <iostream>
#include <memory>
 
int main () {
  std::unique_ptr<int> foo;
  std::unique_ptr<int> bar;
 
  foo = std::unique_ptr<int>(new int (101));  // rvalue
 
  bar = std::move(foo);                       // using std::move
 
  std::cout << "foo: ";
  if (foo) std::cout << *foo << '\n'; else std::cout << "empty\n";
 
  std::cout << "bar: ";
  if (bar) std::cout << *bar << '\n'; else std::cout << "empty\n";
 
  return 0;
}</int></int></int></memory></iostream></code>
/* 输出： 
foo: empty 
bar: 101 
唯一需要说明的就是std::move后，foo变为了empty，如果对于这个empty再做一些操作的话，就会导致一些灾难了。

其实说白了，就是摧毁原来的指针，并把新指针指向原来指针指向的对象。。。。

那么接下来reset方法即出厂了，到达上面的效果： */

<code class=" hljs cpp">#include <iostream>
#include <memory>
 
int main () {
  std::unique_ptr<int> up;  // empty
 
  up.reset (new int);       // takes ownership of pointer
  *up=5;
  std::cout << *up << '\n';
 
  up.reset (new int);       // deletes managed object, acquires new pointer
  *up=10;
  std::cout << *up << '\n';
 
  up.reset();               // deletes managed object
 
  return 0;
}
//输出：
5
10</int></memory></iostream></code>

swap 
我们在vector里就接触过，unique_ptr同样具有这个成员函数： 
Exchanges the contents of the unique_ptr object with those of x, transferring ownership of any managed object between them without destroying either.

最重要的就是没有销毁任何一个：

<code class=" hljs cpp">#include <iostream>
#include <memory>
 
int main () {
  std::unique_ptr<int> foo (new int(10));
  std::unique_ptr<int> bar (new int(20));
 
  foo.swap(bar);
 
  std::cout << "foo: " << *foo << '\n';
  std::cout << "bar: " << *bar << '\n';
 
  return 0;
}
//输出
foo为20
bar为10</int></int></memory></iostream></code>


get 
get很简单，唯一需要注意的就是： 
Notice that a call to this function does not make unique_ptr release ownership of the pointer (i.e., it is still responsible for deleting the managed data at some point). Therefore, the value returned by this function shall not be used to construct a new managed pointer.

最主要的一点就是，智能指针没有释放，即没有失去所有权：

<code class=" hljs cpp">#include <iostream>
#include <memory>
 
int main () {
                                           // foo   bar    p
                                           // ---   ---   ---
  std::unique_ptr<int> foo;                // null
  std::unique_ptr<int> bar;                // null  null
  int* p = nullptr;                        // null  null  null
 
  foo = std::unique_ptr<int>(new int(10)); // (10)  null  null
  bar = std::move(foo);                    // null  (10)  null
  p = bar.get();                           // null  (10)  (10)
  *p = 20;                                 // null  (20)  (20)
  p = nullptr;                             // null  (20)  null
 
  foo = std::unique_ptr<int>(new int(30)); // (30)  (20)  null
  p = foo.release();                       // null  (20)  (30)
  *p = 40;                                 // null  (20)  (40)
 
  std::cout << "foo: ";
  if (foo) std::cout << *foo << '\n'; else std::cout << "(null)\n";
 
  std::cout << "bar: ";
  if (bar) std::cout << *bar << '\n'; else std::cout << "(null)\n";
 
  std::cout << "p: ";
  if (p) std::cout << *p << '\n'; else std::cout << "(null)\n";
  std::cout << '\n';
 
  delete p;   // the program is now responsible of deleting the object pointed to by p
              // bar deletes its managed object automatically
 
  return 0;
}</int></int></int></int></memory></iostream></code>

即上面代码提到的，p = bar.get(); 后，bar并非被释放，也就相当于指针p和智能指针bar共同管理一个对象，所以就*p做的一切，都会反应到bar指向的对象上。

这段代码有了一个与get相对比的方法：release

release 
不必多说： 
This call does not destroy the managed object, but the unique_ptr object is released from the responsibility of deleting the object.
 Some other entity must take responsibility for deleting the object at some point. 
重点就是一句话：智能指针被释放。
<code class=" hljs cpp">#include <iostream>
#include <memory>
 
int main () {
  std::unique_ptr<int> auto_pointer (new int);
  int * manual_pointer;
 
  *auto_pointer=10;
 
  manual_pointer = auto_pointer.release();
  // (auto_pointer is now empty)
 
  std::cout << "manual_pointer points to " << *manual_pointer << '\n';
 
  delete manual_pointer;
 
  return 0;
}</int></memory></iostream></code>

最后了，再介绍一个operator bool吧，即unique_ptr有这样一个成员函数，来检查是否为空：
<code class=" hljs cpp">#include <iostream>
#include <memory>
 
 
int main () {
  std::unique_ptr<int> foo;
  std::unique_ptr<int> bar (new int(12));
 
  if (foo) std::cout << "foo points to " << *foo << '\n';
  else std::cout << "foo is empty\n";
 
  if (bar) std::cout << "bar points to " << *bar << '\n';
  else std::cout << "bar is empty\n";
 
  return 0;
}</int></int></memory></iostream></code>
}

unordered_map
{
	1.1 特性

关联性：通过key去检索value，而不是通过绝对地址（和顺序容器不同）
无序性：使用hash表存储，内部无序
Map : 每个值对应一个键值
键唯一性：不存在两个元素的键一样
动态内存管理：使用内存管理模型来动态管理所需要的内存空间

    1.2 Hashtable和bucket

由于unordered_map内部采用的hashtable的数据结构存储，所以，每个特定的key会通过一些特定的哈希运算映射到一个特定的位置，
我们知道，hashtable是可能存在冲突的（多个key通过计算映射到同一个位置），在同一个位置的元素会按顺序链在后面。
所以把这个位置称为一个bucket是十分形象的（像桶子一样，可以装多个元素）
	
	2. 模版

template < class Key,                                    // unordered_map::key_type
           class T,                                      // unordered_map::mapped_type
           class Hash = hash<Key>,                       // unordered_map::hasher
           class Pred = equal_to<Key>,                   // unordered_map::key_equal
           class Alloc = allocator< pair<const Key,T> >  // unordered_map::allocator_type
           > class unordered_map;
		   
 主要使用的也是模板的前2个参数<键，值>

   unordered_map<const Key, T> map;
   
   2.1 迭代器

	unordered_map的迭代器是一个指针，指向这个元素，通过迭代器来取得它的值。

	unordered_map<Key,T>::iterator it;
	(*it).first;             // the key value (of type Key)
	(*it).second;            // the mapped value (of type T)
	(*it);                   // the "element value" (of type pair<const Key,T>)

 它的键值分别是迭代器的first和second属性。

		it->first;               // same as (*it).first   (the key value)
		it->second;              // same as (*it).second  (the mapped value) 
		
	3. 功能函数

3.1 构造函数

unordered_map的构造方式有几种： 
- 构造空的容器 
- 复制构造 
- 范围构造 
- 用数组构造

3.1.2示例代码
// constructing unordered_maps
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

typedef unordered_map<string,string> stringmap;

stringmap merge (stringmap a,stringmap b) {
  stringmap temp(a); temp.insert(b.begin(),b.end()); return temp;
}

int main ()
{
  stringmap first;                              // 空
  stringmap second ( {{"apple","red"},{"lemon","yellow"}} );       // 用数组初始
  stringmap third ( {{"orange","orange"},{"strawberry","red"}} );  // 用数组初始
  stringmap fourth (second);                    // 复制初始化
  stringmap fifth (merge(third,fourth));        // 移动初始化
  stringmap sixth (fifth.begin(),fifth.end());  // 范围初始化

  cout << "sixth contains:";
  for (auto& x: sixth) cout << " " << x.first << ":" << x.second;
  cout << endl;

  return 0;
}	
/* 输出结果：

sixth contains: apple:red lemon:yellow orange:orange strawberry:red
*/
3.2.1 size

size_type size() const noexcept;//返回unordered_map的大小

3.2.2 empty

bool empty() const noexcept;//- 为空返回true 
                            //- 不为空返回false，和用size() == 0判断一样。

3.3.1 find
iterator find ( const key_type& k );
/* 查找key所在的元素。 
- 找到：返回元素的迭代器。通过迭代器的second属性获取值 
- 没找到：返回unordered_map::end */
3.3.2 insert

插入有几种方式： 
- 复制插入(复制一个已有的pair的内容) 
- 数组插入（直接插入一个二维数组） 
- 范围插入（复制一个起始迭代器和终止迭代器中间的内容） 
- 数组访问模式插入(和数组的[]操作很相似)
3.3.3 at
mapped_type& at ( const key_type& k );
/* 查找key所对应的值 
- 如果存在，返回key对应的值，可以直接修改，和[]操作一样。 
- 如果不存在：抛出 out_of_range 异常. */
//mymap.at(“Mars”) = 3396; //mymap[“Mars”] = 3396

unordered_map::count
{使用特定键计算元素搜索容器的键是k的元素，并返回找到的元素的数量。
 由于unordered_map容器不允许重复键，这意味着如果容器中存在具有该键的元素，
 则该函数实际返回1，否则返回零。
 // unordered_map::count
		#include <iostream>
		#include <string>
		#include <unordered_map>

		int main ()
		{
		  std::unordered_map<std::string,double> mymap = {
			 {"Burger",2.99},
			 {"Fries",1.99},
			 {"Soda",1.50} };

		  for (auto& x: {"Burger","Pizza","Salad","Soda"}) {
			if (mymap.count(x)>0)
			  std::cout << "mymap has " << x << std::endl;
			else
			  std::cout << "mymap has no " << x << std::endl;
		  }

		  return 0;
		}
		/* Output:
				mymap has Burger
				mymap has no Pizza
				mymap has no Salad
				mymap has Soda */
}


}
 
T qobject_cast(QObject *object)
{
	
	如果对象的类型为T（或子类），则返回给定类型的类型转换为T的类型; 否则返回0.如果object是0，那么它也将返回0。
类T必须继承（直接或间接）QObject，并用Q_OBJECT宏声明。
一个类被认为是继承自己。


  QObject *obj = new QTimer;          // QTimer inherits QObject

  QTimer *timer = qobject_cast<QTimer *>(obj);
  // timer == (QObject *)obj

  QAbstractButton *button = qobject_cast<QAbstractButton *>(obj);
  // button == 0
}

enum Qt::WidgetAttribute
{
	这个枚举类型用于指定各种小部件属性。 使用QWidget :: setAttribute（）来设置和清除属性，
	并使用QWidget :: testAttribute（）来查询属性，尽管一些属性具有特殊的便利功能，这些功能将在下面提到。
	
	Qt::WA_Hover 
	{
		强制Qt在鼠标进入或离开小部件时生成绘画事件。 实现自定义样式时通常使用此功能; 有关详细信息，请参阅样式示例。
	}
}
FILE 文件流
{
	fopen

函数原型    FILE * fopen(const char *path,cost char *mode)

作用：打开一个文件，返回指向该文件的指针

参数说明：第一个参数为欲打开文件的文件路径及文件名，第二个参数表示对文件的打开方式

注：mode有以下值：

r：只读方式打开，文件必须存在

r+：可读写，必须存在

rb+：打开二进制文件，可以读写

rt+:打开文本文件，可读写

w:只写，文件存在则文件长度清0，文件不存在则建立该文件

w+:可读写，文件存在则文件长度清0，文件不存在则建立该文件

a:附加方式打开只写，不存在建立该文件，存在写入的数据加到文件尾，EOF符保留

a+：附加方式打开可读写，不存在建立该文件，存在写入的数据加到文件尾，EOF符不保留

wb：打开二进制文件，只写

wb+:打开或建立二进制文件，可读写

wt+:打开或建立文本文件，可读写

at+:打开文本文件，可读写，写的数据加在文本末尾

ab+:打开二进制文件，可读写，写的数据加在文件末尾

由mode字符可知，上述如r、w、a在其后都可以加一个b，表示以二进制形式打开文件

返回值：文件打开了，返回一个指向该打开文件的指针(FILE结构)；文件打开失败，错误上存error code(错误代码)

注意：在fopen操作后要进行判断，是否文件打开，文件真正打开了才能进行后面的读或写操作，如有错误要进行错误处理

例：FILE *pfile=fopen(const char *filename,"rb");

打开文件流还有一个支持宽字符的函数，如下

FILE *_wfopen(const wchar_t *filename,const wchar_t *mode)

fread

函数原型:size_t fread(void* buff,size_t size,size_t count,FILE* stream)

作用：从文件中读入数据到指定的地址中

参数：第一个参数为接收数据的指针(buff),也即数据存储的地址

第二个参数为单个元素的大小，即由指针写入地址的数据大小，注意单位是字节

第三个参数为元素个数，即要读取的数据大小为size的元素个素

第四个参数为提供数据的文件指针，该指针指向文件内部数据

返回值：读取的总数据元素个数

例：

int  num,count;

int* pr=new int[num*count];

fread(pr, num*4, count, stream);   // stream为fopen中返回的FILE指针

要将数据写入pr中，必须为pr分配内存，一个int为4个字节，所以要x4

fseek

函数原型：int fseek(FILE *stream,long offset,int framewhere)

作用：重定位文件内部的指针

参数：第一个为文件指针，第二个是指针的偏移量，第三个是指针偏移起始位置

返回值：重定位成功返回0，否则返回非零值

需要注意的是该函数不是重定位文件指针，而是重定位文件内部的指针，让指向文件内部数据的指针移到文件中我们感兴趣的数据上，重定位主要是这个目的。

说明：执行成功，则stream指向以fromwhere为基准，偏移offset个字节的位置。执行失败(比方说offset偏移的位置超出了文件大小)，则保留原来stream的位置不变

fclose

函数原型：int fclose(FILE *stream)

功能：关闭一个文件流，使用fclose就可以把缓冲区内最后剩余的数据输出到磁盘文件中，并释放文件指针和有关的缓冲区

熟练使用以上四个函数可以从文件中获取对我们有用的数据型，前提对于文件格式很了解，比如，对于一个DIB位图文件，就可以读取出他的文件中的头信息和像素点信息。
}