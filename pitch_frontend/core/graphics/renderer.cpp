#include "renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Renderer::render(const VertexBufferObject& vbo)
{
    glDrawArrays(GL_TRIANGLE_STRIP, 0, static_cast<GLsizei>(vbo.vertexCount()));
}
