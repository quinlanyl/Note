//特征提取
RunFeatureExtraction() {
    if (sift_options_.estimate_affine_shape || sift_options_.domain_size_pooling) //#include "extraction.h"
    {
        success = ExtractCovariantSiftFeaturesCPU()
    } else if (sift_options_.use_gpu) {
        success = ExtractSiftFeaturesGPU()
    } else {
        success = ExtractSiftFeaturesCPU
    }

    bool ExtractSiftFeaturesCPU(const SiftExtractionOptions &options,
                                const Bitmap &bitmap, FeatureKeypoints *keypoints,//#include "sift.h"
                                FeatureDescriptors *descriptors);
    {
        //建立一个sift提取器指针，vls是一个库 #include “VLFeat/sift.h”
        std::unique_ptr<VlSiftFilt, void (*)(VlSiftFilt *)> sift(
                vl_sift_new(bitmap.Width(), bitmap.Height(), options.num_octaves,//octaves代表的是金字塔的层数？
                            options.octave_resolution, options.first_octave), &vl_sift_delete);
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
        const VlSiftKeypoint *vl_keypoints = vl_sift_get_keypoints(sift.get());
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

    }
}






//特征匹配
RunFeatureMatching()
{
//特征数据计算
void SiftCPUFeatureMatcher::Run() {
  SignalValidSetup();

  while (true) {
    if (IsStopped()) {
      break;
    }

    const auto input_job = input_queue_->Pop();//这条语句会等待图片数据data压入队列，才会往下执行，到这会执行Match()函数，
    if (input_job.IsValid()) {
      auto data = input_job.Data();

      const FeatureDescriptors descriptors1 =
          cache_->GetDescriptors(data.image_id1);//获得该图片的描述符
      const FeatureDescriptors descriptors2 =
          cache_->GetDescriptors(data.image_id2);
      MatchSiftFeaturesCPU(options_, descriptors1, descriptors2, &data.matches);//计算

      CHECK(output_queue_->Push(data));
    }
  }
}
//预处理并将图片以键值对的形式传入到Match（）函数，image_t的数据类型是unint类型，
//该函数会构造图片数据，并压入队列
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
      CHECK(matcher_queue_.Push(data));//将数据加到队列，此时回到SiftCPUFeatureMatcher::Run()，继续执行
    }

 for (size_t i = 0; i < num_outputs; ++i) {
    const auto output_job = output_queue_.Pop();//已经处理完匹配数据，
    CHECK(output_job.IsValid());
    auto output = output_job.Data();

    if (output.matches.size() < static_cast<size_t>(options_.min_num_inliers)) {
      output.matches = {};
    }

    if (output.two_view_geometry.inlier_matches.size() <
        static_cast<size_t>(options_.min_num_inliers)) {
      output.two_view_geometry = TwoViewGeometry();
    }

    cache_->WriteMatches(output.image_id1, output.image_id2, output.matches);//写入数据库
    cache_->WriteInlierMatches(output.image_id1, output.image_id2,
                               output.two_view_geometry);
  }

  CHECK_EQ(output_queue_.Size(), 0);
}

//匹配函数的实现
void MatchSiftFeaturesCPU(const SiftMatchingOptions& match_options,
                          const FeatureDescriptors& descriptors1,
                          const FeatureDescriptors& descriptors2,
                          FeatureMatches* matches) {
  CHECK(match_options.Check());
  CHECK_NOTNULL(matches);
//计算特征描述符相应距离，函数实现见下
  const Eigen::MatrixXi dists = ComputeSiftDistanceMatrix(
      nullptr, nullptr, descriptors1, descriptors2, nullptr);


//找到最佳匹配，函数实现见下
  FindBestMatches(dists, match_options.max_ratio, match_options.max_distance,
                  match_options.cross_check, matches);
}

