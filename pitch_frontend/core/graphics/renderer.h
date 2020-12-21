#ifndef RENDERER_H
#define RENDERER_H

#include "vertex_buffer_object.h"

/*
 * I need to abstract the drawing code
 * out of main but I'm not really sure
 * what I want this to be yet. So, it's
 * very basic
 */

/*
 * Things this should do (at least some
 * of) int the future:
 *
 * Order draw calls such that drawables
 * with the same shader are drawn in
 * the same chunk
 *
 * Batch rendering?
 */

class Renderer
{
public:
    Renderer() = default;
    Renderer(const Renderer&) = default; //<should this be copyable?
    Renderer(Renderer&&) = default;
    ~Renderer() = default;

    Renderer& operator=(const Renderer&) = default;
    Renderer& operator=(Renderer&&) = default;

    void render(const VertexBufferObject& vbo);

private:
};

#endif //ENDERER_H
