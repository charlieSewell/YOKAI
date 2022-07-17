#include <CppUTest/TestHarness.h>
#include <core/Transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <fstream>
namespace 
{
    glm::mat4 testData
    {{3.0f, 0.0f, 0.0f, 0.0f},
     {0.0f, 2.0f, 2.0f, 0.0f},
     {0.0f, -2.0f, 1.0f, 0.0f},
     {0.0f, 0.0f, 0.0f, 1.0f}};

    glm::mat4 testData2
    {{3.0f, 20.0f, 6.0f, 0.0f},
     {3.0f, 4.0f, 2.0f, 0.0f},
     {0.0f, -2.0f, 1.0f, 0.0f},
     {21.0f, 8.0f, 21.0f, 1.0f}};
    SimpleString StringFrom (const glm::mat4& mat)
    {
        return(glm::to_string(mat).c_str());
    }
    SimpleString StringFrom (const nlohmann::json& j)
    {
        return(std::string(j).c_str());
    }
}
namespace glm
{
    bool operator==(const vec4 &vecA, const vec4 &vecB) 
    { 
        const float epsilion = 0.0001f;  // Precision of comparison.

        return fabs(vecA[0] - vecB[0]) < epsilion   
            && fabs(vecA[1] - vecB[1]) < epsilion   
            && fabs(vecA[2] - vecB[2]) < epsilion
            && fabs(vecA[3] - vecB[3]) < epsilion;
    }
    //CPPunit compares with !=
    bool operator!=(const mat4 &matA, const mat4 &matB) 
    { 
        return !(matA[0] == matB[0]
            && matA[1] == matB[1]
            && matA[2] == matB[2]
            && matA[3] == matB[3]);
    }
}

TEST_GROUP(TransformTestGroup)
{

};


TEST(TransformTestGroup, TestTranslateOverloads)
{
    Transform matrix1(testData);
    Transform matrix2(testData);
    matrix1.Translate(8.0f,8.0f,8.0f);
    matrix2.Translate(glm::vec3(8.0f));
    CHECK_EQUAL(matrix1.GetMatrix(),matrix2.GetMatrix());
    
    matrix1.Translate(7.0f,7.0f,7.0f);
    matrix2.Translate(glm::vec3(7.0f));
    CHECK_EQUAL(matrix1.GetMatrix(),matrix2.GetMatrix());
    
    matrix1.Translate(8000.0f,8000.0f,8000.0f);
    matrix2.Translate(glm::vec3(8000.0f));
    CHECK_EQUAL(matrix1.GetMatrix(),matrix2.GetMatrix());
    
};
TEST(TransformTestGroup, TestTranslatePostMultiplyOverloads)
{
    Transform matrix1(testData);
    Transform matrix2(testData);
    matrix1.TranslatePostMultiply(8.0f,8.0f,8.0f);
    matrix2.TranslatePostMultiply(glm::vec3(8.0f));
    CHECK_EQUAL(matrix1.GetMatrix(),matrix2.GetMatrix());
    
    matrix1.TranslatePostMultiply(7.0f,7.0f,7.0f);
    matrix2.TranslatePostMultiply(glm::vec3(7.0f));
    CHECK_EQUAL(matrix1.GetMatrix(),matrix2.GetMatrix());
    
    matrix1.TranslatePostMultiply(8000.0f,8000.0f,8000.0f);
    matrix2.TranslatePostMultiply(glm::vec3(8000.0f));
    CHECK_EQUAL(matrix1.GetMatrix(),matrix2.GetMatrix());
    
};


TEST(TransformTestGroup, TestTranslate)
{
    glm::mat4 expectedResult
    {{3.0f, 0.0f, 0.0f, 0.0f},
     {0.0f, 2.0f, 2.0f, 0.0f},
     {0.0f, -2.0f, 1.0f, 0.0f},
     {21.0f, 0.0f, 21.0f, 1.0f}};
    Transform actualResult(testData);
    actualResult.Translate(glm::vec3(7.0f));
    CHECK_EQUAL(expectedResult, actualResult.GetMatrix()); 
};

TEST(TransformTestGroup, TestTranslatePostMultiply)
{
    glm::mat4 expectedResult
    {{3.0f, 0.0f, 0.0f, 0.0f},
     {0.0f, 2.0f, 2.0f, 0.0f},
     {0.0f, -2.0f, 1.0f, 0.0f},
     {7.0f, 7.0f, 7.0f, 1.0f}};
    Transform actualResult(testData);
    actualResult.TranslatePostMultiply(glm::vec3(7.0f));
    CHECK_EQUAL(expectedResult, actualResult.GetMatrix());
    
};

TEST(TransformTestGroup, TestScaleOverloads)
{
    Transform matrix1(testData);
    Transform matrix2(testData);
    Transform matrix3(testData);

    matrix1.Scale(8.0f,8.0f,8.0f);
    matrix2.Scale(glm::vec3(8.0f));
    matrix3.Scale(8.0f);

    //if matrix1 == matrix2 then check if matrix1 == matrix3
    CHECK_EQUAL(matrix1.GetMatrix(),matrix2.GetMatrix());
    CHECK_EQUAL(matrix1.GetMatrix(),matrix3.GetMatrix());
}

TEST(TransformTestGroup, TestScale)
{
    glm::mat4 expectedResult
    {{120.0f, 800.0f, 240.0f, 0.0f},
     {120.0f, 160.0f, 80.0f, 0.0f},
     {0.0f, -80.0f, 40.0f, 0.0f},
     {21.0f, 8.0f, 21.0f, 1.0f}};
    Transform actualResult(testData2);
    actualResult.Scale(glm::vec3(40.0f));
    CHECK_EQUAL(expectedResult, actualResult.GetMatrix());
}

TEST(TransformTestGroup, TestRotate)
{
    glm::mat4 expectedResult
    {{-1.344221f, -7.173479f, -3.582438f, 0.0f},
     {3.0f, 4.0f, 2.0f, 0.0f},
     {2.681990f, 18.776079f, 4.915906f, 0.0f},
     {21.0f, 8.0f, 21.0f, 1.0f}};

    Transform actualResult(testData2);
    actualResult.Rotate(90,glm::vec3(0.0,1.0,0.0));
    CHECK_EQUAL(expectedResult, actualResult.GetMatrix());
}

TEST(TransformTestGroup, TestSerialize)
{
    Transform transform(testData2);
    nlohmann::json actual = {};
    nlohmann::json expected = {};
    std::ifstream input("test_data/serializetransform_test.json");
    if (!input.is_open()) 
    {
        FAIL("Couldnt open serializetransform_test.json");
    }
    input >> expected;
    transform.Serialize(actual);
    CHECK_EQUAL(expected,actual);
    input.close();
    
}