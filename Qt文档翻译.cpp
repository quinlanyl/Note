QOffscreenSurface Class
{
/* qoffscreensurface在底层平台代表的是离屏表面。

qoffscreensurface旨在和qopenglcontext搭配来允许OpenGL能够在任意线程渲染而不需要创建一个qwindow。

即使表面通常是可渲染的，表面的像素是不可访问的。qoffscreensurface只能用于创建OpenGL资源如纹理或
帧缓冲对象。

应用程序通常会在一个单独的线程使用qoffscreensurface执行一些耗时的任务，这样是为了避免主线程渲染失速。
在qoffscreensurface的环境中创建的资源可与主OpenGL环境共享。一些常见的用例是用异步的纹理上传或
渲染成qopenglframebufferobject。

如何实现离屏表面将会依赖于底层的平台，但它通常会使用一个像素缓冲区（缓存）。如果平台不能实现或不支持支持屏幕
外表面，qoffscreensurface将内部的使用不可见的qwindow。

注意：由于QOffscreenSurface在某些平台上是由QWindow支持的，所以跨平台的应用程序
 必须确保只在主（GUI）线程上调用create()。 QOffscreenSurface可以安全地用于其他线程上的makeCurrent()，
但是初始化和销毁​​必须总是在主线程（GUI）上进行。
 
 注意：为了创建一个保证与给定的环境和窗口兼容的离屏表面，请确保将格式设置为环境或窗口的实际格式，
也就是从返回的QSurfaceFormat在创建了环境或窗口之后的QOpenGLContext :: format()或QWindow :: format()。将从
QWindow :: requestedFormat()返回的格式传递给setFormat()可能会导致不兼容的屏幕外表面，因为底层
窗口系统接口可能会为窗口和pbuffer曲面提供一组不同的配置。

注意：有些平台可能会使用无表面环境扩展（例如EGL_KHR_surfaceless_context）
可用。在这种情况下，将不存在潜在的本地表面。对于QOffscreenSurface（呈现给FBO，纹理上传）的用例，这不是问题。
另请参阅destroy()。
 */
void QOffscreenSurface :: create()
{
/* 分配与屏幕外表面关联的平台资源。
在这一点上，使用setFormat()设置的表面格式被解析为实际的本地表面。
调用destroy()以在必要时释放平台资源。
注：某些平台需要在主（GUI）线程上调用此函数。
 */
}


}

QOpenGLContext Class
{
/* QOpenGLContext代表一个本地OpenGL环境，使OpenGL能够在QSurface渲染。
也表示在底层OpenGL环境的OpenGL状态。创建一个环境，设置它的屏幕和格式，使之与表面或所要使用的表面相
匹配，如果必要的话可以调用setShareContext()来与其它的环境分享资源，最后调用create()。可以使用返回值
和isValid()来检查环境是否成功初始化。
通过调用makeCurrent()，可以使环境的一个给定的表面变为当前的。当OpenGL渲染完成后，调用swapBuffers()
交换表面的前后缓冲区，以使新渲染的内容变得可见。 为了能够支持某些平台，QOpenGLContext需要在调用swapBuffers()之后再次
调用makeCurrent()，然后开始渲染一个新的框架。

如果环境暂时不需要，比如当应用程序没有呈现时，删除它以释放资源会很有用。 您可以连接
到aboutToBeDestroyed()信号来清理已经从QOpenGLContext本身分配了不同所有权的资源。
一旦QOpenGLContext已经成为当前，你可以通过使用Qt的OpenGL启动器（如QOpenGLFunctions，QOpenGLBuffer，
QOpenGLShaderProgram和QOpenGLFramebufferObject）以独立于平台的方式呈现给它。 也可以直接使用该平台
的OpenGL API，而不使用Qt启动器，尽管这可能是以可移植性为代价的。 后者在想要使用OpenGL 1.x或
OpenGL ES 1.x时是必需的。

有关OpenGL API的更多信息，请参阅官方的OpenGL文档。

有关如何使用QOpenGLContext的示例，请参阅OpenGL窗口示例。

可以使用moveToThread()将QOpenGLContext移动到不同的线程。 不要从不同于QOpenGLContext对象所属的线程
调用makeCurrent()。一个环境只能在一个线程一个表面上运行，而一个线程一次只能有一个环境。

环境资源共享

一些资源，如帧缓冲区对象，纹理和顶点缓冲区对象可以在环境之间共享。 在调用create()之前使用
setShareContext()来指定环境应共享这些资源。 QOpenGLContext在内部跟踪一个可以使用shareGroup()
访问的QOpenGLContextGroup对象，它可以用来查找给定共享组中的所有环境。 共享组由所有已成功初始化并
与共享组中的现有环境共享的环境组成。 非共享环境具有由单个环境组成的共享组。 */

bool QOpenGLContext :: makeCurrent（QSurface * surface）
{
/* 使当前线程中的环境在给定表面设为当前。 如果成功则返回true。
如果surface为0，这相当于调用doneCurrent()。
避免从不同于QOpenGLContext实例所在的线程中调用此函数。如果您希望从另一个线程使用QOpenGLContext，
则应首先调用确保所在线程中不是当前线程，如有必要，请调用doneCurrent()。 然后在另一个线程中使用
它之前调用moveToThread（otherThread）。
默认情况下，Qt使用一个检查来强制线程关联的上述条件。 通过设置Qt :: AA_DontCheckOpenGLContextThreadAffinity
应用程序属性，仍然可以禁用此检查。 一定要理解从QObject的线程以外使用QObjects的后果，如QObject线程关联文档中所述。
 */
}

void QOpenGLContext :: doneCurrent()
{
/* 使用 0 表面调用makeCurrent。

这导致当前线程中没有环境。

另请参阅makeCurrent()和currentContext()。
 */
}

void QObject :: moveToThread（QThread * targetThread）
{
/* 更改此对象及其子项的线程关联。如果父对象具有父对象，则该对象不能移动。事件处理将继续在目标线程中。
要将对象移动到主线程，使用QApplication :: instance()来检索指向当前应用程序的指针，然后使用
QApplication :: thread()来检索应用程序所在的线程。例如：

  myObject-> moveToThread(QApplication ::instance()->thread());

如果targetThread为零，则停止此对象及其子项的所有事件处理。
请注意，该对象的所有活动计时器将被重置。定时器首先在当前线程中停止，并在targetThread中重新
启动（具有相同的时间间隔）。因此，在线程之间不断移动对象可以无限期地推迟定时器事件。
QEvent :: ThreadChange事件是在线程关联改变之前发送给这个对象的。您可以处理此事件以执行任何
特殊处理。请注意，任何发布到此对象的新事件都将在targetThread中处理。
警告：这个函数不是线程安全的; 当前线程必须与当前线程关联相同。 换句话说，这个函数只能将一个对象
从当前线程“推送”到另一个线程，而不能将任何线程的对象“拉”到当前线程。
 */
}

}

