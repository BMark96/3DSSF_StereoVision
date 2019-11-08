# 3DSSF Stereo Vision Homework
Stereo vision project for 3D Sensing and Sensor Fusion subject at ELTE 

## Parameters

## Dataset
Half-size and full-size Reindeer and Art images. Source: http://vision.middlebury.edu/stereo/data/scenes2005

## Experiments:

7 experiments were made with the following parameters. Output disparity maps can be found at disparityMapPath and output pointclouds can be are at pointCloudPath.

| Experiment | leftImagePath | rightImagePath | disparityMapPath | pointCloudPath | mode | windowSize | disparityRange | weight | baseline | focalLength | dmin |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| **Art, Naive, Half** | Input/Art/Half/view1.png | Input/Art/Half/view5.png | Output/Art/DisparityMaps/Naive/Half/DisparityMap.png | Output/Art/Pointclouds/Naive/Half/Pointcloud.asc |  |  |  |  |  |  |  |
| **Art, Naive, Full** | Input/Art/Full/view1.png | Input/Art/Full/view5.png | Output/Art/DisparityMaps/Naive/Full/DisparityMap.png | Output/Art/Pointclouds/Naive/Full/Pointcloud.asc |  |  |  |  |  |  |  |
| **Art, DP, Half** | Input/Art/Half/view1.png | Input/Art/Half/view5.png | Output/Art/DisparityMaps/DP/Half/DisparityMap.png | Output/Art/Pointclouds/DP/Half/Pointcloud.asc |  |  |  |  |  |  |  |
| **Reindeer, Naive, Half** | Input/Reindeer/Half/view1.png | Input/Reindeer/Half/view5.png | Output/Reindeer/DisparityMaps/Naive/Half/DisparityMap.png | Output/Reindeer/Pointclouds/Naive/Half/Pointcloud.asc |  |  |  |  |  |  |  |
| **Reindeer, Naive, Full** | Input/Reindeer/Full/view1.png | Input/Reindeer/Full/view5.png | Output/Reindeer/DisparityMaps/Naive/Full/DisparityMap.png | Output/Reindeer/Pointclouds/Naive/Full/Pointcloud.asc |  |  |  |  |  |  |  |
| **Reindeer, DP, Half** | Input/Reindeer/Half/view1.png | Input/Reindeer/Half/view5.png | Output/Reindeer/DisparityMaps/DP/Half/DisparityMap.png | Output/Reindeer/Pointclouds/DP/Half/Pointcloud.asc |  |  |  |  |  |  |  |
| **Reindeer, DP, Full** | Input/Reindeer/Full/view1.png | Input/Reindeer/Full/view5.png | Output/Reindeer/DisparityMaps/DP/Full/DisparityMap.png | Output/Reindeer/Pointclouds/DP/Full/Pointcloud.asc |  |  |  |  |  |  |  |
