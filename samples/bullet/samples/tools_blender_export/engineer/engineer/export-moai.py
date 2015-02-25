#
# `export-moai.py`
# ================
#
# `blender --background _scene_ --python export-moai.py -- _mesh_ _lua_`
# means open the `.blend` file _scene_ and export the mesh named _mesh_
# from it into a Lua file named _lua_ that can read by Moai.
#
# Very rough right now.
#

# No error checking
# No exception handling
# No file overwrite protection
# No vertex indexing
# No triangle strips
# Has to have UVs
# Has to have vertex colors

import math
import os
import sys

import bpy
import bmesh
import mathutils

s = """-- Created by export-moai.py
local coords = {%s}
local uvs = {%s}
local colors = {%s}

local vertexFormat = MOAIVertexFormat.new()
local vertexBuffer = MOAIVertexBuffer.new()
local mesh = MOAIMesh.new()

vertexFormat:declareCoord(1, MOAIVertexFormat.GL_FLOAT, 3)
vertexFormat:declareUV(2, MOAIVertexFormat.GL_FLOAT, 2)
vertexFormat:declareColor(3, MOAIVertexFormat.GL_UNSIGNED_BYTE)

vertexBuffer:setFormat(vertexFormat)
vertexBuffer:reserveVerts(#coords)

for i = 1, #coords do
    vertexBuffer:writeFloat(unpack(coords[i]))
    vertexBuffer:writeFloat(unpack(uvs[i]))
    vertexBuffer:writeColor32(unpack(colors[i]))
end

vertexBuffer:bless()

mesh:setVertexBuffer(vertexBuffer)
mesh:setPrimType(MOAIMesh.GL_TRIANGLES)

return mesh
"""

def export(mesh, file):
    m = bpy.data.meshes[mesh]

    b = bmesh.new()
    b.from_mesh(m)

    # Make sure all polygons are triangles
    bmesh.ops.triangulate(b, faces=b.faces)

    # Rotate the coordinates so Y is vertical
    matrix = mathutils.Matrix.Rotation(-math.pi / 2, 3, 'X')
    bmesh.ops.rotate(b, verts=b.verts, cent=(0, 0, 0), matrix=matrix)

    b.to_mesh(m)
    b.free()

    coords = []
    uvs    = []
    colors = []
    for p in m.polygons:
        for i in p.loop_indices:
            coord = m.vertices[m.loops[i].vertex_index].co
            uv    = m.uv_layers.active.data[i].uv
            color = m.vertex_colors.active.data[i].color

            # Flip Y to point down
            uv.y = 1 - uv.y

            coords.append('{%s}' % ','.join(['%.5f' % _ for _ in coord]))
            uvs   .append('{%s}' % ','.join(['%.5f' % _ for _ in uv]))
            colors.append('{%s}' % ','.join(['%.5f' % _ for _ in color]))

    # Convert the lists to strings
    coords = ','.join(coords)
    uvs    = ','.join(uvs)
    colors = ','.join(colors)

    # Write the file
    f = open(file, 'w')
    f.write(s % (coords, uvs, colors))
    f.close()

sys.argv = sys.argv[sys.argv.index('--'):]
export(sys.argv[1], sys.argv[2])
