#include "pch.h"
#include "Transform.h"
#include <fstream>
#include <string>

namespace nc
{
    std::istream& operator >> (std::istream& stream, Transform& transform)
    {
        stream >> transform.position;

        std::string line;
        
        std::getline(stream, line);
        transform.scale = stof(line);
        
        std::getline(stream, line);
        transform.angle = stof(line);

        return stream;
    }

    void Transform::Read(const rapidjson::Value& value)
    {
        nc::json::Get(value, "position", position);
        nc::json::Get(value, "scale", scale);
        nc::json::Get(value, "angle", angle);
    }

    void Transform::Update()
    {
        Matrix33 mxs;
        mxs.Scale(scale);
        Matrix33 mxr;
        mxr.Rotate(angle);
        Matrix33 mxt;
        mxt.Translate(position);

        matrix = mxs * mxr * mxt;
    }

    void Transform::Update(const Matrix33& mx)
    {
        Matrix33 mxs;
        mxs.Scale(scale);
        Matrix33 mxr;
        mxr.Rotate(angle);
        Matrix33 mxt;
        mxt.Translate(position);

        matrix = mxs * mxr * mxt * mx;
    }
}