QStandardItemModel class
{
	/*QStandardItemModel类为存储自定义数据提供了一个通用模型。

QStandardItemModel可以用作标准Qt数据类型的存储库。 它是模型/视图类之一，是Qt的模型/视图框架的一部分。

QStandardItemModel提供了一个经典的基于项目的方法来处理模型。 QStandardItemModel中的项目由QStandardItem提供。

QStandardItemModel实现了QAbstractItemModel接口，这意味着该模型可以用来在任何支持该接口的视图中提供数据（如QListView，QTableView和QTreeView，以及您自己的自定义视图）。
 为了提高性能和灵活性，您可能需要继承QAbstractItemModel以支持不同类型的数据存储库。 例如，QDirModel为底层文件系统提供了一个模型接口。
 
 当你想要一个列表或树时，通常会创建一个空的QStandardItemModel，并使用appendRow（）向模型添加项目，使用item（）来访问项目。 如果模型表示一个表，那么通常会将表的维度传递给QStandardItemModel构造函数，并使用setItem（）将项目放入表中。 您还可以使用setRowCount（）和setColumnCount（）来更改模型的尺寸。 要插入项目，使用insertRow（）或insertColumn（），并删除项目，请使用removeRow（）或removeColumn（）。

您可以使用setHorizontalHeaderLabels（）和setVerticalHeaderLabels（）来设置模型的标题标签。

您可以使用findItems（）在模型中搜索项目，并通过调用sort（）对模型进行排序。

调用clear（）从模型中删除所有项目。

   QStandardItemModel创建表的示例用法：*/
***************************************
QStandardItemModel model(4, 4);
for (int row = 0; row < 4; ++row) 
{
    for (int column = 0; column < 4; ++column) 
	{
        QStandardItem *item = new QStandardItem(QString("row %0, column %1").arg(row).arg(column));
        model.setItem(row, column, item);
    }
}

***************************************

/*QStandardItemModel创建树的示例用法：*/
QStandardItemModel model;
QStandardItem *parentItem = model.invisibleRootItem();
for (int i = 0; i < 4; ++i)
	{
      QStandardItem *item = new QStandardItem(QString("item %0").arg(i));
      parentItem->appendRow(item);
      parentItem = item;
    }

************************************
/*在视图上设置模型之后，您通常需要对用户操作（如正在单击的项目）作出反应。 由于QAbstractItemView提供了基于QModelIndex的信号和函数，
因此需要一种方法来获得与给定QModelIndex相对应的QStandardItem，反之亦然。 itemFromIndex（）和indexFromItem（）提供了这个映射。
 itemFromIndex（）的典型用法包括获取视图中当前索引处的项目，并获取与QAbstractItemView信号所携带的索引对应的项目，如QAbstractItemView :: clicked（）。 
 首先将视图的信号连接到类的一个插槽：*/
 
 QTreeView *treeView = new QTreeView(this);
 treeView->setModel(myStandardItemModel);
 connect(treeView, SIGNAL(clicked(QModelIndex)),
        this, SLOT(clicked(QModelIndex)));
		
/*当你收到这个信号的时候，你可以在给定的模型索引上调用itemFromIndex（）来得到一个指向该项目的指针：*/

void MyWidget::clicked(const QModelIndex &index)
{
    QStandardItem *item = myStandardItemModel->itemFromIndex(index);
    // Do stuff with the item ...
}

/*相反，如果要调用将索引作为参数的模型/视图函数，则必须获取项目的QModelIndex。 您可以通过使用模型的indexFromItem（）函数或
通过调用QStandardItem :: index（）来获得索引：*/

treeView->scrollTo(item->index());
/*当然，您不需要使用基于项目的方法; 你可以完全依赖QAbstractItemModel接口在使用模型时，或者根据需要使用两者的组合。

另请参阅QStandardItem，模型/视图编程，QAbstractItemModel，简单树模型示例和项目视图便利类。*/
}

