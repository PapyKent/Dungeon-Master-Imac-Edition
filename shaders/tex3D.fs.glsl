#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uTexture;

uniform vec3 uKd;//coeff reflec obj
uniform vec3 uKs;//coeff reflec glossi
uniform float uShininess;//exposant de brillance

uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

vec3 blinnPhong(){
float distLum = distance(vPosition_vs,uLightPos_vs);
vec3 color = (uLightIntensity/pow(distLum,2))*(uKd*(dot((normalize(uLightPos_vs - vPosition_vs)),vNormal_vs))+uKs*(pow(dot((normalize(-vPosition_vs)+(normalize(uLightPos_vs - vPosition_vs)))/2,vNormal_vs),uShininess)));
return color;
}

void main() {
    vec4 text = texture(uTexture,vTexCoords);
   // fFragColor = vec3(text[0],text[1],text[2]);
    fFragColor = blinnPhong()*vec3(text[0],text[1],text[2]);
}


