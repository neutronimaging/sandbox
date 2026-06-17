#version 330 core

in vec3 vPos;
out vec4 fragColor;

uniform sampler3D uVolume;
uniform vec3 uCameraLocal;

uniform float uOpacity;
uniform float uGrayMin;
uniform float uGrayMax;
uniform int uSteps;

vec2 intersectBox(vec3 origin, vec3 dir)
{
    vec3 boxMin = vec3(-0.5);
    vec3 boxMax = vec3( 0.5);

    vec3 invDir = 1.0 / dir;
    vec3 t0 = (boxMin - origin) * invDir;
    vec3 t1 = (boxMax - origin) * invDir;

    vec3 tSmall = min(t0, t1);
    vec3 tLarge = max(t0, t1);

    float tNear = max(max(tSmall.x, tSmall.y), tSmall.z);
    float tFar  = min(min(tLarge.x, tLarge.y), tLarge.z);

    return vec2(tNear, tFar);
}

void main()
{
    vec3 rayDir = normalize(vPos - uCameraLocal);

    vec2 hit = intersectBox(uCameraLocal, rayDir);
    float tNear = max(hit.x, 0.0);
    float tFar = hit.y;

    if (tNear >= tFar)
        discard;

    vec4 accum = vec4(0.0);
    float dt = (tFar - tNear) / float(uSteps);

    for (int i = 0; i < uSteps; ++i)
    {
        float t = tNear + float(i) * dt;
        vec3 p = uCameraLocal + t * rayDir;
        vec3 texCoord = p + vec3(0.5);

        float v = texture(uVolume, texCoord).r;
        float g = clamp((v - uGrayMin) / max(uGrayMax - uGrayMin, 1e-20), 0.0, 1.0);

        float alpha = g * uOpacity;
        vec3 color = vec3(g);

        accum.rgb += (1.0 - accum.a) * alpha * color;
        accum.a   += (1.0 - accum.a) * alpha;

        if (accum.a > 0.98)
            break;
    }

    fragColor = accum;
}