QOpenGLWidget Class
{
	QOpenGLWidget类是一个用于渲染OpenGL图形的小部件。

QOpenGLWidget提供了将OpenGL图形集成到Qt应用程序中的功能。 使用起来非常简单：让你的类继承它，像使用其他QWidget一样使用子类，
除了你选择使用QPainter和标准的OpenGL渲染命令之外。

QOpenGLWidget提供了三个方便的虚拟函数，你可以在你的子类中重新执行典型的OpenGL任务：
paintGL（） - 呈现OpenGL场景。 获取调用时，小部件需要更新。
resizeGL（） - 设置OpenGL视口，投影等。每当小部件被调整大小时（以及第一次显示它，因为所有新创建的小部件自动获取大小调整事件）都会调用它。
initializeGL（） - 设置OpenGL资源和状态。 在第一次调用resizeGL（）或paintGL（）之前调用一次。

如果需要从paintGL（）以外的位置触发重绘（一个典型的例子是使用计时器动画场景），您应该调用小部件的update（）函数来安排更新。

在调用paintGL（），resizeGL（）或initializeGL（）时，您的窗口小部件的OpenGL渲染环境将变为当前状态。如果您需要从其他位置调用标准的OpenGL API函数（例如，在您的Widget构造函数或自己的绘制函数中），
则必须首先调用makeCurrent（）。所有的渲染发生在一个OpenGL帧缓冲区对象中。 makeCurrent（）确保它在环境中绑定。
在paintGL（）中的渲染代码中创建和绑定附加帧缓冲区对象时，请记住这一点。不要用ID 0重新绑定framebuffer。相反，调用defaultFramebufferObject（）来获得应该绑定的ID。

QOpenGLWidget允许在平台支持时使用不同的OpenGL版本和配置文件。只需通过setFormat（）设置请求的格式即可。
请记住，在同一个窗口中有多个QOpenGLWidget实例需要它们都使用相同的格式，或者至少是不能使环境不可共享的格式。
为了解决这个问题，最好使用QSurfaceFormat :: setDefaultFormat（）而不是setFormat（）。

注：在请求OpenGL核心配置文件环境时，在构建QApplication实例之前在某些平台（例如，macOS）上强制调用QSurfaceFormat :: setDefaultFormat（）。 
这是为了确保环境之间的资源共享保持正常工作，因为所有内部环境都是使用正确的版本和配置文件创建的。

Painting Techniques

如上所述，按照以下方式呈现纯3D内容的子类QOpenGLWidget：
  重新实现initializeGL（）和resizeGL（）函数来设置OpenGL状态并提供透视转换。
  重新实现paintGL（）来绘制3D场景，只调用OpenGL函数。
  
也可以使用QPainter将2D图形绘制到QOpenGLWidget子类上：
	在paintGL（）中，不是发出OpenGL命令，而是构造一个QPainter对象以作用于这个widget。
	使用QPainter的成员函数绘制图元。
	直接的OpenGL命令仍然可以发出。 但是，您必须确保通过调用painter（QPainter对象）的beginNativePainting（）和endNativePainting（）来包含它们。
	
当仅使用QPainter进行绘图时，也可以像执行普通小部件那样执行绘画：通过重新实现paintEvent（）。
	重新实现paintEvent（）函数。
	构建一个定位于widget小部件的QPainter对象。 将widget小部件传递给构造函数或QPainter :: begin（）函数。
	使用QPainter的成员函数绘制图元。
	绘画完成后，QPainter实例被销毁。 另外，显式调用QPainter :: end（）。
	
	
OpenGL Function Calls, Headers and QOpenGLFunctions
{
	在进行OpenGL函数调用时，强烈建议避免直接调用函数。相反，更喜欢使用QOpenGLFunctions（制作可移植应用程序时）或版本化（例如，针对现代桌面型OpenGL的QOpenGLFunctions_3_2_Core等）。
	这样，应用程序将在所有Qt构建配置中正常工作，包括执行动态OpenGL实现加载的应用程序，这意味着应用程序不直接链接到GL实现，因此直接函数调用不可行。
    
	在paintGL（）中，通过调用QOpenGLContext :: currentContext（），总是可以访问当前的环境。在这种情况下，可以通过调用QOpenGLContext :: functions（）来获取已经初始化的，
   准备使用的QOpenGLFunctions实例。每次加前缀GL的替代方法是从QOpenGLFunctions继承并在initializeGL（）中调用QOpenGLFunctions :: initializeOpenGLFunctions（）。
   
   至于OpenGL头文件，注意在大多数情况下，不需要直接包含像GL.h这样的头文件。与OpenGL相关的Qt头文件将包含qopengl.h，而qopengl.h将包含适当的系统头文件。
   这可能是一个OpenGL ES 3.x或2.0头，可用的最高版本，或系统提供的gl.h.另外，OpenGL和OpenGL ES都提供了扩展头的副本（在某些系统上称为glext.h），作为Qt的一部分。
   这些将被自动包含在可行的平台上。这意味着来自ARB，EXT，OES扩展的常量和函数指针类型定义是自动可用的。
	
	Code Examples
**********************************
class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

protected:
    void initializeGL()
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        ...
    }

    void resizeGL(int w, int h)
    {
        // Update projection matrix and other size related settings:
        m_projection.setToIdentity();
        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
        ...
    }

    void paintGL()
    {
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClear(GL_COLOR_BUFFER_BIT);
        ...
    }

};
**************************************
class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    ...
    void initializeGL()
    {
        initializeOpenGLFunctions();
        glClearColor(...);
        ...
    }
    ...
};
****************************************
要获得与给定的OpenGL版本或配置文件兼容的环境，或请求深度和模板缓冲区，请调用setFormat（）：
************************************

