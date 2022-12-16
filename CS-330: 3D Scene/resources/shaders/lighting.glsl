#version 440 core


struct AmbientLight {
    vec4 color;
};

struct PointLight {
    vec4 color;
    vec3 position;
};

struct DirectionalLight {
    vec4 color;
    vec3 position;
    vec3 target;
};


vec4 applyAmbientLight( vec4 iFragColor ) {
    // create an rgb that factors in the alpha component
    vec4 ambient = vec4(ambientLight.color.rgb * ambientLight.color.a, 1);

    // make sure that we're working with a unit vector for simpler calculations
    vec3 normal = normalize(oNormal);
    vec3 lightDirection = normalize(lightPosition - oFragPosition);

    // as the angle of intersection passes 90, learnopengl said that the dot product will go negative
    // to counteract this, just take the max between the result and 0, to prevent negative numbers
    float diffuseStrength = max(dot(normal, lightDirection), 0.0);
    vec4 diffuse = diffuseStrength * lightColor;

    return (ambient + diffuse) * iFragColor;
}

vec4 applyPointLight(vec4 iFragColor, PointLight settings) {
    return iFragColor;
}

vec4 applyDirectionalLight(vec4 iFragColor, DirectionalLight settings) {
    return iFragColor;
}

vec4 applyLighting( vec4 iFragColor ) {
    // apply ambient lighting to fragment
    iFragColor = applyAmbientLight(iFragColor);

    // next, apply point lights
    for(int i=0; i < pointLights.length; i++) {
        iFragColor = applyPointLight(iFragColor, pointLights[i]);
    }

    // finally, apply directional lights
    for(int i=0; i < directionalLights.length; i++) {
        iFragColor = applyDirectionalLight(iFragColor, directionalLights[i]);
    }

    return iFragColor;
}