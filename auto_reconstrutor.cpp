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









//特征匹配
RunFeatureMatching()
//预处理并将图片以键值对的形式传入到Match（）函数，image_t的数据类型是unint类型，
void SiftFeatureMatcher::Match(const std::vector<std::pair<image_t, image_t>>& image_pairs)//#include "matching.cc"
{
//检查数据库是否已存在匹配数据
const bool exists_matches =
        cache_->ExistsMatches(image_pair.first, image_pair.second);
const bool exists_inlier_matches =
        cache_->ExistsInlierMatches(image_pair.first, image_pair.second);
/*
如果只存在其中一个匹配或内部匹配项，我们将从头开始重新计算它们并删除现有结果。 
这必须在将作业推送到队列之前完成，否则在将现有结果写入数据库时，数据库约束可能会失败。
*/
 if (exists_inlier_matches) {
      cache_->DeleteInlierMatches(image_pair.first, image_pair.second);
    }

    internal::FeatureMatcherData data;//定义数据匹配变量
    data.image_id1 = image_pair.first;
    data.image_id2 = image_pair.second;

    if (exists_matches) {
      data.matches = cache_->GetMatches(image_pair.first, image_pair.second);
      cache_->DeleteMatches(image_pair.first, image_pair.second);
      CHECK(verifier_queue_.Push(data));
    } else {
      CHECK(matcher_queue_.Push(data));//将数据加到队列
    }

 for (size_t i = 0; i < num_outputs; ++i) {
    const auto output_job = output_queue_.Pop();//已经处理完匹配数据，不知道具体匹配函数在哪执行的，涉及到多线程
    CHECK(output_job.IsValid());
    auto output = output_job.Data();

    if (output.matches.size() < static_cast<size_t>(options_.min_num_inliers)) {
      output.matches = {};
    }

    if (output.two_view_geometry.inlier_matches.size() <
        static_cast<size_t>(options_.min_num_inliers)) {
      output.two_view_geometry = TwoViewGeometry();
    }

    cache_->WriteMatches(output.image_id1, output.image_id2, output.matches);
    cache_->WriteInlierMatches(output.image_id1, output.image_id2,
                               output.two_view_geometry);
  }

  CHECK_EQ(output_queue_.Size(), 0);
}






