QOpenGLWidget *widget = new QOpenGLWidget(parent);
QSurfaceFormat format;
format.setDepthBufferSize(24);
format.setStencilBufferSize(8);
format.setVersion(3, 2);
format.setProfile(QSurfaceFormat::CoreProfile);
widget->setFormat(format); // must be called before the widget or its parent window gets shown

***************************************************

使用OpenGL 3.0+环境，当可移植性不重要时，版本化的QOpenGLFunctions变体可以轻松访问给定版本中可用的所有现在OpenGL函数：
 ...
    void paintGL()
    {
        QOpenGLFunctions_3_2_Core *f = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_3_2_Core>();
        ...
        f->glDrawArraysInstanced(...);
        ...
    }
    ...
}

与QGLWidget的关系
{
传统的QtOpenGL模块（以QGL为前缀的类）提供了一个名为QGLWidget的控件。 QOpenGLWidget旨在成为现代化的替代品。因此，特别是在新的应用程序中，一般的建议是使用QOpenGLWidget。

虽然API非常相似，但两者之间有一个重要的区别：QOpenGLWidget总是使用帧缓冲区对象在屏幕外呈现。 QGLWidget另一方面使用本地窗口和表面。后者在将其用于复杂用户界面时会引起问题，因为取决于平台，这样的本地子窗口小部件可能具有各种限制，例如关于堆叠顺序。 QOpenGLWidget通过不创建一个单独的本地窗口来避免这一点。

由于被framebuffer对象支持，QOpenGLWidget的行为与QOpenGLWindow非常相似，其更新行为被设置为PartialUpdateBlit或PartialUpdateBlend。这意味着内容在paintGL（）调用之间保存，所以增量渲染是可能的。与QGLWidget（自然QOpenGLWindow具有默认的更新行为）通常不是这种情况，因为交换缓冲区留下未定义的内容的后台缓冲区。

注：大多数应用程序不需要增量渲染，因为它们将在每次调用paint时在视图中渲染所有内容。在这种情况下，在paintGL（）中尽可能早地调用glClear（）是非常重要的。这有助于使用基于图块的体系结构的移动GPU识别图块缓冲区不需要使用帧缓冲区先前的内容重新加载。忽略清晰的呼叫可能会导致此类系统性能下降。

注意：避免在QOpenGLWidget上调用winId（）。这个函数触发创建一个本地窗口，导致性能降低，并可能出现毛刺。
}

与QGLWidget的差异
{
除了被framebuffer对象支持的主要概念上的区别之外，QOpenGLWidget和旧的QGLWidget之间还有一些较小的内部差异：

调用paintGL（）时的OpenGL状态。 QOpenGLWidget通过glViewport（）设置视口。它不执行任何清除。
清除开始通过QPainter绘画。与常规小部件不同，QGLWidget默认为autoFillBackground的值为true。然后，每次使用QPainter :: begin（）时，都会执行清除调色板的背景颜色。 QOpenGLWidget不遵循这个：autoFillBackground默认为false，就像任何其他小部件。唯一的例外是当被用作其他小部件，如QGraphicsView的视口。在这种情况下，autoFillBackground将自动设置为true，以确保与基于QGLWidget的视口的兼容性。
}

