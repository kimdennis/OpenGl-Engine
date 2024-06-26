#include <OGL3D/Game/OCubeEntity.h>
#include <OGL3D/Math/OVec2.h>
#include <OGL3D/Game/OCubeEntity.h>
#include <OGL3D/Game/OGame.h>
#include <OGL3D/Resource/OTexture.h>

struct Vertex
{
    OVec3 position;
    OVec2 texCoords;
};


//during the oncreate method of this entity, we initialize the graphics data of the cube
void OCubeEntity::onCreate()
{
    OVec3 position_list[] =
    {
        //front face
        { OVec3(-0.5f,-0.5f,-0.5f)},
        { OVec3(-0.5f,0.5f,-0.5f) },
        { OVec3(0.5f,0.5f,-0.5f) },
        { OVec3(0.5f,-0.5f,-0.5f)},

        //back face
        { OVec3(0.5f,-0.5f,0.5f) },
        { OVec3(0.5f,0.5f,0.5f) },
        { OVec3(-0.5f,0.5f,0.5f)},
        { OVec3(-0.5f,-0.5f,0.5f) }
    };

    OVec2 texcoord_list[] =
    {
        { OVec2(0.0f,0.0f) },
        { OVec2(0.0f,1.0f) },
        { OVec2(1.0f,0.0f) },
        { OVec2(1.0f,1.0f) }
    };

    Vertex verticesList[] =
    {
        //front face
        { position_list[0],texcoord_list[1] },
        { position_list[1],texcoord_list[0] },
        { position_list[2],texcoord_list[2] },
        { position_list[3],texcoord_list[3] },

        //back face
        { position_list[4],texcoord_list[1] },
        { position_list[5],texcoord_list[0] },
        { position_list[6],texcoord_list[2] },
        { position_list[7],texcoord_list[3] },

        //top face
        { position_list[1],texcoord_list[1] },
        { position_list[6],texcoord_list[0] },
        { position_list[5],texcoord_list[2] },
        { position_list[2],texcoord_list[3] },

        //bottom face
        { position_list[7],texcoord_list[1] },
        { position_list[0],texcoord_list[0] },
        { position_list[3],texcoord_list[2] },
        { position_list[4],texcoord_list[3] },

        //right face
        { position_list[3],texcoord_list[1] },
        { position_list[2],texcoord_list[0] },
        { position_list[5],texcoord_list[2] },
        { position_list[4],texcoord_list[3] },

        //left face
        { position_list[7],texcoord_list[1] },
        { position_list[6],texcoord_list[0] },
        { position_list[1],texcoord_list[2] },
        { position_list[0],texcoord_list[3] }
    };

    ui32 indicesList[] =
    {
        //front face
        0,1,2,  //first triangle
        2,3,0,  //second triangle
        //back face
        4,5,6,
        6,7,4,
        //top face
        8,9,10,
        10,11,8,
        //bottom face
        12,13,14,
        14,15,12,
        //right face
        16,17,18,
        18,19,16,
        //left face
        20,21,22,
        22,23,20
    };



    static const OVertexAttribute attribsList[] = {
        { 3 }, //numElements position attribute
        { 2 } //numElements texture coordinates attribute
    };



    m_mesh = m_game->getGraphicsEngine()->createVertexArrayObject(
        //vertex buffer
        {
                (void*)verticesList,
                sizeof(Vertex), //size in bytes of a single composed vertex (in this case composed by vertex (3 nums* sizeof float) + texcoord (2 nums* sizeof float))
                sizeof(verticesList) / sizeof(Vertex),  //number of composed vertices,

                (OVertexAttribute*)attribsList,
                2 //numelements attrib list
        },
        //index buffer
        {
            (void*)indicesList,
            sizeof(indicesList)
        }
        );
}

void OCubeEntity::setTexture(const OTexturePtr& texture)
{
    m_texture = texture;
}


void OCubeEntity::onGraphicsUpdate(f32 deltaTime)
{
    auto engine = m_game->getGraphicsEngine();
    engine->setFaceCulling(OCullType::BackFace); // draw only the front faces, the back faces are discarded
    engine->setWindingOrder(OWindingOrder::ClockWise); //consider the position of vertices in clock wise way.

    engine->setTexture2D(m_texture->getTexture2D(), 0);
    //during the graphcis update, we call the draw function
    engine->setVertexArrayObject(m_mesh); //bind vertex buffer to graphics pipeline
    engine->drawIndexedTriangles(OTriangleType::TriangleList, 36);//draw triangles through the usage of index buffer
}