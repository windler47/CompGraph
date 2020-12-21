#version 400 core

out vec4 FragColor;

struct Light {
    vec3 direction;

    float ambient;
    float diffuse;
    float specular;
};

in vec3 Color;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform Light light;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0) * light.diffuse;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0) * light.specular;

    vec3 result = min((light.ambient + diff + spec), 1.0) * Color;
    FragColor = vec4(result, 1.0);
}