多重采样
{
要启用多重采样，请在传递给setFormat（）的QSurfaceFormat上设置请求的样本数。在不支持它的系统上，请求可能会被忽略。

多重采样支持需要支持多重采样的渲染缓冲区和帧缓冲区溢出。在OpenGL ES 2.0实现中，这些可能不会出现。这意味着多重采样将不可用。随着现代的OpenGL版本和OpenGL ES 3.0，这通常不再是一个问题。
}

Threading
{
在工作线程上执行离线渲染，例如为了生成纹理，然后在paintGL（）的GUI /主线程中使用纹理，通过暴露小部件的QOpenGLContext来支持，
从而可以在每个线程上创建与它共享的额外环境。

通过重新实现paintEvent（）不执行任何操作，直接在GUI /主线程之外直接绘制到QOpenGLWidget的framebuffer是可能的。
环境的线程相关性必须通过QObject :: moveToThread（）进行更改。之后，makeCurrent（）和doneCurrent（）在工作线程上可用。之后小心将环境移回GUI /主线程。

与QGLWidget不同的是，仅仅为QOpenGLWidget触发一个缓冲区交换是不可能的，因为它没有真正的屏幕本地表面。
相反，它由widget堆栈来管理gui线程上的组​​合和缓冲区交换。当线程完成更新帧缓冲区时，调用GUI /主线程上的update（）来调度组合。

在GUI /主线程执行合成时，必须格外小心以避免使用帧缓冲区。当构图开始和结束时，关于ToCompose（）和frameSwapped（）的信号将被发射。
它们在GUI /主线程上发射。这意味着通过使用直接连接aboutToCompose（）可以阻止GUI /主线程，直到工作线程完成其渲染。
之后，工作线程必须执行任何进一步的渲染，直到frameSwapped（）信号被发射。如果这是不可接受的，工作线程必须实现双缓冲机制。
这涉及使用由线程完全控制的替代渲染目标的绘制，例如，一个额外的framebuffer对象，并在适当的时候传送给QOpenGLWidget的framebuffer。

}

Context Sharing
{
当多个QOpenGLWidgets作为子级添加到同一个顶级小部件时，它们的环境将相互共享。这不适用于属于不同窗口的QOpenGLWidget实例。

这意味着同一个窗口中的所有QOpenGLWidget都可以访问对方的可共享资源，比如纹理，而不需要像QGLWidget那样额外的“全局共享”环境。

要设置属于不同窗口的QOpenGLWidget实例之间的共享，请在实例化QApplication之前设置Qt :: AA_ShareOpenGLContexts应用程序属性。
这将触发所有QOpenGLWidget实例之间的共享，而无需任何进一步的步骤。

使用QOpenGLWidget的环境创建共享资源（如纹理）的额外QOpenGLContext实例也是可能的。在调用QOpenGLContext :: create（）之前，
只需将context（）返回的指针传递给QOpenGLContext :: setShareContext（）即可。生成的环境也可以在不同的线程上使用，允许线程生成纹理和异步纹理上传。

请注意，QOpenGLWidget在涉及底层图形驱动程序时期望遵循标准的资源共享实现。例如，一些驱动程序，尤其是移动和嵌入式硬件的驱动程序，
在设置现有环境和稍后创建的其他驱动程序之间的共享方面存在问题。尝试利用不同线程之间的共享资源时，某些其他驱动程序可能会以意外的方式运行。

}

当调用initializeGL（）和paintGL（）时，QOpenGLWidget关联的OpenGL环境保证是当前的。不要在调用initializeGL（）之前尝试创建OpenGL资源。
例如，在子类的构造函数中尝试编译着色器，初始化顶点缓冲区对象或上传纹理数据将失败。这些操作必须推迟到initializeGL（）之后。
一些Qt的OpenGL辅助类，如QOpenGLBuffer或QOpenGLVertexArrayObject，有一个匹配的延迟行为：它们可以在没有环境的情况下被实例化，
但所有的初始化都被推迟到一个create（）或类似的调用之后。这意味着它们可以用作QOpenGLWidget子类中的普通（非指针）成员变量，
但create（）或类似的函数只能从initializeGL（）中调用。但请注意，并非所有的类都是这样设计的。如果有疑问，
请将成员变量指向一个指针，并分别在initializeGL（）和析构函数中动态创建和销毁实例。

释放资源也需要环境是当前的。因此执行这种清理的析构函数在继续破坏任何OpenGL资源或包装之前，都需要调用makeCurrent（）。
避免通过deleteLater（）或QObject的父母机制延迟删除。不能保证在所讨论的实例被真正销毁时正确的环境将是当前的。不能保证在所涉实例真正销毁时，正确的环境是当前的。

因此，在资源初始化和破坏时，典型的子类通常看起来像下面这样：
*************************************************
  class MyGLWidget : public QOpenGLWidget
{
    ...

private:
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;
    QOpenGLShaderProgram *m_program;
    QOpenGLShader *m_shader;
    QOpenGLTexture *m_texture;
};

