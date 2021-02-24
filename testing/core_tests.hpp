#include "pch.h"

#include "objparser.hpp"
#include "mathhelpers.hpp"

TEST (ObjParserTest, CoreParsing)
{
    ObjParser mockParser("./testing/test_models/cube.obj");
    unsigned int testAgainst[36] = {
        1, 3, 0,
        7, 5, 4,
        4, 1, 0, 
        5, 2, 1,
        2, 7, 3, 
        0, 7, 4,
        1, 2, 3,
        7, 6, 5,
        4, 5, 1,
        5, 6, 2,
        2, 6, 7,
        0, 3, 7
    };

    ASSERT_EQ(mockParser.m_faces.size(), 36) << "The size of the face indexes container does not match the cube testing model file";

    for (int i = 0; i < mockParser.m_faces.size(); i++)
    {   
        EXPECT_EQ(testAgainst[i], mockParser.m_faces.at(i)) << "The face index does not match the cube.obj file at index " << i;
    }
}

TEST (MathHelperTest, vectors)
{
  vec<2> a {2.f, 2.f};
  vec<2> b {2.f, 5.f};
  
  EXPECT_EQ(14, a.dotProduct(b)) << "The dot product does not return the right value.";

}

