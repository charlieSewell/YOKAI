#pragma once
#include<glm/glm.hpp>
struct VolumeTileAABB{
    glm::vec4 minPoint = {};
    glm::vec4 maxPoint = {};
};

struct ScreenToView{
    glm::mat4 inverseProjectionMat;
    unsigned int tileSizes[4];
    unsigned int screenWidth;
    unsigned int screenHeight;
    float sliceScalingFactor;
    float sliceBiasFactor;
};

struct VisibleIndex {
	int index = 0;
};
struct LightGrid{
    unsigned int offset;
    unsigned int count;
};