MyGLWidget::MyGLWidget()
    : m_program(0), m_shader(0), m_texture(0)
{
    // No OpenGL resource initialization is done here.
}

MyGLWidget::~MyGLWidget()
{
    // Make sure the context is current and then explicitly
    // destroy all underlying OpenGL resources.
    makeCurrent();

    delete m_texture;
    delete m_shader;
    delete m_program;

    m_vbo.destroy();
    m_vao.destroy();

    doneCurrent();
}

void MyGLWidget::initializeGL()
{
    m_vao.create();
    if (m_vao.isCreated())
        m_vao.bind();

    m_vbo.create();
    m_vbo.bind();
    m_vbo.allocate(...);

    m_texture = new QOpenGLTexture(QImage(...));

    m_shader = new QOpenGLShader(...);
    m_program = new QOpenGLShaderProgram(...);

    ...
}
***********************************************

这当然不是唯一可能的解决方案。 另一种方法是使用QOpenGLContext的aboutToBeDestroyed（）信号。
 通过使用直接连接的插槽连接到这个信号，每当底层本地环境句柄或者整个QOpenGLContext实例将要被释放时，就可以执行清理。
 以下代码片段原则上相当于上一个代码片段：
 ******************************************
 void MyGLWidget::initializeGL()
{
    // context() and QOpenGLContext::currentContext() are equivalent when called from initializeGL or paintGL.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &MyGLWidget::cleanup);
}

void MyGLWidget::cleanup()
{
    makeCurrent();
    delete m_texture;
    m_texture = 0;
    ...
    doneCurrent();
}
**********************************************

注意：对于在其生命周期内多次更改关联的顶级窗口的小部件，组合的方法至关重要。每当小部件或它的父项被重新设定，以使顶层窗口变得不同时，小部件的关联环境被销毁，并创建一个新的。
然后调用initializeGL（），所有的OpenGL资源都必须重新初始化。由于这个原因，执行正确清理的唯一选择是连接到环境的aboutToBeDestroyed（）信号。
请注意，当发出信号时，环境可能不是当前的环境。因此，在连接的插槽中调用makeCurrent（）是一个好习惯。
此外，必须从派生类的析构函数执行相同的清理步骤，因为连接到信号的插槽在小部件被销毁时不会被调用。

注意：当设置Qt :: AA_ShareOpenGLContexts时，小部件的环境永远不会改变，即使在重新设置时也不会改变，因为小部件的关联纹理也可以从新的顶层的环境中访问。

由于环境共享，适当的清理尤为重要。即使每个QOpenGLWidget的关联环境与QOpenGLWidget一起被销毁，
该环境中的可共享资源（如纹理）将保持有效，直到QOpenGLWidget所在的顶级窗口被销毁。
另外，像Qt :: AA_ShareOpenGLContexts和一些Qt模块这样的设置可能会触发更广泛的共享环境的空间，
潜在地导致在应用程序的整个生命周期中保持有问题的资源。因此，最安全和最健壮的总是对QOpenGLWidget中使用的所有资源和资源包装进行显式清理。

Limitations
{
将其他小部件置于其下并使QOpenGLWidget透明将不会导致预期的结果：下面的小部件将不可见。 
这是因为在实践中，QOpenGLWidget是在所有其他常规的，非OpenGL小部件之前绘制的，所以透视类型的解决方案是不可行的。
 其他类型的布局，如在QOpenGLWidget之上的小部件，将按预期运行。

当绝对必要时，可以通过在QOpenGLWidget上设置Qt :: WA_AlwaysStackOnTop属性来克服此限制。 
不过要注意的是，这会打乱堆栈顺序，例如，在QOpenGLWidget之上不可能有其他的小部件，
所以只能在需要其他小部件可见的半透明QOpenGLWidget的情况下使用。

请注意，这不适用于下面没有其他小部件，目的是要有一个半透明的窗口。 在这种情况下，在顶层窗口中设置Qt :: WA_TranslucentBackground的传统方法就足够了。
 请注意，如果仅在QOpenGLWidget中需要透明区域，那么在启用Qt :: WA_TranslucentBackground后，需要将Qt :: WA_NoSystemBackground重新转换为false。 
 另外，根据系统的不同，通过setFormat（）为QOpenGLWidget的环境请求一个alpha通道也是必要的。

QOpenGLWidget支持多种更新行为，就像QOpenGLWindow一样。 在保存模式下，以前的paintGL（）调用的渲染内容在下一个是可用的，
允许增量渲染。 在非保存模式下，内容丢失，并且预期 paintGL（）的实现 将重绘视图中的所有内容。

在Qt 5.5之前，QOpenGLWidget的默认行为是保存调用paintGL（）之间的渲染内容。 
由于Qt 5.5的默认行为是不保留的，因为这提供了更好的性能，大多数应用程序不需要以前的内容。 
这也类似于基于OpenGL的QWindow的语义，并匹配QOpenGLWindow的默认行为，因为每一帧的颜色和辅助缓冲区都是无效的。 
要恢复保留的行为，请使用PartialUpdate调用setUpdateBehavior（）。
}
Alternatives
{
将一个QOpenGLWidget添加到一个窗口中会打开基于OpenGL的合成的整个窗口。
在某些特殊情况下，这可能不是很理想，而且需要使用单独的本地子窗口的旧QGLWidget风格的行为。
桌面应用程序理解这种方法的局限性（Desktop applications that understand the limitations of this approach）（例如，当涉及到重叠，透明度，滚动视图和MDI区域时），
可以使用带有QWidget :: createWindowContainer（）的QOpenGLWindow。
这是QGLWidget的一个当前替代方法，并且比QOpenGLWidget更快，因为缺少额外的组合步骤。
强烈建议将这种方法的使用限制在没有其他选择的情况下。请注意，此选项不适用于大多数嵌入式和移动平台，
并且在某些桌面平台（例如macOS）上也存在问题。稳定的，跨平台的解决方案总是QOpenGLWidget。
}

