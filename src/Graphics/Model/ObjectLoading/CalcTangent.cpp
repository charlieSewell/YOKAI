#include "CalcTangent.hpp"
#include <assert.h>
CalcTangents::CalcTangents()
{
    iface.m_getNumFaces = get_num_faces;
    iface.m_getNumVerticesOfFace = get_num_vertices_of_face;

    iface.m_getNormal = get_normal;
    iface.m_getPosition = get_position;
    iface.m_getTexCoord = get_tex_coords;
    iface.m_setTSpaceBasic = set_tspace_basic;

    context.m_pInterface = &iface;
}

void CalcTangents::calc(Mesh *mesh) {

    context.m_pUserData = mesh;
    genTangSpaceDefault(&this->context);
}

int CalcTangents::get_num_faces(const SMikkTSpaceContext *context) {
    Mesh *working_mesh = static_cast<Mesh*> (context->m_pUserData);

    float f_size = (float)working_mesh->getIndices()->size() / 3.f;
    int i_size = (int)working_mesh->getIndices()->size() / 3;

    assert((f_size - (float)i_size) == 0.f);

    return i_size;
}

int CalcTangents::get_num_vertices_of_face(const SMikkTSpaceContext*, const int) 
{
    return 3;
}

void CalcTangents::get_position(const SMikkTSpaceContext *context, float *outpos, const int iFace, const int iVert) 
{
    Mesh *working_mesh = static_cast<Mesh*> (context->m_pUserData);
    auto index = get_vertex_index(context, iFace, iVert);
    auto vertex = working_mesh->getVertices()->at(index);
    outpos[0] = vertex.position.x;
    outpos[1] = vertex.position.y;
    outpos[2] = vertex.position.z;
}

void CalcTangents::get_normal(const SMikkTSpaceContext *context, float *outnormal, const int iFace, const int iVert) 
{
    Mesh *working_mesh = static_cast<Mesh*> (context->m_pUserData);
    auto index = get_vertex_index(context, iFace, iVert);
    auto vertex = working_mesh->getVertices()->at(index);
    outnormal[0] = vertex.normal.x;
    outnormal[1] = vertex.normal.y;
    outnormal[2] = vertex.normal.z;
}

void CalcTangents::get_tex_coords(const SMikkTSpaceContext *context, float *outuv, const int iFace, const int iVert)
{
    Mesh *working_mesh = static_cast<Mesh*> (context->m_pUserData);
    auto index = get_vertex_index(context, iFace, iVert);
    auto vertex = working_mesh->getVertices()->at(index);
    outuv[0] = vertex.textureCoords.x;
    outuv[1] = vertex.textureCoords.y;
}

void CalcTangents::set_tspace_basic(const SMikkTSpaceContext *context, const float *tangentu, const float fSign, const int iFace, const int iVert) 
{
    Mesh *working_mesh = static_cast<Mesh*> (context->m_pUserData);
    auto index = get_vertex_index(context, iFace, iVert);
    auto *vertex = &working_mesh->getVertices()->at(index);
    vertex->tangent.x = tangentu[0];
    vertex->tangent.y = tangentu[1];
    vertex->tangent.z = tangentu[2];
    vertex->tangent.w = fSign;
}

int CalcTangents::get_vertex_index(const SMikkTSpaceContext *context, int iFace, int iVert) 
{
    Mesh *working_mesh = static_cast<Mesh*> (context->m_pUserData);
    auto face_size = get_num_vertices_of_face(context, iFace);
    auto indices_index = (iFace * face_size) + iVert;
    int index = working_mesh->getIndices()->at(indices_index);
    return index;
}