#include <vector>

#include <VENDOR/GLM/glm.hpp>

namespace geo
{
    class Surface
    {
        protected:
            std::vector<int> m_Indices;
            std::vector<glm::vec3> m_Vertices;
            std::vector<glm::vec2> m_TexCoords;
            std::vector<glm::vec3> m_Normals;

        protected:
            virtual void init() = 0;

        public:
            Surface();
            int getNVertices();
            int getNIndices();

            std::vector<int> getIndices();
            std::vector<glm::vec3> getVertices();
            std::vector<glm::vec3> getNormals();
            std::vector<glm::vec2> getTexCoords();
    };

    class Sphere : public Surface
    {
        private:
            float m_Precision;

        private:
            float degreesToRad(float degrees);
            float radToDegrees(float rads);
            void init();

        public:
            Sphere();
            Sphere(float precision);
    };
}