OpenGL是Silicon Graphics，Inc.在美国和其他国家的商标。

另请参阅QOpenGLFunctions，QOpenGLWindow，Qt :: AA_ShareOpenGLContexts和UpdateBehavior。
}

QOpenGLBuffer Class
{
	QOpenGLBuffer类提供了用于创建和管理OpenGL缓冲区对象的函数。

缓冲区对象在OpenGL服务器中创建，以便客户端应用程序可以避免每次需要时上传顶点，索引，纹理图像数据等。

QOpenGLBuffer对象可以作为底层OpenGL缓冲区对象的引用进行复制：

 /*        QOpenGLBuffer buffer1(QOpenGLBuffer::IndexBuffer);
		buffer1.create();

		QOpenGLBuffer buffer2 = buffer1; */
		
		当以这种方式复制对象时，QOpenGLBuffer执行浅拷贝，但不实现即写即拷贝语义。 每当修改副本时，原始对象都会受到影响。
		
		enum QOpenGLBuffer::Type
		{
			Constant	                    Value	Description
			QOpenGLBuffer::VertexBuffer	    0x8892	Vertex buffer object for use when specifying vertex arrays.
			QOpenGLBuffer::IndexBuffer	    0x8893	Index buffer object for use with glDrawElements().
			QOpenGLBuffer::PixelPackBuffer	0x88EB	Pixel pack buffer object for reading pixel data from the OpenGL server (for example, with glReadPixels()). Not supported under OpenGL/ES.（用于从OpenGL服务器读取像素数据的像素包缓冲区对象（例如，使用glReadPixels（））。 在OpenGL / ES下不受支持。）
			QOpenGLBuffer::PixelUnpackBuffer 0x88EC	Pixel unpack buffer object for writing pixel data to the OpenGL server (for example, with glTexImage2D()). Not supported under OpenGL/ES.（像素解压缓冲区对象，用于将像素数据写入OpenGL服务器（例如，使用glTexImage2D（））。 在OpenGL / ES下不受支持。）

		}
		
		bool QOpenGLBuffer::create()
		{
			在OpenGL服务器中创建缓冲区对象。 如果创建了对象，则返回true; 否则为假。

			这个函数必须用当前的QOpenGLContext来调用。 缓冲区将被绑定并且只能在该context中使用（或者与其共享的任何其他context）。

			如果OpenGL的实现 不支持缓冲区，或者没有当前的QOpenGLContext，则此函数将返回false。
		}
		
		bool QOpenGLBuffer::bind()
		{
			将与此对象关联的缓冲区绑定到当前的OpenGLcontext。 如果绑定不可行，则返回false，通常是因为此OpenGL实现不支持type（）。

            调用create（）时，必须将缓冲区绑定到相同的QOpenGLContext，或者与另一个与之共享的QOpenGLContext绑定。 否则，这个函数返回false。
		}
		
		void QOpenGLBuffer::allocate(const void *data, int count)
		{
			将计数字节的空间分配给缓冲区，初始化为数据内容。 任何以前的内容将被删除。

            假设这个缓冲区已经调用了create（），并且已经绑定了当前的context。
		}
		
}

