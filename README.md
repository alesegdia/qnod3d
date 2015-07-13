# qnod3d

## OpenGL design

All nodes will be drawn based on a z-stretched, xy-unit box, with a size of (1,1,0.25). This way, we can use instancing
to xy-scale boxes depending on node size.

Uniform buffers will be used as instancing data to send per-node sizes and matrices to the vertex shader. Alternatively,
a grid-fixed mode can be done.

Node matrices can be computed on CPU or GPU. If using the latter, only (x,y) position will be passed as per-instance data,
and an uniform to provide the z coordinate to the vertex shader. A grid-fixed mode can be done alternatively.

