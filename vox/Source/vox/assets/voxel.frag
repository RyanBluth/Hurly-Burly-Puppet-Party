#version 150

uniform mat4 model;

struct Light{
	vec3 position;
	vec3 intensities;
	float ambientCoefficient;
	float attenuation;
};

struct Material{
	int type;
	float shininess;
	vec3 specularColor;
};

uniform Light lights[5];
uniform int numLights;

uniform Material materials[5];
uniform int numMaterials;

uniform sampler2D textureSampler[5];
uniform int numTextures;

uniform sampler2D shadowMapSampler;

in vec3 fragVert;
in vec3 fragNormal;
in vec4 fragColor;
in vec2 fragUV;
in vec4 shadowCoord;

out vec4 outColor;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216 ), 
   vec2( 0.94558609, -0.76890725 ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760 ), 
   vec2( -0.91588581, 0.45771432 ), 
   vec2( -0.81544232, -0.87912464 ), 
   vec2( -0.38277543, 0.27676845 ), 
   vec2( 0.97484398, 0.75648379 ), 
   vec2( 0.44323325, -0.97511554 ), 
   vec2( 0.53742981, -0.47373420 ), 
   vec2( -0.26496911, -0.41893023 ), 
   vec2( 0.79197514, 0.19090188 ), 
   vec2( -0.24188840, 0.99706507 ), 
   vec2( -0.81409955, 0.91437590 ), 
   vec2( 0.19984126, 0.78641367 ), 
   vec2( 0.14383161, -0.14100790 ) 
);

float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

void main()
{
	//Texture stuff
	vec4 fragColorTex = vec4(0, 0, 0, 0);
	
	if(numTextures == 0){
		fragColorTex = fragColor;
	}

	for(int i = 0; i < numTextures; i++){
		if(i == 0){
			fragColorTex = texture(textureSampler[i], fragUV).rgba;
		}else{
			fragColorTex = mix(fragColorTex, texture(textureSampler[i], fragUV).rgba, 0.5);
		}
	}

	//Light Stuff
    mat3 normalMatrix = transpose(inverse(mat3(model)));

	vec3 normal = normalize(normalMatrix * fragNormal);

	vec3 fragWorldPosition = vec3(model * vec4(fragVert, 1));

	float brightness = 0;
	vec3 outIntensities = vec3(0,0,0);

	for(int i = 0; i < numLights; i++){
		vec3 surfaceToLight = lights[i].position - fragWorldPosition;
		brightness += dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
		outIntensities += vec3(lights[i].intensities);
	}

	brightness = clamp(brightness, 0.1, 1);
 
	//Shadow stuff
	float visibility = 1.0;
   
	for (int i=0; i<16; i++){

        vec3 ProjCoords = shadowCoord.xyz / shadowCoord.w;
		vec2 UVCoords;
		
		UVCoords.x = (0.5 * ProjCoords.x + 0.5 + poissonDisk[i].x/900.0);
		UVCoords.y = (0.5 * ProjCoords.y + 0.5 + poissonDisk[i].y/900.0);

		float z = 0.5 * ProjCoords.z + 0.5;
		float Depth = texture(shadowMapSampler, UVCoords).x;

		if(Depth < z - 0.005){
			visibility -= 0.05;
		}
	}
	//Requires lights and shadows
	visibility += brightness;
	//Set the out color to white
	outColor  = fragColor;
	//Texture modification
	outColor = fragColorTex;
	//Shadow modification
	outColor *= vec4(clamp(visibility, 0.5, 1), clamp(visibility, 0.5, 1), clamp(visibility, 0.5, 1) , 1);
	//lights Modficiation
	outColor *= vec4(vec3(outIntensities), 1) * vec4(brightness, brightness, brightness, 1);
	
	//outColor = vec4(vec3(outIntensities), 1) * vec4(vec3(fragColorTex.xyz),1) * vec4(clamp(visibility, 0.5, 1), clamp(visibility, 0.5, 1), clamp(visibility, 0.5, 1) , 1) * vec4(brightness, brightness, brightness, 1);
}