QVector3D class
{
	QVector3D类表示3D空间中的矢量或顶点。
	向量是3D表示和绘图的主要构件之一。 它们由三个坐标组成，传统上称为x，y和z。
	QVector3D类也可以用来表示3D空间中的顶点。 因此我们不需要提供一个单独的顶点类。
}

 QOpenGLShaderProgram class 
 {
	 QOpenGLShaderProgram类允许OpenGL着色器程序被链接和使用。
	 
	 该类支持以OpenGL着色语言（GLSL）和OpenGL / ES着色语言（GLSL / ES）编写的着色器程序。

	QOpenGLShader和QOpenGLShaderProgram为程序员提供了编译和链接顶点和片段着色器的细节。

	以下示例使用提供的源代码创建顶点着色器程序。 编译和链接后，通过调用QOpenGLShaderProgram :: bind（），在当前的QOpenGLContext中激活着色器程序：
				
				/* QOpenGLShader shader(QOpenGLShader::Vertex);
				shader.compileSourceCode(code);

				QOpenGLShaderProgram program(context);
				program.addShader(&shader);
				program.link();

				program.bind(); */
				
编写便携式着色器
{
		由于对标准顶点属性和统一变量的支持程度不同，Shader程序可能难以在OpenGL实现中重用。 
		特别是，GLSL / ES缺少桌面OpenGL系统上的所有标准变量：gl_Vertex，gl_Normal，gl_Color等等。
		 桌面OpenGL缺少变量限定符highp，mediump和lowp。

		QOpenGLShaderProgram类通过在桌面OpenGL上添加以下几行代码前缀所有着色器程序，使得编写便携式着色器的过程变得更加简单：

			   #define highp
				#define mediump
				#define lowp
		
		这使得在桌面系统上运行大多数GLSL / ES着色器程序成为可能。
		程序员应该将程序限制在GLSL / ES中的特性中，避免使用只能在桌面上工作的标准变量名称。
}

Simple Shader Example
{
				program.addShaderFromSourceCode(QOpenGLShader::Vertex,
				"attribute highp vec4 vertex;\n"
				"uniform highp mat4 matrix;\n"
				"void main(void)\n"
				"{\n"
				"   gl_Position = matrix * vertex;\n"
				"}");
				program.addShaderFromSourceCode(QOpenGLShader::Fragment,
					"uniform mediump vec4 color;\n"
					"void main(void)\n"
					"{\n"
					"   gl_FragColor = color;\n"
					"}");
				program.link();
				program.bind();

				int vertexLocation = program.attributeLocation("vertex");
				int matrixLocation = program.uniformLocation("matrix");
				int colorLocation = program.uniformLocation("color");
				
	在上面的着色器程序激活的情况下，我们可以画一个绿色三角形，如下所示：
	
	static GLfloat const triangleVertices[] = {
												60.0f,  10.0f,  0.0f,
												110.0f, 110.0f, 0.0f,
												10.0f,  110.0f, 0.0f
											   };

		QColor color(0, 255, 0, 255);

		QMatrix4x4 pmvMatrix;
		pmvMatrix.ortho(rect());

		program.enableAttributeArray(vertexLocation);
		program.setAttributeArray(vertexLocation, triangleVertices, 3);
		program.setUniformValue(matrixLocation, pmvMatrix);
		program.setUniformValue(colorLocation, color);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		program.disableAttributeArray(vertexLocation);
}	

Binary Shaders and Programs
{
	二进制着色器可以在QOpenGLShader :: shaderId（）的返回值上使用glShaderBinary（）指定。包含二进制文件的QOpenGLShader实例可以通过addShader（）添加到着色器程序中，并以通常的方式与link（）链接。

二进制程序可以使用glProgramBinaryOES（）来指定programId（）的返回值。然后应用程序应该调用link（），它会注意到程序已经被指定和链接，允许在着色器程序上执行其他操作。着色器程序的id可以使用create（）函数显式创建。

缓存程序二进制文件

从Qt 5.9开始，内置了对磁盘上缓存程序二进制文件的支持。为了启用这个功能，切换到使用addCacheableShaderFromSourceCode（）和addCacheableShaderFromSourceFile（）。使用OpenGL ES 3.xcontext或支持GL_ARB_get_program_binary，这将透明地缓存QStandardPaths :: GenericCacheLocation或QStandardPaths :: CacheLocation下的程序二进制文件。当支持不可用时，调用可缓存的函数变体相当于正常的变体。

注意：某些驱动程序没有可用的二进制格式，即使它们宣传了扩展名或提供了OpenGL ES 3.0。在这种情况下，程序二进制支持将被禁用。
}

int QOpenGLShaderProgram::attributeLocation(const char *name) const
{
	返回该着色器程序的参数列表中属性名称的位置。 如果名称不是该着色器程序的有效属性，则返回-1。
}

void QOpenGLShaderProgram::enableAttributeArray(int location)
{
	在该着色器程序中启用该位置处的顶点数组，以便 在此位置处被setAttributeArray（）设置的 值 能被着色器程序使用。
}

void QOpenGLShaderProgram::setAttributeBuffer(int location, GLenum type, int offset, int tupleSize, int stride = 0)
{
	在此着色器程序中的位置属性上设置顶点值的数组，从当前绑定的顶点缓冲区中的特定偏移量开始。 
	步幅表示顶点之间的字节数。 默认步长值为零表示顶点在数组数组中紧密排列。
	该type表示顶点值数组中元素的类型，通常是GL_FLOAT，GL_UNSIGNED_BYTE等。
	tupleSize表示每个顶点的组件数量：1,2,3或4。
	在位置上调用enableAttributeArray（）时，该数组将变为活动状态。 否则，将使用setAttributeValue（）指定的值来指定位置。
	注意：标准化将被启用。 如果不需要，直接通过QOpenGLFunctions调用glVertexAttribPointer。
}


 }



