//实现函数ComputeSiftDistanceMatrix
Eigen::MatrixXi ComputeSiftDistanceMatrix(
    const FeatureKeypoints* keypoints1, const FeatureKeypoints* keypoints2,
    const FeatureDescriptors& descriptors1,
    const FeatureDescriptors& descriptors2,
    const std::function<bool(float, float, float, float)>& guided_filter) {
  if (guided_filter != nullptr) {
    CHECK_NOTNULL(keypoints1);
    CHECK_NOTNULL(keypoints2);
    CHECK_EQ(keypoints1->size(), descriptors1.rows());
    CHECK_EQ(keypoints2->size(), descriptors2.rows());
  }
  //转换数据格式，并且只有行信息
  const Eigen::Matrix<int, Eigen::Dynamic, 128> descriptors1_int =
      descriptors1.cast<int>();
  const Eigen::Matrix<int, Eigen::Dynamic, 128> descriptors2_int =
      descriptors2.cast<int>();

  Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> dists(
      descriptors1.rows(), descriptors2.rows());

  for (FeatureDescriptors::Index i1 = 0; i1 < descriptors1.rows(); ++i1) {
    for (FeatureDescriptors::Index i2 = 0; i2 < descriptors2.rows(); ++i2) {
      if (guided_filter != nullptr &&
          guided_filter((*keypoints1)[i1].x, (*keypoints1)[i1].y,
                        (*keypoints2)[i2].x, (*keypoints2)[i2].y)) {
        dists(i1, i2) = 0;
      } else {
        dists(i1, i2) = descriptors1_int.row(i1).dot(descriptors2_int.row(i2));//dists是一个以图1特征描述符的行数为行，以图2特征描述符的行数为列的数组
      }//行向量点乘有什么意义，返回的值是点与点的距离吗？  特征点的欧式距离是点乘吗？。。。这里应该用的是求向量夹角来代替欧式距离，但是并没有除以向量的模长，所以要归一化
    }
  }

  return dists;
}
//最佳匹配函数实现
void FindBestMatches(const Eigen::MatrixXi& dists, const float max_ratio,
                     const float max_distance, const bool cross_check,
                     FeatureMatches* matches) {
  matches->clear();

  std::vector<int> matches12;
  const size_t num_matches12 =
      FindBestMatchesOneWay(dists, max_ratio, max_distance, &matches12);
  //交叉检测
  if (cross_check) {
    std::vector<int> matches21;
    const size_t num_matches21 = FindBestMatchesOneWay(
        dists.transpose(), max_ratio, max_distance, &matches21);
    matches->reserve(std::min(num_matches12, num_matches21));
    for (size_t i1 = 0; i1 < matches12.size(); ++i1) {//最好的匹配
      if (matches12[i1] != -1 && matches21[matches12[i1]] != -1 &&
          matches21[matches12[i1]] == static_cast<int>(i1)) {
        FeatureMatch match;
        match.point2D_idx1 = i1;
        match.point2D_idx2 = matches12[i1];
        matches->push_back(match);//具有稳定性的匹配点
      }
    }
  } else {//否则以第一次检测为标准，压入容器存储
    matches->reserve(num_matches12);
    for (size_t i1 = 0; i1 < matches12.size(); ++i1) {
      if (matches12[i1] != -1) {
        FeatureMatch match;
        match.point2D_idx1 = i1;
        match.point2D_idx2 = matches12[i1];
        matches->push_back(match);
      }
    }
  }

//
size_t FindBestMatchesOneWay(const Eigen::MatrixXi& dists,
                             const float max_ratio, const float max_distance,
                             std::vector<int>* matches) {
  // SIFT descriptor vectors are normalized to length 512.
  const float kDistNorm = 1.0f / (512.0f * 512.0f);//归一化，不然夹角值不好求

  size_t num_matches = 0;
  matches->resize(dists.rows(), -1);
//对所有点逐一匹配，找到最近距离和次近距离
  for (Eigen::MatrixXi::Index i1 = 0; i1 < dists.rows(); ++i1) {
    int best_i2 = -1;
    int best_dist = 0;
    int second_best_dist = 0;
    for (Eigen::MatrixXi::Index i2 = 0; i2 < dists.cols(); ++i2) {
      const int dist = dists(i1, i2);
      if (dist > best_dist) {
        best_i2 = i2;
        second_best_dist = best_dist;//最佳距离找到的怎么是最大距离。不懂
        best_dist = dist;
      } else if (dist > second_best_dist) {
        second_best_dist = dist;
      }
    }

    // Check if any match found.
    if (best_i2 == -1) {
      continue;
    }

    const float best_dist_normed =
        std::acos(std::min(kDistNorm * best_dist, 1.0f));

    // Check if match distance passes threshold.
    if (best_dist_normed > max_distance) {
      continue;
    }

    const float second_best_dist_normed =
        std::acos(std::min(kDistNorm * second_best_dist, 1.0f));

 //如果最佳距离 比上 次佳距离 大于max_ratio(通常设为0.8) 则忽略
    if (best_dist_normed >= max_ratio * second_best_dist_normed) {
      continue;
    }

    num_matches += 1;
    (*matches)[i1] = best_i2;
  }

  return num_matches;
 }
}
}




























