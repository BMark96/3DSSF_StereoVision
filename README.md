# 3DSSF Stereo Vision Homework
Stereo vision project for 3D Sensing and Sensor Fusion subject at ELTE.

## Tasks
1. Stereo matching and disparity map calculation using naive approach and dynamic programming.
2. Pointcloud generation from disparity map.

## Program parameters
| ID | Variable name | Value |
| --- | --- | --- |
| 1 | leftImagePath | Path of left image |
| 2 | rightImagePath | Path of right image |
| 3 | disparityMapPath | Path to save disparity map to |
| 4 | pointCloudPath | Path to save pointcloud to |
| 5 | mode | Running stereo matching using naive approach or dynamic programming. Values: naive or dp |
| 6 | windowSize | Size of window for SAD calculation |
| 7 | disparityRange | Disparity range for naive approach |
| 8 | weight | Lambda value for dp approach |
| 9 | baseline | Given baseline (http://vision.middlebury.edu/stereo/data/scenes2005) |
| 10 | focalLength | Given focalLength (http://vision.middlebury.edu/stereo/data/scenes2005) |
| 11 | dmin | Given dmin value (http://vision.middlebury.edu/stereo/data/scenes2005) |

## Dataset
Half-size and full-size Reindeer and Art images. Source: http://vision.middlebury.edu/stereo/data/scenes2005

## Experiments:

8 experiments were made with the following parameters. Output disparity map can be found at disparityMapPath and output pointclouds can be found at pointCloudPath.

| Experiment | leftImagePath | rightImagePath | disparityMapPath | pointCloudPath | mode | windowSize | disparityRange | weight | baseline | focalLength | dmin |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| **Art, Naive, Half** | Input/Art/Half/view1.png | Input/Art/Half/view5.png | Output/Art/DisparityMaps/Naive/Half/DisparityMap.png | Output/Art/Pointclouds/Naive/Half/Pointcloud.asc | naive | 4 | 128 | 0 | 160 | 3740 | 200 |
| **Art, Naive, Full** | Input/Art/Full/view1.png | Input/Art/Full/view5.png | Output/Art/DisparityMaps/Naive/Full/DisparityMap.png | Output/Art/Pointclouds/Naive/Full/Pointcloud.asc | naive | 4 | 128 | 0 | 160 | 3740 | 200 |
| **Art, DP, Half** | Input/Art/Half/view1.png | Input/Art/Half/view5.png | Output/Art/DisparityMaps/DP/Half/DisparityMap.png | Output/Art/Pointclouds/DP/Half/Pointcloud.asc | dp | 0 | 0 | 4 | 160 | 3740 | 200 |
| **Art, DP, Full** | Input/Art/Full/view1.png | Input/Art/Full/view5.png | Output/Art/DisparityMaps/DP/Full/DisparityMap.png | Output/Art/Pointclouds/DP/Full/Pointcloud.asc | dp | 0 | 0 | 4 | 160 | 3740 | 200 |
| **Reindeer, Naive, Half** | Input/Reindeer/Half/view1.png | Input/Reindeer/Half/view5.png | Output/Reindeer/DisparityMaps/Naive/Half/DisparityMap.png | Output/Reindeer/Pointclouds/Naive/Half/Pointcloud.asc | naive | 4 | 128 | 0 | 160 | 3740 | 230 |
| **Reindeer, Naive, Full** | Input/Reindeer/Full/view1.png | Input/Reindeer/Full/view5.png | Output/Reindeer/DisparityMaps/Naive/Full/DisparityMap.png | Output/Reindeer/Pointclouds/Naive/Full/Pointcloud.asc | naive | 4 | 128 | 0 | 160 | 3740 | 230 |
| **Reindeer, DP, Half** | Input/Reindeer/Half/view1.png | Input/Reindeer/Half/view5.png | Output/Reindeer/DisparityMaps/DP/Half/DisparityMap.png | Output/Reindeer/Pointclouds/DP/Half/Pointcloud.asc | dp | 0 | 0 | 4 | 160 | 3740 | 230 |
| **Reindeer, DP, Full** | Input/Reindeer/Full/view1.png | Input/Reindeer/Full/view5.png | Output/Reindeer/DisparityMaps/DP/Full/DisparityMap.png | Output/Reindeer/Pointclouds/DP/Full/Pointcloud.asc | dp | 0 | 0 | 4 | 160 | 3740 | 230 |
