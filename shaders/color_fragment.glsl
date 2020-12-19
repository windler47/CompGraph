#version 400 core

out vec4 FragColor;

struct Light {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

uniform vec3 viewPos;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * Color.rgb;

    // diffuse
    vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(light.position - FragPos);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * Color.rgb;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = max(dot(viewDir, reflectDir), 0.0);
    vec3 specular = light.specular * spec * Color.rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}