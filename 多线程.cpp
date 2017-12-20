#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

using namespace std;

void exec_proc1(int n)
{
    for (int i = 0; i < 5; ++i) {
        cout << "pass value, executing thread " << n << endl;
        //阻止线程运行到10毫秒
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void exec_proc2(int& n)
{
    for (int i = 0; i < 5; ++i) {
        cout << "pass reference, executing thread " << n << endl;
        ++n;
        //阻止线程运行到10毫秒
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main()
{
    int n = 0;
    // t1，使用默认构造函数，什么都没做
    thread t1;
    // t2，使用有参构造函数，传入函数名称（地址）exec_pro1，并以传值的方式传入args
    // 将会执行exec_proc1中的代码

    thread t2(exec_proc1, n );//只引过来n=0的值，下次还是这个值，并不是去从n地址去调用，除非引用。

    // t3，使用有参构造函数，传入函数名称（地址）exec_pro1，并以传引用的方式传入args
    // 将会执行exec_proc1中的代码
    thread t3(exec_proc2, ref(n));//每次都重新去查看n的地址
    // t4，使用移动构造函数，由t4接管t3的任务，t3不再是线程了
    thread t4(move(t3));
    // 可被 joinable 的 thread 对象必须在他们销毁之前被主线程 join 或者将其设置为 detached.

    t2.join();
    t4.join();
    cout << "the result of n is " << n << endl;
    system("pause");
    return 0;
}

*******************************************************
赋值操作
{
/*
1）move 赋值操作：thread& operator= (thread&& rhs) noexcept，如果当前对象不可 joinable，需要传递一个右值引用(rhs)给 move 赋值操作；如果当前对象可被 joinable，则 terminate() 报错。 
2）拷贝赋值操作被禁用：thread& operator= (const thread&) = delete，thread 对象不可被拷贝。 */
#include <stdio.h>
#include <stdlib.h>
#include <chrono>   
#include <iostream>  
#include <thread>  
using namespace std;

void exec_produce(int duration) {
    //阻止线程运行到duration秒
    this_thread::sleep_for(chrono::seconds(duration));
    //this_thread::get_id()获取当前线程id
    cout << "exec_produce thread " << this_thread::get_id()
        << " has sleeped " << duration << " seconds" << endl;
}

int main(int argc, const char *argv[])
{
    thread threads[5];
    cout << "create 5 threads ..." << endl;
    for (int i = 0; i < 5; i++) {
        threads[i] = thread(exec_produce, i + 1);
    }
    cout << "finished creating 5 threads, and waiting for joining" << endl;
    //下面代码会报错,原因就是copy操作不可用，相当于是delete操作，所以报错
    /*for(auto it : threads) {
        it.join();
    }*/
    for (auto& it: threads) {
        it.join();
    }
    cout << "Finished!!!" << endl;
    system("pause");
    return 0;
}
}
****************************************************************

 std::mutex 的成员函数 
 {
/*1）构造函数，std::mutex不允许拷贝构造，也不允许 move 拷贝，最初产生的 mutex 对象是处于 unlocked 状态的。 
2）lock()，调用线程将锁住该互斥量。线程调用该函数会发生下面 3 种情况：(1). 如果该互斥量当前没有被锁住，则调用线程将该互斥量锁住，
直到调用 unlock之前，该线程一直拥有该锁。(2). 如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住。(3). 如果当前互斥量被当前
调用线程锁住，则会产生死锁(deadlock)。 
3）unlock()， 解锁，释放对互斥量的所有权。 
4）try_lock()，尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞。线程调用该函数也会出现下面 3 种情况，(1). 如果当前
互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量。(2). 如果当前互斥量被其他线程锁住，则当前调用线程
返回 false，而并不会被阻塞掉。(3). 如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)。
  */
#include <iostream>      
#include <thread>      
#include <mutex>  
using namespace std;

/**
就像大家更熟悉的const一样，volatile是一个类型修饰符（type specifier）。
它是被设计用来修饰被不同线程访问和修改的变量。如果不加入volatile，
基本上会导致这样的结果：要么无法编写多线程程序，要么编译器失去大量优化的机会。
**/
volatile int counter = 0; 
const int MAX_TIMES_VALUE = 10000;
mutex my_mutex;           

void my_task() {
    for (int i = 0; i < MAX_TIMES_VALUE; ++ i) {
        //尝试获取锁，try_lock()失败时返回false
        if (my_mutex.try_lock()) {   
            ++counter;
            my_mutex.unlock();
        }
    }
}

int main() {
    thread threads[10];
    for (int i = 0; i < 10; ++ i) {
        threads[i] = thread(my_task);
    }

    for (auto& it : threads) {
        it.join();
    }

    cout << "Finished : the result of counter is " << counter << endl;
    system("pause");
    return 0;
}
}

/****************************************************************************/

std::time_mutex 
{
/* std::time_mutex 比 std::mutex 多了两个成员函数，try_lock_for()，try_lock_until() 
try_lock_for() 函数接受一个时间范围，表示在这一段时间范围之内线程如果没有获得锁则被阻塞住（与 std::mutex 的 try_lock() 不同，try_lock 如果被调用时
没有获得锁则直接返回 false），如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。 
try_lock_until() 函数则接受一个时间点作为参数，在指定时间点未到来之前线程如果没有获得锁则被阻塞住，如果在此期间其他线程释放了锁，则该线程可以获得对
互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 false。 */

#include <iostream>     
#include <chrono>      
#include <thread>  
#include <mutex>  
using namespace std;

timed_mutex my_mutex;

void my_task(int val, char tag) {
    //每200ms尝试获取锁,如果获取到跳出while循环，否则输出一次线程编号
    //比如0-200ms,在200ms之前如果获取不到锁，则线程阻塞，时间到了200ms如果取得了锁，
    //则加锁，否则返回false
    while (!my_mutex.try_lock_for(chrono::milliseconds(200))) {
        //int pid = this_thread::get_id().hash();
        cout << val;
    }
    //成功取得锁，然后将线程sleep到1000ms
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << tag << endl;
    my_mutex.unlock();
}

int main ()
{
    thread threads[10];
    char end_tag[] = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'};
    //创建10个线程，分别执行my_task()中的代码
    for (int i=0; i<10; ++i) {
        threads[i] = thread(my_task, i, end_tag[i]);
    }

    for (auto& it : threads) {
        it.join();
    }
    system("pause");
    return 0;
}
/* 结果分析： 
0-9号线程从0ms时刻开始运行，由于线程调度的随机性，假使最开始运行的是0号线程，则0号线程可以在0ms时刻便取得锁，这时候0号线程持锁sleep，
这时线程调度会去执行1-9号线程，显然这时是无法取得锁的，所以什么调用try_lock_for()在0-200ms内去尝试取锁，在200ms之前由于取不到锁会分别阻塞，
到了200ms这个时刻由于取锁失败，try_lock_for()返回false，所以在200ms这个时刻会在控制台中输出1-9这九个字符，之后类似的，直到到了1000ms这个时刻，
0号线程释放了锁，并输出与其对应的tag。 
之后的过程便成了9个线程的调度执行的过程了，和上面描述基本类似的过程。 */

}

/***********************************************************************************************/

std::lock_guard 
{
	/* 与 mutex RAII 相关，方便线程对互斥量上锁，是一种自解锁。std::lock_guard是一个局部变量，创建时，对mutex 上锁，析构时对mutex解锁。
	这个功能在函数体比较长，尤其是存在多个分支的时候很有用 */
	
#include <iostream>       
#include <thread>        
#include <mutex>         
using namespace std;

mutex my_mutex;

void print (int x) {
    cout << "value is " << x;
    cout << endl; 
    this_thread::sleep_for(chrono::milliseconds(200));
}

void my_task (int id) {
    // lock_guard创建局部变量my_lock，会在lock_guard的构造方法中对my_mutex加锁
    lock_guard<mutex> my_lock (my_mutex);
    //由于自解锁的作用，下面的代码相当于临界区，执行过程不会被打断
    print(id);
    //运行结束时会析构my_lock，然后在析构函数中对my_mutex解锁
}

int main ()
{
    thread threads[10];

    for (int i=0; i<10; ++i) {
        threads[i] = thread(my_task,i+1);
    }

    for (auto& th : threads) {
        th.join();
    }

    system("pause");
    return 0;
}
}

/*********************************************************************************************/

std::unique_lock
{
	/* 与 mutex RAII 相关，方便线程对互斥量上锁，但提供了更好的上锁和解锁控制，相对于std::lock_guard来说，std::unique_lock更加灵活，
	std::unique_lock不拥有与其关联的mutex。构造函数的第二个参数可以指定为std::defer_lock，这样表示在构造unique_lock时，传入的mutex保持unlock状态。
	然后通过调用std::unique_lock对象的lock()方法或者将将std::unique_lock对象传入std::lock()方法来锁定mutex。 
std::unique_lock比std::lock_guard需要更大的空间，因为它需要存储它所关联的mutex是否被锁定，如果被锁定，在析构该std::unique_lock时，
就需要unlock它所关联的mutex。std::unique_lock的性能也比std::lock_guard稍差，因为在lock或unlock mutex时，还需要更新mutex是否锁定的标志。
大多数情况下，推荐使用std::lock_guard但是如果需要更多的灵活性，比如上面这个例子，或者需要在代码之间传递lock的所有权，这可以使用std::unique_lock，
std::unique_lock的灵活性还在于我们可以主动的调用unlock()方法来释放mutex，因为锁的时间越长，越会影响程序的性能，在一些特殊情况下，提前释放mutex可以提高程序执行的效率。 
使用std::unique_lock默认构造方法和std::lock_guard类似，多了可以主动unlock，其他相当于一个自解锁，所以类似于unique_lock my_lock(my_mutex)的用法就不再举例。 */ 

#include <iostream>  
#include <thread>  
#include <mutex>    
using namespace std;

mutex my_mutex;  
mutex some_mutex;

//使用含两个参数的构造函数
void my_task (int n, char c) {
    unique_lock<mutex> my_lock (my_mutex, defer_lock);
    my_lock.lock();
    for (int i=0; i<n; ++i) {
        cout << c;
    }
    cout << endl;
    //会自动unlock
}

unique_lock<mutex> prepare_task()
{
    unique_lock<mutex> lock(some_mutex);

    cout << "print prepare data" << endl;
    //返回对some_mutex的所有权，尚未解锁
    return lock;
}
void finish_task(int v)
{
    //取得prepare_task创建的锁所有权
    unique_lock<mutex> lk(prepare_task());
    cout << "finished :" << v << endl;
    //析构，解锁
}

int main ()
{
    thread t1 (my_task, 50, '1');
    thread t2 (my_task, 50, '2');

    t1.join();
    t2.join();

    thread threads[5];
    for(int i = 0; i < 5; ++ i)
    {
        threads[i] = thread(finish_task, i);
    }
    for(auto& it : threads) {
        it.join();
    }
    system("pause");
    return 0;
}
}