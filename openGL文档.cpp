void glUniform{1234}{fdi ui}(GLint location, TYPE value);
void glUniform{1234}{fdi ui}v(GLint location, GLsizei count,const TYPE * values);
void glUniformMatrix{234}{fd}v(GLint location, GLsizei count,GLboolean transpose,const GLfloat * values);
void glUniformMatrix{2x3,2x4,3x2,3x4,4x2,4x3}{fd}v(GLint location, GLsizei count,GLboolean transpose,
                                                   const GLfloat * values);  P36
{
	
}
 void glPointSize(GLfloat size)
 {
	设置固定的像素大小，如果没有开启GL_PROGRAM_SIZE,那么它将
	被用于设置点的大小。
 }
 
 void glLineWidth(GLfloat width)
 {
	 设置线段的固定宽度。默认值为1.0。这里的width表示线段的宽度，它必须是一个
	 大于0.0的值，否则会产生一个错误的信息。
 }
 void glPolygonMode(GLenum face, GLenum mode)
 {
	 控制多边形的正面与背面绘制模式。参数face必须是GL_FRONT_AND_BACK,而mode可以
	 是GL_POINT,GL_LINE 或者GL_FILL,它们分别设置多边形的绘制模式是点集，轮廓线还是填充
	 模式。默认情况下，正面和背面的绘制都使用填充模式来完成。
 }
 void glFrontFace(GLenum mode)
 {
	控制多边形正面的判断方式。默认模式为GL_CCW,即多边形投影到窗口坐标系之后，
	顶点按照逆时针排序的面作为正面。如果模式为GL_CW,那么采用顺时针方向的面将被认为
	是物体的正面。	
 }
 void glCullFace(GLenum mode)
 {
	 在转换到屏幕空间渲染之前，设置需要抛弃（裁剪）哪一类多边形。mode可以是GL_FRONT,
	 GL_BACK或者GL_FRONT_AND_BACK，分别表示正面、背面或者所有多边形。要使命令
	 生效，我们还需要使用glEnable()和GL_CULL_FACE参数来开启裁剪；之后也可以使用glDisable()
	 和同样的参数来关闭它。
 }
 void glGenBuffers(GLsizei n,GLuint *buffers)
 {
	 返回n个当前未使用的缓存对象名称，并保存到buffers数组中。
	 调用glGenBuffers()完成之后，我们将在buffers中得到一个缓存对象的数组，但是此时这
	 些名称只是徒有其表。它们还不是真正的缓存对象。只有某个名称首次绑定到系统环境中
	 的一个结合点之后，它所对应的缓存对象才会真正创建出来。
	 
 }
 void glBindBuffer(GLenum target,GLuint buffer)
 {
	 将名称为buffer的缓存对象绑定到target所指定的缓存结合点。target必须是OpenGL支持的缓存绑定
	 目标之一，buffer必须是通过glGenBuffers()分配的名称。如果buffer是第一次被绑定，
	 那么它所对应的缓存对象也将同时被创建。
 }
 void glBufferData (GLenum target,GLsizeiptr size,const GLvoid* data,GLenum uasge)
 {
	 为绑定到target的缓存对象分配size大小的存储空间。如果参数data不是NULL，那么
	 将使用data所在额内存区域的内容来初始化整个空间。usage语序应用程序向OpenGL
	 端发出一个提示，只是缓存中的数据可能具备一些特定的用途。
 }
 void glBufferSubData(GLenum target,GLintptr offset,GLsizeiptr size,const GLvoid* data)
 {
	 使用新的数据替换缓存对象中的部分数据。绑定到target的缓存对象要从offset字节处开始
	 需要使用地址为data、大小为size的数据块来进行更新。如果offset和size的总和超出
	 了缓存对象绑定数据的范围，那么将产生一个错误。
 }
 void glClearBufferData（GLenum target,GLenum internalformat,GLenum format,GLenum type,const void*data)
 void glClearBufferSubData（GLenum target,GLenum internalformat,GLintptr offset,GLintptr size,GLenum format,GLenum type,const void*data)
 {
	 清除缓存对象中所有或者部分数据。绑定到target的缓存存储空间将使用data中存储的数据
	 进行填充。format和type分别指定了data对应数据的格式和类型。首先将数据转换到internalformat所指定
	 的格式，然后填充缓存数据的指定区域范围。
	 对于glClearBufferData()来说，整个区域都会被指定的数据所填充。而对于glClearBufferSubData(0
	 来说，填充区域是通过offset和size来指定的，它们分别给出了一字节为单位的其实偏移地址和大小。
 }
 void glCopyBufferSubData(GLenum readtarget,GLenum writetarget,
							GLintptr readoffset,
							GLintprr writeoffset, GLsizeiptr size)
{
	将绑定到readtarget的缓存对象的一部分存储数据拷贝大偶遇writetarget向绑定的缓存
	对象的数据区上。readtarget对应的数据从readoffset位置开始复制size的字节，然后
	拷贝到writetarget对应数据的writeoffset位置。如果readoffset或者writetarget与size的和超出了
	绑定的缓存对象的范围，那么OpenGL会产生一个GL_INVALID_VALUE错误	
}
void glGetBufferSubData(GLenum target, GLintptr offset,
                          GLsizeiptr size, GLvoid * data)
 {
	返回当前绑定到target的缓存对象中的部分或者全部数据。起始数据的偏移字节位置为
offset，回读的数据大小为size个字节，它们将从缓存的数据区域拷贝到data所指向的内存
区域中，如果缓存对象当前已经被映射，或者offset和size的和超出了缓存对象数据区域
的范围，那么将提示一个错误。	
 }
 
 void * glMapBuffer(GLenum target, GLenum access)
 {
	将当前绑定到target的缓存对象的整个数据区域映射到客户端的地址空间中。之后可以
根据给定的access策略，通过返回的指针对数据进行直接读或写的操作。如果OpenGL无法将
缓存对象的数据映射出来，那么glMapBuffer()将产生一个错误并且返货NuLL，发生这种情况的
原因可能是与系统相关的，比如可用的虚拟内存过低等。
     调用glMapBuffer（）时会返回一个指针，它将指向绑定到target的缓存对象的数据区域
所对应的内存。	 
 }
 GLboolean glUnmapBuffer(GLenum target)
 {
	 解除glMapBuffer()创建的映射。如果对象数据的内容在映射过程中没有发生损坏，那么glUnmapBuffer()
	 将返回GL_TRUE。发生损坏的原因通常与系统相关，例如屏幕模式发生了改变，这会影响
	 内存的可用性。这种情况下，函数的返回值为GL_FALSE,并且对应的数据内容是不可预测的，
	 应用程序必须考虑到这种几率较低的情形，并且及时对数据进行重新初始化。
 }
 void * glMapBufferRange(GLenum target, GLintptr offset,
                             GLsizeiptr length, GLbitfield access)
{
	将缓存对象数据的全部或者一部分映射到应用程序的地址空间中。target设置了缓存对象
当前绑定的目标。offset和length一起设置了准备映射的数据范围。access是一个位域标识符，
用于描述映射的模式。	
}
void glFlushMappedBufferRange(GLenum target, GLintptr offset, GLsizeiptr length)
{
	通知OpenGL，绑定到target的映射缓存中有offset和length所划分的区域已经发生了修改，
需要立即更新到缓存对象的数据区域中。	
}
void glInvalidateBufferData(GLuint buffer);
void glInvalidateBufferSubData(GLuint buffer, GLintptr offset,GLsizeiptr length)
{
	通知OpenGL，应用程序已经完成对缓存对象中给定范围内容的操作，因此可以随时根据
	实际情况抛弃数据，gllinvalidateBufferSubData()会抛弃名称为buffer的缓存对象中，
	从offset字节处开始共length字节的数据。gllinnvalidataBufferData()会直接抛弃整个
	缓存的数据内容。
}

void glVertexAttribPointer(GLuint index, GLint size,GLenum type, GLboolean normalized,
                             GLsizei stride, const GLvoid *pointer)
 {
	设置顶点属性在index位置可访问的数据值。pointer的起始位置也就是数组中的第一组数据值，
它是以基本计算机单位（例如字节）度量的，由绑定到GL_ARRAY_BUFFER目标的缓存对象中的
地址偏移量确定的。size标志每个顶点中需要更新的元素个数（表示属性向量的元素个数1,2,3,4）。type表示数组中每个元素的数据类型,
nomalized表示顶点数据是否需要在传递到顶点数组之前进行归一化处理。stride表示数组中
两个连续元素之间的偏移字节数。如果stride为0，那么在内存存当中各个数据就是紧密贴合的。	
 }
 void glVertexAttribIPointer(GLuint index, GLint size,GLenum type, GLsizei stride,
                               const GLvoid *pointer)  P82
{
	glVertexAttribPointer类似，只不过是整型传入。
同理 	glVertexAttribLPointer
}
gl_VertexID是一个在OpenGL中是一个内置的变量，每个顶点运行它时它们的gl_VertexID都不一样。我们利用这样的特点，将此作一个索引，得到不同的gl_Position，用以传入下一阶段——栅格化（Rasterize），这样一个三角形就得以显示出来了
void glVertexAttrib{1234}[fds}(GLuint index,TYPE values);    P84
void glVertexAttrib{1234}[fds}v(GLuint index,const TYPE* values);
void glVertexAttrib{1234}[bsifd ub us ui}v(GLuint index,const TYPE values);
	{
		设置索引为index的顶点属性的静态值。如果函数名称末尾没有v，那么最多可以
		指定4个参数值，即x y z w参数。如果函数末尾有v，那么最多有4个参数是保存
		在一个数组中传入的，它的地址通过values来指定，存储顺序依次为x,y,z和w分量；
	}
	
void glVertexAttrib4Nub(GLuint index, GLubyte x, GLubyte y,
GLubyte z, GLubyte w);          P85
void glVertexAttrib4N{bsi ub us ui}v(GLuint index,
const TYPE *v);
{
	
}

void glVertexAttribI{1234}{i ui}(GLuint index, TYPE values); P85
void glVertexAttribI{123}{i ui}v(GLuint index,const TYPE *values);
void glVertexAttribI4{bsi ub us ui}v(GLuint index,const TYPE *values);
	{
		
	}

void glVertexAttribL{1234}(GLuint index, TYPE values);
void glVertexAttribL{1234}v(GLuint index, const TYPE *values);
	{
		
	}
void glDrawArrays(GLenum mode, GLint first, GLsizei count); P86
{
	
}
void glDrawElements(GLenum mode, GLsizei count,
                    GLenum type, const GLvoid *indices);  P86
					{
						
					}
void glDrawElementsBaseVertex(GLenum mode, GLsizei count,GLenum type,
                                const GLvoid *indices,GLint basevertex);
								{
									
								}
void glDrawRangeElements(GLenum mode, GLuint start,GLuint end, GLsizei count,
							GLenum type,
							const GLvoid *indices);	
							{
								
							}
void glDrawRangeElementsBaseVertex(GLenum mode,
							GLuint start, GLuint end,
							GLsizei count,
							GLenum type,
							const GLvoid *indices,
							GLint basevertex);
							{
								
							}	
void glDrawArraysIndirect(GLenum mode,
                       const GLvoid *indirect);	    P88
					   {
						   
					   }
void glPrimitiveRestartIndex(GLuint index)   P93
{
	
}
void glDrawArraysInstanced(GLenum mode, GLint first,
                           GLsizei count, GLsizei primCount); P96
						   {
	Draws primCount instances of the geometric primitives specified by mode,
	first, and count as if specified by individual calls to glDrawArrays(). The
	built-in variable gl_InstanceID is incremented for each instance, and
	new values are presented to the vertex shader for each instanced vertex
	attribute.	
						   }
void glDrawElementsInstanced(GLenum mode, GLsizei count,
							GLenum type,
							const void* indices,
							GLsizei primCount);
							{
	Draws primCount instances of the geometric primitives specified by mode,
	count and indices as if specified by individual calls to glDrawElements().
	As with glDrawArraysInstanced(), the built-in variable gl_InstanceID
	is incremented for each instance, and new values are presented to the
	vertex shader for each instanced vertex attribute.	
							}
void glDrawElementsInstancedBaseVertex(GLenum mode,
							GLsizei count,
							GLenum type,
							const void* indices,
							GLsizei instanceCount,
							GLuint baseVertex);
							{
	Draws instanceCount instances of the geometric primitives specified by
	mode, count, indices, and baseVertex as if specified by individual calls to
	glDrawElementsBaseVertex(). As with glDrawArraysInstanced(), the
	built-in variable gl_InstanceID is incremented for each instance, and
	new values are presented to the vertex shader for each instanced vertex
	attribute.
							}	
void glVertexAttribDivisor(GLuint index, GLuint divisor)  P97
{
	Specifies the rate at which new values of the instanced the vertex
	attribute at index are presented to the vertex shader during instanced
	rendering. A divisor value of 0 turns off instancing for the specified
	attribute, whereas any other value of divisor indicates that a new value
    should be presented to the vertex shader each divisor instances.
}
void glDrawArraysInstancedBaseInstance(GLenum mode,
								GLint first,
								GLsizei count,
								GLsizei instanceCount,
								GLuint baseInstance);
								{
		Draws primCount instances of the geometric primitives specified by mode,
first, and count as if specified by individual calls to glDrawArrays(). The
built-in variable gl_InstanceID is incremented for each instance, and
new values are presented to the vertex shader for each instanced vertex
attribute. Furthermore, the implied index used to fetch any instanced
vertex attributes is offset by the value of baseInstance by OpenGL.	
								}	
void glDrawElementsInstancedBaseInstance(GLenum mode,
							GLsizei count,
							GLenum type,
							const GLvoid * indices,
							GLsizei instanceCount,
							GLuint baseInstance);	  P101
							{
		Draws primCount instances of the geometric primitives specified by mode,
count, and indices as if specified by individual calls to glDrawElements().
As with glDrawArraysInstanced(), the built-in variable gl_InstanceID
is incremented for each instance, and new values are presented to the
vertex shader for each instanced vertex attribute. Furthermore, the
implied index used to fetch any instanced vertex attributes is offset by
the value of baseInstance by OpenGL.
							}							