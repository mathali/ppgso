// Example gl4_transform
// - This example demonstrates basic 2D transformations
// - Notice that the glm library uses column major order when declaring matrices
// - Try to combine multiple transformation using multiplication

#include <iostream>

#include <ppgso/ppgso.h>
// GLM contains 2D specific transformations in the following header
#include <glm/gtx/matrix_transform_2d.hpp>

#include "gl4_transform_vert.h"
#include "gl4_transform_frag.h"

using namespace std;
using namespace glm;
using namespace ppgso;

const unsigned int SIZE = 512;

class TransformWindow : public Window {
private:
  Shader program = {gl4_transform_vert, gl4_transform_frag};
  Texture texture = {"lena.bmp"};
  Mesh quad = {program, "quad.obj"};

  mat3 GetTransformation(float time) {
    // Create transformation matrix
    // NOTE: glm matrices are declared column major !

    // identity
//    auto transform = mat3({
//        1.0, 0.0, 0.0,
//        0.0, 1.0, 0.0,
//        0.0, 0.0, 1.0
//    });

    // scale
//   transform *= mat3({
//      sin(time), 0.0, 0.0,
//      0.0, sin(time), 0.0,
//      0.0, 0.0, 1.0
//    });

    // squash
//   transform *= mat3({
//     sin(time), 0.0, 0.0,
//     0.0, cos(time), 0.0,
//     0.0, 0.0, 1.0
//   });

    // rotate
//    transform *= mat3({
//      cos(time), sin(time), 0.0,
//      -sin(time), cos(time), 0.0,
//      0.0, 0.0, 1.0
//    });

    // translate
//   transform *= mat3({
//      1.0, 0.0, 0.0,
//     0.0, 1.0, 0.0,
//     sin(time)/2.0, cos(time)/2.0, 1.0
//   });

    // Rotate around top right corner
//   transform *= mat3({
//     // Move back
//     1.0, 0.0, 0.0,
//     0.0, 1.0, 0.0,
//     1.0, 1.0, 1.0
//   }) * mat3({
//     // Rotate
//     cos(time), sin(time), 0.0,
//     -sin(time), cos(time), 0.0,
//     0.0, 0.0, 1.0
//   }) * mat3({
//     // Move to origin
//     1.0, 0.0, 0.0,
//     0.0, 1.0, 0.0,
//     -1.0, -1.0, 1.0
//   });

    // Rotate around top right corner using glm functions
    auto rotation_point = vec2{1,1};
    auto transform = translate(mat3{}, rotation_point) * rotate(mat3{}, time) * glm::translate(mat3{}, -rotation_point);

    return transform;
  }

public:
  TransformWindow() : Window{"gl4_transform", SIZE, SIZE} {
    // Set program input for texture uniform
    program.SetTexture(texture, "Texture");
  }

  void onIdle() override {
    // Set gray background
    glClearColor(.5f,.5f,.5f,0);

    // Clear depth and color buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float time = (float) glfwGetTime();

    // Generate and set the transformation matrix
    program.SetMatrix(GetTransformation(time), "ModelView");

    // Render geometry
    quad.Render();
  }
};

int main() {
  // Create our window
  auto window = TransformWindow{};

  // Main execution loop
  while (window.Pool()) {}

  return EXIT_SUCCESS;
}