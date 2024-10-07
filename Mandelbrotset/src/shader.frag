#version 330 core
out vec4 FragColor;

uniform float minReal;
uniform float maxReal;
uniform float minImg;
uniform float maxImg;
uniform int maxIterations;

void main()
{
    // Skärmpixelkoordinater
    float x = gl_FragCoord.x;
    float y = gl_FragCoord.y;

    // Konvertera pixelkoordinater till komplexa koordinater
    float cReal = minReal + (x / 800.0) * (maxReal - minReal);
    float cImg = maxImg - (y / 600.0) * (maxImg - minImg);

    // Mandelbrot-iterationer
    float zReal = 0.0;
    float zImg = 0.0;
    int iterations;
    for (iterations = 0; iterations < maxIterations; iterations++) {
        float zRealNew = zReal * zReal - zImg * zImg + cReal;
        float zImgNew = 2.0 * zReal * zImg + cImg;
        zReal = zRealNew;
        zImg = zImgNew;
        if (zReal * zReal + zImg * zImg > 4.0) break;
    }

    // Färgsättning
    float color = float(iterations) / float(maxIterations);
    FragColor = vec4(color, color * 0.5, color * 0.25, 1.0);
}
