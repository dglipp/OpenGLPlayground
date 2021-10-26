#pragma once

#include <vector>

#include <VENDOR/GLM/glm.hpp>

namespace geo
{
    class Surface
    {
        protected:
            std::vector<unsigned int> m_Indices;
            std::vector<glm::vec3> m_Vertices;
            std::vector<glm::vec2> m_TexCoords;
            std::vector<glm::vec3> m_Normals;

        protected:
            virtual void init() = 0;

        public:
            Surface();
            int getNVertices();
            int getNIndices();

            std::vector<unsigned int> getIndices();
            std::vector<glm::vec3> getVertices();
            std::vector<glm::vec3> getNormals();
            std::vector<glm::vec2> getTexCoords();

            std::vector<float> getVertexBuffer();
            std::vector<float> getNormalBuffer();
            std::vector<float> getTextureBuffer();
    };

    class Sphere : public Surface
    {
        private:
            float m_Precision;

        private:
            void init();

        public:
            Sphere();
            Sphere(float precision);
    };

    class Torus : public Surface
    {
        private:
            float m_Precision;
            float m_InnerRadius;
            float m_OuterRadius;

        private:
            void init();

        public:
            Torus();
            Torus(float innerRadius, float outerRadius);
            Torus(float innerRadius, float outerRadius, float precision);
    };

    class Mesh : public Surface
    {
        private:
            void init();

        public:
            Mesh();
            Mesh(std::vector<glm::vec3> vertices);
            Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals);
            Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textureCoords);
            Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textureCoords);

            Mesh(std::vector<glm::vec3> vertices, std::vector<unsigned int> indices);
            Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<unsigned int> indices);
            Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textureCoords, std::vector<unsigned int> indices);
            Mesh(std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals,
                 std::vector<glm::vec2> textureCoords, std::vector<unsigned int> indices);
    };
}