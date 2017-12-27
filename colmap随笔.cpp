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
 #include "bitmap.h"
 {
	template <typename T>
struct BitmapColor {
  BitmapColor();//默认初始化颜色
  BitmapColor(const T r, const T g, const T b);//给定初始化颜色

  template <typename D>
  BitmapColor<D> Cast() const;
  /*颜色数据类型转换 比如BitmapColor<float> color1(1.1, 2.9, -3.0);
                    BitmapColor<uint8_t> color2 = color1.Cast<uint8_t>();
     将float转化为uint8_t类型*/

  bool operator==(const BitmapColor<T>& rhs) const;//运算符重载
  bool operator!=(const BitmapColor<T>& rhs) const;

  template <typename D>
  friend std::ostream& operator<<(std::ostream& output,
                                  const BitmapColor<D>& color);//运算符重载。输出颜色

  T r;
  T g;
  T b;
};

// Wrapper class around FreeImage bitmaps.
class Bitmap {
 public:
  Bitmap();//构造位图数据对象

  // Copy constructor.
  Bitmap(const Bitmap& other);
  // Move constructor.
  Bitmap(Bitmap&& other);

  // Create bitmap object from existing FreeImage bitmap object. Note that
  // this class takes ownership of the object.
  explicit Bitmap(FIBITMAP* data);

  // Copy assignment.
  Bitmap& operator=(const Bitmap& other);
  // Move assignment.
  Bitmap& operator=(Bitmap&& other);

  // Allocate bitmap by overwriting the existing data.
  bool Allocate(const int width, const int height, const bool as_rgb);//分配位图的大小和类型

  // Deallocate the bitmap by releasing the existing data.
  void Deallocate();//回收位图资源

  // Get pointer to underlying FreeImage object.
  inline const FIBITMAP* Data() const;//返回数据
  inline FIBITMAP* Data();

  // Dimensions of bitmap.
  inline int Width() const;//返回宽度等等
  inline int Height() const;
  inline int Channels() const;

  // Number of bits per pixel. This is 8 for grey and 24 for RGB image.
  inline unsigned int BitsPerPixel() const;//返回每个像素在位图中占用的大小

  // Scan width of bitmap which differs from the actual image width to achieve
  // 32 bit aligned memory. Also known as pitch or stride. 
  //扫描与实际图像宽度不同的位图宽度，以实现32位对齐的内存。 也被称为俯仰或步幅。
  inline unsigned int ScanWidth() const;

  // Check whether image is grey- or colorscale.
  inline bool IsRGB() const;//判断位图rgb 或灰图
  inline bool IsGrey() const;

  // Number of bytes required to store image.
  size_t NumBytes() const;//存储图片所需要的大小

  // Copy raw image data to array.
  std::vector<uint8_t> ConvertToRawBits() const;
  // 将内存中的一个bit 位原始缓冲块转换为一个FIBITMAP
// ( 首先储存最左上方像素)
  std::vector<uint8_t> ConvertToRowMajorArray() const;//将位图的每个像素的行数据形式保存到一个数组里
  std::vector<uint8_t> ConvertToColMajorArray() const;//先从b通道读取所有像素的b值，g。b

  // Manipulate individual pixels. For grayscale images, only the red element
  // of the RGB color is used.
  bool GetPixel(const int x, const int y, BitmapColor<uint8_t>* color) const;//获取单个像素的颜色值
  bool SetPixel(const int x, const int y, const BitmapColor<uint8_t>& color);//设置每个像素的颜色值

  // Get pointer to y-th scanline, where the 0-th scanline is at the top.
  const uint8_t* GetScanline(const int y) const;

  // Fill entire bitmap with uniform color. For grayscale images, the first
  // element of the vector is used.
  void Fill(const BitmapColor<uint8_t>& color);//用所给的颜色填充整个位图

  // Interpolate color at given floating point position.
  bool InterpolateNearestNeighbor(const double x, const double y,
                                  BitmapColor<uint8_t>* color) const;//获取所给位置像素的 周围像素
  bool InterpolateBilinear(const double x, const double y,
                           BitmapColor<float>* color) const;

  // Extract EXIF information from bitmap. Returns false if no EXIF information
  // is embedded in the bitmap.
  bool ExifFocalLength(double* focal_length);
  bool ExifLatitude(double* latitude);
  bool ExifLongitude(double* longitude);
  bool ExifAltitude(double* altitude);

  // Read bitmap at given path and convert to grey- or colorscale.
  bool Read(const std::string& path, const bool as_rgb = true);

  // Write image to file. Flags can be used to set e.g. the JPEG quality.
  // Consult the FreeImage documentation for all available flags.
  bool Write(const std::string& path,
             const FREE_IMAGE_FORMAT format = FIF_UNKNOWN,
             const int flags = 0) const;

  // Smooth the image using a Gaussian kernel.
  void Smooth(const float sigma_x, const float sigma_y);

  // Rescale image to the new dimensions.
  void Rescale(const int new_width, const int new_height,
               const FREE_IMAGE_FILTER filter = FILTER_BILINEAR);

  // Clone the image to a new bitmap object.
  Bitmap Clone() const;
  Bitmap CloneAsGrey() const;
  Bitmap CloneAsRGB() const;

  // Clone metadata from this bitmap object to another target bitmap object.
  void CloneMetadata(Bitmap* target) const;

  // Read specific EXIF tag.
  bool ReadExifTag(const FREE_IMAGE_MDMODEL model, const std::string& tag_name,
                   std::string* result) const;

 private:
  typedef std::unique_ptr<FIBITMAP, decltype(&FreeImage_Unload)> FIBitmapPtr;

  void SetPtr(FIBITMAP* data);

  static bool IsPtrGrey(FIBITMAP* data);
  static bool IsPtrRGB(FIBITMAP* data);
  static bool IsPtrSupported(FIBITMAP* data);

  FIBitmapPtr data_;
  int width_;
  int height_;
  int channels_;
};

// Jet colormap inspired by Matlab. Grayvalues are expected in the range [0, 1]
// and are converted to RGB values in the same range.
class JetColormap {
 public:
  static float Red(const float gray);
  static float Green(const float gray);
  static float Blue(const float gray);

 private:
  static float Interpolate(const float val, const float y0, const float x0,
                           const float y1, const float x1);
  static float Base(const float val);
};



 }
 #include "cache.h"
 {
template <typename key_t, typename value_t>
class LRUCache {
 public:
  LRUCache(const size_t max_num_elems,
           const std::function<value_t(const key_t&)>& getter_func);

  // The number of elements in the cache.
  size_t NumElems() const;
  size_t MaxNumElems() const;

  // Check whether the element with the given key exists.
  bool Exists(const key_t& key) const;

  // Get the value of an element either from the cache or compute the new value.
  const value_t& Get(const key_t& key);
  value_t& GetMutable(const key_t& key);

  // Manually set the value of an element. Note that the ownership of the value
  // is moved to the cache, which invalidates the object on the caller side.
  virtual void Set(const key_t& key, value_t&& value);

  // Pop least recently used element from cache.
  virtual void Pop();

  // Clear all elements from cache.
  virtual void Clear();

 protected:
  typedef typename std::pair<key_t, value_t> key_value_pair_t;
  typedef typename std::list<key_value_pair_t>::iterator list_iterator_t;

  // Maximum number of least-recently-used elements the cache remembers.
  const size_t max_num_elems_;

  // List to keep track of the least-recently-used elements.
  std::list<key_value_pair_t> elems_list_;

  // Mapping from key to location in the list.
  std::unordered_map<key_t, list_iterator_t> elems_map_;

  // Function to compute new values if not in the cache.
  const std::function<value_t(const key_t&)> getter_func_;
};

// Least Recently Used cache implementation that is constrained by a maximum
// memory limitation of its elements. Whenever the memory limit is exceeded, the
// least recently used (by Get and GetMutable) is deleted. Each element must
// implement a `size_t NumBytes()` method that returns its size in memory.
template <typename key_t, typename value_t>
class MemoryConstrainedLRUCache : public LRUCache<key_t, value_t> {
 public:
  MemoryConstrainedLRUCache(
      const size_t max_num_bytes,
      const std::function<value_t(const key_t&)>& getter_func);

  size_t NumBytes() const;
  size_t MaxNumBytes() const;
  void UpdateNumBytes(const key_t& key);

  void Set(const key_t& key, value_t&& value) override;
  void Pop() override;
  void Clear() override;

 private:
  using typename LRUCache<key_t, value_t>::key_value_pair_t;
  using typename LRUCache<key_t, value_t>::list_iterator_t;
  using LRUCache<key_t, value_t>::max_num_elems_;
  using LRUCache<key_t, value_t>::elems_list_;
  using LRUCache<key_t, value_t>::elems_map_;
  using LRUCache<key_t, value_t>::getter_func_;

  const size_t max_num_bytes_;
  size_t num_bytes_;
  std::unordered_map<key_t, size_t> elems_num_bytes_;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation
////////////////////////////////////////////////////////////////////////////////

template <typename key_t, typename value_t>
//getter_func为lamber表达式，用来查找键值，如果没有的话，则新增键值对
LRUCache<key_t, value_t>::LRUCache(
    const size_t max_num_elems,
    const std::function<value_t(const key_t&)>& getter_func)
    : max_num_elems_(max_num_elems), getter_func_(getter_func) {
  CHECK(getter_func);
  CHECK_GT(max_num_elems, 0);
}

template <typename key_t, typename value_t>
size_t LRUCache<key_t, value_t>::NumElems() const {
  return elems_map_.size();//返回数量
}

template <typename key_t, typename value_t>
size_t LRUCache<key_t, value_t>::MaxNumElems() const {
  return max_num_elems_;//缓存中最大存储的数目
}

template <typename key_t, typename value_t>
bool LRUCache<key_t, value_t>::Exists(const key_t& key) const {
  return elems_map_.find(key) != elems_map_.end();//判断是否存在该键值
}

template <typename key_t, typename value_t>
const value_t& LRUCache<key_t, value_t>::Get(const key_t& key) {
  return GetMutable(key);//获取键值，没有则新建
}

template <typename key_t, typename value_t>
value_t& LRUCache<key_t, value_t>::GetMutable(const key_t& key) {
  const auto it = elems_map_.find(key);
  if (it == elems_map_.end()) {
    Set(key, std::move(getter_func_(key)));
    return elems_map_[key]->second;
  } else {
    elems_list_.splice(elems_list_.begin(), elems_list_, it->second);//将elems_list_中的第it->second位插到起始位置
    return it->second->second;
  }
}

template <typename key_t, typename value_t>//设置值
void LRUCache<key_t, value_t>::Set(const key_t& key, value_t&& value) {
  auto it = elems_map_.find(key);
  elems_list_.push_front(key_value_pair_t(key, std::move(value)));
  if (it != elems_map_.end()) {
    elems_list_.erase(it->second);
    elems_map_.erase(it);
  }
  elems_map_[key] = elems_list_.begin();
  if (elems_map_.size() > max_num_elems_) {
    Pop();
  }
}

template <typename key_t, typename value_t>//弹出最后压入得值
void LRUCache<key_t, value_t>::Pop() {
  if (!elems_list_.empty()) {
    auto last = elems_list_.end();
    --last;
    elems_map_.erase(last->first);
    elems_list_.pop_back();
  }
}

template <typename key_t, typename value_t>//清除所有
void LRUCache<key_t, value_t>::Clear() {
  elems_list_.clear();
  elems_map_.clear();
}

template <typename key_t, typename value_t>
MemoryConstrainedLRUCache<key_t, value_t>::MemoryConstrainedLRUCache(
    const size_t max_num_bytes,
    const std::function<value_t(const key_t&)>& getter_func)
    : LRUCache<key_t, value_t>(std::numeric_limits<size_t>::max(), getter_func),
      max_num_bytes_(max_num_bytes),
      num_bytes_(0) {
  CHECK_GT(max_num_bytes, 0);
}

template <typename key_t, typename value_t>
size_t MemoryConstrainedLRUCache<key_t, value_t>::NumBytes() const {
  return num_bytes_;
}

template <typename key_t, typename value_t>
size_t MemoryConstrainedLRUCache<key_t, value_t>::MaxNumBytes() const {
  return max_num_bytes_;
}

template <typename key_t, typename value_t>
void MemoryConstrainedLRUCache<key_t, value_t>::Set(const key_t& key,
                                                    value_t&& value) {
  auto it = elems_map_.find(key);
  elems_list_.push_front(key_value_pair_t(key, std::move(value)));
  if (it != elems_map_.end()) {
    elems_list_.erase(it->second);
    elems_map_.erase(it);
  }
  elems_map_[key] = elems_list_.begin();

  const size_t num_bytes = value.NumBytes();
  num_bytes_ += num_bytes;
  elems_num_bytes_.emplace(key, num_bytes);

  while (num_bytes_ > max_num_bytes_ && elems_map_.size() > 1) {
    Pop();
  }
}

template <typename key_t, typename value_t>
void MemoryConstrainedLRUCache<key_t, value_t>::Pop() {
  if (!elems_list_.empty()) {
    auto last = elems_list_.end();
    --last;
    num_bytes_ -= elems_num_bytes_.at(last->first);
    CHECK_GE(num_bytes_, 0);
    elems_num_bytes_.erase(last->first);
    elems_map_.erase(last->first);
    elems_list_.pop_back();
  }
}

template <typename key_t, typename value_t>
void MemoryConstrainedLRUCache<key_t, value_t>::UpdateNumBytes(
    const key_t& key) {
  auto& num_bytes = elems_num_bytes_.at(key);
  num_bytes_ -= num_bytes;
  CHECK_GE(num_bytes_, 0);
  num_bytes = LRUCache<key_t, value_t>::Get(key).NumBytes();
  num_bytes_ += num_bytes;

  while (num_bytes_ > max_num_bytes_ && elems_map_.size() > 1) {
    Pop();
  }
}

template <typename key_t, typename value_t>
void MemoryConstrainedLRUCache<key_t, value_t>::Clear() {
  LRUCache<key_t, value_t>::Clear();
  num_bytes_ = 0;
  elems_num_bytes_.clear();
}

 }
 