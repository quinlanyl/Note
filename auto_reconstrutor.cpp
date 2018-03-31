//特征提取接口
 if (sift_options_.estimate_affine_shape ||  sift_options_.domain_size_pooling) //#include "extraction.h"
    {
          success = ExtractCovariantSiftFeaturesCPU()
    } 
 else if (sift_options_.use_gpu) 
   {
          success = ExtractSiftFeaturesGPU()
   } 
else 
  {
          success = ExtractSiftFeaturesCPU
  }

bool ExtractSiftFeaturesCPU(const SiftExtractionOptions& options,
                            const Bitmap& bitmap, FeatureKeypoints* keypoints,//#include "sift.h"
                            FeatureDescriptors* descriptors);
{
      //建立一个sift提取器指针，vls是一个库 #include “VLFeat/sift.h”
       std::unique_ptr<VlSiftFilt, void (*)(VlSiftFilt*)> sift(
      vl_sift_new(bitmap.Width(), bitmap.Height(), options.num_octaves,//octaves代表的是金字塔的层数？
                  options.octave_resolution, options.first_octave),&vl_sift_delete);
      //设置峰值阈值
      vl_sift_set_peak_thresh(sift.get(), options.peak_threshold);
      //设置边缘阈值
      vl_sift_set_edge_thresh(sift.get(), options.edge_threshold);



// Iterate through octaves.迭代处理

      //开始处理第一个图片
      //该功能通过在较低octave处计算其高斯尺度空间来开始处理新图像。 它也清空内部关键点缓冲区。
      vl_sift_process_first_octave(sift.get(), data_float.data());
      //处理下一个 octave，该函数计算高斯尺度空间的下一个octave。 注意，这将清除在前一个octave中检测到的任何特征的记录。
      vl_sift_process_next_octave(sift.get())
      //检测特征点，函数检测当前octave中的关键点，填充内部关键点缓冲区。 关键点可以通过:: vl_sift get keypoints（）来获取。
      vl_sift_detect(sift.get());
      //提取检测到的关键点，返回当前关键点的列表指针
      const VlSiftKeypoint* vl_keypoints = vl_sift_get_keypoints(sift.get());
      //返回当前关键点的数目
      const int num_keypoints = vl_sift_get_nkeypoints(sift.get());



//提取每个DOG级别不同方向的特征。

      /********************************************
       。。。。省略一万字
      **********************************************/

//Resize containers for last DOG level in octave.

      /*********************************************
       。。。。。。。
      *******************************************/


      
//确定要保持多少DOG级别以满足max_num_features选项。
      /**********************************************
        。。。。。。。。。。。。
      ***********************************************/


//Extract the features to be kept.

     (*keypoints)[k] = level_keypoints[i][j];//保存在keypoints
     

//计算检测到的关键点的描述符。
     //格式转换
     *descriptors = TransformVLFeatToUBCFeatureDescriptors(*descriptors);//保存在descriptors

    return success
}

//特征提取处理成功，
     if (success) {
          ScaleKeypoints(image_data.bitmap, image_data.camera,
                         &image_data.keypoints);

