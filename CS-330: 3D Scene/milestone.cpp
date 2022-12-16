#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <easylogging++.h>

#include "src/Window.h"
#include "src/Camera.h"
#include "src/GL/Model.h"
#include "src/Geometry/CubeGeometry.h"
#include "src/Utils/Timer.h"

std::shared_ptr<Model> createTableModel();
std::vector<
    std::shared_ptr<Model>
> createPlacematModels();

INITIALIZE_EASYLOGGINGPP

#include "src/GL/Light.h"
std::vector<Light> lights;
void bindLight(const std::shared_ptr<Shader>& shader, const Light& light, int index);

std::shared_ptr<Model> createBowlModel();

std::shared_ptr<Model> createPaperTowelHolderModel();

int main(int argc, char* argv[]) {
    START_EASYLOGGINGPP(argc, argv);

    LOG(INFO) << "Running the Module Four Milestone Code";

    glfwInit();
    atexit(glfwTerminate);

    Window window("ModuleSix Milestone: Adding Lighting to Scene", 800, 600); // create window and load gl
    Camera camera({ 1, 2, 15 }); // retrieved by positioning the camera in application, then printing the coordinates with V
    camera.attachTo(window); // make the camera respond to the window's inputs

    // load the shader from the resources path
    auto shader = Shader::FromFiles("resources/shaders/generic.vert", "resources/shaders/generic.frag");

    //
    auto table = createTableModel();
    table->setShader(shader);

    window.modelCollection.push_back(table);

    for(const auto mat: createPlacematModels()) {
        mat->setShader(shader);
        window.modelCollection.push_back(mat);
    }

    // create bowl
    auto pumpkinBowl = createBowlModel();
    pumpkinBowl->setShader(shader);
    window.modelCollection.push_back(pumpkinBowl);


    // load the paper towel model
    auto paperTowelHolder = createPaperTowelHolderModel();
    paperTowelHolder->setShader(shader);
    window.modelCollection.push_back(paperTowelHolder);

    lights.emplace_back(Light {
        .ambient = {1, 1, 1, 1},
        .diffuse = {1, 1, 1, 1},
        .specular = {1, 1, 1, 1},

        .position = {0, 1.5, 0},
        .direction = {0, -1, 0}
    });

    lights.emplace_back(Light {
        .ambient = {1, 0, 0, 1},
        .diffuse = {1, 0, 0, 1},
        .specular = {1, 0, 0, 1},

        .position = {1, 5, 1},
        .direction = glm::normalize( glm::vec3 {-2, -2, -2} )
    });

    Timer timer( 1.f / 60.f );
    while(window.open()) {

        // this loops until we reach 1/60 of a second, at which point it returns and then allows the render to happen
        timer.tick([&](double dt) {
            // let glfw process all queued events
            glfwPollEvents();

            // update camera fields
            camera.update(dt);

            // update all models
            window.updateModels(dt);
        });

        // this only needs set when rendering, so there's no need to put it in the ticker
        shader->setMat4("pv", window.GetProjectionMatrix() * camera.GetView());

        // bind all lights
        shader->setInt("numLights", lights.size());
        shader->setVec3("viewPosition", camera.GetPosition()); // for specular lighting
        for(auto i=0; i < lights.size(); i++)
            bindLight(shader, lights[i], i);

        // make sure we only send for rendering whatever is visible to the camera (called frustum culling)
        // @todo actually implement frustum culling
        for(auto& model: window.modelCollection) {
            if(model->isInView(camera)) window.queueForRendering(model);
        }

        // render everything in the window
        window.clear();
        {
            window.renderModels();
        }
        window.swap();
    }

    LOG(INFO) << "Closing the Milestone Program";

    return 0;
}

#include <tinyobjloader/tiny_obj_loader.h>
#include <numeric>

std::shared_ptr<Model> createPaperTowelHolderModel() {
    std::string filename = "resources/models/paper-towel-holder.obj";
    tinyobj::ObjReaderConfig config;
    config.mtl_search_path = "resources/models/";
    config.triangulate = true;

    tinyobj::ObjReader reader;
    reader.ParseFromFile(filename, config);

    if(!reader.Error().empty()) {
        LOG(ERROR) << reader.Error();
    }

    // load the vertices
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;

        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {

                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];

                // generate the application vertex format
                Vertex vert { vx, vy, vz };

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];

                    // add normal
                    vert.normal.x = nx;
                    vert.normal.y = ny;
                    vert.normal.z = nz;
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];

                    vert.texture.x = tx;
                    vert.texture.y = ty;
                }

                // this pushes back the current index, so we have vertices in this array that were used earlier
                // rather than reference them by index, we're just doing 0..n
                vertices.push_back(vert);
            }
            index_offset += fv;

            // per-face material
            auto const& mat_id = shapes[s].mesh.material_ids[f];

            //
            tinyobj::material_t const& material = materials[mat_id];

            char buffer[256];
            sprintf(buffer, "Material: %s\nFile: %s\nDiffuse: %.2f, %.2f, %.2f\n\n",
                    material.name.c_str(), material.diffuse_texname.c_str(), material.diffuse[0], material.diffuse[1], material.diffuse[2]);

            LOG(INFO) << buffer;
        }
    }

    // because we're expanding the indexed vertices, we need to just sequentially use the vertices 0..vertices.size()
    indices.resize(vertices.size());
    std::iota(indices.begin(), indices.end(), 0);

    auto mesh = std::make_shared<Mesh>(vertices, indices);

    // @todo load this from the mtl file, rather than manually. I'm just lazy right now
    mesh->addMaterial(std::make_shared<Material>("resources/models/metal-texture.jpg"));
    mesh->addMaterial(std::make_shared<Material>("resources/models/paper-towel-texture.jpg"));

    return std::make_shared<Model>(mesh, glm::vec3(2, .1025, -.5), glm::vec3(), .33);
}

