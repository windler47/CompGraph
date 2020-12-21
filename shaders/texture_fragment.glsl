#version 400 core

out vec4 FragColor;

struct Light {
    vec3 direction;

    float ambient;
    float diffuse;
    float specular;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Light light;
uniform sampler2D texture_image;

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

    vec3 result = (light.ambient + diff + spec) * texture(texture_image, TexCoords).rgb;
    FragColor = vec4(result, 1.0);
}