std::shared_ptr<Model> createBowlModel() {
    std::string filename = "resources/models/bowl-and-pumpkins.obj";
    tinyobj::ObjReaderConfig config;
    config.mtl_search_path = "resources/models/";
    config.triangulate = true;

    tinyobj::ObjReader reader;
    reader.ParseFromFile(filename, config);

    if(!reader.Error().empty()) {
        LOG(ERROR) << reader.Error();
    }

    // load the vertices
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    std::vector<Vertex> vertices;
    std::vector<GLushort> indices;

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;

        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {

                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                tinyobj::real_t vx = attrib.vertices[3*size_t(idx.vertex_index)+0];
                tinyobj::real_t vy = attrib.vertices[3*size_t(idx.vertex_index)+1];
                tinyobj::real_t vz = attrib.vertices[3*size_t(idx.vertex_index)+2];

                // generate the application vertex format
                Vertex vert { vx, vy, vz };

                // Check if `normal_index` is zero or positive. negative = no normal data
                if (idx.normal_index >= 0) {
                    tinyobj::real_t nx = attrib.normals[3*size_t(idx.normal_index)+0];
                    tinyobj::real_t ny = attrib.normals[3*size_t(idx.normal_index)+1];
                    tinyobj::real_t nz = attrib.normals[3*size_t(idx.normal_index)+2];

                    // add normal
                    vert.normal.x = nx;
                    vert.normal.y = ny;
                    vert.normal.z = nz;
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                    tinyobj::real_t tx = attrib.texcoords[2*size_t(idx.texcoord_index)+0];
                    tinyobj::real_t ty = attrib.texcoords[2*size_t(idx.texcoord_index)+1];

                    vert.texture.x = tx;
                    vert.texture.y = ty;
                }

                switch(s) {
                    case 0:
                        // bowl
                        vert.color.r = 0.182;
                        vert.color.g = 0.091;
                        vert.color.b = 0.0506;
                        vert.color.a = 1;
                        break;
                    case 1:
                        vert.color.r = .798;
                        vert.color.g = .183;
                        vert.color.b = .039;
                        vert.color.a = 1;
                        break;
                    case 2:
                        vert.color.r = .798;
                        vert.color.g = 0.095;
                        vert.color.b = 0.055;
                        vert.color.a = 1;
                        break;
                    default:
                        vert.color.r = .080;
                        vert.color.g = .028;
                        vert.color.b = 0.004;
                        vert.color.a = 1;
                        break;
                }

                // Optional: vertex colors
                // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
                // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
                // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];

                // this pushes back the current index, so we have vertices in this array that were used earlier
                // rather than reference them by index, we're just doing 0..n
                vertices.push_back(vert);
            }
            index_offset += fv;

            // per-face material
            shapes[s].mesh.material_ids[f];
        }
    }

    // because we're expanding the indexed vertices, we need to just sequentially use the vertices 0..vertices.size()
    indices.resize(vertices.size());
    std::iota(indices.begin(), indices.end(), 0);

    auto mesh = std::make_shared<Mesh>(vertices, indices);

    return std::make_shared<Model>(mesh, glm::vec3(0, .1025, 0));
}

std::shared_ptr<Model> createTableModel() {
    auto material = std::make_shared<Material>("resources/images/table.png");

    auto mesh = std::make_shared<CubeGeometry>(10, .2, 5);

    mesh->addMaterial( material );
    mesh->addMaterial( std::make_shared<Material>("resources/images/specular.png") );

    return std::make_shared<Model>(mesh, glm::vec3(0, 0, 0));
}


std::vector<std::shared_ptr<Model>> createPlacematModels() {
    auto mesh = std::make_shared<CubeGeometry>(2, .1, 1);

    mesh->addMaterial( std::make_shared<Material>("resources/images/placemat.png") );

    return {
        std::make_shared<Model>(mesh, glm::vec3(-4.5, .1, 0), glm::vec3(0, -90, 0)),
        std::make_shared<Model>(mesh, glm::vec3(0, .1, -2), glm::vec3(0, 180, 0)),
        std::make_shared<Model>(mesh, glm::vec3(4.5, .1, 0), glm::vec3(0, 90, 0)),
        std::make_shared<Model>(mesh, glm::vec3(0, .1, 2), glm::vec3(0, 0, 0)),
    };
}


void bindLight(const std::shared_ptr<Shader>& shader, const Light& light, int index) {
    char buffer[255];
    sprintf(buffer, "lights[%d].", index);

    std::string prefix{buffer};

    shader->setFloat(prefix + "constant", light.constant);
    shader->setFloat(prefix + "linear", light.linear);
    shader->setFloat(prefix + "quadratic", light.quadratic);

    shader->setVec4(prefix + "ambient", light.ambient);
    shader->setVec4(prefix + "diffuse", light.diffuse);
    shader->setVec4(prefix + "specular", light.specular);

    shader->setVec3(prefix + "position", light.position);
    shader->setVec3(prefix + "direction", glm::normalize(light.direction));
}